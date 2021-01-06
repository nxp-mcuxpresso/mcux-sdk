Overview
========
The lpuart_functioncal_interrupt example shows how to use lpuart driver functional
API to receive data with interrupt method:

In this example, one lpuart instance connect to PC, the board will
send back all characters that PC send to the board.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK CPU Board
- MCIMX8-8X-BB
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- USB to RS232 Convertor

Board settings
==============
Connect USB to RS232 Convertor to J37 (On base board) if there's no RS232 port on your host PC.
For CM4_0, use the serial port provided by J18(On CPU board).
For CM4_1, use the serial port provided by J37(On Base board).

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
5.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Lpuart functional API interrupt example

Board receives characters then sends them out

Now please input:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
