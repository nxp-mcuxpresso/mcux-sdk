/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_wdog8.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* RESET_CHECK_FLAG is a RAM variable used for wdog8 self test.
 * Make sure this variable's location is proper that it will not be affected by watchdog reset,
 * that is, the variable shall not be intialized in startup code.
 */
#define RESET_CHECK_FLAG       (*((uint32_t *)0x20000100))
#define RESET_CHECK_INIT_VALUE 0x0D0D
#define EXAMPLE_WDOG_BASE      WDOG
#define DELAY_TIME             100000U

#define WDOG_WCT_INSTRUCITON_COUNT (128U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static WDOG_Type *wdog8_base = EXAMPLE_WDOG_BASE;
static wdog8_config_t config;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Wait until the WCT is closed.
 *
 * This function is used to wait until the WCT window is closed, WCT time is 128 bus cycles
 *
 * @param base WDOG32 peripheral base address
 */
static void WaitWctClose(WDOG_Type *base)
{
    /* Accessing register by bus clock */
    for (uint32_t i = 0; i < WDOG_WCT_INSTRUCITON_COUNT; i++)
    {
        (void)base->CNT;
    }
}

/*!
 * @brief Get current test mode.
 *
 * @param base WDOG8 peripheral base address
 */
static inline wdog8_test_mode_t GetTestMode(WDOG_Type *base)
{
    return (wdog8_test_mode_t)((base->CS1 & WDOG_CS1_TST_MASK) >> WDOG_CS1_TST_SHIFT);
}

/*!
 * @brief WDOG IRQ handler.
 *
 */
void WDOG_IRQHandler(void)
{
    WDOG8_ClearStatusFlags(wdog8_base, kWDOG8_InterruptFlag);

    RESET_CHECK_FLAG++;
}

/*!
 * @brief WDOG8 fast testing.
 *
 * Testing each byte of the WDOG8 counter
 */
void Wdog8FastTesting(void)
{
    wdog8_test_mode_t current_test_mode;
    uint32_t temp;

    /* When system is boot up, WDOG8 is disabled. We must wait for at least 2.5
     * periods of wdog8 clock to reconfigure wodg8. So Delay a while to wait for
     * the previous configuration taking effect. */
    for (temp = 0; temp < DELAY_TIME; temp++)
    {
        __NOP();
    }

    /*
     * config.enableWdog8 = true;
     * config.clockSource = kWDOG8_ClockSource1;
     * config.prescaler = kWDOG8_ClockPrescalerDivide1;
     * config.testMode = kWDOG8_TestModeDisabled;
     * config.enableUpdate = true;
     * config.enableInterrupt = false;
     * config.enableWindowMode = false;
     * config.windowValue = 0U;
     * config.timeoutValue = 0xFFFFU;
     */
    WDOG8_GetDefaultConfig(&config);

    config.enableInterrupt = true;
    config.timeoutValue    = 0xf0f0U;

    current_test_mode = GetTestMode(wdog8_base);

    if (current_test_mode == kWDOG8_TestModeDisabled)
    {
        /* Set flags in RAM */
#if defined(APP_SKIP_LOW_BYTE_TEST) && (APP_SKIP_LOW_BYTE_TEST)
        RESET_CHECK_FLAG = RESET_CHECK_INIT_VALUE + 1;

        /* High byte test */
        config.testMode = kWDOG8_HighByteTest;
#else
        RESET_CHECK_FLAG = RESET_CHECK_INIT_VALUE;

        /* Low byte test */
        config.testMode = kWDOG8_LowByteTest;
#endif
        WDOG8_Init(wdog8_base, &config);
        /* Wait for timeout reset */
        while (1)
        {
        }
    }
    else if (current_test_mode == kWDOG8_LowByteTest)
    {
        if (RESET_CHECK_FLAG != (RESET_CHECK_INIT_VALUE + 1))
        {
            PRINTF("Low Byte test fail\r\n");
        }
        else
        {
            PRINTF("Low Byte test success\r\n");
            /* High byte test */
            config.testMode = kWDOG8_HighByteTest;

            WDOG8_Init(wdog8_base, &config);
            /* Wait for timeout reset */
            while (1)
            {
            }
        }
    }
    else if (current_test_mode == kWDOG8_HighByteTest)
    {
        if (RESET_CHECK_FLAG != (RESET_CHECK_INIT_VALUE + 2))
        {
            PRINTF("High Byte test fail\r\n");
        }
        else
        {
            PRINTF("High Byte test success\r\n");

            config.testMode    = kWDOG8_UserModeEnabled;
            config.enableWdog8 = false;

            WDOG8_Init(wdog8_base, &config);
            WaitWctClose(wdog8_base);
        }
    }
    else
    {
    }
}

/*!
 * @brief WDOG8 refresh testing
 *
 * Refresh WDOG8 in window and non-window mode.
 */
void Wdog8RefreshTest(void)
{
    uint32_t primaskValue = 0U;

    /*
     * config.enableWdog8 = true;
     * config.clockSource = kWDOG8_ClockSource1;
     * config.prescaler = kWDOG8_ClockPrescalerDivide1;
     * config.testMode = kWDOG8_TestModeDisabled;
     * config.enableUpdate = true;
     * config.enableInterrupt = false;
     * config.enableWindowMode = false;
     * config.windowValue = 0U;
     * config.timeoutValue = 0xFFFFU;
     */
    WDOG8_GetDefaultConfig(&config);

    config.testMode = kWDOG8_UserModeEnabled;

    config.clockSource  = kWDOG8_ClockSource0;
    config.prescaler    = kWDOG8_ClockPrescalerDivide256;
    config.windowValue  = 6000U;
    config.timeoutValue = 60000U;

    PRINTF("\r\n----- Refresh test start -----\r\n");

    /* Refresh test in none-window mode */
    PRINTF("----- None-window mode -----\r\n");
    config.enableWindowMode = false;
    config.enableWdog8      = true;

    WDOG8_Init(wdog8_base, &config);

    for (int i = 0; i < 10; i++)
    {
        for (;;)
        {
            if (1000 * i < WDOG8_GetCounterValue(wdog8_base))
            {
                PRINTF("Refresh wdog8 %d time\r\n", i);
                WDOG8_Refresh(wdog8_base);
                break;
            }
        }
    }
    /* Disable the global interrupts */
    primaskValue = DisableGlobalIRQ();
    WDOG8_Unlock(wdog8_base);
    WDOG8_Disable(wdog8_base);
    WaitWctClose(wdog8_base);
    EnableGlobalIRQ(primaskValue);
    /* Refresh test in window mode */
    PRINTF("----- Window mode -----\r\n");

    config.enableWindowMode = true;
    config.enableWdog8      = true;

#if (!defined(BOARD_XTAL0_CLK_HZ))
    /* Use internal clocks when oscilator clock is not available */
    config.clockSource = kWDOG8_ClockSource1;
#else
    config.clockSource = kWDOG8_ClockSource2;
#endif

    config.prescaler = kWDOG8_ClockPrescalerDivide1;

    WDOG8_Init(wdog8_base, &config);
    /* When switching clock sources during reconfiguration, the watchdog hardware holds the counter at
       zero for 2.5 periods of the previous clock source and 2.5 periods of the new clock source
       after the configuration time period (128 bus clocks) ends */
    while (WDOG8_GetCounterValue(wdog8_base) != 0)
    {
    }
    while (WDOG8_GetCounterValue(wdog8_base) == 0)
    {
    }
    for (int i = 6; i < 9; i++)
    {
        for (;;)
        {
            /* Refresh wdog8 in the refresh window */
            if (1000 * i < WDOG8_GetCounterValue(wdog8_base))
            {
                PRINTF("Refresh wdog8 %d time\r\n", i - 6);
                WDOG8_Refresh(wdog8_base);
                break;
            }
        }
    }

    config.enableWdog8 = false;
    config.testMode    = kWDOG8_TestModeDisabled;

    WDOG8_Init(wdog8_base, &config);
    WaitWctClose(wdog8_base);

    PRINTF("----- Refresh test success  -----\r\n\r\n");
}

int main(void)
{
    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    NVIC_EnableIRQ(WDOG_IRQn);

    Wdog8FastTesting();
    Wdog8RefreshTest();
    PRINTF("----- End of WDOG8 example  -----\r\n\r\n");

    while (1)
    {
    }
}
