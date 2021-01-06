/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_flexio_i2c_master.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_I2C_SLAVE_BASE      I2C3
#define BOARD_I2C_SLAVE_IRQn      I2C3_IRQn
#define BOARD_FLEXIO_BASE         FLEXIO0
#define FLEXIO_I2C_SDA_PIN        24U
#define FLEXIO_I2C_SCL_PIN        25U
#define FLEXIO_CLOCK_FREQUENCY    12000000U
#define I2C_SLAVE_CLOCK_FREQUENCY CLOCK_GetFreq(I2C3_CLK_SRC)
/* I2C Slave Address */
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
/* I2C Baudrate 100K */
#define I2C_BAUDRATE 100000U
/* The length of data */
#define I2C_DATA_LENGTH 32U
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_slave_buff[I2C_DATA_LENGTH];
uint8_t g_master_buff[I2C_DATA_LENGTH];

flexio_i2c_master_handle_t g_m_handle;
FLEXIO_I2C_Type i2cDev;
i2c_slave_handle_t g_s_handle;
volatile bool completionFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void i2c_slave_callback(I2C_Type *base, i2c_slave_transfer_t *xfer, void *userData)
{
    switch (xfer->event)
    {
        /*  Transmit request */
        case kI2C_SlaveTransmitEvent:
            /*  Update information for transmit process */
            xfer->data     = g_slave_buff;
            xfer->dataSize = I2C_DATA_LENGTH;
            break;

        /*  Receive request */
        case kI2C_SlaveReceiveEvent:
            /*  Update information for received process */
            xfer->data     = g_slave_buff;
            xfer->dataSize = I2C_DATA_LENGTH;
            break;

        /* Transfer done. */
        case kI2C_SlaveCompletionEvent:
            completionFlag = true;
            break;

        default:
            completionFlag = true;
            break;
    }
}

int main(void)
{
    i2c_slave_config_t slaveConfig;

    flexio_i2c_master_transfer_t masterXfer;
    IRQn_Type flexio_irqs[] = FLEXIO_IRQS;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_SetFlexio0Clock(2U);

    PRINTF("\r\nFlexIO I2C interrupt - I2C interrupt\r\n");

    /* Set i2c slave interrupt priority higher. */
    NVIC_SetPriority(BOARD_I2C_SLAVE_IRQn, 0);

    NVIC_SetPriority(flexio_irqs[0], 1);

    /* 1.Set up i2c slave first. */
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
    slaveConfig.upperAddress   = 0;

    I2C_SlaveInit(BOARD_I2C_SLAVE_BASE, &slaveConfig, I2C_SLAVE_CLOCK_FREQUENCY);

    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
    {
        g_slave_buff[i] = 0;
    }

    memset(&g_s_handle, 0, sizeof(g_s_handle));

    I2C_SlaveTransferCreateHandle(BOARD_I2C_SLAVE_BASE, &g_s_handle, i2c_slave_callback, NULL);
    I2C_SlaveTransferNonBlocking(BOARD_I2C_SLAVE_BASE, &g_s_handle, kI2C_SlaveCompletionEvent);

    /* 2.Set up i2c master to send data to slave. */
    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
    {
        g_master_buff[i] = i;
    }

    PRINTF("Master will send data :");
    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%02X  ", g_master_buff[i]);
    }
    PRINTF("\r\n\r\n");

    flexio_i2c_master_config_t masterConfig;

    /* Do hardware configuration. */
    i2cDev.flexioBase      = BOARD_FLEXIO_BASE;
    i2cDev.SDAPinIndex     = FLEXIO_I2C_SDA_PIN;
    i2cDev.SCLPinIndex     = FLEXIO_I2C_SCL_PIN;
    i2cDev.shifterIndex[0] = 0U;
    i2cDev.shifterIndex[1] = 1U;
    i2cDev.timerIndex[0]   = 0U;
    i2cDev.timerIndex[1]   = 1U;
    i2cDev.timerIndex[2]   = 2U;

    /*
     * masterConfig.enableMaster = true;
     * masterConfig.enableInDoze = false;
     * masterConfig.enableInDebug = true;
     * masterConfig.enableFastAccess = false;
     * masterConfig.baudRate_Bps = 100000U;
     */
    FLEXIO_I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = I2C_BAUDRATE;
    FLEXIO_I2C_MasterInit(&i2cDev, &masterConfig, FLEXIO_CLOCK_FREQUENCY);

    memset(&g_m_handle, 0, sizeof(g_m_handle));
    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
    masterXfer.direction      = kFLEXIO_I2C_Write;
    masterXfer.subaddress     = 0;
    masterXfer.subaddressSize = 0;
    masterXfer.data           = g_master_buff;
    masterXfer.dataSize       = I2C_DATA_LENGTH;

    FLEXIO_I2C_MasterTransferCreateHandle(&i2cDev, &g_m_handle, NULL, NULL);
    FLEXIO_I2C_MasterTransferNonBlocking(&i2cDev, &g_m_handle, &masterXfer);

    /* Wait for transfer completed. */
    while (!completionFlag)
    {
    }
    completionFlag = false;

    /* 3.Transfer completed. Check the data. */
    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
    {
        if (g_slave_buff[i] != g_master_buff[i])
        {
            PRINTF("\r\nError occurred in this transfer !\r\n");
            break;
        }
    }

    PRINTF("Slave received data :");
    for (uint32_t i = 0; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%02X  ", g_slave_buff[i]);
    }
    PRINTF("\r\n\r\n");

    while (1)
    {
    }
}
