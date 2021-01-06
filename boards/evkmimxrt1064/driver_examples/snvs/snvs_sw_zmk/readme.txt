Overview
========
The SNVS SW ZMK project shows how to provision the zeroizable master key (ZMK)
by software based on SDK SNVS driver. In this example, ZMK key value is set and
ECC is enabled. When change the ZMK key value, violation detected and ZMK key
is zeroized.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1064 board
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
The log below shows the output of snvs example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SNVS software Zeroizable Master Key example:
Set the ZMK key value
Enable the ZMK
Enable the ZMK ECC
Set new ZMK key to generate ZMK violation
ZMK violation detected, ZMK key is zeroized

SNVS software ZMK example finished successfully
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
