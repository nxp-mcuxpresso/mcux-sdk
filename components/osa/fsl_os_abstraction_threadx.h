/*! *********************************************************************************
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ********************************************************************************** */
#if !defined(__FSL_OS_ABSTRACTION_THREADX_H__)
#define __FSL_OS_ABSTRACTION_THREADX_H__

#include "tx_api.h"
#include "fsl_component_generic_list.h"

/*!
 * @addtogroup os_abstraction_thread
 * @{
 */

/*******************************************************************************
 * Declarations
 ******************************************************************************/
/*! @brief OSA task handle size. */
#define OSA_TASK_HANDLE_SIZE (sizeof(TX_THREAD) + sizeof(list_element_t))

/*! @brief OSA event handle size. */
#define OSA_EVENT_HANDLE_SIZE (sizeof(TX_EVENT_FLAGS_GROUP) + sizeof(uint8_t))

/*! @brief OSA semaphore handle size. */
#define OSA_SEM_HANDLE_SIZE sizeof(TX_SEMAPHORE)

/*! @brief OSA mutex handle size. */
#define OSA_MUTEX_HANDLE_SIZE sizeof(TX_MUTEX)

/*!
 * @brief To provide unified task priority for upper layer, OSA layer makes conversion.
 */
#define PRIORITY_OSA_TO_THREAD(osa_prio)    ((UINT)TX_MAX_PRIORITIES - (osa_prio)-2U)
#define PRIORITY_THREAD_TO_OSA(thread_prio) ((UINT)TX_MAX_PRIORITIES - (thread_prio)-2U)

#endif /* __FSL_OS_ABSTRACTION_THREADX_H__ */
