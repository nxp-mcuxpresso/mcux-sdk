/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_ecspi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ECSPI_TRANSFER_SIZE     64
#define ECSPI_TRANSFER_BAUDRATE 500000U
#define ECSPI_MASTER_BASEADDR   ECSPI2
#define ECSPI_MASTER_CLK_FREQ                                                                 \
    (CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootEcspi2)) / \
     (CLOCK_GetRootPostDivider(kCLOCK_RootEcspi2)))
#define ECSPI_MASTER_TRANSFER_CHANNEL kECSPI_Channel0

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t i;
    ecspi_transfer_t masterXfer;
    ecspi_master_config_t masterConfig;
    uint32_t masterRxData[ECSPI_TRANSFER_SIZE] = {0};
    uint32_t masterTxData[ECSPI_TRANSFER_SIZE] = {0};

    /* Init board hardware. */
    /* M7 has its local cache and enabled by default,
     * need to set smart subsystems (0x28000000 ~ 0x3FFFFFFF)
     * non-cacheable before accessing this address region */
    BOARD_InitMemory();

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_SetRootMux(kCLOCK_RootEcspi2, kCLOCK_EcspiRootmuxSysPll1); /* Set ECSPI2 source to SYSTEM PLL1 800MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootEcspi2, 2U, 5U);                 /* Set root clock to 800MHZ / 10 = 80MHZ */

    PRINTF("\r\n***ECSPI Loopback Demo***\r\n");
    PRINTF("\r\nThis demo is a loopback transfer test for ECSPI.\r\n");
    PRINTF("The ECSPI will connect the transmitter and receiver sections internally.\r\n");
    PRINTF("So, there is no need to connect the MOSI and MISO pins.\r\n");

    /* Master config:
     * masterConfig.channel = kECSPI_Channel0;
     * masterConfig.burstLength = 8;
     * masterConfig.samplePeriodClock = kECSPI_spiClock;
     * masterConfig.baudRate_Bps = TRANSFER_BAUDRATE;
     * masterConfig.chipSelectDelay = 0;
     * masterConfig.samplePeriod = 0;
     * masterConfig.txFifoThreshold = 1;
     * masterConfig.rxFifoThreshold = 0;
     * masterConfig.enableLoopback = true;
     */
    ECSPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps   = ECSPI_TRANSFER_BAUDRATE;
    masterConfig.enableLoopback = true;
    ECSPI_MasterInit(ECSPI_MASTER_BASEADDR, &masterConfig, ECSPI_MASTER_CLK_FREQ);

    for (i = 0; i < ECSPI_TRANSFER_SIZE; i++)
    {
        masterTxData[i] = i;
    }
    /*Start master transfer*/
    masterXfer.txData   = masterTxData;
    masterXfer.rxData   = masterRxData;
    masterXfer.dataSize = ECSPI_TRANSFER_SIZE;
    masterXfer.channel  = ECSPI_MASTER_TRANSFER_CHANNEL;
    ECSPI_MasterTransferBlocking(ECSPI_MASTER_BASEADDR, &masterXfer);

    /* Compare Tx and Rx data. */
    for (i = 0; i < ECSPI_TRANSFER_SIZE; i++)
    {
        if (masterTxData[i] != masterRxData[i])
        {
            break;
        }
    }

    if (ECSPI_TRANSFER_SIZE == i)
    {
        PRINTF("\r\nECSPI loopback test pass!");
    }
    else
    {
        PRINTF("\r\nECSPI loopback test fail!");
    }

    /* Deinit the ECSPI. */
    ECSPI_Deinit(ECSPI_MASTER_BASEADDR);

    while (1)
    {
        __NOP();
    }
}
