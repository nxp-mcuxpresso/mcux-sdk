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
#include "fsl_adc12.h"
#include "fsl_trgmux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDB_BASE        PDB0
#define DEMO_PDB_IRQ_ID      PDB0_IRQn
#define DEMO_PDB_IRQ_HANDLER PDB0_IRQHandler

#define DEMO_PDB_ADC_TRIGGER_CHANNEL    kPDB_ADCTriggerChannel0 /* For ADC0. */
#define DEMO_PDB_ADC_PRETRIGGER_CHANNEL kPDB_ADCPreTrigger0     /* For ADC0_SC1[0]. */

#define DEMO_ADC12_BASE          ADC0
#define DEMO_ADC12_CHANNEL_GROUP 0U
#define DEMO_ADC12_USER_CHANNEL  0U
#define DEMO_ADC12_IRQ_ID        ADC0_IRQn
#define DEMO_ADC12_IRQ_HANDLER   ADC0_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the ADC12
 */
static void DEMO_InitPDB_ADC(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_PdbDelayInterruptCounter;
volatile bool g_PdbDelayInterruptFlag;
volatile uint32_t g_Adc12InterruptCounter;
volatile bool g_Adc12InterruptFlag;
volatile uint32_t g_Adc12ConvValue;
const uint32_t g_Adc12_8bitFullRange = 256U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void static DEMO_InitPDB_ADC(void)
{
    adc12_config_t adc12ConfigStruct;
    adc12_channel_config_t adc12ChannelConfigStruct;

    ADC12_GetDefaultConfig(&adc12ConfigStruct);
    ADC12_Init(DEMO_ADC12_BASE, &adc12ConfigStruct);
    ADC12_EnableHardwareTrigger(DEMO_ADC12_BASE, true);

    adc12ChannelConfigStruct.channelNumber                        = DEMO_ADC12_USER_CHANNEL;
    adc12ChannelConfigStruct.enableInterruptOnConversionCompleted = true; /* Enable the interrupt. */
    ADC12_SetChannelConfig(DEMO_ADC12_BASE, DEMO_ADC12_CHANNEL_GROUP, &adc12ChannelConfigStruct);
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
void DEMO_ADC12_IRQ_HANDLER(void)
{
    /* Read to clear COCO flag. */
    g_Adc12ConvValue = ADC12_GetChannelConversionValue(DEMO_ADC12_BASE, DEMO_ADC12_CHANNEL_GROUP);
    g_Adc12InterruptCounter++;
    g_Adc12InterruptFlag = true;
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

    CLOCK_SetIpSrc(kCLOCK_Adc0, kCLOCK_IpSrcFircAsync);
    EnableIRQ(DEMO_PDB_IRQ_ID);
    EnableIRQ(DEMO_ADC12_IRQ_ID);

    PRINTF("\r\nPDB ADC12 Pre-Trigger Example.\r\n");

    /* Configure the PDB counter. */
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
    g_Adc12InterruptCounter    = 0U;

    PRINTF("ADC Full Range: %d\r\n", g_Adc12_8bitFullRange);
    PRINTF("\r\nType any key into terminal to trigger the PDB and then trigger the ADC12's conversion ...\r\n");

    while (1)
    {
        GETCHAR();

        g_PdbDelayInterruptFlag = false;
        g_Adc12InterruptFlag    = false;
        PDB_DoSoftwareTrigger(DEMO_PDB_BASE);
        while ((!g_PdbDelayInterruptFlag) || (!g_Adc12InterruptFlag))
        {
        }
        PRINTF("\r\n");
        PRINTF("PDB Interrupt Counter: %d\r\n", g_PdbDelayInterruptCounter);
        PRINTF("ADC12 Conversion Interrupt Counter: %d\r\n", g_Adc12InterruptCounter);
    }
}
