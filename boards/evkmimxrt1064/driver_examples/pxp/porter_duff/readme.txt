Overview
========
This example shows how to use the PXP Porter Duff compositing. In this example,
A blue rectangle is in the left up corner of the destination surface (also named
PS surface, or s0 in reference mannal). A red rectangle is in the center of the
source surface (also named AS surface, or s1 in reference mannal). Every Porter Duff
mode result is shown 2 seconds, then switch to the other mode.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
- Personal Computer
- RK043FN02H-CT LCD board

Board settings
==============
1. Connect the RK043FN02H-CT board to J8.

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
When the demo runs successfully, press any key in the terminal, the panel
shows different porter duff mode result.
