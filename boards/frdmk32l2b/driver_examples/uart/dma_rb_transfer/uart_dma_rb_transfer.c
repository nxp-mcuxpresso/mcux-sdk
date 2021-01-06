/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart_dma.h"
#include "fsl_dmamux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_UART                 UART2
#define EXAMPLE_UART_CLKSRC          kCLOCK_BusClk
#define EXAMPLE_UART_CLK_FREQ        CLOCK_GetFreq(kCLOCK_BusClk)
#define UART_TX_DMA_CHANNEL          0U
#define UART_RX_DMA_CHANNEL          1U
#define EXAMPLE_UART_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_UART_DMA_BASEADDR    DMA0
#define UART_TX_DMA_REQUEST          kDmaRequestMux0UART2Tx
#define UART_RX_DMA_REQUEST          kDmaRequestMux0UART2Rx

#define DEMO_UART_IRQn       UART2_FLEXIO_IRQn
#define DEMO_UART_IRQHandler UART2_FLEXIO_IRQHandler
#define EXAMPLE_RING_BUFFER_SIZE      (32U)
#define EXAMPLE_DMA_MODULE_TYPE       kDMA_Modulo32Bytes
#define EXAMPLE_DMA_TRANSFER_MAX_SIZE (0xFFFFFU)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Initialize the UART module. */
static void EXAMPLE_InitUART(void);

/* Initialize the DMA configuration. */
static void EXAMPLE_InitDMA(void);

/* Start ring buffer configuration. */
static void EXAMPLE_StartRingBufferDMA(void);

/* Get how many bytes in ring buffer. */
static uint32_t EXAMPLE_GetRingBufferLengthDMA(void);

/* Read the characters from ring buffer. */
static void EXAMPLE_ReadRingBufferDMA(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length);

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_dma_handle_t *handle, status_t status, void *userData);

/* UART user irq handler */
void DEMO_UART_IRQHandler(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
uart_dma_handle_t g_uartDmaHandle;
dma_handle_t g_uartTxDmaHandle;
dma_handle_t g_uartRxDmaHandle;
uint8_t g_tipString[]                        = "UART DMA ring buffer example\r\nBoard will send back received data\r\n";
uint8_t g_rxBuffer[EXAMPLE_RING_BUFFER_SIZE] = {0};
volatile bool txOnGoing                      = false;
volatile bool rxIdleLineDetected             = false;
volatile uint32_t ringBufferIndex            = 0U;

AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_ringBuffer[EXAMPLE_RING_BUFFER_SIZE], 32);

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

/* Initialize the DMA configuration. */
static void EXAMPLE_InitDMA(void)
{
    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_UART_DMAMUX_BASEADDR);

    /* Set channel for LPUART  */
    DMAMUX_SetSource(EXAMPLE_UART_DMAMUX_BASEADDR, UART_TX_DMA_CHANNEL, UART_TX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_UART_DMAMUX_BASEADDR, UART_TX_DMA_CHANNEL);
    DMAMUX_SetSource(EXAMPLE_UART_DMAMUX_BASEADDR, UART_RX_DMA_CHANNEL, UART_RX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_UART_DMAMUX_BASEADDR, UART_RX_DMA_CHANNEL);

    /* Init the DMA module */
    DMA_Init(EXAMPLE_UART_DMA_BASEADDR);

    /* Create handle for DMA transfer used. */
    DMA_CreateHandle(&g_uartTxDmaHandle, EXAMPLE_UART_DMA_BASEADDR, UART_TX_DMA_CHANNEL);
    DMA_CreateHandle(&g_uartRxDmaHandle, EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL);

    /* Create UART DMA handle for sending data. */
    UART_TransferCreateHandleDMA(EXAMPLE_UART, &g_uartDmaHandle, UART_UserCallback, NULL, &g_uartTxDmaHandle, NULL);
}

/* Start ring buffer configuration. */
static void EXAMPLE_StartRingBufferDMA(void)
{
    dma_transfer_config_t xferConfig;

    ringBufferIndex = 0U;

    /* Prepare transfer. */
    DMA_PrepareTransfer(&xferConfig, (void *)UART_GetDataRegisterAddress(EXAMPLE_UART), sizeof(uint8_t), g_ringBuffer,
                        sizeof(uint8_t), EXAMPLE_DMA_TRANSFER_MAX_SIZE, kDMA_PeripheralToMemory);

    /* Submit transfer. */
    DMA_SubmitTransfer(&g_uartRxDmaHandle, &xferConfig, kDMA_EnableInterrupt);

    /* Note that, the dma_modulo_t must be equals to ring buffer size. */
    DMA_SetModulo(EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL, kDMA_ModuloDisable, EXAMPLE_DMA_MODULE_TYPE);

    DMA_StartTransfer(&g_uartRxDmaHandle);

    /* Enable LPUART RX DMA. */
    UART_EnableRxDMA(EXAMPLE_UART, true);

    /* Enable IDLE line interrupt */
    UART_EnableInterrupts(EXAMPLE_UART, (uint32_t)kUART_IdleLineInterruptEnable);
    EnableIRQ(DEMO_UART_IRQn);
}

/* Get how many bytes in ring buffer. */
static uint32_t EXAMPLE_GetRingBufferLengthDMA(void)
{
    uint32_t receivedBytes =
        EXAMPLE_DMA_TRANSFER_MAX_SIZE - DMA_GetRemainingBytes(EXAMPLE_UART_DMA_BASEADDR, UART_RX_DMA_CHANNEL);
    if (receivedBytes != 0U)
    {
        /* Reload the BCR count for continueous transfer. */
        EXAMPLE_UART_DMA_BASEADDR->DMA[UART_RX_DMA_CHANNEL].DSR_BCR = DMA_DSR_BCR_BCR(EXAMPLE_DMA_TRANSFER_MAX_SIZE);
    }

    return receivedBytes;
}

/* Read the characters from ring buffer. */
static void EXAMPLE_ReadRingBufferDMA(uint8_t *ringBuffer, uint8_t *receiveBuffer, uint32_t length)
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
void UART_UserCallback(UART_Type *base, uart_dma_handle_t *handle, status_t status, void *userData)
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
    uart_transfer_t xfer;
    uart_transfer_t sendXfer;
    uint32_t length = 0U;

    /* Initialzie the hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();

    /* Initialize the UART configurations. */
    EXAMPLE_InitUART();

    /* Initialize the DMA configuration for UART trasnfer. */
    EXAMPLE_InitDMA();

    /* Send g_tipString out. */
    xfer.data     = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    txOnGoing     = true;
    UART_TransferSendDMA(EXAMPLE_UART, &g_uartDmaHandle, &xfer);

    /* Wait send finished */
    while (txOnGoing)
    {
    }

    /* Start ring buffer. */
    EXAMPLE_StartRingBufferDMA();

    while (1)
    {
        /* Wait for idle line interrupt occur*/
        while (!rxIdleLineDetected)
        {
        }
        rxIdleLineDetected = false;
        /* Get the received bytes number stored in DMA ring buffer. */
        length = EXAMPLE_GetRingBufferLengthDMA();
        /* If byte count larger than ring buffer size, it menas data overflow occurred with ring buffer used.
         * Users should make sure the ring buffer is large enough or read the ring buffer ASAP.
         */
        if (length > EXAMPLE_RING_BUFFER_SIZE)
        {
            length = EXAMPLE_RING_BUFFER_SIZE;
        }

        /* Move the data from ring buffer to given buffer section. */
        EXAMPLE_ReadRingBufferDMA(g_ringBuffer, g_rxBuffer, length);
        /* Wait for sending finished */
        while (txOnGoing)
        {
        }

        /* Start to echo. */
        txOnGoing         = true;
        sendXfer.data     = g_rxBuffer;
        sendXfer.dataSize = length;
        UART_TransferSendDMA(EXAMPLE_UART, &g_uartDmaHandle, &sendXfer);
    }
}
