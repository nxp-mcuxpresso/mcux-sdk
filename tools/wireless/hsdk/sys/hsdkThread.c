/*
 * \file hsdkThread.c
 * This is a source file for the OS abstraction threading module.
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

Thread HSDKCreateThread(void *(*startRoutine) (void *), void *arg)
{
    Thread t = CreateThread(NULL,
                            0,
                            (LPTHREAD_START_ROUTINE)startRoutine,
                            arg,
                            0,
                            NULL);

    if (t == NULL) {
        logMessage(HSDK_ERROR, "[hsdkThread]HSDKCreateThread", "Thread creation failed", HSDKThreadId());
    }

    return t;
}

int HSDKDestroyThread(Thread t)
{
    DWORD ret = WaitForSingleObject(t, INFINITE);
    if (ret != WAIT_OBJECT_0) {
        DWORD err = GetLastError();
        switch (ret) {
            case WAIT_ABANDONED:
                logMessage(HSDK_ERROR, "[hsdkThread]HSDKDestroyThread", "Wait abandoned", HSDKThreadId());
                break;
            case WAIT_TIMEOUT:
                logMessage(HSDK_ERROR, "[hsdkThread]HSDKDestroyThread", "Timeout on wait", HSDKThreadId());
                break;
            case WAIT_FAILED:
                logMessage(HSDK_ERROR, "[hsdkThread]HSDKDestroyThread", "WaitForSingleObject failed", HSDKThreadId());
                break;
        }
        return (int)err;
    }

    BOOL b = CloseHandle(t);
    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkThread]HSDKDestroyThread", "Failed to close thread", HSDKThreadId());
        return (int)err;
    }
}

int HSDKThreadId()
{
    return GetCurrentThreadId();
}

#elif __linux__ || __APPLE__

Thread HSDKCreateThread(void *(*startRoutine) (void *), void *arg)
{
    int ret;
    Thread thread;

    ret = pthread_create(&thread, NULL, startRoutine, arg);

    if (!ret) {
        return thread;
    } else {
        return 0;
    }
}

int HSDKDestroyThread(Thread thread)
{
    return pthread_join(thread, NULL);
}

int HSDKThreadId()
{
    return (int)pthread_self();
}
#endif
