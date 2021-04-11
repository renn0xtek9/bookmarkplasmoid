#!/bin/bash
set -euxo pipefail
rm -rf build
mkdir -p build 
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr .. 
make -j 12
