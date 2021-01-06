/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  SDK Included Files */
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
#define LPI2C_CLOCK_FREQUENCY    CLOCK_GetIpFreq(kCLOCK_DMA_Lpi2c1)
#define BOARD_ACCEL_I2C_BASEADDR ADMA__LPI2C1

#define EXAMPLE_IOEXP_LPI2C_BAUDRATE               (400000) /*in i2c example it is 100000*/
#define EXAMPLE_IOEXP_LPI2C_MASTER_CLOCK_FREQUENCY SC_133MHZ
#define EXAMPLE_IOEXP_LPI2C_MASTER                 ADMA__LPI2C1
#define EXAMPLE_I2C_EXPANSION_A_ADDR               (0x1A)

/*! @brief PCA9557 Registers address definition. */
#define PCA9557_REG_INTPUT_PORT        (0x00)
#define PCA9557_REG_OUTPUT_PORT        (0x01)
#define PCA9557_REG_POLARITY_INVERSION (0x02)
#define PCA9557_REG_CONFIGURATION      (0x03)

#define EXAMPLE_I2C_SWITCH_ADDR (0x71)
#define I2C_BAUDRATE       100000U
#define FXOS8700_WHOAMI    0xC7U
#define MMA8451_WHOAMI     0x1AU
#define ACCEL_STATUS       0x00U
#define ACCEL_XYZ_DATA_CFG 0x0EU
#define ACCEL_CTRL_REG1    0x2AU
/* FXOS8700 and MMA8451 have the same who_am_i register address. */
#define ACCEL_WHOAMI_REG 0x0DU
#define ACCEL_READ_TIMES 10U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);
static bool LPI2C_ReadAccelWhoAmI(void);
static bool LPI2C_WriteAccelReg(LPI2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t value);
static bool LPI2C_ReadAccelRegs(
    LPI2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t *rxBuff, uint32_t rxSize);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*  FXOS8700 and MMA8451 device address */
const uint8_t g_accel_address[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};

lpi2c_master_handle_t g_m_handle;

uint8_t g_accel_addr_found = 0x00U;

volatile bool completionFlag = false;
volatile bool nakFlag        = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
static bool PCA9557_WriteReg(
    LPI2C_Type *base, const uint8_t dev_addr, uint8_t reg_offset, uint8_t *txBuff, uint32_t txSize)
{
    status_t reVal = kStatus_Fail;

    if (kStatus_Success == LPI2C_MasterStart(base, dev_addr, kLPI2C_Write))
    {
        while (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
        {
        }

        reVal = LPI2C_MasterSend(base, &reg_offset, 1);
        if (reVal != kStatus_Success)
        {
            return -1;
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

static void delay(void)
{
    uint32_t i = 0;

    while (i < 15000000)
    {
        __ASM("nop");
        i++;
    }
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
     * U191 has I2C Address of 0x71, here enable channel 3 to control the IO EXP
     * (9557) to
     * reset the accelermeter sensor.
     */
    txBuffer[0] = 0x8;
    PCA9646_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_SWITCH_ADDR, txBuffer, 1);

    /* Set CAN enable and standby pin as output */
    txBuffer[0] = 0;
    PCA9557_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_EXPANSION_A_ADDR, PCA9557_REG_CONFIGURATION, txBuffer, 1);
    delay();
    /* Output '0' to reset pin */
    txBuffer[0] = 0x0;
    PCA9557_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_EXPANSION_A_ADDR, PCA9557_REG_OUTPUT_PORT, txBuffer, 1);
    delay();
    /* Output '1' to remove reset pin */
    txBuffer[0] = 0x20;
    PCA9557_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_EXPANSION_A_ADDR, PCA9557_REG_OUTPUT_PORT, txBuffer, 1);

    /*
     * U191, here enable channel 2 to control the accelermeter sensor.
     */
    txBuffer[0] = 0x4;
    PCA9646_WriteReg(EXAMPLE_IOEXP_LPI2C_MASTER, EXAMPLE_I2C_SWITCH_ADDR, txBuffer, 1);

    LPI2C_MasterDeinit(EXAMPLE_IOEXP_LPI2C_MASTER);
    return err;
}



static void lpi2c_master_callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if (status == kStatus_LPI2C_Nak)
    {
        nakFlag = true;
    }
}

static bool LPI2C_ReadAccelWhoAmI(void)
{
    /*
    How to read the device who_am_I value ?
    Start + Device_address_Write , who_am_I_register;
    Repeart_Start + Device_address_Read , who_am_I_value.
    */
    uint8_t who_am_i_reg          = ACCEL_WHOAMI_REG;
    uint8_t who_am_i_value        = 0x00;
    uint8_t accel_addr_array_size = 0x00;
    bool result                   = false;
    uint8_t i                     = 0U;
    status_t reVal                = kStatus_Fail;

    lpi2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = g_accel_address[0];
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = who_am_i_reg;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = &who_am_i_value;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    accel_addr_array_size = sizeof(g_accel_address) / sizeof(g_accel_address[0]);

    for (i = 0; i < accel_addr_array_size; i++)
    {
        masterXfer.slaveAddress = g_accel_address[i];

        reVal = LPI2C_MasterTransferNonBlocking(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, &masterXfer);
        if (reVal != kStatus_Success)
        {
            continue;
        }
        /*  wait for transfer completed. */
        while ((!nakFlag) && (!completionFlag))
        {
        }

        nakFlag = false;

        if (completionFlag == true)
        {
            g_accel_addr_found = masterXfer.slaveAddress;
            break;
        }

        /* Delay at least one clock cycle to make sure the bus is idle. */
        SDK_DelayAtLeastUs(1000000UL / I2C_BAUDRATE, SystemCoreClock); 
    }

    if (completionFlag)
    {
        completionFlag     = false;
        if (who_am_i_value == FXOS8700_WHOAMI)
        {
            PRINTF("Found an FXOS8700 on board , the device address is 0x%x . \r\n", masterXfer.slaveAddress);
            result = true;
        }
        else if (who_am_i_value == MMA8451_WHOAMI)
        {
            PRINTF("Found an MMA8451 on board , the device address is 0x%x . \r\n", masterXfer.slaveAddress);
            result = true;
        }
        else
        {
            PRINTF("Found a device, the WhoAmI value is 0x%x\r\n", who_am_i_value);
            PRINTF("It's not MMA8451 or FXOS8700. \r\n");
            PRINTF("The device address is 0x%x. \r\n", masterXfer.slaveAddress);
            result = false;
        }
    }
    else
    {
        PRINTF("\r\n Do not find an accelerometer device ! \r\n");
        result = false;
    }
    return result;
}

static bool LPI2C_WriteAccelReg(LPI2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t value)
{
    lpi2c_master_transfer_t masterXfer;
    status_t reVal = kStatus_Fail;

    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = device_addr;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = reg_addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = &value;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    /*  direction=write : start+device_write;cmdbuff;xBuff; */
    /*  direction=recive : start+device_write;cmdbuff;repeatStart+device_read;xBuff; */

    reVal = LPI2C_MasterTransferNonBlocking(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, &masterXfer);
    if (reVal != kStatus_Success)
    {
        return false;
    }

    /*  wait for transfer completed. */
    while ((!nakFlag) && (!completionFlag))
    {
    }

    nakFlag = false;

    if (completionFlag == true)
    {
        completionFlag = false;
        return true;
    }
    else
    {
        return false;
    }
}

static bool LPI2C_ReadAccelRegs(
    LPI2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t *rxBuff, uint32_t rxSize)
{
    lpi2c_master_transfer_t masterXfer;
    status_t reVal = kStatus_Fail;

    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = device_addr;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = reg_addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    /*  direction=write : start+device_write;cmdbuff;xBuff; */
    /*  direction=recive : start+device_write;cmdbuff;repeatStart+device_read;xBuff; */

    reVal = LPI2C_MasterTransferNonBlocking(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, &masterXfer);
    if (reVal != kStatus_Success)
    {
        return false;
    }
    /*  wait for transfer completed. */
    while ((!nakFlag) && (!completionFlag))
    {
    }

    nakFlag = false;

    if (completionFlag == true)
    {
        completionFlag = false;
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    bool isThereAccel = false;
    lpi2c_master_config_t masterConfig;

    sc_ipc_t ipc;
    sc_pm_clock_rate_t src_rate = SC_133MHZ;

    ipc = BOARD_InitRpc();
    BOARD_InitPinsPre();
    BOARD_InitPins(ipc);
    BOARD_PowerOnBaseBoard();
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

    PRINTF("\r\nLPI2C example -- Read Accelerometer Value\r\n");

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

    masterConfig.baudRate_Hz = I2C_BAUDRATE;

    LPI2C_MasterInit(BOARD_ACCEL_I2C_BASEADDR, &masterConfig, LPI2C_CLOCK_FREQUENCY);
    LPI2C_MasterTransferCreateHandle(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, lpi2c_master_callback, NULL);
    isThereAccel = LPI2C_ReadAccelWhoAmI();

    /*  read the accel xyz value if there is accel device on board */
    if (true == isThereAccel)
    {
        uint8_t databyte  = 0;
        uint8_t write_reg = 0;
        uint8_t readBuff[7];
        int16_t x, y, z;
        uint8_t status0_value = 0;
        uint32_t i            = 0U;
        bool reTrans          = false;

        /*  please refer to the "example FXOS8700CQ Driver Code" in FXOS8700 datasheet. */
        /*  write 0000 0000 = 0x00 to accelerometer control register 1 */
        /*  standby */
        /*  [7-1] = 0000 000 */
        /*  [0]: active=0 */
        write_reg = ACCEL_CTRL_REG1;
        databyte  = 0;
        reTrans   = LPI2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);
        if (reTrans == false)
        {
            PRINTF("F1\n");
            return -1;
        }

        /*  write 0000 0001= 0x01 to XYZ_DATA_CFG register */
        /*  [7]: reserved */
        /*  [6]: reserved */
        /*  [5]: reserved */
        /*  [4]: hpf_out=0 */
        /*  [3]: reserved */
        /*  [2]: reserved */
        /*  [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB */
        /*  databyte = 0x01; */
        write_reg = ACCEL_XYZ_DATA_CFG;
        databyte  = 0x01;
        reTrans   = LPI2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);
        if (reTrans == false)
        {
            PRINTF("F2\n");
            return -1;
        }

        /*  write 0000 1101 = 0x0D to accelerometer control register 1 */
        /*  [7-6]: aslp_rate=00 */
        /*  [5-3]: dr=001 for 200Hz data rate (when in hybrid mode) */
        /*  [2]: lnoise=1 for low noise mode */
        /*  [1]: f_read=0 for normal 16 bit reads */
        /*  [0]: active=1 to take the part out of standby and enable sampling */
        /*   databyte = 0x0D; */
        write_reg = ACCEL_CTRL_REG1;
        databyte  = 0x0d;
        reTrans   = LPI2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);
        if (reTrans == false)
        {
            PRINTF("F3\n");
            return -1;
        }

        PRINTF("The accel values:\r\n");
        for (i = 0; i < ACCEL_READ_TIMES; i++)
        {
            status0_value = 0;
            /*  wait for new data are ready. */
            while (status0_value != 0xff)
            {
                reTrans =
                    LPI2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, &status0_value, 1);
                if (reTrans == false)
                {
                    PRINTF("F4\n");
                    return -1;
                }
                else
                {
                }
            }

            /*  Multiple-byte Read from STATUS (0x00) register */
            reTrans = LPI2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, readBuff, 7);
            if (reTrans == false)
            {
                PRINTF("F5\n");
                return -1;
            }

            status0_value = readBuff[0];
            x             = ((int16_t)(((readBuff[1] * 256U) | readBuff[2]))) / 4U;
            y             = ((int16_t)(((readBuff[3] * 256U) | readBuff[4]))) / 4U;
            z             = ((int16_t)(((readBuff[5] * 256U) | readBuff[6]))) / 4U;

            PRINTF("status_reg = 0x%x , x = %5d , y = %5d , z = %5d \r\n", status0_value, x, y, z);
        }
    }

    PRINTF("\r\nEnd of LPI2C example .\r\n");
    while (1)
    {
    }
}
