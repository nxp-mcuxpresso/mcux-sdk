/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma9553_pedometer_i2c.c
 *  @brief The mma9553_pedometer_i2c.c file implements the ISSDK MMA9553L sensor driver
 *          example demonstration as a Pedometer in I2C Mode.
 */

/*  SDK Includes */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lptmr.h"
#include "fsl_debug_console.h"

/* CMSIS Includes */
#include "Driver_I2C.h"

/* ISSDK Includes */
#include "issdk_hal.h"
#include "mma9553_drv.h"
#include "systick_utils.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define SAMPLING_RATE_ms (100)                /* Timeout for the ODR Timer. */
#define MMA9553_ACCEL_DATA_SIZE (6)           /* 2 byte X,Y,Z Axis Data each. */
#define mma9553_en_callback LPTMR0_IRQHandler /* Timer timeout Callback. */

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*! Prepare the register write list to configure MMA9553L in 30Hz Mode. */
const registercommandlist_t cMma9553Config30Hz[] = {
    {SetFSRange_2g, 0, sizeof(SetFSRange_2g)},                     /* Set FS Range 2G */
    {SetSampleRate_30Hz, 0, sizeof(SetSampleRate_30Hz)},           /* Set Sensor Sampling Rate 30Hz */
    {SetAFEPriority_for30Hz, 0, sizeof(SetAFEPriority_for30Hz)},   /* Set AFE Priority for 30Hz Sampling Rate */
    {SetMBoxPriority_for30Hz, 0, sizeof(SetMBoxPriority_for30Hz)}, /* Set MBox Priority for 30Hz Sampling Rate */
    __END_WRITE_CMD__};

/*! Prepare the register read list to read the raw Accel data from MMA9553. */
const registerreadlist_t cMma9553ReadRawOutput[] = {
    {.readFrom = MMA9553_XYZ_DATA_OFFSET, .numBytes = MMA9553_ACCEL_DATA_SIZE}, __END_READ_DATA__};

/*! Prepare the command list to read the Pedometer data from MMA9553. */
const registercommandlist_t cMma9553ReadPedometerCommand[] = {{ReadPedometerData, 0, sizeof(ReadPedometerData)},
                                                              __END_WRITE_CMD__};

/*! Prepare the read list to read the Pedometer data from MMA9553. */
const registerreadlist_t cMma9553ReadPedometerOutput[] = {{.readFrom = 0, .numBytes = sizeof(mma9553_pedometerdata_t)},
                                                          __END_READ_DATA__};

/*******************************************************************************
 * Globals
 ******************************************************************************/
volatile bool gMma9553DataReady;

/*******************************************************************************
 * Functions
 ******************************************************************************/
/* LPTMR based ODR Callback function. */
void mma9553_en_callback(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    gMma9553DataReady = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    lptmr_config_t lptmrConfig;
    mma9553_acceldata_t rawData;
    mma9553_pedometerdata_t pedometerData;
    mma9553_i2c_sensorhandle_t mma9553Driver;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!

    /*! Initialize the MCU hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    /* Initialize ODR Timer. */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    LPTMR_SetTimerPeriod(LPTMR0, MSEC_TO_COUNT(SAMPLING_RATE_ms, CLOCK_GetFreq(kCLOCK_LpoClk)));
    EnableIRQ(LPTMR0_IRQn);

    PRINTF("\r\n ISSDK MMA9553 sensor driver example for Pedometer Mode. \r\n");

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

    /*! Initialize the MMA9553 sensor driver. */
    status = MMA9553_I2C_Initialize(&mma9553Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA9553_I2C_ADDR);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initialized Sensor. \r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA9553_I2C_SetIdleTask(&mma9553Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    gMma9553DataReady = false; /* Do not read data, data will be read after ODR Timer expires. */

    /*! Configure the MMA9553 sensor driver with 30Hz Mode settings. */
    status = MMA9553_I2C_Configure(&mma9553Driver, cMma9553Config30Hz);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA9553 Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }

    LPTMR_StartTimer(LPTMR0);
    PRINTF("\r\n Successfully Applied MMA9553 Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {
        if (gMma9553DataReady == false)
        {
            continue;
        }
        else
        {
            gMma9553DataReady = false;
        }

        /*! Read the Pedometer data from the MMA9553. */
        status = MMA9553_I2C_CommandResponse(&mma9553Driver, cMma9553ReadPedometerCommand, cMma9553ReadPedometerOutput,
                                             (uint8_t *)&pedometerData);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /* Swap bytes for 2 byte fields for Big Endian to Little Endian conversion. */
        pedometerData.statusRegister = (pedometerData.statusRegister >> 8) | (pedometerData.statusRegister << 8);
        pedometerData.stepCount = (pedometerData.stepCount >> 8) | (pedometerData.stepCount << 8);
        pedometerData.distance = (pedometerData.distance >> 8) | (pedometerData.distance << 8);
        pedometerData.speed = (pedometerData.speed >> 8) | (pedometerData.speed << 8);
        pedometerData.calories = (pedometerData.calories >> 8) | (pedometerData.calories << 8);
        pedometerData.sleepCount = (pedometerData.sleepCount >> 8) | (pedometerData.sleepCount << 8);

        PRINTF("\r\n Steps = %d  Distance = %dm  Speed = %dm/h  Calories = %d \r\n", pedometerData.stepCount,
               pedometerData.distance, pedometerData.speed, pedometerData.calories);

        /*! Read the raw sensor data from the MMA9553. */
        status = MMA9553_I2C_CommandResponse(&mma9553Driver, NULL, cMma9553ReadRawOutput, (uint8_t *)&rawData.accel);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        PRINTF("\r\n Accel X = %d  Y = %d  Z = %d \r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(100); /* Ask for user input after processing 100 samples. */
    }
}
