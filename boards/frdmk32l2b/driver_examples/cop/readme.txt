Overview
========
The COP Example project is to demonstrate usage of the KSDK cop driver.
In this example, after 10 times of refreshing, a timeout reset is generated.
Please notice that because COP control registers are write-once only, so the 
COP_Init function and the COP_Disable function can be called only once after reset.
In SystemInit() function which is called in startup code, there is an operation to 
disable the watchdog if macro DISABLE_WDOG is defined as 0, and by default if the 
DISABLE_WDOG is not defined, the DISABLE_WDOG is defined as 1. So this example has 
a special project setting that defines the DISABLE_WDOG macro to 0 so the startup 
code will skip the disable COP WDOG operation.


Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L2B board
- Personal Computer

Board settings
==============
This example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the example runs successfully, you can see the similar information from the terminal as below.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
COP example start!
COP refresh 1 time
COP refresh 2 time
COP refresh 3 time
COP refresh 4 time
COP refresh 5 time
COP refresh 6 time
COP refresh 7 time
COP refresh 8 time
COP refresh 9 time
COP refresh 10 time
COP will timeout and chip will be reset
Reset due to COP timeout
COP example ends!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
