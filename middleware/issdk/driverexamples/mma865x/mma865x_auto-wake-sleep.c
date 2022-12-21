/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  mma865x_auto-wake-sleep.c
*  @brief The mma865x_auto-wake-sleep.c file implements the ISSDK MMA865x
*         sensor example demonstrating configuring MMA8652 Accel and enabling
*         detection motion detection event.
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
#define MT_FFMT_THS 0x07  /* Motion Threshold Value. */
#define MT_FFMT_COUNT 0x00
#define ASLP_COUNT  0x14

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
const registerwritelist_t mma865x_autowake_motiondet_config[] = {
    /* A_FFMT_CFG to be Raise event flag on measured X & Y-axis acceleration above/below threshold & detect motion */
    {MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_OAE_MOTION | MMA865x_FF_MT_CFG_YEFE_EN | MMA865x_FF_MT_CFG_XEFE_EN,
     MMA865x_FF_MT_CFG_OAE_MASK | MMA865x_FF_MT_CFG_YEFE_MASK | MMA865x_FF_MT_CFG_XEFE_MASK},
    /* Set Motion detection threshold. */
    {MMA865x_FF_MT_THS, MT_FFMT_THS, MMA865x_FF_MT_THS_THS_MASK},
     /* Set thresholds to be used by the system to start the pulse-event detection procedure */
    {MMA865x_FF_MT_COUNT, MT_FFMT_COUNT, 0},
    {MMA865x_ASLP_COUNT, ASLP_COUNT, 0},
    /* Configure MMA8652 in standby mode, normal read and noise mode, 800Hz ODR and sleep frequency of 1.56Hz */
    {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_ACTIVE_STANDBY | MMA865x_CTRL_REG1_F_READ_NORMAL | MMA865x_CTRL_REG1_DR_800HZ | MMA865x_CTRL_REG1_ASLP_RATE_1_56HZ,
     MMA865x_CTRL_REG1_ACTIVE_MASK | MMA865x_CTRL_REG1_F_READ_MASK | MMA865x_CTRL_REG1_DR_MASK | MMA865x_CTRL_REG1_ASLP_RATE_MASK},
    /* Configure MMA8652 in low power wake mode  and enable auto-sleep. */
    {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_LP | MMA865x_CTRL_REG2_SLPE_EN | MMA865x_CTRL_REG2_SMODS_LP,
     MMA865x_CTRL_REG2_MODS_MASK | MMA865x_CTRL_REG2_SLPE_MASK | MMA865x_CTRL_REG2_SMODS_MASK},
    /* Configure INT1/INT2 interrupt logic polarity to Active high and enable motion function in sleep mode. */
    {MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH | MMA865x_CTRL_REG3_WAKE_FF_MT_EN,
     MMA865x_CTRL_REG3_IPOL_MASK | MMA865x_CTRL_REG3_WAKE_FF_MT_MASK},
    /* Enable FFMT interrupts. */
	{MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_FF_MT_EN, MMA865x_CTRL_REG4_INT_EN_FF_MT_MASK},
    {MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_FF_MT_INT1, MMA865x_CTRL_REG5_INT_CFG_FF_MT_MASK}, /*! INT1 Pin  */
    __END_WRITE_DATA__};

/*! @brief Read register list for MMA8562 to read SysMode Register. */
const registerreadlist_t gMma8562ReadSysMode[] = {{.readFrom = MMA865x_SYSMOD, .numBytes = 1}, __END_READ_DATA__};

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
    uint8_t wake        = 0;
    uint8_t sleep       = 0;
    uint8_t sleepflag   = 1;
    uint16_t eventDetectionCount = 0;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;
    GENERIC_DRIVER_GPIO *gpioDriver = &Driver_GPIO_KSDK;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor example demonstration for Auto Wake Sleep feature.\r\n");

    /*! Initialize MMA865x pin used by FRDM board */
    gpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_isr_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    gpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    /*! Initialize RGB LED pin used by FRDM board */
    gpioDriver->pin_init(&RED_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

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

    status = MMA865x_I2C_Configure(&mma865xDriver, mma865x_autowake_motiondet_config);

    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied MMA865x Sensor Configuration for Auto-Wake-Sleep Mode\r\n\r\n");
    PRINTF("\r\n MMA865x is now active and detecting sudden motion gesture of lifting up the board... \r\n\r\n");

    for (;;) /* Forever loop */
    {

      eventStatus = 0;

      status = MMA865x_I2C_ReadData(&mma865xDriver, gMma8562ReadSysMode, &eventStatus);
      if (ARM_DRIVER_OK != status)
      {
          return status;
      }

      /*! Check whether Motion Interrupt has occurred and event status is Wake mode  */
      if ((eventStatus == MMA865x_SYSMOD_SYSMOD_WAKE))
      {
         if (true == gMma865xIntFlag)
         {
            if (wake == 1)
            {
                /*! Wake Mode Detected. */
                eventDetectionCount++;
                PRINTF("\r\n Sensor Detected Motion!!!\r\n");
                PRINTF("\r\n Waking up MCU on motion detection event\r\n");
                PRINTF("\r\n Total Motion Detection Events captured = %d\r\n", eventDetectionCount);
                PRINTF("\r\n Will enter sleep mode automatically on expiry of ASLP Count = ~6sec\r\n");
                PRINTF("\r\n ==================================================================\r\n\r\n");
                wake = 0;
            }
            gpioDriver->set_pin(&RED_LED);
            gpioDriver->clr_pin(&GREEN_LED);
            sleep = 1;
         }
      }
      else
      {
         if ((sleep == 1) || (sleepflag == 1))
         {
            PRINTF("\r\n No-Motion Detected - ASLP Counter = ~6sec Expired\r\n");
            PRINTF("\r\n Going to Sleep Mode...\r\n");
            PRINTF("\r\n Putting MCU in low power sleep\r\n");
            PRINTF("\r\n ==================================================================\r\n\r\n");
            sleep = 0;
            sleepflag = 0;
         }
         gpioDriver->set_pin(&GREEN_LED);
         gpioDriver->clr_pin(&RED_LED);
         wake = 1;
       	 /*! Clear the sensor event interrupt flag, it will be set again by the ISR. */
         gMma865xIntFlag = false;
       	 /*! Put MCU in low-power sleep. */
         SMC_SetPowerModeWait(SMC);
        continue;
      }
    }
}
