#!/usr/bin/env bash

set -e

cd ../

mkdir -p build
cd build
cmake ..
cmake --build .
