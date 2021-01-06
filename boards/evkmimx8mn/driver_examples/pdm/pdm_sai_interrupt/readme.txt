Overview
========
The pdm sai interrupt example shows how to use pdm driver with interrupt:

In this example, pdm gather audio data, and sai send it to codec.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8MN6-EVK  board
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- Microphone
- Headphone

Board settings
==============
Connect microphone module to EVK board:
3V->J1003-1
GND->J1003-6
CLK->J1003-40
DATA->J1003-38
Connect headphone to J401

#### Note! ####
There are two microphones on module, please put the sound source in the middle of microphones for balance.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW101 to power on the board
2.  Connect a USB cable between the host PC and the J901 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.


Running the demo
================
When the demo runs successfully, you can hear the sound gathered from microphone and the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~
PDM sai interrupt example started!
~~~~~~~~~~~~~~~~~~~




