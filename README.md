# Mini C Compiler

A robust Mini C compiler implementing a Lexer and Parser using Flex, Bison, and C++. It generates an Abstract Syntax Tree (AST) for valid Mini C programs.

## 🚀 Quick Start

The project includes an **automated script** that builds the compiler, runs all tests, and generates visualization.

```bash
./run.sh
```

Alternatively, you can run commands manually:

### 1. Build
```bash
make
```

### 2. Run
```bash
./minic < tests/test1.mc
```

### 3. Verify
```bash
cd tests
./verify.sh
```

---

## 🔧 Project Structure

The project follows a clean standard C++ structure:

*   `src/`: Source files (`lexer.l`, `parser.y`)
*   `include/`: Header files (`ast.h`)
*   `tests/`: Test programs (`.mc` files)
*   `Makefile`: Build configuration
*   `run.sh`: Automation script

---

## 📖 Language Features

The compiler supports the following C subset features:

*   **Data Types**: `int`, `float`
*   **Functions**: Declared with return type, name, and parameters.
*   **Control Structures**: `if/else`, `while`, `return`.
*   **I/O**: Built-in `print(expression);`.
*   **Comments**: `//` single-line and `/* */` multi-line.

### Example Code
```c
int main() {
    int x;
    x = 10;
    while (x > 0) {
        print(x);
        x = x - 1;
    }
    return 0;
}
```

---

## 🔧 Technical Details

### Grammar (EBNF)
```ebnf
program         ::= { function_decl }
function_decl   ::= ( "int" | "float" ) ID "(" [ param_list ] ")" block
statement       ::= var_decl | assign_stmt | return_stmt | if_stmt | while_stmt | print_stmt | block
expression      ::= expression op term | term
```

### AST Visualization
You can generate a Graphviz DOT visualization of the AST:
```bash
./minic -dot < tests/test5.mc > ast.dot
dot -Tpng ast.dot -o ast.png
```
*(Note: `./run.sh` does this automatically)*

---

## 📋 Requirements
*   Flex
*   Bison
*   G++ (C++17)
*   Make
*   Graphviz (optional, for visualization)
