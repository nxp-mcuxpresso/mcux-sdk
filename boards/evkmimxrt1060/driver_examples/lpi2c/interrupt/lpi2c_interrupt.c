/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_LPI2C_MASTER_BASEADDR LPI2C1
#define EXAMPLE_LPI2C_SLAVE_BASEADDR  LPI2C3

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

#define LPI2C_MASTER_CLOCK_FREQUENCY LPI2C_CLOCK_FREQUENCY
#define LPI2C_SLAVE_CLOCK_FREQUENCY  LPI2C_CLOCK_FREQUENCY

#define LPI2C_MASTER_IRQ LPI2C1_IRQn
#define LPI2C_SLAVE_IRQ  LPI2C3_IRQn

#define LPI2C_MASTER_IRQHandler LPI2C1_IRQHandler
#define LPI2C_SLAVE_IRQHandler  LPI2C3_IRQHandler
#define LPI2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define LPI2C_BAUDRATE               100000U
#define LPI2C_DATA_LENGTH            32U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_slave_buff[LPI2C_DATA_LENGTH]  = {0};
uint8_t g_master_buff[LPI2C_DATA_LENGTH] = {0};
volatile uint8_t g_masterTxIndex         = 0U;
volatile uint8_t g_masterRxIndex         = 0U;
volatile uint8_t g_slaveTxIndex          = 0U;
volatile uint8_t g_slaveRxIndex          = 0U;
volatile bool g_masterReadBegin          = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void LPI2C_MASTER_IRQHandler(void)
{
    uint32_t flags = 0U;
    status_t reVal = kStatus_Fail;
    /* Get interrupt status flags */
    flags = LPI2C_MasterGetStatusFlags(EXAMPLE_LPI2C_MASTER_BASEADDR);

    if (flags & kLPI2C_MasterTxReadyFlag)
    {
        /* If tx Index < LPI2C_DATA_LENGTH, master send->slave receive transfer is ongoing. */
        if (g_masterTxIndex < LPI2C_DATA_LENGTH)
        {
            reVal = LPI2C_MasterSend(EXAMPLE_LPI2C_MASTER_BASEADDR, &g_master_buff[g_masterTxIndex++], 1);
            if (reVal != kStatus_Success)
            {
                return;
            }
            /* The last byte */
            if (g_masterTxIndex == LPI2C_DATA_LENGTH)
            {
                /* Master send stop command. */
                reVal = LPI2C_MasterStop(EXAMPLE_LPI2C_MASTER_BASEADDR);
                if (reVal != kStatus_Success)
                {
                    return;
                }
                /* Disable master Tx interrupt otherwise the Tx interrupt will always works */
                LPI2C_MasterDisableInterrupts(EXAMPLE_LPI2C_MASTER_BASEADDR, kLPI2C_MasterTxReadyFlag);
            }
        }
    }

    if (flags & kLPI2C_MasterRxReadyFlag)
    {
        /* If rx Index < LPI2C_DATA_LENGTH, master receive->slave send transfer is ongoing. */
        if (g_masterRxIndex < LPI2C_DATA_LENGTH)
        {
            g_master_buff[g_masterRxIndex++] = EXAMPLE_LPI2C_MASTER_BASEADDR->MRDR;
            if (g_masterRxIndex == LPI2C_DATA_LENGTH - 1U)
            {
                /* Master send stop command. */
                reVal = LPI2C_MasterStop(EXAMPLE_LPI2C_MASTER_BASEADDR);
                if (reVal != kStatus_Success)
                {
                    return;
                }
                /* Disable master Rx interrupt otherwise the Rx interrupt will always works */
                LPI2C_MasterDisableInterrupts(EXAMPLE_LPI2C_MASTER_BASEADDR, kLPI2C_MasterTxReadyFlag);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

void LPI2C_SLAVE_IRQHandler(void)
{
    uint32_t flags = 0U;

    /* Get interrupt status flags. */
    flags = LPI2C_SlaveGetStatusFlags(EXAMPLE_LPI2C_SLAVE_BASEADDR);

    if (flags & kLPI2C_SlaveAddressValidFlag)
    {
        /* Release the i2c bus */
        EXAMPLE_LPI2C_SLAVE_BASEADDR->SASR;
        return;
    }

    if (flags & kLPI2C_SlaveRxReadyFlag)
    {
        /* If rx Index < LPI2C_DATA_LENGTH, slave receive->master send transfer is ongoing. */
        if (g_slaveRxIndex < LPI2C_DATA_LENGTH)
        {
            /* Send NACK at the last byte. */
            if (g_slaveRxIndex == (LPI2C_DATA_LENGTH - 1U))
            {
                EXAMPLE_LPI2C_SLAVE_BASEADDR->STAR = LPI2C_STAR_TXNACK_MASK;
            }

            g_slave_buff[g_slaveRxIndex++] = EXAMPLE_LPI2C_SLAVE_BASEADDR->SRDR;

            if (g_slaveRxIndex == LPI2C_DATA_LENGTH)
            {
                LPI2C_SlaveDisableInterrupts(EXAMPLE_LPI2C_SLAVE_BASEADDR,
                                             kLPI2C_SlaveRxReadyFlag | kLPI2C_SlaveAddressValidFlag);
            }
        }
    }

    if (flags & kLPI2C_SlaveTxReadyFlag)
    {
        /* If rx Index < LPI2C_DATA_LENGTH, slave send->master receive transfer is ongoing. */
        if (g_slaveTxIndex < LPI2C_DATA_LENGTH)
        {
            EXAMPLE_LPI2C_SLAVE_BASEADDR->STDR = g_slave_buff[g_slaveTxIndex++];

            if (g_slaveTxIndex == LPI2C_DATA_LENGTH)
            {
                LPI2C_SlaveDisableInterrupts(EXAMPLE_LPI2C_SLAVE_BASEADDR,
                                             kLPI2C_SlaveTxReadyFlag | kLPI2C_SlaveAddressValidFlag);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    lpi2c_slave_config_t slaveConfig   = {0};
    lpi2c_master_config_t masterConfig = {0};
    status_t reVal                     = kStatus_Fail;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);

    PRINTF("\r\nLPI2C example -- MasterFunctionalInterrupt_SlaveFunctionalInterrupt.\r\n");

    /*  Enable master and slave NVIC interrupt. */
    EnableIRQ(LPI2C_MASTER_IRQ);
    EnableIRQ(LPI2C_SLAVE_IRQ);

    /* Set lpi2c slave interrupt priority higher. */
    NVIC_SetPriority(LPI2C_SLAVE_IRQ, 0);
    NVIC_SetPriority(LPI2C_MASTER_IRQ, 1);

    /* 1.Set up lpi2c slave first */
    /*
     * slaveConfig.address0 = 0U;
     * slaveConfig.address1 = 0U;
     * slaveConfig.addressMatchMode = kLPI2C_MatchAddress0;
     * slaveConfig.filterDozeEnable = true;
     * slaveConfig.filterEnable = true;
     * slaveConfig.enableGeneralCall = false;
     * slaveConfig.ignoreAck = false;
     * slaveConfig.enableReceivedAddressRead = false;
     * slaveConfig.sdaGlitchFilterWidth_ns = 0;
     * slaveConfig.sclGlitchFilterWidth_ns = 0;
     * slaveConfig.dataValidDelay_ns = 0;
     * slaveConfig.clockHoldTime_ns = 0;
     */
    LPI2C_SlaveGetDefaultConfig(&slaveConfig);
    slaveConfig.address0 = LPI2C_MASTER_SLAVE_ADDR_7BIT;

    LPI2C_SlaveInit(EXAMPLE_LPI2C_SLAVE_BASEADDR, &slaveConfig, LPI2C_SLAVE_CLOCK_FREQUENCY);

    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        g_slave_buff[i] = 0;
    }

    /* 2.Set up lpi2c master to send data to slave */
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        g_master_buff[i] = i;
    }

    PRINTF("Master will send data :");
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_buff[i]);
    }
    PRINTF("\r\n\r\n");

    /* Setup lpi2c master */
    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = LPI2C_BAUDRATE;

    LPI2C_MasterInit(EXAMPLE_LPI2C_MASTER_BASEADDR, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY);

    /* Master start and send address to slave. */
    reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, LPI2C_MASTER_SLAVE_ADDR_7BIT, kLPI2C_Write);
    if (reVal != kStatus_Success)
    {
        return -1;
    }
    /* Enable module interrupt. */
    LPI2C_MasterEnableInterrupts(EXAMPLE_LPI2C_MASTER_BASEADDR, kLPI2C_MasterTxReadyFlag);
    LPI2C_SlaveEnableInterrupts(EXAMPLE_LPI2C_SLAVE_BASEADDR, kLPI2C_SlaveRxReadyFlag | kLPI2C_SlaveAddressValidFlag);

    /* Wait slave receive finished. */
    while (g_slaveRxIndex < LPI2C_DATA_LENGTH)
    {
    }

    /* 3.Transfer completed. Check the data. */
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        if (g_slave_buff[i] != g_master_buff[i])
        {
            PRINTF("\r\nError occurred in this transfer ! \r\n");
            break;
        }
    }

    PRINTF("Slave received data :");
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_slave_buff[i]);
    }
    PRINTF("\r\n\r\n");

    /* 4.Set up slave ready to send data to master. */
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        g_slave_buff[i] = ~g_slave_buff[i];
    }

    PRINTF("This time , slave will send data: ");
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_slave_buff[i]);
    }
    PRINTF("\r\n\r\n");

    /* 5.Set up master to receive data from slave. */
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        g_master_buff[i] = 0;
    }

    /* Master start and send address to slave. */
    reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, LPI2C_MASTER_SLAVE_ADDR_7BIT, kLPI2C_Read);
    if (reVal != kStatus_Success)
    {
        return -1;
    }
    /* Set command to receive data so that the master will send a NACK when received enough data */
    EXAMPLE_LPI2C_MASTER_BASEADDR->MTDR = LPI2C_MTDR_CMD(0X1U) | LPI2C_MTDR_DATA(LPI2C_DATA_LENGTH - 1);

    LPI2C_MasterEnableInterrupts(EXAMPLE_LPI2C_MASTER_BASEADDR, kLPI2C_MasterRxReadyFlag);
    LPI2C_SlaveEnableInterrupts(EXAMPLE_LPI2C_SLAVE_BASEADDR, kLPI2C_SlaveTxReadyFlag | kLPI2C_SlaveAddressValidFlag);

    /* Wait master receive finished. */
    while (g_masterRxIndex < LPI2C_DATA_LENGTH)
    {
    }
    /* 6.Transfer completed. Check the data. */
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        if (g_slave_buff[i] != g_master_buff[i])
        {
            PRINTF("\r\nError occurred in the transfer ! \r\n");
            break;
        }
    }

    PRINTF("Master received data :");
    for (uint32_t i = 0U; i < LPI2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_buff[i]);
    }
    PRINTF("\r\n\r\n");

    PRINTF("\r\nEnd of LPI2C example .\r\n");
    while (1)
    {
    }
}
