Overview
========
The tsi_v4_normal example shows how to use TSI_V4 driver in normal modes:

In this example , we make use of the available electrodes on board to show driver usage.
1. Firstly, we get the non-touch calibration results as baseline electrode counter;
2. Then, we start the Software-Trigger scan using polling method and interrupt method;
3. Then, we start the Hardware-Trigger scan using interrupt method.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L2A4S board
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.

Running the demo
================
1. Open serial terminal utility with specific COM number when board is powered on
2. Download the code to device and run it
3. When you touch the specific pad, one LED will toggle to indicate that touch event happened.

When the example runs successfully, you can see the similar information from the terminal as below.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TSI_V4 Normal_mode Example Start!
Calibrated counters for channel 0 is: 757
Calibrated counters for channel 1 is: 15
Calibrated counters for channel 2 is: 65535
Calibrated counters for channel 3 is: 65535
Calibrated counters for channel 4 is: 130
Calibrated counters for channel 5 is: 65535
Calibrated counters for channel 6 is: 804
Calibrated counters for channel 7 is: 667
Calibrated counters for channel 8 is: 607
Calibrated counters for channel 9 is: 1584
Calibrated counters for channel 10 is: 1588
Calibrated counters for channel 11 is: 649
Calibrated counters for channel 12 is: 629
Calibrated counters for channel 13 is: 652
Calibrated counters for channel 14 is: 65535
Calibrated counters for channel 15 is: 747

NOW, comes to the software trigger scan using polling method!
Channel 2 Normal mode counter is: 1555 
Channel 3 Normal mode counter is: 1590 

NOW, comes to the software trigger scan using interrupt method!
Channel 2 Normal mode counter is: 1555 
Channel 3 Normal mode counter is: 1591 

NOW, comes to the hardware trigger scan method!
After running, touch pad E1 each time, you will see LED toggles.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
