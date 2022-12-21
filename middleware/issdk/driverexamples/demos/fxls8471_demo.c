/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls8471_demo.c
 * @brief The fxls8471_demo.c file implements the ISSDK FXLS8471 sensor
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
#include "Driver_SPI.h"
#include "Driver_USART.h"

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "fxls8471q_drv.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXLS8471_STREAM_DATA_SIZE 11
/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "FXLS8471 Accelerometer Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

typedef struct
{
    uint32_t timestamp; /*! The time, this sample was recorded.  */
    int16_t accel[3];   /*!< The accel data */
    uint8_t intsrc;
} fxls8471q_acceldataUser_t;

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Prepare the register write list to configure FXLS8471Q in non-FIFO mode. */
const registerwritelist_t cFxls8471q_Config_Isr[] = {
    /*! Clear F_SETUP. */
    {FXLS8471Q_F_SETUP, 0x00, 0x00},
    /*! Set FS Range 2G. */
    {FXLS8471Q_XYZ_DATA_CFG, FXLS8471Q_XYZ_DATA_CFG_FS_FS_RANGE_2G, FXLS8471Q_XYZ_DATA_CFG_FS_MASK},
    /*! Configure CTRL_REG1 register to put FXLS8471Q to 100Hz sampling rate. */
    {FXLS8471Q_CTRL_REG1, FXLS8471Q_CTRL_REG1_DR_100HZ , FXLS8471Q_CTRL_REG1_DR_MASK},
    /*! Configure CTRL_REG2 register to put FXLS8471Q to High Resolution mode. */
    {FXLS8471Q_CTRL_REG2, FXLS8471Q_CTRL_REG2_MODS_HIGHRES, FXLS8471Q_CTRL_REG2_MODS_MASK},	
    /*! Configure settings for interrupt notification. */
    /*! Active High, Push-Pull */
    {FXLS8471Q_CTRL_REG3, FXLS8471Q_CTRL_REG3_IPOL_HIGH | FXLS8471Q_CTRL_REG3_PP_OD_PUSHPULL,
                          FXLS8471Q_CTRL_REG3_IPOL_MASK | FXLS8471Q_CTRL_REG3_PP_OD_MASK},
    //{FXLS8471Q_CTRL_REG4, FXLS8471Q_CTRL_REG4_INT_EN_DRDY_ENABLED,
    //                      FXLS8471Q_CTRL_REG4_INT_EN_DRDY_MASK}, /*! Data Ready Event. */
    {FXLS8471Q_CTRL_REG5, FXLS8471Q_CTRL_REG5_INT_CFG_DRDY_INT1, FXLS8471Q_CTRL_REG5_INT_CFG_DRDY_MASK}, /*! INT1 Pin */
    {FXLS8471Q_CTRL_REG4,255,0x00},

    //PL registers
    {FXLS8471Q_PL_CFG,FXLS8471Q_PL_CFG_DBCNTM_CLR ,FXLS8471Q_PL_CFG_DBCNTM_MASK},
    {FXLS8471Q_PL_CFG,FXLS8471Q_PL_CFG_PL_EN_ENABLED  ,FXLS8471Q_PL_CFG_PL_EN_MASK },
    {FXLS8471Q_PL_COUNT, 0x40, 0x00},//FF
    {FXLS8471Q_PL_BF_ZCOMP,4 ,FXLS8471Q_PL_BF_ZCOMP_ZLOCK_MASK},
    {FXLS8471Q_PL_BF_ZCOMP,2 ,FXLS8471Q_PL_BF_ZCOMP_BKFR_MASK},
    {FXLS8471Q_PL_THS_REG,132,0x00},


    //Freefall registers
    {FXLS8471Q_A_FFMT_CFG,FXLS8471Q_A_FFMT_CFG_ELE_ENABLED    ,FXLS8471Q_A_FFMT_CFG_ELE_MASK },
    {FXLS8471Q_A_FFMT_CFG,FXLS8471Q_A_FFMT_CFG_OAE_FREEFALL   ,FXLS8471Q_A_FFMT_CFG_OAE_MASK  },
    {FXLS8471Q_A_FFMT_CFG,FXLS8471Q_A_FFMT_CFG_XEFE_ENABLED   ,FXLS8471Q_A_FFMT_CFG_XEFE_MASK  },
    {FXLS8471Q_A_FFMT_CFG,FXLS8471Q_A_FFMT_CFG_YEFE_ENABLED   ,FXLS8471Q_A_FFMT_CFG_YEFE_MASK  },
    {FXLS8471Q_A_FFMT_CFG,FXLS8471Q_A_FFMT_CFG_ZEFE_ENABLED   ,FXLS8471Q_A_FFMT_CFG_ZEFE_MASK  },
    {FXLS8471Q_A_FFMT_THS,3,FXLS8471Q_A_FFMT_THS_THS_MASK},//2
    //{FXLS8471Q_A_FFMT_THS,FXLS8471Q_A_FFMT_THS_DBCNTM_CLR,FXLS8471Q_A_FFMT_THS_THS_MASK},
    {FXLS8471Q_A_FFMT_COUNT,6,0x00},//2

    //Pulse registers
    {FXLS8471Q_PULSE_CFG,21,0x00},
    {FXLS8471Q_PULSE_TMLT,80,0x00},//48
    {FXLS8471Q_PULSE_LTCY,240,0x00},
    {FXLS8471Q_PULSE_THSX,55,0x00},
    {FXLS8471Q_PULSE_THSY,55,0x00},
    {FXLS8471Q_PULSE_THSZ,82,0x00},

    //VECM
    { FXLS8471Q_A_VECM_CNT,15,0x00},
    { FXLS8471Q_A_VECM_THS_LSB,88,0x00},
    { FXLS8471Q_A_VECM_CFG,72,0x00},
    { FXLS8471Q_A_VECM_THS_MSB,1, FXLS8471Q_A_VECM_THS_MSB_A_VECM_DBCNTM_MASK},
    { FXLS8471Q_A_VECM_THS_MSB,27, FXLS8471Q_A_VECM_THS_MSB_A_VECM_THS_MASK },
    __END_WRITE_DATA__};

/*! Prepare the register read list to read the raw accel data from the FXLS8471Q. */
const registerreadlist_t cFxls8471q_Output_Values[] = {
    {.readFrom = FXLS8471Q_OUT_X_MSB, .numBytes = FXLS8471Q_ACCEL_DATA_SIZE}, __END_READ_DATA__};

const registerreadlist_t cFxls8471q_int_src[] = {
    {.readFrom = FXLS8471Q_INT_SOURCE, .numBytes = 1}, __END_READ_DATA__};

const registerreadlist_t cFxls8471q_ffmt_src[] = {
    {.readFrom = FXLS8471Q_A_FFMT_SRC , .numBytes = 1}, __END_READ_DATA__};

const registerreadlist_t cFxls8471q_pl_status[] = {
    {.readFrom = FXLS8471Q_PL_STATUS, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bFxls8471DataReady = false, bFxls8471Ready = false;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* This is the Sensor Data Ready ISR implementation.*/
void fxls8471_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bFxls8471DataReady = true;
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
                if (hostCommand[1] == gStreamID && bFxls8471Ready && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bFxls8471Ready && bStreamingEnabled == true)
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
    uint8_t regdata, data[FXLS8471Q_ACCEL_DATA_SIZE], streamingPacket[STREAMING_HEADER_LEN + FXLS8471_STREAM_DATA_SIZE];
    fxls8471q_spi_sensorhandle_t fxls8471Driver;
    fxls8471q_acceldataUser_t rawData = {.timestamp = 0};

    ARM_DRIVER_SPI *pSPIdriver = &SPI_S_DRIVER;
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

    /*! Initialize FXLS8471 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS8471_INT1, GPIO_DIRECTION_IN, NULL, &fxls8471_int_data_ready_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /*! Initialize the SPI driver. */
    status = pSPIdriver->Initialize(SPI_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the SPI Power mode. */
    status = pSPIdriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the SPI Slave speed. */
    status = pSPIdriver->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0, SPI_S_BAUDRATE);
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

    /*! Initialize FXLS8471 sensor driver. */
    status = FXLS8471Q_SPI_Initialize(&fxls8471Driver, &SPI_S_DRIVER, SPI_S_DEVICE_INDEX, &FXLS8471_SPI_CS,
                                      FXLS8471Q_WHO_AM_I_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE == status)
    {
        /*!  Set the task to be executed while waiting for SPI transactions to complete. */
        FXLS8471Q_SPI_SetIdleTask(&fxls8471Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the FXLS8471 sensor. */
        status = FXLS8471Q_SPI_Configure(&fxls8471Driver, cFxls8471q_Config_Isr);
        if (SENSOR_ERROR_NONE == status)
        {
            bFxls8471Ready = true;
        }
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID = Host_IO_Init(pUartDriver, (void *)fxls8471Driver.pCommDrv, &fxls8471Driver.deviceInfo,
                             &fxls8471Driver.slaveParams, FXLS8471Q_I2C_ADDRESS_SA0_0_SA1_0);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bFxls8471Ready = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, FXLS8471_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED);
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        /* Process packets only if streaming has been enabled by Host and ISR is available.
         * In ISR Mode we do not need to check Data Ready Register.
         * The receipt of interrupt will indicate data is ready. */
        if (false == bStreamingEnabled || false == bFxls8471DataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bFxls8471DataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read new raw sensor data from the FXLS8471. */
        status = FXLS8471Q_SPI_ReadData(&fxls8471Driver, cFxls8471q_Output_Values, data);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            continue;
        }

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)data[0] << 8) | (int16_t)data[1];
        rawData.accel[0] /= 4;
        rawData.accel[1] = ((int16_t)data[2] << 8) | (int16_t)data[3];
        rawData.accel[1] /= 4;
        rawData.accel[2] = ((int16_t)data[4] << 8) | (int16_t)data[5];
        rawData.accel[2] /= 4;

        status = FXLS8471Q_SPI_ReadData(&fxls8471Driver, cFxls8471q_int_src, &regdata);

        // The following condition checks for multiple interrupts occurring at the same time and sends only one out as per occurrence order.
        // Check for Free-fall interrupt
        if((regdata & 0x04) == 0x04)
        {
            rawData.intsrc = 0x04;
        }
        // Check for Vector Magnitude change interrupt
        else if((regdata & 0x02) == 0x02)
        {
            rawData.intsrc = 0x02;
        }
        // Else send other interrupts
        else
        {
            rawData.intsrc = regdata;
        }

        // read FFMT/PL/interrupt source registers to clear flags
        status = FXLS8471Q_SPI_ReadData(&fxls8471Driver, cFxls8471q_int_src, &regdata);
        status = FXLS8471Q_SPI_ReadData(&fxls8471Driver, cFxls8471q_ffmt_src, &regdata);
        status = FXLS8471Q_SPI_ReadData(&fxls8471Driver, cFxls8471q_pl_status, &regdata);

        /* Copy Raw samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, FXLS8471_STREAM_DATA_SIZE);
        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
