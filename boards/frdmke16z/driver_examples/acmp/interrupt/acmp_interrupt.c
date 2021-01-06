/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acmp.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ACMP_BASEADDR         CMP0
#define DEMO_ACMP_USER_CHANNEL     0U
#define DEMO_ACMP_IRQ_ID           CMP0_IRQn
#define DEMO_ACMP_IRQ_HANDLER_FUNC CMP0_IRQHandler
#define LED_INIT()                 LED_GREEN1_INIT(LOGIC_LED_OFF)
#define LED_ON()                   LED_GREEN1_ON()
#define LED_OFF()                  LED_GREEN1_OFF()

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_acmpOutputRising  = 0U;
volatile uint32_t g_acmpOutputFalling = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_ACMP_IRQ_HANDLER_FUNC(void)
{
    uint32_t statusFlags;

    statusFlags = ACMP_GetStatusFlags(DEMO_ACMP_BASEADDR);
    ACMP_ClearStatusFlags(DEMO_ACMP_BASEADDR, statusFlags);

    if ((kACMP_OutputAssertEventFlag == (statusFlags & kACMP_OutputAssertEventFlag)) &&
        (kACMP_OutputRisingEventFlag == (statusFlags & kACMP_OutputRisingEventFlag)))
    {
        g_acmpOutputRising = 1U;
    }
    else if ((kACMP_OutputAssertEventFlag != (statusFlags & kACMP_OutputAssertEventFlag)) &&
             (kACMP_OutputFallingEventFlag == (statusFlags & kACMP_OutputFallingEventFlag)))
    {
        g_acmpOutputFalling = 1U;
    }
    else
    {
        /* Unknown interrupt. */
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    acmp_config_t acmpConfigStruct;
    acmp_channel_config_t channelConfigStruct;
    acmp_dac_config_t dacConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    LED_INIT();
    LED_OFF();

    /* Configure ACMP. */
    /*
     * acmpConfigStruct.enableHighSpeed = false;
     * acmpConfigStruct.enableInvertOutput = false;
     * acmpConfigStruct.useUnfilteredOutput = false;
     * acmpConfigStruct.enablePinOut = false;
     * acmpConfigStruct.offsetMode = kACMP_OffsetLevel0;
     * acmpConfigStruct.hysteresisMode = kACMP_HysteresisLevel0;
     */
    ACMP_GetDefaultConfig(&acmpConfigStruct);
    ACMP_Init(DEMO_ACMP_BASEADDR, &acmpConfigStruct);

    /* Configure channel. Select the positive port input from DAC and negative port input from minus mux input. */
    channelConfigStruct.positivePortInput = kACMP_PortInputFromDAC;
    channelConfigStruct.negativePortInput = kACMP_PortInputFromMux;
    channelConfigStruct.minusMuxInput     = DEMO_ACMP_USER_CHANNEL;
    channelConfigStruct.plusMuxInput      = 0U; /* Dummy channel. */
    ACMP_SetChannelConfig(DEMO_ACMP_BASEADDR, &channelConfigStruct);

    /* Configure DAC. */
    dacConfigStruct.referenceVoltageSource = kACMP_VrefSourceVin1;
    dacConfigStruct.DACValue               = 0x7FU; /* Half of referene voltage. */
#if defined(FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT) && (FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT == 1U)
    dacConfigStruct.enableOutput = true;
#endif /* FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT */
#if defined(FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT) && (FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT == 1U)
    dacConfigStruct.workMode = kACMP_DACWorkLowSpeedMode;
#endif /* FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT */
    ACMP_SetDACConfig(DEMO_ACMP_BASEADDR, &dacConfigStruct);

    /* Enable the interrupts. */
    ACMP_EnableInterrupts(DEMO_ACMP_BASEADDR, kACMP_OutputRisingInterruptEnable | kACMP_OutputFallingInterruptEnable);
    EnableIRQ(DEMO_ACMP_IRQ_ID);

    ACMP_Enable(DEMO_ACMP_BASEADDR, true);

    PRINTF("The example compares analog input to the reference DAC output(CMP positive port).\r\n");
    PRINTF("The LED will be turned ON/OFF when the analog input is LOWER/HIGHER than the DAC output.\r\n");
    PRINTF("Change the analog input voltage to see the LED status.\r\n");

    while (true)
    {
        /* Check the comparison result and toggle the LED according to the result. */
        if (g_acmpOutputRising)
        {
            g_acmpOutputRising = 0U;
            LED_ON();
            PRINTF("The analog input is LOWER than DAC output\r\n");
        }
        else if (g_acmpOutputFalling)
        {
            g_acmpOutputFalling = 0U;
            LED_OFF();
            PRINTF("The analog input is HIGHER than DAC output\r\n");
        }
        else
        {
            /* Unknown status. */
        }
    }
}
