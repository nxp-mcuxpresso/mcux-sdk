/*! *********************************************************************************
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 *
 * This is the header file for the OS Abstraction layer for Zephyr.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ********************************************************************************** */
#ifndef _FSL_OS_ABSTRACTION_ZEPHYR_H_
#define _FSL_OS_ABSTRACTION_ZEPHYR_H_

#include <zephyr/kernel.h>
#include <zephyr/kernel/thread.h>

/*!
 * @addtogroup os_abstraction_zephyr
 * @{
 */

/**
 * INFORMATION for developers:
 *
 * To turn on ASSERTS of OSA layer, define and set macro CONFIG_OSA_DEBUG_ASSERT_ENABLED = 1.
 * Turned off by default.
 *
 * Call OSA_Init() before using any task API (taskCreate, etc ...)
 *
 * List of differences between NXP's OSA API and Zephyr's API:
 *      [OSA_TaskCreate] unused following variables in OSA's thread_def: tlink, useFloat, instances.
 *      [OSA_TaskGetPriority] different priority formats. See function comment for more info.
 *      [OSA_TaskSetPriority] different priority formats. See function comment for more info.
 *      [OSA_Start] does nothing in Zephyr. Scheduler started automatically.
 * List of unsupported OSA API:
 *      [OSA_InstallIntHandler]
 *
 * CONFIG_EVENTS must be set in order to use Event api. Zephyr is not enabling its event API by default.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** Zephyr does not check whether handle for specific OS primitive is correct.
   This may lead to unexpected behavior. This OSA layer port adds checkmark to all
   OS primitives checking if it is correct at every API call, returning back error
   and rising assert if incorrect, preventing from unexpected behavior. Every checkmark
   value prefixes with "OSA_CHECKMARK".
 */
#define OSA_CHECKMARK_TASK  (0x05A05A01u)
#define OSA_CHECKMARK_MSGQ  (0x05A05A02u)
#define OSA_CHECKMARK_EVENT (0x05A05A03u)
#define OSA_CHECKMARK_MUTEX (0x05A05A04u)
#define OSA_CHECKMARK_SEM   (0x05A05A05u)
#define OSA_CHECKMARK_EMPTY (0x05A05A00u)
typedef uint32_t checkmark_t;

/** List of Zephyr primitive handles.
   Each time RTOS primitive is created, it is pointing to one of following structures
   with naming convention: osa_zephyr_<primitiveName>Handle_t. For example:
   osa_zephyr_taskHandle_t.
*/

/*! @brief Private Zephyr OSA task handle. Do not use directly. */
typedef struct _osa_zephyr_taskHandle
{
    sys_dnode_t listNode;
    k_tid_t handle;
    k_thread_stack_t *stackPtr;
    struct k_thread controlBlock;
    checkmark_t checkmark;
    struct k_sem notification;
} osa_zephyr_taskHandle_t;

/*! @brief Private Zephyr OSA message queue handle. Do not use directly. */
typedef struct _osa_zephyr_msgQueueHandle
{
    struct k_msgq handle;
    checkmark_t checkmark;
} osa_zephyr_msgQueueHandle_t;

/*! @brief Private Zephyr OSA event handle. Do not use directly. */
typedef struct _osa_zephyr_eventHandle
{
#ifdef CONFIG_EVENTS
    struct k_event handle;
    bool is_autoClear;
    checkmark_t checkmark;
#endif
} osa_zephyr_eventHandle_t;

/*! @brief Private Zephyr OSA mutex handle. Do not use directly. */
typedef struct _osa_zephyr_mutexHandle
{
    struct k_mutex handle;
    checkmark_t checkmark;
} osa_zephyr_mutexHandle_t;

/*! @brief Private Zephyr OSA semaphore handle. Do not use directly. */
typedef struct _osa_zephyr_semHandle
{
    struct k_sem handle;
    checkmark_t checkmark;
} osa_zephyr_semHandle_t;

/*! @brief Private Zephyr OSA timer handle. Do not use directly.*/
typedef struct _osa_zephyr_timerHandle
{
    struct k_timer handle;
    struct k_work work;
    uint32_t padding[4];
} osa_zephyr_timerHandle_t;

/*! @brief Zephyr OSA task handle size. */
#define OSA_TASK_HANDLE_SIZE (sizeof(osa_zephyr_taskHandle_t))

/*! @brief Zephyr OSA event handle size. */
#define OSA_EVENT_HANDLE_SIZE (sizeof(osa_zephyr_eventHandle_t))

/*! @brief Zephyr OSA semaphore handle size. */
#define OSA_SEM_HANDLE_SIZE (sizeof(osa_zephyr_semHandle_t))

/*! @brief Zephyr OSA mutex handle size. */
#define OSA_MUTEX_HANDLE_SIZE (sizeof(osa_zephyr_mutexHandle_t))

/*! @brief Zephyr OSA queue handle size. */
#define OSA_MSGQ_HANDLE_SIZE (sizeof(osa_zephyr_msgQueueHandle_t))

/*! @brief Zephyr OSA timer handle size. */
#define OSA_TIMER_HANDLE_SIZE (sizeof(osa_zephyr_timerHandle_t))

#define OSA_ZEPHYR_TASK_GET_PRIORITY_ERROR (0xDEAD)

/**
 * @}
 */

#endif /* _FSL_OS_ABSTRACTION_ZEPHYR_H_ */
