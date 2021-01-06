/*
 * Copyright  2017 NXP
 * All rights reserved.
 *
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
#define DEMO_IRQn                 UART4_IRQn
#define DEMO_UART_CLK_FREQ        BOARD_DEBUG_UART_CLK_FREQ
#define UART_RX_DMA_CHANNEL       1U
#define UART_TX_DMA_CHANNEL       2U
#define UART_RX_DMA_REQUEST       (28)
#define UART_TX_DMA_REQUEST       (29)
#define DEMO_UART_IRQHandler      UART4_IRQHandler
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
    "Uart sdma transfer example!\r\nUart will receive 8 charactes every time, if less characters were received, "
    "\r\nUart will generate the idle line detect interrupt, SDMA receive operation will be aborted.\r\nBoard will send "
    "the received characters out.\r\nNow please input:\r\n";

AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_txBuffer[ECHO_BUFFER_LENGTH], 4);
AT_NONCACHEABLE_SECTION_ALIGN(uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH], 4);

volatile bool rxBufferEmpty = true;
volatile bool txBufferFull  = false;
volatile bool txOnGoing     = false;
volatile bool rxOnGoing     = false;
volatile uint32_t dataSize  = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART IRQHandler function. */
void DEMO_UART_IRQHandler(uint32_t giccIar, void *param)
{
    /* if receiver awake flag was detedted. */
    if ((UART_GetStatusFlag(DEMO_UART, kUART_WakeFlag)) && (UART_GetEnabledInterrupts(DEMO_UART) & kUART_WakeEnable))
    {
        /* Enable the IDLE line detected interrupt. */
        UART_ClearStatusFlag(DEMO_UART, kUART_IdleFlag);
        UART_EnableInterrupts(DEMO_UART, kUART_RxDmaIdleEnable);
        /* Disable the receiver awake interrupt for next transfer. */
        UART_DisableInterrupts(DEMO_UART, kUART_WakeEnable);
        UART_ClearStatusFlag(DEMO_UART, kUART_WakeFlag);
    }
    __DSB();
}

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
        dataSize      = ECHO_BUFFER_LENGTH;

        /* Check if IDLE flag was detedted with idle interrupt enabled.
         * Please note that, the IDLE flag will always be set if no data received.
         * If the receiver was not in IDLE status, the idle flag will be cleared by hardware.
         * That is to say, Idle lines indicate the end or the beginning of a message.
         */
        if ((UART_GetStatusFlag(DEMO_UART, kUART_IdleFlag)) &&
            (UART_GetEnabledInterrupts(DEMO_UART) & kUART_RxDmaIdleEnable))
        {
            dataSize = SDMA_GetTransferredBytes(&g_uartRxSdmaHandle);
            UART_DisableInterrupts(DEMO_UART, kUART_RxDmaIdleEnable);
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uart_config_t config;
    sdma_config_t sdmaConfig;
    uart_transfer_t xfer;
    status_t status;

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

    /* Configure the condition of IDLE detected. */
    UART_SetIdleCondition(DEMO_UART, kUART_IdleFor16Frames);
    UART_DisableInterrupts(DEMO_UART, kUART_AllInterruptsEnable);

    EnableIRQ(DEMO_IRQn);

    while (1)
    {
        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;
            UART_SendSDMA(DEMO_UART, &g_uartSdmaHandle, &sendXfer);
        }

        /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
        if ((!rxOnGoing) && rxBufferEmpty)
        {
            /* Enable receiver wake interrupt, if the receiver start to receive data,
             * this interrupt will be generated.
             */
            if (UART_GetStatusFlag(DEMO_UART, kUART_IdleFlag))
            {
                UART_ClearStatusFlag(DEMO_UART, kUART_WakeFlag);
                UART_EnableInterrupts(DEMO_UART, kUART_WakeEnable);
            }

            rxOnGoing = true;
            UART_ReceiveSDMA(DEMO_UART, &g_uartSdmaHandle, &receiveXfer);
        }

        /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
        if ((!rxBufferEmpty) && (!txBufferFull))
        {
            if (dataSize == 0U)
            {
                rxBufferEmpty = true;
                continue;
            }
            memcpy(g_txBuffer, g_rxBuffer, dataSize);
            memset(g_rxBuffer, 0, ECHO_BUFFER_LENGTH);
            sendXfer.dataSize = dataSize;
            rxBufferEmpty     = true;
            txBufferFull      = true;
        }
    }
}
