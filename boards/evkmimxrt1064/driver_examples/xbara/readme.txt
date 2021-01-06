Overview
========
The Xbara project is a simple demonstration program of the SDK Xbara driver.The intended application
of this module is to provide a flexible crossbar switch function that allows any input to be
connected to any output under user control.It sets up the Xbara hardware block to trigger a periodic
interrupt after every 1 second. When the Xbar interrupt is triggered a message a printed on the UART
terminal.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- MIMXRT1064-EVK board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
These instructions are displayed/shown on the terminal window:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
XBARA Peripheral Driver Example.
XBARA interrupt is occured !
XBARA interrupt is occured !
XBARA interrupt is occured !
............................
............................
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
