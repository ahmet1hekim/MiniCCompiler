#ifndef AST_H
#define AST_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class CodeGenContext;
namespace llvm {
    class Value;
}

// Base class for all AST nodes
class ASTNode {
public:
  virtual ~ASTNode() = default;
  virtual void print(int indent = 0) const = 0;

  // Generate DOT output
  // returns the unique ID of this node
  virtual int generateDOT(ostream &out, int &count) const = 0;
  virtual llvm::Value* codegen(CodeGenContext& ctx) = 0;

  void printIndent(int indent) const {
    for (int i = 0; i < indent; ++i)
      cout << "  ";
  }
};

// Expressions
class Expression : public ASTNode {};

class Number : public Expression {
public:
  int value;

  Number(int v) : value(v) {}
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Number: " << value << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Number: " << value << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class Float : public Expression {
public:
  float value;

  Float(float v) : value(v) {}
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Float: " << value << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Float: " << value << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class Variable : public Expression {
public:
  string name;

  Variable(const string &n) : name(n) {}
  void print(int indent = 0) const override {
    printIndent(indent);
    cout << "Variable: " << name << endl;
  }
  int generateDOT(ostream &out, int &count) const override {
    int id = count++;
    out << "  node" << id << " [label=\"Variable: " << name << "\"];" << endl;
    return id;
  }
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class CallExpr : public Expression {
public:
  string name;
  vector<unique_ptr<Expression>> args;

  CallExpr(const string &n, vector<Expression *> *a) : name(n) {
    if (a) {
      for (auto *expr : *a) {
        args.emplace_back(expr);
      }
      delete a;
    }
  }
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class BinaryExpr : public Expression {
public:
  string op;
  unique_ptr<Expression> left, right;

  BinaryExpr(Expression *l, const string &o, Expression *r)
      : left(l), op(o), right(r) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

// Statements
class Statement : public ASTNode {};

class VarDecl : public Statement {
public:
  string type;
  string name;

  VarDecl(const string &t, const string &n) : type(t), name(n) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class AssignStmt : public Statement {
public:
  string name;
  unique_ptr<Expression> expr;

  AssignStmt(const string &n, Expression *e) : name(n), expr(e) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class PrintStmt : public Statement {
public:
  unique_ptr<Expression> expr;

  PrintStmt(Expression *e) : expr(e) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class ReturnStmt : public Statement {
public:
  unique_ptr<Expression> expr;

  ReturnStmt(Expression *e) : expr(e) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class IfStmt : public Statement {
public:
  unique_ptr<Expression> condition;
  unique_ptr<Statement> thenBranch;
  unique_ptr<Statement> elseBranch;

  IfStmt(Expression *c, Statement *t, Statement *e = nullptr)
      : condition(c), thenBranch(t), elseBranch(e) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class WhileStmt : public Statement {
public:
  unique_ptr<Expression> condition;
  unique_ptr<Statement> body;

  WhileStmt(Expression *c, Statement *b) : condition(c), body(b) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class Block : public Statement {
public:
  vector<unique_ptr<Statement>> statements;

  void addStatement(Statement *stmt) { statements.emplace_back(stmt); }
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

// Top Level
class Parameter : public ASTNode {
public:
  string type;
  string name;

  Parameter(const string &t, const string &n) : type(t), name(n) {}
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class FunctionDecl : public ASTNode {
public:
  string returnType;
  string name;
  vector<unique_ptr<Parameter>> params;
  unique_ptr<Block> body;

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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

class Program : public ASTNode {
public:
  vector<unique_ptr<FunctionDecl>> functions;

  void addFunction(FunctionDecl *func) { functions.emplace_back(func); }
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
  llvm::Value* codegen(CodeGenContext& ctx) override;
};

#endif
