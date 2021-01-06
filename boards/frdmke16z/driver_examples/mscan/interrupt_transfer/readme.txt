Overview
========
The mscan_interrupt example shows how to use MSCAN driver in none-blocking interrupt way:

In this example, 2 boards are connected through CAN bus. Endpoint A(board A) send a CAN Message to
Endpoint B(board B) when user press space key in terminal. Endpoint B receive the message, print
the message content to terminal and echo back the message. Endpoint A will increase the received
message and waiting for the next transmission of the user initiated.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cables
- FRDM-KE16Z board
- Personal Computer

Board settings
==============
The example requires connecting between CAN pins of two FRDM-KE16Z boards.
The connection should be set as follows:

Between boards:
- J12-1 node A, J12-1 node B
- J12-2 node A, J12-2 node B
- J12-3 node A, J12-3 node B

Prepare the Demo
================
1. Connect a micro USB cable between the PC host and the OpenSDA USB on the board.
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
After connecting the two boards, these instructions display on each terminal window.
One board must be chosen as node A and the other board as node B. (Note: Node B should start first)
Data is sent continuously between the node A and the node B.

~~~~~~~~~~~~~~~~~~~~~
This message displays on the node A terminal:

********* MSCAN Interrupt EXAMPLE *********
    Message format: Standard (11 bit id)
    Interrupt Mode: Enabled
    Operation Mode: TX and RX --> Normal
*********************************************

Please select local node as A or B:
Note: Node B should start first.
Node:A
Press any key to trigger one-shot transmission

Rx MB ID: 0x123, Rx MB data: 0x0, Time stamp: 5759
Press any key to trigger the next transmission!

Rx MB ID: 0x123, Rx MB data: 0x1, Time stamp: 20363
Press any key to trigger the next transmission!

This message displays on the node B terminal:

********* MSCAN Interrupt EXAMPLE *********
    Message format: Standard (11 bit id)
    Interrupt Mode: Enabled
    Operation Mode: TX and RX --> Normal
*********************************************

Please select local node as A or B:
Note: Node B should start first.
Node:B
Start to Wait data from Node A

Rx MB ID: 0x321, Rx MB data: 0x0, Time stamp: 3635
Wait Node A to trigger the next transmission!

Rx MB ID: 0x321, Rx MB data: , Time stamp: 8877
Wait Node A to trigger the next transmission!
~~~~~~~~~~~~~~~~~~~~~
