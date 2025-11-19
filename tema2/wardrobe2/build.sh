#!/bin/bash
mkdir -p build
mkdir -p bin
cd build
# Șterge cache-ul vechi pentru a evita erorile de cale
rm -f CMakeCache.txt
cmake ..
cmake --build .
cd ..
echo "Build completat! Executabilul este în bin/wardrobe"

