/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pwm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ipwm"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance from the base address
 *
 * @param base PWM peripheral base address
 *
 * @return The PWM module instance
 */
static uint32_t PWM_GetInstance(PWM_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to PWM bases for each instance. */
static PWM_Type *const s_pwmBases[] = PWM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of PWM clock name. */
static const clock_ip_name_t s_pwmClock[] = PWM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t PWM_GetInstance(PWM_Type *base)
{
    uint32_t instance;
    uint32_t pwmArrayCount = (sizeof(s_pwmBases) / sizeof(s_pwmBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < pwmArrayCount; instance++)
    {
        if (s_pwmBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < pwmArrayCount);

    return instance;
}

/*!
 * brief Ungates the PWM clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the PWM driver.
 *
 * param base      PWM peripheral base address
 * param config    Pointer to user's PWM config structure.
 *
 * return kStatus_Success means success; else failed.
 */
status_t PWM_Init(PWM_Type *base, const pwm_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate PWM clock */
    CLOCK_EnableClock(s_pwmClock[PWM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Setup the PWM operation */
    base->PWMCR = (PWM_PWMCR_REPEAT(config->sampleRepeat) | PWM_PWMCR_PRESCALER(config->prescale) |
                   PWM_PWMCR_CLKSRC(config->clockSource) | PWM_PWMCR_POUTC(config->outputConfig) |
                   PWM_PWMCR_HCTR(config->halfWordSwap) | PWM_PWMCR_BCTR(config->byteSwap) |
                   PWM_PWMCR_STOPEN(config->enableStopMode) | PWM_PWMCR_DBGEN(config->enableDebugMode) |
                   PWM_PWMCR_WAITEN(config->enableWaitMode) | PWM_PWMCR_DOZEN(config->enableDozeMode) |
                   PWM_PWMCR_FWM(config->fifoWater));

    return kStatus_Success;
}

/*!
 * brief Gate the PWM submodule clock
 *
 * param base      PWM peripheral base address
 */
void PWM_Deinit(PWM_Type *base)
{
    /* Set clock source to none to disable counter */
    base->PWMCR &= ~(PWM_PWMCR_CLKSRC_MASK);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the PWM clock */
    CLOCK_DisableClock(s_pwmClock[PWM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Fill in the PWM config struct with the default settings
 *
 * The default values are:
 * code
 *   config->enableStopMode = false;
 *   config->enableDozeMode = false;
 *   config->enableWaitMode = false;
 *   config->enableDozeMode = false;
 *   config->clockSource = kPWM_LowFrequencyClock;
 *   config->prescale = 0U;
 *   config->outputConfig = kPWM_SetAtRolloverAndClearAtcomparison;
 *   config->fifoWater = kPWM_FIFOWaterMark_2;
 *   config->sampleRepeat = kPWM_EachSampleOnce;
 *   config->byteSwap = kPWM_ByteNoSwap;
 *   config->halfWordSwap = kPWM_HalfWordNoSwap;
 * endcode
 * param config Pointer to user's PWM config structure.
 */
void PWM_GetDefaultConfig(pwm_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Stop mode disabled */
    config->enableStopMode = false;
    /* Doze mode disabled */
    config->enableDozeMode = false;
    /* Wait mode disabled */
    config->enableWaitMode = false;
    /* Debug mode disabled */
    config->enableDebugMode = false;
    /* Choose low frequency clock to control counter operation */
    config->clockSource = kPWM_LowFrequencyClock;
    /* PWM clock devide by (config->prescale + 1) */
    config->prescale = 0U;
    /* Output pin is set at rollover and cleared at comparison */
    config->outputConfig = kPWM_SetAtRolloverAndClearAtcomparison;
    /* FIFO empty flag is set when there are more than or equal to 2 empty slots in FIFO */
    config->fifoWater = kPWM_FIFOWaterMark_2;
    /* Use each sample once */
    config->sampleRepeat = kPWM_EachSampleOnce;
    /* byte ordering remains the same */
    config->byteSwap = kPWM_ByteNoSwap;
    /* Half word swapping does not take place */
    config->halfWordSwap = kPWM_HalfWordNoSwap;
}
