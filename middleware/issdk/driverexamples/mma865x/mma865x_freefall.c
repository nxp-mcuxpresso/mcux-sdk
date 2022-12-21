/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  mma865x_freefall.c
 *  @brief The mma865x_freefall.c file implements the ISSDK MMA865x sensor driver
 *        example demonstration for Freefall Detection.
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
/* FF_MT freefall counter register values for High resolution Mode and ODR = 100Hz.
 * These values have been derived based on the MMA865x DataSheet and Application Note AN4070 for MMA8451 (the same is
 * applicable to MMA865x too).
 * http://cache.freescale.com/files/sensors/doc/app_note/AN4070.pdf */
#define FF_MT_WT_DBCNT 0x28  /* Debounce count value. */
#define FF_MT_THS_VALUE 0x03 /* Threshold Value. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for freefall detection. */
const registerwritelist_t cMma865xConfigFreeFall[] =
    {/*! Configure the MMA865x to set FS Range as 2g. */
     {MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
     /*! Configure the MMA865x to set ODR to 100Hz. */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_100HZ, MMA865x_CTRL_REG1_DR_MASK},
     /*! Configure the MMA865x to set High Resolution mode. */
     {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
     /*! Configure the MMA865x to set interrupt polarity as Active High. */
     {MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
     /*! Configure the MMA865x to enable Interrupts for Data Ready. */
     {MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_FF_MT_EN, MMA865x_CTRL_REG4_INT_EN_FF_MT_MASK},
     /*! Configure the MMA865x to route Data Ready Interrupts to INT1. */
     {MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_FF_MT_INT1, MMA865x_CTRL_REG5_INT_CFG_FF_MT_MASK},
     /*! Configure the MMA865x to set freefall Mode and enable all XYZ axis events and event latching. */
     {MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_ELE_EN | MMA865x_FF_MT_CFG_OAE_FREEFALL | MMA865x_FF_MT_CFG_XEFE_EN |
                             MMA865x_FF_MT_CFG_YEFE_EN | MMA865x_FF_MT_CFG_ZEFE_EN,
      MMA865x_FF_MT_CFG_ELE_MASK | MMA865x_FF_MT_CFG_OAE_MASK | MMA865x_FF_MT_CFG_XEFE_MASK |
          MMA865x_FF_MT_CFG_YEFE_MASK | MMA865x_FF_MT_CFG_ZEFE_MASK},
     /*! Configure the MMA865x to set Debounce counter to be cleared on favourable events and the thresholds . */
     {MMA865x_FF_MT_THS, MMA865x_FF_MT_THS_DBCNTM_INC_CLR | FF_MT_THS_VALUE,
      MMA865x_FF_MT_THS_DBCNTM_MASK | MMA865x_FF_MT_THS_THS_MASK},
     /*! Configure the MMA865x to set Debounce counter value. */
     {MMA865x_FF_MT_COUNT, FF_MT_WT_DBCNT, 0},
     __END_WRITE_DATA__};

/*! @brief Address of Freefall Status Register. */
const registerreadlist_t cMma865xFreeFallEvent[] = {{.readFrom = MMA865x_FF_MT_SRC, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gMma865xEventReady;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! @brief This is the Sensor Event Ready ISR implementation. */
void mma865x_int_event_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gMma865xEventReady = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t dataReady;
    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor driver example for Freefall Detection. \r\n");

    /*! Initialize MMA865x pin used by FRDM board */
    pGpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_int_event_ready_callback, NULL);

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

    /* Set data not ready, event data will be available after sensor is configured and free fall detected. */
    gMma865xEventReady = false;
    dataReady = 0;

    /*! Configure the MMA865x sensor for Freefall detection Mode. */
    status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigFreeFall);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n MMA865x now active and detecting freefall... \r\n");

    for (;;) /* Forever loop */
    {        /* In ISR Mode we do not need to check Event Ready Register.
              * The receipt of interrupt will indicate Event has occured. */
        if (false == gMma865xEventReady)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gMma865xEventReady = false;
        }

        /*! Read the Freefall event FLAGs from MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xFreeFallEvent, &dataReady);
        if (SENSOR_ERROR_NONE != status)
        {
            PRINTF("\r\n Read Failed\r\n");
            return -1;
        }

        if (MMA865x_FF_MT_SRC_EA_NONE == (dataReady & MMA865x_FF_MT_SRC_EA_MASK))
        { /* Loop, if new event is not detected. */
            continue;
        }

        /*! Display that a freefall event has been detected. */
        PRINTF("\r\n Freefall detected !!!\r\n");
    }
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
