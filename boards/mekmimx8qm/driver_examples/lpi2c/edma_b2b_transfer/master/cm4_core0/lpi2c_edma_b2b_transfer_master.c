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
#include "fsl_lpi2c_edma.h"
#include "fsl_edma.h"
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif

#include "fsl_irqsteer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_I2C_MASTER_BASE DMA__LPI2C0

#define EXAMPLE_LPI2C_MASTER_DMA   DMA__EDMA1
#define LPI2C_TRANSMIT_DMA_CHANNEL 1U
#define LPI2C_RECEIVE_DMA_CHANNEL  0U

#define LPI2C_MASTER_CLOCK_FREQUENCY CLOCK_GetIpFreq(kCLOCK_DMA_Lpi2c0)

#define EXAMPLE_I2C_MASTER ((LPI2C_Type *)EXAMPLE_I2C_MASTER_BASE)

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_BAUDRATE               100000U
#define I2C_DATA_LENGTH            33U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

AT_NONCACHEABLE_SECTION(uint8_t g_master_txBuff[I2C_DATA_LENGTH]);
AT_NONCACHEABLE_SECTION(uint8_t g_master_rxBuff[I2C_DATA_LENGTH]);
AT_NONCACHEABLE_SECTION(lpi2c_master_edma_handle_t g_m_edma_handle);
edma_handle_t g_edmaTxHandle;
edma_handle_t g_edmaRxHandle;
volatile bool g_MasterCompletionFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void lpi2c_master_callback(LPI2C_Type *base, lpi2c_master_edma_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        g_MasterCompletionFlag = true;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    lpi2c_master_config_t masterConfig;
    lpi2c_master_transfer_t masterXfer = {0};
    edma_config_t userConfig;
    status_t reVal = kStatus_Fail;

    sc_ipc_t ipc;
    uint32_t freq;

    ipc = BOARD_InitRpc();

    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    /* Power on LPI2C. */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_I2C_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on LPI2C\r\n");
    }

    /* Set LPI2C clock */
    freq = CLOCK_SetIpFreq(kCLOCK_DMA_Lpi2c0, SC_24MHZ);
    if (freq == 0)
    {
        PRINTF("Error: Failed to set LPI2C frequency\r\n");
    }

    /* Power up DMA_EDMA1 channel 0, channel 1 for RX, TX */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_DMA_1_CH0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on DMA Channel!\r\n");
    }
    if (sc_pm_set_resource_power_mode(ipc, SC_R_DMA_1_CH1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on DMA Channel!\r\n");
    }

    /* Enable interrupt in irqsteer */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTEER!\r\n");
    }
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, DMA_I2C0_DMA_RX_INT_IRQn);
    IRQSTEER_EnableInterrupt(IRQSTEER, DMA_I2C0_DMA_TX_INT_IRQn);

    PRINTF("\r\nLPI2C board2board EDMA example -- Master transfer.\r\n");
#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
    /* DMAMUX init */
    DMAMUX_Init(EXAMPLE_LPI2C_MASTER_DMA_MUX);

    DMAMUX_SetSource(EXAMPLE_LPI2C_MASTER_DMA_MUX, LPI2C_TRANSMIT_DMA_CHANNEL,
                     LPI2CMASTER_TRANSMIT_EDMA_REQUEST_SOURCE);
    DMAMUX_EnableChannel(EXAMPLE_LPI2C_MASTER_DMA_MUX, LPI2C_TRANSMIT_DMA_CHANNEL);

    DMAMUX_SetSource(EXAMPLE_LPI2C_MASTER_DMA_MUX, LPI2C_RECEIVE_DMA_CHANNEL, LPI2CMASTER_RECEIVE_EDMA_REQUEST_SOURCE);
    DMAMUX_EnableChannel(EXAMPLE_LPI2C_MASTER_DMA_MUX, LPI2C_RECEIVE_DMA_CHANNEL);
#endif

    /* EDMA init */
    /*
     * userConfig.enableRoundRobinArbitration = false;
     * userConfig.enableHaltOnError = true;
     * userConfig.enableContinuousLinkMode = false;
     * userConfig.enableDebugMode = false;
     */
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_LPI2C_MASTER_DMA, &userConfig);

    /* Set up i2c master to send data to slave*/
    /* First data in txBuff is data length of the transmiting data. */
    g_master_txBuff[0] = I2C_DATA_LENGTH - 1U;
    for (uint32_t i = 1U; i < I2C_DATA_LENGTH; i++)
    {
        g_master_txBuff[i] = i - 1;
    }

    PRINTF("Master will send data :");
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH - 1U; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_txBuff[i + 1]);
    }
    PRINTF("\r\n\r\n");

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

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Hz = I2C_BAUDRATE;

    /* Initialize the LPI2C master peripheral */
    LPI2C_MasterInit(EXAMPLE_I2C_MASTER, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY);

    /* Create the EDMA channel handles */
    EDMA_CreateHandle(&g_edmaTxHandle, EXAMPLE_LPI2C_MASTER_DMA, LPI2C_TRANSMIT_DMA_CHANNEL);
    EDMA_CreateHandle(&g_edmaRxHandle, EXAMPLE_LPI2C_MASTER_DMA, LPI2C_RECEIVE_DMA_CHANNEL);
#if defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
    EDMA_SetChannelMux(EXAMPLE_LPI2C_MASTER_DMA, LPI2C_TRANSMIT_DMA_CHANNEL, DEMO_LPI2C_TRANSMIT_EDMA_CHANNEL);
    EDMA_SetChannelMux(EXAMPLE_LPI2C_MASTER_DMA, LPI2C_RECEIVE_DMA_CHANNEL, DEMO_LPI2C_RECEIVE_EDMA_CHANNEL);
#endif
    /* Create the LPI2C master DMA driver handle */
    LPI2C_MasterCreateEDMAHandle(EXAMPLE_I2C_MASTER, &g_m_edma_handle, &g_edmaRxHandle, &g_edmaTxHandle,
                                 lpi2c_master_callback, NULL);

    /* subAddress = 0x01, data = g_master_txBuff - write to slave.
      start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
    uint8_t deviceAddress     = 0x01U;
    masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = (uint32_t)deviceAddress;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = g_master_txBuff;
    masterXfer.dataSize       = I2C_DATA_LENGTH;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    /* Send master non-blocking data to slave */
    reVal = LPI2C_MasterTransferEDMA(EXAMPLE_I2C_MASTER, &g_m_edma_handle, &masterXfer);
    if (reVal != kStatus_Success)
    {
        return -1;
    }

    /*  Wait for transfer completed. */
    while (!g_MasterCompletionFlag)
    {
    }
    g_MasterCompletionFlag = false;

    PRINTF("Receive sent data from slave :");

    /* subAddress = 0x01, data = g_master_rxBuff - read from slave.
      start + slaveaddress(w) + subAddress + repeated start + slaveaddress(r) + rx data buffer + stop */
    masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = (uint32_t)deviceAddress;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = g_master_rxBuff;
    masterXfer.dataSize       = I2C_DATA_LENGTH - 1;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    /* Receive non-blocking data from slave */
    reVal = LPI2C_MasterTransferEDMA(EXAMPLE_I2C_MASTER, &g_m_edma_handle, &masterXfer);

    if (reVal != kStatus_Success)
    {
        return -1;
    }

    /*  Wait for transfer completed. */
    while (!g_MasterCompletionFlag)
    {
    }
    g_MasterCompletionFlag = false;

    for (uint32_t i = 0U; i < I2C_DATA_LENGTH - 1; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_rxBuff[i]);
    }
    PRINTF("\r\n\r\n");

    /* Transfer completed. Check the data.*/
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH - 1; i++)
    {
        if (g_master_rxBuff[i] != g_master_txBuff[i + 1])
        {
            PRINTF("\r\nError occurred in the transfer ! \r\n");
            break;
        }
    }

    PRINTF("\r\nEnd of LPI2C example .\r\n");
    while (1)
    {
    }
}
