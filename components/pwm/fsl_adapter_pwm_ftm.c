/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_pwm.h"
#include "fsl_ftm.h"

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
typedef struct _hal_pwm_handle_struct_t
{
    uint32_t pwmClock_Hz;
    uint8_t instance;
} hal_pwm_handle_struct_t;
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static FTM_Type *const s_ftmBase[]                                        = FTM_BASE_PTRS;
static uint8_t s_pwmUsedChannel[sizeof(s_ftmBase) / sizeof(s_ftmBase[0])] = {0};

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_pwm_status_t HAL_PwmInit(hal_pwm_handle_t halPwmHandle, uint8_t instance, uint32_t srcClock_Hz)
{
    ftm_config_t ftmInfo;
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(instance < (uint8_t)FSL_FEATURE_SOC_FTM_COUNT);
    assert(NULL != halPwmHandle);
    assert(sizeof(hal_pwm_handle_struct_t) == HAL_PWM_HANDLE_SIZE);
    halPwmState->pwmClock_Hz = srcClock_Hz;
    halPwmState->instance    = instance;

    /* Initialize ftm module */
    if (0U == s_pwmUsedChannel[instance])
    {
        FTM_GetDefaultConfig(&ftmInfo);
        if (kStatus_Fail == FTM_Init(s_ftmBase[instance], &ftmInfo))
        {
            return kStatus_HAL_PwmFail;
        }
    }

    return kStatus_HAL_PwmSuccess;
}

void HAL_PwmDeinit(hal_pwm_handle_t halPwmHandle)
{
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(halPwmHandle);
    assert(halPwmState->instance < (uint8_t)FSL_FEATURE_SOC_FTM_COUNT);

    /* Decrease the channel counter for the instance */
    if (s_pwmUsedChannel[halPwmState->instance] > 0U)
    {
        s_pwmUsedChannel[halPwmState->instance] -= 1U;
    }

    /* DeInitialize tpm module */
    if (0U == s_pwmUsedChannel[halPwmState->instance])
    {
        FTM_Deinit(s_ftmBase[halPwmState->instance]);
    }
}
/*! -------------------------------------------------------------------------
 * \brief  Returns the absolute time at the moment of the call.
 * \return Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
hal_pwm_status_t HAL_PwmSetupPwm(hal_pwm_handle_t halPwmHandle, uint8_t channel, hal_pwm_setup_config_t *setupConfig)
{
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(halPwmHandle);
    assert(channel <= (uint8_t)kFTM_Chnl_7);
    assert(halPwmState->instance < (uint8_t)FSL_FEATURE_SOC_FTM_COUNT);
    assert(setupConfig);
    ftm_chnl_pwm_signal_param_t pwmChannelConfig = {
        .chnlNumber       = (ftm_chnl_t)channel,
        .level            = (ftm_pwm_level_select_t)setupConfig->level,
        .dutyCyclePercent = setupConfig->dutyCyclePercent,
#if defined(FSL_FEATURE_FTM_HAS_COMBINE) && FSL_FEATURE_FTM_HAS_COMBINE
        .firstEdgeDelayPercent = 0
#endif
    };

    if (kStatus_Success != FTM_SetupPwm(s_ftmBase[halPwmState->instance], &pwmChannelConfig, 1,
                                        (ftm_pwm_mode_t)setupConfig->mode, setupConfig->pwmFreq_Hz,
                                        halPwmState->pwmClock_Hz))
    {
        return kStatus_HAL_PwmFail;
    }
    FTM_StartTimer(s_ftmBase[halPwmState->instance], kFTM_SystemClock);

    /* Increase the channel counter for the instance */
    s_pwmUsedChannel[halPwmState->instance] += 1U;

    return kStatus_HAL_PwmSuccess;
}

/*! -------------------------------------------------------------------------
 * \brief   update the Duty cycle
 *---------------------------------------------------------------------------*/
hal_pwm_status_t HAL_PwmUpdateDutycycle(hal_pwm_handle_t halPwmHandle,
                                        uint8_t channel,
                                        hal_pwm_mode_t mode,
                                        uint8_t dutyCyclePercent)
{
    hal_pwm_handle_struct_t *halPwmState = halPwmHandle;

    assert(halPwmHandle);
    assert(channel <= (uint8_t)kFTM_Chnl_7);
    assert(halPwmState->instance < (uint8_t)FSL_FEATURE_SOC_FTM_COUNT);

    FTM_UpdatePwmDutycycle(s_ftmBase[halPwmState->instance], (ftm_chnl_t)channel, (ftm_pwm_mode_t)mode,
                           dutyCyclePercent);
    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(s_ftmBase[halPwmState->instance], true);

    return kStatus_HAL_PwmSuccess;
}
