/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_tmu.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.tmu_2"
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
 * @brief Set the high temperature threshold.
 *
 * @param base TMU peripheral base address.
 * @param probe probe selection, if select both 2 probes, enable main probe path by default. Refer to
 "tmu_probe_select_t" structure.
 * @param thresholdConfig threshold configuration. Refer to "tmu_threshold_config_t" structure.
 */
static void TMU_SetHighTemperatureThreshold(TMU_Type *base,
                                            tmu_probe_select_t probe,
                                            const tmu_threshold_config_t *thresholdConfig);

/*!
 * @brief Enable/disable the high temperature threshold.
 *
 * @param base TMU peripheral base address.
 * @param probe probe selection, if select both 2 probes, enable main probe path by default. Refer to
 "tmu_probe_select_t" structure.
 * @param thresholdConfig threshold configuration. Refer to "tmu_threshold_config_t" structure.
 */
static void TMU_EnableHighTemperatureThreshold(TMU_Type *base,
                                               tmu_probe_select_t probe,
                                               const tmu_threshold_config_t *thresholdConfig);

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

void TMU_Init(TMU_Type *base, const tmu_config_t *config)
{
    assert(NULL != base);
    assert(NULL != config);

    uint32_t ctrlReg;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable TMU clock. */
    CLOCK_EnableClock(s_tmuClocks[TMU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL. */

    /* Configure averageLPF register. */
    ctrlReg = base->TER;
    ctrlReg |= TMU_TER_ALPF(config->averageLPF);
    base->TER = ctrlReg;

    /* Configure high temperature threshold. */
    TMU_UpdateHighTemperatureThreshold(base, config->probeSelect,
                                       (const tmu_threshold_config_t *)&config->thresholdConfig);
}

void TMU_Deinit(TMU_Type *base)
{
    /* Disable TMU monitor mode. */
    base->TER &= ~TMU_TER_EN_MASK;
    /* Power down. */
    base->TER |= TMU_TER_ADC_PD_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable TMU clock. */
    CLOCK_DisableClock(s_tmuClocks[TMU_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL. */
}

void TMU_Enable(TMU_Type *base, bool enable)
{
    uint32_t ctrlReg;

    ctrlReg = base->TER;

    if (enable)
    {
        /* Power on. */
        ctrlReg &= ~TMU_TER_ADC_PD_MASK;
        /* Enable the temperature sensor. */
        base->TER = ctrlReg | TMU_TER_EN_MASK;
    }
    else
    {
        /* Disable TMU monitor mode. */
        ctrlReg &= ~TMU_TER_EN_MASK;
        /* Power off. */
        base->TER = ctrlReg | TMU_TER_ADC_PD_MASK;
    }
}

void TMU_GetDefaultConfig(tmu_config_t *config)
{
    assert(NULL != config);

    config->probeSelect = kTMU_ProbeSelectMainProbe;
    config->averageLPF  = kTMU_AverageLowPassFilter0_5;

    config->thresholdConfig.immediateThresholdEnable                   = false;
    config->thresholdConfig.immediateThresholdValueOfMainProbe         = 0x00U;
    config->thresholdConfig.immediateThresholdValueOfRemoteProbe       = 0x00U;
    config->thresholdConfig.AverageThresholdEnable                     = false;
    config->thresholdConfig.averageThresholdValueOfMainProbe           = 0x00U;
    config->thresholdConfig.averageThresholdValueOfRemoteProbe         = 0x00U;
    config->thresholdConfig.AverageCriticalThresholdEnable             = false;
    config->thresholdConfig.averageCriticalThresholdValueOfMainProbe   = 0x00U;
    config->thresholdConfig.averageCriticalThresholdValueOfRemoteProbe = 0x00U;
}

status_t TMU_GetImmediateTemperature(TMU_Type *base, tmu_probe_select_t probe, int8_t *temperature)
{
    assert(NULL != temperature);

    uint32_t temp   = 0x00U;
    int8_t rawVal   = 0x00;
    status_t status = kStatus_Success;

    /* If select both 2 probes, return main probe path by default. */
    if ((kTMU_ProbeSelectMainProbe == probe) || (kTMU_ProbeSelectBothProbes == probe))
    {
        /* Check first measurement ready or not, this valid bit field(V0/V1) only shows temperature sensor
           first captured actual temperature completely and relevant temperature registers can be read continuously. */
        if (0U == (TMU_TRATSR_V0_MASK & base->TRITSR))
        {
            status = kStatus_Fail;
        }
        else
        {
            /* Get raw average temperature value. */
            temp = (TMU_TRITSR_TEMP0_MASK & base->TRITSR) >> TMU_TRITSR_TEMP0_SHIFT;
        }
    }
    else if (kTMU_ProbeSelectRemoteProbe == probe)
    {
        /* Check first measurement ready or not, this valid bit field(V0/V1) only shows temperature sensor
           first captured actual temperature completely and relevant temperature registers can be read continuously. */
        if (0U == (TMU_TRATSR_V1_MASK & base->TRITSR))
        {
            status = kStatus_Fail;
        }
        else
        {
            /* Get raw average temperature value. */
            temp = (TMU_TRITSR_TEMP1_MASK & base->TRITSR) >> TMU_TRITSR_TEMP1_SHIFT;
        }
    }
    else
    {
        ; /* For MISRA C-2012 rule 15.7. */
    }

    rawVal       = (int8_t)temp;
    *temperature = rawVal;
    return status;
}

status_t TMU_GetAverageTemperature(TMU_Type *base, tmu_probe_select_t probe, int8_t *temperature)
{
    assert(NULL != temperature);

    uint32_t temp   = 0x00U;
    int8_t rawVal   = 0x00;
    status_t status = kStatus_Success;

    /* If select both 2 probes, return main probe path by default. */
    if ((kTMU_ProbeSelectMainProbe == probe) || (kTMU_ProbeSelectBothProbes == probe))
    {
        /* Check first measurement ready or not, this valid bit field(V0/V1) only shows temperature sensor
           first captured actual temperature completely and relevant temperature registers can be read continuously. */
        if (0U == (TMU_TRATSR_V0_MASK & base->TRATSR))
        {
            status = kStatus_Fail;
        }
        else
        {
            /* Get raw average temperature value. */
            temp = (TMU_TRATSR_TEMP0_MASK & base->TRATSR) >> TMU_TRATSR_TEMP0_SHIFT;
        }
    }
    else if (kTMU_ProbeSelectRemoteProbe == probe)
    {
        /* Check first measurement ready or not, this valid bit field(V0/V1) only shows temperature sensor
           first captured actual temperature completely and relevant temperature registers can be read continuously. */
        if (0U == (TMU_TRATSR_V1_MASK & base->TRATSR))
        {
            status = kStatus_Fail;
        }
        else
        {
            /* Get raw average temperature value. */
            temp = (TMU_TRATSR_TEMP1_MASK & base->TRATSR) >> TMU_TRATSR_TEMP1_SHIFT;
        }
    }
    else
    {
        ; /* For MISRA C-2012 rule 15.7. */
    }

    rawVal       = (int8_t)temp;
    *temperature = rawVal;
    return status;
}

static void TMU_SetHighTemperatureThreshold(TMU_Type *base,
                                            tmu_probe_select_t probe,
                                            const tmu_threshold_config_t *thresholdConfig)
{
    uint32_t tempITRegVal;
    uint32_t tempATRegVal;
    uint32_t tempACTRegVal;

    /* Configure the high temperature immediate threshold. */
    if (thresholdConfig->immediateThresholdEnable)
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Disable immediate threshold.*/
            base->TMHTITR &= ~TMU_TMHTITR_EN0_MASK;
            /* Clear immediate threshold value and set a new immediate threshold value of probe0. */
            tempITRegVal = base->TMHTITR;
            tempITRegVal = (tempITRegVal & ~TMU_TMHTITR_TEMP0_MASK) |
                           TMU_TMHTITR_TEMP0(thresholdConfig->immediateThresholdValueOfMainProbe);
            base->TMHTITR = tempITRegVal;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Disable immediate threshold.*/
            base->TMHTITR &= ~TMU_TMHTITR_EN1_MASK;
            /* Clear immediate threshold value and set a new immediate threshold value of probe1. */
            tempITRegVal = base->TMHTITR;
            tempITRegVal = (tempITRegVal & ~TMU_TMHTITR_TEMP1_MASK) |
                           TMU_TMHTITR_TEMP1(thresholdConfig->immediateThresholdValueOfRemoteProbe);
            base->TMHTITR = tempITRegVal;
        }
    }

    /* Configure the high temperature average threshold. */
    if (thresholdConfig->AverageThresholdEnable)
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average threshold.*/
            base->TMHTATR &= ~TMU_TMHTATR_EN0_MASK;
            /* Clear average threshold value and set a new average threshold value of probe0. */
            tempATRegVal = base->TMHTATR;
            tempATRegVal = (tempATRegVal & ~TMU_TMHTATR_TEMP0_MASK) |
                           TMU_TMHTATR_TEMP0(thresholdConfig->averageThresholdValueOfMainProbe);
            base->TMHTATR = tempATRegVal;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average threshold.*/
            base->TMHTATR &= ~TMU_TMHTATR_EN1_MASK;
            /* Clear average threshold value and set a new average threshold value of probe1. */
            tempATRegVal = base->TMHTATR;
            tempATRegVal = (tempATRegVal & ~TMU_TMHTATR_TEMP1_MASK) |
                           TMU_TMHTATR_TEMP1(thresholdConfig->averageThresholdValueOfRemoteProbe);
            base->TMHTATR = tempATRegVal;
        }
    }

    /* Configure the high temperature average critical threshold. */
    if (thresholdConfig->AverageCriticalThresholdEnable)
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average critical threshold.*/
            base->TMHTACTR &= ~TMU_TMHTACTR_EN0_MASK;
            /* Clear average critical threshold value and set a new average threshold value of probe0. */
            tempACTRegVal = base->TMHTACTR;
            tempACTRegVal = (tempACTRegVal & ~TMU_TMHTACTR_TEMP0_MASK) |
                            TMU_TMHTACTR_TEMP0(thresholdConfig->averageCriticalThresholdValueOfMainProbe);
            base->TMHTACTR = tempACTRegVal;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average critical threshold.*/
            base->TMHTACTR &= ~TMU_TMHTACTR_EN1_MASK;
            /* Clear average critical threshold value and set a new average threshold value of probe1. */
            tempACTRegVal = base->TMHTACTR;
            tempACTRegVal = (tempACTRegVal & ~TMU_TMHTACTR_TEMP1_MASK) |
                            TMU_TMHTACTR_TEMP1(thresholdConfig->averageCriticalThresholdValueOfRemoteProbe);
            base->TMHTACTR = tempACTRegVal;
        }
    }
}

static void TMU_EnableHighTemperatureThreshold(TMU_Type *base,
                                               tmu_probe_select_t probe,
                                               const tmu_threshold_config_t *thresholdConfig)
{
    uint32_t tempITRegVal;
    uint32_t tempATRegVal;
    uint32_t tempACTRegVal;

    /* Configure the high temperature immediate threshold. */
    if (thresholdConfig->immediateThresholdEnable)
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Enable threshold after configuring its value. Otherwise, TIDR interrupt status will be set immediately
             * and dead loop into ISR. */
            tempITRegVal = base->TMHTITR;
            tempITRegVal |= TMU_TMHTITR_EN0_MASK;
            base->TMHTITR = tempITRegVal;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Enable threshold after configuring its value. Otherwise, TIDR interrupt status will set immediately and
             * dead loop into ISR. */
            tempITRegVal = base->TMHTITR;
            tempITRegVal |= TMU_TMHTITR_EN1_MASK;
            base->TMHTITR = tempITRegVal;
        }
    }
    else
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Disable immediate threshold.*/
            base->TMHTITR &= ~TMU_TMHTITR_EN0_MASK;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Disable immediate threshold.*/
            base->TMHTITR &= ~TMU_TMHTITR_EN1_MASK;
        }
    }

    /* Configure the high temperature average threshold. */
    if (thresholdConfig->AverageThresholdEnable)
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Enable threshold after configuring its value. Otherwise, TIDR interrupt status will set immediately and
             * dead loop into ISR. */
            tempATRegVal = base->TMHTATR;
            tempATRegVal |= TMU_TMHTATR_EN0_MASK;
            base->TMHTATR = tempATRegVal;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Enable threshold after configuring its value. Otherwise, TIDR interrupt status will set immediately and
             * dead loop into ISR. */
            tempATRegVal = base->TMHTATR;
            tempATRegVal |= TMU_TMHTATR_EN1_MASK;
            base->TMHTATR = tempATRegVal;
        }
    }
    else
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average threshold.*/
            base->TMHTATR &= ~TMU_TMHTATR_EN0_MASK;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average threshold.*/
            base->TMHTATR &= ~TMU_TMHTATR_EN1_MASK;
        }
    }

    /* Configure the high temperature average critical threshold. */
    if (thresholdConfig->AverageCriticalThresholdEnable)
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Enable threshold after configuring its value. Otherwise, TIDR interrupt status will set immediately and
             * dead loop into ISR. */
            tempACTRegVal = base->TMHTACTR;
            tempACTRegVal |= TMU_TMHTACTR_EN0_MASK;
            base->TMHTACTR = tempACTRegVal;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Enable threshold after configuring its value. Otherwise, TIDR interrupt status will set immediately and
             * dead loop into ISR. */
            tempACTRegVal = base->TMHTACTR;
            tempACTRegVal |= TMU_TMHTACTR_EN1_MASK;
            base->TMHTACTR = tempACTRegVal;
        }
    }
    else
    {
        if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average critical threshold.*/
            base->TMHTACTR &= ~TMU_TMHTACTR_EN0_MASK;
        }

        if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
        {
            /* Disable average critical threshold.*/
            base->TMHTACTR &= ~TMU_TMHTACTR_EN1_MASK;
        }
    }
}

void TMU_UpdateHighTemperatureThreshold(TMU_Type *base,
                                        tmu_probe_select_t probe,
                                        const tmu_threshold_config_t *thresholdConfig)
{
    /*a. disable the TMU.*/
    TMU_Enable(base, false);
    /* Set TMU probe select. */
    base->TPS = TMU_TPS_PROBE_SEL((uint32_t)probe - 0x01U);
    /*b. disable the threshold.*/
    /*c. update the threshold value.*/
    TMU_SetHighTemperatureThreshold(base, probe, thresholdConfig);
    /*d. enable the TMU, waiting at least 5 us.*/
    TMU_Enable(base, true);
    /* Delay 5us to make sure that TMU registers' status reset completely. */
    SDK_DelayAtLeastUs(5, SystemCoreClock);
    /*e. enable the threshold*/
    TMU_EnableHighTemperatureThreshold(base, probe, thresholdConfig);

    if (((uint8_t)kTMU_ProbeSelectMainProbe & (uint8_t)probe) != 0U)
    {
        while (((TMU_TRITSR_V0_MASK & base->TRITSR) == 0x00U) && ((TMU_TRATSR_V0_MASK & base->TRATSR) == 0x00U))
        {
        }
    }
    if (((uint8_t)kTMU_ProbeSelectRemoteProbe & (uint8_t)probe) != 0U)
    {
        while (((TMU_TRITSR_V1_MASK & base->TRITSR) == 0x00U) && ((TMU_TRATSR_V1_MASK & base->TRATSR) == 0x00U))
        {
        }
    }

    /* Delay 1us to make sure that load captured temperature value into related registers. */
    SDK_DelayAtLeastUs(1, SystemCoreClock);
}
