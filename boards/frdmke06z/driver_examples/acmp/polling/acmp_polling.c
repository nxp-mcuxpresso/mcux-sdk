/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acmp.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_gpio.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ACMP_BASEADDR       ACMP0
#define DEMO_ACMP_POSITIVE_INPUT kACMP_InternalDACOutput
#define DEMO_ACMP_NEGATIVE_INPUT kACMP_ExternalReference0

#define LED_INIT() LED_RED1_INIT(LOGIC_LED_OFF)
#define LED_OFF()  LED_RED1_OFF()
#define LED_ON()   LED_RED1_ON()

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
    acmp_dac_config_t dacConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    LED_INIT();
    LED_OFF();

    /* Initialize ACMP module. */
    ACMP_GetDefaultConfig(&acmpConfigStruct);
    ACMP_Init(DEMO_ACMP_BASEADDR, &acmpConfigStruct);

    /* Configure ACMP negative and positive input channels. */
    ACMP_SetChannelConfig(DEMO_ACMP_BASEADDR, DEMO_ACMP_POSITIVE_INPUT, DEMO_ACMP_NEGATIVE_INPUT);

    /* Configure internal DAC. */
    dacConfigStruct.DACValue               = 32U;                  /* Half of reference voltage. */
    dacConfigStruct.referenceVoltageSource = kACMP_VrefSourceVin2; /* VDDA as the reference voltage. */
    ACMP_SetDACConfig(DEMO_ACMP_BASEADDR, &dacConfigStruct);

    /* Enable ACMP input pin. */
    ACMP_EnableInputPin(DEMO_ACMP_BASEADDR, 1U << DEMO_ACMP_NEGATIVE_INPUT, true);

    /* Enable the ACMP module. */
    ACMP_Enable(DEMO_ACMP_BASEADDR, true);

    PRINTF("The example compares analog input to the reference DAC output(CMP positive port).\r\n");
    PRINTF("The LED will be turned ON/OFF when the analog input is LOWER/HIGHER than the DAC output.\r\n");
    PRINTF("Change the analog input voltage to see the LED status.\r\n");

    while (true)
    {
        /* Check the comparison result and sets the LED state according to the result.*/
        if (kACMP_OutputFlag == (kACMP_OutputFlag & ACMP_GetStatusFlags(DEMO_ACMP_BASEADDR)))
        {
            LED_ON();
        }
        else
        {
            LED_OFF();
        }
    }
}
