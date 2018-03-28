#!/bin/sh
mkdir -p build \
&& g++ -Wall -Wextra -I../include -Dlest_FEATURE_AUTO_REGISTER=1 -std=c++11 -o build/test *.cpp \
&& ./build/test

