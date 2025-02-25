#!/bin/bash

# Copyright 2019-2023 NXP
# All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

# Script gets as first command line argument the directory
# containing the ELF files which will be signed using
# $SIGNING_TOOL. After the signing process, the binary
# is extracted from the ELF file and placed in an equivalent
# filename with the .bin extension.


function is_linux_package_installed()
{
	which ${1} &> /dev/null

	if [ $? -ne 0 ]; then
        echo "Linux package ** ${1} ** is not installed! Please install it then recompile."
        echo "Installation command (Debian-based Linux system): sudo apt-get install ${1}"
		exit 1
	fi
}

function is_python_package_installed()
{
	pip3 list --format=columns | grep -F ${1} &> /dev/null

	if [ $? -ne 0 ]; then
        echo "Python package ** ${1} ** is not installed! Please install it then recompile."
        echo "Installation command: pip3 install ${1}"
		exit 1
	fi
}

function is_win_package_installed()
{
	${1} -V &> /dev/null
	if [ $? -ne 0 ]; then
		echo "WINDOWS package ** ${1} ** is not installed! Please install it then recompile."
		exit 1
	fi
}

# let's determine first if we're on linux or not...
host=`uname -s`
case "${host}" in
    CYGWIN*)    machine=WIN;;
    MINGW*)     machine=WIN;;
    MSYS*)     machine=WIN;;
    *)          machine="LNX"
esac

if [ "${machine}" == "LNX" ]; then
	is_linux_package_installed "python3"
	is_linux_package_installed "pip3"
else
	is_win_package_installed "python3"
	is_win_package_installed "pip3"
fi

is_python_package_installed "pycryptodome"

CURR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ADDITIONAL_ARGS=""

if [ $# -ge 2 ]; then
    ADDITIONAL_ARGS=$2
fi

if [ $# -eq 3 ]; then
    SIGNING_TOOL=$3/dk6_image_tool.py
else
    SIGNING_TOOL=$CURR_DIR/dk6_image_tool.py
fi

MIME_PATTERN="application/x-executable"

if [ "$#" -gt 0 ]; then
	DIR_WITH_ELFS=$1

	for FILENAME in $DIR_WITH_ELFS/*; do
		MIME_SET="$(file -b --mime $FILENAME)"

		if [[ $MIME_SET == *"$MIME_PATTERN"* ]]; then
			OTA_ENABLED=0
			APP_START=`arm-none-eabi-nm $FILENAME | grep -i m_app_start | cut -d " " -f 1`

			APP_START=$((APP_START + 0))
			if [ "$APP_START" -gt 0 ]; then
				OTA_ENABLED=1
			fi

			python3 $SIGNING_TOOL -i="$OTA_ENABLED" $ADDITIONAL_ARGS $FILENAME
			arm-none-eabi-objcopy -O binary $FILENAME $FILENAME.bin
		fi
	done
fi
