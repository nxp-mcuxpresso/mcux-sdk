/*
 * Copyright 2021 ~ 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_vbat.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.vbat"
#endif

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
 * brief Configure internal 16kHz free running oscillator, including enabel FRO16k, gate FRO16k output.
 *
 * param base VBAT peripheral base address.
 * param config Pointer to vbat_fro16k_config_t structure.
 */
void VBAT_ConfigFRO16k(VBAT_Type *base, const vbat_fro16k_config_t *config)
{
    assert(config != NULL);

    VBAT_EnableFRO16k(base, config->enableFRO16k);

    if (config->enableFRO16k)
    {
        VBAT_UngateFRO16k(base, true);
    }
    else
    {
        VBAT_UngateFRO16k(base, false);
    }
}

/*!
 * brief Enable/disable Bandgap.
 *
 * note The FRO16K must be enabled before enableing the bandgap.
 * note This setting can be locked by VBAT_LockLdoRamSettings() function.
 *
 * param base VBAT peripheral base address.
 * param enable Used to enable/disable bandgap.
 *      - \b true Enable the bandgap.
 *      - \b false Disable the bandgap.
 *
 * retval kStatus_Success Success to enable/disable the bandgap.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to enable the bandgap due to FRO16k is not enabled previously.
 */
status_t VBAT_EnableBandgap(VBAT_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        if (VBAT_CheckFRO16kEnabled(base))
        {
            base->LDOCTLA |= VBAT_LDOCTLA_BG_EN_MASK;
        }
        else
        {
            /* FRO16K must be enabled before enabling the Bandgap. */
            status = kStatus_VBAT_Fro16kNotEnabled;
        }
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_BG_EN_MASK;
    }

    return status;
}

/*!
 * brief Enable/disable Backup RAM Regulator(RAM_LDO).
 *
 * note This setting can be locked by VBAT_LockLdoRamSettings() function.
 *
 * param base VBAT peripheral base address.
 * param enable Used to enable/disable RAM_LDO.
 *          - \b true Enable backup SRAM regulator.
 *          - \b false Disable backup SRAM regulator.
 *
 * retval kStatusSuccess Success to enable/disable backup SRAM regulator.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to enable backup SRAM regulator due to FRO16k is not enabled previously.
 * retval kStatus_VBAT_BandgapNotEnabled Fail to enable backup SRAM regulator due to the bandgap is not enabled
 * previously.
 */
status_t VBAT_EnableBackupSRAMRegulator(VBAT_Type *base, bool enable)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        if (VBAT_CheckFRO16kEnabled(base))
        {
            if (VBAT_CheckBandgapEnabled(base))
            {
                base->LDOCTLA |= VBAT_LDOCTLA_LDO_EN_MASK;
                while ((base->STATUSA & VBAT_STATUSA_LDO_RDY_MASK) == 0UL)
                {
                }
            }
            else
            {
                /* The bandgap must be enabled previously. */
                status = kStatus_VBAT_BandgapNotEnabled;
            }
        }
        else
        {
            /* FRO16k must be enabled previously. */
            status = kStatus_VBAT_Fro16kNotEnabled;
        }
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_LDO_EN_MASK;
    }

    return status;
}

/*!
 * brief Switch the SRAM to be powered by VBAT.
 *
 * param base VBAT peripheral base address.
 *
 * retval kStatusSuccess Success to Switch SRAM powered by VBAT.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to switch SRAM powered by VBAT due to FRO16K not enabled previously.
 */
status_t VBAT_SwitchSRAMPowerByVBAT(VBAT_Type *base)
{
    status_t status = kStatus_Success;

    status = VBAT_EnableBandgap(base, true);

    if (status == kStatus_Success)
    {
        VBAT_EnableBandgapRefreshMode(base, true);
        (void)VBAT_EnableBackupSRAMRegulator(base, true);

        /* Isolate the SRAM array */
        base->LDORAMC |= VBAT_LDORAMC_ISO_MASK;
        /* Switch the supply to VBAT LDO. */
        base->LDORAMC |= VBAT_LDORAMC_SWI_MASK;
    }

    return status;
}

/*!
 * brief Enable/disable Bandgap timer.
 *
 * note The bandgap timer is available when the bandgap is enabled and are clocked by the FRO16k.
 *
 * param base VBAT peripheral base address.
 * param enable Used to enable/disable bandgap timer.
 * param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of vbat_bandgap_timer_id_t.
 *
 * retval kStatus_Success Success to enable/disable selected bandgap timer.
 * retval kStatus_VBAT_Fro16kNotEnabled Fail to enable/disable selected bandgap timer due to FRO16k not enabled
 * previously. retval kStatus_VBAT_BandgapNotEnabled Fail to enable/disable selected bandgap timer due to bandgap not
 * enabled previously.
 */
status_t VBAT_EnableBandgapTimer(VBAT_Type *base, bool enable, uint8_t timerIdMask)
{
    status_t status = kStatus_Success;

    if (enable)
    {
        if (VBAT_CheckFRO16kEnabled(base))
        {
            if (VBAT_CheckBandgapEnabled(base))
            {
                if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer0) != 0U)
                {
                    base->LDOTIMER0 |= VBAT_LDOTIMER0_TIMEN_MASK;
                }

                if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer1) != 0U)
                {
                    base->LDOTIMER1 |= VBAT_LDOTIMER1_TIMEN_MASK;
                }
            }
            else
            {
                /* Bandgap must be enabled previously. */
                status = kStatus_VBAT_BandgapNotEnabled;
            }
        }
        else
        {
            /* FRO16K must be enabled previously. */
            status = kStatus_VBAT_Fro16kNotEnabled;
        }
    }
    else
    {
        if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer0) != 0U)
        {
            base->LDOTIMER0 &= ~VBAT_LDOTIMER0_TIMEN_MASK;
        }

        if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer1) != 0U)
        {
            base->LDOTIMER1 &= ~VBAT_LDOTIMER1_TIMEN_MASK;
        }
    }

    return status;
}

/*!
 * brief Set bandgap timer timeout value.
 *
 * param base VBAT peripheral base address.
 * param timeoutPeriod Bandgap timer timeout value, please refer to vbat_bandgap_timer_timeout_period_t.
 * param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of vbat_bandgap_timer_id_t.
 */
void VBAT_SetBandgapTimerTimeoutValue(VBAT_Type *base,
                                      vbat_bandgap_timer_timeout_period_t timeoutPeriod,
                                      uint8_t timerIdMask)
{
    bool timerEnabled = false;

    if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer0) != 0U)
    {
        timerEnabled = ((base->LDOTIMER0 & VBAT_LDOTIMER0_TIMEN_MASK) != 0UL) ? true : false;

        if (timerEnabled)
        {
            base->LDOTIMER0 &= ~VBAT_LDOTIMER0_TIMEN_MASK;
        }

        base->LDOTIMER0 = ((base->LDOTIMER0 & (~VBAT_LDOTIMER0_TIMCFG_MASK)) | VBAT_LDOTIMER0_TIMCFG(timeoutPeriod));

        if (timerEnabled)
        {
            base->LDOTIMER0 |= VBAT_LDOTIMER0_TIMEN_MASK;
        }
    }

    if ((timerIdMask & (uint8_t)kVBAT_BandgapTimer1) != 0U)
    {
        timerEnabled = ((base->LDOTIMER1 & VBAT_LDOTIMER1_TIMEN_MASK) != 0UL) ? true : false;

        if (timerEnabled)
        {
            base->LDOTIMER1 &= ~VBAT_LDOTIMER1_TIMEN_MASK;
        }

        base->LDOTIMER1 = ((base->LDOTIMER1 & (~VBAT_LDOTIMER1_TIMCFG_MASK)) | VBAT_LDOTIMER1_TIMCFG(timeoutPeriod));

        if (timerEnabled)
        {
            base->LDOTIMER1 |= VBAT_LDOTIMER1_TIMEN_MASK;
        }
    }
}
