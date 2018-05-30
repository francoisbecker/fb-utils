#!/bin/sh
echo "Building the tests..."
mkdir -p build \
&& g++ -Wall -Wextra -I../include -Dlest_FEATURE_AUTO_REGISTER=1 -std=c++11 -o build/test ./src/*.cpp \
&& ./build/test

