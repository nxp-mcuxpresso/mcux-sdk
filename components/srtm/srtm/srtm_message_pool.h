/*
 * Copyright 2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_MESSAGE_POOL_H__
#define __SRTM_MESSAGE_POOL_H__

#include <srtm_defs.h>

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Allocate a message with specific size.
 *
 * @param size message size to allocate.
 *
 * @return allocated message address.
 */
void *SRTM_MessagePool_Alloc(uint32_t size);

/*!
 * @brief Free the allocated message.
 *
 * @param buf the address of the allocated message
 */
void SRTM_MessagePool_Free(void *buf);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_MESSAGE_POOL_H__ */
