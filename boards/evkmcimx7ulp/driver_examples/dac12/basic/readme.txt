Overview
========

The dac12_basic example shows how to use DAC12 module simply as the general DAC12 converter.

When the DAC12's fifo feature is not enabled, Any write to the DATA register will replace the
data in the buffer and push data to analog conversion without trigger support.
In this example, it gets the value from terminal,
outputs the DAC12 output voltage through DAC12 output pin.

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
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1. Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2. Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3. Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4. Download the program to the target board.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DAC basic Example.

Please input a value (0 - 4095) to output with DAC: 
Input value is 4095
DAC out: 4095
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Then user can measure the DAC0 output pin(J11-8) to check responding voltage.
