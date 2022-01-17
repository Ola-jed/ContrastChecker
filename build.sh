#!/usr/bin/env sh
mkdir build
cmake -S . -B build
cd build
make
./ContrastChecker