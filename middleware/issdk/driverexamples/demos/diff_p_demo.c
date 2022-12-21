/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file diff_p_demo.c
 * @brief The diff_p_demo.c file implements the ISSDK DIFF_P sensor driver
 *        example demonstration with Interrupt mode.
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
#include "gpio_driver.h"
#include "diff_p_drv.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define DIFF_P_DATA_SIZE (3)        /* 2 byte Pressure and 1 byte Temperature. */
#define DIFF_P_STREAM_DATA_SIZE (7) /* 7 byte Data */

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "NPS300x Differential Pressure Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for Normal (non buffered) mode. */
const registerwritelist_t cDiffPConfigNormal[] = {
    {DIFF_P_CTRL_REG2, DIFF_P_CTRL_REG2_ODR_ODR6P25, DIFF_P_CTRL_REG2_ODR_MASK},
    {DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_OSR_OSR512, DIFF_P_CTRL_REG1_OSR_MASK},
    {DIFF_P_INT_MASK0, DIFF_P_INT_MASK0_TDR_INT_EN | DIFF_P_INT_MASK0_PDR_INT_EN,
     DIFF_P_INT_MASK0_TDR_MASK | DIFF_P_INT_MASK0_PDR_MASK},
    {DIFF_P_CTRL_REG3, DIFF_P_CTRL_REG3_IPOL1_ACTIVE_HIGH, DIFF_P_CTRL_REG3_IPOL1_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Clearing Pressure and Temperature Data Ready Bits. */
const registerwritelist_t cDiffPClearStatusBits[] = {
    {DIFF_P_INT_STATUS_0, 0x00, DIFF_P_INT_STATUS_0_TDR_MASK | DIFF_P_INT_STATUS_0_PDR_MASK}, __END_WRITE_DATA__};

/*! @brief Address of Status Register. */
const registerreadlist_t cDiffPStatus[] = {{.readFrom = DIFF_P_INT_STATUS_0, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Pressure+Temperature Data in Normal Mode. */
const registerreadlist_t cDiffPOutputNormal[] = {{.readFrom = DIFF_P_OUT_P_LSB, .numBytes = DIFF_P_DATA_SIZE},
                                                 __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bDiffPDataReady = false, bDiffPReady = false;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* This is the Sensor Data Ready ISR implementation.*/
void diffp_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bDiffPDataReady = true;
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
                if (hostCommand[1] == gStreamID && bDiffPReady && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bDiffPReady && bStreamingEnabled == true)
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
    uint8_t dataReady, data[DIFF_P_DATA_SIZE], streamingPacket[STREAMING_HEADER_LEN + DIFF_P_STREAM_DATA_SIZE];

    diff_p_i2c_sensorhandle_t diffpDriver;
    diff_p_pressuredata_t rawData = {.timestamp = 0};

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

    /*! Initialize INT1 DIFF_P pin used by FRDM board */
    pGpioDriver->pin_init(&DIFF_P_INT1, GPIO_DIRECTION_IN, NULL, &diffp_int_data_ready_callback, NULL);

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

    do
    { /*! Initialize DIFF_P sensor driver. */
        status = DIFF_P_I2C_Initialize(&diffpDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, DIFF_P_I2C_ADDR,
                                       DIFF_P_NPS3000VV_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE == status)
        {
            bDiffPReady = true;
            break;
        }
        status = DIFF_P_I2C_Initialize(&diffpDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, DIFF_P_I2C_ADDR,
                                       DIFF_P_NPS3001DV_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE == status)
        {
            bDiffPReady = true;
            break;
        }
        status = DIFF_P_I2C_Initialize(&diffpDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, DIFF_P_I2C_ADDR,
                                       DIFF_P_NPS3002VV_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE == status)
        {
            bDiffPReady = true;
            break;
        }
        status = DIFF_P_I2C_Initialize(&diffpDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, DIFF_P_I2C_ADDR,
                                       DIFF_P_NPS3005DV_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE == status)
        {
            bDiffPReady = true;
            break;
        }
    } while (false);

    if (bDiffPReady)
    { /*! Configure the DIFF_P sensor. */
        status = DIFF_P_I2C_Configure(&diffpDriver, cDiffPConfigNormal);
        if (SENSOR_ERROR_NONE != status)
        {
            bDiffPReady = false;
        }
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID = Host_IO_Init(pUartDriver, (void *)diffpDriver.pCommDrv, &diffpDriver.deviceInfo, NULL, DIFF_P_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bDiffPReady = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, DIFF_P_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED); /* Set LED to indicate application is ready. */
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /* Process packets only if streaming has been enabled by Host and ISR is available.
         * In ISR Mode we do not need to check Data Ready Register.
         * The receipt of interrupt will indicate data is ready. */
        if (false == bStreamingEnabled || false == bDiffPDataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bDiffPDataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        do
        { /* Read INT_STATUS register */
            status = DIFF_P_I2C_ReadData(&diffpDriver, cDiffPStatus, &dataReady);
            if (ARM_DRIVER_OK != status)
            {
                break;
            }

            /*! Check for both data ready bits from the DIFF_P. */
            if ((DIFF_P_INT_STATUS_0_PDR_DRDY | DIFF_P_INT_STATUS_0_TDR_DRDY) !=
                (dataReady & (DIFF_P_INT_STATUS_0_PDR_MASK | DIFF_P_INT_STATUS_0_TDR_MASK)))
            { /* Loop, if new samples are not available. */
                continue;
            }

            /*! If samples available, explicitly clear the Status Bits. */
            status = Sensor_I2C_Write(diffpDriver.pCommDrv, &diffpDriver.deviceInfo, diffpDriver.slaveAddress,
                                      cDiffPClearStatusBits);
            if (ARM_DRIVER_OK != status)
            {
                break;
            }
        } while (false);

        /*! Read new raw sensor data from the DIFF_P. */
        status = DIFF_P_I2C_ReadData(&diffpDriver, cDiffPOutputNormal, data);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            return -1;
        }

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Process the sample and convert the raw sensor data. */
        rawData.pressure = ((int16_t)(data[1]) << 8) | data[0];
        rawData.temperature = (int8_t)(data[2]);

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, DIFF_P_STREAM_DATA_SIZE);
        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
