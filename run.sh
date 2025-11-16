#!/bin/bash

mkdir -p outputs

for file in test/*.mc; do
    filename=$(basename "$file" .mc)
    ./out/bin/minic < "$file" > "outputs/${filename}.out"
    echo "Ran $file -> outputs/${filename}.out"
done

echo "All tests completed."
