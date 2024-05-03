#!/bin/bash 
set -euxo pipefail
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR/..
QMLFORMAT=/usr/lib/qt5/bin/qmlformat
CMAKEFORMAT=cmake-format

IFS='' #If you want leading spaces to be kept. Remove it if not
# while read line 
# do 
#     $QMLFORMAT -i "$line"
# done < <(find -name "*.qml") 

while read line 
do 
    $CMAKEFORMAT -i "$line"
done < <(find -name "CMakeLists.txt") 
