Overview
========
The gpt_timer project is a simple demonstration program of the SDK GPT driver. It sets up the GPT
hardware block to trigger a periodic interrupt after every 1 second. When the GPT interrupt is triggered
a message a printed on the UART terminal.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8MM6-EVK  board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
No special is needed.



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
When the example runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~

Press any key to start the example
s
Starting GPT timer ...
 GPT interrupt is occurred !
 GPT interrupt is occurred !
 GPT interrupt is occurred !
 GPT interrupt is occurred !
 .
 .
 .
 GPT interrupt is occurred !
 .
 .
 .
~~~~~~~~~~~~~~~~~~~~~
