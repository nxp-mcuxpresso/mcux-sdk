/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  fxls8962_fifo_spi.c
 *  @brief The fxls8962_fifo_spi.c file implements the ISSDK FXLS8962 SPI sensor driver
 *         example demonstration for FIFO Mode.
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
#include "fxls8962_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_SPI.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXLS8962_DATA_SIZE (6)
#define FXLS8962_FIFO_WMRK_SIZE (16)

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*! @brief Register settings for FIFO (buffered) mode. */
const registerwritelist_t cFxls8962ConfigFIFO[] = {
    /* Set Full-scale range as 2G. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_2G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    /* Set Wake Mode ODR Rate as 12.5Hz. */
    {FXLS8962_SENS_CONFIG3, FXLS8962_SENS_CONFIG3_WAKE_ODR_12_5HZ, FXLS8962_SENS_CONFIG3_WAKE_ODR_MASK},
    /* Set Buffering Mode as Stop-when-Full.  */
    {FXLS8962_BUF_CONFIG1, FXLS8962_BUF_CONFIG1_BUF_MODE_STOP_MODE, FXLS8962_BUF_CONFIG1_BUF_MODE_MASK},
    /* Set FIFO Water Mark. */
    {FXLS8962_BUF_CONFIG2, FXLS8962_FIFO_WMRK_SIZE, FXLS8962_BUF_CONFIG2_BUF_WMRK_MASK},
    /* Enable Interrupts for FIFO Watermark Events. */
    {FXLS8962_INT_EN, FXLS8962_INT_EN_BUF_EN_EN, FXLS8962_INT_EN_BUF_EN_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Raw Accel Data in FIFO Mode. */
const registerreadlist_t cFxls8962OutputFIF0[] = {
    {.readFrom = FXLS8962_BUF_X_LSB, .numBytes = FXLS8962_DATA_SIZE * FXLS8962_FIFO_WMRK_SIZE}, __END_READ_DATA__};

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
volatile bool gFxls8962DataReady = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief The Data ready ISR callback function
 */
void fxls8962_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gFxls8962DataReady = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t i, data[FXLS8962_DATA_SIZE * FXLS8962_FIFO_WMRK_SIZE];
    fxls8962_acceldata_t rawData;

    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;
    ARM_DRIVER_SPI *pSPIdriver = &SPI_S_DRIVER;
    fxls8962_spi_sensorhandle_t fxls8962Driver;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXLS8962 sensor driver example demonstration for SPI with FIFO Mode.\r\n");

    /*! Initialize FXLS8962 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS8962_INT1, GPIO_DIRECTION_IN, NULL, &fxls8962_int_data_ready_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

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
    status = pSPIdriver->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0, SPI_S_BAUDRATE);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n SPI Control Mode setting Failed\r\n");
        return -1;
    }

    /*! Initialize FXLS8962 sensor driver. */
    status = FXLS8962_SPI_Initialize(&fxls8962Driver, &SPI_S_DRIVER, SPI_S_DEVICE_INDEX, &FXLS8962_CS,
                                     FXLS8962_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLS8962 Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed FXLS8962 Sensor\r\n");

    /*!  Set the task to be executed while waiting for SPI transactions to complete. */
    FXLS8962_SPI_SetIdleTask(&fxls8962Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the FXLS8962 sensor. */
    status = FXLS8962_SPI_Configure(&fxls8962Driver, cFxls8962ConfigFIFO);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLS8962 Sensor Configuration Failed, Err = %d\r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXLS8962 Sensor Configuration\r\n");

    gFxls8962DataReady = false;
    for (;;) /* Forever loop */
    {        /* In ISR Mode we do not need to check Data Ready Register.
              * The receipt of interrupt will indicate data is ready. */
        if (false == gFxls8962DataReady)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gFxls8962DataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read new raw sensor data from the FXLS8962. */
        status = FXLS8962_SPI_ReadData(&fxls8962Driver, cFxls8962OutputFIF0, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        for (i = 0; i < FXLS8962_FIFO_WMRK_SIZE; i++)
        { /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
            rawData.accel[0] = ((int16_t)data[i * FXLS8962_DATA_SIZE + 1] << 8) | data[i * FXLS8962_DATA_SIZE + 0];
            rawData.accel[1] = ((int16_t)data[i * FXLS8962_DATA_SIZE + 3] << 8) | data[i * FXLS8962_DATA_SIZE + 2];
            rawData.accel[2] = ((int16_t)data[i * FXLS8962_DATA_SIZE + 5] << 8) | data[i * FXLS8962_DATA_SIZE + 4];
        }

        /*! Display to the debug port the last sample.
         *  NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop. */
        PRINTF("\r\nX=%5d Y=%5d Z=%5d\r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(8); /* Ask for user input after processing 8 FIFOs. */
    }
}
