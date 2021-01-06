/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_snvs_lp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_LOOP 5 /* How many times the MC increases in this example. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_CheckResult(bool condition, char *log);
static void DEMO_PrintUINT64(uint64_t value);

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
    uint64_t cnt, cnt_old;

    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Init SNVS */
    SNVS_LP_Init(SNVS);

    PRINTF("SNVS LP MC example:\r\n");

    SNVS_LP_EnableMonotonicCounter(SNVS, true);

    cnt = SNVS_LP_GetMonotonicCounter(SNVS);

    for (uint32_t i = 0; i < DEMO_LOOP; i++)
    {
        cnt_old = cnt;

        SNVS_LP_IncreaseMonotonicCounter(SNVS);
        cnt = SNVS_LP_GetMonotonicCounter(SNVS);

        PRINTF("Current Monotonic Counter value is ");
        DEMO_PrintUINT64(cnt);
        PRINTF("\r\n");

        DEMO_CheckResult(cnt_old + 1 == cnt, "MC not increased");
    }

    PRINTF("SNVS LP MC example finished successfully\r\n");
    while (1)
        ;
}

static void DEMO_CheckResult(bool condition, char *log)
{
    if (!condition)
    {
        PRINTF("FAIL: %s\r\n", log);
        while (1)
            ;
    }
}

static void DEMO_PrintUINT64(uint64_t value)
{
    uint32_t val_lsb = (uint32_t)value;
    uint32_t val_msb = (uint64_t)(value >> 32UL);

    PRINTF("0x%08X%08X", val_msb, val_lsb);
}
