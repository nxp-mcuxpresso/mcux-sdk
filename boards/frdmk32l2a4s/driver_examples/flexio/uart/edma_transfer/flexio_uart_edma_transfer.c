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
#include "fsl_flexio_uart_edma.h"
#include "fsl_dmamux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_FLEXIO_BASE                   FLEXIO0
#define FLEXIO_UART_TX_PIN                  3U
#define FLEXIO_UART_RX_PIN                  2U
#define FLEXIO_CLOCK_FREQUENCY              CLOCK_GetIpFreq(kCLOCK_Flexio0)
#define FLEXIO_DMA_REQUEST_BASE             kDmaRequestMux0FlexIO0Channel0
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
                              flexio_uart_edma_handle_t *handle,
                              status_t status,
                              void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
flexio_uart_edma_handle_t g_uartHandle;
FLEXIO_UART_Type uartDev;
edma_handle_t g_uartTxEdmaHandle;
edma_handle_t g_uartRxEdmaHandle;

AT_NONCACHEABLE_SECTION_INIT(uint8_t g_tipString[]) =
    "Flexio uart edma example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";

AT_NONCACHEABLE_SECTION_INIT(uint8_t g_txBuffer[ECHO_BUFFER_LENGTH]) = {0};
AT_NONCACHEABLE_SECTION_INIT(uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH]) = {0};
volatile bool rxBufferEmpty                                          = true;
volatile bool txBufferFull                                           = false;
volatile bool txOnGoing                                              = false;
volatile bool rxOnGoing                                              = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART user callback */
void FLEXIO_UART_UserCallback(FLEXIO_UART_Type *base,
                              flexio_uart_edma_handle_t *handle,
                              status_t status,
                              void *userData)
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
    flexio_uart_config_t userconfig;
    flexio_uart_transfer_t xfer;
    flexio_uart_transfer_t sendXfer;
    flexio_uart_transfer_t receiveXfer;
    status_t result = kStatus_Success;
    edma_config_t config;

    BOARD_InitPins();
    BOARD_BootClockRUN();

    CLOCK_SetIpSrc(kCLOCK_Flexio0, kCLOCK_IpSrcSircAsync);

    /*
     * config.enableUart = true;
     * config.enableInDoze = false;
     * config.enableInDebug = true;
     * config.enableFastAccess = false;
     * config.baudRate_Bps = 115200U;
     * config.bitCountPerChar = kFLEXIO_UART_8BitsPerChar;
     */
    FLEXIO_UART_GetDefaultConfig(&userconfig);
    userconfig.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    userconfig.enableUart   = true;

    uartDev.flexioBase      = BOARD_FLEXIO_BASE;
    uartDev.TxPinIndex      = FLEXIO_UART_TX_PIN;
    uartDev.RxPinIndex      = FLEXIO_UART_RX_PIN;
    uartDev.shifterIndex[0] = FLEXIO_TX_SHIFTER_INDEX;
    uartDev.shifterIndex[1] = FLEXIO_RX_SHIFTER_INDEX;
    uartDev.timerIndex[0]   = 0U;
    uartDev.timerIndex[1]   = 1U;

    result = FLEXIO_UART_Init(&uartDev, &userconfig, FLEXIO_CLOCK_FREQUENCY);
    if (result != kStatus_Success)
    {
        return -1;
    }

    /*Init DMA for example*/
    DMAMUX_Init(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR);
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(EXAMPLE_FLEXIO_UART_DMA_BASEADDR, &config);

    /* Request DMA channels for TX & RX. */
    DMAMUX_SetSource(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_TX_DMA_CHANNEL, EXAMPLE_TX_DMA_SOURCE);
    DMAMUX_SetSource(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_RX_DMA_CHANNEL, EXAMPLE_RX_DMA_SOURCE);
    DMAMUX_EnableChannel(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_TX_DMA_CHANNEL);
    DMAMUX_EnableChannel(EXAMPLE_FLEXIO_UART_DMAMUX_BASEADDR, FLEXIO_UART_RX_DMA_CHANNEL);
    EDMA_CreateHandle(&g_uartTxEdmaHandle, EXAMPLE_FLEXIO_UART_DMA_BASEADDR, FLEXIO_UART_TX_DMA_CHANNEL);
    EDMA_CreateHandle(&g_uartRxEdmaHandle, EXAMPLE_FLEXIO_UART_DMA_BASEADDR, FLEXIO_UART_RX_DMA_CHANNEL);

    FLEXIO_UART_TransferCreateHandleEDMA(&uartDev, &g_uartHandle, FLEXIO_UART_UserCallback, NULL, &g_uartTxEdmaHandle,
                                         &g_uartRxEdmaHandle);

    /* Send g_tipString out. */
    xfer.data     = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing     = true;
    FLEXIO_UART_TransferSendEDMA(&uartDev, &g_uartHandle, &xfer);

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
            FLEXIO_UART_TransferReceiveEDMA(&uartDev, &g_uartHandle, &receiveXfer);
        }

        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;
            FLEXIO_UART_TransferSendEDMA(&uartDev, &g_uartHandle, &sendXfer);
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
