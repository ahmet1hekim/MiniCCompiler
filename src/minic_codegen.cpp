#include "ast.h"
#include "codegen_context.h"
#include <iostream>
#include <vector>

#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Helper to create alloca in the entry block
static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, StringRef VarName, Type* type) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, VarName);
}

// Helper to get LLVM type from string
static Type* getLLVMType(const std::string& typeName, LLVMContext& ctx) {
    if (typeName == "int") return Type::getInt32Ty(ctx);
    if (typeName == "float") return Type::getFloatTy(ctx);
    if (typeName == "void") return Type::getVoidTy(ctx);
    return nullptr;
}


llvm::Value* Number::codegen(CodeGenContext& ctx) {
    // Return Value*
    return ConstantInt::get(Type::getInt32Ty(ctx.llvmContext), value, true);
}

llvm::Value* Float::codegen(CodeGenContext& ctx) {
    return ConstantFP::get(Type::getFloatTy(ctx.llvmContext), value);
}

llvm::Value* Variable::codegen(CodeGenContext& ctx) {
    AllocaInst* alloc = ctx.getVal(name);
    if (!alloc) {
        std::cerr << "Error: Unknown variable name " << name << std::endl;
        return nullptr;
    }
    return ctx.builder.CreateLoad(alloc->getAllocatedType(), alloc, name.c_str());
}

llvm::Value* BinaryExpr::codegen(CodeGenContext& ctx) {
    Value* L = left->codegen(ctx);
    Value* R = right->codegen(ctx);
    if (!L || !R) return nullptr;

    // Type checking/casting
    bool isFloat = L->getType()->isFloatTy() || R->getType()->isFloatTy();
    if (isFloat) {
        if (!L->getType()->isFloatTy()) L = ctx.builder.CreateSIToFP(L, Type::getFloatTy(ctx.llvmContext), "casttmp");
        if (!R->getType()->isFloatTy()) R = ctx.builder.CreateSIToFP(R, Type::getFloatTy(ctx.llvmContext), "casttmp");
    }

    if (op == "+") return isFloat ? ctx.builder.CreateFAdd(L, R, "addtmp") : ctx.builder.CreateAdd(L, R, "addtmp");
    if (op == "-") return isFloat ? ctx.builder.CreateFSub(L, R, "subtmp") : ctx.builder.CreateSub(L, R, "subtmp");
    if (op == "*") return isFloat ? ctx.builder.CreateFMul(L, R, "multmp") : ctx.builder.CreateMul(L, R, "multmp");
    if (op == "/") return isFloat ? ctx.builder.CreateFDiv(L, R, "divtmp") : ctx.builder.CreateSDiv(L, R, "divtmp"); 
    
    // Comparisons return i1, we need to cast to i32 for C semantics (0/1)
    Value* cmp = nullptr;
    if (op == "==") cmp = isFloat ? ctx.builder.CreateFCmpOEQ(L, R, "cmptmp") : ctx.builder.CreateICmpEQ(L, R, "cmptmp");
    else if (op == "!=") cmp = isFloat ? ctx.builder.CreateFCmpONE(L, R, "cmptmp") : ctx.builder.CreateICmpNE(L, R, "cmptmp");
    else if (op == "<") cmp = isFloat ? ctx.builder.CreateFCmpOLT(L, R, "cmptmp") : ctx.builder.CreateICmpSLT(L, R, "cmptmp");
    else if (op == ">") cmp = isFloat ? ctx.builder.CreateFCmpOGT(L, R, "cmptmp") : ctx.builder.CreateICmpSGT(L, R, "cmptmp");
    else if (op == "<=") cmp = isFloat ? ctx.builder.CreateFCmpOLE(L, R, "cmptmp") : ctx.builder.CreateICmpSLE(L, R, "cmptmp");
    else if (op == ">=") cmp = isFloat ? ctx.builder.CreateFCmpOGE(L, R, "cmptmp") : ctx.builder.CreateICmpSGE(L, R, "cmptmp");
    
    if (cmp) {
        return ctx.builder.CreateZExt(cmp, Type::getInt32Ty(ctx.llvmContext), "booltmp");
    }

    std::cerr << "Error: Unknown binary operator " << op << std::endl;
    return nullptr;
}

llvm::Value* CallExpr::codegen(CodeGenContext& ctx) {
    Function* CalleeF = ctx.module->getFunction(name);
    if (!CalleeF) {
        std::cerr << "Error: Unknown function referenced " << name << std::endl;
        return nullptr;
    }

    if (CalleeF->arg_size() != args.size()) {
        std::cerr << "Error: Incorrect number of arguments passed to function " << name << std::endl;
        return nullptr;
    }

    std::vector<Value*> ArgsV;
    for (unsigned i = 0, e = args.size(); i != e; ++i) {
        Value* argVal = args[i]->codegen(ctx);
        if (!argVal) return nullptr;
        
        // Basic Type casting for arguments if needed? For now assume strict or auto-cast to float if needed.
        Type* expectedType = CalleeF->getArg(i)->getType();
        if (argVal->getType() != expectedType) {
             if (expectedType->isFloatTy() && argVal->getType()->isIntegerTy()) {
                 argVal = ctx.builder.CreateSIToFP(argVal, expectedType, "argcast");
             } else if (expectedType->isIntegerTy() && argVal->getType()->isFloatTy()) {
                 argVal = ctx.builder.CreateFPToSI(argVal, expectedType, "argcast");
             }
             // else .. strict check?
        }
        
        ArgsV.push_back(argVal);
    }

    return ctx.builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

llvm::Value* VarDecl::codegen(CodeGenContext& ctx) {
    Function* TheFunction = ctx.builder.GetInsertBlock()->getParent();
    Type* llvmType = getLLVMType(type, ctx.llvmContext);
    
    AllocaInst* Alloca = CreateEntryBlockAlloca(TheFunction, name, llvmType);
    ctx.setVal(name, Alloca);
    
    // Default initialize to 0. Cast to Value* to avoid type mismatch in ternary.
    Value* zero = (type == "float") ? (Value*)ConstantFP::get(ctx.llvmContext, APFloat(0.0f)) : (Value*)ConstantInt::get(Type::getInt32Ty(ctx.llvmContext), 0, true);
    ctx.builder.CreateStore(zero, Alloca);

    return Alloca;
}

llvm::Value* AssignStmt::codegen(CodeGenContext& ctx) {
    Value* Val = expr->codegen(ctx);
    if (!Val) return nullptr;

    AllocaInst* Alloca = ctx.getVal(name);
    if (!Alloca) {
        std::cerr << "Error: Unknown variable name " << name << std::endl;
        return nullptr;
    }

    // Implicit cast logic
    if (Alloca->getAllocatedType()->isFloatTy() && Val->getType()->isIntegerTy()) {
        Val = ctx.builder.CreateSIToFP(Val, Type::getFloatTy(ctx.llvmContext), "cast");
    } else if (Alloca->getAllocatedType()->isIntegerTy() && Val->getType()->isFloatTy()) {
        Val = ctx.builder.CreateFPToSI(Val, Type::getInt32Ty(ctx.llvmContext), "cast");
    }

    ctx.builder.CreateStore(Val, Alloca);
    return Val;
}

llvm::Value* Block::codegen(CodeGenContext& ctx) {
    for (const auto& stmt : statements) {
        stmt->codegen(ctx);
    }
    return nullptr;
}


llvm::Value* ReturnStmt::codegen(CodeGenContext& ctx) {
    Value* RetVal = nullptr;
    if (expr) {
        RetVal = expr->codegen(ctx);
        // Cast to function return type? We strictly don't know it here easily without looking up current function.
        // Assuming user writes correct types or we cast locally.
        // Let's rely on LLVM to check types or just auto-cast if we can find the function.
        // Getting current function: 
        Function* TheFunction = ctx.builder.GetInsertBlock()->getParent();
        Type* retType = TheFunction->getReturnType();
        
        if (retType->isFloatTy() && RetVal->getType()->isIntegerTy()) 
             RetVal = ctx.builder.CreateSIToFP(RetVal, retType, "cast");
        else if (retType->isIntegerTy() && RetVal->getType()->isFloatTy())
             RetVal = ctx.builder.CreateFPToSI(RetVal, retType, "cast");
        
        ctx.builder.CreateRet(RetVal);
    } else {
        ctx.builder.CreateRetVoid();
    }
    return RetVal;
}

llvm::Value* IfStmt::codegen(CodeGenContext& ctx) {
    Value* CondV = condition->codegen(ctx);
    if (!CondV) return nullptr;

    // Convert to bool (i1)
    if (CondV->getType()->isFloatTy())
        CondV = ctx.builder.CreateFCmpONE(CondV, ConstantFP::get(ctx.llvmContext, APFloat(0.0f)), "ifcond");
    else
        CondV = ctx.builder.CreateICmpNE(CondV, ConstantInt::get(Type::getInt32Ty(ctx.llvmContext), 0), "ifcond");

    Function* TheFunction = ctx.builder.GetInsertBlock()->getParent();

    BasicBlock* ThenBB = BasicBlock::Create(ctx.llvmContext, "then", TheFunction);
    BasicBlock* ElseBB = BasicBlock::Create(ctx.llvmContext, "else");
    BasicBlock* MergeBB = BasicBlock::Create(ctx.llvmContext, "ifcont");

    bool hasElse = (elseBranch != nullptr);

    ctx.builder.CreateCondBr(CondV, ThenBB, hasElse ? ElseBB : MergeBB);

    // Emit Then
    ctx.builder.SetInsertPoint(ThenBB);
    
    // Scope for then block?
    ctx.pushBlock();
    thenBranch->codegen(ctx);
    ctx.popBlock();
    
    // If the block didn't return (terminator), branch to merge
    if (!ctx.builder.GetInsertBlock()->getTerminator())
        ctx.builder.CreateBr(MergeBB);

    // Emit Else
    if (hasElse) {
        // TheFunction->getBasicBlockList().push_back(ElseBB); // Private, user insertInto
        ElseBB->insertInto(TheFunction);
        ctx.builder.SetInsertPoint(ElseBB);
        
        ctx.pushBlock();
        elseBranch->codegen(ctx);
        ctx.popBlock();
        
         if (!ctx.builder.GetInsertBlock()->getTerminator())
            ctx.builder.CreateBr(MergeBB);
    }

    // TheFunction->getBasicBlockList().push_back(MergeBB);
    MergeBB->insertInto(TheFunction);
    ctx.builder.SetInsertPoint(MergeBB);

    return nullptr;
}


llvm::Value* WhileStmt::codegen(CodeGenContext& ctx) {
    Function* TheFunction = ctx.builder.GetInsertBlock()->getParent();

    BasicBlock* CondBB = BasicBlock::Create(ctx.llvmContext, "whilecond", TheFunction);
    BasicBlock* LoopBB = BasicBlock::Create(ctx.llvmContext, "whileloop", TheFunction);
    BasicBlock* AfterBB = BasicBlock::Create(ctx.llvmContext, "afterwhile"); 

    ctx.builder.CreateBr(CondBB);

    ctx.builder.SetInsertPoint(CondBB);
    Value* CondV = condition->codegen(ctx);
    if (!CondV) return nullptr;

    if (CondV->getType()->isFloatTy())
        CondV = ctx.builder.CreateFCmpONE(CondV, ConstantFP::get(ctx.llvmContext, APFloat(0.0f)), "loopcond");
    else
        CondV = ctx.builder.CreateICmpNE(CondV, ConstantInt::get(Type::getInt32Ty(ctx.llvmContext), 0), "loopcond");

    ctx.builder.CreateCondBr(CondV, LoopBB, AfterBB);

    ctx.builder.SetInsertPoint(LoopBB);
    ctx.pushBlock();
    body->codegen(ctx);
    ctx.popBlock();
    
    if (!ctx.builder.GetInsertBlock()->getTerminator())
        ctx.builder.CreateBr(CondBB);

    // TheFunction->getBasicBlockList().push_back(AfterBB);
    AfterBB->insertInto(TheFunction);
    ctx.builder.SetInsertPoint(AfterBB);
    
    return nullptr;
}

llvm::Value* PrintStmt::codegen(CodeGenContext& ctx) {
    Value* Val = expr->codegen(ctx);
    if (!Val) return nullptr;
    
    std::string fmt;
    if (Val->getType()->isIntegerTy()) fmt = "%d\n";
    else if (Val->getType()->isFloatTy()) fmt = "%f\n";
    else fmt = "%d\n"; // default
    
    // Declare printf
    Function* PrintfF = ctx.module->getFunction("printf");
    if (!PrintfF) {
        // Use opaque pointer type (ptr) for first arg
        std::vector<Type*> args = { PointerType::getUnqual(ctx.llvmContext) };
        FunctionType* FT = FunctionType::get(Type::getInt32Ty(ctx.llvmContext), args, true);
        PrintfF = Function::Create(FT, Function::ExternalLinkage, "printf", ctx.module.get());
    }
    
    // Constant string for format, use CreateGlobalString
    Value* FmtStr = ctx.builder.CreateGlobalString(fmt);
    
    std::vector<Value*> ArgsV;
    ArgsV.push_back(FmtStr);
    
    if (Val->getType()->isFloatTy()) {
        // printf expects double for %f
        Val = ctx.builder.CreateFPExt(Val, Type::getDoubleTy(ctx.llvmContext));
    }
    ArgsV.push_back(Val);
    
    ctx.builder.CreateCall(PrintfF, ArgsV, "printcall");
    return nullptr;
}

llvm::Value* Parameter::codegen(CodeGenContext& ctx) {
    // Handled in FunctionDecl
    return nullptr;
}

llvm::Value* FunctionDecl::codegen(CodeGenContext& ctx) {
    std::vector<Type*> argTypes;
    for (auto& param : params) {
        argTypes.push_back(getLLVMType(param->type, ctx.llvmContext));
    }
    
    Type* retType = getLLVMType(returnType, ctx.llvmContext);
    FunctionType* FT = FunctionType::get(retType, argTypes, false);
    Function* F = Function::Create(FT, Function::ExternalLinkage, name, ctx.module.get());
    
    // Create new block
    BasicBlock* BB = BasicBlock::Create(ctx.llvmContext, "entry", F);
    ctx.builder.SetInsertPoint(BB);
    
    ctx.pushBlock();
    
    // Set arguments names and create allocas
    unsigned Idx = 0;
    for (auto& Arg : F->args()) {
        std::string argName = params[Idx]->name;
        Arg.setName(argName);
        AllocaInst* Alloca = CreateEntryBlockAlloca(F, argName, Arg.getType());
        ctx.builder.CreateStore(&Arg, Alloca);
        ctx.setVal(argName, Alloca);
        Idx++;
    }
    
    body->codegen(ctx);
    
    // Return void if no explicit return?
    if (!ctx.builder.GetInsertBlock()->getTerminator()) {
        if (retType->isVoidTy()) ctx.builder.CreateRetVoid();
        else {
             // Return default 0
             Value* zero = (retType->isFloatTy()) ? (Value*)ConstantFP::get(ctx.llvmContext, APFloat(0.0f)) : (Value*)ConstantInt::get(Type::getInt32Ty(ctx.llvmContext), 0, true);
             ctx.builder.CreateRet(zero);
        }
    }
    
    ctx.popBlock();
    
    verifyFunction(*F);
    
    return F;
}

llvm::Value* Program::codegen(CodeGenContext& ctx) {
    for (const auto& func : functions) {
        func->codegen(ctx);
    }
    return nullptr;
}
