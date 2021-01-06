Overview
========

The dac_buffer_interrupt example shows how to use DAC buffer with interrupts.

When the DAC's buffer feature is enabled, user can benefit from the automation of updating DAC output by hardware/
software trigger. As we know, the DAC converter outputs the value of item pointed by current read pointer. Once the 
buffer is triggered by software or hardware, the buffer's read pointer would move automatically as the work mode is set,
like normal (cycle) mode, swing mode, one-time-scan mode or FIFO mode.

In this example, it captures the user's type-in operation from terminal and does the software trigger to the buffer.
The terminal would also display the log that shows the current buffer pointer's position with buffer events.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-KV31F board
- Personal Computer

Board settings
==============
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
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DAC buffer interrupt Example.

DAC Buffer Information
      Buffer index max  : 15
      Buffer watermark  : 14
Press any key in terminal to trigger the buffer ...
Buffer Index  0: ReadPointerTopPositionEvent
Buffer Index  1:
Buffer Index  2:
Buffer Index  3:
Buffer Index  4:
Buffer Index  5:
Buffer Index  6:
Buffer Index  7:
Buffer Index  8:
Buffer Index  9:
Buffer Index 10:
Buffer Index 11:
Buffer Index 12:
Buffer Index 13:
Buffer Index 14: WatermarkEvent
Buffer Index 15: ReadPointerBottomPositionEvent

Buffer Index  0: ReadPointerTopPositionEvent
Buffer Index  1:
Buffer Index  2:
Buffer Index  3:
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

User can take a look at how the pointer is moved by triggered, then user can also measure the DAC output
pin to check responding voltage.
