/*
 * Copyright 2023 NXP
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

static CCM_Type *ccm_base = CCM_CTRL;

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

void CLOCK_Init(CCM_Type *regBase)
{
	ccm_base = regBase;
}

void CLOCK_SetRootClockMux(clock_root_t root, uint8_t src)
{
    assert(src < 8U);
    ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW =
        (ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & ~(CCM_CLOCK_ROOT_MUX_MASK)) | CCM_CLOCK_ROOT_MUX(src);
    __DSB();
    __ISB();
}

uint32_t CLOCK_GetRootClockMux(clock_root_t root)
{
	return (ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & CCM_CLOCK_ROOT_MUX_MASK) >> CCM_CLOCK_ROOT_MUX_SHIFT;
}

void CLOCK_SetRootClockDiv(clock_root_t root, uint8_t div)
{
    assert(div);
    ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW =
        (ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & ~CCM_CLOCK_ROOT_DIV_MASK) |
	CCM_CLOCK_ROOT_DIV((uint32_t)div - 1UL);
    __DSB();
    __ISB();
}

uint32_t CLOCK_GetRootClockDiv(clock_root_t root)
{
    return ((ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & CCM_CLOCK_ROOT_DIV_MASK) >> CCM_CLOCK_ROOT_DIV_SHIFT) +
    1UL;
}

void CLOCK_PowerOffRootClock(clock_root_t root)
{
    if (0UL == (ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW & CCM_CLOCK_ROOT_OFF_MASK))
    {
        ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.SET = CCM_CLOCK_ROOT_OFF_MASK;
        __DSB();
        __ISB();
    }
}

void CLOCK_PowerOnRootClock(clock_root_t root)
{
    ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.CLR = CCM_CLOCK_ROOT_OFF_MASK;
    __DSB();
    __ISB();
}

void CLOCK_SetRootClock(clock_root_t root, const clock_root_config_t *config)
{
    assert(config);
    ccm_base->CLOCK_ROOT[root].CLOCK_ROOT_CONTROL.RW = CCM_CLOCK_ROOT_MUX(config->mux) |
                                                       CCM_CLOCK_ROOT_DIV((uint32_t)config->div - 1UL) |
						       (config->clockOff ? CCM_CLOCK_ROOT_OFF(config->clockOff) : 0UL);
    __DSB();
    __ISB();
}

void CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    if (((uint32_t)value & CCM_LPCG_DIRECT_ON_MASK) != (ccm_base->LPCG[name].DIRECT & CCM_LPCG_DIRECT_ON_MASK))
    {
        ccm_base->LPCG[name].DIRECT = ((uint32_t)value & CCM_LPCG_DIRECT_ON_MASK);
	__DSB();
	__ISB();
    }
}
