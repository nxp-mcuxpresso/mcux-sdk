/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_wdog.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_WDOG_BASE       WDOG1
#define DEMO_WDOG_IRQHandler WDOG1_IRQHandler

#define EXAMPLE_DISABLE_WDOG_RESET_FUNCTION (1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void DEMO_WDOG_IRQHandler(void)
{
    WDOG_ClearInterruptStatus(DEMO_WDOG_BASE, kWDOG_InterruptFlag);
    /* User code. User can do urgent case before timeout reset.
     * IE. user can backup the ram data or ram log to flash.
     * the period is set by config.interruptTimeValue, user need to
     * check the period between interrupt and timeout.
     */
}

void delay(uint32_t u32Timeout)
{
    while (u32Timeout-- > 0U)
    {
        __NOP();
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint16_t resetFlag = 0U;
    wdog_config_t config;
    /* M7 has its local cache and enabled by default,
     * need to set smart subsystems (0x28000000 ~ 0x3FFFFFFF)
     * non-cacheable before accessing this address region */
    BOARD_InitMemory();

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n******** System Start ********\r\n");
    PRINTF("System reset by:");

    resetFlag = WDOG_GetStatusFlags(DEMO_WDOG_BASE);

    switch (resetFlag & (kWDOG_PowerOnResetFlag | kWDOG_TimeoutResetFlag | kWDOG_SoftwareResetFlag))
    {
        case kWDOG_PowerOnResetFlag:
            PRINTF(" Power On Reset!\r\n");
            break;
        case kWDOG_TimeoutResetFlag:
            PRINTF(" Time Out Reset!\r\n");
            break;
        case kWDOG_SoftwareResetFlag:
            PRINTF(" Software Reset!\r\n");
            break;
        default:
            PRINTF(" Error status!\r\n");
            break;
    }
/* Disable wdog reset function test for some devices can't using this feature. */
#if (!(defined(EXAMPLE_DISABLE_WDOG_RESET_FUNCTION) && EXAMPLE_DISABLE_WDOG_RESET_FUNCTION))
    /* If system reset from power on, trigger a software reset. */
    if (resetFlag & kWDOG_PowerOnResetFlag)
    {
        PRINTF("\r\n- 1.Testing System reset by software trigger...   ");
        WDOG_TriggerSystemSoftwareReset(DEMO_WDOG_BASE);
    }

    /* If system reset from software trigger, testing the timeout reset. */
    if (resetFlag & kWDOG_SoftwareResetFlag)
    {
        PRINTF("\r\n- 2.Testing system reset by WDOG timeout.\r\n");
        /*
         * wdogConfig->enableWdog = true;
         * wdogConfig->workMode.enableWait = true;
         * wdogConfig->workMode.enableStop = false;
         * wdogConfig->workMode.enableDebug = false;
         * wdogConfig->enableInterrupt = false;
         * wdogConfig->enablePowerdown = false;
         * wdogConfig->resetExtension = flase;
         * wdogConfig->timeoutValue = 0xFFU;
         * wdogConfig->interruptTimeValue = 0x04u;
         */
        WDOG_GetDefaultConfig(&config);
        config.timeoutValue = 0xFU; /* Timeout value is (0xF + 1)/2 = 8 sec. */
        WDOG_Init(DEMO_WDOG_BASE, &config);
        PRINTF("--- wdog Init done---\r\n");

        /* without feed watch dog, wait until timeout. */
        while (1)
        {
        }
    }

    /* If system reset from WDOG timeout, testing the refresh function using interrupt. */
    if (resetFlag & kWDOG_TimeoutResetFlag)
    {
#endif
        PRINTF("\r\n- 3.Test the WDOG refresh function by using interrupt.\r\n");
        /*
         * wdogConfig->enableWdog = true;
         * wdogConfig->workMode.enableWait = true;
         * wdogConfig->workMode.enableStop = false;
         * wdogConfig->workMode.enableDebug = false;
         * wdogConfig->enableInterrupt = false;
         * wdogConfig->enablePowerdown = false;
         * wdogConfig->resetExtension = flase;
         * wdogConfig->timeoutValue = 0xFFU;
         * wdogConfig->interruptTimeValue = 0x04u;
         */
        WDOG_GetDefaultConfig(&config);
        config.timeoutValue       = 0xFU; /* Timeout value is (0xF+1)/2 = 8 sec. */
        config.enableInterrupt    = true;
        config.interruptTimeValue = 0x4U; /* Interrupt occurred (0x4)/2 = 2 sec before WDOG timeout. */
        WDOG_Init(DEMO_WDOG_BASE, &config);

        PRINTF("--- wdog Init done---\r\n");

#if (!(defined(EXAMPLE_DISABLE_WDOG_RESET_FUNCTION) && EXAMPLE_DISABLE_WDOG_RESET_FUNCTION))
    }
#endif

    while (1)
    {
        /* User can feed WDG in their main thread. */
        WDOG_Refresh(DEMO_WDOG_BASE);
        PRINTF(" \r\nWDOG has be refreshed!");

        /* Delay. */
        delay(SystemCoreClock);
    }
}
