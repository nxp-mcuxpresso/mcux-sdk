#!/bin/bash
# Copyright 2020 NXP
# All rights reserved.

# SPDX-License-Identifier: BSD-3-Clause

###########################################################################################
# Bash script for loading CM4 ELF files to the remote iMX ARM-CM4 core via SSH and
# starting/stopping it using remoteproc. In order to use this script, make sure the remoteproc 
# Linux kernel module is loaded and that the device is connected to your local network with an IP.
# The authentication is performed using SSH keys. 

# Set up the SSH keys beforehand (https://www.ssh.com/ssh/keygen) and make sure you can login
# to the device without having to provide a password! 

# Configure the Linux login Username and IP address (hostname) in the device.cfg file and test the
# connection using `load.sh state`. 
# The script was tested with OpenSSH version 8.1 which is provided with the Windows Git Bash
############################################################################################

## Configuration file - contains the Username and Hostname of the remote
source ./remote.cfg

## Print Usage
function print_usage {
    echo "Usage: load.sh <firmware.elf> [action]";
    echo "    flash   - (default) download the ELF file to the remote and start the core";
    echo "    start   - Start the remote core";
    echo "    stop    - Stop the remote core";
    echo "    restart - Restart the remote core";
    echo "    state   - Get the state of the remote core";
}


if [[ -z "$1" || "$1" == "-h" || "$1" == "--help" || "$1" == "-help" || "$1" == "help" ]]; then
    print_usage;
    exit 0;
fi

if [[ $# == 1 ]]; then

    # We need a firmware file in order to flash
    if [[ "$1" == "flash" ]]; then
        echo "Please provide a ELF firmware file: load.sh <firmware.elf> flash";
        exit 1;
    fi
    
    # These comands can be executed without firmware file
    if [[ "$1" == "start" || "$1" == "stop"  || "$1" == "restart"  || "$1" == "state" ]]; then
        ACTION=$1;
    else
        # The argument is probably a path, we are going to flash by default
        ACTION='flash';
    fi
elif [[ $# == 2 ]]; then
    # When two arguments provided, first is the elf file path, the second is a command.
    ACTION="$2";
else
    echo "Invalid number of arguments";
    print_usage;
    exit 1;
fi


# TODO: Better way of converting paths (only valid for flash command)
ELFPATH=$(echo "$1" | sed -e 's/\\/\//g' -e 's/C:/\/c/');     # Convert Windows path to UNIX path
ELFNAME="$(basename $ELFPATH)";

### Commands to execute on the Remote
#------------------------------------
#  1. Check if the M4 core is in the running state, and if nescessary stop it
#  2. Set the firmware to the name of the new ELF file
#  3. Start the M4 core

REMOTEPROC_START="\
echo start > $REMOTEPROC/state;";

REMOTEPROC_STOP="\
[[ \$(< $REMOTEPROC/state) == 'running' ]] && echo stop > $REMOTEPROC/state; ";

REMOTEPROC_FLASH="\
$REMOTEPROC_STOP \
echo $ELFNAME.elf > $REMOTEPROC/firmware; \
$REMOTEPROC_START";

REMOTEPROC_RESTART="\
$REMOTEPROC_STOP \
$REMOTEPROC_START";

REMOTEPROC_GET_STATE="\
cat $REMOTEPROC/state;";


# Build the SSH Username and Hostname string
SSH_USER_HOST="$SSH_USER@$SSH_HOST";


# If specifying a jump proxy, set the 
if [[ -n "$SSH_PROXY" ]]; then
SSH_PROXY="-J $SSH_PROXY";
fi 

# If designating a different SSH port, set up the correct flags
if [[ -n "$SSH_PORT" ]]; then
SSH_PORT_SCP="-P $SSH_PORT";
SSH_PORT_SSH="-p $SSH_PORT";
else 
SSH_PORT_SCP="";
SSH_PORT_SSH="";
fi 

## get_core_state retrieves the state of the core from the remote and prints it to the console
function get_core_state {
    result="$(echo $REMOTEPROC_GET_STATE | \
    ssh $SSH_PROXY $SSH_PORT_SSH $SSH_USER_HOST 'bash -s')";
    
    if [ $? != 0 ]; then
        echo "Failed getting Core state";
        exit 1;
    fi
    
    echo "M4 Core is $result!";
}

## Copy firmware ELF file to the remote /lib/firmware directory
function flash_firmware {
    echo "==========================================";
    echo "Copying $ELFNAME to remote $SSH_USER_HOST";

    scp $SSH_PROXY $SSH_PORT_SCP $ELFPATH $SSH_USER_HOST:/lib/firmware/$ELFNAME.elf;

    if [ $? != 0 ]; then
        echo "Failed Transfering ELF file!";
        get_core_state;
        exit 1;
    fi
}

## Send a given remoteproc bash script, passed as an argument, to the remote 
function send_rproc_cmd {
    echo $1 |
    ssh $SSH_PROXY $SSH_PORT_SSH $SSH_USER_HOST "bash -s";
    
    if [ $? != 0 ]; then
        echo "Failed executing remoteproc command!";
        get_core_state;
        exit 1;
    fi
}



case $ACTION in
    "start")
        echo "================";
        echo "Starting M4 core";
        send_rproc_cmd "$REMOTEPROC_START";
        get_core_state;
        ;;
    "stop")
        echo "================";
        echo "Stopping M4 core";
        send_rproc_cmd "$REMOTEPROC_STOP";
        get_core_state;
        ;;
    "restart")
        echo "==================";
        echo "Restarting M4 core";
        send_rproc_cmd "$REMOTEPROC_RESTART";
        get_core_state;
        ;;
    "flash")
        flash_firmware;
        echo "================";
        echo "Starting M4 core";
        send_rproc_cmd "$REMOTEPROC_FLASH";
        get_core_state;
        ;;
    "state")
        get_core_state;
        exit;
        ;;
    *)
        echo "Unknown command $ACTION";
        exit 1;
        ;;
esac


exit;