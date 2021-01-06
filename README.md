# Overview

MCUXpresso SDK is a comprehensive software enablement package designed to simplify and accelerate application development with Arm® Cortex®-M-based devices from NXP, including its general purpose, crossover and Bluetooth™-enabled MCUs. 

Previously user should get MCUXpresso SDK via mcuxpresso.nxp.com or MCUXpresso IDE. Now NXP MCUXpresso SDK project provides a new way for user to achieve this. You could find all NXP hot parts in this project and get below features:

* Arm® CMSIS-CORE startup and device header files and CMSIS-DSP standard libraries
* Open-source peripheral drivers that provide stateless, high-performance, easy-to-use APIs
* Drivers for communication peripherals also include high-level transactional APIs for high-performance data transfers 
* High-quality software: all drivers and startup code are MISRA-C: 2012 compliant and checked with Coverity® static analysis tools
* Software examples demonstrating the usage of peripheral drivers

Other features like RTOS support and middleware stacks currently are not demonstrated in this project. If you are interest in these features please go mcuxpresso.nxp.com to find full SDK support.

# Releases

There are two types of release in the project. The MCUXpresso SDK release and GitHub Main SDK release. Below description uses **MCUX release** short for MCUXpresso SDK release, use **Main release** short for GitHub Main SDK release.

## MCUX Release
The MCUX release launches once a new release is available on [SDK Builder](http://mcuxpresso.nxp.com/). Users previously using [SDK Builder](http://mcuxpresso.nxp.com/) could easily find the exact same code base MCUX release with same 2.x.y version of SDK archive package, software examples build/run quality are guaranteed in the release. **MCUX releases will be prefixed with 'MCUX_'**, and every release will be merged into main branch to ensure main branch has all released boards/socs support. 

The "MCUX_" releases are categorized into mainline releases and NPI release.
* For mainline releases, usually it's planned twice a year to do a global feature update for NXP hot parts. The x in 2.x.y version increments each time a mainline release goes out. 
* For NPI release, it aims to support a new soc product recently launched in the market. It is built with verified features in previous mainline release. The release name is suffixed with NPI name to identify it's an NPI release.

Each MCUX release is made on previous mainline release tag/NPI release tag, thus user could easily check the difference between two releases using ````git diff```` command.

## Main Release
The Main release is a regular release made in main branch. It releases the latest code base and feature set on main branch, which is expected to include all the previous 'MCUX_' release content and new enablement on main branch for NXP hot parts. **Main releases will be prefixed with 'MAIN_'**.

Below figure takes 2.9.0 and 2.10.0 release as an example to show the relationship between MCUX release and Main release.
![Release Introduction](docs/Getting_Started/images/github_release_introduction.png)

# Supported development tools and systems
* Tools
    * MCUXpresso IDE
    * GCC ARM Embedded

    For version of the tool used, please check the release notes in each release.
* Systems

    See [Supported development systems](docs/supported_development_systems.md) for the list of boards/socs currently support in this project.

# Getting Started
See [Getting Start Guide](docs/Getting_Started.md) to start explore the project.

# License
Most of software in the project is open-source and licensed under BSD-3-Clause, see [COPYING_BSD-3](COPYING-BSD-3). Whole license information for the project could be found in [SW-Content-Register.txt](SW-Content-Register.txt)

# Contribution
Currently we are not ready to accept contribution, you could create an issue to suggest a new idea or track a bug. Contribution will be open soon.

