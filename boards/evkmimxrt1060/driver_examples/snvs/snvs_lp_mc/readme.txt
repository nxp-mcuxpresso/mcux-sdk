Overview
========
The SNVS LP MC project shows how to use the Monotonic Counter (MC) based on
SDK SNVS LP driver. In this example, the MC value is increased and checked
several times.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1060 board
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
The log below shows the output of snvs example in the terminal window, the count
value might be different
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SNVS LP MC example:
Current Monotonic Counter value is 0x000000000000007E
Current Monotonic Counter value is 0x000000000000007F
Current Monotonic Counter value is 0x0000000000000080
Current Monotonic Counter value is 0x0000000000000081
Current Monotonic Counter value is 0x0000000000000082
SNVS LP MC example finished successfully

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
