#!/bin/bash 
set -euxo pipefail
DEBIBIAN_FRONTEND=noninteractive
sudo apt-get update
sudo apt-get install qt5-default plasma-desktop-dev qml-module-qttest qtdeclarative5-dev libkf5plasma-dev libkf5iconthemes-dev build-essential cmake extra-cmake-modules gettext g++ python3-pip gettext -y
python3 -m pip install cmake-format pre-commit
