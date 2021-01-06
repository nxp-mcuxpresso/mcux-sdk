/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SPI_SLAVE     SPI0
#define EXAMPLE_SPI_SLAVE_IRQ SPI0_IRQn
#define SPI_SLAVE_IRQHandler  SPI0_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define BUFFER_SIZE (64)
static uint8_t srcBuff[BUFFER_SIZE];
static uint8_t destBuff[BUFFER_SIZE];
static uint32_t txIndex            = BUFFER_SIZE;
static uint32_t rxIndex            = BUFFER_SIZE;
static volatile bool slaveFinished = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void SPI_SLAVE_IRQHandler(void)
{
    if ((SPI_GetStatusFlags(EXAMPLE_SPI_SLAVE) & kSPI_RxBufferFullFlag) && (rxIndex > 0U))
    {
        destBuff[BUFFER_SIZE - rxIndex] = SPI_ReadData(EXAMPLE_SPI_SLAVE);
        rxIndex--;
    }

    if ((SPI_GetStatusFlags(EXAMPLE_SPI_SLAVE) & kSPI_TxBufferEmptyFlag) && (txIndex > 0U))
    {
        SPI_WriteData(EXAMPLE_SPI_SLAVE, (uint16_t)(srcBuff[BUFFER_SIZE - txIndex]));
        txIndex--;
    }

    if ((rxIndex == 0U) && (txIndex == 0U))
    {
        slaveFinished = true;
        SPI_DisableInterrupts(EXAMPLE_SPI_SLAVE, kSPI_RxFullAndModfInterruptEnable | kSPI_TxEmptyInterruptEnable);
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    spi_slave_config_t slaveConfig = {0};
    uint32_t i                     = 0U;
    uint32_t err                   = 0U;

    /* Init the boards */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nSPI board to board interrupt slave example started!\r\n");

    /* Init SPI slave */
    /*
     * slaveConfig->polarity = kSPI_ClockPolarityActiveHigh;
     * slaveConfig->phase = kSPI_ClockPhaseFirstEdge;
     * slaveConfig->direction = kSPI_MsbFirst;
     * slaveConfig->enableStopInWaitMode = false;
     * slaveConfig->dataMode = kSPI_8BitMode;
     * slaveConfig->txWatermark = kSPI_TxFifoOneHalfEmpty;
     * slaveConfig->rxWatermark = kSPI_RxFifoOneHalfFull;
     */
    SPI_SlaveGetDefaultConfig(&slaveConfig);
    SPI_SlaveInit(EXAMPLE_SPI_SLAVE, &slaveConfig);

/* Disable FIFO */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && (FSL_FEATURE_SPI_HAS_FIFO)
    SPI_EnableFIFO(EXAMPLE_SPI_SLAVE, false);
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Init source buffer */
    for (i = 0U; i < BUFFER_SIZE; i++)
    {
        srcBuff[i] = i;
    }

    /* Enable interrupt, first enable slave and then master. */
    EnableIRQ(EXAMPLE_SPI_SLAVE_IRQ);
    SPI_EnableInterrupts(EXAMPLE_SPI_SLAVE, kSPI_RxFullAndModfInterruptEnable | kSPI_TxEmptyInterruptEnable);

    while (slaveFinished != true)
    {
    }

    /* Check the data received */
    for (i = 0U; i < BUFFER_SIZE; i++)
    {
        if (destBuff[i] != srcBuff[i])
        {
            PRINTF("\r\nThe %d data is wrong, the data received is %d \r\n", i, destBuff[i]);
            err++;
        }
    }
    if (err == 0U)
    {
        PRINTF("\r\nSPI transfer finished!\r\n");
    }

    while (1)
    {
    }
}
