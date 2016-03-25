#!/bin/bash

ROOT_PATH="$(cd "$(dirname "$0")" && pwd)"
cd "${ROOT_PATH}" || exit 1

# Make include =================================================================

rm -rf /usr/include/libqvkapi
mkdir -p /usr/include/libqvkapi || exit $?

cp -f include/*.h /usr/include/libqvkapi/ || exit $?

# Make library =================================================================

cd build/QVkApi/Debug || exit 2

make install || exit $?
