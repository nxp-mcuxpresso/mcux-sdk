/*
 * Copyright (c) 2015,2020, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acmp.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ACMP_BASEADDR    CMP1
#define DEMO_ACMP_MINUS_INPUT 6U
#define DEMO_ACMP_PLUS_INPUT  7U /*  Internal 8bit DAC output. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    acmp_config_t acmpConfigStruct;
    acmp_channel_config_t channelConfigStruct;
    acmp_dac_config_t dacConfigStruct;
    acmp_discrete_mode_config_t acmpDiscreteconfig;
    uint32_t statusFlags;

    /*Enable PMC0->ACTRL BUFEN bit filed to make sure ACMP voltage reference available*/
    PMC0->ACTRL |= PMC0_ACTRL_BUFEN_MASK;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

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

    /* Configure negative inputs are coming from 3v domain. */
    ACMP_GetDefaultDiscreteModeConfig(&acmpDiscreteconfig);
    acmpDiscreteconfig.enableNegativeChannelDiscreteMode = true;
    ACMP_SetDiscreteModeConfig(DEMO_ACMP_BASEADDR, &acmpDiscreteconfig);

    /* Configure channel. Select the positive port input from DAC and negative port input from minus mux input. */
    channelConfigStruct.minusMuxInput = DEMO_ACMP_MINUS_INPUT;
    channelConfigStruct.plusMuxInput  = DEMO_ACMP_PLUS_INPUT;
    ACMP_SetChannelConfig(DEMO_ACMP_BASEADDR, &channelConfigStruct);

    /* Configure DAC. */
#if (defined(DEMO_CMP_USE_VIN1) && DEMO_CMP_USE_VIN1)
    dacConfigStruct.referenceVoltageSource = kACMP_VrefSourceVin1;
#else
    dacConfigStruct.referenceVoltageSource = kACMP_VrefSourceVin2;
#endif                                /* DEMO_CMP_USE_VIN1 */
    dacConfigStruct.DACValue = 0x7FU; /* Half of referene voltage. */
#if defined(FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT) && (FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT == 1U)
    dacConfigStruct.enableOutput = true;
#endif /* FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT */
#if defined(FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT) && (FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT == 1U)
    dacConfigStruct.workMode = kACMP_DACWorkLowSpeedMode;
#endif /* FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT */
    ACMP_SetDACConfig(DEMO_ACMP_BASEADDR, &dacConfigStruct);

    ACMP_Enable(DEMO_ACMP_BASEADDR, true);

    PRINTF("The example compares analog input to the reference DAC output(CMP positive port).\r\n");
    PRINTF("The terminal will print CMP's output value when press any key.\r\n");
    PRINTF("Please press any key to get CMP's output value.\r\n");

    while (true)
    {
        GETCHAR();
        statusFlags = ACMP_GetStatusFlags(DEMO_ACMP_BASEADDR);

        /* Check the comparison result. */
        if ((kACMP_OutputAssertEventFlag == (statusFlags & kACMP_OutputAssertEventFlag)))
        {
            PRINTF("The analog input is LOWER than DAC output\r\n");
        }
        else if ((kACMP_OutputAssertEventFlag != (statusFlags & kACMP_OutputAssertEventFlag)))
        {
            PRINTF("The analog input is HIGHER than DAC output\r\n");
        }
        else
        {
            /* The input state has no change. */
        }
    }
}
