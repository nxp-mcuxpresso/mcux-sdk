/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file control_lpc.c
    \brief Defines control sub-system for LPC54114

    This file contains a USART implementation of the control subsystem.  The
    command interpreter and streaming functions are contained in two separate
    files.  So you can easily swap those out with only minor changes here.
*/
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "fsl_usart.h"
#include "sensor_fusion.h"
#include "control.h"

// global structures
uint8_t           sUARTOutputBuffer[256];             // larger than the nominal 124 byte size for outgoing packets

// direct access to sfg here is the only place in the entire library where we cannot simply
// pass a pointer.  This is because it is needed by the UART interrupt handlers.  Since this
// only occurs here, in a subsystem which is defined to be application dependent, that is
// considered acceptable.
extern SensorFusionGlobals sfg;

// Blocking function to write a single byte to a specified UART
void myUART_WriteByte(USART_Type *base, uint8_t data)
{
    uint32_t flag = kUSART_TxFifoNotFullFlag & USART_GetStatusFlags(base);
    while (!flag)
    {
        flag = kUSART_TxFifoNotFullFlag & USART_GetStatusFlags(base);
    }
    USART_WriteByte(base, data);
}

// Blocking function pipes specified buffer to both output UARTS
int8_t writeControlPort(ControlSubsystem *pComm, uint8_t buffer[], uint16_t nbytes)
{
    uint16_t    i;
    for (i = 0; i < nbytes; i++)
    {
        myUART_WriteByte(WIRED_USART, buffer[i]);
    }

    return (0);
}

void WIRED_USART_IRQHandler(void)
{
    uint8_t data;
    static char iCommandBuffer_B[5] = "~~~~";	// 5 bytes long to include the unused terminating \0

    /* If new data arrived. */
    if ((kUSART_RxFifoNotEmptyFlag | kUSART_RxError) & USART_GetStatusFlags(WIRED_USART))
    {
        data = USART_ReadByte(WIRED_USART);
        DecodeCommandBytes(&sfg, iCommandBuffer_B, &data, 1);
    }
}

/// Initialize the control subsystem and all related hardware
int8_t initializeControlPort(
    ControlSubsystem *pComm  ///< pointer to the control subystem structure
)
{
    usart_config_t config;
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

        // attach 12 MHz clock to FLEXCOMM0 (debug console)
        CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

        // reset FLEXCOMM for USART
        RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);

        //USART0_InitPins(); // defined in pin_mux.c
        // config.baudRate_Bps = 115200U;
        // config.parityMode = kUSART_ParityDisabled;
        // config.stopBitCount = kUSART_OneStopBit;
        // config.loopback = false;
        // config.enableTx = false;
        // config.enableRx = false;

        USART_GetDefaultConfig(&config);
        config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
        config.enableTx = true;
        config.enableRx = true;

        USART_Init(WIRED_USART, &config, WIRED_USART_CLK_FREQ);

        // Enable RX interrupt.
        USART_EnableInterrupts(WIRED_USART, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
        EnableIRQ(WIRED_USART_IRQn);

        return (0);
    }
    else
    {
        return (1);
    }
}
