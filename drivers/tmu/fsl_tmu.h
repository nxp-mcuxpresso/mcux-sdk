/*
 * Copyright 2017-2020, NXP
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
#define FSL_TMU_DRIVER_VERSION (MAKE_VERSION(2, 0, 3)) /*!< Version 2.0.3. */

enum _tmu_monitor_site
{
    kTMU_MonitorSite0  = 1U << 15U, /* TMU monitoring site 0. */
    kTMU_MonitorSite1  = 1U << 14U, /* TMU monitoring site 1. */
    kTMU_MonitorSite2  = 1U << 13U, /* TMU monitoring site 2. */
    kTMU_MonitorSite3  = 1U << 12U, /* TMU monitoring site 3. */
    kTMU_MonitorSite4  = 1U << 11U, /* TMU monitoring site 4. */
    kTMU_MonitorSite5  = 1U << 10U, /* TMU monitoring site 5. */
    kTMU_MonitorSite6  = 1U << 9U,  /* TMU monitoring site 6. */
    kTMU_MonitorSite7  = 1U << 8U,  /* TMU monitoring site 7. */
    kTMU_MonitorSite8  = 1U << 7U,  /* TMU monitoring site 8. */
    kTMU_MonitorSite9  = 1U << 6U,  /* TMU monitoring site 9. */
    kTMU_MonitorSite10 = 1U << 5U,  /* TMU monitoring site 10. */
    kTMU_MonitorSite11 = 1U << 4U,  /* TMU monitoring site 11. */
    kTMU_MonitorSite12 = 1U << 3U,  /* TMU monitoring site 12. */
    kTMU_MonitorSite13 = 1U << 2U,  /* TMU monitoring site 13. */
    kTMU_MonitorSite14 = 1U << 1U,  /* TMU monitoring site 14. */
    kTMU_MonitorSite15 = 1U << 0U,  /* TMU monitoring site 15. */
};

/*!
 * @brief TMU interrupt enable.
 */
enum _tmu_interrupt_enable
{
    kTMU_ImmediateTemperatureInterruptEnable =
        TMU_TIER_ITTEIE_MASK, /*!< Immediate temperature threshold exceeded interrupt enable. */
    kTMU_AverageTemperatureInterruptEnable =
        TMU_TIER_ATTEIE_MASK, /*!< Average temperature threshold exceeded interrupt enable. */
    kTMU_AverageTemperatureCriticalInterruptEnable =
        TMU_TIER_ATCTEIE_MASK, /*!< Average temperature critical threshold exceeded interrupt enable. >*/
};

/*!
 * @brief TMU interrupt status flags.
 */
enum _tmu_interrupt_status_flags
{
    kTMU_ImmediateTemperatureStatusFlags = TMU_TIDR_ITTE_MASK, /*!< Immediate temperature threshold exceeded(ITTE).  */
    kTMU_AverageTemperatureStatusFlags   = TMU_TIDR_ATTE_MASK, /*!< Average temperature threshold exceeded(ATTE). */
    kTMU_AverageTemperatureCriticalStatusFlags =
        TMU_TIDR_ATCTE_MASK, /*!< Average temperature critical threshold exceeded.(ATCTE) */
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
                               reading above the highest measurable temperature of 125 °C. */
};

/*!
 * @brief configuration for TMU thresold.
 */
typedef struct _tmu_thresold_config
{
    bool immediateThresoldEnable;       /*!< Enable high temperature immediate threshold. */
    bool AverageThresoldEnable;         /*!< Enable high temperature average threshold. */
    bool AverageCriticalThresoldEnable; /*!< Enable high temperature average critical threshold. */
    uint8_t immediateThresoldValue; /*!< Range:0U-125U. Valid when corresponding thresold is enabled. High temperature
                                       immediate threshold value.
                                               Determines the current upper temperature threshold, for anyenabled
                                       monitored site. */
    uint8_t averageThresoldValue;   /*!< Range:0U-125U. Valid when corresponding thresold is enabled. High temperature
                                       average threshold value.
                                               Determines the average upper temperature threshold, for any enabled
                                       monitored site. */
    uint8_t averageCriticalThresoldValue; /*!< Range:0U-125U. Valid when corresponding thresold is enabled. High
                                             temperature average critical threshold value.
                                                     Determines the average upper critical temperature threshold, for
                                             any enabled monitored site. */
} tmu_thresold_config_t;

/*!
 * @brief TMU interrupt status.
 */
typedef struct _tmu_interrupt_status
{
    uint32_t interruptDetectMask; /*!< The mask of interrupt status flags. Refer to "_tmu_interrupt_status_flags"
                                     enumeration. */
    uint16_t immediateInterruptsSiteMask; /*!< The mask of the temperature sensor site associated with a detected ITTE
                                             event. Please refer to "_tmu_monitor_site" enumeration. */
    uint16_t AverageInterruptsSiteMask;   /*!< The mask of the temperature sensor site associated with a detected ATTE
                                             event.   Please refer to "_tmu_monitor_site" enumeration. */
    uint16_t AverageCriticalInterruptsSiteMask; /*!< The mask of the temperature sensor site associated with a detected
                                                   ATCTE event.
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
        base->TMR |= TMU_TMR_ME_MASK;
    }
    else
    {
        base->TMR &= ~TMU_TMR_ME_MASK;
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
 *                         sensor range of 0-125 °C for an enabled monitored site.
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
 *                         sensor range of 0-125 °C for an enabled monitored site.
 */
status_t TMU_GetLowestTemperature(TMU_Type *base, uint32_t *temperature);

/*!
 * @brief Get the last immediate temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * @param base TMU peripheral base address.
 * @param siteIndex The index of the site user want to read. 0U: site0 ~ 15U: site15.
 * @param temperature Last immediate temperature reading at site n .
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetImmediateTemperature(TMU_Type *base, uint32_t siteIndex, uint32_t *temperature);

/*!
 * @brief Get the last average temperature at site n. The site must be part of the list of enabled
 *        monitored sites as defined by monitorSiteSelection in "tmu_config_t" structure.
 *
 * @param base TMU peripheral base address.
 * @param siteIndex The index of the site user want to read. 0U: site0 ~ 15U: site15.
 * @param temperature Last average temperature reading at site n .
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetAverageTemperature(TMU_Type *base, uint32_t siteIndex, uint32_t *temperature);

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
