Overview
========

The asrc_m2m_sdma example shows how to use asrc driver with sdma:

In this example, one asrc instance convert the audio data stored in flash/SRAM/DDR by SDMA channel and then playback through SAI.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8MN6-EVK board
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- Headphone

Board settings
==============
No special settings are required.

#### Note! ####
This case does not support TCM targets because of limited memory size.
This case does not support flash targets because of SDMA2 burst DMA not supporting for accessing flexspi.

#### Please note this application can't support running with Linux BSP! ####

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
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
<<<<<<< HEAD
When the demo runs successfully, you will hear two audio clips, the first one is the original 44.1k, the second one is the converted 16K and the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~
ASRC memory to memory SDMA example.
Playback original 44.1K audio data.
Playback converted 16K audio data.
ASRC memory to memory SDMA example finished.
 ~~~~~~~~~~~~~~~~~~~

