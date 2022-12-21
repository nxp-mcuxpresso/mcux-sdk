/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma845x_demo.c
 * @brief The mma845x_demo.c file implements the ISSDK MMA845x sensor
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
#include "gpio_driver.h"
#include "mma845x_drv.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MMA845x_STREAM_DATA_SIZE 11 /* 6+1 byte Data */

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "MMA845x Accelerometer Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

typedef struct
{
    uint32_t timestamp; /*!< Time stamp value in micro-seconds. */
    int16_t accel[3];   /*!< The accel data */
    uint8_t intsrc;
} mma845x_acceluserdata_t;

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure MMA845x in non-FIFO and ISR mode. */
const registerwritelist_t mma845x_Config_Isr[] = {
    /*! Configure the MMA845x to disable FIFO */
    {MMA845x_F_SETUP, 0x00, 0},
	/*! Configure the MMA845x XYZ_DATA_CFG to set FS Range 2G. */
	{ MMA845x_XYZ_DATA_CFG, MMA845x_XYZ_DATA_CFG_FS_FS_RANGE_2G, MMA845x_XYZ_DATA_CFG_FS_MASK},
    /*! Configure the MMA845x CTRL_REG1 to set ODR to 100Hz. */
    {MMA845x_CTRL_REG1, MMA845x_CTRL_REG1_DR_100HZ, MMA845x_CTRL_REG1_DR_MASK},
    /*! Configure the MMA845x CTRL_REG2 to set the Oversampling mode to High Resolution. */
    {MMA845x_CTRL_REG2, MMA845x_CTRL_REG2_MODS_HIGHRES, 0},
    /*! Configure the MMA845x CTRL_REG3 to set the Interrupt polarity to ACTIVE high. */
    {MMA845x_CTRL_REG3, MMA845x_CTRL_REG3_IPOL_HIGH, 0},
    /*! Configure the MMA845x CTRL_REG4 to enable the data ready interrupt. */
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PL_CFG, MMA845x_PL_CFG_PL_EN_ENABLED|MMA845x_PL_CFG_DBCNTM_CLR, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PL_COUNT, 0xFF, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_FF_MT_CFG, MMA845x_FF_MT_CFG_OAE_FREEFALL|MMA845x_FF_MT_CFG_XEFE_ENABLED|MMA845x_FF_MT_CFG_YEFE_ENABLED|MMA845x_FF_MT_CFG_ZEFE_ENABLED, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_FF_MT_COUNT, 0x02, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_FF_MT_THS, MMA845x_FF_MT_THS_DBCNTM_CLR|0x02, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_TRANSIENT_CFG, MMA845x_TRANSIENT_CFG_XTEFE_ENABLED|MMA845x_TRANSIENT_CFG_YTEFE_ENABLED|MMA845x_TRANSIENT_CFG_ZTEFE_ENABLED, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_TRANSIENT_THS, MMA845x_TRANSIENT_THS_DBCNTM_CLR|0x10, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_TRANSIENT_COUNT, 0x0C, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_CFG, MMA845x_PULSE_CFG_XSPEFE_ENABLED|MMA845x_PULSE_CFG_YSPEFE_ENABLED|MMA845x_PULSE_CFG_ZSPEFE_ENABLED, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_THSX, 0x37, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_THSY, 0x37, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_THSZ, 0x52, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_TMLT, 0x30, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_LTCY, 0xF0, 0},
    /*! Configure the MMA845x to set interrupt polarity as Active High. */
    {MMA845x_PULSE_WIND, 0x3C, 0},
    /*! Configure the MMA845x to enable Interrupts for Data Ready. */
    {MMA845x_CTRL_REG4, MMA845x_CTRL_REG4_INT_EN_DRDY_ENABLED|MMA845x_CTRL_REG4_INT_EN_LNDPRT_ENABLED|MMA845x_CTRL_REG4_INT_EN_FF_MT_ENABLED|MMA845x_CTRL_REG4_INT_EN_TRANS_ENABLED|MMA845x_CTRL_REG4_INT_EN_PULSE_ENABLED, 0},
    /*! Configure the MMA845x CTRL_REG5 to route Interrupt to INT1 pin. */
    {MMA845x_CTRL_REG5, MMA845x_CTRL_REG5_INT_CFG_DRDY_INT1, 0},
    __END_WRITE_DATA__};

/*! Prepare the register read list to read the raw Accel data from MMA845x. */
const registerreadlist_t mma845x_Output_Values[] = {
    {.readFrom = MMA845x_OUT_X_MSB, .numBytes = MMA845x_ACCEL_DATA_SIZE}, __END_READ_DATA__};
/*! Prepare the register read for Status Register. */
const registerreadlist_t cMma845xqStatus[] = {
    {.readFrom = MMA845x_INT_SOURCE, .numBytes = 1}, __END_READ_DATA__};
const registerreadlist_t cMma845xqPLStatus[] = {
    {.readFrom = MMA845x_PL_STATUS, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bMma845xDataReady = false, bMma845xReady = false;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* This is the Sensor Data Ready ISR implementation.*/
void mma845x_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bMma845xDataReady = true;
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
                if (hostCommand[1] == gStreamID && bMma845xReady && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bMma845xReady && bStreamingEnabled == true)
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
    uint8_t data[MMA845x_ACCEL_DATA_SIZE], intsrcdata, PLstatusdata, streamingPacket[STREAMING_HEADER_LEN + MMA845x_STREAM_DATA_SIZE];

    mma845x_i2c_sensorhandle_t mma845xDriver;
    mma845x_acceluserdata_t rawData = {.timestamp = 0};

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

    /*! Initialize INT1 MMA845x pin used by FRDM board */
    pGpioDriver->pin_init(&MMA845x_INT1, GPIO_DIRECTION_IN, NULL, &mma845x_int_data_ready_callback, NULL);

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

    /*! Initialize the MMA845x sensor driver. */
    status = MMA845x_I2C_Initialize(&mma845xDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA845x_I2C_ADDR,
                                    MMA8451_WHO_AM_I_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE == status)
    {
        /*!  Set the task to be executed while waiting for I2C transactions to complete. */
        MMA845x_I2C_SetIdleTask(&mma845xDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the MMA845x sensor driver. */
        status = MMA845x_I2C_Configure(&mma845xDriver, mma845x_Config_Isr);
        if (SENSOR_ERROR_NONE == status)
        {
            bMma845xReady = true;
        }
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID =
        Host_IO_Init(pUartDriver, (void *)mma845xDriver.pCommDrv, &mma845xDriver.deviceInfo, NULL, MMA845x_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bMma845xReady = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, MMA845x_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED); /* Set LED to indicate application is ready. */
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /* Process packets only if streaming has been enabled by Host and ISR is available.
         * In ISR Mode we do not need to check Data Ready Register.
         * The receipt of interrupt will indicate data is ready. */
        if (false == bStreamingEnabled || false == bMma845xDataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bMma845xDataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read raw sensor data from the MMA845x. */
        status = MMA845x_I2C_ReadData(&mma845xDriver, mma845x_Output_Values, data);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            continue;
        }

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Convert the raw sensor data to signed 32-bit and 16-bit containers for display to the debug port. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | data[1];
        rawData.accel[0] /= 4;
        rawData.accel[1] = ((int16_t)data[2] << 8) | data[3];
        rawData.accel[1] /= 4;
        rawData.accel[2] = ((int16_t)data[4] << 8) | data[5];
        rawData.accel[2] /= 4;

        /*! Read INT_SRC 0x0C from MMA845x. */
        status = MMA845x_I2C_ReadData(&mma845xDriver, cMma845xqStatus, &intsrcdata);
        status = MMA845x_I2C_ReadData(&mma845xDriver, cMma845xqPLStatus, &PLstatusdata);
        /* Send INTSRC */
        rawData.intsrc = intsrcdata;

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, MMA845x_STREAM_DATA_SIZE);
        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
