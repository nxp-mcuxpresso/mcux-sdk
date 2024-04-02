/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SM_CLOCK_H_
#define SM_CLOCK_H_

#include "fsl_common.h"
#include "scmi_clock.h"
#include "sm_platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SM_CLOCK_RATE_MASK 0xFFFFFFFFU

typedef struct
{
    uint32_t channel;    /* channel id: SCMI_A2P, SCMI_NOTIRY, SCMI_P2A, */
    uint32_t rateu;
    uint32_t ratel;
    uint32_t clk_id;     /* clock device id */
    uint32_t pclk_id;    /* parent clock device id */
    uint32_t div;        /* clock divider */
    uint32_t attributes; /* clock attributes */
    uint32_t oem_config_val;
    uint32_t flags;
} sm_clock_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void SM_CLOCK_SetRootClock(sm_clock_t *sm_clk);
void SM_CLOCK_SetPllClock(sm_clock_t *sm_clk);
void SM_CLOCK_EnableRootClock(sm_clock_t *sm_clk);

uint64_t SM_CLOCK_GetIpFreq(sm_clock_t *sm_clk);
uint64_t SM_CLOCK_GetSourceFreq(sm_clock_t *sm_clk);

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* SM_CLOCK_H_ */
