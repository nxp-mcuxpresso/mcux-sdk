/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_rtwdog.h"
#if defined(FSL_FEATURE_SOC_RCM_COUNT) && (FSL_FEATURE_SOC_RCM_COUNT)
#include "fsl_rcm.h"
#endif
#if defined(FSL_FEATURE_SOC_SMC_COUNT) && (FSL_FEATURE_SOC_SMC_COUNT > 1)
#include "fsl_msmc.h"
#endif
#if defined(FSL_FEATURE_SOC_ASMC_COUNT) && (FSL_FEATURE_SOC_ASMC_COUNT)
#include "fsl_asmc.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* RESET_CHECK_CNT_VALUE and RESET_CHECK_FLAG is RAM variables used for wdog32 self test.
 * Make sure these variables' locations are proper and will not be affected by watchdog reset,
 * that is, these variables will not be intialized in startup code.
 */
#define RESET_CHECK_CNT_VALUE  (*((uint32_t *)0x20001000))
#define RESET_CHECK_FLAG       (*((uint32_t *)0x20002000))
#define RESET_CHECK_INIT_VALUE 0x0D0DU
#define EXAMPLE_WDOG_BASE      RTWDOG
#define DELAY_TIME             100000U
#define WDOG_IRQHandler        RTWDOG_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if defined(FSL_FEATURE_SOC_RCM_COUNT) && (FSL_FEATURE_SOC_RCM_COUNT)
static RCM_Type *rcm_base = RCM;
#endif
static rtwdog_config_t config;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Get current test mode.
 *
 * @param base RTWDOG peripheral base address
 */
static inline rtwdog_test_mode_t GetTestMode(RTWDOG_Type *base)
{
    return (rtwdog_test_mode_t)((base->CS & RTWDOG_CS_TST_MASK) >> RTWDOG_CS_TST_SHIFT);
}

#if !(defined(FSL_FEATURE_SOC_ASMC_COUNT) && (FSL_FEATURE_SOC_ASMC_COUNT))
/*!
 * @brief WDOG0 IRQ handler.
 *
 */
void WDOG_IRQHandler(void)
{
    RTWDOG_ClearStatusFlags(EXAMPLE_WDOG_BASE, kRTWDOG_InterruptFlag);

    RESET_CHECK_FLAG++;
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
    __DSB();
#endif
}
#endif /* FSL_FEATURE_SOC_ASMC_COUNT */

/*!
 * @brief WDOG32 fast testing.
 *
 * Testing each byte of the WDOG32 counter
 */
void RTWdogFastTesting(void)
{
    rtwdog_test_mode_t current_test_mode;
    uint32_t temp;

    /* When system is boot up, WDOG32 is disabled. We must wait for at least 2.5
     * periods of wdog32 clock to reconfigure wodg32. So Delay a while to wait for
     * the previous configuration taking effect. */
    for (temp = 0; temp < DELAY_TIME; temp++)
    {
        __NOP();
    }
    /*
     * config.enableWdog32 = true;
     * config.clockSource = kWDOG32_ClockSource1;
     * config.prescaler = kWDOG32_ClockPrescalerDivide1;
     * config.testMode = kWDOG32_TestModeDisabled;
     * config.enableUpdate = true;
     * config.enableInterrupt = false;
     * config.enableWindowMode = false;
     * config.windowValue = 0U;
     * config.timeoutValue = 0xFFFFU;
     */
    RTWDOG_GetDefaultConfig(&config);

    config.enableInterrupt = true;
    /* Set the low bits 0xCDU, high bits 0xABU */
    config.timeoutValue = 0xABCDU;
    config.prescaler    = kRTWDOG_ClockPrescalerDivide256;

    current_test_mode = GetTestMode(EXAMPLE_WDOG_BASE);
    if (current_test_mode == kRTWDOG_TestModeDisabled)
    {
        PRINTF("\r\n----- Fast test starts -----\r\n");
/* Set flags in RAM */
#if defined(APP_SKIP_LOW_BYTE_TEST) && (APP_SKIP_LOW_BYTE_TEST)
        RESET_CHECK_FLAG = RESET_CHECK_INIT_VALUE + 1;

        /* High byte test */
        config.testMode = kRTWDOG_HighByteTest;
        PRINTF("High Byte test starts\r\n");
#else
        RESET_CHECK_FLAG = RESET_CHECK_INIT_VALUE;

        /* Low byte test */
        config.testMode = kRTWDOG_LowByteTest;
        PRINTF("Low Byte test starts\r\n");
#endif

        RTWDOG_Init(EXAMPLE_WDOG_BASE, &config);

        /* Waiting for timeout reset */
        PRINTF("Waiting for timeout reset\r\n");
        while (1)
        {
            /* Use temp to store the low byte of counter value */
            temp = (RTWDOG_GetCounterValue(EXAMPLE_WDOG_BASE) & 0x00FFU);
            /* In the idle loop, save the RTWDOG counter value in the RAM for later comparison,
               because the RAM is not affected by the RTWDOG reset*/
            if (temp != 0U)
            {
                RESET_CHECK_CNT_VALUE = temp;
            }
        }
    }
    else if (current_test_mode == kRTWDOG_LowByteTest)
    {
        if ((RESET_CHECK_CNT_VALUE != (config.timeoutValue & 0x00FFU)) ||
            (RESET_CHECK_FLAG != RESET_CHECK_INIT_VALUE + 1)
#if defined(FSL_FEATURE_SOC_RCM_COUNT) && (FSL_FEATURE_SOC_RCM_COUNT)
            || ((RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog) == 0)
#elif defined(FSL_FEATURE_SOC_SMC_COUNT) && (FSL_FEATURE_SOC_SMC_COUNT > 1) /* MSMC */
            || ((SMC_GetPreviousResetSources(EXAMPLE_MSMC_BASE) & kSMC_SourceWdog) == 0)
#elif defined(FSL_FEATURE_SOC_ASMC_COUNT) && (FSL_FEATURE_SOC_ASMC_COUNT)   /* ASMC */
            || ((ASMC_GetSystemResetStatusFlags(EXAMPLE_ASMC_BASE) & kASMC_WatchdogResetFlag) == 0)
#endif
        )
        {
            PRINTF("Low Byte test failed\r\n");
        }
        else
        {
            PRINTF("Low Byte test succeeded\r\n");
        }
        /* High byte test */
        config.testMode = kRTWDOG_HighByteTest;

        PRINTF("----- High Byte test starts -----\r\n");
        RTWDOG_Init(EXAMPLE_WDOG_BASE, &config);
        /* Waiting for timeout reset */
        PRINTF("Waiting for timeout reset\r\n");
        while (1)
        {
            /* Use temp to store the high byte of counter value */
            temp = ((RTWDOG_GetCounterValue(EXAMPLE_WDOG_BASE) >> 8U) & 0x00FFU);
            if (temp != 0U)
            {
                RESET_CHECK_CNT_VALUE = temp;
            }
        }
    }
    else if (current_test_mode == kRTWDOG_HighByteTest)
    {
        if ((RESET_CHECK_CNT_VALUE != ((config.timeoutValue >> 8U) & 0x00FFU)) ||
            (RESET_CHECK_FLAG != RESET_CHECK_INIT_VALUE + 2)
#if defined(FSL_FEATURE_SOC_RCM_COUNT) && (FSL_FEATURE_SOC_RCM_COUNT)
            || ((RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog) == 0)
#elif defined(FSL_FEATURE_SOC_SMC_COUNT) && (FSL_FEATURE_SOC_SMC_COUNT > 1) /* MSMC */
            || ((SMC_GetPreviousResetSources(EXAMPLE_MSMC_BASE) & kSMC_SourceWdog) == 0)
#elif defined(FSL_FEATURE_SOC_ASMC_COUNT) && (FSL_FEATURE_SOC_ASMC_COUNT)   /* ASMC */
            || ((ASMC_GetSystemResetStatusFlags(EXAMPLE_ASMC_BASE) & kASMC_WatchdogResetFlag) == 0)
#endif
        )
        {
            PRINTF("High Byte test failed\r\n");
        }
        else
        {
            PRINTF("High Byte test succeeded\r\n");
        }
        config.testMode     = kRTWDOG_UserModeEnabled;
        config.enableRtwdog = false;

        PRINTF("----- The end of RTWDOG fast test -----\r\n");
        RTWDOG_Init(EXAMPLE_WDOG_BASE, &config);
        RESET_CHECK_FLAG = RESET_CHECK_INIT_VALUE;
    }
    else
    {
        /* User mode enable, skip the fast test */
    }
}

/*!
 * @brief RTWDOG refresh testing
 *
 * Refresh RTWDOG in window and non-window mode.
 */
void RTWdogRefreshTest(void)
{
    if (RESET_CHECK_FLAG == RESET_CHECK_INIT_VALUE)
    {
        /*
         * config.enableWdog32 = true;
         * config.clockSource = kWDOG32_ClockSource1;
         * config.prescaler = kWDOG32_ClockPrescalerDivide1;
         * config.testMode = kWDOG32_TestModeDisabled;
         * config.enableUpdate = true;
         * config.enableInterrupt = false;
         * config.enableWindowMode = false;
         * config.windowValue = 0U;
         * config.timeoutValue = 0xFFFFU;
         */
        RTWDOG_GetDefaultConfig(&config);

        config.testMode        = kRTWDOG_UserModeEnabled;
        config.enableInterrupt = true;

        config.prescaler    = kRTWDOG_ClockPrescalerDivide256;
        config.timeoutValue = 600U;

        PRINTF("\r\n----- Refresh test start -----\r\n");

        /* Refresh test in none-window mode */
        PRINTF("----- None-window mode -----\r\n");

        RTWDOG_Init(EXAMPLE_WDOG_BASE, &config);

        for (int i = 0; i < 6; i++)
        {
            for (;;)
            {
                if (100 * i < RTWDOG_GetCounterValue(EXAMPLE_WDOG_BASE))
                {
                    PRINTF("Refresh rtwdog %d time\r\n", i + 1);
                    RTWDOG_Refresh(EXAMPLE_WDOG_BASE);
                    break;
                }
            }
        }
        PRINTF("Waiting for time out reset\r\n");
        RESET_CHECK_FLAG = RESET_CHECK_INIT_VALUE;
        while (1)
        {
        }
    }
    if (RESET_CHECK_FLAG == RESET_CHECK_INIT_VALUE + 1)
    {
        PRINTF("None-window mode reset succeeded\r\n");
        RTWDOG_GetDefaultConfig(&config);
        config.prescaler       = kRTWDOG_ClockPrescalerDivide256;
        config.testMode        = kRTWDOG_UserModeEnabled;
        config.enableInterrupt = true;
        config.timeoutValue    = 600U;
        /* Refresh test in window mode */
        PRINTF("----- Window mode -----\r\n");
        config.enableWindowMode = true;
        config.windowValue      = 300U;
        RTWDOG_Init(EXAMPLE_WDOG_BASE, &config);

        for (int i = 3; i < 6; i++)
        {
            for (;;)
            {
                /* Refresh wdog32 in the refresh window */
                if (100 * i < RTWDOG_GetCounterValue(EXAMPLE_WDOG_BASE))
                {
                    PRINTF("Refresh rtwdog %d time\r\n", i - 2);
                    RTWDOG_Refresh(EXAMPLE_WDOG_BASE);
                    break;
                }
            }
        }
        PRINTF("Waiting for time out reset\r\n");
        while (1)
        {
        }
    }
    if (RESET_CHECK_FLAG == RESET_CHECK_INIT_VALUE + 2)
    {
        config.enableRtwdog = false;
        config.testMode     = kRTWDOG_TestModeDisabled;

        RTWDOG_Init(EXAMPLE_WDOG_BASE, &config);

        PRINTF("Window mode reset succeeded\r\n");
    }
}

int main(void)
{
    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Enable RTWDOG clock */
    CLOCK_EnableClock(kCLOCK_Wdog3);
    NVIC_EnableIRQ(RTWDOG_IRQn);

#if defined(FSL_FEATURE_SOC_ASMC_COUNT) && (FSL_FEATURE_SOC_ASMC_COUNT)
    if ((ASMC_GetSystemResetStatusFlags(EXAMPLE_ASMC_BASE) & kASMC_WatchdogResetFlag))
    {
        RESET_CHECK_FLAG++;
    }
#endif
    RTWdogFastTesting();
    RTWdogRefreshTest();

    return 0;
}
