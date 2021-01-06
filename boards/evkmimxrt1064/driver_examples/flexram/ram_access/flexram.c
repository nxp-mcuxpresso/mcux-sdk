/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_flexram.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_FLEXRAM                  FLEXRAM
#define APP_FLEXRAM_IRQ              FLEXRAM_IRQn
#define APP_FLEXRAM_OCRAM_START_ADDR 0x20280000
#define APP_FLEXRAM_OCRAM_MAGIC_ADDR 0x202800a8
#define APP_FLEXRAM_IRQ_HANDLER      FLEXRAM_IRQHandler

/*
 * If cache is enabled, this example should maintain the cache to make sure
 * CPU core accesses the memory, not cache only.
 */
#define APP_USING_CACHE 1


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief ocram access function.
 *
 */
static void OCRAM_Access(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static bool s_flexram_ocram_access_error_match = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void APP_FLEXRAM_IRQ_HANDLER(void)
{
    if (FLEXRAM_GetInterruptStatus(APP_FLEXRAM) & kFLEXRAM_OCRAMAccessError)
    {
        FLEXRAM_ClearInterruptStatus(APP_FLEXRAM, kFLEXRAM_OCRAMAccessError);
        s_flexram_ocram_access_error_match = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
#if APP_USING_CACHE
#include "fsl_cache.h"
#endif

int main(void)
{
    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nFLEXRAM ram access driver example.\r\n");

    /* enable IRQ */
    EnableIRQ(APP_FLEXRAM_IRQ);
    /* init flexram */
    FLEXRAM_Init(APP_FLEXRAM);
    /* access the default ocram */
    OCRAM_Access();

    PRINTF("\r\nFLEXRAM ram access driver example finish.\r\n");

    while (1)
    {
    }
}

static void OCRAM_Access(void)
{
    uint8_t *ocramAddr = (uint8_t *)APP_FLEXRAM_OCRAM_START_ADDR;

    /* enable FLEXRAM OCRAM access error interrupt and OCRAM magic address match interrupt */
    FLEXRAM_EnableInterruptSignal(APP_FLEXRAM, kFLEXRAM_OCRAMAccessError);

    for (;;)
    {
        *ocramAddr = 0xCC;
        /* Synchronizes the execution stream with memory accesses */
        __DSB();
        __ISB();

#if APP_USING_CACHE
        DCACHE_CleanByRange((uint32_t)ocramAddr, sizeof(uint8_t));
#endif

        /* check ocram access error event */
        if (s_flexram_ocram_access_error_match)
        {
            PRINTF("\r\nOCRAM access 0x%x to boundary.\r\n", (uint32_t)(ocramAddr));
            s_flexram_ocram_access_error_match = false;
            break;
        }
        ocramAddr++;
    }
}
