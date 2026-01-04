#ifndef CODEGEN_CONTEXT_H
#define CODEGEN_CONTEXT_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <iostream>

struct CodeGenContext {
    llvm::LLVMContext llvmContext;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;
    
    // Symbol table variables: map variable name to its memory address (AllocaInst)
    // We use a list of maps to handle nested scopes (shadowing).
    std::list<std::map<std::string, llvm::AllocaInst*>> locals;

    CodeGenContext() : builder(llvmContext) {
        module = std::make_unique<llvm::Module>("minic", llvmContext);
    }

    // Start a new scope
    void pushBlock() {
        locals.push_front(std::map<std::string, llvm::AllocaInst*>());
    }

    // End the current scope
    void popBlock() {
        locals.pop_front();
    }

    // Register a variable in the current code
    void setVal(const std::string& name, llvm::AllocaInst* val) {
        locals.front()[name] = val;
    }

    // Look up a variable, searching from inner-most scope outwards
    llvm::AllocaInst* getVal(const std::string& name) {
        for (auto& scope : locals) {
            if (scope.find(name) != scope.end()) {
                return scope[name];
            }
        }
        return nullptr;
    }
};

#endif
