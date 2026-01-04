#!/bin/bash
for file in ../inputs/*.mc; do
    echo "Testing $file..."
    ../../bin/parser < "$file"
    echo "--------------------------------"
done
