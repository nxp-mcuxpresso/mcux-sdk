/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_cmp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT() LED_RED_INIT(LOGIC_LED_OFF)
#define LED_ON()   LED_RED_ON()
#define LED_OFF()  LED_RED_OFF()

#define DEMO_CMP_BASE             CMP0
#define DEMO_CMP_USER_CHANNEL     0U /* PTC6, CMP0_IN0 */
#define DEMO_CMP_DAC_CHANNEL      7U
#define DEMO_CMP_IRQ_ID           CMP0_IRQn
#define DEMO_CMP_IRQ_HANDLER_FUNC CMP0_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_CmpFlags = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief ISR for CMP interrupt function.
 */
void DEMO_CMP_IRQ_HANDLER_FUNC(void)
{
    g_CmpFlags = CMP_GetStatusFlags(DEMO_CMP_BASE);
    CMP_ClearStatusFlags(DEMO_CMP_BASE, kCMP_OutputRisingEventFlag | kCMP_OutputFallingEventFlag);
    if (0U != (g_CmpFlags & kCMP_OutputRisingEventFlag))
    {
        LED_ON(); /* Turn on led. */
    }
    else if (0U != (g_CmpFlags & kCMP_OutputFallingEventFlag))
    {
        LED_OFF(); /* Turn off led. */
    }
    else
    {
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    cmp_config_t mCmpConfigStruct;
    cmp_dac_config_t mCmpDacConfigStruct;

    /* Initialize hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_CMP_IRQ_ID);

    PRINTF("\r\nCMP interrupt Example.\r\n");

    /*
     * mCmpConfigStruct.enableCmp = true;
     * mCmpConfigStruct.hysteresisMode = kCMP_HysteresisLevel0;
     * mCmpConfigStruct.enableHighSpeed = false;
     * mCmpConfigStruct.enableInvertOutput = false;
     * mCmpConfigStruct.useUnfilteredOutput = false;
     * mCmpConfigStruct.enablePinOut = false;
     * mCmpConfigStruct.enableTriggerMode = false;
     */
    CMP_GetDefaultConfig(&mCmpConfigStruct);
    /* Init the CMP comparator. */
    CMP_Init(DEMO_CMP_BASE, &mCmpConfigStruct);

    /* Configure the DAC channel. */
    mCmpDacConfigStruct.referenceVoltageSource = kCMP_VrefSourceVin2; /* VCC. */
    mCmpDacConfigStruct.DACValue               = 32U;                 /* Half voltage of logic high level. */
    CMP_SetDACConfig(DEMO_CMP_BASE, &mCmpDacConfigStruct);
    CMP_SetInputChannels(DEMO_CMP_BASE, DEMO_CMP_USER_CHANNEL, DEMO_CMP_DAC_CHANNEL);

    /* Configure the LED. */
    LED_INIT();

    CMP_EnableInterrupts(DEMO_CMP_BASE, kCMP_OutputRisingInterruptEnable | kCMP_OutputFallingInterruptEnable);

    while (1)
    {
    }
}
