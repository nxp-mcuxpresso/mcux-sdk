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
#include "fsl_uart.h"
#include "fsl_uart_sdma.h"

#include "fsl_rdc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_UART_DMA_BASEADDR SDMAARM1
#define DEMO_UART                 UART4
#define DEMO_UART_CLK_FREQ        BOARD_DEBUG_UART_CLK_FREQ
#define UART_RX_DMA_CHANNEL       1U
#define UART_TX_DMA_CHANNEL       2U
#define UART_RX_DMA_REQUEST       (28)
#define UART_TX_DMA_REQUEST       (29)
#define ECHO_BUFFER_LENGTH 8

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_sdma_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(uart_sdma_handle_t g_uartSdmaHandle, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_handle_t g_uartTxSdmaHandle, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_handle_t g_uartRxSdmaHandle, 4);

AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t context_Tx, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t context_Rx, 4);

AT_NONCACHEABLE_SECTION_ALIGN(uart_transfer_t sendXfer, 4);
AT_NONCACHEABLE_SECTION_ALIGN(uart_transfer_t receiveXfer, 4);

AT_NONCACHEABLE_SECTION_ALIGN_INIT(uint8_t g_tipString[], 4) =
    "Uart sdma transfer example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";

AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_txBuffer[ECHO_BUFFER_LENGTH], 4);
AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH], 4);

volatile bool rxBufferEmpty = true;
volatile bool txBufferFull  = false;
volatile bool txOnGoing     = false;
volatile bool rxOnGoing     = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_sdma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing    = false;
    }

    if (kStatus_UART_RxIdle == status)
    {
        rxBufferEmpty = false;
        rxOnGoing     = false;
    }
}

/*!e
 * @brief Main function
 */
int main(void)
{
    status_t status;
    uart_config_t config;
    sdma_config_t sdmaConfig;
    uart_transfer_t xfer;

    /*set SDMA1 PERIPH to M4 Domain(DID=1),due to UART not be accessible by DID=0 by default*/
    rdc_domain_assignment_t assignment = {0};
    assignment.domainId                = BOARD_DOMAIN_ID;
    RDC_SetMasterDomainAssignment(RDC, kRDC_Master_SDMA1_PERIPH, &assignment);

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
     * config.rxFifoWatermark = 1;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps    = BOARD_DEBUG_UART_BAUDRATE;
    config.rxFifoWatermark = 1;
    config.enableTx        = true;
    config.enableRx        = true;

    status = UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    /* Init the SDMA module */
    SDMA_GetDefaultConfig(&sdmaConfig);
    SDMA_Init(EXAMPLE_UART_DMA_BASEADDR, &sdmaConfig);
    SDMA_CreateHandle(&g_uartTxSdmaHandle, EXAMPLE_UART_DMA_BASEADDR, UART_TX_DMA_CHANNEL, &context_Tx);
    SDMA_CreateHandle(&g_uartRxSdmaHandle, EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL, &context_Rx);
    SDMA_SetChannelPriority(EXAMPLE_UART_DMA_BASEADDR, UART_TX_DMA_CHANNEL, 3U);
    SDMA_SetChannelPriority(EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL, 4U);

    /* Create UART DMA handle. */
    UART_TransferCreateHandleSDMA(DEMO_UART, &g_uartSdmaHandle, UART_UserCallback, NULL, &g_uartTxSdmaHandle,
                                  &g_uartRxSdmaHandle, UART_TX_DMA_REQUEST, UART_RX_DMA_REQUEST);

    /* Send g_tipString out. */
    xfer.data     = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing     = true;
    UART_SendSDMA(DEMO_UART, &g_uartSdmaHandle, &xfer);

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
            UART_ReceiveSDMA(DEMO_UART, &g_uartSdmaHandle, &receiveXfer);
        }
        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;
            UART_SendSDMA(DEMO_UART, &g_uartSdmaHandle, &sendXfer);
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
