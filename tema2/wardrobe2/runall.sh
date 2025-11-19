#!/bin/bash

set -e  # oprește scriptul dacă apare o eroare

BUILD_DIR="build"
BIN_DIR="bin"
EXEC="wardrobe"

echo "==============================="
echo "  CLEAN + BUILD + RUN PROJECT"
echo "==============================="

# 1. Stergere build vechi
echo "[1] Ștergem build-ul vechi..."
rm -rf "$BUILD_DIR"
rm -rf "$BIN_DIR"

# 2. Creăm build nou
echo "[2] Creăm directorul de build..."
mkdir "$BUILD_DIR"

# 3. Run CMake configurare
echo "[3] Configurăm proiectul cu CMake..."
cmake -S . -B "$BUILD_DIR"

# 4. Rulează compilarea
echo "[4] Compilăm proiectul..."
cmake --build "$BUILD_DIR" -- -j$(nproc)

# 5. Rulează executabilul
echo ""
echo "[5] Rulăm aplicația:"
echo "--------------------------------"
./"$BIN_DIR"/"$EXEC"
echo "--------------------------------"

echo ""
echo "Totul a mers perfect "
