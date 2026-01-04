#!/bin/bash

# 1. Clean and Build
echo "========================================"
echo " 1. Building Project"
echo "========================================"
make clean
make

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

# 2. Run Automation Verification
echo -e "\n========================================"
echo " 2. Running Verification Suite"
echo "========================================"
cd tests
./verify.sh
cd ..

# 3. Generate Output Files
echo -e "\n========================================"
echo " 3. Generating Output Files (outputs/)"
echo "========================================"
mkdir -p outputs
for file in tests/*.mc; do
    filename=$(basename "$file" .mc)
    ./minic < "$file" > "outputs/${filename}.out" 2>&1
    echo "Generated outputs/${filename}.out"
done

# 4. Generate Visualization
echo -e "\n========================================"
echo " 4. Generating Visualization (test5)"
echo "========================================"
./minic -dot < tests/test5.mc > ast.dot
if command -v dot &> /dev/null; then
    dot -Tpng ast.dot -o ast.png
    echo "Generated ast.png"
else
    echo "Graphviz 'dot' command not found. Skipping PNG generation."
fi

echo -e "\nBuild and Run Complete!"
