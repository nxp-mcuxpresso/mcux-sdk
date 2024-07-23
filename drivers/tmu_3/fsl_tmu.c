/*
 * Copyright 2022-2024, NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_tmu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tmu_3"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for TMU module.
 *
 * @param base TMU peripheral base address
 */
static uint32_t TMU_GetInstance(TMU_Type *base);

/*!
 * @brief Programming the sensor translation table.
 *
 * @param base TMU peripheral base address.
 */
static void TMU_SetTranslationTable(TMU_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to TMU bases for each instance. */
static TMU_Type *const s_tmuBases[] = TMU_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to TMU clocks for each instance. */
static const clock_ip_name_t s_tmuClocks[] = TMU_CLOCKS;
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t TMU_GetInstance(TMU_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_tmuBases); instance++)
    {
        if (s_tmuBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_tmuBases));

    return instance;
}

static void TMU_SetTranslationTable(TMU_Type *base)
{
    /*  programming the sensor translation table. */
    base->TTRCR[0] = TMU_TTRCR_TEMP(218U) | TMU_TTRCR_V(1U); /* Range0. */
    base->TTRCR[1] = TMU_TTRCR_TEMP(233U) | TMU_TTRCR_V(1U); /* Range1. */
    base->TTRCR[2] = TMU_TTRCR_TEMP(258U) | TMU_TTRCR_V(1U); /* Range2. */
    base->TTRCR[3] = TMU_TTRCR_TEMP(298U) | TMU_TTRCR_V(1U); /* Range3. */
    base->TTRCR[4] = TMU_TTRCR_TEMP(358U) | TMU_TTRCR_V(1U); /* Range4. */
    base->TTRCR[5] = TMU_TTRCR_TEMP(423U) | TMU_TTRCR_V(1U); /* Range5. */
    base->TTRCR[6] = TMU_TTRCR_TEMP(438U) | TMU_TTRCR_V(1U); /* Range6. */
    /* For range0. */
    base->TTCFGR = 0x000U;
    base->TSCFGR = 0x00EU;
    /* For range1. */
    base->TTCFGR = 0x001U;
    base->TSCFGR = 0x029U;
    /* For range2. */
    base->TTCFGR = 0x002U;
    base->TSCFGR = 0x056U;
    /* For range3. */
    base->TTCFGR = 0x003U;
    base->TSCFGR = 0x0A2U;
    /* For range4. */
    base->TTCFGR = 0x004U;
    base->TSCFGR = 0x116U;
    /* For range5. */
    base->TTCFGR = 0x005U;
    base->TSCFGR = 0x195U;
    /* For range6. */
    base->TTCFGR = 0x006U;
    base->TSCFGR = 0x1B2U;
}
/*!
 * brief Enable the access to TMU registers and Initialize TMU module.
 *
 * param base TMU peripheral base address.
 * param config Pointer to configuration structure. Refer to "tmu_config_t" structure.
 */
void TMU_Init(TMU_Type *base, const tmu_config_t *config)
{
    assert(NULL != base);
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable TMU clock. */
    CLOCK_EnableClock(s_tmuClocks[TMU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL. */

    /* Disable TMU monitor mode. */
    TMU_Enable(base, false);

    /* Set the sensor translation table. */
    TMU_SetTranslationTable(base);

    /* Clear interrupt relevant register. */
    TMU_ClearInterruptStatusFlags(base, (uint32_t)kTMU_ImmediateTemperatureStatusFlags |
                                            (uint32_t)kTMU_AverageTemperatureStatusFlags |
                                            (uint32_t)kTMU_AverageTemperatureCriticalStatusFlags |
                                            (uint32_t)kTMU_RisingTemperatureCriticalStatusFlags  |
                                            (uint32_t)kTMU_FallingTemperatureCriticalStatusFlags);
    /* Configure TCMCFG register. */
    base->TCMCFG |= (TMU_TCMCFG_OCM_MASK | TMU_TCMCFG_DEMA_MASK);
    base->TCMCFG &= ~TMU_TCMCFG_CLK_DIV_MASK;
    /* Configure TMR register. */
    base->TMR = TMU_TMR_ALPF(config->averageLPF);
    /* Configure TMSR register. */
    base->TMSR |= TMU_TMSR_SITE_MASK;
    /* Configure the time interval. */
    base->TMTMIR = TMU_TMTMIR_TMI(config->monitorInterval);
}

/*!
 * brief De-initialize TMU module and Disable the access to DCDC registers.
 *
 * param base TMU peripheral base address.
 */
void TMU_Deinit(TMU_Type *base)
{
    /* Disable TMU monitor mode.. */
    TMU_Enable(base, false);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable TMU clock. */
    CLOCK_DisableClock(s_tmuClocks[TMU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL. */
}

/*!
 * brief Gets the default configuration for TMU.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   code
   config->monitorInterval = 0U;
   config->monitorSiteSelection = 0U;
   config->averageLPF = kTMU_AverageLowPassFilter1_0;
   endcode
 *
 * param config Pointer to TMU configuration structure.
 */
void TMU_GetDefaultConfig(tmu_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->monitorInterval      = 0U;
    config->monitorSiteSelection = 0U; /* If no site is selected, site 0 is monitored by default. */
    config->averageLPF           = kTMU_AverageLowPassFilter1_0;
}

/*!
 * brief Get interrupt status flags.
 *
 * param base TMU peripheral base address.
 * param status The pointer to interrupt status structure. Record the current interrupt status.
 *        Please refer to "tmu_interrupt_status_t" structure.
 */
void TMU_GetInterruptStatusFlags(TMU_Type *base, tmu_interrupt_status_t *status)
{
    assert(NULL != status);

    status->interruptDetectMask         = base->TIDR;
    status->immediateInterruptsSiteMask = (uint16_t)((TMU_TIISCR_SITE_MASK & base->TIISCR) >> TMU_TIISCR_SITE_SHIFT);
    status->averageInterruptsSiteMask   = (uint16_t)((TMU_TIASCR_SITE_MASK & base->TIASCR) >> TMU_TIASCR_SITE_SHIFT);
    status->averageCriticalInterruptsSiteMask =
        (uint16_t)((TMU_TICSCR_SITE_MASK & base->TICSCR) >> TMU_TICSCR_SITE_SHIFT);
    status->risingCriticalInterruptsSiteMask =
        (uint16_t)((TMU_TICSCR_SITE_MASK & base->TICSCR) >> TMU_TICSCR_SITE_SHIFT);
    status->fallingCriticalInterruptsSiteMask =
        (uint16_t)((TMU_TICSCR_SITE_MASK & base->TICSCR) >> TMU_TICSCR_SITE_SHIFT);
}

/*!
 * brief Clear interrupt status flags and corresponding interrupt critical site capture register.
 *
 * param base TMU peripheral base address.
 * param The mask of interrupt status flags. Refer to "_tmu_interrupt_status_flags" enumeration.
 */
void TMU_ClearInterruptStatusFlags(TMU_Type *base, uint32_t mask)
{
    /* For immediate temperature threshold interrupt. */
    if (0U != ((uint32_t)kTMU_ImmediateTemperatureStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_IHTT_MASK;       /* Clear interrupt detect register. */
        base->TIISCR &= ~TMU_TIISCR_SITE_MASK; /* Clear interrupt site capture register. */
    }
    /* For average temperature threshold interrupt. */
    if (0U != ((uint32_t)kTMU_AverageTemperatureStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_AHTT_MASK;       /* Clear interrupt detect register. */
        base->TIASCR &= ~TMU_TIASCR_SITE_MASK; /* Clear interrupt site capture register. */
    }
    /* For Average temperature critical threshold interrupt. */
    if (0U != ((uint32_t)kTMU_AverageTemperatureCriticalStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_AHTCT_MASK;      /* Clear interrupt detect register. */
        base->TICSCR &= ~TMU_TICSCR_SITE_MASK; /* Clear interrupt critical site capture register. */
    }
    /* For Rising temperature critical threshold interrupt. */
    if (0U != ((uint32_t)kTMU_RisingTemperatureCriticalStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_RTRCT_MASK;      /* Clear interrupt detect register. */
        base->TICSCR &= ~TMU_TICSCR_SITE_MASK; /* Clear interrupt critical site capture register. */
    }
    /* For Falling temperature critical threshold interrupt. */
    if (0U != ((uint32_t)kTMU_FallingTemperatureCriticalStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_FTRCT_MASK;      /* Clear interrupt detect register. */
        base->TICSCR &= ~TMU_TICSCR_SITE_MASK; /* Clear interrupt critical site capture register. */
    }
}

/*!
 * brief Get the highest temperature reached for any enabled monitored site within the temperature
 *        sensor range.
 *
 * param base TMU peripheral base address.
 * param temperature Highest temperature recorded in degrees Celsius by any enabled monitored site.
 *
 * return Execution status.
 * retval kStatus_Success Temperature reading is valid.
 * retval kStatus_Fail    Temperature reading is not valid due to no measured temperature within the
 *                         sensor range of 0-160 °C for an enabled monitored site.
 */
status_t TMU_GetHighestTemperature(TMU_Type *base, uint32_t *temperature)
{
    assert(NULL != temperature);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TMHTCR_V_MASK & base->TMHTCR))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TMHTCR_TEMP_MASK & base->TMHTCR) >> TMU_TMHTCR_TEMP_SHIFT;
    }

    return ret;
}

/*!
 * brief Get the lowest temperature reached for any enabled monitored site within the temperature
 *        sensor range.
 *
 * param base TMU peripheral base address.
 * param temperature Lowest temperature recorded in degrees Celsius by any enabled monitored site.
 *
 * return Execution status.
 * retval kStatus_Success Temperature reading is valid.
 * retval kStatus_Fail    Temperature reading is not valid due to no measured temperature within the
 *                         sensor range of 0-160 °C for an enabled monitored site.
 */
status_t TMU_GetLowestTemperature(TMU_Type *base, uint32_t *temperature)
{
    assert(NULL != temperature);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TMLTCR_V_MASK & base->TMLTCR))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TMLTCR_TEMP_MASK & base->TMHTCR) >> TMU_TMLTCR_TEMP_SHIFT;
    }

    return ret;
}

/*!
 * brief Get the last immediate temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * param base TMU peripheral base address.
 * param temperature Last immediate temperature reading at site 0.
 *
 * return Execution status.
 * retval kStatus_Success Temperature reading is valid.
 * retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetImmediateTemperature(TMU_Type *base, float *temperature)
{
    assert(NULL != temperature);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TRITSR_V_MASK & base->TRITRATSR[0].TRITSR))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (float)(uint32_t)((TMU_TRITSR_TEMP_MASK & base->TRITRATSR[0].TRITSR) >> TMU_TRITSR_TEMP_SHIFT);
        if (TMU_TRITSR_TP5_MASK == (TMU_TRITSR_TP5_MASK & base->TRITRATSR[0].TRITSR))
        {
            *temperature += 0.50f;
        }
        /* To Celsius */
        *temperature -= 273.15f;
    }

    return ret;
}

/*!
 * brief Get the last average temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * param base TMU peripheral base address.
 * param temperature Last average temperature reading at site 0.
 *
 * return Execution status.
 * retval kStatus_Success Temperature reading is valid.
 * retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetAverageTemperature(TMU_Type *base, uint32_t *temperature)
{
    assert(NULL != temperature);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TRATSR_V_MASK & base->TRITRATSR[0].TRATSR))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TRATSR_TEMP_MASK & base->TRITRATSR[0].TRATSR) >> TMU_TRATSR_TEMP_SHIFT;
    }

    return ret;
}

/*!
 * brief Configure the high temperature thresold value and enable/disable relevant thresold.
 *
 * param base TMU peripheral base address.
 * param config Pointer to configuration structure. Refer to "tmu_thresold_config_t" structure.
 */
void TMU_SetHighTemperatureThresold(TMU_Type *base, const tmu_thresold_config_t *config)
{
    assert(NULL != config);

    /* Configure the high temperature immediate threshold. */
    if (config->immediateThresoldEnable)
    {
        base->TMHTITR = TMU_TMHTITR_EN_MASK | TMU_TMHTITR_TEMP(config->immediateThresoldValue);
    }
    else
    {
        base->TMHTITR = 0U;
    }
    /* Configure the high temperature average threshold. */
    if (config->averageThresoldEnable)
    {
        base->TMHTATR = TMU_TMHTATR_EN_MASK | TMU_TMHTATR_TEMP(config->averageThresoldValue);
    }
    else
    {
        base->TMHTATR = 0U;
    }
    /* Configure the high temperature average critical thresold. */
    if (config->averageCriticalThresoldEnable)
    {
        base->TMHTACTR = TMU_TMHTACTR_EN_MASK | TMU_TMHTACTR_TEMP(config->averageCriticalThresoldValue);
    }
    else
    {
        base->TMHTACTR = 0U;
    }
    /* Configure the rising temperature rate critical thresold. */
    if (config->risingCriticalThresoldEnable)
    {
        base->TMRTRCTR = TMU_TMRTRCTR_EN_MASK | TMU_TMRTRCTR_TEMP(config->risingfallingCriticalThresoldValue);
    }
    else
    {
        base->TMRTRCTR = 0U;
    }
    /* Configure the falling temperature rate critical thresold. */
    if (config->fallingCriticalThresoldEnable)
    {
        base->TMFTRCTR = TMU_TMFTRCTR_EN_MASK | TMU_TMFTRCTR_TEMP(config->risingfallingCriticalThresoldValue);
    }
    else
    {
        base->TMFTRCTR = 0U;
    }
}
