# Mini C Compiler

A robust Mini C compiler implementing a Lexer and Parser using Flex, Bison, and C++. It generates an Abstract Syntax Tree (AST) for valid Mini C programs, targeting a specific subset of the C language.

## 🚀 Quick Start

Here are the exact commands to build and run the project:

### 1. Build
```bash
# Generate build files
cmake -S . -B build

# Compile the project
cmake --build build
```

### 2. Run
To parse a Mini C file and see the AST:
```bash
./out/bin/minic < tests/test1.mc
```

### 3. Verify
To run the automated test suite:
```bash
cd tests
./verify.sh
```

---

## � Language Features

The compiler supports the following C subset features:

*   **Data Types**: `int`, `float`
*   **Functions**: Declared with return type, name, and parameters.
*   **Control Structures**:
    *   `if (condition) { ... } else { ... }`
    *   `while (condition) { ... }`
    *   `return expression;`
*   **I/O**: Built-in `print(expression);` statement.
*   **Comments**:
    *   Single-line: `// comment`
    *   Multi-line: `/* comment */`

### Example Code
```c
int main() {
    int x;
    float y;
    x = 10;
    y = 3.14;
    
    if (x > 5) {
        print(x);
    }
    return 0;
}
```

---

## 🔧 Technical Details

### Grammar (EBNF)
The language syntax allows strictly typed function and variable declarations.

```ebnf
program         ::= { function_decl }
function_decl   ::= ( "int" | "float" ) ID "(" [ param_list ] ")" block
param_list      ::= param { "," param }
block           ::= "{" { statement } "}"
statement       ::= var_decl | assign_stmt | return_stmt | if_stmt | while_stmt | print_stmt | block
expression      ::= expression op term | term
```

### AST Structure
The Abstract Syntax Tree is built using a C++ class hierarchy rooted at `ASTNode`.

*   **Program**: Root node containing function declarations.
*   **FunctionDecl**: Stores return type, name, parameters, and body.
*   **Statement Nodes**:
    *   `IfStmt`, `WhileStmt`: Control flow.
    *   `VarDecl`: Variable definitions (`int x;`).
    *   `AssignStmt`: Assignments (`x = 5;`).
    *   `PrintStmt`: Output operations.
*   **Expression Nodes**:
    *   `BinaryExpr`: Arithmetic (`+`, `-`, `*`, `/`) and Logic (`>`, `==`, etc.).
    *   `Number` / `Float`: Literals.
    *   `Variable`: Identifier references.

### Visualization
You can generate a Graphviz DOT visualization of the AST:
```bash
./out/bin/minic -dot < tests/test5.mc > ast.dot
dot -Tpng ast.dot -o ast.png
```

---

## 📋 Requirements
*   CMake (3.16+)
*   Flex & Bison
*   C++ Compiler (C++17)
