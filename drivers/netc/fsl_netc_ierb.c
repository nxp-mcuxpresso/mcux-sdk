/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_ierb.h"

void NETC_SoftReset(void)
{
    /* Software reset whole NETC. */
    NETC_PRIV->NETCRR |= NETC_PRIV_NETCRR_SR_MASK;
}

status_t NETC_IERBLock(void)
{
    /* IERB have been locked. */
    if ((NETC_PRIV->NETCRR & NETC_PRIV_NETCRR_LOCK_MASK) != 0U)
    {
        return kStatus_Fail;
    }

    /* Lock the IERB. */
    NETC_PRIV->NETCRR |= NETC_PRIV_NETCRR_LOCK_MASK;

    return kStatus_Success;
}

status_t NETC_IERBUnlock(void)
{
    /* IERB have been unlocked. */
    if ((NETC_PRIV->NETCRR & NETC_PRIV_NETCRR_LOCK_MASK) == 0U)
    {
        return kStatus_Fail;
    }

    /* Unlock the IERB. It will warm reset whole NETC. */
    NETC_PRIV->NETCRR &= ~NETC_PRIV_NETCRR_LOCK_MASK;

    return kStatus_Success;
}


