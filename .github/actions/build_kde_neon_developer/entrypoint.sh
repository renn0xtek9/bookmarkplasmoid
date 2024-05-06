#!/bin/bash 
set -euxo pipefail
if [ -n "$1" ]
then
    sudo chown -R "$(whoami)" .
    eval "$1"
fi
