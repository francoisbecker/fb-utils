#!/bin/sh
echo "Building the tests..."
mkdir -p build \
&& cd $_ \
&& cmake -G Xcode .. \
&& xcodebuild -project fbu-tests.xcodeproj -target ALL_BUILD -config Debug \
&& ./Debug/fbu-test

