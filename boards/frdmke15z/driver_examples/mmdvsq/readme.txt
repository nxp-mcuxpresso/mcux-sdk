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
- Micro USB cable
- FRDM-KE15Z board
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
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
Start MMDVSQ Example

Calculation square root, please enter radicand
(Input 9 for example)
Square root of 9 is 3

Calculation division to get remainder and quotient
Enter dividend and divisor
(Input 12 and 3 for example, seperated two number by a blank space)
Remainder of 12 and 3 is 0

Quotient of 12 and 3 is 4
~~~~~~~~~~~~~~~~~~~~~
