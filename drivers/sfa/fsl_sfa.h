/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SFA_H_
#define FSL_SFA_H_

#include "fsl_common.h"

/*!
 * @addtogroup sfa
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SFA driver version 2.1.2 */
#define FSL_SFA_DRVIER_VERSION (MAKE_VERSION(2, 1, 2))
/*! @} */

#define SFA_CUT_CLK_Enable(val) SFA_CTRL_EXT_CUT_CLK_EN(1UL << (uint32_t)(val))

/*!
 * @brief sfa measure completion callback function pointer type
 *
 * This callback can be used in non blocking IRQHandler.
 * Specify the callback you want in the call to SFA_InstallCallback().
 *
 * @param base SFA peripheral base address.
 * @param status The runtime measurement status.
 *        kStatus_SFA_MeasurementCompleted: The measurement completes.
 *        kStatus_SFA_ReferenceCounterTimeout: Reference counter timeout happenes.
 *        kStatus_SFA_CUTCounterTimeout: CUT counter timeout happenes.
 */
typedef void (*sfa_callback_t)(status_t status);

/*!
 * @brief SFA status return codes.
 *
 * enumeration _sfa_status
 */
enum
{
    kStatus_SFA_MeasurementCompleted         = MAKE_STATUS(kStatusGroup_SFA, 0U),    /*!< Measurement completed */
    kStatus_SFA_ReferenceCounterTimeout      = MAKE_STATUS(kStatusGroup_SFA, 1U),    /*!< Reference counter timeout */
    kStatus_SFA_CUTCounterTimeout            = MAKE_STATUS(kStatusGroup_SFA, 2U),    /*!< CUT counter timeout */
    kStatus_SFA_CUTClockFreqLessThanMinLimit = MAKE_STATUS(kStatusGroup_SFA, 3U),    /*!< CUT clock  frequency less
                                                                                        than minimum limit */
    kStatus_SFA_CUTClockFreqGreaterThanMaxLimit = MAKE_STATUS(kStatusGroup_SFA, 4U), /*!< CUT clock frequency greater
                                                                                        than maximum limit  */
};

/*!
 * @brief List of SFA status flags.
 *
 * The following status register flags can be cleared on any write to REF_CNT.
 * - kSFA_RefStoppedFlag
 * - kSFA_CutStoppedFlag
 * - kSFA_MeasurementStartedFlag
 * - kSFA_ReferenceCounterTimeOutFlag
 *
 * @note These enums are meant to be OR'd together to from a bit mask.
 */
enum _sfa_status_flags
{
    kSFA_RefStoppedFlag                  = SFA_CNT_STAT_REF_STOPPED_MASK,     /*!< Reference counter stopped flag */
    kSFA_CutStoppedFlag                  = SFA_CNT_STAT_CUT_STOPPED_MASK,     /*!< CUT counter stopped flag */
    kSFA_MeasurementStartedFlag          = SFA_CNT_STAT_MEAS_STARTED_MASK,    /*!< Measurement Started flag */
    kSFA_ReferenceCounterTimeOutFlag     = SFA_CNT_STAT_REF_CNT_TIMEOUT_MASK, /*!< Reference counter time out flag */
    kSFA_InterruptRequestFlag            = SFA_CNT_STAT_SFA_IRQ_MASK,         /*!< SFA interrupt request flag */
    kSFA_FreqGreaterThanMaxInterruptFlag = SFA_CNT_STAT_FREQ_GT_MAX_IRQ_MASK, /*!< FREQ_GT_MAX interrupt flag */
    kSFA_FreqLessThanMinInterruptFlag    = SFA_CNT_STAT_FREQ_LT_MIN_IRQ_MASK, /*!< FREQ_LT_MIN interrupt flag */

    kSFA_AllStatusFlags = kSFA_RefStoppedFlag | kSFA_CutStoppedFlag | kSFA_MeasurementStartedFlag |
                          kSFA_ReferenceCounterTimeOutFlag | kSFA_InterruptRequestFlag |
                          kSFA_FreqGreaterThanMaxInterruptFlag | kSFA_FreqLessThanMinInterruptFlag,
};

/*!
 * @brief List of SFA interrupt.
 *
 */
enum _sfa_interrupts_enable
{
    kSFA_InterruptEnable                   = SFA_CTRL_SFA_IRQ_EN_MASK,          /*!< SFA interrupt enable */
    kSFA_FreqGreaterThanMaxInterruptEnable = SFA_CTRL2_FREQ_GT_MAX_IRQ_EN_MASK, /*!< FREQ_GT_MAX interrupt enable */
    kSFA_FreqLessThanMinInterruptEnable    = SFA_CTRL2_FREQ_LT_MIN_IRQ_EN_MASK, /*!< FREQ_LT_MIN interrupt enable */
};

/*!
 * @brief List of SFA measurement mode(Please check the mode configuration according to the manual).
 */
typedef enum _sfa_measurement_mode
{
    kSFA_FrequencyMeasurement0   = 0U, /*!< Frequency measurement performed with REF frequency > CUT frequency  */
    kSFA_FrequencyMeasurement1   = 1U, /*!< Frequency measurement performed with REF frequency < CUT frequency  */
    kSFA_CUTPeriodMeasurement    = 2U, /*!< CUT period measurement performed */
    kSFA_TriggerBasedMeasurement = 3U, /*!< Trigger based measurement performed */
} sfa_measurement_mode_t;

/*!
 * @brief List of CUT which is connected to the CUT counter (Please refer to the manual for configuration).
 */
typedef enum _sfa_cut_select
{
    kSFA_CUTSelect0  = 0U,
    kSFA_CUTSelect1  = 1U,
    kSFA_CUTSelect2  = 2U,
    kSFA_CUTSelect3  = 3U,
    kSFA_CUTSelect4  = 4U,
    kSFA_CUTSelect5  = 5U,
    kSFA_CUTSelect6  = 6U,
    kSFA_CUTSelect7  = 7U,
    kSFA_CUTSelect8  = 8U,
    kSFA_CUTSelect9  = 9U,
    kSFA_CUTSelect10 = 10U,
    kSFA_CUTSelect11 = 11U,
    kSFA_CUTSelect12 = 12U,
    kSFA_CUTSelect13 = 13U,
    kSFA_CUTSelect14 = 14U,
    kSFA_CUTSelect15 = 15U,
} sfa_cut_select_t;

/*!
 * @brief List of REF which is connected to the REF counter (Please refer to the manual for configuration).
 */
typedef enum _sfa_ref_select
{
    kSFA_REFSelect0 = 0U,
    kSFA_REFSelect1 = 1U,
    kSFA_REFSelect2 = 2U,
} sfa_ref_select_t;

/*!
 * @brief List of Signal MUX for Trigger Based Measurement Start.
 */
typedef enum _sfa_trigger_start_select
{
    kSFA_TriggerStartSelect0 = 0U,
    kSFA_TriggerStartSelect1 = 1U,
} sfa_trigger_start_select_t;

/*!
 * @brief List of Signal MUX for Trigger Based Measurement End.
 */
typedef enum _sfa_trigger_end_select
{
    kSFA_TriggerEndSelect0 = 0U,
    kSFA_TriggerEndSelect1 = 1U,
} sfa_trigger_end_select_t;

/*!
 * @brief List of Trigger Start Polarity
 */
typedef enum _sfa_trigger_start_polarity
{
    kSFA_TriggerStartPolarityRiseEdge = 0U, /*!< Rising edge will begin the measurement sequence */
    kSFA_TriggerStartPolarityFallEdge = 1U, /*!< Falling edge will begin the measurement sequence */
} sfa_trigger_start_polarity_t;

/*!
 * @brief List of Trigger End Polarity
 */
typedef enum _sfa_trigger_end_polarity
{
    kSFA_TriggerEndPolarityRiseEdge = 0U, /*!< Rising edge will end the measurement sequence */
    kSFA_TriggerEndPolarityFallEdge = 1U, /*!< Falling edge will end the measurement sequence */
} sfa_trigger_end_polarity_t;

/*!
 * @brief Structure with setting to initialize the SFA module
 *
 * This structure holds configuration setting for the SFA peripheral. To initialize this
 * structure to reasonable defaults, call the SFA_GetDefaultConfig() function and pass a
 * pointer to your configuration structure instance.
 */
typedef struct _sfa_init_config
{
    sfa_measurement_mode_t mode;          /*!< measurement mode */
    sfa_cut_select_t cutSelect;           /*!< Select clock connected to the clock under test counter */
    sfa_ref_select_t refSelect;           /*!< Selcet REF connected the bus clock */
    uint8_t prediv;                       /*!< Integer divide of the Input CUT signal */
    sfa_trigger_start_select_t trigStart; /*!< Select the signal will be used to end a trigger based measurement */
    sfa_trigger_start_polarity_t startPolarity; /*!< Select the polarity of the start trigger signal */
    sfa_trigger_end_select_t trigEnd; /*!< Select the signal will be used to commence a trigger based measurement */
    sfa_trigger_end_polarity_t endPolarity; /*!< Select the polarity of the end trigger signal */
    bool enableTrigMeasurement; /*!< false: The measurement will start by default with a dummy write to the CUT counter;
                                     true : The measurement will start after receiving a dummy write to the REF_CNT
                                   followed by receiving the trigger edge*/
    bool enableCUTPin;          /*!< Control the connection of the clock under test to an external pin. */
    uint32_t refTarget;         /*!< Reference counter target counts*/
    uint32_t cutTarget;         /*!< CUT counter target counts */
} sfa_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and Deinitialization.
 * @{
 */

/*!
 * @brief Fill the SFA configuration structure with default settings.
 *
 * The default values are:
 * @code
 *      config->mode = kSFA_FrequencyMeasurement0;
 *      config->cutSelect = kSFA_CUTSelect0;
 *      config->refSelect = kSFA_REFSelect0;
 *      config->prediv = 0U;
 *      config->trigStart = kSFA_TriggerStartSelect0;
 *      config->startPolarity = kSFA_TriggerStartPolarityRiseEdge;
 *      config->trigEnd = kSFA_TriggerEndSelect0;
 *      config->endPolarity = kSFA_TriggerEndPolarityRiseEdge;
 *      config->enableTrigMeasurement = false;
 *      config->enableCUTPin = false;
 *      config->cutTarget = 0xffffU;
 *      config->refTarget = 0xffffffffU;
 * @endcode
 *
 * @param config Pointer to the user configuration structure.
 */
void SFA_GetDefaultConfig(sfa_config_t *config);

/*!
 * @brief Initialize SFA.
 *
 * @param base SFA peripheral base address.
 */
void SFA_Init(SFA_Type *base);

/*!
 * @brief Clear counter, disable SFA and gate the SFA clock.
 *
 * @param base SFA peripheral base address.
 */
void SFA_Deinit(SFA_Type *base);

/*!
 * @brief Control the connection of the clock under test to an external pin.
 *
 * @param base SFA peripheral base address.
 * @param enable true: connect the clock under test and external pin.
 *               false: Disconnect the clock under test and external pin.
 */
static inline void SFA_EnableCUTPin(SFA_Type *base, bool enable)
{
    if (enable)
    {
#if defined(FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN) && FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN
        base->CTRL_EXT |= SFA_CTRL_EXT_CUT_PIN_EN_MASK;
#endif /* FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN */

        if (1 == FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base))
        {
            base->CTRL |= SFA_CTRL_CUT_PIN_EN_MASK;
        }
    }
    else
    {
#if defined(FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN) && FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN
        base->CTRL_EXT &= ~SFA_CTRL_EXT_CUT_PIN_EN_MASK;
#endif /* FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN */

        if (1 == FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base))
        {
            base->CTRL &= ~SFA_CTRL_CUT_PIN_EN_MASK;
        }
    }
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Get SFA status flags.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetStatusFlags(SFA_Type *base)
{
    return base->CNT_STAT;
}

/*!
 * @brief Clear the SFA status flags.
 *
 * @note To clear kSFA_RefStoppedFlag, kSFA_CUTStoppedFlag, kSFA_MeasurementStartedFlag, and
 * kSFA_ReferenceCounterTimeOutFlag, each counter will also be cleared.
 *
 * @param base SFA peripheral base address.
 * @param mask SFA status flag mask (see @ref _sfa_status_flags for bit definition).
 */
void SFA_ClearStatusFlag(SFA_Type *base, uint32_t mask);

/*! @}*/

/*!
 * @name Interrupts Interface
 * @{
 */

/*!
 * @brief Enable the selected SFA interrupt.
 *
 * @param base SFA peripheral base address.
 * @param mask The interrupt to enable (see @ref _sfa_interrupts_enable for definition).
 */
static inline void SFA_EnableInterrupts(SFA_Type *base, uint32_t mask)
{
    base->CTRL |= (mask & SFA_CTRL_SFA_IRQ_EN_MASK);
    base->CTRL2 |= (mask & (SFA_CTRL2_FREQ_GT_MAX_IRQ_EN_MASK | SFA_CTRL2_FREQ_LT_MIN_IRQ_EN_MASK));
}

/*!
 * @brief Disable the selected SFA interrupt.
 *
 * @param base SFA peripheral base address.
 * @param mask The interrupt to disable (see @ref _sfa_interrupts_enable for definition).
 */
static inline void SFA_DisableInterrupts(SFA_Type *base, uint32_t mask)
{
    base->CTRL &= ~(mask & SFA_CTRL_SFA_IRQ_EN_MASK);
    base->CTRL2 &= ~(mask & (SFA_CTRL2_FREQ_GT_MAX_IRQ_EN_MASK | SFA_CTRL2_FREQ_LT_MIN_IRQ_EN_MASK));
}

/*! @}*/

/*!
 * @name Control SFA Measurement sequence.
 * @{
 */

/*!
 * @brief Get SFA measurement mode.
 *
 * @param base SFA peripheral base address.
 */
static inline uint8_t SFA_GetMode(SFA_Type *base)
{
    return (uint8_t)((base->CTRL & SFA_CTRL_MODE_MASK) >> SFA_CTRL_MODE_SHIFT);
}

/*!
 * @brief Get CUT predivide value.
 *
 * @param base SFA peripheral base address.
 */
static inline uint8_t SFA_GetCUTPredivide(SFA_Type *base)
{
    return (uint8_t)((base->CTRL & SFA_CTRL_CUT_PREDIV_MASK) >> SFA_CTRL_CUT_PREDIV_SHIFT);
}

/*!
 * @brief Install the callback function to be called when IRQ happens or measurement completes.
 *
 * @param base SFA peripheral base address.
 * @param function the SFA measure completed callback function.
 */
void SFA_InstallCallback(SFA_Type *base, sfa_callback_t function);

/*!
 * @brief Set Measurement options with the passed in configuration structure.
 *
 * @param base SFA peripheral base address.
 * @param config SFA configuration structure.
 */
void SFA_SetMeasureConfig(SFA_Type *base, const sfa_config_t *config);

/*!
 * @brief Start SFA measurement in blocking mode.
 *
 * @param base SFA peripheral base address.
 *
 * @retval kStatus_SFA_MeasurementCompleted SFA measure completes.
 * @retval kStatus_SFA_ReferenceCounterTimeout reference counter timeout error happens.
 * @retval kStatus_SFA_CUTCounterTimeout CUT counter time out happens.
 */
status_t SFA_MeasureBlocking(SFA_Type *base);

/*!
 * @brief Start measure sequence in NonBlocking mode.
 *
 * This function performs nonblocking measurement by enabling sfa interrupt (Please enable the FreqGreaterThanMax and
 * FreqLessThanMin interrupts individually as needed). The callback function must be installed before invoking this
 * function.
 * @note This function has different functions for different instances.
 * @param base SFA peripheral base address.
 */
void SFA_MeasureNonBlocking(SFA_Type *base);

/*!
 * @brief Abort SFA measurement sequence.
 *
 * @param base SFA peripheral base address.
 */
void SFA_AbortMeasureSequence(SFA_Type *base);

/*!
 * @brief Calculate the frequency or period.
 *
 * @param base SFA peripheral base address.
 * @param refFrequency The reference clock frequency(BUS clock recommended).
 */
uint32_t SFA_CalculateFrequencyOrPeriod(SFA_Type *base, uint32_t refFrequency);

/*! @}*/

/*!
 * @name Control CUT counter
 * @{
 */

/*!
 * @brief Get current count of the clock under test.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetCUTCounter(SFA_Type *base)
{
    return base->CUT_CNT;
}

/*!
 * @brief Set the target count for the clock under test.
 *
 * @param base SFA peripheral base address.
 * @param count target count for CUT.
 */
static inline void SFA_SetCUTTargetCount(SFA_Type *base, uint32_t count)
{
    base->CUT_TARGET = count;
}

/*!
 * @brief Get the target count of the clock under test.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetCUTTargetCount(SFA_Type *base)
{
    return base->CUT_TARGET;
}

/*!
 * @brief Set CUT low limit clock count.
 *
 * @param base SFA peripheral base address.
 * @param count low limit count for CUT clock.
 */
static inline void SFA_SetCUTLowLimitClockCount(SFA_Type *base, uint32_t count)
{
    base->CUT_LOW_LIMIT_CNT = count;
}

/*!
 * @brief Get CUT low limit clock count.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetCUTLowLimitClockCount(SFA_Type *base)
{
    return base->CUT_LOW_LIMIT_CNT;
}

/*!
 * @brief Set CUT high limit clock count.
 *
 * @param base SFA peripheral base address.
 * @param count high limit count for CUT clock.
 */
static inline void SFA_SetCUTHighLimitClockCount(SFA_Type *base, uint32_t count)
{
    base->CUT_HIGH_LIMIT_CNT = count;
}

/*!
 * @brief Get CUT high limit clock count.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetCUTHighLimitClockCount(SFA_Type *base)
{
    return base->CUT_HIGH_LIMIT_CNT;
}

/*! @}*/

/*!
 * @name Control REF counter
 */

/*!
 * @brief Get current count of the reference clock.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetREFCounter(SFA_Type *base)
{
    return base->REF_CNT;
}

/*!
 * @brief Set the target count for the reference clock.
 *
 * @param base SFA peripheral base address.
 * @param count target count for reference clock.
 */
static inline void SFA_SetREFTargetCount(SFA_Type *base, uint32_t count)
{
    base->REF_TARGET = count;
}

/*!
 * @brief Get the target count of the reference clock
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetREFTargetCount(SFA_Type *base)
{
    return base->REF_TARGET;
}

/*!
 * @brief Get saved reference clock counter which is loaded when measurement start.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetREFStartCount(SFA_Type *base)
{
    return base->REF_CNT_ST_SAVED;
}

/*!
 * @brief Get saved reference clock counter which is loaded when measurement complete.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetREFEndCount(SFA_Type *base)
{
    return base->REF_CNT_END_SAVED;
}

/*!
 * @brief Set REF low limit clock count.
 *
 * @param base SFA peripheral base address.
 * @param count low limit count for REF clock.
 */
static inline void SFA_SetREFLowLimitClockCount(SFA_Type *base, uint32_t count)
{
    base->REF_LOW_LIMIT_CNT = count;
}

/*!
 * @brief Get REF low limit clock count.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetREFLowLimitClockCount(SFA_Type *base)
{
    return base->REF_LOW_LIMIT_CNT;
}

/*!
 * @brief Set REF high limit clock count.
 *
 * @param base SFA peripheral base address.
 * @param count high limit count for REF clock.
 */
static inline void SFA_SetREFHighLimitClockCount(SFA_Type *base, uint32_t count)
{
    base->REF_HIGH_LIMIT_CNT = count;
}

/*!
 * @brief Get REF high limit clock count.
 *
 * @param base SFA peripheral base address.
 */
static inline uint32_t SFA_GetREFHighLimitClockCount(SFA_Type *base)
{
    return base->REF_HIGH_LIMIT_CNT;
}

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_SFA_H_ */
