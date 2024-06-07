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

#include "fsl_os_abstraction.h"
#include "fsl_os_abstraction_zephyr.h"

#include <string.h>
#include <zephyr/kernel.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define OSA_RETURN_IF_HANDLE_IS_NULL(handlePtr, retVal) \
    {                                                   \
        if (handlePtr == NULL)                          \
        {                                               \
            OSA_ASSERT(false, "OSA Handle is NULL!");   \
            return retVal;                              \
        }                                               \
    }

#define OSA_RETURN_IF_IS_IN_ISR(retVal)                          \
    {                                                            \
        if (k_is_in_isr())                                       \
        {                                                        \
            OSA_ASSERT(false, "Cannot execute in isr routine!"); \
            return retVal;                                       \
        }                                                        \
    }

#define OSA_RETURN_IF_WRONG_CHECKMARK(checked, expected, retVal) \
    {                                                            \
        if (checked != expected)                                 \
        {                                                        \
            OSA_ASSERT(false, "Checkmark is not correct");       \
            return retVal;                                       \
        }                                                        \
    }

#define OSA_RETURN_IF_WAITING_IN_ISR(timeToWait, retVal)               \
    {                                                                  \
        if (k_is_in_isr() && timeToWait > 0)                           \
        {                                                              \
            OSA_ASSERT(false, "Cannot wait for event in ISR routine"); \
            return retVal;                                             \
        }                                                              \
    }

#ifndef CONFIG_OSA_DEBUG_ASSERT_ENABLED
/** Enable this macro to trigger assert on error */
#define CONFIG_OSA_DEBUG_ASSERT_ENABLED (0u)
#endif

#if (CONFIG_OSA_DEBUG_ASSERT_ENABLED == 1)
#define OSA_ASSERT(condition, message, ...) __ASSERT(condition, message __VA_OPT__(, ) __VA_ARGS__)
#else
#define OSA_ASSERT(condition, message, ...)
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
static sys_dlist_t s_OSA_TaskList = {0}; /*!< List of alive tasks. Used for binding Zephyr and OSA task handles. */
static bool s_OSA_IsInitialized   = false; /*!< Indicates whether OSA_Init() was called. */
#endif

static uint32_t s_OSA_InterruptDisableCount = 0; /*!< Used for correct enabling/disabling IRQs based on call count. */

const uint8_t gUseRtos_c = USE_RTOS; /*!< USE_RTOS = 0 for BareMetal and 1 for OS. */

/*******************************************************************************
 * Code - Helpers and static functions
 ******************************************************************************/

/**
 * @brief Coverts timeout in OSA's data type into Zephyr's data type
 *
 * @param timeout_ms Input time to be converted in ms
 * @return k_timeout_t Output time in Zephyr's data type
 */
static k_timeout_t s_OSA_ConvertTimeoutToZephyr(uint32_t timeout_ms)
{
    switch (timeout_ms)
    {
        case osaWaitNone_c:
            return K_NO_WAIT;
        case osaWaitForever_c:
            return K_FOREVER;
        default:
            return K_MSEC(timeout_ms);
    }
}

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
/*!
 * @brief Converts task priority from OSA format to Zephyr format
 *
 * @param taskPriority_osa OSA task priority
 * @return task priority in Zephyr format
 *
 * uint16_t is converted into int16_t. Be aware, if result is negative, thread
 * will become cooperative thread. See Zephyr's docu related to cooperative threads.
 */
static int s_OSA_ConvertTaskPriorityFromOsaToZephyr(osa_task_priority_t taskPriority_osa)
{
    int taskPriority_zephyr = (int)(int16_t)taskPriority_osa;

    return taskPriority_zephyr;
}
#endif /* (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U)) */

/*!
 * @brief Wrapper - Translates one argument API into three arguments API
 *
 * @param p1 Function pointer to the task body function
 * @param p2 Argument to the task body function
 * @param p3 Thread custom data or NULL

 OSA API supports task body function which takes only one argument.
 Zephyr API supports task body function which takes three arguments.
 When creating task using OSA we must somehow ensure the translation.
 This is helper function which does the job. Zephyrs task enters this
 function (with 3 arguments) and jumps on function stored in p1 with
 arguments stored in p2 afterwards.
 */
void s_OSA_TaskCallback(void *p1, void *p2, void *p3)
{
    /* Save thread data */
#ifdef CONFIG_THREAD_CUSTOM_DATA
    k_thread_custom_data_set(p3);
#endif

    void (*taskBodyFunction)(void *taskArgs) = p1;

    taskBodyFunction(p2);
}

/*******************************************************************************
 * Code - System API
 ******************************************************************************/

void *OSA_MemoryAllocate(uint32_t memLength)
{
    /* Allocating on the System Heap */
    void *p = k_malloc(memLength);

    OSA_ASSERT(p != NULL, "Memory of length: %u, could not be allocated\r\n", memLength);

    if (p != NULL)
    {
        (void)memset(p, 0, memLength);
    }

    return p;
}

void OSA_MemoryFree(void *p)
{
    OSA_ASSERT(p != NULL, "Trying to free memory pointing to NULL\r\n");

    if (p != NULL)
    {
        k_free(p);
    }
}

void *OSA_MemoryAllocateAlign(uint32_t memLength, uint32_t alignbytes)
{
    /* Allocating on the System Heap */
    void *p = k_aligned_alloc(alignbytes, memLength);

    OSA_ASSERT(p != NULL, "Memory of length: %u, could not be allocated\r\n", memLength);

    if (p != NULL)
    {
        (void)memset(p, 0, memLength);
    }

    return p;
}

void OSA_MemoryFreeAlign(void *p)
{
    OSA_ASSERT(p != NULL, "Trying to free memory pointing to NULL\r\n");

    if (p != NULL)
    {
        k_free(p);
    }
}

void OSA_EnterCritical(uint32_t *sr)
{
    OSA_ASSERT(sr != NULL, "Critical section counter pointer is NULL\r\n");

    *sr = irq_lock();
}

void OSA_ExitCritical(uint32_t sr)
{
    irq_unlock(sr);
}

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
/**
 * @brief OSA initialization.
 *
 * This function has to be called once before calling any task API.
 *
 * Currently it initializes only things related to Task API (currently nothing more to initialize).
 * Warning: If OSA_Init is not explicitely called, initialization is called inside OSA_TaskCreate,
 *          ensuring OSA Task API will work correctly.
 */
void OSA_Init(void)
{
    OSA_InterruptDisable();

    if(s_OSA_IsInitialized != true)
    {
        sys_dlist_init(&s_OSA_TaskList);
    #if 0
        // Initialization to 0 should be done automatically since it is static varriable
        s_OSA_InterruptDisableCount = 0;
    #endif
        s_OSA_IsInitialized = true;
    }

    OSA_InterruptEnable();
}
#endif

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
/**
 * Warning: Function OSA_Start without effect. Scheduler started automatically in Zephyr.
 */
void OSA_Start(void)
{
}
#endif

void OSA_InterruptEnable(void)
{
    __enable_irq();
}

void OSA_InterruptDisable(void)
{
    __disable_irq();
}

void OSA_EnableIRQGlobal(void)
{
    if (s_OSA_InterruptDisableCount > 0U)
    {
        s_OSA_InterruptDisableCount--;

        if (0U == s_OSA_InterruptDisableCount)
        {
            __enable_irq();
        }
        /* call core API to enable the global interrupt*/
    }
}

void OSA_DisableIRQGlobal(void)
{
    /* call core API to disable the global interrupt*/
    __disable_irq();

    /* update counter*/
    s_OSA_InterruptDisableCount++;
}

/*!
 * Prevents scheduler for scheduling out currently running task.
 */
void OSA_DisableScheduler(void)
{
    k_sched_lock();
}

/*!
 * Enables scheduler for scheduling out currently running task.
 */
void OSA_EnableScheduler(void)
{
    k_sched_unlock();
}

void OSA_TimeDelay(uint32_t millisec)
{
    k_msleep(millisec);
}

/**
 * Time overflows after ~8 years of continuous usage.
 */
uint32_t OSA_TimeGetMsec(void)
{
    return k_uptime_get_32();
}

/**
 * Function OSA_InstallIntHandler currently not supported.
 */
void OSA_InstallIntHandler(uint32_t IRQNumber, void (*handler)(void))
{
    OSA_ASSERT(false, "Function %s not implemented/supported", __FUNCTION__);
}

/*******************************************************************************
 * Code - Thread API
 ******************************************************************************/

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
/**
 * Warning: Unused following variables in thread_def: tlink, useFloat, instances.
 *
 * Calls also OSA_Init if it wasn't called explicitely before to ensure OSA Task API
 * works correctly. Please see OSA_Init().
 */
osa_status_t OSA_TaskCreate(osa_task_handle_t taskHandle, const osa_task_def_t *thread_def, osa_task_param_t task_param)
{
    osa_zephyr_taskHandle_t *z_taskHandle = (osa_zephyr_taskHandle_t *)taskHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_taskHandle, KOSA_StatusError)

    (void)memset(z_taskHandle, 0, OSA_TASK_HANDLE_SIZE);

    OSA_Init();

    /* Converting from uint16_t OSA format into Zephyr's priority format */
    int taskPriority = s_OSA_ConvertTaskPriorityFromOsaToZephyr(thread_def->tpriority);

    if (thread_def->stacksize == 0)
    {
        OSA_ASSERT(false, "Stack size is less or equall 0!\r\n");
        return KOSA_StatusError;
    }

    OSA_InterruptDisable();

    /* init semaphore before create thread to avoid restart thread getting semaphore unexpectedly */
    if (k_sem_init(&z_taskHandle->notification, 0, 1) != 0)
    {
        OSA_ASSERT(false, "Could not create notification semaphore!\r\n");
        return KOSA_StatusError;
    }

    z_taskHandle->stackPtr = (k_thread_stack_t *) thread_def->tstack;

    /* Create a task */
    z_taskHandle->handle =
        k_thread_create(&z_taskHandle->controlBlock, (k_thread_stack_t *)z_taskHandle->stackPtr,
                        thread_def->stacksize, s_OSA_TaskCallback, (void *)thread_def->pthread, (void *)task_param,
                        &(z_taskHandle->controlBlock), taskPriority, 0, K_NO_WAIT);
    if (z_taskHandle->handle == NULL)
    {
        OSA_ASSERT(false, "Task handle was not created!\r\n");
        OSA_InterruptEnable();
        return KOSA_StatusError;
    }

    if (thread_def->tname != NULL)
    {
        k_thread_name_set(z_taskHandle->handle, thread_def->tname);
    }

    if(s_OSA_IsInitialized == true)
    {
        sys_dlist_append(&s_OSA_TaskList, &(z_taskHandle->listNode));
    }

    z_taskHandle->checkmark = OSA_CHECKMARK_TASK;

    OSA_InterruptEnable();

    return KOSA_StatusSuccess;
}
#endif /* (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U)) */

#if ((defined(FSL_OSA_TASK_ENABLE)) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskDestroy(osa_task_handle_t taskHandle)
{
    osa_zephyr_taskHandle_t *z_taskHandle = (osa_zephyr_taskHandle_t *)taskHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_taskHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_taskHandle->checkmark, OSA_CHECKMARK_TASK, KOSA_StatusError)

    k_thread_abort(z_taskHandle->handle);

    z_taskHandle->checkmark = OSA_CHECKMARK_EMPTY;

    k_sem_reset((struct k_sem *)&z_taskHandle->notification);

    /* Functions for link manipulation are not thread safe. */
    OSA_InterruptDisable();
    sys_dlist_remove(taskHandle);
    OSA_InterruptEnable();

    return KOSA_StatusSuccess;
}
#endif /* FSL_OSA_TASK_ENABLE */

#if ((defined(FSL_OSA_TASK_ENABLE)) && (FSL_OSA_TASK_ENABLE > 0U))
void OSA_TaskYield(void)
{
    if (k_can_yield())
    {
        k_yield();
    }
}
#endif /* FSL_OSA_TASK_ENABLE */

#if ((defined(FSL_OSA_TASK_ENABLE)) && (FSL_OSA_TASK_ENABLE > 0U))
osa_task_handle_t OSA_TaskGetCurrentHandle(void)
{
    sys_dnode_t *list_element;
    osa_zephyr_taskHandle_t *z_taskHandle;
    k_tid_t currentThreadTid;

    OSA_RETURN_IF_IS_IN_ISR(NULL);

    if(s_OSA_IsInitialized != true)
    {
        OSA_ASSERT(false, "First initialize OSA by ccalling OSA_Init bbefore any task creation to be able to use this function correctly");
        return NULL;
    }

    if(sys_dlist_is_empty(&s_OSA_TaskList))
    {
        OSA_ASSERT(false, "Should never happen, unless function is called outside task.");
        return NULL;
    }

    currentThreadTid = k_current_get();
    list_element = &s_OSA_TaskList;

    /* Functions for link manipulation are not thread safe. */
    OSA_InterruptDisable();
    do
    {
        list_element = sys_dlist_peek_next(&s_OSA_TaskList, list_element);
        z_taskHandle = (osa_zephyr_taskHandle_t *)(void *)list_element;

        if(z_taskHandle->handle == currentThreadTid)
        {
            OSA_InterruptEnable();
            return (osa_task_handle_t) z_taskHandle;
        }
    } while (! sys_dlist_is_tail(&s_OSA_TaskList, list_element));

    OSA_InterruptEnable();

    return NULL;
}
#endif /* FSL_OSA_TASK_ENABLE */

#if ((defined(FSL_OSA_TASK_ENABLE)) && (FSL_OSA_TASK_ENABLE > 0U))
#include <limits.h>
/*!
 * Warning: Loss convertion. When priority is bigger or smaller than limits of int16,
 * priority is set as SHRT_MAX or SHRT_MIN. Result is returned as uint16 (osa_task_priority_t).
 */
osa_task_priority_t OSA_TaskGetPriority(osa_task_handle_t taskHandle)
{
    osa_zephyr_taskHandle_t *z_taskHandle = (osa_zephyr_taskHandle_t *)taskHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_taskHandle, OSA_ZEPHYR_TASK_GET_PRIORITY_ERROR)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_taskHandle->checkmark, OSA_CHECKMARK_TASK, OSA_ZEPHYR_TASK_GET_PRIORITY_ERROR)

    int zephyr_taskPriority = k_thread_priority_get(z_taskHandle->handle);

    OSA_ASSERT((zephyr_taskPriority < SHRT_MAX && zephyr_taskPriority > SHRT_MIN), "Priority conversion loss");

    osa_task_priority_t osa_taskPriority;

    if (zephyr_taskPriority > SHRT_MAX)
    {
        osa_taskPriority = SHRT_MAX;
    }
    else if (zephyr_taskPriority < SHRT_MIN)
    {
        osa_taskPriority = (uint16_t)SHRT_MIN;
    }
    else
    {
        osa_taskPriority = (uint16_t)zephyr_taskPriority;
    }

    return osa_taskPriority;
}
#endif /* FSL_OSA_TASK_ENABLE */

#if ((defined(FSL_OSA_TASK_ENABLE)) && (FSL_OSA_TASK_ENABLE > 0U))
/*!
 * Warning: uint16_t is converted into int16_t and int afterwards. Be aware, if result is
 * negative, thread will become cooperative thread. See Zephyr's docu related to cooperative threads.
 */
osa_status_t OSA_TaskSetPriority(osa_task_handle_t taskHandle, osa_task_priority_t taskPriority)
{
    osa_zephyr_taskHandle_t *z_taskHandle = (osa_zephyr_taskHandle_t *)taskHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_taskHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_taskHandle->checkmark, OSA_CHECKMARK_TASK, KOSA_StatusError)

    int taskPrio_zephyr = s_OSA_ConvertTaskPriorityFromOsaToZephyr(taskPriority);

    k_thread_priority_set(z_taskHandle->handle, taskPrio_zephyr);

    return KOSA_StatusSuccess;
}
#endif /* FSL_OSA_TASK_ENABLE */

/*******************************************************************************
 * Code - Mutex API
 ******************************************************************************/

osa_status_t OSA_MutexCreate(osa_mutex_handle_t mutexHandle)
{
    osa_zephyr_mutexHandle_t *z_mutexHandle = mutexHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_mutexHandle, KOSA_StatusError)

    if (k_mutex_init(&z_mutexHandle->handle) != 0)
    {
        return KOSA_StatusError;
    }

    z_mutexHandle->checkmark = OSA_CHECKMARK_MUTEX;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_MutexLock(osa_mutex_handle_t mutexHandle, uint32_t millisec)
{
    osa_zephyr_mutexHandle_t *z_mutexHandle = mutexHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_mutexHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_mutexHandle->checkmark, OSA_CHECKMARK_MUTEX, KOSA_StatusError)

    int retVal = k_mutex_lock(&z_mutexHandle->handle, s_OSA_ConvertTimeoutToZephyr(millisec));
    switch (retVal)
    {
        case -EBUSY:
            return KOSA_StatusTimeout;
        case -EAGAIN:
            return KOSA_StatusTimeout;
        case 0:
            return KOSA_StatusSuccess; /* Mutex locked */
        default:
            return KOSA_StatusError;
    }

    return KOSA_StatusError;
}

osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle)
{
    osa_zephyr_mutexHandle_t *z_mutexHandle = mutexHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_mutexHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_mutexHandle->checkmark, OSA_CHECKMARK_MUTEX, KOSA_StatusError)

    int retVal = k_mutex_unlock(&z_mutexHandle->handle);
    switch (retVal)
    {
        case 0:
            return KOSA_StatusSuccess;
        case -EPERM:
            return KOSA_StatusError;
        case -EINVAL:
            return KOSA_StatusError; /* Mutex is not locked */
        default:
            return KOSA_StatusError;
    }

    return KOSA_StatusError;
}

/**
 * WARNING: API does not ensure there is none task waiting in mutexe's queue when function for
 * destroying is called.
 */
osa_status_t OSA_MutexDestroy(osa_mutex_handle_t mutexHandle)
{
    /* Zephyr does not have any function for destroying the mutex */
    osa_zephyr_mutexHandle_t *z_mutexHandle = mutexHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_mutexHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_mutexHandle->checkmark, OSA_CHECKMARK_MUTEX, KOSA_StatusError)

    z_mutexHandle->checkmark = OSA_CHECKMARK_EMPTY;

    return KOSA_StatusSuccess;
}

/*******************************************************************************
 * Code - Event API
 ******************************************************************************/

#ifdef CONFIG_EVENTS

osa_status_t OSA_EventCreate(osa_event_handle_t eventHandle, uint8_t autoClear)
{
    osa_zephyr_eventHandle_t *z_eventHandle = (osa_zephyr_eventHandle_t *)eventHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_eventHandle, KOSA_StatusError)

    k_event_init(&z_eventHandle->handle);
    z_eventHandle->is_autoClear = (bool)autoClear;

    z_eventHandle->checkmark = OSA_CHECKMARK_EVENT;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventSet(osa_event_handle_t eventHandle, osa_event_flags_t flagsToSet)
{
    osa_zephyr_eventHandle_t *z_eventHandle = (osa_zephyr_eventHandle_t *)eventHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_eventHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_eventHandle->checkmark, OSA_CHECKMARK_EVENT, KOSA_StatusError)

    k_event_post(&z_eventHandle->handle, flagsToSet);

    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventWait(osa_event_handle_t eventHandle,
                           osa_event_flags_t flagsToWait,
                           uint8_t waitAll,
                           uint32_t millisec,
                           osa_event_flags_t *pSetFlags)
{
    osa_zephyr_eventHandle_t *z_eventHandle = (osa_zephyr_eventHandle_t *)eventHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_eventHandle, KOSA_StatusError)
    OSA_RETURN_IF_WAITING_IN_ISR(millisec, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_eventHandle->checkmark, OSA_CHECKMARK_EVENT, KOSA_StatusError)

    osa_event_flags_t setFlags = 0;
    bool isTimeouted           = false;

    if (waitAll)
    {
        setFlags =
            k_event_wait_all(&z_eventHandle->handle, flagsToWait, false, s_OSA_ConvertTimeoutToZephyr(millisec));
    }
    else
    {
        setFlags = k_event_wait(&z_eventHandle->handle, flagsToWait, false, s_OSA_ConvertTimeoutToZephyr(millisec));
    }

    isTimeouted = (setFlags == 0) ? true : false;

    if(isTimeouted)
    {
        return KOSA_StatusTimeout;
    }

    // Means it was not timeouted as well
    if (z_eventHandle->is_autoClear)
    {
        (void)k_event_clear(&z_eventHandle->handle, setFlags);
    }

    if (NULL != pSetFlags)
    {
        *pSetFlags = (osa_event_flags_t)setFlags;
    }

    return KOSA_StatusSuccess;
}

/**
 * WARNING: API does not ensure there is none task waiting for Event when
 * destroying is made.
 */
osa_status_t OSA_EventDestroy(osa_event_handle_t eventHandle)
{
    osa_zephyr_eventHandle_t *z_eventHandle = (osa_zephyr_eventHandle_t *)eventHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_eventHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_eventHandle->checkmark, OSA_CHECKMARK_EVENT, KOSA_StatusError)

    z_eventHandle->checkmark = OSA_CHECKMARK_EMPTY;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventPrecreate(osa_event_handle_t eventHandle, osa_task_ptr_t taskHandler)
{
    eventHandle = eventHandle;
    taskHandler = taskHandler;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventClear(osa_event_handle_t eventHandle, osa_event_flags_t flagsToClear)
{
    osa_zephyr_eventHandle_t *z_eventHandle = (osa_zephyr_eventHandle_t *)eventHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_eventHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_eventHandle->checkmark, OSA_CHECKMARK_EVENT, KOSA_StatusError)

    k_event_clear(&z_eventHandle->handle, flagsToClear);

    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventGet(osa_event_handle_t eventHandle, osa_event_flags_t flagsMask, osa_event_flags_t *pFlagsOfEvent)
{
    osa_zephyr_eventHandle_t *z_eventHandle = (osa_zephyr_eventHandle_t *)eventHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_eventHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_eventHandle->checkmark, OSA_CHECKMARK_EVENT, KOSA_StatusError)

    if (pFlagsOfEvent == NULL)
    {
        OSA_ASSERT(false, "OSA Events flag pointer is NULL\r\n");
        return KOSA_StatusError;
    }

    *pFlagsOfEvent = k_event_test(&z_eventHandle->handle, flagsMask);

    return KOSA_StatusSuccess;
}

#else // CONFIG_EVENTS not defined

osa_status_t OSA_EventCreate(osa_event_handle_t eventHandle, uint8_t autoClear)
{
    return KOSA_StatusError;
}

osa_status_t OSA_EventSet(osa_event_handle_t eventHandle, osa_event_flags_t flagsToSet)
{
    return KOSA_StatusError;
}

osa_status_t OSA_EventWait(osa_event_handle_t eventHandle,
                           osa_event_flags_t flagsToWait,
                           uint8_t waitAll,
                           uint32_t millisec,
                           osa_event_flags_t *pSetFlags)
{
    return KOSA_StatusError;
}

osa_status_t OSA_EventDestroy(osa_event_handle_t eventHandle)
{
    return KOSA_StatusError;
}

osa_status_t OSA_EventPrecreate(osa_event_handle_t eventHandle, osa_task_ptr_t taskHandler)
{
    return KOSA_StatusError;
}

osa_status_t OSA_EventClear(osa_event_handle_t eventHandle, osa_event_flags_t flagsToClear)
{
    return KOSA_StatusError;
}

osa_status_t OSA_EventGet(osa_event_handle_t eventHandle, osa_event_flags_t flagsMask, osa_event_flags_t *pFlagsOfEvent)
{
    return KOSA_StatusError;
}

#endif // CONFIG_EVENTS

/*******************************************************************************
 * Code - Message queue API
 ******************************************************************************/

osa_status_t OSA_MsgQCreate(osa_msgq_handle_t msgqHandle, uint32_t msgNo, uint32_t msgSize)
{
    osa_zephyr_msgQueueHandle_t *z_msgqHandle = (osa_zephyr_msgQueueHandle_t *)msgqHandle;
    uint32_t bufferSize_B                     = (msgNo * msgSize);
    uint8_t *buffer_addr                      = (uint8_t *)((uint8_t *)msgqHandle + OSA_MSGQ_HANDLE_SIZE);

    OSA_RETURN_IF_HANDLE_IS_NULL(z_msgqHandle, KOSA_StatusError)

    if (bufferSize_B == 0)
    {
        OSA_ASSERT(false, "Allocated buffer size must be bigger than 0.\r\n");
        return KOSA_StatusError;
    }

    k_msgq_init(&z_msgqHandle->handle, buffer_addr, msgSize, msgNo);
    z_msgqHandle->checkmark = OSA_CHECKMARK_MSGQ;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_MsgQPut(osa_msgq_handle_t msgqHandle, osa_msg_handle_t pMessage)
{
    osa_zephyr_msgQueueHandle_t *z_msgqHandle = (osa_zephyr_msgQueueHandle_t *)msgqHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_msgqHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_msgqHandle->checkmark, OSA_CHECKMARK_MSGQ, KOSA_StatusError)

    int retVal = k_msgq_put(&z_msgqHandle->handle, pMessage, K_NO_WAIT);

    switch (retVal)
    {
        case 0:
            return KOSA_StatusSuccess;
        case -ENOMSG:
            return KOSA_StatusError;
        case -EAGAIN:
            return KOSA_StatusTimeout;
        default:
            return KOSA_StatusError;
    }

    return KOSA_StatusError;
}

osa_status_t OSA_MsgQGet(osa_msgq_handle_t msgqHandle, osa_msg_handle_t pMessage, uint32_t millisec)
{
    osa_zephyr_msgQueueHandle_t *z_msgqHandle = (osa_zephyr_msgQueueHandle_t *)msgqHandle;

    OSA_RETURN_IF_WAITING_IN_ISR(millisec, KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_msgqHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_msgqHandle->checkmark, OSA_CHECKMARK_MSGQ, KOSA_StatusError)

    int retVal = k_msgq_get(&z_msgqHandle->handle, pMessage, s_OSA_ConvertTimeoutToZephyr(millisec));
    switch (retVal)
    {
        case 0:
            return KOSA_StatusSuccess;
        case -ENOMSG:
            return KOSA_StatusError;
        case -EAGAIN:
            return KOSA_StatusTimeout;
        default:
            return KOSA_StatusError;
    }

    return KOSA_StatusError;
}

osa_status_t OSA_MsgQDestroy(osa_msgq_handle_t msgqHandle)
{
    osa_zephyr_msgQueueHandle_t *z_msgqHandle = (osa_zephyr_msgQueueHandle_t *)msgqHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_msgqHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_msgqHandle->checkmark, OSA_CHECKMARK_MSGQ, KOSA_StatusError)

    k_msgq_purge(&z_msgqHandle->handle);

    z_msgqHandle->checkmark = OSA_CHECKMARK_EMPTY;

    return KOSA_StatusSuccess;
}

int OSA_MsgQAvailableMsgs(osa_msgq_handle_t msgqHandle)
{
    osa_zephyr_msgQueueHandle_t *z_msgqHandle = (osa_zephyr_msgQueueHandle_t *)msgqHandle;
    uint32_t message_number                   = 0;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_msgqHandle, 0)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_msgqHandle->checkmark, OSA_CHECKMARK_MSGQ, 0)

    message_number = k_msgq_num_used_get(&z_msgqHandle->handle);

    return message_number;
}

/*******************************************************************************
 * Code - Semaphore API
 ******************************************************************************/

osa_status_t OSA_SemaphoreCreate(osa_semaphore_handle_t semaphoreHandle, uint32_t initValue)
{
    osa_zephyr_semHandle_t *z_semHandle = (osa_zephyr_semHandle_t *)semaphoreHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_semHandle, KOSA_StatusError)

    if (k_sem_init(&(z_semHandle->handle), initValue, K_SEM_MAX_LIMIT) != 0)
    {
        return KOSA_StatusError;
    }

    z_semHandle->checkmark = OSA_CHECKMARK_SEM;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_SemaphoreCreateBinary(osa_semaphore_handle_t semaphoreHandle)
{
    osa_zephyr_semHandle_t *z_semHandle = (osa_zephyr_semHandle_t *)semaphoreHandle;

    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_semHandle, KOSA_StatusError)

    if (k_sem_init(&(z_semHandle->handle), 0, 1) != 0)
    {
        return KOSA_StatusError;
    }

    z_semHandle->checkmark = OSA_CHECKMARK_SEM;

    return KOSA_StatusSuccess;
}

/**
 * WARNING: API does not ensure there is none task waiting for semaphore when
 * destroying is made.
 */
osa_status_t OSA_SemaphoreDestroy(osa_semaphore_handle_t semaphoreHandle)
{
    osa_zephyr_semHandle_t *z_semHandle = (osa_zephyr_semHandle_t *)semaphoreHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_semHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_semHandle->checkmark, OSA_CHECKMARK_SEM, KOSA_StatusError)

    z_semHandle->checkmark = OSA_CHECKMARK_EMPTY;

    return KOSA_StatusSuccess;
}

osa_status_t OSA_SemaphoreWait(osa_semaphore_handle_t semaphoreHandle, uint32_t millisec)
{
    osa_zephyr_semHandle_t *z_semHandle = (osa_zephyr_semHandle_t *)semaphoreHandle;

    OSA_RETURN_IF_WAITING_IN_ISR(millisec, KOSA_StatusError)
    OSA_RETURN_IF_HANDLE_IS_NULL(z_semHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_semHandle->checkmark, OSA_CHECKMARK_SEM, KOSA_StatusError)

    int retVal = k_sem_take(&(z_semHandle->handle), s_OSA_ConvertTimeoutToZephyr(millisec));
    switch (retVal)
    {
        case -EBUSY:
            return KOSA_StatusTimeout;
        case -EAGAIN:
            return KOSA_StatusTimeout;
        case 0:
            return KOSA_StatusSuccess;
        default:
            return KOSA_StatusError;
    }

    return KOSA_StatusError;
}

osa_status_t OSA_SemaphorePost(osa_semaphore_handle_t semaphoreHandle)
{
    osa_zephyr_semHandle_t *z_semHandle = (osa_zephyr_semHandle_t *)semaphoreHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_semHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_semHandle->checkmark, OSA_CHECKMARK_SEM, KOSA_StatusError)

    k_sem_give(&(z_semHandle->handle));

    return KOSA_StatusSuccess;
}

osa_status_t OSA_SemaphorePrecreate(osa_semaphore_handle_t semaphoreHandle, osa_task_ptr_t taskHandler)
{
    semaphoreHandle = semaphoreHandle;
    taskHandler     = taskHandler;

    return KOSA_StatusSuccess;
}

osa_semaphore_count_t OSA_SemaphoreGetCount(osa_semaphore_handle_t semaphoreHandle)
{
    osa_zephyr_semHandle_t *z_semHandle = (osa_zephyr_semHandle_t *)semaphoreHandle;
    osa_semaphore_count_t semCount;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_semHandle, 0)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_semHandle->checkmark, OSA_CHECKMARK_SEM, 0)

    semCount = (osa_semaphore_count_t) k_sem_count_get((struct k_sem *)&z_semHandle->handle);

    return semCount;
}

/*******************************************************************************
 * Code - Notifications
 ******************************************************************************/

#if (defined(FSL_OSA_TASK_ENABLE) && (FSL_OSA_TASK_ENABLE > 0U))
osa_status_t OSA_TaskNotifyGet(osa_notify_time_ms_t waitTime_ms)
{
    OSA_RETURN_IF_IS_IN_ISR(KOSA_StatusError);

    osa_zephyr_taskHandle_t *z_taskHandle = OSA_TaskGetCurrentHandle();

    OSA_RETURN_IF_HANDLE_IS_NULL(z_taskHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_taskHandle->checkmark, OSA_CHECKMARK_TASK, KOSA_StatusError)

    int retVal = k_sem_take(&(z_taskHandle->notification), s_OSA_ConvertTimeoutToZephyr(waitTime_ms));
    switch (retVal)
    {
        case -EBUSY:
            return KOSA_StatusTimeout;
        case -EAGAIN:
            return KOSA_StatusTimeout;
        case 0:
            return KOSA_StatusSuccess;
        default:
            return KOSA_StatusError;
    }
}

osa_status_t OSA_TaskNotifyPost(osa_task_handle_t taskHandle)
{
    osa_zephyr_taskHandle_t *z_taskHandle = (osa_zephyr_taskHandle_t *)taskHandle;

    OSA_RETURN_IF_HANDLE_IS_NULL(z_taskHandle, KOSA_StatusError)
    OSA_RETURN_IF_WRONG_CHECKMARK(z_taskHandle->checkmark, OSA_CHECKMARK_TASK, KOSA_StatusError)

    k_sem_give(&z_taskHandle->notification);

    return KOSA_StatusSuccess;
}
#endif /* FSL_OSA_TASK_ENABLE */