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
#define FSL_EDMA_SOC_IP_DMA5 (1)

/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA3, EDMA5_2           \
    }

#define EDMA_CHN_IRQS                                                                                               \
    {                                                                                                               \
        {                                                                                                           \
            DMA3_0_IRQn, DMA3_1_IRQn, DMA3_2_IRQn, DMA3_3_IRQn, DMA3_4_IRQn, DMA3_5_IRQn, DMA3_6_IRQn, DMA3_7_IRQn, \
                DMA3_8_IRQn, DMA3_9_IRQn, DMA3_10_IRQn, DMA3_11_IRQn, DMA3_12_IRQn, DMA3_13_IRQn, DMA3_14_IRQn,     \
                DMA3_15_IRQn, DMA3_16_IRQn, DMA3_17_IRQn, DMA3_18_IRQn, DMA3_19_IRQn, DMA3_20_IRQn, DMA3_21_IRQn,   \
                DMA3_22_IRQn, DMA3_23_IRQn, DMA3_24_IRQn, DMA3_25_IRQn, DMA3_26_IRQn, DMA3_27_IRQn, DMA3_28_IRQn,   \
                DMA3_29_IRQn, DMA3_30_IRQn,                                                                         \
        },                                                                                                           \
        {                                                                                                             \
            DMA5_2_0_1_IRQn, DMA5_2_0_1_IRQn, DMA5_2_2_3_IRQn, DMA5_2_2_3_IRQn, DMA5_2_4_5_IRQn, DMA5_2_4_5_IRQn, DMA5_2_6_7_IRQn,  \
                DMA5_2_6_7_IRQn, DMA5_2_8_9_IRQn, DMA5_2_8_9_IRQn, DMA5_2_10_11_IRQn, DMA5_2_10_11_IRQn, DMA5_2_12_13_IRQn,       \
                DMA5_2_12_13_IRQn, DMA5_2_14_15_IRQn, DMA5_2_14_15_IRQn, DMA5_2_16_17_IRQn, DMA5_2_16_17_IRQn, DMA5_2_18_19_IRQn, \
                DMA5_2_18_19_IRQn, DMA5_2_20_21_IRQn, DMA5_2_20_21_IRQn, DMA5_2_22_23_IRQn, DMA5_2_22_23_IRQn, DMA5_2_24_25_IRQn, \
                DMA5_2_24_25_IRQn, DMA5_2_26_27_IRQn, DMA5_2_26_27_IRQn, DMA5_2_28_29_IRQn, DMA5_2_28_29_IRQn, DMA5_2_30_31_IRQn, \
                DMA5_2_30_31_IRQn, DMA5_2_32_33_IRQn, DMA5_2_32_33_IRQn, DMA5_2_34_35_IRQn, DMA5_2_34_35_IRQn, DMA5_2_36_37_IRQn, \
                DMA5_2_36_37_IRQn, DMA5_2_38_39_IRQn, DMA5_2_38_39_IRQn, DMA5_2_40_41_IRQn, DMA5_2_40_41_IRQn, DMA5_2_42_43_IRQn, \
                DMA5_2_42_43_IRQn, DMA5_2_44_45_IRQn, DMA5_2_44_45_IRQn, DMA5_2_46_47_IRQn, DMA5_2_46_47_IRQn, DMA5_2_48_49_IRQn, \
                DMA5_2_48_49_IRQn, DMA5_2_50_51_IRQn, DMA5_2_50_51_IRQn, DMA5_2_52_53_IRQn, DMA5_2_52_53_IRQn, DMA5_2_54_55_IRQn, \
                DMA5_2_54_55_IRQn, DMA5_2_56_57_IRQn, DMA5_2_56_57_IRQn, DMA5_2_58_59_IRQn, DMA5_2_58_59_IRQn, DMA5_2_60_61_IRQn, \
                DMA5_2_60_61_IRQn, DMA5_2_62_63_IRQn, DMA5_2_62_63_IRQn,                                                    \
        }                                                                                                             \
    }

/*!@brief dma request source */
typedef enum _dma_request_source
{
    DmaRequestDisabled                 = 0U,           /**< DSisabled*/
    Dma3RequestMuxCAN1                 = 1U,  /**< CAN1 */
    Dma3RequestMuxLPTMR1Request        = 2U,  /**< LPTMR1 Request */
    Dma3RequestMuxELERequest           = 3U,  /**< ELE Request */
    Dma3RequestMuxTPM1OverflowRequest  = 4U,  /**< TPM1 Overflow Request */
    Dma3RequestMuxTPM2OverflowRequest  = 5U,  /**< TPM2 Overflow Request */
    Dma3RequestMuxPDMRequest           = 6U,  /**< PDM */
    Dma3RequestMuxADC1Request          = 7U,  /**< ADC1 */
    Dma3RequestMuxGPIO1Request0        = 8U,  /**< GPIO1 channel 0 */
    Dma3RequestMuxGPIO1Request1        = 9U,  /**< GPIO1 channel 1 */
    Dma3RequestMuxI3C1ToBusRequest     = 10U, /**< I3C1 To-bus Request */
    Dma3RequestMuxI3C1FromBusRequest   = 11U, /**< I3C1 From-bus Request */
    Dma3RequestMuxLPI2C1Tx             = 12U, /**< LPI2C1 */
    Dma3RequestMuxLPI2C1Rx             = 13U, /**< LPI2C1 */
    Dma3RequestMuxLPI2C2Tx             = 14U, /**< LPI2C2 */
    Dma3RequestMuxLPI2C2Rx             = 15U, /**< LPI2C2 */
    Dma3RequestMuxLPSPI1Tx             = 16U, /**< LPSPI1 Transmit */
    Dma3RequestMuxLPSPI1Rx             = 17U, /**< LPSPI1 Receive */
    Dma3RequestMuxLPSPI2Tx             = 18U, /**< LPSPI2 Transmit */
    Dma3RequestMuxLPSPI2Rx             = 19U, /**< LPSPI2 Receive */
    Dma3RequestMuxLPUART1Tx            = 20U, /**< LPUART1 Transmit */
    Dma3RequestMuxLPUART1Rx            = 21U, /**< LPUART1 Receive */
    Dma3RequestMuxLPUART2Tx            = 22U, /**< LPUART2 Transmit */
    Dma3RequestMuxLPUART2Rx            = 23U, /**< LPUART2 Receive */
    Dma3RequestMuxSai1Tx               = 24U, /**< SAI1 Transmit */
    Dma3RequestMuxSai1Rx               = 25U, /**< SAI1 Receive */
    Dma3RequestMuxTPM1Request0Request2 = 26U, /**< TPM1 request 0 and request 2 */
    Dma3RequestMuxTPM1Request1Request3 = 27U, /**< TPM1 request 1 and request 3 */
    Dma3RequestMuxTPM2Request0Request2 = 28U, /**< TPM2 request 0 and request 2 */
    Dma3RequestMuxTPM2Request1Request3 = 29U, /**< TPM2 request 1 and request 3 */
    Dma5RequestMuxCAN2                 = 1U | 0x200U,   /**< CAN2 */
    Dma5RequestMuxGPIO2Request0        = 2U | 0x200U,   /**< GPIO2 channel 0 */
    Dma5RequestMuxGPIO2Request1        = 3U | 0x200U,   /**< GPIO2 channel 1 */
    Dma5RequestMuxGPIO3Request0        = 4U | 0x200U,   /**< GPIO3 channel 0 */
    Dma5RequestMuxGPIO3Request1        = 5U | 0x200U,   /**< GPIO3 channel 1 */
    Dma5RequestMuxI3C2ToBusRequest     = 6U | 0x200U,   /**< I3C2 To-bus Request */
    Dma5RequestMuxI3C2FromBusRequest   = 7U | 0x200U,   /**< I3C2 From-bus Request */
    Dma5RequestMuxLPI2C3Tx             = 8U | 0x200U,   /**< LPI2C3 */
    Dma5RequestMuxLPI2C3Rx             = 9U | 0x200U,   /**< LPI2C3 */
    Dma5RequestMuxLPI2C4Tx             = 10U | 0x200U,  /**< LPI2C4 */
    Dma5RequestMuxLPI2C4Rx             = 11U | 0x200U,  /**< LPI2C2 */
    Dma5RequestMuxLPSPI3Tx             = 12U | 0x200U,  /**< LPSPI3 Transmit */
    Dma5RequestMuxLPSPI3Rx             = 13U | 0x200U,  /**< LPSPI3 Receive */
    Dma5RequestMuxLPSPI4Tx             = 14U | 0x200U,  /**< LPSPI4 Transmit */
    Dma5RequestMuxLPSPI4Rx             = 15U | 0x200U,  /**< LPSPI4 Receive */
    Dma5RequestMuxLPTMR2Request        = 16U | 0x200U,  /**< LPTMR2 Request */
    Dma5RequestMuxLPUART3Tx            = 17U | 0x200U,  /**< LPUART3 Transmit */
    Dma5RequestMuxLPUART3Rx            = 18U | 0x200U,  /**< LPUART3 Receive */
    Dma5RequestMuxLPUART4Tx            = 19U | 0x200U,  /**< LPUART4 Transmit */
    Dma5RequestMuxLPUART4Rx            = 20U | 0x200U,  /**< LPUART4 Receive */
    Dma5RequestMuxLPUART5Tx            = 21U | 0x200U,  /**< LPUART5 Transmit */
    Dma5RequestMuxLPUART5Rx            = 22U | 0x200U,  /**< LPUART5 Receive */
    Dma5RequestMuxLPUART6Tx            = 23U | 0x200U,  /**< LPUART6 Transmit */
    Dma5RequestMuxLPUART6Rx            = 24U | 0x200U,  /**< LPUART6 Receive */
    Dma5RequestMuxTPM3Request0Request2 = 25U | 0x200U,  /**< TPM3 request 0 and request 2 */
    Dma5RequestMuxTPM3Request1Request3 = 26U | 0x200U,  /**< TPM3 request 1 and request 3 */
    Dma5RequestMuxTPM3OverflowRequest  = 27U | 0x200U,  /**< TPM3 Overflow request */
    Dma5RequestMuxTPM4Request0Request2 = 28U | 0x200U,  /**< TPM4 request 0 and request 2 */
    Dma5RequestMuxTPM4Request1Request3 = 29U | 0x200U,  /**< TPM4 request 1 and request 3 */
    Dma5RequestMuxTPM4OverflowRequest  = 30U | 0x200U,  /**< TPM4 Overflow request */
    Dma5RequestMuxTPM5Request0Request2 = 31U | 0x200U,  /**< TPM5 request 0 and request 2 */
    Dma5RequestMuxTPM5Request1Request3 = 32U | 0x200U,  /**< TPM5 request 1 and request 3 */
    Dma5RequestMuxTPM5OverflowRequest  = 33U | 0x200U,  /**< TPM5 Overflow request */
    Dma5RequestMuxTPM6Request0Request2 = 34U | 0x200U,  /**< TPM6 request 0 and request 2 */
    Dma5RequestMuxTPM6Request1Request3 = 35U | 0x200U,  /**< TPM6 request 1 and request 3 */
    Dma5RequestMuxTPM6OverflowRequest  = 36U | 0x200U,  /**< TPM6 Overflow request */
    Dma5RequestMuxFlexIO1Request0      = 37U | 0x200U,  /**< FlexIO1 Request0 */
    Dma5RequestMuxFlexIO1Request1      = 38U | 0x200U,  /**< FlexIO1 Request1 */
    Dma5RequestMuxFlexIO1Request2      = 39U | 0x200U,  /**< FlexIO1 Request2 */
    Dma5RequestMuxFlexIO1Request3      = 40U | 0x200U,  /**< FlexIO1 Request3 */
    Dma5RequestMuxFlexIO1Request4      = 41U | 0x200U,  /**< FlexIO1 Request4 */
    Dma5RequestMuxFlexIO1Request5      = 42U | 0x200U,  /**< FlexIO1 Request5 */
    Dma5RequestMuxFlexIO1Request6      = 43U | 0x200U,  /**< FlexIO1 Request6 */
    Dma5RequestMuxFlexIO1Request7      = 44U | 0x200U,  /**< FlexIO1 Request7 */
    Dma5RequestMuxFlexIO2Request0      = 45U | 0x200U,  /**< FlexIO2 Request0 */
    Dma5RequestMuxFlexIO2Request1      = 46U | 0x200U,  /**< FlexIO2 Request1 */
    Dma5RequestMuxFlexIO2Request2      = 47U | 0x200U,  /**< FlexIO2 Request2 */
    Dma5RequestMuxFlexIO2Request3      = 48U | 0x200U,  /**< FlexIO2 Request3 */
    Dma5RequestMuxFlexIO2Request4      = 49U | 0x200U,  /**< FlexIO2 Request4 */
    Dma5RequestMuxFlexIO2Request5      = 50U | 0x200U,  /**< FlexIO2 Request5 */
    Dma5RequestMuxFlexIO2Request6      = 51U | 0x200U,  /**< FlexIO2 Request6 */
    Dma5RequestMuxFlexIO2Request7      = 52U | 0x200U,  /**< FlexIO2 Request7 */
    Dma5RequestMuxFlexSPI1Tx           = 53U | 0x200U,  /**< FlexSPI1 Transmit */
    Dma5RequestMuxFlexSPI1Rx           = 54U | 0x200U,  /**< FlexSPI1 Receive */
    Dma5RequestMuxGPIO5Request0        = 53U | 0x200U,  /**< GPIO5 Request0 */
    Dma5RequestMuxGPIO5Request1        = 54U | 0x200U,  /**< GPIO5 Request1 */
    Dma5RequestMuxCAN3                 = 57U | 0x200U,  /**< CAN3 */
    Dma5RequestMuxSai2Tx               = 58U | 0x200U,  /**< SAI2 Transmit */
    Dma5RequestMuxSai2Rx               = 59U | 0x200U,  /**< SAI2 Receive */
    Dma5RequestMuxSai3Tx               = 60U | 0x200U,  /**< SAI3 Transmit */
    Dma5RequestMuxSai3Rx               = 61U | 0x200U,  /**< SAI3 Receive */
    Dma5RequestMuxGPIO4Request0        = 62U | 0x200U,  /**< GPIO4 Request0 */
    Dma5RequestMuxGPIO4Request1        = 63U | 0x200U,  /**< GPIO4 Request1 */
    Dma5RequestMuxeARCRequest0         = 65U | 0x200U,  /**< eARC enhanced Audio Return Channel */
    Dma5RequestMuxeARCRequest1         = 66U | 0x200U,  /**< eARC enhanced Audio Return Channel */
    Dma5RequestMuxSai4Tx               = 67U | 0x200U,  /**< SAI4 Transmit */
    Dma5RequestMuxSai4Rx               = 68U | 0x200U,  /**< SAI4 Receive */
    Dma5RequestMuxSai5Tx               = 69U | 0x200U,  /**< SAI5 Transmit */
    Dma5RequestMuxSai5Rx               = 70U | 0x200U,  /**< SAI5 Receive */
    Dma5RequestMuxLPI2C5Tx             = 71U | 0x200U,  /**< LPI2C5 */
    Dma5RequestMuxLPI2C5Rx             = 72U | 0x200U,  /**< LPI2C5 */
    Dma5RequestMuxLPI2C6Tx             = 73U | 0x200U,  /**< LPI2C6 */
    Dma5RequestMuxLPI2C6Rx             = 74U | 0x200U,  /**< LPI2C6 */
    Dma5RequestMuxLPI2C7Tx             = 75U | 0x200U,  /**< LPI2C7 */
    Dma5RequestMuxLPI2C7Rx             = 76U | 0x200U,  /**< LPI2C7 */
    Dma5RequestMuxLPI2C8Tx             = 77U | 0x200U,  /**< LPI2C8 */
    Dma5RequestMuxLPI2C8Rx             = 78U | 0x200U,  /**< LPI2C8 */
    Dma5RequestMuxLPSPI5Tx             = 79U | 0x200U,  /**< LPSPI5 Transmit */
    Dma5RequestMuxLPSPI5Rx             = 80U | 0x200U,  /**< LPSPI5 Receive */
    Dma5RequestMuxLPSPI6Tx             = 81U | 0x200U,  /**< LPSPI6 Transmit */
    Dma5RequestMuxLPSPI6Rx             = 82U | 0x200U,  /**< LPSPI6 Receive */
    Dma5RequestMuxLPSPI7Tx             = 83U | 0x200U,  /**< LPSPI7 Transmit */
    Dma5RequestMuxLPSPI7Rx             = 84U | 0x200U,  /**< LPSPI7 Receive */
    Dma5RequestMuxLPSPI8Tx             = 85U | 0x200U,  /**< LPSPI8 Transmit */
    Dma5RequestMuxLPSPI8Rx             = 86U | 0x200U,  /**< LPSPI8 Receive */
    Dma5RequestMuxLPUART7Tx            = 87U | 0x200U,  /**< LPUART7 Transmit */
    Dma5RequestMuxLPUART7Rx            = 88U | 0x200U,  /**< LPUART7 Receive */
    Dma5RequestMuxLPUART8Tx            = 89U | 0x200U,  /**< LPUART8 Transmit */
    Dma5RequestMuxLPUART8Rx            = 90U | 0x200U,  /**< LPUART8 Receive */
    Dma5RequestMuxCAN4                 = 91U | 0x200U,  /**< CAN4 */
    Dma5RequestMuxCAN5                 = 92U | 0x200U,  /**< CAN5 */
} dma_request_source_t;

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
