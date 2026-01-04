#include "ast.h"
#include "codegen.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <vector>
#include <string>

using namespace llvm;

// Expression implementations

Value* Number::codegen(CodeGenerator* gen) {
    return ConstantInt::get(gen->getContext(), APInt(32, getValue(), true));
}

Value* Float::codegen(CodeGenerator* gen) {
    return ConstantFP::get(gen->getContext(), APFloat(getValue()));
}

Value* Variable::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* BinaryExpr::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* CallExpr::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

// Statement implementations

Value* VarDecl::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* AssignStmt::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* ReturnStmt::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* IfStmt::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* WhileStmt::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* PrintStmt::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* Block::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

// Top-level implementations

Value* Parameter::codegen(CodeGenerator* gen) {
    return gen->codegen(this);
}

Value* FunctionDecl::codegen(CodeGenerator* gen) {
    Function* func = gen->codegen(this);
    return func;
}

Value* Program::codegen(CodeGenerator* gen) {
    for (const auto& func : getFunctions()) {
        func->codegen(gen);
    }
    return nullptr;
}
