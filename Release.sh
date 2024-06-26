#!/bin/bash
version_number=$(grep "^Version number:" Readme.md |sed 's/Version number://g')

if [ -z "$version_number" ]
then
	echo "Could not detect version number"
	exit 1
fi
# shellcheck disable=SC2001
major=$(echo "$version_number" | sed 's/\([0-9]*\)\..*/\1/g')
# shellcheck disable=SC2001
minor=$(echo "$version_number" | sed 's/[0-9]*\.\([0-9]*\)\..*/\1/g')
# shellcheck disable=SC2001
patch=$(echo "$version_number" | sed 's/[0-9]*\.[0-9]*\.\([0-9]*\)/\1/g')

echo "Current version number is $major.$minor.$patch"
patch=$(( patch + 1 ))
echo "Will make a release for $major.$minor.$patch"



#Replace in CMake
sed -i "s/^set(PROJECT_VERSION_MAJOR [0-9]*)/set(PROJECT_VERSION_MAJOR $major)/" CMakeLists.txt
sed -i "s/^set(PROJECT_VERSION_MINOR [0-9]*)/set(PROJECT_VERSION_MINOR $minor)/" CMakeLists.txt
sed -i "s/^set(PROJECT_VERSION_PATCH [0-9]*)/set(PROJECT_VERSION_PATCH $patch)/" CMakeLists.txt

#Edit the Reamde.md


sed -i "s/^Version number:[0-9]*\.[0-9]*\.[0-9]*/Version number:$major.$minor.$patch/" Readme.md
sed -i "s/## Changelog/## Changelog \nVersion $major.$minor.$patch/" Readme.md

tmp=$(mktemp -d)
cd ..
rsync -av --progress --exclude="Release" --exclude="build" --exclude=".git" --exclude=".vscode"  --exclude=".kdev4" --exclude="BookMarkWidgets/*.kdev4" BookMarkWidgets "$tmp"
cd BookMarkWidgets || exit 1
7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on BookMarkWidgets-"$major"-"$minor"-"$patch".7z "$tmp"/BookMarkWidgets
mv BookMarkWidgets-"$major"-"$minor"-"$patch".7z ./Release/


echo "$tmp"
echo "Finished"
exit 0
