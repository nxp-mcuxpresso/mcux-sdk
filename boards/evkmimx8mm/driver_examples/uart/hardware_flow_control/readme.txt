Overview
========
The uart_hardware_flow_control example project demonstrates usage of the hardware
flow control function. This example sends data to itself(loopback), and hardware flow
control is enabled. The CTS(clear-to-send) pin is for transmiter to check if receiver
is ready, if the CTS pin asserts, transmiter start to send data. The RTS(request-to-send)
is a pin for receiver to inform the transmiter if receiver is ready to receive data.
So, please connect RTS to CTS pin directly.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8MM6-EVK board
- J-Link Debug Probe
- 12V power supply
- Personal Computer

Board settings
==============
UART hardware flow control on one board.
The UART sends data to itself(loopback), and hardware flow control function is 
enabled on this example. So please make sure the correct connection for example.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pin Name    Board Location    connect to     Pin Name    Board Location
UART_TX     J1003 Pin 8       ----------     UART_RX     J1003 pin 10
UART_CTS    J1003 Pin 11      ----------     UART_RTS    J1003 Pin 7
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW101 to power on the board
2.  Connect a USB cable between the host PC and the J901 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This is UART hardware flow control example on one board.
This example will send data to itself and will use hardware flow control to avoid the overflow.
Please make sure you make the correct line connection. Basically, the connection is:
      UART_TX    --     UART_RX
      UART_RTS   --     UART_CTS
Data matched! Transfer successfully.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
