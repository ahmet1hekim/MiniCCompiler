#!/usr/bin/env bash

# Assuming running from tests/scripts directory
PARSER="../../bin/parser"
INPUT_DIR="../inputs"
OUTPUT_DIR="../../outputs"

# Ensure output dir exists
mkdir -p "$OUTPUT_DIR"

if [ ! -f "$PARSER" ]; then
    echo "Parser executable not found at $PARSER"
    echo "Attempting build..."
    # Go to root
    pushd ../..
    cmake -S . -B build || exit 1
    cmake --build build || exit 1
    popd
fi

echo "========================================"
echo "    Running MiniC CodeGen Tests"
echo "========================================"

count=0
pass=0

# Loop through all valid test files
for testfile in "$INPUT_DIR"/test*.mc; do
    [ -e "$testfile" ] || continue
    ((count++))
    filename=$(basename -- "$testfile")
    echo -n "Testing $filename ... "
    
    # Run parser and capture output
    $PARSER "$testfile" > "$OUTPUT_DIR/${filename}.ll" 2> "$OUTPUT_DIR/${filename}.err"
    
    if [ $? -eq 0 ]; then
        echo "PASS"
        ((pass++))
        # Optional: check if LLVM IR is not empty
        if [ ! -s "$OUTPUT_DIR/${filename}.ll" ]; then
             echo "  [WARNING] Output LLVM IR is empty!"
        fi
    else
        echo "FAIL"
        cat "$OUTPUT_DIR/${filename}.err"
    fi
done

echo "----------------------------------------"
echo "Tests passed: $pass / $count"
echo "========================================"
