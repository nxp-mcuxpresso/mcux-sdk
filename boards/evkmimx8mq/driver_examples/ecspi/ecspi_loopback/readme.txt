Overview
========
The ecspi_loopback demo shows how the ecspi do a loopback transfer internally.
The ECSPI connects the transmitter and receiver sections internally, and the data shifted out from the 
most-significant bit of the shift register is looped back into the least-significant bit of the Shift register. 
In this way, a self-test of the complete transmit/receive path can be made. The output pins are not affected, 
and the input pins are ignored.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MCIMX8MQ6-EVK  board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.



Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW701 to power on the board
2.  Connect a USB cable between the host PC and the J1701 USB port on the target board.
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
If the demo run successfully, the below log will be print in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
***ECSPI Loopback Demo***

This demo is a loopback transfer test for ECSPI.
The ECSPI will connect the transmitter and receiver sections internally.
So, there is no need to connect the MOSI and MISO pins.

ECSPI loopback test pass!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
