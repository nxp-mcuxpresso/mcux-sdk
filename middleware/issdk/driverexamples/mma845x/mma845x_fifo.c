/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma845x_fifo.c
* @brief The mma845x_fifo.c file implements the ISSDK MMA845x sensor driver
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
#include "mma845x_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/*! @def    FIFO_SIZE
 *  @brief  The watermark value configured for MMA845x FIFO Buffer.
 */
#define FIFO_SIZE 4 // Must be between 1 - 32

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure MMA845x in FIFO mode. */
const registerwritelist_t mma845x_Config_Fifo[] = {
    /*! Configure the MMA845x CTRL_REG1 to set mode to STANDBY and odr to 12.5Hz. */
    {MMA845x_CTRL_REG1, MMA845x_CTRL_REG1_MODE_STANDBY | MMA845x_CTRL_REG1_DR_12DOT5HZ, 0},
    /*! Configure the MMA845x F_SETUP to set FIFO mode to STOP, set the watermark size to FIFO_SIZE. */
    {MMA845x_F_SETUP, MMA845x_F_SETUP_F_MODE_FIFOSTOP | FIFO_SIZE, 0},
    /*! Configure the MMA845x CTRL_REG2 to set the Oversampling mode to High Resolution. */
    {MMA845x_CTRL_REG2, MMA845x_CTRL_REG2_MODS_HIGHRES, 0},
    __END_WRITE_DATA__};

/*! Prepare the register read list to read the FIFO event from MMA845x. */
const registerreadlist_t mma845x_Fifo_Status[] = {{.readFrom = MMA845x_F_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! Prepare the register read list to read the raw Accel data from MMA845x. */
const registerreadlist_t mma845x_Output_Values[] = {
    {.readFrom = MMA845x_OUT_X_MSB, .numBytes = MMA845x_ACCEL_DATA_SIZE * FIFO_SIZE}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t fifoEvent;
    uint8_t data[MMA845x_ACCEL_DATA_SIZE * FIFO_SIZE];
    mma845x_acceldata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma845x_i2c_sensorhandle_t MMA845xdrv;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA845x sensor driver example for fifo mode\r\n");

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

    /*! Initialize the MMA845x sensor driver. */
    status = MMA845x_I2C_Initialize(&MMA845xdrv, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA845x_I2C_ADDR,
                                    MMA8451_WHO_AM_I_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA845x_I2C_SetIdleTask(&MMA845xdrv, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the MMA845x sensor driver with FIFO mode. */
    status = MMA845x_I2C_Configure(&MMA845xdrv, mma845x_Config_Fifo);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA845x Sensor Configuration Failed, Err = %d\r\n", status);
        return -1;
    }
    PRINTF("\r\n MMA845x now active and entering data read loop... \r\n");

    for (;;) /* Forever loop */
    {
        /*! Wait for data ready from the MMA845x. */
        status = MMA845x_I2C_ReadData(&MMA845xdrv, mma845x_Fifo_Status, &fifoEvent);
        if (0 == (fifoEvent & MMA845x_F_STATUS_F_WMRK_FLAG_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Read the raw sensor data from the MMA845x. */
        status = MMA845x_I2C_ReadData(&MMA845xdrv, mma845x_Output_Values, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        for (uint8_t i = 0; i < FIFO_SIZE; i++)
        {
            /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
            rawData.accel[0] =
                ((int16_t)data[i * MMA845x_ACCEL_DATA_SIZE + 0] << 8) | data[i * MMA845x_ACCEL_DATA_SIZE + 1];
            rawData.accel[0] /= 4;
            rawData.accel[1] =
                ((int16_t)data[i * MMA845x_ACCEL_DATA_SIZE + 2] << 8) | data[i * MMA845x_ACCEL_DATA_SIZE + 3];
            rawData.accel[1] /= 4;
            rawData.accel[2] =
                ((int16_t)data[i * MMA845x_ACCEL_DATA_SIZE + 4] << 8) | data[i * MMA845x_ACCEL_DATA_SIZE + 5];
            rawData.accel[2] /= 4;
        }
        /* NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop.
         * Hence, we display only the last sample from each FIFO Burst Read. */
        PRINTF("\r\n Accel X = %d  Y = %d  Z = %d\r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(100 / FIFO_SIZE); /* Ask for user input after processing 100 samples. */
    }
}
