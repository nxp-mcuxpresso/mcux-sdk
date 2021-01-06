/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_vref.h"
#include "fsl_adc16.h"

#include "fsl_device_registers.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_VREF_BASE           VREF
#define DEMO_ADC16_BASE          ADC1
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL  18U /* ADC1 channel 18, VREF_OUT. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void ADC_Configuration(void);
static void ADC_StartConversation(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
adc16_channel_config_t g_adc16ChnConfigStruct;
const uint32_t g_Adc16_12bitFullRange = 4096U;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void ADC_Configuration(void)
{
    adc16_config_t adc16ConfigStruct;

    /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
#ifdef BOARD_ADC_USE_ALT_VREF
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(DEMO_ADC16_BASE, &adc16ConfigStruct);

    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false); /* Make sure the software trigger is used. */
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASE))
    {
        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    /* Set ADC16 channel conversion configuration structure */
    /* Select USER channel */
    g_adc16ChnConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
    /* Generate a interrupt request once the conversion is completed */
    g_adc16ChnConfigStruct.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    g_adc16ChnConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
    ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &g_adc16ChnConfigStruct);
}

static void ADC_StartConversation()
{
    uint32_t i           = 0;
    uint32_t adcConValue = 0;
    /* Configure the channel group 0 conversion */
    ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &g_adc16ChnConfigStruct);
    /* Wait until conversion is completed */
    while (0U ==
           (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
    {
    }

    /* Get the conversion result through mean filtering. */
    for (i = 0; i < 128; i++)
    {
        adcConValue += ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);
    }
    adcConValue >>= 7U;

    PRINTF("ADC value: %d\r\n", adcConValue);
}

/*!
 * @brief Main function
 */
int main(void)
{
    vref_config_t vrefConfig;
    uint32_t trimVal = 0;
    uint32_t i       = 0;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    PRINTF("\r\nVREF example\r\n");

    /*
     * vrefConfig.bufferMode = kVREF_ModeHighPowerBuffer;
     * vrefConfig.enableExternalVoltRef = false;
     * vrefConfig.enableLowRef = false;
     */
    VREF_GetDefaultConfig(&vrefConfig);
    /* Initialize the VREF mode. */
    VREF_Init(DEMO_VREF_BASE, &vrefConfig);

    ADC_Configuration();

    PRINTF("ADC Full Range: %d\r\n", g_Adc16_12bitFullRange);
    PRINTF("Defalut (Factory) trim value is :%d\r\n", VREF_GetTrimVal(DEMO_VREF_BASE));
    ADC_StartConversation();

    /* Change the voltage by 2mV each loop. */
    for (trimVal = 0U; trimVal < 0x3FU; trimVal += 4U)
    {
        VREF_SetTrimVal(DEMO_VREF_BASE, trimVal);
        /* Waiting some times */
        for (i = 0; i < 0xFFFFF; i++)
        {
            __NOP();
        }
        PRINTF("Use trim value: %d\r\n", trimVal);
        ADC_StartConversation();
    }

    while (1)
    {
    }
}
