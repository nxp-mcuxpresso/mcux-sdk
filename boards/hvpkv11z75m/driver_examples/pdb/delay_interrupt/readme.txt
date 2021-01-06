Overview
========

The pdb_delay_interrupt example show how to use the PDB as a general programmable interrupt timer.

The PDB is triggered by software, and other external triggers are generated from PDB in this project,
so that user can see just a general counter is working with interrupt.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/Micro USB cable
- HVP-KV11Z75M board
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PDB Delay Interrupt Example.

Type any key into terminal to trigger the PDB counter ...
PDB Delay Interrupt Counter: 1

Type any key into terminal to trigger the PDB counter ...
PDB Delay Interrupt Counter: 2

Type any key into terminal to trigger the PDB counter ...
PDB Delay Interrupt Counter: 3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
