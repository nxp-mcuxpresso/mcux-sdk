/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart_edma.h"
#include "fsl_dmamux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_UART                 UART0
#define EXAMPLE_UART_CLKSRC          SYS_CLK
#define EXAMPLE_UART_CLK_FREQ        CLOCK_GetFreq(SYS_CLK)
#define UART_TX_DMA_CHANNEL          0U
#define UART_RX_DMA_CHANNEL          1U
#define EXAMPLE_UART_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_UART_DMA_BASEADDR    DMA0
#define UART_TX_DMA_REQUEST          kDmaRequestMux0UART0Tx
#define UART_RX_DMA_REQUEST          kDmaRequestMux0UART0Rx

#define DEMO_UART_IRQn       UART0_RX_TX_IRQn
#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler
#define EXAMPLE_RING_BUFFER_SIZE 32

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Initialize the UART module. */
static void EXAMPLE_InitUART(void);

/* Initialize the EDMA configuration. */
static void EXAMPLE_InitEDMA(void);

/* Start ring buffer configuration. */
static void EXAMPLE_StartRingBufferEDMA(void);

/* Get how many bytes in ring buffer. */
static uint32_t EXAMPLE_GetRingBufferLengthEDMA(void);

/* Read the characters from ring buffer. */
static void EXAMPLE_ReadRingBufferEDMA(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length);

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_edma_handle_t *handle, status_t status, void *userData);

/* UART user irq handler */
void DEMO_UART_IRQHandler(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/

uart_edma_handle_t g_uartEdmaHandle;
edma_handle_t g_uartTxEdmaHandle;
edma_handle_t g_uartRxEdmaHandle;
uint8_t g_tipString[] = "UART EDMA example\r\nSend back received data\r\nEcho every 8 characters\r\n";
uint8_t g_rxBuffer[EXAMPLE_RING_BUFFER_SIZE] = {0};
volatile bool txOnGoing                      = false;
volatile bool rxIdleLineDetected             = false;
volatile uint32_t ringBufferIndex            = 0U;

AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_ringBuffer[EXAMPLE_RING_BUFFER_SIZE], 16);
/* Allocate TCD memory poll with ring buffer used. */
AT_NONCACHEABLE_SECTION_ALIGN(edma_tcd_t tcdMemoryPoolPtr[1], sizeof(edma_tcd_t));

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize the UART module. */
static void EXAMPLE_InitUART(void)
{
    uart_config_t uartConfig;

    /*
     * uartConfig.baudRate_Bps = 115200U;
     * uartConfig.parityMode = kUART_ParityDisabled;
     * uartConfig.stopBitCount = kUART_OneStopBit;
     * uartConfig.txFifoWatermark = 0;
     * uartConfig.rxFifoWatermark = 1;
     * uartConfig.enableTx = false;
     * uartConfig.enableRx = false;
     */
    UART_GetDefaultConfig(&uartConfig);
    uartConfig.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    uartConfig.enableTx     = true;
    uartConfig.enableRx     = true;

    UART_Init(EXAMPLE_UART, &uartConfig, EXAMPLE_UART_CLK_FREQ);
}

/* Initialize the EDMA configuration. */
static void EXAMPLE_InitEDMA(void)
{
    edma_config_t config;

    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_UART_DMAMUX_BASEADDR);
    /* Set channel for UART */
    DMAMUX_SetSource(EXAMPLE_UART_DMAMUX_BASEADDR, UART_TX_DMA_CHANNEL, UART_TX_DMA_REQUEST);
    DMAMUX_SetSource(EXAMPLE_UART_DMAMUX_BASEADDR, UART_RX_DMA_CHANNEL, UART_RX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_UART_DMAMUX_BASEADDR, UART_TX_DMA_CHANNEL);
    DMAMUX_EnableChannel(EXAMPLE_UART_DMAMUX_BASEADDR, UART_RX_DMA_CHANNEL);

    /* Init the EDMA module */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(EXAMPLE_UART_DMA_BASEADDR, &config);
    EDMA_CreateHandle(&g_uartTxEdmaHandle, EXAMPLE_UART_DMA_BASEADDR, UART_TX_DMA_CHANNEL);
    EDMA_CreateHandle(&g_uartRxEdmaHandle, EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL);

    /* Create UART DMA handle. */
    UART_TransferCreateHandleEDMA(EXAMPLE_UART, &g_uartEdmaHandle, UART_UserCallback, NULL, &g_uartTxEdmaHandle, NULL);
}

/* Start ring buffer configuration. */
static void EXAMPLE_StartRingBufferEDMA(void)
{
    edma_transfer_config_t xferConfig;

    /* Install TCD memory. */
    EDMA_InstallTCDMemory(&g_uartRxEdmaHandle, tcdMemoryPoolPtr, 1U);

    /* Prepare transfer to receive data to ring buffer. */
    EDMA_PrepareTransfer(&xferConfig, (void *)UART_GetDataRegisterAddress(EXAMPLE_UART), sizeof(uint8_t), g_ringBuffer,
                         sizeof(uint8_t), sizeof(uint8_t), EXAMPLE_RING_BUFFER_SIZE, kEDMA_PeripheralToMemory);

    /* Submit transfer. */
    g_uartRxEdmaHandle.tcdUsed = 1U;
    g_uartRxEdmaHandle.tail    = 0U;
    EDMA_TcdReset(&g_uartRxEdmaHandle.tcdPool[0U]);
    EDMA_TcdSetTransferConfig(&g_uartRxEdmaHandle.tcdPool[0U], &xferConfig, tcdMemoryPoolPtr);

    /* Enable major interrupt for calculating the received bytes. */
    g_uartRxEdmaHandle.tcdPool[0U].CSR |= DMA_CSR_INTMAJOR_MASK;

    /* There is no live chain, TCD block need to be installed in TCD registers. */
    EDMA_InstallTCD(EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL, &g_uartRxEdmaHandle.tcdPool[0U]);

    /* Start EDMA transfer. */
    EDMA_StartTransfer(&g_uartRxEdmaHandle);

    /* Enable UART RX EDMA. */
    UART_EnableRxDMA(EXAMPLE_UART, true);
}

/* Get how many bytes in ring buffer. */
static uint32_t EXAMPLE_GetRingBufferLengthEDMA(void)
{
    uint32_t regPrimask    = 0U;
    uint32_t receivedBytes = 0U;

    /* Disable IRQ, protect ring buffer. */
    regPrimask = DisableGlobalIRQ();

    receivedBytes =
        EXAMPLE_RING_BUFFER_SIZE - EDMA_GetRemainingMajorLoopCount(EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL);

    /* If the received bytes is less than index value, it means the ring buffer has reached it boundary. */
    if (receivedBytes < ringBufferIndex)
    {
        receivedBytes += EXAMPLE_RING_BUFFER_SIZE;
    }

    receivedBytes -= ringBufferIndex;

    /* Enable IRQ if previously enabled. */
    EnableGlobalIRQ(regPrimask);

    return receivedBytes;
}

/* Read the characters from ring buffer. */
static void EXAMPLE_ReadRingBufferEDMA(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length)
{
    assert(ringBuffer);
    assert(receiveBuffer);
    assert(length);

    uint32_t index = length;

    /* If length if larger than ring buffer size, it means overflow occurred, need to reset the ringBufferIndex. */
    if (length > EXAMPLE_RING_BUFFER_SIZE)
    {
        ringBufferIndex = ((ringBufferIndex + length) % EXAMPLE_RING_BUFFER_SIZE);
        index           = EXAMPLE_RING_BUFFER_SIZE;
    }

    while (index)
    {
        *(receiveBuffer++) = ringBuffer[ringBufferIndex++];
        if (ringBufferIndex == EXAMPLE_RING_BUFFER_SIZE)
        {
            ringBufferIndex = 0U;
        }
        index--;
    }
}

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_edma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
        txOnGoing = false;
    }
}

/* UART user irq handler */
void DEMO_UART_IRQHandler(void)
{
    if ((UART_GetStatusFlags(EXAMPLE_UART) & (uint32_t)kUART_IdleLineFlag) != 0U)
    {
        rxIdleLineDetected = true;
        UART_ClearStatusFlags(EXAMPLE_UART, (uint32_t)kUART_IdleLineFlag);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t byteCount = 0U;
    uart_transfer_t xfer;
    uart_transfer_t sendXfer;

    /* Initialzie the hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();

    /* Initialize the UART configurations. */
    EXAMPLE_InitUART();

    /* Initialize the EDMA configuration for UART trasnfer. */
    EXAMPLE_InitEDMA();

    /* Send g_tipString out. */
    xfer.data     = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing     = true;
    UART_SendEDMA(EXAMPLE_UART, &g_uartEdmaHandle, &xfer);

    /* Wait send finished */
    while (txOnGoing)
    {
    }

    /* Start ring buffer. */
    EXAMPLE_StartRingBufferEDMA();

    /* Enable IDLE line interrupt */
    EnableIRQ(DEMO_UART_IRQn);
    UART_EnableInterrupts(EXAMPLE_UART, (uint32_t)kUART_IdleLineInterruptEnable);

    while (1)
    {
        byteCount = 0U;

        /* Wait for idle line interrupt occur */
        while (!rxIdleLineDetected)
        {
        }

        rxIdleLineDetected = false;
        /* Get the received bytes number stored in DMA ring buffer. */
        byteCount = EXAMPLE_GetRingBufferLengthEDMA();

        /* If byte count larger than ring buffer size, it menas data overflow occurred with ring buffer used.
         * Users should make sure the ring buffer is large enough or read the ring buffer ASAP.
         */
        if (byteCount > EXAMPLE_RING_BUFFER_SIZE)
        {
            byteCount = EXAMPLE_RING_BUFFER_SIZE;
        }

        /* Move the data from ring buffer to given buffer section. */
        EXAMPLE_ReadRingBufferEDMA(g_ringBuffer, g_rxBuffer, byteCount);

        /* Wait for sending finished */
        while (txOnGoing)
        {
        }

        /* Start to echo. */
        txOnGoing         = true;
        sendXfer.data     = g_rxBuffer;
        sendXfer.dataSize = byteCount;
        UART_SendEDMA(EXAMPLE_UART, &g_uartEdmaHandle, &sendXfer);
    }
}
