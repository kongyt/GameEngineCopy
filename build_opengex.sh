#!/bin/bash
mkdir -p External/build/opengex
cd External/build/opengex
cmake -DCMAKE_INSTALL_PREFIX=../../Linux ../../src/opengex
cmake --build . --config release --target install