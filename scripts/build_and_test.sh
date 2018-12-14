#!/usr/bin/env sh
mkdir build
cd build
cmake ..
make
ctest -j6 -C Debug -T test --output-on-failure
cd ..