/*
 * \file hsdkEvent.c
 * This is a source file for the OS abstraction eventing module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hsdkOSCommon.h"
#include "hsdkLogger.h"

#ifdef _WIN32

typedef struct {
    OVERLAPPED ov;
    DWORD eventMask;
} CommEventHelper;

Event HSDKCreateEvent(int initialValue)
{
    uint8_t signaled = (initialValue == 0) ? 0 : 1;
    Event evt = CreateEvent(NULL, TRUE, signaled, NULL);

    if (evt == INVALID_HANDLE_VALUE) {
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKCreateEvent", "Failed to create event", HSDKThreadId());
        return INVALID_EVENT_HANDLE;
    }

    return evt;
}

Event HSDKDeviceTriggerableEvent(File e, void **asyncMask)
{
    CommEventHelper *evtHelper = (CommEventHelper *) calloc(1, sizeof(CommEventHelper));

    if (evtHelper == NULL) {
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKDeviceTriggerableEvent", "Failed to allocate memory for helper", HSDKThreadId());
        return INVALID_EVENT_HANDLE;
    }

    *asyncMask = evtHelper;
    DWORD dwRet;

    ZeroMemory(&evtHelper->ov, sizeof(OVERLAPPED));
    evtHelper->ov.hEvent = HSDKCreateEvent(0);

    dwRet = WaitCommEvent(e, &evtHelper->eventMask, &evtHelper->ov);
    DWORD err = GetLastError();

    if (dwRet == FALSE && err != ERROR_IO_PENDING) {
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKDeviceTriggerableEvent", "Failed to initialize event for specific signals", HSDKThreadId());
        return INVALID_EVENT_HANDLE;
    }

    return evtHelper->ov.hEvent;
}

int HSDKFinishTriggerableEvent(void *asyncMask)
{
    CommEventHelper *evtHelper = (CommEventHelper *) asyncMask;
    BOOL b = CloseHandle(evtHelper->ov.hEvent);

    if (!b) {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKFinishTriggerableEvent", "Failed to close event", HSDKThreadId());
        return (int)err;
    }

    free(evtHelper);

    return ERROR_SUCCESS;
}

int HSDKResetEvent(Event e)
{
    BOOL b = ResetEvent(e);

    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKResetEvent", "Failed to reset event", HSDKThreadId());
        return (int)err;
    }
}

int HSDKDestroyEvent(Event e)
{
    BOOL b = CloseHandle(e);

    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKDestroyEvent", "Failed to close event", HSDKThreadId());
        return (int)err;
    }
}

int HSDKSignalEvent(Event e)
{
    BOOL b = SetEvent(e);

    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKSignalEvent", "Failed to set event", HSDKThreadId());
        return (int)err;
    }
}

int HSDKWaitEvent(Event e, int64_t millisecondsToWait)
{
    DWORD time;

    if (millisecondsToWait == INFINITE_WAIT) {
        time = INFINITE;
    } else {
        time = (DWORD) millisecondsToWait;
    }

    DWORD ret = WaitForSingleObject(e, time);

    if (ret != WAIT_OBJECT_0) {
        switch (ret) {
            case WAIT_ABANDONED:
                logMessage(HSDK_ERROR, "[hsdkEvent]HSDKWaitEvent", "Wait abandoned", HSDKThreadId());
                break;

            case WAIT_TIMEOUT:
                logMessage(HSDK_ERROR, "[hsdkEvent]HSDKWaitEvent", "Timeout on wait", HSDKThreadId());
                break;

            case WAIT_FAILED:
                logMessage(HSDK_ERROR, "[hsdkEvent]HSDKWaitEvent", "WaitForSingleObject failed", HSDKThreadId());
                break;
        }

        return (int)ret;
    }

    BOOL b = ResetEvent(e);

    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKWaitEvent", "Failed to initialize port to the desired config", HSDKThreadId());
        return (int)err;
    }
}

int HSDKWaitMultipleEvents(Event *events, uint32_t noEvents, int64_t millisecondsToWait, int *triggeredEvent)
{
    DWORD ret;
    DWORD time;

    *triggeredEvent = -1;

    if (millisecondsToWait == INFINITE_WAIT) {
        time = INFINITE;
    } else {
        time = (DWORD) millisecondsToWait;
    }

    ret = WaitForMultipleObjectsEx(noEvents, events, FALSE, time, TRUE);
    DWORD evtNumber = ret - WAIT_OBJECT_0;

    if (evtNumber >= noEvents) {
        DWORD err = GetLastError();

        logMessage(HSDK_ERROR, "[hsdkEvent]HSDKWaitMultipleEvents", "Wait abandoned", HSDKThreadId());
        return (int)err;
    }

    *triggeredEvent = (int)evtNumber;
    return ERROR_SUCCESS;
}


#elif __linux__

#include "hsdkError.h"

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/eventfd.h>
#include <sys/select.h>
#include <sys/types.h>


Event HSDKCreateEvent(int initialValue)
{
    Event evt = (Event) calloc(1, sizeof(EvtWrapper));

    evt->pureEvent = 1;
    evt->gpioPollEvent = 0;
    evt->event = eventfd(initialValue, EFD_SEMAPHORE);

    return evt;
}

Event HSDKDeviceTriggerableEvent(File e, void **asyncMask)
{
    Event evt = (Event) calloc(1, sizeof(EvtWrapper));

    evt->pureEvent = 0;
    evt->gpioPollEvent = 0;
    evt->event = e;

    *asyncMask = evt;

    return evt;
}

int HSDKFinishTriggerableEvent(void *asyncMask)
{
    Event evt = (Event) asyncMask;
    free(evt);
    /* Maybe it should be invalid for a non pure event. */
    return 0;
}

int HSDKResetEvent(Event e)
{
    if (e->pureEvent) {
        uint64_t inc;
        int rc = read(e->event, &inc, sizeof(uint64_t));

        if (rc == -1) {
            perror("HSDKResetEvent read");
            return errno;
        }
    }

    /* Maybe it should be invalid for a non pure event. */
    return 0;
}

int HSDKDestroyEvent(Event e)
{
    if (e->pureEvent) {
        close(e->event);
    }

    free(e);
    /* Maybe it should be invalid for a non pure event. */
    return 0;
}

int HSDKSignalEvent(Event e)
{
    if (e->pureEvent) {
        uint64_t inc = 1;
        int rc = write(e->event, &inc, sizeof(uint64_t));

        if (rc == -1) {
            perror("HSDKSignalEvent write");
            return errno;
        }
    }

    /* Maybe it should be invalid for a non pure event. */
    return 0;
}

int HSDKWaitEvent(Event e, int64_t millisecondsToWait)
{
    if (e->pureEvent) {
        uint64_t inc;

        struct pollfd pfds[1];
        int nfds = 1;
        pfds[0].fd = e->event;
        pfds[0].events = POLLIN;

        int rc = poll(pfds, nfds, (int)millisecondsToWait);

        /* Poll error */
        if (rc == -1) {
            perror("[HSDKWaitEvent] poll");
            logMessage(HSDK_ERROR, "[HSDKWaitEvent] poll", strerror(errno), HSDKThreadId());
            return -1;
        }
        /* Poll timeout */
        else if (rc == 0) {
            logMessage(HSDK_INFO, "[HSDKWaitEvent] poll", "timeout", HSDKThreadId());
            return 0;
        }

        if (pfds[0].revents & POLLIN) {
            rc = read(e->event, &inc, sizeof(uint64_t));

            if (rc == -1) {
                perror("[HSDKWaitEvent] read");
                logMessage(HSDK_ERROR, "[HSDKWaitEvent] read", strerror(errno), HSDKThreadId());
                return -1;
            }
        }

        return 1;
    }

    /* Maybe it should be invalid for a non pure event. */
    return HSDK_ERROR_INVALID;
}



int HSDKWaitMultipleEvents(Event *events, uint32_t noEvents, int64_t millisecondsToWait, int *triggeredEvent)
{
    int rc = 0;
    uint32_t i;

    /* Set up descriptors to poll on. */
    struct pollfd pfds[noEvents];

    for (i = 0; i < noEvents; i++) {
        if (events[i] != NULL) {
            pfds[i].fd = events[i]->event;
        } else {
            pfds[i].fd = -1;
        }

        if (events[i] != NULL && events[i]->gpioPollEvent) {
            pfds[i].events = POLLPRI;
        } else {
            pfds[i].events = POLLIN;
        }
    }

    rc = poll(pfds, noEvents, (int)millisecondsToWait);

    /* Poll error */
    if (rc == -1) {
        perror("[HSDKWaitMultipleEvents] poll");
        logMessage(HSDK_ERROR, "[HSDKWaitMultipleEvents] poll", strerror(errno), HSDKThreadId());
        return -1;
    }
    /* Poll timeout */
    else if (rc == 0) {
        logMessage(HSDK_INFO, "[HSDKWaitMultipleEvents] poll", "timeout", HSDKThreadId());
        return -1;
    }

    for (i = 0; i < noEvents; i++) {

        if (events[i] != NULL) {

            if ((events[i]->gpioPollEvent == 1) && (pfds[i].revents & POLLPRI)) {
                *triggeredEvent = i;

                if (lseek(pfds[i].fd, 0, SEEK_SET) == -1) {
                    perror("lseek");
                }

                break;
            }

            else if ((pfds[i].revents & POLLIN) && (events[i]->gpioPollEvent != 1)) {
                *triggeredEvent = i;
                break;
            }
        }
    }

    return HSDK_ERROR_SUCCESS;
}


#elif __APPLE__

#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>


Event HSDKCreateEvent(int initialValue)
{
    Event evt = (Event) calloc(1, sizeof(EvtWrapper));
    int fildes[2], rc;

    rc = pipe(fildes);

    if (rc == -1) {
        perror("HSDKCreateEvent pipe");
    }

    evt->pureEvent = 1;
    evt->read_end = fildes[0];
    evt->write_end = fildes[1];

    return evt;
}

Event HSDKDeviceTriggerableEvent(File e, void **asyncMask)
{
    Event evt = (Event) calloc(1, sizeof(EvtWrapper));

    evt->pureEvent = 0;
    evt->read_end = e;

    *asyncMask = evt;

    return evt;
}

int HSDKFinishTriggerableEvent(void *asyncMask)
{
    Event evt = (Event) asyncMask;
    free(evt);
    //Maybe it should be invalid for a non pure event
    return 0;
}

int HSDKResetEvent(Event e)
{
    if (e->pureEvent) {
        uint64_t inc;
        read(e->read_end, &inc, sizeof(uint64_t));
    }

    //Maybe it should be invalid for a non pure event
    return 0;
}

int HSDKDestroyEvent(Event e)
{
    if (e->pureEvent) {
        close(e->read_end);
        close(e->write_end);
    }

    free(e);
    //Maybe it should be invalid for a non pure event
    return 0;
}

int HSDKSignalEvent(Event e)
{
    if (e->pureEvent) {
        uint64_t inc = 1;

        int rc = write(e->write_end, &inc, sizeof(uint64_t));

        if (rc == -1) {
            perror("HSDKSignalEvent write");
        }
    }

    //Maybe it should be invalid for a non pure event
    return 0;
}

int HSDKWaitEvent(Event e, int64_t millisecondsToWait)
{
    int rc = 0;

    if (e->pureEvent) {
        uint64_t inc;
        struct pollfd pfds[1];
        int nfds = 1;

        pfds[0].fd = e->read_end;
        pfds[0].events = POLLIN;
        rc = poll(pfds, nfds, millisecondsToWait);

        if (rc == -1) {
            perror("HSDKWaitEvent poll");
            return errno;
        }

        if (pfds[0].revents & POLLIN) {
            read(e->read_end, &inc, sizeof(uint64_t));
        }

    }

    //Maybe it should be invalid for a non pure event
    return rc;
}

int HSDKWaitMultipleEvents(Event *events, uint32_t noEvents, int64_t millisecondsToWait, int *triggeredEvent)
{
    uint32_t i;
    int max = events[0]->read_end;
    fd_set waitSet;
    FD_ZERO(&waitSet);
    FD_SET(events[0]->read_end, &waitSet);

    for (i = 1; i < noEvents; i++) {
        FD_SET(events[i]->read_end, &waitSet);

        if (max < events[i]->read_end) {
            max = events[i]->read_end;
        }
    }

    if (millisecondsToWait == INFINITE_WAIT) {
        int rc = select(max + 1, &waitSet, NULL, NULL, NULL);

        if (rc < 0) {
            perror("HSDKWaitMultipleEvents select");
        }
    } else {
        struct timeval time;

        time.tv_sec = (int)millisecondsToWait / 1000;
        time.tv_usec = (millisecondsToWait - time.tv_sec * 1000) * 1000;

        select(max + 1, &waitSet, NULL, NULL, &time);
    }

    *triggeredEvent = -1;

    for (i = 0; i < noEvents; i++) {
        if (FD_ISSET(events[i]->read_end, &waitSet)) {
            HSDKWaitEvent(events[i], 0);
            *triggeredEvent = i;
            break;
        }
    }

    return 0;
}

#endif
