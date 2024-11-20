/*
 * Copyright 2024 ACRIOS Systems s.r.o.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "fsl_common.h"
#include "fsl_os_abstraction.h"
#include "os_abstraction_linux.h"
#include "stdio.h"
#include <time.h>

#define MAX_TASKS 10

static struct osa_task_t taskList[MAX_TASKS];
static pthread_mutex_t taskListMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_key_t taskKey;

void setTaskForCurrentThread(struct osa_task_t *task) {
    pthread_setspecific(taskKey, task);
}

void *osa_thread_wrapper(void *arg) {
    struct osa_task_t *task = (struct osa_task_t *)arg;

    while (1) {
        // Check if the task is suspended
        pthread_mutex_lock(&task->suspendMutex);
        while (task->isSuspended) {
            pthread_cond_wait(&task->suspendCond, &task->suspendMutex);
        }
        pthread_mutex_unlock(&task->suspendMutex);

        // Check if task function is valid
        if (task->task_function != NULL) {
            task->task_function(NULL); // Execute task function if valid
        }
        else {
            fprintf(stderr, "Error: Task function pointer is NULL.\n");
            break;
        }
    }
    return NULL;
}

static void addTaskToList(struct osa_task_t *task) {
    pthread_mutex_lock(&taskListMutex);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (taskList[i].thread == 0) {
            taskList[i] = *task;
            printf("Added task for thread %lu at index %d\n", (unsigned long)task->thread, i);
            break;
        }
    }

    pthread_mutex_unlock(&taskListMutex);
}

static struct osa_task_t *findTaskByThread(pthread_t thread) {
    pthread_mutex_lock(&taskListMutex);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (pthread_equal(taskList[i].thread, thread)) {
            pthread_mutex_unlock(&taskListMutex);
            return &taskList[i];
        }
    }

    pthread_mutex_unlock(&taskListMutex);
    return NULL; // Not found
}

static void removeTaskFromList(pthread_t thread) {
    pthread_mutex_lock(&taskListMutex);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (pthread_equal(taskList[i].thread, thread)) {
            memset(&taskList[i], 0, sizeof(struct osa_task_t)); // Clear the slot
            printf("Removed task for thread %lu from index %d\n", (unsigned long)thread, i);
            break;
        }
    }

    pthread_mutex_unlock(&taskListMutex);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_TaskCreate
 * Description   : This function is used to create a task and make it ready.
 * Param[in]     :  threadDef  - Definition of the thread.
 *                  task_param - Parameter to pass to the new thread.
 * Return Thread handle of the new thread, or NULL if failed.
 *
 *END**************************************************************************/

osa_status_t OSA_TaskCreate(osa_task_handle_t taskHandle, const osa_task_def_t *thread_def, osa_task_param_t task_param) {
    struct osa_task_t* task = (struct osa_task_t*)taskHandle;
    osa_status_t status = KOSA_StatusError;
    pthread_attr_t attr;

    // Set up task function
    task->task_function = thread_def->pthread;

    printf("Task function pointer address = %p\n", (void *)task->task_function);

    // Initialize pthread attributes
    if (pthread_attr_init(&attr) != 0) {
        return status;
    }

    // Set stack size if specified in thread_def
    if (thread_def->stacksize > 0) {
        pthread_attr_setstacksize(&attr, thread_def->stacksize);
    }

    // Initialize suspension control
    pthread_mutex_init(&task->suspendMutex, NULL);
    pthread_cond_init(&task->suspendCond, NULL);
    task->isSuspended = false;

    // Register the task
    setTaskForCurrentThread(task);

    // Create the thread
    if (pthread_create(&task->thread, &attr, osa_thread_wrapper, (void *)task) == 0) {
        status = KOSA_StatusSuccess;
        addTaskToList(task); // Add task to the list
    }

    // Clean up attributes
    pthread_attr_destroy(&attr);
    return status;
}

osa_status_t OSA_TaskDestroy(osa_task_handle_t taskHandle) {
    struct osa_task_t* task = (struct osa_task_t*)taskHandle;

    if (task == NULL) {
        fprintf(stderr, "Error: Task handle is NULL in OSA_TaskDestroy.\n");
        return KOSA_StatusError;
    }

    // Cancel the thread
    if (pthread_cancel(task->thread) != 0) {
        fprintf(stderr, "Error: Failed to cancel thread in OSA_TaskDestroy.\n");
        return KOSA_StatusError;
    }

    // Wait for the thread to exit
    if (pthread_join(task->thread, NULL) != 0) {
        fprintf(stderr, "Error: Failed to join thread in OSA_TaskDestroy.\n");
        return KOSA_StatusError;
    }

    // Remove the task from the taskList
    removeTaskFromList(task->thread);

    // Destroy mutex and condition variable
    pthread_mutex_destroy(&task->suspendMutex);
    pthread_cond_destroy(&task->suspendCond);

    // Clear the task structure
    memset(task, 0, sizeof(struct osa_task_t));

    return KOSA_StatusSuccess;
}


void OSA_TimeDelay(uint32_t millisec) {
    usleep(millisec * 1000);  //usleep is in microseconds
}

void OSA_TaskSuspend(osa_task_handle_t taskHandle) {
    struct osa_task_t *task;

    printf("Task suspending thread %lu\n", (unsigned long)pthread_self());

    if (taskHandle == NULL) {
        pthread_t currentThread = pthread_self();
        task = findTaskByThread(currentThread); // Retrieve task from taskList
        if (task == NULL) {
            fprintf(stderr, "Error: No task found for current thread.\n");
            return; // Exit if task is not found
        }
    } else {
        task = (struct osa_task_t *)taskHandle;
    }

    // Suspend the task
    task->isSuspended = true;
    pthread_mutex_lock(&task->suspendMutex);
    while (task->isSuspended) {
        pthread_cond_wait(&task->suspendCond, &task->suspendMutex); // Block until resumed
    }
    pthread_mutex_unlock(&task->suspendMutex);
}


void OSA_TaskResume(osa_task_handle_t taskHandle) {
    struct osa_task_t *task = (struct osa_task_t *)taskHandle;

    if (task == NULL) {
        fprintf(stderr, "Error: Task handle is NULL in OSA_TaskResume.\n");
        return;
    }

    pthread_mutex_lock(&task->suspendMutex);
    task->isSuspended = false;
    pthread_cond_signal(&task->suspendCond); // Notify waiting threads
    pthread_mutex_unlock(&task->suspendMutex);

    printf("Task resumed for thread %lu\n", (unsigned long)task->thread);
}


osa_status_t OSA_MutexCreate(osa_mutex_handle_t mutexHandle) {
    if (mutexHandle == NULL)
    {
        return KOSA_StatusError;
    }
    pthread_mutex_t *mutex = (pthread_mutex_t *)mutexHandle;
    if (pthread_mutex_init(mutex, NULL) == 0)
    {
        return KOSA_StatusSuccess;
    }
    return KOSA_StatusError;
}

osa_status_t OSA_MutexLock(osa_mutex_handle_t mutexHandle, uint32_t millisec) {
    if (mutexHandle == NULL) {
        return KOSA_StatusError;
    }
    pthread_mutex_t *mutex = (pthread_mutex_t *)mutexHandle;

    if (millisec == osaWaitForever_c) {
        if (pthread_mutex_lock(mutex) == 0) {
            return KOSA_StatusSuccess;
        }
    }
    else if (millisec == 0) {
        if (pthread_mutex_trylock(mutex) == 0) {
            return KOSA_StatusSuccess;
        }
        return KOSA_StatusTimeout;
    }
    else {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += millisec / 1000;
        ts.tv_nsec += (millisec % 1000) * 1000000;

        if (pthread_mutex_timedlock(mutex, &ts) == 0) {
            return KOSA_StatusSuccess;
        }
        return KOSA_StatusTimeout;
    }
    return KOSA_StatusError;
}

osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle) {
    if (mutexHandle == NULL) {
        return KOSA_StatusError;
    }
    pthread_mutex_t *mutex = (pthread_mutex_t *)mutexHandle;
    if (pthread_mutex_unlock(mutex) == 0) {
        return KOSA_StatusSuccess;
    }
    return KOSA_StatusError;
}

osa_status_t OSA_MutexDestroy(osa_mutex_handle_t mutexHandle) {
    if (mutexHandle == NULL) {
        return KOSA_StatusError;
    }
    pthread_mutex_t *mutex = (pthread_mutex_t *)mutexHandle;
    if (pthread_mutex_destroy(mutex) == 0) {
        return KOSA_StatusSuccess;
    }
    return KOSA_StatusError;
}