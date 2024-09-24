/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
/*! @brief DSP driver version 2.0.0. */
#define FSL_DSP_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#if defined(SYSCON0)
#define SYSCON SYSCON0
#elif defined(SYSCON1)
#define SYSCON SYSCON1
#endif
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

/*!
 * @brief Fusion DSP vector table select
 */
typedef enum _dsp_static_vec_sel
{
    kDSP_StatVecSel0 = 0U, /* Vector base 0058_0000h for HiFi1. Primary vector (2402_0000h) for HiFi4. */
    kDSP_StatVecSel1 = 1U, /* Vector base 0060_0000h.  Alternate vector (2010_0000h) for HiFi4. */
} dsp_static_vec_sel_t;

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
    SYSCON->DSPSTALL = 0x0;
}

/*!
 * @brief Stop DSP core.
 */
static inline void DSP_Stop(void)
{
    SYSCON->DSPSTALL = 0x1;
}

/*!
 * @brief Set DSP static vector table remap.
 *
 * @param statVecSel static vector base address selection
 * @param remap static vector remap, For HiFi1 when statVecSel = 0, the valid range is 0~0x3FF, when statVecSel=1, the
 * valid range is 0~0x7FF. For HiFi4, the bits value will remap ARADDR[22:10] when [STATVECSELECT] is high and ARADDR
 * hits 1 KB from 2010_0000h.
 */
static inline void DSP_SetVecRemap(dsp_static_vec_sel_t statVecSel, uint32_t remap)
{
#if defined(SYSCON1)
    SYSCON1->DSP_VECT_REMAP =
        SYSCON1_DSP_VECT_REMAP_STATVECSELECT(statVecSel) | SYSCON1_DSP_VECT_REMAP_DSP_VECT_REMAP(remap);
#else
    SYSCON0->DSP_VECT_REMAP =
        SYSCON0_DSP_VECT_REMAP_STATVECSELECT(statVecSel) | SYSCON0_DSP_VECT_REMAP_DSP_VECT_REMAP(remap);
#endif
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_RESET_H_ */
