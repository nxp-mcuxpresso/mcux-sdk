/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  fxls8471q_spi_poll.c
 * @brief The fxls8471q_poll_spi.c file implements the ISSDK FXLS8471Q sensor driver
 * example demonstration for SPI Mode with polling.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "fxls8471q_drv.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_SPI.h"

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure FXLS8471Q in non-FIFO mode. */
const registerwritelist_t cFxls8471q_Config_Normal[] = {
    /*! Configure CTRL_REG1 register to put FXLS8471Q to 12.5Hz sampling rate. */
    {FXLS8471Q_CTRL_REG1, FXLS8471Q_CTRL_REG1_DR_12DOT5HZ, FXLS8471Q_CTRL_REG1_DR_MASK},
    __END_WRITE_DATA__};

/*! Prepare the register read list to read FXLS8471Q DataReady status. */
const registerreadlist_t cFxls8471q_DataReady[] = {{.readFrom = FXLS8471Q_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! Prepare the register read list to read the raw accel data from the FXLS8471Q. */
const registerreadlist_t cFxls8471q_Output_Values[] = {
    {.readFrom = FXLS8471Q_OUT_X_MSB, .numBytes = FXLS8471Q_ACCEL_DATA_SIZE}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! -----------------------------------------------------------------------
 *  @brief       This is the The main function implementation.
 *  @details     This function invokes board initializes routines, then then brings up the sensor and
 *               finally enters an endless loop to continuously read available samples.
 *  @param[in]   void This is no input parameter.
 *  @return      void  There is no return value.
 *  @constraints None
 *  @reeentrant  No
 *  -----------------------------------------------------------------------*/
int main(void)
{
    int32_t status;
    uint8_t gFxls8471qDataReady;
    uint8_t data[FXLS8471Q_ACCEL_DATA_SIZE];
    fxls8471q_acceldata_t rawData;

    ARM_DRIVER_SPI *pSPIdriver = &SPI_S_DRIVER;
    fxls8471q_spi_sensorhandle_t fxls8471qDriver;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXLS8471Q sensor driver example demonstration for SPI with Poll Mode.\r\n");

    /*! Initialize the SPI driver. */
    status = pSPIdriver->Initialize(SPI_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n SPI Initialization Failed\r\n");
        return -1;
    }

    /*! Set the SPI Power mode. */
    status = pSPIdriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n SPI Power Mode setting Failed\r\n");
        return -1;
    }

    /*! Set the SPI Slave speed. */
#ifndef FRDM_KL27Z
    status = pSPIdriver->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL1_CPHA0, SPI_S_BAUDRATE);
#else
    status = pSPIdriver->Control(ARM_SPI_MODE_MASTER | ARM_SPI_SS_MASTER_HW_OUTPUT, SPI_S_BAUDRATE);
#endif
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n SPI Control Mode setting Failed\r\n");
        return -1;
    }

    /*! Initialize the FXLS8471Q sensor driver. */
    status = FXLS8471Q_SPI_Initialize(&fxls8471qDriver, &SPI_S_DRIVER, SPI_S_DEVICE_INDEX, &FXLS8471_SPI_CS,
                                      FXLS8471Q_WHO_AM_I_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLS8471Q Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed FXLS8471Q Sensor\r\n");

    /*!  Set the task to be executed while waiting for SPI transactions to complete. */
    FXLS8471Q_SPI_SetIdleTask(&fxls8471qDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the FXLS8471Q sensor driver. */
    status = FXLS8471Q_SPI_Configure(&fxls8471qDriver, cFxls8471q_Config_Normal);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLS8471Q Sensor Configuration Failed, Err = %d\r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXLS8471Q Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {
        /*! Wait for data ready from the FXLS8471Q. */
        status = FXLS8471Q_SPI_ReadData(&fxls8471qDriver, cFxls8471q_DataReady, &gFxls8471qDataReady);
        if (0 == (gFxls8471qDataReady & FXLS8471Q_STATUS_ZYXDR_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Read the raw sensor data from the FXLS8471Q. */
        status = FXLS8471Q_SPI_ReadData(&fxls8471qDriver, cFxls8471q_Output_Values, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\nRead Failed.\r\n");
            return -1; /* Read did not work, exit. */
        }

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | (int16_t)data[1];
        rawData.accel[0] /= 4;
        rawData.accel[1] = ((int16_t)data[2] << 8) | (int16_t)data[3];
        rawData.accel[1] /= 4;
        rawData.accel[2] = ((int16_t)data[4] << 8) | (int16_t)data[5];
        rawData.accel[2] /= 4;

        /* NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop. */
        PRINTF("\r\n Accel X = %d  Y = %d  Z = %d \r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(100); /* Ask for user input after processing 100 samples. */
    }
}
