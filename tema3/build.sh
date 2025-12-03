#!/bin/bash

set -e  # Stop script if any error occurs

BUILD_DIR="build"
BIN_DIR="bin"
EXEC="resource_manager"

echo "==============================="
echo "  CLEAN + BUILD + RUN PROJECT"
echo "==============================="

# 1. Remove old build
echo "[1] Removing old build..."
rm -rf "$BUILD_DIR"
rm -rf "$BIN_DIR"

# 2. Create new build directory
echo "[2] Creating build directory..."
mkdir "$BUILD_DIR"

# 3. Run CMake configuration
echo "[3] Configuring project with CMake..."
cmake -S . -B "$BUILD_DIR"

# 4. Run compilation
echo "[4] Compiling project..."
# Check if nproc exists (Linux), otherwise use sysctl (macOS) or default to 4
if command -v nproc &> /dev/null; then
    JOBS=$(nproc)
elif command -v sysctl &> /dev/null; then
    JOBS=$(sysctl -n hw.ncpu)
else
    JOBS=4
fi

cmake --build "$BUILD_DIR" -- -j${JOBS}

# 5. Run the executable
echo ""
echo "[5] Running application:"
echo "--------------------------------"
./"$BIN_DIR"/"$EXEC"
echo "--------------------------------"

echo ""
echo "Everything completed successfully! ✓"


