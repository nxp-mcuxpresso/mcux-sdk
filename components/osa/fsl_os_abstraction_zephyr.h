/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if !defined(__FSL_OS_ABSTRACTION_ZEPHYR_H__)
#define __FSL_OS_ABSTRACTION_ZEPHYR_H__

#include <zephyr/irq.h>
#include <zephyr/kernel.h>
#include "fsl_component_generic_list.h"

/*!
 * @addtogroup os_abstraction_thread
 * @{
 */

/*******************************************************************************
 * Declarations
 ******************************************************************************/
/*! @brief OSA task handle size. */
#define OSA_TASK_HANDLE_SIZE (sizeof(struct k_thread) + sizeof(k_tid_t) + sizeof(k_thread_stack_t *) + sizeof(struct k_sem) + sizeof(list_element_t))

/*! @brief OSA event handle size. */
#define OSA_EVENT_HANDLE_SIZE (sizeof(struct k_event) + sizeof(uint8_t))

/*! @brief OSA semaphore handle size. */
#define OSA_SEM_HANDLE_SIZE sizeof(struct k_sem)

/*! @brief OSA mutex handle size. */
#define OSA_MUTEX_HANDLE_SIZE sizeof(struct k_mutex)

/*! @brief OSA queue handle size. */
#define OSA_MSGQ_HANDLE_SIZE sizeof(struct k_msgq)

/*! @brief OSA timer handle size. */
#define OSA_TIMER_HANDLE_SIZE (sizeof(struct k_timer) + sizeof(struct k_work) + (4 * sizeof(int)))

/*!
 * @brief To provide unified task priority for upper layer, OSA layer makes conversion.
 */
#define PRIORITY_OSA_TO_ZEPHYR(osa_prio)    ((int)OSA_TASK_PRIORITY_MAX + (osa_prio) + 1U)
#define PRIORITY_ZEPHYR_TO_OSA(thread_prio) ((int)(thread_prio) - OSA_TASK_PRIORITY_MAX - 1U)

/*! @} */

#endif /* __FSL_OS_ABSTRACTION_ZEPHYR_H__ */
