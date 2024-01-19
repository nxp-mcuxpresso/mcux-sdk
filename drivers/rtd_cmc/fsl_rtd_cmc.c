/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_rtd_cmc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rtd_cmc"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Sets clock mode.
 *
 * This function configs the amount of clock gating when the core asserts
 * Sleeping due to WFI, WFE or SLEEPONEXIT.
 *
 * param base CMC peripheral base address.
 * param mode System clock mode.
 */
void RTDCMC_SetClockMode(CMC_Type *base, cmc_clock_mode_t mode)
{
    uint32_t reg;

    reg = base->CKCTRL;
    reg &= ~CMC_CKCTRL_CKMODE_MASK;
    reg |= CMC_CKCTRL_CKMODE((mode));
    base->CKCTRL = reg;
}

/*!
 * brief Configures all power mode protection settings.
 *
 * This function configures the power mode protection settings for
 * supported power modes. This should be done before setting the lowPower mode
 * for each power doamin.
 *
 * The allowed lowpower modes are passed as bit map. For example, to allow
 * Sleep and DeepSleep, use CMC_SetPowerModeProtection(CMC_base, kCMC_AllowSleepMode|kCMC_AllowDeepSleepMode).
 * To allow all low power modes, use CMC_SetPowerModeProtection(CMC_base, kCMC_AllowAllLowPowerModes).
 *
 * param base CMC peripheral base address.
 * param allowedModes Bitmaps of the allowed power modes.
 */
void RTDCMC_SetPowerModeProtection(CMC_Type *base, uint8_t allowedModes)
{
    uint32_t reg;

    reg = base->RTD_PMPROT;
    reg &= ~(CMC_RTD_PMPROT_AS_MASK | CMC_RTD_PMPROT_ADS_MASK | CMC_RTD_PMPROT_APD_MASK | CMC_RTD_PMPROT_ADPD_MASK |
             CMC_RTD_PMPROT_AHLD_MASK);
    reg |= allowedModes;

    base->RTD_PMPROT = reg;
}

/*!
 * brief Enter into the selected low power mode, please make sure the selected power mode has been enabled in the
 * protection level.
 *
 * param base CMC peripheral base address.
 * param lowPowerMode The desired lowPower mode. See cmc_low_power_mode_t for details.
 */
void RTDCMC_EnterLowPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode)
{
    base->RTD_PMCTRL = CMC_RTD_PMCTRL_RTD_LPMODE(lowPowerMode);

    /* Before executing WFI instruction read back the last register to
     * ensure all registers writes have completed. */
    (void)base->RTD_PMCTRL;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __DSB();
    __WFI();
    __ISB();
}
