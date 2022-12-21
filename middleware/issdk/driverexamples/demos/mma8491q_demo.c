/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma8491q_demo.c
 * @brief The mma8491q_demo.c file implements the ISSDK MMA8491Q sensor driver
 *        demo demonstration with polling mode.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "board.h"
#include "pin_mux.h"
#include "fsl_lptmr.h"
#include "clock_config.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_I2C.h"
#include "Driver_USART.h"

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "mma8491q_drv.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* Timer timeout Callback. */
#define mma8491q_en_callback LPTMR0_IRQHandler
/* Desired ODR rate in milli seconds (since the example uses LPTMR, this should be >= 10ms for reliable timing). */
#define MMA8491Q_T_ODR_ms 100U
#define MMA8491Q_STREAM_DATA_SIZE 13 /* The size of Streaming Data in Host Message. */
/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "MMA8491 Accelerometer Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"
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
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bMma8491qReady = false, bMma849qDataReady = false;
gpioConfigKSDK_t gGpioConfigInPins = /* SDK GPIO Config for Tilt Pins. */
    {
        .pinConfig = {kGPIO_DigitalInput, 0},
        .interruptMode = kPORT_InterruptOrDMADisabled,
        .portPinConfig = {0},
        .portPinConfig.mux = kPORT_MuxAsGpio,
};
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
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

/* Handler for Device Info and Streaming Control Commands. */
bool process_host_command(
    uint8_t tag, uint8_t *hostCommand, uint8_t *hostResponse, size_t *hostMsgSize, size_t respBufferSize)
{
    bool success = false;

    /* If it is Host requesting Device Info, send Board Name and Shield Name. */
    if (tag == HOST_PRO_INT_DEV_TAG)
    { /* Byte 1     : Payload - Length of APPLICATION_NAME (b)
       * Bytes=b    : Payload Application Name
       * Byte b+1   : Payload - Length of BOARD_NAME (s)
       * Bytes=s    : Payload Board Name
       * Byte b+s+2 : Payload - Length of SHIELD_NAME (v)
       * Bytes=v    : Payload Shield Name */

        size_t appNameLen = strlen(embAppName);
        size_t boardNameLen = strlen(boardString);
        size_t shieldNameLen = strlen(shieldString);

        if (respBufferSize >= boardNameLen + shieldNameLen + appNameLen + 3)
        { /* We have sufficient buffer. */
            *hostMsgSize = 0;
        }
        else
        {
            return false;
        }

        hostResponse[*hostMsgSize] = appNameLen;
        *hostMsgSize += 1;

        memcpy(hostResponse + *hostMsgSize, embAppName, appNameLen);
        *hostMsgSize += appNameLen;

        hostResponse[*hostMsgSize] = boardNameLen;
        *hostMsgSize += 1;

        memcpy(hostResponse + *hostMsgSize, boardString, boardNameLen);
        *hostMsgSize += boardNameLen;

        hostResponse[*hostMsgSize] = shieldNameLen;
        *hostMsgSize += 1;

        memcpy(hostResponse + *hostMsgSize, shieldString, shieldNameLen);
        *hostMsgSize += shieldNameLen;

        return true;
    }

    /* If it is Host sending Streaming Commands, take necessary actions. */
    if ((tag == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_W_CFG_TAG)) &&
        (*hostMsgSize == HOST_MSG_CMD_ACT_OFFSET - HOST_MSG_LEN_LSB_OFFSET))
    {                           /* Byte 1 : Payload - Operation Code (Start/Stop Operation Code)
                                 * Byte 2 : Payload - Stream ID (Target Stream for carrying out operation) */
        switch (hostCommand[0]) /* Execute desired operation (Start/Stop) on the requested Stream. */
        {
            case HOST_CMD_START:
                if (hostCommand[1] == gStreamID && bMma8491qReady && bStreamingEnabled == false)
                {
                    LPTMR_StartTimer(LPTMR0);
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bMma8491qReady && bStreamingEnabled == true)
                {
                    LPTMR_StopTimer(LPTMR0);
                    pGpioDriver->clr_pin(&GREEN_LED);
                    bStreamingEnabled = false;
                    success = true;
                }
                break;
            default:
                break;
        }
        *hostMsgSize = 0; /* Zero payload in response. */
    }

    return success;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t dataReady, data[MMA8491Q_DATA_SIZE], streamingPacket[STREAMING_HEADER_LEN + MMA8491Q_STREAM_DATA_SIZE];

    mma8491q_i2c_sensorhandle_t mma8491qDriver;
    mma8491q_acceldata_t rawData = {.timestamp = 0};

    ARM_DRIVER_I2C *pI2cDriver = &I2C_S_DRIVER;
    ARM_DRIVER_USART *pUartDriver = &HOST_S_DRIVER;

    /*! Initialize the MCU hardware. */
    BOARD_BootClockRUN();
    BOARD_SystickEnable();

    /* Create the Short Application Name String for ADS. */
    sprintf(embAppName, "%s:%s", APPLICATION_NAME, APPLICATION_VERSION);

    /* Run ADS. */
    BOARD_RunADS(embAppName, boardString, shieldString, ADS_MAX_STRING_LENGTH);

    /* Create the Full Application Name String for Device Info Response. */
    sprintf(embAppName, "%s:%s:%s", SHIELD_NAME, APPLICATION_NAME, APPLICATION_VERSION);

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
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = pI2cDriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = pI2cDriver->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Initialize the UART driver. */
    status = pUartDriver->Initialize(HOST_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the UART Power mode. */
    status = pUartDriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set UART Baud Rate. */
    status = pUartDriver->Control(ARM_USART_MODE_ASYNCHRONOUS, BOARD_DEBUG_UART_BAUDRATE);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /* Set EN = 1 to enable I2C communication. */
    pGpioDriver->set_pin(&MMA8491_EN);
    mma8491q_en_delay();

    /* Initialize the Sensor Driver. */
    status = MMA8491Q_I2C_Initialize(&mma8491qDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8491_I2C_ADDR);
    if (SENSOR_ERROR_NONE == status)
    {
        /*!  Set the task to be executed while waiting for I2C transactions to complete. */
        MMA8491Q_I2C_SetIdleTask(&mma8491qDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);
        bMma8491qReady = true;
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID =
        Host_IO_Init(pUartDriver, (void *)mma8491qDriver.pCommDrv, &mma8491qDriver.deviceInfo, NULL, MMA8491_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bMma8491qReady = false;
    }
    else
    { /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, MMA8491Q_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED); /* Set LED to indicate application is ready. */
    }

    /*! Initialize MMA8491_ODR Timer framework. */
    mma8491q_timer_fwk_init(MMA8491Q_T_ODR_ms);
    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /*! Process packets only if streaming has been enabled by Host */
        if (false == bStreamingEnabled || false == bMma849qDataReady)
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

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

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

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, MMA8491Q_STREAM_DATA_SIZE);
        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
