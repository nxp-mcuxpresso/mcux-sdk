/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_dspi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_DSPI_MASTER_BASEADDR   SPI0
#define EXAMPLE_DSPI_MASTER_CLK_SRC    DSPI0_CLK_SRC
#define EXAMPLE_DSPI_MASTER_CLK_FREQ   CLOCK_GetFreq(DSPI0_CLK_SRC)
#define EXAMPLE_DSPI_MASTER_PCS        kDSPI_Pcs0
#define EXAMPLE_DSPI_MASTER_IRQ        SPI0_IRQn
#define EXAMPLE_DSPI_MASTER_IRQHandler SPI0_IRQHandler

#define EXAMPLE_DSPI_DEALY_COUNT 0XFFFFFU
#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t masterRxData[TRANSFER_SIZE] = {0U};
uint8_t masterTxData[TRANSFER_SIZE] = {0U};

volatile uint32_t masterTxCount;
volatile uint32_t masterRxCount;
volatile uint32_t masterCommand;
uint32_t masterFifoSize;

volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void EXAMPLE_DSPI_MASTER_IRQHandler(void)
{
    uint32_t tmpmasterTxCount = masterTxCount;
    uint32_t tmpmasterRxCount = masterRxCount;
    uint32_t tmpmasterCommand = masterCommand;

    if (tmpmasterRxCount < TRANSFER_SIZE)
    {
        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_RxFifoDrainRequestFlag)
        {
            masterRxData[tmpmasterRxCount] = DSPI_ReadData(EXAMPLE_DSPI_MASTER_BASEADDR);
            ++masterRxCount;
            tmpmasterRxCount = masterRxCount;

            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_RxFifoDrainRequestFlag);

            if (tmpmasterRxCount == TRANSFER_SIZE)
            {
                break;
            }
        }
    }

    if (tmpmasterTxCount < TRANSFER_SIZE)
    {
        while ((DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_TxFifoFillRequestFlag) &&
               ((tmpmasterTxCount - tmpmasterRxCount) < masterFifoSize))
        {
            if (tmpmasterTxCount < TRANSFER_SIZE)
            {
                EXAMPLE_DSPI_MASTER_BASEADDR->PUSHR = tmpmasterCommand | masterTxData[tmpmasterTxCount];
                ++masterTxCount;
                tmpmasterTxCount = masterTxCount;
            }
            else
            {
                break;
            }

            /* Try to clear the TFFF; if the TX FIFO is full this will clear */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }
    }

    /* Check if we're done with this transfer.*/
    if ((tmpmasterTxCount == TRANSFER_SIZE) && (tmpmasterRxCount == TRANSFER_SIZE))
    {
        isTransferCompleted = true;
        /* Complete the transfer and disable the interrupts */
        DSPI_DisableInterrupts(EXAMPLE_DSPI_MASTER_BASEADDR,
                               kDSPI_RxFifoDrainRequestInterruptEnable | kDSPI_TxFifoFillRequestInterruptEnable);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("dspi_functional_interrupt_board2board_master start.\r\n");
    PRINTF("This example use one board as master and another as slave.\r\n");
    PRINTF("Master and slave uses interrupt way. Slave should start first. \r\n");
    PRINTF("Please make sure you make the correct line connection. Basically, the connection is: \r\n");
    PRINTF("DSPI_master -- DSPI_slave   \r\n");
    PRINTF("   CLK      --    CLK  \r\n");
    PRINTF("   PCS      --    PCS \r\n");
    PRINTF("   SOUT     --    SIN  \r\n");
    PRINTF("   SIN      --    SOUT \r\n");
    PRINTF("   GND      --    GND \r\n");

    uint32_t srcClock_Hz;
    uint32_t errorCount;
    uint32_t loopCount = 1;
    uint32_t i;
    dspi_master_config_t masterConfig;

    /* Master config */
    masterConfig.whichCtar                                = kDSPI_Ctar0;
    masterConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.bitsPerFrame                  = 8U;
    masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
    masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;

    masterConfig.whichPcs           = EXAMPLE_DSPI_MASTER_PCS;
    masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

    masterConfig.enableContinuousSCK        = false;
    masterConfig.enableRxFifoOverWrite      = false;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

    srcClock_Hz = EXAMPLE_DSPI_MASTER_CLK_FREQ;
    DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);

    /* Enable the NVIC for DSPI peripheral. */
    EnableIRQ(EXAMPLE_DSPI_MASTER_IRQ);

    dspi_command_data_config_t commandData;
    commandData.isPcsContinuous    = false;
    commandData.whichCtar          = kDSPI_Ctar0;
    commandData.whichPcs           = EXAMPLE_DSPI_MASTER_PCS;
    commandData.isEndOfQueue       = false;
    commandData.clearTransferCount = false;

    masterCommand  = DSPI_MasterGetFormattedCommand(&commandData);
    masterFifoSize = FSL_FEATURE_DSPI_FIFO_SIZEn(EXAMPLE_DSPI_MASTER_BASEADDR);

    while (1)
    {
        /* Set up the transfer data */
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            masterTxData[i] = (i + loopCount) % 256U;
            masterRxData[i] = 0U;
        }

        /* Print out transmit buffer */
        PRINTF("\r\n Master transmit:\r\n");
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            /* Print 16 numbers in a line */
            if ((i & 0x0FU) == 0U)
            {
                PRINTF("\r\n");
            }
            PRINTF(" %02X", masterTxData[i]);
        }
        PRINTF("\r\n");

        /* 1st round , send TX data to slave*/
        masterTxCount = 0;
        masterRxCount = 0;

        isTransferCompleted = false;
        DSPI_StopTransfer(EXAMPLE_DSPI_MASTER_BASEADDR);
        DSPI_FlushFifo(EXAMPLE_DSPI_MASTER_BASEADDR, true, true);
        DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, (uint32_t)kDSPI_AllStatusFlag);

        /*Fill up the master Tx data*/
        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_TxFifoFillRequestFlag)
        {
            if (masterTxCount < TRANSFER_SIZE)
            {
                DSPI_MasterWriteData(EXAMPLE_DSPI_MASTER_BASEADDR, &commandData, masterTxData[masterTxCount]);
                ++masterTxCount;
            }
            else
            {
                break;
            }
            /* Try to clear the TFFF; if the TX FIFO is full this will clear */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }

        /*Enable master RX interrupt*/
        DSPI_EnableInterrupts(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_RxFifoDrainRequestInterruptEnable);
        DSPI_StartTransfer(EXAMPLE_DSPI_MASTER_BASEADDR);

        /* Wait 1st round transfer complete */
        while (!isTransferCompleted)
        {
        }

        /* Delay to wait slave is ready */
        for (i = 0; i < EXAMPLE_DSPI_DEALY_COUNT; i++)
        {
            __NOP();
        }

        /* Clear the RX data.*/
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            masterRxData[i] = 0U;
        }

        /* 2nd round , read RX data from slave*/
        masterTxCount       = 0;
        masterRxCount       = 0;
        isTransferCompleted = false;
        DSPI_StopTransfer(EXAMPLE_DSPI_MASTER_BASEADDR);
        DSPI_FlushFifo(EXAMPLE_DSPI_MASTER_BASEADDR, true, true);
        DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, (uint32_t)kDSPI_AllStatusFlag);

        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_TxFifoFillRequestFlag)
        {
            if (masterTxCount < TRANSFER_SIZE)
            {
                DSPI_MasterWriteData(EXAMPLE_DSPI_MASTER_BASEADDR, &commandData, masterTxData[masterTxCount]);
                ++masterTxCount;
            }
            else
            {
                break;
            }

            /* Try to clear the TFFF; if the TX FIFO is full this will clear */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }

        /*Enable master RX interrupt*/
        DSPI_EnableInterrupts(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_RxFifoDrainRequestInterruptEnable);
        DSPI_StartTransfer(EXAMPLE_DSPI_MASTER_BASEADDR);

        /* Wait 2nd round transfer complete */
        while (!isTransferCompleted)
        {
        }

        errorCount = 0U;
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            if (masterTxData[i] != masterRxData[i])
            {
                errorCount++;
            }
        }
        if (errorCount == 0U)
        {
            PRINTF(" \r\nDSPI transfer all data matched! \r\n");
            /* Print out receive buffer */
            PRINTF("\r\n Master received:\r\n");
            for (i = 0U; i < TRANSFER_SIZE; i++)
            {
                /* Print 16 numbers in a line */
                if ((i & 0x0FU) == 0U)
                {
                    PRINTF("\r\n");
                }
                PRINTF(" %02X", masterRxData[i]);
            }
            PRINTF("\r\n");
        }
        else
        {
            PRINTF(" \r\nError occurred in DSPI transfer ! \r\n");
        }

        /* Wait for press any key */
        PRINTF("\r\n Press any key to run again\r\n");
        GETCHAR();

        /* Increase loop count to change transmit buffer */
        loopCount++;
    }
}
