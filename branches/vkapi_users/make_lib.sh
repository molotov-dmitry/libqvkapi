#!/bin/bash

ROOT_PATH="$(cd "$(dirname "$0")" && pwd)"
cd "${ROOT_PATH}" || exit 1

# Check script launched as root ================================================

if [[ "$(whoami)" != 'root' ]]
then
    if [ -t 1 ]
    then
        sudo bash "$0" $*
    else
        gksudo bash "$0" $*
    fi
    
    exit $?
fi

# Make include =================================================================

rm -rf /usr/include/libqvkapi
mkdir -p /usr/include/libqvkapi || exit $?

cp -f include/*.h /usr/include/libqvkapi/ || exit $?

# Make library =================================================================

for makefile in $(find ./build -name Makefile)
do
    cd "${ROOT_PATH}"
    cd "$(dirname "${makefile}")" || exit $?

    make install || exit $?
done
