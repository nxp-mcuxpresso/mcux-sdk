/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sfa.h"

/*
 * $Coverage Justification Reference$
 *
 * $Justification sfa_c_ref_1$
 * The peripheral base address is always valid and checked by assert.
 *
 * $Justification sfa_c_ref_2$
 * If the incoming base can not make (1U == FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base) is true,
 * The following statement will not be executed.
 *
 * $Justification sfa_c_ref_3$
 * If the incoming base can not make (1U == FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base) is true,
 * The connection of the clock under test to the external pin will not be enabled.
 *
 * $Justification sfa_c_ref_4$
 * while ((base->CNT_STAT & SFA_CNT_STAT_CUT_STOPPED_MASK) == 0U) not covered. Test unfeasible,
 * The CUT counter stop state is too short not to catch.
 *
 * $Justification sfa_c_ref_5$
 * ((mode != kSFA_CUTPeriodMeasurement || mode != kSFA_TriggerBasedMeasurement) not covered.
 * All status are covered above.
 *
 * $Justification sfa_c_ref_6$
 * Switch (!= mode) not covered. Other modes cannot be executed.
 *
 * $Justification sfa_c_ref_7$
 * (flags & (uint32_t)kSFA_RefStoppedFlag) == 0U) not covered. Test unfeasible,
 * the reference counter stopped flag state is too short not to catch.
 *
 */

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sfa"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * brief Get the instance from the base address.
 *
 * param base SFA peripheral base address.
 *
 * return The SFA instance.
 */
static uint8_t SFA_GetInstance(SFA_Type *base);

/*!
 * brief Start to measure the frequency of the clock under test.
 *
 * This function starts to measure the frequency of select CUT source.
 * This function does not return until the measurement starts.
 *
 * note If the CUT frequency > REF frequency, it is recommended CUT target be set to 0xFFFF_FFFF.
 *
 *  param base SFA peripheral base address.
 */
static void SFA_StartMeasureFrequency(SFA_Type *base);

/*!
 * brief Start to measure the period of the clock under test or the time between triggers.
 *
 * This function starts to measure the period of the selected CUT source or the time of the selected triggers.
 * This function does not return until the measurement starts.
 *
 * param base SFA peripheral base address.
 */
static void SFA_StartMeasurePeriod(SFA_Type *base);

/*!
 * brief Calculate the frequency of the selected CUT source when the selected mode is mode0.
 *
 * This function calculate the frequency of CUT in mode0 (when CUT frequency < REF frequency).
 *
 * note The unit of this function return value is HZ.
 *
 * param base SFA peripheral base address.
 * param refFrequency reference clock frequency (BUS clock frequency)
 */
static uint32_t SFA_Mode0Calculate(SFA_Type *base, uint32_t refFrequency);

/*!
 * brief Calculate the frequency of the selected CUT source when the selected mode is mode1.
 *
 * This function calculate the frequency of CUT in mode1 (when CUT frequency > REF frequency).
 *
 * note The unit of this function return value is HZ.
 *
 * param base SFA peripheral base address.
 * param refFrequency reference clock frequency (BUS clock frequency)
 */
static uint32_t SFA_Mode1Calculate(SFA_Type *base, uint32_t refFrequency);

/*!
 * brief Calculate the period of the selected CUT source in mode2 or the time of the selected triggers in mode3.
 *
 * In mode2 this function calculate the period of the selected CUT source.
 * In mode3 this function calculate the time of the selected triggers.
 *
 * note The return data is multiple of the reference clock.
 *
 * param base SFA peripheral base address.
 */
static uint32_t SFA_Mode2Mode3Calculate(SFA_Type *base);

/*!
 * brief Measure Frequency in blocking mode.
 *
 * param base SFA peripheral base address.
 * param mode SFA measurement mode.
 *
 * retval kStatus_SFA_ReferenceCounterTimeout error happens.
 * retval kStatus_SFA_MeasurementCompleted measure completes.
 * retval kStatus_SFA_CUTCounterTimeout error happens.
 */
static status_t SFA_MeasureFrequencyBlocking(SFA_Type *base, sfa_measurement_mode_t mode);

/*!
 * brief Measure Period in blocking mode.
 *
 * param base SFA peripheral base address.
 *
 * retval kStatus_SFA_ReferenceCounterTimeout error happens.
 * retval kStatus_SFA_MeasurementCompleted measure completes.
 */
static status_t SFA_MeasurePeriodBlocking(SFA_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! brief Pointers to SFA bases for each instance. */
static SFA_Type *const s_sfaBases[] = SFA_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! brief Pointer to SFA clocks for each instance. */
static clock_ip_name_t const s_sfaClocks[] = SFA_CLOCKS;
#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/

static sfa_callback_t s_sfaIsr[FSL_FEATURE_SOC_SFA_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint8_t SFA_GetInstance(SFA_Type *base)
{
    uint8_t instance;

    /* Find the instance index from base address mappings. */
    /*
     * $Branch Coverage Justification$
     * (instance >= ARRAY_SIZE(s_sfaBases)) not covered.
     * $ref sfa_c_ref_1$.
     */
    for (instance = 0U; instance < ARRAY_SIZE(s_sfaBases); instance++)
    {
        /*
         * $Branch Coverage Justification$
         * (s_sfaBases[instance] != base) not covered.
         * $ref sfa_c_ref_1$.
         */
        if (MSDK_REG_SECURE_ADDR(s_sfaBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_sfaBases));

    return instance;
}

static void SFA_StartMeasureFrequency(SFA_Type *base)
{
    bool triggerable = false;

#if defined(RF_SFA)
    /*
     * $Branch Coverage Justification$
     * (1U != FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base) not covered.
     * $ref sfa_c_ref_2$.
     */
    if (1 == FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base))
    {
        /*
         * $Line Coverage Justification$
         * $ref sfa_c_ref_2$.
         */
        triggerable = ((base->CTRL & SFA_CTRL_SFA_TRIG_MEAS_EN_MASK) != 0U);
    }
#endif

    (*(volatile uint32_t *)&(base->REF_CNT)) = 0U; /* Dummy write to REF counter. */

    /* Poll the CUT_STOPPED bit to make sure it cleared. */
    /*
     * $Branch Coverage Justification$
     * $ref sfa_c_ref_4$.
     */
    while ((base->CNT_STAT & SFA_CNT_STAT_CUT_STOPPED_MASK) != 0U)
    {
        ;
    }
    /*
     * $Branch Coverage Justification$
     * (true == triggerable) not covered. The trigger measurement function does not have enable.
     */
    if (!triggerable)
    {
        (*(volatile uint32_t *)&(base->CUT_CNT)) = 0U; /* Dummy write to CUT counter. */
        while (0U == (base->CNT_STAT & SFA_CNT_STAT_MEAS_STARTED_MASK))
        {
            ; /* Loop until measurement start. */
        }
    }
}

static void SFA_StartMeasurePeriod(SFA_Type *base)
{
    (*(volatile uint32_t *)&(base->REF_CNT)) = 0U; /* Dummy write to REF counter. */
    /*
     * $Branch Coverage Justification$
     * $ref sfa_c_ref_4$.
     */
    while ((base->CNT_STAT & SFA_CNT_STAT_CUT_STOPPED_MASK) != 0U)
    {
        ;
    }

    while (0U == (base->CNT_STAT & SFA_CNT_STAT_MEAS_STARTED_MASK))
    {
        ; /* Loop until measurement start. */
    }
}

static uint32_t SFA_Mode0Calculate(SFA_Type *base, uint32_t refFrequency)
{
    uint64_t frequency;
    uint8_t prediv;

    prediv    = SFA_GetCUTPredivide(base);
    frequency = ((uint64_t)SFA_GetCUTCounter(base) - 1ULL) * (uint64_t)refFrequency;
    frequency += (((uint64_t)SFA_GetREFEndCount(base) - (uint64_t)SFA_GetREFStartCount(base))) >> 1;
    frequency /= ((uint64_t)SFA_GetREFEndCount(base) - (uint64_t)SFA_GetREFStartCount(base));
    if (prediv > 1U)
    {
        /* If the cut predivide is provided. */
        frequency *= prediv;
    }
    return (uint32_t)frequency;
}

static uint32_t SFA_Mode1Calculate(SFA_Type *base, uint32_t refFrequency)
{
    uint64_t frequency;
    uint8_t prediv;

    prediv    = SFA_GetCUTPredivide(base);
    frequency = ((uint64_t)SFA_GetCUTCounter(base) - 1ULL) * (uint64_t)refFrequency;
    frequency /= (uint64_t)SFA_GetREFTargetCount(base);
    if (prediv > 1U)
    {
        /* If the cut predivide is provided. */
        frequency *= prediv;
    }
    return (uint32_t)frequency;
}

static uint32_t SFA_Mode2Mode3Calculate(SFA_Type *base)
{
    uint32_t count;
    uint8_t prediv;

    prediv = SFA_GetCUTPredivide(base);
    count  = SFA_GetREFEndCount(base) - SFA_GetREFStartCount(base);
    if (prediv > 1U)
    {
        /* If the cut predivide is provided. */
        count /= prediv;
    }
    return count;
}

static status_t SFA_MeasureFrequencyBlocking(SFA_Type *base, sfa_measurement_mode_t mode)
{
    status_t status = kStatus_Success;

    if (mode == kSFA_FrequencyMeasurement0)
    {
        while (((base->CNT_STAT & SFA_CNT_STAT_REF_STOPPED_MASK) == 0U) ||
               ((base->CNT_STAT & SFA_CNT_STAT_CUT_STOPPED_MASK) == 0U))
        {
            ;
        }
        if ((base->CNT_STAT & SFA_CNT_STAT_REF_CNT_TIMEOUT_MASK) != 0U)
        {
            /* REF counter reached the target before CUT counter reaching target,
             * Reference clock timeout occurred. */
            status = kStatus_SFA_ReferenceCounterTimeout;
        }
        else
        {
            status = kStatus_SFA_MeasurementCompleted;
        }
    }
    else
    {
        while (0U == (base->CNT_STAT & SFA_CNT_STAT_CUT_STOPPED_MASK))
        {
            ;
        }
        if ((base->CUT_CNT) < (base->CUT_TARGET))
        {
            status = kStatus_SFA_MeasurementCompleted;
        }
        else
        {
            /* CUT counter reached target, CUT timeout occurred. */
            status = kStatus_SFA_CUTCounterTimeout;
        }
    }
    return status;
}

static status_t SFA_MeasurePeriodBlocking(SFA_Type *base)
{
    status_t status = kStatus_Success;

    while (0U == (base->CNT_STAT & SFA_CNT_STAT_REF_STOPPED_MASK))
    {
        ;
    }
    if ((base->CNT_STAT & SFA_CNT_STAT_REF_CNT_TIMEOUT_MASK) != 0U)
    {
        /* REF counter reached the target before SFA receiving a full period or
         * before receiving trigger end signal. */
        status = kStatus_SFA_ReferenceCounterTimeout;
    }
    else
    {
        status = kStatus_SFA_MeasurementCompleted;
    }
    return status;
}

/*!
 * brief Clear the SFA status flags.
 *
 * note To clear kSFA_RefStoppedFlag, kSFA_CUTStoppedFlag, kSFA_MeasurementStartedFlag, and
 * kSFA_ReferenceCounterTimeOutFlag, each counter will also be cleared.
 *
 * param base SFA peripheral base address.
 * param mask SFA status flag mask (see @ref _sfa_status_flags for bit definition).
 */
void SFA_ClearStatusFlag(SFA_Type *base, uint32_t mask)
{
    /* Clear interrupt status flag */
    base->CNT_STAT =
        (mask & (SFA_CNT_STAT_SFA_IRQ_MASK | SFA_CNT_STAT_FREQ_GT_MAX_IRQ_MASK | SFA_CNT_STAT_FREQ_LT_MIN_IRQ_MASK));

    if ((mask & ((uint32_t)kSFA_RefStoppedFlag | (uint32_t)kSFA_CutStoppedFlag | (uint32_t)kSFA_MeasurementStartedFlag |
                 (uint32_t)kSFA_ReferenceCounterTimeOutFlag)) != 0UL)
    {
        /* Dummy write REF counter to clear each counter, kSFA_RefStoppedFlag, kSFA_CutStoppedFlag,
         kSFA_MeasurementStartedFlag, kSFA_ReferenceCounterTimeOutFlag. */
        (*(volatile uint32_t *)&(base->REF_CNT)) = 0U;
    }
}

/*!
 * brief Fill the SFA configuration structure with default settings.
 *
 * The default values are:
 * code
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
 * endcode
 *
 * param config Pointer to the user configuration structure.
 */
void SFA_GetDefaultConfig(sfa_config_t *config)
{
    assert(config);

    (void *)memset(config, 0, sizeof(*config));

    config->mode                  = kSFA_FrequencyMeasurement0;
    config->cutSelect             = kSFA_CUTSelect0;
    config->refSelect             = kSFA_REFSelect0;
    config->prediv                = 0U;
    config->trigStart             = kSFA_TriggerStartSelect0;
    config->startPolarity         = kSFA_TriggerStartPolarityRiseEdge;
    config->trigEnd               = kSFA_TriggerEndSelect0;
    config->endPolarity           = kSFA_TriggerEndPolarityRiseEdge;
    config->enableTrigMeasurement = false;
    config->enableCUTPin          = false;
    config->cutTarget             = 0xffffU;
    config->refTarget             = 0xffffffffU;
}

/*!
 * brief Initialize SFA.
 *
 * param base SFA peripheral base address.
 */
void SFA_Init(SFA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(s_sfaClocks[SFA_GetInstance(base)]);
#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/

    /* dummy write REF_CNT to clear each counters and status flags */
    (*(volatile uint32_t *)&(base->REF_CNT)) = 0U;
}

/*!
 * brief Clear counter, disable SFA and gate the SFA clock.
 *
 * param base SFA peripheral base address.
 */
void SFA_Deinit(SFA_Type *base)
{
    (*(volatile uint32_t *)&(base->REF_CNT)) = 0U; /* Dummy write REF counter to clear flags and counters. */
    while ((base->CNT_STAT & SFA_CNT_STAT_CUT_STOPPED_MASK) != 0U)
    {
        ;
    }
    base->CTRL &= ~SFA_CTRL_SFA_EN_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_sfaClocks[SFA_GetInstance(base)]);
#endif /*FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL*/
}

/*!
 * brief Set Measurement options with the passed in configuration structure.
 *
 * param base SFA peripheral base address.
 * param config SFA configuration structure.
 */
void SFA_SetMeasureConfig(SFA_Type *base, const sfa_config_t *config)
{
    assert(config);
    assert(((1 != FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base)) &&
            ((config->refSelect < kSFA_REFSelect2) && (config->cutSelect < kSFA_CUTSelect2))) ||
           (1 == FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base)));
    assert(((1 != FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base)) && (config->mode < kSFA_TriggerBasedMeasurement)) ||
           (1 == FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base)));

    sfa_measurement_mode_t mode;

    mode = config->mode;

    /* Enable selected clock under test source. */
    base->CTRL_EXT |= SFA_CUT_CLK_Enable(config->cutSelect);

    /* Enable selected REF clock. */
    base->CTRL2 = (base->CTRL2 & ~SFA_CTRL2_REF_CLK_SEL_MASK) | SFA_CTRL2_REF_CLK_SEL(config->refSelect);

    if (config->enableCUTPin)
    {
#if defined(FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN) && FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN
        base->CTRL_EXT |= SFA_CTRL_EXT_CUT_PIN_EN_MASK;
#endif
        /*
         * $Branch Coverage Justification$
         * (1 != FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base)) not covered.
         * $ref sfa_c_ref_3$.
         */
        if (1 == FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base))
        {
            base->CTRL |= SFA_CTRL_CUT_PIN_EN_MASK;
        }
    }
    else
    {
#if defined(FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN) && FSL_FEATURE_SFA_CTRL_EXT_HAS_CUT_PIN_EN
        base->CTRL_EXT &= ~SFA_CTRL_EXT_CUT_PIN_EN_MASK;
#endif
        /*
         * $Branch Coverage Justification$
         * (1 != FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base)) not covered.
         * $ref sfa_c_ref_3$.
         */
        if (1 == FSL_FEATURE_SFA_CTRL_HAS_CUT_PIN_ENn(base))
        {
            base->CTRL &= ~SFA_CTRL_CUT_PIN_EN_MASK;
        }
    }

    /* Before modifying measurement basic options, disable SFA general enable signal. */
    base->CTRL &= ~SFA_CTRL_SFA_EN_MASK;
    switch (mode)
    {
        case kSFA_FrequencyMeasurement0:
        case kSFA_FrequencyMeasurement1:
        {
            base->CTRL =
                SFA_CTRL_MODE(config->mode) | SFA_CTRL_CUT_SEL(config->cutSelect) | SFA_CTRL_CUT_PREDIV(config->prediv);

#if defined(RF_SFA)
            /*
             * $Branch Coverage Justification$
             * (1U != FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base) not covered.
             * $ref sfa_c_ref_2$.
             */
            if (1 == FSL_FEATURE_SFA_INSTANCE_HAS_TRIGGERn(base))
            {
                /*
                 * $Line Coverage Justification$
                 * $ref sfa_c_ref_2$.
                 */
                if (config->enableTrigMeasurement)
                {
                    base->CTRL |= SFA_CTRL_SFA_TRIG_MEAS_EN_MASK;
                    base->CTRL |=
                        SFA_CTRL_TRIG_START_SEL(config->trigStart) | SFA_CTRL_TRIG_START_POL(config->startPolarity);
                }
                else
                {
                    base->CTRL &= ~SFA_CTRL_SFA_TRIG_MEAS_EN_MASK;
                }
            }
#endif
            base->CTRL |= SFA_CTRL_SFA_EN_MASK;

            SFA_SetCUTTargetCount(base, config->cutTarget);
            SFA_SetREFTargetCount(base, config->refTarget);
            break;
        }
        case kSFA_CUTPeriodMeasurement:
        {
            base->CTRL =
                SFA_CTRL_MODE(config->mode) | SFA_CTRL_CUT_SEL(config->cutSelect) | SFA_CTRL_CUT_PREDIV(config->prediv);

            base->CTRL |= SFA_CTRL_SFA_EN_MASK;

            SFA_SetREFTargetCount(base, config->refTarget);
            break;
        }
        case kSFA_TriggerBasedMeasurement:
        {
#if defined(RF_SFA)
            base->CTRL = SFA_CTRL_MODE(config->mode) | SFA_CTRL_TRIG_START_SEL(config->trigStart) |
                         SFA_CTRL_TRIG_START_POL(config->startPolarity) | SFA_CTRL_TRIG_END_SEL(config->trigEnd) |
                         SFA_CTRL_TRIG_END_POL(config->endPolarity);

            base->CTRL |= SFA_CTRL_SFA_EN_MASK;

            SFA_SetREFTargetCount(base, config->refTarget);
#endif
            break;
        }
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Install the callback routine to be called when IRQ happens or measurement completes.
 *
 * param base SFA peripheral base address.
 * param function the SFA measure completed callback function.
 */
void SFA_InstallCallback(SFA_Type *base, sfa_callback_t function)
{
    assert(function);
    assert(1 == FSL_FEATURE_SFA_INSTANCE_HAS_INTERRUPTn(base));

    uint8_t instance;

    instance = SFA_GetInstance(base);
    if (s_sfaIsr[instance] == NULL)
    {
        s_sfaIsr[instance] = function;
    }
}

/*!
 * brief Start SFA measurement in blocking mode
 *
 * This function start SFA measurement based on the configged mode.
 * The user must config measure mode before invoking this function.
 * This function will return the measurement status until measure completes or timeout error happens.
 *
 * param base SFA peripheral base address.
 *
 * retval kStatus_SFA_MeasurementCompleted SFA measure completes.
 * retval kStatus_SFA_ReferenceCounterTimeout reference counter timeout error happens.
 * retval kStatus_SFA_CUTCounterTimeout CUT counter time out happens.
 */
status_t SFA_MeasureBlocking(SFA_Type *base)
{
    sfa_measurement_mode_t mode;
    status_t status = kStatus_Success;

    mode = (sfa_measurement_mode_t)SFA_GetMode(base);

    if (mode == kSFA_FrequencyMeasurement0 || mode == kSFA_FrequencyMeasurement1)
    {
        SFA_StartMeasureFrequency(base);
        status = SFA_MeasureFrequencyBlocking(base, mode);
    }
    /*
     * $Branch Coverage Justification$
     * $ref sfa_c_ref_5$.
     */
    else if (mode == kSFA_CUTPeriodMeasurement || mode == kSFA_TriggerBasedMeasurement)
    {
        SFA_StartMeasurePeriod(base);
        status = SFA_MeasurePeriodBlocking(base);
    }
    else
    {
        /* Add comments to prevent the case of MISRA C-2012 rule 15.7. */
    }

    return status;
}

/*!
 * brief Start measure sequence in NonBlocking mode.
 *
 * This function performs nonblocking measurement by enabling sfa interrupt (Please enable the FreqGreaterThanMax and
 * FreqLessThanMin interrupts individually as needed). The callback function must be installed before invoking this
 * function.
 * note This function has different functions for different instances.
 * param base SFA peripheral base address.
 */
void SFA_MeasureNonBlocking(SFA_Type *base)
{
    assert(1 == FSL_FEATURE_SFA_INSTANCE_HAS_INTERRUPTn(base));

    sfa_measurement_mode_t mode;

    mode = (sfa_measurement_mode_t)SFA_GetMode(base);

    SFA_EnableInterrupts(base, (uint32_t)kSFA_InterruptEnable);

    if (mode == kSFA_FrequencyMeasurement0 || mode == kSFA_FrequencyMeasurement1)
    {
        SFA_StartMeasureFrequency(base);
    }
    /*
     * $Branch Coverage Justification$
     * $ref sfa_c_ref_5$.
     */
    else if (mode == kSFA_CUTPeriodMeasurement || mode == kSFA_TriggerBasedMeasurement)
    {
        SFA_StartMeasurePeriod(base);
    }
    else
    {
        /* Add comments to prevent the case of MISRA C-2012 ruel 15.7. */
    }
}

/*!
 * brief Abort SFA measurement sequence.
 *
 * This function will clear each counters and each status flags firstly, and then disable SFA.
 *
 * param base SFA peripheral base address.
 */
void SFA_AbortMeasureSequence(SFA_Type *base)
{
    /* Dummy write REF counter to clear each counters and status flags. */
    (*(volatile uint32_t *)&(base->REF_CNT)) = 0U;
    base->CTRL &= ~SFA_CTRL_SFA_EN_MASK;
}

/*!
 * brief Calculate the frequency or period.
 *
 * This funcion will calculate the frequency or period based on configged measure mode.
 * This function must be invoked after the measurement completes.
 *
 * note This function returns frequency with Hz as the unit when used to calculate frequency.
 * note This function returns period with the counts of reference clock when used to calculate period or triggers time.
 *
 * param base SFA peripheral base address.
 * param refFrequency The reference clock frequency(BUS clock recommended).
 */
uint32_t SFA_CalculateFrequencyOrPeriod(SFA_Type *base, uint32_t refFrequency)
{
    sfa_measurement_mode_t mode;
    uint32_t result;

    mode = (sfa_measurement_mode_t)SFA_GetMode(base);
    /*
     * $Branch Coverage Justification$
     * $ref sfa_c_ref_6$.
     */
    switch (mode)
    {
        case kSFA_FrequencyMeasurement0:
        {
            result = SFA_Mode0Calculate(base, refFrequency);
            break;
        }
        case kSFA_FrequencyMeasurement1:
        {
            result = SFA_Mode1Calculate(base, refFrequency);
            break;
        }
        case kSFA_CUTPeriodMeasurement:
        case kSFA_TriggerBasedMeasurement:
        {
            result = SFA_Mode2Mode3Calculate(base);
            break;
        }
            /*
             * $Line Coverage Justification$
             * $ref sfa_c_ref_6$.
             */
        default:
            assert(false);
            break;
    }
    return result;
}

/*!
 * brief Common IRQ handler for each instance.
 *
 * If enable SFA IRQ, this function will be invoked when the measurement is complete.
 * The installed callback function will be invoked with status as the parameter.
 *
 * param base SFA peripheral base address.
 */
static void SFA_CommonIRQHandler(SFA_Type *base)
{
    uint8_t instance;
    sfa_measurement_mode_t mode;
    status_t status = kStatus_Success;
    uint32_t flags;

    instance = (uint8_t)SFA_GetInstance(base);
    flags    = SFA_GetStatusFlags(base);

    assert(s_sfaIsr[instance]);

    if ((flags & (uint32_t)kSFA_InterruptRequestFlag) != 0U)
    {
        mode = (sfa_measurement_mode_t)SFA_GetMode(base);

        SFA_ClearStatusFlag(base, (uint32_t)kSFA_InterruptRequestFlag);
        SFA_DisableInterrupts(base, (uint32_t)kSFA_InterruptEnable);
        /*
         * $Branch Coverage Justification$
         * $ref sfa_c_ref_6$.
         */
        switch (mode)
        {
            case kSFA_FrequencyMeasurement0:
            {
                /*
                 * $Branch Coverage Justification$
                 * ((flags & ((uint32_t)kSFA_RefStoppedFlag | (uint32_t)kSFA_CutStoppedFlag)) == 0U) not covered. Test
                 * unfeasible, the Reference counter stopped flag and CUT counter stopped flag state is too short to
                 * catch.
                 */
                if ((flags & ((uint32_t)kSFA_RefStoppedFlag | (uint32_t)kSFA_CutStoppedFlag)) != 0U)
                {
                    status = kStatus_SFA_MeasurementCompleted;
                }
                /*
                 * $Branch Coverage Justification$
                 * ((flags & (uint32_t)kSFA_ReferenceCounterTimeOutFlag) == 0U) not covered. Test unfeasible,
                 * the Reference counter time out flag state is too short to catch.
                 */
                if ((flags & (uint32_t)kSFA_ReferenceCounterTimeOutFlag) != 0U)
                {
                    status = kStatus_SFA_ReferenceCounterTimeout;
                }
                break;
            }
            case kSFA_FrequencyMeasurement1:
            {
                /*
                 * $Branch Coverage Justification$
                 * $ref sfa_c_ref_7$.
                 */
                if ((flags & (uint32_t)kSFA_RefStoppedFlag) != 0U)
                {
                    status = kStatus_SFA_MeasurementCompleted;
                }
                if (SFA_GetCUTCounter(base) >= SFA_GetCUTTargetCount(base))
                {
                    status = kStatus_SFA_CUTCounterTimeout;
                }
                break;
            }
            case kSFA_CUTPeriodMeasurement:
            case kSFA_TriggerBasedMeasurement:
            {
                /*
                 * $Branch Coverage Justification$
                 * $ref sfa_c_ref_7$.
                 */
                if ((flags & (uint32_t)kSFA_RefStoppedFlag) != 0U)
                {
                    status = kStatus_SFA_MeasurementCompleted;
                }
                if ((flags & (uint32_t)kSFA_ReferenceCounterTimeOutFlag) != 0U)
                {
                    status = kStatus_SFA_ReferenceCounterTimeout;
                }
                break;
            }
                /*
                 * $Line Coverage Justification$
                 * $ref sfa_c_ref_6$.
                 */
            default:
                assert(false);
                break;
        }
    }
    else if ((flags & (uint32_t)kSFA_FreqLessThanMinInterruptFlag) != 0U)
    {
        SFA_ClearStatusFlag(base, (uint32_t)kSFA_FreqLessThanMinInterruptFlag);
        SFA_DisableInterrupts(base, (uint32_t)kSFA_FreqLessThanMinInterruptEnable);
        status = kStatus_SFA_CUTClockFreqLessThanMinLimit;
    }
    /*
     * $Branch Coverage Justification$
     * ((flags & (uint32_t)kSFA_FreqGreaterThanMaxInterruptFlag) == 0U) not covered. All status are covered above.
     */
    else if ((flags & (uint32_t)kSFA_FreqGreaterThanMaxInterruptFlag) != 0U)
    {
        SFA_ClearStatusFlag(base, (uint32_t)kSFA_FreqGreaterThanMaxInterruptFlag);
        SFA_DisableInterrupts(base, (uint32_t)kSFA_FreqGreaterThanMaxInterruptEnable);
        status = kStatus_SFA_CUTClockFreqGreaterThanMaxLimit;
    }
    else
    {
        /* Add comments to prevent the case of MISRA C-2012 ruel 15.7. */
    }

    s_sfaIsr[instance](status);

    SDK_ISR_EXIT_BARRIER;
}

#if defined(SFA0)
void SFA0_DriverIRQHandler(void);
void SFA0_DriverIRQHandler(void)
{
    SFA_CommonIRQHandler(SFA0);
}
#endif

#if defined(RF_SFA)
void RF_SFA_DriverIRQHandler(void);
void RF_SFA_DriverIRQHandler(void)
{
    SFA_CommonIRQHandler(RF_SFA);
}
#endif