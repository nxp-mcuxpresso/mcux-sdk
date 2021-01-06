/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_UART          UART4
#define DEMO_UART_CLK_FREQ BOARD_DEBUG_UART_CLK_FREQ
#define DEMO_UART_BAUDRATE 115200U

#define RX_RING_BUFFER_SIZE 20U
#define ECHO_BUFFER_SIZE    8U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uart_handle_t g_uartHandle;
uint8_t g_tipString[] = "UART RX ring buffer example\r\nSend back received data\r\nEcho every 8 bytes\r\n";
uint8_t g_rxRingBuffer[RX_RING_BUFFER_SIZE] = {0}; /* RX ring buffer. */

uint8_t g_rxBuffer[ECHO_BUFFER_SIZE] = {0}; /* Buffer for receive data to echo. */
uint8_t g_txBuffer[ECHO_BUFFER_SIZE] = {0}; /* Buffer for send data to echo. */
volatile bool rxBufferEmpty          = true;
volatile bool txBufferFull           = false;
volatile bool txOnGoing              = false;
volatile bool rxOnGoing              = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing    = false;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uart_config_t config;
    uart_transfer_t xfer;
    uart_transfer_t sendXfer;
    uart_transfer_t receiveXfer;
    size_t receivedBytes;
    uint32_t i;
    status_t status;

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitMemory();

    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.dataBitsCount = kUART_EightDataBits;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 2;
     * config.rxFifoWatermark = 16;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps    = DEMO_UART_BAUDRATE;
    config.txFifoWatermark = 2;
    config.rxFifoWatermark = 16;
    config.enableTx        = true;
    config.enableRx        = true;

    status = UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    UART_TransferCreateHandle(DEMO_UART, &g_uartHandle, UART_UserCallback, NULL);
    UART_TransferStartRingBuffer(DEMO_UART, &g_uartHandle, g_rxRingBuffer, RX_RING_BUFFER_SIZE);

    /* Send g_tipString out. */
    xfer.data     = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing     = true;
    UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &xfer);

    /* Wait send finished */
    while (txOnGoing)
    {
    }

    /* Start to echo. */
    sendXfer.data        = g_txBuffer;
    sendXfer.dataSize    = ECHO_BUFFER_SIZE;
    receiveXfer.data     = g_rxBuffer;
    receiveXfer.dataSize = ECHO_BUFFER_SIZE;

    while (1)
    {
        /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
        if ((!rxBufferEmpty) && (!txBufferFull))
        {
            memcpy(g_txBuffer, g_rxBuffer, ECHO_BUFFER_SIZE);
            rxBufferEmpty = true;
            txBufferFull  = true;
        }

        /* If the data in ring buffer reach ECHO_BUFFER_SIZE, then start to read data from ring buffer. */
        if (ECHO_BUFFER_SIZE <= UART_TransferGetRxRingBufferLength(&g_uartHandle))
        {
            UART_TransferReceiveNonBlocking(DEMO_UART, &g_uartHandle, &receiveXfer, &receivedBytes);
            rxBufferEmpty = false;
        }

        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;
            UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &sendXfer);
        }

        /* Delay some time, simulate the app is processing other things, input data save to ring buffer. */
        i = 0x10U;
        while (i--)
        {
            __NOP();
        }
    }
}
