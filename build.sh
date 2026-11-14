#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
mkdir -p build

i686-w64-mingw32-gcc -shared -o build/ss.dll src/main.c -static-libgcc -lshlwapi -luser32

i686-w64-mingw32-windres -I exe exe/ss.rc -O coff -o exe/ss.res
i686-w64-mingw32-gcc -O2 -mwindows -o build/ss.exe exe/main.c exe/ss.res

echo "SS Client by 2014"