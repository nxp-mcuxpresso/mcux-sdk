## Overview
-----------------------------------------------------------------------------------------
The LED Blinky demo application provides a sanity check for the new SDK build environments 
and board bring up. The LED Blinky demo uses the systick interrupt to realize the function 
of timing delay. The demo takes turns to shine the LED. The purpose of this demo is to 
provide a simple project for debugging and further development.

## Functional Description
-----------------------------------------------------------------------------------------
The LED Blinky demo mainly is to bring up the new SDK build environments on the board.
This demo will initialize the pin configuration, then configure System Tick to generate 
1ms interrupt. When 1000 interrupts occur(1s), the pin output of LED is toggled. We can 
see that LED is blinking on the board.

## Toolchain Supported
---------------------
- IAR embedded Workbench 8.50.5
- Keil MDK 5.31
- GCC ARM Embedded  9.2.1
- MCUXpresso 11.2.0

## Hardware Requirements
------------------------
- Mini/micro USB cable
- LPCXpresso824MAX board
- Personal Computer

## Board Settings
------------------------
Connect SJ9: 2-3

## Run the Demo
------------------------
1. Connect a micro USB cable between the PC host and the CMSIS DAP port(J3 on the board).

2. Choose an IDE, building the project and download the program to the target board.
   More information about how to compile and program the project can refer to the 

   [Getting Started with MCUXpresso SDK](../../../../docs/Getting Started with MCUXpresso SDK.pdf).

3. Launch the debugger in your IDE to begin running the demo.

## Expected Result
------------------------
When the demo runs successfully, you will find the LED is blinking.

