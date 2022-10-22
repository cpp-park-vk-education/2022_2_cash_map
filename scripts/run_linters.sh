#!/usr/bin/env bash

set -o pipefail

cd ../

echo -e "\n==============cppcheck server================"
cppcheck server --enable=all --inconclusive --error-exitcode=1 \
-I server/include -I server/tests/include --suppress=missingIncludeSystem

echo -e "\n==============cppcheck client================"
cppcheck client --enable=all --inconclusive --error-exitcode=1 \
-I client/include -I client/tests/include --suppress=missingIncludeSystem



echo -e "\n==============clang-tidy server================"
clang-tidy server/src/* server/include/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iserver/include

echo -e "\n==============clang-tidy client================"
clang-tidy client/src/* client/include/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iclient/include


echo -e "\n==============cpplint server===================="
cpplint --extensions=c server/include/* server/src/*

echo -e "\n==============cpplint client===================="
cpplint --extensions=cpp client/include/* client/src/*