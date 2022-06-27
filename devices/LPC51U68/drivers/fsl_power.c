/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, 2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_power.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Initialize BOD, including enabling/disabling BOD interrupt, enabling/disabling BOD reset, setting BOD
 * interrupt level, and reset level.
 *
 * param bodConfig Pointer the the structure  power_bod_config_t.
 */
void POWER_InitBod(const power_bod_config_t *bodConfig)
{
    assert(bodConfig != NULL);

    uint32_t tmp32 = 0UL;

    tmp32 = SYSCON->BODCTRL;

    tmp32 &= ~(SYSCON_BODCTRL_BODRSTLEV_MASK | SYSCON_BODCTRL_BODRSTENA_MASK | SYSCON_BODCTRL_BODINTLEV_MASK |
               SYSCON_BODCTRL_BODINTENA_MASK | SYSCON_BODCTRL_BODRSTSTAT_MASK | SYSCON_BODCTRL_BODINTSTAT_MASK);

    tmp32 |= SYSCON_BODCTRL_BODRSTLEV(bodConfig->resetLevel) | SYSCON_BODCTRL_BODRSTENA(bodConfig->enableReset) |
             SYSCON_BODCTRL_BODINTLEV(bodConfig->interruptLevel) | SYSCON_BODCTRL_BODINTENA(bodConfig->enableInterrupt);
    SYSCON->BODCTRL = tmp32;
}

/*!
 * brief Get default BOD configuration, including enabling/disabling BOD interrupt, enabling/disabling BOD reset,
 * setting BOD interrupt level, and reset level.
 *
 * param bodConfig Pointer the the structure power_bod_config_t.
 */
void POWER_GetDefaultBodConfig(power_bod_config_t *bodConfig)
{
    assert(bodConfig != NULL);

    bodConfig->enableReset     = true;
    bodConfig->resetLevel      = kBod_ResetLevel0;
    bodConfig->enableInterrupt = false;
    bodConfig->interruptLevel  = kBod_InterruptLevel0;
}
