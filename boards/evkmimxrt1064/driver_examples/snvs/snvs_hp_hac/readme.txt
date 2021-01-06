Overview
========
The SNVS HP HAC project shows how to use the High Assurance Counter (HAC) based on
SDK SNVS HP driver. In this example,
   1. The HAC is enabled and set a initial value.
   2. Software fatal security violation is triggered, and the SSM switches to soft fail mode.
   3. In soft fail mode, software stops the HAC counter, and clear the HAC to make SSM
      switch to hard fail mode. 
   4. The system resets when enters hard fail mode.

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
Follow the instruction from the terminal window to run the demo. This demo resets
the system at last.
