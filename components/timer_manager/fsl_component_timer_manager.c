/*
 * Copyright 2018-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_component_timer_manager.h"
#include "fsl_adapter_timer.h"
#if (defined(TM_ENABLE_TIME_STAMP) && (TM_ENABLE_TIME_STAMP > 0U))
#include "fsl_adapter_time_stamp.h"
#endif
/*
 * The OSA_USED macro can only be defined when the OSA component is used.
 * If the source code of the OSA component does not exist, the OSA_USED cannot be defined.
 * OR, If OSA component is not added into project event the OSA source code exists, the OSA_USED
 * also cannot be defined.
 * The source code path of the OSA component is <MCUXpresso_SDK>/components/osa.
 *
 */
#if defined(OSA_USED)
#include "fsl_os_abstraction.h"
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
#include "fsl_component_common_task.h"
#endif
#endif

#if defined(OSA_USED)
#if (defined(USE_RTOS) && (USE_RTOS > 0U))
#define TIMER_ENTER_CRITICAL() \
    OSA_SR_ALLOC();            \
    OSA_ENTER_CRITICAL()
#define TIMER_EXIT_CRITICAL() OSA_EXIT_CRITICAL()
#else
#define TIMER_ENTER_CRITICAL()
#define TIMER_EXIT_CRITICAL()
#endif
#else
#define TIMER_ENTER_CRITICAL() uint32_t regPrimask = DisableGlobalIRQ();
#define TIMER_EXIT_CRITICAL()  EnableGlobalIRQ(regPrimask);
#endif

/*****************************************************************************
******************************************************************************
* Private macros
******************************************************************************
*****************************************************************************/
#define mTmrDummyEvent_c (1UL << 16U)

/**@brief Timer status. */
typedef enum _timer_state
{
    kTimerStateFree_c     = 0x00, /**< The timer free status. */
    kTimerStateActive_c   = 0x20, /**< The timer active status. */
    kTimerStateReady_c    = 0x40, /**< The timer ready status. */
    kTimerStateInactive_c = 0x80, /**< The timer inactive status. */
    kTimerStateMask_c     = 0xE0, /**< The timer status mask all. */
    kTimerModeMask_c      = 0x1F, /**< The timer mode mask all. */
} timer_state_t;

/*****************************************************************************
******************************************************************************
* Private type definitions
******************************************************************************
*****************************************************************************/
/*! @brief Timer handle structure for timer manager. */
typedef struct _timer_handle_struct_t
{
    struct _timer_handle_struct_t *next; /*!< LIST_ element of the link */
    volatile uint8_t tmrStatus;          /*!< Timer status and mode*/
    uint64_t timeoutInUs;                /*!< Time out of the timer, should be microseconds */
    uint64_t remainingUs;                /*!< Remaining of the timer, should be microseconds */
    timer_callback_t pfCallBack;         /*!< Callback function of the timer */
    void *param;                         /*!< Parameter of callback function of the timer */
} timer_handle_struct_t;
/*! @brief State structure for timer manager. */
typedef struct _timermanager_state
{
    uint32_t mUsInTimerInterval;         /*!< Timer intervl in microseconds */
    uint32_t previousTimeInUs;           /*!< Previous timer count in microseconds */
    timer_handle_struct_t *timerHead;    /*!< Timer list head */
    TIMER_HANDLE_DEFINE(halTimerHandle); /*!< Timer handle buffer */
#if (defined(TM_ENABLE_TIME_STAMP) && (TM_ENABLE_TIME_STAMP > 0U))
    TIME_STAMP_HANDLE_DEFINE(halTimeStampHandle); /*!< Time stamp handle buffer */
#endif
#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
    common_task_message_t mTimerCommontaskMsg; /*!< Timer common_task message */
#else
    OSA_EVENT_HANDLE_DEFINE(halTimerTaskEventHandle); /*!< Timer task event handle buffer */
    OSA_TASK_HANDLE_DEFINE(timerTaskHandle);          /*!< Timer task id */
#endif
#endif
    volatile uint8_t numberOfActiveTimers;         /*!< Number of active Timers*/
    volatile uint8_t numberOfLowPowerActiveTimers; /*!< Number of low power active Timers */
    volatile uint8_t timerHardwareIsRunning;       /*!< Hardware timer is runnig */
    uint8_t initialized;                           /*!< Timer is initialized */
} timermanager_state_t;

/*****************************************************************************
******************************************************************************
* Public memory declarations
******************************************************************************
*****************************************************************************/

/*****************************************************************************
 *****************************************************************************
 * Private prototypes
 *****************************************************************************
 *****************************************************************************/

/*! -------------------------------------------------------------------------
 * \brief Function called by driver ISR on channel match in interrupt context.
 *---------------------------------------------------------------------------*/
static void HAL_TIMER_Callback(void *param);

/*! -------------------------------------------------------------------------
 * \brief     Timer thread.
 *            Called by the kernel when the timer ISR posts a timer event.
 * \param[in] param - User parameter to timer thread; not used.
 *---------------------------------------------------------------------------*/
static void TimerManagerTask(void *param);

static void TimerEnable(timer_handle_t timerHandle);

static timer_status_t TimerStop(timer_handle_t timerHandle);

/*****************************************************************************
 *****************************************************************************
 * Private memory definitions
 *****************************************************************************
 *****************************************************************************/
static timermanager_state_t s_timermanager = {0};
/*****************************************************************************
******************************************************************************
* Private API macro define
******************************************************************************
*****************************************************************************/

#define IncrementActiveTimerNumber(type)                                                                     \
    ((((type) & (uint8_t)kTimerModeLowPowerTimer) != 0U) ? (++s_timermanager.numberOfLowPowerActiveTimers) : \
                                                           (++s_timermanager.numberOfActiveTimers))
#define DecrementActiveTimerNumber(type)                                                                     \
    ((((type) & (uint8_t)kTimerModeLowPowerTimer) != 0U) ? (--s_timermanager.numberOfLowPowerActiveTimers) : \
                                                           (--s_timermanager.numberOfActiveTimers))

/*
 * \brief Detect if the timer is a low-power timer
 */
#define IsLowPowerTimer(type) ((type) & (uint8_t)kTimerModeLowPowerTimer)

#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))

#else
/*
 * \brief Defines the timer thread's stack
 */
static OSA_TASK_DEFINE(TimerManagerTask, TM_TASK_PRIORITY, 1, TM_TASK_STACK_SIZE, false);
#endif
#endif

/*****************************************************************************
******************************************************************************
* Private functions
******************************************************************************
*****************************************************************************/
/*!-------------------------------------------------------------------------
 * \brief     Returns the timer status
 * \param[in] timerHandle - the handle of timer
 * \return    see definition of uint8_t
 *---------------------------------------------------------------------------*/
static uint8_t TimerGetTimerStatus(timer_handle_t timerHandle)
{
    timer_handle_struct_t *timer = (timer_handle_struct_t *)timerHandle;
    return timer->tmrStatus & (uint8_t)kTimerStateMask_c;
}

/*! -------------------------------------------------------------------------
 * \brief     Set the timer status
 * \param[in] timerHandle - the handle of timer
 * \param[in] status - the status of the timer
 *---------------------------------------------------------------------------*/
static void TimerSetTimerStatus(timer_handle_t timerHandle, uint8_t status)
{
    timer_handle_struct_t *timer = (timer_handle_struct_t *)timerHandle;
    timer->tmrStatus &= (~(uint8_t)kTimerStateMask_c);
    timer->tmrStatus |= status;
}

/*! -------------------------------------------------------------------------
 * \brief     Returns the timer type
 * \param[in] timerHandle - the handle of timer
 * \return    see definition of uint8_t
 *---------------------------------------------------------------------------*/
static uint8_t TimerGetTimerType(timer_handle_t timerHandle)
{
    timer_handle_struct_t *timer = (timer_handle_struct_t *)timerHandle;
    return timer->tmrStatus & (uint8_t)kTimerModeMask_c;
}

/*! -------------------------------------------------------------------------
 * \brief     Set the timer type
 * \param[in] timerHandle - the handle of timer
 * \param[in] timerType   - timer type
 *---------------------------------------------------------------------------*/
static void TimerSetTimerType(timer_handle_t timerHandle, uint8_t timerType)
{
    timer_handle_struct_t *timer = (timer_handle_struct_t *)timerHandle;
    timer->tmrStatus &= (~(uint8_t)kTimerModeMask_c);
    timer->tmrStatus |= timerType;
}

/*! -------------------------------------------------------------------------
 * \brief     Set the timer free
 * \param[in] timerHandle - the handle of timer
 * \param[in] type - timer type
 *---------------------------------------------------------------------------*/
static void TimerMarkTimerFree(timer_handle_t timerHandle)
{
    timer_handle_struct_t *timer = (timer_handle_struct_t *)timerHandle;
    timer->tmrStatus             = 0;
}

/*! -------------------------------------------------------------------------
 * \brief  Notify Timer task to run.
 * \return
 *---------------------------------------------------------------------------*/
static void NotifyTimersTask(void)
{
#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
    s_timermanager.mTimerCommontaskMsg.callback = TimerManagerTask;
    (void)COMMON_TASK_post_message(&s_timermanager.mTimerCommontaskMsg);
#else
    (void)OSA_EventSet((osa_event_handle_t)s_timermanager.halTimerTaskEventHandle, mTmrDummyEvent_c);
#endif
#else
    TimerManagerTask(NULL);
#endif
}

/*! -------------------------------------------------------------------------
 * \brief  Update Remaining Us for all Active timers
 * \return
 *---------------------------------------------------------------------------*/
static void TimersUpdate(bool updateRemainingUs, bool updateOnlyPowerTimer, uint32_t remainingUs)
{
    timer_handle_struct_t *th = s_timermanager.timerHead;

    if ((s_timermanager.numberOfLowPowerActiveTimers != 0U) || (s_timermanager.numberOfActiveTimers != 0U))
    {
        while (th != NULL)
        {
            if (updateRemainingUs)
            {
                if ((timer_state_t)TimerGetTimerStatus(th) == kTimerStateActive_c)
                {
                    if ((updateOnlyPowerTimer && (0U != IsLowPowerTimer(TimerGetTimerType(th)))) ||
                        (!updateOnlyPowerTimer))

                    {
                        if (th->remainingUs > remainingUs)
                        {
                            th->remainingUs = th->remainingUs - remainingUs;
                        }
                        else
                        {
                            th->remainingUs = 0;
                        }
                    }
                }
            }
            th = th->next;
        }
    }
}

/*! -------------------------------------------------------------------------
 * \brief  Update Remaining Us for all Active timers and sync timer task
 * \return
 *---------------------------------------------------------------------------*/
static void TimersUpdateSyncTask(uint32_t remainingUs)
{
    TimersUpdate(true, false, remainingUs);
    s_timermanager.previousTimeInUs = HAL_TimerGetCurrentTimerCount((hal_timer_handle_t)s_timermanager.halTimerHandle);
    NotifyTimersTask();
}

/*! -------------------------------------------------------------------------
 * \brief Function called by driver ISR on channel match in interrupt context.
 *---------------------------------------------------------------------------*/
static void HAL_TIMER_Callback(void *param)
{
    TimersUpdateSyncTask(s_timermanager.mUsInTimerInterval);
}
/*! -------------------------------------------------------------------------
 * \brief     TimerManager task.
 *            Called by the kernel when the timer ISR posts a timer event.
 * \param[in] param
 *---------------------------------------------------------------------------*/
static void TimerManagerTask(void *param)
{
    uint8_t timerType;
    timer_state_t state;
    static uint32_t mpevUsInTimerInterval = 0;
    uint8_t activeLPTimerNum, activeTimerNum;

#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
    {
#else
    osa_event_flags_t ev = 0;
    do
    {
        if (KOSA_StatusSuccess == OSA_EventWait((osa_event_handle_t)s_timermanager.halTimerTaskEventHandle,
                                                osaEventFlagsAll_c, 0U, osaWaitForever_c, &ev))
        {
#endif
#endif

        uint32_t regPrimask               = DisableGlobalIRQ();
        s_timermanager.mUsInTimerInterval = HAL_TimerGetMaxTimeout((hal_timer_handle_t)s_timermanager.halTimerHandle);
        timer_handle_struct_t *th         = s_timermanager.timerHead;
        while (NULL != th)
        {
            timerType = TimerGetTimerType(th);
            state     = (timer_state_t)TimerGetTimerStatus(th);
            if (kTimerStateReady_c == state)
            {
                TimerSetTimerStatus(th, (uint8_t)kTimerStateActive_c);
                if (s_timermanager.mUsInTimerInterval > th->timeoutInUs)
                {
                    s_timermanager.mUsInTimerInterval = (uint32_t)th->timeoutInUs;
                }
            }
            if (kTimerStateActive_c == state)
            {
                /* This timer is active. Decrement it's countdown.. */
                if (0U >= th->remainingUs)
                {
                    /* If this is an interval timer, restart it. Otherwise, mark it as inactive. */
                    if (0U != (timerType & (uint32_t)(kTimerModeSingleShot)))
                    {
                        th->remainingUs = 0;
                        (void)TimerStop(th);
                        state = (timer_state_t)TimerGetTimerStatus(th);
                    }
                    else
                    {
                        th->remainingUs = th->timeoutInUs;
                    }
                    /* This timer has expired. */
                    /*Call callback if it is not NULL*/
                    EnableGlobalIRQ(regPrimask);
                    if (NULL != th->pfCallBack)
                    {
                        th->pfCallBack(th->param);
                    }
                    regPrimask = DisableGlobalIRQ();
                }
                if ((kTimerStateActive_c == state) && (s_timermanager.mUsInTimerInterval > th->remainingUs))
                {
                    s_timermanager.mUsInTimerInterval = (uint32_t)th->remainingUs;
                }
            }
            else
            {
                /* Ignore any timer that is not active. */
            }
            th = th->next;
        }

        activeLPTimerNum = s_timermanager.numberOfLowPowerActiveTimers;
        activeTimerNum   = s_timermanager.numberOfActiveTimers;

        if ((0U != activeLPTimerNum) || (0U != activeTimerNum))
        {
            if ((s_timermanager.mUsInTimerInterval != mpevUsInTimerInterval) ||
                (0U == s_timermanager.timerHardwareIsRunning))
            {
                HAL_TimerDisable((hal_timer_handle_t)s_timermanager.halTimerHandle);
                (void)HAL_TimerUpdateTimeout((hal_timer_handle_t)s_timermanager.halTimerHandle,
                                             s_timermanager.mUsInTimerInterval);
                HAL_TimerEnable((hal_timer_handle_t)s_timermanager.halTimerHandle);
                mpevUsInTimerInterval = s_timermanager.mUsInTimerInterval;
            }
            s_timermanager.timerHardwareIsRunning = (uint8_t) true;
        }
        else
        {
            if (0U != s_timermanager.timerHardwareIsRunning)
            {
                HAL_TimerDisable((hal_timer_handle_t)s_timermanager.halTimerHandle);
                s_timermanager.timerHardwareIsRunning = (uint8_t) false;
                s_timermanager.mUsInTimerInterval     = 0;
            }
        }
        EnableGlobalIRQ(regPrimask);
#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
    }
#else
        }
    } while (0U != gUseRtos_c);
#endif
#endif
}

/*! -------------------------------------------------------------------------
 * \brief     stop a specified timer.
 * \param[in] timerHandle - the handle of the timer
 * \return    see definition of timer_status_t
 *---------------------------------------------------------------------------*/
static timer_status_t TimerStop(timer_handle_t timerHandle)
{
    timer_status_t status = kStatus_TimerInvalidId;
    timer_state_t state;
    uint8_t activeLPTimerNum, activeTimerNum;
    uint32_t regPrimask = DisableGlobalIRQ();
    if (NULL != timerHandle)
    {
        state  = (timer_state_t)TimerGetTimerStatus(timerHandle);
        status = kStatus_TimerSuccess;
        if ((state == kTimerStateActive_c) || (state == kTimerStateReady_c))
        {
            TimerSetTimerStatus(timerHandle, (uint8_t)kTimerStateInactive_c);
            DecrementActiveTimerNumber(TimerGetTimerType(timerHandle));
            /* if no sw active timers are enabled, */
            /* call the TimerManagerTask() to countdown the ticks and stop the hw timer*/
            activeLPTimerNum = s_timermanager.numberOfLowPowerActiveTimers;
            activeTimerNum   = s_timermanager.numberOfActiveTimers;
            if ((0U == activeTimerNum) && (0U == activeLPTimerNum))
            {
                if (0U != s_timermanager.timerHardwareIsRunning)
                {
                    HAL_TimerDisable((hal_timer_handle_t)s_timermanager.halTimerHandle);
                    s_timermanager.timerHardwareIsRunning = 0U;
                }
            }
        }
    }
    EnableGlobalIRQ(regPrimask);
    return status;
}

/*! -------------------------------------------------------------------------
 * \brief     Enable the specified timer
 * \param[in] timerHandle - the handle of the timer
 *---------------------------------------------------------------------------*/
static void TimerEnable(timer_handle_t timerHandle)
{
    assert(timerHandle);
    uint32_t regPrimask = DisableGlobalIRQ();

    if ((uint8_t)kTimerStateInactive_c == TimerGetTimerStatus(timerHandle))
    {
        IncrementActiveTimerNumber(TimerGetTimerType(timerHandle));
        TimerSetTimerStatus(timerHandle, (uint8_t)kTimerStateReady_c);
        TimersUpdateSyncTask(HAL_TimerGetCurrentTimerCount((hal_timer_handle_t)s_timermanager.halTimerHandle));
    }
    EnableGlobalIRQ(regPrimask);
}

/*****************************************************************************
******************************************************************************
* Public functions
******************************************************************************
*****************************************************************************/
/*!
 * @brief Initializes timer manager module with the user configuration structure.
 *
 *
 * @param timerConfig              Pointer to user-defined timer configuration structure.
 * @retval kStatus_TimerSuccess      Timer manager initialization succeed.
 * @retval kStatus_TimerError      An error occurred.
 */
timer_status_t TM_Init(timer_config_t *timerConfig)
{
    hal_timer_config_t halTimerConfig;
    hal_timer_handle_t halTimerHandle = &s_timermanager.halTimerHandle[0];
    hal_timer_status_t status;
#if (defined(TM_ENABLE_TIME_STAMP) && (TM_ENABLE_TIME_STAMP > 0U))
    hal_time_stamp_config_t halTimeStampConfig;
    hal_time_stamp_handle_t halTimeStampHandle = &s_timermanager.halTimeStampHandle[0];
#endif
    assert(timerConfig);
    /* Check if TMR is already initialized */
    if (0U == s_timermanager.initialized)
    {
        halTimerConfig.timeout     = 1000;
        halTimerConfig.srcClock_Hz = timerConfig->srcClock_Hz;
        halTimerConfig.instance    = timerConfig->instance;
#if (defined(TM_ENABLE_TIMER_CLOCK_SELECT) && (TM_ENABLE_TIMER_CLOCK_SELECT > 0U))
        halTimerConfig.clockSrcSelect = timerConfig->clockSrcSelect;
#endif
        status = HAL_TimerInit(halTimerHandle, &halTimerConfig);
        assert(kStatus_HAL_TimerSuccess == status);
        (void)status;

        HAL_TimerInstallCallback(halTimerHandle, HAL_TIMER_Callback, NULL);
        s_timermanager.mUsInTimerInterval = halTimerConfig.timeout;
#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
        (void)COMMON_TASK_init();
#else
        osa_status_t osaStatus;
        osaStatus = OSA_EventCreate((osa_event_handle_t)s_timermanager.halTimerTaskEventHandle, 1U);
        assert(KOSA_StatusSuccess == (osa_status_t)osaStatus);
        (void)osaStatus;

        osaStatus = OSA_TaskCreate((osa_task_handle_t)s_timermanager.timerTaskHandle, OSA_TASK(TimerManagerTask), NULL);
        assert(KOSA_StatusSuccess == (osa_status_t)osaStatus);
        (void)osaStatus;
#endif
#endif
#if (defined(TM_ENABLE_TIME_STAMP) && (TM_ENABLE_TIME_STAMP > 0U))
        halTimeStampConfig.srcClock_Hz = timerConfig->timeStampSrcClock_Hz;
        halTimeStampConfig.instance    = timerConfig->timeStampInstance;
#if (defined(TM_ENABLE_TIME_STAMP_CLOCK_SELECT) && (TM_ENABLE_TIME_STAMP_CLOCK_SELECT > 0U))
        halTimeStampConfig.clockSrcSelect = timerConfig->clockSrcSelect;
#endif
        HAL_TimeStampInit(halTimeStampHandle, &halTimeStampConfig);
#endif
        s_timermanager.initialized = 1U;
    }
    return kStatus_TimerSuccess;
}

/*!
 * @brief Deinitialize timer manager module.
 *
 */
void TM_Deinit(void)
{
#if defined(OSA_USED)
#if (defined(TM_COMMON_TASK_ENABLE) && (TM_COMMON_TASK_ENABLE > 0U))
#else
    (void)OSA_EventDestroy((osa_event_handle_t)s_timermanager.halTimerTaskEventHandle);
    (void)OSA_TaskDestroy((osa_task_handle_t)s_timermanager.timerTaskHandle);
#endif
#endif
    HAL_TimerDeinit((hal_timer_handle_t)s_timermanager.halTimerHandle);
    (void)memset(&s_timermanager, 0x0, sizeof(s_timermanager));
}

/*!
 * @brief Power up timer manager module.
 *
 */
void TM_ExitLowpower(void)
{
#if (defined(TM_ENABLE_LOW_POWER_TIMER) && (TM_ENABLE_LOW_POWER_TIMER > 0U))
    HAL_TimerExitLowpower((hal_timer_handle_t)s_timermanager.halTimerHandle);
#endif
#if (defined(TM_ENABLE_TIME_STAMP) && (TM_ENABLE_TIME_STAMP > 0U))
    HAL_TimeStampExitLowpower(s_timermanager.halTimerHandle);
#endif
}

/*!
 * @brief Power down timer manager module.
 *
 */
void TM_EnterLowpower(void)
{
#if (defined(TM_ENABLE_LOW_POWER_TIMER) && (TM_ENABLE_LOW_POWER_TIMER > 0U))
    HAL_TimerEnterLowpower((hal_timer_handle_t)s_timermanager.halTimerHandle);
#endif
}

/*!
 * @brief Get a time-stamp value
 *
 */
uint64_t TM_GetTimestamp(void)
{
#if (defined(TM_ENABLE_TIME_STAMP) && (TM_ENABLE_TIME_STAMP > 0U))
    return HAL_GetTimeStamp((hal_time_stamp_handle_t)s_timermanager.halTimeStampHandle);
#else
    return 0U;
#endif /* TM_ENABLE_TIME_STAMP */
}

/*!
 * @brief Open a timer with user handle.
 *
 * @param timerHandle              Pointer to point to a memory space of size #TIMER_HANDLE_SIZE allocated by the
 * caller.
 * @retval kStatus_TimerSuccess    Timer open succeed.
 * @retval kStatus_TimerError      An error occurred.
 */
timer_status_t TM_Open(timer_handle_t timerHandle)
{
    timer_handle_struct_t *timerState = timerHandle;
    assert(sizeof(timer_handle_struct_t) == TIMER_HANDLE_SIZE);
    assert(timerHandle);
    TIMER_ENTER_CRITICAL();
    TimerSetTimerStatus(timerState, (uint8_t)kTimerStateInactive_c);
    if (NULL == s_timermanager.timerHead)
    {
        s_timermanager.timerHead = timerHandle;
    }
    else
    {
        timerState->next         = s_timermanager.timerHead;
        s_timermanager.timerHead = timerHandle;
    }
    TIMER_EXIT_CRITICAL();
    return kStatus_TimerSuccess;
}

/*!
 * @brief Close a timer with user handle.
 *
 * @param timerHandle - the handle of the timer
 *
 * @retval kStatus_TimerSuccess    Timer close succeed.
 * @retval kStatus_TimerError      An error occurred.
 */
timer_status_t TM_Close(timer_handle_t timerHandle)
{
    timer_status_t status;
    timer_handle_struct_t *timerState = timerHandle;
    timer_handle_struct_t *timerStatePre;
    assert(timerHandle);
    TIMER_ENTER_CRITICAL();
    status = TM_Stop(timerHandle);

    assert(kStatus_TimerSuccess == status);
    (void)status;

    TimerMarkTimerFree(timerHandle);

    timerStatePre = s_timermanager.timerHead;

    if (timerStatePre != timerState)
    {
        while ((NULL != timerStatePre) && (timerStatePre->next != timerState))
        {
            timerStatePre = timerStatePre->next;
        }
        if (NULL != timerStatePre)
        {
            timerStatePre->next = timerState->next;
        }
    }
    else
    {
        s_timermanager.timerHead = timerState->next;
    }
    TIMER_EXIT_CRITICAL();
    return kStatus_TimerSuccess;
}

/*!
 * @brief   Check if all timers except the LP timers are OFF
 *
 *
 * @retval return 1 there are no active non-low power timers, 0 otherwise.
 */

uint8_t TM_AreAllTimersOff(void)
{
    return s_timermanager.numberOfActiveTimers == 0U ? 1U : 0U;
}

/*!
 * @brief  Check if a specified timer is active
 *
 * @param timerHandle - the handle of the timer
 *
 * @retval return 1 if timer is active, return 0 if timer is not active.
 */
uint8_t TM_IsTimerActive(timer_handle_t timerHandle)
{
    assert(timerHandle);
    return (uint8_t)(TimerGetTimerStatus(timerHandle) == (uint8_t)kTimerStateActive_c);
}

/*!
 * @brief  Check if a specified timer is ready
 *
 * @param timerHandle - the handle of the timer
 *
 * @retval return 1 if timer is ready, return 0 if timer is not ready.
 */
uint8_t TM_IsTimerReady(timer_handle_t timerHandle)
{
    assert(timerHandle);
    return (uint8_t)(TimerGetTimerStatus(timerHandle) == (uint8_t)kTimerStateReady_c);
}

/*!
 * @brief  Install a specified timer callback
 *
 * @param timerHandle - the handle of the timer
 * @param callback - callback function
 * @param callbackParam - parameter to callback function
 *
 * @retval kStatus_TimerSuccess    Timer install callback succeed.
 *
 */
timer_status_t TM_InstallCallback(timer_handle_t timerHandle, timer_callback_t callback, void *callbackParam)
{
    timer_handle_struct_t *th = timerHandle;

    assert(timerHandle);
    th->pfCallBack = callback;
    th->param      = callbackParam;

    return kStatus_TimerSuccess;
}

/*!
 * @brief  Start a specified timer
 *
 * @param timerHandle - the handle of the timer
 * @param timerType - the type of the timer
 * @param timerTimout - time expressed in millisecond units
 *
 * @retval kStatus_TimerSuccess    Timer start succeed.
 * @retval kStatus_TimerError      An error occurred.
 */
timer_status_t TM_Start(timer_handle_t timerHandle, uint8_t timerType, uint32_t timerTimeout)
{
    timer_status_t status;
    timer_handle_struct_t *th = timerHandle;
    assert(timerHandle);
    /* Stopping an already stopped timer is harmless. */
    status = TM_Stop(timerHandle);
    assert(status == kStatus_TimerSuccess);

    TimerSetTimerType(timerHandle, timerType);

    if (0U != ((uint8_t)timerType & (uint8_t)kTimerModeSetMinuteTimer))
    {
        th->timeoutInUs = (uint64_t)1000U * 1000U * 60U * timerTimeout;
        th->remainingUs = (uint64_t)1000U * 1000U * 60U * timerTimeout;
    }
    else if (0U != ((uint8_t)timerType & (uint8_t)kTimerModeSetSecondTimer))
    {
        th->timeoutInUs = (uint64_t)1000U * 1000U * timerTimeout;
        th->remainingUs = (uint64_t)1000U * 1000U * timerTimeout;
    }
    else
    {
        th->timeoutInUs = (uint64_t)1000U * timerTimeout;
        th->remainingUs = (uint64_t)1000U * timerTimeout;
    }

    /* Enable timer, the timer task will do the rest of the work. */
    TimerEnable(timerHandle);

    return status;
}

/*!
 * @brief  Stop a specified timer
 *
 * @param timerHandle - the handle of the timer
 *
 * @retval kStatus_TimerSuccess    Timer stop succeed.
 * @retval kStatus_TimerError      An error occurred.
 */
timer_status_t TM_Stop(timer_handle_t timerHandle)
{
    timer_status_t status;
    uint32_t regPrimask = DisableGlobalIRQ();

    status = TimerStop(timerHandle);
    TimersUpdateSyncTask(HAL_TimerGetCurrentTimerCount((hal_timer_handle_t)s_timermanager.halTimerHandle));
    EnableGlobalIRQ(regPrimask);
    return status;
}

/*!
 * @brief  Returns the remaining time until timeout
 *
 * @param timerHandle - the handle of the timer
 *
 * @retval remaining time in microseconds until first timer timeouts.
 */
uint32_t TM_GetRemainingTime(timer_handle_t timerHandle)
{
    timer_handle_struct_t *timerState = timerHandle;
    assert(timerHandle);
    return ((uint32_t)(timerState->remainingUs) -
            (uint32_t)(HAL_TimerGetCurrentTimerCount((hal_timer_handle_t)s_timermanager.halTimerHandle) -
                       s_timermanager.previousTimeInUs));
}

/*!
 * @brief Get the first expire time of timer
 *
 * @param timerHandle - the handle of the timer
 *
 * @retval return the first expire time us of all timer.
 */
uint32_t TM_GetFirstExpireTime(uint8_t timerType)
{
    uint32_t min = 0xFFFFFFFFU;
    uint32_t remainingTime;

    timer_handle_struct_t *th = s_timermanager.timerHead;
    while (NULL != th)
    {
        if ((bool)TM_IsTimerActive(th) && ((timerType & TimerGetTimerType(th)) > 0U))
        {
            remainingTime = TM_GetRemainingTime(th);
            if (remainingTime < min)
            {
                min = remainingTime;
            }
        }
        th = th->next;
    }
    return min;
}

/*!
 * @brief Returns the handle of the timer of the first allocated timer that has the
 *        specified parameter.
 *
 * @param param - specified parameter of timer
 *
 * @retval return the handle of the timer if success.
 */
timer_handle_t TM_GetFirstTimerWithParam(void *param)
{
    timer_handle_struct_t *th = s_timermanager.timerHead;

    while (NULL != th)
    {
        if (th->param == param)
        {
            return th;
        }
        th = th->next;
    }
    return NULL;
}

/*!
 * @brief Returns not counted time before entering in sleep,This function is called
 *        by Low Power module;
 *
 * @retval return microseconds that wasn't counted before entering in sleep.
 */
uint32_t TM_NotCountedTimeBeforeSleep(void)
{
    uint32_t timeUs = 0;
#if (defined(TM_ENABLE_LOW_POWER_TIMER) && (TM_ENABLE_LOW_POWER_TIMER > 0U))
    uint32_t currentTimeInUs;

    if (0U != s_timermanager.numberOfLowPowerActiveTimers)
    {
        currentTimeInUs = HAL_TimerGetCurrentTimerCount((hal_timer_handle_t)s_timermanager.halTimerHandle);
        HAL_TimerDisable((hal_timer_handle_t)s_timermanager.halTimerHandle);
        s_timermanager.timerHardwareIsRunning = 0U;

        /* The hw timer is stopped but keep s_timermanager.timerHardwareIsRunning = TRUE...*/
        /* The Lpm timers are considered as being in running mode, so that  */
        /* not to start the hw timer if a TMR event occurs (this shouldn't happen) */

        timeUs = (uint32_t)(currentTimeInUs - s_timermanager.previousTimeInUs);
        return timeUs;
    }
    return 0;
#endif
}

/*!
 * @brief Sync low power timer in sleep mode,This function is called by Low Power module;
 *
 * @param sleepDurationTmrUs - sleep duration in TMR microseconds
 *
 */
void TM_SyncLpmTimers(uint32_t sleepDurationTmrUs)
{
#if (defined(TM_ENABLE_LOW_POWER_TIMER) && (TM_ENABLE_LOW_POWER_TIMER > 0U))

    TimersUpdateSyncTask(sleepDurationTmrUs);
    HAL_TimerEnable((hal_timer_handle_t)s_timermanager.halTimerHandle);
    s_timermanager.previousTimeInUs = HAL_TimerGetCurrentTimerCount((hal_timer_handle_t)s_timermanager.halTimerHandle);

#else
    sleepDurationTmrUs = sleepDurationTmrUs;
#endif /* #if (TM_ENABLE_LOW_POWER_TIMER) */
}

/*!
 * @brief Make timer task ready after wakeup from lowpower mode,This function is called
 *        by Low Power module;
 *
 */
void TM_MakeTimerTaskReady(void)
{
#if (defined(TM_ENABLE_LOW_POWER_TIMER) && (TM_ENABLE_LOW_POWER_TIMER > 0U))
    NotifyTimersTask();
#endif
}
