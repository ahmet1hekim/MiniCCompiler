#!/usr/bin/env bash

# Mini C Compiler Project 3 - Master Run Script
# Automates Build, Verification, and Demonstration

# 1. Clean and Build
echo "========================================"
echo " 1. Building Project 3 (LLVM Support)"
echo "========================================"
make clean
make

if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi
echo "✅ Build successful."

# 2. Run Verification Suite
echo -e "\n========================================"
echo " 2. Running Verification Suite (15 Tests)"
echo "========================================"
cd tests
./verify.sh
if [ $? -ne 0 ]; then
    echo "❌ Verification failed!"
    exit 1
fi
cd ..

# 3. Generate Demonstration Outputs
echo -e "\n========================================"
echo " 3. Generating Demo Outputs (outputs/)"
echo "========================================"
mkdir -p outputs

# Generate LLVM IR for test5 (Function Call)
echo "Generating LLVM IR for tests/test5.mc..."
./minic -llvm < tests/test5.mc > outputs/test5.ll
echo "Saved to outputs/test5.ll"

# Generate AST DOT for test5
echo "Generating AST Visual for tests/test5.mc..."
./minic -dot < tests/test5.mc > outputs/test5.dot
if command -v dot &> /dev/null; then
    dot -Tpng outputs/test5.dot -o outputs/test5.png
    echo "Saved to outputs/test5.png"
else
    echo "Graphviz 'dot' not found. Skipping PNG."
fi

# 4. Run 'lli' Demo
echo -e "\n========================================"
echo " 4. Running 'lli' Demo (JIT Execution)"
echo "========================================"
echo "Running: ./minic -llvm < tests/test9.mc (Factorial 5)"
result=$(./minic -llvm < tests/test9.mc | lli)
echo "Result: $result"
if [ "$result" -eq 120 ]; then
    echo "✅ Correct Result (120)"
else
    echo "❌ Incorrect Result"
fi

echo -e "\n🎉 Project 3 Workflow Complete!"
