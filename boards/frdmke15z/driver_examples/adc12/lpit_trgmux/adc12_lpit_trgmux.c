/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lpit.h"
#include "fsl_adc12.h"
#include "fsl_trgmux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC12_BASEADDR ADC0
/* PTA0, ADC0_SEL0 */
#define DEMO_ADC12_USER_CHANNEL (0U)

#define DEMO_ADC12_CHANNEL_GROUP    (0U)
#define DEMO_ADC12_IRQ_ID           ADC0_IRQn
#define DEMO_ADC12_IRQ_HANDLER_FUNC ADC0_IRQHandler

#define DEMO_LPIT_USER_CHANNEL  kLPIT_Chnl_0
#define DEMO_LPIT_USER_TIMER_CH kLPIT_Trigger_TimerChn0
#define DEMO_LPIT_SOURCECLOCK   CLOCK_GetIpFreq(kCLOCK_Lpit0)
/* LPIT triggers ADC every LPIT_TRIGGER_TIME us*/
#define LPIT_TRIGGER_TIME (1000000U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_ConfigTriggerSource(void);
/*!
 * @brief Initialize the LPIT to periodic counter mode
 */
static void DEMO_InitLpitTrigger(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_Adc12InterruptCounter;
volatile bool g_Adc12ConversionCompletedFlag;
volatile uint32_t g_Adc12ConvValue;
const uint32_t g_Adc12_12bitFullRange = 4096U;

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_ConfigTriggerSource(void)
{
    TRGMUX_SetTriggerSource(TRGMUX0, kTRGMUX_Adc0, kTRGMUX_TriggerInput0, kTRGMUX_SourceLpit0Ch0);

    /* Configure SIM for ADC hardware trigger source selection */
    /* Use TRGMUX output as ADC pre-trigger trigger source */
    SIM->ADCOPT |= SIM_ADCOPT_ADC0TRGSEL(1U);
    SIM->ADCOPT |= SIM_ADCOPT_ADC0PRETRGSEL(1U);
}
static void DEMO_InitLpitTrigger(void)
{
    /* Structure of initialize LPIT */
    lpit_config_t lpitConfig;
    lpit_chnl_params_t lpitChannelConfig;

    LPIT_GetDefaultConfig(&lpitConfig);
    /* Init lpit module */
    LPIT_Init(LPIT0, &lpitConfig);

    lpitChannelConfig.chainChannel          = false;
    lpitChannelConfig.enableReloadOnTrigger = false;
    lpitChannelConfig.enableStartOnTrigger  = false;
    lpitChannelConfig.enableStopOnTimeout   = false;
    lpitChannelConfig.timerMode             = kLPIT_PeriodicCounter;
    /* Set default values for the trigger source */
    lpitChannelConfig.triggerSelect = DEMO_LPIT_USER_TIMER_CH;
    lpitChannelConfig.triggerSource = kLPIT_TriggerSource_External;

    /* Init lpit channel 0 */
    LPIT_SetupChannel(LPIT0, DEMO_LPIT_USER_CHANNEL, &lpitChannelConfig);

    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(LPIT0, DEMO_LPIT_USER_CHANNEL, USEC_TO_COUNT(LPIT_TRIGGER_TIME, DEMO_LPIT_SOURCECLOCK));

    /* Disable timer interrupts for channel 0 */
    LPIT_DisableInterrupts(LPIT0, kLPIT_Channel0TimerInterruptEnable);

    /* Start the timer */
    LPIT_StartTimer(LPIT0, kLPIT_Chnl_0);
}

/*!
 * @brief ISR for ADC12 interrupt function
 */
void DEMO_ADC12_IRQ_HANDLER_FUNC(void)
{
    /* Read to clear COCO flag. */
    g_Adc12ConvValue = ADC12_GetChannelConversionValue(DEMO_ADC12_BASEADDR, DEMO_ADC12_CHANNEL_GROUP);
    g_Adc12InterruptCounter++;
    g_Adc12ConversionCompletedFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    adc12_config_t adc12ConfigStruct;
    adc12_channel_config_t adc12ChannelConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Set the source for the ADC module */
    CLOCK_SetIpSrc(kCLOCK_Adc0, kCLOCK_IpSrcSircAsync);
    /* Set the source for the LPIT module */
    CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcSircAsync);
    BOARD_ConfigTriggerSource();

    /* Configure the lpit to trigger ADC periodically */
    DEMO_InitLpitTrigger();

    /* Initialize ADC. */
    ADC12_GetDefaultConfig(&adc12ConfigStruct);
    adc12ConfigStruct.referenceVoltageSource     = kADC12_ReferenceVoltageSourceVref;
    adc12ConfigStruct.resolution                 = kADC12_Resolution12Bit;
    adc12ConfigStruct.enableContinuousConversion = false;
    ADC12_Init(DEMO_ADC12_BASEADDR, &adc12ConfigStruct);
    /* Set to hardware trigger mode. */
    ADC12_EnableHardwareTrigger(DEMO_ADC12_BASEADDR, true);

    /* Calibrate ADC. */
    if (kStatus_Success != ADC12_DoAutoCalibration(DEMO_ADC12_BASEADDR))
    {
        PRINTF("ADC calibration failed!\r\n");
    }

    adc12ChannelConfigStruct.channelNumber                        = DEMO_ADC12_USER_CHANNEL;
    adc12ChannelConfigStruct.enableInterruptOnConversionCompleted = true; /* Enable the interrupt. */
    ADC12_SetChannelConfig(DEMO_ADC12_BASEADDR, DEMO_ADC12_CHANNEL_GROUP, &adc12ChannelConfigStruct);

    NVIC_EnableIRQ(DEMO_ADC12_IRQ_ID);

    g_Adc12InterruptCounter = 0U;

    PRINTF("ADC Full Range: %d\r\n", g_Adc12_12bitFullRange);
    PRINTF("\r\nChange the input voltage to check ADC12's conversion result...\r\n");

    while (1)
    {
        g_Adc12ConversionCompletedFlag = false;

        while (!g_Adc12ConversionCompletedFlag)
        {
        }

        PRINTF("\r\nADC12 Interrupt Counter: %d\r\n", g_Adc12InterruptCounter);
        PRINTF("ADC12 Conversion Completed, result value: %d\r\n", g_Adc12ConvValue);
    }
}
