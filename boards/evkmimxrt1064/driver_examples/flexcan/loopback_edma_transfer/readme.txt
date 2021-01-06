Overview
========
The flexcan_loopback_edma example shows how to use the EDMA version transactional driver to receive
CAN Message from Rx FIFO:

To demonstrates this example, only one board is needed. The example will config one FlexCAN Message
Buffer to Tx Message Buffer and also setup Rx FIFO. After that, the example will send 4 CAN Messages
from Tx Message Buffer to Rx FIFO through internal loopback interconnect and read them out using
EDMA version FlexCAN transactional driver. The Sent and received message will be print out to terminal
at last.

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
When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~
==FlexCAN loopback edma example -- Start.==

Send Msg1 to Rx FIFO: word0 = 0x11111111, word1 = 0x11111111.

Send Msg2 to Rx FIFO: word0 = 0x22222222, word1 = 0x22222222.

Send Msg3 to Rx FIFO: word0 = 0x33333333, word1 = 0x33333333.

Send Msg4 to Rx FIFO: word0 = 0x44444444, word1 = 0x44444444.

Receive Msg1 from FIFO: word0 = 0x11111111, word1 = 0x11111111, ID Filter Hit2.

Receive Msg2 from FIFO: word0 = 0x22222222, word1 = 0x22222222, ID Filter Hit2.

Receive Msg3 from FIFO: word0 = 0x33333333, word1 = 0x33333333, ID Filter Hit2.

Receive Msg4 from FIFO: word0 = 0x44444444, word1 = 0x44444444, ID Filter Hit2.

==FlexCAN loopback EDMA example -- Finish.==
~~~~~~~~~~~~~~~~~~~~~
