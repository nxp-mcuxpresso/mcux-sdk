/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file control.c
    \brief Defines control sub-system

    This file contains a UART implementation of the control subsystem.  The
    command interpreter and streaming functions are contained in two separate
    files.  So you can easily swap those out with only minor changes here.
*/
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "sensor_fusion.h"
#include "control.h"

#ifndef F_USE_WIRELESS_UART
#define F_USE_WIRELESS_UART     0x0001	///< 0x0001 to include, 0x0000 otherwise
#endif
#ifndef F_USE_WIRED_UART
#define F_USE_WIRED_UART        0x0002	///< 0x0002 to include, 0x0000 otherwise
#endif

#define CONTROL_BAUDRATE        115200  ///< Baudrate to be used for serial communications

uart_handle_t   wired_uartHandle;
uart_handle_t   wireless_uartHandle;

// global structures
uint8_t           sUARTOutputBuffer[256];             // larger than the nominal 124 byte size for outgoing packets

// direct access to sfg here is the only place in the entire library where we cannot simply
// pass a pointer.  This is because it is needed by the UART interrupt handlers.  Since this
// only occurs here, in a subsystem which is defined to be application dependent, that is
// considered acceptable.
extern SensorFusionGlobals sfg;

// Blocking function to write a single byte to a specified UART
void myUART_WriteByte(UART_Type *base, uint8_t data)
{
    uint8_t flag = 0;
    while (!flag)
    {
        flag = base->S1 & 0x80;
    }
    UART_WriteByte(base, data);
}

// Blocking function pipes specified buffer to both output UARTS
int8_t writeControlPort(ControlSubsystem *pComm, uint8_t buffer[], uint16_t nbytes)
{
    uint16_t    i;
    for (i = 0; i < nbytes; i++)
    {
#if F_USE_WIRED_UART
        myUART_WriteByte(WIRED_UART, buffer[i]);
#endif
#if F_USE_WIRELESS_UART
        myUART_WriteByte(WIRELESS_UART, buffer[i]);
#endif
    }

    return (0);
}

#if F_USE_WIRELESS_UART
// writeWirelessPort() is called from BlueRadios_Init(), which is used to
// initialize the Bluetooth module on NXP sensor shields.  That function will
// obviously need to be replaced for alternate hardware.
int8_t writeWirelessPort(uint8_t buffer[], uint16_t nbytes)
{
    uint16_t    i;
    for (i = 0; i < nbytes; i++)
    {
        myUART_WriteByte(WIRELESS_UART, buffer[i]);
    }

    return (0);
}
// Wired and Wireless UART interrupt handlers are essentially identical.
void WIRELESS_UART_IRQHandler(void)
{
    uint8_t     data;
    status_t    sts;
    uint32_t    nbytes;				// number of bytes received
    uint32_t    flags;
    static char iCommandBuffer_B[5] = "~~~~";	// 5 bytes long to include the unused terminating \0
    sfg.setStatus(&sfg, RECEIVING_WIRELESS);
    flags = UART_GetStatusFlags(WIRELESS_UART);
    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags)
    {
        sts = UART_TransferGetReceiveCount(WIRELESS_UART, &wireless_uartHandle, &nbytes);
        if (sts == kStatus_Success)
        {
            data = UART_ReadByte(WIRELESS_UART);
            DecodeCommandBytes(&sfg, iCommandBuffer_B, &data, 1);
        }
    }
}
// initialize BlueRadios BR-LE4.0-D2A Bluetooth module
// This is required for NXP FRDM-FXS-MULT2-B boards.
void BlueRadios_Init(void)
{
	uint16_t ilen;		// command string length

	// transmit "ATSRM,2,0\r" to minimize traffic from the module
	// command "ATSRM": sets the module response mode which configures how verbose the module will be
	// 2: response mode at to minimal
	// 0: disconnected mode is command mode
	// \r: carriage return escape sequence
	strcpy((char *)sUARTOutputBuffer, "ATSRM,2,0\r");
	ilen = strlen((char *)sUARTOutputBuffer);
        writeWirelessPort(sUARTOutputBuffer, ilen);
 	return;
}
#endif

#if F_USE_WIRED_UART
void echo(uint8_t data)  // only used for comms debug
{
    /* Send data only when UART TX register is empty and ring buffer has data to send out. */
    if (kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(WIRED_UART))
    {
        UART_WriteByte(WIRED_UART, data);
    }
}
// Wired and Wireless UART interrupt handlers are essentially identical.
void WIRED_UART_IRQHandler(void)
{
    uint8_t     data;
    status_t    sts;
    uint32_t    nbytes;		   // number of bytes received
    uint32_t    flags;
    static char iCommandBuffer_A[5] = "~~~~";	// 5 bytes long to include the unused terminating \0

    sfg.setStatus(&sfg, RECEIVING_WIRED);
    flags = UART_GetStatusFlags(WIRED_UART);
    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags)
    {
        sts = UART_TransferGetReceiveCount(WIRED_UART, &wired_uartHandle, &nbytes);
        if (sts == kStatus_Success)
        {
            data = UART_ReadByte(WIRED_UART);
            DecodeCommandBytes(&sfg, iCommandBuffer_A, &data, 1);
        }
    }
}
#endif

/// Initialize the control subsystem and all related hardware
int8_t initializeControlPort(
    ControlSubsystem *pComm  ///< pointer to the control subystem structure
)
{
    uart_config_t   config;
    if (pComm)
    {
        pComm->DefaultQuaternionPacketType = Q3;    // default to simplest algorithm
        pComm->QuaternionPacketType = Q3;           // default to simplest algorithm
        pComm->AngularVelocityPacketOn = true;      // transmit angular velocity packet
        pComm->DebugPacketOn = true;                // transmit debug packet
        pComm->RPCPacketOn = true;                  // transmit roll, pitch, compass packet
        pComm->AltPacketOn = true;                 // Altitude packet
        pComm->AccelCalPacketOn = 0;
        pComm->write = writeControlPort;
        pComm->stream = CreateAndSendPackets;

#if F_USE_WIRED_UART
        /* Initialize WIRED UART pins below - currently duplicates code in pin_mux.c */
        CLOCK_EnableClock(WIRED_UART_PORT_CLKEN);
        PORT_SetPinMux(WIRED_UART_PORT, WIRED_UART_RX_PIN, WIRED_UART_MUX);
        PORT_SetPinMux(WIRED_UART_PORT, WIRED_UART_TX_PIN, WIRED_UART_MUX);
        UART_GetDefaultConfig(&config);

        config.baudRate_Bps = CONTROL_BAUDRATE;
        config.enableTx = true;
        config.enableRx = true;
        config.rxFifoWatermark = 1;
        UART_Init(WIRED_UART, &config, CLOCK_GetFreq(WIRED_UART_CLKSRC));

        /* Enable RX interrupt. */
        UART_EnableInterrupts(WIRED_UART, kUART_RxDataRegFullInterruptEnable |
                              kUART_RxOverrunInterruptEnable);
        EnableIRQ(WIRED_UART_IRQn);
#endif
#if F_USE_WIRELESS_UART
        /* Initialize WIRELESS UART pins below */
        CLOCK_EnableClock(WIRELESS_UART_PORT_CLKEN);
        PORT_SetPinMux(WIRELESS_UART_PORT, WIRELESS_UART_RX_PIN,
                       WIRELESS_UART_MUX);
        PORT_SetPinMux(WIRELESS_UART_PORT, WIRELESS_UART_TX_PIN,
                       WIRELESS_UART_MUX);

        UART_Init(WIRELESS_UART, &config, CLOCK_GetFreq(WIRELESS_UART_CLKSRC));
        BlueRadios_Init();

        /* Enable RX interrupt. */
        UART_EnableInterrupts(WIRELESS_UART, kUART_RxDataRegFullInterruptEnable |
                              kUART_RxOverrunInterruptEnable);
        EnableIRQ(WIRELESS_UART_IRQn);
#endif

        return (0);
    }
    else
    {
        return (1);
    }
}
