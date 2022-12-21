/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma9553_pedometer_interrupt.c
*   @brief The mma9553_pedometer_interrupt.c file implements the ISSDK MMA9553L sensor driver
*          example demonstration as a Pedometer in I2C Mode with Interrupts.
*/

/*  SDK Includes */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

/* CMSIS Includes */
#include "Driver_I2C.h"

/* ISSDK Includes */
#include "issdk_hal.h"
#include "mma9553_drv.h"
#include "gpio_driver.h"
#include "systick_utils.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define MMA9553_ACCEL_DATA_SIZE (6) /* 2 byte X,Y,Z Axis Data each. */
#define MMA9553_INT_O A0            /* The INT_O pin of MMA9553 on the FRDM-STBC-SA955x Board. */

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*! Prepare the register write list to configure MMA9553L in 30Hz Mode. */
const registercommandlist_t cMma9553Config30Hz[] = {
    {SetFSRange_2g, 0, sizeof(SetFSRange_2g)},                   /* Set FS Range 2G */
    {SetSampleRate_3Hz, 0, sizeof(SetSampleRate_3Hz)},           /* Set Sensor Sampling Rate 3Hz */
    {SetAFEPriority_for3Hz, 0, sizeof(SetAFEPriority_for3Hz)},   /* Set AFE Priority for 3Hz Sampling Rate */
    {SetMBoxPriority_for3Hz, 0, sizeof(SetMBoxPriority_for3Hz)}, /* Set MBox Priority for 3Hz Sampling Rate */
    __END_WRITE_CMD__};

/*! Prepare the register read list to read the raw Accel data from MMA9553. */
const registerreadlist_t cMma9553ReadRawOutput[] = {
    {.readFrom = MMA9553_XYZ_DATA_OFFSET, .numBytes = MMA9553_ACCEL_DATA_SIZE}, __END_READ_DATA__};

/*! Prepare the command list to read the Pedometer data from MMA9553. */
const registercommandlist_t cMma9553ReadPedometerCommand[] = {{ReadPedometerData, 0, sizeof(ReadPedometerData)},
                                                              __END_WRITE_CMD__};

/*! Prepare the command list to enable interrupts for AFE sampling completion with Legacy Mode for MMA9553. */
const registercommandlist_t cMma9553EnableInterruptCommand[] = {{SetLegacyIntMode, 0, sizeof(SetLegacyIntMode)},
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
/* Data Ready INT Callback function. */
void mma9553_int_data_ready_callback(void *pUserData)
{
    gMma9553DataReady = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    mma9553_acceldata_t rawData;
    mma9553_pedometerdata_t pedometerData;
    mma9553_i2c_sensorhandle_t mma9553Driver;

    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;
    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!

    /*! Initialize the MCU hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA9553 sensor driver example for Interrupt Mode. \r\n");

    /* Here MMA9553_INT_O and RGB_LED are the GPIO PIN IDs.
     * These are generated using the same Port ID(PortB for the pins) and Pin ID(2 and 22 for the pins) used for
     * creating the GPIO handles above. */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGpioDriver->pin_init(&MMA9553_INT_O, GPIO_DIRECTION_IN, NULL, &mma9553_int_data_ready_callback, NULL);

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

    gMma9553DataReady = false; /* Do not read data, data will be read after Interrupt is received. */

    /*! Configure the MMA9553 sensor driver with 30Hz Mode settings. */
    status = MMA9553_I2C_Configure(&mma9553Driver, cMma9553Config30Hz);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA9553 Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }

    /*! MMA9553_I2C_Configure sets the part to Legacy Mode.
     *  To enable MMA9553_INT_O interrupt for MMA9553 we need to override this by setting Legacy+AFE Sampling Interrupt.
     */
    status = MMA9553_I2C_CommandResponse(&mma9553Driver, cMma9553EnableInterruptCommand, NULL, NULL);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n Enable Interrupt Failed. \r\n");
        return -1; /* Read failed, so exit. */
    }

    PRINTF("\r\n Successfully Applied MMA9553 Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {        /* In ISR Mode receipt of interrupt will indicate data is ready. */
        if (false == gMma9553DataReady)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gMma9553DataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read the Pedometer data from the MMA9553. */
        status = MMA9553_I2C_CommandResponse(&mma9553Driver, cMma9553ReadPedometerCommand, cMma9553ReadPedometerOutput,
                                             (uint8_t *)&pedometerData);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /* Swap bytes for 2 byte fields for Little Endian to Big Endian conversion. */
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
        ASK_USER_TO_RESUME(30); /* Ask for user input after processing 100 samples. */
    }
}
