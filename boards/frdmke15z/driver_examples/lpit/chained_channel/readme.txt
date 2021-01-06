Overview
========
The LPIT chained_channel project is a simple example of the SDK LPIT driver. It sets up the LPIT 
hardware block to trigger a periodic interrupt after every 1 second in the channel No.0, the channel 
No.1 chained with channel No.0, if LPIT contain more than two channels, the channel No.2 chained with 
channel No.1....the channel No.N chained with Channel No.N-1. When the LPIT interrupt is triggered
a message a printed on the serial terminal.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Micro USB cable
- FRDM-KE15Z board
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
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, you will see the similar information from the terminal shown as below.
Detail prints for each channel depends on by the total numbs of chained channels and the order of 
interrupt flag handler process for each channel. 

~~~~~~~~~~~~~~~~~~~~~
Starting channel No.0 ...
Starting channel No.1 ...
Starting channel No.2 ...
Starting channel No.3 ...

 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !
 Channel No.0 interrupt is occurred !

 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !
......................................
 Channel No.1 Chained with Channel No.0 interrupt is occurred !

 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.2 Chained with Channel No.1 interrupt is occurred !
......................................
......................................
 Channel No.3 Chained with Channel No.2 interrupt is occurred !
 .....................................
 .....................................
 .....................................

~~~~~~~~~~~~~~~~~~~~~
