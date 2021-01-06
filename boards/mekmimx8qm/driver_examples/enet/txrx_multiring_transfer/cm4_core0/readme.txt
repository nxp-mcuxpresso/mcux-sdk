Overview
========

The enet_txrx_multiring_transfer example shows the way to use ENET driver to  
 receive and transmit avb frame in the avb feature supported multi-ring platforms.
 this example is only supported in multi-ring platform.

1. This example shows how to initialize the ENET MAC.
2. How to use ENET MAC to transmit frames in avb supported 
multiple-ring platforms.

The example transmits 30 number frames. For simple demo, we create frames with some special definition.
1. Build transmission frames with broadcast mac address.
2. Build different frames for each ring: 10 normal ethernet frame, 10 similar IEC 61883-6 type frames,
10 similar IEC 61883-8 type frames and the two IEC 1722 avb frames are set with different vlan priority .
 
Notice, To simply show how to use three different rings in rx/tx on one board. This example set PHY local loop and you will see there will be PHY init auto-negotiation fail and this is normal. because phy can not finish
auto-negotiation when phy is in loop back mode. However, the auto-negotiation fail has no impact on this loop back example, so just forget about the failure auto-negotiation.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK CPU Board
- J-Link Debug Probe
- 12V power supply
- Loopback network cable RJ45 standard
- Network switch
- Personal Computer

Board settings
==============
J14 connected with network switch through RJ45 network cable.

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
4.  Insert loopback network cable into network switch device(support loopback frames) and connect switch to board's Ethernet RJ45 port.
5.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
6.  Launch the debugger in your IDE to begin running the example.

Make loopback network cable:
      Standard 1	     Standard 2
J1    orange+white       green+white
J2    orange             green
J3    green+white        orange+white
J4    blue               brown+white
J5    blue+white         brown
J6    green              orange
J7	  brown+white        blue
J8    brown              blue+white

Connect J1 => J3, J2 => J6, J4 => J7, J5 => J8. 10/100M transfer only requires J1, J2, J3, J6, and 1G transfer requires all 8 pins.
Check your net cable color order and refer to the sheet above. If your cable's color order is not showed in the list,
please connect J1~J8 based on your situation.

Running the demo
================
When the demo runs, the log would be seen on the debug terminal like:

ENET multi-ring txrx example start.
The 0 frame transmitted from the ring 0 !
The frame received from the ring 0, 1, 2 is 1, 0, 0 now!
The 1 frame transmitted from the ring 1 !
The frame received from the ring 0, 1, 2 is 1, 0, 1 now!
The 1 frame transmitted from the ring 2 !

......

The 10 frame transmitted from the ring 1 !
The frame received from the ring 0, 1, 2 is 10, 9, 10 now!
The 10 frame transmitted from the ring 2 !
The frame received from the ring 0, 1, 2 is 10, 10, 10 now!
30 frame transmitted succeed!
10 frame successfully received from the ring 0!
10 frame successfully received from the ring 1!
10 frame successfully received from the ring 2!


