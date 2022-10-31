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
        {DMA_0_IRQn,  DMA_1_IRQn,  DMA_2_IRQn,  DMA_3_IRQn,  DMA_4_IRQn,  DMA_5_IRQn,  DMA_6_IRQn,  DMA_7_IRQn,       \
         DMA_8_IRQn,  DMA_9_IRQn,  DMA_10_IRQn, DMA_11_IRQn, DMA_12_IRQn, DMA_13_IRQn, DMA_14_IRQn, DMA_15_IRQn,      \
         DMA_16_IRQn, DMA_17_IRQn, DMA_18_IRQn, DMA_19_IRQn, DMA_20_IRQn, DMA_21_IRQn, DMA_22_IRQn, DMA_23_IRQn,      \
         DMA_24_IRQn, DMA_25_IRQn, DMA_26_IRQn, DMA_27_IRQn, DMA_28_IRQn, DMA_29_IRQn, DMA_30_IRQn},                  \
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
                DMA4_60_61_IRQn, DMA4_62_63_IRQn, DMA4_62_63_IRQn                                                     \
        }                                                                                                             \
    }

#ifndef DMA_CH_MUX_SRC_MASK
#define DMA_CH_MUX_SRC_MASK  (0x7FU)
#define DMA_CH_MUX_SRC_SHIFT (0U)
#define DMA_CH_MUX_SRC(x)    (((uint32_t)(((uint32_t)(x)) << DMA_CH_MUX_SRC_SHIFT)) & DMA_CH_MUX_SRC_MASK)
#endif

/*!@brief dma request source */
typedef enum _dma_request_source
{
    kDmaRequestDisabled                 = 0U,           /**< DSisabled*/
    kDma3RequestMuxCAN1                 = 1U | 0x100U,  /**< CAN1 */
    kDma3RequestMuxGPIO1Request0        = 3U | 0x100U,  /**< GPIO1 channel 0 */
    kDma3RequestMuxGPIO1Request1        = 4U | 0x100U,  /**< GPIO1 channel 1 */
    kDma3RequestMuxI3C1ToBusRequest     = 5U | 0x100U,  /**< I3C1 To-bus Request */
    kDma3RequestMuxI3C1FromBusRequest   = 6U | 0x100U,  /**< I3C1 From-bus Request */
    kDma3RequestMuxLPI2C1Tx             = 7U | 0x100U,  /**< LPI2C1 */
    kDma3RequestMuxLPI2C1Rx             = 8U | 0x100U,  /**< LPI2C1 */
    kDma3RequestMuxLPI2C2Tx             = 9U | 0x100U,  /**< LPI2C2 */
    kDma3RequestMuxLPI2C2Rx             = 10U | 0x100U, /**< LPI2C2 */
    kDma3RequestMuxLPSPI1Tx             = 11U | 0x100U, /**< LPSPI1 Transmit */
    kDma3RequestMuxLPSPI1Rx             = 12U | 0x100U, /**< LPSPI1 Receive */
    kDma3RequestMuxLPSPI2Tx             = 13U | 0x100U, /**< LPSPI2 Transmit */
    kDma3RequestMuxLPSPI2Rx             = 14U | 0x100U, /**< LPSPI2 Receive */
    kDma3RequestMuxLPTMR1Request        = 15U | 0x100U, /**< LPTMR1 Request */
    kDma3RequestMuxLPUART1Tx            = 16U | 0x100U, /**< LPUART1 Transmit */
    kDma3RequestMuxLPUART1Rx            = 17U | 0x100U, /**< LPUART1 Receive */
    kDma3RequestMuxLPUART2Tx            = 18U | 0x100U, /**< LPUART2 Transmit */
    kDma3RequestMuxLPUART2Rx            = 19U | 0x100U, /**< LPUART2 Receive */
    kDma3RequestMuxEdgelockRequest      = 20U | 0x100U, /**< Edgelock enclave DMA Request */
    kDma3RequestMuxSai1Tx               = 21U | 0x100U, /**< SAI1 Transmit */
    kDma3RequestMuxSai1Rx               = 22U | 0x100U, /**< SAI1 Receive */
    kDma3RequestMuxTPM1Request0Request2 = 23U | 0x100U, /**< TPM1 request 0 and request 2 */
    kDma3RequestMuxTPM1Request1Request3 = 24U | 0x100U, /**< TPM1 request 1 and request 3 */
    kDma3RequestMuxTPM1OverflowRequest  = 25U | 0x100U, /**< TPM1 Overflow request */
    kDma3RequestMuxTPM2Request0Request2 = 26U | 0x100U, /**< TPM2 request 0 and request 2 */
    kDma3RequestMuxTPM2Request1Request3 = 27U | 0x100U, /**< TPM2 request 1 and request 3 */
    kDma3RequestMuxTPM2OverflowRequest  = 28U | 0x100U, /**< TPM2 Overflow request */
    kDma3RequestMuxPDMRequest           = 29U | 0x100U, /**< PDM */
    kDma3RequestMuxADC1Request          = 30U | 0x100U, /**< ADC1 */
    kDma4RequestMuxCAN2                 = 1U | 0x200U,  /**< CAN2 */
    kDma4RequestMuxGPIO2Request0        = 2U | 0x200U,  /**< GPIO2 channel 0 */
    kDma4RequestMuxGPIO2Request1        = 3U | 0x200U,  /**< GPIO2 channel 1 */
    kDma4RequestMuxGPIO3Request0        = 4U | 0x200U,  /**< GPIO3 channel 0 */
    kDma4RequestMuxGPIO3Request1        = 5U | 0x200U,  /**< GPIO3 channel 1 */
    kDma4RequestMuxI3C2ToBusRequest     = 6U | 0x200U,  /**< I3C2 To-bus Request */
    kDma4RequestMuxI3C2FromBusRequest   = 7U | 0x200U,  /**< I3C2 From-bus Request */
    kDma4RequestMuxLPI2C3Tx             = 8U | 0x200U,  /**< LPI2C3 */
    kDma4RequestMuxLPI2C3Rx             = 9U | 0x200U,  /**< LPI2C3 */
    kDma4RequestMuxLPI2C4Tx             = 10U | 0x200U, /**< LPI2C4 */
    kDma4RequestMuxLPI2C4Rx             = 11U | 0x200U, /**< LPI2C4 */
    kDma4RequestMuxLPSPI3Tx             = 12U | 0x200U, /**< LPSPI3 Transmit */
    kDma4RequestMuxLPSPI3Rx             = 13U | 0x200U, /**< LPSPI3 Receive */
    kDma4RequestMuxLPSPI4Tx             = 14U | 0x200U, /**< LPSPI4 Transmit */
    kDma4RequestMuxLPSPI4Rx             = 15U | 0x200U, /**< LPSPI4 Receive */
    kDma4RequestMuxLPTMR2Request        = 16U | 0x200U, /**< LPTMR2 Request */
    kDma4RequestMuxLPUART3Tx            = 17U | 0x200U, /**< LPUART3 Transmit */
    kDma4RequestMuxLPUART3Rx            = 18U | 0x200U, /**< LPUART3 Receive */
    kDma4RequestMuxLPUART4Tx            = 19U | 0x200U, /**< LPUART4 Transmit */
    kDma4RequestMuxLPUART4Rx            = 20U | 0x200U, /**< LPUART4 Receive */
    kDma4RequestMuxLPUART5Tx            = 21U | 0x200U, /**< LPUART5 Transmit */
    kDma4RequestMuxLPUART5Rx            = 22U | 0x200U, /**< LPUART5 Receive */
    kDma4RequestMuxLPUART6Tx            = 23U | 0x200U, /**< LPUART6 Transmit */
    kDma4RequestMuxLPUART6Rx            = 24U | 0x200U, /**< LPUART6 Receive */
    kDma4RequestMuxTPM3Request0Request2 = 25U | 0x200U, /**< TPM3 request 0 and request 2 */
    kDma4RequestMuxTPM3Request1Request3 = 26U | 0x200U, /**< TPM3 request 1 and request 3 */
    kDma4RequestMuxTPM3OverflowRequest  = 27U | 0x200U, /**< TPM3 Overflow request */
    kDma4RequestMuxTPM4Request0Request2 = 28U | 0x200U, /**< TPM4 request 0 and request 2 */
    kDma4RequestMuxTPM4Request1Request3 = 29U | 0x200U, /**< TPM4 request 1 and request 3 */
    kDma4RequestMuxTPM4OverflowRequest  = 30U | 0x200U, /**< TPM4 Overflow request */
    kDma4RequestMuxTPM5Request0Request2 = 31U | 0x200U, /**< TPM5 request 0 and request 2 */
    kDma4RequestMuxTPM5Request1Request3 = 32U | 0x200U, /**< TPM5 request 1 and request 3 */
    kDma4RequestMuxTPM5OverflowRequest  = 33U | 0x200U, /**< TPM5 Overflow request */
    kDma4RequestMuxTPM6Request0Request2 = 34U | 0x200U, /**< TPM6 request 0 and request 2 */
    kDma4RequestMuxTPM6Request1Request3 = 35U | 0x200U, /**< TPM6 request 1 and request 3 */
    kDma4RequestMuxTPM6OverflowRequest  = 36U | 0x200U, /**< TPM6 Overflow request */
    kDma4RequestMuxFlexIO1Request0      = 37U | 0x200U, /**< FlexIO1 Request0 */
    kDma4RequestMuxFlexIO1Request1      = 38U | 0x200U, /**< FlexIO1 Request1 */
    kDma4RequestMuxFlexIO1Request2      = 39U | 0x200U, /**< FlexIO1 Request2 */
    kDma4RequestMuxFlexIO1Request3      = 40U | 0x200U, /**< FlexIO1 Request3 */
    kDma4RequestMuxFlexIO1Request4      = 41U | 0x200U, /**< FlexIO1 Request4 */
    kDma4RequestMuxFlexIO1Request5      = 42U | 0x200U, /**< FlexIO1 Request5 */
    kDma4RequestMuxFlexIO1Request6      = 43U | 0x200U, /**< FlexIO1 Request6 */
    kDma4RequestMuxFlexIO1Request7      = 44U | 0x200U, /**< FlexIO1 Request7 */
    kDma4RequestMuxFlexIO2Request0      = 45U | 0x200U, /**< FlexIO2 Request0 */
    kDma4RequestMuxFlexIO2Request1      = 46U | 0x200U, /**< FlexIO2 Request1 */
    kDma4RequestMuxFlexIO2Request2      = 47U | 0x200U, /**< FlexIO2 Request2 */
    kDma4RequestMuxFlexIO2Request3      = 48U | 0x200U, /**< FlexIO2 Request3 */
    kDma4RequestMuxFlexIO2Request4      = 49U | 0x200U, /**< FlexIO2 Request4 */
    kDma4RequestMuxFlexIO2Request5      = 50U | 0x200U, /**< FlexIO2 Request5 */
    kDma4RequestMuxFlexIO2Request6      = 51U | 0x200U, /**< FlexIO2 Request6 */
    kDma4RequestMuxFlexIO2Request7      = 52U | 0x200U, /**< FlexIO2 Request7 */
    kDma4RequestMuxFlexSPI1Tx           = 53U | 0x200U, /**< FlexSPI1 Transmit */
    kDma4RequestMuxSai2Tx               = 58U | 0x200U, /**< SAI2 Transmit */
    kDma4RequestMuxSai2Rx               = 59U | 0x200U, /**< SAI2 Receive */
    kDma4RequestMuxSai3Tx               = 60U | 0x200U, /**< SAI3 Transmit */
    kDma4RequestMuxSai3Rx               = 61U | 0x200U, /**< SAI3 Receive */
    kDma4RequestMuxGPIO4Request0        = 62U | 0x200U, /**< GPIO4 channel 0 */
    kDma4RequestMuxGPIO4Request1        = 63U | 0x200U, /**< GPIO4 channel 1 */
    kDma4RequestMuxSPDIFRequest         = 65U | 0x200U, /**< SPDIF */
    kDma4RequestMuxSPDIFRequest1        = 66U | 0x200U, /**< SPDIF */
    kDma4RequestMuxENETRequest          = 67U | 0x200U, /**< ENET */
    kDma4RequestMuxENETRequest1         = 68U | 0x200U, /**< ENET */
    kDma4RequestMuxENETRequest2         = 69U | 0x200U, /**< ENET */
    kDma4RequestMuxENETRequest3         = 70U | 0x200U, /**< ENET */
    kDma4RequestMuxLPI2C5Tx             = 71U | 0x200U, /**< LPI2C5 */
    kDma4RequestMuxLPI2C5Rx             = 72U | 0x200U, /**< LPI2C5 */
    kDma4RequestMuxLPI2C6Tx             = 73U | 0x200U, /**< LPI2C6 */
    kDma4RequestMuxLPI2C6Rx             = 74U | 0x200U, /**< LPI2C6 */
    kDma4RequestMuxLPI2C7Tx             = 75U | 0x200U, /**< LPI2C7 */
    kDma4RequestMuxLPI2C7Rx             = 76U | 0x200U, /**< LPI2C7 */
    kDma4RequestMuxLPI2C8Tx             = 77U | 0x200U, /**< LPI2C8 */
    kDma4RequestMuxLPI2C8Rx             = 78U | 0x200U, /**< LPI2C8 */
    kDma4RequestMuxLPSPI5Tx             = 79U | 0x200U, /**< LPSPI5 Transmit */
    kDma4RequestMuxLPSPI5Rx             = 80U | 0x200U, /**< LPSPI5 Receive */
    kDma4RequestMuxLPSPI6Tx             = 81U | 0x200U, /**< LPSPI6 Transmit */
    kDma4RequestMuxLPSPI6Rx             = 82U | 0x200U, /**< LPSPI6 Receive */
    kDma4RequestMuxLPSPI7Tx             = 83U | 0x200U, /**< LPSPI7 Transmit */
    kDma4RequestMuxLPSPI7Rx             = 84U | 0x200U, /**< LPSPI7 Receive */
    kDma4RequestMuxLPSPI8Tx             = 85U | 0x200U, /**< LPSPI8 Transmit */
    kDma4RequestMuxLPSPI8Rx             = 86U | 0x200U, /**< LPSPI8 Receive */
    kDma4RequestMuxLPUART7Tx            = 87U | 0x200U, /**< LPUART7 Transmit */
    kDma4RequestMuxLPUART7Rx            = 88U | 0x200U, /**< LPUART7 Receive */
    kDma4RequestMuxLPUART8Tx            = 89U | 0x200U, /**< LPUART8 Transmit */
    kDma4RequestMuxLPUART8Rx            = 90U | 0x200U, /**< LPUART8 Receive */
    kDma4RequestMuxENET_QOSRequest      = 91U | 0x200U, /**< ENET_QOS */
    kDma4RequestMuxENET_QOSRequest1     = 92U | 0x200U, /**< ENET_QOS */
    kDma4RequestMuxENET_QOSRequest2     = 93U | 0x200U, /**< ENET_QOS */
    kDma4RequestMuxENET_QOSRequest3     = 94U | 0x200U, /**< ENET_QOS */
} dma_request_source_t;

/*!< Verify dma base and request source */
#define EDMA_CHANNEL_HAS_REQUEST_SOURCE(base, source) ((base) == DMA3 ? ((source)&0x100U) : ((source)&0x200U))

#define FSL_FEATURE_EDMA_MODULE_CHANNEL(base)                    (base == DMA3 ? 31U : 64U)
#define FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL                      (64)
#define FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION        (1)
#define FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE                (0)
#define FSL_FEATURE_EDMA_MODULE_COUNT                            (2)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG                      (1)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE                   (1)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE                 (1)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MEMRORY_ATTRIBUTE           (1)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION              (1)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_MATTR(base)              (base == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_SIGN_EXTENSION(base)     (base == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_SWAP(base)               (base == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_INSTR(base)              (base == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER              (1)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_128_BYTES_TRANSFER(base) (base == DMA3 ? 0U : 1U)

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
