Overview
========
The True Random Number Generator (TRNG) is a hardware accelerator module that generates a 512-bit
entropy as needed by an entropy consuming module or by other post processing functions. The TRNG
Example project is a demonstration program that uses the KSDK software to generate random numbers
and prints them to the terminal.

NOTE:

On i.MXRT1020/1050/1060, the TRNG entropy register is initialized by the ROM boot process
with 128 entropy bits (read from registers ENT12-ENT15, sampleSize = 128).
 
The TRNG driver version <= 2.0.2 has issue that TRNG_Init() function doesn't flush
these entropy bits, thus, the first TRNG_GetRandomData(base, data, 64) after TRNG_Init()
only reads 384 non-random bits followed by 128 random bits. After the first call, next calls
to TRNG_GetRandomData() return entropy bits collected with new TRNG settings.

The issue is fixed in TRNG driver version 2.0.3, by regenerating entropy bits with new
TRNG settings already during TRNG_Init().



Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVKB-IMXRT1050 board
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
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

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
