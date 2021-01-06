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
#include "fsl_pdb.h"
#include "fsl_adc16.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDB_BASE        PDB0
#define DEMO_PDB_IRQ_ID      PDB0_IRQn
#define DEMO_PDB_IRQ_HANDLER PDB0_IRQHandler

#define DEMO_PDB_ADC_TRIGGER_CHANNEL    kPDB_ADCTriggerChannel0 /* For ADC0. */
#define DEMO_PDB_ADC_PRETRIGGER_CHANNEL kPDB_ADCPreTrigger0     /* For ADC0_SC1[0]. */

#define DEMO_ADC_BASE          ADC0
#define DEMO_ADC_CHANNEL_GROUP 0U
#define DEMO_ADC_USER_CHANNEL  0U
#define DEMO_ADC_IRQ_ID        ADC0_IRQn
#define DEMO_ADC_IRQ_HANDLER   ADC0_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the ADC16
 */
static void DEMO_InitPDB_ADC(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_PdbDelayInterruptCounter;
volatile bool g_PdbDelayInterruptFlag;
volatile uint32_t g_AdcInterruptCounter;
volatile bool g_AdcInterruptFlag;
volatile uint32_t g_AdcConvValue;
const uint32_t g_Adc16_12bitFullRange = 4096U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void static DEMO_InitPDB_ADC(void)
{
    adc16_config_t adc16ConfigStruct;
    adc16_channel_config_t adc16ChannelConfigStruct;

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
    ADC16_Init(DEMO_ADC_BASE, &adc16ConfigStruct);
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    ADC16_EnableHardwareTrigger(DEMO_ADC_BASE, false);
    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC_BASE))
    {
        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
    ADC16_EnableHardwareTrigger(DEMO_ADC_BASE, true);

    adc16ChannelConfigStruct.channelNumber                        = DEMO_ADC_USER_CHANNEL;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true; /* Enable the interrupt. */
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
    ADC16_SetChannelConfig(DEMO_ADC_BASE, DEMO_ADC_CHANNEL_GROUP, &adc16ChannelConfigStruct);
}

/*!
 * @brief ISR for PDB interrupt function
 */
void DEMO_PDB_IRQ_HANDLER(void)
{
    PDB_ClearStatusFlags(DEMO_PDB_BASE, kPDB_DelayEventFlag);
    g_PdbDelayInterruptCounter++;
    g_PdbDelayInterruptFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief ISR for ADC16 interrupt function
 */
void DEMO_ADC_IRQ_HANDLER(void)
{
    /* Read to clear COCO flag. */
    g_AdcConvValue = ADC16_GetChannelConversionValue(DEMO_ADC_BASE, DEMO_ADC_CHANNEL_GROUP);
    g_AdcInterruptCounter++;
    g_AdcInterruptFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    pdb_config_t pdbConfigStruct;
    pdb_adc_pretrigger_config_t pdbAdcPreTriggerConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_PDB_IRQ_ID);
    EnableIRQ(DEMO_ADC_IRQ_ID);

    PRINTF("\r\nPDB ADC16 Pre-Trigger Example.\r\n");

    /* Configure the PDB counter. */
    /*
     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
     * pdbConfigStruct.enableContinuousMode = false;
     */
    PDB_GetDefaultConfig(&pdbConfigStruct);
    PDB_Init(DEMO_PDB_BASE, &pdbConfigStruct);

    /* Configure the delay interrupt. */
    PDB_SetModulusValue(DEMO_PDB_BASE, 1000U);

    /* The available delay value is less than or equal to the modulus value. */
    PDB_SetCounterDelayValue(DEMO_PDB_BASE, 1000U);
    PDB_EnableInterrupts(DEMO_PDB_BASE, kPDB_DelayInterruptEnable);

    /* Configure the ADC Pre-Trigger. */
    pdbAdcPreTriggerConfigStruct.enablePreTriggerMask          = 1U << DEMO_PDB_ADC_PRETRIGGER_CHANNEL;
    pdbAdcPreTriggerConfigStruct.enableOutputMask              = 1U << DEMO_PDB_ADC_PRETRIGGER_CHANNEL;
    pdbAdcPreTriggerConfigStruct.enableBackToBackOperationMask = 0U;
    PDB_SetADCPreTriggerConfig(DEMO_PDB_BASE, DEMO_PDB_ADC_TRIGGER_CHANNEL, &pdbAdcPreTriggerConfigStruct);
    PDB_SetADCPreTriggerDelayValue(DEMO_PDB_BASE, DEMO_PDB_ADC_TRIGGER_CHANNEL, DEMO_PDB_ADC_PRETRIGGER_CHANNEL, 200U);
    /* The available Pre-Trigger delay value is less than or equal to the modulus value. */

    PDB_DoLoadValues(DEMO_PDB_BASE);

    /* Configure the ADC. */
    DEMO_InitPDB_ADC();

    g_PdbDelayInterruptCounter = 0U;
    g_AdcInterruptCounter      = 0U;

    PRINTF("ADC Full Range: %d\r\n", g_Adc16_12bitFullRange);
    while (1)
    {
        PRINTF("\r\nType any key into terminal to trigger the PDB and then trigger the ADC's conversion ...\r\n");
        GETCHAR();

        g_PdbDelayInterruptFlag = false;
        g_AdcInterruptFlag      = false;
        PDB_DoSoftwareTrigger(DEMO_PDB_BASE);
        while ((!g_PdbDelayInterruptFlag) || (!g_AdcInterruptFlag))
        {
        }
        PRINTF("\r\n");
        PRINTF("PDB Interrupt Counter: %d\r\n", g_PdbDelayInterruptCounter);
        PRINTF("ADC Conversion Interrupt Counter: %d\r\n", g_AdcInterruptCounter);
        PRINTF("ADC Conversion Value: %d\r\n", g_AdcConvValue);
    }
}
