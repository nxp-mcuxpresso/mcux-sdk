/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_adapter_time_stamp.h"
#include "fsl_gpt.h"

typedef struct _hal_time_stamp_handle_struct_t
{
    uint32_t timeStampClock_Hz;
    uint8_t timeStampInstance;
    uint8_t timeStampClockSrcSelect;

} hal_time_stamp_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static GPT_Type *const s_GptBase[] = GPT_BASE_PTRS;
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
    gpt_config_t gptConfig;
    hal_time_stamp_handle_struct_t *halTimeStampState = halTimeStampHandle;
    assert(halTimeStampHandle);

    GPT_Type *gpt = s_GptBase[halTimeStampState->timeStampInstance];

    gptConfig.clockSource     = halTimeStampState->timeStampClockSrcSelect;
    gptConfig.divider         = 1u;
    gptConfig.enableFreeRun   = true;
    gptConfig.enableRunInWait = true;
    gptConfig.enableRunInStop = true;
    gptConfig.enableRunInDoze = true;
    gptConfig.enableRunInDbg  = false;
    gptConfig.enableMode      = true;

    /* Initialize the LPTMR */
    GPT_Init(gpt, &gptConfig);
    GPT_SetOutputCompareValue(gpt, kGPT_OutputCompare_Channel1, ~0UL);
    /* Disables the selected GPT channel interrupts */
    GPT_DisableInterrupts(gpt, (uint32_t)kGPT_OutputCompare1InterruptEnable);
    /* Start counting */
    GPT_StartTimer(gpt);
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

    halTimeStampState->timeStampInstance       = halTimeStampConfig->instance;
    halTimeStampState->timeStampClock_Hz       = halTimeStampConfig->srcClock_Hz;
    halTimeStampState->timeStampClockSrcSelect = halTimeStampConfig->clockSrcSelect;

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
    GPT_Type *gpt = s_GptBase[halTimeStampState->timeStampInstance];

    return COUNT_TO_USEC(GPT_GetCurrentTimerCount(gpt), halTimeStampState->timeStampClock_Hz);
}

void HAL_TimeStampExitLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
}

void HAL_TimeStampEnterLowpower(hal_time_stamp_handle_t halTimeStampHandle)
{
}
