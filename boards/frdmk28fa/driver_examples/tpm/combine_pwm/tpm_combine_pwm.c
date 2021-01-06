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
#include "fsl_tpm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* TPM channel pair 0 works with TPM channels 0 and 1 */
#define BOARD_TPM_CHANNEL_PAIR kTPM_Chnl_0

/* Interrupt to enable and flag to read; depends on the TPM channel pair used */
#define TPM_CHANNEL_INTERRUPT_ENABLE kTPM_Chnl0InterruptEnable
#define TPM_CHANNEL_FLAG             kTPM_Chnl0Flag

/* Interrupt number and interrupt handler for the TPM instance used */
#define TPM_INTERRUPT_NUMBER TPM2_IRQn
#define TPM_LED_HANDLER      TPM2_IRQHandler
/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool brightnessUp        = true; /* Indicate LED is brighter or dimmer */
volatile uint8_t updatedDutycycle = 10U;
volatile uint8_t getCharValue     = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    tpm_config_t tpmInfo;
    tpm_chnl_pwm_signal_param_t tpmParam;
    uint8_t deadtimeValue;
    uint32_t filterVal;

#ifndef TPM_LED_ON_LEVEL
#define TPM_LED_ON_LEVEL kTPM_LowTrue
#endif

    /* Configure tpm params with frequency 24kHZ */
    tpmParam.chnlNumber       = BOARD_TPM_CHANNEL_PAIR;
    tpmParam.level            = TPM_LED_ON_LEVEL;
    tpmParam.dutyCyclePercent = updatedDutycycle;
    /* Note: If setting deadtime insertion, the value of firstEdgeDelayPercent must be non-zero */
    tpmParam.firstEdgeDelayPercent = 10U;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* TPM known issue of KL81, enable clock of TPM0 to use other TPM module */
    CLOCK_EnableClock(kCLOCK_Tpm2);
    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    /* Need a deadtime value of about 200nsec */
    deadtimeValue = (((uint64_t)TPM_SOURCE_CLOCK * 200) / 1000000000) / 4;

    /* Print a note to terminal */
    PRINTF("\r\nTPM example to output combined complementary PWM signals on two channels\r\n");
    PRINTF(
        "\r\nIf an LED is connected to the TPM pin, you will see a change in LED brightness if you enter different "
        "values");
    PRINTF("\r\nIf no LED is connected to the TPM pin, then probe the signal using an oscilloscope");

    TPM_GetDefaultConfig(&tpmInfo);

    /* Initialize TPM module */
    TPM_Init(BOARD_TPM_BASEADDR, &tpmInfo);

#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
    /* Change the polarity on the second channel of the pair to get complementary PWM signals */
    BOARD_TPM_BASEADDR->POL |= (1U << ((BOARD_TPM_CHANNEL_PAIR * 2) + 1));
#endif

    /* Set deadtime insertion for the channel pair using channel filter register */
    filterVal = BOARD_TPM_BASEADDR->FILTER;
    /* Clear the channel pair's filter values */
    filterVal &= ~((TPM_FILTER_CH0FVAL_MASK | TPM_FILTER_CH1FVAL_MASK)
                   << ((BOARD_TPM_CHANNEL_PAIR * 2) * (TPM_FILTER_CH0FVAL_SHIFT + TPM_FILTER_CH1FVAL_SHIFT)));
    /* Shift the deadtime insertion value to the right place in the register */
    filterVal |= (TPM_FILTER_CH0FVAL(deadtimeValue) | TPM_FILTER_CH1FVAL(deadtimeValue))
                 << ((BOARD_TPM_CHANNEL_PAIR * 2) * (TPM_FILTER_CH0FVAL_SHIFT + TPM_FILTER_CH1FVAL_SHIFT));
    BOARD_TPM_BASEADDR->FILTER = filterVal;

    TPM_SetupPwm(BOARD_TPM_BASEADDR, &tpmParam, 1U, kTPM_CombinedPwm, 24000U, TPM_SOURCE_CLOCK);

    TPM_StartTimer(BOARD_TPM_BASEADDR, kTPM_SystemClock);

    while (1)
    {
        do
        {
            PRINTF("\r\nPlease enter a value to update the Duty cycle:\r\n");
            PRINTF("Note: The range of value is 1 to 9.\r\n");
            PRINTF("For example: If enter '5', the duty cycle will be set to 50 percent.\r\n");
            PRINTF("Value:");
            getCharValue = GETCHAR() - 0x30U;
            PRINTF("%d", getCharValue);
            PRINTF("\r\n");
        } while ((getCharValue > 9U) || (getCharValue == 0U));

        updatedDutycycle = getCharValue * 10U;

        /* Disable output on each channel of the pair before updating the dutycycle */
        TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)(BOARD_TPM_CHANNEL_PAIR * 2), 0U);
        TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)((BOARD_TPM_CHANNEL_PAIR * 2) + 1), 0U);

        /* Update PWM duty cycle on the channel pair */
        /* Note: If setting deadtime insertion, the value of Dutycycle must be non-zero */
        TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, BOARD_TPM_CHANNEL_PAIR, kTPM_CombinedPwm, updatedDutycycle);

        /* Start output on each channel of the pair with updated dutycycle */
        TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)(BOARD_TPM_CHANNEL_PAIR * 2), TPM_LED_ON_LEVEL);
        TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)((BOARD_TPM_CHANNEL_PAIR * 2) + 1),
                                      TPM_LED_ON_LEVEL);

        PRINTF("The duty cycle was successfully updated!\r\n");
    }
}
