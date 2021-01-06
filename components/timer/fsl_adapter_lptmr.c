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
#include "fsl_lptmr.h"

/*! @brief Definition to determine LPTMR timer whether use free running mode*/
#ifndef LPTMR_USE_FREE_RUNNING
#define LPTMR_USE_FREE_RUNNING (0)
#endif

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

static LPTMR_Type *const s_LptmrBase[] = LPTMR_BASE_PTRS;

static hal_timer_handle_t s_timerHandle[sizeof(s_LptmrBase) / sizeof(LPTMR_Type *)];
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
static void HAL_TimerInterruptHandle(uint8_t instance)
{
    hal_timer_handle_struct_t *halTimerState = (hal_timer_handle_struct_t *)s_timerHandle[instance];
    uint32_t lptmrIntFlag;

    if (NULL == halTimerState)
    {
        return;
    }

    lptmrIntFlag = LPTMR_GetStatusFlags(s_LptmrBase[instance]);
    LPTMR_ClearStatusFlags(s_LptmrBase[instance], (uint32_t)kLPTMR_TimerCompareFlag);

    if (0U != lptmrIntFlag)
    {
        if (halTimerState->callback != NULL)
        {
            halTimerState->callback(halTimerState->callbackParam);
        }
    }
}

void PWT_LPTMR0_IRQHandler(void);
void PWT_LPTMR0_IRQHandler(void)
{
    HAL_TimerInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}
void LPTMR0_IRQHandler(void);
void LPTMR0_IRQHandler(void)
{
    HAL_TimerInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}

#if (FSL_FEATURE_SOC_LPTMR_COUNT > 1)
void LPTMR1_IRQHandler(void);
void LPTMR1_IRQHandler(void)
{
    HAL_TimerInterruptHandle(1);
    SDK_ISR_EXIT_BARRIER;
}
#endif

void LPTMR0_LPTMR1_IRQHandler(void);
void LPTMR0_LPTMR1_IRQHandler(void)
{
    HAL_TimerInterruptHandle(0);
#if (defined(FSL_FEATURE_SOC_LPTMR_COUNT) && (FSL_FEATURE_SOC_LPTMR_COUNT > 1))
    HAL_TimerInterruptHandle(1);
#endif /* (FSL_FEATURE_SOC_LPTMR_COUNT > 1) */
    SDK_ISR_EXIT_BARRIER;
}
/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_timer_status_t HAL_TimerInit(hal_timer_handle_t halTimerHandle, hal_timer_config_t *halTimerConfig)
{
    IRQn_Type mLptmrIrqId[] = LPTMR_IRQS;
    IRQn_Type irqId;
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    /* Structure of initialize LPTMR */
    lptmr_config_t lptmrConfig;

    assert(sizeof(hal_timer_handle_struct_t) == HAL_TIMER_HANDLE_SIZE);
    assert(halTimerConfig);
    assert(halTimerHandle);
    assert(halTimerConfig->instance < (sizeof(s_LptmrBase) / sizeof(LPTMR_Type *)));

    halTimerState->timeout  = halTimerConfig->timeout;
    halTimerState->instance = halTimerConfig->instance;
    irqId                   = mLptmrIrqId[halTimerState->instance];

    LPTMR_GetDefaultConfig(&lptmrConfig);
#if (defined(TM_ENABLE_TIMER_CLOCK_SELECT) && (TM_ENABLE_TIMER_CLOCK_SELECT > 0U))
    lptmrConfig.prescalerClockSource = (lptmr_prescaler_clock_select_t)halTimerConfig->clockSrcSelect;
#endif

#if (defined(LPTMR_USE_FREE_RUNNING) && (LPTMR_USE_FREE_RUNNING > 0))
    lptmrConfig.enableFreeRunning = true;
#endif
    /* Initialize the LPTMR */
    LPTMR_Init(s_LptmrBase[halTimerState->instance], &lptmrConfig);
    halTimerState->timerClock_Hz = halTimerConfig->srcClock_Hz;
    /*
     * Set timer period.
     * Note : the parameter "ticks" of LPTMR_SetTimerPeriod should be equal or greater than 1.
     */
    LPTMR_SetTimerPeriod(s_LptmrBase[halTimerState->instance],
                         (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz));

    /* Enable timer interrupt */
    LPTMR_EnableInterrupts(s_LptmrBase[halTimerState->instance], (uint32_t)kLPTMR_TimerInterruptEnable);

    s_timerHandle[halTimerState->instance] = halTimerHandle;

    NVIC_SetPriority((IRQn_Type)irqId, HAL_TIMER_ISR_PRIORITY);
    (void)EnableIRQ(irqId);
    return kStatus_HAL_TimerSuccess;
}

void HAL_TimerDeinit(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    s_timerHandle[halTimerState->instance]   = NULL;
    LPTMR_Deinit(s_LptmrBase[halTimerState->instance]);
}
/*************************************************************************************/
void HAL_TimerEnable(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    LPTMR_StartTimer(s_LptmrBase[halTimerState->instance]);
}

/*************************************************************************************/
void HAL_TimerDisable(hal_timer_handle_t halTimerHandle)
{
#if !(defined(LPTMR_USE_FREE_RUNNING) && (LPTMR_USE_FREE_RUNNING > 0))
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    LPTMR_StopTimer(s_LptmrBase[halTimerState->instance]);
#endif
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
    return (uint32_t)COUNT_TO_USEC(((uint64_t)0xFFFFFFFF - (uint64_t)reserveCount),
                                   (uint64_t)halTimerState->timerClock_Hz);
}
/* return micro us */
uint32_t HAL_TimerGetCurrentTimerCount(hal_timer_handle_t halTimerHandle)
{
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    return (uint32_t)COUNT_TO_USEC((uint64_t)LPTMR_GetCurrentTimerCount(s_LptmrBase[halTimerState->instance]),
                                   halTimerState->timerClock_Hz);
}

hal_timer_status_t HAL_TimerUpdateTimeout(hal_timer_handle_t halTimerHandle, uint32_t timeout)
{
    uint32_t tickCount;
#if (defined(LPTMR_USE_FREE_RUNNING) && (LPTMR_USE_FREE_RUNNING > 0))
    uint64_t totalCount = 0;
#endif
    assert(halTimerHandle);
    hal_timer_handle_struct_t *halTimerState = halTimerHandle;
    halTimerState->timeout                   = timeout;
    tickCount = (uint32_t)USEC_TO_COUNT(halTimerState->timeout, halTimerState->timerClock_Hz);
    if ((tickCount < 1U) || (tickCount > 0xfffffff0U))
    {
        return kStatus_HAL_TimerOutOfRanger;
    }
#if (defined(LPTMR_USE_FREE_RUNNING) && (LPTMR_USE_FREE_RUNNING > 0))
    totalCount = (uint64_t)tickCount + (uint64_t)LPTMR_GetCurrentTimerCount(s_LptmrBase[halTimerState->instance]);
    if (totalCount > 0xffffffff)
    {
        tickCount = totalCount - 0xffffffff;
    }
    else
    {
        tickCount = totalCount;
    }

#endif
    LPTMR_SetTimerPeriod(s_LptmrBase[halTimerState->instance], tickCount);
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
