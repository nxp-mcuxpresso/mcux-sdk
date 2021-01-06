/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_adapter_timer.h"
#include "fsl_ctimer.h"

#define gStackTimerChannel_c (kCTIMER_Match_0)
typedef struct _hal_timer_handle_struct_t
{
    uint32_t timeout;
    uint32_t timerClock_Hz;
    hal_timer_callback_t callback;
    void *callbackParam;
    uint8_t instance;
} hal_timer_handle_struct_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

static CTIMER_Type *const s_CtimerBase[] = CTIMER_BASE_PTRS;

static hal_timer_handle_t s_timerHandle[sizeof(s_CtimerBase) / sizeof(CTIMER_Type *)];
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
static void HAL_TimerInterruptHandle(uint8_t instance)
{
    hal_timer_handle_struct_t *halTimerState = (hal_timer_handle_struct_t *)s_timerHandle[instance];

    if (halTimerState->callback != NULL)
    {
        halTimerState->callback(halTimerState->callbackParam);
    }
}

void ctimer0_match0_callback(uint32_t flags);
void ctimer0_match0_callback(uint32_t flags)
{
    HAL_TimerInterruptHandle(0);
}

void ctimer1_match0_callback(uint32_t flags);
void ctimer1_match0_callback(uint32_t flags)
{
    HAL_TimerInterruptHandle(1);
}
static ctimer_callback_t ctimer_callback_table[] = {ctimer0_match0_callback, ctimer1_match0_callback};

static hal_timer_status_t HAL_CTimerConfigTimeout(hal_timer_handle_t halTimerHandle, uint32_t timeout)
{
    ctimer_match_config_t mCtimerMatchConfig;
    ctimer_config_t config;
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    halTimerState->timeout                   = timeout;
    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(s_CtimerBase[halTimerState->instance], &config);
    CTIMER_StopTimer(s_CtimerBase[halTimerState->instance]);

    /* Configuration 0 */
    mCtimerMatchConfig.enableCounterReset = true;
    mCtimerMatchConfig.enableCounterStop  = false;
    mCtimerMatchConfig.outControl         = kCTIMER_Output_NoAction;
    mCtimerMatchConfig.outPinInitState    = false;
    mCtimerMatchConfig.enableInterrupt    = true;
    mCtimerMatchConfig.matchValue = (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz);
    if ((mCtimerMatchConfig.matchValue < 1U) || (mCtimerMatchConfig.matchValue > 0xFFFFFFF0U))
    {
        return kStatus_HAL_TimerOutOfRanger;
    }
    /* Configure channel to Software compare; output pin not used */
    CTIMER_RegisterCallBack(s_CtimerBase[halTimerState->instance], &ctimer_callback_table[halTimerState->instance],
                            kCTIMER_SingleCallback);
    CTIMER_SetupMatch(s_CtimerBase[halTimerState->instance], (ctimer_match_t)gStackTimerChannel_c, &mCtimerMatchConfig);
    return kStatus_HAL_TimerSuccess;
}

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_timer_status_t HAL_TimerInit(hal_timer_handle_t halTimerHandle, hal_timer_config_t *halTimerConfig)
{
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    ctimer_config_t config;
    assert(sizeof(hal_timer_handle_struct_t) == HAL_TIMER_HANDLE_SIZE);
    assert(halTimerConfig);
    assert(halTimerHandle);
    assert(halTimerConfig->instance < (sizeof(s_CtimerBase) / sizeof(CTIMER_Type *)));

    CTIMER_GetDefaultConfig(&config);
    halTimerState->timeout                 = halTimerConfig->timeout;
    halTimerState->instance                = halTimerConfig->instance;
    halTimerState->timerClock_Hz           = (uint32_t)halTimerConfig->srcClock_Hz / (uint32_t)(config.prescale + 1U);
    s_timerHandle[halTimerState->instance] = halTimerHandle;
    return HAL_CTimerConfigTimeout(halTimerHandle, halTimerState->timeout);
}
/*************************************************************************************/
void HAL_TimerDeinit(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    s_timerHandle[halTimerState->instance]   = NULL;
    CTIMER_Deinit(s_CtimerBase[halTimerState->instance]);
}
/*************************************************************************************/
void HAL_TimerEnable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    CTIMER_StartTimer(s_CtimerBase[halTimerState->instance]);
}

/*************************************************************************************/
void HAL_TimerDisable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    CTIMER_StopTimer(s_CtimerBase[halTimerState->instance]);
}

/*************************************************************************************/
void HAL_TimerInstallCallback(hal_timer_handle_t halTimerHandle, hal_timer_callback_t callback, void *callbackParam)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    halTimerState->callback                  = callback;
    halTimerState->callbackParam             = callbackParam;
}

uint32_t HAL_TimerGetMaxTimeout(hal_timer_handle_t halTimerHandle)
{
    uint32_t reserveCount;
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    reserveCount                             = (uint32_t)MSEC_TO_COUNT((4), (halTimerState->timerClock_Hz));
    if (reserveCount < MSEC_TO_COUNT((1), (halTimerState->timerClock_Hz)))
    {
        return 1000;
    }
    return (uint32_t)COUNT_TO_USEC(((uint64_t)0xFFFFFFFFUL - (uint64_t)reserveCount), halTimerState->timerClock_Hz);
}
/* return micro us */
uint32_t HAL_TimerGetCurrentTimerCount(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    return (uint32_t)COUNT_TO_USEC(s_CtimerBase[halTimerState->instance]->TC, halTimerState->timerClock_Hz);
}

hal_timer_status_t HAL_TimerUpdateTimeout(hal_timer_handle_t halTimerHandle, uint32_t timeout)
{
    return HAL_CTimerConfigTimeout(halTimerHandle, timeout);
}

void HAL_TimerExitLowpower(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
}

void HAL_TimerEnterLowpower(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
}
