Overview
========
The lptmr_trigger_lpit project is a simple example of the SDK LPIT,LPTMR and TRGMUX driver which shows how to 
use the LPTMR and TRGMUX to generate a LPIT trigger. It sets up the LPTMR hardware block to generate the triggerevery 0.5 second,
and the LPIT counter will load on the first trigger rising edge and then decrement down to zero on each trigger rising edge.
A message would be printed on the serial terminal.


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
1.  Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2.  Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
These instructions are displayed/shown on the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~
Example Starts!
LPIT interrupt No.1 
LPIT interrupt No.2 
LPIT interrupt No.3 
LPIT interrupt No.4 
LPIT interrupt No.5 
LPIT interrupt No.6 
LPIT interrupt No.7 
LPIT interrupt No.8 
LPIT interrupt No.9 
LPIT interrupt No.10 
LPIT interrupt No.11 
LPIT interrupt No.12 
LPIT interrupt No.13 
......
~~~~~~~~~~~~~~~~~~~~~~~
