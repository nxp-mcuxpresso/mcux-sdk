/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi_dma.h"
#include "fsl_dmamux.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SPI_SLAVE      SPI1
#define EXAMPLE_DMA            DMA0
#define EXAMPLE_DMAMUX         DMAMUX0
#define EXAMPLE_SPI_TX_CHANNEL 0U
#define EXAMPLE_SPI_RX_CHANNEL 1U
#define EXAMPLE_SPI_TX_SOURCE  kDmaRequestMux0SPI1Tx
#define EXAMPLE_SPI_RX_SOURCE  kDmaRequestMux0SPI1Rx

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define BUFFER_SIZE (64)
static uint8_t buff[BUFFER_SIZE];
static uint8_t sendBuff[BUFFER_SIZE];
static spi_dma_handle_t s_handle;
static dma_handle_t txHandle;
static dma_handle_t rxHandle;
static volatile bool slaveFinished = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
static void slaveCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData)
{
    slaveFinished = true;
}

int main(void)
{
    uint32_t i          = 0;
    uint8_t err         = 0;
    spi_transfer_t xfer = {0};
    spi_slave_config_t userConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    PRINTF("\n\rSlave is working....\n\r");

    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_DMAMUX);
    DMAMUX_SetSource(EXAMPLE_DMAMUX, EXAMPLE_SPI_TX_CHANNEL, EXAMPLE_SPI_TX_SOURCE);
    DMAMUX_SetSource(EXAMPLE_DMAMUX, EXAMPLE_SPI_RX_CHANNEL, EXAMPLE_SPI_RX_SOURCE);
    DMAMUX_EnableChannel(EXAMPLE_DMAMUX, EXAMPLE_SPI_TX_CHANNEL);
    DMAMUX_EnableChannel(EXAMPLE_DMAMUX, EXAMPLE_SPI_RX_CHANNEL);

    /* Init the DMA module */
    DMA_Init(EXAMPLE_DMA);
    DMA_CreateHandle(&txHandle, EXAMPLE_DMA, EXAMPLE_SPI_TX_CHANNEL);
    DMA_CreateHandle(&rxHandle, EXAMPLE_DMA, EXAMPLE_SPI_RX_CHANNEL);

    /* Init the SPI slave */
    /*
     * userConfig->polarity = kSPI_ClockPolarityActiveHigh;
     * userConfig->phase = kSPI_ClockPhaseFirstEdge;
     * userConfig->direction = kSPI_MsbFirst;
     * userConfig->enableStopInWaitMode = false;
     * userConfig->dataMode = kSPI_8BitMode;
     * userConfig->txWatermark = kSPI_TxFifoOneHalfEmpty;
     * userConfig->rxWatermark = kSPI_RxFifoOneHalfFull;
     */
    SPI_SlaveGetDefaultConfig(&userConfig);
    SPI_SlaveInit(EXAMPLE_SPI_SLAVE, &userConfig);
    SPI_SlaveTransferCreateHandleDMA(EXAMPLE_SPI_SLAVE, &s_handle, slaveCallback, NULL, &txHandle, &rxHandle);
    for (i = 0; i < 64; i++)
    {
        sendBuff[i] = i;
    }

    /* receive data from master */
    xfer.txData   = sendBuff;
    xfer.rxData   = buff;
    xfer.dataSize = BUFFER_SIZE;
    SPI_SlaveTransferDMA(EXAMPLE_SPI_SLAVE, &s_handle, &xfer);

    while (slaveFinished != true)
    {
    }

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        if (buff[i] != i)
        {
            PRINTF("\n\rThe %d number is wrong! It is %d\n\r", i, buff[i]);
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
