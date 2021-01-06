Overview
========
The ELCDIF LUT project shows how to use the ELCDIF LUT to convert 8-bit input pixel
to 24-bit output pixel. There are two LUT memories, this project uses one input
frame buffer, and swithes between the two memories, so from the LCD panel, two
different pictures are shown one by one.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- EVKB-IMXRT1050 board
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
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo..

Running the demo
================
If this example runs correctly, the screen switches between red and blue.
