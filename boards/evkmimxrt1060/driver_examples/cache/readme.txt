Overview
========

The cache example shows how to use memory cache driver.

In this example, many memory (such as SDRAM, etc) and DMA will be used to show the example.
Those memory is both accessible for cpu and DMA. For the memory data alignment, cache driver should be 
used rightly. For cache enabled case, the cache invalidate operation should be done before cpu access the memory. The cache clean opeartion should be done after CPU verify the memory
memory and before DMA access the memory.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVK_MIMXRT1060 board
- Personal Computer

Board settings
==============
Connect pin:
No special settings are required.

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
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The log below shows the output of the example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Cache example start.

 Cache Invalidate success! 

 Cache Clean success! 
 
 Cache example end. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
