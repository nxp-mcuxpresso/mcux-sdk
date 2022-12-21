/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls8962_freefall.c
 * @brief The fxls8962_freefall.c file implements the ISSDK FXLS8962 sensor driver
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

/* ISSDK Includes */
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "fxls8962_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* SDCD free-fall counter register values.
 * These values have been derived form the Application Note AN4070 for MMA8451 (the same is applicable to FXLS8962 too).
 * http://cache.freescale.com/files/sensors/doc/app_note/AN4070.pdf */
#define SDCD_WT_DBCNT 0x0A /* Debounce count value. */
#define SDCD_LTHS_LSB 0x33 /* Lower Threshold LSB value. */
#define SDCD_LTHS_MSB 0x0F /* Lower Threshold MSB value. */
#define SDCD_UTHS_LSB 0xCD /* Upper Threshold LSB value. */
#define SDCD_UTHS_MSB 0x00 /* Upper Threshold MSB value. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for free-fall detection. */
const registerwritelist_t cFxls8962ConfigFreeFall[] = {
    /* Set Wake Mode ODR Rate as 100Hz. */
    {FXLS8962_SENS_CONFIG3, FXLS8962_SENS_CONFIG3_WAKE_ODR_100HZ, FXLS8962_SENS_CONFIG3_WAKE_ODR_MASK},
    /* Enable Within-Threshold Event-Laching-Enable and X,Y,Z Axis functions. */
    {FXLS8962_SDCD_CONFIG1, FXLS8962_SDCD_CONFIG1_WT_ELE_EN | FXLS8962_SDCD_CONFIG1_X_WT_EN_EN |
                                FXLS8962_SDCD_CONFIG1_Y_WT_EN_EN | FXLS8962_SDCD_CONFIG1_Z_WT_EN_EN,
     FXLS8962_SDCD_CONFIG1_WT_ELE_MASK | FXLS8962_SDCD_CONFIG1_X_WT_EN_MASK | FXLS8962_SDCD_CONFIG1_Y_WT_EN_MASK |
         FXLS8962_SDCD_CONFIG1_Z_WT_EN_MASK},
    /* Enable SDCD function; Set SDCD internal reference values update mode to fixed value; Set Debounce counter to be
       cleared whenever the SDCD within thresholds. */
    {FXLS8962_SDCD_CONFIG2, FXLS8962_SDCD_CONFIG2_SDCD_EN_EN | FXLS8962_SDCD_CONFIG2_REF_UPDM_FIXED_VAL |
                                FXLS8962_SDCD_CONFIG2_WT_DBCTM_CLEARED,
     FXLS8962_SDCD_CONFIG2_SDCD_EN_MASK | FXLS8962_SDCD_CONFIG2_REF_UPDM_MASK | FXLS8962_SDCD_CONFIG2_WT_DBCTM_MASK},
    /* Set WT INT Enable. */
    {FXLS8962_INT_EN, FXLS8962_INT_EN_SDCD_WT_EN_EN, FXLS8962_INT_EN_SDCD_WT_EN_MASK},

    /* Set SDCD Debounce counter value. */
    {FXLS8962_SDCD_WT_DBCNT, SDCD_WT_DBCNT, 0},
    /* Set SDCD Lower Threshold LSB value. */
    {FXLS8962_SDCD_LTHS_LSB, SDCD_LTHS_LSB, 0},
    /* Set SDCD Lower Threshold MSB value. */
    {FXLS8962_SDCD_LTHS_MSB, SDCD_LTHS_MSB, 0},
    /* Set SDCH Upper Threshold LSB value. */
    {FXLS8962_SDCD_UTHS_LSB, SDCD_UTHS_LSB, 0},
    /* Set SDCH Upper Threshold MSB value. */
    {FXLS8962_SDCD_UTHS_MSB, SDCD_UTHS_MSB, 0},
    __END_WRITE_DATA__};

/*! @brief Address of SDCD Status Register. */
const registerreadlist_t cFxls8962FreeFallEvent[] = {{.readFrom = FXLS8962_SDCD_INT_SRC2, .numBytes = 1},
                                                     __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gFxls8962EventReady = false;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! @brief This is the Sensor Data Ready ISR implementation. */
void fxls8962_int_event_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gFxls8962EventReady = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t whoami;
    uint8_t dataReady;
    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    fxls8962_i2c_sensorhandle_t fxls8962Driver;
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXLS8962 sensor driver example for Freefall Detection. \r\n");

    /*! Initialize FXLS8962 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS8962_INT1, GPIO_DIRECTION_IN, NULL, &fxls8962_int_event_ready_callback, NULL);

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

    /*! Initialize the FXLS8962 sensor driver. */
    status = FXLS8962_I2C_Initialize(&fxls8962Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLS8962_I2C_ADDR,
                                     &whoami);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    if ((FXLS8964_WHOAMI_VALUE == whoami) || (FXLS8967_WHOAMI_VALUE == whoami))
    {
    	PRINTF("\r\n Successfully Initialized Gemini with WHO_AM_I = 0x%X\r\n", whoami);
    }
    else if (FXLS8974_WHOAMI_VALUE == whoami)
    {
    	PRINTF("\r\n Successfully Initialized Timandra with WHO_AM_I = 0x%X\r\n", whoami);
    }
    else if (FXLS8962_WHOAMI_VALUE == whoami)
    {
    	PRINTF("\r\n Successfully Initialized Newstein with WHO_AM_I = 0x%X\r\n", whoami);
    }
    else
    {
    	PRINTF("\r\n Bad WHO_AM_I = 0x%X\r\n", whoami);
    }

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXLS8962_I2C_SetIdleTask(&fxls8962Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /* Set data not ready, event data will be available after sensor is configured and free fall detected. */
    dataReady = 0;

    /*! Configure the FXLS8962 sensor for Freefall detection Mode. */
    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962ConfigFreeFall);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLS8962 Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n FXLS8962 now active and detecting freefall... \r\n");

    for (;;) /* Forever loop */
    {        /* In ISR Mode we do not need to check Data Ready Register.
              * The receipt of interrupt will indicate data is ready. */
        if (false == gFxls8962EventReady)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gFxls8962EventReady = false;
        }

        /*! Read the Freefall event FLAGs from FXLS8962. */
        status = FXLS8962_I2C_ReadData(&fxls8962Driver, cFxls8962FreeFallEvent, &dataReady);
        if (SENSOR_ERROR_NONE != status)
        {
            PRINTF("\r\n Read Failed\r\n");
            return -1;
        }

        if (FXLS8962_SDCD_INT_SRC2_WT_EA_EVENT_NO == (dataReady & FXLS8962_SDCD_INT_SRC2_WT_EA_MASK))
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
