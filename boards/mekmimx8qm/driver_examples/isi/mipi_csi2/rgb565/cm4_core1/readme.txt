Overview
========
This example shows how to use ISI to receive camera frame through MIPI CSI2.

In this example, the camera input frame and ISI output frame are both RGB656
format. The output frame is shown in the screen.

NOTE:
This example must run continously to get the right result, breaking during debug
will results to display tearing. Because the ISI driver maintains IP state through
ISR, if the core is halted, then driver state does not match the IP state. When
exiting debug, the core might be halted for a short while, so the tearing may
happen when exiting debug.

If the camera and LCD panel resolutions are not the same, then only part of the
camera frame will be shown.

Toolchain supported
===================
- GCC ARM Embedded  9.3.1

Hardware requirements
=====================
- Micro USB cable
- i.MX8QM MEK CPU Board
- J-Link Debug Probe
- 12V power supply
- MX8_DSI_OLED1 board
- OV5640 camera adapter board
- OV5640 camera
- Personal Computer

Another option is using monitor but not OLED panel, in this case MX8_DSI_OLED1 board
is not required, LVDS or MIPI_DSI could be used. To use LVDS, these are required:
- X-IMX-LVDS-HDMI convert board
- Monitor supports HDMI input
To use MIPI_DSI, these are required:
- X-IMX-MIPI-HDMI convert board
- Monitor supports HDMI input

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board.
2.  Use X-IMX-VAL-SAS cable to connect J9 and MX8_DSI_OLED1 board.
3.  Connect OV5640 camera to camera adapter board.
4.  Use X-IMX-VAL-SAS cable to connect J10 port and camera adapter board.
5.  Connect a USB cable between the host PC and the Debug port on the board (Refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for debug port information).
6.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
7.  Download the program to the target board (Please refer "Getting Started with MCUXpresso SDK for i.MX 8QuadMax.pdf" for how to run different targets).
8.  Launch the debugger in your IDE to begin running the example.

If use monitor to display through MIPI_DSI, change step 2 to:
    Use X-IMX-VAL-SAS cable to connect J9 and X-IMX-MIPI-HDMI board, and connect
    the X-IMX-MIPI-HDMI convert board with the monitor. Then change
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 0
    to
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 1
    in isi_config.h.

If use monitor to display through LVDS, change step 2 to:
    Use X-IMX-VAL-SAS cable to connect J7 and X-IMX-LVDS-HDMI board, and connect
    the X-IMX-LVDS-HDMI convert board with the monitor. Then change
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 0
    to
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 1
    and change
    #define DPU_EXAMPLE_DI DPU_DI_MIPI
    to
    #define DPU_EXAMPLE_DI DPU_DI_LVDS
    in isi_config.h.

Running the demo
================
When the example runs successfully, camera input frame in the screen.

NOTE: Before load and run the project, press SW1 until D3/D5 are off, then press
SW1 until D3/D5 are on. This perform a whole reset.
