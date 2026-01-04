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

## 📚 How the Compiler Works: End-to-End Pipeline

The Mini C Compiler transforms source code (`.mc` files) into executable machine code through a **5-stage pipeline**:

```
Mini C Source (.mc) 
    ↓
[1] Lexical Analysis (Flex)
    ↓
Token Stream
    ↓
[2] Syntax Analysis (Bison)
    ↓
Abstract Syntax Tree (AST)
    ↓
[3] Semantic Analysis & Code Generation (LLVM API)
    ↓
LLVM IR (.ll)
    ↓
[4] LLVM Optimization (opt - optional)
    ↓
Optimized LLVM IR
    ↓
[5] Native Code Generation (Clang/LLC)
    ↓
Native Executable (a.out / binary)
```

### Stage 1: Lexical Analysis (Tokenization)
**File**: `src/lexer.l`

The lexer scans the input source code and breaks it into **tokens**:
- **Keywords**: `int`, `float`, `if`, `else`, `while`, `return`, `print`
- **Identifiers**: Variable/function names
- **Literals**: Numbers (`123`), floats (`3.14`)
- **Operators**: `+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Delimiters**: `{`, `}`, `(`, `)`, `;`, `,`

**Example**: `int x = 5 + 3;` → `[KW_INT] [ID:"x"] [ASSIGN] [NUM:5] [PLUS] [NUM:3] [SEMICOLON]`

### Stage 2: Syntax Analysis (Parsing)
**File**: `src/parser.y`

The parser consumes tokens and builds an **Abstract Syntax Tree (AST)** based on the grammar rules:
- **Program**: Collection of function declarations
- **Function Declaration**: Return type, name, parameters, body
- **Statements**: Variable declarations, assignments, control flow (`if`/`while`), `return`, `print`
- **Expressions**: Arithmetic, comparisons, function calls, variables, literals

**Grammar Rules**:
```
program → function_decl*
function_decl → type ID ( param_list ) block
statement → var_decl | assign_stmt | if_stmt | while_stmt | return_stmt | print_stmt | block
expression → term (+ | - | == | != | < | > | <= | >=) term
term → factor (* | /) factor
factor → NUM | FLOAT_LIT | ID | ID(arg_list) | (expression)
```

**AST Node Types** (defined in `include/ast.h`):
- `Program`, `FunctionDecl`, `Parameter`
- `Block`, `VarDecl`, `AssignStmt`, `ReturnStmt`, `IfStmt`, `WhileStmt`, `PrintStmt`
- `BinaryExpr`, `CallExpr`, `Variable`, `Number`, `Float`

### Stage 3: Semantic Analysis & LLVM IR Generation
**Files**: `src/codegen.cpp`, `src/ast_codegen.cpp`, `include/codegen.h`

The `CodeGenerator` class traverses the AST and emits **LLVM Intermediate Representation**:

**Key Components**:
1. **LLVM Context**: Owns LLVM core data structures
2. **LLVM Module**: Container for functions and global variables (named "MiniC")
3. **IRBuilder**: Helper for generating IR instructions
4. **Symbol Tables**:
   - `namedValues`: Maps variable names → `AllocaInst*` (stack allocations)
   - `functions`: Maps function names → `Function*`

**Compilation Process**:

**A. Function Declaration** (`CodeGenerator::codegen(FunctionDecl*)`):
- Create LLVM function with proper signature
- Create entry basic block
- Allocate stack space for parameters using `alloca`
- Generate code for function body
- Add default return if missing (0 for int, 0.0 for float)

**B. Variable Declaration** (`codegen(VarDecl*)`):
- Allocate stack space: `alloca i32` or `alloca float`
- Initialize to zero
- Register in `namedValues` symbol table

**C. Assignment** (`codegen(AssignStmt*)`):
- Generate code for right-hand expression
- Look up variable in symbol table
- Emit `store` instruction

**D. Expressions** (`codegen(BinaryExpr*)`, `codegen(Number*)`, etc.):
- Arithmetic: `add`, `fadd`, `sub`, `fsub`, `mul`, `fmul`, `div`, `fdiv`
- Comparisons: `icmp slt`, `fcmp ult`, etc. (returns boolean, extended to i32)
- Variables: `load` from stack allocation
- Function calls: `call` instruction

**E. Control Flow**:
- **If Statement**: Creates `then`, `else` (optional), and `merge` basic blocks with conditional branch
- **While Loop**: Creates `condition`, `body`, and `after` blocks with looping branches

**F. Print Statement**:
- Uses external `printf` function (declared as variadic)
- Creates format string (`"%d\n"` for int, `"%f\n"` for float)
- Promotes float to double for variadic arguments

**Example LLVM IR Output**:
```llvm
define i32 @factorial(i32 %n) {
entry:
  %n1 = alloca i32
  store i32 %n, i32* %n1
  %n2 = load i32, i32* %n1
  %cmptmp = icmp sle i32 %n2, 1
  br i1 %cmptmp, label %then, label %ifcont
  
then:
  ret i32 1
  
ifcont:
  %n3 = load i32, i32* %n1
  %n4 = load i32, i32* %n1
  %subtmp = sub i32 %n4, 1
  %calltmp = call i32 @factorial(i32 %subtmp)
  %multmp = mul i32 %n3, %calltmp
  ret i32 %multmp
}
```

### Stage 4: LLVM Optimization (Optional)
**Tool**: `opt`

You can optimize the generated LLVM IR:
```bash
./minic -llvm < tests/test9.mc > program.ll
opt -O2 program.ll -o program_opt.ll
```

Common optimizations applied:
- Dead code elimination
- Constant folding
- Inlining
- Loop optimizations
- Register allocation hints

### Stage 5: Native Code Compilation
**Tools**: `clang`, `llc`, `lli`

#### Option 1: JIT Execution (Interpreter)
Execute LLVM IR directly without creating a binary:
```bash
./minic -llvm < tests/test9.mc | lli
```
**Output**: `120` (factorial of 5)

#### Option 2: Compile to Native Executable via Clang
```bash
# Step 1: Generate LLVM IR
./minic -llvm < tests/test9.mc > program.ll

# Step 2: Compile to native executable
clang program.ll -o program

# Step 3: Run the executable
./program
```
**Output**: `120`

#### Option 3: Two-Stage Compilation (LLC + GCC)
```bash
# Step 1: Generate LLVM IR
./minic -llvm < tests/test9.mc > program.ll

# Step 2: Generate assembly code
llc program.ll -o program.s

# Step 3: Assemble and link
gcc program.s -o program

# Step 4: Run
./program
```

#### Option 4: Compile with Optimizations
```bash
# Using Clang with optimization level
./minic -llvm < tests/test9.mc > program.ll
clang -O3 program.ll -o program_optimized

# Or using opt first, then Clang
opt -O2 program.ll -o program_opt.ll
clang program_opt.ll -o program_optimized
```

---

## 🛠 Build & Run

### Prerequisites
*   `g++` (C++17 or later)
*   `bison` (GNU Parser Generator)
*   `flex` (Fast Lexical Analyzer)
*   `llvm` (LLVM Development Libraries - install `llvm-dev` or use `llvm-config`)
*   `clang` (LLVM C/C++ Compiler - for final executable generation)

**Installation (Ubuntu/Debian)**:
```bash
sudo apt-get update
sudo apt-get install g++ bison flex llvm-dev clang
```

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

**Build the Compiler:**
```bash
make
```

**Run with LLVM JIT Execution:**
```bash
./minic -llvm < tests/test9.mc | lli
# Output: 120
```

**Generate LLVM IR File:**
```bash
./minic -llvm < tests/test5.mc > program.ll
```

**Compile to Native Executable:**
```bash
./minic -llvm < tests/test9.mc > program.ll
clang program.ll -o program
./program
# Output: 120
```

**Visualize AST (Project 2 feature):**
```bash
./minic -dot < tests/test5.mc > ast.dot
dot -Tpng ast.dot -o ast.png
```

### 3. Complete Workflow Example

```bash
# 1. Compile the compiler
make clean && make

# 2. Test a Mini C program (factorial)
cat tests/test9.mc

# 3. Generate LLVM IR
./minic -llvm < tests/test9.mc > factorial.ll

# 4. View the generated IR
cat factorial.ll

# 5. Compile to executable
clang factorial.ll -o factorial

# 6. Run the program
./factorial
# Expected output: 120

# 7. Optionally, optimize before compiling
opt -O2 factorial.ll -o factorial_opt.ll
clang factorial_opt.ll -o factorial_optimized
./factorial_optimized
```

---

## 🏗 Implementation Details

### Architecture Overview

```
┌─────────────────────────────────────────────────────────┐
│                    Mini C Compiler                       │
├─────────────────────────────────────────────────────────┤
│                                                          │
│  ┌────────────┐    ┌────────────┐    ┌──────────────┐  │
│  │   Lexer    │───▶│   Parser   │───▶│  CodeGen     │  │
│  │ (lexer.l)  │    │ (parser.y) │    │ (codegen.cpp)│  │
│  │            │    │            │    │              │  │
│  │  Flex      │    │   Bison    │    │  LLVM API    │  │
│  └────────────┘    └────────────┘    └──────────────┘  │
│        ↓                  ↓                   ↓         │
│     Tokens              AST              LLVM IR        │
│                                                          │
│  Supporting Structures:                                 │
│  • AST Node Classes (ast.h)                            │
│  • Symbol Tables (namedValues, functions)              │
│  • Type System (int, float)                            │
│  • LLVM Context, Module, IRBuilder                     │
└─────────────────────────────────────────────────────────┘
```

### Detailed Component Breakdown

#### 1. Lexer (`src/lexer.l`)
- **Technology**: Flex (Fast Lexical Analyzer)
- **Input**: Raw source code string
- **Output**: Token stream
- **Features**:
  - Pattern matching using regular expressions
  - Keywords recognition
  - Identifier/number extraction
  - Comment skipping
  - Line/column tracking for error reporting

#### 2. Parser (`src/parser.y`)
- **Technology**: Bison (GNU Parser Generator)
- **Input**: Token stream from lexer
- **Output**: Abstract Syntax Tree (AST)
- **Features**:
  - Context-free grammar rules
  - Operator precedence handling
  - Error recovery
  - AST construction during parsing
  - `main()` function: Entry point that handles CLI flags

**CLI Flags**:
- `-dot`: Generate AST visualization in DOT format
- `-llvm`: Generate LLVM IR code
- (no flag): Print AST to stdout

#### 3. AST (`include/ast.h`, `src/ast_codegen.cpp`)
- **Design**: Visitor pattern with polymorphic `codegen()` methods
- **Node Hierarchy**:
  ```
  ASTNode (base class)
  ├── Program
  ├── FunctionDecl
  ├── Parameter
  ├── Statement
  │   ├── Block
  │   ├── VarDecl
  │   ├── AssignStmt
  │   ├── ReturnStmt
  │   ├── IfStmt
  │   ├── WhileStmt
  │   └── PrintStmt
  └── Expression
      ├── BinaryExpr
      ├── CallExpr
      ├── Variable
      ├── Number
      └── Float
  ```

Each node implements:
- `codegen(CodeGenerator*)`: Emits LLVM IR
- `print()`: Debugging output
- `generateDOT()`: Graph visualization

#### 4. Code Generator (`src/codegen.cpp`, `include/codegen.h`)
- **LLVM Components**:
  - `LLVMContext`: Thread-local LLVM state
  - `Module`: Container for all compiled code
  - `IRBuilder`: Helper for instruction generation
  - `Function`, `BasicBlock`, `Value`: Core IR types

- **Symbol Table Management**:
  ```cpp
  std::map<std::string, AllocaInst*> namedValues;  // Variables
  std::map<std::string, Function*> functions;       // Functions
  ```

- **Key Methods**:
  - `getType()`: Maps "int"/"float" → LLVM types
  - `createEntryBlockAlloca()`: Allocates stack variables
  - `codegen(Program*)`: Main entry point
  - `codegen(FunctionDecl*)`: Function translation
  - `codegen(Statement*)`: Statement code generation
  - `codegen(Expression*)`: Expression evaluation
  - `printIR()`: Outputs generated LLVM IR

### Semantic Checks Performed

1. **Variable Resolution**: 
   - Checks `namedValues` during variable reference lookups
   - Reports unknown variable errors

2. **Function Verification**: 
   - `functions` map tracks declared functions
   - Reports unknown function errors on calls

3. **Type Awareness**:
   - Distinguishes int vs float operations
   - Uses appropriate LLVM instructions (`add` vs `fadd`)

4. **Scope Management**:
   - Function-local scoping via `namedValues.clear()` on function entry
   - Block scoping supported (variables shadow outer scopes)

---

## 🧪 Test Suite

See `tests/` directory for comprehensive examples.

**Valid Test Cases**:
*   `test1.mc`: Basic type declarations and literals
*   `test2.mc`: Arithmetic operations and operator precedence
*   `test3.mc`: `if/else` control flow statements
*   `test4.mc`: `while` loop constructs
*   `test5.mc`: Function calls with parameters
*   `test6.mc`: Nested function calls
*   `test7.mc`: Mixed int/float operations
*   `test8.mc`: Complex expressions with multiple operators
*   `test9.mc`: Recursive factorial function
*   `test10.mc`: Advanced control flow combinations

**Invalid Test Cases** (for error handling verification):
*   `invalid_1.mc`: Undefined variable reference
*   `invalid_2.mc`: Type mismatch errors
*   `invalid_3.mc`: Syntax errors
*   `invalid_4.mc`: Undefined function calls
*   `invalid_5.mc`: Missing return statements

**Running Tests**:
```bash
# Run all tests
./tests/verify.sh

# Run a single test
./minic -llvm < tests/test9.mc | lli

# Generate IR for inspection
./minic -llvm < tests/test3.mc > outputs/test3.ll
```

---

## 📖 Mini C Language Specification

**Supported Features**:
- **Types**: `int`, `float`
- **Declarations**: Variables and functions
- **Operators**: 
  - Arithmetic: `+`, `-`, `*`, `/`
  - Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`
  - Assignment: `=`
- **Control Flow**: `if`, `if-else`, `while`
- **Functions**: Declaration, parameters, recursion, return values
- **I/O**: `print(expr)` (outputs value to stdout)

**Example Program**:
```c
// Compute GCD using Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp;
        temp = b;
        b = a - (a / b) * b;  // a % b
        a = temp;
    }
    return a;
}

int main() {
    print(gcd(48, 18));  // Output: 6
    return 0;
}
```

---

## 🚀 Advanced Usage

### Debugging Generated IR
```bash
# Generate IR with comments
./minic -llvm < tests/test9.mc > debug.ll

# Validate IR syntax
llvm-as debug.ll -o /dev/null

# Disassemble to human-readable form
llvm-dis debug.ll
```

### Performance Analysis
```bash
# Generate optimized code
./minic -llvm < tests/test9.mc > program.ll
opt -O3 -time-passes program.ll -o optimized.ll

# Compare assembly output
llc program.ll -o program.s
llc optimized.ll -o optimized.s
diff program.s optimized.s
```

### Cross-Compilation
```bash
# Compile for different architectures
./minic -llvm < tests/test9.mc > program.ll

# ARM
llc -march=arm program.ll -o program_arm.s

# x86-64
llc -march=x86-64 program.ll -o program_x64.s
```

---

## 📝 Development Notes

**Build System** (`Makefile`):
1. Generates parser: `bison -d src/parser.y → build/parser.tab.c`
2. Generates lexer: `flex src/lexer.l → build/lex.yy.c`
3. Compiles C++ sources with LLVM flags
4. Links with LLVM libraries (`llvm-config --ldflags --libs`)

**LLVM Integration**:
- Uses `llvm-config` to detect LLVM installation
- Links against: `core`, `native` libraries
- Requires LLVM headers during compilation (`--cxxflags`)

**Clean Build**:
```bash
make clean        # Remove all generated files
make              # Full rebuild
```
