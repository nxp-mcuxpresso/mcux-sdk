/*! *********************************************************************************
 * Copyright 2020-2021, 2024 NXP
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

#define OSA_MEM_MAGIC_NUMBER (12345U)
#define OSA_MEM_SIZE_ALIGN(var, alignbytes) \
    ((unsigned int)((var) + ((alignbytes)-1U)) & (unsigned int)(~(unsigned int)((alignbytes)-1U)))

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
    TX_EVENT_FLAGS_GROUP eventHandle; /* The event handle */
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

/*! @brief Definition structure contains allocated memory information.*/
typedef struct _osa_mem_align_control_block
{
    uint16_t identifier; /*!< Identifier for the memory control block. */
    uint16_t offset;     /*!< offset from aligned address to real address */
} osa_mem_align_cb_t;

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
void *OSA_MemoryAllocate(uint32_t memLength)
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

void *OSA_MemoryAllocateAlign(uint32_t memLength, uint32_t alignbytes)
{
    osa_mem_align_cb_t *p_cb = NULL;
    uint32_t alignedsize;

    /* Check overflow. */
    alignedsize = (uint32_t)(unsigned int)OSA_MEM_SIZE_ALIGN(memLength, alignbytes);
    if (alignedsize < memLength)
    {
        return NULL;
    }

    if (alignedsize > 0xFFFFFFFFU - alignbytes - sizeof(osa_mem_align_cb_t))
    {
        return NULL;
    }

    alignedsize += alignbytes + (uint32_t)sizeof(osa_mem_align_cb_t);

    union
    {
        void *pointer_value;
        uintptr_t unsigned_value;
    } p_align_addr, p_addr;

    p_addr.pointer_value = OSA_MemoryAllocate(alignedsize);

    if (p_addr.pointer_value == NULL)
    {
        return NULL;
    }

    p_align_addr.unsigned_value = OSA_MEM_SIZE_ALIGN(p_addr.unsigned_value + sizeof(osa_mem_align_cb_t), alignbytes);

    p_cb             = (osa_mem_align_cb_t *)(p_align_addr.unsigned_value - 4U);
    p_cb->identifier = OSA_MEM_MAGIC_NUMBER;
    p_cb->offset     = (uint16_t)(p_align_addr.unsigned_value - p_addr.unsigned_value);

    return p_align_addr.pointer_value;
}

void OSA_MemoryFreeAlign(void *p)
{
    union
    {
        void *pointer_value;
        uintptr_t unsigned_value;
    } p_free;
    p_free.pointer_value = p;
    osa_mem_align_cb_t *p_cb = (osa_mem_align_cb_t *)(p_free.unsigned_value - 4U);

    if (p_cb->identifier != OSA_MEM_MAGIC_NUMBER)
    {
        return;
    }

    p_free.unsigned_value = p_free.unsigned_value - p_cb->offset;

    OSA_MemoryFree(p_free.pointer_value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_EnterCritical
 * Description   : Enter critical.
 *
 *END**************************************************************************/
void OSA_EnterCritical(uint32_t *sr)
{
    *sr = tx_interrupt_control(TX_INT_DISABLE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_ExitCritical
 * Description   : Exit critical.
 *
 *END**************************************************************************/
void OSA_ExitCritical(uint32_t sr)
{
    (void)tx_interrupt_control(sr);
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
__WEAK_FUNC void Prepare_ThreadX(void);
__WEAK_FUNC void Prepare_ThreadX(void)
{
}
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
    list_element_handle_t list_element;
    osa_thread_task_t *ptask;

    list_element = LIST_GetHead(&s_osaState.taskList);
    while (NULL != list_element)
    {
        ptask = (osa_thread_task_t *)(void *)list_element;
        if ((TX_THREAD *)&ptask->taskHandle == tx_thread_identify())
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
    tx_thread_relinquish();
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
    osa_thread_task_t *ptask = (osa_thread_task_t *)taskHandle;
    UINT status      = 0;
    CHAR *task_name;
    UINT task_status;
    ULONG scheduled_count;
    UINT priority_tmp;
    UINT preempt;
    ULONG time_slice;
    TX_THREAD *next_thread;
    TX_THREAD *suspended_thread;

    assert(&ptask->taskHandle != NULL);

    status = tx_thread_info_get((TX_THREAD *)&ptask->taskHandle, &task_name, &task_status, &scheduled_count,
                                &priority_tmp, &preempt, &time_slice, &next_thread, &suspended_thread);

    if (status != TX_SUCCESS)
    {
        return 0U;
    }

    return PRIORITY_THREAD_TO_OSA(priority_tmp);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskSetPriority
 * Description   : This function sets task's priority by task handler.
 * This function cannot be called within an interrupt handler, nor during 
 * the initialization phase of ThreadX.
 *
 *END**************************************************************************/
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskSetPriority(osa_task_handle_t taskHandle, osa_task_priority_t taskPriority)
{
    assert(taskHandle);
    osa_thread_task_t *ptask = (osa_thread_task_t *)taskHandle;
    UINT status      = 0;
    UINT priority;

    status = tx_thread_priority_change((TX_THREAD *)&ptask->taskHandle, PRIORITY_OSA_TO_THREAD(taskPriority), &priority);

    if (status != TX_SUCCESS)
    {
        return KOSA_StatusError;
    }

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

    if (tx_thread_create(
            &ptask->taskHandle,                            /* task handle, allocated by application */
            (char *)thread_def->tname,                     /* thread name */
            (void (*)(ULONG))thread_def->pthread,          /* entry function */
            (ULONG)((ULONG *)task_param),                  /* entry input */
            (void *)thread_def->tstack,                    /* stack start */
            (ULONG)thread_def->stacksize,                  /* stack size */
            PRIORITY_OSA_TO_THREAD(thread_def->tpriority), /* initial priority */
            PRIORITY_OSA_TO_THREAD(
                thread_def->tpriority), /* preempt threshold (same value than the priority means disabled) */
            0U,                         /* time slice */
            true                        /* auto start */
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

    osa_task_priority_t oldPriority;
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

    if (TX_SUCCESS != tx_event_flags_create(&pEventStruct->eventHandle, NULL))
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

    if (TX_SUCCESS != tx_event_flags_set(&pEventStruct->eventHandle, (ULONG)flagsToSet, TX_OR))
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

    if (TX_SUCCESS != tx_event_flags_set(&pEventStruct->eventHandle, (ULONG)~flagsToClear, TX_AND))
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

    if (TX_SUCCESS != tx_event_flags_info_get(&pEventStruct->eventHandle, NULL, &flags, NULL, NULL, NULL))
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

    status = tx_event_flags_get(&pEventStruct->eventHandle, flagsToWait, options, (ULONG *)&flagsSave, timeoutTicks);
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

    if (TX_SUCCESS != tx_event_flags_delete(&pEventStruct->eventHandle))
    {
        status = KOSA_StatusError;
    }

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
    assert(NULL != msgqHandle);

    /* Create the message queue where the number and size is specified by msgNo and msgSize */
    if (TX_SUCCESS == tx_queue_create((TX_QUEUE *)msgqHandle, (CHAR *)"queue 0", msgSize, (uint8_t *)msgqHandle + OSA_MSGQ_HANDLE_SIZE , msgNo *msgSize))
    {
        return KOSA_StatusSuccess;
    }
    return KOSA_StatusError;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQPut
 * Description   : This function is used to put a message to a message queue.
 * Return         : KOSA_StatusSuccess if the message is put successfully, otherwise return KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQPut(osa_msgq_handle_t msgqHandle, osa_msg_handle_t pMessage)
{
    assert(NULL != msgqHandle);

    if (TX_SUCCESS == tx_queue_send((TX_QUEUE *)msgqHandle, pMessage, TX_WAIT_FOREVER))
    {
        return KOSA_StatusSuccess;
    }

    return KOSA_StatusError;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQGet
 * Description   : This function checks the queue's status, if it is not empty,
 * get message from it and return KOSA_StatusSuccess, otherwise, timeout will
 * be used for wait. The parameter timeout indicates how long should wait in
 * milliseconds. Pass osaWaitForever_c to wait indefinitely, pass 0 will return
 * KOSA_StatusTimeout immediately if queue is empty.
 * This function returns KOSA_StatusSuccess if message is got successfully,
 * returns KOSA_StatusTimeout if message queue is empty within the specified
 * 'timeout', returns KOSA_StatusError if any errors occur during waiting.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQGet(osa_msgq_handle_t msgqHandle, osa_msg_handle_t pMessage, uint32_t millisec)
{
    osa_status_t osaStatus              = KOSA_StatusError;
    assert(NULL != msgqHandle);

    uint32_t timeoutTicks;

    if (millisec == osaWaitForever_c)
    {
        timeoutTicks = TX_WAIT_FOREVER;
    }
    else
    {
        timeoutTicks = MSEC_TO_TICK(millisec);
    }
    if (TX_SUCCESS != tx_queue_receive((TX_QUEUE *)msgqHandle, pMessage, timeoutTicks))
    {
        osaStatus = KOSA_StatusTimeout; /* not able to send it to the queue? */
    }
    else
    {
        osaStatus = KOSA_StatusSuccess;
    }
    return osaStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQAvailableMsgs
 * Description   : This function is used to get the available message.
 * Return        : Available message count
 *
 *END**************************************************************************/
int OSA_MsgQAvailableMsgs(osa_msgq_handle_t msgqHandle)
{
    CHAR *name;
    ULONG enqueued;
    ULONG available_storage;
    TX_THREAD *first_suspended;
    ULONG suspended_count;
    TX_QUEUE *next_queue;
    assert(NULL != msgqHandle);
    
    if (TX_SUCCESS == tx_queue_info_get((TX_QUEUE *)msgqHandle, &name, &enqueued, &available_storage, &first_suspended, &suspended_count, &next_queue))
    {
       return  (int)available_storage;
    }

    return -1;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_MsgQDestroy
 * Description   : This function is used to destroy the message queue.
 * Return        : KOSA_StatusSuccess if the message queue is destroyed successfully, otherwise return KOSA_StatusError.
 *
 *END**************************************************************************/
osa_status_t OSA_MsgQDestroy(osa_msgq_handle_t msgqHandle)
{
    assert(NULL != msgqHandle);
    
    if (TX_SUCCESS == tx_queue_delete((TX_QUEUE *)msgqHandle))
    {
        return KOSA_StatusSuccess;
    }
    return KOSA_StatusError;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptEnable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
void OSA_InterruptEnable(void)
{
    (void)tx_interrupt_control(TX_INT_ENABLE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptDisable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
void OSA_InterruptDisable(void)
{
    (void)tx_interrupt_control(TX_INT_DISABLE);
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

/**
 * Warning: Needs to be implemented
 */
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskNotifyGet(osa_notify_time_ms_t waitTime_ms)
{
    return KOSA_StatusError;
}
#endif

/**
 * Warning: Needs to be implemented
 */
#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskNotifyPost(osa_task_handle_t taskHandle)
{
    return KOSA_StatusError;
}
#endif

/**
 * Warning: Needs to be implemented
 */
osa_semaphore_count_t OSA_SemaphoreGetCount(osa_semaphore_handle_t semaphoreHandle)
{
    assert(false);

    return 0;
}