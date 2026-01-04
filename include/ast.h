#ifndef AST_H
#define AST_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declaration for LLVM
namespace llvm {
    class Value;
}

// Forward declaration for code generator
class CodeGenerator;

using namespace std;

// Base class for all AST nodes
class ASTNode {
public:
  virtual ~ASTNode() = default;
  virtual void print(int indent = 0) const = 0;

  // Generate DOT output
  // returns the unique ID of this node
  virtual int generateDOT(ostream &out, int &count) const = 0;
  
  // Generate LLVM IR
  virtual llvm::Value* codegen(CodeGenerator* gen) = 0;

  void printIndent(int indent) const {
    for (int i = 0; i < indent; ++i)
      cout << "  ";
  }
};

// Expressions
class Expression : public ASTNode {};

class Number : public Expression {
  int value;

public:
  Number(int v) : value(v) {}
  int getValue() const { return value; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Number: " << value << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Number: " << value << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class Float : public Expression {
  float value;

public:
  Float(float v) : value(v) {}
  float getValue() const { return value; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Float: " << value << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Float: " << value << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class Variable : public Expression {
  string name;

public:
  Variable(const string &n) : name(n) {}
  const string& getName() const { return name; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Variable: " << name << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Variable: " << name << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class CallExpr : public Expression {
  string name;
  vector<unique_ptr<Expression>> args;

public:
  CallExpr(const string &n, vector<Expression *> *a) : name(n) {
    if (a) {
      for (auto *expr : *a) {
        args.emplace_back(expr);
      }
      delete a;
    }
  }
  const string& getName() const { return name; }
  const vector<unique_ptr<Expression>>& getArgs() const { return args; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Call: " << name << endl;
    for (const auto &arg : args) {
      arg->print(indent + 1);
    }
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Call: " << name << "\"];" << endl;
    for (const auto &arg : args) {
      int childId = arg->generateDOT(out, count);
      out << "  node" << id << " -> node" << childId << ";" << endl;
    }
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class BinaryExpr : public Expression {
  string op;
  unique_ptr<Expression> left, right;

public:
  BinaryExpr(Expression *l, const string &o, Expression *r)
      : left(l), op(o), right(r) {}
  const string& getOp() const { return op; }
  Expression* getLeft() const { return left.get(); }
  Expression* getRight() const { return right.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "BinaryExpr: " << op << endl;
    left->print(indent + 1);
    right->print(indent + 1);
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Op: " << op << "\"];" << endl;
    int leftId = left->generateDOT(out, count);
    int rightId = right->generateDOT(out, count);
    out << "  node" << id << " -> node" << leftId << ";" << endl;
    out << "  node" << id << " -> node" << rightId << ";" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

// Statements
class Statement : public ASTNode {};

class VarDecl : public Statement {
  string type;
  string name;

public:
  VarDecl(const string &t, const string &n) : type(t), name(n) {}
  const string& getType() const { return type; }
  const string& getName() const { return name; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "VarDecl: " << type << " " << name << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"VarDecl: " << type << " " << name
        << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class AssignStmt : public Statement {
  string name;
  unique_ptr<Expression> expr;

public:
  AssignStmt(const string &n, Expression *e) : name(n), expr(e) {}
  const string& getName() const { return name; }
  Expression* getExpr() const { return expr.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Assign: " << name << endl;
    expr->print(indent + 1);
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Assign: " << name << "\"];" << endl;
    int exprId = expr->generateDOT(out, count);
    out << "  node" << id << " -> node" << exprId << ";" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class PrintStmt : public Statement {
  unique_ptr<Expression> expr;

public:
  PrintStmt(Expression *e) : expr(e) {}
  Expression* getExpr() const { return expr.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Print" << endl;
    expr->print(indent + 1);
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Print\"];" << endl;
    int exprId = expr->generateDOT(out, count);
    out << "  node" << id << " -> node" << exprId << ";" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class ReturnStmt : public Statement {
  unique_ptr<Expression> expr;

public:
  ReturnStmt(Expression *e) : expr(e) {}
  Expression* getExpr() const { return expr.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Return" << endl;
    if (expr)
      expr->print(indent + 1);
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Return\"];" << endl;
    if (expr) {
      int exprId = expr->generateDOT(out, count);
      out << "  node" << id << " -> node" << exprId << ";" << endl;
    }
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class IfStmt : public Statement {
  unique_ptr<Expression> condition;
  unique_ptr<Statement> thenBranch;
  unique_ptr<Statement> elseBranch;

public:
  IfStmt(Expression *c, Statement *t, Statement *e = nullptr)
      : condition(c), thenBranch(t), elseBranch(e) {}
  Expression* getCondition() const { return condition.get(); }
  Statement* getThenBranch() const { return thenBranch.get(); }
  Statement* getElseBranch() const { return elseBranch.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "If" << endl;
    condition->print(indent + 1);
    thenBranch->print(indent + 1);
    if (elseBranch) {
      printIndent(indent);
      cout << "Else" << endl;
      elseBranch->print(indent + 1);
    }
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"If\"];" << endl;

    int condId = condition->generateDOT(out, count);
    out << "  node" << id << " -> node" << condId << " [label=\"cond\"];"
        << endl;

    int thenId = thenBranch->generateDOT(out, count);
    out << "  node" << id << " -> node" << thenId << " [label=\"then\"];"
        << endl;

    if (elseBranch) {
      int elseId = elseBranch->generateDOT(out, count);
      out << "  node" << id << " -> node" << elseId << " [label=\"else\"];"
          << endl;
    }
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class WhileStmt : public Statement {
  unique_ptr<Expression> condition;
  unique_ptr<Statement> body;

public:
  WhileStmt(Expression *c, Statement *b) : condition(c), body(b) {}
  Expression* getCondition() const { return condition.get(); }
  Statement* getBody() const { return body.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "While" << endl;
    condition->print(indent + 1);
    body->print(indent + 1);
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"While\"];" << endl;

    int condId = condition->generateDOT(out, count);
    out << "  node" << id << " -> node" << condId << " [label=\"cond\"];"
        << endl;

    int bodyId = body->generateDOT(out, count);
    out << "  node" << id << " -> node" << bodyId << " [label=\"body\"];"
        << endl;

    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class Block : public Statement {
  vector<unique_ptr<Statement>> statements;

public:
  void addStatement(Statement *stmt) { statements.emplace_back(stmt); }
  const vector<unique_ptr<Statement>>& getStatements() const { return statements; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Block" << endl;
    for (const auto &stmt : statements) {
      stmt->print(indent + 1);
    }
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Block\"];" << endl;
    for (const auto &stmt : statements) {
      int stmtId = stmt->generateDOT(out, count);
      out << "  node" << id << " -> node" << stmtId << ";" << endl;
    }
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

// Top Level
class Parameter : public ASTNode {
  string type;
  string name;

public:
  Parameter(const string &t, const string &n) : type(t), name(n) {}
  const string& getType() const { return type; }
  const string& getName() const { return name; }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Param: " << type << " " << name << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Param: " << type << " " << name
        << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class FunctionDecl : public ASTNode {
  string returnType;
  string name;
  vector<unique_ptr<Parameter>> params;
  unique_ptr<Block> body;

public:
  FunctionDecl(const string &rt, const string &n, vector<Parameter *> *p,
               Block *b)
      : returnType(rt), name(n), body(b) {
    if (p) {
      for (auto *param : *p) {
        params.emplace_back(param);
      }
      delete p;
    }
  }
  const string& getReturnType() const { return returnType; }
  const string& getName() const { return name; }
  const vector<unique_ptr<Parameter>>& getParams() const { return params; }
  Block* getBody() const { return body.get(); }
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Function: " << returnType << " " << name << endl;
    for (const auto &param : params) {
      param->print(indent + 1);
    }
    body->print(indent + 1);
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Function: " << returnType << " " << name
        << "\"];" << endl;
    for (const auto &param : params) {
      int paramId = param->generateDOT(out, count);
      out << "  node" << id << " -> node" << paramId << ";" << endl;
    }
    int bodyId = body->generateDOT(out, count);
    out << "  node" << id << " -> node" << bodyId << ";" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

class Program : public ASTNode {
  vector<unique_ptr<FunctionDecl>> functions;

public:
  void addFunction(FunctionDecl *func) { functions.emplace_back(func); }
  const vector<unique_ptr<FunctionDecl>>& getFunctions() const { return functions; }
  void print(int indent = 0) const override {
    cout << "Program" << endl;
    for (const auto &func : functions) {
      func->print(indent + 1);
    }
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "digraph AST {" << endl;
    out << "  node" << id << " [label=\"Program\"];" << endl;
    for (const auto &func : functions) {
      int funcId = func->generateDOT(out, count);
      out << "  node" << id << " -> node" << funcId << ";" << endl;
    }
    out << "}" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenerator* gen) override;
};

#endif
