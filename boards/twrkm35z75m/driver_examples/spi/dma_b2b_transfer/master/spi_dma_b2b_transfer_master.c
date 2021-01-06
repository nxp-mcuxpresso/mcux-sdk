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
#define EXAMPLE_SPI_MASTER              SPI0
#define EXAMPLE_DMA                     DMA0
#define EXAMPLE_DMAMUX                  DMAMUX
#define EXAMPLE_SPI_TX_CHANNEL          3U
#define EXAMPLE_SPI_RX_CHANNEL          2U
#define EXAMPLE_SPI_TX_SOURCE           kDmaRequestMux0SPI0Tx
#define EXAMPLE_SPI_RX_SOURCE           kDmaRequestMux0SPI0Rx
#define EXAMPLE_SPI_MASTER_SOURCE_CLOCK kCLOCK_CoreSysClk
#define EXAMPLE_SPI_MASTER_CLK_FREQ     CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define BUFFER_SIZE (64)
static uint8_t srcBuff[BUFFER_SIZE];
static uint8_t destBuff[BUFFER_SIZE];
static spi_dma_handle_t s_handle;
static dma_handle_t txHandle;
static dma_handle_t rxHandle;
static volatile bool masterFinished = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
static void masterCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData)
{
    masterFinished = true;
}

int main(void)
{
    spi_transfer_t xfer = {0};
    spi_master_config_t userConfig;
    uint8_t i        = 0;
    uint32_t err     = 0;
    uint32_t srcFreq = 0;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    PRINTF("\n\rMaster Start...\n\r");

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

    /* Init SPI */
    /*
     * userConfig->enableStopInWaitMode = false;
     * userConfig->polarity = kSPI_ClockPolarityActiveHigh;
     * userConfig->phase = kSPI_ClockPhaseFirstEdge;
     * userConfig->direction = kSPI_MsbFirst;
     * userConfig->dataMode = kSPI_8BitMode;
     * userConfig->txWatermark = kSPI_TxFifoOneHalfEmpty;
     * userConfig->rxWatermark = kSPI_RxFifoOneHalfFull;
     * userConfig->pinMode = kSPI_PinModeNormal;
     * userConfig->outputMode = kSPI_SlaveSelectAutomaticOutput;
     * userConfig->baudRate_Bps = 500000U;
     */
    SPI_MasterGetDefaultConfig(&userConfig);
    srcFreq = EXAMPLE_SPI_MASTER_CLK_FREQ;
    SPI_MasterInit(EXAMPLE_SPI_MASTER, &userConfig, srcFreq);

    /* Init Buffer */
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        srcBuff[i] = i;
    }

    /* Send to slave */
    xfer.txData   = srcBuff;
    xfer.rxData   = destBuff;
    xfer.dataSize = BUFFER_SIZE;
    SPI_MasterTransferCreateHandleDMA(EXAMPLE_SPI_MASTER, &s_handle, masterCallback, NULL, &txHandle, &rxHandle);
    SPI_MasterTransferDMA(EXAMPLE_SPI_MASTER, &s_handle, &xfer);

    while (masterFinished != true)
    {
    }

    /* Check if the data is right */
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        if (srcBuff[i] != destBuff[i])
        {
            err++;
            PRINTF("The %d is wrong! data is %d\n\r", i, destBuff[i]);
        }
    }
    if (err == 0)
    {
        PRINTF("Succeed!\n\r");
    }

    while (1)
    {
    }
}
