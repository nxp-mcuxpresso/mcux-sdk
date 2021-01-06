/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_adc.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC_BASE          ADC1
#define DEMO_ADC_IRQn          ADC1_IRQn
#define DEMO_ADC_USER_CHANNEL  0U
#define DEMO_ADC_CHANNEL_GROUP 0U
#define EXAMPLE_ADC_IRQHandler ADC1_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_AdcConversionDoneFlag;
volatile uint32_t g_AdcConversionValue;
volatile uint32_t g_AdcInterruptCounter;
const uint32_t g_Adc_12bitFullRange = 4096U;

/*******************************************************************************
 * Code
 ******************************************************************************/

void EXAMPLE_ADC_IRQHandler(void)
{
    g_AdcConversionDoneFlag = true;
    /* Read conversion result to clear the conversion completed flag. */
    g_AdcConversionValue = ADC_GetChannelConversionValue(DEMO_ADC_BASE, DEMO_ADC_CHANNEL_GROUP);
    g_AdcInterruptCounter++;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    adc_config_t adcConfigStrcut;
    adc_channel_config_t adcChannelConfigStruct;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_ADC_IRQn);

    PRINTF("\r\nADC interrupt Example.\r\n");

    /*
     *  config->enableAsynchronousClockOutput = true;
     *  config->enableOverWrite =               false;
     *  config->enableContinuousConversion =    false;
     *  config->enableHighSpeed =               false;
     *  config->enableLowPower =                false;
     *  config->enableLongSample =              false;
     *  config->referenceVoltageSource =        kADC_ReferenceVoltageSourceVref;
     *  config->samplePeriodMode =              kADC_SamplePeriod2or12Clocks;
     *  config->clockSource =                   kADC_ClockSourceAD;
     *  config->clockDriver =                   kADC_ClockDriver1;
     *  config->resolution =                    kADC_Resolution12Bit;
     */
    ADC_GetDefaultConfig(&adcConfigStrcut);
    ADC_Init(DEMO_ADC_BASE, &adcConfigStrcut);
#if !(defined(FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE) && FSL_FEATURE_ADC_SUPPORT_HARDWARE_TRIGGER_REMOVE)
    ADC_EnableHardwareTrigger(DEMO_ADC_BASE, false);
#endif

    /* Do auto hardware calibration. */
    if (kStatus_Success == ADC_DoAutoCalibration(DEMO_ADC_BASE))
    {
        PRINTF("ADC_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC_DoAutoCalibration() Failed.\r\n");
    }

    /* Configure the user channel and interrupt. */
    adcChannelConfigStruct.channelNumber                        = DEMO_ADC_USER_CHANNEL;
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = true;
    g_AdcInterruptCounter                                       = 0U; /* Clear the interrupt counter. */

    PRINTF("ADC Full Range: %d\r\n", g_Adc_12bitFullRange);
    while (1)
    {
        PRINTF("Press any key to get user channel's ADC value.\r\n");
        GETCHAR();
        g_AdcConversionDoneFlag = false;
        /*
            When in software trigger mode, each conversion would be launched once calling the "ADC16_ChannelConfigure()"
            function, which works like writing a conversion command and executing it. For another channel's conversion,
            just to change the "channelNumber" field in channel configuration structure, and call the function
            "ADC_ChannelConfigure()"" again.
            Also, the "enableInterruptOnConversionCompleted" inside the channel configuration structure is a parameter
           for
            the conversion command. It takes affect just for the current conversion. If the interrupt is still required
            for the following conversion, it is necessary to assert the "enableInterruptOnConversionCompleted" every
           time
            for each command.
           */
        ADC_SetChannelConfig(DEMO_ADC_BASE, DEMO_ADC_CHANNEL_GROUP, &adcChannelConfigStruct);
        while (g_AdcConversionDoneFlag == false)
        {
        }
        PRINTF("ADC Value: %d\r\n", g_AdcConversionValue);
        PRINTF("ADC Interrupt Counter: %d\r\n", g_AdcInterruptCounter);
    }
}
