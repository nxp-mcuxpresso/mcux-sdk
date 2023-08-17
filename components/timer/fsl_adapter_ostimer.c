/*
 * Copyright 2018-2022, 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_adapter_timer.h"
#include "fsl_ostimer.h"

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
static OSTIMER_Type *const s_ostimerBase[] = OSTIMER_BASE_PTRS;

static hal_timer_handle_t s_timerHandle[sizeof(s_ostimerBase) / sizeof(OSTIMER_Type *)];

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

void ostimer_match_callback(void);
void ostimer_match_callback(void)
{
    HAL_TimerInterruptHandle(0);
}

static ostimer_callback_t ostimer_callback_table[] = {ostimer_match_callback};

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_timer_status_t HAL_TimerInit(hal_timer_handle_t halTimerHandle, hal_timer_config_t *halTimerConfig)
{
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    assert(sizeof(hal_timer_handle_struct_t) == HAL_TIMER_HANDLE_SIZE);
    assert(halTimerConfig);
    assert(halTimerHandle);
    assert(halTimerConfig->instance < (sizeof(s_ostimerBase) / sizeof(OSTIMER_Type *)));

    halTimerState->instance                = halTimerConfig->instance;
    halTimerState->timerClock_Hz           = halTimerConfig->srcClock_Hz;
    s_timerHandle[halTimerState->instance] = halTimerHandle;
    OSTIMER_Init(s_ostimerBase[halTimerState->instance]);
    return kStatus_HAL_TimerSuccess;
}

/*************************************************************************************/
void HAL_TimerDeinit(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    s_timerHandle[halTimerState->instance]   = NULL;
    OSTIMER_Deinit(s_ostimerBase[halTimerState->instance]);
}

/*************************************************************************************/
void HAL_TimerEnable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
}

/*************************************************************************************/
void HAL_TimerDisable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
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
    uint64_t retValue;
    uint32_t reserveMs = 4U;
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    reserveCount                             = (uint32_t)MSEC_TO_COUNT((reserveMs), (halTimerState->timerClock_Hz));
    
    retValue = COUNT_TO_USEC(((uint64_t)0xFFFFFFFF - (uint64_t)reserveCount), (uint64_t)halTimerState->timerClock_Hz);
    return (uint32_t)((retValue > 0xFFFFFFFFU) ? (0xFFFFFFFFU - reserveMs * 1000U) : (uint32_t)retValue);
}

/* return micro us */
uint32_t HAL_TimerGetCurrentTimerCount(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    return (uint32_t)COUNT_TO_USEC(OSTIMER_GetCurrentTimerValue(s_ostimerBase[halTimerState->instance]),
                                   halTimerState->timerClock_Hz);
}

hal_timer_status_t HAL_TimerUpdateTimeout(hal_timer_handle_t halTimerHandle, uint32_t timeout)
{
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    uint64_t timerTicks                      = OSTIMER_GetCurrentTimerValue(s_ostimerBase[halTimerState->instance]);
    /* Translate the millisecond to ostimer count value. */
    timerTicks += USEC_TO_COUNT(timeout, halTimerState->timerClock_Hz);

    /* Set the match value with unit of ticks. */
    OSTIMER_SetMatchValue(s_ostimerBase[halTimerState->instance], timerTicks,
                          ostimer_callback_table[halTimerState->instance]);
    return kStatus_HAL_TimerSuccess;
}

void HAL_TimerExitLowpower(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
}

void HAL_TimerEnterLowpower(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
}
