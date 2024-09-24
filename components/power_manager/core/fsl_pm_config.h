/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PM_CONFIG_H_
#define _FSL_PM_CONFIG_H_

#include "fsl_pm_device_config.h"

#ifndef FSL_PM_SUPPORT_NOTIFICATION
#define FSL_PM_SUPPORT_NOTIFICATION (0)
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

#ifndef FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER
#define FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER (0)
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

#ifndef FSL_PM_SUPPORT_LP_TIMER_CONTROLLER
#define FSL_PM_SUPPORT_LP_TIMER_CONTROLLER (0)
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

/*!
 * @brief If defined FSL_PM_SUPPORT_ALWAYS_ON_SECTION and set the macro to 1, then some critical
 * data of the power manager will be placed into the RAM section that is always powered on.
 * If this macro is not defined or this macro is set as 0, then upper software should use some
 * memory related constraint to guarantee some critical data of the system are retained in the selected power mode.
 */
#ifndef FSL_PM_SUPPORT_ALWAYS_ON_SECTION
#define FSL_PM_SUPPORT_ALWAYS_ON_SECTION (0)
#endif /* FSL_PM_SUPPORT_ALWAYS_ON_SECTION */

#ifndef PM_CONSTRAINT_COUNT
#define PM_CONSTRAINT_COUNT (0U)
#endif /* PM_CONSTRAINT_COUNT */

#ifndef PM_LP_STATE_COUNT
#define PM_LP_STATE_COUNT (0U)
#endif

#ifndef PM_RESC_GROUP_ARRAY_SIZE
#define PM_RESC_GROUP_ARRAY_SIZE ((PM_CONSTRAINT_COUNT) / 8U + 1U)
#endif /* PM_RESC_GROUP_ARRAY_SIZE */

#ifndef PM_RESC_MASK_ARRAY_SIZE
#define PM_RESC_MASK_ARRAY_SIZE ((PM_CONSTRAINT_COUNT) / 32U + 1U)
#endif /* PM_RESC_MASK_ARRAY_SIZE */

#define PM_RESOURCE_OFF          (0U)
#define PM_RESOURCE_PARTABLE_ON1 (1U)
#define PM_RESOURCE_PARTABLE_ON2 (2U)
#define PM_RESOURCE_FULL_ON      (4U)

/* The whole counter for constraint is allocated as 8-bits width. */
#define PM_PARTABLE_ON1_COUNTER_SIZE (3U)
#define PM_PARTABLE_ON1_COUNTER_MASK (0x7U)
#define PM_PARTABLE_ON2_COUNTER_SIZE (3U)
#define PM_PARTABLE_ON2_COUNTER_MASK (0x38U)
#define PM_FULL_ON_COUNTER_SIZE      (2U)
#define PM_FULL_ON_COUNTER_MASK      (0xC0U)

#ifndef PM_ENCODE_RESC
#define PM_ENCODE_RESC(opMode, rescShift) ((((uint32_t)(opMode)) << 8UL) | (rescShift))
#endif /* PM_ENCODE_RESC */

#ifndef PM_DECODE_RESC
#define PM_DECODE_RESC(resConstraint)                         \
    opMode    = (uint32_t)(((uint32_t)resConstraint) >> 8UL); \
    rescShift = (uint32_t)(((uint32_t)resConstraint) & 0xFFUL)
#endif /* PM_DECODE_RESC */

#ifndef PM_ENCODE_WAKEUP_SOURCE_ID
#define PM_ENCODE_WAKEUP_SOURCE_ID(id) (id)
#endif /* PM_ENCODE_WAKEUP_SOURCE_ID */

#ifndef PM_DECODE_WAKEUP_SOURCE_ID
#define PM_DECODE_WAKEUP_SOURCE_ID(wsId) (wsId)
#endif /* PM_DECODE_WAKEUP_SOURCE_ID */

#endif /* _FSL_PM_CONFIG_H_ */
