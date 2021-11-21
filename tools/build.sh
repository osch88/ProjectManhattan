#!/usr/bin/env bash

cd ..
if [ -d "build" ]; then
    rm -r build
fi

mkdir build
cd build
cmake ..
make