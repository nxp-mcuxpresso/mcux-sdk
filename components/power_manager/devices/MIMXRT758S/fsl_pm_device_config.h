/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_PM_DEVICE_CONFIG_H_
#define FSL_PM_DEVICE_CONFIG_H_

#include "fsl_pm_device.h"

#define FSL_PM_SUPPORT_NOTIFICATION          (1U)
#define FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER (1U)
#define FSL_PM_SUPPORT_LP_TIMER_CONTROLLER   (1U)

#define PM_CONSTRAINT_COUNT ((uint32_t)kResc_MaxNum)
#define PM_LP_STATE_COUNT   (5U)

/*!
 * irqn:      The irq number of wakeup.
 * misc:      Misc usage, for wakeup pin, this field is used to store edge detection type.
 *            0b -- Wakeup pin enabled with low level detection.
 *            1b -- Wakeup pin enabled with high level detection.
 */
#define PM_ENCODE_WAKEUP_SOURCE_ID(irqn, misc) (((irqn)&0xFFUL) | (((misc) << 8UL) & 0xFF00UL))

#define PM_DECODE_WAKEUP_SOURCE_ID(wsId) \
    irqn = ((wsId)&0xFFUL);              \
    misc = ((wsId)&0xFF00UL) >> 8UL

#endif /* FSL_PM_DEVICE_CONFIG_H_ */
