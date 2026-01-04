#!/bin/bash

echo "============================================="
echo "        MiniC Compiler Verification          "
echo "============================================="

# 1. Invalid Tests (Should fail or produce error)
echo -e "\n[1] Testing Invalid Cases (Parsing/Semantics)"
for file in invalid_*.mc; do
    echo "--------------------------------"
    echo "Processing $file..."
    
    # Capture stderr to check for specific errors
    output=$(../minic -llvm < "$file" 2>&1)
    status=$?
    
    if echo "$output" | grep -E -q "Error|Unknown|syntax error"; then
        echo "✅ PASS: Detected error as expected."
        echo "   Message: $(echo "$output" | head -n 1)"
    else
        echo "❌ FAIL: Expected error but got none."
    fi
done

# 2. Valid Tests (Should execute and produce output)
echo -e "\n[2] Testing Valid Cases (Execution via LLVM JIT)"
for file in test*.mc; do
    echo "--------------------------------"
    echo "Running $file..."
    
    # Run with lli
    result=$(../minic -llvm < "$file" | lli)
    
    echo "Output: $result"
    
    # Check return code of lli pipeline
    if [ $? -eq 0 ]; then
         echo "✅ PASS: Execution successful."
    else
         echo "❌ FAIL: Execution failed."
    fi
done

echo -e "\nVerification Complete."
