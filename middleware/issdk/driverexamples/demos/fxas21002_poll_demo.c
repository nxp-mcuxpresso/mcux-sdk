/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxas21002_poll_demo.c
 * @brief The fxas21002_poll_demo.c file implements the ISSDK FXAS21002 sensor
 *        demo example demonstration with Poll mode.
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
#include "host_io_uart.h"
#include "systick_utils.h"
#include "fxas21002_drv.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXAS21002_STREAM_DATA_SIZE 12

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "FXAS21002 Gyroscope Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"
/* Number of packets to skip after every restart. */
#define SKIP_PACKET_COUNT 5

/*! @brief This structure defines the fxas21002 raw data buffer.*/
typedef struct
{
    uint32_t timestamp; /*! The time, this sample was recorded.  */
    int16_t gyro[3];    /*!< The gyro data */
    int8_t temp;
    uint8_t intsrc;
} fxas21002_gyrodataUser_t;

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure FXAS21002 in non-FIFO mode. */
const registerwritelist_t fxas21002_Config_Isr[] = {
    /*! Clear F_SETUP */
    {FXAS21002_F_SETUP, 0x00, 0x00},
    /*! Configure CTRL_REG1 register to put FXAS21002 to 12.5Hz sampling rate. */
    {FXAS21002_CTRL_REG1, FXAS21002_CTRL_REG1_DR_12_5HZ, FXAS21002_CTRL_REG1_DR_MASK},
    {FXAS21002_CTRL_REG2, FXAS21002_CTRL_REG2_INT_EN_RT_ENABLE, FXAS21002_CTRL_REG2_INT_EN_RT_MASK},
    /*! Clear CTRL_REG3 */
    {FXAS21002_CTRL_REG3, 0x00, 0x00},
    __END_WRITE_DATA__};

/*! Prepare the register read list to read the status register from the FXAS21002. */
const registerreadlist_t fxas21002_Status[] = {{.readFrom = FXAS21002_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! Prepare the register read list to read the raw gyro data from the FXAS21002. */
const registerreadlist_t fxas21002_Output_Values[] = {
    {.readFrom = FXAS21002_OUT_X_MSB, .numBytes = FXAS21002_GYRO_DATA_SIZE}, __END_READ_DATA__};

const registerreadlist_t fxas21002_Reg[] = {
    {.readFrom = FXAS21002_INT_SRC_FLAG, .numBytes = 1}, __END_READ_DATA__};

const registerreadlist_t fxas21002_Temp[] = {
    {.readFrom = FXAS21002_TEMP, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bFxas21002Ready = false;
volatile uint8_t bSkipPacket = 0;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
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
                if (hostCommand[1] == gStreamID && bFxas21002Ready && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    bSkipPacket = SKIP_PACKET_COUNT;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bFxas21002Ready && bStreamingEnabled == true)
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
    uint8_t intSrc, tempOut, dataReady, data[FXAS21002_GYRO_DATA_SIZE], streamingPacket[STREAMING_HEADER_LEN + FXAS21002_STREAM_DATA_SIZE];

    fxas21002_i2c_sensorhandle_t fxas21002Driver;
    fxas21002_gyrodataUser_t rawData = {.timestamp = 0};

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

    /*! Initialize FXAS21002 sensor driver. */
    status = FXAS21002_I2C_Initialize(&fxas21002Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXAS21002_I2C_ADDR,
                                      FXAS21002_WHO_AM_I_WHOAMI_PROD_VALUE);
    if (SENSOR_ERROR_NONE == status)
    {
        /*!  Set the task to be executed while waiting for SPI transactions to complete. */
        FXAS21002_I2C_SetIdleTask(&fxas21002Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the FXAS21002 sensor. */
        status = FXAS21002_I2C_Configure(&fxas21002Driver, fxas21002_Config_Isr);
        if (SENSOR_ERROR_NONE == status)
        {
            bFxas21002Ready = true;
        }
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID = Host_IO_Init(pUartDriver, (void *)fxas21002Driver.pCommDrv, &fxas21002Driver.deviceInfo, NULL,
                             FXAS21002_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bFxas21002Ready = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, FXAS21002_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED);
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /* Process packets only if streaming has been enabled by Host and ISR is available.
         * In ISR Mode we do not need to check Data Ready Register.
         * The receipt of interrupt will indicate data is ready. */
        if (false == bStreamingEnabled)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }

        do /*! Keep checking the Status FLAG for completion. */
        {
            status = FXAS21002_I2C_ReadData(&fxas21002Driver, fxas21002_Status, &dataReady);
            if (ARM_DRIVER_OK != status)
            {
                return -1;
            }
            /* Call UART Non-Blocking Receive while waiting for OST. */
            Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);
        } /* Loop, untill sample acquisition is not completed. */
        while (0 == (dataReady & FXAS21002_DR_STATUS_ZYXDR_MASK));
        pGpioDriver->toggle_pin(&GREEN_LED);

        /*! Read new raw sensor data from the FXAS21002. */
        status = FXAS21002_I2C_ReadData(&fxas21002Driver, fxas21002_Output_Values, data);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            continue;
        }

        // Read intSrc Register of FXAS21002
        status = FXAS21002_I2C_ReadData(&fxas21002Driver, fxas21002_Reg, &intSrc);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        status = FXAS21002_I2C_ReadData(&fxas21002Driver, fxas21002_Temp, &tempOut);
        if (ARM_DRIVER_OK != status)
        {
           return -1;
        }

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.gyro[0] = ((int16_t)data[0] << 8) | data[1];
        rawData.gyro[1] = ((int16_t)data[2] << 8) | data[3];
        rawData.gyro[2] = ((int16_t)data[4] << 8) | data[5];
        rawData.temp = tempOut;
        rawData.intsrc = intSrc;

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, FXAS21002_STREAM_DATA_SIZE);
        /* Send streaming packet to Host. */
        if(bSkipPacket)
        {
            bSkipPacket--;
        }
        else
        {
            Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
        }
    }
}
