# Mini C Compiler

A robust Mini C compiler implementing a Lexer and Parser using Flex, Bison, and C++. It specifically targets a subset of C, generating an Abstract Syntax Tree (AST) for analysis and visualization.

## 🚀 Quick Start

If you have `devenv` installed, you can get started immediately:

```bash
# 1. Activate the environment
devenv shell

# 2. Build the project
cmake -S . -B build && cmake --build build

# 3. Run a test
./out/bin/minic < tests/test1.mc
```

---

## 🛠️ Build & Run Instructions

### Option 1: Using Devenv (Recommended)
This project uses [devenv](https://devenv.sh/) to manage dependencies automatically.

1.  **Enter the Shell**:
    ```bash
    devenv shell
    ```
2.  **Build**:
    ```bash
    cmake -S . -B build && cmake --build build
    ```

### Option 2: Manual Setup
**Prerequisites**:
*   CMake (3.16+)
*   Flex
*   Bison
*   C++ Compiler (GCC/Clang, C++17 support)

**Build Steps**:
```bash
mkdir -p build && cd build
cmake ..
make
```

### 🏃 Running the Compiler
The compiler accepts code via **Standard Input (stdin)** and outputs the AST to **Standard Output (stdout)**.

**Basic Usage:**
```bash
./out/bin/minic < tests/test1.mc
```

**Run Verification Suite:**
```bash
cd tests
./verify.sh
```

**Generate AST Visualization (DOT/PNG):**
```bash
# Generate DOT file
./out/bin/minic -dot < tests/test5.mc > ast.dot

# Convert to PNG (requires Graphviz)
dot -Tpng ast.dot -o ast.png
```

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

## 🏗️ Project Structure
*   `src/`: Lexer (`.lex`) and Parser (`.y`) source.
*   `include/`: AST node definitions (`ast.h`).
*   `tests/`: Verification scripts and invalid/valid test cases.
