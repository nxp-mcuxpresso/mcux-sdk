/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma865x_demo.c
 * @brief The mma865x_demo.c file implements the ISSDK MMA865x sensor
 *        demo example demonstration with interrupt mode.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "board.h"
#include "pin_mux.h"
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
#include "mma865x_drv.h"
#include "gpio_driver.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MMA865x_ACCEL_DATA_SIZE 6 /* 2 byte X,Y,Z Axis Data each. */
#define MMA865x_STREAM_DATA_SIZE 11

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "MMA8652 Accelerometer Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

typedef struct
{
    uint32_t timestamp; /*!< Time stamp value in micro-seconds. */
    int16_t accel[3];   /*!< The accel data */
    uint8_t intsrc;
} mma865x_acceluserdata_t;

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure MMA865x in non-FIFO and ISR mode. */
const registerwritelist_t cMma865xConfigInterrupt[] =
{   /*! Clear F_SETUP. */
	{MMA865x_F_SETUP, 0x00, 0},
    /*! Configure the MMA865x to set FS Range as 2g. */
	{MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
	/*! Configure the MMA865x to set ODR to 100Hz. */
	{MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_100HZ, MMA865x_CTRL_REG1_DR_MASK},
	/*! Configure the MMA865x to set High Resolution mode. */
	{MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PL_CFG, MMA865x_PL_CFG_PL_EN_EN|MMA865x_PL_CFG_DBCNTM_CLEAR, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PL_COUNT, 0xFF, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_OAE_FREEFALL|MMA865x_FF_MT_CFG_ZEFE_EN|MMA865x_FF_MT_CFG_YEFE_EN|MMA865x_FF_MT_CFG_XEFE_EN, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_FF_MT_COUNT, 0x01, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_FF_MT_THS, MMA865x_FF_MT_THS_DBCNTM_INC_CLR|0x02, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_TRANSIENT_CFG,MMA865x_TRANSIENT_CFG_ZTEFE_EN|MMA865x_TRANSIENT_CFG_YTEFE_EN|MMA865x_TRANSIENT_CFG_XTEFE_EN, 0},
	{MMA865x_TRANSIENT_THS, MMA865x_TRANSIENT_THS_DBCNTM_INC_CLR|0x10, 0},
	{MMA865x_TRANSIENT_COUNT, 0x0C, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_CFG, MMA865x_PULSE_CFG_XSPEFE_EN|MMA865x_PULSE_CFG_YSPEFE_EN|MMA865x_PULSE_CFG_ZSPEFE_EN, 0},
	{MMA865x_PULSE_THSX, 0x37, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_THSY, 0x37, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_THSZ, 0x52, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_TMLT, 0x30, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_LTCY, 0x3C, 0},
	/*! Configure the MMA865x to enable Interrupts for Data Ready. */
	{MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_DRDY_EN|MMA865x_CTRL_REG4_INT_EN_LNDPRT_EN|MMA865x_CTRL_REG4_INT_EN_FF_MT_EN|MMA865x_CTRL_REG4_INT_EN_TRANS_EN|MMA865x_CTRL_REG4_INT_EN_PULSE_EN, 0},
	/*! Configure the MMA865x to route Data Ready Interrupts to INT1. */
	{MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_DRDY_INT1, 0},
	__END_WRITE_DATA__};

/*! Prepare the register read list to read the raw Accel data from MMA865x. */
const registerreadlist_t cMma865xOutputValues[] = {{.readFrom = MMA865x_OUT_X_MSB, .numBytes = MMA865x_ACCEL_DATA_SIZE},
                                                   __END_READ_DATA__};
/*! Prepare the register read for INT Status Register. */
const registerreadlist_t cMma8652qStatus[] = {{.readFrom = MMA865x_INT_SOURCE, .numBytes = 1}, __END_READ_DATA__};
/*! Prepare the register read for PL Status Register. */
const registerreadlist_t cMma8652qPLStatus[] = {{.readFrom = MMA865x_PL_STATUS, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bMma865xDataReady = false, bMma865xReady = false;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* This is the Sensor Data Ready ISR implementation.*/
void mma865x_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bMma865xDataReady = true;
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
                if (hostCommand[1] == gStreamID && bMma865xReady && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bMma865xReady && bStreamingEnabled == true)
                {
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
    uint8_t data[MMA865x_ACCEL_DATA_SIZE], intsrcdata, PLstatusdata, streamingPacket[STREAMING_HEADER_LEN + MMA865x_STREAM_DATA_SIZE];

    mma865x_i2c_sensorhandle_t mma865xDriver;
    mma865x_acceluserdata_t rawData = {.timestamp = 0};

    ARM_DRIVER_I2C *pI2Cdriver = &I2C_S_DRIVER;
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

    /*! Initialize MMA865x pin used by FRDM board */
    pGpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_int_data_ready_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /*! Initialize the I2C driver. */
    status = pI2Cdriver->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = pI2Cdriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = pI2Cdriver->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
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

    /*! Initialize MMA865x sensor driver. */
    status = MMA865x_I2C_Initialize(&mma865xDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8652_I2C_ADDR,
                                    MMA8652_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE == status)
    {
        /*!  Set the task to be executed while waiting for SPI transactions to complete. */
        MMA865x_I2C_SetIdleTask(&mma865xDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the MMA865x sensor. */
        status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigInterrupt);
        if (SENSOR_ERROR_NONE == status)
        {
            bMma865xReady = true;
        }
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID =
        Host_IO_Init(pUartDriver, (void *)mma865xDriver.pCommDrv, &mma865xDriver.deviceInfo, NULL, MMA8652_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bMma865xReady = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, MMA865x_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED);
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /* Process packets only if streaming has been enabled by Host and ISR is available.
         * In ISR Mode we do not need to check Data Ready Register.
         * The receipt of interrupt will indicate data is ready. */
        if (false == bStreamingEnabled || false == bMma865xDataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bMma865xDataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read new raw sensor data from the MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xOutputValues, data);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            continue;
        }

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | data[1];
        rawData.accel[0] /= 16;
        rawData.accel[1] = ((int16_t)data[2] << 8) | data[3];
        rawData.accel[1] /= 16;
        rawData.accel[2] = ((int16_t)data[4] << 8) | data[5];
        rawData.accel[2] /= 16;

        /*! Read INT_SRC 0x0C from MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma8652qStatus, &intsrcdata);
        /*! Read PL_STATUS 0x10 from MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma8652qPLStatus, &PLstatusdata);
           /* Send INTSRC */
        rawData.intsrc = intsrcdata;

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, MMA865x_STREAM_DATA_SIZE);
        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
