/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxpq3115_oneshot.c
 * @brief The fxpq3115_oneshot.c file implements the ISSDK FXPQ3115BV sensor driver
 *        example demonstration with one-shot sampling mode.
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
#include "fxpq3115_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXPQ3115_DATA_SIZE (5) /* 3 byte Pressure/Altitude and 2 byte Temperature. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for Altitude readings in One-Shot mode. */
const registerwritelist_t B3115ConfigAltitude[] = {
    /* Enable Altitude output. */
    {FXPQ3115_CTRL_REG1, FXPQ3115_CTRL_REG1_ALT_ALT, FXPQ3115_CTRL_REG1_ALT_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Triggring One-Shot Sampling. */
const registerwritelist_t B3115SetOST[] = {
    /* Set the One ShoT Bit. */
    {FXPQ3115_CTRL_REG1, FXPQ3115_CTRL_REG1_OST_SET, FXPQ3115_CTRL_REG1_OST_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Register containing OST Bit. */
const registerreadlist_t B3115GetOST[] = {{.readFrom = FXPQ3115_CTRL_REG1, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Altitude+Temperature Data. */
const registerreadlist_t B3115OutputNormal[] = {{.readFrom = FXPQ3115_OUT_P_MSB, .numBytes = FXPQ3115_DATA_SIZE},
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
    uint8_t data[FXPQ3115_DATA_SIZE];
    fxpq3115_altitudedata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    fxpq3115_i2c_sensorhandle_t fxpq3115Driver;
    registerDeviceInfo_t deviceInfo;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXPQ3115 sensor driver example demonstration with oneshot mode\r\n");

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

    /*! Initialize FXPQ3115 sensor driver. */
    status = FXPQ3115_I2C_Initialize(&fxpq3115Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXPQ3115_I2C_ADDR,
                                     FXPQ3115_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*! We do not need to call FXPQ3115_I2C_Configure() in this case as we are going to read samples on demand.
     *  Instead we directly write register settings for One-Shot Mode... */
    deviceInfo.deviceInstance = I2C_S_DEVICE_INDEX;
    deviceInfo.functionParam = SMC;
    deviceInfo.idleFunction = (registeridlefunction_t)SMC_SetPowerModeWait;
    status = Sensor_I2C_Write(fxpq3115Driver.pCommDrv, &deviceInfo, fxpq3115Driver.slaveAddress, B3115ConfigAltitude);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\nWrite Failed.\r\n");
        return -1;
    }
    PRINTF("\r\nFXPQ3115 will now trigger acquisition of one sample and then read the data...\r\n");

    /*! The code contained withing the braces illustrate steps to read one-sample.
     *  These can be repated at desired intervals to acquire more samples. */
    { /* Trigger acquisition of One Sample. */
        status = Sensor_I2C_Write(fxpq3115Driver.pCommDrv, &deviceInfo, fxpq3115Driver.slaveAddress, B3115SetOST);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\nWrite Failed.\r\n");
            return SENSOR_ERROR_WRITE;
        }

        do /*! Keep checking the OST FLAG for completion. */
        {
            status = FXPQ3115_I2C_ReadData(&fxpq3115Driver, B3115GetOST, &dataReady);
            if (ARM_DRIVER_OK != status)
            {
                PRINTF("\r\nRead Failed.\r\n");
                return -1;
            }
        } /* Loop, untill sample acquisition is not completed. */
        while (0 != (dataReady & FXPQ3115_CTRL_REG1_OST_MASK));

        /*! Read raw sensor data from the FXPQ3115. */
        status = FXPQ3115_I2C_ReadData(&fxpq3115Driver, B3115OutputNormal, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Process the sample and convert the raw sensor data. */
        rawData.altitude = (int32_t)((data[0]) << 24) | ((data[1]) << 16) | ((data[2]) << 8);
        rawData.temperature = (int16_t)((data[3]) << 8) | (data[4]);
        altitudeInMeters = rawData.altitude / FXPQ3115_ALTITUDE_CONV_FACTOR;
        tempInDegrees = rawData.temperature / FXPQ3115_TEMPERATURE_CONV_FACTOR;

        PRINTF("\r\nAltitude    = %d Meters\r\n", altitudeInMeters);
        PRINTF("\r\nTemperature = %d degC\r\n", tempInDegrees);
        ASK_USER_TO_RESUME(1); /* Ask for user input after processing 8 samples. */
    }

    return 0;
}
