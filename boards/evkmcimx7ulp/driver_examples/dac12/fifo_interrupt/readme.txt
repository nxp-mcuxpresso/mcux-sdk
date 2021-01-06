Overview
========

The dac12_fifo_interrupt example shows how to use DAC12 FIFO interrupt.

When the DAC12 FIFO watermark interrupt is enabled firstly, the application would enter the DAC12 ISR immediately, since remaining FIFO data is less than the watermark. Then the FIFO would be feed inside the ISR. Then the DAC12 interrupt could be restrained. Once the DAC12 FIFO is triggered in while loop, the data in FIFO is read out, then it becomes less than the watermark, so the FIFO would be feed again in DAC12 ISR. 

With this example, user can define the DAC12 output array to generate the different wave output. Also the software trigger can be called in some timer ISR so that the DAC12 would output the analog signal in indicated period. Or even use the hardware trigger to release the CPU.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- MCIMX7ULP-EVK board
- J-Link Debug Probe
- 5V power supply
- Personal Computer

Board settings
==============
No special settings are required.

#### Please note this application can't support running with Linux BSP! ####

Prepare the Demo
================
1. Connect 5V power supply and J-Link Debug Probe to the board, switch SW1 to power on the board.
2. Connect a micro USB cable between the host PC and the J6 USB port on the target board.
3. Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4. Download the program to the target board.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
When the demo runs successfully, following information can be seen on the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Press any key to trigger the DAC...
DAC next output: 0
DAC next output: 100
DAC next output: 200
DAC next output: 300
DAC next output: 400
DAC next output: 500
DAC next output: 600
DAC next output: 700
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Then user can measure the DAC0 output pin(J11-8) to check responding voltage.
