/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_uart.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_UART          UART2
#define DEMO_UART_CLKSRC   SYS_CLK
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(SYS_CLK)

#define EXAMPLE_ADDRESS 0x7EU
#define TRANSFER_SIZE   16U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_txBuffer[TRANSFER_SIZE * 2U] = {0};
uint8_t g_rxBuffer[TRANSFER_SIZE + 1U] = {0};
volatile bool txComplete               = false;
volatile bool rxComplete               = false;
uart_handle_t g_uartHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
    if (kStatus_UART_TxIdle == status)
    {
        txComplete = true;
    }

    if (kStatus_UART_RxIdle == status)
    {
        rxComplete = true;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i;
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    PRINTF(
        "UART 9-bit mode example begins\r\nUART is configured with address, only data sent to itself after matched "
        "address can be received\r\n");

    /* Initialize uart instance. */
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 1;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    uart_config_t config;
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;
    UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
    UART_Enable9bitMode(DEMO_UART, true);
    /* Configure address. */
    UART_SetMatchAddress(DEMO_UART, EXAMPLE_ADDRESS, 0U);
    /* Enable match address. */
    UART_EnableMatchAddress(DEMO_UART, true, false);

    /* Set up transfer data */
    for (i = 0U; i < TRANSFER_SIZE * 2U; i++)
    {
        g_txBuffer[i] = i;
    }

    for (i = 0U; i < TRANSFER_SIZE + 1U; i++)
    {
        g_rxBuffer[i] = 0;
    }

    /* Create uart handle. */
    UART_TransferCreateHandle(DEMO_UART, &g_uartHandle, UART_UserCallback, NULL);
    /* Start receiving. */
    uart_transfer_t g_receiveXfer;
    g_receiveXfer.data     = g_rxBuffer;
    g_receiveXfer.dataSize = TRANSFER_SIZE + 1U;
    UART_TransferReceiveNonBlocking(DEMO_UART, &g_uartHandle, &g_receiveXfer, NULL);

    /* First send TRANSFER_SIZE byte of data without addressing itself first, these data should be discarded. */
    PRINTF("UART will send first piece of data out:\n\r");
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        if (i % 8U == 0U)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_txBuffer[i]);
    }
    PRINTF("\r\n\r\n");
    uart_transfer_t g_sendXfer;
    g_sendXfer.data     = g_txBuffer;
    g_sendXfer.dataSize = TRANSFER_SIZE;
    UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &g_sendXfer);
    /* Waiting for transfer completion. */
    while (txComplete == false)
    {
    }
    txComplete = false;
    /* Address itself. */
    PRINTF("UART will address itself\n\r");
    UART_SendAddress(DEMO_UART, EXAMPLE_ADDRESS);
    /* Then send the other TRANSFER_SIZE byte of data, these data should be received in g_rxBuffer. */
    PRINTF("UART will send the other piece of data out:\n\r");
    for (i = TRANSFER_SIZE; i < TRANSFER_SIZE * 2U; i++)
    {
        if (i % 8U == 0U)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_txBuffer[i]);
    }
    PRINTF("\r\n\r\n");
    g_sendXfer.data     = &g_txBuffer[TRANSFER_SIZE];
    g_sendXfer.dataSize = TRANSFER_SIZE;
    UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &g_sendXfer);

    /* Waiting for transfer completion */
    while ((txComplete == false) || (rxComplete == false))
    {
    }

    bool success = true;
    PRINTF("UART received data:\n\r");
    for (i = 0; i < TRANSFER_SIZE; i++)
    {
        if (i % 8U == 0U)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_rxBuffer[i + 1U]);
    }
    PRINTF("\r\n\r\n");
    /* Check if the data is right. */
    for (i = 0; i < TRANSFER_SIZE; i++)
    {
        if (g_rxBuffer[i + 1U] != g_txBuffer[i + TRANSFER_SIZE])
        {
            success = false;
            PRINTF("Received data does not match!\n\r");
            break;
        }
    }
    if (success)
    {
        PRINTF("All data matches!\n\r");
    }

    while (1)
    {
    }
}
