# Mini C Compiler

A robust Mini C compiler implementing a Lexer and Parser using Flex, Bison, and C++. It features **Semantic Analysis** and **LLVM IR Code Generation**. It generates an Abstract Syntax Tree (AST) for valid Mini C programs and produces valid LLVM IR, which can be compiled into native executables.

## 🚀 Quick Start

### 1. Requirements
*   CMake (3.16+)
*   Flex & Bison
*   C++ Compiler (C++17)
*   **LLVM** (development libraries, version 16+ recommended)

### 2. Build
The build process uses CMake. Executables are placed in the `bin/` directory.

```bash
# Generate build files
cmake -S . -B build

# Compile the project
cmake --build build
```

This will create the compiler executables in the `bin/` folder.

### 3. Usage

#### Compile a Program
To compile a Mini C source file into an executable:

```bash
tests/scripts/compile.sh tests/inputs/test1.mc
```
This generates an executable `test1` in the `tests/inputs/` directory.

#### Generate LLVM IR Only
To parse and generate LLVM IR without compiling to an executable:

```bash
./bin/parser tests/inputs/test1.mc
```
This prints the AST and generated LLVM IR to stdout.

### 4. Verify & Test
Run the automated test suite to ensure the compiler is working correctly:

```bash
cd tests/scripts
./verify_codegen.sh
```
This script builds the project (if needed) and runs the compiler against all test files in `tests/inputs/`.

---

## 📂 Project Structure

```text
MiniCCompiler/
├── bin/                # Compiled executables (parser, lexer)
├── build/              # CMake build artifacts
├── include/            # Header files (AST definitions, etc.)
├── src/                # Source code (Parser, Lexer, CodeGen)
├── tests/
│   ├── inputs/         # Test input files (*.mc)
│   └── scripts/        # Utility scripts (compile, verify)
└── outputs/            # Output files from verification scripts
```

---

## ✨ Language Features

The compiler supports a subset of C:

*   **Data Types**: `int`, `float`, `void`
*   **Functions**: Typed declarations with parameters.
*   **Control Flow**: `if/else`, `while`, `return`.
*   **I/O**: Built-in `print(expr)` statement.
*   **Comments**: `//` and `/* ... */`.

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

---

## 🔧 Technical Details

### Architecture
1.  **Lexer**: Tokenizes input using Flex.
2.  **Parser**: detailed grammar analysis using Bison, building an **Abstract Syntax Tree (AST)**.
3.  **Semantic Analysis**: Checks variable scopes and types.
4.  **Code Generation**: Traverses the AST to generate **LLVM IR** using the LLVM C++ API.

### AST Visualization
Generate a Graphviz DOT visualization of a program's structure:
```bash
./bin/parser tests/inputs/test5.mc -dot > ast.dot
dot -Tpng ast.dot -o ast.png
```
