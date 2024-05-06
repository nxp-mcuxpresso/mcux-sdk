# Installation
Host SDK is a set of C libraries designed to facilitate communication between a host system (PC with Windows, Linux or OS X) and KWxx boards.
### Installation on Linux
Packages **libudev-dev** (for device discovery) and **libpcap-dev** (for FSCI over RNDIS) are needed.
When system resources are limited or a package manager is not available, one may opt out from linking with udev or pcap by removing USE_(UDEV|PCAP) from the Makefile.

* `$ sudo apt-get install libudev-dev libpcap-dev` (for Debian-based distros)
* `$ sudo yum install libudev-devel libpcap-devel` (for RPM-based distros)
* `$ make`
* `$ sudo make install <PREFIX=...>` (installs Host SDK libraries in `/usr/local/lib/`, if PREFIX is not specified)

### Installation on Windows
Open ConnectivityLibrary.sln with Visual Studio 2013 to generate HSDK.dll and then read ../hsdk-python/lib/README.md for instructions on how to use it with Python (or use the precompiled versions in the same folder).

### Installation on OpenWrt
Host SDK needs to be cross compiled for the MIPS architecture generally present in OpenWrt routers.

1. Follow instructions for installation of [OpenWrt Buildroot](http://wiki.openwrt.org/doc/howto/buildroot.exigence). Pay attention to the prerequisites that are not checked by `make config`.

2. Make sure that **udev** is selected under Base System when issuing `make menuconfig`.

3. Follow instructions for [Cross Compilation](http://wiki.openwrt.org/doc/devel/crosscompile).
    * `$ PATH=$PATH:~/openwrt/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/`
    * `$ export PATH`
    * `$ STAGING_DIR=/home/adrian/openwrt/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/`
    * `$ export STAGING_DIR`

4. `make` - Internet connection is required - make will download patches and other packages selected by user with menuconfig.

5. Host SDK depends on libudev. The header and library for it aren't in the proper location, so we move them.
    * `$ cp ~/openwrt/staging_dir/target-mips_34kc_uClibc-0.9.33.2/usr/include/libudev.h $STAGING_DIR/usr/include/`
    * `$ cp ~/openwrt/staging_dir/target-mips_34kc_uClibc-0.9.33.2/lib/libudev.so $STAGING_DIR/lib/`

6. Compilation
    * `$ make OPENWRT=yes` (installs Host SDK libraries in `$STAGING_DIR/lib`)

### Tests
* `$ cd Tests/`
* `$ make` (`make OPENWRT=yes` when targeting OpenWrt)
* `$ cd bin/` (compiled executables)
