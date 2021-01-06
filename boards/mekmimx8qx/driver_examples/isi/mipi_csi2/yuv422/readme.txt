Overview
========
This example shows how to use ISI to receive camera frame through MIPI CSI2.

In this example, the camera input frame is YUV422 format and ISI output frame
is RGB656 format. The output frame is shown in the screen.

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
- MIMX8QX MEK board
- J-Link Debug Probe
- 12V power supply
- OV5640 camera adapter board
- OV5640 camera
- MAX9286 IMX8 APPS board
- MAXCAM10635EVKIT
- MX8_DSI_OLED1 board
- Personal Computer

Another option is using monitor but not OLED panel, in this case MX8_DSI_OLED1 board
is not required, LVDS or MIPI_DSI could be used. To use LVDS, these are required:
- X-IMX-LVDS-HDMI convert board
- Monitor supports HDMI input
To use MIPI_DSI, these are required:
- X-IMX-MIPI-HDMI convert board
- Monitor supports HDMI input

The MAX9286+OV10635 is supported, to use this, MAX9286 IMX8 DEMO board and MAXCAM10635EVKIT
are used.

Board settings
==============
Connect OV5640 camera to camera adapter board, connect J2 and camera adapter board.
If use MX8_DSI_OLED1, connect J1 and MX8_DSI_OLED1 board.
If use monitor to display through MIPI DSI, connect J1 and X-IMX-MIPI-HDMI board, and connect
the X-IMX-MIPI-HDMI convert board with the monitor.
If use monitor to display through LVDS, connect J1 and X-IMX-LVDS-HDMI board, and connect
the X-IMX-LVDS-HDMI convert board with the monitor.
If use MAX9286+OV10635, connect MAX9286 IMX8 DEMO board J9
and MAXCAM10635EVKIT, make sure J15 on MAX9286 IMX8 DEMO board is shorten. Then connect
MAX9286 IMX8 DEMO board to CPU board J2 use X-IMX-VAL-SAS cable.

Prepare the Demo
================
1.  Connect 12V power supply and J-Link Debug Probe to the board, switch SW3 to power on the board.
2.  Connect a micro USB cable between the host PC and the J11 USB port on the cpu board.
3.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4.  Download the program to the target board.
5.  Launch the debugger in your IDE to begin running the example.

If use monitor to display through MIPI DSI, change
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 0
    to
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 1
    in isi_config.h.

If use monitor to display through LVDS, change
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 0
    to
    #define APP_DISPLAY_EXTERNAL_CONVERTOR 1
    and change
    #define DPU_EXAMPLE_DI DPU_DI_MIPI
    to
    #define DPU_EXAMPLE_DI DPU_DI_LVDS
    in isi_config.h.

If use MAX9286+OV10635, change
    #define CAMERA_DEVICE CAMERA_DEVICE_OV5640
    to
    #define CAMERA_DEVICE CAMERA_DEVICE_MAX9286
    in isi_config.h.

Running the demo
================
When the example runs successfully, camera input frame in the screen.

NOTE: Before load and run the project, press SW3 until D3 is off, then press
SW3 until D3 is on. This perform a clean power on.
