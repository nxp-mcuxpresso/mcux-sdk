Overview
========
The csi_fragment_gray project shows how to use CSI driver fragment mode functions.
In this example, the camera input format is YUV422, the CSI driver extracts the
Y element of a specific window (gray image). To show gray image, ELCDIF LUT is used.
If this example runs successfully, you will see a gray image window in the middle
of the LCD panel. The image is updated each time input any value from debug console.

Please note that only one frame buffer is used in this example, so there might be
screen tearing.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1
- MCUXpresso  11.3.0

Hardware requirements
=====================
- Mini/micro USB cable
- EVKB-IMXRT1050 board
- Personal Computer
- RK043FN02H-CT LCD board
- MT9M114 module
This example supports OV7725 too, if OV7725 is used, then MT9M114 is not necessary.

Board settings
==============
1. Connect the RK043FN02H-CT board.
2. Connect the MT9M114 or OV7725 camera module.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the demo.

Note: If OV7725 is used, change the macro APP_CAMERA_TYPE to APP_CAMERA_OV7725 in
csi_rgb565.c.

Running the demo
================
When the demo runs successfully, the camera received pictures are shown in the LCD.
