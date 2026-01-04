#!/bin/bash
for file in *.mc; do
    echo "Testing $file..."
    ../minic < "$file"
    echo "--------------------------------"
done
