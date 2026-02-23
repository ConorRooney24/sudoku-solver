#!/usr/bin/env bash

TARGET=${1:-linux}

SRC="main.c src/*.c"
OUT="build/sudoku"

echo "Compiling for target: [$TARGET]"

if [ "$TARGET" = "linux" ]; then
        x86_64-linux-gnu-gcc $SRC -o $OUT

elif [ "$TARGET" = "windows" ]; then
        x86_64-w64-mingw32-gcc $SRC -o ${OUT}.exe -static
        
else
        echo "Invalid target specified '$TARGET'"
        exit 1
fi