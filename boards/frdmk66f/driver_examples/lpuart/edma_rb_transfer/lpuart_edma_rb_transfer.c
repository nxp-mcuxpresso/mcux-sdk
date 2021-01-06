/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lpuart_edma.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_LPUART                 LPUART0
#define EXAMPLE_LPUART_CLKSRC          kCLOCK_PllFllSelClk
#define EXAMPLE_LPUART_CLK_FREQ        CLOCK_GetFreq(kCLOCK_PllFllSelClk)
#define LPUART_TX_DMA_CHANNEL          0U
#define LPUART_RX_DMA_CHANNEL          1U
#define EXAMPLE_LPUART_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_LPUART_DMA_BASEADDR    DMA0
#define LPUART_TX_DMA_REQUEST          kDmaRequestMux0LPUART0Tx
#define LPUART_RX_DMA_REQUEST          kDmaRequestMux0LPUART0Rx
#define EXAMPLE_LPUART_IRQHandler      LPUART0_IRQHandler
#define EXAMPLE_LPUART_IRQn            LPUART0_IRQn
/* Ring buffer size definition, please make sure to set this value large enough.
 * Otherwise, once overflow occurred, data in ring buffer will be overwritten.
 */
#define EXAMPLE_RING_BUFFER_SIZE (32U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Initialzie the USART module. */
static void EXAMPLE_InitEDMA(void);

/* Initalize the DMA configuration for USART  TX and RX used.  */
static void EXAMPLE_InitLPUART(void);

/* Start ring buffer. */
static void EXAMPLE_StartRingBufferEDMA(void);

/* Reading data from the ring buffer. */
static void EXAMPLE_ReadRingBuffer(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length);

/* LPUART RX EDMA call back. */
void EXAMPLE_RxEDMACallback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

/* LPUART user callback */
void EXAMPLE_TxEDMACallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
lpuart_edma_handle_t g_lpuartEdmaHandle;
edma_handle_t g_lpuartTxEdmaHandle;
edma_handle_t g_lpuartRxEdmaHandle;
AT_NONCACHEABLE_SECTION_INIT(uint8_t g_tipString[]) =
    "LPUART EDMA ring buffer example.\r\nBoard will send back received characters:\r\n";
AT_NONCACHEABLE_SECTION_INIT(uint8_t g_rxBuffer[EXAMPLE_RING_BUFFER_SIZE]) = {0};
volatile bool txOnGoing                                                    = false;
volatile bool isIdleLineDetected                                           = false;
volatile uint32_t ringBufferFlag                                           = 0U;
volatile uint32_t receivedBytes                                            = 0U;
volatile uint32_t ringBufferIndex                                          = 0U;

/* allocate ring buffer section. */
AT_NONCACHEABLE_SECTION_INIT(uint8_t g_ringBuffer[EXAMPLE_RING_BUFFER_SIZE]) = {0};
/* Allocate TCD memory poll with ring buffer used. */
AT_NONCACHEABLE_SECTION_ALIGN(static edma_tcd_t tcdMemoryPoolPtr[1], sizeof(edma_tcd_t));

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Initialzie the USART module. */
static void EXAMPLE_InitLPUART(void)
{
    lpuart_config_t lpuartConfig;

    /*
     * lpuartConfig.baudRate_Bps = 115200U;
     * lpuartConfig.parityMode = kLPUART_ParityDisabled;
     * lpuartConfig.stopBitCount = kLPUART_OneStopBit;
     * lpuartConfig.txFifoWatermark = 0;
     * lpuartConfig.rxFifoWatermark = 0;
     * lpuartConfig.enableTx = false;
     * lpuartConfig.enableRx = false;
     */
    LPUART_GetDefaultConfig(&lpuartConfig);
    lpuartConfig.rxIdleType   = kLPUART_IdleTypeStopBit;
    lpuartConfig.rxIdleConfig = kLPUART_IdleCharacter2;
    lpuartConfig.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    lpuartConfig.enableTx     = true;
    lpuartConfig.enableRx     = true;

    LPUART_Init(EXAMPLE_LPUART, &lpuartConfig, EXAMPLE_LPUART_CLK_FREQ);
}

/* Initalize the DMA configuration for USART  TX and RX used. */
static void EXAMPLE_InitEDMA(void)
{
    edma_config_t config;

#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_LPUART_DMAMUX_BASEADDR);
    /* Set channel for LPUART */
    DMAMUX_SetSource(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_TX_DMA_CHANNEL, LPUART_TX_DMA_REQUEST);
    DMAMUX_SetSource(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_RX_DMA_CHANNEL, LPUART_RX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_TX_DMA_CHANNEL);
    DMAMUX_EnableChannel(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_RX_DMA_CHANNEL);
#endif

    /* Init the EDMA module */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(EXAMPLE_LPUART_DMA_BASEADDR, &config);
    EDMA_CreateHandle(&g_lpuartTxEdmaHandle, EXAMPLE_LPUART_DMA_BASEADDR, LPUART_TX_DMA_CHANNEL);
    EDMA_CreateHandle(&g_lpuartRxEdmaHandle, EXAMPLE_LPUART_DMA_BASEADDR, LPUART_RX_DMA_CHANNEL);

    /* Create LPUART DMA handle for sending data. */
    LPUART_TransferCreateHandleEDMA(EXAMPLE_LPUART, &g_lpuartEdmaHandle, EXAMPLE_TxEDMACallback, NULL,
                                    &g_lpuartTxEdmaHandle, &g_lpuartRxEdmaHandle);
}

/* Start ring buffer. */
static void EXAMPLE_StartRingBufferEDMA(void)
{
    edma_transfer_config_t xferConfig;

    /* Install TCD memory for using only one TCD queue. */
    EDMA_InstallTCDMemory(&g_lpuartRxEdmaHandle, (edma_tcd_t *)&tcdMemoryPoolPtr[0], 1U);

    /* Prepare transfer to receive data to ring buffer. */
    EDMA_PrepareTransfer(&xferConfig, (void *)(uint32_t *)LPUART_GetDataRegisterAddress(EXAMPLE_LPUART),
                         sizeof(uint8_t), g_ringBuffer, sizeof(uint8_t), sizeof(uint8_t), EXAMPLE_RING_BUFFER_SIZE,
                         kEDMA_PeripheralToMemory);

    /* Submit transfer. */
    g_lpuartRxEdmaHandle.tcdUsed = 1U;
    g_lpuartRxEdmaHandle.tail    = 0U;
    EDMA_TcdReset(&g_lpuartRxEdmaHandle.tcdPool[0U]);
    EDMA_TcdSetTransferConfig(&g_lpuartRxEdmaHandle.tcdPool[0U], &xferConfig, tcdMemoryPoolPtr);

    /* Enable major interrupt for counting received bytes. */
    g_lpuartRxEdmaHandle.tcdPool[0U].CSR |= DMA_CSR_INTMAJOR_MASK;

    /* There is no live chain, TCD block need to be installed in TCD registers. */
    EDMA_InstallTCD(g_lpuartRxEdmaHandle.base, g_lpuartRxEdmaHandle.channel, &g_lpuartRxEdmaHandle.tcdPool[0U]);

    /* Setup call back function. */
    EDMA_SetCallback(&g_lpuartRxEdmaHandle, EXAMPLE_RxEDMACallback, NULL);

    /* Start EDMA transfer. */
    EDMA_StartTransfer(&g_lpuartRxEdmaHandle);

    /* Enable LPUART RX EDMA. */
    LPUART_EnableRxDMA(EXAMPLE_LPUART, true);

    /* Enable RX interrupt for detecting the IDLE line interrupt. */
    LPUART_EnableInterrupts(EXAMPLE_LPUART, kLPUART_IdleLineInterruptEnable);
    EnableIRQ(EXAMPLE_LPUART_IRQn);
}

/* Reading out the data from ring buffer. */
static void EXAMPLE_ReadRingBuffer(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length)
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
            ringBufferFlag--;
        }
        index--;
    }
}

void EXAMPLE_LPUART_IRQHandler(void)
{
    uint32_t status            = LPUART_GetStatusFlags(EXAMPLE_LPUART);
    uint32_t enabledInterrupts = LPUART_GetEnabledInterrupts(EXAMPLE_LPUART);

    /* If new data arrived. */
    if ((0U != ((uint32_t)kLPUART_IdleLineFlag & status)) &&
        (0U != ((uint32_t)kLPUART_IdleLineInterruptEnable & enabledInterrupts)))
    {
        (void)LPUART_ClearStatusFlags(EXAMPLE_LPUART, kLPUART_IdleLineFlag);
        isIdleLineDetected = true;
        receivedBytes      = EXAMPLE_RING_BUFFER_SIZE -
                        EDMA_GetRemainingMajorLoopCount(EXAMPLE_LPUART_DMA_BASEADDR, LPUART_RX_DMA_CHANNEL);
        receivedBytes += (EXAMPLE_RING_BUFFER_SIZE * ringBufferFlag) - ringBufferIndex;

        if (receivedBytes > 32U)
        {
            __NOP();
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

/* LPUART RX EDMA call back. */
void EXAMPLE_RxEDMACallback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (true == transferDone)
    {
        ringBufferFlag++;
    }
}

/* LPUART EDMA TX user callback */
void EXAMPLE_TxEDMACallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_LPUART_TxIdle == status)
    {
        txOnGoing = false;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    lpuart_transfer_t sendXfer;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    CLOCK_SetLpuartClock(1U);

    /* Initialize the LPUART module. */
    EXAMPLE_InitLPUART();

    /* Intialzie the EDMA configuration. */
    EXAMPLE_InitEDMA();

    /* Send g_tipString out. */
    sendXfer.data     = g_tipString;
    sendXfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing         = true;
    LPUART_SendEDMA(EXAMPLE_LPUART, &g_lpuartEdmaHandle, &sendXfer);

    /* Wait send finished */
    while (txOnGoing)
    {
    }

    /* Start ring buffer with EDMA used. */
    EXAMPLE_StartRingBufferEDMA();

    while (1)
    {
        isIdleLineDetected = false;
        /* Wait for IDLE line detect. */
        while (!isIdleLineDetected)
        {
        }

        EXAMPLE_ReadRingBuffer(g_ringBuffer, g_rxBuffer, receivedBytes);

        /* Start to echo. */
        sendXfer.data     = g_rxBuffer;
        sendXfer.dataSize = receivedBytes;

        LPUART_SendEDMA(EXAMPLE_LPUART, &g_lpuartEdmaHandle, &sendXfer);
    }
}
