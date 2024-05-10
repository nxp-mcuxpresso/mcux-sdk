/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_IERB_H_
#define FSL_NETC_IERB_H_

#include "fsl_netc.h"

/*!
 * @brief Software reset NETC module
 * Software should follow these steps when initiating a soft reset to avoid hanging any outstanding transactions in the system.
 * - Software disables MAC receive function(s).
 * - Software sets the soft reset bit NETCRR[SR]=1.
 *   + NETC stops further prefetching of BDs
 *   + NETC stops scheduling transmit frames
 * - Software waits for NETC to complete any in-flight transmit frames processing.
 *   + If there is use of time gating or credit based shaping, worst case wait time is SaTGSLR/EaTGSLR[MIN_LOOKAHEAD] +
 *     PTGSATOR[ADV_TIME_OFFSET] + Transmit(MAX_SDU) + Writeback BD.
 *   + If there is no use of time gating or credit based shaping, worst case wait time is Transmit(MAX_SDU) + Writeback BD.
 * - Software waits for either:
 *   + 100 ms (as per PCIe specification).
 *   + Shortest possible reset time as defined by IERB register NETCFLRCR.
 *   + NETCSR[SR] bit to clear by polling.
 * - Software reconfigures NETC.
 */
void NETC_SoftReset(void);

/*!
 * @brief Check NETC software reset over status
 *
 * @return bool  True: Software reset is over, False: Software reset is not over.
 */
static inline bool NETC_SoftResetIsOver(void)
{
    return ((NETC_PRIV->NETCRR & NETC_PRIV_NETCRR_SR_MASK) == 0U);
}

/*!
 * @brief Lock NETC IERB access
 * @note Can't access IERB register after locking.
 *
 * @return status_t
 */
status_t NETC_IERBLock(void);

/*!
 * @brief Check NETC IERB lock complete status.
 *
 * @return bool  True: IERB lock is over, False: IERB lock is not over.
 */
static inline bool NETC_IERBIsLockOver(void)
{
    return ((NETC_PRIV->NETCSR & NETC_PRIV_NETCSR_STATE_MASK) == 0U);
}

/*!
 * @brief Check NETC IERB lock error status
 *
 * @return bool  True: IERB lock is over, False: IERB lock is not over.
 */
static inline bool NETC_IERBIsLockErr(void)
{
    return ((NETC_PRIV->NETCSR & NETC_PRIV_NETCSR_ERROR_MASK) != 0U);
}

/*!
 * @brief Unlock NETC IERB
 *
 * @return status_t
 */
status_t NETC_IERBUnlock(void);

/*!
 * @brief Check NETC IERB unlock complete status.
 *
 * @return bool  True: IERB lock is over, False: IERB lock is not over.
 */
static inline bool NETC_IERBIsUnlockOver(void)
{
    return ((NETC_PRIV->NETCRR & NETC_PRIV_NETCRR_LOCK_MASK) == 0U);
}

#endif /* FSL_NETC_IERB_H_ */
