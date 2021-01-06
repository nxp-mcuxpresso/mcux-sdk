Overview
========

The pdb_dac_trigger example shows how to use the PDB to generate a DAC trigger.

Based on the basic counter, to use the DAC trigger, just to enable the DAC trigger's "milestone" and set the user-
defined value for it.
The DAC's "milestone" is called as "interval". Multiple DAC trigger intervals can be included into one PDB counter's cycle.
DAC trigger's counter would reset after the trigger is created and start counting again to the interval value.

In this example, the DAC is configured with hardware buffer enabled in normal work mode. Once it gets the trigger from 
the PDB, the buffer read pointer increases.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-KV11Z board
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
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~
PDB DAC trigger Example.

DAC Buffer Information
          Buffer index max  : 1
Type any key into terminal to trigger the DAC buffer through PDB ...

DAC Buffer Index  0: ReadPointerTopPositionEvent
DAC Buffer Index  1: ReadPointerBottomPositionEvent
.......................
~~~~~~~~~~~~~~~~~~~~~~~~~~~
