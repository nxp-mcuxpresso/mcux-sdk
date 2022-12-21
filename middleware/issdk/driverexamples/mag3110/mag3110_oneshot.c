/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mag3110_oneshot.c
 * @brief The mag3110_oneshot.c file implements the ISSDK MAG3110 sensor driver
 *        example demonstration with polling mode.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_I2C.h"

/* ISSDK Includes */
#include "issdk_hal.h"
#include "mag3110_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MAG3110_DATA_SIZE (6) /* 2 byte X,Y,Z Axis Data each. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for Magnetic Strength readings in One-Shot mode. */
const registerwritelist_t cMag3110ConfigOneShot[] = {
    /* Set Auto Magnetic Sensor Reset. */
    {MAG3110_CTRL_REG2, MAG3110_CTRL_REG2_MAG_RST_EN | MAG3110_CTRL_REG2_AUTO_MSRT_EN_EN | MAG3110_CTRL_REG2_RAW_RAW,
                        MAG3110_CTRL_REG2_MAG_RST_MASK | MAG3110_CTRL_REG2_AUTO_MSRT_EN_MASK | MAG3110_CTRL_REG2_RAW_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Triggring One-Shot Sampling. */
const registerwritelist_t cMag3110SetOST[] = {
    /* Set the One ShoT Bit. */
    {MAG3110_CTRL_REG1, MAG3110_CTRL_REG1_TM_TRIGGER, MAG3110_CTRL_REG1_TM_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Register containing OST Bit. */
const registerreadlist_t cMag3110GetOST[] = {{.readFrom = MAG3110_CTRL_REG1, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Magnetic Strength Data. */
const registerreadlist_t cMag3110OutputNormal[] = {{.readFrom = MAG3110_OUT_X_MSB, .numBytes = MAG3110_DATA_SIZE},
                                                   __END_READ_DATA__};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t dataReady;
    uint8_t data[MAG3110_DATA_SIZE];
    mag3110_magdata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mag3110_i2c_sensorhandle_t mag3110Driver;
    registerDeviceInfo_t deviceInfo;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MAG3110 sensor driver example demonstration with oneshot mode\r\n");

    /*! Initialize the I2C driver. */
    status = I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Initialization Failed\r\n");
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = I2Cdrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Power Mode setting Failed\r\n");
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Control Mode setting Failed\r\n");
        return -1;
    }

    /*! Initialize MAG3110 sensor driver. */
    status = MAG3110_I2C_Initialize(&mag3110Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MAG3110_I2C_ADDR,
                                    MAG3110_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*! We do not need to call MAG3110_I2C_Configure() in this case as we are going to read samples on demand.
     *  Instead we directly write register settings for One-Shot Mode... */
    deviceInfo.deviceInstance = I2C_S_DEVICE_INDEX;
    deviceInfo.functionParam = SMC;
    deviceInfo.idleFunction = (registeridlefunction_t)SMC_SetPowerModeWait;
    status = Sensor_I2C_Write(mag3110Driver.pCommDrv, &deviceInfo, mag3110Driver.slaveAddress, cMag3110ConfigOneShot);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\nWrite Failed.\r\n");
        return -1;
    }
    PRINTF("\r\nMAG3110 will now trigger acquisitioin of one sample and then read the data...\r\n");

    /*! The code contained withing the braces illustrate steps to read one-sample.
     *  These can be repated at desired intervals to acquire more samples. */
    { /* Trigger acquisition of One Sample. */
        status = Sensor_I2C_Write(mag3110Driver.pCommDrv, &deviceInfo, mag3110Driver.slaveAddress, cMag3110SetOST);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\nWrite Failed.\r\n");
            return SENSOR_ERROR_WRITE;
        }

        do /*! Keep checking the OST FLAG for completion. */
        {
            status = MAG3110_I2C_ReadData(&mag3110Driver, cMag3110GetOST, &dataReady);
            if (ARM_DRIVER_OK != status)
            {
                PRINTF("\r\nRead Failed.\r\n");
                return -1;
            }
        } /* Loop, untill sample acquisition is not completed. */
        while (0 != (dataReady & MAG3110_CTRL_REG1_TM_MASK));

        /*! Read raw sensor data from the MAG3110. */
        status = MAG3110_I2C_ReadData(&mag3110Driver, cMag3110OutputNormal, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Process the sample and convert the raw sensor data to signed 16-bit container. */
        rawData.mag[0] = ((int16_t)data[0] << 8) | data[1];
        rawData.mag[1] = ((int16_t)data[2] << 8) | data[3];
        rawData.mag[2] = ((int16_t)data[4] << 8) | data[5];

        PRINTF("\r\n Mag  X = %d  Y = %d  Z = %d\r\n", rawData.mag[0], rawData.mag[1], rawData.mag[2]);
        ASK_USER_TO_RESUME(1); /* Ask for user input after processing 1 samples. */
    }

    return 0;
}
