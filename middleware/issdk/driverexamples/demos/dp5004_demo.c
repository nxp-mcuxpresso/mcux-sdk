/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file dp5004_demo.c
 * @brief The dp5004_demo.c file implements the ISSDK MPXVDP5004 analog sensor
 *        driver demo demonstration in interrupt mode with FRDM-KE15Z.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "board.h"
#include "pin_mux.h"
#include "fsl_lptmr.h"
#include "fsl_adc12.h"
#include "clock_config.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_USART.h"

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "host_io_uart.h"
#include "systick_utils.h"
#include "auto_detection_service.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* Timer timeout Callback. */
#define dp5004_odr_callback PWT_LPTMR0_IRQHandler
/* ADC completion Callback. */
#define adc12_irq_callback ADC0_IRQHandler

/* The desired ODR in milli seconds for the Pressure output */
#define MPXV5004DP_ODR_ms 100U
/* The size of Streaming Data in Host Message. */
#define MPXV5004DP_STREAM_DATA_SIZE 6U

/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "Analog Pressure Sensor Demo (MPXV5004DP)"
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

//-----------------------------------------------------------------------
// Data Types
//-----------------------------------------------------------------------
/*! @brief This structure defines the mpxv5004dp data buffer.*/
typedef struct
{
    uint32_t timestamp; /*!< Time stamp value in micro-seconds. */
    uint16_t pressure;  /*!< Sensor pressure output: unsigned 16-bits. */
} dp5004_pressuredata_t;

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool bAdc12ConversionCompletedFlag = false, bStreamingEnabled = false, bDp5004Ready = false;
adc12_channel_config_t gAdcChannelConfigStruct;
volatile uint32_t gAdcConversionValue;
uint8_t gStreamID; /* The auto assigned Stream ID. */
int32_t gSystick;
GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/* LPTMR based ODR control Timer Callback function. */
void dp5004_odr_callback(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    /* Trigger ADC Conversion */
    ADC12_SetChannelConfig(ADC0, MPXVDP5004_ADC12_CHANNEL_GROUP, &gAdcChannelConfigStruct);
}

/* ADC12 based voltage conversion completion IRQ Callback function. */
void adc12_irq_callback(void)
{
    /* Read conversion result to clear the conversion completed flag. */
    gAdcConversionValue = ADC12_GetChannelConversionValue(ADC0, MPXVDP5004_ADC12_CHANNEL_GROUP);
    bAdc12ConversionCompletedFlag = true;
}

void KE15Z_LPTMR0_ADC0_Initialize(void)
{
    lptmr_config_t lptmrConfig;
    adc12_config_t adc12ConfigStruct;

    /* Configure ODR Timer. */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);
    LPTMR_SetTimerPeriod(LPTMR0, MSEC_TO_COUNT(MPXV5004DP_ODR_ms, CLOCK_GetFreq(kCLOCK_LpoClk)));
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    EnableIRQ(PWT_LPTMR0_IRQn);

    /* Configure ADC. */
    /* Set ADC12's clock source to be Slow IRC async clock. */
    CLOCK_SetIpSrc(kCLOCK_Adc0, kCLOCK_IpSrcSircAsync);
    EnableIRQ(ADC0_IRQn);
    ADC12_GetDefaultConfig(&adc12ConfigStruct);
    adc12ConfigStruct.clockSource = kADC12_ClockSourceAlt0;
    adc12ConfigStruct.resolution = kADC12_Resolution12Bit;
    ADC12_Init(ADC0, &adc12ConfigStruct);
    /* Set to software trigger mode. */
    ADC12_EnableHardwareTrigger(ADC0, false);
    /* Calibrate ADC. */
    if (kStatus_Success == ADC12_DoAutoCalibration(ADC0))
    {
        bDp5004Ready = true;
    }
    gAdcChannelConfigStruct.channelNumber = MPXVDP5004_ADC12_CHANNEL;
    /* Enable the interrupt. */
    gAdcChannelConfigStruct.enableInterruptOnConversionCompleted = true;
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
                if (hostCommand[1] == gStreamID && bDp5004Ready && bStreamingEnabled == false)
                {
                    BOARD_SystickStart(&gSystick);
                    bStreamingEnabled = true;
                    LPTMR_StartTimer(LPTMR0);
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gStreamID && bDp5004Ready && bStreamingEnabled == true)
                {
                    pGpioDriver->clr_pin(&GREEN_LED);
                    bStreamingEnabled = false;
                    LPTMR_StopTimer(LPTMR0);
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
    dp5004_pressuredata_t rawData = {.timestamp = 0};
    uint8_t streamingPacket[STREAMING_HEADER_LEN + MPXV5004DP_STREAM_DATA_SIZE];

    ARM_DRIVER_USART *pUartDriver = &HOST_S_DRIVER;

    BOARD_BootClockRUN();
    BOARD_SystickEnable();

    /* Create the Short Application Name String for ADS. */
    sprintf(embAppName, "%s:%s", APPLICATION_NAME, APPLICATION_VERSION);

    /* Run ADS. */
    BOARD_RunADS(embAppName, boardString, shieldString, ADS_MAX_STRING_LENGTH);

    /* Create the Full Application Name String for Device Info Response. */
    sprintf(embAppName, "%s:%s:%s", SHIELD_NAME, APPLICATION_NAME, APPLICATION_VERSION);

    /*! Initialize GREEN LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

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

    /* Initialize LPTMR and ADC framework */
    KE15Z_LPTMR0_ADC0_Initialize();

    /*! Initialize streaming and assign a Stream ID. */
    gStreamID = Host_IO_Init(pUartDriver, NULL, NULL, NULL, 0);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gStreamID)
    {
        bDp5004Ready = false;
    }
    else
    {
        /*! Populate streaming header. */
        Host_IO_Add_ISO_Header(gStreamID, streamingPacket, MPXV5004DP_STREAM_DATA_SIZE);
        pGpioDriver->clr_pin(&GREEN_LED); /* Set LED to indicate application is ready. */
    }

    for (;;) /* Forever loop */
    {        /* Call UART Non-Blocking Receive. */
        Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

        if (false == bAdc12ConversionCompletedFlag)
        {
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        {
            bAdc12ConversionCompletedFlag = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /* Update timestamp from Systick framework. */
        rawData.timestamp += BOARD_SystickElapsedTime_us(&gSystick);

        rawData.pressure = (uint16_t)MPXV5004DP_PRESSURE_FROM_ADC_VALUE(gAdcConversionValue);

        /* Copy samples to Streaming Buffer. */
        memcpy(streamingPacket + STREAMING_HEADER_LEN, &rawData, MPXV5004DP_STREAM_DATA_SIZE);

        /* Send streaming packet to Host. */
        Host_IO_Send(streamingPacket, sizeof(streamingPacket), HOST_FORMAT_HDLC);
    }
}
