/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acmp.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_lptmr.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ACMP_BASEADDR CMP0

#define DEMO_ACMP_IRQ_ID           CMP0_IRQn
#define DEMO_ACMP_IRQ_HANDLER_FUNC CMP0_IRQHandler

/* Select which channels is used to do round robin checker.
 * Example sets positive port as fixed port with DAC output as comparison reference. So Pre-state mask bit high
 * represents the pre-state of corresponding channel's input voltage is higher than DAC output voltage. If the round
 * robin check result shows that corresponding channel's actual input voltage is lower than DAC output voltage, wakeup
 * event will be generated. The case of pre-state mask bit low is contrary to the case of pre-state mask bit high.
 */
#define DEMO_ACMP_ROUND_ROBIN_FIXED_CHANNEL           0U
#define DEMO_ACMP_ROUND_ROBIN_CHANNELS_CHECKER_MASK   0x01U /* Left-most bit is for channel 7. */
#define DEMO_ACMP_ROUND_ROBIN_CHANNELS_PRE_STATE_MASK 0x01U /* Left-most bit is for channel 7. */
#define DEMO_ACMP_ROUND_ROBIN_PERIOD_MILLISECONDS     1000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_InitAcmpRoundRobinTrigger(uint32_t triggerPeroid_Ms);
void BOARD_ClearAcmpRoundRobinTrigger(void);
void BOARD_EnterStopMode(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_InitAcmpRoundRobinTrigger(uint32_t triggerPeroid_Ms)
{
    lptmr_config_t lptmrConfig;

    /* Configure LPTMR */
    /*
     * lptmrConfig.timerMode = kLPTMR_TimerModeTimeCounter;
     * lptmrConfig.pinSelect = kLPTMR_PinSelectInput_0;
     * lptmrConfig.pinPolarity = kLPTMR_PinPolarityActiveHigh;
     * lptmrConfig.enableFreeRunning = false;
     * lptmrConfig.bypassPrescaler = true;
     * lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
     * lptmrConfig.value = kLPTMR_Prescale_Glitch_0;
     */
    LPTMR_GetDefaultConfig(&lptmrConfig);
    /* Enable prescaler */
    lptmrConfig.bypassPrescaler = false;
    /* Prescaler divides the prescaler clock(LPO 128kHz) by 128 */
    lptmrConfig.value = kLPTMR_Prescale_Glitch_6;

    /* Initialize the LPTMR */
    LPTMR_Init(LPTMR0, &lptmrConfig);

    /* Set timer period */
    LPTMR_SetTimerPeriod(LPTMR0, triggerPeroid_Ms);

    /* Start counting */
    LPTMR_StartTimer(LPTMR0);
}

void BOARD_ClearAcmpRoundRobinTrigger(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
}

void BOARD_EnterStopMode(void)
{
    volatile uint32_t i;

    /* Allows to enter stop mode. */
    SMC->PMPROT |= SMC_PMPROT_AVLP_MASK;
    /* Select to enter STOP mode. */
    SMC->PMCTRL &= ~SMC_PMCTRL_STOPM_MASK;
    SMC->PMCTRL |= SMC_PMCTRL_STOPM(0U);

    /* Clear the SLEEPDEEP bit to disable deep sleep mode - enter wait mode*/
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    /*
     * Delay some time to ensure that all register writes associated with setting up the low power mode being entered
     * have completed before the MCU enters the low power mode.
     */
    for (i = 0U; i <= 100000U; i++)
    {
        __ASM("NOP");
    }
    __WFI();
}
void DEMO_ACMP_IRQ_HANDLER_FUNC(void)
{
    uint32_t statusFlags;

    statusFlags = ACMP_GetStatusFlags(DEMO_ACMP_BASEADDR);
    ACMP_ClearStatusFlags(DEMO_ACMP_BASEADDR, statusFlags);

    statusFlags = ACMP_GetRoundRobinStatusFlags(DEMO_ACMP_BASEADDR);
    ACMP_ClearRoundRobinStatusFlags(DEMO_ACMP_BASEADDR, statusFlags);

    BOARD_ClearAcmpRoundRobinTrigger();
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
    acmp_round_robin_config_t roundRobinConfigStruct;
    uint8_t ch;

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

#if defined(FSL_FEATURE_ACMP_HAS_C1_INPSEL_BIT) && (FSL_FEATURE_ACMP_HAS_C1_INPSEL_BIT == 1U)
    /* Configure channel. Select the positive port input from DAC and negative port input from minus mux input. */
    channelConfigStruct.positivePortInput = kACMP_PortInputFromDAC;
    channelConfigStruct.negativePortInput = kACMP_PortInputFromMux;
#endif
    /* Plus mux input must be different from minus mux input in round robin mode although they aren't functional.
     * Please refer to the reference manual to get detail description.
     */
    channelConfigStruct.plusMuxInput  = 0U;
    channelConfigStruct.minusMuxInput = 1U;
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

    /* Configure round robin mode. */
    roundRobinConfigStruct.fixedPort          = kACMP_FixedPlusPort;
    roundRobinConfigStruct.fixedChannelNumber = DEMO_ACMP_ROUND_ROBIN_FIXED_CHANNEL;
    roundRobinConfigStruct.checkerChannelMask = DEMO_ACMP_ROUND_ROBIN_CHANNELS_CHECKER_MASK;
    roundRobinConfigStruct.sampleClockCount   = 0U;
    roundRobinConfigStruct.delayModulus       = 0U;
    ACMP_SetRoundRobinConfig(DEMO_ACMP_BASEADDR, &roundRobinConfigStruct);

    ACMP_EnableInterrupts(DEMO_ACMP_BASEADDR, kACMP_RoundRobinInterruptEnable);
    EnableIRQ(DEMO_ACMP_IRQ_ID);

    ACMP_SetRoundRobinPreState(DEMO_ACMP_BASEADDR, DEMO_ACMP_ROUND_ROBIN_CHANNELS_PRE_STATE_MASK);

    /* Set round robin comparison trigger period in STOP mode. */
    BOARD_InitAcmpRoundRobinTrigger(DEMO_ACMP_ROUND_ROBIN_PERIOD_MILLISECONDS);

    ACMP_Enable(DEMO_ACMP_BASEADDR, true);

    PRINTF(
        "\r\nExample to demonstrate low power wakeup by round robin comparison! \
           \r\nIn order to wakeup the MCU, please change the analog input voltage to be different from original pre-state setting.\r\n");

    while (1)
    {
        PRINTF("\r\nPress %c for enter: Stop Mode\r\n", 'S');

        ch = GETCHAR();

        if ((ch >= 'a') && (ch <= 'z'))
        {
            ch -= 'a' - 'A';
        }
        if (ch == 'S')
        {
            PRINTF("\r\nThe system entered into stop mode.\r\n");
            BOARD_EnterStopMode();

            /* Wakeup and print information. */
            PRINTF("\r\nThe system exited from stop mode!\r\n");
            while (true)
            {
            }
        }
        else
        {
            PRINTF("Wrong value!\r\n");
        }
    }
}
