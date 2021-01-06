Remoteproc load script
========

Bash script for remotely flashing M4 core using SSH

Remoteproc is a Linux utility which allows to start, stop and flash a secondary core, such as the ARM M4 in the i.MX 8 series, directly from Linux user space without requiring a reboot.

This script connects to a given Linux target using SSH and allows starting, stopping and  flashing new firmware for the secondary core over the network.

## Configuration and setup

SSH is utilized for connecting to the target. Therefore it is necessary for the target to be connected to the network and reachable form the client machine.

In windows, the recommended shell is the git-bash shell shipped with the standard Git application. Other bash shells such as Cygwin may not work due to different path handling and different shell versions.

**SSH Keys**

It is also mandatory to set up access to the target with SSH Keys for authentication (https://www.ssh.com/ssh/keygen). This enables login to the target without having to provide a password.

The target is configured using the `remote.cfg` file. 

```bash
# Copyright 2020 NXP
# All rights reserved.

# SPDX-License-Identifier: BSD-3-Clause

## Device configuration file for remote connection to iMX CortexA cores

SSH_USER=root                                   # SSH User
SSH_HOST=192.168.0.100                          # SSH Host target
SSH_PORT=''                                     # Set the SSH port
SSH_PROXY=                                      # SSH Jump proxy
REMOTEPROC=/sys/class/remoteproc/remoteproc0    # Remoteproc path

```

At minimum, the `SSH_USER` and `SSH_HOST` must be specified. The  `SSH_HOST` is the IP address or hostname under which the Linux machine is reachable and the SSH_USER is the user to be used. Currently, due to the requirement of sudo privileges for remoteproc usage, it is advised to only use the root user.

`SSH_PROXY` is an optional setting for allowing tunneling through multiple SSH proxies before reaching the target. See https://www.redhat.com/sysadmin/ssh-proxy-bastion-proxyjump By default it can be left blank.

`REMOTEPROC` is the location of the remoteproc device file in Linux. This should also stay untouched.

##  Usage

The load script can be used from command line by providing it a path to a project output ELF file and a command to be executed on the target (start, stop, flash, restart....). *Note: In IAR, the output ELF file has the extension `.out`.*

### Flashing
To flash the firmware located at `iar/debug/hello_world.out` relative to the load script, one can issues this command:

```bash
./load.sh debug/hello_world.out flash
```

### Restarting
In order to remotely restart the core:

```bash
./load.sh debug/hello_world.out restart
## Or just simply
./load.sh restart
```

### State
To get the state of the remote core:
```bash
./load.sh debug/hello_world.out state
## Or just simply
./load.sh state
M4 Core is running!
```
For more help see:
```bash
./load.sh -h
```

## A word on Project Paths

The `load.sh` together with the default `remote.cfg` is located in `middleware/multicore/tools/remoteproc-load/`. It can be used directly from this location, however the path to the ELF file must then either be provided as an absolute or relative path. 

```bash
# Flashing hello_world using relative path
./load.sh ../../../../boards/evkmimx8mq/demo_apps/hello_world/iar/debug/hello_world.out flash
# Flashing hello_world using absolute path
./load.sh "C:\<Path_to_SDK>\boards\evkmimx8mq\demo_apps\hello_world\iar\debug\hello_world.out" flash
```

It is always advisable to wrap Windows paths in "".  However as can be seen, both methods are very cumbersome. It is therefore advised to manually copy the `load.sh` and `remote.cfg` to the directory of the desired project and execute the load script from there with a much simplified path:

```bash
# Copy load script and remote config to the project directory
cp middleware/multicore/tools/remoteproc-load/load.sh boards/evkmimx8mq/demo_apps/hello_world/
cp middleware/multicore/tools/remoteproc-load/remote.cfg boards/evkmimx8mq/demo_apps/hello_world/

# Move to the directory
cd boards/evkmimx8mq/demo_apps/hello_world

./load.sh iar/debug/hello_world.out flash
```

