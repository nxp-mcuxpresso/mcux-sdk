/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_config.h"
#include "hal_clock.h"
#if SM_CLOCK
#include "sm_clock.h"
#elif CCM_CLOCK
#include "fsl_clock.h"
#endif

#if SM_CLOCK && CCM_CLOCK
#error "Pls not define them as 1 at the same time in hal_config.h!!!"
#endif

volatile uint64_t g_halClkFreq[HAL_CLOCK_PLATFORM_MAX_ID] = {0ULL};

#if SM_CLOCK
void HAL_ClockSetRootClk(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = hal_clk->clk_round_opt;

    sm_clk.clk_id     = hal_clk->clk_id;
    sm_clk.pclk_id    = hal_clk->pclk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.div        = hal_clk->div;
    sm_clk.attributes = SCMI_CLOCK_CONFIG_SET_ENABLE(hal_clk->enable_clk);

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    SM_CLOCK_SetRootClock(&sm_clk);
}
void HAL_ClockEnableRootClk(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = hal_clk->clk_round_opt;

    sm_clk.clk_id     = hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.attributes = SCMI_CLOCK_CONFIG_SET_ENABLE(hal_clk->enable_clk);

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    SM_CLOCK_EnableRootClock(&sm_clk);
}

void HAL_ClockSetPllClk(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = hal_clk->clk_round_opt;

    sm_clk.clk_id     = hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.rateu       = hal_clk->rateu;
    sm_clk.ratel       = hal_clk->ratel;

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    SM_CLOCK_SetPllClock(&sm_clk);
}

uint64_t HAL_ClockGetIpFreq(hal_clk_id_e clk_id)
{
    sm_clock_t sm_clk = {0};

    if (clk_id < HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return 0UL;
    }
    sm_clk.clk_id  = (uint32_t)clk_id;
    sm_clk.channel = SM_PLATFORM_A2P;

    g_halClkFreq[clk_id] = SM_CLOCK_GetIpFreq(&sm_clk);

    return g_halClkFreq[clk_id];
}

uint64_t HAL_ClockGetFreq(hal_clk_id_e clk_id)
{
    sm_clock_t sm_clk = {0};

    sm_clk.clk_id  = (uint32_t)clk_id;
    sm_clk.channel = SM_PLATFORM_A2P;
    if (clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        g_halClkFreq[clk_id] = SM_CLOCK_GetIpFreq(&sm_clk);
    }
    else
    {
        g_halClkFreq[clk_id] = SM_CLOCK_GetSourceFreq(&sm_clk);
    }

    return g_halClkFreq[clk_id];
}
#elif CCM_CLOCK
void HAL_ClockSetRootClk(hal_clk_t *hal_clk)
{
    clock_root_t name                   = (clock_root_t)0;
    clock_root_config_t config          = {0};
    const clock_root_config_t *p_config = &config;
    uint32_t mux_id                     = 0;

    config.clockOff = !hal_clk->enable_clk;

    if (hal_clk->clk_id < HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return;
    }
    name = (clock_root_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM);
    if (hal_clk->pclk_id > HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return;
    }

    mux_id = HAL_ClockPlatformGetMuxId(hal_clk->clk_id, hal_clk->pclk_id);
    if (mux_id == HAL_CLOCK_PLATFORM_MUX_MAX_ID)
    {
        return;
    }

    config.mux = mux_id;
    config.div = hal_clk->div;

    CLOCK_SetRootClock(name, p_config);
}


void HAL_ClockSetPllClk(hal_clk_t *hal_clk)
{
}

uint64_t HAL_ClockGetIpFreq(hal_clk_id_e clk_id)
{
    clock_root_t name = (clock_root_t)(clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM);

    g_halClkFreq[clk_id] = CLOCK_GetIpFreq(name);

    return g_halClkFreq[clk_id];
}

uint64_t HAL_ClockGetFreq(hal_clk_id_e clk_id)
{
    if (clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        g_halClkFreq[clk_id] = CLOCK_GetIpFreq((clock_root_t)(clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM));
    }
    else
    {
        g_halClkFreq[clk_id] = CLOCK_GetSourceFreq((uint32_t)clk_id);
    }

    return g_halClkFreq[clk_id];
}
#else
#error "Pls define macro SM_CLOCK or CCM_CLOCK in hal_config.h.!!!"
#endif
