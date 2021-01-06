/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"

#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SPI_SLAVE     SPI3
#define EXAMPLE_SPI_SLAVE_IRQ FLEXCOMM3_IRQn
#define EXAMPLE_SPI_SSEL      2
#define EXAMPLE_SPI_SPOL      kSPI_SpolActiveAllLow

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define TRANSFER_SIZE (64)
spi_slave_handle_t handle;
static uint8_t receiveBuff[TRANSFER_SIZE];
static uint8_t sendBuff[TRANSFER_SIZE];
static volatile bool slaveFinished = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
static void slaveCallback(SPI_Type *base, spi_slave_handle_t *slaveHandle, status_t status, void *userData)
{
    slaveFinished = true;
}

int main(void)
{
    uint32_t i          = 0;
    uint8_t err         = 0;
    spi_transfer_t xfer = {0};
    spi_slave_config_t userConfig;

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* attach 12 MHz clock to SPI3 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);

    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC3_RST_SHIFT_RSTn);

    BOARD_InitPins();
    BOARD_BootClockPLL150M();
    BOARD_InitDebugConsole();
    PRINTF("\n\rSlave is working....\n\r");

    /*
     * userConfig.enableSlave = true;
     * userConfig.polarity = kSPI_ClockPolarityActiveHigh;
     * userConfig.phase = kSPI_ClockPhaseFirstEdge;
     * userConfig.direction = kSPI_MsbFirst;
     */
    SPI_SlaveGetDefaultConfig(&userConfig);
    userConfig.sselPol = (spi_spol_t)EXAMPLE_SPI_SPOL;
    SPI_SlaveInit(EXAMPLE_SPI_SLAVE, &userConfig);
    SPI_SlaveTransferCreateHandle(EXAMPLE_SPI_SLAVE, &handle, slaveCallback, NULL);
    for (i = 0; i < 64; i++)
    {
        sendBuff[i] = i;
    }

    /* receive data from master*/
    xfer.txData   = sendBuff;
    xfer.rxData   = receiveBuff;
    xfer.dataSize = sizeof(sendBuff);
    SPI_SlaveTransferNonBlocking(EXAMPLE_SPI_SLAVE, &handle, &xfer);

    while (slaveFinished != true)
    {
    }

    for (i = 0; i < TRANSFER_SIZE; i++)
    {
        if (receiveBuff[i] != sendBuff[i])
        {
            PRINTF("\n\rThe %d number is wrong! It is %d\n\r", i, receiveBuff[i]);
            err++;
        }
    }
    PRINTF("\r\n");
    if (err == 0)
    {
        PRINTF("Succeed!\n\r");
    }

    while (1)
    {
    }
}
