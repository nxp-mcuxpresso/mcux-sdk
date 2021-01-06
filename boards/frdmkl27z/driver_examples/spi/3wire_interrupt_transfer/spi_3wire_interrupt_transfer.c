/*
 * Copyright 2017 NXP
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
#define EXAMPLE_SPI_MASTER              SPI0
#define EXAMPLE_SPI_SLAVE               SPI1
#define EXAMPLE_SPI_MASTER_SOURCE_CLOCK kCLOCK_BusClk
#define EXAMPLE_SPI_MASTER_CLK_FREQ     CLOCK_GetFreq(kCLOCK_BusClk)
#define EXAMPLE_SPI_SLAVE_SOURCE_CLOCK  kCLOCK_SysCoreClk
#define EXAMPLE_SPI_MASTER_IRQ          SPI0_IRQn
#define EXAMPLE_SPI_SLAVE_IRQ           SPI1_IRQn

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define BUFFER_SIZE (256)
static uint8_t masterTxBuff[BUFFER_SIZE];
static uint8_t masterRxBuff[BUFFER_SIZE];
static uint8_t slaveTxBuff[BUFFER_SIZE];
static uint8_t slaveRxBuff[BUFFER_SIZE];
static spi_master_handle_t masterHandle;
static spi_slave_handle_t slaveHandle;
static volatile bool masterFinished = false;
static volatile bool slaveFinished  = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
static void masterCallback(SPI_Type *base, spi_master_handle_t *handle, status_t status, void *userData)
{
    masterFinished = true;
}

static void slaveCallback(SPI_Type *base, spi_slave_handle_t *handle, status_t status, void *userData)
{
    slaveFinished = true;
}

int main(void)
{
    spi_master_config_t masterConfig = {0};
    spi_slave_config_t slaveConfig   = {0};
    spi_transfer_t xfer              = {0};
    uint32_t sourceClock             = 0U;
    uint32_t i                       = 0U;
    uint32_t err                     = 0U;

    /* Init the boards */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("SPI one board 3-wire interrupt transfer example started!\r\n");
    PRINTF("This example will use 3 wires for transmission.\r\n");
    PRINTF("For SPI master: MOSI pin is an I/O pin for master to transmit data or receive data.\r\n");
    PRINTF("For SPI slave: MISO pin is an I/O pin for slave to transmit data or receive data.\r\n");
    PRINTF("Please make sure you make the correct line connection. Basically, the connection is: \r\n");
    PRINTF(" SPI_master --  SPI_slave   \r\n");
    PRINTF("   CLK      --    CLK  \r\n");
    PRINTF("   PCS      --    PCS  \r\n");
    PRINTF("   MOSI     --    MISO  \r\n");

    PRINTF("\r\nSPI master starts to transmit data to slave.\r\n");
    /* Init SPI master */
    /*
     * masterConfig.enableStopInWaitMode = false;
     * masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
     * masterConfig.phase = kSPI_ClockPhaseFirstEdge;
     * masterConfig.direction = kSPI_MsbFirst;
     * masterConfig.dataMode = kSPI_8BitMode;
     * masterConfig.txWatermark = kSPI_TxFifoOneHalfEmpty;
     * masterConfig.rxWatermark = kSPI_RxFifoOneHalfFull;
     * masterConfig.outputMode = kSPI_SlaveSelectAutomaticOutput;
     * masterConfig.baudRate_Bps = 500000U;
     */
    SPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.pinMode = kSPI_PinModeOutput;
    sourceClock          = EXAMPLE_SPI_MASTER_CLK_FREQ;
    SPI_MasterInit(EXAMPLE_SPI_MASTER, &masterConfig, sourceClock);
    /* Create handle for SPI master */
    SPI_MasterTransferCreateHandle(EXAMPLE_SPI_MASTER, &masterHandle, masterCallback, NULL);

    /* Init SPI slave */
    /*
     * slaveConfig.polarity = kSPI_ClockPolarityActiveHigh;
     * slaveConfig.phase = kSPI_ClockPhaseFirstEdge;
     * slaveConfig.direction = kSPI_MsbFirst;
     * slaveConfig.enableStopInWaitMode = false;
     * slaveConfig.dataMode = kSPI_8BitMode;
     * slaveConfig.txWatermark = kSPI_TxFifoOneHalfEmpty;
     * slaveConfig.rxWatermark = kSPI_RxFifoOneHalfFull;
     */
    SPI_SlaveGetDefaultConfig(&slaveConfig);
    slaveConfig.pinMode = kSPI_PinModeInput;
    SPI_SlaveInit(EXAMPLE_SPI_SLAVE, &slaveConfig);
    SPI_SlaveTransferCreateHandle(EXAMPLE_SPI_SLAVE, &slaveHandle, slaveCallback, NULL);

    /* Set priority, slave have higher priority */
    NVIC_SetPriority(EXAMPLE_SPI_MASTER_IRQ, 1U);
    NVIC_SetPriority(EXAMPLE_SPI_SLAVE_IRQ, 0U);

    /* Init source buffer */
    for (i = 0U; i < BUFFER_SIZE; i++)
    {
        masterTxBuff[i] = i;
        masterRxBuff[i] = 0U;
        slaveTxBuff[i]  = ~masterTxBuff[i];
        slaveRxBuff[i]  = 0U;
    }

    /* SPI slave transfer */
    xfer.rxData   = slaveRxBuff;
    xfer.dataSize = BUFFER_SIZE;
    xfer.txData   = NULL;
    SPI_SlaveTransferNonBlocking(EXAMPLE_SPI_SLAVE, &slaveHandle, &xfer);

    /* SPI master start transfer */
    xfer.txData   = masterTxBuff;
    xfer.rxData   = NULL;
    xfer.dataSize = BUFFER_SIZE;
    SPI_MasterTransferNonBlocking(EXAMPLE_SPI_MASTER, &masterHandle, &xfer);

    while ((masterFinished != true) || (slaveFinished != true))
    {
    }

    PRINTF("\r\nSPI master transmit data completed!\r\n");
    PRINTF("SPI master starts to receive data from slave.\r\n");
    PRINTF("\r\nPlease input any character to continue the transmission.\r\n");
    GETCHAR();
    masterFinished = false;
    slaveFinished  = false;

    /* Set the pin mode: master -> input/slave -> ouput. */
    SPI_SetPinMode(EXAMPLE_SPI_MASTER, kSPI_PinModeInput);
    SPI_SetPinMode(EXAMPLE_SPI_SLAVE, kSPI_PinModeOutput);

    /* SPI slave transfer */
    xfer.rxData   = NULL;
    xfer.dataSize = BUFFER_SIZE;
    xfer.txData   = slaveTxBuff;
    SPI_SlaveTransferNonBlocking(EXAMPLE_SPI_SLAVE, &slaveHandle, &xfer);

    /* SPI master start transfer */
    xfer.txData   = NULL;
    xfer.rxData   = masterRxBuff;
    xfer.dataSize = BUFFER_SIZE;
    SPI_MasterTransferNonBlocking(EXAMPLE_SPI_MASTER, &masterHandle, &xfer);

    while ((masterFinished != true) || (slaveFinished != true))
    {
    }

    PRINTF("\r\nSPI master receive data completed!\r\n");
    /* Check the data received */
    for (i = 0U; i < BUFFER_SIZE; i++)
    {
        if (slaveRxBuff[i] != masterTxBuff[i])
        {
            PRINTF("\r\nThe %d data is wrong, the data slave received is %d \r\n", i, slaveRxBuff[i]);
            err++;
        }
        if (slaveTxBuff[i] != masterRxBuff[i])
        {
            PRINTF("\r\nThe %d data is wrong, the data master received is %d \r\n", i, masterRxBuff[i]);
            err++;
        }
    }
    if (err == 0U)
    {
        PRINTF("SPI transfer finished! All data matched!\r\n");
    }

    while (1)
    {
    }
}
