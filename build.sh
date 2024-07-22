#!/bin/sh

#PICO
export PICO_HOME="/usr/share/pico-sdk"
export PICO_SDK_PATH="$PICO_HOME"

cmake -S . -B out/build
cd out/build && make
