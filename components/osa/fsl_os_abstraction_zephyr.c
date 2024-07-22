/*! *********************************************************************************
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2019-2024 NXP
 * All rights reserved.
 *
 *
 * This is the source file for the OS Abstraction layer for Zephyr.
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
#include <string.h>
#include "fsl_component_generic_list.h"
#include "fsl_os_abstraction_zephyr.h"

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

#define millisecToTicks(millisec) k_ms_to_ticks_floor32(millisec)

#ifdef DEBUG_ASSERT
#define OS_ASSERT(condition) \
    if (!(condition))        \
        while (1)            \
            ;
#else
#define OS_ASSERT(condition) (void)(condition);
#endif

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec) k_ms_to_ticks_floor32(msec)

#define TICKS_TO_MSEC(tick) k_ticks_to_ms_floor32(tick)

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef struct osa_zephyr_task
{
    list_element_t link;
    struct k_thread thread;
    k_tid_t tid;
    k_thread_stack_t *stack;
    struct k_sem event;
} osa_zephyr_task_t;

typedef struct _osa_event_struct
{
    struct k_event handle; /* The event handle */
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
void *OSA_MemoryAllocate(uint32_t memLength)
{
    void *p = (void *)k_malloc(memLength);

    if (NULL != p)
    {
        (void)memset(p, 0, memLength);
    }

    return p;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MemoryFree
 * Description   : Frees the memory previously reserved.
 *
 *END**************************************************************************/
void OSA_MemoryFree(void *p)
{
    k_free(p);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EnterCritical
 * Description   : Enter critical.
 *
 *END**************************************************************************/
void OSA_EnterCritical(uint32_t *sr)
{
    (void)sr;

    irq_lock();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_ExitCritical
 * Description   : Exit critical.
 *
 *END**************************************************************************/
void OSA_ExitCritical(uint32_t sr)
{
    irq_unlock(sr);
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
    list_element_handle_t list_element;
    osa_zephyr_task_t *ptask;

    list_element = LIST_GetHead(&s_osaState.taskList);
    while (NULL != list_element)
    {
        ptask = (osa_zephyr_task_t *)(void *)list_element;
        if (ptask->tid == k_current_get())
        {
            return (osa_task_handle_t)ptask;
        }
        list_element = LIST_GetNext(list_element);
    }
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
void OSA_TaskYield(void)
{
    k_yield();
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
    assert(taskHandle);
    osa_zephyr_task_t *ptask = (osa_zephyr_task_t *)taskHandle;

    return (osa_task_priority_t)k_thread_priority_get(ptask->tid);
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
    assert(taskHandle);
    osa_zephyr_task_t *ptask = (osa_zephyr_task_t *)taskHandle;

    k_thread_priority_set(ptask->tid, (int)taskPriority);

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

/* Used to convert 3 argument zephyr threads to one arg OSA threads */
static void OSA_Thread_Wrapper(void *entry, void *arg, void *tdata)
{
    /* Save thread data */
    k_thread_custom_data_set(tdata);
    void (*func)(void *) = entry;
    func(arg);
}

osa_status_t OSA_TaskCreate(osa_task_handle_t taskHandle, const osa_task_def_t *thread_def, osa_task_param_t task_param)
{
    assert(taskHandle);
    osa_zephyr_task_t *ptask = (osa_zephyr_task_t *)taskHandle;

    /* init semaphore before create thread to avoid restart thread getting semaphore unexpectedly */
    k_sem_init(&ptask->event, 0, 1);

    ptask->stack = k_thread_stack_alloc((size_t)thread_def->stacksize, 0);

    if (ptask->stack == NULL)
    {
        return KOSA_StatusError;
    }

    ptask->tid = k_thread_create(&ptask->thread, ptask->stack, (size_t)thread_def->stacksize, OSA_Thread_Wrapper, thread_def->pthread, task_param, &ptask->thread,
                                 PRIORITY_OSA_TO_ZEPHYR(thread_def->tpriority), 0, K_NO_WAIT);
    k_thread_name_set(ptask->tid, (char *)thread_def->tname);

    OSA_InterruptDisable();
    (void)LIST_AddTail(&s_osaState.taskList, (list_element_handle_t) & (ptask->link));
    OSA_InterruptEnable();

    return KOSA_StatusSuccess;
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
    osa_zephyr_task_t *ptask = (osa_zephyr_task_t *)taskHandle;
    osa_status_t status      = KOSA_StatusSuccess;

    k_thread_abort(ptask->tid);

    k_sem_reset((struct k_sem *)&ptask->event);

    if (0 != k_thread_stack_free(ptask->stack))
    {
        return KOSA_StatusError;
    }
    OSA_InterruptDisable();
    (void)LIST_RemoveElement(taskHandle);
    OSA_InterruptEnable();

    return status;
}
#endif

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
/**
 * Wait for task notification
 *
 * This function waits for task notification from other task or interrupt
 * context. This is similar to binary semaphore, but uses less RAM and much
 * faster than semaphore mechanism
 *
 * @param[in] wait_time Timeout specified in no. of OS ticks
 *
 * @return WM_SUCCESS when notification is successful
 * @return -WM_FAIL on failure or timeout
 */
osa_status_t OSA_EventNotifyGet(unsigned long wait_time)
{
    osa_zephyr_task_t *ptask = OSA_TaskGetCurrentHandle();
    osa_status_t status = KOSA_StatusSuccess;
    k_timeout_t timeout = {0};

    timeout.ticks = MSEC_TO_TICK(wait_time);

    if (0U != k_sem_take((struct k_sem *)&ptask->event, timeout))
    {
        status = KOSA_StatusError;
    }

    return status;
}

/**
 * Give task notification
 *
 * This function gives task notification so that waiting task can be
 * unblocked. This is similar to binary semaphore, but uses less RAM and much
 * faster than semaphore mechanism
 *
 * @param[in] task Task handle to be notified
 *
 * @return WM_SUCCESS when notification is successful
 * @return -WM_FAIL on failure or timeout
 */
osa_status_t OSA_EventNotifyPost(osa_task_handle_t taskHandle)
{
    assert(taskHandle);
    osa_zephyr_task_t *ptask = (osa_zephyr_task_t *)taskHandle;
    osa_status_t status      = KOSA_StatusSuccess;

    k_sem_give(&ptask->event);

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
    (void)k_msleep(millisec);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TimeGetMsec
 * Description   : This function gets current time in milliseconds.
 *
 *END**************************************************************************/
uint32_t OSA_TimeGetMsec(void)
{
    return TICKS_TO_MSEC(k_uptime_get_32());
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_SemaphorePrecreate
 * Description   : This function is used to pre-create a semaphore.
 * Return         : KOSA_StatusSuccess
 *
 *END**************************************************************************/

osa_status_t OSA_SemaphorePrecreate(osa_semaphore_handle_t semaphoreHandle, osa_task_ptr_t taskHandler)
{
    semaphoreHandle = semaphoreHandle;
    taskHandler     = taskHandler;
    return KOSA_StatusSuccess;
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

    if (0U != k_sem_init((struct k_sem *)semaphoreHandle, initValue, 1))
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

    k_sem_reset((struct k_sem *)semaphoreHandle);

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
    k_timeout_t timeout = {0};

    assert(semaphoreHandle != NULL);

    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeout = K_FOREVER;
    }
    else if (millisec == osaWaitNone_c)
    {
        timeout = K_NO_WAIT;
    }
    else
    {
        timeout.ticks = MSEC_TO_TICK(millisec);
    }

    if (0U != k_sem_take((struct k_sem *)semaphoreHandle, timeout))
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

    k_sem_give((struct k_sem *)semaphoreHandle);

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
    if (0U != k_mutex_init((struct k_mutex *)mutexHandle))
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
    k_timeout_t timeout = {0};
    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeout = K_FOREVER;
    }
    else
    {
        timeout.ticks = MSEC_TO_TICK(millisec);
    }

    if (0U != k_mutex_lock((struct k_mutex *)mutexHandle, timeout))
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
    if (0U != k_mutex_unlock((struct k_mutex *)mutexHandle))
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

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EventPrecreate
 * Description   : This function is used to pre-create a event.
 * Return         : KOSA_StatusSuccess
 *
 *END**************************************************************************/

osa_status_t OSA_EventPrecreate(osa_event_handle_t eventHandle, osa_task_ptr_t taskHandler)
{
    eventHandle = eventHandle;
    taskHandler = taskHandler;
    return KOSA_StatusSuccess;
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

    k_event_init(&pEventStruct->handle);

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

    (void)k_event_set(&pEventStruct->handle, flagsToSet);

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

    k_event_clear(&pEventStruct->handle, flagsToClear);

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

    assert(eventHandle != NULL);

    if (NULL == pFlagsOfEvent)
    {
        return KOSA_StatusError;
    }

    *pFlagsOfEvent = k_event_test(&pEventStruct->handle, flagsMask);

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
    k_timeout_t timeout = {0};
    osa_event_flags_t flagsSave;

    assert(eventHandle != NULL);

    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeout = K_FOREVER;
    }
    else if (millisec == osaWaitNone_c)
    {
        timeout = K_NO_WAIT;
    }
    else
    {
        timeout.ticks = MSEC_TO_TICK(millisec);
    }

    if (1U == waitAll)
    {
        flagsSave = k_event_wait_all(&pEventStruct->handle, flagsToWait, pEventStruct->autoClear, timeout);
    }
    else
    {
        flagsSave = k_event_wait(&pEventStruct->handle, flagsToWait, pEventStruct->autoClear, timeout);
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
    osa_status_t status              = KOSA_StatusSuccess;

    assert(eventHandle != NULL);

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQCreate
 * Description   : This function is used to create a message queue.
 * Return        : the handle to the message queue if create successfully, otherwise
 * return NULL.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQCreate(osa_msgq_handle_t msgqHandle, uint32_t msgNo, uint32_t msgSize)
{
    osa_status_t status = KOSA_StatusSuccess;

    assert(msgqHandle != NULL);

    /* Create the message queue */
    k_msgq_init((struct k_msgq *)msgqHandle, (uint8_t *)((uint8_t *)msgqHandle + OSA_MSGQ_HANDLE_SIZE), msgSize, msgNo);

    return status;
}

osa_status_t OSA_MsgQPut(osa_msgq_handle_t msgqHandle, osa_msg_handle_t pMessage)
{
    osa_status_t status = KOSA_StatusSuccess;

    assert(msgqHandle != NULL);

    if (0U != k_msgq_put((struct k_msgq *)msgqHandle, pMessage, K_NO_WAIT))
    {
        status = KOSA_StatusError;
    }

    return status;
}

osa_status_t OSA_MsgQGet(osa_msgq_handle_t msgqHandle, osa_msg_handle_t pMessage, uint32_t millisec)
{
    osa_status_t status = KOSA_StatusSuccess;
    k_timeout_t timeout = {0};

    assert(msgqHandle != NULL);

    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c)
    {
        timeout = K_FOREVER;
    }
    else if (millisec == osaWaitNone_c)
    {
        timeout = K_NO_WAIT;
    }
    else
    {
        timeout.ticks = MSEC_TO_TICK(millisec);
    }

    if (0U != k_msgq_get((struct k_msgq *)msgqHandle, pMessage, timeout))
    {
        status = KOSA_StatusError;
    }

    return status;
}

int OSA_MsgQAvailableMsgs(osa_msgq_handle_t msgqHandle)
{
    uint32_t nmsg = 0;

    assert(msgqHandle != NULL);

    nmsg = k_msgq_num_used_get((struct k_msgq *)msgqHandle);

    return (int)nmsg;
}

osa_status_t OSA_MsgQDestroy(osa_msgq_handle_t msgqHandle)
{
    osa_status_t status = KOSA_StatusSuccess;

    assert(msgqHandle != NULL);

    k_msgq_purge((struct k_msgq *)msgqHandle);

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
    __enable_irq();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptDisable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
void OSA_InterruptDisable(void)
{
    __disable_irq();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EnableIRQGlobal
 * Description   : enable interrupts using PRIMASK register.
 *
 *END**************************************************************************/
void OSA_EnableIRQGlobal(void)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_DisableIRQGlobal
 * Description   : disable interrupts using PRIMASK register.
 *
 *END**************************************************************************/
void OSA_DisableIRQGlobal(void)
{
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
