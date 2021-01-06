Overview
========
The sema4 uboot example shows how to use SEMA4 driver to lock and unlock a sema gate,
the notification IRQ is also demonstrated in this example.
This example should work together with uboot. This example runs on Cortex-M core,
the uboot runs on the Cortex-A core.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8MM6-EVK  board
- J-Link Debug Probe
- SD card with uboot
- 12V power supply
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Prepare an SD card with the prebuilt U-Boot image. Then, insert the SD card to the target board.
2.  Connect a USB cable between the host PC and the J901 USB port on the target board.
3.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW101 to power on the board
4.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
Follow the output log, lock and unlock the sema4 gate in uboot. The whole log:
~~~~~~~~~~~~~~~~~~~
SEMA4 uboot example start
Lock sema4 gate in uboot using:
 > mw.b 0x30ac0000 1 1
Unlock sema4 gate in uboot using:
 > mw.b 0x30ac0000 0 1
SEMA4 uboot example success
~~~~~~~~~~~~~~~~~~~
