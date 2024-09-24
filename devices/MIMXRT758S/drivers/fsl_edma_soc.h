/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_EDMA_SOC_H_
#define FSL_EDMA_SOC_H_

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
/*! @brief Driver version 1.0.0. */
#define FSL_EDMA_SOC_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*!@brief DMA IP version */
#define FSL_EDMA_SOC_IP_DMA3 (1)
#define FSL_EDMA_SOC_IP_DMA4 (0)

#if defined(MIMXRT798S_hifi4_SERIES) || defined(MIMXRT798S_cm33_core0_SERIES) || \
    defined(MIMXRT758S_cm33_core0_SERIES) || defined(MIMXRT735S_cm33_core0_SERIES)
/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA0, DMA1     \
    }

#define EDMA_CHN_IRQS                                                                                             \
    {                                                                                                             \
        {EDMA0_CH0_IRQn,  EDMA0_CH1_IRQn,  EDMA0_CH2_IRQn,  EDMA0_CH3_IRQn, EDMA0_CH4_IRQn,  EDMA0_CH5_IRQn,      \
         EDMA0_CH6_IRQn,  EDMA0_CH7_IRQn,  EDMA0_CH8_IRQn,  EDMA0_CH9_IRQn, EDMA0_CH10_IRQn, EDMA0_CH11_IRQn,     \
         EDMA0_CH12_IRQn, EDMA0_CH13_IRQn, EDMA0_CH14_IRQn, EDMA0_CH15_IRQn},                                     \
        {                                                                                                         \
            EDMA1_CH0_IRQn, EDMA1_CH1_IRQn, EDMA1_CH2_IRQn, EDMA1_CH3_IRQn, EDMA1_CH4_IRQn, EDMA1_CH5_IRQn,       \
                EDMA1_CH6_IRQn, EDMA1_CH7_IRQn, EDMA1_CH8_IRQn, EDMA1_CH9_IRQn, EDMA1_CH10_IRQn, EDMA1_CH11_IRQn, \
                EDMA1_CH12_IRQn, EDMA1_CH13_IRQn, EDMA1_CH14_IRQn, EDMA1_CH15_IRQn                                \
        }                                                                                                         \
    }

#elif defined(MIMXRT798S_hifi1_SERIES) || defined(MIMXRT798S_cm33_core1_SERIES) || \
    defined(MIMXRT758S_cm33_core1_SERIES) || defined(MIMXRT735S_cm33_core1_SERIES)
/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA2, DMA3     \
    }

#define EDMA_CHN_IRQS                                                                                       \
    {                                                                                                       \
        {EDMA2_CH0_IRQn, EDMA2_CH1_IRQn, EDMA2_CH2_IRQn, EDMA2_CH3_IRQn,                                    \
         EDMA2_CH4_IRQn, EDMA2_CH5_IRQn, EDMA2_CH6_IRQn, EDMA2_CH7_IRQn},                                   \
        {                                                                                                   \
            EDMA3_CH0_IRQn, EDMA3_CH1_IRQn, EDMA3_CH2_IRQn, EDMA3_CH3_IRQn, EDMA3_CH4_IRQn, EDMA3_CH5_IRQn, \
                EDMA3_CH6_IRQn, EDMA3_CH7_IRQn                                                              \
        }                                                                                                   \
    }

#else
#error "Unsupported core."
#endif

/*!@brief EDMA base address convert macro */
#define EDMA_CHANNEL_OFFSET           0x1000U
#define EDMA_CHANNEL_ARRAY_STEP(base) (0x1000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Enable the eDMA request.
 *
 * This function enables the eDMA request controlled by SYSCON.
 *
 * @param base eDMA peripheral base address.
 * @param requestSource eDMA request source, see "dma_request_source_t".
 */
void EDMA_EnableRequest(DMA_Type *base, dma_request_source_t requestSource);

/*!
 * @brief Disable the eDMA request.
 *
 * This function disables the eDMA request controlled by SYSCON.
 *
 * @param base eDMA peripheral base address.
 * @param requestSource eDMA request source, see "dma_request_source_t".
 */
void EDMA_DisableRequest(DMA_Type *base, dma_request_source_t requestSource);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* FSL_EDMA_SOC_H_ */
