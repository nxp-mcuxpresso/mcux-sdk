/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_MSGINTR_H_
#define FSL_MSGINTR_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief MSGINTR driver version. */
#define FSL_MSGINTR_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

#define FSL_MSGINTR_CHANNEL_NUM (3U)

typedef void (*msgintr_cb_t)(MSGINTR_Type *base, uint8_t channel, uint32_t pendingIntr);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initializes the MSGINT
 * This API enables the interrupt and set the callback for message interrrupt.
 *
 * @param base  MSGINT base address
 * @param callback  Callback for message interrupt
 * @retval status_t
 */
status_t MSGINTR_Init(MSGINTR_Type *base, msgintr_cb_t callback);

/*!
 * @brief Deinitializes the MSGINT
 * This API disables the interrupt and clean the pending interrupt status.
 *
 * @param base  MSGINT base address
 * @retval status_t
 */
status_t MSGINTR_Deinit(MSGINTR_Type *base);

/*!
 * @brief Gets the message interrupt address
 * This API return the address to let application choose which message interrupt to be triggered.
 *
 * @param base  MSGINT base address
 * @param channel  The channel to be triggered.
 * @retval status_t
 */
static inline uint32_t MSGINTR_GetIntrSelectAddr(MSGINTR_Type *base, uint8_t channel)
{
    assert(channel < FSL_MSGINTR_CHANNEL_NUM);

    return (uint32_t)(&base->MSI[channel].MSIIR);
}

#if defined(__cplusplus)
}
#endif

#endif /* FSL_MSGINTR_H_ */
