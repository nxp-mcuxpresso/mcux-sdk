/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_EDMA_SOC_H_
#define _FSL_EDMA_SOC_H_

#include "fsl_common.h"

/*!
 * @addtogroup edma_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.0. */
#define FSL_EDMA_SOC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!@brief DMA IP version */
#define FSL_EDMA_SOC_IP_DMA3 (1)
#define FSL_EDMA_SOC_IP_DMA4 (1)

/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA3, DMA4     \
    }

#define EDMA_CHN_IRQS                                                                                                 \
    {                                                                                                                 \
        {                                                                                                             \
            DMA3_0_IRQn,  DMA3_1_IRQn,  DMA3_2_IRQn,  DMA3_3_IRQn,  DMA3_4_IRQn,  DMA3_5_IRQn,  DMA3_6_IRQn,          \
            DMA3_7_IRQn,  DMA3_8_IRQn,  DMA3_9_IRQn,  DMA3_10_IRQn, DMA3_11_IRQn, DMA3_12_IRQn, DMA3_13_IRQn,         \
            DMA3_14_IRQn, DMA3_15_IRQn, DMA3_16_IRQn, DMA3_17_IRQn, DMA3_18_IRQn, DMA3_19_IRQn, DMA3_20_IRQn,         \
            DMA3_21_IRQn, DMA3_22_IRQn, DMA3_23_IRQn, DMA3_24_IRQn, DMA3_25_IRQn, DMA3_26_IRQn, DMA3_27_IRQn,         \
            DMA3_28_IRQn, DMA3_29_IRQn, DMA3_30_IRQn,                                                                 \
        },                                                                                                            \
        {                                                                                                             \
            DMA4_0_1_IRQn, DMA4_0_1_IRQn, DMA4_2_3_IRQn, DMA4_2_3_IRQn, DMA4_4_5_IRQn, DMA4_4_5_IRQn, DMA4_6_7_IRQn,  \
                DMA4_6_7_IRQn, DMA4_8_9_IRQn, DMA4_8_9_IRQn, DMA4_10_11_IRQn, DMA4_10_11_IRQn, DMA4_12_13_IRQn,       \
                DMA4_12_13_IRQn, DMA4_14_15_IRQn, DMA4_14_15_IRQn, DMA4_16_17_IRQn, DMA4_16_17_IRQn, DMA4_18_19_IRQn, \
                DMA4_18_19_IRQn, DMA4_20_21_IRQn, DMA4_20_21_IRQn, DMA4_22_23_IRQn, DMA4_22_23_IRQn, DMA4_24_25_IRQn, \
                DMA4_24_25_IRQn, DMA4_26_27_IRQn, DMA4_26_27_IRQn, DMA4_28_29_IRQn, DMA4_28_29_IRQn, DMA4_30_31_IRQn, \
                DMA4_30_31_IRQn, DMA4_32_33_IRQn, DMA4_32_33_IRQn, DMA4_34_35_IRQn, DMA4_34_35_IRQn, DMA4_36_37_IRQn, \
                DMA4_36_37_IRQn, DMA4_38_39_IRQn, DMA4_38_39_IRQn, DMA4_40_41_IRQn, DMA4_40_41_IRQn, DMA4_42_43_IRQn, \
                DMA4_42_43_IRQn, DMA4_44_45_IRQn, DMA4_44_45_IRQn, DMA4_46_47_IRQn, DMA4_46_47_IRQn, DMA4_48_49_IRQn, \
                DMA4_48_49_IRQn, DMA4_50_51_IRQn, DMA4_50_51_IRQn, DMA4_52_53_IRQn, DMA4_52_53_IRQn, DMA4_54_55_IRQn, \
                DMA4_54_55_IRQn, DMA4_56_57_IRQn, DMA4_56_57_IRQn, DMA4_58_59_IRQn, DMA4_58_59_IRQn, DMA4_60_61_IRQn, \
                DMA4_60_61_IRQn, DMA4_62_63_IRQn, DMA4_62_63_IRQn,                                                    \
        }                                                                                                             \
    }

/* Channel mux feature marked as false for DMA3 driver. Marked true here for EDMA4 driver. */
#undef FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MUX (1)

/*!< Verify dma base and request source */
#define EDMA_CHANNEL_HAS_REQUEST_SOURCE(base, source) ((base) == DMA3 ? ((source)&0x100U) : ((source)&0x200U))
/*!@brief EDMA base address convert macro */
#define EDMA_CHANNEL_OFFSET           0x10000U
#define EDMA_CHANNEL_ARRAY_STEP(base) ((base) == DMA3 ? 0x10000U : 0x8000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_EDMA_SOC_H_ */
