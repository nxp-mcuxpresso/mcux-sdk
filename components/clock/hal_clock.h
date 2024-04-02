/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HAL_CLOCK_H_
#define HAL_CLOCK_H_

#include "hal_clock_platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
extern volatile uint64_t g_halClkFreq[HAL_CLOCK_PLATFORM_MAX_ID];

/* clock round options(Currently the enum is only used by System Manager Agent) */
typedef enum
{
    hal_clk_round_down = 0,
    hal_clk_round_up   = 1,
    hal_clk_round_auto = 2
} hal_clk_rnd_opt_e;

typedef struct
{
    hal_clk_id_e clk_id;             /* clock device id */
    hal_clk_id_e pclk_id;            /* parent clock device id */
    uint32_t div;                    /* clock divider */
    bool enable_clk;                 /* true: enable clock; false: disable clock */
    hal_clk_rnd_opt_e clk_round_opt; /* clock round options */
    uint32_t rateu;                   /* PLL clock Rate upper */
    uint32_t ratel;                   /* PLL clock Rate lower */
} hal_clk_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void HAL_ClockSetRootClk(hal_clk_t *hal_clk);
void HAL_ClockSetPllClk(hal_clk_t *hal_clk);
void HAL_ClockEnableRootClk(hal_clk_t *hal_clk);

uint64_t HAL_ClockGetIpFreq(hal_clk_id_e clk_id);

uint64_t HAL_ClockGetFreq(hal_clk_id_e clk_id);
#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* HAL_CLOCK_H_ */
