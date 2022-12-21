/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma8491q_example.c
 * @brief The mma8491q_example.c file implements the ISSDK MMA8491Q sensor driver
 *        example demonstration with Timers.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lptmr.h"
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
#include "mma8491q_drv.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* Timer timeout Callback. */
#define mma8491q_en_callback LPTMR0_IRQHandler
/* Desired ODR rate in milli seconds (since the example uses LPTMR, this should be >= 10ms for reliable timing). */
#define MMA8491Q_T_ODR_ms 100U
/* The LPTMR Timeout Correction in milliseconds. */
#define LPTMR_T_CORRECTION_ms 2

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Address of Status Register. */
const registerreadlist_t cMma8491qStatus[] = {{.readFrom = MMA8491Q_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Acceleration Data. */
const registerreadlist_t cMma8491qOutput[] = {{.readFrom = MMA8491Q_OUT_X_MSB, .numBytes = MMA8491Q_DATA_SIZE},
                                              __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bool bMma849qDataReady = false;
gpioConfigKSDK_t gGpioConfigInPins = /* SDK GPIO Config for Tilt Pins. */
    {
        .pinConfig = {kGPIO_DigitalInput, 0},
        .interruptMode = kPORT_InterruptOrDMADisabled,
        .portPinConfig = {0},
        .portPinConfig.mux = kPORT_MuxAsGpio,
};
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* @brief  Block for adding EN delay. */
void mma8491q_en_delay()
{
    uint32_t delay, count, systemCoreClock;

    systemCoreClock = CLOCK_GetCoreSysClkFreq();
    delay = (int)(0.16*MSEC_TO_COUNT(MMA8491Q_T_ON_TYPICAL, systemCoreClock));
    for(count=0;count<delay;count++)
    {
        __NOP();
    }
}

/* LPTMR based EN control Timer Callback function. */
void mma8491q_en_callback(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    bMma849qDataReady = true;
}

/* Function for MMA8491Q specific initialization tasks. */
void mma8491q_timer_fwk_init(uint32_t samplingInterval)
{
    lptmr_config_t lptmrConfig;
    /* Initialize ODR Timer. */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    EnableIRQ(LPTMR0_IRQn);

    /* Put the Sensor into Active Mode to enable I2C communication. */
    LPTMR_SetTimerPeriod(LPTMR0, MSEC_TO_COUNT((samplingInterval-LPTMR_T_CORRECTION_ms), CLOCK_GetFreq(kCLOCK_LpoClk)));
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t dataReady, data[MMA8491Q_DATA_SIZE];
    
    mma8491q_i2c_sensorhandle_t mma8491qDriver;
    mma8491q_acceldata_t rawData = {.timestamp = 0};

    ARM_DRIVER_I2C *pI2cDriver = &I2C_S_DRIVER;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA8491Q sensor driver example demonstration with poll mode\r\n");

    /* Initialize Tilt Pin IDs. */
    pGpioDriver->pin_init(&MMA8491_EN, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGpioDriver->pin_init(&MMA8491_XOUT, GPIO_DIRECTION_IN, &gGpioConfigInPins, NULL, NULL);
    pGpioDriver->pin_init(&MMA8491_YOUT, GPIO_DIRECTION_IN, &gGpioConfigInPins, NULL, NULL);
    pGpioDriver->pin_init(&MMA8491_ZOUT, GPIO_DIRECTION_IN, &gGpioConfigInPins, NULL, NULL);

    /*! Initialize GREEN LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /*! Initialize the I2C driver. */
    status = pI2cDriver->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Initialization Failed\r\n");
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = pI2cDriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Power Mode setting Failed\r\n");
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = pI2cDriver->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Control Mode setting Failed\r\n");
        return -1;
    }

    /* Set EN = 1 to enable I2C communication. */
    pGpioDriver->set_pin(&MMA8491_EN);
    mma8491q_en_delay();

    /* Initialize the Sensor Driver. */
    status = MMA8491Q_I2C_Initialize(&mma8491qDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8491_I2C_ADDR);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA8491Q_I2C_SetIdleTask(&mma8491qDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Initialize MMA8491_ODR Timer framework. */
    mma8491q_timer_fwk_init(MMA8491Q_T_ODR_ms);
    for (;;) /* Forever loop */
    {
        /*! Process packets on Data ready Timer Expiry */
        if (false == bMma849qDataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        {
            pGpioDriver->toggle_pin(&GREEN_LED);
            bMma849qDataReady = false;
        }

        /* Set EN = 1 to put the Sensor into Active Mode. */
        pGpioDriver->set_pin(&MMA8491_EN);
        mma8491q_en_delay();
        do
        { /*! Process packets only when data ready is indicated by the MMA8491Q. */
            MMA8491Q_I2C_ReadData(&mma8491qDriver, cMma8491qStatus, &dataReady);
        } while (0 == (dataReady & MMA8491Q_STATUS_ZYXDR_MASK));

        /*! Read the raw sensor data from the MMA8491Q. */
        status = MMA8491Q_I2C_ReadData(&mma8491qDriver, cMma8491qOutput, data);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            continue;
        }
        /* Set EN = 0 to put the Sensor into Shutdown Mode. */
        pGpioDriver->clr_pin(&MMA8491_EN);

        /* Read Tilt Output */
        rawData.tilt[0] = pGpioDriver->read_pin(&MMA8491_XOUT);
        rawData.tilt[1] = pGpioDriver->read_pin(&MMA8491_YOUT);
        rawData.tilt[2] = pGpioDriver->read_pin(&MMA8491_ZOUT);

        /*! Process the sample and convert the raw sensor data. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | (data[1]);
        rawData.accel[0] /= 4;
        rawData.accel[1] = ((int16_t)data[2] << 8) | (data[3]);
        rawData.accel[1] /= 4;
        rawData.accel[2] = ((int16_t)data[4] << 8) | (data[5]);
        rawData.accel[2] /= 4;
        
        PRINTF("\r\n Tilt :  X = %d  Y = %d  Z = %d ", rawData.tilt[0], rawData.tilt[1], rawData.tilt[2]);
        PRINTF("|| Accel : X = %5d  Y = %5d  Z = %5d \r\n", rawData.accel[0], rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(100); /* Ask for user input after processing 100 samples. */
    }
}
