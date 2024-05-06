#!/bin/bash 
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit 1

directory=$(mktemp -d)
echo "Copy files over to $directory to try there"
cp -r "$SCRIPT_DIR"/../plasmoid "$directory"
cd "$directory" || exit 1

sed -i "s%path/to/konqueror/bookmarks.xml%$HOME/.local/share/konqueror/bookmarks.xml%" plasmoid/contents/config/main.xml
sed -i "s%path/to/okular/bookmarks.xml%$HOME/.local/share/okular/bookmarks.xml%" plasmoid/contents/config/main.xml
export LD_LIBRARY_PATH="$SCRIPT_DIR"/build/libbookmarksmodule/Bookmarkmodelplugin:"$LD_LIBRARY_PATH"
export QML_IMPORT_PATH="$SCRIPT_DIR"/build/libbookmarksmodule/Bookmarkmodelplugin:"$QML_IMPORT_PATH"
plasmoidviewer -a plasmoid
