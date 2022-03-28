/*
 *     Copyright 2021 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CSS_PKC_H_
#define _FSL_CSS_PKC_H_

#include <stdint.h>
#include <stddef.h>

#include "fsl_common.h"
#include <mcuxClCss.h>              // Interface to the entire nxpClCss component
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <ip_platform.h>

/*!
 * @addtogroup css_pkc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum
{
    kStatus_SlotUnavailable = MAKE_STATUS(kStatusGroup_CSS_PKC, 0),  /*!< Key slot is not available to be used as PRNG kick-off. */
};
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief CSS Init after power down.
 *
 * This function enable all CSS related clocks, enable CSS and start CSS PRNG.
 * Normally all of these actions are done automatically by boot ROM, but if an application uses Power Down mode
 * this function must be called before using CSS after wake-up.
 *
 * @param base CSS peripheral address.
 *
 * @return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t CSS_PowerDownWakeupInit(CSS_Type *base);

/*!
 * @brief PKC Init after power down.
 *
 * This function enables RAM interleave, clocks, zeroize the PKC RAM and reset PKC peripheral.
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
 * This function enables RAM interleave, clocks and reset PKC peripheral.
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

#endif /* _FSL_CSS_PKC_H_ */
