#!/bin/bash
mkdir -p /workspace/build
cd /workspace/build
cmake "$@" ..
cmake --build .