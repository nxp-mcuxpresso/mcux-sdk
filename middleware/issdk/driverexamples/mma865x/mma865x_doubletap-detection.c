/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * @file mma865x_doubletap-detection.c
*   @brief The mma865x_doubletap-detection.c file implements the ISSDK MMA865x sensor
*        example demonstration for double-tap detection.
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
/* Double-Tap detection threshold values.
 * Refer: https://www.nxp.com/docs/en/application-note/AN3919.pdf
*/
#define PULSE_THX     0x12  /* X-axis pulse threshold value. */
#define PULSE_THY     0x12  /* Y-axis pulse threshold value. */
#define PULSE_THZ     0x12  /* Z-axis pulse threshold value. */
#define PULSE_TL      0x0C  /* Time limit value for pulse detection. */
#define PULSE_LT      0x14  /* Latency time for second pulse detection. */
#define PULSE_WT      0x1E  /* Window time for second pulse detection. */

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
const registerwritelist_t cMma865xConfigDoubleTap[] =
    {/* HP_FILTER_CUTOFF to be set to 0x00 */
     {MMA865x_HP_FILTER_CUTOFF, MMA865x_HP_FILTER_CUTOFF_PULSE_HPF_BYP_ENABLED, MMA865x_HP_FILTER_CUTOFF_PULSE_HPF_BYP_MASK},
     /* Enable double-pulse event on X, Y & Z axis */
     {MMA865x_PULSE_CFG, MMA865x_PULSE_CFG_XDPEFE_EN | MMA865x_PULSE_CFG_YDPEFE_EN | MMA865x_PULSE_CFG_ZDPEFE_EN,
      MMA865x_PULSE_CFG_XDPEFE_MASK | MMA865x_PULSE_CFG_YDPEFE_MASK | MMA865x_PULSE_CFG_ZDPEFE_MASK},
     /* Set thresholds to be used by the system to start the pulse-event detection procedure */
     {MMA865x_PULSE_THSX, PULSE_THX, MMA865x_PULSE_THSX_THSX_MASK},
     {MMA865x_PULSE_THSY, PULSE_THY, MMA865x_PULSE_THSY_THSY_MASK},
     {MMA865x_PULSE_THSZ, PULSE_THZ, MMA865x_PULSE_THSZ_THSZ_MASK},
     /* Set Pulse time limit threshold to PULSE_TL */
     {MMA865x_PULSE_TMLT, PULSE_TL, 0},
     /* Set Pulse latency time threshold to PULSE_LT */
     {MMA865x_PULSE_LTCY, PULSE_LT, 0},
     /* Set Pulse window time threshold to PULSE_WT */
     {MMA865x_PULSE_WIND, PULSE_WT, 0},
     /* Configure MMA8652 in standby mode, normal read and noise mode, 100Hz ODR and auto-wake frequency of 50Hz */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_ACTIVE_STANDBY | MMA865x_CTRL_REG1_F_READ_NORMAL | MMA865x_CTRL_REG1_DR_100HZ | MMA865x_CTRL_REG1_ASLP_RATE_50HZ,
     MMA865x_CTRL_REG1_ACTIVE_MASK | MMA865x_CTRL_REG1_F_READ_MASK | MMA865x_CTRL_REG1_DR_MASK | MMA865x_CTRL_REG1_ASLP_RATE_MASK},
     /* Configure MMA8652 in low power wake mode */
     {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_LP, MMA865x_CTRL_REG2_MODS_MASK},
     /* Configure INT1/INT2 interrupt logic polarity to Active high */
     {MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
     {MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_PULSE_EN, MMA865x_CTRL_REG4_INT_EN_PULSE_MASK}, /*! Pulse Detection Event. */
     {MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_PULSE_INT1, MMA865x_CTRL_REG5_INT_CFG_PULSE_MASK}, /*! INT1 Pin  */
     __END_WRITE_DATA__};

/*! @brief Read register list for MMA8652 to read status bits for the pulse detection function. */
const registerreadlist_t gMma865xReadPulseSrc[] = {{.readFrom = MMA865x_PULSE_SRC, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool gMma865xIntFlag = false;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! -----------------------------------------------------------------------
 *  @brief       This is the Sensor Event ISR implementation.
 *  @details     This function sets the flag which indicates if a new event is detected.
 *  @param[in]   pUserData This is a void pointer to the instance of the user specific data structure for the ISR.
 *  @return      void  There is no return value.
 *  @constraints None
 *  @reeentrant  Yes
 *  -----------------------------------------------------------------------*/
void mma865x_isr_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has detected an event. */
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
    uint8_t eventStatus = 0;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;
    GENERIC_DRIVER_GPIO *gpioDriver = &Driver_GPIO_KSDK;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor driver example for Double-Tap detection.\r\n");

    /*! Initialize MMA865x pin used by FRDM board */
    gpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_isr_callback, NULL);

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

    status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigDoubleTap);

    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied MMA865x Sensor Configuration for Double-Tap Detection\r\n");
    PRINTF("\r\n MMA865x is now active and detecting double-tap... \r\n");

    for (;;) /* Forever loop */
    {        /* In ISR Mode we do not need to check Data Ready Register.
              * The receipt of interrupt will indicate data is ready. */
        if (false == gMma865xIntFlag)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            gMma865xIntFlag = false;
            gpioDriver->toggle_pin(&GREEN_LED);
        }

        status = MMA865x_I2C_ReadData(&mma865xDriver, gMma865xReadPulseSrc, &eventStatus);
        if (ARM_DRIVER_OK != status)
        {
            return status;
        }

        if (0 == (eventStatus & MMA865x_PULSE_SRC_DPE_MASK))
        { /* continue, if new event is not detected. */
          continue;
        }

        PRINTF("\r\n Double-Tap Detected !!!");
    }
}
