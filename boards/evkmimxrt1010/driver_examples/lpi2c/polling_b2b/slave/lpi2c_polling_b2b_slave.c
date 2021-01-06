/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <stdio.h>
#include <string.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_I2C_SLAVE_BASE (LPI2C1_BASE)

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

#define LPI2C_SLAVE_CLOCK_FREQUENCY LPI2C_CLOCK_FREQUENCY


#define EXAMPLE_I2C_SLAVE ((LPI2C_Type *)EXAMPLE_I2C_SLAVE_BASE)

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_DATA_LENGTH            34U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_slave_buff[I2C_DATA_LENGTH];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    lpi2c_slave_config_t slaveConfig;
    status_t reVal = kStatus_Fail;
    uint8_t subaddress;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);

    PRINTF("\r\nLPI2C board2board polling example -- Slave transfer.\r\n\r\n");

    /* Set up i2c slave first */
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

    /* Change the slave address */
    slaveConfig.address0 = I2C_MASTER_SLAVE_ADDR_7BIT;

    /* Initialize the LPI2C slave peripheral */
    LPI2C_SlaveInit(EXAMPLE_I2C_SLAVE, &slaveConfig, LPI2C_SLAVE_CLOCK_FREQUENCY);

    memset(g_slave_buff, 0, sizeof(g_slave_buff));

    /* Wait until being visited by master before slave polling transfer */
    while (!(LPI2C_SlaveGetStatusFlags(EXAMPLE_I2C_SLAVE) & kLPI2C_SlaveAddressValidFlag))
    {
    }
    /* Clear being visited flag */
    LPI2C_SlaveGetReceivedAddress(EXAMPLE_I2C_SLAVE);

    /* Start accepting I2C transfers on the LPI2C slave peripheral */
    reVal = LPI2C_SlaveReceive(EXAMPLE_I2C_SLAVE, g_slave_buff, I2C_DATA_LENGTH, 0);

    if (reVal != kStatus_Success)
    {
        return -1;
    }

    /* Wait until being visited by master before slave polling transfer */
    while (!(LPI2C_SlaveGetStatusFlags(EXAMPLE_I2C_SLAVE) & kLPI2C_SlaveAddressValidFlag))
    {
    }
    /* Clear being visited flag */
    LPI2C_SlaveGetReceivedAddress(EXAMPLE_I2C_SLAVE);

    /* Start accepting I2C transfers on the LPI2C slave peripheral to simulate subaddress and will send ACK to master */
    reVal = LPI2C_SlaveReceive(EXAMPLE_I2C_SLAVE, &subaddress, 1, 0);

    if (reVal != kStatus_Success)
    {
        return -1;
    }

    /* Wait until being visited by master before slave polling transfer */
    while (!(LPI2C_SlaveGetStatusFlags(EXAMPLE_I2C_SLAVE) & kLPI2C_SlaveAddressValidFlag))
    {
    }
    /* Clear being visited flag */
    LPI2C_SlaveGetReceivedAddress(EXAMPLE_I2C_SLAVE);

    reVal = LPI2C_SlaveSend(EXAMPLE_I2C_SLAVE, &g_slave_buff[2], g_slave_buff[1], 0);

    if (reVal != kStatus_Success)
    {
        return -1;
    }

    PRINTF("Slave received data :");
    for (uint32_t i = 0U; i < g_slave_buff[1]; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_slave_buff[2 + i]);
    }
    PRINTF("\r\n\r\n");

    PRINTF("\r\nEnd of LPI2C example .\r\n");

    while (1)
    {
    }
}
