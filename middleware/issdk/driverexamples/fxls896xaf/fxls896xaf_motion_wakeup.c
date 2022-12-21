/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  fxls896x_motion_wakeup.c
 *  @brief The fxls896x_motion_wakeup.c file implements the ISSDK FXLS896xAF I2C sensor driver
 *         example demonstrating motion detection and Auto-Wake/Sleep features.
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
#include "fxls896x_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_I2C.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXLS8964_DATA_SIZE      6
#define FXLS8964_STANDBY_MODE   0
#define FXLS8964_ACTIVE_MODE    1
//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for configuring SDCD-OT for tap-detection and Auto-Wake/Sleep in interrupt mode. */
const registerwritelist_t cFxls896xAwsConfig[] = {
    /* Set Full-scale range as 4G. */
    {FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_FSR_4G, FXLS896x_SENS_CONFIG1_FSR_MASK},
    /* Set Wake ODR as 400Hz & Sleep Mode ODR as 6.25Hz. */
    {FXLS896x_SENS_CONFIG3, FXLS896x_SENS_CONFIG3_WAKE_ODR_400HZ | FXLS896x_SENS_CONFIG3_SLEEP_ODR_6_25HZ, FXLS896x_SENS_CONFIG3_WAKE_ODR_MASK | FXLS896x_SENS_CONFIG3_SLEEP_ODR_MASK},
    /* Enable SDCD OT for all 3 axes X, Y & Z and within-thresholds event latch disabled. */
    {FXLS896x_SDCD_CONFIG1, FXLS896x_SDCD_CONFIG1_X_OT_EN_EN | FXLS896x_SDCD_CONFIG1_Y_OT_EN_EN | FXLS896x_SDCD_CONFIG1_Z_OT_EN_EN | FXLS896x_SDCD_CONFIG1_OT_ELE_DIS,
    		FXLS896x_SDCD_CONFIG1_X_OT_EN_MASK | FXLS896x_SDCD_CONFIG1_Y_OT_EN_MASK | FXLS896x_SDCD_CONFIG1_Z_OT_EN_MASK | FXLS896x_SDCD_CONFIG1_OT_ELE_MASK},
    /* Enabling SDCD and Relative Data (N) � Data (N-1) mode for transient detection */
    {FXLS896x_SDCD_CONFIG2, FXLS896x_SDCD_CONFIG2_SDCD_EN_EN | FXLS896x_SDCD_CONFIG2_REF_UPDM_SDCD_REF, FXLS896x_SDCD_CONFIG2_SDCD_EN_MASK | FXLS896x_SDCD_CONFIG2_REF_UPDM_MASK},
    /* Set the SDCD_OT debounce count to 0 */
    {FXLS896x_SDCD_OT_DBCNT, 0, 0},
    /* Set the SDCD lower and upper thresholds to +/-100mg*/
    {FXLS896x_SDCD_LTHS_LSB, 0xCC, 0},
    {FXLS896x_SDCD_LTHS_MSB, 0xFF, 0},
    {FXLS896x_SDCD_UTHS_LSB, 0x34, 0},
    {FXLS896x_SDCD_UTHS_MSB, 0x00, 0},
    /* Enable SDCD outside of thresholds event Auto-WAKE/SLEEP transition source enable. */
    {FXLS896x_SENS_CONFIG4, FXLS896x_SENS_CONFIG4_WK_SDCD_OT_EN | FXLS896x_SENS_CONFIG4_INT_POL_ACT_HIGH, FXLS896x_SENS_CONFIG4_WK_SDCD_OT_MASK | FXLS896x_SENS_CONFIG4_INT_POL_MASK},
    /* Set the ASLP count to 5sec */
    {FXLS896x_ASLP_COUNT_LSB, 0xD0, 0},
    {FXLS896x_ASLP_COUNT_MSB, 0x07, 0},
    /* Enable Interrupts for WAKE mode. */
    {FXLS896x_INT_EN, FXLS896x_INT_EN_WAKE_OUT_EN_EN, FXLS896x_INT_EN_WAKE_OUT_EN_MASK},
    {FXLS896x_INT_PIN_SEL, FXLS896x_INT_PIN_SEL_WK_OUT_INT2_DIS, FXLS896x_INT_PIN_SEL_WK_OUT_INT2_MASK},
    __END_WRITE_DATA__};

/*! @brief Read register list to read SysMode Register. */
const registerreadlist_t cFxls896xReadSysMode[] = {{.readFrom = FXLS896x_SYS_MODE, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Read register list to read INT_STATUS Register. */
const registerreadlist_t cFxls896xReadIntStatus[] = {{.readFrom = FXLS896x_INT_STATUS, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gFxls896xIntFlag = false;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER;
    fxls896x_i2c_sensorhandle_t fxls896xDriver;
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;
//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! -----------------------------------------------------------------------
 *  @brief       This is the Sensor Data Ready ISR implementation.
 *  @details     This function sets the flag which indicates if a new sample(s) is available for reading.
 *  @param[in]   pUserData This is a void pointer to the instance of the user specific data structure for the ISR.
 *  @return      void  There is no return value.
 *  -----------------------------------------------------------------------*/
void fxls896x_int_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
	gFxls896xIntFlag = true;
}

/*! -----------------------------------------------------------------------
 *  @brief       This is the The main function implementation.
 *  @details     This function invokes board initializes routines, then then brings up the sensor and
 *               finally enters an endless loop to continuously read available samples.
 *  @param[in]   void This is no input parameter.
 *  @return      void  There is no return value.
 *  -----------------------------------------------------------------------*/
int main(void)
{
    int32_t status;
    uint8_t whoami;
    uint8_t intStatus, eventStatus = 0;
    uint8_t sleeptowake = 0;
	uint8_t waketosleep = 0;
    uint8_t firsttransition = 1;
    uint8_t onetime_modetransition = 1;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK FXLS896xAF sensor driver example to detect motion event & AWS\r\n");

    /*! Initialize FXLS8964 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS896x_INT1, GPIO_DIRECTION_IN, NULL, &fxls896x_int_callback, NULL);

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

    /*! Initialize FXLS896x sensor driver. */
    status = FXLS896x_I2C_Initialize(&fxls896xDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLS896x_I2C_ADDR,
                                     &whoami);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    if ((FXLS8964_WHOAMI_VALUE == whoami) || (FXLS8967_WHOAMI_VALUE == whoami))
    {
    	PRINTF("\r\n Successfully Initialized Gemini with WHO_AM_I = 0x%X\r\n", whoami);
    }
    else if ((FXLS8974_WHOAMI_VALUE == whoami) || (FXLS8968_WHOAMI_VALUE == whoami))
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
        return -1;
    }

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXLS896x_I2C_SetIdleTask(&fxls896xDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the FXLS896x sensor. */
    status = FXLS896x_I2C_Configure(&fxls896xDriver, cFxls896xAwsConfig);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLS8964 Sensor Configuration Failed, Err = %d\r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXLS8964 Sensor Configuration\r\n");

    for (;;) /* Forever loop */
    {
    	eventStatus = 0;
        /*! Read new raw sensor data from the FXLS8964. */
        status = FXLS896x_I2C_ReadData(&fxls896xDriver, cFxls896xReadSysMode, &eventStatus);
        if (ARM_DRIVER_OK != status)
        {
            return status;
        }

        if (eventStatus == FXLS896x_SYS_MODE_SYS_MODE_WAKE)
        {
            if (true == gFxls896xIntFlag)
            {
              if (sleeptowake == 1)
              {
                /*! Wake Mode Detected. */
                PRINTF("\r\n Motion Detected....\r\n");
                PRINTF("\r\n Motion Wake Mode Detected....SYSMODE = %d\r\n", eventStatus);
                PRINTF("\r\n MCU woke-up on sensor motion event\r\n");
                PRINTF("\r\n Will enter sleep mode after expiration of ASLP counter = ~5sec\r\n\r\n");
                sleeptowake = 0;
              }
                pGpioDriver->set_pin(&RED_LED);
                pGpioDriver->clr_pin(&GREEN_LED);
                waketosleep = 1;
            }
        }
        else
        {
           if ((waketosleep == 1) || (firsttransition == 1))
           {
             if (1 == onetime_modetransition)
             {
               onetime_modetransition = 0;
             }
             
             status = FXLS896x_I2C_ReadData(&fxls896xDriver, cFxls896xReadIntStatus, &intStatus);
             if (ARM_DRIVER_OK != status)
             {
               return status;
             }
             PRINTF("\r\n ASLP counter expired....\r\n");
             PRINTF("\r\n Going to Sleep Mode....SYSMODE = %d\r\n", eventStatus);
             PRINTF("\r\n Putting MCU in low power sleep\r\n\r\n");
             waketosleep = 0;
             firsttransition = 0;
           }
           pGpioDriver->set_pin(&GREEN_LED);
           pGpioDriver->clr_pin(&RED_LED);
           sleeptowake = 1;
           gFxls896xIntFlag = false;
           SMC_SetPowerModeWait(SMC);
          continue;
        }
    }
}
