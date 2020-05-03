#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR

rm -r ./build
mkdir build
cd build
touch .keep
cmake ..
make

# Binary will be cynapse, but be sure to make this cross-project
if [ "$(uname -sp)" == "Darwin arm64" ]; then
  su -c "cp ./cynapse /usr/bin/cynapse && sign /usr/bin/cynapse"
fi
