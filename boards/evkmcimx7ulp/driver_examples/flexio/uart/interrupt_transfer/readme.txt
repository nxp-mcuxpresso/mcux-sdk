Overview
========
The flexio_uart_interrupt example shows how to use flexio uart driver in interrupt way:

In this example, a flexio simulated uart connect to PC through USB-Serial, the board will send back all characters
that PC send to the board. Note: two queued transfer in this example, so please input even number characters.

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

Board settings
==============
The example requires connecting the FLEXIO pins with the USB2COM pins
The connection should be set as follows:
- TP25 on base board, TX of USB2COM connected
- TP27 on base board, RX of USB2COM connected
- GND  on base board, Ground of USB2COM connected

#### Please note this application can't support running with Linux BSP! ####

#### Please note there's some limitation if running this application in QSPI flash in place.
If run it in QSPI flash, there's high latency when instruction cache miss. The FlexIO UART has
no FIFO so it has critical timing requirement that UART data must be read in time, otherwise
overflow may occur which causes data loss. So when running in QSPI flash, please don't
input more than 8 characters each time. ####

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
When the demo runs successfully, the log would be seen on the UART Terminal port which connected to the USB2COM like:

~~~~~~~~~~~~~~~~~~~~~
Flexio uart interrupt example
Board receives 8 characters then sends them out
Now please input:
~~~~~~~~~~~~~~~~~~~~~
