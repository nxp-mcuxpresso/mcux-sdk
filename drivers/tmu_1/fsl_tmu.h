/*
 * Copyright 2018-2020, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_TMU_H__
#define __FSL_TMU_H__

#include "fsl_common.h"

/*!
 * @addtogroup tmu
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief TMU driver version. */
#define FSL_TMU_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)) /*!< Version 2.1.1. */

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
 * @brief configuration for TMU thresold.
 */
typedef struct _tmu_thresold_config
{
    bool immediateThresoldEnable;       /*!< Enable high temperature immediate threshold. */
    bool AverageThresoldEnable;         /*!< Enable high temperature average threshold. */
    bool AverageCriticalThresoldEnable; /*!< Enable high temperature average critical threshold. */
    uint8_t immediateThresoldValue; /*!< Range:10U-125U. Valid when corresponding threshold is enabled. High temperature
                                       immediate threshold value.
                                               Determines the current upper temperature threshold, for any enabled
                                       monitored site. */
    uint8_t averageThresoldValue;   /*!< Range:10U-125U. Valid when corresponding threshold is enabled. High temperature
                                       average threshold value.
                                               Determines the average upper temperature threshold, for any enabled
                                       monitored site. */
    uint8_t averageCriticalThresoldValue; /*!< Range:10U-125U. Valid when corresponding threshold is enabled. High
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
 * @brief Amplifier gain setting.
 */
typedef enum _tmu_amplifier_gain
{
    kTMU_AmplifierGain6_34  = 0U,  /*!< TMU amplifier gain voltage 6.34mV. */
    kTMU_AmplifierGain6_485 = 1U,  /*!< TMU amplifier gain voltage 6.485mV. */
    kTMU_AmplifierGain6_63  = 2U,  /*!< TMU amplifier gain voltage 6.63mV. */
    kTMU_AmplifierGain6_775 = 3U,  /*!< TMU amplifier gain voltage 6.775mV. */
    kTMU_AmplifierGain6_92  = 4U,  /*!< TMU amplifier gain voltage 6.92mV. */
    kTMU_AmplifierGain7_065 = 5U,  /*!< TMU amplifier gain voltage 7.065mV. */
    kTMU_AmplifierGain7_21  = 6U,  /*!< TMU amplifier gain voltage 7.21mV. */
    kTMU_AmplifierGain7_355 = 7U,  /*!< TMU amplifier gain voltage 7.355mV. */
    kTMU_AmplifierGain7_5   = 8U,  /*!< TMU amplifier gain voltage 7.5mV. */
    kTMU_AmplifierGain7_645 = 9U,  /*!< TMU amplifier gain voltage 7.645mV. */
    kTMU_AmplifierGain7_79  = 10U, /*!< TMU amplifier gain voltage 7.79mV. */
    kTMU_AmplifierGain7_935 = 11U, /*!< TMU amplifier gain voltage 7.935mV. */
    kTMU_AmplifierGain8_08  = 12U, /*!< TMU amplifier gain voltage 8.08mV(default). */
    kTMU_AmplifierGain8_225 = 13U, /*!< TMU amplifier gain voltage 8.225mV. */
    kTMU_AmplifierGain8_37  = 14U, /*!< TMU amplifier gain voltage 8.37mV. */
    kTMU_AmplifierGain8_515 = 15U, /*!< TMU amplifier gain voltage 8.515mV. */
} tmu_amplifier_gain_t;

/*!
 * @brief Amplifier reference voltage setting.
 */
typedef enum _tmu_amplifier_reference_voltage
{
    kTMU_AmplifierReferenceVoltage510   = 0U,  /*!< TMU amplifier reference voltage 510mV. */
    kTMU_AmplifierReferenceVoltage517_5 = 1U,  /*!< TMU amplifier reference voltage 517.5mV. */
    kTMU_AmplifierReferenceVoltage525   = 2U,  /*!< TMU amplifier reference voltage 525mV. */
    kTMU_AmplifierReferenceVoltage532_5 = 3U,  /*!< TMU amplifier reference voltage 532.5mV. */
    kTMU_AmplifierReferenceVoltage540   = 4U,  /*!< TMU amplifier reference voltage 540mV. */
    kTMU_AmplifierReferenceVoltage547_5 = 5U,  /*!< TMU amplifier reference voltage 547.5mV. */
    kTMU_AmplifierReferenceVoltage555   = 6U,  /*!< TMU amplifier reference voltage 555mV. */
    kTMU_AmplifierReferenceVoltage562_5 = 7U,  /*!< TMU amplifier reference voltage 562.5mV. */
    kTMU_AmplifierReferenceVoltage570   = 8U,  /*!< TMU amplifier reference voltage 570mV. */
    kTMU_AmplifierReferenceVoltage577_5 = 9U,  /*!< TMU amplifier reference voltage 577.5mV. */
    kTMU_AmplifierReferenceVoltage585   = 10U, /*!< TMU amplifier reference voltage 585mV. */
    kTMU_AmplifierReferenceVoltage592_5 = 11U, /*!< TMU amplifier reference voltage 592.5mV. */
    kTMU_AmplifierReferenceVoltage600   = 12U, /*!< TMU amplifier reference voltage 600mV. */
    kTMU_AmplifierReferenceVoltage607_5 = 13U, /*!< TMU amplifier reference voltage 607.5mV. */
    kTMU_AmplifierReferenceVoltage615   = 14U, /*!< TMU amplifier reference voltage 615mV. */
    kTMU_AmplifierReferenceVoltage622_5 = 15U, /*!< TMU amplifier reference voltage 622.5mV. */
    kTMU_AmplifierReferenceVoltage630   = 16U, /*!< TMU amplifier reference voltage 630mV. */
    kTMU_AmplifierReferenceVoltage637_5 = 17U, /*!< TMU amplifier reference voltage 637.5mV. */
    kTMU_AmplifierReferenceVoltage645   = 18U, /*!< TMU amplifier reference voltage 645mV. */
    kTMU_AmplifierReferenceVoltage652_5 = 19U, /*!< TMU amplifier reference voltage 652.5mV(default). */
    kTMU_AmplifierReferenceVoltage660   = 20U, /*!< TMU amplifier reference voltage 660mV. */
    kTMU_AmplifierReferenceVoltage667_5 = 21U, /*!< TMU amplifier reference voltage 667.5mV. */
    kTMU_AmplifierReferenceVoltage675   = 22U, /*!< TMU amplifier reference voltage 675mV. */
    kTMU_AmplifierReferenceVoltage682_5 = 23U, /*!< TMU amplifier reference voltage 682.5mV. */
    kTMU_AmplifierReferenceVoltage690   = 24U, /*!< TMU amplifier reference voltage 690mV. */
    kTMU_AmplifierReferenceVoltage697_5 = 25U, /*!< TMU amplifier reference voltage 697.5mV. */
    kTMU_AmplifierReferenceVoltage705   = 26U, /*!< TMU amplifier reference voltage 705mV. */
    kTMU_AmplifierReferenceVoltage712_5 = 27U, /*!< TMU amplifier reference voltage 712.5mV. */
    kTMU_AmplifierReferenceVoltage720   = 28U, /*!< TMU amplifier reference voltage 720mV. */
    kTMU_AmplifierReferenceVoltage727_5 = 29U, /*!< TMU amplifier reference voltage 727.5mV. */
    kTMU_AmplifierReferenceVoltage735   = 30U, /*!< TMU amplifier reference voltage 735mV. */
    kTMU_AmplifierReferenceVoltage742_5 = 31U, /*!< TMU amplifier reference voltage 742.5mV. */
} tmu_amplifier_reference_voltage_t;

/*!
 * @brief Configuration for TMU module.
 */
typedef struct _tmu_config
{
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
   config->averageLPF = kTMU_AverageLowPassFilter0_5;
   @endcode
 *
 * @param config Pointer to TMU configuration structure.
 */
void TMU_GetDefaultConfig(tmu_config_t *config);

/*!
 * @brief Enable/Disable monitoring the temperature sensor.
 *
 * @param base TMU peripheral base address.
 * @param enable Switcher to enable/disable TMU.
 */
static inline void TMU_Enable(TMU_Type *base, bool enable)
{
    if (enable)
    {
        base->TER |= TMU_TER_EN_MASK;
    }
    else
    {
        base->TER &= ~TMU_TER_EN_MASK;
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
 * @brief Clear interrupt status flags.
 *
 * @param base TMU peripheral base address.
 * @param mask The mask of interrupt status flags. Refer to "_tmu_interrupt_status_flags" enumeration.
 */
void TMU_ClearInterruptStatusFlags(TMU_Type *base, uint32_t mask);

/*!
 * @brief Get the last immediate temperature at site.
 *
 * @param base TMU peripheral base address.
 * @param temperature Last immediate temperature reading at site when V=1.
 *
 * @return Execution status.
 * @retval kStatus_Success Temperature reading is valid.
 * @retval kStatus_Fail    Temperature reading is not valid because temperature out of sensor range or
 *                         first measurement still pending.
 */
status_t TMU_GetImmediateTemperature(TMU_Type *base, uint32_t *temperature);

/*!
 * @brief Get the last average temperature at site.
 *
 * @param base TMU peripheral base address.
 * @param temperature Last average temperature reading at site.
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

/*@}*/

#endif /* __FSL_TMU_H__ */
