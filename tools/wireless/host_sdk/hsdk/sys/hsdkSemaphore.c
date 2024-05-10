/*
 * \file hsdkSemaphore.c
 * This is a source file for the OS abstraction synchronization module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hsdkOSCommon.h"
#include "hsdkLogger.h"

#ifdef _WIN32

Semaphore HSDKCreateSemaphore(uint32_t initialValue, uint32_t maxValue)
{
    Semaphore s = CreateSemaphore(NULL, initialValue, maxValue, NULL);
    return s;
}

int HSDKAcquireExplicitlySemaphore(Semaphore s)
{
    DWORD ret = WaitForSingleObject(s, INFINITE);
    if (ret != WAIT_OBJECT_0) {
        DWORD err = GetLastError();
        switch (ret) {
            case WAIT_ABANDONED:
                logMessage(HSDK_ERROR, "[hsdkSemaphore]HSDKAcquireExplicitlySemaphore", "Wait abandoned", HSDKThreadId());
                break;
            case WAIT_TIMEOUT:
                logMessage(HSDK_ERROR, "[hsdkSemaphore]HSDKAcquireExplicitlySemaphore", "Timeout on wait", HSDKThreadId());
                break;
            case WAIT_FAILED:
                logMessage(HSDK_ERROR, "[hsdkSemaphore]HSDKAcquireExplicitlySemaphore", "WaitForSingleObject failed", HSDKThreadId());
                break;
        }
        return (int)err;
    }

    return ERROR_SUCCESS;
}

int HSDKReleaseSemaphore(Semaphore s)
{
    BOOL b = ReleaseSemaphore(s, 1, NULL);
    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkSemaphore]HSDKReleaseSemaphore", "Failed to release semaphore", HSDKThreadId());
        return (int)err;
    }
}

int HSDKDestroySemaphore(Semaphore s)
{
    BOOL b = CloseHandle(s);
    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkSemaphore]HSDKDestroySemaphore", "Failed to close semaphore", HSDKThreadId());
        return (int)err;
    }
}


#elif __linux__ || __APPLE__

#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>

/* NOTE: Using eventfd as a semaphore to use select on either events, files or semaphores. */

Semaphore HSDKCreateSemaphore(uint32_t initialValue, uint32_t maxValue)
{
    return HSDKCreateEvent(initialValue);
}

int HSDKAcquireExplicitlySemaphore(Semaphore s)
{
#ifdef _WIN32
    return HSDKWaitEvent(s, 0);
#else
    return 0;
#endif
}

int HSDKReleaseSemaphore(Semaphore s)
{
    return HSDKSignalEvent(s);
}

int HSDKDestroySemaphore(Semaphore s)
{
    return HSDKDestroyEvent(s);
}

#endif
