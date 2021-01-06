/*
 * Copyright 2017-2019, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_tmu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tmu"
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
    base->TTRCR[0] = TMU_TTRCR_TEMP(0U) | TMU_TTRCR_CAL_PTS(11U);  /* Range0. */
    base->TTRCR[1] = TMU_TTRCR_TEMP(44U) | TMU_TTRCR_CAL_PTS(9U);  /* Range1. */
    base->TTRCR[2] = TMU_TTRCR_TEMP(78U) | TMU_TTRCR_CAL_PTS(6U);  /* Range2. */
    base->TTRCR[3] = TMU_TTRCR_TEMP(102U) | TMU_TTRCR_CAL_PTS(3U); /* Range3. */
    /* For range0. */
    base->TTCFGR = 0x00000000U;
    base->TSCFGR = 0x00000020U;
    base->TTCFGR = 0x00000001U;
    base->TSCFGR = 0x00000024U;
    base->TTCFGR = 0x00000002U;
    base->TSCFGR = 0x0000002AU;
    base->TTCFGR = 0x00000003U;
    base->TSCFGR = 0x00000032U;
    base->TTCFGR = 0x00000004U;
    base->TSCFGR = 0x00000038U;
    base->TTCFGR = 0x00000005U;
    base->TSCFGR = 0x0000003EU;
    base->TTCFGR = 0x00000006U;
    base->TSCFGR = 0x00000043U;
    base->TTCFGR = 0x00000007U;
    base->TSCFGR = 0x0000004AU;
    base->TTCFGR = 0x00000008U;
    base->TSCFGR = 0x00000050U;
    base->TTCFGR = 0x00000009U;
    base->TSCFGR = 0x00000059U;
    base->TTCFGR = 0x0000000AU;
    base->TSCFGR = 0x0000005FU;
    base->TTCFGR = 0x0000000BU;
    base->TSCFGR = 0x00000066U;
    /* For range1. */
    base->TTCFGR = 0x00010000U;
    base->TSCFGR = 0x00000023U;
    base->TTCFGR = 0x00010001U;
    base->TSCFGR = 0x0000002BU;
    base->TTCFGR = 0x00010002U;
    base->TSCFGR = 0x00000033U;
    base->TTCFGR = 0x00010003U;
    base->TSCFGR = 0x0000003AU;
    base->TTCFGR = 0x00010004U;
    base->TSCFGR = 0x00000042U;
    base->TTCFGR = 0x00010005U;
    base->TSCFGR = 0x0000004AU;
    base->TTCFGR = 0x00010006U;
    base->TSCFGR = 0x00000054U;
    base->TTCFGR = 0x00010007U;
    base->TSCFGR = 0x0000005CU;
    base->TTCFGR = 0x00010008U;
    base->TSCFGR = 0x00000065U;
    base->TTCFGR = 0x00010009U;
    base->TSCFGR = 0x0000006FU;
    /* For range2. */
    base->TTCFGR = 0x00020000U;
    base->TSCFGR = 0x00000029U;
    base->TTCFGR = 0x00020001U;
    base->TSCFGR = 0x00000033U;
    base->TTCFGR = 0x00020002U;
    base->TSCFGR = 0x0000003DU;
    base->TTCFGR = 0x00020003U;
    base->TSCFGR = 0x00000048U;
    base->TTCFGR = 0x00020004U;
    base->TSCFGR = 0x00000054U;
    base->TTCFGR = 0x00020005U;
    base->TSCFGR = 0x00000060U;
    base->TTCFGR = 0x00020006U;
    base->TSCFGR = 0x0000006CU;
    /* For range3. */
    base->TTCFGR = 0x00030000U;
    base->TSCFGR = 0x00000025U;
    base->TTCFGR = 0x00030001U;
    base->TSCFGR = 0x00000033U;
    base->TTCFGR = 0x00030002U;
    base->TSCFGR = 0x00000043U;
    base->TTCFGR = 0x00030003U;
    base->TSCFGR = 0x00000055U;
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
                                            (uint32_t)kTMU_AverageTemperatureCriticalStatusFlags);

    /* Configure TMR register. */
    base->TMR = TMU_TMR_ALPF(config->averageLPF) | TMU_TMR_MSITE(config->monitorSiteSelection);

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
    status->immediateInterruptsSiteMask = (uint16_t)((TMU_TISCR_ISITE_MASK & base->TISCR) >> TMU_TISCR_ISITE_SHIFT);
    status->AverageInterruptsSiteMask   = (uint16_t)((TMU_TISCR_ASITE_MASK & base->TISCR) >> TMU_TISCR_ASITE_SHIFT);
    status->AverageCriticalInterruptsSiteMask =
        (uint16_t)((TMU_TICSCR_CASITE_MASK & base->TICSCR) >> TMU_TICSCR_CASITE_SHIFT);
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
        base->TIDR = TMU_TIDR_ITTE_MASK;      /* Clear interrupt detect register. */
        base->TISCR &= ~TMU_TISCR_ISITE_MASK; /* Clear interrupt site capture register. */
    }
    /* For average temperature threshold interrupt. */
    if (0U != ((uint32_t)kTMU_AverageTemperatureStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_ATTE_MASK;      /* Clear interrupt detect register. */
        base->TISCR &= ~TMU_TISCR_ASITE_MASK; /* Clear interrupt site capture register. */
    }
    /* For Average temperature critical threshold interrupt. */
    if (0U != ((uint32_t)kTMU_AverageTemperatureCriticalStatusFlags & mask))
    {
        base->TIDR = TMU_TIDR_ATCTE_MASK;        /* Clear interrupt detect register. */
        base->TICSCR &= ~TMU_TICSCR_CASITE_MASK; /* Clear interrupt critical site capture register. */
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
 *                         sensor range of 0-125 °C for an enabled monitored site.
 */
status_t TMU_GetHighestTemperature(TMU_Type *base, uint32_t *temperature)
{
    assert(NULL != temperature);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TMHTCRH_V_MASK & base->TMHTCRH))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TMHTCRH_TEMP_MASK & base->TMHTCRH) >> TMU_TMHTCRH_TEMP_SHIFT;
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
 *                         sensor range of 0-125 °C for an enabled monitored site.
 */
status_t TMU_GetLowestTemperature(TMU_Type *base, uint32_t *temperature)
{
    assert(NULL != temperature);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TMHTCRL_V_MASK & base->TMHTCRL))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TMHTCRL_TEMP_MASK & base->TMHTCRL) >> TMU_TMHTCRL_TEMP_SHIFT;
    }

    return ret;
}

/*!
 * brief Get the last immediate temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * param base TMU peripheral base address.
 * param siteIndex The index of the site user want to read. 0U: site0 ~ 15U: site15.
 * param temperature Last immediate temperature reading at site n .
 *
 * return Execution status.
 * retval kStatus_Success Temperature reading is valid.
 * retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetImmediateTemperature(TMU_Type *base, uint32_t siteIndex, uint32_t *temperature)
{
    assert(NULL != temperature);
    assert(siteIndex < TMU_TRITSR_COUNT);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TRITSR_V_MASK & base->TRTSR[siteIndex].TRITSR))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TRITSR_TEMP_MASK & base->TRTSR[siteIndex].TRITSR) >> TMU_TRITSR_TEMP_SHIFT;
    }

    return ret;
}

/*!
 * brief Get the last average temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * param base TMU peripheral base address.
 * param siteIndex The index of the site user want to read. 0U: site0 ~ 15U: site15.
 * param temperature Last average temperature reading at site n .
 *
 * return Execution status.
 * retval kStatus_Success Temperature reading is valid.
 * retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetAverageTemperature(TMU_Type *base, uint32_t siteIndex, uint32_t *temperature)
{
    assert(NULL != temperature);
    assert(siteIndex < TMU_TRATSR_COUNT);

    status_t ret = kStatus_Success;

    if (0U == (TMU_TRATSR_V_MASK & base->TRTSR[siteIndex].TRATSR))
    {
        ret = kStatus_Fail;
    }
    else
    {
        *temperature = (TMU_TRATSR_TEMP_MASK & base->TRTSR[siteIndex].TRATSR) >> TMU_TRATSR_TEMP_SHIFT;
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
    if (config->AverageThresoldEnable)
    {
        base->TMHTATR = TMU_TMHTATR_EN_MASK | TMU_TMHTATR_TEMP(config->averageThresoldValue);
    }
    else
    {
        base->TMHTATR = 0U;
    }
    /* Configure the high temperature average critical thresold. */
    if (config->AverageCriticalThresoldEnable)
    {
        base->TMHTACTR = TMU_TMHTACTR_EN_MASK | TMU_TMHTACTR_TEMP(config->averageCriticalThresoldValue);
    }
    else
    {
        base->TMHTACTR = 0U;
    }
}
