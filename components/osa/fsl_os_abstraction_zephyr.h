/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_OS_ABSTRACTION_ZEPHYR_H_
#define _FSL_OS_ABSTRACTION_ZEPHYR_H_

#include <zephyr/irq.h>
#include <zephyr/kernel.h>

#ifndef PRINTF
#define PRINTF printk
#endif

/* enter critical macros */
#define OSA_SR_ALLOC()       int osa_current_sr
#define OSA_ENTER_CRITICAL() osa_current_sr = irq_lock()
#define OSA_EXIT_CRITICAL()  irq_unlock(osa_current_sr)

#define OSA_TimeDelay(ms) k_msleep(ms)

#define USE_RTOS 1

#define OSA_SEM_HANDLE_SIZE   (4U)
#define OSA_MUTEX_HANDLE_SIZE (4U)
#define OSA_MSGQ_HANDLE_SIZE  (4U)
#define OSA_EVENT_HANDLE_SIZE (8U)

enum _osa_status
{
    KOSA_StatusSuccess = 0, /*!< Success */
    KOSA_StatusError   = 1, /*!< Failed */
    KOSA_StatusTimeout = 2, /*!< Timeout occurs while waiting */
    /*!< Used for bare metal only, the wait object is not ready and timeout still not occur */
    KOSA_StatusIdle = 3,
};
#define osa_status_t enum _osa_status

struct event_handle {
    struct k_event *event;
    uint8_t autoClear;
};

/*! @brief Type for the semaphore handler */
#define osa_semaphore_handle_t struct k_sem **
/*! @brief Type for the mutex handler */
#define osa_mutex_handle_t struct k_mutex **
/*! @brief Type for the mutex handler */
#define osa_event_handle_t struct event_handle *
/*! @brief Type for an event flags group, bit 32 is reserved. */
#define osa_event_flags_t uint32_t
/*! @brief Type for the task param */
#define osa_task_param_t void *

#define SIZE_IN_UINT32_UNITS(size) (((size) + sizeof(uint32_t) - 1) / sizeof(uint32_t))

/*! @brief Constant to pass as timeout value in order to wait indefinitely. */
#define osaWaitNone_c            ((uint32_t)(0))
#define osaWaitForever_c         ((uint32_t)(-1))
#define osaEventFlagsAll_c       ((osa_event_flags_t)(0x00FFFFFF))
#define osThreadStackArray(name) osThread_##name##_stack
#define osThreadStackDef(name, stacksize, instances) \
    const uint32_t osThreadStackArray(name)[SIZE_IN_UINT32_UNITS(stacksize) * (instances)];

/* ==== Buffer Definition ==== */

/*! 191 + * @brief Defines the semaphore handle
 *
 * This macro is used to define a 4 byte aligned semaphore handle.
 * Then use "(osa_semaphore_handle_t)name" to get the semaphore handle.
 *
 * The macro should be global and could be optional. You could also define semaphore handle by
 * yourself.
 *
 * This is an example,
 * @code
 *   OSA_SEMAPHORE_HANDLE_DEFINE(semaphoreHandle); 201 + * @endcode
 *
 * @param name The name string of the semaphore handle.
 */
#define OSA_SEMAPHORE_HANDLE_DEFINE(name) \
    uint32_t name[(OSA_SEM_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

/*!
 * @brief Defines the mutex handle
 *
 * This macro is used to define a 4 byte aligned mutex handle.
 * Then use "(osa_mutex_handle_t)name" to get the mutex handle.
 *
 * The macro should be global and could be optional. You could also define mutex handle by yourself.
 *
 * This is an example,
 * @code
 *   OSA_MUTEX_HANDLE_DEFINE(mutexHandle);
 * @endcode
 *
 * @param name The name string of the mutex handle.
 */
#define OSA_MUTEX_HANDLE_DEFINE(name) uint32_t name[(OSA_MUTEX_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

#define OSA_EVENT_HANDLE_DEFINE(name) \
    uint32_t name[((OSA_EVENT_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]
/*!
 * @brief Defines the message queue handle
 *
 * This macro is used to define a 4 byte aligned message queue handle.
 * Then use "(osa_msgq_handle_t)name" to get the message queue handle.
 *
 * The macro should be global and could be optional. You could also define message queue handle by
 * yourself.
 *
 * This is an example,
 * @code
 *   OSA_MSGQ_HANDLE_DEFINE(msgqHandle, 3, sizeof(msgStruct));
 * @endcode
 *
 * @param name The name string of the message queue handle.
 * @param numberOfMsgs Number of messages.
 * @param msgSize Message size.
 *
 */
#define OSA_MSGQ_HANDLE_DEFINE(name, numberOfMsgs, msgSize) \
    uint32_t name[(OSA_MSGQ_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

/* ==== APIs ==== */
/*!
 * @brief Reserves the requested amount of memory in bytes.
 *
 * The function is used to reserve the requested amount of memory in bytes and initializes it to 0.
 *
 * @param length Amount of bytes to reserve.
 *
 * @return Pointer to the reserved memory. NULL if memory can't be allocated.
 */
void *OSA_MemoryAllocate(uint32_t length);

/*!
 * @brief Frees the memory previously reserved.
 *
 * The function is used to free the memory block previously reserved.
 *
 * @param p Pointer to the start of the memory block previously reserved.
 *
 */
void OSA_MemoryFree(void *p);

/*!
 * @brief Creates a semaphore with a given value.
 *
 * This function creates a semaphore and sets the value to the parameter
 * initValue.
 *
 * Example below shows how to use this API to create the semaphore handle.
 * @code
 *   OSA_SEMAPHORE_HANDLE_DEFINE(semaphoreHandle);
 *   OSA_SemaphoreCreate((osa_semaphore_handle_t)semaphoreHandle, 0xff);
 * @endcode
 *
 * @param semaphoreHandle Pointer to a memory space of size OSA_SEM_HANDLE_SIZE allocated by the
 * caller. The handle should be 4 byte aligned, because unaligned access doesn't be supported on
 * some devices. You can define the handle in the following two ways:
 * #OSA_SEMAPHORE_HANDLE_DEFINE(semaphoreHandle);
 * or
 * uint32_t semaphoreHandle[((OSA_SEM_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param initValue Initial value the semaphore will be set to.
 *
 * @retval KOSA_StatusSuccess  the new semaphore if the semaphore is created successfully.
 * @retval KOSA_StatusError   if the semaphore can not be created.
 */
osa_status_t OSA_SemaphoreCreate(osa_semaphore_handle_t semaphoreHandle, uint32_t initValue);

/*!
 * @brief Creates a binary semaphore.
 *
 * This function creates a binary semaphore
 *
 * Example below shows how to use this API to create the semaphore handle.
 * @code
 *   OSA_SEMAPHORE_HANDLE_DEFINE(semaphoreHandle);
 *   OSA_SemaphoreCreateBinary((osa_semaphore_handle_t)semaphoreHandle);
 * @endcode
 *
 * @param semaphoreHandle Pointer to a memory space of size OSA_SEM_HANDLE_SIZE allocated by the
 * caller. The handle should be 4 byte aligned, because unaligned access doesn't be supported on
 * some devices. You can define the handle in the following two ways:
 * #OSA_SEMAPHORE_HANDLE_DEFINE(semaphoreHandle);
 * or
 * uint32_t semaphoreHandle[((OSA_SEM_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 *
 * @retval KOSA_StatusSuccess  the new binary semaphore if the binary semaphore is created
 * successfully.
 * @retval KOSA_StatusError   if the binary semaphore can not be created.
 */
osa_status_t OSA_SemaphoreCreateBinary(osa_semaphore_handle_t semaphoreHandle);

/*!
 * @brief Destroys a previously created semaphore.
 *
 * @param semaphoreHandle The semaphore handle.
 * The macro SEMAPHORE_HANDLE_BUFFER_GET is used to get the semaphore buffer pointer,
 * and should not be used before the macro SEMAPHORE_HANDLE_BUFFER_DEFINE is used.
 *
 * @retval KOSA_StatusSuccess The semaphore is successfully destroyed.
 * @retval KOSA_StatusError   The semaphore can not be destroyed.
 */
osa_status_t OSA_SemaphoreDestroy(osa_semaphore_handle_t semaphoreHandle);

/*!
 * @brief Pending a semaphore with timeout.
 *
 * This function checks the semaphore's counting value. If it is positive,
 * decreases it and returns KOSA_StatusSuccess. Otherwise, a timeout is used
 * to wait.
 *
 * @param semaphoreHandle    The semaphore handle.
 * @param millisec The maximum number of milliseconds to wait if semaphore is not
 *                 positive. Pass osaWaitForever_c to wait indefinitely, pass 0
 *                 will return KOSA_StatusTimeout immediately.
 *
 * @retval KOSA_StatusSuccess  The semaphore is received.
 * @retval KOSA_StatusTimeout  The semaphore is not received within the specified 'timeout'.
 * @retval KOSA_StatusError    An incorrect parameter was passed.
 */
osa_status_t OSA_SemaphoreWait(osa_semaphore_handle_t semaphoreHandle, uint32_t millisec);

/*!
 * @brief Signals for someone waiting on the semaphore to wake up.
 *
 * Wakes up one task that is waiting on the semaphore. If no task is waiting, increases
 * the semaphore's counting value.
 *
 * @param semaphoreHandle The semaphore handle to signal.
 *
 * @retval KOSA_StatusSuccess The semaphore is successfully signaled.
 * @retval KOSA_StatusError   The object can not be signaled or invalid parameter.
 *
 */
osa_status_t OSA_SemaphorePost(osa_semaphore_handle_t semaphoreHandle);

/*!
 * @brief Create an unlocked mutex.
 *
 * This function creates a non-recursive mutex and sets it to unlocked status.
 *
 * Example below shows how to use this API to create the mutex handle.
 * @code
 *   OSA_MUTEX_HANDLE_DEFINE(mutexHandle);
 *   OSA_MutexCreate((osa_mutex_handle_t)mutexHandle);
 * @endcode
 *
 * @param mutexHandle       Pointer to a memory space of size OSA_MUTEX_HANDLE_SIZE allocated by the
 * caller. The handle should be 4 byte aligned, because unaligned access doesn't be supported on
 * some devices. You can define the handle in the following two ways:
 * #OSA_MUTEX_HANDLE_DEFINE(mutexHandle);
 * or
 * uint32_t mutexHandle[((OSA_MUTEX_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @retval KOSA_StatusSuccess  the new mutex if the mutex is created successfully.
 * @retval KOSA_StatusError   if the mutex can not be created.
 */
osa_status_t OSA_MutexCreate(osa_mutex_handle_t mutexHandle);

/*!
 * @brief Waits for a mutex and locks it.
 *
 * This function checks the mutex's status. If it is unlocked, locks it and returns the
 * KOSA_StatusSuccess. Otherwise, waits for a timeout in milliseconds to lock.
 *
 * @param mutexHandle The mutex handle.
 * @param millisec The maximum number of milliseconds to wait for the mutex.
 *                 If the mutex is locked, Pass the value osaWaitForever_c will
 *                 wait indefinitely, pass 0 will return KOSA_StatusTimeout
 *                 immediately.
 *
 * @retval KOSA_StatusSuccess The mutex is locked successfully.
 * @retval KOSA_StatusTimeout Timeout occurred.
 * @retval KOSA_StatusError   Incorrect parameter was passed.
 *
 * @note This is non-recursive mutex, a task can not try to lock the mutex it has locked.
 */
osa_status_t OSA_MutexLock(osa_mutex_handle_t mutexHandle, uint32_t millisec);

/*!
 * @brief Unlocks a previously locked mutex.
 *
 * @param mutexHandle The mutex handle.
 *
 * @retval KOSA_StatusSuccess The mutex is successfully unlocked.
 * @retval KOSA_StatusError   The mutex can not be unlocked or invalid parameter.
 */
osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle);

/*!
 * @brief Destroys a previously created mutex.
 *
 * @param mutexHandle The mutex handle.
 *
 * @retval KOSA_StatusSuccess The mutex is successfully destroyed.
 * @retval KOSA_StatusError   The mutex can not be destroyed.
 *
 */
osa_status_t OSA_MutexDestroy(osa_mutex_handle_t mutexHandle);

/*!
 * @brief Initializes an event object with all flags cleared.
 *
 * This function creates an event object and set its clear mode. If autoClear
 * is 1, when a task gets the event flags, these flags will be
 * cleared automatically. Otherwise these flags must
 * be cleared manually.
 *
 * Example below shows how to use this API to create the event handle.
 * @code
 *   OSA_EVENT_HANDLE_DEFINE(eventHandle);
 *   OSA_EventCreate((osa_event_handle_t)eventHandle, 0);
 * @endcode
 *
 * @param eventHandle Pointer to a memory space of size OSA_EVENT_HANDLE_SIZE allocated by the
 * caller. The handle should be 4 byte aligned, because unaligned access doesn't be supported on
 * some devices. You can define the handle in the following two ways:
 * #OSA_EVENT_HANDLE_DEFINE(eventHandle);
 * or
 * uint32_t eventHandle[((OSA_EVENT_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param autoClear 1 The event is auto-clear.
 *                  0 The event manual-clear
 * @retval KOSA_StatusSuccess  the new event if the event is created successfully.
 * @retval KOSA_StatusError   if the event can not be created.
 */
osa_status_t OSA_EventCreate(osa_event_handle_t eventHandle, uint8_t autoClear);

/*!
 * @brief Waits for specified event flags to be set.
 *
 * This function waits for a combination of flags to be set in an event object.
 * Applications can wait for any/all bits to be set. Also this function could
 * obtain the flags who wakeup the waiting task.
 *
 * @param eventHandle     The event handle.
 * @param flagsToWait Flags that to wait.
 * @param waitAll     Wait all flags or any flag to be set.
 * @param millisec    The maximum number of milliseconds to wait for the event.
 *                    If the wait condition is not met, pass osaWaitForever_c will
 *                    wait indefinitely, pass 0 will return KOSA_StatusTimeout
 *                    immediately.
 * @param pSetFlags    Flags that wakeup the waiting task are obtained by this parameter.
 *
 * @retval KOSA_StatusSuccess The wait condition met and function returns successfully.
 * @retval KOSA_StatusTimeout Has not met wait condition within timeout.
 * @retval KOSA_StatusError   An incorrect parameter was passed.

 *
 * @note    Please pay attention to the flags bit width, FreeRTOS uses the most
 *          significant 8 bis as control bits, so do not wait these bits while using
 *          FreeRTOS.
 *
 */
osa_status_t OSA_EventWait(osa_event_handle_t eventHandle,
                           osa_event_flags_t flagsToWait,
                           uint8_t waitAll,
                           uint32_t millisec,
                           osa_event_flags_t *pSetFlags);

/*!
 * @brief Sets one or more event flags.
 *
 * Sets specified flags of an event object.
 *
 * @param eventHandle     The event handle.
 * @param flagsToSet  Flags to be set.
 *
 * @retval KOSA_StatusSuccess The flags were successfully set.
 * @retval KOSA_StatusError   An incorrect parameter was passed.
 */
osa_status_t OSA_EventSet(osa_event_handle_t eventHandle, osa_event_flags_t flagsToSet);

/*!
 * @brief Clears one or more flags.
 *
 * Clears specified flags of an event object.
 *
 * @param eventHandle       The event handle.
 * @param flagsToClear  Flags to be clear.
 *
 * @retval KOSA_StatusSuccess The flags were successfully cleared.
 * @retval KOSA_StatusError   An incorrect parameter was passed.
 */
osa_status_t OSA_EventClear(osa_event_handle_t eventHandle, osa_event_flags_t flagsToClear);

/*!
 * @brief Destroys a previously created event object.
 *
 * @param eventHandle The event handle.
 *
 * @retval KOSA_StatusSuccess The event is successfully destroyed.
 * @retval KOSA_StatusError   Event destruction failed.
 */
osa_status_t OSA_EventDestroy(osa_event_handle_t eventHandle);

#endif /* _FSL_OS_ABSTRACTION_ZEPHYR_H_ */
