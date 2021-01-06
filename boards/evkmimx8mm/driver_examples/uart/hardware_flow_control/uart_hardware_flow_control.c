/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_UART UART3
#define DEMO_UART_CLK_FREQ                                                                  \
    CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootUart3)) / \
        (CLOCK_GetRootPostDivider(kCLOCK_RootUart3)) / 10
#define DEMO_UART_BAUDRATE 115200U
#define DELAY_TIME         0xFFFFU
#define TRANSFER_SIZE     256U    /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 115200U /*! Transfer baudrate - 115200 */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t transferRxData[TRANSFER_SIZE] = {0U};
uint8_t transferTxData[TRANSFER_SIZE] = {0U};
uart_handle_t g_uartHandle;
volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* PUART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
    if (kStatus_UART_TxIdle == status)
    {
        isTransferCompleted = true;
    }
}
/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0U, errCount = 0U;
    status_t status = 0;
    uart_config_t config;
    uart_transfer_t sendXfer;

    /* Board specific RDC settings */
    BOARD_RdcInit();

    /* Set UART3 source to SysPLL1 Div10 80MHZ */
    CLOCK_SetRootMux(kCLOCK_RootUart3, kCLOCK_UartRootmuxSysPll1Div10);
    /* Set root clock to 80MHZ/ 1= 80MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootUart3, 1U, 1U);

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();
    PRINTF("This is UART hardware flow control example on one board.\r\n");
    PRINTF("This example will send data to itself and will use hardware flow control to avoid the overflow.\r\n");
    PRINTF("Please make sure you make the correct line connection. Basically, the connection is: \r\n");
    PRINTF("      UART_TX    --     UART_RX    \r\n");
    PRINTF("      UART_RTS   --     UART_CTS   \r\n");
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 0;
     * config.enableTx = true;
     * config.enableRx = true;
     * config.enableRxRTS  = true;
     * config.enableTxCTS  = true;
     */
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = DEMO_UART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;
    config.enableRxRTS  = true;
    config.enableTxCTS  = true;

    UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
    UART_TransferCreateHandle(DEMO_UART, &g_uartHandle, UART_UserCallback, NULL);

    /* Set up the transfer data */
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        transferTxData[i] = i % 256U;
        transferRxData[i] = 0U;
    }

    sendXfer.data     = (uint8_t *)transferTxData;
    sendXfer.dataSize = TRANSFER_SIZE;
    UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &sendXfer);

    /* Delay for some time to let the RTS pin dessart. */
    for (i = 0U; i < DELAY_TIME; i++)
    {
        __NOP();
    }

    status = UART_ReadBlocking(DEMO_UART, transferRxData, TRANSFER_SIZE);
    if (kStatus_Success != status)
    {
        PRINTF(" Error occurred when UART receiving data.\r\n");
    }
    /* Wait for the transmit complete. */
    while (!isTransferCompleted)
    {
    }

    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        if (transferTxData[i] != transferRxData[i])
        {
            errCount++;
        }
    }
    if (errCount)
    {
        PRINTF("Data not matched! Transfer error.\r\n");
    }
    else
    {
        PRINTF("Data matched! Transfer successfully.\r\n");
    }
    /* Deinit the UART. */
    UART_Deinit(DEMO_UART);

    while (1)
    {
    }
}
