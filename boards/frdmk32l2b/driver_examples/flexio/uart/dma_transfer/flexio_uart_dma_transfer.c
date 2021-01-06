/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_flexio_uart_dma.h"
#include "fsl_dmamux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_FLEXIO_BASE                   FLEXIO
#define FLEXIO_UART_TX_PIN                  5U
#define FLEXIO_UART_RX_PIN                  4U
#define FLEXIO_CLOCK_FREQUENCY              48000000U
#define FLEXIO_DMA_REQUEST_BASE             kDmaRequestMux0FlexIOChannel0
#define EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_FLEXIO_UART_DMA_BASEADDR    DMA0
#define FLEXIO_UART_TX_DMA_CHANNEL          0U
#define FLEXIO_UART_RX_DMA_CHANNEL          1U
#define FLEXIO_TX_SHIFTER_INDEX             0U
#define FLEXIO_RX_SHIFTER_INDEX             1U
#define EXAMPLE_TX_DMA_SOURCE               (FLEXIO_DMA_REQUEST_BASE + FLEXIO_TX_SHIFTER_INDEX)
#define EXAMPLE_RX_DMA_SOURCE               (FLEXIO_DMA_REQUEST_BASE + FLEXIO_RX_SHIFTER_INDEX)
#define ECHO_BUFFER_LENGTH 8

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* UART user callback */
void FLEXIO_UART_UserCallback(FLEXIO_UART_Type *base,
                              flexio_uart_dma_handle_t *handle,
                              status_t status,
                              void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
flexio_uart_dma_handle_t g_uartHandle;
FLEXIO_UART_Type uartDev;
dma_handle_t g_uartTxDmaHandle;
dma_handle_t g_uartRxDmaHandle;

uint8_t g_tipString[] =
    "Flexio uart dma example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";

uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};
uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};
volatile bool rxBufferEmpty            = true;
volatile bool txBufferFull             = false;
volatile bool txOnGoing                = false;
volatile bool rxOnGoing                = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART user callback */
void FLEXIO_UART_UserCallback(FLEXIO_UART_Type *base, flexio_uart_dma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_FLEXIO_UART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing    = false;
    }

    if (kStatus_FLEXIO_UART_RxIdle == status)
    {
        rxBufferEmpty = false;
        rxOnGoing     = false;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    flexio_uart_config_t config;
    flexio_uart_transfer_t xfer;
    flexio_uart_transfer_t sendXfer;
    flexio_uart_transfer_t receiveXfer;
    dma_request_source_t dma_request_source_tx;
    dma_request_source_t dma_request_source_rx;
    status_t result = kStatus_Success;

    BOARD_InitPins();
    BOARD_BootClockRUN();

    CLOCK_SetFlexio0Clock(1U);

    /*
     * config.enableUart = true;
     * config.enableInDoze = false;
     * config.enableInDebug = true;
     * config.enableFastAccess = false;
     * config.baudRate_Bps = 115200U;
     * config.bitCountPerChar = kFLEXIO_UART_8BitsPerChar;
     */
    FLEXIO_UART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableUart   = true;

    uartDev.flexioBase      = BOARD_FLEXIO_BASE;
    uartDev.TxPinIndex      = FLEXIO_UART_TX_PIN;
    uartDev.RxPinIndex      = FLEXIO_UART_RX_PIN;
    uartDev.shifterIndex[0] = FLEXIO_TX_SHIFTER_INDEX;
    uartDev.shifterIndex[1] = FLEXIO_RX_SHIFTER_INDEX;
    uartDev.timerIndex[0]   = 0U;
    uartDev.timerIndex[1]   = 1U;

    result = FLEXIO_UART_Init(&uartDev, &config, FLEXIO_CLOCK_FREQUENCY);
    if (result != kStatus_Success)
    {
        return -1;
    }

    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR);

    dma_request_source_tx = (dma_request_source_t)(EXAMPLE_TX_DMA_SOURCE);
    dma_request_source_rx = (dma_request_source_t)(EXAMPLE_RX_DMA_SOURCE);

    /* Set channel for FLEXIO_UART */
    DMAMUX_SetSource(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_TX_DMA_CHANNEL, dma_request_source_tx);
    DMAMUX_SetSource(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_RX_DMA_CHANNEL, dma_request_source_rx);
    DMAMUX_EnableChannel(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_TX_DMA_CHANNEL);
    DMAMUX_EnableChannel(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_RX_DMA_CHANNEL);

    /* Init the DMA module */
    DMA_Init(EXAMPLE_FLEXIO_UART_DMA_BASEADDR);
    DMA_CreateHandle(&g_uartTxDmaHandle, EXAMPLE_FLEXIO_UART_DMA_BASEADDR, FLEXIO_UART_TX_DMA_CHANNEL);
    DMA_CreateHandle(&g_uartRxDmaHandle, EXAMPLE_FLEXIO_UART_DMA_BASEADDR, FLEXIO_UART_RX_DMA_CHANNEL);

    FLEXIO_UART_TransferCreateHandleDMA(&uartDev, &g_uartHandle, FLEXIO_UART_UserCallback, NULL, &g_uartTxDmaHandle,
                                        &g_uartRxDmaHandle);

    /* Send g_tipString out. */
    xfer.data     = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing     = true;
    FLEXIO_UART_TransferSendDMA(&uartDev, &g_uartHandle, &xfer);

    /* Wait send finished */
    while (txOnGoing)
    {
    }

    /* Start to echo. */
    sendXfer.data        = g_txBuffer;
    sendXfer.dataSize    = ECHO_BUFFER_LENGTH;
    receiveXfer.data     = g_rxBuffer;
    receiveXfer.dataSize = ECHO_BUFFER_LENGTH;

    while (1)
    {
        /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
        if ((!rxOnGoing) && rxBufferEmpty)
        {
            rxOnGoing = true;
            FLEXIO_UART_TransferReceiveDMA(&uartDev, &g_uartHandle, &receiveXfer);
        }

        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;
            FLEXIO_UART_TransferSendDMA(&uartDev, &g_uartHandle, &sendXfer);
        }

        /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
        if ((!rxBufferEmpty) && (!txBufferFull))
        {
            memcpy(g_txBuffer, g_rxBuffer, ECHO_BUFFER_LENGTH);
            rxBufferEmpty = true;
            txBufferFull  = true;
        }
    }
}
