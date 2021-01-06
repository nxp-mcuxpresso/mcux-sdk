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
#include "fsl_lpit.h"

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

static LPIT_Type *const s_LpitBase[] = LPIT_BASE_PTRS;

static hal_timer_handle_t s_timerHandle[sizeof(s_LpitBase) / sizeof(LPIT_Type *)];
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

    LPIT_ClearStatusFlags(s_LpitBase[halTimerState->instance], (uint32_t)kLPIT_Channel0TimerFlag);
    if (halTimerState->callback != NULL)
    {
        halTimerState->callback(halTimerState->callbackParam);
    }
}

void LPIT0_IRQHandler(void);
void LPIT0_IRQHandler(void)
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
    IRQn_Type instanceIrq[][FSL_FEATURE_LPIT_TIMER_COUNT] = LPIT_IRQS;
    IRQn_Type irqId;
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    /* Structure of initialize LPIT */
    lpit_config_t lpitConfig;

    assert(sizeof(hal_timer_handle_struct_t) == HAL_TIMER_HANDLE_SIZE);
    assert(halTimerConfig);
    assert(halTimerHandle);
    assert(halTimerConfig->instance < (sizeof(s_LpitBase) / sizeof(LPIT_Type *)));

    halTimerState->timeout  = halTimerConfig->timeout;
    halTimerState->instance = halTimerConfig->instance;
    irqId                   = instanceIrq[halTimerState->instance][0];
    /*
     * lpitConfig.enableRunInDebug = false;
     */
    LPIT_GetDefaultConfig(&lpitConfig);
    assert(s_LpitBase[halTimerState->instance]);
    /* Init llpit module */
    LPIT_Init(s_LpitBase[halTimerState->instance], &lpitConfig);
    halTimerState->timerClock_Hz = halTimerConfig->srcClock_Hz;
    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(s_LpitBase[halTimerState->instance], kLPIT_Chnl_0,
                        (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz));
    /* Enable timer interrupts for channel 0 */
    LPIT_EnableInterrupts(s_LpitBase[halTimerState->instance], (uint32_t)kLPIT_Channel0TimerInterruptEnable);
    s_timerHandle[halTimerState->instance] = halTimerHandle;
    NVIC_SetPriority((IRQn_Type)irqId, HAL_TIMER_ISR_PRIORITY);
    (void)EnableIRQ(irqId);
    return kStatus_HAL_TimerSuccess;
}

/*************************************************************************************/
void HAL_TimerDeinit(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    s_timerHandle[halTimerState->instance]   = NULL;
    LPIT_Deinit(s_LpitBase[halTimerState->instance]);
}

/*************************************************************************************/
void HAL_TimerEnable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    LPIT_StartTimer(s_LpitBase[halTimerState->instance], kLPIT_Chnl_0);
}

/*************************************************************************************/
void HAL_TimerDisable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    LPIT_StopTimer(s_LpitBase[halTimerState->instance], kLPIT_Chnl_0);
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
    return (uint32_t)COUNT_TO_USEC(
        (uint64_t)LPIT_GetCurrentTimerCount(s_LpitBase[halTimerState->instance], kLPIT_Chnl_0),
        halTimerState->timerClock_Hz);
}

hal_timer_status_t HAL_TimerUpdateTimeout(hal_timer_handle_t halTimerHandle, uint32_t timeout)
{
    uint32_t tickCount;
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    halTimerState->timeout                   = timeout;
    tickCount = (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz);
    if ((tickCount < 1U) || (tickCount > 0xfffffff0U))
    {
        return kStatus_HAL_TimerOutOfRanger;
    }
    LPIT_SetTimerPeriod(s_LpitBase[halTimerState->instance], kLPIT_Chnl_0, tickCount);
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
