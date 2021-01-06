/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* UART instance and clock */
#define EXAMPLE_I2C_MASTER_BASEADDR I2C0
#define EXAMPLE_I2C_SLAVE_BASEADDR  I2C1
#define I2C_MASTER_CLK_SRC          kCLOCK_BusClk
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(kCLOCK_BusClk)
#define I2C_SLAVE_CLK_SRC           kCLOCK_BusClk
#define I2C_SLAVE_CLK_FREQ          CLOCK_GetFreq(kCLOCK_BusClk)
#define I2C_MASTER_IRQ              I2C0_IRQn
#define I2C_SLAVE_IRQ               I2C1_IRQn
#define I2C_MASTER_IRQHandler       I2C0_IRQHandler
#define I2C_SLAVE_IRQHandler        I2C1_IRQHandler
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_BAUDRATE               100000U

#define I2C_DATA_LENGTH 32U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile uint8_t g_slave_buff[I2C_DATA_LENGTH];
volatile uint8_t g_master_buff[I2C_DATA_LENGTH];
volatile uint8_t g_masterTxIndex = 0;
volatile uint8_t g_masterRxIndex = 0xFFU;
volatile uint8_t g_slaveTxIndex  = 0xFFU;
volatile uint8_t g_slaveRxIndex  = 0;
volatile bool g_masterReadBegin  = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void I2C_MASTER_IRQHandler(void)
{
    uint8_t tmpdata;
    /* Clear pending flag. */
    EXAMPLE_I2C_MASTER_BASEADDR->S = kI2C_IntPendingFlag;

    if (g_masterReadBegin)
    {
        /* Change direction to read direction and automatically send ACK. */
        EXAMPLE_I2C_MASTER_BASEADDR->C1 &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

        /* Read dummy to free the bus. */
        EXAMPLE_I2C_MASTER_BASEADDR->D;

        g_masterReadBegin = false;

        return;
    }

    /* If tx Index < I2C_DATA_LENGTH, master send->slave receive transfer is ongoing. */
    if (g_masterTxIndex < I2C_DATA_LENGTH)
    {
        EXAMPLE_I2C_MASTER_BASEADDR->D = g_master_buff[g_masterTxIndex];
        g_masterTxIndex++;
    }

    /* If rx Index < I2C_DATA_LENGTH, master receive->slave send transfer is ongoing. */
    if (g_masterRxIndex < I2C_DATA_LENGTH)
    {
        /* Send STOP after receiving the last byte. */
        if (g_masterRxIndex == (I2C_DATA_LENGTH - 1U))
        {
            I2C_MasterStop(EXAMPLE_I2C_MASTER_BASEADDR);
        }

        tmpdata                        = EXAMPLE_I2C_MASTER_BASEADDR->D;
        g_master_buff[g_masterRxIndex] = tmpdata;
        g_masterRxIndex++;

        /* Send NAK at the last byte. */
        if (g_masterRxIndex == (I2C_DATA_LENGTH - 1U))
        {
            EXAMPLE_I2C_MASTER_BASEADDR->C1 |= I2C_C1_TXAK_MASK;
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

void I2C_SLAVE_IRQHandler(void)
{
    uint8_t tmpdata;
    uint8_t status = I2C_SlaveGetStatusFlags(EXAMPLE_I2C_SLAVE_BASEADDR);

    /* Clear pending flag. */
    EXAMPLE_I2C_SLAVE_BASEADDR->S = kI2C_IntPendingFlag;

    if (status & kI2C_AddressMatchFlag)
    {
        /* Slave transmit, master reading from slave. */
        if (status & kI2C_TransferDirectionFlag)
        {
            /* Change direction to send data. */
            EXAMPLE_I2C_SLAVE_BASEADDR->C1 |= I2C_C1_TX_MASK;

            /* Start to send data in tx buffer. */
            g_slaveTxIndex = 0;
        }
        else
        {
            /* Slave receive, master writing to slave. */
            EXAMPLE_I2C_SLAVE_BASEADDR->C1 &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

            /* Read dummy to free the bus. */
            EXAMPLE_I2C_SLAVE_BASEADDR->D;

            return;
        }
    }

    if (g_slaveTxIndex == I2C_DATA_LENGTH)
    {
        /* Change to RX mode when send out all data in tx buffer. */
        EXAMPLE_I2C_SLAVE_BASEADDR->C1 &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

        /* Read dummy to release bus. */
        EXAMPLE_I2C_SLAVE_BASEADDR->D;
    }

    /* If tx Index < I2C_DATA_LENGTH, master receive->slave send transfer is ongoing. */
    if (g_slaveTxIndex < I2C_DATA_LENGTH)
    {
        EXAMPLE_I2C_SLAVE_BASEADDR->D = g_slave_buff[g_slaveTxIndex];
        g_slaveTxIndex++;
    }

    /* If rx Index < I2C_DATA_LENGTH, slave receive->master send transfer is ongoing. */
    if (g_slaveRxIndex < I2C_DATA_LENGTH)
    {
        /* Send NAK at the last byte. */
        if (g_slaveRxIndex == (I2C_DATA_LENGTH - 1U))
        {
            EXAMPLE_I2C_SLAVE_BASEADDR->C1 |= I2C_C1_TXAK_MASK;
        }

        tmpdata                      = EXAMPLE_I2C_SLAVE_BASEADDR->D;
        g_slave_buff[g_slaveRxIndex] = tmpdata;
        g_slaveRxIndex++;
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t tmpmasterdata;
    uint8_t tmpslavedata;
    i2c_slave_config_t slaveConfig;

    i2c_master_config_t masterConfig;
    uint32_t sourceClock;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nI2C example -- MasterFunctionalInterrupt_SlaveFunctionalInterrupt.\r\n");

    /*  Enable master and slave NVIC interrupt. */
    EnableIRQ(I2C_MASTER_IRQ);
    EnableIRQ(I2C_SLAVE_IRQ);

    /* Set i2c slave interrupt priority higher. */
    NVIC_SetPriority(I2C_SLAVE_IRQ, 0);
    NVIC_SetPriority(I2C_MASTER_IRQ, 1);

    /*1.Set up i2c slave first*/
    /*
     * slaveConfig.addressingMode = kI2C_Address7bit;
     * slaveConfig.enableGeneralCall = false;
     * slaveConfig.enableWakeUp = false;
     * slaveConfig.enableBaudRateCtl = false;
     * slaveConfig.enableSlave = true;
     */
    I2C_SlaveGetDefaultConfig(&slaveConfig);

    slaveConfig.addressingMode = kI2C_Address7bit;
    slaveConfig.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;

    I2C_SlaveInit(EXAMPLE_I2C_SLAVE_BASEADDR, &slaveConfig, I2C_SLAVE_CLK_FREQ);

    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        g_slave_buff[i] = 0;
    }

    /*2.Set up i2c master to send data to slave*/
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        g_master_buff[i] = i;
    }

    PRINTF("Master will send data :");
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_buff[i]);
    }
    PRINTF("\r\n\r\n");

    /*
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.enableStopHold = false;
     * masterConfig.glitchFilterWidth = 0U;
     * masterConfig.enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = I2C_BAUDRATE;

    sourceClock = I2C_MASTER_CLK_FREQ;

    I2C_MasterInit(EXAMPLE_I2C_MASTER_BASEADDR, &masterConfig, sourceClock);

    /* Master send address to slave. */
    I2C_MasterStart(EXAMPLE_I2C_MASTER_BASEADDR, I2C_MASTER_SLAVE_ADDR_7BIT, kI2C_Write);

    /* Enable module interrupt. */
    I2C_EnableInterrupts(EXAMPLE_I2C_MASTER_BASEADDR, kI2C_GlobalInterruptEnable);
    I2C_EnableInterrupts(EXAMPLE_I2C_SLAVE_BASEADDR, kI2C_GlobalInterruptEnable);

    /* Wait slave receive finished. */
    while (g_slaveRxIndex < I2C_DATA_LENGTH)
    {
    }

    /* Disable module interrupt. */
    I2C_DisableInterrupts(EXAMPLE_I2C_MASTER_BASEADDR, kI2C_GlobalInterruptEnable);
    I2C_DisableInterrupts(EXAMPLE_I2C_SLAVE_BASEADDR, kI2C_GlobalInterruptEnable);

    /* Master send stop command. */
    I2C_MasterStop(EXAMPLE_I2C_MASTER_BASEADDR);

    /*3.Transfer completed. Check the data.*/
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        tmpmasterdata = g_master_buff[i];
        tmpslavedata  = g_slave_buff[i];
        if (tmpslavedata != tmpmasterdata)
        {
            PRINTF("\r\nError occurred in this transfer ! \r\n");
            break;
        }
    }

    PRINTF("Slave received data :");
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_slave_buff[i]);
    }
    PRINTF("\r\n\r\n");

    /*4.Set up slave ready to send data to master.*/
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        g_slave_buff[i] = ~g_slave_buff[i];
    }

    PRINTF("This time , slave will send data: :");
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_slave_buff[i]);
    }
    PRINTF("\r\n\r\n");

    /*  Already setup the slave transfer ready in item 1. */

    /* 5.Set up master to receive data from slave. */

    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        g_master_buff[i] = 0;
    }

    /* Master send address to slave. */
    I2C_MasterStart(EXAMPLE_I2C_MASTER_BASEADDR, I2C_MASTER_SLAVE_ADDR_7BIT, kI2C_Read);

    /* Enable module interrupt. */
    I2C_EnableInterrupts(EXAMPLE_I2C_MASTER_BASEADDR, kI2C_GlobalInterruptEnable);
    I2C_EnableInterrupts(EXAMPLE_I2C_SLAVE_BASEADDR, kI2C_GlobalInterruptEnable);

    g_masterReadBegin = true;

    /* Master put receive data in receive buffer. */
    g_masterRxIndex = 0;

    /* Wait master receive finished. */
    while (g_masterRxIndex < I2C_DATA_LENGTH)
    {
    }

    /* Disable module interrupt. */
    I2C_DisableInterrupts(EXAMPLE_I2C_MASTER_BASEADDR, kI2C_GlobalInterruptEnable);
    I2C_DisableInterrupts(EXAMPLE_I2C_SLAVE_BASEADDR, kI2C_GlobalInterruptEnable);

    /*6.Transfer completed. Check the data.*/
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        tmpmasterdata = g_master_buff[i];
        tmpslavedata  = g_slave_buff[i];
        if (tmpslavedata != tmpmasterdata)
        {
            PRINTF("\r\nError occurred in the transfer ! \r\n");
            break;
        }
    }

    PRINTF("Master received data :");
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_buff[i]);
    }
    PRINTF("\r\n\r\n");

    PRINTF("\r\nEnd of I2C example .\r\n");
    while (1)
    {
    }
}
