Overview
========
The sai_interrupt example shows how to use sai functional API to implement interrupt playback:

In this example, one sai instance playbacks the audio data stored in flash/SRAM using interrupt.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- J-Link Debug Probe
- 5V power supply
- Personal Computer
- Headphone

Board settings
==============

#### Please note this application can't support running with Linux BSP! ####

Note
~~~~~~~~~~~~~~
Because of the hardware design issue, you can not restart this demo/example by press the Reset Button(SW3):
The I2S0_RXD0 signal is connected to PTA2 of i.MX 7ULP on EVK Board. This pin is also used as BOO_CFG2 pin 
when the i.MX SoC reboot. The I2S0_RXD0 signal is driven by on-board WM8960 Codec IC, when user press Reset
Button. This may cause M4 Core enter Boot ROM's "Infinit-Loop" debug mode and only re-powerup the board can
let the M4 core exit such debug mode. 

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
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example

Running the demo
================
When the demo runs successfully, you can hear the tone and the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~
 SAI functional interrupt example started!



 SAI functional interrupt example finished!

 ~~~~~~~~~~~~~~~~~~~
