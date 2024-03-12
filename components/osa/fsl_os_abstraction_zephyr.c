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

#include "fsl_os_abstraction_zephyr.h"
#include <string.h>

void *OSA_MemoryAllocate(uint32_t length)
{
    void *p = k_malloc(length);

    if (p != NULL)
    {
        (void)memset(p, 0, length);
    }
    return p;
}

void OSA_MemoryFree(void *p)
{
    k_free(p);
}

osa_status_t OSA_SemaphoreCreate(osa_semaphore_handle_t semaphoreHandle, uint32_t initValue)
{
    int ret;
    struct k_sem *sem = NULL;

    sem = OSA_MemoryAllocate(sizeof(struct k_sem));
    if (sem == NULL)
    {
        printk("OSA: Sem Alloc failr\n");
        return KOSA_StatusError;
    }

    ret = k_sem_init(sem, initValue, 0xFF);
    if (ret != 0)
    {
        printk("OSA: Sem Init fail ret %d\r\n", ret);
        return KOSA_StatusError;
    }

    *semaphoreHandle = sem;
    return KOSA_StatusSuccess;
}

osa_status_t OSA_SemaphoreCreateBinary(osa_semaphore_handle_t semaphoreHandle)
{
    int ret;
    struct k_sem *sem = NULL;

    sem = OSA_MemoryAllocate(sizeof(struct k_sem));
    if (sem == NULL)
    {
        printk("OSA: Sem Alloc failr\n");
        return KOSA_StatusError;
    }

    ret = k_sem_init(sem, 0, 1);
    if (ret != 0)
    {
        printk("OSA: Sem Init fail ret %d\r\n", ret);
        return KOSA_StatusError;
    }

    *semaphoreHandle = sem;
    return KOSA_StatusSuccess;
}

osa_status_t OSA_SemaphoreDestroy(osa_semaphore_handle_t semaphoreHandle)
{
    if (semaphoreHandle == NULL || (*semaphoreHandle) == NULL)
    {
        return KOSA_StatusSuccess;
    }

    k_sem_reset(*semaphoreHandle);
    OSA_MemoryFree(*semaphoreHandle);
    *semaphoreHandle = NULL;
    return KOSA_StatusSuccess;
}

osa_status_t OSA_SemaphoreWait(osa_semaphore_handle_t semaphoreHandle, uint32_t millisec)
{
    int ret;

    if (semaphoreHandle == NULL || (*semaphoreHandle) == NULL)
    {
        return KOSA_StatusError;
    }

    ret = k_sem_take(*semaphoreHandle, K_MSEC(millisec));
    return ret == 0 ? KOSA_StatusSuccess : KOSA_StatusError;
}

osa_status_t OSA_SemaphorePost(osa_semaphore_handle_t semaphoreHandle)
{
    if (semaphoreHandle == NULL || (*semaphoreHandle) == NULL)
    {
        return KOSA_StatusError;
    }

    k_sem_give(*semaphoreHandle);
    return KOSA_StatusSuccess;
}

osa_status_t OSA_MutexCreate(osa_mutex_handle_t mutexHandle)
{
    struct k_mutex *mutex = NULL;
    int ret;

    mutex = OSA_MemoryAllocate(sizeof(struct k_mutex));
    if (mutex == NULL)
    {
        printk("OSA: Mutex Alloc fail\r\n");
        return KOSA_StatusError;
    }

    ret = k_mutex_init(mutex);
    if (ret != 0)
    {
        printk("OSA: Mutex Init fail ret %d\r\n", ret);
    }

    *mutexHandle = mutex;
    return KOSA_StatusSuccess;
}

osa_status_t OSA_MutexDestroy(osa_mutex_handle_t mutexHandle)
{
    if (mutexHandle == NULL || (*mutexHandle) == NULL)
    {
        return KOSA_StatusSuccess;
    }

    OSA_MutexLock(mutexHandle, osaWaitForever_c);
    OSA_MutexUnlock(mutexHandle);
    OSA_MemoryFree(*mutexHandle);
    *mutexHandle = NULL;
    return KOSA_StatusSuccess;
}

osa_status_t OSA_MutexLock(osa_mutex_handle_t mutexHandle, uint32_t millisec)
{
    int ret;

    if (mutexHandle == NULL || (*mutexHandle) == NULL)
    {
        return KOSA_StatusError;
    }

    ret = k_mutex_lock(*mutexHandle, K_MSEC(millisec));
    return ret == 0 ? KOSA_StatusSuccess : KOSA_StatusError;
}

osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle)
{
    int ret;

    if (mutexHandle == NULL || (*mutexHandle) == NULL)
    {
        return KOSA_StatusError;
    }

    ret = k_mutex_unlock(*mutexHandle);
    return ret == 0 ? KOSA_StatusSuccess : KOSA_StatusError;
}

osa_status_t OSA_EventCreate(osa_event_handle_t eventHandle, uint8_t autoClear)
{
    struct k_event *event = NULL;

    event = OSA_MemoryAllocate(sizeof(struct k_event));
    if (event == NULL){
        printk("OSA: Event Alloc fail\r\n");
        return KOSA_StatusError;
    }
    k_event_init(event);

    eventHandle->event = event;
    eventHandle->autoClear = autoClear;
    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventWait(osa_event_handle_t eventHandle,
                           osa_event_flags_t flagsToWait,
                           uint8_t waitAll,
                           uint32_t millisec,
                           osa_event_flags_t *pSetFlags)
{
    k_timeout_t timeout;
    uint32_t wakeflags;

    if (eventHandle == NULL || eventHandle->event == NULL) {
        return KOSA_StatusError;
    }

    /* Convert timeout from millisecond to tick. */
    if (millisec == osaWaitForever_c) {
        timeout = K_FOREVER;
    } else if (millisec == osaWaitNone_c) {
        timeout = K_NO_WAIT;
    } else {
        timeout = Z_TIMEOUT_MS(millisec);
    }

    if (waitAll == 0U) {
        wakeflags = k_event_wait(eventHandle->event, flagsToWait, false, timeout);
    } else {
        wakeflags = k_event_wait_all(eventHandle->event, flagsToWait, false, timeout);
    }
    if (!wakeflags) {
        return KOSA_StatusTimeout;
    }

    if (pSetFlags != NULL) {
        *pSetFlags = (osa_event_flags_t)wakeflags;
    }
    if (eventHandle->autoClear) {
        k_event_clear(eventHandle->event, flagsToWait);
    }
    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventSet(osa_event_handle_t eventHandle, osa_event_flags_t flagsToSet)
{
    if (eventHandle == NULL || eventHandle->event == NULL) {
        return KOSA_StatusError;
    }
    k_event_post(eventHandle->event, flagsToSet);

    return KOSA_StatusSuccess;
}

osa_status_t OSA_EventClear(osa_event_handle_t eventHandle, osa_event_flags_t flagsToClear)
{
    if (eventHandle == NULL || eventHandle->event == NULL) {
        return KOSA_StatusError;
    }

    k_event_clear(eventHandle->event, flagsToClear);

    return KOSA_StatusSuccess;
}
osa_status_t OSA_EventDestroy(osa_event_handle_t eventHandle)
{
    if (eventHandle == NULL || eventHandle->event == NULL) {
        return KOSA_StatusSuccess;
    }

    OSA_MemoryFree(eventHandle->event);
    eventHandle->event = NULL;
    return KOSA_StatusSuccess;
}
