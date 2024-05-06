/*
 * \file hsdkOSCommon.h
 * This is the header file for the OS abstraction modules.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HSDK_OSCOMMON__
#define __HSDK_OSCOMMON__

/************************************************************************************
 ************************************************************************************
 * Include
 ************************************************************************************
 ********************************************************************************* */
#include <stdint.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <Windows.h>

#elif __linux__ || __APPLE__
    #include <fcntl.h>
    #include <poll.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <sys/types.h>

#endif

/*! *********************************************************************************
 ************************************************************************************
 * Public type definitions
 ************************************************************************************
 ********************************************************************************* */
#ifdef _WINDLL
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

#ifdef _WIN32

    #define Thread HANDLE
    #define File HANDLE
    #define Event HANDLE
    #define Lock CRITICAL_SECTION*
    #define Semaphore HANDLE
    #define Timer HANDLE

    #define INVALID_LOCK_HANDLE NULL
    #define INVALID_EVENT_HANDLE NULL
    #define INVALID_THREAD_HANDLE NULL
    #define INVALID_SEMAPHORE_HANDLE NULL

#elif __linux__ || __APPLE__

    #define Thread pthread_t
    #define File int
    #define Lock pthread_mutex_t*
    #define ConditionVariable pthread_cond_t

    #define INVALID_HANDLE_VALUE -1
    #define INVALID_LOCK_HANDLE -1
    #define INVALID_SEMAPHORE_HANDLE  NULL
    #define INVALID_EVENT_HANDLE NULL

#endif

#ifdef __linux__

#define INVALID_THREAD_HANDLE -1

/**
 * @brief Structure for describing an event, on Linux.
 * @details On Linux, the event is an eventfd object.
 */
typedef struct {
    int event;              /**< Implemented on Linux with eventfd. */
    uint8_t pureEvent;      /**< Whether or not the event is an actual frame. */
    uint8_t gpioPollEvent;  /**< Whether a GPIO pin triggered the event. */
} EvtWrapper;

#define Event EvtWrapper*
#define Semaphore EvtWrapper*

#elif defined(__APPLE__)

#define INVALID_THREAD_HANDLE NULL

/**
 * @brief Structure for describing an event, on OS X.
 * @details On OS X, the event is implemented via a pipe, as eventfd is Linux specific.
 */
typedef struct {
    int read_end;       /**< The read end of the pipe. */
    int write_end;      /**< The write end of the pipe. */
    uint8_t pureEvent;  /**< Whether or not the event is an actual frame. */
} EvtWrapper;

#define Event EvtWrapper*
#define Semaphore EvtWrapper*

#endif

#define INFINITE_WAIT -1

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
 ************************************************************************************
 * Public prototypes
 ************************************************************************************
 ********************************************************************************* */

/*! *********************************************************************************
 * \brief  Creates a OS specific thread
 *
 * \param[in] startRoutine   start address of the thread
 * \param[in] arg            pointer to the arguments for the thread
 *
 * \return A Thread
 ********************************************************************************* */
DLLEXPORT Thread HSDKCreateThread(void *(*startRoutine)(void *), void *arg);

/*! *********************************************************************************
 * \brief  Stops and deallocates the memory for a thread
 *
 * \param[in] thread The thread to be stopped
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKDestroyThread(Thread thread);

/*! *********************************************************************************
* \brief  Returns the current thread id
*
* \return None
********************************************************************************** */
DLLEXPORT int HSDKThreadId();


/*! *********************************************************************************
 * \brief  Creates an OS specific event
 *
 * \param[in] initialValue the initial value of the created event
 *
 * \return An Event
 ********************************************************************************* */
DLLEXPORT Event HSDKCreateEvent(int initialValue);
/*! *********************************************************************************
 * \brief  Creates an event that waits for data from a device
 *
 * \param[in] e      the device on which to wait
 * \param[in] context pointer to a pointer to a structure to store the context
 *
 * \return An Event
 ********************************************************************************* */
DLLEXPORT Event HSDKDeviceTriggerableEvent(File e, void **context);
/*! *********************************************************************************
 * \brief  Destroys the context of the device waitable event
 *
 * \param[in] context pointer to a structure to store the context
 *
 * \return A None
 ********************************************************************************* */
DLLEXPORT int HSDKFinishTriggerableEvent(void *context);
/*! *********************************************************************************
 * \brief  Destroys an event
 *
 * \param[in] e the event
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKDestroyEvent(Event e);
/*! *********************************************************************************
 * \brief  Resets the value of the event
 *
 * \param[in] e the event
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKResetEvent(Event e);
/*! *********************************************************************************
 * \brief  Signals the event
 *
 * \param[in] e the event
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKSignalEvent(Event e);
/*! *********************************************************************************
 * \brief  Waits on the event
 *
 * \param[in] e the event
 * \param[in] milisecondToWait the timeout value of the wait
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKWaitEvent(Event e, int64_t milisecondToWait);
/*! *********************************************************************************
 * \brief  Waits for multiple events
 *
 * \param[in] events                an array of events
 * \param[in] noEvents              the number of events
 * \param[in] milisecondToWait      the timeout value
 * \param[in,out] triggeredEvent    used for return value; -1 means no triggered event,
 *                                  otherwise it is the index of the event
 *
 * \return Index in the array of the event that was signaled. If multiple events were
 * signaled the first one to be signaled is returned
 ********************************************************************************* */
DLLEXPORT int HSDKWaitMultipleEvents(Event *events, uint32_t noEvents, int64_t milisecondToWait, int *triggeredEvent);


/*! *********************************************************************************
 * \brief  Opens the file referenced by the filename, in full or relative path
 *
 * \param[in] filename  the path of the file
 *
 * \return A File
 ********************************************************************************* */
DLLEXPORT File HSDKOpenFile(char *filename);
/*! *********************************************************************************
 * \brief  Closes the file
 *
 * \param[in] f The file
 *
 * \return 0 if successful, -1 otherwise
 ********************************************************************************* */
DLLEXPORT int HSDKCloseFile(File f);
/*! *********************************************************************************
* \brief  Write to the file
*
* \param[in] file  The file
* \param[in] buffer The buffer from which data written to the file
* \param[in] count Max count of bytes to be written
*
* \return Number of bytes written
********************************************************************************** */
DLLEXPORT int HSDKWriteFile(File file, uint8_t *buffer, uint32_t count);
/*! *********************************************************************************
* \brief  Reads from the file
*
* \param[in] file  The file
* \param[in] buffer The buffer into which data is read
* \param[in] count Max count of bytes to be read
*
* \return Count of bytes read
********************************************************************************** */
DLLEXPORT int HSDKReadFile(File file, uint8_t *buffer, uint32_t *count);
/*! *********************************************************************************
 * \brief  Checks for the validity of a descriptor. An open file has a valid descriptor
 *
 * \param[in] f  The file

 * \return 0 if it is invalid and 1 if valid
 ********************************************************************************* */
DLLEXPORT int HSDKIsDescriptorValid(File f);
/*! *********************************************************************************
 * \brief  Invalidates the descriptor
 *
 * \param[in] f The file
 *
 * \return 0 if it is invalid and 1 if valid
 ********************************************************************************* */
DLLEXPORT void HSDKInvalidateDescriptor(File *f);
/*! *********************************************************************************
 * \brief  Handles an error on the file
 *
 * \param[in] f     The file
 *
 * \return 0
 ********************************************************************************* */
DLLEXPORT int HSDKHandleError(File f);


/*! *********************************************************************************
 * \brief  Creates an OS specific lock
 *
 * \return A lock
 ********************************************************************************* */
DLLEXPORT Lock HSDKCreateLock();
/*! *********************************************************************************
 * \brief  Acquires the lock
 *
 * \param[in] l The lock
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKAcquireLock(Lock l);
/*! *********************************************************************************
 * \brief  Releases the lock
 *
 * \param[in] l The lock
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKReleaseLock(Lock l);
/*! *********************************************************************************
 * \brief  Destroys the lock
 *
 * \param[in] l The lock
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKDestroyLock(Lock l);

/*! *********************************************************************************
 * \brief  Creates a semaphore
 *
 * \param[in] initialValue the value of the semaphore
 * \param[in] maxValue the maximum value the semaphore can obtain
 *
 * \return A semaphore
 ********************************************************************************* */
DLLEXPORT Semaphore HSDKCreateSemaphore(uint32_t initialValue, uint32_t maxValue);
/*! *********************************************************************************
 * \brief  Acquires the semaphore
 *
 * \param[in] s The semaphore
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKAcquireExplicitlySemaphore(Semaphore s);
/*! *********************************************************************************
 * \brief  Releases the semaphore
 *
 * \param[in] s The semaphore
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKReleaseSemaphore(Semaphore s);
/*! *********************************************************************************
 * \brief  Destroy the semaphore
 *
 * \param[in] s The semaphore
 *
 * \return None
 ********************************************************************************* */
DLLEXPORT int HSDKDestroySemaphore(Semaphore s);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
