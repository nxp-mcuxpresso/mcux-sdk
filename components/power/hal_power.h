/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HAL_POWER_H_
#define HAL_POWER_H_

#include "fsl_common.h"
#include "hal_power_platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum
{
    hal_power_state_on    = 0,
    hal_power_state_off   = 1,
    hal_power_state_err   = 2
} hal_pwr_st_e;

typedef struct
{
    uint32_t did; /* domain ID */
    hal_pwr_st_e st; /* power state */
} hal_pwr_s_t;


/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void HAL_PowerSetState(hal_pwr_s_t *pwr_st);
hal_pwr_st_e HAL_PowerGetState(hal_pwr_s_t *pwr_st);

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* HAL_POWER_H_ */
