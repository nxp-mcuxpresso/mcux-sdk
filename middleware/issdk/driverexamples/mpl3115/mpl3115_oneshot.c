/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mpl3115_oneshot.c
 * @brief The mpl3115_oneshot.c file implements the ISSDK MPL3115 sensor driver
 *        example demonstration with one shot mode.
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
#include "mpl3115_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MPL3115_DATA_SIZE (5) /* 3 byte Pressure/Altitude and 2 byte Temperature. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for Altitude readings in One-Shot mode. */
const registerwritelist_t cMpl3115ConfigAltitude[] = {
    /* Enable Altitude output. */
    {MPL3115_CTRL_REG1, MPL3115_CTRL_REG1_ALT_ALT, MPL3115_CTRL_REG1_ALT_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Triggring One-Shot Sampling. */
const registerwritelist_t cMpl3115SetOST[] = {
    /* Set the One ShoT Bit. */
    {MPL3115_CTRL_REG1, MPL3115_CTRL_REG1_OST_SET, MPL3115_CTRL_REG1_OST_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Register containing OST Bit. */
const registerreadlist_t cMpl3115GetOST[] = {{.readFrom = MPL3115_CTRL_REG1, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Altitude+Temperature Data. */
const registerreadlist_t cMpl3115OutputNormal[] = {{.readFrom = MPL3115_OUT_P_MSB, .numBytes = MPL3115_DATA_SIZE},
                                                   __END_READ_DATA__};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*!
 * @brief Main function
 */
int main(void)
{
    int16_t tempInDegrees;
    int32_t altitudeInMeters;
    int32_t status;
    uint8_t dataReady;
    uint8_t data[MPL3115_DATA_SIZE];
    mpl3115_altitudedata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mpl3115_i2c_sensorhandle_t mpl3115Driver;
    registerDeviceInfo_t deviceInfo;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MPL3115 sensor driver example demonstration with oneshot mode\r\n");

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

    /*! Initialize MPL3115 sensor driver. */
    status = MPL3115_I2C_Initialize(&mpl3115Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MPL3115_I2C_ADDR,
                                    MPL3115_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*! We do not need to call MPL3115_I2C_Configure() in this case as we are going to read samples on demand.
     *  Instead we directly write register settings for One-Shot Mode... */
    deviceInfo.deviceInstance = I2C_S_DEVICE_INDEX;
    deviceInfo.functionParam = SMC;
    deviceInfo.idleFunction = (registeridlefunction_t)SMC_SetPowerModeWait;
    status = Sensor_I2C_Write(mpl3115Driver.pCommDrv, &deviceInfo, mpl3115Driver.slaveAddress, cMpl3115ConfigAltitude);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\nWrite Failed.\r\n");
        return -1;
    }
    PRINTF("\r\nMPL3115 will now trigger acquisition of one sample and then read the data...\r\n");

    /*! The code contained withing the braces illustrate steps to read one-sample.
     *  These can be repated at desired intervals to acquire more samples. */
    { /* Trigger acquisition of One Sample. */
        status = Sensor_I2C_Write(mpl3115Driver.pCommDrv, &deviceInfo, mpl3115Driver.slaveAddress, cMpl3115SetOST);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\nWrite Failed.\r\n");
            return SENSOR_ERROR_WRITE;
        }

        do /*! Keep checking the OST FLAG for completion. */
        {
            status = MPL3115_I2C_ReadData(&mpl3115Driver, cMpl3115GetOST, &dataReady);
            if (ARM_DRIVER_OK != status)
            {
                PRINTF("\r\nRead Failed.\r\n");
                return -1;
            }
        } /* Loop, untill sample acquisition is not completed. */
        while (0 != (dataReady & MPL3115_CTRL_REG1_OST_MASK));

        /*! Read raw sensor data from the MPL3115. */
        status = MPL3115_I2C_ReadData(&mpl3115Driver, cMpl3115OutputNormal, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Process the sample and convert the raw sensor data. */
        rawData.altitude = (int32_t)((data[0]) << 24) | ((data[1]) << 16) | ((data[2]) << 8);
        rawData.temperature = (int16_t)((data[3]) << 8) | (data[4]);
        altitudeInMeters = rawData.altitude / MPL3115_ALTITUDE_CONV_FACTOR;
        tempInDegrees = rawData.temperature / MPL3115_TEMPERATURE_CONV_FACTOR;

        PRINTF("\r\nAltitude    = %d Meters\r\n", altitudeInMeters);
        PRINTF("\r\nTemperature = %d degC\r\n", tempInDegrees);
        ASK_USER_TO_RESUME(1); /* Ask for user input after processing 8 samples. */
    }

    return 0;
}
