/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_adapter_time_stamp.h"
#include "fsl_ostimer.h"

typedef struct _hal_time_stamp_handle_struct_t
{
    uint32_t timeStampClock_Hz;
    uint8_t timeStampInstance;
} hal_time_stamp_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static OSTIMER_Type *const s_ostimerBase[] = OSTIMER_BASE_PTRS;
/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampConfig->instance < (sizeof(s_ostimerBase) / sizeof(OSTIMER_Type *)));

    halTimeStampState->timeStampInstance = halTimeStampConfig->instance;
    halTimeStampState->timeStampClock_Hz = halTimeStampConfig->srcClock_Hz;
    OSTIMER_Init(s_ostimerBase[halTimeStampState->timeStampInstance]);
    return;
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

    uint64_t timerCount = OSTIMER_GetCurrentTimerValue(s_ostimerBase[halTimeStampState->timeStampInstance]);

    /* Discard the 20 MSBs of the timer to avoid 64bit overflow when converting to USEC */
    return (uint64_t)COUNT_TO_USEC(timerCount & 0xFFFFFFFFFFFU, halTimeStampState->timeStampClock_Hz);
}

void HAL_TimeStampExitLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);

    OSTIMER_Init(s_ostimerBase[halTimeStampState->timeStampInstance]);
}

void HAL_TimeStampEnterLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);

    OSTIMER_Deinit(s_ostimerBase[halTimeStampState->timeStampInstance]);
}
