#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Verifier.h>
#include <map>
#include <string>
#include <memory>

// Forward declarations
class Program;
class FunctionDecl;
class Parameter;
class Statement;
class Block;
class VarDecl;
class AssignStmt;
class ReturnStmt;
class IfStmt;
class WhileStmt;
class PrintStmt;
class Expression;
class Number;
class Float;
class Variable;
class BinaryExpr;
class CallExpr;

class CodeGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    
    // Symbol tables
    std::map<std::string, llvm::AllocaInst*> namedValues;  // Local variables
    std::map<std::string, llvm::Function*> functions;       // Function declarations
    
    // Current function being generated
    llvm::Function* currentFunction;
    
    // Printf function for print statements
    llvm::Function* printfFunc;
    
    // Helper methods
    llvm::Type* getType(const std::string& typeStr);
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* func, const std::string& varName, llvm::Type* type);
    void createPrintfDeclaration();
    
public:
    CodeGenerator();
    ~CodeGenerator() = default;
    
    // Main code generation entry point
    void generate(Program* prog);
    
    // Code generation for different AST nodes
    llvm::Function* codegen(FunctionDecl* func);
    llvm::Value* codegen(Parameter* param);
    llvm::Value* codegen(Statement* stmt);
    llvm::Value* codegen(Block* block);
    llvm::Value* codegen(VarDecl* varDecl);
    llvm::Value* codegen(AssignStmt* assign);
    llvm::Value* codegen(ReturnStmt* ret);
    llvm::Value* codegen(IfStmt* ifStmt);
    llvm::Value* codegen(WhileStmt* whileStmt);
    llvm::Value* codegen(PrintStmt* print);
    
    llvm::Value* codegen(Expression* expr);
    llvm::Value* codegen(Number* num);
    llvm::Value* codegen(Float* flt);
    llvm::Value* codegen(Variable* var);
    llvm::Value* codegen(BinaryExpr* binExpr);
    llvm::Value* codegen(CallExpr* call);
    
    // Output methods
    void printIR();
    llvm::Module* getModule() { return module.get(); }
    
    // Context access
    llvm::LLVMContext& getContext() { return *context; }
};

#endif // CODEGEN_H
