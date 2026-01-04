#!/usr/bin/env bash
set -e

if [ -z "$1" ]; then
    echo "Usage: $0 <source_file>"
    exit 1
fi

SOURCE_FILE="$1"
BASENAME=$(basename "$SOURCE_FILE" .mc)
DIRNAME=$(dirname "$SOURCE_FILE")
OUTPUT_LL="${DIRNAME}/${BASENAME}.ll"
OUTPUT_ASM="${DIRNAME}/${BASENAME}.s"
OUTPUT_EXE="${DIRNAME}/${BASENAME}"

# 1. Parse and Generate LLVM IR
../../bin/parser "$SOURCE_FILE" > "$OUTPUT_LL"
if [ $? -ne 0 ]; then
    echo "Error: Parser failed."
    exit 1
fi

# 2. Compile LLVM IR to Assembly using llc
llc "$OUTPUT_LL" -o "$OUTPUT_ASM"
if [ $? -ne 0 ]; then
    echo "Error: llc failed."
    exit 1
fi

# 3. Assemble and Link using gcc
gcc "$OUTPUT_ASM" -o "$OUTPUT_EXE" -no-pie
if [ $? -ne 0 ]; then
    echo "Error: gcc failed to link."
    exit 1
fi

echo "Successfully built executable: $OUTPUT_EXE"
