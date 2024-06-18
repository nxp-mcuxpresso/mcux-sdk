/*! *********************************************************************************
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2019-2023 NXP
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
        return -KOSA_StatusError;
    }

    ret = k_sem_init(sem, initValue, 0xFF);
    if (ret != 0)
    {
        printk("OSA: Sem Init fail ret %d\r\n", ret);
        return -KOSA_StatusError;
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
        return -KOSA_StatusError;
    }

    ret = k_sem_init(sem, 0, 1);
    if (ret != 0)
    {
        printk("OSA: Sem Init fail ret %d\r\n", ret);
        return -KOSA_StatusError;
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

    if (semaphoreHandle == NULL)
    {
        return -KOSA_StatusError;
    }

    ret = k_sem_take(*semaphoreHandle, K_MSEC(millisec));
    return ret == 0 ? KOSA_StatusSuccess : -KOSA_StatusError;
}

osa_status_t OSA_SemaphorePost(osa_semaphore_handle_t semaphoreHandle)
{
    if (semaphoreHandle == NULL)
    {
        return -KOSA_StatusError;
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
        return -KOSA_StatusError;
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

    if (mutexHandle == NULL)
    {
        return -KOSA_StatusError;
    }

    ret = k_mutex_lock(*mutexHandle, K_MSEC(millisec));
    return ret == 0 ? KOSA_StatusSuccess : -KOSA_StatusError;
}

osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle)
{
    int ret;

    if (mutexHandle == NULL)
    {
        return -KOSA_StatusError;
    }

    ret = k_mutex_unlock(*mutexHandle);
    return ret == 0 ? KOSA_StatusSuccess : -KOSA_StatusError;
}
