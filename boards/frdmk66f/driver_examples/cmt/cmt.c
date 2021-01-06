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
#include "fsl_cmt.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BUS_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)

#define CMT_TEST_DATA_BITS     11    /*! The data test bit numbers. */
#define CMT_DATA_MODULATE_RATE 9600  /*! The data modulation transmit rate */
#define CMT_CG_FREQUENCY       40000 /*! The carrier generator frequency */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile uint32_t g_CmtDataBitLen = 0;
volatile bool g_CmtFinish         = false;
uint32_t g_CmtModDataOneMarkCount;
uint32_t g_CmtModDataOneSpaceCount;
uint32_t g_CmtModDataZeroMarkCount;
uint32_t g_CmtModDataZeroSpaceCount;
uint32_t data = 0x875631;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Prepare the CMT modulate configuration for
 * mode - TimeMode.
 * carrier generator - 50% duty cycle, CMT_CG_FREQUENCY.
 */
void CMT_PrepareModulateConfig(cmt_modulate_config_t *modulateConfig, uint32_t busClock)
{
    uint32_t cgHighCount;
    uint32_t cgLowCount;
    uint32_t cmTotalCount;
    uint32_t cmMarkCount;
    uint32_t cmSpaceCount;
    uint32_t frequency;

    /* Prepare the cmt modulate configuration. */
    frequency = CMT_GetCMTFrequency(CMT, busClock);

    /* Get the carrier generator for 50% duty cycle. */
    cgHighCount = (frequency / CMT_CG_FREQUENCY) / 2;
    cgLowCount  = cgHighCount;
    /* Get the carrier modulator total counts.
    Set the modulate mark space count for the first transmitted data. */
    cmTotalCount = (frequency / 8) / CMT_DATA_MODULATE_RATE;
    /* LSB. */
    if (data & 0x1)
    {
        /* Data bit "1" - set the space time to min. */
        cmMarkCount  = cmTotalCount - 1;
        cmSpaceCount = 0;
    }
    else
    {
        /* Data bit "0" - set the mark time to min. */
        cmMarkCount  = 0;
        cmSpaceCount = cmTotalCount - 1;
    }
    modulateConfig->highCount1 = cgHighCount;
    modulateConfig->lowCount1  = cgLowCount;
    modulateConfig->markCount  = cmMarkCount;
    modulateConfig->spaceCount = cmSpaceCount;

    /* CMT carrier modulate mark and space set for bit 1 and bit 0. */
    g_CmtModDataOneMarkCount   = cmTotalCount - 1;
    g_CmtModDataOneSpaceCount  = 0;
    g_CmtModDataZeroMarkCount  = 0;
    g_CmtModDataZeroSpaceCount = cmTotalCount - 1;

    /* The initialized mark/space count is for the first Data. */
    g_CmtDataBitLen = 1;
}

/*!
 * @brief System default IRQ handler defined in startup code.
 *
 */
void CMT_IRQHandler(void)
{
    if (CMT_GetStatusFlags(CMT))
    {
        if (g_CmtDataBitLen <= CMT_TEST_DATA_BITS)
        {
            if (g_CmtDataBitLen == CMT_TEST_DATA_BITS)
            {
                /* Stop CG if the required data has been transmitted. */
                CMT_SetMode(CMT, kCMT_DirectIROCtl, NULL);

                CMT_DisableInterrupts(CMT, kCMT_EndOfCycleInterruptEnable);

                g_CmtFinish = true;
            }

            /* LSB. */
            if (data & ((uint32_t)0x01 << g_CmtDataBitLen))
            {
                CMT_SetModulateMarkSpace(CMT, g_CmtModDataOneMarkCount, g_CmtModDataOneSpaceCount);
            }
            else
            {
                CMT_SetModulateMarkSpace(CMT, g_CmtModDataZeroMarkCount, g_CmtModDataZeroSpaceCount);
            }
            g_CmtDataBitLen++;
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    uint32_t busClock;
    cmt_config_t config;
    cmt_modulate_config_t modulateConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nCMT Example Start.\r\n");

    busClock = BUS_CLK_FREQ;

    /*
     * config.isInterruptEnabled = false;
     * config.isIroEnabled = true;
     * config.iroPolarity = kCMT_IROActiveHigh;
     * config.divider = kCMT_SecondClkDiv1;
     */
    CMT_GetDefaultConfig(&config);
    /* Interrupt is enabled to change the modulate mark and space count. */
    config.isInterruptEnabled = true;
    CMT_Init(CMT, &config, busClock);

    /* Prepare the modulate configuration. */
    CMT_PrepareModulateConfig(&modulateConfig, busClock);

    /* Set the time mode. */
    CMT_SetMode(CMT, kCMT_TimeMode, &modulateConfig);

    while (1)
    {
        if (g_CmtFinish)
        {
            PRINTF("\r\nCMT DATA Modulate Finished.\r\n");
            PRINTF("\r\nCMT Example End.\r\n");
            g_CmtFinish = false;
        }
    }
}
