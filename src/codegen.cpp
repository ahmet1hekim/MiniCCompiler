#include "codegen.h"
#include "ast.h"
#include <iostream>
#include <llvm/IR/Constants.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

CodeGenerator::CodeGenerator() {
  context = std::make_unique<LLVMContext>();
  module = std::make_unique<Module>("MiniC", *context);
  builder = std::make_unique<IRBuilder<>>(*context);
  currentFunction = nullptr;
  createPrintfDeclaration();
}

Type *CodeGenerator::getType(const std::string &typeStr) {
  if (typeStr == "int") {
    return Type::getInt32Ty(*context);
  } else if (typeStr == "float") {
    return Type::getFloatTy(*context);
  }
  return Type::getVoidTy(*context);
}

AllocaInst *CodeGenerator::createEntryBlockAlloca(Function *func,
                                                  const std::string &varName,
                                                  Type *type) {
  IRBuilder<> tmpBuilder(&func->getEntryBlock(), func->getEntryBlock().begin());
  return tmpBuilder.CreateAlloca(type, nullptr, varName);
}

void CodeGenerator::createPrintfDeclaration() {
  // Declare printf: int printf(i8*, ...)
  std::vector<Type *> printfArgs;
  printfArgs.push_back(PointerType::getUnqual(*context)); // char*

  FunctionType *printfType =
      FunctionType::get(Type::getInt32Ty(*context), printfArgs,
                        true // variadic
      );
  printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf",
                                module.get());
}

void CodeGenerator::generate(Program *prog) {
  if (!prog)
    return;

  // Generate code for the program
  prog->codegen(this);
}

Function *CodeGenerator::codegen(FunctionDecl *func) {
  // Create function type
  std::vector<Type *> paramTypes;
  for (const auto &param : func->getParams()) {
    paramTypes.push_back(getType(param->getType()));
  }

  Type *retType = getType(func->getReturnType());
  FunctionType *funcType = FunctionType::get(retType, paramTypes, false);

  // Create function
  Function *llvmFunc = Function::Create(funcType, Function::ExternalLinkage,
                                        func->getName(), module.get());

  // Store function for later use
  functions[func->getName()] = llvmFunc;
  currentFunction = llvmFunc;

  // Create entry basic block
  BasicBlock *entry = BasicBlock::Create(*context, "entry", llvmFunc);
  builder->SetInsertPoint(entry);

  // Clear named values for new function
  namedValues.clear();

  // Allocate parameters and store their values
  unsigned idx = 0;
  for (auto &arg : llvmFunc->args()) {
    const auto &param = func->getParams()[idx];
    AllocaInst *alloca =
        createEntryBlockAlloca(llvmFunc, param->getName(), arg.getType());
    builder->CreateStore(&arg, alloca);
    namedValues[param->getName()] = alloca;
    arg.setName(param->getName());
    idx++;
  }

  // Generate function body
  func->getBody()->codegen(this);

  // If the last block doesn't have a terminator, add a default return
  if (!builder->GetInsertBlock()->getTerminator()) {
    if (retType->isVoidTy()) {
      builder->CreateRetVoid();
    } else if (retType->isIntegerTy()) {
      builder->CreateRet(ConstantInt::get(retType, 0));
    } else {
      builder->CreateRet(ConstantFP::get(retType, 0.0));
    }
  }

  return llvmFunc;
}

Value *CodeGenerator::codegen(Parameter *param) {
  return nullptr; // Parameters are handled in FunctionDecl
}

Value *CodeGenerator::codegen(Statement *stmt) {
  return nullptr; // Base class, not used
}

Value *CodeGenerator::codegen(Block *block) {
  Value *last = nullptr;
  for (const auto &stmt : block->getStatements()) {
    last = stmt->codegen(this);
    // Stop if we hit a terminator
    if (builder->GetInsertBlock()->getTerminator()) {
      break;
    }
  }
  return last;
}

Value *CodeGenerator::codegen(VarDecl *varDecl) {
  Type *type = getType(varDecl->getType());
  AllocaInst *alloca =
      createEntryBlockAlloca(currentFunction, varDecl->getName(), type);
  namedValues[varDecl->getName()] = alloca;

  // Initialize to zero
  if (type->isIntegerTy()) {
    builder->CreateStore(ConstantInt::get(type, 0), alloca);
  } else {
    builder->CreateStore(ConstantFP::get(type, 0.0), alloca);
  }

  return alloca;
}

Value *CodeGenerator::codegen(AssignStmt *assign) {
  Value *val = assign->getExpr()->codegen(this);
  AllocaInst *var = namedValues[assign->getName()];
  if (!var) {
    std::cerr << "Unknown variable: " << assign->getName() << std::endl;
    return nullptr;
  }
  builder->CreateStore(val, var);
  return val;
}

Value *CodeGenerator::codegen(ReturnStmt *ret) {
  if (ret->getExpr()) {
    Value *retVal = ret->getExpr()->codegen(this);
    return builder->CreateRet(retVal);
  } else {
    return builder->CreateRetVoid();
  }
}

Value *CodeGenerator::codegen(IfStmt *ifStmt) {
  Value *cond = ifStmt->getCondition()->codegen(this);

  // Convert condition to bool
  cond = builder->CreateICmpNE(cond, ConstantInt::get(*context, APInt(32, 0)),
                               "ifcond");

  Function *func = builder->GetInsertBlock()->getParent();

  BasicBlock *thenBB = BasicBlock::Create(*context, "then", func);
  BasicBlock *elseBB =
      ifStmt->getElseBranch() ? BasicBlock::Create(*context, "else") : nullptr;
  BasicBlock *mergeBB = BasicBlock::Create(*context, "ifcont");

  if (elseBB) {
    builder->CreateCondBr(cond, thenBB, elseBB);
  } else {
    builder->CreateCondBr(cond, thenBB, mergeBB);
  }

  // Then block
  builder->SetInsertPoint(thenBB);
  ifStmt->getThenBranch()->codegen(this);
  if (!builder->GetInsertBlock()->getTerminator()) {
    builder->CreateBr(mergeBB);
  }

  // Else block
  if (elseBB) {
    elseBB->insertInto(func);
    builder->SetInsertPoint(elseBB);
    ifStmt->getElseBranch()->codegen(this);
    if (!builder->GetInsertBlock()->getTerminator()) {
      builder->CreateBr(mergeBB);
    }
  }

  // Merge block
  mergeBB->insertInto(func);
  builder->SetInsertPoint(mergeBB);

  return nullptr;
}

Value *CodeGenerator::codegen(WhileStmt *whileStmt) {
  Function *func = builder->GetInsertBlock()->getParent();

  BasicBlock *condBB = BasicBlock::Create(*context, "whilecond", func);
  BasicBlock *bodyBB = BasicBlock::Create(*context, "whilebody");
  BasicBlock *afterBB = BasicBlock::Create(*context, "afterwhile");

  // Jump to condition
  builder->CreateBr(condBB);

  // Condition block
  builder->SetInsertPoint(condBB);
  Value *cond = whileStmt->getCondition()->codegen(this);
  cond = builder->CreateICmpNE(cond, ConstantInt::get(*context, APInt(32, 0)),
                               "whilecond");
  builder->CreateCondBr(cond, bodyBB, afterBB);

  // Body block
  bodyBB->insertInto(func);
  builder->SetInsertPoint(bodyBB);
  whileStmt->getBody()->codegen(this);
  if (!builder->GetInsertBlock()->getTerminator()) {
    builder->CreateBr(condBB);
  }

  // After block
  afterBB->insertInto(func);
  builder->SetInsertPoint(afterBB);

  return nullptr;
}

Value *CodeGenerator::codegen(PrintStmt *print) {
  Value *val = print->getExpr()->codegen(this);

  // Create format string
  Value *formatStr;
  if (val->getType()->isIntegerTy()) {
    formatStr = builder->CreateGlobalString("%d\n", "", 0, module.get());
  } else {
    formatStr = builder->CreateGlobalString("%f\n", "", 0, module.get());
    // Promote float to double for printf variadic argument
    if (val->getType()->isFloatTy()) {
      val = builder->CreateFPExt(val, Type::getDoubleTy(*context), "float_ext");
    }
  }

  // Call printf
  std::vector<Value *> args = {formatStr, val};
  return builder->CreateCall(printfFunc, args, "printfcall");
}

Value *CodeGenerator::codegen(Expression *expr) {
  return nullptr; // Base class, not used
}

Value *CodeGenerator::codegen(Number *num) {
  return ConstantInt::get(*context, APInt(32, num->getValue(), true));
}

Value *CodeGenerator::codegen(Float *flt) {
  return ConstantFP::get(*context, APFloat(flt->getValue()));
}

Value *CodeGenerator::codegen(Variable *var) {
  AllocaInst *alloca = namedValues[var->getName()];
  if (!alloca) {
    std::cerr << "Unknown variable: " << var->getName() << std::endl;
    return nullptr;
  }
  return builder->CreateLoad(alloca->getAllocatedType(), alloca,
                             var->getName().c_str());
}

Value *CodeGenerator::codegen(BinaryExpr *binExpr) {
  Value *L = binExpr->getLeft()->codegen(this);
  Value *R = binExpr->getRight()->codegen(this);

  if (!L || !R)
    return nullptr;

  const std::string &op = binExpr->getOp();

  // Check if we're dealing with floats
  bool isFloat = L->getType()->isFloatTy() || R->getType()->isFloatTy();

  // Arithmetic operations
  if (op == "+") {
    return isFloat ? builder->CreateFAdd(L, R, "addtmp")
                   : builder->CreateAdd(L, R, "addtmp");
  } else if (op == "-") {
    return isFloat ? builder->CreateFSub(L, R, "subtmp")
                   : builder->CreateSub(L, R, "subtmp");
  } else if (op == "*") {
    return isFloat ? builder->CreateFMul(L, R, "multmp")
                   : builder->CreateMul(L, R, "multmp");
  } else if (op == "/") {
    return isFloat ? builder->CreateFDiv(L, R, "divtmp")
                   : builder->CreateSDiv(L, R, "divtmp");
  }
  // Comparison operations
  else if (op == "<") {
    Value *cmp = isFloat ? builder->CreateFCmpULT(L, R, "cmptmp")
                         : builder->CreateICmpSLT(L, R, "cmptmp");
    return builder->CreateZExt(cmp, Type::getInt32Ty(*context), "booltmp");
  } else if (op == ">") {
    Value *cmp = isFloat ? builder->CreateFCmpUGT(L, R, "cmptmp")
                         : builder->CreateICmpSGT(L, R, "cmptmp");
    return builder->CreateZExt(cmp, Type::getInt32Ty(*context), "booltmp");
  } else if (op == "<=") {
    Value *cmp = isFloat ? builder->CreateFCmpULE(L, R, "cmptmp")
                         : builder->CreateICmpSLE(L, R, "cmptmp");
    return builder->CreateZExt(cmp, Type::getInt32Ty(*context), "booltmp");
  } else if (op == ">=") {
    Value *cmp = isFloat ? builder->CreateFCmpUGE(L, R, "cmptmp")
                         : builder->CreateICmpSGE(L, R, "cmptmp");
    return builder->CreateZExt(cmp, Type::getInt32Ty(*context), "booltmp");
  } else if (op == "==") {
    Value *cmp = isFloat ? builder->CreateFCmpUEQ(L, R, "cmptmp")
                         : builder->CreateICmpEQ(L, R, "cmptmp");
    return builder->CreateZExt(cmp, Type::getInt32Ty(*context), "booltmp");
  } else if (op == "!=") {
    Value *cmp = isFloat ? builder->CreateFCmpUNE(L, R, "cmptmp")
                         : builder->CreateICmpNE(L, R, "cmptmp");
    return builder->CreateZExt(cmp, Type::getInt32Ty(*context), "booltmp");
  }

  std::cerr << "Unknown binary operator: " << op << std::endl;
  return nullptr;
}

Value *CodeGenerator::codegen(CallExpr *call) {
  Function *callee = functions[call->getName()];
  if (!callee) {
    std::cerr << "Unknown function: " << call->getName() << std::endl;
    return nullptr;
  }

  std::vector<Value *> args;
  for (const auto &arg : call->getArgs()) {
    args.push_back(arg->codegen(this));
  }

  return builder->CreateCall(callee, args, "calltmp");
}

void CodeGenerator::printIR() { module->print(outs(), nullptr); }
