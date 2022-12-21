/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxos8700_poll.c
 * @brief The fxos8700_poll.c file implements the ISSDK FXOS8700 sensor driver
 *        example demonstration with polling mode.
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
#include "fxos8700_drv.h"

/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
#define RAW_ACCELMAG_DATA_SIZE (12)

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*! Prepare the register write list to configure FXOS8700 in Hybrid mode. */
const registerwritelist_t fxos8700_Config_Hybrid[] = {
    /*! System and Control registers. */
    /*! Configure the FXOS8700 to 25Hz Hybrid sampling rate. */
    {FXOS8700_CTRL_REG1, FXOS8700_CTRL_REG1_DR_HYBRID_25_HZ, FXOS8700_CTRL_REG1_DR_MASK},
    {FXOS8700_M_CTRL_REG1, FXOS8700_M_CTRL_REG1_M_ACAL_EN | FXOS8700_M_CTRL_REG1_M_HMS_HYBRID_MODE,
                           FXOS8700_M_CTRL_REG1_M_ACAL_MASK | FXOS8700_M_CTRL_REG1_M_HMS_MASK}, /*! Enable the Hybrid Mode. */
    {FXOS8700_M_CTRL_REG2, FXOS8700_M_CTRL_REG2_M_AUTOINC_HYBRID_MODE | FXOS8700_M_CTRL_REG2_M_RST_CNT_DISABLE,
                           FXOS8700_M_CTRL_REG2_M_AUTOINC_MASK | FXOS8700_M_CTRL_REG2_M_RST_CNT_MASK}, /*! Enable the Data read with Hybrid Mode. */
    __END_WRITE_DATA__};

/*! Command definition to read the Data Ready Status */
const registerreadlist_t FXOS8700_STATUS_READ[] = {{.readFrom = FXOS8700_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! Command definition to read the Accel + Mag Data */
const registerreadlist_t FXOS8700_ACCELMAG_READ[] = {{.readFrom = FXOS8700_OUT_X_MSB, .numBytes = 12},
                                                     __END_READ_DATA__};

/*! Command definition to read the Accel + Mag Data (in 2 TXNs). */
const registerreadlist_t FXOS8700_ACCEL_MAG_READ[] = {{.readFrom = FXOS8700_OUT_X_MSB, .numBytes = 6},
                                                      {.readFrom = FXOS8700_M_OUT_X_MSB, .numBytes = 6},
                                                      __END_READ_DATA__};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t dataReady;
    uint8_t data[RAW_ACCELMAG_DATA_SIZE];
    fxos8700_accelmagdata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    fxos8700_i2c_sensorhandle_t FXOS8700drv;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXOS8700 sensor driver example demonstration with poll mode\r\n");

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

    /*! Initialize the FXOS8700 sensor driver. */
    status = FXOS8700_I2C_Initialize(&FXOS8700drv, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXOS8700_I2C_ADDR,
                                     FXOS8700_WHO_AM_I_PROD_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    //FXOS8700_I2C_SetIdleTask(&FXOS8700drv, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the fxos8700 sensor driver. */
    status = FXOS8700_I2C_Configure(&FXOS8700drv, fxos8700_Config_Hybrid);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXOS8700 Sensor Configuration Failed, Err = %d\r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXOS8700 Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {
        /*! Wait for data ready from the FXOS8700. */
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, FXOS8700_STATUS_READ, &dataReady);
        if (0 == (dataReady & FXOS8700_DR_STATUS_ZYXDR_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Read the raw sensor data from the fxos8700. */
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, FXOS8700_ACCELMAG_READ, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | data[1];
        rawData.accel[0] /= 4;
        rawData.accel[1] = ((int16_t)data[2] << 8) | data[3];
        rawData.accel[1] /= 4;
        rawData.accel[2] = ((int16_t)data[4] << 8) | data[5];
        rawData.accel[2] /= 4;
        rawData.mag[0] = ((int16_t)data[6] << 8) | data[7];
        rawData.mag[1] = ((int16_t)data[8] << 8) | data[9];
        rawData.mag[2] = ((int16_t)data[10] << 8) | data[11];

        /* NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop. */
        PRINTF("\r\n Accel X = %d  Y = %d  Z = %d\r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        PRINTF("\r\n Mag   X = %d  Y = %d  Z = %d\r\n", rawData.mag[0], rawData.mag[1], rawData.mag[2]);
        ASK_USER_TO_RESUME(50); /* Ask for user input after processing 100 samples. */
    }
}
