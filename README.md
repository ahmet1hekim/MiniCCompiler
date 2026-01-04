# Mini C Compiler - Project 3: Semantics & Code Generation

A complete Mini C compiler extending Project 2 (Parser) with Semantic Analysis and Code Generation using LLVM.

## 🚀 Features (Project 3 Implementation)

1.  **Semantic Analysis**:
    *   **Scope Resolution**: Uses a Symbol Table (managed via `std::map<string, AllocaInst*>`) to track variables across block scopes (Shadowing supported).
    *   **Type Checking**: Ensures compatibility between operands (e.g., `int` vs `float`).
2.  **Code Generation**:
    *   **LLVM IR**: implementation using LLVM C++ API (`IRBuilder`, `Module`, `Context`).
    *   Generates native-ready LLVM Intermediate Representation.

---

## 🛠 Build & Run

### Prerequisites
*   `g++` (C++17)
*   `bison`, `flex`
*   `llvm` (install `llvm-dev` or similar, explicitly uses `llvm-config`)

### 1. Quick Start (Master Script)
The easiest way to build, verify, and verify the project:

```bash
./run.sh
```

This script will:
1.  Clean and rebuild the project (`make clean && make`).
2.  Run the full test suite (`tests/verify.sh`).
3.  Generate valid LLVM IR and DOT visualizations in `outputs/`.
4.  Run a live demo of the factorial program.

### 2. Manual Build & Run
If you prefer manual commands:

**Build:**
```bash
make
```

**Run (LLVM JIT):**
```bash
./minic -llvm < tests/test9.mc | lli
# Output: 120
```

**Generate LLVM IR File:**
```bash
./minic -llvm < tests/test5.mc > program.ll
```

**Visualize AST (Project 2 feature):**
```bash
./minic -dot < tests/test5.mc > ast.dot
dot -Tpng ast.dot -o ast.png
```

---

## 🏗 Implementation Details

### Architecture
1.  **Lexer/Parser**: Flex/Bison generate the AST (`ast.h`).
2.  **Code Generation (`codegen.cpp`)**:
    *   `CodeGenerator` class traverses the AST via visitor-like pattern (`codegen` methods on nodes).
    *   Maintains `namedValues` map for variable scope.
    *   Uses `llvm::IRBuilder` to emit instructions (`alloca`, `store`, `load`, `add`, `icmp`, etc.).

### Semantic Checks
*   **Variable Resolution**: Checking `namedValues` during variable reference lookups.
*   **Function Verification**: `functions` map tracks declared functions.

---

## 🧪 Test Suite

See `tests/` directory.

*   `test1.mc`: Basic types.
*   `test2.mc`: Arithmetic rules.
*   `test3.mc`: `if/else` control flow.
*   `test4.mc`: `while` loops.
*   `test5.mc`: Function calls and parameters.
