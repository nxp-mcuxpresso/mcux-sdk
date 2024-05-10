/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_soc_src.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.soc_src"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_MASK (0x1U)
#define SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_CONFIG(resetSource, resetMode) \
    ((uint32_t)(resetMode) << (uint32_t)(resetSource))

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
 * brief Release related core reset operation.
 *
 * The core reset will be held until boot core to release it.
 *
 * param base SRC peripheral base address.
 * param coreName The name of the reset core to be released.
 */
void SRC_ReleaseCM7(SRC_GENERAL_Type *base)
{
    if ((base->SCR & SRC_GENERAL_SCR_BT_RELEASE_M7_MASK) == 0UL)
    {
        base->SCR |= SRC_GENERAL_SCR_BT_RELEASE_M7_MASK;
    }
}

/*!
 * brief Sets the reset mode of global system reset source.
 *
 * This function sets the selected mode of the input global system reset sources. This function will return as soon as
 * the reset if finished.
 *
 * param base SRC peripheral base address.
 * param resetSource The global system reset source. See @ref src_global_system_reset_source_t for more details.
 * param resetMode The reset mode of each reset source. See @ref src_global_system_reset_mode_t for more details.
 */
void SRC_SetGlobalSystemResetMode(SRC_GENERAL_Type *base, src_reset_source_t resetSource, src_reset_mode_t resetMode)
{
    uint32_t regValue;

    regValue = base->SRMASK;
    regValue &= ~SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_CONFIG(resetSource, SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_MASK);
    regValue |= SRC_GLOBAL_SYSTEM_RESET_BEHAVIOR_CONFIG(resetSource, resetMode);

    base->SRMASK = regValue;
}

/*!
 * brief Set software control step for slice power on/off sequence.
 *
 * param base SRC peripheral base address.
 * param step Slice power on/off sequence step. See @ref src_power_ctrl_step_t for more details.
 */
void SRC_SLICE_SoftwareControl(SRC_MIX_SLICE_Type *base, src_power_ctrl_step_t step)
{
    base->AUTHEN_CTRL &= ~SRC_MIX_SLICE_AUTHEN_CTRL_LPM_MODE_MASK;

    switch (step)
    {
        case kSRC_PDN_EdgelockHandshake:
            base->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_EDGELOCK_HDSK_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_EDGELOCK_HDSK_STAT_MASK) !=
                   SRC_MIX_SLICE_FUNC_STAT_EDGELOCK_HDSK_STAT_MASK)
            {
            }
            break;
        case kSRC_PDN_IsolationOn:
            base->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_ISO_ON_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_ISO_STAT_MASK) != SRC_MIX_SLICE_FUNC_STAT_ISO_STAT_MASK)
            {
            }
            break;
        case kSRC_PDN_ResetAssert:
            base->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_RST_STAT_MASK) != 0UL)
            {
            }
            break;
        case kSRC_PDN_PowerSwitchOff:
            base->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_PSW_OFF_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_PSW_STAT_MASK) != SRC_MIX_SLICE_FUNC_STAT_PSW_STAT_MASK)
            {
            }
            break;
        case kSRC_PUP_PowerSwitchOn:
            base->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_PSW_OFF_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_PSW_STAT_MASK) != 0UL)
            {
            }
            break;
        case kSRC_PUP_ResetRelease:
            base->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_RST_STAT_MASK) != SRC_MIX_SLICE_FUNC_STAT_RST_STAT_MASK)
            {
            }
            break;
        case kSRC_PUP_IsolationOff:
            base->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_ISO_ON_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_ISO_STAT_MASK) != 0UL)
            {
            }
            break;
        case kSRC_PUP_EdgeLockHandshake:
            base->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_EDGELOCK_HDSK_SOFT_MASK;
            while ((base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_EDGELOCK_HDSK_STAT_MASK) != 0UL)
            {
            }
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Power on/off slice.
 *
 * param base SRC peripheral base address.
 * param powerOff Used to trigger slice power on/off sequence.
 *			   - \b true Trigger a power off sequence.
 *			   - \b false Trigger a power on sequence.
 */
void SRC_SLICE_PowerDown(SRC_MIX_SLICE_Type *base, bool powerOff)
{
    base->AUTHEN_CTRL &= ~SRC_MIX_SLICE_AUTHEN_CTRL_LPM_MODE_MASK;

    if (powerOff)
    {
        base->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_PDN_SOFT_MASK;
    }
    else
    {
        base->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_PDN_SOFT_MASK;
    }
}

void SRC_SLICE_ControlByCpuLowPowerMode(SRC_MIX_SLICE_Type *base, uint32_t domainMap, src_power_level_t level)
{
    uint32_t domainIndex            = 0UL;
    uint32_t tmp32                  = 0UL;
    uint32_t regIndex               = 0UL;
    volatile uint32_t *ptrMemLpmReg = NULL;

    /* Change power level for each domain. */
    domainMap &= 0xFFFFU;
    ptrMemLpmReg = &(base->LPM_SETTING_1);
    for (regIndex = 0UL; regIndex < 2UL; regIndex++)
    {
        ptrMemLpmReg += regIndex;
        tmp32 = *ptrMemLpmReg;
        for (domainIndex = 0UL; domainIndex < 8UL; domainIndex++)
        {
            if (0UL != (domainMap & (1UL << ((regIndex * 8UL) + domainIndex))))
            {
                tmp32 &= ~((uint32_t)SRC_MIX_SLICE_LPM_SETTING_1_LPM_SETTING_D0_MASK << (domainIndex * 4U));
                tmp32 |= ((uint32_t)SRC_MIX_SLICE_LPM_SETTING_1_LPM_SETTING_D0(level) << (domainIndex * 4U));
            }
        }
        *ptrMemLpmReg = tmp32;
    }

    /* Set control mode to CPU low power mode. */
    base->AUTHEN_CTRL |= SRC_MIX_SLICE_AUTHEN_CTRL_LPM_MODE_MASK;
}
