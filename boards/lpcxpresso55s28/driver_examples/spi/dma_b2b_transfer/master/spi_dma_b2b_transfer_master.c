/*
 * Copyright  2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "fsl_spi.h"
#include "fsl_spi_dma.h"
#include "fsl_dma.h"
#include "pin_mux.h"
#include "board.h"
#include <stdbool.h>
#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SPI_MASTER            SPI7
#define EXAMPLE_SPI_MASTER_IRQ        FLEXCOMM7_IRQn
#define EXAMPLE_SPI_MASTER_CLK_SRC    kCLOCK_Flexcomm7
#define EXAMPLE_SPI_MASTER_CLK_FREQ   CLOCK_GetFlexCommClkFreq(7U)
#define EXAMPLE_SPI_SSEL              1
#define EXAMPLE_DMA                   DMA0
#define EXAMPLE_SPI_MASTER_RX_CHANNEL 18
#define EXAMPLE_SPI_MASTER_TX_CHANNEL 19
#define EXAMPLE_MASTER_SPI_SPOL       kSPI_SpolActiveAllLow

#define TRANSFER_SIZE 64U /*! Transfer dataSize */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void SPI_MasterUserCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData);
static void EXAMPLE_MasterInit(void);
static void EXAMPLE_MasterDMASetup(void);
static void EXAMPLE_MasterStartDMATransfer(void);
static void EXAMPLE_TransferDataCheck(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t masterRxData[TRANSFER_SIZE] = {0};
uint8_t masterTxData[TRANSFER_SIZE] = {0};

dma_handle_t masterTxHandle;
dma_handle_t masterRxHandle;

spi_dma_handle_t masterHandle;

volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SPI_MasterUserCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_Success)
    {
        isTransferCompleted = true;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Initialize board setting. */
    /* set BOD VBAT level to 1.65V */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    /* attach 12 MHz clock to SPI3 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);

    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);

    BOARD_InitPins();
    BOARD_BootClockPLL150M();
    BOARD_InitDebugConsole();

    /* Print project information. */
    PRINTF("This is SPI DMA transfer master example.\r\n");
    PRINTF("This example will communicate with another slave SPI on the other board.\r\n");
    PRINTF("Please start the slave board first!\r\n");

    /* Initialize SPI master with configuration. */
    EXAMPLE_MasterInit();

    /* Set up DMA for SPI master TX and RX channel. */
    EXAMPLE_MasterDMASetup();

    /* Prepare DMA and start SPI master transfer in DMA way. */
    EXAMPLE_MasterStartDMATransfer();

    /* Waiting for transmission complete and check if all data matched. */
    EXAMPLE_TransferDataCheck();

    /* De-initialzie the DMA instance. */
    DMA_Deinit(EXAMPLE_DMA);

    /* De-initialize the SPI instance. */
    SPI_Deinit(EXAMPLE_SPI_MASTER);

    while (1)
    {
    }
}

static void EXAMPLE_MasterInit(void)
{
    /* SPI init */
    uint32_t srcClock_Hz = 0U;
    spi_master_config_t masterConfig;
    srcClock_Hz = EXAMPLE_SPI_MASTER_CLK_FREQ;

    SPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.sselNum = (spi_ssel_t)EXAMPLE_SPI_SSEL;
    masterConfig.sselPol = (spi_spol_t)EXAMPLE_MASTER_SPI_SPOL;
    SPI_MasterInit(EXAMPLE_SPI_MASTER, &masterConfig, srcClock_Hz);
}

static void EXAMPLE_MasterDMASetup(void)
{
    /* DMA init */
    DMA_Init(EXAMPLE_DMA);
    /* Configure the DMA channel,priority and handle. */
    DMA_EnableChannel(EXAMPLE_DMA, EXAMPLE_SPI_MASTER_TX_CHANNEL);
    DMA_EnableChannel(EXAMPLE_DMA, EXAMPLE_SPI_MASTER_RX_CHANNEL);
    DMA_SetChannelPriority(EXAMPLE_DMA, EXAMPLE_SPI_MASTER_TX_CHANNEL, kDMA_ChannelPriority3);
    DMA_SetChannelPriority(EXAMPLE_DMA, EXAMPLE_SPI_MASTER_RX_CHANNEL, kDMA_ChannelPriority2);
    DMA_CreateHandle(&masterTxHandle, EXAMPLE_DMA, EXAMPLE_SPI_MASTER_TX_CHANNEL);
    DMA_CreateHandle(&masterRxHandle, EXAMPLE_DMA, EXAMPLE_SPI_MASTER_RX_CHANNEL);
}

static void EXAMPLE_MasterStartDMATransfer(void)
{
    spi_transfer_t masterXfer;
    uint32_t i = 0U;

    /* Set up the transfer data */
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        /* SPI is configured for 8 bits transfer - set only lower 8 bits of buffers */
        masterTxData[i] = i % 256U;
        masterRxData[i] = 0U;
    }

    /* Set up handle for spi master */
    SPI_MasterTransferCreateHandleDMA(EXAMPLE_SPI_MASTER, &masterHandle, SPI_MasterUserCallback, NULL, &masterTxHandle,
                                      &masterRxHandle);

    /* Start master transfer */
    masterXfer.txData      = (uint8_t *)&masterTxData;
    masterXfer.rxData      = (uint8_t *)&masterRxData;
    masterXfer.dataSize    = TRANSFER_SIZE * sizeof(masterTxData[0]);
    masterXfer.configFlags = kSPI_FrameAssert;

    if (kStatus_Success != SPI_MasterTransferDMA(EXAMPLE_SPI_MASTER, &masterHandle, &masterXfer))
    {
        PRINTF("There is an error when start SPI_MasterTransferDMA \r\n ");
    }
}

static void EXAMPLE_TransferDataCheck(void)
{
    uint32_t i = 0U, errorCount = 0U;

    /* Wait until transfer completed */
    while (!isTransferCompleted)
    {
    }

    PRINTF("\r\nThe received data are:");
    /*Check if the data is right*/
    for (i = 0; i < TRANSFER_SIZE; i++)
    {
        /* Print 16 numbers in a line */
        if ((i & 0x0FU) == 0U)
        {
            PRINTF("\r\n  ");
        }
        PRINTF("  0x%02X", masterRxData[i]);
        /* Check if data matched. */
        if (masterTxData[i] != masterRxData[i])
        {
            errorCount++;
        }
    }
    if (errorCount == 0)
    {
        PRINTF("\r\nSPI transfer all data matched! \r\n");
    }
    else
    {
        PRINTF("\r\nError occurred in SPI transfer ! \r\n");
    }
}
