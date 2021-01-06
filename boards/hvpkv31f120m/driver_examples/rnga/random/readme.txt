Overview
========
The RNGA is a digital integrated circuit capable of generating the 32-bit random numbers. The RNGA
Example project is a demonstration program that uses the KSDK software to generate random numbers
and prints them to the terminal.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- HVP-KV31F120M board
- Personal Computer

Board settings
==============
The RNGA demo does not call for any special hardware configurations.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
When the demo runs successfully, from the terminal you can see:

RNGA Peripheral Driver Example
Generate 10 random numbers:
Random[0] = 0xE1554295
Random[1] = 0x827AD456
Random[2] = 0x9A1CBE1E
Random[3] = 0x4354CB53
Random[4] = 0xFE3B2494
Random[5] = 0xEDAB3F7D
Random[6] = 0x9AB91722
Random[7] = 0x4F54D999
Random[8] = 0x492414D1
Random[9] = 0x84611992

 Press any key to continue...
