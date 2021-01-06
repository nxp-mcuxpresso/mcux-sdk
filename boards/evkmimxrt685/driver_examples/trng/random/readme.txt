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
- Micro USB cable
- EVK-MIMXRT685 board
- Personal Computer

Board settings
==============


Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J5) on the board
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the trng example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TRNG Peripheral Driver Example
Generate 10 random numbers: 
Random[0] = 0x201FEB53
Random[1] = 0x85A32C28
Random[2] = 0xDC66342C
Random[3] = 0xFD43ACFF
Random[4] = 0x1CD53C0
Random[5] = 0xB27EDBEB
Random[6] = 0x32AB81D5
Random[7] = 0x6AA5B70F
Random[8] = 0x81C41286
Random[9] = 0xC9620BD8

 Press any key to continue... 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
