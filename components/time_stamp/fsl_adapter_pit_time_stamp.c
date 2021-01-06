/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_adapter_time_stamp.h"
#include "fsl_pit.h"

typedef struct _hal_time_stamp_handle_struct_t
{
    uint32_t timeStampClock_Hz;
    uint8_t timeStampInstance;
} hal_time_stamp_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static PIT_Type *const s_PitBase[] = PIT_BASE_PTRS;
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
    pit_config_t pitConfig;
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);
    PIT_GetDefaultConfig(&pitConfig);
    /* Init pit module */
    PIT_Init(s_PitBase[halTimeStampState->timeStampInstance], &pitConfig);
#if (defined(FSL_FEATURE_PIT_HAS_CHAIN_MODE) && (FSL_FEATURE_PIT_HAS_CHAIN_MODE > 0))
    PIT_SetTimerPeriod(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_1, 0xFFFFFFFFUL);
    PIT_StopTimer(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_1);
    PIT_DisableInterrupts(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_1, 0xFFFFFFFFUL);
    PIT_SetTimerChainMode(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_1, true);
    PIT_StartTimer(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_1);
#endif
    PIT_SetTimerPeriod(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_0, 0xFFFFFFFFUL);
    PIT_StartTimer(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_0);
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
#if (defined(FSL_FEATURE_PIT_HAS_CHAIN_MODE) && (FSL_FEATURE_PIT_HAS_CHAIN_MODE > 0))
#if (defined(FSL_FEATURE_PIT_HAS_LIFETIME_TIMER) && (FSL_FEATURE_PIT_HAS_LIFETIME_TIMER > 0))
    uint64_t count = 0xFFFFFFFFFFFFFFFFULL - PIT_GetLifetimeTimerCount(s_PitBase[halTimeStampState->timeStampInstance]);
#else
    uint64_t count =
        0xFFFFFFFFFFFFFFFFULL -
        (((uint64_t)PIT_GetCurrentTimerCount(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_1) << 32U) +
         (uint64_t)PIT_GetCurrentTimerCount(s_PitBase[halTimeStampState->timeStampInstance], kPIT_Chnl_0));
#endif
#else
    uint64_t count = 0xFFFFFFFFUL - PIT_GetCurrentTimerCount(s_PitBase[halTimeStampState->timeStampInstance]);
#endif

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
