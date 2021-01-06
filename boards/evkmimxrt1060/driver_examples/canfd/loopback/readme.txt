Overview
========
The flexcan_loopback_functional example shows how to use the loopback test mode to debug your CAN Bus design:

To demonstrates this example, only one board is needed. The example will config one FlexCAN Message
Buffer to Rx Message Buffer and the other FlexCAN Message Buffer to Tx Message Buffer with same ID.
After that, the example will send a CAN Message from the Tx Message Buffer to the Rx Message Buffer
throuth internal loopback interconnect and print out the Message payload to terminal.

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
1. Connect a USB cable between the PC host and the OpenSDA USB on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the example.

Running the demo
================
Consider special errata 005829 feature, the 1st valid MB should be used as reserved one.
The TX MB number will change from 8 to 9, while RX MB number will change from 9 to 10
When the example runs successfully, following information can be seen on the OpenSDA terminal:

~~~~~~~~~~~~~~~~~~~~~

==FlexCAN loopback functional example -- Start.==

Send message from MB9 to MB10
tx word0 = 0x0
tx word1 = 0x1
tx word2 = 0x2
tx word3 = 0x3
tx word4 = 0x4
tx word5 = 0x5
tx word6 = 0x6
tx word7 = 0x7
tx word8 = 0x8
tx word9 = 0x9
tx word10 = 0xa
tx word11 = 0xb
tx word12 = 0xc
tx word13 = 0xd
tx word14 = 0xe
tx word15 = 0xf

Received message from MB10
rx word0 = 0x0
rx word1 = 0x1
rx word2 = 0x2
rx word3 = 0x3
rx word4 = 0x4
rx word5 = 0x5
rx word6 = 0x6
rx word7 = 0x7
rx word8 = 0x8
rx word9 = 0x9
rx word10 = 0xa
rx word11 = 0xb
rx word12 = 0xc
rx word13 = 0xd
rx word14 = 0xe
rx word15 = 0xf

==FlexCAN loopback functional example -- Finish.==
~~~~~~~~~~~~~~~~~~~~~
