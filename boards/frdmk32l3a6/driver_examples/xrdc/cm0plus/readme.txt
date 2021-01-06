Overview
========
The xrdc example shows how to control the memory and peripheral access
policy using XRDC.

In this example, one peripheral and a memory region are set to unaccessible, then
the hardfault occurs.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
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
The log below shows the output of the example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
XRDC example start
Set the peripheral not accessiable
Violent access at address: 0x40032000
The peripheral is accessiable now
Set the memory not accessiable
Violent access at address: 0x 8000000
The memory is accessiable now
XRDC example Success
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
