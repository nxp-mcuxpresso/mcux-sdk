Overview
========
The lpuart_hardware_flow_control Example project is to demonstrate usage of the hardware flow control function.
This example will send data to itself(loopback), and hardware flow control will be enabled in the example.
The CTS(clear-to-send) pin is for transmiter to check if receiver is ready, if the CTS pin is assert, transmiter start
to send data. The RTS(request-to-send) is a pin for receiver to inform the transmiter if receiver is ready to receive
data. So, please connect RTS to CTS pin directly.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-K28FA REV A board
- Personal Computer

Board settings
==============
LPUART hardware flow control on one board.
The LPUART will send data to itself(loopback), and hardware flow control function will be 
enabled on this example. So, please makesure the correct connection for example.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pin Name     Board Location    connect to      Pin Name    Board Location
LPUART_TX    J27 Pin 20        ----------      LPUART_RX    J27 pin 19
LPUART_CTS   J27 Pin 22        ----------      LPUART_RTS   J27 Pin 21

Tips: For FRDM-K28FA REV B board, please connect the pins like REV A, but the pin location on the 
      REV B board may different with REV A board.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
This is LPUART hardware flow control example on one board.
This example will send data to itself and will use hardware flow control to avoid the overflow.
Please make sure you make the correct line connection. Basically, the connection is: 
      LPUART_TX    --     LPUART_RX    
      LPUART_RTS   --     LPUART_CTS   
Data matched! Transfer successfully.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
