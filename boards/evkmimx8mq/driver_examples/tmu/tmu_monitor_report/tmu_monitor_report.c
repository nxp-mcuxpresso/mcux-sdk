/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_tmu.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_TMU_BASE               TMU
#define DEMO_TMU_IMMEDIATE_THRESOLD 0U
#define DEMO_TMU_INTERVAL_VALUE     8U
#define DEMO_TMU_IRQ                TEMPMON_IRQn
#define DEMO_TMU_IRQ_HANDLER_FUNC   TEMPMON_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile tmu_interrupt_status_t g_tmuInterruptStausStruct;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief TMU ISR.
 */
void DEMO_TMU_IRQ_HANDLER_FUNC(void)
{
    uint32_t temp;

    TMU_GetInterruptStatusFlags(DEMO_TMU_BASE, (tmu_interrupt_status_t *)&g_tmuInterruptStausStruct);
    TMU_ClearInterruptStatusFlags(DEMO_TMU_BASE, g_tmuInterruptStausStruct.interruptDetectMask);
    if (0U != (g_tmuInterruptStausStruct.interruptDetectMask & kTMU_ImmediateTemperatureStatusFlags))
    {
        /* For site0. */
        if (0U != (g_tmuInterruptStausStruct.immediateInterruptsSiteMask & kTMU_MonitorSite0))
        {
            TMU_GetImmediateTemperature(TMU, 0U, &temp);
            PRINTF("site 0 immediate temperature is too high. %d celsius degree\r\n", temp);
        }
        /* For site1. */
        if (0U != (g_tmuInterruptStausStruct.immediateInterruptsSiteMask & kTMU_MonitorSite1))
        {
            TMU_GetImmediateTemperature(TMU, 1U, &temp);
            PRINTF("site 1 immediate temperature is too high. %d celsius degree\r\n", temp);
        }
    }
    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    tmu_config_t k_tmuConfig;
    tmu_thresold_config_t k_tmuThresoldConfig;

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    PRINTF("TMU monitor report example.\r\n");

    /* Initialize the TMU mode. */
    k_tmuConfig.monitorInterval = DEMO_TMU_INTERVAL_VALUE;
    k_tmuConfig.monitorSiteSelection =
        kTMU_MonitorSite0 | kTMU_MonitorSite1; /* Monitor temperature of site 0 and site 1. */
    k_tmuConfig.averageLPF = kTMU_AverageLowPassFilter1_0;
    TMU_Init(DEMO_TMU_BASE, &k_tmuConfig);

    /* Set the temperature threshold. */
    k_tmuThresoldConfig.immediateThresoldEnable       = true;
    k_tmuThresoldConfig.AverageThresoldEnable         = false;
    k_tmuThresoldConfig.AverageCriticalThresoldEnable = false;
    k_tmuThresoldConfig.immediateThresoldValue        = DEMO_TMU_IMMEDIATE_THRESOLD;
    k_tmuThresoldConfig.averageThresoldValue          = 0U;
    k_tmuThresoldConfig.averageCriticalThresoldValue  = 0U;
    TMU_SetHighTemperatureThresold(DEMO_TMU_BASE, &k_tmuThresoldConfig);

    /* Enable the Immediate temperature threshold exceeded interrupt. */
    TMU_EnableInterrupts(DEMO_TMU_BASE, kTMU_ImmediateTemperatureInterruptEnable);
    EnableIRQ(DEMO_TMU_IRQ);

    /* Enable the monitor mode. */
    TMU_Enable(DEMO_TMU_BASE, true);

    while (true)
    {
    }
}
