Overview
========
The esai_edma_transfer example shows how to use esai driver with edma:

In this example, one esai instance playbacks the audio data recorded by the same esai instance using edma.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK CPU Board
- MCIMX8-8X-BB
- X-IMX-AUD-IO Audio IO CARD
- J-Link Debug Probe
- 12V power supply
- Personal Computer
- 2 RCA to 3.5 male audio cable
- 2 RCA to 3.5 female audio cable
- Headpone
- AUX cable

Board settings
==============
Insert the Audio IO Card into Audio Slot1(J20) 
Connect headphone to a A/V RCA to 3.5mm cable, connect AUX cable to another A/V RCA to 3.5mm cable.
Connect headphone RCA cable to Audio IO Card AOUT 0, AOUT 1. Connect AUX RCA cable to Audio IO Card AUX IN1, AUX IN2.
Connect AUX cable to your PC or mobile phone.

#### Please note this application can't support running with Linux BSP! ####
This example aims to show the basic usage of the IP's function, some of the used Pads/Resources are also used by Cortex-A core.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
5.  Launch the debugger in your IDE to begin running the example.
6.  Play music in your PC or mobile phone.

Running the demo
================
You can hear the audio played in your PC or headphone.
ESAI EDMA example started!
ESAI EDMA example succeed!
~~~~~~~~~~~~~~~~~~~~~
