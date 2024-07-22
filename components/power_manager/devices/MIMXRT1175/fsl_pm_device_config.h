/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PM_DEVICE_CONFIG_H_
#define _FSL_PM_DEVICE_CONFIG_H_

#define FSL_PM_SUPPORT_NOTIFICATION          (true)
#define FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER (true)
#define FSL_PM_SUPPORT_LP_TIMER_CONTROLLER   (true)

#ifndef PM_PM_DUAL_CORE_USED
#define PM_PM_DUAL_CORE_USED (false)  /*!< Can change to true based on specific application. */
#endif                                /* PM_PM_DUAL_CORE_USED */

#define PM_RESC_MASK_ARRAY_SIZE  (2U) // defined 43 basic resources, each basic resource cost 1 bit.
#define PM_RESC_GROUP_ARRAY_SIZE (6U) // defined 43 basic resources, each basic resource cost 4 bit.

#define PM_CONSTRAINT_COUNT (43U)     // defined 43 basic resources, can found in fsl_pm_device.h.
#define PM_LP_STATE_COUNT   (17U)     // defined 17 low power states.

#define PM_ENCODE_WAKEUP_SOURCE_ID(irqId) (irqId)
#define PM_DECODE_WAKEUP_SOURCE_ID(wsId)  (wsId)

#endif /* _FSL_PM_DEVICE_CONFIG_H_ */
