/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma865x_fifo.c
*   @brief The mma865x_fifo.c file implements the ISSDK MMA865x sensor driver
*        example demonstration with FIFO mode.
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
#include "mma865x_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* The watermark value configured for MMA865x FIFO Buffer. */
#define FIFO_WATERMARK (16)         /* Must be between 1 - 32 */
#define MMA865x_ACCEL_DATA_SIZE (6) /* 2 byte X,Y,Z Axis Data each. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure MMA865x in FIFO mode. */
const registerwritelist_t cMma865xConfigFifo[] =
    {/*! Configure the MMA865x to enable FIFO Mode and set Watermark. */
     {MMA865x_F_SETUP, MMA865x_F_SETUP_F_MODE_STOP_MODE | FIFO_WATERMARK,
      MMA865x_F_SETUP_F_MODE_MASK | MMA865x_F_SETUP_F_WMRK_MASK},
     /*! Configure the MMA865x to set FS Range as 2g. */
     {MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
     /*! Configure the MMA865x to set ODR to 100Hz. */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_100HZ, MMA865x_CTRL_REG1_DR_MASK},
     /*! Configure the MMA865x to set High Resolution mode. */
     {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
     __END_WRITE_DATA__};

/*! Prepare the register read list to read the FIFO Status from MMA865x. */
const registerreadlist_t cMma865xFifoStatus[] = {{.readFrom = MMA865x_F_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! Prepare the register read list to read the raw Accel data from MMA865x. */
const registerreadlist_t cMma865xOutputValues[] = {
    {.readFrom = MMA865x_OUT_X_MSB, .numBytes = MMA865x_ACCEL_DATA_SIZE * FIFO_WATERMARK}, __END_READ_DATA__};

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
    uint8_t data[MMA865x_ACCEL_DATA_SIZE * FIFO_WATERMARK];
    mma865x_acceldata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor driver example for FIFO Mode. \r\n");

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

    /*! Initialize the MMA865x sensor driver. */
    status = MMA865x_I2C_Initialize(&mma865xDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8652_I2C_ADDR,
                                    MMA8652_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA865x_I2C_SetIdleTask(&mma865xDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the MMA865x sensor driver with FIFO mode. */
    status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigFifo);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n MMA865x now active and entering data read loop... \r\n");

    for (;;) /* Forever loop */
    {
        /*! Wait for data ready from the MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xFifoStatus, &dataReady);
        if (0 == (dataReady & MMA865x_F_STATUS_F_WMKF_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Read the raw sensor data from the MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xOutputValues, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        for (uint8_t i = 0; i < FIFO_WATERMARK; i++)
        {
            /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
            rawData.accel[0] =
                ((int16_t)data[i * MMA865x_ACCEL_DATA_SIZE + 0] << 8) | data[i * MMA865x_ACCEL_DATA_SIZE + 1];
            rawData.accel[0] /= 16;
            rawData.accel[1] =
                ((int16_t)data[i * MMA865x_ACCEL_DATA_SIZE + 2] << 8) | data[i * MMA865x_ACCEL_DATA_SIZE + 3];
            rawData.accel[1] /= 16;
            rawData.accel[2] =
                ((int16_t)data[i * MMA865x_ACCEL_DATA_SIZE + 4] << 8) | data[i * MMA865x_ACCEL_DATA_SIZE + 5];
            rawData.accel[2] /= 16;
        }
        /* NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop.
         * Hence, we display only the last sample from each FIFO Burst Read. */
        PRINTF("\r\n Accel X = %d  Y = %d  Z = %d \r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(992 / FIFO_WATERMARK); /* Ask for user input after processing 992 samples. */
    }
}
