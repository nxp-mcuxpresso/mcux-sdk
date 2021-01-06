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
#include "fsl_device_registers.h"
#include "fsl_lpuart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_LPUART          LPUART3
#define DEMO_LPUART_CLK_FREQ BOARD_DebugConsoleSrcFreq()


#define EXAMPLE_ADDRESS 0x7EU
#define TRANSFER_SIZE   16U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* LPUART user callback */
void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_txBuffer[TRANSFER_SIZE * 2U] = {0};
uint8_t g_rxBuffer[TRANSFER_SIZE + 1U] = {0};
volatile bool txComplete               = false;
volatile bool rxComplete               = false;
lpuart_handle_t g_lpuartHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* LPUART user callback */
void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if (kStatus_LPUART_TxIdle == status)
    {
        txComplete = true;
    }

    if (kStatus_LPUART_RxIdle == status)
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
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    PRINTF(
        "LPUART 9-bit mode example begins\r\nLPUART is configured with address, only data sent to itself after matched "
        "address can be received\r\n");

    /* Initialize lpuart instance. */
    /* lpuartConfig->baudRate_Bps = 115200U;
     * lpuartConfig->parityMode = kLPUART_ParityDisabled;
     * lpuartConfig->dataBitsCount = kLPUART_EightDataBits;
     * lpuartConfig->isMsb = false;
     * lpuartConfig->stopBitCount = kLPUART_OneStopBit;
     * lpuartConfig->txFifoWatermark = 0;
     * lpuartConfig->rxFifoWatermark = 1;
     * lpuartConfig->rxIdleType = kLPUART_IdleTypeStartBit;
     * lpuartConfig->rxIdleConfig = kLPUART_IdleCharacter1;
     * lpuartConfig->enableTx = false;
     * lpuartConfig->enableRx = false;
     */
    lpuart_config_t config;
    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200U;
    config.enableTx     = true;
    config.enableRx     = true;
    LPUART_Init(DEMO_LPUART, &config, DEMO_LPUART_CLK_FREQ);
    LPUART_Enable9bitMode(DEMO_LPUART, true);
    /* Configure address. */
    LPUART_SetMatchAddress(DEMO_LPUART, EXAMPLE_ADDRESS, 0U);
    /* Enable match address. */
    LPUART_EnableMatchAddress(DEMO_LPUART, true, false);

    /* Set up transfer data */
    for (i = 0U; i < TRANSFER_SIZE * 2U; i++)
    {
        g_txBuffer[i] = i;
    }

    for (i = 0U; i < TRANSFER_SIZE + 1U; i++)
    {
        g_rxBuffer[i] = 0;
    }

    /* Create lpuart handle. */
    LPUART_TransferCreateHandle(DEMO_LPUART, &g_lpuartHandle, LPUART_UserCallback, NULL);
    /* Start receiving. */
    lpuart_transfer_t g_receiveXfer;
    g_receiveXfer.data     = g_rxBuffer;
    g_receiveXfer.dataSize = TRANSFER_SIZE + 1U;
    LPUART_TransferReceiveNonBlocking(DEMO_LPUART, &g_lpuartHandle, &g_receiveXfer, NULL);

    /* First send TRANSFER_SIZE byte of data without addressing itself first, these data should be discarded. */
    PRINTF("LPUART will send first piece of data out:\n\r");
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        if (i % 8U == 0U)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_txBuffer[i]);
    }
    PRINTF("\r\n\r\n");
    lpuart_transfer_t g_sendXfer;
    g_sendXfer.data     = g_txBuffer;
    g_sendXfer.dataSize = TRANSFER_SIZE;
    LPUART_TransferSendNonBlocking(DEMO_LPUART, &g_lpuartHandle, &g_sendXfer);
    /* Waiting for transfer completion. */
    while (txComplete == false)
    {
    }
    txComplete = false;
    /* Address itself. */
    PRINTF("LPUART will address itself\n\r");
    LPUART_SendAddress(DEMO_LPUART, EXAMPLE_ADDRESS);
    /* Then send the other TRANSFER_SIZE byte of data, these data should be received in g_rxBuffer. */
    PRINTF("LPUART will send the other piece of data out:\n\r");
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
    LPUART_TransferSendNonBlocking(DEMO_LPUART, &g_lpuartHandle, &g_sendXfer);

    /* Waiting for transfer completion */
    while ((txComplete == false) || (rxComplete == false))
    {
    }

    bool success = true;
    PRINTF("LPUART received data:\n\r");
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
