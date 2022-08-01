/*! *********************************************************************************
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 *
 * This is the source file for the OS Abstraction layer for thread.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "fsl_common.h"
#include "fsl_os_abstraction.h"
#include "tx_api.h"
#include "tx_event_flags.h"
#include <string.h>
#include "fsl_component_generic_list.h"
#include "fsl_os_abstraction_threadx.h"

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */

/* Weak function. */
#if defined(__GNUC__)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__ICCARM__)
#define __WEAK_FUNC __weak
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __WEAK_FUNC __attribute__((weak))
#endif

#define millisecToTicks(millisec) (((millisec)*TX_TIMER_TICKS_PER_SECOND + 999U) / 1000U)

#ifdef DEBUG_ASSERT
#define OS_ASSERT(condition) \
    if (!(condition))        \
        while (1)            \
            ;
#else
#define OS_ASSERT(condition) (void)(condition);
#endif

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec) \
    (((uint32_t)(msec) + 500uL / (uint32_t)TX_TIMER_TICKS_PER_SECOND) * (uint32_t)TX_TIMER_TICKS_PER_SECOND / 1000uL)

#define TICKS_TO_MSEC(tick) ((uint32_t)((uint64_t)(tick)*1000uL / (uint64_t)TX_TIMER_TICKS_PER_SECOND))

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef struct osa_thread_task
{
    list_element_t link;
    TX_THREAD taskHandle;
} osa_thread_task_t;

typedef struct _osa_event_struct
{
    TX_EVENT_FLAGS_GROUP handle; /* The event handle */
    uint8_t autoClear;           /*!< Auto clear or manual clear   */
} osa_event_struct_t;

/*! @brief State structure for thread osa manager. */
typedef struct _osa_state
{
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
    list_label_t taskList;
#endif
    uint32_t basePriority;
    int32_t basePriorityNesting;
    uint32_t interruptDisableCount;
} osa_state_t;

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
const uint8_t gUseRtos_c = USE_RTOS; // USE_RTOS = 0 for BareMetal and 1 for OS

static TX_INTERRUPT_SAVE_AREA

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
    static osa_state_t s_osaState = {0};
#endif

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemoryAllocate
 * Description   : Reserves the requested amount of memory in bytes.
 *
 *END**************************************************************************/
void *OSA_MemoryAllocate(uint32_t length)
{
    return NULL;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemoryFree
 * Description   : Frees the memory previously reserved.
 *
 *END**************************************************************************/
void OSA_MemoryFree(void *p)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EnterCritical
 * Description   : Enter critical.
 *
 *END**************************************************************************/
void OSA_EnterCritical(uint32_t *sr)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_ExitCritical
 * Description   : Exit critical.
 *
 *END**************************************************************************/
void OSA_ExitCritical(uint32_t sr)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_Init
 * Description   : This function is used to setup the basic services, it should
 * be called first in function main.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
void OSA_Init(void)
{
    LIST_Init((&s_osaState.taskList), 0);
    s_osaState.basePriorityNesting   = 0;
    s_osaState.interruptDisableCount = 0;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_Start
 * Description   : This function is used to start RTOS scheduler.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
/* Configures _tx_initialize_low_level_ptr and tx_application_define_ptr */
extern void Prepare_ThreadX(void);

void OSA_Start(void)
{
    Prepare_ThreadX();
    /* Start ThreadX */
    tx_kernel_enter();
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskGetCurrentHandle
 * Description   : This function is used to get current active task's handler.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_task_handle_t OSA_TaskGetCurrentHandle(void)
{
    return NULL;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskYield
 * Description   : When a task calls this function, it will give up CPU and put
 * itself to the tail of ready list.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskYield(void)
{
    return KOSA_StatusSuccess;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskGetPriority
 * Description   : This function returns task's priority by task handler.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_task_priority_t OSA_TaskGetPriority(osa_task_handle_t taskHandle)
{
    return 0U;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskSetPriority
 * Description   : This function sets task's priority by task handler.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskSetPriority(osa_task_handle_t taskHandle, osa_task_priority_t taskPriority)
{
    return KOSA_StatusSuccess;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskCreate
 * Description   : This function is used to create a task and make it ready.
 * Param[in]     :  threadDef  - Definition of the thread.
 *                  task_param - Parameter to pass to the new thread.
 * Return Thread handle of the new thread, or NULL if failed.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskCreate(osa_task_handle_t taskHandle, const osa_task_def_t *thread_def, osa_task_param_t task_param)
{
    assert(taskHandle);
    osa_status_t status      = KOSA_StatusError;
    osa_thread_task_t *ptask = (osa_thread_task_t *)taskHandle;

    if (tx_thread_create(&ptask->taskHandle,                            /* task handle, allocated by application */
                         (char *)thread_def->tname,                     /* thread name */
                         (void (*)(ULONG))thread_def->pthread,          /* entry function */
                         (ULONG)((ULONG *)task_param),                  /* entry input */
                         (void *)thread_def->tstack,                    /* stack start */
                         (ULONG)thread_def->stacksize,                  /* stack size */
                         PRIORITY_OSA_TO_THREAD(thread_def->tpriority), /* initial priority */
                         0U,                                            /* preempt threshold */
                         0U,                                            /* time slice */
                         true                                           /* auto start */
                         ) == TX_SUCCESS)
    {
        OSA_InterruptDisable();
        (void)LIST_AddTail(&s_osaState.taskList, (list_element_handle_t) & (ptask->link));
        OSA_InterruptEnable();
        status = KOSA_StatusSuccess;
    }
    return status;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskDestroy
 * Description   : This function destroy a task.
 * Param[in]     :taskHandle - Thread handle.
 * Return KOSA_StatusSuccess if the task is destroied, otherwise return KOSA_StatusError.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskDestroy(osa_task_handle_t taskHandle)
{
    assert(taskHandle);
    osa_thread_task_t *ptask = (osa_thread_task_t *)taskHandle;
    osa_status_t status      = KOSA_StatusSuccess;

#if 0
    uint16_t oldPriority;
    /*Change priority to avoid context switches*/
    oldPriority = OSA_TaskGetPriority(OSA_TaskGetCurrentHandle());
    (void)OSA_TaskSetPriority(OSA_TaskGetCurrentHandle(), OSA_PRIORITY_REAL_TIME);
    if (TX_SUCCESS != tx_thread_delete(&ptask->taskHandle))
    {
        status = KOSA_StatusError;
    }
    (void)OSA_TaskSetPriority(OSA_TaskGetCurrentHandle(), oldPriority);
    OSA_InterruptDisable();
    (void)LIST_RemoveElement(taskHandle);
    OSA_InterruptEnable();
#else
    if (TX_SUCCESS != tx_thread_delete(&ptask->taskHandle))
    {
        status = KOSA_StatusError;
    }
    (void)LIST_RemoveElement(taskHandle);
#endif
    return status;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeDelay
 * Description   : This function is used to suspend the active thread for the given number of milliseconds.
 *
 *END**************************************************************************/
void OSA_TimeDelay(uint32_t millisec)
{
    (void)tx_thread_sleep(millisecToTicks(millisec));
}
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeGetMsec
 * Description   : This function gets current time in milliseconds.
 *
 *END**************************************************************************/
uint32_t OSA_TimeGetMsec(void)
{
    return TICKS_TO_MSEC(tx_time_get());
}
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaphoreCreate
 * Description   : This function is used to create a semaphore.
 * Return         : Semaphore handle of the new semaphore, or NULL if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaphoreCreate(osa_semaphore_handle_t semaphoreHandle, uint32_t initValue)
{
    osa_status_t status = KOSA_StatusSuccess;

    assert(semaphoreHandle != NULL);

    if (TX_SUCCESS != tx_semaphore_create((TX_SEMAPHORE *)semaphoreHandle, NULL, (ULONG)initValue))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaphoreCreateBinary
 * Description   : This function is used to create a binary semaphore.
 * Return        : Semaphore handle of the new binary semaphore, or NULL if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaphoreCreateBinary(osa_semaphore_handle_t semaphoreHandle)
{
    /* TODO */
    return KOSA_StatusError;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaphoreDestroy
 * Description   : This function is used to destroy a semaphore.
 * Return        : KOSA_StatusSuccess if the semaphore is destroyed successfully, otherwise return KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaphoreDestroy(osa_semaphore_handle_t semaphoreHandle)
{
    osa_status_t status = KOSA_StatusSuccess;

    assert(semaphoreHandle != NULL);

    if (TX_SUCCESS != tx_semaphore_delete((TX_SEMAPHORE *)semaphoreHandle))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaphoreWait
 * Description   : This function checks the semaphore's counting value, if it is
 * positive, decreases it and returns KOSA_StatusSuccess, otherwise, timeout
 * will be used for wait. The parameter timeout indicates how long should wait
 * in milliseconds. Pass osaWaitForever_c to wait indefinitely, pass 0 will
 * return KOSA_StatusTimeout immediately if semaphore is not positive.
 * This function returns KOSA_StatusSuccess if the semaphore is received, returns
 * KOSA_StatusTimeout if the semaphore is not received within the specified
 * 'timeout', returns KOSA_StatusError if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaphoreWait(osa_semaphore_handle_t semaphoreHandle, uint32_t millisec)
{
    osa_status_t status = KOSA_StatusSuccess;
    ULONG timeoutTicks;

    assert(semaphoreHandle != NULL);

    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeoutTicks = TX_WAIT_FOREVER;
    }
    else if (millisec == osaWaitNone_c)
    {
        timeoutTicks = TX_NO_WAIT;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(millisec);
    }

    if (TX_SUCCESS != tx_semaphore_get((TX_SEMAPHORE *)semaphoreHandle, timeoutTicks))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaphorePost
 * Description   : This function is used to wake up one task that wating on the
 * semaphore. If no task is waiting, increase the semaphore. The function returns
 * KOSA_StatusSuccess if the semaphre is post successfully, otherwise returns
 * KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_SemaphorePost(osa_semaphore_handle_t semaphoreHandle)
{
    osa_status_t status = KOSA_StatusSuccess;

    assert(semaphoreHandle != NULL);

    if (TX_SUCCESS != tx_semaphore_put((TX_SEMAPHORE *)semaphoreHandle))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexCreate
 * Description   : This function is used to create a mutex.
 * Return        : KOSA_StatusSuccess if mutex is created successfully, otherwise returns
 *                 KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexCreate(osa_mutex_handle_t mutexHandle)
{
    assert(mutexHandle);
    osa_status_t status = KOSA_StatusSuccess;

#ifndef CPU2
    if (TX_SUCCESS != tx_mutex_create((TX_MUTEX *)mutexHandle, NULL, 0U))
    {
        status = KOSA_StatusError;
    }
#endif
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexLock
 * Description   : This function checks the mutex's status, if it is unlocked,
 * lock it and returns KOSA_StatusSuccess, otherwise, wait for the mutex.
 * This function returns KOSA_StatusSuccess if the mutex is obtained, returns
 * KOSA_StatusError if any errors occur during waiting. If the mutex has been
 * locked, pass 0 as timeout will return KOSA_StatusTimeout immediately.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexLock(osa_mutex_handle_t mutexHandle, uint32_t millisec)
{
    assert(mutexHandle);
    osa_status_t status = KOSA_StatusSuccess;

#ifndef CPU2
    uint32_t timeoutTicks;
    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeoutTicks = TX_WAIT_FOREVER;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(millisec);
    }

    if (TX_SUCCESS != tx_mutex_get((TX_MUTEX *)mutexHandle, timeoutTicks))
    {
        status = KOSA_StatusError;
    }
#endif
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexUnlock
 * Description   : This function is used to unlock a mutex.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle)
{
    assert(mutexHandle);
    osa_status_t status = KOSA_StatusSuccess;

#ifndef CPU2
    if (TX_SUCCESS != tx_mutex_put((TX_MUTEX *)mutexHandle))
    {
        status = KOSA_StatusError;
    }
#endif
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MutexDestroy
 * Description   : This function is used to destroy a mutex.
 * Return        : KOSA_StatusSuccess if the lock object is destroyed successfully, otherwise return KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_MutexDestroy(osa_mutex_handle_t mutexHandle)
{
    assert(mutexHandle);
    osa_status_t status = KOSA_StatusSuccess;

    if (TX_SUCCESS != tx_mutex_delete((TX_MUTEX *)mutexHandle))
    {
        status = KOSA_StatusError;
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventCreate
 * Description   : This function is used to create a event object.
 * Return        : Event handle of the new event, or NULL if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventCreate(osa_event_handle_t eventHandle, uint8_t autoClear)
{
    osa_event_struct_t *pEventStruct = (osa_event_struct_t *)eventHandle;
    osa_status_t status              = KOSA_StatusSuccess;

    assert(eventHandle != NULL);

    pEventStruct->autoClear = autoClear;

    if (TX_SUCCESS != tx_event_flags_create(&pEventStruct->handle, NULL))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventSet
 * Description   : Set one or more event flags of an event object.
 * Return        : KOSA_StatusSuccess if set successfully, KOSA_StatusError if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventSet(osa_event_handle_t eventHandle, osa_event_flags_t flagsToSet)
{
    osa_event_struct_t *pEventStruct = (osa_event_struct_t *)eventHandle;
    osa_status_t status              = KOSA_StatusSuccess;

    assert(eventHandle != NULL);

    if (TX_SUCCESS != tx_event_flags_set(&pEventStruct->handle, (ULONG)flagsToSet, TX_OR))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventClear
 * Description   : Clear one or more event flags of an event object.
 * Return        :KOSA_StatusSuccess if clear successfully, KOSA_StatusError if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventClear(osa_event_handle_t eventHandle, osa_event_flags_t flagsToClear)
{
    osa_event_struct_t *pEventStruct = (osa_event_struct_t *)eventHandle;
    osa_status_t status              = KOSA_StatusSuccess;

    assert(eventHandle != NULL);

    if (TX_SUCCESS != tx_event_flags_set(&pEventStruct->handle, (ULONG)~flagsToClear, TX_AND))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventGet
 * Description   : This function is used to get event's flags that specified by prameter
 * flagsMask, and the flags (user specified) are obatianed by parameter pFlagsOfEvent. So
 * you should pass the parameter 0xffffffff to specify you want to check all.
 * Return        :KOSA_StatusSuccess if event flags were successfully got, KOSA_StatusError if failed.
 *
 *END**************************************************************************/
osa_status_t OSA_EventGet(osa_event_handle_t eventHandle, osa_event_flags_t flagsMask, osa_event_flags_t *pFlagsOfEvent)
{
    osa_event_struct_t *pEventStruct = (osa_event_struct_t *)eventHandle;
    osa_status_t status              = KOSA_StatusSuccess;
    ULONG flags;

    assert(eventHandle != NULL);

    if (NULL == pFlagsOfEvent)
    {
        return KOSA_StatusError;
    }

    if (TX_SUCCESS != tx_event_flags_info_get(&pEventStruct->handle, NULL, &flags, NULL, NULL, NULL))
    {
        status = KOSA_StatusError;
    }
    else
    {
        *pFlagsOfEvent = (osa_event_flags_t)flags & flagsMask;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventWait
 * Description   : This function checks the event's status, if it meets the wait
 * condition, return KOSA_StatusSuccess, otherwise, timeout will be used for
 * wait. The parameter timeout indicates how long should wait in milliseconds.
 * Pass osaWaitForever_c to wait indefinitely, pass 0 will return the value
 * KOSA_StatusTimeout immediately if wait condition is not met. The event flags
 * will be cleared if the event is auto clear mode. Flags that wakeup waiting
 * task could be obtained from the parameter setFlags.
 * This function returns KOSA_StatusSuccess if wait condition is met, returns
 * KOSA_StatusTimeout if wait condition is not met within the specified
 * 'timeout', returns KOSA_StatusError if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_EventWait(osa_event_handle_t eventHandle,
                           osa_event_flags_t flagsToWait,
                           uint8_t waitAll,
                           uint32_t millisec,
                           osa_event_flags_t *pSetFlags)
{
    osa_event_struct_t *pEventStruct = (osa_event_struct_t *)eventHandle;
    uint32_t timeoutTicks;
    osa_event_flags_t flagsSave;
    UINT options = 0;
    UINT status  = 0;

    assert(eventHandle != NULL);

    /* Clean FreeRTOS cotrol flags */
    flagsToWait = flagsToWait & 0x00FFFFFFU;

    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeoutTicks = TX_WAIT_FOREVER;
    }
    else if (millisec == osaWaitNone_c)
    {
        timeoutTicks = TX_NO_WAIT;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(millisec);
    }

    if (1U == pEventStruct->autoClear)
    {
        options |= TX_EVENT_FLAGS_CLEAR_MASK;
    }

    if (1U == waitAll)
    {
        options |= TX_EVENT_FLAGS_AND_MASK;
    }

    status = tx_event_flags_get(&pEventStruct->handle, flagsToWait, options, (ULONG *)&flagsSave, timeoutTicks);
    if (status != TX_SUCCESS && status != TX_NO_EVENTS)
    {
        return KOSA_StatusError;
    }

    flagsSave &= (osa_event_flags_t)flagsToWait;

    if (NULL != pSetFlags)
    {
        *pSetFlags = (osa_event_flags_t)flagsSave;
    }

    if (0U != flagsSave)
    {
        return KOSA_StatusSuccess;
    }
    else
    {
        return KOSA_StatusTimeout;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventDestroy
 * Description   : This function is used to destroy a event object. Return
 * KOSA_StatusSuccess if the event object is destroyed successfully, otherwise
 * return KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_EventDestroy(osa_event_handle_t eventHandle)
{
    osa_event_struct_t *pEventStruct = (osa_event_struct_t *)eventHandle;
    osa_status_t status              = KOSA_StatusSuccess;

    assert(eventHandle != NULL);

    if (TX_SUCCESS != tx_event_flags_delete(&pEventStruct->handle))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptEnable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
void OSA_InterruptEnable(void)
{
#if 0
    if (0U != __get_IPSR())
    {
        if (1 == s_osaState.basePriorityNesting)
        {
            portCLEAR_INTERRUPT_MASK_FROM_ISR(s_osaState.basePriority);
        }

        if (s_osaState.basePriorityNesting > 0)
        {
            s_osaState.basePriorityNesting--;
        }
    }
    else
    {
        portEXIT_CRITICAL();
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptDisable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
void OSA_InterruptDisable(void)
{
#if 0
    if (0U != __get_IPSR())
    {
        if (0 == s_osaState.basePriorityNesting)
        {
            s_osaState.basePriority = portSET_INTERRUPT_MASK_FROM_ISR();
        }
        s_osaState.basePriorityNesting++;
    }
    else
    {
        portENTER_CRITICAL();
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EnableIRQGlobal
 * Description   : enable interrupts using PRIMASK register.
 *
 *END**************************************************************************/
void OSA_EnableIRQGlobal(void)
{
    TX_RESTORE
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_DisableIRQGlobal
 * Description   : disable interrupts using PRIMASK register.
 *
 *END**************************************************************************/
void OSA_DisableIRQGlobal(void)
{
    TX_DISABLE
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InstallIntHandler
 * Description   : This function is used to install interrupt handler.
 *
 *END**************************************************************************/
void OSA_InstallIntHandler(uint32_t IRQNumber, void (*handler)(void))
{
#if defined(__IAR_SYSTEMS_ICC__)
    _Pragma("diag_suppress = Pm138")
#endif
#if defined(ENABLE_RAM_VECTOR_TABLE)
        (void) InstallIRQHandler((IRQn_Type)IRQNumber, (uint32_t) * (uint32_t *)&handler);
#endif /* ENABLE_RAM_VECTOR_TABLE. */
#if defined(__IAR_SYSTEMS_ICC__)
    _Pragma("diag_remark = PM138")
#endif
}
