Overview
========
This driver example should demonstrate how to setup BEE driver for on the fly decryption of data stored in QSPI memory region. The BEE is configuerd to 
decrypt all data starting from location 0x6000_0000 to 0x6001_0000 using AES ECB mode with user specified key. If the BEE_KEY_SEL fuse is programmed, then OTPMK key will be used instead.
The example itself does not perform any data decryption operation over QSPI. It is used only as a BEE setup guide.

Toolchain supported
===================
- MCUXpresso  11.3.0
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1060 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BEE Example.

BEE was succesfully configured for reading from 0x60000000 to 0x60010000.

Example end.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
