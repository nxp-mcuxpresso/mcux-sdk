/*
 * Copyright 2021, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FUSION_H_
#define _FSL_FUSION_H_

#include "fsl_common.h"

/*!
 * @addtogroup fusion
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief fusion driver version 2.0.0. */
#define FSL_FUSION_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
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
 * @brief Set Fusion DSP vector table remap.
 *
 * @param remap vector remap, valid value from 0x0U to 0x1FFFU
 */
static inline void Fusion_SetVecRemap(uint32_t remap)
{
    SIM_SEC->FUSION_GPR0 &= ~SIM_SEC_FUSION_GPR0_VECTOR_REMAP_MASK;
    SIM_SEC->FUSION_GPR0 |= SIM_SEC_FUSION_GPR0_VECTOR_REMAP(remap);
}

/*!
 * @brief Copy DSP image to destination address.
 *
 * Copy DSP image from source address to destination address with given size.
 *
 * @param dspCopyImage Structure contains information for DSP copy image to destination address.
 */
void DSP_CopyImage(dsp_copy_image_t *dspCopyImage);

/*!
 * @brief Initializing Fusion core.
 *
 * Power up Fusion
 * Put Fusion core in reset
 * Enable Fusion clocks
 * Enable SSRAM access
 * Reset Fusion Debug logic
 */
void Fusion_Init(void);

/*!
 * @brief Deinitializing Fusion core.
 *
 * Stop Fusion core
 * Disable Fusion clocks
 * Disable SSRAM access
 * Poweroff Fusion
 */
void Fusion_Deinit(void);

/*!
 * @brief Start Fusion core.
 */
static inline void Fusion_Start(void)
{
    SIM_SEC_Type *base = SIM_SEC;

    base->SYSCTRL0 &= ~SIM_SEC_SYSCTRL0_FUSION_DSP_STALL_MASK;
}

/*!
 * @brief Stop Fusion core.
 */
static inline void Fusion_Stop(void)
{
    SIM_SEC_Type *base = SIM_SEC;

    base->SYSCTRL0 |= SIM_SEC_SYSCTRL0_FUSION_DSP_STALL_MASK;
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_FUSION_H_ */
