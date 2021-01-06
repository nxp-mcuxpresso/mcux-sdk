Overview
========
The Xbar project is a simple demonstration program of the SDK Xbar driver.The intended application
of this module is to provide a flexible crossbar switch function that allows any input to be
connected to any output under user control.It sets up the Xbar hardware block to trigger a periodic
interrupt after every 1 second. When the Xbar interrupt is triggered a message a printed on the UART
terminal.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- TWR-KM35Z75M board
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
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
XBAR Peripheral Driver Example.
XBAR interrupt is occurred !
XBAR interrupt is occurred !
XBAR interrupt is occurred !
........................
........................
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
