/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file: fxlc95000_flash_demo.c
 * @brief The fxlc95000_flash_demo.c file implements the ISSDK FXLC95000L sensor driver
 *          example demonstration for FLASH programming and Streaming for I2C Mode using Host I/O.
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
#include "host_io_uart.h"
#include "systick_utils.h"
#include "fxlc95000_drv.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define fxlc95000_odrCallback LPTMR0_IRQHandler /* Timer timeout Callback. */
#define SAMPLING_RATE_ms 100                    /* Timeout for the ODR Timer in ms. */
#define FXLC95000_SAMPLE_SIZE 10                /* 4-Byte timestamp and 2-Byte X,Y,Z Data each. */

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "FXLC95000 Accelerometer Demo"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! Create commands for setting FXLC95000L desired configuration. */
const uint8_t cFxlc95000_SetODR_Cmd[] = {FXLC95000_SET_ODR_CMD_HDR, /* ODR equal to Sampling Rate. */
                                         FXLC95000_SST_ODR_PAYLOAD(SAMPLING_RATE_ms * 1000)};
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

/*! Prepare the register write list with Flash Preprocess Commands. */
const registercommandlist_t cFxlc95000FlashPreprocess[] = {
    {UnprotectFlash, 0, sizeof(UnprotectFlash)},           /* Unprotect Flash Banks to enable Writing. */
    {EraseMainFlashArray, 0, sizeof(EraseMainFlashArray)}, /* Erase Flash completely before writing new Data. */
    __END_WRITE_CMD__                                      /* Ref. Section 16.5 of FXLC95000CLHWRM. */
};

/*! Prepare the register write list with Flash Postprocess Commands. */
const registercommandlist_t cFxlc95000FlashPostprocess[] = {
    {ProtectFlash, 0, sizeof(ProtectFlash)}, /* Protect Flash Banks after Writing to enable booting to Flash. */
    __END_WRITE_CMD__                        /* Ref. Section 16.5 of FXLC95000CLHWRM. */
};

/*! Prepare the register read list to read the Timestamp and Accel data from FXLC95000. */
const registerreadlist_t cFxlc95000ReadSample[] = {
    {.readFrom = FXLC95000_SAMPLE_OFFSET, .numBytes = FXLC95000_SAMPLE_SIZE}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bStreamingEnabled = false, bFxlc95000DataReady = false, bFxlc95000Ready = false, bFxlc95000Boot = false,
              bFxlc95000Flashing = false;
fxlc95000_i2c_sensorhandle_t fxlc95000Driver = /* Sensor Handle. */
    {.deviceInfo = {.deviceInstance = I2C_S_DEVICE_INDEX, .idleFunction = NULL}};
uint8_t gStreamID; /* The auto assigned Stream ID. */
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* LPTMR based ODR Callback function. */
void fxlc95000_odrCallback(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    bFxlc95000DataReady = true;
}

/* Sequence of commands for booting up FXLC95000 to Flash and enabling reading of samples. */
int fxlc95000_enSensor(fxlc95000_i2c_sensorhandle_t *pSensorHandle)
{
    int32_t status;

    /*! Initialize the FXLC95000 sensor driver. */
    status = FXLC95000_I2C_Initialize(pSensorHandle, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLC95000_I2C_ADDR,
                                      FXLC95000_BUILD_ID);
    if (SENSOR_ERROR_NONE != status)
    {
        return -1;
    }

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXLC95000_I2C_SetIdleTask(pSensorHandle, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the FXLC95000 with MBox settings. */
    status = FXLC95000_I2C_CommandResponse(pSensorHandle, cFxlc95000ConfigMBox, NULL, NULL);
    if (SENSOR_ERROR_NONE != status)
    {
        return -1;
    }
    /*! Configure the FXLC95000 with Sampling settings. */
    status = FXLC95000_I2C_CommandResponse(pSensorHandle, cFxlc95000ConfigSensor, NULL, NULL);
    if (SENSOR_ERROR_NONE != status)
    {
        return -1;
    }

    LPTMR_StartTimer(LPTMR0);
    bFxlc95000Boot = true;
    pGpioDriver->set_pin(&RED_LED);   /* Clear RED LED to indicate sensor boot process is complete. */
    pGpioDriver->clr_pin(&GREEN_LED); /* Set GREEN LED to indicate application is ready. */
    return 0;
}

/* Handler for Flash Write, Device Info and Streaming Control Commands. */
bool process_host_command(
    uint8_t tag, uint8_t *hostCommand, uint8_t *hostResponse, size_t *hostMsgSize, size_t respBufferSize)
{
    static uint8_t toggle_led = 0;
    bool success = false;
    size_t rxMsgSize = *hostMsgSize; /* Capture Rx Command Size. */
    *hostMsgSize = 0;                /* Set Tx Response payload size to '0' as default and update if required. */

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

        if (false == bFxlc95000Boot) /* Bringup FXLC95000 if not already done. */
        {
            if (fxlc95000_enSensor(&fxlc95000Driver))
            {
                bFxlc95000Boot = false;
            }
        }

        return true;
    }

    /* If it is Host sending Streaming Commands, take necessary actions. */
    if ((tag == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_W_CFG_TAG)) &&
        (rxMsgSize == HOST_MSG_CMD_ACT_OFFSET - HOST_MSG_LEN_LSB_OFFSET))
    {                           /* Byte 1 : Payload - Operation Code (Start/Stop Operation Code)
                                 * Byte 2 : Payload - Stream ID (Target Stream for carrying out operation) */
        switch (hostCommand[0]) /* Execute desired operation (Start/Stop) on the requested Stream. */
        {
            case HOST_CMD_START:
                if (hostCommand[1] == gStreamID && bStreamingEnabled == false)
                {
                    if (false == bFxlc95000Boot) /* Bringup FXLC95000 if not already done. */
                    {
                        if (fxlc95000_enSensor(&fxlc95000Driver))
                        {
                            break;
                        }
                    }
                    bStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bStreamingEnabled == true)
                {
                    pGpioDriver->clr_pin(&GREEN_LED);
                    bStreamingEnabled = false;
                    success = true;
                }
                break;
            default:
                break;
        }
    }

    /* If it is Host sending Flash Commands, take necessary actions. */
    if ((tag == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_W_CFG_TAG)) &&
        (rxMsgSize >= HOST_MSG_CMD_ACT_OFFSET - HOST_MSG_LEN_LSB_OFFSET))
    {                           /* Byte 1  : Payload - Operation Code (Start/Bytes/Stop Operation Code)
                                 * Byte 2  : Payload - Slave ID (The Sensor's I2C Slave Address)
                                 * Byte 3+ : Payload - (Only for Flash Bytes) The Flash Payload to be Written. */
        switch (hostCommand[0]) /* Execute desired operation on the requested Sensor. */
        {
            case HOST_CMD_FLASH_START:
                /* Confirm Flashing is not active and Sensor is in ROM Mode. */
                if ((hostCommand[1] == FXLC95000_I2C_ADDR && false == bFxlc95000Flashing) &&
                    (0 == FXLC95000_I2C_CheckRomMode(&I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLC95000_I2C_ADDR)))
                { /*! Write Flash Preprocess Commands. */
                    if (SENSOR_ERROR_NONE == FXLC95000_I2C_FlashCommands(&I2C_S_DRIVER, I2C_S_DEVICE_INDEX,
                                                                         FXLC95000_I2C_ADDR, cFxlc95000FlashPreprocess))
                    {
                        bFxlc95000Flashing = true;
                        success = true;
                    }
                    pGpioDriver->set_pin(&RED_LED); /* Indicate Flash Processing is active. */
                }
                break;
            case HOST_CMD_FLASH_BYTES:
                /* Confirm Flashing is active. */
                if ((hostCommand[1] == FXLC95000_I2C_ADDR) && (true == bFxlc95000Flashing))
                { /*! Write Flash Data Bytes. */
                    if (SENSOR_ERROR_NONE == FXLC95000_I2C_FlashPayload(&I2C_S_DRIVER, I2C_S_DEVICE_INDEX,
                                                                        FXLC95000_I2C_ADDR, hostCommand + 2,
                                                                        rxMsgSize - 2))
                    {
                        success = true;
                    }
                    if (toggle_led++ % 32 == 0 ? true : false)
                    {
                        pGpioDriver->toggle_pin(&RED_LED); /* Indicate Flash Processing is active. */
                    }
                }
                break;
            case HOST_CMD_FLASH_STOP:
                /* Confirm Flashing is active. */
                if ((hostCommand[1] == FXLC95000_I2C_ADDR) && (true == bFxlc95000Flashing))
                { /*! Write Flash Postprocess Commands. */
                    if (SENSOR_ERROR_NONE == FXLC95000_I2C_FlashCommands(&I2C_S_DRIVER, I2C_S_DEVICE_INDEX,
                                                                         FXLC95000_I2C_ADDR,
                                                                         cFxlc95000FlashPostprocess))
                    {
                        bFxlc95000Flashing = false;
                        success = true;
                    }
                    pGpioDriver->clr_pin(&RED_LED); /* Indicate Flash Processing is complete. */
                }
                break;
            default:
                break;
        }
    }

    return success;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t streamingPacket[STREAMING_HEADER_LEN + FXLC95000_SAMPLE_SIZE];
    lptmr_config_t lptmrConfig;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER;
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

    /* Initialize ODR Timer. */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    LPTMR_SetTimerPeriod(LPTMR0, MSEC_TO_COUNT(SAMPLING_RATE_ms, CLOCK_GetFreq(kCLOCK_LpoClk)));
    EnableIRQ(LPTMR0_IRQn);

    /*! Initialize RED LED pin used by FRDM board */
    pGpioDriver->pin_init(&RED_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGpioDriver->set_pin(&RED_LED);

    /*! Initialize GREEN LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGpioDriver->set_pin(&GREEN_LED);

    /*! Initialize the I2C driver. */
    status = I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = I2Cdrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
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

    /*! Register with Host I/O Service and get a Stream ID. */
    gStreamID = Host_IO_Init(pUartDriver, (void *)&I2C_S_DRIVER, &fxlc95000Driver.deviceInfo, NULL, FXLC95000_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        return -1;
    }

    /*! Populate streaming header. */
    Host_IO_Add_ISO_Header(gStreamID, streamingPacket, FXLC95000_SAMPLE_SIZE);
    pGpioDriver->clr_pin(&RED_LED); /* Set the RED LED to indicate that Boot proccess has not been done.*/

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive to check for Commands from Host. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        if (false == bStreamingEnabled || false == bFxlc95000DataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bFxlc95000DataReady = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Read raw sensor data from the FXLC95000. */
        status = FXLC95000_I2C_CommandResponse(&fxlc95000Driver, NULL, cFxlc95000ReadSample,
                                               streamingPacket + STREAMING_HEADER_LEN);
        if (ARM_DRIVER_OK != status)
        { /* Loop, if sample read failed. */
            continue;
        }

        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
