/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxpq3115_fifo_interrupt.c
 * @brief The fxpq3115_fifo_interrupt.c file implements the ISSDK FXPQ3115BV sensor driver
 *        example demonstration with fifo in interrupt mode.
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

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "fxpq3115_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* Application Configurations Selections */
#define FIFO_WMRK_SIZE (8)     /* Buffer 8 Samples. */
#define FXPQ3115_DATA_SIZE (5) /* 3 byte Pressure/Altitude and 2 byte Temperature. */
/*! In FXPQ3115 the Auto Acquisition Time Step (ODR) can be set only in powers of 2 (i.e. 2^x, where x is the
 *  SAMPLING_EXPONENT).
 *  This gives a range of 1 second to 2^15 seconds (9 hours). */
#define FXPQ3115_SAMPLING_EXPONENT (0) /* 1 seconds. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for FIFO (buffered) mode @ default 1 sample per second with Interrupts. */
const registerwritelist_t B3115ConfigFIFOInt[] = {
    /* Set FIFO Mode and set FIFO Watermark Level. */
    {FXPQ3115_F_SETUP, FXPQ3115_F_SETUP_F_MODE_STOP_MODE | FIFO_WMRK_SIZE,
     FXPQ3115_F_SETUP_F_MODE_MASK | FXPQ3115_F_SETUP_F_WMRK_MASK},
    /* Enable Data Ready and Event flags for Pressure, Temperature or either. */
    {FXPQ3115_PT_DATA_CFG,
     FXPQ3115_PT_DATA_CFG_TDEFE_ENABLED | FXPQ3115_PT_DATA_CFG_PDEFE_ENABLED | FXPQ3115_PT_DATA_CFG_DREM_ENABLED,
     FXPQ3115_PT_DATA_CFG_TDEFE_MASK | FXPQ3115_PT_DATA_CFG_PDEFE_MASK | FXPQ3115_PT_DATA_CFG_DREM_MASK},
    /* Set Over Sampling Ratio to 128. */
    {FXPQ3115_CTRL_REG1, FXPQ3115_CTRL_REG1_OS_OSR_128, FXPQ3115_CTRL_REG1_OS_MASK},
    {FXPQ3115_CTRL_REG2, FXPQ3115_SAMPLING_EXPONENT, FXPQ3115_CTRL_REG2_ST_MASK},
    /* Set INT1 Active High. */
    {FXPQ3115_CTRL_REG3, FXPQ3115_CTRL_REG3_IPOL1_HIGH, FXPQ3115_CTRL_REG3_IPOL1_MASK},
    /* Enable Interrupts for FIFO Events. */
    {FXPQ3115_CTRL_REG4, FXPQ3115_CTRL_REG4_INT_EN_FIFO_INTENABLED, FXPQ3115_CTRL_REG4_INT_EN_FIFO_MASK},
    /* Route Interrupt to INT1. */
    {FXPQ3115_CTRL_REG5, FXPQ3115_CTRL_REG5_INT_CFG_FIFO_INT1, FXPQ3115_CTRL_REG5_INT_CFG_FIFO_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Status Register. */
const registerreadlist_t B3115Status[] = {{.readFrom = FXPQ3115_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Pressure+Temperature Data in FIFO Mode. */
const registerreadlist_t B3115OutputFIFO[] = {
    {.readFrom = FXPQ3115_OUT_P_MSB, .numBytes = FXPQ3115_DATA_SIZE * FIFO_WMRK_SIZE}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile uint8_t gB3115DataReady;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! -----------------------------------------------------------------------
 *  @brief       This is the Sensor Data Ready ISR implementation.
 *  @details     This function sets the flag which indicates if a new sample(s) is available for reading.
 *  @param[in]   pUserData This is a void pointer to the instance of the user specific data structure for the ISR.
 *  @return      void  There is no return value.
 *  @constraints None
 *  @reeentrant  Yes
 *  -----------------------------------------------------------------------*/
void fxpq3115_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gB3115DataReady = true;
}

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
    int16_t tempInDegrees;
    uint32_t pressureInPascals;
    int32_t status;
    uint8_t data[FXPQ3115_DATA_SIZE * FIFO_WMRK_SIZE];
    fxpq3115_pressuredata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    fxpq3115_i2c_sensorhandle_t fxpq3115Driver;
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXPQ3115 sensor driver example demonstration with interrupt mode.\r\n");

    /*! Initialize FXPQ3115 pin used by FRDM board */
    pGpioDriver->pin_init(&FXPQ3115_INT1, GPIO_DIRECTION_IN, NULL, &fxpq3115_int_data_ready_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

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

    gB3115DataReady = false;

    /*! Configure the FXPQ3115 sensor driver. */
    status = FXPQ3115_I2C_Configure(&fxpq3115Driver, B3115ConfigFIFOInt);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXPQ3115 Sensor Configuration Failed, Err = %d\r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXPQ3115 Sensor Configuration\r\n");

    for (;;) /* Forever loop (with logic optimized for FIFO Mode). */
    {        /* In ISR Mode we do not need to check Data Ready Register.
              * The receipt of interrupt will indicate data is ready. */
        if (false == gB3115DataReady)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gB3115DataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
            /* Read FIFO status, to clear sensor's INT.
             * Note: This is a special step in FIFO Mode particular to FXPQ3115, where we have to read F_STATUS to clear
             * the sensor's internal INT.  */
            FXPQ3115_I2C_ReadData(&fxpq3115Driver, B3115Status, (uint8_t *)&status);
        }

        /*! Read new raw sensor data from the FXPQ3115. */
        status = FXPQ3115_I2C_ReadData(&fxpq3115Driver, B3115OutputFIFO, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /* Reset Counters */
        pressureInPascals = 0;
        tempInDegrees = 0;

        for (uint8_t i = 0; i < FIFO_WMRK_SIZE; i++)
        { /*! Process all samples and convert the raw sensor data. */
            rawData.pressure = (uint32_t)((data[i * FXPQ3115_DATA_SIZE + 0]) << 16) |
                               ((data[i * FXPQ3115_DATA_SIZE + 1]) << 8) | ((data[i * FXPQ3115_DATA_SIZE + 2]));
            pressureInPascals += rawData.pressure / FXPQ3115_PRESSURE_CONV_FACTOR;

            rawData.temperature =
                (int16_t)((data[i * FXPQ3115_DATA_SIZE + 3]) << 8) | (data[i * FXPQ3115_DATA_SIZE + 4]);
            tempInDegrees += rawData.temperature / FXPQ3115_TEMPERATURE_CONV_FACTOR;
        }
        /* NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop. */
        PRINTF("\r\n Average Pressure    = %d Pa\r\n", pressureInPascals / FIFO_WMRK_SIZE);
        PRINTF("\r\n Average Temperature = %d degC\r\n", tempInDegrees / FIFO_WMRK_SIZE);
        ASK_USER_TO_RESUME(16 / FIFO_WMRK_SIZE); /* Ask for user input after processing 16 samples. */
    }
}
