/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_RNG_DRIVER_H_
#define FSL_RNG_DRIVER_H_

#include "fsl_common.h"

#if defined(FSL_FEATURE_SOC_LPC_RNG_COUNT) && FSL_FEATURE_SOC_LPC_RNG_COUNT

/*!
 * @addtogroup rng
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rng"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief RNG driver version 2.1.0.
 *
 * Current version: 2.1.0
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version.
 * - Version 2.1.0
 *   - Renamed function RNG_GetRandomData() to RNG_GetRandomDataWord(). Added function RNG_GetRandomData() which
 * discarding next 32 words after reading RNG register which results into better entropy, as is recommended in UM.
 *   - API is aligned with other RNG driver, having similar functionality as other RNG/TRNG drivers.
 */
#define FSL_RNG_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Gets random data.
 *
 * This function gets random data from the RNG.
 *
 * @param data  Pointer address used to store random data.
 * @param dataSize  Size of the buffer pointed by the data parameter.
 * @return Status from operation
 */
status_t RNG_GetRandomData(void *data, size_t dataSize);

/*!
 * @brief Gets random data.
 *
 * This function returns single 32 bit random number.
 * For each read word next 32 words should be discarded to achieve better entropy.
 *
 * @return random data
 */
static inline uint32_t RNG_GetRandomDataWord(void)
{
    return OTP_API->rngRead();
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_LPC_RNG_COUNT */
#endif /*FSL_RNG_DRIVER_H_*/
