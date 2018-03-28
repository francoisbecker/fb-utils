#!/bin/sh
mkdir -p build \
&& g++ -Wall -Wextra -Dlest_FEATURE_AUTO_REGISTER=1 -std=c++11 -o build/test *.cpp \
&& ./build/test

