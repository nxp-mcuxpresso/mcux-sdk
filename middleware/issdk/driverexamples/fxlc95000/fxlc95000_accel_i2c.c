/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxlc95000_accel_i2c.c
 * @brief The fxlc95000_accel_i2c.c file implements the ISSDK FXLC95000 sensor driver
 * example demonstration as for I2C Mode.
 */

/*  SDK Includes */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lptmr.h"
#include "fsl_debug_console.h"

/* CMSIS Includes */
#include "Driver_I2C.h"

/* ISSDK Includes */
#include "issdk_hal.h"
#include "fxlc95000_drv.h"
#include "systick_utils.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define SAMPLING_RATE_us (100000)                /* Timeout for the ODR Timer. */
#define FXLC95000_SAMPLE_SIZE (10)               /* 4-Byte timestamp and 2-Byte X,Y,Z Data each. */
#define fxlc95000_odr_callback LPTMR0_IRQHandler /* Timer timeout Callback. */

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*! Create commands for setting FXLC95000L desired configuration. */
const uint8_t cFxlc95000_SetODR_Cmd[] = {FXLC95000_SET_ODR_CMD_HDR, /* ODR equal to Sampling Rate. */
                                         FXLC95000_SST_ODR_PAYLOAD(SAMPLING_RATE_us)};
const uint8_t cFxlc95000_SetResolution_Cmd[] = {FXLC95000_SET_RESOLUTION_CMD_HDR, /* Resolution 14-bits. */
                                                FXLC95000_ACCEL_RESOLUTION_14_BIT};
const uint8_t cFxlc95000_SetRange_Cmd[] = {FXLC95000_SET_RANGE_CMD_HDR, /* FS Range 2G. */
                                           FXLC95000_ACCEL_RANGE_2G};

/*! Prepare the register write list to initialize FXLC95000L with desired MBox Settings. */
const registercommandlist_t cFxlc95000ConfigMBox[] = {
    {QuickReadInterruptDisable, 0, sizeof(QuickReadInterruptDisable)}, /* Disable QR INT. */
    {ConfigureMBoxCmd, 0, sizeof(ConfigureMBoxCmd)}, /* Configure MBox 16 to 25 with 10 byte Sample. */
    __END_WRITE_CMD__                                /* Ref. Table 3-7 of ISF1P195K_SW_REFERENCE_RM. */
};

/*! Prepare the register write list to configure FXLC95000L with desired Sampling Settings. */
const registercommandlist_t cFxlc95000ConfigSensor[] = {
    {StopDataCmd, 0, sizeof(StopDataCmd)},                                   /* Stop Data before (re)configuration. */
    {cFxlc95000_SetODR_Cmd, 0, sizeof(cFxlc95000_SetODR_Cmd)},               /* Set Sensor Sampling Rate. */
    {cFxlc95000_SetRange_Cmd, 0, sizeof(cFxlc95000_SetRange_Cmd)},           /* Set FS Range. */
    {cFxlc95000_SetResolution_Cmd, 0, sizeof(cFxlc95000_SetResolution_Cmd)}, /* Set Resolution */
    {StartDataCmd, 0, sizeof(StartDataCmd)},                                 /* Start Data after (re)configuration. */
    __END_WRITE_CMD__};

/*! Prepare the register read list to read the Timestamp and Accel data from FXLC95000. */
const registerreadlist_t cFxlc95000ReadSample[] = {
    {.readFrom = FXLC95000_SAMPLE_OFFSET, .numBytes = FXLC95000_SAMPLE_SIZE}, __END_READ_DATA__};

/*******************************************************************************
 * Globals
 ******************************************************************************/
volatile bool gFxlc95000DataRead;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* LPTMR based ODR Callback function. */
void fxlc95000_odr_callback(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    gFxlc95000DataRead = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    lptmr_config_t lptmrConfig;
    fxlc95000_acceldata_t rawData;
    uint8_t data[FXLC95000_SAMPLE_SIZE];

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    fxlc95000_i2c_sensorhandle_t fxlc95000Driver;

    /*! Initialize the MCU hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    /* Initialize ODR Timer. */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(SAMPLING_RATE_us, CLOCK_GetFreq(kCLOCK_LpoClk)));
    EnableIRQ(LPTMR0_IRQn);

    PRINTF("\r\n ISSDK FXLC95000 sensor driver example for Normal Mode. \r\n");

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

    /*! Initialize the FXLC95000 sensor driver. */
    status = FXLC95000_I2C_Initialize(&fxlc95000Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLC95000_I2C_ADDR,
                                      FXLC95000_BUILD_ID);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXLC95000_I2C_SetIdleTask(&fxlc95000Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    gFxlc95000DataRead = false; /* Do not read data, data will be read after ODR Timer expires. */

    /*! Configure the FXLC95000 with MBox settings. */
    status = FXLC95000_I2C_CommandResponse(&fxlc95000Driver, cFxlc95000ConfigMBox, NULL, NULL);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLC95000 MBox Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    /*! Configure the FXLC95000 with Sampling settings. */
    status = FXLC95000_I2C_CommandResponse(&fxlc95000Driver, cFxlc95000ConfigSensor, NULL, NULL);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n FXLC95000 Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n Successfully Applied FXLC95000 Sensor Configuration\r\n");

    LPTMR_StartTimer(LPTMR0);
    for (;;) /* Forever loop */
    {
        if (gFxlc95000DataRead == false)
        {
            __NOP();
            continue;
        }
        else
        {
            gFxlc95000DataRead = false;
        }

        /*! Read the raw sensor data from the FXLC95000. */
        status = FXLC95000_I2C_CommandResponse(&fxlc95000Driver, NULL, cFxlc95000ReadSample, data);
        if (ARM_DRIVER_OK != status)
        {
            PRINTF("\r\n Read Failed. \r\n");
            return -1;
        }

        /*! Convert the raw bytes to sensor data with correct endianness. */
        rawData.timestamp = ((uint32_t)data[3] << 24) | ((uint32_t)data[2] << 16) | ((uint16_t)data[1] << 8) | data[0];
        rawData.accel[0] = ((int16_t)data[5] << 8) | data[4];
        rawData.accel[1] = ((int16_t)data[7] << 8) | data[6];
        rawData.accel[2] = ((int16_t)data[9] << 8) | data[8];

        PRINTF("\r\n Timestamp = 0x%X \r\n Accel X = %d  Y = %d  Z = %d \r\n", rawData.timestamp, rawData.accel[0],
               rawData.accel[1], rawData.accel[2]);
        ASK_USER_TO_RESUME(100); /* Ask for user input after processing 100 samples. */
    }
}
