/*
 *     Copyright 2021 - 2023 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MCUX_PKC_H_
#define _MCUX_PKC_H_

#include <stdint.h>
#include <stddef.h>

#include "fsl_common.h"
#include <ip_platform.h>

/*!
 * @addtogroup els_pkc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief PKC Init after power down.
 *
 * This function enables clocks, zeroize the PKC RAM and reset PKC peripheral.
 * Normally all of these actions are done automatically by boot ROM, but if an application uses Power Down mode
 * this function must be called before using PKC after wake-up.
 *
 * @param base PKC peripheral address.
 *
 * @return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t PKC_PowerDownWakeupInit(PKC_Type *base);

/*!
 * @brief PKC Init after power down.
 *
 * This function enables clocks and reset PKC peripheral.
 *
 * @param base PKC peripheral address.
 *
 * @return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t PKC_InitNoZeroize(PKC_Type *base);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _MCUX_PKC_H_ */
