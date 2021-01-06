## Overview
-----------
The led_output example shows how to use GPIO with interrupts and make the led shine.The output can be observed with an oscilloscope. 

When the GPIO feature is enabled, initialize the port and the pin connected to LED and SW2, configure the port mask with MASK register
and MPIN register, which can be used to monitor the every GPIO's status. Red LED will blink when users hold the SW2 button.

## Functional Description
-------------------------
In this example, The GPIO will output the status into serial terminal. 

When start running this example, main routine will initialize clock, pin mux configuration, and configure the GPIO module to make it work in interrupt way. Red LED will blink when users hold the USER button.

## Toolchain Supported
---------------------
- IAR embedded Workbench 8.50.5
- Keil MDK 5.31
- GCC ARM Embedded  9.2.1
- MCUXpresso 11.2.0

## Hardware Requirements
------------------------
- Micro USB cable
- LPCXpresso802 board
- Personal Computer

## Board Settings
------------------------

## Run the Project
------------------------
Run this example by performing the following steps:

1. Connect a micro USB cable between the PC host and the CMSIS DAP port(CN1 on the 
   LPCXpresso802 board) for receiving debug information.

2. Open a serial terminal in PC(for example PUTTY) with the following settings:
   - 9600 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control

3. Compile and download the program to the target board.
   More information about how to compile and program the project can refer to 

   [Getting Started with MCUXpresso SDK](../../../../../docs/Getting Started with MCUXpresso SDK.pdf).

4. Start the slave board on another board first, then launch the debugger in your IDE to
   begin running this project.

5. Monitor the information on the debug console.

## Expected Result
------------------------
Users are prompted to press the USER key, and board will blink the LED.
