#!/bin/sh
echo "Building the tests..."
mkdir -p build \
&& cd $_ \
&& cmake .. \
&& make \
&& ./fbu-test

