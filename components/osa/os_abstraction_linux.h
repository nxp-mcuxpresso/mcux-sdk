/*
 * Copyright 2024 ACRIOS Systems s.r.o.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __OS_ABSTRACTION_LINUX_H__
#define __OS_ABSTRACTION_LINUX_H__

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>

struct osa_task_t {
    pthread_t thread;
    pthread_mutex_t suspendMutex;
    pthread_cond_t suspendCond;
    bool isSuspended;
    void (*task_function)(void *);
};
#endif /* __OS_ABSTRACTION_LINUX_H__ */
