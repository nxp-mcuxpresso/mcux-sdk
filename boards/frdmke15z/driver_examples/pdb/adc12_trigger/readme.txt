Overview
========

The pdb_adc12_trigger example shows how to use the PDB to generate a ADC trigger.

Based on the basic counter, to use the ADC trigger, just to enable the ADC trigger's "milestone" and set the user-defined value for it.
After the PDB counter is triggered to start, when the counter pass the "milestone", the ADC's Pre-Trigger would be generated and sent
to the ADC12 module.

In this example, the ADC12 is configured with hardware trigger and conversion complete interrupt enabled.
Once it gets the trigger from the PDB, the conversion goes, then the ISR would be executed.


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
No special is needed.

Prepare the Demo
================
1.  Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================

When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

PDB ADC12 Pre-Trigger Example.

Type any key into terminal to trigger the PDB and then trigger the ADC12's conversion ...

PDB Interrupt Counter: 1
ADC12 Conversion Interrupt Counter: 1

PDB Interrupt Counter: 2
ADC12 Conversion Interrupt Counter: 2

PDB Interrupt Counter: 3
ADC12 Conversion Interrupt Counter: 3

PDB Interrupt Counter: 4
ADC12 Conversion Interrupt Counter: 4
...
