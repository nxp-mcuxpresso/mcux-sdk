/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  mma865x_freefall-detection.c
*  @brief The mma865x_freefall-detection.c file implements the ISSDK
*         MMA865x sensor example demonstrating configuring MMA8652 Accel
*         and enabling detection of freefall event.
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
/* FF_MT freefall counter register values for High resolution Mode and ODR = 200Hz.
 * These values have been derived based on the MMA865x DataSheet and Application Note AN4070 for MMA8451 (the same is
 * applicable to MMA865x too).
 * http://cache.freescale.com/files/sensors/doc/app_note/AN4070.pdf */
#define FF_MT_WT_DBCNT 0x18  /* Debounce count value. */
#define FF_MT_THS_VALUE 0x08 /* Threshold Value. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for freefall detection. */
const registerwritelist_t cMma865xConfigFreeFall[] ={
     /*! Configure the MMA865x to set FS Range as 2g. */
     {MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
     /*! Configure the MMA865x to set Debounce counter value. */
     {MMA865x_FF_MT_COUNT, FF_MT_WT_DBCNT, 0},
     /*! Configure the MMA865x to set Debounce counter to be cleared on favourable events and the thresholds . */
     {MMA865x_FF_MT_THS, MMA865x_FF_MT_THS_DBCNTM_INC_CLR | FF_MT_THS_VALUE,
      MMA865x_FF_MT_THS_DBCNTM_MASK | MMA865x_FF_MT_THS_THS_MASK},
     /*! Configure the MMA865x to set freefall Mode and enable all XYZ axis events and event latching. */
     {MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_OAE_FREEFALL | MMA865x_FF_MT_CFG_XEFE_EN |
      MMA865x_FF_MT_CFG_YEFE_EN | MMA865x_FF_MT_CFG_ZEFE_EN,MMA865x_FF_MT_CFG_OAE_MASK | MMA865x_FF_MT_CFG_XEFE_MASK |
      MMA865x_FF_MT_CFG_YEFE_MASK | MMA865x_FF_MT_CFG_ZEFE_MASK},
     /*! Configure the MMA865x to set interrupt polarity as Active High. */
     {MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
     /*! Configure the MMA865x to enable Interrupts for Data Ready. */
     {MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_FF_MT_EN, MMA865x_CTRL_REG4_INT_EN_FF_MT_MASK},
     /*! Configure the MMA865x to route Data Ready Interrupts to INT1. */
     {MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_FF_MT_INT1, MMA865x_CTRL_REG5_INT_CFG_FF_MT_MASK},
     /*! Configure the MMA865x to set ODR to 100Hz. */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_200HZ | MMA865x_CTRL_REG1_ACTIVE_ACTIVATED, MMA865x_CTRL_REG1_DR_MASK | MMA865x_CTRL_REG1_ACTIVE_MASK},
     __END_WRITE_DATA__};

/*! @brief Address of Freefall Status Register. */
const registerreadlist_t cMma865xFreeFallEvent[] = {{.readFrom = MMA865x_FF_MT_SRC, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gMma865xIntFlag = false;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! -----------------------------------------------------------------------
 *  @brief       This is the Sensor ISR implementation.
 *  @details     This function sets the flag which indicates if a new sample(s) is available for reading or new
 *               event has occurred.
 *  @param[in]   pUserData This is a void pointer to the instance of the user specific data structure for the ISR.
 *  @return      void  There is no return value.
 *  @constraints None
 *  @reeentrant  Yes
 *  -----------------------------------------------------------------------*/
void mma865x_isr_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gMma865xIntFlag = true;
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

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor driver example for Freefall Detection. \r\n");

    /*! Initialize MMA865x pin used by FRDM board */
    pGpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_isr_callback, NULL);

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
    PRINTF("\r\n Successfully Initialized Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA865x_I2C_SetIdleTask(&mma865xDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the MMA865x sensor for Freefall detection Mode. */
    status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigFreeFall);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied MMA865x Sensor Configuration for Freefall Detection\r\n");
    PRINTF("\r\n MMA865x is now active and detecting freefall... \r\n");

    for (;;) /* Forever loop */
    {        /* In ISR Mode we do not need to check Event Ready Register.
              * The receipt of interrupt will indicate Event has occured. */
        if (false == gMma865xIntFlag)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the event flag, it will be set again by the ISR. */
            gMma865xIntFlag = false;
        }

        /*! Display that a freefall event has been detected. */
        PRINTF("\r\n Freefall detected !!!\r\n");
    }
}
