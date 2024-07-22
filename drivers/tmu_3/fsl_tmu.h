/*
 * Copyright 2022-2024, NXP
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
#define FSL_TMU_DRIVER_VERSION (MAKE_VERSION(2, 1, 0)) /*!< Version 2.1.0. */

/*!
 * @brief TMU monitor site.
 */
enum _tmu_monitor_site
{
    kTMU_MonitorSite0 = 1U << 0U, /*!< TMU monitoring site 0. */
};

/*!
 * @brief TMU interrupt enable.
 */
enum _tmu_interrupt_enable
{
    kTMU_ImmediateTemperatureInterruptEnable =
        TMU_TIER_IHTTIE_MASK, /*!< Immediate temperature threshold exceeded interrupt enable. */
    kTMU_AverageTemperatureInterruptEnable =
        TMU_TIER_AHTTIE_MASK, /*!< Average temperature threshold exceeded interrupt enable. */
    kTMU_AverageTemperatureCriticalInterruptEnable =
        TMU_TIER_AHTCTIE_MASK, /*!< Average temperature critical threshold exceeded interrupt enable. */
    kTMU_RisingTemperatureCriticalInterruptEnable =
        TMU_TIER_RTRCTIE_MASK, /*!< Rising temperature critical threshold exceeded interrupt enable. */
    kTMU_FallingTemperatureCriticalInterruptEnable =
        TMU_TIER_FTRCTIE_MASK, /*!< Falling temperature critical threshold exceeded interrupt enable. */
};

/*!
 * @brief TMU interrupt status flags.
 */
enum _tmu_interrupt_status_flags
{
    kTMU_ImmediateTemperatureStatusFlags = TMU_TIDR_IHTT_MASK, /*!< Immediate temperature threshold exceeded(IHTT).  */
    kTMU_AverageTemperatureStatusFlags   = TMU_TIDR_AHTT_MASK, /*!< Average temperature threshold exceeded(AHTT). */
    kTMU_AverageTemperatureCriticalStatusFlags =
        TMU_TIDR_AHTCT_MASK, /*!< Average temperature critical threshold exceeded.(AHTCT) */
    kTMU_RisingTemperatureCriticalStatusFlags =
        TMU_TIDR_RTRCT_MASK, /*!< Rising temperature critical threshold exceeded.(RTRCT) */
    kTMU_FallingTemperatureCriticalStatusFlags =
        TMU_TIDR_FTRCT_MASK, /*!< Falling temperature critical threshold exceeded.(FTRCT) */
};

/*!
 * @brief TMU status flags.
 */
enum _tmu_status_flags
{
    kTMU_IntervalExceededStatusFlags = TMU_TSR_MIE_MASK, /*!< Monitoring interval exceeded. The time required to perform
                                                            measurement of all monitored sites has
                                                              exceeded the monitoring interval as defined by TMTMIR. */
    kTMU_OutOfLowRangeStatusFlags = TMU_TSR_ORL_MASK,    /*!< Out-of-range low temperature measurement detected. A
                                                            temperature sensor detected a temperature
                                                              reading below the lowest measurable temperature of 0 °C. */
    kTMU_OutOfHighRangeStatusFlags =
        TMU_TSR_ORH_MASK, /*!< Out-of-range high temperature measurement detected. A temperature sensor detected a
                             temperature
                               reading above the highest measurable temperature of 160 °C. */
};

/*!
 * @brief configuration for TMU thresold.
 */
typedef struct _tmu_thresold_config
{
    bool immediateThresoldEnable;       /*!< Enable high temperature immediate threshold. */
    bool averageThresoldEnable;         /*!< Enable high temperature average threshold. */
    bool averageCriticalThresoldEnable; /*!< Enable high temperature average critical threshold. */
    bool risingCriticalThresoldEnable; /*!< Enable rising temperature rate critical threshold. */
    bool fallingCriticalThresoldEnable; /*!< Enable rising temperature rate critical threshold. */
    uint8_t immediateThresoldValue; /*!< Range:0U-160U. Valid when corresponding thresold is enabled. High temperature
                                       immediate threshold value.
                                               Determines the current upper temperature threshold, for anyenabled
                                       monitored site. */
    uint8_t averageThresoldValue;   /*!< Range:0U-160U. Valid when corresponding thresold is enabled. High temperature
                                       average threshold value.
                                               Determines the average upper temperature threshold, for any enabled
                                       monitored site. */
    uint8_t averageCriticalThresoldValue; /*!< Range:0U-160U. Valid when corresponding thresold is enabled. High
                                             temperature average critical threshold value.
                                                     Determines the average upper critical temperature threshold, for
                                             any enabled monitored site. */
    uint8_t risingfallingCriticalThresoldValue; /*!< Range:0U-160U. Valid when corresponding thresold is enabled. Rising
                                             temperature rate critical threshold value.
                                                     Determines the rising upper critical temperature threshold, for
                                             any enabled monitored site. */
} tmu_thresold_config_t;

/*!
 * @brief TMU interrupt status.
 */
typedef struct _tmu_interrupt_status
{
    uint32_t interruptDetectMask; /*!< The mask of interrupt status flags. Refer to "_tmu_interrupt_status_flags"
                                     enumeration. */
    uint16_t immediateInterruptsSiteMask; /*!< The mask of the temperature sensor site associated with a detected IHTT
                                             event. Please refer to "_tmu_monitor_site" enumeration. */
    uint16_t averageInterruptsSiteMask;   /*!< The mask of the temperature sensor site associated with a detected AHTT
                                             event.   Please refer to "_tmu_monitor_site" enumeration. */
    uint16_t averageCriticalInterruptsSiteMask; /*!< The mask of the temperature sensor site associated with a detected
                                                   AHTCT event.
                                                     Please refer to "_tmu_monitor_site" enumeration. */
    uint16_t risingCriticalInterruptsSiteMask; /*!< The mask of the temperature sensor site associated with a detected
                                                   RTRCT event.
                                                     Please refer to "_tmu_monitor_site" enumeration. */
    uint16_t fallingCriticalInterruptsSiteMask; /*!< The mask of the temperature sensor site associated with a detected
                                                   FTRCT event.
                                                     Please refer to "_tmu_monitor_site" enumeration. */
} tmu_interrupt_status_t;
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
    uint8_t monitorInterval; /*!< Temperature monitoring interval in seconds. Please refer to specific table in RM.  */
    uint16_t monitorSiteSelection; /*!< By setting the select bit for a temperature sensor site, it is enabled and
                                      included in all monitoring functions.
                                         If no site is selected, site 0 is monitored by default. Refer to
                                      "_tmu_monitor_site" enumeration. Please look up
                                         relevant table in reference manual. */
    tmu_average_low_pass_filter_t
        averageLPF; /*!< The average temperature is calculated as: ALPF x Current_Temp + (1 - ALPF) x Average_Temp.
                         For proper operation, this field should only change when monitoring is disabled. */
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
 * @brief Gets the default configuration for TMU.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 *
 * Example:
   @code
   config->monitorInterval = 0U;
   config->monitorSiteSelection = 0U;
   config->averageLPF = kTMU_AverageLowPassFilter1_0;
   @endcode
 *
 * @param config Pointer to TMU configuration structure.
 */
void TMU_GetDefaultConfig(tmu_config_t *config);

/*!
 * @brief Enable/Disable the TMU module.
 *
 * @param base TMU peripheral base address.
 * @param enable Switcher to enable/disable TMU.
 */
static inline void TMU_Enable(TMU_Type *base, bool enable)
{
    if (enable)
    {
        base->TMR = ((base->TMR & ~TMU_TMR_MODE_MASK) | TMU_TMR_MODE(2));
    }
    else
    {
        base->TMR &= ~TMU_TMR_MODE_MASK;
    }
}

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
 * @param status The pointer to interrupt status structure. Record the current interrupt status.
 *        Please refer to "tmu_interrupt_status_t" structure.
 */
void TMU_GetInterruptStatusFlags(TMU_Type *base, tmu_interrupt_status_t *status);

/*!
 * @brief Clear interrupt status flags and corresponding interrupt critical site capture register.
 *
 * @param base TMU peripheral base address.
 * @param mask The mask of interrupt status flags. Refer to "_tmu_interrupt_status_flags" enumeration.
 */
void TMU_ClearInterruptStatusFlags(TMU_Type *base, uint32_t mask);

/*!
 * @brief Get TMU status flags.
 *
 * @param base TMU peripheral base address.
 *
 * @return The mask of status flags. Refer to "_tmu_status_flags" enumeration.
 */
static inline uint32_t TMU_GetStatusFlags(TMU_Type *base)
{
    return base->TSR;
}

/*!
 * @brief Get the highest temperature reached for any enabled monitored site within the temperature
 *        sensor range.
 *
 * @param base TMU peripheral base address.
 * @param temperature Highest temperature recorded in degrees Celsius by any enabled monitored site.
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid due to no measured temperature within the
 *                         sensor range of 0-160 °C for an enabled monitored site.
 */
status_t TMU_GetHighestTemperature(TMU_Type *base, uint32_t *temperature);

/*!
 * @brief Get the lowest temperature reached for any enabled monitored site within the temperature
 *        sensor range.
 *
 * @param base TMU peripheral base address.
 * @param temperature Lowest temperature recorded in degrees Celsius by any enabled monitored site.
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid due to no measured temperature within the
 *                         sensor range of 0-160 °C for an enabled monitored site.
 */
status_t TMU_GetLowestTemperature(TMU_Type *base, uint32_t *temperature);

/*!
 * @brief Get the last immediate temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * @param base TMU peripheral base address.
 * @param temperature Last immediate temperature reading at site 0.
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetImmediateTemperature(TMU_Type *base, float *temperature);

/*!
 * @brief Get the last average temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * @param base TMU peripheral base address.
 * @param temperature Last average temperature reading at site 0.
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetAverageTemperature(TMU_Type *base, uint32_t *temperature);

/*!
 * @brief Configure the high temperature thresold value and enable/disable relevant thresold.
 *
 * @param base TMU peripheral base address.
 * @param config Pointer to configuration structure. Refer to "tmu_thresold_config_t" structure.
 */
void TMU_SetHighTemperatureThresold(TMU_Type *base, const tmu_thresold_config_t *config);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_TMU_H__ */
