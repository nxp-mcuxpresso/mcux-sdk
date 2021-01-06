/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_adapter_time_stamp.h"
#include "fsl_lpit.h"

typedef struct _hal_time_stamp_handle_struct_t
{
    uint32_t timeStampClock_Hz;
    uint8_t timeStampInstance;
} hal_time_stamp_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static LPIT_Type *const s_LpitBase[] = LPIT_BASE_PTRS;
/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
static void HAL_HWTimeStampInit(hal_time_stamp_handle_t halTimeStampHandle)
{
    lpit_config_t lpitConfig;
    lpit_chnl_params_t lpitChanneConfig;
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);

    LPIT_GetDefaultConfig(&lpitConfig);
    /* Init pit module */
    LPIT_Init(s_LpitBase[halTimeStampState->timeStampInstance], &lpitConfig);

    lpitChanneConfig.chainChannel          = false;
    lpitChanneConfig.enableReloadOnTrigger = false;
    lpitChanneConfig.enableStartOnTrigger  = false;
    lpitChanneConfig.enableStopOnTimeout   = false;
    lpitChanneConfig.timerMode             = kLPIT_PeriodicCounter;
    lpitChanneConfig.triggerSelect         = kLPIT_Trigger_TimerChn0;
    lpitChanneConfig.triggerSource         = kLPIT_TriggerSource_External;
    (void)LPIT_SetupChannel(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_0, &lpitChanneConfig);

    lpitChanneConfig.chainChannel = true;
    (void)LPIT_SetupChannel(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_1, &lpitChanneConfig);

    LPIT_SetTimerPeriod(LPIT0, kLPIT_Chnl_1, 0xFFFFFFFFUL);
    LPIT_StopTimer(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_1);
    LPIT_DisableInterrupts(LPIT0, 0xFFFFFFFFUL);
    LPIT_StartTimer(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_1);
    LPIT_SetTimerPeriod(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_0, 0xFFFFFFFFUL);
    LPIT_StartTimer(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_0);
}
/*!
 * @brief Initializes the timer Stamp adapter module for a timer basic operation.
 *
 * @note This API should be called at the beginning of the application using the timer Stampadapter.
 * For Initializes timer Stamp adapter,
 *
 * @param halTimerHandle     HAL timer adapter handle
 * @param halTimeStampConfig A pointer to the HAL time stamp configuration structure
 */
void HAL_TimeStampInit(hal_time_stamp_handle_t halTimeStampHandle, hal_time_stamp_config_t *halTimeStampConfig)
{
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);

    halTimeStampState->timeStampInstance = halTimeStampConfig->instance;
    halTimeStampState->timeStampClock_Hz = halTimeStampConfig->srcClock_Hz;

    HAL_HWTimeStampInit(halTimeStampHandle);
}

/*!
 * @brief Get the absolute time at the moment of the call.
 *
 * @param halTimerHandle     HAL timer adapter handle
 * @retval the absolute time(microsecond) at the moment of the call
 */
uint64_t HAL_GetTimeStamp(hal_time_stamp_handle_t halTimeStampHandle)
{
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);
    uint64_t count =
        0xFFFFFFFFFFFFFFFFULL -
        (((uint64_t)LPIT_GetCurrentTimerCount(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_1) << 32U) +
         (uint64_t)LPIT_GetCurrentTimerCount(s_LpitBase[halTimeStampState->timeStampInstance], kLPIT_Chnl_0));
    return COUNT_TO_USEC(count, halTimeStampState->timeStampClock_Hz);
}

void HAL_TimeStampExitLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
    assert(halTimeStampHandle);
    HAL_HWTimeStampInit(halTimeStampHandle);
}

void HAL_TimeStampEnterLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
}
