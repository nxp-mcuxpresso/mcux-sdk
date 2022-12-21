/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls8962_demo.c
 * @brief The fxls8962_demo.c file implements the ISSDK FXLS8962 sensor
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
#include "fxls8962_drv.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXLS8962_DATA_SIZE 8
#define FXLS8962_STREAM_DATA_SIZE 12
#define FXLS8962_STREAM_SELF_TEST_SIZE 18
/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "FXLS8962 Accelerometer Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"
#define HOST_CMD_RESET    6 /* 6 (Reset Sensor) */
#define HOST_CMD_SELFTEST 7 /* 7 (Self Test Sensor) */

/*! @brief This structure defines the fxls8962 raw data buffer.*/
typedef struct
{
    uint32_t timestamp; /*! The time, this sample was recorded.  */
    int16_t accel[3];   /*!< The accel data */
    uint8_t sdcd;
    int8_t temp;
    int16_t selftest[3];
} fxls8962_acceldataUser_t;

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for Interrupt (non buffered) mode. */
const registerwritelist_t cFxls8962ConfigNormal[] = {
    /* Set Full-scale range as 4G. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_4G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    /* Clear SENS_CONFIG2 */
    {FXLS8962_SENS_CONFIG2, 0x00, 0x00},
    /* Disable Self-Test. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_DISABLED, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    /* Set Wake Mode ODR Rate as 12.5Hz. */
    {FXLS8962_SENS_CONFIG3, FXLS8962_SENS_CONFIG3_WAKE_ODR_12_5HZ, FXLS8962_SENS_CONFIG3_WAKE_ODR_MASK},
    /* Enable Interrupts for Data Ready Events. */
    {FXLS8962_INT_EN, FXLS8962_INT_EN_DRDY_EN_EN, FXLS8962_INT_EN_DRDY_EN_MASK},
    /* Enable Temperature sensor. */
    {FXLS8962_SENS_CONFIG2,FXLS8962_SENS_CONFIG2_ANIC_TEMP_EN,FXLS8962_SENS_CONFIG2_ANIC_TEMP_MASK},
    /* Set Self-Test ODR to 100 Hz. */
    {0x38,0x05,0x00},
    {0x2F,0x38,0x00},
    {0x30,0xD8,0x00},
    {0x33,0xC0,0x00},
    {0x34,0x0F,0x00},
    {0x35,0x40,0x00},
    __END_WRITE_DATA__};

/*! @brief Register settings for Interrupt (non buffered) mode. */
const registerwritelist_t cFxls8962ConfigNormal2[] = {
    /* Disable Self-Test. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_DISABLED, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    /* Set Wake Mode ODR Rate as 12.5Hz. */
    {FXLS8962_SENS_CONFIG3, FXLS8962_SENS_CONFIG3_WAKE_ODR_12_5HZ, FXLS8962_SENS_CONFIG3_WAKE_ODR_MASK},
    /* Enable Interrupts for Data Ready Events. */
    {FXLS8962_INT_EN, FXLS8962_INT_EN_DRDY_EN_EN, FXLS8962_INT_EN_DRDY_EN_MASK},
    /* Enable Temperature sensor. */
    {FXLS8962_SENS_CONFIG2,FXLS8962_SENS_CONFIG2_ANIC_TEMP_EN,FXLS8962_SENS_CONFIG2_ANIC_TEMP_MASK},
    /* Set Self-Test ODR to 100 Hz. */
    {0x38,0x05,0x00},
    __END_WRITE_DATA__};

const registerwritelist_t cFxls896216G[] = {
    /* Disable Self-Test. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_DISABLED, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    /* Set Full-scale range as 16G. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    /* Enable Interrupts for Data Ready Events. */
    {FXLS8962_INT_EN, FXLS8962_INT_EN_DRDY_EN_EN, FXLS8962_INT_EN_DRDY_EN_MASK},
    /* Enable Temperature sensor. */
    {FXLS8962_SENS_CONFIG2,FXLS8962_SENS_CONFIG2_ANIC_TEMP_EN,FXLS8962_SENS_CONFIG2_ANIC_TEMP_MASK},
    /* Set Self-Test ODR to 100 Hz. */
    {0x38,0x05,0x00},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in X Axis (Positive polarity). */
const registerwritelist_t cFxls8962STXP[] = {
    /* Set Self Test Axis. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_EN_X, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_POL_POSITIVE,  FXLS8962_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in X Axis (Negative polarity). */
const registerwritelist_t cFxls8962STXN[] = {
    /* Set Self Test Axis. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_EN_X, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_POL_NEGATIVE, FXLS8962_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Y Axis (Positive polarity). */
const registerwritelist_t cFxls8962STYP[] = {
    /* Set Self Test Axis. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_EN_Y, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_POL_POSITIVE,FXLS8962_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Y Axis (Negative polarity). */
const registerwritelist_t cFxls8962STYN[] = {
    /* Set Self Test Axis. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_EN_Y, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_POL_NEGATIVE, FXLS8962_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Z Axis (Positive polarity). */
const registerwritelist_t cFxls8962STZP[] = {
    /* Set Self Test Axis. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_EN_Z, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_POL_POSITIVE, FXLS8962_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Z Axis (Negative polarity). */
const registerwritelist_t cFxls8962STZN[] = {
    /* Set Self Test Axis. */
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_FSR_16G, FXLS8962_SENS_CONFIG1_FSR_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_EN_Z, FXLS8962_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8962_SENS_CONFIG1, FXLS8962_SENS_CONFIG1_ST_POL_NEGATIVE,  FXLS8962_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Raw Accel Data in Normal Mode. */
const registerreadlist_t cFxls8962OutputNormal[] = {{.readFrom = FXLS8962_INT_STATUS, .numBytes = FXLS8962_DATA_SIZE},
    __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bFxls8962DataReady = false, bFxls8962Ready = false;
uint8_t gStreamID; /* The auto assigned Stream ID. */
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;
uint8_t data[FXLS8962_DATA_SIZE], streamingPacket[STREAMING_HEADER_LEN + FXLS8962_STREAM_DATA_SIZE],streamingPacket1[STREAMING_HEADER_LEN + FXLS8962_STREAM_SELF_TEST_SIZE];
fxls8962_acceldataUser_t rawData = {.timestamp = 0};
fxls8962_i2c_sensorhandle_t fxls8962Driver;
int32_t status, gSystick;
int st_on =0, st_sample=0;
int16_t st_xp,st_yp,st_zp,st_xn,st_yn,st_zn,st_dx,st_dy,st_dy;
float fsr_scale;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* This is the Sensor Data Ready ISR implementation.*/
void fxls8962_int_data_ready_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bFxls8962DataReady = true;
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
                if (hostCommand[1] == gStreamID && bFxls8962Ready && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bFxls8962Ready && bStreamingEnabled == true)
                {
                    pGpioDriver->clr_pin(&GREEN_LED);
                    bStreamingEnabled = false;
                    success = true;
                }
                break;
            case HOST_CMD_RESET:
                if (hostCommand[1] == gStreamID && bFxls8962Ready)
                {
                    do
                    {
                        status =  FXLS8962_I2C_DeInit(&fxls8962Driver);
                        if (SENSOR_ERROR_NONE != status)
                            break;
                        status = FXLS8962_I2C_Initialize(&fxls8962Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLS8962_I2C_ADDR,
                                FXLS8962_WHOAMI_VALUE);

                        if (SENSOR_ERROR_NONE != status)
                            break;
                        status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962ConfigNormal2);
                        if (SENSOR_ERROR_NONE != status)
                            break;
                        success = true;
                    } while(0);
                }
                break;
            case HOST_CMD_SELFTEST:
                st_on=1;
                st_sample=98;
                rawData.selftest[0]=0;
                rawData.selftest[1]=0;
                rawData.selftest[2]=0;
                /* Copy Raw samples to Streaming Buffer. */
                memcpy(streamingPacket1 + STREAMING_HEADER_LEN, &rawData, FXLS8962_STREAM_SELF_TEST_SIZE);
                /* Send streaming packet to Host. */
                Host_IO_Send(streamingPacket1, sizeof(streamingPacket1), HOST_FORMAT_HDLC);
                success = true;
                break;
            default:
                break;
        }
        *hostMsgSize = 0; /* Zero payload in response. */
    }

    if ((tag == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_W_REG_TAG)) && (*hostMsgSize >= 3))
    {
        /* If ODR set from GUI > 100 Hz set ODR to 100 Hz */
        if(hostCommand[1]==0x17)
        {
            if(((hostCommand[2] & 0x0F)<5))
            {
                hostCommand[2]= ((hostCommand[2]&0xF0) | 0x05);
            }
            if((((hostCommand[2] & 0xF0)>>4)<5))
            {
                hostCommand[2]= ((hostCommand[2]&0x0F) | 0x50);
            }
        }

        /* Select the Sensitivity factor according to the FSR selected from the GUI*/
        if(hostCommand[1]==0x15)
        {
            if(((hostCommand[2] & 0x06)==0x06))
            {
                fsr_scale=7.81;
            }
            if(((hostCommand[2] & 0x06)==0x04))
            {
                fsr_scale=3.91;
            }
            if(((hostCommand[2] & 0x06)==0x02))
            {
                fsr_scale=1.95;
            }
            if(((hostCommand[2] & 0x06)==0x00))
            {
                fsr_scale=0.98;
            }
        }

        /* If Self-Test ODR set from GUI > 100 Hz set ODR to 100 Hz */
        if(hostCommand[1]==0x38 && hostCommand[2]<5)
        {
            hostCommand[2]=0x05;
        }
        if(hostCommand[1]==0x90)
        {
            st_on=1;
            st_sample=98;
        }
    }
    if ((tag == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_R_REG_TAG)) &&
        (*hostMsgSize == 3))
    {
        /* Select the Sensitivity factor according to the FSR selected from the GUI*/
        if(hostCommand[1]==0x15)
        {
            if((*hostResponse & 0x06)==0x06)
            {
                fsr_scale=7.81;
            }
            if((*hostResponse & 0x06)==0x04)
            {
                fsr_scale=3.91;
            }
            if((*hostResponse & 0x06)==0x02)
            {
                fsr_scale=1.95;
            }
            if((*hostResponse  & 0x06)==0x00)
            {
                fsr_scale=0.98;
            }
        }
    }
    return success;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int flag=0;
    int32_t status;
    uint8_t data[FXLS8962_DATA_SIZE], streamingPacket[STREAMING_HEADER_LEN + FXLS8962_STREAM_DATA_SIZE];

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

    /*! Initialize FXLS8962 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS8962_INT1, GPIO_DIRECTION_IN, NULL, &fxls8962_int_data_ready_callback, NULL);

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

    /*! Initialize FXLS8962 sensor driver. */
    status = FXLS8962_I2C_Initialize(&fxls8962Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLS8962_I2C_ADDR,
                                     FXLS8962_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE == status)
    {
        /*!  Set the task to be executed while waiting for I2C transactions to complete. */
        FXLS8962_I2C_SetIdleTask(&fxls8962Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

        /*! Configure the FXLS8962 sensor. */
        status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962ConfigNormal);
        if (SENSOR_ERROR_NONE == status)
        {
            bFxls8962Ready = true;
        }
    }

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID =
        Host_IO_Init(pUartDriver, (void *)fxls8962Driver.pCommDrv, &fxls8962Driver.deviceInfo, NULL, FXLS8962_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bFxls8962Ready = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, FXLS8962_STREAM_DATA_SIZE);
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket1, FXLS8962_STREAM_SELF_TEST_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED);
    }

    rawData.selftest[0]=0;
    rawData.selftest[1]=0;
    rawData.selftest[2]=0;

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        /* If Self-Test is selected*/
        if(st_on)
        {   /* Call UART Non-Blocking Receive. */
            Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);
            switch(st_sample)
            {
                case 98:
                    status =FXLS8962_I2C_Configure(&fxls8962Driver, cFxls896216G); /* Configure 16G mode*/
                    break;
                case 100:
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962STXP);/* Enable Self-Test +X Axis*/
                    break;
                case 200:
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962STXN);/* Enable Self-Test -X Axis*/
                    break;
                case 300:
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962STYP);/* Enable Self-Test +Y Axis*/
                    break;
                case 400:
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962STYN);/* Enable Self-Test -Y Axis*/
                    break;
                case 500:
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962STZP);/* Enable Self-Test +Z Axis*/
                    break;
                case 600:
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls8962STZN);/* Enable Self-Test -Z Axis*/
                    break;
            }
            /* Process packets only if streaming has been enabled by Host and ISR is available.
             * In ISR Mode we do not need to check Data Ready Register.
             * The receipt of interrupt will indicate data is ready. */
            if (false == bStreamingEnabled || false == bFxls8962DataReady)
            {
                SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
                continue;
            }
            else
            { /*! Clear the data ready flag, it will be set again by the ISR. */
                bFxls8962DataReady = false;
                pGpioDriver->toggle_pin(&GREEN_LED);
            }

            /* Place device in Standby mode after acquiring close to 100 samples */
            switch(st_sample)
            {
                case 99:
                    Register_I2C_Write(&I2C_S_DRIVER,&(fxls8962Driver.deviceInfo),0x18, 0x15,0x00,0x00,0x00);
                    break;
                case 199:
                    Register_I2C_Write(&I2C_S_DRIVER,&(fxls8962Driver.deviceInfo),0x18, 0x15,0x00,0x00,0x00);
                    break;
                case 299:
                    Register_I2C_Write(&I2C_S_DRIVER,&(fxls8962Driver.deviceInfo),0x18, 0x15,0x00,0x00,0x00);
                    break;
                case 399:
                    Register_I2C_Write(&I2C_S_DRIVER,&(fxls8962Driver.deviceInfo),0x18, 0x15,0x00,0x00,0x00);
                    break;
                case 499:
                    Register_I2C_Write(&I2C_S_DRIVER,&(fxls8962Driver.deviceInfo),0x18, 0x15,0x00,0x00,0x00);
                    break;
                case 599:
                    Register_I2C_Write(&I2C_S_DRIVER,&(fxls8962Driver.deviceInfo),0x18, 0x15,0x00,0x00,0x00);
                    break;
            }
            /*! Read new raw sensor data from the FXLS8962. */
            status = FXLS8962_I2C_ReadData(&fxls8962Driver, cFxls8962OutputNormal, data);
            if (ARM_DRIVER_OK != status)
            { /* Loop, if sample read failed. */
                continue;
            }

            /* Update timestamp from Systick framework. */
            rawData.timestamp +=BOARD_SystickElapsedTime_us(&gSystick);

            /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
            rawData.accel[0] = (int16_t)(((int16_t)(((int16_t)data[3] << 8) | data[2]))); /*7.81 is the scale factor for 16 G mode */
            rawData.accel[1] = (int16_t)(((int16_t)(((int16_t)data[5] << 8) | data[4])));
            rawData.accel[2] = (int16_t)(((int16_t)(((int16_t)data[7] << 8) | data[6])));

            switch(st_sample)
            {
                case 100:
                    st_xp = (int16_t)(((int16_t)data[3] << 8) | data[2]);
                    st_sample=st_sample+1;
                    break;
                case 200:
                    st_xn = (int16_t)(((int16_t)data[3] << 8) | data[2]);
                    st_sample=st_sample+1;
                    break;
                case 300:
                    st_yp = (int16_t)(((int16_t)data[5] << 8) | data[4]);
                    st_sample=st_sample+1;
                    break;
                case 400:
                    st_yn = (int16_t)(((int16_t)data[5] << 8) | data[4]);
                    st_sample=st_sample+1;
                    break;
                case 500:
                    st_zp = (int16_t)(((int16_t)data[7] << 8) | data[6]);
                    st_sample=st_sample+1;
                    break;
                case 600:
                    st_zn = (int16_t)(((int16_t)data[7] << 8) | data[6]);
                    st_sample=st_sample+1;
                    break;
                case 700: /* Calculate Self-Test output */
                    rawData.selftest[0] =(st_xp-st_xn)/2;
                    rawData.selftest[1] =(st_yp-st_yn)/2;
                    rawData.selftest[2] =(st_zp-st_zn)/2;
                    st_on=0;
                    st_sample=98;
                    flag=1;
                    status = FXLS8962_I2C_Configure(&fxls8962Driver, cFxls896216G);
                    break;
                default:
                    st_sample=st_sample+1;
                    break;
            }

            rawData.temp = data[1]+25;
            rawData.sdcd = (data[0] & 0x10)>>4;

            /* Copy Raw samples to Streaming Buffer. */
            memcpy(streamingPacket1 + STREAMING_HEADER_LEN, &rawData, FXLS8962_STREAM_SELF_TEST_SIZE);
            Host_IO_Send(streamingPacket1, sizeof(streamingPacket1), HOST_FORMAT_HDLC);
        }
        else
        {
            /* Call UART Non-Blocking Receive. */
            Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

            /* Process packets only if streaming has been enabled by Host and ISR is available.
             * In ISR Mode we do not need to check Data Ready Register.
             * The receipt of interrupt will indicate data is ready. */
            if (false == bStreamingEnabled || false == bFxls8962DataReady)
            {
                SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
                continue;
            }
            else
            { /*! Clear the data ready flag, it will be set again by the ISR. */
                bFxls8962DataReady = false;
                pGpioDriver->toggle_pin(&GREEN_LED);
            }

            /*! Read new raw sensor data from the FXLS8962. */
            status=  FXLS8962_I2C_ReadData(&fxls8962Driver, cFxls8962OutputNormal, data);

            if (ARM_DRIVER_OK != status)
            { /* Loop, if sample read failed. */
                continue;
            }

            /* Update timestamp from Systick framework. */
            rawData.timestamp +=BOARD_SystickElapsedTime_us(&gSystick);

            /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
            rawData.accel[0] = (int16_t)(((int16_t)(((int16_t)data[3] << 8) | data[2])));
            rawData.accel[1] = (int16_t)(((int16_t)(((int16_t)data[5] << 8) | data[4])));
            rawData.accel[2] = (int16_t)(((int16_t)(((int16_t)data[7] << 8) | data[6])));

            rawData.temp = data[1]+25;
            rawData.sdcd = (data[0] & 0x10)>>4;

            /* Copy Raw samples to Streaming Buffer. */
            memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, FXLS8962_STREAM_DATA_SIZE);
            /* Send streaming packet to Host. */
            Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);

            if(flag==1) /*Reset Self-Test Values */
            {
                rawData.selftest[0]=0;
                rawData.selftest[1]=0;
                rawData.selftest[2]=0;
                flag=0;
            }
        }
    }
}
