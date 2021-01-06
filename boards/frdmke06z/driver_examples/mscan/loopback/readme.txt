Overview
========
The mscan_loopback_functional example shows how to use the loopback test mode to debug your CAN Bus design:

To demonstrates this example, only one board is needed. The example will configure one MSCAN Message Tx
buffer and Rx buffer with same ID.
After that, the example will send a CAN Message from the Tx Buffer to the Rx Buffer
throuth internal loopback interconnect and print out the Message payload to terminal.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- FRDM-KE06Z board
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
==MSCAN loopback functional example -- Start.==

Send message!
tx word0 = 0x44332211
tx word1 = 0x88776655

Received message!
rx word0 = 0x44332211
rx word1 = 0x88776655

==MSCAN loopback functional example -- Finish.==
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
