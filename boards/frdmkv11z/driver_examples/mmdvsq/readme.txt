Overview
========
The MMDVSQ Example project is a demonstration program that uses the KSDK software to Calculation square root and Quotient

MMDVSQ Peripheral Driver Example


Start MMDVSQ Example
Calculation square root, please enter radicand
Square root of 9 is 3
Calculation division to get remainder and quotient
Enter dividend and divisor
Remainder of 10 and 5 is 0
Quotient of 10 and 5 is 2

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-KV11Z board
- Personal Computer

Board settings
==============
This Example project does not call for any special hardware configurations. Although not required, the recommendation is to leave the development
board's jumper settings and configurations in default state when running this example.

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~
Start MMDVSQ Example

Calculation square root, please enter radicand
(Input 9 for example)
Square root of 9 is 3

Calculation division to get remainder and quotient
Enter dividend and divisor
(e.g.: "12 3" - input 12 and 3 for example, two number seperated by a blank space)
Remainder of 12 and 3 is 0

Quotient of 12 and 3 is 4
~~~~~~~~~~~~~~~~~~~~~
