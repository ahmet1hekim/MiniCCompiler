# Mini C Compiler

A robust Mini C compiler implementing a Lexer and Parser using Flex, Bison, and C++. It specifically targets a subset of C, generating an Abstract Syntax Tree (AST) for analysis and visualization.

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

### 3. Test
To run all tests:
```bash
cd tests
./verify.sh
```

---

## 📋 Requirements
*   CMake (3.16+)
*   Flex
*   Bison
*   C++ Compiler (GCC/Clang)

---

## 📖 Language Features

Mini C supports:
*   **Types**: `int`, `float`
*   **Control**: `if/else`, `while`, `return`, `block { }`
*   **I/O**: `print(expr);`
*   **Functions**: Recursive calls, parameters, return values.
*   **Comments**: `//` single-line and `/* */` multi-line.

### Example Code
```c
int main() {
    int x;
    x = 10;
    if (x > 5) {
        print(x);
    }
    return 0;
}
```
