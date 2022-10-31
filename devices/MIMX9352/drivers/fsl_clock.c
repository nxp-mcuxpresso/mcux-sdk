/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

volatile uint32_t g_clockSourceFreq[kCLOCK_Ext + 1];

uint32_t CLOCK_GetIpFreq(clock_root_t name)
{
    clock_name_t clock;
    uint32_t mux;
    uint32_t div;

    mux = CLOCK_GetRootClockMux(name);
    div = CLOCK_GetRootClockDiv(name);

    clock = CLOCK_GetRootClockSource(name, mux);
    assert(clock <= kCLOCK_Ext);

    return g_clockSourceFreq[clock] / div;
}
