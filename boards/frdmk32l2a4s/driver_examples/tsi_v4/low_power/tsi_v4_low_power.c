/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_tsi_v4.h"
#include "fsl_llwu.h"
#include "fsl_pmc.h"
#include "fsl_rcm.h"
#include "fsl_smc.h"
#include "fsl_debug_console.h"
#include "fsl_lptmr.h"

#include "fsl_intmux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Available PAD names on board */
#define PAD_TSI_ELECTRODE_1_NAME "E1"

/* LLWU module wakeup source index for TSI module */
#define LLWU_TSI_IDX 4U

/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
/* Define LPTMR microseconds counts value */
#define LPTMR_USEC_COUNT (500000U)
#define CORE_CLK_FREQ    CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
tsi_calibration_data_t buffer;

/* Array of LLWU peripheral base address. */
static LLWU_Type *const s_llwuBases[] = LLWU_BASE_PTRS;
/* Array of LLWU IRQ number. */
static const IRQn_Type s_llwuIRQ[] = LLWU_IRQS;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Delay n ms */
void DelayMs(uint32_t n)
{
    uint32_t temp = 0U;
    temp          = n * ((CORE_CLK_FREQ) / 1000U);

    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; /* use core clock */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;  /* disable interrupt */

    do
    {
        if (temp > SysTick_LOAD_RELOAD_Msk)
        {
            SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
            temp -= SysTick_LOAD_RELOAD_Msk;
        }
        else
        {
            SysTick->LOAD = temp;
            temp          = 0;
        }
        SysTick->VAL = 0U;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        /* wait for timeout */
        while (0U == (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
        {
        }
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    } while (temp != 0);
}

void TSI0_IRQHandler(void)
{
    /* Clear flags */
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_ClearStatusFlags(TSI0, (uint32_t)kTSI_OutOfRangeFlag);
    SDK_ISR_EXIT_BARRIER;
}

void LLWU_IRQHandler(void)
{
    if (LLWU_GetInternalWakeupModuleFlag(s_llwuBases[0], LLWU_TSI_IDX))
    {
        /* Clear flags */
        TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
        TSI_ClearStatusFlags(TSI0, (uint32_t)kTSI_OutOfRangeFlag);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i = 0U;
    uint8_t usrInput    = 0U;
#if (defined(FSL_FEATURE_MCG_HAS_PLL) && FSL_FEATURE_MCG_HAS_PLL)
    bool tsi_pee_work_mode_flag = 0;
#endif /* FSL_FEATURE_MCG_HAS_PLL */
    tsi_config_t tsiConfig_normal   = {0};
    tsi_config_t tsiConfig_lowPower = {0};
    lptmr_config_t lptmrConfig;
    memset((void *)&lptmrConfig, 0, sizeof(lptmrConfig));

#if (defined(FSL_FEATURE_SOC_OSC_COUNT) && FSL_FEATURE_SOC_OSC_COUNT)
    oscer_config_t osc_tsiConfig = {0};
    osc_tsiConfig.enableMode     = kOSC_ErClkEnable | kOSC_ErClkEnableInStop;
#if (defined(FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER) && FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER)
    osc_tsiConfig.erclkDiv = 0;
#endif /* FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER */
#endif /* FSL_FEATURE_SOC_OSC_COUNT */

#if (defined(FSL_FEATURE_SMC_HAS_LLS_SUBMODE) && FSL_FEATURE_SMC_HAS_LLS_SUBMODE) || \
    (defined(FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO)
    smc_power_mode_lls_config_t lls_config;
    lls_config.subMode = kSMC_StopSub3;
#if (defined(FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO)
    lls_config.enableLpoClock = true;
#endif
#endif /* (FSL_FEATURE_SMC_HAS_LLS_SUBMODE || FSL_FEATURE_SMC_HAS_LPOPO) */

#if (defined(FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE) && FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE)
    smc_power_mode_vlls_config_t vlls_config;
    vlls_config.subMode                = kSMC_StopSub1;
    vlls_config.enablePorDetectInVlls0 = true;
#if (defined(FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION) && FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION)
    vlls_config.enableRam2InVlls2 = true;
#endif
#if (defined(FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO)
    vlls_config.enableLpoClock = true;
#endif
#endif /* FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE */

    /* Initialize standard SDK demo application pins */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    INTMUX_Init(INTMUX0);
    INTMUX_EnableInterrupt(INTMUX0, 0, TSI0_IRQn);
#if (defined(FSL_FEATURE_MCG_HAS_PLL) && FSL_FEATURE_MCG_HAS_PLL)
    if (kMCG_ModePEE == CLOCK_GetMode())
    {
        tsi_pee_work_mode_flag = 1U;
    }
#endif /* FSL_FEATURE_MCG_HAS_PLL */

#if (defined(FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION) && FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION)
    CLOCK_SetEr32kClock(0x3U); /* Use LPO as source clock */
#endif                         /* FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION */
#if (defined(FSL_FEATURE_SOC_OSC_COUNT) && FSL_FEATURE_SOC_OSC_COUNT)
    OSC_SetExtRefClkConfig(OSC0, &osc_tsiConfig);
#endif /* FSL_FEATURE_SOC_OSC_COUNT */

#if (defined(FSL_FEATURE_SOC_SCG_COUNT) && FSL_FEATURE_SOC_SCG_COUNT)
    SCG->SOSCCSR |= SCG_SOSCCSR_SOSCSTEN_MASK; /* System OSC is enabled in Stop modes */
#endif                                         /* FSL_FEATURE_SOC_SCG_COUNT */

    /* Check wake up from VLLSx mode */
    if (RCM_GetPreviousResetSources(RCM) & 0x01U)
    {
        PMC_ClearPeriphIOIsolationFlag(PMC);
        PRINTF("\r\nWake up from VLLSx modes...\r\n");
    }

    CLOCK_EnableClock(kCLOCK_Tsi0); /* Enable TSI clock after wakeup reset */
    TSI_EnableModule(TSI0, true);   /* Enable module */
    NVIC_EnableIRQ(s_llwuIRQ[0]);
    NVIC_EnableIRQ(TSI0_IRQn);
    TSI_EnableInterrupts(TSI0, kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(TSI0, kTSI_OutOfRangeInterruptEnable);

    /* TSI default hardware configuration for normal mode */
    TSI_GetNormalModeDefaultConfig(&tsiConfig_normal);
    TSI_Init(TSI0, &tsiConfig_normal);
    TSI_EnableHardwareTriggerScan(TSI0, false); /* Enable software trigger scan */

    PRINTF("\r\nTSI_V4 Low_Power_Modes Example Start!\r\n");
    /************ CALIBRATION PROCESS ************/
    PRINTF("Please don't touch the touchpad.\r\n");
    PRINTF("Press anykey to start TSI low power example. \r\n");
    GETCHAR();
    PRINTF("Start calibartion....\r\n");
    memset((void *)&buffer, 0, sizeof(buffer));
    TSI_Calibrate(TSI0, &buffer);
    /* Print calibrated counter values */
    for (i = 0U; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
    {
        PRINTF("Calibrated counters for channel %d is: %d \r\n", i, buffer.calibratedData[i]);
    }
    /************ LOW POWER FUNCTIONS **********/
    /*
     * lptmrConfig.timerMode = kLPTMR_TimerModeTimeCounter;
     * lptmrConfig.pinSelect = kLPTMR_PinSelectInput_0;
     * lptmrConfig.pinPolarity = kLPTMR_PinPolarityActiveHigh;
     * lptmrConfig.enableFreeRunning = false;
     * lptmrConfig.bypassPrescaler = true;
     * lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
     * lptmrConfig.value = kLPTMR_Prescale_Glitch_0;
     */
    LPTMR_GetDefaultConfig(&lptmrConfig);                                              /* Configure LPTMR */
    lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;                        /* Use LPO as clock source. */
    LPTMR_Init(LPTMR0, &lptmrConfig);                                                  /* Initialize the LPTMR */
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(LPTMR_USEC_COUNT, LPTMR_SOURCE_CLOCK)); /* Set timer period */
    /* TSI hardware configuration for low power mode */
    TSI_GetLowPowerModeDefaultConfig(&tsiConfig_lowPower);
    TSI_Init(TSI0, &tsiConfig_lowPower);
    TSI_EnableModule(TSI0, false);                             /* Disable module */
    TSI_EnableLowPower(TSI0, true);                            /* Enable low power */
    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_1); /* Using BOARD_TSI_ELECTRODE_1 as wakeup electrode */
    TSI_SetLowThreshold(TSI0, (uint16_t)(buffer.calibratedData[BOARD_TSI_ELECTRODE_1] / 3));
    TSI_SetHighThreshold(TSI0, (uint16_t)(buffer.calibratedData[BOARD_TSI_ELECTRODE_1] + 100U));
    TSI_EnableHardwareTriggerScan(TSI0, true);
    TSI_EnableInterrupts(TSI0, kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(TSI0, kTSI_OutOfRangeInterruptEnable);
    TSI_ClearStatusFlags(TSI0, (uint32_t)kTSI_OutOfRangeFlag);
    TSI_EnableModule(TSI0, true);

    SMC_SetPowerModeProtection(SMC, SMC_PMPROT_AVLLS_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLP_MASK);

    PRINTF("\r\nLet's move to the low power modes world!!!\r\n");
    PRINTF("\r\nPress specific key to enter stop mode.\r\n");
    PRINTF("After enter stop modes, touch PAD %s to wakeup.\r\n", PAD_TSI_ELECTRODE_1_NAME);
    LPTMR_StartTimer(LPTMR0); /* Start LPTMR triggering */

    while (1)
    {
        PRINTF("\r\nPlease input the mode you want to enter!\r\n");
        PRINTF("0 ------>  STOP MODE \r\n");
        PRINTF("1 ------>  VLPS MODE \r\n");
#if (defined(FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE) && FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE)
        PRINTF("2 ------>  LLS  MODE \r\n");
#endif /* FSL_FEATURE_SMC_HAS_LLS_SUBMODE */
#if (defined(FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE) && FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE)
        PRINTF("3 ------>  VLLS1 MODE\r\n");
        PRINTF("4 ------>  VLLS2 MODE\r\n");
        PRINTF("5 ------>  VLLS3 MODE\r\n");
#endif /* FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE */
        usrInput = GETCHAR();
        switch (usrInput)
        {
            case '0':
                PRINTF("About to enter into STOP MODE! \r\n");
                DelayMs(1U);
                SMC_SetPowerModeStop(SMC, kSMC_PartialStop);

#if (defined(FSL_FEATURE_MCG_HAS_PLL) && FSL_FEATURE_MCG_HAS_PLL)
                if (1 == tsi_pee_work_mode_flag)
                {
                    CLOCK_SetPeeMode();
                }
#endif /* FSL_FEATURE_MCG_HAS_PLL */
                PRINTF("Great!!! You touched it!!!\r\n");
                break;
            case '1':
                PRINTF("About to enter into VLPS MODE! \r\n");
                DelayMs(1U);
                SMC_SetPowerModeVlps(SMC);

#if (defined(FSL_FEATURE_MCG_HAS_PLL) && FSL_FEATURE_MCG_HAS_PLL)
                if (1 == tsi_pee_work_mode_flag)
                {
                    CLOCK_SetPeeMode();
                }
#endif /* FSL_FEATURE_MCG_HAS_PLL */
                PRINTF("Great!!! You touched it!!!\r\n");
                break;
#if (defined(FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE) && FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE)
            case '2':
                PRINTF("About to enter into LLS MODE! \r\n");
                PRINTF("Wakeup will lead to a interrupt flow, pay attention to it!!!\r\n");
                DelayMs(1U);
                LLWU_EnableInternalModuleInterruptWakup(s_llwuBases[0], LLWU_TSI_IDX, true);
#if (defined(FSL_FEATURE_SMC_HAS_LLS_SUBMODE) && FSL_FEATURE_SMC_HAS_LLS_SUBMODE) || \
    (defined(FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO)
                SMC_SetPowerModeLls(SMC, &lls_config);
#else
                SMC_SetPowerModeLls(SMC);
#endif

#if (defined(FSL_FEATURE_MCG_HAS_PLL) && FSL_FEATURE_MCG_HAS_PLL)
                if (1 == tsi_pee_work_mode_flag)
                {
                    CLOCK_SetPeeMode();
                }
#endif /* FSL_FEATURE_MCG_HAS_PLL */
                PRINTF("Great!!! You touched it!!!\r\n");
                break;
#endif /* FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE */
#if (defined(FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE) && FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE)
            case '3':
                PRINTF("About to enter into VLLS1 MODE! \r\n");
                PRINTF("Wakeup will lead to a reset flow, pay attention to it!!!\r\n");
                LLWU_EnableInternalModuleInterruptWakup(s_llwuBases[0], LLWU_TSI_IDX, true);
                SMC_SetPowerModeVlls(SMC, &vlls_config);

                PRINTF("\r\nShould never get here !!!!!!\r\n");
                break;

            case '4':
                PRINTF("About to enter into VLLS2 MODE! \r\n");
                PRINTF("Wakeup will lead to a reset flow, pay attention to it!!!\r\n");
                LLWU_EnableInternalModuleInterruptWakup(s_llwuBases[0], LLWU_TSI_IDX, true);
                vlls_config.subMode = kSMC_StopSub2;
                SMC_SetPowerModeVlls(SMC, &vlls_config);

                PRINTF("\r\nShould never get here !!!!!!\r\n");
                break;

            case '5':
                PRINTF("About to enter into VLLS3 MODE! \r\n");
                PRINTF("Wakeup will lead to a reset flow, pay attention to it!!!\r\n");
                LLWU_EnableInternalModuleInterruptWakup(s_llwuBases[0], LLWU_TSI_IDX, true);
                vlls_config.subMode = kSMC_StopSub3;
                SMC_SetPowerModeVlls(SMC, &vlls_config);

                PRINTF("\r\nShould never get here !!!!!!\r\n");
                break;
#endif /* FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE */
            default:
                PRINTF("Please input a valid character, 0~5!!!\r\n");
                break;
        } /* End of switch(usr_input) */
    }     /* End of while(1) */
} /* End of main() */
