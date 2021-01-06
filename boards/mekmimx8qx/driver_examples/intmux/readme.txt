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
- MIMX8QX MEK board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW3 to power on the board.
2.  Connect a micro USB cable between the host PC and the J11 USB port on the cpu board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
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
