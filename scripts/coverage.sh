#!/usr/bin/env bash

set -e
export GTEST_COLOR=1
export CTEST_OUTPUT_ON_FAILURE=true

cd ../

cmake -H. -Bbuild  -DBUILD_COVERAGE=ON
cmake --build build
cmake --build build --target test --verbose
gcovr -r . | sed '/tests/d'
