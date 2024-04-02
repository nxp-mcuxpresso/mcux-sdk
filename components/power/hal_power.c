/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_config.h"
#include "hal_power.h"
#if SM_POWER
#include "sm_power.h"
#elif CCMSRCGPC_POWER
#include "fsl_power.h"
#endif

#if SM_POWER && CCMSRCGPC_POWER
#error "Pls not define them as 1 at the same time in hal_config.h!!!"
#endif

#if SM_POWER
void HAL_PowerSetState(hal_pwr_s_t *pwr_st)
{
    sm_power_t sm_power = {0};

    sm_power.channel         = SM_PLATFORM_A2P;
    sm_power.domain_id        = pwr_st->did;

    if (pwr_st->st == hal_power_state_on)
    {
        sm_power.power_st = SCMI_POWER_DOMAIN_STATE_ON;
    }
    else if (pwr_st->st == hal_power_state_off)
    {
        sm_power.power_st = SCMI_POWER_DOMAIN_STATE_OFF;
    }
    else
    {
        return;
    }

    SM_POWER_SetState(&sm_power);
}

hal_pwr_st_e HAL_PowerGetState(hal_pwr_s_t *pwr_st)
{
    uint32_t power_state;
    sm_power_t sm_power = {0};

    sm_power.channel         = SM_PLATFORM_A2P;
    sm_power.domain_id        = pwr_st->did;

    power_state = SM_POWER_GetState(&sm_power);

    if (power_state == SCMI_POWER_DOMAIN_STATE_ON)
    {
        return hal_power_state_on;
    }
    else if (power_state == SCMI_POWER_DOMAIN_STATE_OFF)
    {
        return hal_power_state_off;
    }

    return hal_power_state_err;
}

#elif CCMSRCGPC_POWER
void HAL_PowerSetState(hal_pwr_s_t *pwr_st)
{
    bool power_on = false;

    if (pwr_st->st == hal_power_state_on)
    {
        power_on = true;
    }
    else if (pwr_st->st == hal_power_state_off)
    {
        power_on = false;
    }
    else
    {
        return;
    }

    //CCMSRCGPC__SRC__XSPR_NETCMIX->SLICE_SW_CTRL &= ~0x80000000;
    PWR_MixPowerSet(pwr_st->did, power_on);
}

hal_pwr_st_e HAL_PowerGetState(hal_pwr_s_t *pwr_st)
{
    hal_pwr_st_e state = hal_power_state_off;
    //while ((CCMSRCGPC__SRC__XSPR_NETCMIX->FUNC_STAT & 0x00000004) == 0x0)
    //  ;
    if (PWR_IsParentPowered(pwr_st->did) == true)
    {
        state = hal_power_state_on;
    }

    return state;
}
#else
#error "Pls define macro SM_POWER or CCMSRCGPC_POWER in hal_config.h.!!!"
#endif
