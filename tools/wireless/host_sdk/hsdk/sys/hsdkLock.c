/*
 * \file hsdkLock.c
 * This is a source file for the OS abstraction synchronization module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hsdkOSCommon.h"

#ifdef _WIN32

Lock HSDKCreateLock()
{
    Lock lock = (Lock)malloc(sizeof(CRITICAL_SECTION));
    InitializeCriticalSection(lock);
    return lock;
}

int HSDKAcquireLock(Lock l)
{
    EnterCriticalSection(l);
    return ERROR_SUCCESS;
}

int HSDKReleaseLock(Lock l)
{
    LeaveCriticalSection(l);
    return ERROR_SUCCESS;
}

int HSDKDestroyLock(Lock l)
{
    DeleteCriticalSection(l);
    return ERROR_SUCCESS;
}

#elif __linux__ || __APPLE__

Lock HSDKCreateLock()
{
    Lock lock = (Lock)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock, NULL);
    return lock;
}

int HSDKAcquireLock(Lock l)
{
    return pthread_mutex_lock(l);
}

int HSDKReleaseLock(Lock l)
{
    return pthread_mutex_unlock(l);
}

int HSDKDestroyLock(Lock l)
{
    return pthread_mutex_destroy(l);
}

ConditionVariable HSDKCreateCondition()
{
    ConditionVariable cond;
    pthread_cond_init(&cond, NULL);
    return cond;
}

int HSDKSignalCondition(ConditionVariable cond)
{
    return pthread_cond_signal(&cond);
}

int HSDKSignalConditionBroadcast(ConditionVariable cond)
{
    return pthread_cond_signal(&cond);
}

int HSDKDestroyCondition(ConditionVariable cond)
{
    return pthread_cond_destroy(&cond);
}

#endif
