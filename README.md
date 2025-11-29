# Mini C Compiler

This project implements a Lexer and Parser for a Mini C language using Flex, Bison, and C++. It generates an Abstract Syntax Tree (AST) for valid Mini C programs.

## Build and Run Instructions

### Prerequisites
- CMake (3.16+)
- Flex
- Bison
- C++ Compiler (GCC/Clang) supporting C++17

### Building
1. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
2. Generate build files with CMake:
   ```bash
   cmake ..
   ```
3. Compile the project:
   ```bash
   make
   ```

### Running
The executable `minic` reads from standard input and prints the AST to standard output.

```bash
./out/bin/minic < tests/test_parser.c
```

Or run the verification script:
```bash
cd tests
./verify.sh
```

### Generating AST Visualization (DOT)
To generate a Graphviz DOT file for the AST, use the `-dot` flag:

```bash
./out/bin/minic -dot < tests/test5.mc > ast.dot
```

You can then convert the DOT file to an image using `dot` (requires Graphviz):
```bash
dot -Tpng ast.dot -o ast.png
```

## Language Syntax Description

The Mini C language is a subset of C with the following features:
- **Data Types**: `int` and `float` are supported.
- **Functions**: Functions are declared with a return type (`int` or `float`), a name, and a parameter list.
- **I/O**: `print(expression);` statement.
- **Control Flow**:
  - `if (condition) statement [else statement]`
  - `while (condition) statement`
  - `return expression;`
- **Variables**: Must be declared before use. Example: `int x;`.
- **Comments**: Supports single-line `//` and multi-line `/* ... */` comments.
- **Operators**:
  - Arithmetic: `+`, `-`, `*`, `/`
  - Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`
  - Assignment: `=`

## Grammar (EBNF)

```ebnf
program         ::= { function_decl }

function_decl   ::= ( "int" | "float" ) ID "(" [ param_list ] ")" block

param_list      ::= param { "," param }
param           ::= ( "int" | "float" ) ID

block           ::= "{" { statement } "}"

statement       ::= var_decl
                  | assign_stmt
                  | return_stmt
                  | if_stmt
                  | while_stmt
                  | print_stmt
                  | block

var_decl        ::= ( "int" | "float" ) ID ";"

assign_stmt     ::= ID "=" expression ";"

return_stmt     ::= "return" expression ";"

if_stmt         ::= "if" "(" expression ")" statement [ "else" statement ]

while_stmt      ::= "while" "(" expression ")" statement

print_stmt      ::= "print" "(" expression ")" ";"

expression      ::= expression ("+" | "-" | "==" | "!=" | "<" | ">" | "<=" | ">=") term
                  | term

term            ::= term ("*" | "/") factor
                  | factor

factor          ::= NUM
                  | FLOAT_LIT
                  | ID
                  | ID "(" [ arg_list ] ")"
                  | "(" expression ")"

arg_list        ::= expression { "," expression }
```

## AST Node Structure

The Abstract Syntax Tree is implemented using a class hierarchy in C++. All nodes inherit from the base class `ASTNode`.

### Class Hierarchy

- **ASTNode** (Base Class)
  - `virtual void print()`: Prints the node structure.

- **Program**
  - Contains a list of `FunctionDecl` nodes.

- **FunctionDecl**
  - Represents a function declaration.
  - Attributes: `returnType`, `name`, `params` (List of Parameters), `body` (Block).

- **Parameter**
  - Represents a function parameter.
  - Attributes: `type`, `name`.

- **Statement** (Abstract Base Class)
  - **Block**: Contains a list of `Statement` nodes.
  - **VarDecl**: Represents variable declaration (e.g., `int x;`).
  - **AssignStmt**: Represents assignment (e.g., `x = 10;`).
  - **ReturnStmt**: Represents return statement.
  - **IfStmt**: Contains `condition` (Expression), `thenBranch` (Statement), and optional `elseBranch` (Statement).
  - **WhileStmt**: Contains `condition` (Expression) and `body` (Statement).
  - **PrintStmt**: Contains `expr` (Expression).

- **Expression** (Abstract Base Class)
  - **BinaryExpr**: Represents binary operations (`+`, `-`, `*`, `/`, etc.). Contains `left` and `right` expressions and an operator string.
  - **Number**: Represents integer literals.
  - **Float**: Represents floating point literals.
  - **Variable**: Represents identifier usage.
  - **CallExpr**: Represents function calls. Contains `name` and `args` (List of Expressions).
