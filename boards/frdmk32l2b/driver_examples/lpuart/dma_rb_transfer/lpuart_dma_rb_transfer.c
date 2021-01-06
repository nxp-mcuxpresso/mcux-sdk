/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lpuart_dma.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_LPUART                 LPUART0
#define EXAMPLE_LPUART_CLKSRC          BOARD_DEBUG_UART_CLKSRC
#define EXAMPLE_LPUART_CLK_FREQ        CLOCK_GetFreq(BOARD_DEBUG_UART_CLKSRC)
#define LPUART_TX_DMA_CHANNEL          0U
#define LPUART_RX_DMA_CHANNEL          1U
#define EXAMPLE_LPUART_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_LPUART_DMA_BASEADDR    DMA0
#define LPUART_TX_DMA_REQUEST          kDmaRequestMux0LPUART0Tx
#define LPUART_RX_DMA_REQUEST          kDmaRequestMux0LPUART0Rx

#define EXAMPLE_LPUART_IRQHandler LPUART0_IRQHandler
#define EXAMPLE_LPUART_IRQn       LPUART0_IRQn
/* Ring buffer size definition, please make sure to set this value large enough.
 * Otherwise, once overflow occurred, data in ring buffer will be overwritten.
 */
#define EXAMPLE_RING_BUFFER_SIZE      (32U)
#define EXAMPLE_DMA_MODULE_TYPE       kDMA_Modulo32Bytes
#define EXAMPLE_DMA_TRANSFER_MAX_SIZE (0xFFFFFU)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Initialzie the LPUART module. */
static void EXAMPLE_InitDMA(void);

/* Initalize the DMA configuration for LPUART  TX and RX used.  */
static void EXAMPLE_InitLPUART(void);

/* Start ring buffer. */
static void EXAMPLE_StartRingBufferDMA(void);

/* Reading data from the ring buffer. */
static void EXAMPLE_ReadRingBuffer(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length);

/* Get how many characters stored in ring buffer. */
static uint32_t EXAMPLE_GetRingBufferLengthDMA(void);

/* LPUART user callback */
void EXAMPLE_TxDMACallback(LPUART_Type *base, lpuart_dma_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
lpuart_dma_handle_t g_lpuartDmaHandle;
dma_handle_t g_lpuartTxDmaHandle;
dma_handle_t g_lpuartRxDmaHandle;
AT_NONCACHEABLE_SECTION_INIT(uint8_t g_tipString[]) =
    "LPUART DMA ring buffer example.\r\nBoard will send back received characters:\r\n";
AT_NONCACHEABLE_SECTION_INIT(uint8_t g_rxBuffer[EXAMPLE_RING_BUFFER_SIZE]) = {0};
volatile bool txOnGoing                                                    = false;
volatile bool isIdleLineDetected                                           = false;
volatile uint32_t receivedBytes                                            = 0U;
volatile uint32_t ringBufferIndex                                          = 0U;

/* Note that, the alignment of ring buffer must be same with EXAMPLE_DMA_MODULE_TYPE. */
AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_ringBuffer[EXAMPLE_RING_BUFFER_SIZE], 32);

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
static void EXAMPLE_InitDMA(void)
{
    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_LPUART_DMAMUX_BASEADDR);

    /* Set channel for LPUART  */
    DMAMUX_SetSource(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_TX_DMA_CHANNEL, LPUART_TX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_TX_DMA_CHANNEL);
    DMAMUX_SetSource(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_RX_DMA_CHANNEL, LPUART_RX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_LPUART_DMAMUX_BASEADDR, LPUART_RX_DMA_CHANNEL);

    /* Init the DMA module */
    DMA_Init(EXAMPLE_LPUART_DMA_BASEADDR);

    /* Create handle for DMA transfer used. */
    DMA_CreateHandle(&g_lpuartTxDmaHandle, EXAMPLE_LPUART_DMA_BASEADDR, LPUART_TX_DMA_CHANNEL);
    DMA_CreateHandle(&g_lpuartRxDmaHandle, EXAMPLE_LPUART_DMA_BASEADDR, LPUART_RX_DMA_CHANNEL);

    /* Create LPUART DMA handle for sending data. */
    LPUART_TransferCreateHandleDMA(EXAMPLE_LPUART, &g_lpuartDmaHandle, EXAMPLE_TxDMACallback, NULL,
                                   &g_lpuartTxDmaHandle, NULL);
}

/* Start ring buffer. */
static void EXAMPLE_StartRingBufferDMA(void)
{
    dma_transfer_config_t xferConfig;

    ringBufferIndex = 0U;

    /* Prepare transfer. */
    DMA_PrepareTransfer(&xferConfig, (void *)LPUART_GetDataRegisterAddress(EXAMPLE_LPUART), sizeof(uint8_t),
                        g_ringBuffer, sizeof(uint8_t), EXAMPLE_DMA_TRANSFER_MAX_SIZE, kDMA_PeripheralToMemory);

    /* Submit transfer. */
    DMA_SubmitTransfer(&g_lpuartRxDmaHandle, &xferConfig, kDMA_EnableInterrupt);

    /* Note that, the dma_modulo_t must be equals to ring buffer size. */
    DMA_SetModulo(EXAMPLE_LPUART_DMA_BASEADDR, LPUART_RX_DMA_CHANNEL, kDMA_ModuloDisable, EXAMPLE_DMA_MODULE_TYPE);

    DMA_StartTransfer(&g_lpuartRxDmaHandle);

    /* Enable LPUART RX DMA. */
    LPUART_EnableRxDMA(EXAMPLE_LPUART, true);

    /* Enable RX IDLE interrupt. */
    LPUART_ClearStatusFlags(EXAMPLE_LPUART, kLPUART_IdleLineFlag);
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
        receivedBytes   = EXAMPLE_RING_BUFFER_SIZE;
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

/* Get how many characters stored in ring buffer.
 * Note: This function must be called before re-write the DSR_BCR register.
 */
static uint32_t EXAMPLE_GetRingBufferLengthDMA(void)
{
    return (EXAMPLE_DMA_TRANSFER_MAX_SIZE - DMA_GetRemainingBytes(EXAMPLE_LPUART_DMA_BASEADDR, LPUART_RX_DMA_CHANNEL));
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

        receivedBytes = EXAMPLE_GetRingBufferLengthDMA();

        /* Reload the BCR count for continueous transfer. */
        EXAMPLE_LPUART_DMA_BASEADDR->DMA[LPUART_RX_DMA_CHANNEL].DSR_BCR =
            DMA_DSR_BCR_BCR(EXAMPLE_DMA_TRANSFER_MAX_SIZE);
    }
    SDK_ISR_EXIT_BARRIER;
}

/* LPUART DMA TX user callback */
void EXAMPLE_TxDMACallback(LPUART_Type *base, lpuart_dma_handle_t *handle, status_t status, void *userData)
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
    CLOCK_SetLpuart0Clock(0x1U);

    /* Initialize the LPUART module. */
    EXAMPLE_InitLPUART();

    /* Intialzie the DMA configuration. */
    EXAMPLE_InitDMA();

    /* Send g_tipString out. */
    sendXfer.data     = g_tipString;
    sendXfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing         = true;
    LPUART_TransferSendDMA(EXAMPLE_LPUART, &g_lpuartDmaHandle, &sendXfer);

    /* Wait send finished */
    while (txOnGoing)
    {
    }

    /* Start ring buffer with DMA used. */
    EXAMPLE_StartRingBufferDMA();

    while (1)
    {
        isIdleLineDetected = false;
        /* Wait for IDLE line detect. */
        while (!isIdleLineDetected)
        {
        }

        EXAMPLE_ReadRingBuffer(g_ringBuffer, g_rxBuffer, receivedBytes);

        /* Wait send finished */
        while (txOnGoing)
        {
        }

        /* Start to echo. */
        txOnGoing         = true;
        sendXfer.data     = g_rxBuffer;
        sendXfer.dataSize = receivedBytes;

        LPUART_TransferSendDMA(EXAMPLE_LPUART, &g_lpuartDmaHandle, &sendXfer);
    }
}
