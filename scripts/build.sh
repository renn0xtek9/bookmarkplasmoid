#!/bin/bash
set -euxo pipefail 
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Never build without formatting before
$SCRIPT_DIR/format.sh
cd $SCRIPT_DIR/../
mkdir -p build 
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr .. -DBUILD_TESTING=ON
make -j12 
