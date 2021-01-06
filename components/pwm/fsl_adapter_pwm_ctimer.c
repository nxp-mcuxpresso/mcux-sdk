/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_pwm.h"
#include "fsl_ctimer.h"

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
typedef struct _hal_pwm_handle_struct_t
{
    uint32_t pwmClock_Hz;
    uint8_t instance;
    uint8_t pwmLevelSelect;
} hal_pwm_handle_struct_t;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static CTIMER_Type *const s_cTimerBase[]                                        = CTIMER_BASE_PTRS;
static uint8_t s_pwmUsedChannel[sizeof(s_cTimerBase) / sizeof(s_cTimerBase[0])] = {0};

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_pwm_status_t HAL_PwmInit(hal_pwm_handle_t halPwmHandle, uint8_t instance, uint32_t srcClock_Hz)
{
    ctimer_config_t ctimerInfo;
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(halPwmHandle);
    assert(instance < (uint8_t)FSL_FEATURE_SOC_CTIMER_COUNT);
    assert(sizeof(hal_pwm_handle_struct_t) == HAL_PWM_HANDLE_SIZE);
    halPwmState->pwmClock_Hz = srcClock_Hz;
    halPwmState->instance    = instance;

    /* Initialize CTIMER module */
    if (0U == s_pwmUsedChannel[instance])
    {
        CTIMER_GetDefaultConfig(&ctimerInfo);
        CTIMER_Init(s_cTimerBase[instance], &ctimerInfo);
    }

    return kStatus_HAL_PwmSuccess;
}

void HAL_PwmDeinit(hal_pwm_handle_t halPwmHandle)
{
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(halPwmHandle);
    assert(halPwmState->instance < (uint8_t)FSL_FEATURE_SOC_CTIMER_COUNT);

    /* Decrease the channel counter for the instance */
    if (s_pwmUsedChannel[halPwmState->instance] > 0U)
    {
        s_pwmUsedChannel[halPwmState->instance] -= 1U;
    }

    /* DeInitialize tpm module */
    if (0U == s_pwmUsedChannel[halPwmState->instance])
    {
        CTIMER_Deinit(s_cTimerBase[halPwmState->instance]);
    }
}

/*! -------------------------------------------------------------------------
 * \brief  Pwm setup.
 *---------------------------------------------------------------------------*/
hal_pwm_status_t HAL_PwmSetupPwm(hal_pwm_handle_t halPwmHandle, uint8_t channel, hal_pwm_setup_config_t *setupConfig)
{
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(halPwmHandle);
    assert(channel <= (uint8_t)kCTIMER_Capture_2);
    assert(halPwmState->instance < (uint8_t)FSL_FEATURE_SOC_CTIMER_COUNT);
    assert(setupConfig);

    halPwmState->pwmLevelSelect = (uint8_t)(setupConfig->level);
    if (kStatus_Success != CTIMER_SetupPwm(s_cTimerBase[halPwmState->instance], kCTIMER_Match_3,
                                           (ctimer_match_t)channel, setupConfig->dutyCyclePercent,
                                           setupConfig->pwmFreq_Hz, halPwmState->pwmClock_Hz, false))
    {
        return kStatus_HAL_PwmFail;
    }

    CTIMER_StartTimer(s_cTimerBase[halPwmState->instance]);

    /* Increase the channel counter for the instance */
    s_pwmUsedChannel[halPwmState->instance] += 1U;

    return kStatus_HAL_PwmSuccess;
}

/*! -------------------------------------------------------------------------
 * \brief   update the Duty cycle of pwm
 *---------------------------------------------------------------------------*/
hal_pwm_status_t HAL_PwmUpdateDutycycle(hal_pwm_handle_t halPwmHandle,
                                        uint8_t channel,
                                        hal_pwm_mode_t mode,
                                        uint8_t dutyCyclePercent)
{
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;
    uint8_t duty                         = 0;

    assert(halPwmHandle);
    assert(channel <= (uint8_t)kCTIMER_Capture_2);
    assert(halPwmState->instance < (uint8_t)FSL_FEATURE_SOC_CTIMER_COUNT);
    if (halPwmState->pwmLevelSelect == (uint8_t)kHAL_PwmHighTrue)
    {
        duty = dutyCyclePercent;
    }
    else
    {
        duty = (uint8_t)100 - dutyCyclePercent;
    }
    CTIMER_UpdatePwmDutycycle(s_cTimerBase[halPwmState->instance], kCTIMER_Match_3, (ctimer_match_t)channel, duty);
    return kStatus_HAL_PwmSuccess;
}
