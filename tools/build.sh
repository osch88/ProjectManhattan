#!/usr/bin/env bash

cd ..
#if [ -d "build" ]; then
#    rm -r build
#fi

#mkdir build
mkdir -p build
cd build
cmake ..
make && test/test_hal_monitor