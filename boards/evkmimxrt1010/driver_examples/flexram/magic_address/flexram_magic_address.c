/*
 * Copyright 2019 NXP
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
#define APP_FLEXRAM_OCRAM_START_ADDR 0x20200000
#define APP_FLEXRAM_OCRAM_END_ADDR   0x20210000
#define APP_FLEXRAM_OCRAM_MAGIC_ADDR 0x202000a8

#define APP_FLEXRAM_IRQ_HANDLER FLEXRAM_IRQHandler

/* OCRAM relocate definition */
#define APP_OCRAM_SIZE (128 * 1024U)

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
 * @param base FLEXRAM base address.
 */
static void OCRAM_Access(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool s_flexram_ocram_magic_addr_match   = false;
static volatile bool s_flexram_ocram_access_error_match = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void APP_FLEXRAM_IRQ_HANDLER(void)
{
    uint32_t intStatus;

    intStatus = FLEXRAM_GetInterruptStatus(APP_FLEXRAM);
    FLEXRAM_ClearInterruptStatus(APP_FLEXRAM, intStatus);

    if (intStatus & kFLEXRAM_OCRAMAccessError)
    {
        s_flexram_ocram_access_error_match = true;
    }

    if (intStatus & kFLEXRAM_OCRAMMagicAddrMatch)
    {
        s_flexram_ocram_magic_addr_match = true;
    }
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

    PRINTF("\r\nFLEXRAM ram magic address example.\r\n");

    /* Enable IRQ */
    EnableIRQ(APP_FLEXRAM_IRQ);
    /* Init flexram */
    FLEXRAM_Init(APP_FLEXRAM);
    /* Test OCRAM access*/
    OCRAM_Access();

    PRINTF("\r\nFLEXRAM ram magic address example finish.\r\n");

    while (1)
    {
    }
}

static void OCRAM_Access(void)
{
    uint8_t *ocramAddr = (uint8_t *)APP_FLEXRAM_OCRAM_START_ADDR;

    /* Enable FLEXRAM OCRAM access error interrupt and OCRAM magic address match interrupt */
    FLEXRAM_EnableInterruptSignal(APP_FLEXRAM, kFLEXRAM_OCRAMAccessError | kFLEXRAM_OCRAMMagicAddrMatch);
    /* config ocram magic address
     * When write access hits magic address, interrupt will be generated.
     */
    FLEXRAM_SetOCRAMMagicAddr(APP_FLEXRAM, (uint16_t)APP_FLEXRAM_OCRAM_MAGIC_ADDR, kFLEXRAM_Write);

    for (;;)
    {
        /* OCRAM write access */
        *ocramAddr = 0xCCU;
        /* Synchronizes the execution stream with memory accesses */
        __DSB();
        __ISB();

#if APP_USING_CACHE
        DCACHE_CleanByRange((uint32_t)ocramAddr, sizeof(uint8_t));
#endif

        /* Check ocram magic addr match event */
        if (ocramAddr == (uint8_t *)APP_FLEXRAM_OCRAM_MAGIC_ADDR)
        {
            while (s_flexram_ocram_magic_addr_match == false)
            {
            }
            PRINTF("\r\nOCRAM Magic address 0x%x match.\r\n", ocramAddr);

            s_flexram_ocram_magic_addr_match = false;
        }

        /* Check ocram access error event */
        if (ocramAddr == (uint8_t *)APP_FLEXRAM_OCRAM_END_ADDR)
        {
            while (s_flexram_ocram_access_error_match == false)
            {
            }
            PRINTF("\r\nOCRAM access to 0x%x boundary.\r\n", ocramAddr);
            break;
        }

        ocramAddr++;
    }
}
