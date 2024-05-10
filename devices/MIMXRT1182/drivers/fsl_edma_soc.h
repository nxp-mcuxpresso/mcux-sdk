/*
 * Copyright 2022-2023 NXP
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
/*! @brief Driver version 2.1.0. */
#define FSL_EDMA_SOC_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/*!@brief DMA IP version */
#define FSL_EDMA_SOC_IP_DMA3 (1)
#define FSL_EDMA_SOC_IP_DMA4 (1)

/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA3, DMA4     \
    }

#define EDMA_CHN_IRQS                                                                                             \
    {                                                                                                             \
        {DMA3_CH0_IRQn,                                                                                           \
         DMA3_CH1_IRQn,                                                                                           \
         DMA3_CH2_IRQn,                                                                                           \
         DMA3_CH3_IRQn,                                                                                           \
         DMA3_CH4_IRQn,                                                                                           \
         DMA3_CH5_IRQn,                                                                                           \
         DMA3_CH6_IRQn,                                                                                           \
         DMA3_CH7_IRQn,                                                                                           \
         DMA3_CH8_IRQn,                                                                                           \
         DMA3_CH9_IRQn,                                                                                           \
         DMA3_CH10_IRQn,                                                                                          \
         DMA3_CH11_IRQn,                                                                                          \
         DMA3_CH12_IRQn,                                                                                          \
         DMA3_CH13_IRQn,                                                                                          \
         DMA3_CH14_IRQn,                                                                                          \
         DMA3_CH15_IRQn,                                                                                          \
         DMA3_CH16_IRQn,                                                                                          \
         DMA3_CH17_IRQn,                                                                                          \
         DMA3_CH18_IRQn,                                                                                          \
         DMA3_CH19_IRQn,                                                                                          \
         DMA3_CH20_IRQn,                                                                                          \
         DMA3_CH21_IRQn,                                                                                          \
         DMA3_CH22_IRQn,                                                                                          \
         DMA3_CH23_IRQn,                                                                                          \
         DMA3_CH24_IRQn,                                                                                          \
         DMA3_CH25_IRQn,                                                                                          \
         DMA3_CH26_IRQn,                                                                                          \
         DMA3_CH27_IRQn,                                                                                          \
         DMA3_CH28_IRQn,                                                                                \
         DMA3_CH29_IRQn,                                                                                \
         DMA3_CH30_IRQn,                                                                                \
         DMA3_CH31_IRQn},                                                                               \
        {                                                                                                         \
            DMA4_CH0_CH1_CH32_CH33_IRQn, DMA4_CH0_CH1_CH32_CH33_IRQn, DMA4_CH2_CH3_CH34_CH35_IRQn, DMA4_CH2_CH3_CH34_CH35_IRQn, DMA4_CH4_CH5_CH36_CH37_IRQn,        \
                DMA4_CH4_CH5_CH36_CH37_IRQn, DMA4_CH6_CH7_CH38_CH39_IRQn, DMA4_CH6_CH7_CH38_CH39_IRQn, DMA4_CH8_CH9_CH40_CH41_IRQn, DMA4_CH8_CH9_CH40_CH41_IRQn,    \
                DMA4_CH10_CH11_CH42_CH43_IRQn, DMA4_CH10_CH11_CH42_CH43_IRQn, DMA4_CH12_CH13_CH44_CH45_IRQn, DMA4_CH12_CH13_CH44_CH45_IRQn,               \
                DMA4_CH14_CH15_CH46_CH47_IRQn, DMA4_CH14_CH15_CH46_CH47_IRQn, DMA4_CH16_CH17_CH48_CH49_IRQn, DMA4_CH16_CH17_CH48_CH49_IRQn,               \
                DMA4_CH18_CH19_CH50_CH51_IRQn, DMA4_CH18_CH19_CH50_CH51_IRQn, DMA4_CH20_CH21_CH52_CH53_IRQn, DMA4_CH20_CH21_CH52_CH53_IRQn,               \
                DMA4_CH22_CH23_CH54_CH55_IRQn, DMA4_CH22_CH23_CH54_CH55_IRQn, DMA4_CH24_CH25_CH56_CH57_IRQn, DMA4_CH24_CH25_CH56_CH57_IRQn,               \
                DMA4_CH26_CH27_CH58_CH59_IRQn, DMA4_CH26_CH27_CH58_CH59_IRQn, DMA4_CH28_CH29_CH60_CH61_IRQn, DMA4_CH28_CH29_CH60_CH61_IRQn,               \
                DMA4_CH30_CH31_CH62_CH63_IRQn, DMA4_CH30_CH31_CH62_CH63_IRQn, DMA4_CH0_CH1_CH32_CH33_IRQn, DMA4_CH0_CH1_CH32_CH33_IRQn,               \
                DMA4_CH2_CH3_CH34_CH35_IRQn, DMA4_CH2_CH3_CH34_CH35_IRQn, DMA4_CH4_CH5_CH36_CH37_IRQn, DMA4_CH4_CH5_CH36_CH37_IRQn,               \
                DMA4_CH6_CH7_CH38_CH39_IRQn, DMA4_CH6_CH7_CH38_CH39_IRQn, DMA4_CH8_CH9_CH40_CH41_IRQn, DMA4_CH8_CH9_CH40_CH41_IRQn,               \
                DMA4_CH10_CH11_CH42_CH43_IRQn, DMA4_CH10_CH11_CH42_CH43_IRQn, DMA4_CH12_CH13_CH44_CH45_IRQn, DMA4_CH12_CH13_CH44_CH45_IRQn,               \
                DMA4_CH14_CH15_CH46_CH47_IRQn, DMA4_CH14_CH15_CH46_CH47_IRQn, DMA4_CH16_CH17_CH48_CH49_IRQn, DMA4_CH16_CH17_CH48_CH49_IRQn, \
                DMA4_CH18_CH19_CH50_CH51_IRQn, DMA4_CH18_CH19_CH50_CH51_IRQn, DMA4_CH20_CH21_CH52_CH53_IRQn,                 \
                DMA4_CH20_CH21_CH52_CH53_IRQn, DMA4_CH22_CH23_CH54_CH55_IRQn, DMA4_CH22_CH23_CH54_CH55_IRQn,                   \
                DMA4_CH24_CH25_CH56_CH57_IRQn, DMA4_CH24_CH25_CH56_CH57_IRQn, DMA4_CH26_CH27_CH58_CH59_IRQn,           \
                DMA4_CH26_CH27_CH58_CH59_IRQn, DMA4_CH28_CH29_CH60_CH61_IRQn, DMA4_CH28_CH29_CH60_CH61_IRQn,         \
                DMA4_CH30_CH31_CH62_CH63_IRQn, DMA4_CH30_CH31_CH62_CH63_IRQn                                        \
        }                                                                                                         \
    }

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
