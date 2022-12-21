/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file demo_11_axis_mult2b.c
 * @brief The demo_11_axis_mult2b.c file implements the ISSDK MMA8652, MAG3110, FXAS21002 and MPL3115 sensors
 *        11-Axis demo example demonstration using Bluetooth.
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
#include "mag3110_drv.h"
#include "mpl3115_drv.h"
#include "mma865x_drv.h"
#include "fxas21002_drv.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define MPL3115_PADDING_SIZE (1)
#define MPL3115_PRESSURE_DATA_SIZE (3)
#define MPL3115_TEMPERATURE_DATA_SIZE (2)

#define STREAMING_PKT_TIMESTAMP_LEN (4)
#define MMA865x_DATA_SIZE (6)
#define MAG3110_DATA_SIZE (6)
#define FXAS21002_DATA_SIZE (FXAS21002_GYRO_DATA_SIZE)
#define MPL3115_DATA_SIZE (MPL3115_PRESSURE_DATA_SIZE + MPL3115_TEMPERATURE_DATA_SIZE)

#define STREAMING_PAYLOAD_LEN                                                                                        \
    (STREAMING_PKT_TIMESTAMP_LEN + MMA865x_DATA_SIZE + MAG3110_DATA_SIZE + FXAS21002_DATA_SIZE + MPL3115_DATA_SIZE + \
     MPL3115_PADDING_SIZE)

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "11 Axis Sensor Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

/* FF_MT freefall counter register values for High resolution Mode and ODR = 100Hz.
 * These values have been derived based on the MMA865x DataSheet and Application Note AN4070 for MMA8451 (the same is
 * applicable to MMA865x too).
 * http://cache.freescale.com/files/sensors/doc/app_note/AN4070.pdf */
#define FF_MT_WT_DBCNT 0x32  /* Debounce count value. */
#define FF_MT_THS_VALUE 0x03 /* Threshold Value. */

#define SDCD_FF_EVT_ID (0x01)
#define P_THS_EVENT_ID (0x02)
#define EVENT_PAYLOAD_LEN (1)

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for freefall detection and poll mode. */
const registerwritelist_t cMma865xConfigFreeFall[] =
    {/*! Configure the MMA865x to set FS Range as 2g. */
     {MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
     /*! Configure the MMA865x to set ODR to 50Hz. */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_50HZ, MMA865x_CTRL_REG1_DR_MASK},
     /*! Configure the MMA865x to set High Resolution mode. */
     {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
     /*! Configure the MMA865x to set interrupt polarity as Active High. */
     {MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
     /*! Configure the MMA865x to enable Interrupts for Data Ready. */
     {MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_FF_MT_EN, MMA865x_CTRL_REG4_INT_EN_FF_MT_MASK},
     /*! Configure the MMA865x to route Data Ready Interrupts to INT1. */
     {MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_FF_MT_INT1, MMA865x_CTRL_REG5_INT_CFG_FF_MT_MASK},
     /*! Configure the MMA865x to set freefall Mode and enable all XYZ axis events and event latching. */
     {MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_ELE_EN | MMA865x_FF_MT_CFG_OAE_FREEFALL | MMA865x_FF_MT_CFG_XEFE_EN |
                             MMA865x_FF_MT_CFG_YEFE_EN | MMA865x_FF_MT_CFG_ZEFE_EN,
      MMA865x_FF_MT_CFG_ELE_MASK | MMA865x_FF_MT_CFG_OAE_MASK | MMA865x_FF_MT_CFG_XEFE_MASK |
          MMA865x_FF_MT_CFG_YEFE_MASK | MMA865x_FF_MT_CFG_ZEFE_MASK},
     /*! Configure the MMA865x to set Debounce counter to be cleared on favourable events and the thresholds . */
     {MMA865x_FF_MT_THS, MMA865x_FF_MT_THS_DBCNTM_INC_CLR | FF_MT_THS_VALUE,
      MMA865x_FF_MT_THS_DBCNTM_MASK | MMA865x_FF_MT_THS_THS_MASK},
     /*! Configure the MMA865x to set Debounce counter value. */
     {MMA865x_FF_MT_COUNT, FF_MT_WT_DBCNT, 0},
     __END_WRITE_DATA__};

/*! Prepare the register read list to read the raw Accel data from MMA865x. */
const registerreadlist_t cMma865xOutputValues[] = {{.readFrom = MMA865x_OUT_X_MSB, .numBytes = MMA865x_DATA_SIZE},
                                                   __END_READ_DATA__};

/*! @brief Address of Freefall Status Register. */
const registerreadlist_t cMma865xFreeFallEvent[] = {{.readFrom = MMA865x_FF_MT_SRC, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Register settings for Normal (non buffered) mode. */
const registerwritelist_t cMag3110ConfigNormal[] = {
    /* Set Ouput Rate @40HZ (ODR = 1 and OSR = 16). */
    {MAG3110_CTRL_REG1, MAG3110_CTRL_REG1_DR_ODR_1 | MAG3110_CTRL_REG1_OS_OSR_16,
                        MAG3110_CTRL_REG1_DR_MASK | MAG3110_CTRL_REG1_OS_MASK},
    /* Set Auto Magnetic Sensor Reset. */
    {MAG3110_CTRL_REG2, MAG3110_CTRL_REG2_MAG_RST_EN | MAG3110_CTRL_REG2_AUTO_MSRT_EN_EN | MAG3110_CTRL_REG2_RAW_RAW,
                        MAG3110_CTRL_REG2_MAG_RST_MASK | MAG3110_CTRL_REG2_AUTO_MSRT_EN_MASK | MAG3110_CTRL_REG2_RAW_MASK},
    __END_WRITE_DATA__};

/*! @brief Address and size of Raw Magnetic Data in Normal Mode. */
const registerreadlist_t cMag3110OutputNormal[] = {{.readFrom = MAG3110_OUT_X_MSB, .numBytes = MAG3110_DATA_SIZE},
                                                   __END_READ_DATA__};

/*! Prepare the register write list to configure FXAS21002 in non-FIFO mode. */
const registerwritelist_t fxas21002_Config_Normal[] = {
    /*! Configure CTRL_REG1 register to put FXAS21002 to 25Hz sampling rate. */
    {FXAS21002_CTRL_REG1, FXAS21002_CTRL_REG1_DR_25HZ, FXAS21002_CTRL_REG1_DR_MASK},
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
    /* Route Interrupt to INT1. */
    {MPL3115_CTRL_REG5, MPL3115_CTRL_REG5_INT_CFG_PTH_INT1, MPL3115_CTRL_REG5_INT_CFG_PTH_MASK},
    /* Enable Interrupts for Pressure Threshold Events. */
    {MPL3115_CTRL_REG4, MPL3115_CTRL_REG4_INT_EN_PTH_INTENABLED, MPL3115_CTRL_REG4_INT_EN_PTH_MASK},
    /* Set INT Active High. */
    {MPL3115_CTRL_REG3, MPL3115_CTRL_REG3_IPOL1_HIGH, MPL3115_CTRL_REG3_IPOL1_MASK},
    /* Set the One ShoT Bit. */
    {MPL3115_CTRL_REG1, MPL3115_CTRL_REG1_OST_SET, MPL3115_CTRL_REG1_OST_MASK},
    __END_WRITE_DATA__};

/*! @brief Address and size of Raw Pressure+Temperature Data in Normal Mode. */
const registerreadlist_t mpl3115_Output_Values[] = {{.readFrom = MPL3115_OUT_P_MSB, .numBytes = MPL3115_DATA_SIZE},
                                                    __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bFxas21002DataReady = false, bMult2bReady = false, bMma865xEventReady = false,
              bMpl3115EventReady = false;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* This is the Sensor Data Ready ISR implementation.*/
void fxas21002_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bFxas21002DataReady = true;
}

/*! @brief This is the Sensor WT Event Ready ISR implementation. */
void mma865x_int_event_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled event ready. */
    bMma865xEventReady = true;
}

/* This is the Sensor PTH Event Ready ISR implementation.*/
void mpl3115_int_event_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bMpl3115EventReady = true;
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
                if (hostCommand[1] == gStreamID && bMult2bReady && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bMult2bReady && bStreamingEnabled == true)
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
    uint8_t eventReady = 0, eventPacket[STREAMING_HEADER_LEN + EVENT_PAYLOAD_LEN], secondaryStreamID1,
            secondaryStreamID2, secondaryStreamID3, /* Auto assigned StreamIDs not to be used for streaming. */
        streamingPacket[STREAMING_HEADER_LEN + STREAMING_PAYLOAD_LEN],
            data[MMA865x_DATA_SIZE + MAG3110_DATA_SIZE + FXAS21002_DATA_SIZE + MPL3115_DATA_SIZE];

    mma865x_i2c_sensorhandle_t mma865xDriver;
    mag3110_i2c_sensorhandle_t mag3110Driver;
    fxas21002_i2c_sensorhandle_t fxas21002Driver;
    mpl3115_i2c_sensorhandle_t mpl3115Driver;

    mma865x_acceldata_t rawData_mma865x;
    mag3110_magdata_t rawData_mag3110;
    fxas21002_gyrodata_t rawData_fxas21002;
    mpl3115_pressuredata_t rawData_mpl3115;

    ARM_DRIVER_I2C *pI2cDriver = &I2C_S_DRIVER;
    ARM_DRIVER_USART *pUartDriver = &HOST_B_DRIVER;

    /*! Initialize the MCU hardware. */
    BOARD_BootClockRUN();
    BOARD_SystickEnable();

    /* Create the Short Application Name String for ADS. */
    sprintf(embAppName, "%s:%s", APPLICATION_NAME, APPLICATION_VERSION);

    /* Run ADS. */
    BOARD_RunADS(embAppName, boardString, shieldString, ADS_MAX_STRING_LENGTH);

    /* Create the Full Application Name String for Device Info Response. */
    sprintf(embAppName, "%s:%s:%s", SHIELD_NAME, APPLICATION_NAME, APPLICATION_VERSION);

    /*! Initialize FXAS21002 INT1 pin used by FRDM board */
    pGpioDriver->pin_init(&FXAS21002_INT1, GPIO_DIRECTION_IN, NULL, &fxas21002_int_data_ready_callback, NULL);

    /*! Initialize MMA865x INT1 pin used by FRDM board */
    pGpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma865x_int_event_ready_callback, NULL);

    /*! Initialize INT1 MAG3110 used on FRDM board.
     *  NOTE: INT1 of MPL3115 pin on MULT2B maps to PTA0 of K64F which is used as OpenSDA CLK.
     *  Hence, we will wire connect INT1_MPL3115 to INT_MAG (J5_Pin3 to J3_Pin2) and use INT1_MAG3110 handle instead. */
    pGpioDriver->pin_init(&MAG3110_INT1, GPIO_DIRECTION_IN, NULL, &mpl3115_int_event_ready_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
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
    status = pUartDriver->Initialize(HOST_B_SIGNAL_EVENT);
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
    { /*! Initialize the MMA865x sensor driver. */
        status = MMA865x_I2C_Initialize(&mma865xDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8652_I2C_ADDR,
                                        MMA8652_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! Initialize MAG3110 sensor driver. */
        status = MAG3110_I2C_Initialize(&mag3110Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MAG3110_I2C_ADDR,
                                        MAG3110_WHOAMI_VALUE);
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
        /*! Initialize the MPL3115 sensor driver. */
        status = MPL3115_I2C_Initialize(&mpl3115Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MPL3115_I2C_ADDR,
                                        MPL3115_WHOAMI_VALUE);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }

        /*!  Set the task to be executed while waiting for SPI transactions to complete. */
        MMA865x_I2C_SetIdleTask(&mma865xDriver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);
        MAG3110_I2C_SetIdleTask(&mag3110Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);
        FXAS21002_I2C_SetIdleTask(&fxas21002Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);
        MPL3115_I2C_SetIdleTask(&mpl3115Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the FXLS8962 sensor. */
        status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigFreeFall);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! Configure the MAG3110 sensor driver. */
        status = MAG3110_I2C_Configure(&mag3110Driver, cMag3110ConfigNormal);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! Configure the FXAS21002 sensor driver. */
        status = FXAS21002_I2C_Configure(&fxas21002Driver, fxas21002_Config_Normal);
        if (SENSOR_ERROR_NONE != status)
        {
            break;
        }
        /*! In One-Shot Mode we do not need to Configure MPL3115, instead we will set OST bit directly. */

        bMult2bReady = true;
    } while (false);

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID =
        Host_IO_Init(pUartDriver, (void *)mma865xDriver.pCommDrv, &mma865xDriver.deviceInfo, NULL, MMA8652_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bMult2bReady = false;
    }
    secondaryStreamID1 = /* This is required for registering the slave address with Host I/O for Register Read/Write. */
        Host_IO_Init(pUartDriver, (void *)mag3110Driver.pCommDrv, &mag3110Driver.deviceInfo, NULL, MAG3110_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == secondaryStreamID1)
    {
        bMult2bReady = false;
    }
    secondaryStreamID2 = /* This is required for registering the slave address with Host I/O for Register Read/Write. */
        Host_IO_Init(pUartDriver, (void *)fxas21002Driver.pCommDrv, &fxas21002Driver.deviceInfo, NULL,
                     FXAS21002_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == secondaryStreamID2)
    {
        bMult2bReady = false;
    }
    secondaryStreamID3 = /* This is required for registering the slave address with Host I/O for Register Read/Write. */
        Host_IO_Init(pUartDriver, (void *)mpl3115Driver.pCommDrv, &mpl3115Driver.deviceInfo, NULL, MPL3115_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == secondaryStreamID3)
    {
        bMult2bReady = false;
    }

    if (true == bMult2bReady)
    {
        *((uint32_t *)&streamingPacket[STREAMING_HEADER_LEN]) = 0; /* Initialize time stamp field. */
        pGpioDriver->clr_pin(&GREEN_LED);                          /* Set LED to indicate application is ready. */
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, STREAMING_PAYLOAD_LEN);
        /*! Populate event header. */
        Host_IO_Add_ISO_Header(EVENT_STREAM_ID, eventPacket, EVENT_PAYLOAD_LEN);
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        if (bMma865xEventReady)
        { /*! Read the Freefall event FLAGs from FXLS8962 to clear INT2. */
            status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xFreeFallEvent, &eventReady);
            if (SENSOR_ERROR_NONE != status)
            {
                return -1;
            }

            if (MMA865x_FF_MT_SRC_EA_DETECTED == (eventReady & MMA865x_FF_MT_SRC_EA_MASK))
            { /* Update Event ID with Freefall event and send message to Host. */
                eventPacket[STREAMING_HEADER_LEN] = SDCD_FF_EVT_ID;
                Host_IO_Send(eventPacket, sizeof(eventPacket), HOST_FORMAT_HDLC);
            }

            eventReady = 0;
            bMma865xEventReady = false;
        }

        if (bMpl3115EventReady)
        { /* Send Pressure Threshold event message to Host. */
            eventPacket[STREAMING_HEADER_LEN] = P_THS_EVENT_ID;
            Host_IO_Send(eventPacket, sizeof(eventPacket), HOST_FORMAT_HDLC);
            bMpl3115EventReady = false;
        }

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
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /* Read timestamp from Systick framework. */
        *((uint32_t *)&streamingPacket[STREAMING_HEADER_LEN]) += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Read new raw sensor data from the MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xOutputValues, data);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        /* Convert to Little Endian, Right Justified, Even Padded Signed integer counts. */
        rawData_mma865x.accel[0] = ((int16_t)data[0] << 8) | data[1];
        rawData_mma865x.accel[0] /= 16;
        rawData_mma865x.accel[1] = ((int16_t)data[2] << 8) | data[3];
        rawData_mma865x.accel[1] /= 16;
        rawData_mma865x.accel[2] = ((int16_t)data[4] << 8) | data[5];
        rawData_mma865x.accel[2] /= 16;

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN, &rawData_mma865x.accel,
               sizeof(rawData_mma865x.accel));

        /*! Read raw sensor data from the MAG3110. */
        status = MAG3110_I2C_ReadData(&mag3110Driver, cMag3110OutputNormal, data + MMA865x_DATA_SIZE);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        /* Convert to Little Endian, Right Justified, Even Padded Signed integer counts. */
        rawData_mag3110.mag[0] = ((int16_t)data[6] << 8) | data[7];
        rawData_mag3110.mag[1] = ((int16_t)data[8] << 8) | data[9];
        rawData_mag3110.mag[2] = ((int16_t)data[10] << 8) | data[11];

		MAG3110_CalibrateHardIronOffset(&rawData_mag3110.mag[0], &rawData_mag3110.mag[1], &rawData_mag3110.mag[2]);
		
        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + MMA865x_DATA_SIZE,
               &rawData_mag3110.mag, sizeof(rawData_mag3110.mag));

        /*! Read the raw sensor data from the FXAS21002. */
        status = FXAS21002_I2C_ReadData(&fxas21002Driver, fxas21002_Output_Values,
                                        data + MMA865x_DATA_SIZE + MAG3110_DATA_SIZE);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        /* Convert to Little Endian, Right Justified, Even Padded Signed integer counts. */
        rawData_fxas21002.gyro[0] = ((int16_t)data[12] << 8) | data[13];
        rawData_fxas21002.gyro[1] = ((int16_t)data[14] << 8) | data[15];
        rawData_fxas21002.gyro[2] = ((int16_t)data[16] << 8) | data[17];

        /* Copy the converted sample to the streaming buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + MMA865x_DATA_SIZE +
                   MAG3110_DATA_SIZE,
               &rawData_fxas21002.gyro, sizeof(rawData_fxas21002.gyro));

        /*! Read raw sensor data from the MPL3115. */
        status = MPL3115_I2C_ReadData(&mpl3115Driver, mpl3115_Output_Values,
                                      data + MMA865x_DATA_SIZE + MAG3110_DATA_SIZE + FXAS21002_DATA_SIZE);
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
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + MMA865x_DATA_SIZE +
                   MAG3110_DATA_SIZE + FXAS21002_DATA_SIZE,
               &rawData_mpl3115.pressure, sizeof(rawData_mpl3115.pressure));
        memcpy(streamingPacket + STREAMING_HEADER_LEN + STREAMING_PKT_TIMESTAMP_LEN + MMA865x_DATA_SIZE +
                   MAG3110_DATA_SIZE + FXAS21002_DATA_SIZE + MPL3115_PRESSURE_DATA_SIZE + MPL3115_PADDING_SIZE,
               &rawData_mpl3115.temperature, sizeof(rawData_mpl3115.temperature));

        /* Trigger acquisition of New Sample. */
        status = Sensor_I2C_Write(mpl3115Driver.pCommDrv, &mpl3115Driver.deviceInfo, mpl3115Driver.slaveAddress,
                                  cMpl3115SetOST);

        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
