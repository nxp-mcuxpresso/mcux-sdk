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
- Mini USB cable
- FRDM-K32L2A4S board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

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
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~
TRNG Peripheral Driver Example
Generate 10 random numbers:
Random[0] = 0xF84D63F2
Random[1] = 0xC480F1AC
Random[2] = 0x554277AE
Random[3] = 0x13EAFA4E
Random[4] = 0x3FDF87B0
Random[5] = 0x502E3E7A
Random[6] = 0x6B692AAE
Random[7] = 0x8906DB6C
Random[8] = 0x8BC1AC01
Random[9] = 0xD9C74853

 Press any key to continue...
~~~~~~~~~~~~~~~~~~~~~~~~~~~
