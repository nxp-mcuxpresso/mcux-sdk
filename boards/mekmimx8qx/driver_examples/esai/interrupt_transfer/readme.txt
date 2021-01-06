Overview
========
The esai_interrupt_transfer example shows how to use esai driver with interrupt:

In this example, one esai instance playbacks the audio data recorded by the same esai instance using interrupt.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MIMX8QX MEK board
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- 2 RCA to 3.5 male audio cable
- 2 RCA to 3.5 female audio cable

Board settings
==============
Base Board is needed to run this demo.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW3 to power on the board.
2.  Connect a micro USB cable between the host PC and the J11 USB port on the cpu board.
3.  Insert AUDIO extended card into AUDIO SLOT-1 on the base board.
4.  Using the RCA to 3.5 male cable to connect Line In audio slots (AUXIN1 and AUXIN2) on the audio board and a audio output device, such as an mobile phone.
5.  Using the RCA to 3.5 female cable to connect Line Out audio slots (AOUT4 and AOUT5) on the audio board and a headphone.
6.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
7.  Download the program to the target board.
8.  Launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
ESAI Interrupt example started!
~~~~~~~~~~~~~~~~~~~~~

Play the music in the audio output device, the sound can be heard in the headphone. 
After a while, the example finish with the following message

~~~~~~~~~~~~~~~~~~~~~
ESAI Interrupt example Succeed!
~~~~~~~~~~~~~~~~~~~~~
