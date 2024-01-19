/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_TMU_H__
#define FSL_TMU_H__

#include "fsl_common.h"

/*!
 * @addtogroup tmu
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief TMU driver version. */
#define FSL_TMU_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0. */

/*!
 * @brief TMU interrupt enable, _tmu_interrupt_enable.
 */
enum
{
    kTMU_ImmediateTemperature0InterruptEnable =
        TMU_TIER_ITTEIE0_MASK, /*!< Immediate temperature threshold exceeded interrupt enable of probe0. */
    kTMU_AverageTemperature0InterruptEnable =
        TMU_TIER_ATTEIE0_MASK, /*!< Average temperature threshold exceeded interrupt enable of probe0. */
    kTMU_AverageTemperature0CriticalInterruptEnable =
        TMU_TIER_ATCTEIE0_MASK, /*!< Average temperature critical threshold exceeded interrupt enable of probe0. */
    kTMU_ImmediateTemperature1Interrupt1Enable =
        TMU_TIER_ITTEIE1_MASK, /*!< Immediate temperature threshold exceeded interrupt enable of probe1. */
    kTMU_AverageTemperature1Interrupt1Enable =
        TMU_TIER_ATTEIE1_MASK, /*!< Average temperature threshold exceeded interrupt enable of probe1. */
    kTMU_AverageTemperature1CriticalInterrupt1Enable =
        TMU_TIER_ATCTEIE1_MASK, /*!< Average temperature critical threshold exceeded interrupt enable of probe1. */
};

/*!
 * @brief TMU interrupt enable, _tmu_interrupt_status_flags.
 */
enum
{
    kTMU_ImmediateTemperature0InterruptStausFlags =
        TMU_TIDR_ITTE0_MASK, /*!< Immediate temperature threshold exceeded interrupt status of probe0. */
    kTMU_AverageTemperature0InterruptStausFlags =
        TMU_TIDR_ATTE0_MASK, /*!< Average temperature threshold exceeded interrupt status of probe0. */
    kTMU_AverageTemperature0CriticalInterruptStausFlags =
        TMU_TIDR_ATCTE0_MASK, /*!< Average temperature critical threshold exceeded interrupt status of probe0. */
    kTMU_ImmediateTemperature1Interrupt1StausFlags =
        TMU_TIDR_ITTE1_MASK, /*!< Immediate temperature threshold exceeded interrupt status of probe1. */
    kTMU_AverageTemperature1Interrupt1StausFlags =
        TMU_TIDR_ATTE1_MASK, /*!< Average temperature threshold exceeded interrupt status of probe1. */
    kTMU_AverageTemperature1CriticalInterrupt1StausFlags =
        TMU_TIDR_ATCTE1_MASK, /*!< Average temperature critical threshold exceeded interrupt status of probe1. */
};

/*!
 * @brief configuration for TMU threshold.
 */
typedef struct _tmu_threshold_config
{
    bool immediateThresholdEnable;       /*!< Enable high temperature immediate threshold. */
    bool AverageThresholdEnable;         /*!< Enable high temperature average threshold. */
    bool AverageCriticalThresholdEnable; /*!< Enable high temperature average critical threshold. */
    uint8_t immediateThresholdValueOfMainProbe; /*!< Range:-40~125. Valid when corresponding threshold is enabled. High temperature
                                       immediate threshold value of main probe.
                                          Besides, bit-8 is sign bit: 1 means nagetive and 0 means positive. */
    uint8_t averageThresholdValueOfMainProbe;   /*!< Range:-40~125. Valid when corresponding threshold is enabled. High temperature
                                       average threshold value of main probe.
                                          Besides, bit-8 is sign bit: 1 means nagetive and 0 means positive. */
    uint8_t averageCriticalThresholdValueOfMainProbe; /*!< Range:-40~125. Valid when corresponding threshold is enabled. High
                                             temperature average critical threshold value of main probe.
                                                Besides, bit-8 is sign bit: 1 means nagetive and 0 means positive. */
    uint8_t immediateThresholdValueOfRemoteProbe; /*!< Range:-40~125. Valid when corresponding threshold is enabled. High temperature
                                       immediate threshold value of remote probe.
                                          Besides, bit-8 is sign bit: 1 means nagetive and 0 means positive. */
    uint8_t averageThresholdValueOfRemoteProbe;   /*!< Range:-40~125. Valid when corresponding threshold is enabled. High temperature
                                       average threshold value of remote probe.
                                          Besides, bit-8 is sign bit: 1 means nagetive and 0 means positive. */
    uint8_t averageCriticalThresholdValueOfRemoteProbe; /*!< Range:-40~125. Valid when corresponding threshold is enabled. High
                                             temperature average critical threshold value of remote probe.
                                                Besides, bit-8 is sign bit: 1 means nagetive and 0 means positive. */
} tmu_threshold_config_t;

/*!
 * @brief Probe selection.
 */
typedef enum _tmu_probe_select
{
    kTMU_ProbeSelectMainProbe   = 1U << 0U, /*!< Select the main probe only. */
    kTMU_ProbeSelectRemoteProbe = 1U << 1U, /*!< Select the remote probe(near A53) only. */
    kTMU_ProbeSelectBothProbes  = ( 1U << 0U) |  (1U << 1U), /*!< Select both 2 probes. */
} tmu_probe_select_t;

/*!
 * @brief Average low pass filter setting.
 */
typedef enum _tmu_average_low_pass_filter
{
    kTMU_AverageLowPassFilter1_0   = 0U, /*!< Average low pass filter = 1. */
    kTMU_AverageLowPassFilter0_5   = 1U, /*!< Average low pass filter = 0.5. */
    kTMU_AverageLowPassFilter0_25  = 2U, /*!< Average low pass filter = 0.25. */
    kTMU_AverageLowPassFilter0_125 = 3U, /*!< Average low pass filter = 0.125. */
} tmu_average_low_pass_filter_t;

/*!
 * @brief Configuration for TMU module.
 */
typedef struct _tmu_config
{
    tmu_probe_select_t probeSelect; /*!< The temperature monitor probe select.*/
    tmu_average_low_pass_filter_t averageLPF; /*!< The average temperature is calculated as:
                                                   ALPF x Current_Temp + (1 - ALPF) x Average_Temp.
                                                   For proper operation, this field should only change when monitoring is disabled. */
    tmu_threshold_config_t thresholdConfig; /*!< The high temperature threshold configuration. */
} tmu_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Enable the access to TMU registers and Initialize TMU module.
 *
 * @param base TMU peripheral base address.
 * @param config Pointer to configuration structure. Refer to "tmu_config_t" structure.
 */
void TMU_Init(TMU_Type *base, const tmu_config_t *config);

/*!
 * @brief De-initialize TMU module and Disable the access to DCDC registers.
 *
 * @param base TMU peripheral base address.
 */
void TMU_Deinit(TMU_Type *base);

/*!
 * @brief Enable/disable TMU module.
 *
 * @param base TMU peripheral base address.
 * @param enable enable or disable TMU.
 */
void TMU_Enable(TMU_Type *base, bool enable);

/*!
 * @brief Gets the default configuration for TMU.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   @code
   config.averageLPF                                     = kTMU_AverageLowPassFilter0_5;
   config.probeSelect                                    = kTMU_ProbeSelectMainProbe;
   config.thresholdConfig.immediateThresholdEnable       = false;
   config.thresholdConfig.immediateThresholdValue        = DEMO_TMU_IMMEDIATE_THRESOLD;
   config.thresholdConfig.AverageThresholdEnable         = true;
   config.thresholdConfig.averageThresholdValue          = DEMO_TMU_AVERAGE_THRESOLD;
   config.thresholdConfig.AverageCriticalThresholdEnable = false;
   config.thresholdConfig.averageCriticalThresholdValue  = DEMO_TMU_AVERAGE_CRITICAL_THRESOLD;
   @endcode
 *
 * @param config Pointer to TMU configuration structure.
 */
void TMU_GetDefaultConfig(tmu_config_t *config);

/*!
 * @brief Enable the TMU interrupts.
 *
 * @param base TMU peripheral base address.
 * @param mask The interrupt mask. Refer to "_tmu_interrupt_enable" enumeration.
 */
static inline void TMU_EnableInterrupts(TMU_Type *base, uint32_t mask)
{
    base->TIER |= mask;
}

/*!
 * @brief Disable the TMU interrupts.
 *
 * @param base TMU peripheral base address.
 * @param mask The interrupt mask. Refer to "_tmu_interrupt_enable" enumeration.
 */
static inline void TMU_DisableInterrupts(TMU_Type *base, uint32_t mask)
{
    base->TIER &= ~mask;
}

/*!
 * @brief Get interrupt status flags.
 *
 * @param base TMU peripheral base address.
 * @retval The current interrupt status.
 */
static inline uint32_t TMU_GetInterruptStatusFlags(TMU_Type *base)
{
    return base->TIDR;
}

/*!
 * @brief Clear interrupt status flags.
 *
 * @param base TMU peripheral base address.
 * @param mask The mask of interrupt status flags. Refer to "_tmu_interrupt_status_flags" enumeration.
 */
static inline void TMU_ClearInterruptStatusFlags(TMU_Type *base, uint32_t mask)
{
    base->TIDR = mask;
}

/*!
 * @brief Get the last immediate temperature at site.
 *
 * @param base TMU peripheral base address.
 * @param probe probe selection, if select both 2 probes, return main probe temeperature by default. Refer to
 * "tmu_probe_select_t" structure.
 * @param temperature Last immediate temperature reading at site when V=1.
 *                    besides, Bit-8 is sign bit: 1 means nagetive and 0 means positive.
 * @retval get immediate temperature status.
 */
status_t TMU_GetImmediateTemperature(TMU_Type *base, tmu_probe_select_t probe, int8_t *temperature);

/*!
 * @brief Get the last average temperature at site.
 *
 * @param base TMU peripheral base address.
 * @param probe probe selection, if select both 2 probes, return main probe temeperature by default. Refer to
 * "tmu_probe_select_t" structure.
 * @param temperature Last average temperature reading at site;
 *                    besides, Bit-8 is sign bit: 1 means nagetive and 0 means positive.
 * @retval get average temperature status.
 */
status_t TMU_GetAverageTemperature(TMU_Type *base, tmu_probe_select_t probe, int8_t *temperature);

/*!
 * @brief Update the high temperature threshold value.
 *
 * @param base TMU peripheral base address.
 * @param probe probe selection, if select both 2 probes, set main probe path by default. Refer to "tmu_probe_select_t"
 structure.
 * @param thresholdConfig threshold configuration. Refer to "tmu_threshold_config_t" structure.
 */
void TMU_UpdateHighTemperatureThreshold(TMU_Type *base,
                                        tmu_probe_select_t probe,
                                        const tmu_threshold_config_t *thresholdConfig);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_TMU_H__ */
