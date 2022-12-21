/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls8962_orientation_detection.c
 * @brief The fxls8962_orientation_detection.c file implements the ISSDK FXLS8962 sensor
 *        driver example demonstration for Motion Activated Orientation detection.
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
#include "fxls8962_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MD_SDCD_WT_DBCNT 0x00 /* Debounce count value. */
#define OT_SDCD_WT_DBCNT 0x09 /* Debounce count value. */
#define SDCD_LTHS_LSB 0xC0    /* Lower Threshold LSB value. */
#define SDCD_LTHS_MSB 0x0F    /* Lower Threshold MSB value. */
#define SDCD_UTHS_LSB 0x40    /* Upper Threshold LSB value. */
#define SDCD_UTHS_MSB 0x00    /* Upper Threshold MSB value. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register Start Motion Detect Mode Register Write List. */
const registerwritelist_t cFxls8962ConfigMotionDetect[] = {
    /* Set Wake Mode ODR Rate as 0.781Hz. */
    {FXLS8962_SENS_CONFIG3, FXLS8962_SENS_CONFIG3_WAKE_ODR_0_781HZ, FXLS8962_SENS_CONFIG3_WAKE_ODR_MASK},
    {FXLS8962_SENS_CONFIG4, FXLS8962_SENS_CONFIG4_DRDY_PUL_DIS, FXLS8962_SENS_CONFIG4_DRDY_PUL_MASK},
    {FXLS8962_INT_EN, FXLS8962_INT_EN_SDCD_OT_EN_EN, 0},
    {FXLS8962_ORIENT_CONFIG, FXLS8962_ORIENT_CONFIG_ORIENT_ENABLE_DIS, FXLS8962_ORIENT_CONFIG_ORIENT_ENABLE_MASK},
    {FXLS8962_SDCD_CONFIG1,
     FXLS8962_SDCD_CONFIG1_X_OT_EN_EN | FXLS8962_SDCD_CONFIG1_Y_OT_EN_EN | FXLS8962_SDCD_CONFIG1_Z_OT_EN_EN, 0},
    {FXLS8962_SDCD_CONFIG2, FXLS8962_SDCD_CONFIG2_SDCD_EN_EN | FXLS8962_SDCD_CONFIG2_REF_UPDM_SDCD_REF |
                                FXLS8962_SDCD_CONFIG2_OT_DBCTM_CLEARED | FXLS8962_SDCD_CONFIG2_WT_DBCTM_CLEARED,
     0},
    /* Set SDCD Debounce counter value. */
    {FXLS8962_SDCD_WT_DBCNT, MD_SDCD_WT_DBCNT, 0},
    /* Set SDCD Lower Threshold LSB value. */
    {FXLS8962_SDCD_LTHS_LSB, SDCD_LTHS_LSB, 0},
    /* Set SDCD Lower Threshold MSB value. */
    {FXLS8962_SDCD_LTHS_MSB, SDCD_LTHS_MSB, 0},
    /* Set SDCH Upper Threshold LSB value. */
    {FXLS8962_SDCD_UTHS_LSB, SDCD_UTHS_LSB, 0},
    /* Set SDCH Upper Threshold MSB value. */
    {FXLS8962_SDCD_UTHS_MSB, SDCD_UTHS_MSB, 0},
    __END_WRITE_DATA__};

/*! @brief Register Start Motion Detect Mode Register Write List. */
const registerwritelist_t cFxls8962ConfigOrientDetect[] = {
    /* Set Wake Mode ODR Rate as 1.563Hz. */
    {FXLS8962_SENS_CONFIG3, FXLS8962_SENS_CONFIG3_WAKE_ODR_1_563HZ, FXLS8962_SENS_CONFIG3_WAKE_ODR_MASK},
    /* Pulse Generation Enabled */
    {FXLS8962_SENS_CONFIG4, FXLS8962_SENS_CONFIG4_DRDY_PUL_EN, FXLS8962_SENS_CONFIG4_DRDY_PUL_MASK},
    {FXLS8962_INT_EN, FXLS8962_INT_EN_DRDY_EN_EN, 0},
    {FXLS8962_ORIENT_CONFIG, FXLS8962_ORIENT_CONFIG_ORIENT_ENABLE_EN, FXLS8962_ORIENT_CONFIG_ORIENT_ENABLE_MASK},
    {FXLS8962_SDCD_CONFIG1, FXLS8962_SDCD_CONFIG1_WT_ELE_EN | FXLS8962_SDCD_CONFIG1_X_WT_EN_EN |
                                FXLS8962_SDCD_CONFIG1_Y_WT_EN_EN | FXLS8962_SDCD_CONFIG1_Z_WT_EN_EN,
     0},
    {FXLS8962_SDCD_CONFIG2, FXLS8962_SDCD_CONFIG2_SDCD_EN_EN | FXLS8962_SDCD_CONFIG2_REF_UPDM_SDCD_REF |
                                FXLS8962_SDCD_CONFIG2_OT_DBCTM_CLEARED | FXLS8962_SDCD_CONFIG2_WT_DBCTM_CLEARED,
     0},
    /* Set SDCD Debounce counter value. */
    {FXLS8962_SDCD_WT_DBCNT, OT_SDCD_WT_DBCNT, 0},
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
const registerreadlist_t cFxls8962SDCDEvent[] = {{.readFrom = FXLS8962_SDCD_INT_SRC2, .numBytes = 1},
                                                 __END_READ_DATA__};

const registerreadlist_t cFxls8962OutputOrientStatus[] = {{.readFrom = FXLS8962_ORIENT_STATUS, .numBytes = 1},
                                                          __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gFxls8962EventReady;

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
void fxls8962_int_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    gFxls8962EventReady = true;
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
    bool motionDetect;
    uint8_t orientStatus;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    fxls8962_i2c_sensorhandle_t fxls8962Driver;
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXLS8962 sensor driver example for Orientation and Motion Detection.\r\n");

    /*! Initialize FXLS8962 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS8962_INT1, GPIO_DIRECTION_IN, NULL, &fxls8962_int_callback, NULL);

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

    /*! Initialize FXLS8962 sensor driver. */
    status = FXLS8962_I2C_Initialize(&fxls8962Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLS8962_I2C_ADDR,
                                     FXLS8962_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXLS8962_I2C_SetIdleTask(&fxls8962Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    for (;;) /* Forever loop for Motion Detection */
    {
        /* Apply FXLS8962 Configuration for Motion Detection. */
        status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962ConfigMotionDetect);
        if (SENSOR_ERROR_NONE != status)
        {
            PRINTF("\r\n Write FXLS8962 Motion Configuration Failed!\r\n");
            return -1;
        }

        motionDetect = true;
        gFxls8962EventReady = false;
        PRINTF("\r\n Waiting for Motion | MCU going to Deep Sleep Mode ...\r\n");

        for (;;) /* Loop for Orientation Detection */
        {        /* In ISR Mode we do not need to check Data Ready Register.
                  * The receipt of interrupt will indicate event is ready. */
            if (false == gFxls8962EventReady)
            { /* Loop, if new sample is not available. */
                SMC_SetPowerModeWait(SMC);
                continue;
            }
            else
            { /*! Clear the data ready flag, it will be set again by the ISR. */
                gFxls8962EventReady = false;
            }

            if (motionDetect)
            { /*! Display that a Motion event has been detected. */
                PRINTF("\r\n Motion detected ...\r\n");

                /* Apply FXLS8962 Configuration for Orientation Detection. */
                status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962ConfigOrientDetect);
                if (SENSOR_ERROR_NONE != status)
                {
                    PRINTF("\r\n Write FXLS8962 Orientation Configuration Failed!\r\n");
                    return -1;
                }
                motionDetect = false;
            }
            else
            { /*! Read the Orientation Status from the FXLS8962. */
                status = FXLS8962_I2C_ReadData(&fxls8962Driver, cFxls8962OutputOrientStatus, &orientStatus);
                if (ARM_DRIVER_OK != status)
                {
                    PRINTF("\r\n Read Orientation Failed!\r\n");
                    return -1;
                }

                if (((orientStatus & FXLS8962_ORIENT_STATUS_NEW_ORIENT_MASK) ==
                     FXLS8962_ORIENT_STATUS_NEW_ORIENT_CHANGED) &&
                    ((orientStatus & FXLS8962_ORIENT_STATUS_LO_MASK) == FXLS8962_ORIENT_STATUS_LO_NOT_DETECTED))
                {
                    if ((orientStatus & FXLS8962_ORIENT_STATUS_LAPO_MASK) == FXLS8962_ORIENT_STATUS_LAPO_UP)
                    {
                        PRINTF("\r\n Portrait Up ...\r\n");
                    }
                    if ((orientStatus & FXLS8962_ORIENT_STATUS_LAPO_MASK) == FXLS8962_ORIENT_STATUS_LAPO_DOWN)
                    {
                        PRINTF("\r\n Portrait Down ...\r\n");
                    }
                    if ((orientStatus & FXLS8962_ORIENT_STATUS_LAPO_MASK) == FXLS8962_ORIENT_STATUS_LAPO_RIGHT)
                    {
                        PRINTF("\r\n Landscape Right ...\r\n");
                    }
                    if ((orientStatus & FXLS8962_ORIENT_STATUS_LAPO_MASK) == FXLS8962_ORIENT_STATUS_LAPO_LEFT)
                    {
                        PRINTF("\r\n Landscape Left ...\r\n");
                    }
                }

                if (((orientStatus & FXLS8962_ORIENT_STATUS_NEW_ORIENT_MASK) ==
                     FXLS8962_ORIENT_STATUS_NEW_ORIENT_CHANGED) &&
                    ((orientStatus & FXLS8962_ORIENT_STATUS_LO_MASK) == FXLS8962_ORIENT_STATUS_LO_DETECTED))
                {
                    if ((orientStatus & FXLS8962_ORIENT_STATUS_BAFRO_MASK) == FXLS8962_ORIENT_STATUS_BAFRO_FRONT)
                    {
                        PRINTF("\r\n Front Side ...\r\n");
                    }
                    if ((orientStatus & FXLS8962_ORIENT_STATUS_BAFRO_MASK) == FXLS8962_ORIENT_STATUS_BAFRO_BACK)
                    {
                        PRINTF("\r\n Back Side ...\r\n");
                    }
                }

                status = FXLS8962_I2C_ReadData(&fxls8962Driver, cFxls8962SDCDEvent, &orientStatus);
                if (ARM_DRIVER_OK != status)
                {
                    PRINTF("\r\n Read SDCD Failed!\r\n");
                    return -1;
                }
                if ((orientStatus & FXLS8962_SDCD_INT_SRC2_WT_EA_MASK) == FXLS8962_SDCD_INT_SRC2_WT_EA_EVENT_YES)
                {
                    break;
                }
            }
        }
    }
}
