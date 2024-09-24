/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_RESET_H_
#define FSL_RESET_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup reset
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief reset driver version 2.0.1. */
#define FSL_RESET_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

#if defined(MIMXRT798S_hifi1_SERIES) || defined(MIMXRT798S_cm33_core1_SERIES) || \
    defined(MIMXRT758S_cm33_core1_SERIES) || defined(MIMXRT735S_cm33_core1_SERIES)
#define FSL_RESET_DRIVER_SENSE
#elif defined(MIMXRT798S_hifi4_SERIES) || defined(MIMXRT798S_cm33_core0_SERIES) || \
    defined(MIMXRT758S_cm33_core0_SERIES) || defined(MIMXRT735S_cm33_core0_SERIES)
#define FSL_RESET_DRIVER_COMPUTE
#elif defined(MIMXRT798S_ezhv_SERIES)
#define FSL_RESET_DRIVER_MEDIA
#else
#error "Unsupported core!"
#endif

/*!
 * @brief Reset control registers index
 */
/* RSTCTL0, RSTCTL_COM_VDD2 */
#define RST_CTL0_PSCCTL0 0
#define RST_CTL0_PSCCTL1 1
#define RST_CTL0_PSCCTL2 2
#define RST_CTL0_PSCCTL3 3
#define RST_CTL0_PSCCTL4 4
#define RST_CTL0_PSCCTL5 5
/* RSTCTL1, RSTCTL_VDD1_SENSE */
#define RST_CTL1_PSCCTL0 6
/* RSTCTL2, RSTCTL_COMN_VDDN */
#define RST_CTL2_PSCCTL0 7
/* RSTCTL3, RSTCTL_VDD1_COM */
#define RST_CTL3_PSCCTL0 8
#define RST_CTL3_PSCCTL1 9
/* RSTCTL4, RSTCTL_MED_VDD2 */
#define RST_CTL4_PSCCTL0 10
#define RST_CTL4_PSCCTL1 11

/*!
 * @brief Enumeration for system reset status bits
 *
 * Defines the enumeration for system reset status bits in SYSRSTSTAT register
 */
typedef enum _rstctl_reset_source
{
    kRSTCTL_SourceVddPor = RSTCTL3_SYSRSTSTAT_VDD_POR_MASK,       /*!< VDD Power-On Reset(POR) */
    kRSTCTL_SourcePad    = RSTCTL3_SYSRSTSTAT_RESETN_RESET_MASK,  /*!< PPAD Reset */
    kRSTCTL_SourceIspAp  = RSTCTL3_SYSRSTSTAT_ISP_AP_RESET_MASK,  /*!< ISP_AP reset Reset */
    kRSTCTL_SourceItrcSw = RSTCTL3_SYSRSTSTAT_ITRC_SW_RESET_MASK, /*!< ITRC_SW (Intrusion and Tamper Response
                                                                             Controller SW) Reset */
    kRSTCTL_SourceCpu0  = RSTCTL3_SYSRSTSTAT_CPU0_RESET_MASK,     /*!< VDD2_COMP Core Reset */
    kRSTCTL_SourceCpu1  = RSTCTL3_SYSRSTSTAT_CPU1_RESET_MASK,     /*!< VDD1_SENSE Core Reset */
    kRSTCTL_SourceWwdt0 = RSTCTL3_SYSRSTSTAT_WWDT0_RESET_MASK,    /*!< WatchDog Timer 0 Reset */
    kRSTCTL_SourceWwdt1 = RSTCTL3_SYSRSTSTAT_WWDT1_RESET_MASK,    /*!< WatchDog Timer 1 Reset*/
    kRSTCTL_SourceWwdt2 = RSTCTL3_SYSRSTSTAT_WWDT2_RESET_MASK,    /*!< WatchDog Timer 2 Reset */
    kRSTCTL_SourceWwdt3 = RSTCTL3_SYSRSTSTAT_WWDT3_RESET_MASK,    /*!< WatchDog Timer 3 Reset*/
    kRSTCTL_SourceCdog0 = RSTCTL3_SYSRSTSTAT_CDOG0_RESET_MASK,    /*!< Code WatchDog Timer 0 Reset */
    kRSTCTL_SourceCdog1 = RSTCTL3_SYSRSTSTAT_CDOG1_RESET_MASK,    /*!< Code WatchDog Timer 1 Reset */
    kRSTCTL_SourceCdog2 = RSTCTL3_SYSRSTSTAT_CDOG2_RESET_MASK,    /*!< Code WatchDog Timer 2 Reset */
    kRSTCTL_SourceCdog3 = RSTCTL3_SYSRSTSTAT_CDOG3_RESET_MASK,    /*!< Code WatchDog Timer 3 Reset */
    kRSTCTL_SourceCdog4 = RSTCTL3_SYSRSTSTAT_CDOG4_RESET_MASK,    /*!< Code WatchDog Timer 4 Reset */
    kRSTCTL_SourceAll   = (int)0xffffffffU,
} rstctl_reset_source_t;

/*!
 * @brief Enumeration for peripheral reset control bits
 *
 * Defines the enumeration for peripheral reset control bits in RSTCLTx registers
 */
typedef enum _RSTCTL_RSTn
{
    kIOPCTL0_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL0 << 8) | 6U,        /*!< IOPCTL0 reset control */

    kELS_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL1 << 8) | 0U,            /*!< ELS S50 reset control */

    kDMA0_RST_SHIFT_RSTn  = (RST_CTL0_PSCCTL2 << 8) | 5U,          /*!< eDMA0 reset control */
    kDMA1_RST_SHIFT_RSTn  = (RST_CTL0_PSCCTL2 << 8) | 6U,          /*!< eDMA1 reset control */
    kPKC_RST_SHIFT_RSTn   = (RST_CTL0_PSCCTL2 << 8) | 8U,          /*!< PKC reset control */
    kXSPI0_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 10U,         /*!< XSPI0 reset control */
    kXSPI1_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 11U,         /*!< XSPI1 reset control */
    kGPIO0_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 18U,         /*!< GPIO0 reset control */
    kGPIO1_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 19U,         /*!< GPIO1 reset control */
    kGPIO2_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 20U,         /*!< GPIO2 reset control */
    kGPIO3_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 21U,         /*!< GPIO3 reset control */
    kGPIO4_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 22U,         /*!< GPIO4 reset control */
    kGPIO5_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 23U,         /*!< GPIO5 reset control */
    kGPIO6_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 24U,         /*!< GPIO6 reset control */
    kGPIO7_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL2 << 8) | 25U,         /*!< GPIO7 reset control */
    kSCT0_RST_SHIFT_RSTn  = (RST_CTL0_PSCCTL2 << 8) | 26U,         /*!< SCT0 reset control */
    kFC0_RST_SHIFT_RSTn   = (RST_CTL0_PSCCTL2 << 8) | 30U,         /*!< LP_FLEXCOMM0 reset control */
    kFC1_RST_SHIFT_RSTn   = (RST_CTL0_PSCCTL2 << 8) | 31U,         /*!< LP_FLEXCOMM1 reset control */

    kFC2_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 0U,        /*!< LP_FLEXCOMM2 reset control */
    kFC3_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 1U,        /*!< LP_FLEXCOMM3 reset control */
    kFC4_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 2U,        /*!< LP_FLEXCOMM4 reset control */
    kFC5_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 3U,        /*!< LP_FLEXCOMM5 reset control */
    kFC6_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 4U,        /*!< LP_FLEXCOMM6 reset control */
    kFC7_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 5U,        /*!< LP_FLEXCOMM7 reset control */
    kFC8_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 6U,        /*!< LP_FLEXCOMM8 reset control */
    kFC9_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 7U,        /*!< LP_FLEXCOMM9 reset control */
    kFC10_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 8U,        /*!< LP_FLEXCOMM10 reset control */
    kFC11_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 9U,        /*!< LP_FLEXCOMM11 reset control */
    kFC12_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 10U,       /*!< LP_FLEXCOMM12 reset control */
    kFC13_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 11U,       /*!< LP_FLEXCOMM13 reset control */
    kSAI0_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 13U,       /*!< SAI0 reset control */
    kSAI1_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 14U,       /*!< SAI1 reset control */
    kSAI2_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 15U,       /*!< SAI2 reset control */
    kI3C0_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 16U,       /*!< I3C0 reset control */
    kI3C1_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 17U,       /*!< I3C1 reset control */
    kCRC0_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 18U,       /*!< CRC0 reset control */
    kCTIMER0_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL3 << 8) | 21U,       /*!< CTIMER0 reset control */
    kCTIMER1_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL3 << 8) | 22U,       /*!< CTIMER1 reset control */
    kCTIMER2_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL3 << 8) | 23U,       /*!< CTIMER2 reset control */
    kCTIMER3_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL3 << 8) | 24U,       /*!< CTIMER3 reset control */
    kCTIMER4_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL3 << 8) | 25U,       /*!< CTIMER4 reset control */
    kMRT0_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL3 << 8) | 26U,       /*!< MRT0 reset control */
    kUTICK0_RST_SHIFT_RSTn  = (RST_CTL0_PSCCTL3 << 8) | 27U,       /*!< UTICK0 reset control */
    kSEMA424_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL3 << 8) | 30U,       /*!< SEMA42_4 reset control */
    kMU4_RST_SHIFT_RSTn     = (RST_CTL0_PSCCTL3 << 8) | 31U,       /*!< MU4 reset control */

    kSYSPM2_RST_SHIFT_RSTn   = (RST_CTL0_PSCCTL4 << 8) | 0U,       /*!< SYSPM_XSPI0 reset control */
    kSYSPM3_RST_SHIFT_RSTn   = (RST_CTL0_PSCCTL4 << 8) | 1U,       /*!< SYSPM_XSPI1 reset control */
    kSAFO_SGI_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL4 << 8) | 2U,       /*!< SAFO_SGI reset control */
#if defined(FSL_RESET_DRIVER_COMPUTE)
    kPINT_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL4 << 8) | 5U,           /*!< PINT0 reset control */
#endif
    kINPUTMUX0_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL4 << 8) | 7U,      /*!< INPUTMUX0 reset control */
    kFREQME0_RST_SHIFT_RSTn   = (RST_CTL0_PSCCTL4 << 8) | 8U,      /*!< FREQME0 reset control */
    kSYSPM0_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL4 << 8) | 10U,     /*!< SYSPM_PC reset control */
    kSYSPM1_RST_SHIFT_RSTn    = (RST_CTL0_PSCCTL4 << 8) | 11U,     /*!< SYSPM_PS reset control */
    kNPU0_RST_SHIFT_RSTn      = (RST_CTL0_PSCCTL4 << 8) | 12U,     /*!< NPU0 reset control */

    kHIFI4_RST_SHIFT_RSTn       = (RST_CTL0_PSCCTL5 << 8) | 0U,    /*!< HiFi4 reset control */
    kHIFI4_DEBUG_RST_SHIFT_RSTn = (RST_CTL0_PSCCTL5 << 8) | 2U,    /*!< HiFi4 Debug reset control */

    kHIFI1_RST_SHIFT_RSTn       = (RST_CTL1_PSCCTL0 << 8) | 1U,    /*!< HiFi1 reset control */
    kHIFI1_DEBUG_RST_SHIFT_RSTn = (RST_CTL1_PSCCTL0 << 8) | 2U,    /*!< HiFi1 Debug reset control */
    kDMA2_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 4U,    /*!< eDMA2 reset control */
    kDMA3_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 5U,    /*!< eDMA3 reset control */
    kFC17_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 6U,    /*!< LP_FLEXCOMM17 reset control */
    kFC18_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 7U,    /*!< LP_FLEXCOMM18 reset control */
    kFC19_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 8U,    /*!< LP_FLEXCOMM19 reset control */
    kFC20_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 9U,    /*!< LP_FLEXCOMM20 reset control */
    kSAI3_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 10U,   /*!< SAI3 reset control */
    kI3C2_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 11U,   /*!< I3C2 reset control */
    kI3C3_RST_SHIFT_RSTn        = (RST_CTL1_PSCCTL0 << 8) | 12U,   /*!< I3C3 reset control */
    kGPIO8_RST_SHIFT_RSTn       = (RST_CTL1_PSCCTL0 << 8) | 13U,   /*!< GPIO8 reset control */
    kGPIO9_RST_SHIFT_RSTn       = (RST_CTL1_PSCCTL0 << 8) | 14U,   /*!< GPIO9 reset control */
    kGPIO10_RST_SHIFT_RSTn      = (RST_CTL1_PSCCTL0 << 8) | 15U,   /*!< GPIO10 reset control */
#if defined(FSL_RESET_DRIVER_SENSE)
    kPINT_RST_SHIFT_RSTn = (RST_CTL1_PSCCTL0 << 8) | 16U,          /*!< PINT1 reset control */
#endif
    kCTIMER5_RST_SHIFT_RSTn = (RST_CTL1_PSCCTL0 << 8) | 17U,       /*!< CTIMER5 reset control */
    kCTIMER6_RST_SHIFT_RSTn = (RST_CTL1_PSCCTL0 << 8) | 18U,       /*!< CTIMER6 reset control */
    kCTIMER7_RST_SHIFT_RSTn = (RST_CTL1_PSCCTL0 << 8) | 19U,       /*!< CTIMER7 reset control */
    kMRT1_RST_SHIFT_RSTn    = (RST_CTL1_PSCCTL0 << 8) | 20U,       /*!< MRT1 reset control */
    kUTICK1_RST_SHIFT_RSTn  = (RST_CTL1_PSCCTL0 << 8) | 21U,       /*!< UTICK1 reset control */
    kMU3_RST_SHIFT_RSTn     = (RST_CTL1_PSCCTL0 << 8) | 24U,       /*!< MU3 reset control */
    kSEMA423_RST_SHIFT_RSTn = (RST_CTL1_PSCCTL0 << 8) | 25U,       /*!< SEMA42_3 reset control */
    kPVT1_RST_SHIFT_RSTn    = (RST_CTL1_PSCCTL0 << 8) | 28U,       /*!< PVT1 reset control */

    kIOPCTL2_RST_SHIFT_RSTn = (RST_CTL2_PSCCTL0 << 8) | 1U,        /*!< IOPCTL2 reset control */

    kIOPCTL1_RST_SHIFT_RSTn   = (RST_CTL3_PSCCTL0 << 8) | 0U,      /*!< IOPCTL1 reset control */
    kCPU1_RST_SHIFT_RSTn      = (RST_CTL3_PSCCTL0 << 8) | 31U,     /*!< CPU1 reset control */
    kMU0_RST_SHIFT_RSTn       = (RST_CTL3_PSCCTL1 << 8) | 1U,      /*!< MU0 reset control */
    kMU1_RST_SHIFT_RSTn       = (RST_CTL3_PSCCTL1 << 8) | 2U,      /*!< MU1 reset control */
    kMU2_RST_SHIFT_RSTn       = (RST_CTL3_PSCCTL1 << 8) | 3U,      /*!< MU2 reset control */
    kSEMA420_RST_SHIFT_RSTn   = (RST_CTL3_PSCCTL1 << 8) | 5U,      /*!< SEMA42_0 reset control */
    kADC0_RST_SHIFT_RSTn      = (RST_CTL3_PSCCTL1 << 8) | 6U,      /*!< ADC0 reset control */
    kSDADC0_RST_SHIFT_RSTn    = (RST_CTL3_PSCCTL1 << 8) | 7U,      /*!< SDADC0 reset control */
    kACMP0_RST_SHIFT_RSTn     = (RST_CTL3_PSCCTL1 << 8) | 8U,      /*!< ACMP0 reset control */
    kPDM_RST_SHIFT_RSTn       = (RST_CTL3_PSCCTL1 << 8) | 9U,      /*!< MICFIL/PDM reset control */
    kINPUTMUX1_RST_SHIFT_RSTn = (RST_CTL3_PSCCTL1 << 8) | 14U,     /*!< INPUTMUX1 reset control */
    kLPI2C15_RST_SHIFT_RSTn   = (RST_CTL3_PSCCTL1 << 8) | 18U,     /*!< LPI2C15 reset control */

    kVGPU_RST_SHIFT_RSTn          = (RST_CTL4_PSCCTL0 << 8) | 2U,  /*!< VGPU reset control */
    kLCDIF_RST_SHIFT_RSTn         = (RST_CTL4_PSCCTL0 << 8) | 3U,  /*!< LCDIF reset control */
    kMIPI_DSI_CTRL_RST_SHIFT_RSTn = (RST_CTL4_PSCCTL0 << 8) | 4U,  /*!< MIPIDSI reset control */
    kEZHV_RST_SHIFT_RSTn          = (RST_CTL4_PSCCTL0 << 8) | 5U,  /*!< EZHV reset control */
    kJPEGDEC_RST_SHIFT_RSTn       = (RST_CTL4_PSCCTL0 << 8) | 6U,  /*!< JPEGDEC reset control */
    kPNGDEC_RST_SHIFT_RSTn        = (RST_CTL4_PSCCTL0 << 8) | 7U,  /*!< PNGDEC reset control */
    kXSPI2_RST_SHIFT_RSTn         = (RST_CTL4_PSCCTL0 << 8) | 8U,  /*!< XSPI2 and MMU2 reset control */
    kLPSPI14_RST_SHIFT_RSTn       = (RST_CTL4_PSCCTL0 << 8) | 13U, /*!< LPSPI14 reset control */
    kLPSPI16_RST_SHIFT_RSTn       = (RST_CTL4_PSCCTL0 << 8) | 14U, /*!< LPSPI16 reset control */
    kFLEXIO0_RST_SHIFT_RSTn       = (RST_CTL4_PSCCTL0 << 8) | 15U, /*!< FLEXIO0 reset control */

    kUSB0_RST_SHIFT_RSTn    = (RST_CTL4_PSCCTL1 << 8) | 0U,        /*!< USB0 reset control */
    kUSBPHY0_RST_SHIFT_RSTn = (RST_CTL4_PSCCTL1 << 8) | 1U,        /*!< USBPHY0 reset control */
    kUSB1_RST_SHIFT_RSTn    = (RST_CTL4_PSCCTL1 << 8) | 2U,        /*!< USB1 reset control */
    kUSDHC0_RST_SHIFT_RSTn  = (RST_CTL4_PSCCTL1 << 8) | 4U,        /*!< USDHC0 reset control */
    kUSDHC1_RST_SHIFT_RSTn  = (RST_CTL4_PSCCTL1 << 8) | 5U,        /*!< USDHC1 reset control */
} RSTCTL_RSTn_t;

/** Array initializers with peripheral reset bits **/
#define ADC_RSTS             \
    {                        \
        kADC0_RST_SHIFT_RSTn \
    } /* Reset bits for ADC peripheral */
#define SDADC_RSTS             \
    {                          \
        kSDADC0_RST_SHIFT_RSTn \
    } /* Reset bits for SDADC peripheral */
#define CRC_RSTS             \
    {                        \
        kCRC0_RST_SHIFT_RSTn \
    } /* Reset bits for CRC peripheral */
#define CTIMER_RSTS                                                                                            \
    {                                                                                                          \
        kCTIMER0_RST_SHIFT_RSTn, kCTIMER1_RST_SHIFT_RSTn, kCTIMER2_RST_SHIFT_RSTn, kCTIMER3_RST_SHIFT_RSTn,    \
            kCTIMER4_RST_SHIFT_RSTn, kCTIMER5_RST_SHIFT_RSTn, kCTIMER6_RST_SHIFT_RSTn, kCTIMER7_RST_SHIFT_RSTn \
    } /* Reset bits for TIMER peripheral */
#define MIPI_DSI_RSTS                 \
    {                                 \
        kMIPI_DSI_CTRL_RST_SHIFT_RSTn \
    } /* Reset bits for MIPI_DSI peripheral */
#define LCDIF_RSTS            \
    {                         \
        kLCDIF_RST_SHIFT_RSTn \
    } /* Reset bits for LCDIF peripheral */
#define LP_FLEXCOMM_RSTS                                                                                               \
    {                                                                                                                  \
        kFC0_RST_SHIFT_RSTn, kFC1_RST_SHIFT_RSTn, kFC2_RST_SHIFT_RSTn, kFC3_RST_SHIFT_RSTn, kFC4_RST_SHIFT_RSTn,       \
            kFC5_RST_SHIFT_RSTn, kFC6_RST_SHIFT_RSTn, kFC7_RST_SHIFT_RSTn, kFC8_RST_SHIFT_RSTn, kFC9_RST_SHIFT_RSTn,   \
            kFC10_RST_SHIFT_RSTn, kFC11_RST_SHIFT_RSTn, kFC12_RST_SHIFT_RSTn, kFC13_RST_SHIFT_RSTn, (RSTCTL_RSTn_t)0U, \
            (RSTCTL_RSTn_t)0U, (RSTCTL_RSTn_t)0U, kFC17_RST_SHIFT_RSTn, kFC18_RST_SHIFT_RSTn, kFC19_RST_SHIFT_RSTn,    \
            kFC20_RST_SHIFT_RSTn                                                                                       \
    } /* Reset bits for FLEXCOMM peripheral */
#define FLEXIO_RSTS             \
    {                           \
        kFLEXIO0_RST_SHIFT_RSTn \
    } /* Resets bits for FLEXIO peripheral */
#define XSPI_RSTS                                                           \
    {                                                                       \
        kXSPI0_RST_SHIFT_RSTn, kXSPI1_RST_SHIFT_RSTn, kXSPI2_RST_SHIFT_RSTn \
    } /* Resets bits for FLEXSPI peripheral */
#define GPIO_RSTS                                                                                        \
    {                                                                                                    \
        kGPIO0_RST_SHIFT_RSTn, kGPIO1_RST_SHIFT_RSTn, kGPIO2_RST_SHIFT_RSTn, kGPIO3_RST_SHIFT_RSTn,      \
            kGPIO4_RST_SHIFT_RSTn, kGPIO5_RST_SHIFT_RSTn, kGPIO6_RST_SHIFT_RSTn, kGPIO7_RST_SHIFT_RSTn,  \
            kGPIO8_RST_SHIFT_RSTn, kGPIO9_RST_SHIFT_RSTn, kGPIO10_RST_SHIFT_RSTn, kGPIO0_RST_SHIFT_RSTn, \
            kGPIO1_RST_SHIFT_RSTn, kGPIO2_RST_SHIFT_RSTn, kGPIO3_RST_SHIFT_RSTn, kGPIO4_RST_SHIFT_RSTn,  \
            kGPIO5_RST_SHIFT_RSTn, kGPIO6_RST_SHIFT_RSTn, kGPIO7_RST_SHIFT_RSTn, kGPIO8_RST_SHIFT_RSTn,  \
            kGPIO9_RST_SHIFT_RSTn, kGPIO10_RST_SHIFT_RSTn                                                \
    } /* Reset bits for GPIO peripheral */
#define I3C_RSTS                                                                               \
    {                                                                                          \
        kI3C0_RST_SHIFT_RSTn, kI3C1_RST_SHIFT_RSTn, kI3C2_RST_SHIFT_RSTn, kI3C3_RST_SHIFT_RSTn \
    } /* Reset bits for I3C peripheral */

#if defined(FSL_RESET_DRIVER_SENSE)
#define INPUTMUX_RSTS             \
    {                             \
        kINPUTMUX1_RST_SHIFT_RSTn \
    } /* Reset bits for INPUTMUX peripheral */
#define DMA_RSTS_N                                 \
    {                                              \
        kDMA2_RST_SHIFT_RSTn, kDMA3_RST_SHIFT_RSTn \
    } /* Reset bits for DMA peripheral */
#endif
#if defined(FSL_RESET_DRIVER_COMPUTE)
#define INPUTMUX_RSTS             \
    {                             \
        kINPUTMUX0_RST_SHIFT_RSTn \
    } /* Reset bits for INPUTMUX peripheral */
#define DMA_RSTS_N                                 \
    {                                              \
        kDMA0_RST_SHIFT_RSTn, kDMA1_RST_SHIFT_RSTn \
    } /* Reset bits for DMA peripheral */
#endif
#define MRT_RSTS                                   \
    {                                              \
        kMRT0_RST_SHIFT_RSTn, kMRT1_RST_SHIFT_RSTn \
    } /* Reset bits for MRT peripheral */
#if (defined(MIMXRT798S_cm33_core0_SERIES) || defined(MIMXRT758S_cm33_core0_SERIES) || \
     defined(MIMXRT735S_cm33_core0_SERIES))
#define MU_RSTS                                                       \
    {                                                                 \
        kMU0_RST_SHIFT_RSTn, kMU1_RST_SHIFT_RSTn, kMU4_RST_SHIFT_RSTn \
    } /* Reset bits for MU peripheral */
#elif (defined(MIMXRT798S_cm33_core1_SERIES) || defined(MIMXRT758S_cm33_core1_SERIES) || \
       defined(MIMXRT735S_cm33_core1_SERIES))
#define MU_RSTS                                                       \
    {                                                                 \
        kMU1_RST_SHIFT_RSTn, kMU2_RST_SHIFT_RSTn, kMU3_RST_SHIFT_RSTn \
    } /* Reset bits for MU peripheral */
#elif defined(MIMXRT798S_hifi4_SERIES)
#define MU_RSTS                                  \
    {                                            \
        kMU2_RST_SHIFT_RSTn, kMU4_RST_SHIFT_RSTn \
    } /* Reset bits for MU peripheral */
#elif defined(MIMXRT798S_hifi1_SERIES)
#define MU_RSTS                                  \
    {                                            \
        kMU0_RST_SHIFT_RSTn, kMU3_RST_SHIFT_RSTn \
    } /* Reset bits for MU peripheral */
#elif defined(MIMXRT798S_ezhv_SERIES)
#else
#error "Unsupported core!"
#endif

#define PINT_RSTS            \
    {                        \
        kPINT_RST_SHIFT_RSTn \
    } /* Reset bits for PINT peripheral */

#define PNGDEC_RSTS            \
    {                          \
        kPNGDEC_RST_SHIFT_RSTn \
    } /* Reset bits for PNGDEC peripheral */

#define JPEGDEC_RSTS            \
    {                           \
        kJPEGDEC_RST_SHIFT_RSTn \
    } /* Reset bits for JPEGDEC peripheral */

#define SCT_RSTS             \
    {                        \
        kSCT0_RST_SHIFT_RSTn \
    } /* Reset bits for SCT peripheral */
#define SEMA42_RSTS                                                                             \
    {                                                                                           \
        kSEMA420_RST_SHIFT_RSTn, (RSTCTL_RSTn_t)0U, (RSTCTL_RSTn_t)0U, kSEMA423_RST_SHIFT_RSTn, \
            kSEMA424_RST_SHIFT_RSTn                                                             \
    } /* Reset bits for SEMA42 peripheral */
#define SAI_RSTS                                                                               \
    {                                                                                          \
        kSAI0_RST_SHIFT_RSTn, kSAI1_RST_SHIFT_RSTn, kSAI2_RST_SHIFT_RSTn, kSAI3_RST_SHIFT_RSTn \
    } /* Reset bits for SAI peripheral */
#define USDHC_RSTS                                     \
    {                                                  \
        kUSDHC0_RST_SHIFT_RSTn, kUSDHC1_RST_SHIFT_RSTn \
    } /* Reset bits for USDHC peripheral */
#define UTICK_RSTS                                     \
    {                                                  \
        kUTICK0_RST_SHIFT_RSTn, kUTICK1_RST_SHIFT_RSTn \
    } /* Reset bits for UTICK peripheral */

/*!
 * @brief IP reset handle
 */
typedef RSTCTL_RSTn_t reset_ip_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Assert reset to peripheral.
 *
 * Asserts reset signal to specified peripheral module.
 *
 * @param peripheral Assert reset to this peripheral. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_SetPeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Clear reset to peripheral.
 *
 * Clears reset signal to specified peripheral module, allows it to operate.
 *
 * @param peripheral Clear reset to this peripheral. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_ClearPeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Reset peripheral module.
 *
 * Reset peripheral module.
 *
 * @param peripheral Peripheral to reset. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_PeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Release peripheral module.
 *
 * Release peripheral module.
 *
 * @param peripheral Peripheral to release. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
static inline void RESET_ReleasePeripheralReset(reset_ip_name_t peripheral)
{
    RESET_ClearPeripheralReset(peripheral);
}

/*!
 * @brief Gets the reset source status which caused a previous reset.
 *
 * This function gets the status of the latest reset event. Use source masks
 * defined in the rstctl_reset_source_t to get the desired source status.
 *
 * @return All reset source status bit map.
 */
static inline uint32_t RESET_GetPreviousResetSources(void)
{
    return RSTCTL3->SYSRSTSTAT;
}

/*!
 * @brief Clears the reset source status.
 *
 * This function clears the system reset flags indicated by source masks.
 *
 * @param sourceMasks reset source status bit map
 */
static inline void RESET_ClearResetSources(uint32_t sourceMasks)
{
    RSTCTL3->SYSRSTSTAT = sourceMasks;
}

/*!
 * @brief Gets the reset status of domains.
 *
 * This function gets the reset status of domains.
 *
 * @return All reset source status bit map.
 */
static inline uint32_t RESET_GetDomainResetStatus(void)
{
    return RSTCTL3->DOMRSTSTAT;
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_RESET_H_ */
