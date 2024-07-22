/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_MSCM_H_
#define FSL_MSCM_H_

#include "fsl_common.h"

/*!
 * @addtogroup mscm
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _mscm_uid
{
    uint32_t UID0;
    uint32_t UID1;
    uint32_t UID2;
    uint32_t UID3;
} mscm_uid_t;

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mscm"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief MSCM driver version 2.0.0. */
#define FSL_MSCM_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Get MSCM UID.
 *
 * @param base MSCM peripheral base address.
 * @param uid Pointer to an uid struct.
 */
static inline void MSCM_GetUID(MSCM_Type *base, mscm_uid_t *uid)
{
    uid->UID0 = base->UID[0];
    uid->UID1 = base->UID[1];
    uid->UID2 = base->UID[2];
    uid->UID3 = base->UID[3];
}

/*!
 * @brief Set MSCM Secure Irq.
 *
 * @param base MSCM peripheral base address.
 * @param parameter Value to be write to SECURE_IRQ.
 */
static inline void MSCM_SetSecureIrqParameter(MSCM_Type *base, const uint32_t parameter)
{
    base->SECURE_IRQ = parameter;
}

/*!
 * @brief Get MSCM Secure Irq.
 *
 * @param base MSCM peripheral base address.
 * @return MSCM Secure Irq.
 */
static inline uint32_t MSCM_GetSecureIrq(MSCM_Type *base)
{
    return base->SECURE_IRQ;
}

/*! @} */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* FSL_MSCM_H_ */
