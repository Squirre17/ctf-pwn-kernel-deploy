#!/bin/bash
path=$PWD
set -eu
RED="\033[31m"
BLUE="\033[34m"
GREEN="\033[32m"
DFT="\033[0m" # default
if [ ! -d $path/rootfs ]; then
	echo -e "[${RED}!${DFT}] Error: $path/rootfs not exist"
	exit 1
fi

if [ ! -d $path/rootfs/etc ]; then
	echo -e "[${RED}!${DFT}] Error: $path/rootfs/etc not exist"
	exit 1
fi
mv $path/rootfs/etc/ .
echo -e "[${GREEN}+${DFT}] mvetc.sh done"