/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_adapter_time_stamp.h"
#include "fsl_lptmr.h"

typedef struct _hal_time_stamp_handle_struct_t
{
    uint32_t timeStampClock_Hz;
    uint8_t timeStampInstance;
#if (defined(TM_ENABLE_TIME_STAMP_CLOCK_SELECT) && (TM_ENABLE_TIME_STAMP_CLOCK_SELECT > 0U))
    uint8_t timeStampClockSrcSelect;
#endif
} hal_time_stamp_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static LPTMR_Type *const s_LptmrBase[] = LPTMR_BASE_PTRS;
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
    lptmr_config_t lptmrConfig;
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);

    LPTMR_GetDefaultConfig(&lptmrConfig);
#if (defined(TM_ENABLE_TIME_STAMP_CLOCK_SELECT) && (TM_ENABLE_TIME_STAMP_CLOCK_SELECT > 0U))
    lptmrConfig.prescalerClockSource = (lptmr_prescaler_clock_select_t)halTimeStampState->timeStampClockSrcSelect;
#endif
    /* Initialize the LPTMR */
    LPTMR_Init(s_LptmrBase[halTimeStampState->timeStampInstance], &lptmrConfig);
#if (defined(FSL_FEATURE_LPTMR_CNR_WIDTH_IS_32B) && (FSL_FEATURE_LPTMR_CNR_WIDTH_IS_32B > 0))
    LPTMR_SetTimerPeriod(s_LptmrBase[halTimeStampState->timeStampInstance], 0xFFFFFFFFUL);
#else
    LPTMR_SetTimerPeriod(s_LptmrBase[halTimeStampState->timeStampInstance], 0xFFFFUL);
#endif
    /* Disables the selected LPTMR interrupts */
    LPTMR_DisableInterrupts(s_LptmrBase[halTimeStampState->timeStampInstance], (uint32_t)kLPTMR_TimerInterruptEnable);
    /* Start counting */
    LPTMR_StartTimer(s_LptmrBase[halTimeStampState->timeStampInstance]);
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
#if (defined(TM_ENABLE_TIME_STAMP_CLOCK_SELECT) && (TM_ENABLE_TIME_STAMP_CLOCK_SELECT > 0U))
    halTimeStampState->timeStampClockSrcSelect = halTimeStampConfig->clockSrcSelect;
#endif

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

    return COUNT_TO_USEC(LPTMR_GetCurrentTimerCount(s_LptmrBase[halTimeStampState->timeStampInstance]),
                         halTimeStampState->timeStampClock_Hz);
}

void HAL_TimeStampExitLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
}

void HAL_TimeStampEnterLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
}
