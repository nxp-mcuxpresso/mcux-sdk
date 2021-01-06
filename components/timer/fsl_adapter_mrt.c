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
#include "fsl_mrt.h"

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

static MRT_Type *const s_MrtBase[] = MRT_BASE_PTRS;

static hal_timer_handle_t s_timerHandle[sizeof(s_MrtBase) / sizeof(MRT_Type *)];
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
    /* Clear interrupt flag.*/
    MRT_ClearStatusFlags(s_MrtBase[halTimerState->instance], kMRT_Channel_0, (uint32_t)kMRT_TimerInterruptFlag);

    if (halTimerState->callback != NULL)
    {
        halTimerState->callback(halTimerState->callbackParam);
    }
}

void MRT0_IRQHandler(void);
void MRT0_IRQHandler(void)
{
    HAL_TimerInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}
/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_timer_status_t HAL_TimerInit(hal_timer_handle_t halTimerHandle, hal_timer_config_t *halTimerConfig)
{
    IRQn_Type instanceIrq[]                  = MRT_IRQS;
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    /* Structure of initialize MRT */
    mrt_config_t mrtConfig;

    assert(sizeof(hal_timer_handle_struct_t) == HAL_TIMER_HANDLE_SIZE);
    assert(halTimerConfig);
    assert(halTimerHandle);
    assert(halTimerConfig->instance < (sizeof(s_MrtBase) / sizeof(MRT_Type *)));

    halTimerState->timeout  = halTimerConfig->timeout;
    halTimerState->instance = halTimerConfig->instance;

    /* mrtConfig.enableMultiTask = false; */
    MRT_GetDefaultConfig(&mrtConfig);

    /* Init mrt module */
    MRT_Init(s_MrtBase[halTimerState->instance], &mrtConfig);

    /* Setup Channel 0 to be repeated */
    MRT_SetupChannelMode(s_MrtBase[halTimerState->instance], kMRT_Channel_0, kMRT_RepeatMode);

    /* Enable timer interrupts for channel 0 */
    MRT_EnableInterrupts(s_MrtBase[halTimerState->instance], kMRT_Channel_0, (uint32_t)kMRT_TimerInterruptEnable);

    halTimerState->timerClock_Hz           = halTimerConfig->srcClock_Hz;
    s_timerHandle[halTimerState->instance] = halTimerHandle;
    /* Enable at the irq */
    NVIC_SetPriority((IRQn_Type)instanceIrq[halTimerState->instance], HAL_TIMER_ISR_PRIORITY);
    (void)EnableIRQ(instanceIrq[halTimerState->instance]);
    return kStatus_HAL_TimerSuccess;
}

void HAL_TimerDeinit(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    s_timerHandle[halTimerState->instance]   = NULL;
    MRT_Deinit(s_MrtBase[halTimerState->instance]);
}
/*************************************************************************************/
void HAL_TimerEnable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    MRT_StartTimer(s_MrtBase[halTimerState->instance], kMRT_Channel_0,
                   (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz));
}

/*************************************************************************************/
void HAL_TimerDisable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    /* Stop channel 0 */
    MRT_StopTimer(s_MrtBase[halTimerState->instance], kMRT_Channel_0);
    /* Clear interrupt flag.*/
    MRT_ClearStatusFlags(s_MrtBase[halTimerState->instance], kMRT_Channel_0, (uint32_t)kMRT_TimerInterruptFlag);
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
    return (uint32_t)COUNT_TO_USEC(((uint64_t)0xFFFF - reserveCount), halTimerState->timerClock_Hz);
}
/* return micro us */
uint32_t HAL_TimerGetCurrentTimerCount(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    return (uint32_t)COUNT_TO_USEC(
        (uint64_t)MRT_GetCurrentTimerCount(s_MrtBase[halTimerState->instance], kMRT_Channel_0),
        halTimerState->timerClock_Hz);
}

hal_timer_status_t HAL_TimerUpdateTimeout(hal_timer_handle_t halTimerHandle, uint32_t timeout)
{
    uint32_t tickCount;
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    halTimerState->timeout                   = timeout;
    tickCount = (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz);
    if ((tickCount < 1U) || (tickCount > 0xfff0U))
    {
        return kStatus_HAL_TimerOutOfRanger;
    }
    MRT_StopTimer(s_MrtBase[halTimerState->instance], kMRT_Channel_0);
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
