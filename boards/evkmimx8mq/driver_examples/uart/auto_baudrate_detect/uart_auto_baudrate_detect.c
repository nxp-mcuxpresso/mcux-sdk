/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_UART          UART2
#define DEMO_UART_CLK_FREQ BOARD_DEBUG_UART_CLK_FREQ
#define DEMO_UART_BAUDRATE 115200U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t infobuff[] = "UART has detected one character ";
uint8_t txbuff[]   = "\r\nBaud rate has been set automatic!\r\nBoard will send back received characters\r\n";
uint8_t rxbuff[20] = {0};

uint8_t fbuffer[] = "";
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t ch;
    status_t status;

    uart_config_t config;

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitMemory();

    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 2;
     * config.rxFifoWatermark = 1;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 0U;

    config.enableTx = true;
    config.enableRx = true;

    status = UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    UART_EnableAutoBaudRate(DEMO_UART, true);

    while (!UART_IsAutoBaudRateComplete(DEMO_UART))
    {
    }
    UART_WriteBlocking(DEMO_UART, infobuff, sizeof(infobuff) - 1);
    /* Read the detect character from recevier register */
    UART_ReadBlocking(DEMO_UART, &ch, 1);
    UART_WriteBlocking(DEMO_UART, &ch, 1);

    UART_WriteBlocking(DEMO_UART, txbuff, sizeof(txbuff) - 1);

    while (1)
    {
        UART_ReadBlocking(DEMO_UART, &ch, 1);
        UART_WriteBlocking(DEMO_UART, &ch, 1);
    }
}
