/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef SM_POWER_H_
#define SM_POWER_H_

#include "fsl_common.h"
#include "sm_platform.h"
#include "scmi_power.h"

/*******************************************************************************
 * definition
 ******************************************************************************/
typedef struct
{
    uint32_t channel;
    uint32_t domain_id;
    uint32_t flag;
    uint32_t power_st;
} sm_power_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void SM_POWER_SetState(sm_power_t *sm_power);
uint32_t SM_POWER_GetState(sm_power_t *sm_power);

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* SM_POWER_H_ */
