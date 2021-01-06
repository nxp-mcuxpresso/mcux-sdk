/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BS
 */
#ifndef _FSL_DSP_H_
#define _FSL_DSP_H_

#include <stdint.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup dsp
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief reset driver version 2.1.1. */
#define FSL_DSP_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*@}*/

/*!
 * @brief Structure for DSP copy image to destination address
 *
 * Defines start and destination address for copying image with given size.
 */
typedef struct _dsp_copy_image
{
    uint32_t *srcAddr;
    uint32_t *destAddr;
    uint32_t size;
} dsp_copy_image_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializing DSP core.
 *
 * Power up DSP TCM
 * Enable DSP clock
 * Reset DSP peripheral
 */
void DSP_Init(void);
/*!
 * @brief Deinit DSP core.
 *
 * Power down DSP TCM
 * Disable DSP clock
 * Set DSP peripheral reset
 */
void DSP_Deinit(void);

/*!
 * @brief Copy DSP image to destination address.
 *
 * Copy DSP image from source address to destination address with given size.
 *
 * @param dspCopyImage Structure contains information for DSP copy image to destination address.
 */
void DSP_CopyImage(dsp_copy_image_t *dspCopyImage);

/*!
 * @brief Start DSP core.
 */
static inline void DSP_Start(void)
{
    SYSCTL0->DSPSTALL = 0x0;
}

/*!
 * @brief Stop DSP core.
 */
static inline void DSP_Stop(void)
{
    SYSCTL0->DSPSTALL = 0x1;
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_RESET_H_ */
