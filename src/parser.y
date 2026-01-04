/*
 * Mini C Parser
 * This file defines the grammar rules and builds the AST.
 */

%{
#include <iostream>
#include <string>
#include <vector>
#include "ast.h"

using namespace std;

// External lexer function
extern int yylex();
// Error handling function
void yyerror(const char *s);

// Global root of the AST
Program* root = nullptr;
%}
/* Union to hold different types of values */
%union {
    int ival;
    float fval;
    char* sval;
    ASTNode* node;
    Expression* expr;
    Statement* stmt;
    Block* block;
    FunctionDecl* func;
    Program* prog;
    vector<Parameter*>* params;
    vector<Expression*>* args;
}

/* Tokens */
%token <sval> ID
%token <ival> NUM
%token <fval> FLOAT_LIT
%token KW_INT KW_FLOAT KW_RETURN KW_IF KW_ELSE KW_WHILE KW_PRINT
%token EQ NEQ LE GE ASSIGN LT GT PLUS MINUS MUL DIV
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE

/* Non-terminal types */
%type <prog> program
%type <func> function_decl
%type <block> block statement_list
%type <stmt> statement var_decl assign_stmt return_stmt if_stmt while_stmt print_stmt
%type <expr> expression term factor
%type <params> param_list
%type <args> arg_list

/* Operator Precedence */
%left PLUS MINUS
%left MUL DIV

/* Start Symbol */
%start program

%%

/* Grammar Rules */

program:
    /* empty */ { root = new Program(); $$ = root; }
    | program function_decl { $1->addFunction($2); root = $1; $$ = $1; }
    ;

function_decl:
    KW_INT ID LPAREN param_list RPAREN block { $$ = new FunctionDecl("int", $2, $4, $6); free($2); }
    | KW_FLOAT ID LPAREN param_list RPAREN block { $$ = new FunctionDecl("float", $2, $4, $6); free($2); }
    ;

param_list:
    /* empty */ { $$ = nullptr; }
    | KW_INT ID { $$ = new vector<Parameter*>(); $$->push_back(new Parameter("int", $2)); free($2); }
    | KW_FLOAT ID { $$ = new vector<Parameter*>(); $$->push_back(new Parameter("float", $2)); free($2); }
    | param_list COMMA KW_INT ID { $$ = $1; $$->push_back(new Parameter("int", $4)); free($4); }
    | param_list COMMA KW_FLOAT ID { $$ = $1; $$->push_back(new Parameter("float", $4)); free($4); }
    ;

block:
    LBRACE statement_list RBRACE { $$ = $2; }
    ;

statement_list:
    /* empty */ { $$ = new Block(); }
    | statement_list statement { $1->addStatement($2); $$ = $1; }
    ;

statement:
    var_decl { $$ = $1; }
    | assign_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | print_stmt { $$ = $1; }
    | block { $$ = $1; }
    ;

var_decl:
    KW_INT ID SEMICOLON { $$ = new VarDecl("int", $2); free($2); }
    | KW_FLOAT ID SEMICOLON { $$ = new VarDecl("float", $2); free($2); }
    ;

assign_stmt:
    ID ASSIGN expression SEMICOLON { $$ = new AssignStmt($1, $3); free($1); }
    ;

return_stmt:
    KW_RETURN expression SEMICOLON { $$ = new ReturnStmt($2); }
    ;

if_stmt:
    KW_IF LPAREN expression RPAREN statement { $$ = new IfStmt($3, $5); }
    | KW_IF LPAREN expression RPAREN statement KW_ELSE statement { $$ = new IfStmt($3, $5, $7); }
    ;

while_stmt:
    KW_WHILE LPAREN expression RPAREN statement { $$ = new WhileStmt($3, $5); }
    ;

print_stmt:
    KW_PRINT LPAREN expression RPAREN SEMICOLON { $$ = new PrintStmt($3); }
    ;

expression:
    expression PLUS term { $$ = new BinaryExpr($1, "+", $3); }
    | expression MINUS term { $$ = new BinaryExpr($1, "-", $3); }
    | expression EQ term { $$ = new BinaryExpr($1, "==", $3); }
    | expression NEQ term { $$ = new BinaryExpr($1, "!=", $3); }
    | expression LE term { $$ = new BinaryExpr($1, "<=", $3); }
    | expression GE term { $$ = new BinaryExpr($1, ">=", $3); }
    | expression LT term { $$ = new BinaryExpr($1, "<", $3); }
    | expression GT term { $$ = new BinaryExpr($1, ">", $3); }
    | term { $$ = $1; }
    ;

term:
    term MUL factor { $$ = new BinaryExpr($1, "*", $3); }
    | term DIV factor { $$ = new BinaryExpr($1, "/", $3); }
    | factor { $$ = $1; }
    ;

factor:
    NUM { $$ = new Number($1); }
    | FLOAT_LIT { $$ = new Float($1); }
    | ID { $$ = new Variable($1); free($1); }
    | ID LPAREN arg_list RPAREN { $$ = new CallExpr($1, $3); free($1); }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

arg_list:
    /* empty */ { $$ = nullptr; }
    | expression { $$ = new vector<Expression*>(); $$->push_back($1); }
    | arg_list COMMA expression { $$ = $1; $$->push_back($3); }
    ;

%%


#include "codegen.h"

void yyerror(const char *s) {
    cerr << "Error: " << s << endl;
}

extern char* yytext;

const char* getTokenName(int token) {
    switch(token) {
        case ID: return "ID";
        case NUM: return "NUM";
        case FLOAT_LIT: return "FLOAT_LIT";
        case KW_INT: return "KW_INT";
        case KW_FLOAT: return "KW_FLOAT";
        case KW_RETURN: return "KW_RETURN";
        case KW_IF: return "KW_IF";
        case KW_ELSE: return "KW_ELSE";
        case KW_WHILE: return "KW_WHILE";
        case KW_PRINT: return "KW_PRINT";
        case EQ: return "EQ";
        case NEQ: return "NEQ";
        case LE: return "LE";
        case GE: return "GE";
        case ASSIGN: return "ASSIGN";
        case LT: return "LT";
        case GT: return "GT";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case SEMICOLON: return "SEMICOLON";
        case COMMA: return "COMMA";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        default: return "UNKNOWN";
    }
}

int main(int argc, char** argv) {
    bool dotOutput = false;
    bool llvmOutput = true; // Default
    bool parseOutput = false;
    bool lexOutput = false;

    if (argc > 1) {
        string arg = argv[1];
        if (arg == "--dot") {
            dotOutput = true;
            llvmOutput = false;
        } else if (arg == "--parse") {
            parseOutput = true;
            llvmOutput = false;
        } else if (arg == "--lex") {
            lexOutput = true;
            llvmOutput = false;
        } else if (arg == "--llvm") {
            llvmOutput = true;
        } else {
            cerr << "Error: Unknown option: " << arg << endl;
            return 1;
        }
    }

    if (lexOutput) {
        int token;
        while ((token = yylex()) != 0) {
            cout << "Token: " << getTokenName(token) << ", Lexeme: " << yytext << endl;
        }
        return 0;
    }

    // Parse
    if (yyparse() == 0) {
        if (root) {
            if (dotOutput) {
                int count = 0;
                root->generateDOT(cout, count);
            } else if (parseOutput) {
                root->print();
            } else {
                // LLVM Output (Default)
                CodeGenerator generator;
                generator.generate(root);
                generator.printIR();
            }
            delete root; 
        }
    } else {
        cerr << "Parse failed" << endl;
        return 1;
    }
    return 0;
}
