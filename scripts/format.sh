#!/bin/bash 
set -euxo pipefail
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR/..
QMLFORMAT=/usr/lib/qt5/bin/qmlformat


IFS='' #If you want leading spaces to be kept. Remove it if not
while read line 
do 
    $QMLFORMAT -i "$line"
done < <(find -name "*.qml") 
