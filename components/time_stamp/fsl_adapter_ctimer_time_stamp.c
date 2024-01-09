/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_adapter_time_stamp.h"
#include "fsl_ctimer.h"

typedef struct _hal_time_stamp_handle_struct_t
{
    uint32_t timeStampClock_Hz;
    uint8_t timeStampInstance;
} hal_time_stamp_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static CTIMER_Type *const s_CtimerBase[] = CTIMER_BASE_PTRS;
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_COUNT 0xffffffffUL

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

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
    ctimer_config_t config;
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    ctimer_match_config_t mCtimerMatchConfig;
    assert(halTimeStampHandle);

    CTIMER_GetDefaultConfig(&config);

    config.prescale = halTimeStampConfig->srcClock_Hz / 1000000U;

    config.prescale -= 1U;

    halTimeStampState->timeStampInstance = halTimeStampConfig->instance;
    halTimeStampState->timeStampClock_Hz = halTimeStampConfig->srcClock_Hz / (uint32_t)(config.prescale + 1U);

    CTIMER_Init(s_CtimerBase[halTimeStampState->timeStampInstance], &config);
    CTIMER_StopTimer(s_CtimerBase[halTimeStampState->timeStampInstance]);

    /* Configuration 0 */
    mCtimerMatchConfig.enableCounterReset = true;
    mCtimerMatchConfig.enableCounterStop  = false;
    mCtimerMatchConfig.outControl         = kCTIMER_Output_NoAction;
    mCtimerMatchConfig.outPinInitState    = false;
    mCtimerMatchConfig.enableInterrupt    = false;
    mCtimerMatchConfig.matchValue         = (uint32_t)USEC_TO_COUNT(MAX_COUNT, halTimeStampState->timeStampClock_Hz);

    CTIMER_SetupMatch(s_CtimerBase[halTimeStampState->timeStampInstance], (ctimer_match_t)kCTIMER_Match_0,
                      &mCtimerMatchConfig);

    CTIMER_StartTimer(s_CtimerBase[halTimeStampState->timeStampInstance]);
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

    uint64_t count = CTIMER_GetTimerCountValue(s_CtimerBase[halTimeStampState->timeStampInstance]);

    return COUNT_TO_USEC(count, halTimeStampState->timeStampClock_Hz);
}

void HAL_TimeStampExitLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
    assert(halTimeStampHandle);
}

void HAL_TimeStampEnterLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
}
