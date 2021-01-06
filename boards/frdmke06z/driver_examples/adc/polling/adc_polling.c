/*
 * Copyright 2017-2018 NXP
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
#define DEMO_ADC_BASE         ADC
#define DEMO_ADC_USER_CHANNEL 0U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const uint32_t g_Adc_8bitFullRange = 256U;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    adc_config_t adcConfigStrcut;
    adc_channel_config_t adcChannelConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nADC polling Example.\r\n");

    /*
     * config->referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
     * config->enableLowPower = false;
     * config->enableLongSampleTime = false;
     * config->clockDivider = kADC_ClockDivider1;
     * config->ResolutionMode = kADC_Resolution8BitMode;
     * config->clockSource = kADC_ClockSourceAlt0;
     */
    ADC_GetDefaultConfig(&adcConfigStrcut);
    ADC_Init(DEMO_ADC_BASE, &adcConfigStrcut);
    ADC_EnableHardwareTrigger(DEMO_ADC_BASE, false);

    /* Configure the user channel and interrupt. */
    adcChannelConfigStruct.channelNumber                        = DEMO_ADC_USER_CHANNEL;
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;
    adcChannelConfigStruct.enableContinuousConversion           = false;

    /* Enable the releated analog pins. */
    ADC_EnableAnalogInput(DEMO_ADC_BASE, 1U << DEMO_ADC_USER_CHANNEL, true);

    PRINTF("ADC Full Range: %d\r\n", g_Adc_8bitFullRange);
    PRINTF("Press any key to get user channel's ADC value.\r\n");
    while (1)
    {
        GETCHAR();
        /*
         When in software trigger mode, each conversion would be launched once calling the "ADC_ChannelConfigure()"
         function, which works like writing a conversion command and executing it. For another channel's conversion,
         just to change the "channelNumber" field in channel's configuration structure, and call the
         "ADC_ChannelConfigure() again.
        */
        ADC_SetChannelConfig(DEMO_ADC_BASE, &adcChannelConfigStruct);
        while (!ADC_GetChannelStatusFlags(DEMO_ADC_BASE))
        {
        }
        PRINTF("ADC Value: %d\r\n", ADC_GetChannelConversionValue(DEMO_ADC_BASE));
    }
}
