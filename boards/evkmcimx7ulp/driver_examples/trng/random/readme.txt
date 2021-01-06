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

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- 5V power supply
- Personal Computer

Board settings
==============
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####


Prepare the Demo
================
1.  Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2.  Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
TRNG Peripheral Driver Example
Generate 10 random numbers:
Random[0] = 0xE4C973F5
Random[1] = 0x25BEBC2B
Random[2] = 0x1A889794
Random[3] = 0xF723958
Random[4] = 0xD9818CFE
Random[5] = 0x409950E7
Random[6] = 0xA9315CA1
Random[7] = 0x5060CAC3
Random[8] = 0x93870888
Random[9] = 0x32DAB69B

 Press any key to continue...
~~~~~~~~~~~~~~~~~~~~~
