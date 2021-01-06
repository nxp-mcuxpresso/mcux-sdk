Overview
========

The LPCMP interrupt Example shows how to use interrupt with LPCMP driver.

In this example, user should indicate an input channel to capture a voltage signal (can be controlled by user) as the 
LPCMP's positive channel input. On the negative side, the internal 6-bit DAC is used to generate the fixed voltage about
half value of reference voltage.

When running the project, change the input voltage of user-defined channel, then the comparator's output would change
between logic one and zero when the user-defined channel's voltage crosses the internal DAC's value. The change of
comparator's output would generate the falling and rising edge events with their interrupts enabled. When any LPCMP 
interrupt happens, the LPCMP's ISR would turn on the LED light if detecting the output's rising edge, or turn off it when
detecting the output's falling edge.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K32L3A6 board
- Personal Computer

Board settings
==============
This example project uses LPCMP instance 0(M4) or instance 1(M0) to compare the voltage signal input from channel 2(PTC9)
with the voltage signal(half of VDDIO) output by LPCMP's internal DAC and output different result.
LED1 will turn ON/OFF corresponding to different result. So the voltage signal input from PTC9
should be changed to observe the dynamical LED state.
- Input signal to J2-18

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
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
The log below shows in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LPCMP Interrupt Example.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
