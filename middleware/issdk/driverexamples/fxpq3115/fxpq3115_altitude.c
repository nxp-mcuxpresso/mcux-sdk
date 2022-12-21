/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxpq3115_altitude.c
 * @brief The fxpq3115_altitude.c file implements the ISSDK FXPQ3115BV sensor driver
 *        example demonstration for Altitude mode.
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
/*! In FXPQ3115 the Auto Acquisition Time Step (ODR) can be set only in powers of 2 (i.e. 2^x, where x is the
 *  SAMPLING_EXPONENT).
 *  This gives a range of 1 second to 2^15 seconds (9 hours). */
#define FXPQ3115_SAMPLING_EXPONENT (1) /* 2 seconds */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for Altitude readings in Poll (non buffered) mode. */
const registerwritelist_t B3115ConfigAltitude[] = {
    /* Enable Data Ready and Event flags for Altitude, Temperature or either. */
    {FXPQ3115_PT_DATA_CFG,
     FXPQ3115_PT_DATA_CFG_TDEFE_ENABLED | FXPQ3115_PT_DATA_CFG_PDEFE_ENABLED | FXPQ3115_PT_DATA_CFG_DREM_ENABLED,
     FXPQ3115_PT_DATA_CFG_TDEFE_MASK | FXPQ3115_PT_DATA_CFG_PDEFE_MASK | FXPQ3115_PT_DATA_CFG_DREM_MASK},
    /* Enable Altitude output and set Over Sampling Ratio to 128. */
    {FXPQ3115_CTRL_REG1, FXPQ3115_CTRL_REG1_ALT_ALT | FXPQ3115_CTRL_REG1_OS_OSR_128,
     FXPQ3115_CTRL_REG1_ALT_MASK | FXPQ3115_CTRL_REG1_OS_MASK},
    /* Set Auto acquisition time step. */
    {FXPQ3115_CTRL_REG2, FXPQ3115_SAMPLING_EXPONENT, FXPQ3115_CTRL_REG2_ST_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Status Register. */
const registerreadlist_t B3115Status[] = {{.readFrom = FXPQ3115_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Altitude+Temperature Data in Poll Mode. */
const registerreadlist_t B3115OutputPoll[] = {{.readFrom = FXPQ3115_OUT_P_MSB, .numBytes = FXPQ3115_DATA_SIZE},
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

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXPQ3115 sensor driver example demonstration with poll mode\r\n");

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

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXPQ3115_I2C_SetIdleTask(&fxpq3115Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the FXPQ3115 sensor. */
    status = FXPQ3115_I2C_Configure(&fxpq3115Driver, B3115ConfigAltitude);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXPQ3115 sensor configuration failed.\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXPQ3115 Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {
        /*! Wait for data ready from the FXPQ3115. */
        status = FXPQ3115_I2C_ReadData(&fxpq3115Driver, B3115Status, &dataReady);
        if (0 == (dataReady & FXPQ3115_DR_STATUS_PTDR_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Read new raw sensor data from the FXPQ3115. */
        status = FXPQ3115_I2C_ReadData(&fxpq3115Driver, B3115OutputPoll, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Process the sample and convert the raw sensor data. */
        rawData.altitude = (int32_t)((data[0]) << 24) | ((data[1]) << 16) | ((data[2]) << 8);
        altitudeInMeters = rawData.altitude / FXPQ3115_ALTITUDE_CONV_FACTOR;

        rawData.temperature = (int16_t)((data[3]) << 8) | (data[4]);
        tempInDegrees = rawData.temperature / FXPQ3115_TEMPERATURE_CONV_FACTOR;

        PRINTF("\r\n Altitude    = %d Meters\r\n", altitudeInMeters);
        PRINTF("\r\n Temperature = %d degC\r\n", tempInDegrees);
        ASK_USER_TO_RESUME(8); /* Ask for user input after processing 8 samples. */
    }
}
