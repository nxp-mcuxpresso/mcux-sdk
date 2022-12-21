/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma865x_interrupt.c
*   @brief The mma865x_interrupt.c file implements the ISSDK MMA865x sensor driver
*        example demonstration with Interrupt mode.
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
#include "mma865x_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MMA865x_ACCEL_DATA_SIZE (6) /* 2 byte X,Y,Z Axis Data each. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure MMA865x in non-FIFO and ISR mode. */
const registerwritelist_t cMma865xConfigInterrupt[] =
    {/*! Configure the MMA865x to set FS Range as 2g. */
     {MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
     /*! Configure the MMA865x to set ODR to 6.25Hz. */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_6_25HZ, MMA865x_CTRL_REG1_DR_MASK},
     /*! Configure the MMA865x to set High Resolution mode. */
     {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
     /*! Configure the MMA865x to set interrupt polarity as Active High. */
     {MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
     /*! Configure the MMA865x to enable Interrupts for Data Ready. */
     {MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_DRDY_EN, MMA865x_CTRL_REG4_INT_EN_DRDY_MASK},
     /*! Configure the MMA865x to route Data Ready Interrupts to INT1. */
     {MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_DRDY_INT1, MMA865x_CTRL_REG5_INT_CFG_DRDY_MASK},
     __END_WRITE_DATA__};

/*! Prepare the register read list to read the raw Accel data from MMA865x. */
const registerreadlist_t cMma865xOutputValues[] = {{.readFrom = MMA865x_OUT_X_MSB, .numBytes = MMA865x_ACCEL_DATA_SIZE},
                                                   __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gMma865xDataReady = false;

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
void mma865x_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gMma865xDataReady = true;
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
    int32_t status;
    uint8_t data[MMA865x_ACCEL_DATA_SIZE];
    mma865x_acceldata_t rawData;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;
    GENERIC_DRIVER_GPIO *gpioDriver = &Driver_GPIO_KSDK;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor driver example for Interrupt Mode.\r\n");

    /*! Initialize MMA865x pin used by FRDM board */
    gpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_int_data_ready_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    gpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

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

    /*! Configure the MMA865x sensor driver with No FIFO mode. */
    status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigInterrupt);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied MMA865x Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {        /* In ISR Mode we do not need to check Data Ready Register.
              * The receipt of interrupt will indicate data is ready. */
        if (false == gMma865xDataReady)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gMma865xDataReady = false;
            gpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read the raw sensor data from the MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xOutputValues, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | data[1];
        rawData.accel[0] /= 16;
        rawData.accel[1] = ((int16_t)data[2] << 8) | data[3];
        rawData.accel[1] /= 16;
        rawData.accel[2] = ((int16_t)data[4] << 8) | data[5];
        rawData.accel[2] /= 16;

        /* NOTE: PRINTF is relatively expensive in terms of CPU time, specially when used with-in execution loop. */
        PRINTF("\r\n Accel X = %d  Y = %d  Z = %d \r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(50); /* Ask for user input after processing 100 samples. */
    }
}
