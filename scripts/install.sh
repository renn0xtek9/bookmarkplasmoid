#!/bin/bash
set -euxo pipefail
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"
./build.sh
./test.sh
cd ../build/
sudo make install
