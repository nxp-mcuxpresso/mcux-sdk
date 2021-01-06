Overview
========
This example shows how to use INTMUX to route the internel interrupt to the system.

In this example, one of the INTMUX input source(such as LPIT, TPM) is used to generate internel interrupt.
The internel interrupt is outputted to system through INTMUX. Then the interrupt is handled by IRQSTEER, which
located outside of the CM4 subsystem.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK CPU Board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

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
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
INTMUX example started.
The interrupt came from INTMUX was handled
The interrupt came from INTMUX was handled
The interrupt came from INTMUX was handled
The interrupt came from INTMUX was handled
The interrupt came from INTMUX was handled
......
~~~~~~~~~~~~~~~~~~~~~
