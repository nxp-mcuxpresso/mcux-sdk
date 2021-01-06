Overview
========

The enet_rxtx_ptp1588_transfer example shows the way to use ENET driver to  
 receive and transmit frame in the 1588 feature required cases.

1. This example shows how to initialize the ENET.
2. How to get the time stamp of the PTP 1588 timer.
3. How to use Get the ENET transmit and receive frame time stamp.

The example transmits 20 number PTP event frame, shows the timestamp of the transmitted frame.
The length, source MAC address and destination MAC address of the received frame will be print. 
The time stamp of the received timestamp will be print when the PTP message frame is received(the outside loopback cable can be used to see the right rx time-stamping log since we send the ptp message). 

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- LPCXpresso54628 board
- Personal Computer
- Loopback network cable RJ45 standard

Board settings
==============
For LPCXpresso54628 V2.0:JP11 and JP12 1-2 on. 

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Insert loopback network cable to Ethernet RJ45 port.
4.  Download the program to the target board.
5.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Make loopback network cable:
      568B standard 	 Unknowed standard
J1    orange+white       green+white
J2    orange             green
J3    green+white        orange+white
J4    blue               brown+white
J5    blue+white         brown
J6    green              orange
J7	  brown+white        blue
J8    brown              blue+white

Connect J1 => J3, J2 => J6, J4 => J7, J5 => J8. 10/100M transfer only requires J1, J2, J3, J6, and 1G transfer requires all 8 pins.
Check your net cable color order and refer to 568B standard or the other standard. If your cable's color order is not showed in the list,
please connect J1~J8 based on your situation.

Running the demo
================
The log below shows example output of the example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ENET example start.
 Get the 1-th time xx second xx nanosecond
 Get the 2-th time xx second xx nanosecond
 Get the 3-th time xx second xx nanosecond
 ......

 Get the 10-th time xx second xx nanosecond


Transmission start now!
The 1 frame transmitted success!
 the timestamp is xx second xx nanosecond
The 2 frame transmitted success! 
 the timestamp is xx second, xx nanosecond
 
Note: the xx second and xx nanosecond should be the number with solid increment.

when a 1000 length normal messsage frame is received, the log would be added like:
A frame received. the length xxx 
when a 1000 length ptp event message frame is received, the log would be added to the terminal like:
A frame received. the length xxx 
  the timestamp is xx second, xx nanosecond

...

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
