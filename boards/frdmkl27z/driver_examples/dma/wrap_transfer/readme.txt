Overview
========
The DMA wrap transfer example is a simple demonstration program that uses the SDK software.
It excuates wrap transfer from source buffer to destination buffer using the SDK EDMA drivers.
The purpose of this example is to show how to use the wrap feature of EDMA and to provide a simple example for
debugging and further development.
                +--------------------------------------------------------------+
                v                                                              |
+-------+     +--------------------+  source address reach modulo boundary   +---------------------+
| start | --> | channel 0 transfer | --------------------------------------> | source address wrap |
+-------+     +--------------------+                                         +---------------------+
                |
                | finsihed
                v
              +--------------------+
              |  example complete  |
              +--------------------+

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini USB cable
- FRDM-KL27Z board
- Personal Computer

Board settings
==============
The DMA memroy to memory demo does not call for any special hardware configurations.

Prepare the Demo
================
1. Connect a mini USB cable between the PC host and the OpenSDA USB on the board.
2. Open a serial terminal on PC for OpenSDA serial device with these settings:
   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running
   the demo.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~
DMA wrap transfer example begin.



Destination Buffer:

0	0	0	0	0	0	0	0	



DMA wrap transfer example finish.



Destination Buffer:

1	2	3	4	1	2	3	4	
~~~~~~~~~~~~~~~~~~~~~


