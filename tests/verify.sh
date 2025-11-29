#!/bin/bash
for file in *.mc; do
    echo "Testing $file..."
    ../out/bin/minic < "$file"
    echo "--------------------------------"
done
