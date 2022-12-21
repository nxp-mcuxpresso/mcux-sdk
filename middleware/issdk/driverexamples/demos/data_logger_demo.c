/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file data_logger_demo.c
 * @brief The data_logger_demo.c file implements the ISSDK Data Logger for RD-KL25-AGMP01
 *        example demonstration with one sensor in Interrupt mode and other two in polling mode.
 *        MPL3115 is in One-Shot Poll Mode.
 *        FXOS8700 is @200Hz Hybrid Poll Mode.
 *        FXAS21002 is @200Hz Interrupt Mode.
 *        Data from MPL3115, FXOS8700 and FXAS21002 is only read when INT from FXAS21002 is received.
 *        The FXAS21002 ODR serves as the application ODR time keeper.
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
#include "mpl3115_drv.h"
#include "fxos8700_drv.h"
#include "fxas21002_drv.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define STREAMING_PKT_TIMESTAMP_LEN (4)
#define FXOS8700_ACCEL_DATA_SIZE (6)
#define FXOS8700_MAG_DATA_SIZE (6)
#define MPL3115_PADDING_SIZE (1)
#define MPL3115_PRESSURE_DATA_SIZE (3)
#define MPL3115_TEMPERATURE_DATA_SIZE (2)

#define FXOS8700_DATA_SIZE (FXOS8700_ACCEL_DATA_SIZE + FXOS8700_MAG_DATA_SIZE)
#define FXAS21002_DATA_SIZE (FXAS21002_GYRO_DATA_SIZE)
#define MPL3115_DATA_SIZE (MPL3115_PRESSURE_DATA_SIZE + MPL3115_TEMPERATURE_DATA_SIZE)

/* Toggle LED after every 100 saples are processed. */
#define LED_TOGGLE_RATE (100)
#define STREAMING_PAYLOAD_LEN \
    (STREAMING_PKT_TIMESTAMP_LEN + FXOS8700_DATA_SIZE + FXAS21002_DATA_SIZE + MPL3115_DATA_SIZE + MPL3115_PADDING_SIZE)
#define STREAMING_PAYLOAD_SHORT_LEN (STREAMING_PKT_TIMESTAMP_LEN + FXOS8700_DATA_SIZE + FXAS21002_DATA_SIZE)

/* Mask out default NMI handler to work around FXOS8700 Init time halt on RD-KL25-AGMP01. */
#define nmi_handler NMI_Handler

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "Generic Data Logger Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure FXOS8700 in Hybrid mode. */
const registerwritelist_t fxos8700_Config_Hybrid[] = {
    /*! System and Control registers. */
    /*! Configure the FXOS8700 to 200Hz sampling rate. */
    {FXOS8700_CTRL_REG1, FXOS8700_CTRL_REG1_DR_HYBRID_200_HZ, FXOS8700_CTRL_REG1_DR_MASK},
    {FXOS8700_M_CTRL_REG1, FXOS8700_M_CTRL_REG1_M_ACAL_EN | FXOS8700_M_CTRL_REG1_M_HMS_HYBRID_MODE,
                           FXOS8700_M_CTRL_REG1_M_ACAL_MASK | FXOS8700_M_CTRL_REG1_M_HMS_MASK}, /*! Enable the Hybrid Mode. */
    {FXOS8700_M_CTRL_REG2, FXOS8700_M_CTRL_REG2_M_AUTOINC_HYBRID_MODE | FXOS8700_M_CTRL_REG2_M_RST_CNT_DISABLE,
                           FXOS8700_M_CTRL_REG2_M_AUTOINC_MASK | FXOS8700_M_CTRL_REG2_M_RST_CNT_MASK}, /*! Enable the Data read with Hybrid Mode. */
    __END_WRITE_DATA__};

/*! Command definition to read the Accel + Mag Data */
const registerreadlist_t fxos8700_Output_values[] = {{.readFrom = FXOS8700_OUT_X_MSB, .numBytes = FXOS8700_DATA_SIZE},
                                                     __END_READ_DATA__};

/*! Prepare the register write list to configure FXAS21002 in Interrupt Mode. */
const registerwritelist_t fxas21002_Config_Isr[] = {
    /*! Configure CTRL_REG1 register to put FXAS21002 to 200Hz sampling rate. */
    {FXAS21002_CTRL_REG1, FXAS21002_CTRL_REG1_DR_200HZ, FXAS21002_CTRL_REG1_DR_MASK},
    /*! Configure CTRL_REG2 register to set interrupt configuration settings. */
    {FXAS21002_CTRL_REG2, FXAS21002_CTRL_REG2_IPOL_ACTIVE_HIGH | FXAS21002_CTRL_REG2_INT_EN_DRDY_ENABLE |
                              FXAS21002_CTRL_REG2_INT_CFG_DRDY_INT1,
     FXAS21002_CTRL_REG2_IPOL_MASK | FXAS21002_CTRL_REG2_INT_EN_DRDY_MASK | FXAS21002_CTRL_REG2_INT_CFG_DRDY_MASK},
    __END_WRITE_DATA__};

/*! Prepare the register read list to read the raw gyro data from the FXAS21002. */
const registerreadlist_t fxas21002_Output_Values[] = {
    {.readFrom = FXAS21002_OUT_X_MSB, .numBytes = FXAS21002_DATA_SIZE}, __END_READ_DATA__};

/*! @brief Register settings for Triggring One-Shot Sampling. */
const registerwritelist_t cMpl3115SetOST[] = {
    /* Set the One ShoT Bit. */
    {MPL3115_CTRL_REG1, MPL3115_CTRL_REG1_OST_SET, MPL3115_CTRL_REG1_OST_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Register containing OST Bit. */
const registerreadlist_t cMpl3115GetOST[] = {{.readFrom = MPL3115_CTRL_REG1, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Address and size of Raw Pressure+Temperature Data in Normal Mode. */
const registerreadlist_t mpl3115_Output_Values[] = {{.readFrom = MPL3115_OUT_P_MSB, .numBytes = MPL3115_DATA_SIZE},
                                                    __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bFxas21002DataReady = false, bDataLoggerReady = false;
uint8_t gPrimaryStreamID; /* The auto assigned Stream ID to be used to stream complete data. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*! Handler for NMI Interrupt. */
void nmi_handler(void *pUserData)
{ /* Ignore NMI interrupt which may be caused due to FXOS8700 INT1 being connected to NMI. */
    __NOP();
}

/* This is the Sensor Data Ready ISR implementation.*/
void fxas21002_isr(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bFxas21002DataReady = true;
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
                if (hostCommand[1] == gPrimaryStreamID && bDataLoggerReady && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gPrimaryStreamID && bDataLoggerReady && bStreamingEnabled == true)
                {
                    pGpioDriver->clr_pin(&LED_GREEN);
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
    size_t payLoadLen;
    int32_t status;
    uint8_t secondaryStreamID1, secondaryStreamID2, /* The auto assigned Stream ID not to be used to stream data. */
        dataReady_3115, toggle_pin = 0,             /* The MPL3115 sensor data ready flag and LED Toggle Counter. */
        data[FXOS8700_DATA_SIZE + FXAS21002_DATA_SIZE + MPL3115_DATA_SIZE],
                        streamingPacket[STREAMING_HEADER_LEN + STREAMING_PAYLOAD_LEN];

    fxos8700_accelmagdata_t rawData_fxos8700;
    fxas21002_gyrodata_t rawData_fxas21002;
    mpl3115_pressuredata_t rawData_mpl3115;

    ARM_DRIVER_I2C *pI2cDriver = &I2C_S_DRIVER;
    ARM_DRIVER_USART *pUartDriver = &HOST_S_DRIVER;

    mpl3115_i2c_sensorhandle_t mpl3115Driver;
    fxos8700_i2c_sensorhandle_t fxos8700Driver;
    fxas21002_i2c_sensorhandle_t fxas21002Driver;

    /*! Initialize the MCU hardware. */
    BOARD_BootClockRUN();
    BOARD_SystickEnable();

    /* Create the Short Application Name String for ADS. */
    sprintf(embAppName, "%s:%s", APPLICATION_NAME, APPLICATION_VERSION);

    /* Run ADS. */
    BOARD_RunADS(embAppName, boardString, shieldString, ADS_MAX_STRING_LENGTH);

    /* Create the Full Application Name String for Device Info Response. */
    sprintf(embAppName, "%s:%s:%s", SHIELD_NAME, APPLICATION_NAME, APPLICATION_VERSION);

    /*! Initialize INT1 FXAS21002 pin used by RD board */
    pGpioDriver->pin_init(&INT1_FXAS21002, GPIO_DIRECTION_IN, NULL, &fxas21002_isr, NULL);

    /*! Initialize GREEN LED pin used by RD board */
    pGpioDriver->pin_init(&LED_GREEN, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGpioDriver->set_pin(&LED_GREEN); /* Clear LED to indicate application is not ready. */

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
    {
        /*! Initialize the MPL3115 sensor driver. */
        status = MPL3115_I2C_Initialize(&mpl3115Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MPL3115_I2C_ADDR,
                                        MPL3115_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! Initialize the FXOS8700 sensor driver. */
        status = FXOS8700_I2C_Initialize(&fxos8700Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXOS8700_I2C_ADDR,
                                         FXOS8700_WHO_AM_I_PROD_VALUE);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! Initialize the FXAS21002 sensor driver. */
        status = FXAS21002_I2C_Initialize(&fxas21002Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXAS21002_I2C_ADDR,
                                          FXAS21002_WHO_AM_I_WHOAMI_PROD_VALUE);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }

        /*!  Set the task to be executed while waiting for I2C transactions to complete. */
        MPL3115_I2C_SetIdleTask(&mpl3115Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);
        FXOS8700_I2C_SetIdleTask(&fxos8700Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);
        FXAS21002_I2C_SetIdleTask(&fxas21002Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the fxos8700 sensor driver. */
        status = FXOS8700_I2C_Configure(&fxos8700Driver, fxos8700_Config_Hybrid);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! Configure the FXAS21002 sensor driver. */
        status = FXAS21002_I2C_Configure(&fxas21002Driver, fxas21002_Config_Isr);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! In One-Shot Mode we do not need to Configure MPL3115, instead we will set OST bit directly. */

        /* If we reach here then all sensors have been initialized, configured and GDL is ready. */
        bDataLoggerReady = true;

    } while (false);

    /*! Initialize streaming and assign a Stream IDs. */
    gPrimaryStreamID =
        Host_IO_Init(pUartDriver, (void *)mpl3115Driver.pCommDrv, &mpl3115Driver.deviceInfo, NULL, MPL3115_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gPrimaryStreamID)
    {
        bDataLoggerReady = false;
    }
    secondaryStreamID1 = /* This is required for registering the slave address with Host I/O for Register Read/Write. */
        Host_IO_Init(pUartDriver, (void *)fxos8700Driver.pCommDrv, &fxos8700Driver.deviceInfo, NULL, FXOS8700_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == secondaryStreamID1)
    {
        bDataLoggerReady = false;
    }
    secondaryStreamID2 = /* This is required for registering the slave address with Host I/O for Register Read/Write. */
        Host_IO_Init(pUartDriver, (void *)fxas21002Driver.pCommDrv, &fxas21002Driver.deviceInfo, NULL,
                     FXAS21002_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == secondaryStreamID2)
    {
        bDataLoggerReady = false;
    }

    if (true == bDataLoggerReady)
    {
        *((uint32_t *)&streamingPacket[STREAMING_HEADER_LEN]) = 0; /* Initialize time stamp field. */
        pGpioDriver->clr_pin(&LED_GREEN);                          /* Set LED to indicate application is ready. */
    }

    for (;;) /* Forever loop */
    {        /* Check for incoming commands from Host. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /* Process packets only if streaming has been enabled by Host and ISR is available.
         * In ISR Mode we do not need to check Data Ready Register.
         * The receipt of interrupt will indicate data is ready. */
        if (false == bStreamingEnabled || false == bFxas21002DataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bFxas21002DataReady = false;
        }

        /* Read timestamp from Systick framework. */
        *((uint32_t *)&streamingPacket[STREAMING_HEADER_LEN]) += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Read the raw sensor data from the fxos8700. */
        status = FXOS8700_I2C_ReadData(&fxos8700Driver, fxos8700_Output_values, data);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        /* Convert to Little Endian, Right Justified, Even Padded Signed integer counts. */
        rawData_fxos8700.accel[0] = ((int16_t)data[0] << 8) | data[1];
        rawData_fxos8700.accel[0] /= 4;
        rawData_fxos8700.accel[1] = ((int16_t)data[2] << 8) | data[3];
        rawData_fxos8700.accel[1] /= 4;
        rawData_fxos8700.accel[2] = ((int16_t)data[4] << 8) | data[5];
        rawData_fxos8700.accel[2] /= 4;
        rawData_fxos8700.mag[0] = ((int16_t)data[6] << 8) | data[7];
        rawData_fxos8700.mag[1] = ((int16_t)data[8] << 8) | data[9];
        rawData_fxos8700.mag[2] = ((int16_t)data[10] << 8) | data[11];

        /* Copy the converted sample to the streaming buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN, &rawData_fxos8700.accel,
               sizeof(rawData_fxos8700.accel));
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + FXOS8700_ACCEL_DATA_SIZE,
               &rawData_fxos8700.mag, sizeof(rawData_fxos8700.mag));

        /*! Read the raw sensor data from the FXAS21002. */
        status = FXAS21002_I2C_ReadData(&fxas21002Driver, fxas21002_Output_Values, data + FXOS8700_DATA_SIZE);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        /* Convert to Little Endian, Right Justified, Even Padded Signed integer counts. */
        rawData_fxas21002.gyro[0] = ((int16_t)data[12] << 8) | data[13];
        rawData_fxas21002.gyro[1] = ((int16_t)data[14] << 8) | data[15];
        rawData_fxas21002.gyro[2] = ((int16_t)data[16] << 8) | data[17];

        /* Copy the converted sample to the streaming buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + FXOS8700_DATA_SIZE,
               &rawData_fxas21002.gyro, sizeof(rawData_fxas21002.gyro));

        /*! MPL3115 is in One-Shot Mode so we have to trigger acquizition of new sample based on OST bit. */
        status = MPL3115_I2C_ReadData(&mpl3115Driver, cMpl3115GetOST, &dataReady_3115);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }
        if (MPL3115_CTRL_REG1_OST_RESET == (dataReady_3115 & MPL3115_CTRL_REG1_OST_MASK))
        {
            /*! Read raw sensor data from the MPL3115. */
            status = MPL3115_I2C_ReadData(&mpl3115Driver, mpl3115_Output_Values,
                                          data + FXOS8700_DATA_SIZE + FXAS21002_DATA_SIZE);
            if (ARM_DRIVER_OK != status)
            {
                return -1;
            }

            /* Convert to Little Endian, Right Justified, Even Padded Signed integer counts. */
            rawData_mpl3115.pressure = (uint32_t)((data[18]) << 16) | ((data[19]) << 8) | ((data[20]));
            rawData_mpl3115.pressure /= 16;
            rawData_mpl3115.temperature = (int16_t)((data[21]) << 8) | (data[22]);
            rawData_mpl3115.temperature /= 16;

            /* Copy the converted sample to the streaming buffer. */
            memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + FXOS8700_DATA_SIZE +
                       FXAS21002_DATA_SIZE,
                   &rawData_mpl3115.pressure, sizeof(rawData_mpl3115.pressure));
            memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + FXOS8700_DATA_SIZE +
                       FXAS21002_DATA_SIZE + MPL3115_PRESSURE_DATA_SIZE + MPL3115_PADDING_SIZE,
                   &rawData_mpl3115.temperature, sizeof(rawData_mpl3115.temperature));

            /* Trigger acquisition of New Sample. */
            status = Sensor_I2C_Write(mpl3115Driver.pCommDrv, &mpl3115Driver.deviceInfo, mpl3115Driver.slaveAddress,
                                      cMpl3115SetOST);
            if (ARM_DRIVER_OK != status)
            {
                return -1;
            }
            payLoadLen = STREAMING_PAYLOAD_LEN;
        }
        else
        {
            payLoadLen = STREAMING_PAYLOAD_SHORT_LEN;
        }

        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gPrimaryStreamID, streamingPacket, payLoadLen);
        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, STREAMING_HEADER_LEN + payLoadLen, HOST_FORMAT_HDLC);

        if (toggle_pin++ == LED_TOGGLE_RATE)
        {                   /* Toggle LED at slow refresh rate to make it perceivable. */
            toggle_pin = 0; /* Toggle LED to indicate application is active. */
            pGpioDriver->toggle_pin(&LED_GREEN);
        }
    }
}
