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

#include "fsl_gpio.h"
#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_I2C_SLAVE_BASE      ADMA__LPI2C1
#define LPI2C_SLAVE_CLOCK_FREQUENCY CLOCK_GetIpFreq(kCLOCK_DMA_Lpi2c1)

#define EXAMPLE_IOEXP_LPI2C_BAUDRATE               (400000)
#define EXAMPLE_IOEXP_LPI2C_MASTER_CLOCK_FREQUENCY SC_133MHZ
#define EXAMPLE_IOEXP_LPI2C_MASTER                 ADMA__LPI2C1
#define EXAMPLE_I2C_EXPANSION_A_ADDR               (0x1A)
#define EXAMPLE_I2C_SWITCH_ADDR                    (0x71)

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
static bool PCA9646_WriteReg(LPI2C_Type *base, const uint8_t dev_addr, uint8_t *txBuff, uint32_t txSize)
{
    status_t reVal = kStatus_Fail;

    if (kStatus_Success == LPI2C_MasterStart(base, dev_addr, kLPI2C_Write))
    {
        while (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
        {
        }

        reVal = LPI2C_MasterSend(base, txBuff, txSize);
        if (reVal != kStatus_Success)
        {
            return -1;
        }

        reVal = LPI2C_MasterStop(base);
        if (reVal != kStatus_Success)
        {
            return -1;
        }
    }
    return kStatus_Success;
}

sc_err_t BOARD_ConfigureExpansionIO()
{
    sc_err_t err = SC_ERR_NONE;
    lpi2c_master_config_t masterConfig;
    uint8_t txBuffer[4] = {0};

    /* lpi2c init */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = EXAMPLE_IOEXP_LPI2C_BAUDRATE;

    LPI2C_MasterInit(EXAMPLE_IOEXP_LPI2C_MASTER, &masterConfig, EXAMPLE_IOEXP_LPI2C_MASTER_CLOCK_FREQUENCY);
    /*Configure Expansion Pin*/

    /*
     * U191 Initialization
     * U191 has I2C Address of 0x71, enable channel 1,set SCL direction reversed by setting MSB HIGH
     */
    txBuffer[0] = 0x82;
    PCA9646_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_SWITCH_ADDR, txBuffer, 1);

    LPI2C_MasterDeinit(EXAMPLE_IOEXP_LPI2C_MASTER);
    return err;
}


/*!
 * @brief Main function
 */
int main(void)
{
    lpi2c_slave_config_t slaveConfig;
    status_t reVal = kStatus_Fail;
    uint8_t subaddress;

    sc_ipc_t ipc;
    sc_pm_clock_rate_t src_rate = SC_133MHZ;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* open the lpi2c power and clock */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_I2C_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on SC_R_I2C_1\r\n");
    }

    if (sc_pm_clock_enable(ipc, SC_R_I2C_1, SC_PM_CLK_PER, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable SC_R_I2C_1 clock \r\n");
    }

    if (sc_pm_set_clock_rate(ipc, SC_R_I2C_1, SC_PM_CLK_PER, &src_rate) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_R_I2C_1 clock rate\r\n");
    }

    /* Power on IRQSteer . */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTR\r\n");
    }

    /*
     * ExpansionIO in MEK board is dependent on I2C1, so need to be invoked
     * after I2C1 power and clock on
     */
    BOARD_ConfigureExpansionIO();

    /* Enable interrupt in irqsteer */
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, ADMA_I2C1_INT_IRQn);

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
