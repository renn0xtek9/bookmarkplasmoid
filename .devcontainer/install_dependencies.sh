#!/bin/bash 
set -euxo pipefail
DEBIBIAN_FRONTEND=noninteractive
sudo apt-get install extra-cmake-modules plasma-desktop-dev qml-module-qttest qtdeclarative5-dev libkf5iconthemes-dev build-essential g++ python3 -y
python3 -m pip install cmake-format
