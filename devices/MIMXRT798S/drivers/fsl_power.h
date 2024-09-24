/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_POWER_H_
#define FSL_POWER_H_

#include "fsl_common.h"

/*!
 * @addtogroup power
 * @{
 */

/*!*****************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief power driver version 2.3.0. */
#define FSL_POWER_DRIVER_VERSION (MAKE_VERSION(2, 3, 0))
/*@}*/

/* Define the default PMIC modes for power modes. */
#ifndef POWER_DEFAULT_PMICMODE_DS
#define POWER_DEFAULT_PMICMODE_DS 1U
#endif
#ifndef POWER_DEFAULT_PMICMODE_DSR
#define POWER_DEFAULT_PMICMODE_DSR 1U
#endif
#ifndef POWER_DEFAULT_PMICMODE_DPD
#define POWER_DEFAULT_PMICMODE_DPD 2U
#endif
#ifndef POWER_DEFAULT_PMICMODE_FDPD
#define POWER_DEFAULT_PMICMODE_FDPD 3U
#endif

#define MAKE_PD_BITS(reg, slot)   (((reg) << 8) | (slot))
#define GET_PD_REG_FROM_BITS(bit) (((uint32_t)(bit) >> 8U) & 0xFFU)

#define SLEEPCON_RCFG 0x0U
#define PMC_PDRCFG0   0x1U
#define PMC_PDRCFG1   0x2U
#define PMC_PDRCFG2   0x3U
#define PMC_PDRCFG3   0x4U
#define PMC_PDRCFG4   0x5U
#define PMC_PDRCFG5   0x6U

/*! @brief Power down control bits defined in SLEEPCON and PMC. */
typedef enum pd_bits
{
#if defined(PMC0)
    kPDRUNCFG_SHUT_COMPT_MAINCLK = MAKE_PD_BITS(SLEEPCON_RCFG, 0U), /*!< VDD2_COMP Domain Main Clock Shut Off. */
#endif
    kPDRUNCFG_SHUT_SENSEP_MAINCLK =
        MAKE_PD_BITS(SLEEPCON_RCFG, 1U), /*!< The Private Part in VDD1_SENSE Main Clock Shut Off. */
    kPDRUNCFG_SHUT_SENSES_MAINCLK =
        MAKE_PD_BITS(SLEEPCON_RCFG, 2U), /*!< The Shared Part in VDD1_SENSE Main Clock Shut Off. */
    kPDRUNCFG_SHUT_RAM0_CLK      = MAKE_PD_BITS(SLEEPCON_RCFG, 3U), /*!< Main Clock of RAM Arbiter 0 Shut Off. */
    kPDRUNCFG_SHUT_RAM1_CLK      = MAKE_PD_BITS(SLEEPCON_RCFG, 4U), /*!< Main Clock of RAM Arbiter 1 shut off. */
    kPDRUNCFG_SHUT_COMNN_MAINCLK = MAKE_PD_BITS(SLEEPCON_RCFG, 5U), /*!< VDDN_COM Domain Main Clock Shut Off. */
    kPDRUNCFG_SHUT_MEDIA_MAINCLK =
        MAKE_PD_BITS(SLEEPCON_RCFG, 6U), /*!< VDD2_MEDIA and VDDN_MEDIA Domains Main Clock of Shut Off. */
    kPDRUNCFG_PD_SYSXTAL = MAKE_PD_BITS(SLEEPCON_RCFG, 7U),    /*!< Xtal Oscillator Power Down. */
#if defined(PMC0)
    kPDRUNCFG_PD_FRO0 = MAKE_PD_BITS(SLEEPCON_RCFG, 8U),       /*!< FRO0 Power Down. */
    kPDRUNCFG_PD_FRO1 = MAKE_PD_BITS(SLEEPCON_RCFG, 9U),       /*!< FRO1 Power Down. */
#endif
    kPDRUNCFG_PD_FRO2      = MAKE_PD_BITS(SLEEPCON_RCFG, 10U), /*!< FRO2 Power Down. */
    kPDRUNCFG_PD_LPOSC     = MAKE_PD_BITS(SLEEPCON_RCFG, 11U), /*!< LPOSC Power Down. */
    kPDRUNCFG_PD_PLLANA    = MAKE_PD_BITS(SLEEPCON_RCFG, 12U), /*!< Main PLL Analog Function Power Down. */
    kPDRUNCFG_PD_PLLLDO    = MAKE_PD_BITS(SLEEPCON_RCFG, 13U), /*!< Main PLL Internal Regulator Power Down. */
    kPDRUNCFG_PD_AUDPLLANA = MAKE_PD_BITS(SLEEPCON_RCFG, 14U), /*!< Audio PLL Analog Function Power Down. */
    kPDRUNCFG_PD_AUDPLLLDO = MAKE_PD_BITS(SLEEPCON_RCFG, 15U), /*!< Audio PLL Internal Regulator Power Down. */
    kPDRUNCFG_PD_ADC0      = MAKE_PD_BITS(SLEEPCON_RCFG, 16U), /*!< ADC0 Power Down, 1 - Applies gating. */
#if defined(PMC0)
    kPDRUNCFG_GATE_FRO0 = MAKE_PD_BITS(SLEEPCON_RCFG, 29U),    /*!< FRO0 Gating, 1 - Applies gating. */
#endif
    kPDRUNCFG_GATE_FRO2 = MAKE_PD_BITS(SLEEPCON_RCFG, 31U),    /*!< FRO2 Gating, 1 - Applies gating. */
    kPDRUNCFG_DSR_VDD2N_MEDIA =
        MAKE_PD_BITS(PMC_PDRCFG0, 6U), /*!< Power Switch and DSR Enable for the VDD2_MEDIA and VDDN_MEDIA domains. */
    kPDRUNCFG_DSR_VDDN_COM = MAKE_PD_BITS(PMC_PDRCFG0, 8U), /*!< Power Switch and DSR Enable for the VDDN_COM domain. */
    kPDRUNCFG_PD_VDD2_DSP  = MAKE_PD_BITS(PMC_PDRCFG0, 9U), /*!< Power switch for the HiFi4 DSP. */
    kPDRUNCFG_PD_VDD2_MIPI = MAKE_PD_BITS(PMC_PDRCFG0, 10U),        /*!< Power Switch for the MIPI PHY. */
    kPDRUNCFG_LP_DCDC      = MAKE_PD_BITS(PMC_PDRCFG0, 12U),        /*!< DCDC Low-Power Mode. */
    kPDRUNCFG_PD_RBB_VDD1  = MAKE_PD_BITS(PMC_PDRCFG0, 22U),        /*!< Power Down RBB in VDD1. */
    kPDRUNCFG_PD_AFBB_VDD1 = MAKE_PD_BITS(PMC_PDRCFG0, 23U),        /*!< Power Down AFBB in VDD1 Domain. */
    kPDRUNCFG_PD_RBB_VDD2  = MAKE_PD_BITS(PMC_PDRCFG0, 24U),        /*!< Power Down RBB in VDD2 Domain.*/
    kPDRUNCFG_PD_AFBB_VDD2 = MAKE_PD_BITS(PMC_PDRCFG0, 25U),        /*!< Power Down AFBB in VDD2 Domain.*/
    kPDRUNCFG_PD_RBB_VDDN  = MAKE_PD_BITS(PMC_PDRCFG0, 26U),        /*!< Power Down RBB in VDDN Domain.*/
    kPDRUNCFG_PD_AFBB_VDDN = MAKE_PD_BITS(PMC_PDRCFG0, 27U),        /*!< Power Down RBB in VDDN Domain.*/
    kPDRUNCFG_PD_SRAM_RBB_VDD1    = MAKE_PD_BITS(PMC_PDRCFG0, 28U), /*!< Power Down SRAM RBB in VDD1 Domain. */
    kPDRUNCFG_PD_SRAM_RBB_VDD2    = MAKE_PD_BITS(PMC_PDRCFG0, 29U), /*!< Power Down SRAM RBB in VDD2 Domain. */
    kPDRUNCFG_PD_SRAM_AFBB_VDD2   = MAKE_PD_BITS(PMC_PDRCFG0, 31U), /*!< Power Down SRAM AFBB in VDD2 Domain.*/
    kPDRUNCFG_PD_PMC_TEMPSNS      = MAKE_PD_BITS(PMC_PDRCFG1, 0U),  /*!< Power Down PMC Temperature Sensor.*/
    kPDRUNCFG_LP_PMCREF           = MAKE_PD_BITS(PMC_PDRCFG1, 1U),  /*!< PMC References in Low-Power Mode.*/
    kPDRUNCFG_PD_HVD1V8           = MAKE_PD_BITS(PMC_PDRCFG1, 2U),  /*!< HVD Power Down.*/
    kPDRUNCFG_LP_POR_VDD1         = MAKE_PD_BITS(PMC_PDRCFG1, 3U),  /*!< POR Low-Power Mode in VDD1 Domain.*/
    kPDRUNCFG_LP_LVD_VDD1         = MAKE_PD_BITS(PMC_PDRCFG1, 4U),  /*!< LVD Low-Power Mode in VDD1 Domain.*/
    kPDRUNCFG_PD_HVD_VDD1         = MAKE_PD_BITS(PMC_PDRCFG1, 5U),  /*!< Power Down HVD in VDD1 Domain.*/
    kPDRUNCFG_PD_AGDET_VDD1       = MAKE_PD_BITS(PMC_PDRCFG1, 6U),  /*!< Power Down AGDET in VDD1 Domain.*/
    kPDRUNCFG_LP_POR_VDD2         = MAKE_PD_BITS(PMC_PDRCFG1, 7U),  /*!< POR Low-Power Mode in VDD2 Domain.*/
    kPDRUNCFG_LP_LVD_VDD2         = MAKE_PD_BITS(PMC_PDRCFG1, 8U),  /*!< LVD Low-Power Mode in VDD2 Domain.*/
    kPDRUNCFG_PD_HVD_VDD2         = MAKE_PD_BITS(PMC_PDRCFG1, 9U),  /*!< Power Down HVD in VDD2 Domain.*/
    kPDRUNCFG_PD_AGDET_VDD2       = MAKE_PD_BITS(PMC_PDRCFG1, 10U), /*!< Power Down AGDET in VDD2 Domain.*/
    kPDRUNCFG_LP_POR_VDDN         = MAKE_PD_BITS(PMC_PDRCFG1, 11U), /*!< POR Low-Power Mode in VDDN Domain.*/
    kPDRUNCFG_LP_LVD_VDDN         = MAKE_PD_BITS(PMC_PDRCFG1, 12U), /*!< LVD Low-Power Mode in VDDN Domain.*/
    kPDRUNCFG_PD_HVD_VDDN         = MAKE_PD_BITS(PMC_PDRCFG1, 13U), /*!< Power Down HVD in VDDN Domain.*/
    kPDRUNCFG_PD_OTP              = MAKE_PD_BITS(PMC_PDRCFG1, 15U), /*!< Power Down OTP.*/
    kPDRUNCFG_PD_ROM              = MAKE_PD_BITS(PMC_PDRCFG1, 16U), /*!< Power Down ROM.*/
    kPDRUNCFG_APD_SRAM1           = MAKE_PD_BITS(PMC_PDRCFG2, 1U),  /*!< RAM Partition 1 Array Power Down. */
    kPDRUNCFG_APD_SRAM2           = MAKE_PD_BITS(PMC_PDRCFG2, 2U),  /*!< RAM Partition 2 Array Power Down. */
    kPDRUNCFG_APD_SRAM3           = MAKE_PD_BITS(PMC_PDRCFG2, 3U),  /*!< RAM Partition 3 Array Power Down. */
    kPDRUNCFG_APD_SRAM4           = MAKE_PD_BITS(PMC_PDRCFG2, 4U),  /*!< RAM Partition 4 Array Power Down. */
    kPDRUNCFG_APD_SRAM5           = MAKE_PD_BITS(PMC_PDRCFG2, 5U),  /*!< RAM Partition 5 Array Power Down. */
    kPDRUNCFG_APD_SRAM6           = MAKE_PD_BITS(PMC_PDRCFG2, 6U),  /*!< RAM Partition 6 Array Power Down. */
    kPDRUNCFG_APD_SRAM7           = MAKE_PD_BITS(PMC_PDRCFG2, 7U),  /*!< RAM Partition 7 Array Power Down. */
    kPDRUNCFG_APD_SRAM8           = MAKE_PD_BITS(PMC_PDRCFG2, 8U),  /*!< RAM Partition 8 Array Power Down. */
    kPDRUNCFG_APD_SRAM9           = MAKE_PD_BITS(PMC_PDRCFG2, 9U),  /*!< RAM Partition 9 Array Power Down. */
    kPDRUNCFG_APD_SRAM10          = MAKE_PD_BITS(PMC_PDRCFG2, 10U), /*!< RAM Partition 10 Array Power Down. */
    kPDRUNCFG_APD_SRAM11          = MAKE_PD_BITS(PMC_PDRCFG2, 11U), /*!< RAM Partition 11 Array Power Down. */
    kPDRUNCFG_APD_SRAM12          = MAKE_PD_BITS(PMC_PDRCFG2, 12U), /*!< RAM Partition 12 Array Power Down. */
    kPDRUNCFG_APD_SRAM13          = MAKE_PD_BITS(PMC_PDRCFG2, 13U), /*!< RAM Partition 13 Array Power Down. */
    kPDRUNCFG_APD_SRAM14          = MAKE_PD_BITS(PMC_PDRCFG2, 14U), /*!< RAM Partition 14 Array Power Down. */
    kPDRUNCFG_APD_SRAM15          = MAKE_PD_BITS(PMC_PDRCFG2, 15U), /*!< RAM Partition 15 Array Power Down. */
    kPDRUNCFG_APD_SRAM16          = MAKE_PD_BITS(PMC_PDRCFG2, 16U), /*!< RAM Partition 16 Array Power Down. */
    kPDRUNCFG_APD_SRAM17          = MAKE_PD_BITS(PMC_PDRCFG2, 17U), /*!< RAM Partition 17 Array Power Down. */
    kPDRUNCFG_APD_SRAM18          = MAKE_PD_BITS(PMC_PDRCFG2, 18U), /*!< RAM Partition 18 Array Power Down. */
    kPDRUNCFG_APD_SRAM19          = MAKE_PD_BITS(PMC_PDRCFG2, 19U), /*!< RAM Partition 19 Array Power Down. */
    kPDRUNCFG_APD_SRAM20          = MAKE_PD_BITS(PMC_PDRCFG2, 20U), /*!< RAM Partition 20 Array Power Down. */
    kPDRUNCFG_APD_SRAM21          = MAKE_PD_BITS(PMC_PDRCFG2, 21U), /*!< RAM Partition 21 Array Power Down. */
    kPDRUNCFG_APD_SRAM22          = MAKE_PD_BITS(PMC_PDRCFG2, 22U), /*!< RAM Partition 22 Array Power Down. */
    kPDRUNCFG_APD_SRAM23          = MAKE_PD_BITS(PMC_PDRCFG2, 23U), /*!< RAM Partition 23 Array Power Down. */
    kPDRUNCFG_APD_SRAM24          = MAKE_PD_BITS(PMC_PDRCFG2, 24U), /*!< RAM Partition 24 Array Power Down. */
    kPDRUNCFG_APD_SRAM25          = MAKE_PD_BITS(PMC_PDRCFG2, 25U), /*!< RAM Partition 25 Array Power Down. */
    kPDRUNCFG_APD_SRAM26          = MAKE_PD_BITS(PMC_PDRCFG2, 26U), /*!< RAM Partition 26 Array Power Down. */
    kPDRUNCFG_APD_SRAM27          = MAKE_PD_BITS(PMC_PDRCFG2, 27U), /*!< RAM Partition 27 Array Power Down. */
    kPDRUNCFG_APD_SRAM28          = MAKE_PD_BITS(PMC_PDRCFG2, 28U), /*!< RAM Partition 28 Array Power Down. */
    kPDRUNCFG_APD_SRAM29          = MAKE_PD_BITS(PMC_PDRCFG2, 29U), /*!< RAM Partition 29 Array Power Down. */
    kPDRUNCFG_PPD_SRAM1           = MAKE_PD_BITS(PMC_PDRCFG3, 1U),  /*!< RAM Partition 1 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM2           = MAKE_PD_BITS(PMC_PDRCFG3, 2U),  /*!< RAM Partition 2 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM3           = MAKE_PD_BITS(PMC_PDRCFG3, 3U),  /*!< RAM Partition 3 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM4           = MAKE_PD_BITS(PMC_PDRCFG3, 4U),  /*!< RAM Partition 4 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM5           = MAKE_PD_BITS(PMC_PDRCFG3, 5U),  /*!< RAM Partition 5 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM6           = MAKE_PD_BITS(PMC_PDRCFG3, 6U),  /*!< RAM Partition 6 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM7           = MAKE_PD_BITS(PMC_PDRCFG3, 7U),  /*!< RAM Partition 7 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM8           = MAKE_PD_BITS(PMC_PDRCFG3, 8U),  /*!< RAM Partition 8 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM9           = MAKE_PD_BITS(PMC_PDRCFG3, 9U),  /*!< RAM Partition 9 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM10          = MAKE_PD_BITS(PMC_PDRCFG3, 10U), /*!< RAM Partition 10 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM11          = MAKE_PD_BITS(PMC_PDRCFG3, 11U), /*!< RAM Partition 11 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM12          = MAKE_PD_BITS(PMC_PDRCFG3, 12U), /*!< RAM Partition 12 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM13          = MAKE_PD_BITS(PMC_PDRCFG3, 13U), /*!< RAM Partition 13 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM14          = MAKE_PD_BITS(PMC_PDRCFG3, 14U), /*!< RAM Partition 14 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM15          = MAKE_PD_BITS(PMC_PDRCFG3, 15U), /*!< RAM Partition 15 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM16          = MAKE_PD_BITS(PMC_PDRCFG3, 16U), /*!< RAM Partition 16 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM17          = MAKE_PD_BITS(PMC_PDRCFG3, 17U), /*!< RAM Partition 17 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM18          = MAKE_PD_BITS(PMC_PDRCFG3, 18U), /*!< RAM Partition 18 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM19          = MAKE_PD_BITS(PMC_PDRCFG3, 19U), /*!< RAM Partition 19 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM20          = MAKE_PD_BITS(PMC_PDRCFG3, 20U), /*!< RAM Partition 20 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM21          = MAKE_PD_BITS(PMC_PDRCFG3, 21U), /*!< RAM Partition 21 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM22          = MAKE_PD_BITS(PMC_PDRCFG3, 22U), /*!< RAM Partition 22 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM23          = MAKE_PD_BITS(PMC_PDRCFG3, 23U), /*!< RAM Partition 23 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM24          = MAKE_PD_BITS(PMC_PDRCFG3, 24U), /*!< RAM Partition 24 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM25          = MAKE_PD_BITS(PMC_PDRCFG3, 25U), /*!< RAM Partition 25 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM26          = MAKE_PD_BITS(PMC_PDRCFG3, 26U), /*!< RAM Partition 26 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM27          = MAKE_PD_BITS(PMC_PDRCFG3, 27U), /*!< RAM Partition 27 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM28          = MAKE_PD_BITS(PMC_PDRCFG3, 28U), /*!< RAM Partition 28 Periphery Power Down. */
    kPDRUNCFG_PPD_SRAM29          = MAKE_PD_BITS(PMC_PDRCFG3, 29U), /*!< RAM Partition 29 Periphery Power Down. */
    kPDRUNCFG_APD_SDHC0_SRAM      = MAKE_PD_BITS(PMC_PDRCFG4, 0U),  /*!< uSDHC0 SRAM array Power Down. */
    kPDRUNCFG_APD_SDHC1_SRAM      = MAKE_PD_BITS(PMC_PDRCFG4, 1U),  /*!< uSDHC1 SRAM array Power Down. */
    kPDRUNCFG_APD_USB0_SRAM       = MAKE_PD_BITS(PMC_PDRCFG4, 2U),  /*!< USB0 SRAM array Power Down. */
    kPDRUNCFG_APD_USB1_SRAM       = MAKE_PD_BITS(PMC_PDRCFG4, 3U),  /*!< USB1 SRAM array Power Down. */
    kPDRUNCFG_APD_JPEGDEC         = MAKE_PD_BITS(PMC_PDRCFG4, 4U),  /*!< Powers down JPEGDEC RAMs array. */
    kPDRUNCFG_APD_PNGDEC          = MAKE_PD_BITS(PMC_PDRCFG4, 5U),  /*!< Powers down PNGDEC RAMs array. */
    kPDRUNCFG_APD_MIPIDSI         = MAKE_PD_BITS(PMC_PDRCFG4, 6U),  /*!< Powers down MIPI PHY RAMs array. */
    kPDRUNCFG_APD_GPU             = MAKE_PD_BITS(PMC_PDRCFG4, 7U),  /*!< Powers down VGPU RAMs array. */
    kPDRUNCFG_APD_DMA2_3          = MAKE_PD_BITS(PMC_PDRCFG4, 8U),  /*!< Powers down DMA2 and DMA3 RAMs array. */
    kPDRUNCFG_APD_DMA0_1_PKC_ETF  = MAKE_PD_BITS(PMC_PDRCFG4, 9U),  /*!< Powers down DMA0-1, PKC, and ETF RAMs array. */
    kPDRUNCFG_APD_CPU0_CODE_CACHE = MAKE_PD_BITS(PMC_PDRCFG4, 10U), /*!< Powers down CPU0 code cache RAMs array. */
    kPDRUNCFG_APD_CPU0_SYSTEM_CACHE = MAKE_PD_BITS(PMC_PDRCFG4, 11U), /*!< Powers down CPU0 system cache RAMs array. */
    kPDRUNCFG_APD_DSP_ICACHE = MAKE_PD_BITS(PMC_PDRCFG4, 12U), /*!< Powers down HiFi4 instruction cache RAMs array. */
    kPDRUNCFG_APD_DSP_DCACHE = MAKE_PD_BITS(PMC_PDRCFG4, 13U), /*!< Powers down HiFi4 data cache RAMs array. */
    kPDRUNCFG_APD_DSP_ITCM   = MAKE_PD_BITS(PMC_PDRCFG4, 14U), /*!< Powers down HiFi4 instruction TCM RAMs array. */
    kPDRUNCFG_APD_DSP_DTCM   = MAKE_PD_BITS(PMC_PDRCFG4, 15U), /*!< Powers down HiFi4 data TCM RAMs array. */
    kPDRUNCFG_APD_EZHV_TCM   = MAKE_PD_BITS(PMC_PDRCFG4, 16U), /*!< Powers down EZH-V TCM RAMs array. */
    kPDRUNCFG_APD_NPU        = MAKE_PD_BITS(PMC_PDRCFG4, 17U), /*!< Powers down NPU RAMs array. */
    kPDRUNCFG_APD_XSPI0      = MAKE_PD_BITS(PMC_PDRCFG4, 18U), /*!< Powers down XSPI0, MMU0, and cache RAMs array. */
    kPDRUNCFG_APD_XSPI1      = MAKE_PD_BITS(PMC_PDRCFG4, 19U), /*!< Powers down XSPI1, MMU1, and cache RAMs array. */
    kPDRUNCFG_APD_XSPI2      = MAKE_PD_BITS(PMC_PDRCFG4, 20U), /*!< Powers down XSPI2 and MMU2 RAMs array. */
    kPDRUNCFG_APD_LCDIF      = MAKE_PD_BITS(PMC_PDRCFG4, 21U), /*!< Powers down LCDIF controller RAMs array. */
    kPDRUNCFG_APD_OCOTP      = MAKE_PD_BITS(PMC_PDRCFG4, 22U), /*!< Powers down OCOTP shadow RAMs array. */
    kPDRUNCFG_PPD_SDHC0_SRAM = MAKE_PD_BITS(PMC_PDRCFG5, 0U),  /*!< Powers down uSDHC0 RAMs periphery. */
    kPDRUNCFG_PPD_SDHC1_SRAM = MAKE_PD_BITS(PMC_PDRCFG5, 1U),  /*!< Powers down uSDHC1 RAMs periphery. */
    kPDRUNCFG_PPD_USB0_SRAM  = MAKE_PD_BITS(PMC_PDRCFG5, 2U),  /*!< Powers down USB0 RAMs periphery. */
    kPDRUNCFG_PPD_USB1_SRAM  = MAKE_PD_BITS(PMC_PDRCFG5, 3U),  /*!< Powers down USB1 RAMs periphery. */
    kPDRUNCFG_PPD_JPEGDEC    = MAKE_PD_BITS(PMC_PDRCFG5, 4U),  /*!< Powers down JPEGDEC RAMs periphery. */
    kPDRUNCFG_PPD_PNGDEC     = MAKE_PD_BITS(PMC_PDRCFG5, 5U),  /*!< Powers down PNGDEC RAMs periphery. */
    kPDRUNCFG_PPD_MIPIDSI    = MAKE_PD_BITS(PMC_PDRCFG5, 6U),  /*!< Powers down MIPI PHY RAMs periphery. */
    kPDRUNCFG_PPD_GPU        = MAKE_PD_BITS(PMC_PDRCFG5, 7U),  /*!< Powers down VGPU RAMs periphery. */
    kPDRUNCFG_PPD_DMA2_3     = MAKE_PD_BITS(PMC_PDRCFG5, 8U),  /*!< Powers down DMA2 and DMA3 RAMs periphery. */
    kPDRUNCFG_PPD_DMA0_1_PKC_ETF =
        MAKE_PD_BITS(PMC_PDRCFG5, 9U),                         /*!< Powers down DMA0-1, PKC, and ETF RAMs periphery. */
    kPDRUNCFG_PPD_CPU0_CODE_CACHE = MAKE_PD_BITS(PMC_PDRCFG5, 10U), /*!< Powers down CPU0 code cache RAMs periphery. */
    kPDRUNCFG_PPD_CPU0_SYSTEM_CACHE =
        MAKE_PD_BITS(PMC_PDRCFG5, 11U), /*!< Powers down CPU0 system cache RAMs periphery. */
    kPDRUNCFG_PPD_DSP_ICACHE =
        MAKE_PD_BITS(PMC_PDRCFG5, 12U), /*!< Powers down HiFi4 instruction cache RAMs periphery. */
    kPDRUNCFG_PPD_DSP_DCACHE = MAKE_PD_BITS(PMC_PDRCFG5, 13U), /*!< Powers down HiFi4 data cache RAMs periphery. */
    kPDRUNCFG_PPD_DSP_ITCM   = MAKE_PD_BITS(PMC_PDRCFG5, 14U), /*!< Powers down HiFi4 instruction TCM RAMs periphery. */
    kPDRUNCFG_PPD_DSP_DTCM   = MAKE_PD_BITS(PMC_PDRCFG5, 15U), /*!< Powers down HiFi4 data TCM RAMs periphery. */
    kPDRUNCFG_PPD_EZHV_TCM   = MAKE_PD_BITS(PMC_PDRCFG5, 16U), /*!< Powers down EZH-V TCM RAMs periphery. */
    kPDRUNCFG_PPD_NPU        = MAKE_PD_BITS(PMC_PDRCFG5, 17U), /*!< Powers down NPU RAMs periphery. */
    kPDRUNCFG_PPD_XSPI0 = MAKE_PD_BITS(PMC_PDRCFG5, 18U), /*!< Powers down XSPI0, MMU0, and cache RAMs periphery. */
    kPDRUNCFG_PPD_XSPI1 = MAKE_PD_BITS(PMC_PDRCFG5, 19U), /*!< Powers down XSPI1, MMU1, and cache RAMs periphery. */
    kPDRUNCFG_PPD_XSPI2 = MAKE_PD_BITS(PMC_PDRCFG5, 20U), /*!< Powers down XSPI2 and MMU2 RAMs periphery. */
    kPDRUNCFG_PPD_LCDIF = MAKE_PD_BITS(PMC_PDRCFG5, 21U), /*!< Powers down LCDIF controller RAMs periphery. */
    kPDRUNCFG_PPD_OCOTP = MAKE_PD_BITS(PMC_PDRCFG5, 22U), /*!< Powers down OCOTP shadow RAMs periphery. */
    /*
    This enum member has no practical meaning,it is used to avoid MISRA issue,
    user should not trying to use it.
    */
    kPDRUNCFG_ForceUnsigned = (int)0x80000000U,
} pd_bit_t;

#define SHA_MED_CCTRL0_OFFSET 0U
#define SHA_MED_TCTRL0_OFFSET 1U
#define SHA_SEN_TCTRL0_OFFSET 3U
#define PRIVATE_CCTRL0_OFFSET 4U
#define PRIVATE_TCTRL0_OFFSET 5U
#define PRIVATE_TCTRL1_OFFSET 6U
#define PRIVATE_TCTRL2_OFFSET 7U

#define SHA_MED_CSTAT0_OFFSET    0U /*0x1D0 */
#define SHA_MEDSEN_TSTAT0_OFFSET 1U /* 0x1D4 */
#define PRIVATE_CSTAT0_OFFSET    4U /* 0x1E0 */
#define PRIVATE_TSTAT0_OFFSET    5U /* 0x1E4 */
#define PRIVATE_TSTAT1_OFFSET    6U /* 0x1E8 */

#define POWER_LP_REQ_CTRL_REG_OFFSET  (5U)
#define POWER_LP_REQ_STATE_REG_OFFSET (13U)
#define POWER_LP_REQ_STATE_BIT_OFFSET (8U)
#define POWER_MAKE_LP_BITS(ctrl_reg, ctrl_bit, state_reg, state_bit)                                              \
    (((ctrl_reg) << POWER_LP_REQ_CTRL_REG_OFFSET) | (ctrl_bit) | ((state_bit) << POWER_LP_REQ_STATE_BIT_OFFSET) | \
     ((state_reg) << POWER_LP_REQ_STATE_REG_OFFSET))
#define GET_LP_CTRL_REG_FROM_BITS(bit)  (((uint32_t)(bit) >> POWER_LP_REQ_CTRL_REG_OFFSET) & 0x7U)
#define GET_LP_CTRL_BIT_FROM_BITS(bit)  (((uint32_t)(bit)) & 0x1FU)
#define GET_LP_STATE_REG_FROM_BITS(bit) (((uint32_t)(bit) >> POWER_LP_REQ_STATE_REG_OFFSET) & 0x7U)
#define GET_LP_STATE_BIT_FROM_BITS(bit) ((((uint32_t)(bit)) >> POWER_LP_REQ_STATE_BIT_OFFSET) & 0x1FU)

/*! @brief low power control bits for modules. Bits used for modules to requesting low-power. */
typedef enum lp_bits
{
    kPower_VGPU_LPREQ =
        POWER_MAKE_LP_BITS(SHA_MED_CCTRL0_OFFSET, 0U, SHA_MED_CSTAT0_OFFSET, 0U), /*!< VGPU low power request. */
    kPower_EZHV_STOP =
        POWER_MAKE_LP_BITS(SHA_MED_CCTRL0_OFFSET, 1U, SHA_MED_CSTAT0_OFFSET, 2U), /*!< EZHV stop request. */
    kPower_EZHV_HALT =
        POWER_MAKE_LP_BITS(SHA_MED_CCTRL0_OFFSET, 2U, SHA_MED_CSTAT0_OFFSET, 3U), /*!< EZHV halt request. */
    kPower_EZHV_EXIT_WAIT =
        POWER_MAKE_LP_BITS(SHA_MED_CCTRL0_OFFSET, 3U, SHA_MED_CSTAT0_OFFSET, 4U), /*!< EZHV exit wait request. */

    kPower_XSPI2_STOP =
        POWER_MAKE_LP_BITS(SHA_MED_TCTRL0_OFFSET, 0U, SHA_MEDSEN_TSTAT0_OFFSET, 0U), /*!< XSPI2 stop request. */
    kPower_LPSPI14_B_LPREQ = POWER_MAKE_LP_BITS(
        SHA_MED_TCTRL0_OFFSET, 3U, SHA_MEDSEN_TSTAT0_OFFSET, 1U),  /*!< LPSPI14 bus low power request. */
    kPower_LPSPI14_F_LPREQ = POWER_MAKE_LP_BITS(
        SHA_MED_TCTRL0_OFFSET, 4U, SHA_MEDSEN_TSTAT0_OFFSET, 2U),  /*!< LPSPI14 function low power request.*/
    kPower_LPSPI16_B_LPREQ = POWER_MAKE_LP_BITS(
        SHA_MED_TCTRL0_OFFSET, 6U, SHA_MEDSEN_TSTAT0_OFFSET, 3U),  /*!< LPSPI16 bus low power request. */
    kPower_LPSPI16_F_LPREQ = POWER_MAKE_LP_BITS(
        SHA_MED_TCTRL0_OFFSET, 7U, SHA_MEDSEN_TSTAT0_OFFSET, 4U),  /*!< LPSPI16 function low power request. */
    kPower_FLEXIO_B_LPREQ = POWER_MAKE_LP_BITS(
        SHA_MED_TCTRL0_OFFSET, 9U, SHA_MEDSEN_TSTAT0_OFFSET, 5U),  /*!< FLEXIO bus low power request. */
    kPower_FLEXIO_F_LPREQ = POWER_MAKE_LP_BITS(
        SHA_MED_TCTRL0_OFFSET, 10U, SHA_MEDSEN_TSTAT0_OFFSET, 6U), /*!< FLEXIO function low power request. */
    kPower_NIC0_LPREQ =
        POWER_MAKE_LP_BITS(SHA_MED_TCTRL0_OFFSET, 11U, SHA_MEDSEN_TSTAT0_OFFSET, 7U), /*!< NIC0 low power request. */
    kPower_NIC1_LPREQ =
        POWER_MAKE_LP_BITS(SHA_MED_TCTRL0_OFFSET, 12U, SHA_MEDSEN_TSTAT0_OFFSET, 8U), /*!< NIC1 low power request. */

    kPower_ADC0_STOP =
        POWER_MAKE_LP_BITS(SHA_SEN_TCTRL0_OFFSET, 0U, SHA_MEDSEN_TSTAT0_OFFSET, 16U), /*!< ADC0 stop request. */
    kPower_ACMP0_STOP =
        POWER_MAKE_LP_BITS(SHA_SEN_TCTRL0_OFFSET, 2U, SHA_MEDSEN_TSTAT0_OFFSET, 17U), /*!< ACMP0 stop request. */
    kPower_MICFIL_STOP =
        POWER_MAKE_LP_BITS(SHA_SEN_TCTRL0_OFFSET, 3U, SHA_MEDSEN_TSTAT0_OFFSET, 18U), /*!< MICFIL stop request. */
    kPower_LPI2C15_B_LPREQ = POWER_MAKE_LP_BITS(
        SHA_SEN_TCTRL0_OFFSET, 5U, SHA_MEDSEN_TSTAT0_OFFSET, 19U), /*!< LPI2C15 bus low power request. */
    kPower_LPI2C15_F_LPREQ = POWER_MAKE_LP_BITS(
        SHA_SEN_TCTRL0_OFFSET, 7U, SHA_MEDSEN_TSTAT0_OFFSET, 20U), /*!< LPI2C15 function low power request. */
    kPower_GDET2_LPREQ =
        POWER_MAKE_LP_BITS(SHA_SEN_TCTRL0_OFFSET, 8U, SHA_MEDSEN_TSTAT0_OFFSET, 21U), /*!< GDET2 low power request. */
    kPower_GDET3_LPREQ =
        POWER_MAKE_LP_BITS(SHA_SEN_TCTRL0_OFFSET, 9U, SHA_MEDSEN_TSTAT0_OFFSET, 22U), /*!< GDET3 low power request. */
    kPower_RTC_STOP = POWER_MAKE_LP_BITS(
        SHA_SEN_TCTRL0_OFFSET, 31U, SHA_MEDSEN_TSTAT0_OFFSET, 31U), /*!< RTC0 and RTC1 stop request. */

#if defined(PMC0)
    kPower_EDMA0_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_CCTRL0_OFFSET, 0U, PRIVATE_CSTAT0_OFFSET, 0U), /*!< EDMA0 stop request. */
    kPower_EDMA1_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_CCTRL0_OFFSET, 1U, PRIVATE_CSTAT0_OFFSET, 1U), /*!< EDMA1 stop request. */

    kPower_FC0_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 0U, PRIVATE_TSTAT0_OFFSET, 0U),   /*!< LP_FLEXCOMM0 bus low power request. */
    kPower_FC1_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 1U, PRIVATE_TSTAT0_OFFSET, 1U),   /*!< LP_FLEXCOMM1 bus low power request. */
    kPower_FC2_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 2U, PRIVATE_TSTAT0_OFFSET, 2U),   /*!< LP_FLEXCOMM2 bus low power request. */
    kPower_FC3_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 3U, PRIVATE_TSTAT0_OFFSET, 3U),   /*!< LP_FLEXCOMM3 bus low power request. */
    kPower_FC4_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 4U, PRIVATE_TSTAT0_OFFSET, 4U),   /*!< LP_FLEXCOMM4 bus low power request. */
    kPower_FC5_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 5U, PRIVATE_TSTAT0_OFFSET, 5U),   /*!< LP_FLEXCOMM5 bus low power request. */
    kPower_FC6_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 6U, PRIVATE_TSTAT0_OFFSET, 6U),   /*!< LP_FLEXCOMM6 bus low power request. */
    kPower_FC7_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 7U, PRIVATE_TSTAT0_OFFSET, 7U),   /*!< LP_FLEXCOMM7 bus low power request. */
    kPower_FC8_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 8U, PRIVATE_TSTAT0_OFFSET, 8U),   /*!< LP_FLEXCOMM8 bus low power request. */
    kPower_FC9_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 9U, PRIVATE_TSTAT0_OFFSET, 9U),   /*!< LP_FLEXCOMM9 bus low power request. */
    kPower_FC10_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 10U, PRIVATE_TSTAT0_OFFSET, 10U), /*!< LP_FLEXCOMM10 bus low power request. */
    kPower_FC11_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 11U, PRIVATE_TSTAT0_OFFSET, 11U), /*!< LP_FLEXCOMM11 bus low power request. */
    kPower_FC12_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 12U, PRIVATE_TSTAT0_OFFSET, 12U), /*!< LP_FLEXCOMM12 bus low power request. */
    kPower_FC13_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 13U, PRIVATE_TSTAT0_OFFSET, 13U), /*!< LP_FLEXCOMM13 bus low power request. */
    kPower_FC0_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 0U, PRIVATE_TSTAT0_OFFSET, 16U),  /*!< LP_FLEXCOMM0 function low power request. */
    kPower_FC1_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 1U, PRIVATE_TSTAT0_OFFSET, 17U),  /*!< LP_FLEXCOMM1 function low power request. */
    kPower_FC2_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 2U, PRIVATE_TSTAT0_OFFSET, 18U),  /*!< LP_FLEXCOMM2 function low power request. */
    kPower_FC3_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 3U, PRIVATE_TSTAT0_OFFSET, 19U),  /*!< LP_FLEXCOMM3 function low power request. */
    kPower_FC4_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 4U, PRIVATE_TSTAT0_OFFSET, 20U),  /*!< LP_FLEXCOMM4 function low power request. */
    kPower_FC5_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 5U, PRIVATE_TSTAT0_OFFSET, 21U),  /*!< LP_FLEXCOMM5 function low power request. */
    kPower_FC6_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 6U, PRIVATE_TSTAT0_OFFSET, 22U),  /*!< LP_FLEXCOMM6 function low power request. */
    kPower_FC7_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 7U, PRIVATE_TSTAT0_OFFSET, 23U),  /*!< LP_FLEXCOMM7 function low power request. */
    kPower_FC8_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 8U, PRIVATE_TSTAT0_OFFSET, 24U),  /*!< LP_FLEXCOMM8 function low power request. */
    kPower_FC9_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 9U, PRIVATE_TSTAT0_OFFSET, 25U),  /*!< LP_FLEXCOMM9 function low power request. */
    kPower_FC10_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 10U, PRIVATE_TSTAT0_OFFSET, 26U), /*!< LP_FLEXCOMM10 function low power request. */
    kPower_FC11_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 11U, PRIVATE_TSTAT0_OFFSET, 27U), /*!< LP_FLEXCOMM11 function low power request. */
    kPower_FC12_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 12U, PRIVATE_TSTAT0_OFFSET, 28U), /*!< LP_FLEXCOMM12 function low power request. */
    kPower_FC13_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL1_OFFSET, 13U, PRIVATE_TSTAT0_OFFSET, 29U), /*!< LP_FLEXCOMM13 function low power request. */

    kPower_GPIO0_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 0U, PRIVATE_TSTAT1_OFFSET, 2U),   /*!< GPIO0 low power request. */
    kPower_GPIO1_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 1U, PRIVATE_TSTAT1_OFFSET, 3U),   /*!< GPIO1 low power request. */
    kPower_GPIO2_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 2U, PRIVATE_TSTAT1_OFFSET, 4U),   /*!< GPIO2 low power request. */
    kPower_GPIO3_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 3U, PRIVATE_TSTAT1_OFFSET, 5U),   /*!< GPIO3 low power request. */
    kPower_GPIO4_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 4U, PRIVATE_TSTAT1_OFFSET, 6U),   /*!< GPIO4 low power request. */
    kPower_GPIO5_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 5U, PRIVATE_TSTAT1_OFFSET, 7U),   /*!< GPIO5 low power request. */
    kPower_GPIO6_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 6U, PRIVATE_TSTAT1_OFFSET, 8U),   /*!< GPIO6 low power request. */
    kPower_GPIO7_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 7U, PRIVATE_TSTAT1_OFFSET, 9U),   /*!< GPIO7 low power request. */
    kPower_SAI0_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 8U, PRIVATE_TSTAT1_OFFSET, 10U),  /*!< SAI0 low power request. */
    kPower_SAI1_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 9U, PRIVATE_TSTAT1_OFFSET, 11U),  /*!< SAI1 low power request. */
    kPower_SAI2_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 10U, PRIVATE_TSTAT1_OFFSET, 12U), /*!< SAI2 low power request. */
    kPower_TRNG_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 11U, PRIVATE_TSTAT1_OFFSET, 13U), /*!< TRNG stop request. */
    kPower_XSPI0_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 12U, PRIVATE_TSTAT1_OFFSET, 14U), /*!< XSPI0 stop request. */
    kPower_XSPI1_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 14U, PRIVATE_TSTAT1_OFFSET, 15U), /*!< XSPI1 stop request. */
    kPower_I3C0_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 16U, PRIVATE_TSTAT1_OFFSET, 16U), /*!< I3C0 stop request. */
    kPower_I3C1_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 17U, PRIVATE_TSTAT1_OFFSET, 17U), /*!< I3C1 stop request. */
    kPower_GDET0_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 18U, PRIVATE_TSTAT1_OFFSET, 0U),  /*!< GDET0 low power request. */
    kPower_GDET1_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL2_OFFSET, 19U, PRIVATE_TSTAT1_OFFSET, 1U),  /*!< GDET1 low power request. */
#else
    kPower_EDMA2_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_CCTRL0_OFFSET, 0U, PRIVATE_CSTAT0_OFFSET, 0U), /*!< EDMA2 stop request. */
    kPower_EDMA3_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_CCTRL0_OFFSET, 1U, PRIVATE_CSTAT0_OFFSET, 1U), /*!< EDMA3 stop request. */

    kPower_FC17_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 0U, PRIVATE_TSTAT0_OFFSET, 0U),  /*!< LP_FLEXCOMM17 bus low power request. */
    kPower_FC18_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 1U, PRIVATE_TSTAT0_OFFSET, 1U),  /*!< LP_FLEXCOMM18 bus low power request. */
    kPower_FC19_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 2U, PRIVATE_TSTAT0_OFFSET, 2U),  /*!< LP_FLEXCOMM19 bus low power request. */
    kPower_FC20_B_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 3U, PRIVATE_TSTAT0_OFFSET, 3U),  /*!< LP_FLEXCOMM20 bus low power request. */
    kPower_FC17_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 4U, PRIVATE_TSTAT0_OFFSET, 16U), /*!< LP_FLEXCOMM17 function low power request. */
    kPower_FC18_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 5U, PRIVATE_TSTAT0_OFFSET, 17U), /*!< LP_FLEXCOMM18 function low power request. */
    kPower_FC19_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 6U, PRIVATE_TSTAT0_OFFSET, 18U), /*!< LP_FLEXCOMM19 function low power request. */
    kPower_FC20_F_LPREQ = POWER_MAKE_LP_BITS(
        PRIVATE_TCTRL0_OFFSET, 7U, PRIVATE_TSTAT0_OFFSET, 19U), /*!< LP_FLEXCOMM20 function low power request. */
    kPower_SAI3_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL0_OFFSET, 8U, PRIVATE_TSTAT0_OFFSET, 4U),  /*!< SAI3 low power request. */
    kPower_GPIO8_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL0_OFFSET, 9U, PRIVATE_TSTAT0_OFFSET, 5U),  /*!< GPIO8 low power request. */
    kPower_GPIO9_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL0_OFFSET, 10U, PRIVATE_TSTAT0_OFFSET, 6U), /*!< GPIO9 low power request. */
    kPower_GPIO10_LPREQ =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL0_OFFSET, 11U, PRIVATE_TSTAT0_OFFSET, 7U), /*!< GPIO10 low power request. */
    kPower_I3C2_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL0_OFFSET, 20U, PRIVATE_TSTAT0_OFFSET, 8U), /*!< I3C2 low power request. */
    kPower_I3C3_STOP =
        POWER_MAKE_LP_BITS(PRIVATE_TCTRL0_OFFSET, 21U, PRIVATE_TSTAT0_OFFSET, 9U), /*!< I3C3 low power request. */
#endif
} lp_bit_t;

/*! @brief PMIC mode pin configuration API parameter */
typedef enum _pmic_mode_reg
{
    kCfg_Run   = 0xA0U, /*!< PDRUNCFG0 register offset. */
    kCfg_Sleep = 0xB8U, /*!< PDSLEEPCFG0 register offset. */
} pmic_mode_reg_t;

/*! @brief Power mode configuration API parameter */
typedef enum _power_mode_config
{
    kPower_Sleep              = 0U, /*!< Sleep mode. */
    kPower_DeepSleep          = 1U, /*!< Deep Sleep mode. */
    kPower_DeepSleepRetention = 2U, /*!< Deep Sleep Retention(DSR) mode. */
    kPower_DeepPowerDown      = 3U, /*!< Deep Power Down(DPD) mode. */
    kPower_FullDeepPowerDown  = 4U, /*!< Full Deep Power Down(FDPD) mode. */
} power_mode_cfg_t;

/*!
 * @brief DMA Wakeup sources.
 *
 */
enum _power_hwwake_src
{
    kPower_HWWakeSrcMicfil     = 0x1U, /*!< Enables DMA to wakeup by MICFIL DMA request.*/
    kPower_HWWakeSrcFlexio     = 0x2U, /*!< Enables DMA to wakeup by FLEXIO DMA request.*/
    kPower_HWWakeSrcLpFlexcomm = 0x4U, /*!< Enables DMA to wakeup by LP_FLEXCOMM0-13(CPU0), LP_FLEXCOMM17-20(CPU1) DMA
                                   request.*/
#if defined(SLEEPCON_COMPT)
    kPower_HWWakeSrcHsSpi = 0x8U,      /*!< Enables DMA to wakeup by LPSPI14 and LPSPI16 DMA request.*/
#endif
    kPower_HWWakeSrcSai = 0x10U,       /*!< Enables DMA to wakeup by SAI0-2(CPU0), SAI3(CPU1) request.*/
};

/*!
 * @brief Definition for shared resources.
 *
 */
enum _power_shared_resource_mask
{
    kPower_MaskAdc0    = 0x1U,      /*!< ADC0 mask.*/
    kPower_MaskAcmp0   = 0x2U,      /*!< ACMP0 mask.*/
    kPower_MaskMicfil  = 0x4U,      /*!< MICFIL mask.*/
    kPower_MaskLpi2c15 = 0x8U,      /*!< LPI2C15 mask.*/
    kPower_MaskGdet2   = 0x10U,     /*!< GDET2 mask.*/
    kPower_MaskGdet3   = 0x20U,     /*!< GDET3 mask.*/
    kPower_MaskRtc     = 0x40U,     /*!< RTC mask.*/
    kPower_MaskVgpu    = 0x10000U,  /*!< VGPU mask.*/
    kPower_MaskEzhv    = 0x20000U,  /*!< EZHV mask.*/
    kPower_MaskXspi2   = 0x40000U,  /*!< XSPI2 mask.*/
    kPower_MaskLpspi14 = 0x80000U,  /*!< LPSPI14 mask.*/
    kPower_MaskLpspi16 = 0x100000U, /*!< LPSPI16 mask.*/
    kPower_MaskFlexio  = 0x200000U, /*!< FlexIO mask.*/
    kPower_MaskNic0    = 0x400000U, /*!< NIC0 mask.*/
    kPower_MaskNic1    = 0x800000U, /*!< NIC1 mask.*/
    kPower_MaskAll     = 0xFF007FU, /*!< Mask all shared modules.*/
};

/*!
 * @brief pad voltage range value for the 3V capable IOs. To reduce power the IOs can be configured for 1.8V or 3.3V
operation, powering down the detector, but requiring the application to restrict the IO supply voltage to the selected
range.
 */
typedef enum _power_pad_vrange_val
{
    kPadVol_Continuous = 0U, /*!< Continuous mode, VDDE detector on. */
    kPadVol_171_198    = 1U, /*!< Voltage from 1.71V to 1.98V. supply detector off. */
    kPadVol_300_360    = 2U, /*!< Voltage from 3.00V to 3.60V. supply detector off. */
} power_pad_vrange_val_t;

/*! @brief Body Bias domain definition */
enum _body_bias_domain
{
    kPower_BodyBiasVdd2Sram = PMC_PDRUNCFG0_RBBSR2_PD_MASK, /*!< VDD2 domain RAMs. */
    kPower_BodyBiasVdd1Sram = PMC_PDRUNCFG0_RBBSR1_PD_MASK, /*!< VDD1 domain RAMs. */
    kPower_BodyBiasVddn     = PMC_PDRUNCFG0_RBBN_PD_MASK,   /*!< VDDN domain. */
    kPower_BodyBiasVdd2     = PMC_PDRUNCFG0_RBB2_PD_MASK,   /*!< VDD2 domain. */
    kPower_BodyBiasVdd1     = PMC_PDRUNCFG0_RBB1_PD_MASK,   /*!< VDD1 domain. */
};

/*! @brief Regulator definition for Regulator and LVD configuration. */
typedef enum _power_regulator
{
    kRegulator_DCDC    = 0U, /*!< DCDC used for VDDN. */
    kRegulator_Vdd2LDO = 1U, /*!< VDD2 LDO. */
    kRegulator_Vdd1LDO = 2U, /*!< VDD1 LDO. */
} power_regulator_t;

/*!
 * @brief Regulator voltage configuraton. Configure the regulator voltage in uV.
 */
typedef union _power_regulator_voltage
{
    struct
    {
        uint32_t vsel0; /*!< DCDC VSEL0. Voltage = 0.5 V + 6.25 mV * value of vsel0. Maximum value = 1150000uV. */
        uint32_t vsel1; /*!< DCDC VSEL1. Voltage = 0.5 V + 6.25 mV * value of vsel1. Maximum value = 1150000uV. */
    } DCDC;
    struct
    {
        uint32_t vsel0; /*!< LDO VSEL0. Voltage = 0.45 V + 12.5 mV * vsel0. Maximum value = 1150000uV. */
        uint32_t vsel1; /*!< LDO VSEL1. Voltage = 0.45 V + 12.5 mV * vsel1. Maximum value = 1150000uV.*/
        uint32_t vsel2; /*!< LDO VSEL2. Voltage = 0.45 V + 12.5 mV * vsel2. Maximum value = 1150000uV. */
        uint32_t vsel3; /*!< LDO VSEL3. Voltage = 0.45 V + 12.5 mV * vsel3. Maximum value = 1150000uV. */
    } LDO;
    uint32_t vsel[4];
} power_regulator_voltage_t;

/*!
 * @brief LDO mode definition.
 */
enum _power_ldo_mode
{
    kPower_LDOMode_Bypass = 0U, /*!< LDO Bypass mode. */
    kPower_LDOMode_HP     = 1U, /*!< LDO High Power mode. */
    kPower_LDOMode_LP     = 2U, /*!< LDO Low Power mode. */
};

/*!
 * @brief DCDC mode definition.
 */
enum _power_dcdc_mode
{
    kPower_DCDCMode_HP = 0U, /*!< LDO High Power mode. */
    kPower_DCDCMode_LP = 1U, /*!< LDO Low Power mode. */
};

/*! @brief VDDN, VDD1 or VDD2 supply source. */
typedef enum _power_vdd_src
{
    kVddSrc_PMC  = 0U, /*!< Supplied by onchip regulator in PMC, DCDC for VDDN, LDO1 for VDD1, LDO2 for VDD2. */
    kVddSrc_PMIC = 1U, /*!< Supplied by external PMIC. */
} power_vdd_src_t;

/*!
 * @brief LVD voltage configuraton. Configure the LVD voltage in uV. Falling trip = 0.5V + 10 mV * bitfield value.
 */
typedef union _power_lvd_voltage
{
    struct
    {
        uint32_t lvl0; /*!< VDDN LVD level0, uV. */
        uint32_t lvl1; /*!< VDDN LVD level1, uV. */
    } VDDN;
    struct
    {
        uint32_t lvl0; /*!< VDD1/2 LVD level0, uV. */
        uint32_t lvl1; /*!< VDD1/2 LVD level1, uV. */
        uint32_t lvl2; /*!< VDD1/2 LVD level2, uV. */
        uint32_t lvl3; /*!< VDD1/2 LVD level3, uV. */
    } VDD12;
    uint32_t lvl[4];
} power_lvd_voltage_t;

#if defined(PMC0)

/*! @brief Internal Regulator and LDO power control bits */
enum _power_regulator_pd_control
{
    kPower_SCPC    = PMC_POWERCFG_SCPCPD_MASK, /*!< SCPC Power control, controls both SCPCs, for all power mode. */
    kPower_Vdd1LDO = PMC_POWERCFG_LDO1PD_MASK, /*!< LDO VDD1 Power control, for all power mode. */
    kPower_Vdd2LDO = PMC_POWERCFG_LDO2PD_MASK, /*!< LDO VDD2 Power control, for all power mode. */
    kPower_DCDC    = PMC_POWERCFG_DCDCPD_MASK, /*!< DCDC Power control, for all power mode. */
};

/*! @brief Internal Regulator and LDO power control bits for FDSR power mode. */
enum _power_regulator_pd_control_fdsr
{
    kPower_Vdd1SCPC_FDSR =
        PMC_POWERCFG_FDSCP1PD_MASK, /*!< SCPC VDD1 Power control in FDSR mode, overridden when [SCPCPD]=1. */
    kPower_Vdd2SCPC_FDSR =
        PMC_POWERCFG_FDSCP2PD_MASK, /*!< SCPC VDD2 Power control in FDSR mode, overridden when [SCPCPD]=1. */
    kPower_Vdd1LDO_FDSR =
        PMC_POWERCFG_FDLDO1PD_MASK, /*!< LDO VDD1 Power control in FDSR mode, overridden when [LPO1PD]=1. */
    kPower_Vdd2LDO_FDSR =
        PMC_POWERCFG_FDLDO2PD_MASK, /*!< LDO VDD2 Power control in FDSR mode, overridden when [LPO2PD]=1. */
    kPower_DCDC_FDSR = PMC_POWERCFG_FDDCPD_MASK, /*!< DCDC Power control in FDSR mode, overridden when [DCDCPD]=1. */
};

/*! @brief RBB Body Bias voltage definition */
typedef enum _body_bias_voltage
{
    kBodyBias_1V0 = 0U, /*!< Reverse Body Bias Voltage 1.0V. */
    kBodyBias_1V3 = 1U, /*!< Reverse Body Bias Voltage 1.3V. */
} body_bias_voltage_t;

/*!
 * @brief RBB Body Bias voltage. 0b - Voltage is set to 1.0V, 1b - Voltage is set to 1.3V.
 */
typedef struct _power_rbb_voltage
{
    uint32_t rbbVdd1 : 1; /*!< Reverse Body Bias Voltage for VDD1 Domain. @ref body_bias_voltage_t */
    uint32_t : 7;         /*!< Reserved. */
    uint32_t rbbVdd2 : 1; /*!< Reverse Body Bias Voltage for VDD2 Domain. @ref body_bias_voltage_t */
    uint32_t : 7;         /*!< Reserved. */
    uint32_t rbbVddn : 1; /*!< Reverse Body Bias Voltage for VDDN Domain. @ref body_bias_voltage_t */
    uint32_t : 15;        /*!< Reserved. */
} power_rbb_voltage_t;

/*!
 * @brief POR voltage. Falling trip voltage = 0.4 + 10 mV * value.
 */
typedef struct _power_por_voltage
{
    uint32_t Vdd1Lvl : 5; /*!< POR falling trip value in VDD1 Domain, falling trip voltage = 0.4 + 10 mV * value. */
    uint32_t : 3;         /*!< Reserved. */
    uint32_t Vdd2Lvl : 5; /*!< POR falling trip value in VDD2 Domain, falling trip voltage = 0.4 + 10 mV * value. */
    uint32_t : 3;         /*!< Reserved. */
    uint32_t VddnLvl : 5; /*!< POR falling trip value in VDDN Domain, falling trip voltage = 0.4 + 10 mV * value. */
} power_por_voltage_t;

/*! @brief IO Banking bitmask.  */
typedef enum _power_io_bank
{
    kPower_IOBank0 = 0x1U,  /*!< Port 0/1/3 in VDD2_COM domain. */
    kPower_IOBank1 = 0x2U,  /*!< Port 2 in VDD2_COM domain. */
    kPower_IOBank2 = 0x4U,  /*!< Port 4 in VDDN_COM domain. */
    kPower_IOBank3 = 0x8U,  /*!< Port 5 in VDD2_COM domain. */
    kPower_IOBank4 = 0x10U, /*!< Port 6 in VDD2_COM domain. */
    kPower_IOBank5 = 0x20U, /*!< Port 7 in VDD2_COM domain. */
    kPower_IOBank6 = 0x40U, /*!< Port 8/9/10 in VDD1_SENSE domain. */
    kPower_IOBank7 = 0x80U, /*!< PMIC_I2C in VDD1_SENSE domain. */
} power_io_bank_t;
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief API to enable PDRUNCFG bit in the SLEEPCON and PMC. Note that enabling the bit powers down the peripheral
 *
 * @param en    peripheral for which to enable the PDRUNCFG bit
 */
void POWER_EnablePD(pd_bit_t en);

/*!
 * @brief API to disable PDRUNCFG bit in the SLEEPCON and PMC. Note that disabling the bit powers up the peripheral
 *
 * @param en    peripheral for which to disable the PDRUNCFG bit
 */
void POWER_DisablePD(pd_bit_t en);

/*!
 * @brief API to request a module entering low power. This API send low power/stop requests to a module and wait the
acknowledgement from the module. For peripherals that are being used by a domain, using this low power request handshake
is recommended to make sure the module is fully stopped before the module is powered down or clock gated.
 *
 * @param en    peripheral for which to enable the low power request.
 * @return  kStatus_Success for succeed, kStatus_Timeout for tiemout.
 */
status_t POWER_ModuleEnterLPRequest(lp_bit_t en);

/*!
 * @brief API to negate low power/stop requests to a module(module resume regular operation).
 *
 * @param en peripheral for which to disable the low power request.
 */
void POWER_ModuleExitLPRequest(lp_bit_t en);

/*!
 * @brief   Set PMIC_MODE pins configure value.
 * @param   mode : PMIC MODE pin value. This field is aggregated low.
 * @param   reg : PDSLEEPCFG0 or PDRUNCFG0 register offset
 * @return  PMIC_MODE pins value in PDSLEEPCFG0
 */
void POWER_SetPmicMode(uint32_t mode, pmic_mode_reg_t reg);

/**
 * @brief   Get PMIC_MODE pins configure value.
 * @param   reg : PDSLEEPCFG0 or PDRUNCFG0 register offset
 * @return  PMIC_MODE pins value in PDSLEEPCFG0 or PDRUNCFG0
 */
uint32_t POWER_GetPmicMode(pmic_mode_reg_t reg);

#if defined(PMC0)
/*!
 * @brief Configure pad voltage level for the 3V capable IOs(FLEXIO pads only) which have a dectector to sense the value
 * of supply. The Continuous cost more power due to enabled voltage detector.
 *
 * NOTE: BE CAUTIOUS TO CALL THIS API. IF THE PAD SUPPLY IS BEYOND THE SET RANGE, SILICON MIGHT BE DAMAGED.
 *
 * @param vrange pad voltage range.
 */
static inline void POWER_SetPio2VoltRange(power_pad_vrange_val_t vrange)
{
    PMC0->PADVRANGE = (uint32_t)vrange & PMC_PADVRANGE_VRANGE_MASK;
}
#endif

/*!
 * @brief API to enable deep sleep bit in the ARM Core.
 */
static inline void POWER_EnableDeepSleep(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

/*!
 * @brief API to disable deep sleep bit in the ARM Core.
 */
static inline void POWER_DisableDeepSleep(void)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

/*!
 * @brief API to apply updated PMC PDRUNCFG bits in the Sysctl0.
 */
void POWER_ApplyPD(void);

/**
 * @brief   Clears the PMC event flags state.
 * @param   statusMask : A bitmask of event flags that are to be cleared.
 */
void POWER_ClearEventFlags(uint32_t statusMask);

/**
 * @brief   Get the PMC event flags state.
 * @return  PMC FLAGS register value
 */
uint32_t POWER_GetEventFlags(void);

/*!
 * @brief   Enable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of interrupts to enable.
 */
void POWER_EnableInterrupts(uint32_t interruptMask);

/*!
 * @brief   Disable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of interrupts to disable.
 */
void POWER_DisableInterrupts(uint32_t interruptMask);

/*!
 * @brief   Enable the PMC reset requests.
 * @param   resetMask : A bitmask of Reset to enable, refer to PMC CTRL register descritpion in RM.
 */
void POWER_EnableResets(uint32_t resetMask);

/*!
 * @brief   Disable the PMC reset requests.
 * @param   resetMask : A bitmask of Reset to disable, refer to PMC CTRL register descritpion in RM.
 */
void POWER_DisableResets(uint32_t resetMask);

/*!
 * @brief Enable specific interrupt for wake-up from deep-sleep mode.
 * Enable the interrupt for wake-up from deep sleep mode.
 * Some interrupts are typically used in sleep mode only and will not occur during
 * deep-sleep mode because relevant clocks are stopped. However, it is possible to enable
 * those clocks (significantly increasing power consumption in the reduced power mode),
 * making these wake-ups possible.
 * @note This function also enables the interrupt in the NVIC (EnableIRQ() is called internally).
 * @param interrupt The IRQ number.
 */
void EnableDeepSleepIRQ(IRQn_Type interrupt);

/*!
 * @brief Disable specific interrupt for wake-up from deep-sleep mode.
 * Disable the interrupt for wake-up from deep sleep mode.
 * Some interrupts are typically used in sleep mode only and will not occur during
 * deep-sleep mode because relevant clocks are stopped. However, it is possible to enable
 * those clocks (significantly increasing power consumption in the reduced power mode),
 * making these wake-ups possible.
 * @note This function also disables the interrupt in the NVIC (DisableIRQ() is called internally).
 * @param interrupt The IRQ number.
 */
void DisableDeepSleepIRQ(IRQn_Type interrupt);

/*!
 * @brief Enable specific DMA channels to generate a wake-up from deep-sleep mode.
 * DMA wakeup is an automatic hardware mechanism that handles DMA transactions for selected modules without the need for
 * core processing. Software can configure individual DMA channels to generate a wakeup when they receive a DMA request.
 * The DMA wakeup triggers an exit from Deep Sleep mode except the core, which remains sleeping.
 * @param sources The bits mask for eDMA wakeup sources. Refers #_power_hwwake_src.
 */
void POWER_EnableDMAHWWake(uint32_t sources);

/*!
 * @brief Disable specific DMA channels to generate a wake-up from deep-sleep mode.
 * Disable the DMA channels for wake-up from deep sleep mode.
 * @param sources The bits mask for eDMA wakeup sources. Refers #_power_hwwake_src.
 */
void POWER_DisableDMAHWWake(uint32_t sources);

/*!
 * @brief   Configure PMC for auto wakeup.This feature allows PMC to wake up some amount of time after the domain enters
 * Deep Sleep. The timer is clocked by PMC's internal 16 MHz clock. If both timers in compute and sense are enabled at
 * the same time, wake-up will occur after BOTH timers time out (i.e. the max timeout value between the two is used).
 * @param   ticks : The ticks of 16MHz PMC internal clock to wait before waking up the domain after it goes to
 * DeepSleep.
 */
void POWER_EnableAutoWake(uint16_t ticks);

/*!
 * @brief Enable low power request masking for shared modules.
 * Enabling the mask will relinquish the caller domain's control over the module, and give the other domain exclusive
 * control over low-power requests to the module.
 * NOTE,  The masking of a shared module must NOT be disabled in both Compute and Sense domain.
 *
 * @param mask An OR'd bitmask of shared modules to be masked from low power request, ref @ref
 * _power_shared_resource_mask and SLEEPCON SHARED_MASK0 register in the RM. DeepSleep.
 */
void POWER_EnableLPRequestMask(uint32_t mask);

/*!
 * @brief Disable low power request masking for shared modules.
 * Disabling the mask means this domain will own the module. Only one domain should own each shared module.
 *
 * @param mask An OR'd bitmask of shared modules to be enabled from low power request, ref @ref
 * _power_shared_resource_mask and SLEEPCON SHARED_MASK0 register in the RM. DeepSleep.
 */
void POWER_DisableLPRequestMask(uint32_t mask);

/*!
 * @brief Enable AFBB mode for various domains in active mode.
 * AFBB mode should always be used for domains that are active/clocked.
 * Note, users should call POWER_ApplyPD() to make the change take effect.
 * @param mask : A bitmask of domains to enable AFBB mode, refer to @ref _body_bias_domain and PMC PDRUNCFG0 register
 * descritpion in RM.
 */
void POWER_EnableRunAFBB(uint32_t mask);

/*!
 * @brief Enable RBB mode for various domains in active mode.
 * This function should only be used when one CPU will not be making use of one of the voltage domains.Configuring the
 * unused voltages for RBB will allow the other domain to have full control of the body bias mode for the voltages even
 * when both domains are in run mode.
 * Note, users should call POWER_ApplyPD() to make the change take effect.
 * @param mask : A bitmask of domains to enable RBB mode, refer to @ref _body_bias_domain and PMC PDRUNCFG0 register
 * descritpion in RM.
 */
void POWER_EnableRunRBB(uint32_t mask);

/*!
 * @brief Enable RBB mode for various domains in deep sleep mode.
 * @param mask : A bitmask of domains to enable RBB mode, refer to @ref _body_bias_domain and PMC PDSLEEPCFG0 register
 * descritpion in RM.
 */
void POWER_EnableSleepRBB(uint32_t mask);

/*!
 * @brief Enable NBB mode for various domains in active mode.
 * NBB can be a lower power option than RBB if the domain enters and exits low-power modes frequently since the wells
 * don't charge and discharge as much on every entry/exit.
 * @param mask : A bitmask of domains to enable NBB mode, refer to @ref _body_bias_domain and PMC PDRUNCFG0 register
 * descritpion in RM.
 */
void POWER_EnableRunNBB(uint32_t mask);

/*!
 * @brief Enable NBB mode for various domains in deep sleep mode.
 * NBB can be a lower power option than RBB if the domain enters and exits low-power modes frequently since the wells
 * don't charge and discharge as much on every entry/exit.
 * @param mask : A bitmask of domains to enable NBB mode, refer to @ref _body_bias_domain and PMC PDSLEEPCFG0 register
 * descritpion in RM.
 */
void POWER_EnableSleepNBB(uint32_t mask);

#if defined(PMC0)

/*!
 * @brief Configure the voltage used for RBB mode for each voltage domain. The voltage specified here is used for any
 * mode where RBB is enabled.
 * @param config Voltage selection for each voltage domain.
 */
void POWER_ConfigRBBVolt(const power_rbb_voltage_t *config);

/*!
 * @brief Disable the on-chip regulators.
 * This function should be used to disable the on-chip regulators for any supplies that will be powered externally
 * (regulators are enabled by default. If disabled the regulators will keep power down until next cold reset).
 * @param mask A bitmask of regulators to be powered down, @ref _power_regulator_pd_control and PMC POWERCFG register
 * descripion in RM.
 */
void POWER_DisableRegulators(uint32_t mask);

/*!
 * @brief Enable the on-chip regulators for FDSR mode.
 * This function is used to enable the on-chip regulators for FDSR power mode.
 * Note, If the regulator is disabled globally(by POWER_DisableRegulators), then they will automatically be powered down
 * in all modes (using this API to request enabling them will have no effect).
 * @param mask A bitmask of regulators to be controlled, @ref _power_regulator_pd_control_fdsr and PMC POWERCFG register
descripion in RM.
*/
void POWER_EnableSleepRegulators(uint32_t mask);

/*!
 * @brief Disable the on-chip regulators for FDSR mode.
 * This function is used to enable the on-chip regulators for FDSR power mode.
 * Note, If the regulator is disabled globally(by POWER_DisableRegulators), then they will automatically be powered down
 * in all modes.
 * @param mask A bitmask of regulators to be controlled, @ref _power_regulator_control_fdsr and PMC POWERCFG register
 * descripion in RM.
 */
void POWER_DisableSleepRegulators(uint32_t mask);

/*!
 * @brief Set VDDN supply source, PMIC or on-chip regulator. When PMIC selected the on-chip regulator will be powered
 * down.
 * @param   src : #power_vdd_src_t, VDDN supply source
 */
void POWER_SetVddnSupplySrc(power_vdd_src_t src);

/*!
 * @brief Set VDD1 supply source, PMIC or on-chip regulator. When PMIC selected the on-chip regulator will be powered
 * down.
 * @param   src : #power_vdd_src_t, VDDN supply source
 */
void POWER_SetVdd1SupplySrc(power_vdd_src_t src);

/*!
 * @brief Set VDD2 supply source, PMIC or on-chip regulator. When PMIC selected the on-chip regulator will be powered
 * down.
 * @param   src : #power_vdd_src_t, VDDN supply source
 */
void POWER_SetVdd2SupplySrc(power_vdd_src_t src);

/*!
 * @brief API to configure the delay for PMIC mode changes.
 * Any time the PMIC_MODE pin values change the PMC will wait for the delay specified here to allow time for the
 * external voltages to settle. Delay time = 250ns * 2^value. Note, need call POWER_ApplyPD() to make the change take
 * effect.
 *
 * @param value Delay value, the calculated delay time(ns) = 250ns*2^value.
 */
void POWER_SetPMICModeDelay(uint8_t value);

/*!
 * @brief Sets the POR falling trip voltages in VDD1, VDD2, and VDDN domains.
 * When the supply voltage falls below the selected trip voltage, it triggers a cold reset.
 * Falling trip = 0.4 + 10 mV * value
 *
 * @param porVolt A bitmask of values to control VDD1, VDD2, VDDN POR voltage.
 */
void POWER_SetPORVoltage(const power_por_voltage_t *porVolt);
#endif /* PMC0 */

/*!
 * @brief Configure the setpoint operation for on-chip regulators and LVD.
 * This function can configure both the target output voltages and LVD levels for each setpoint. The setpoint that is
 * actually selected is controlled by the aggregated value of PDRUNCFG[xxx_VSEL] and PDSLEEPCFG0[xxx_VSEL]. Use the
 * POWER_SelectRunSetpoint() or POWER_SelectSleepSetpoint() to configure the setpoint selections. The voltages selected
 * for each regulator must also be in ascending order (VSEL0 <= VSEL1 <= VSEL2 <= VSEL3). The voltages selected for each
 * LVD must also be in ascending order (LVL0 <= LVL1 <= LVL2 <= LVL3).
 *
 * NOTE, Only valid regulator for sense domain is VDD1 LDO.
 * Note, LDOVDD1VSEL and LVDVDD1CTRL are shared between the compute and sense domains. There is no aggregation to
 * combine the values. Whichever domain wrote the register last determines the value. It is recommended that only one
 * domain be used to configure VDD1 setpoints.
 *
 * @code
 *   const power_regulator_voltage_t regulator = {
 *     .LDO.vsel0 = 700000,
 *     .LDO.vsel1 = 800000,
 *     .LDO.vsel2 = 900000,
 *     .LDO.vsel3 = 1000000,
 *   };
 *   const power_lvd_voltage_t lvd = {
 *     .VDD12.lvl0 = 600000,
 *     .VDD12.lvl1 = 700000,
 *     .VDD12.lvl2 = 800000,
 *     .VDD12.lvl3 = 900000,
 *   };
 *
 *   ret = POWER_ConfigRegulatorSetpoints(kRegulator_Vdd1LDO, &regulator, &lvd);
 * @endcode
 * @param regulator which regulator or power domain to configure, refer to @ref power_regulator_t.
 * @param volt regulator configuration pointer, refer to @ref power_regulator_voltage_t. Note, only two setpoints are
 * available for DCDC.
 * @param lvd LVD voltage configuration, refer to @ref power_lvd_voltage_t.
 * @return kStatus_Success for succeed, kStatus_InvalidArgument for wrong arguments.
 */
status_t POWER_ConfigRegulatorSetpoints(power_regulator_t regulator,
                                        const power_regulator_voltage_t *volt,
                                        const power_lvd_voltage_t *lvd);

/*!
 * @brief Configure the setpoint operation for LVD.
 * This function can configure LVD levels for each setpoint. The setpoint that is actually selected is controlled by
 * the aggregated value of PDRUNCFG[xxx_VSEL] and PDSLEEPCFG0[xxx_VSEL]. Use the POWER_SelectRunSetpoint() or
 * POWER_SelectSleepSetpoint() to configure the setpoint selections. The voltages selected for each LVD must be in
 * ascending order (LVL0 <= LVL1 <= LVL2 <= LVL3).
 *
 * NOTE, Only valid regulator for sense domain is VDD1 LDO.
 * Note, LDOVDD1VSEL and LVDVDD1CTRL are shared between the compute and sense domains. There is no aggregation to
 * combine the values. Whichever domain wrote the register last determines the value. It is recommended that only one
 * domain be used to configure VDD1 setpoints.
 *
 * @code
 *   const power_lvd_voltage_t lvd = {
 *     .VDD12.lvl0 = 600000,
 *     .VDD12.lvl1 = 700000,
 *     .VDD12.lvl2 = 800000,
 *     .VDD12.lvl3 = 900000,
 *   };
 *
 *   ret = POWER_ConfigLvdSetpoints(kRegulator_Vdd1LDO, &lvd);
 * @endcode
 * @param regulator which regulator or power domain to configure, refer to @ref power_regulator_t.
 * @param lvd LVD voltage configuration, refer to @ref power_lvd_voltage_t.
 * @return kStatus_Success for succeed, kStatus_InvalidArgument for wrong arguments.
 */
status_t POWER_ConfigLvdSetpoints(power_regulator_t regulator, const power_lvd_voltage_t *lvd);

/*!
 * @brief Get the LVD setpoints configurations.
 * This function can get the LVD levels for each setpoint. The setpoint that is actually selected is controlled by
 * the aggregated value of PDRUNCFG[xxx_VSEL] and PDSLEEPCFG0[xxx_VSEL].
 *
 * NOTE, Only valid regulator for sense domain is VDD1 LDO.
 *
 * @param regulator which regulator or power domain to get, refer to @ref power_regulator_t.
 * @param lvd LVD voltage configuration, refer to @ref power_lvd_voltage_t.
 */
void POWER_GetLvdSetpoints(power_regulator_t regulator, power_lvd_voltage_t *lvd);

/*!
 * @brief Select the setpoint(target voltage and LVD threshold) for active mode.
 * The requests from the compute and sense domains are aggregated, so depending on the other
domain's configuration the setpoint might not change or might change later (when the other domain
also requests a setpoint change).
 * Note, users should call POWER_ApplyPD() to make the change take effect.
 *
 * @param regulator which regulator or power domain to configure, refer to @ref power_regulator_t.
 * @param setpoint select which setpoint is used. Valid options for DCDC are 0-1. Valid options for VDD1/VDD2 are 0-3.
 */
void POWER_SelectRunSetpoint(power_regulator_t regulator, uint32_t setpoint);

/*!
 * @brief Select setpoint(target voltage and LVD threshold) in Deep Sleep (or lower) mode.
 * Use POWER_ConfigRegulatorSetpoints() to change the target voltage and/or LVD threshold value corresponding to each
 * setpoint. The requests from the compute and sense domains are aggregated,
 *
 * @param regulator which regulator or power domain to configure, refer to @ref power_regulator_t.
 * @param setpoint select which setpoint is used. Valid options for DCDC are 0-1. Valid options for VDD1/VDD2 are 0-3.
 */
void POWER_SelectSleepSetpoint(power_regulator_t regulator, uint32_t setpoint);

/*!
 * @brief Set the on-chip regulator mode in Run/Active mode.
 * The requests from the compute and sense domains are aggregated.
 *
 * @param regulator which regulator or power domain to configure, refer to @ref power_regulator_t.
 * @param mode set the workmode. Refer to @ref _power_dcdc_mode for available DCDC modes, refer to @ref _power_ldo_mode
 * for LDO available modes.
 */
void POWER_SetRunRegulatorMode(power_regulator_t regulator, uint32_t mode);

/*!
 * @brief Set the on-chip regulator mode in Deep Sleep mode.
 * The requests from the compute and sense domains are aggregated.
 *
 * @param regulator which regulator or power domain to configure, refer to @ref power_regulator_t.
 * @param mode set the workmode. Refer to @ref _power_dcdc_mode for available DCDC modes, refer to @ref _power_ldo_mode
 * for LDO available modes.
 */
void POWER_SetSleepRegulatorMode(power_regulator_t regulator, uint32_t mode);

/*!
 * @brief Reset the IO bank.
 * Sets the IO bank reset which tristates the ports. Intended to be used prior to powering off the VDDIO supplies.
 *
 * @param mask A bitmask of IO Banks to be reseted, @ref power_io_bank_t and PMC PADCFG register. The register reset by
 * cold reset.
 */
void POWER_ResetIOBank(uint32_t mask);

/*!
 * @brief IO Bank Isolation Hold.
 *  Maintains IO bank isolation state after wake-up from FDSR/DPD modes. If clear, the IO bank's state will be retained
 * during FDSR & DPD modes, but will be controllable after wake-up. If set, the IO bank will remain in retain mode until
 * ISOCTRL cleared by software.
 *
 * @param mask A bitmask of IO Banks to be set, @ref power_io_bank_t and PMC PADCFG register. The register reset by cold
 * reset.
 */
void POWER_IOBankIsolationHold(uint32_t mask);

/*!
 * @brief Clear the IO bank Isolation Hold and regain state control.
 * This bit cannot be cleared if associated domain is not powered.
 *
 * @param mask A bitmask of IO Banks to be clear, @ref power_io_bank_t and PMC PADCFG register. The register reset by
 * cold reset.
 */
void POWER_IOBankClearIsolationHold(uint32_t mask);

/**
 * @brief   Configures and enters in SLEEP low power mode
 */
void POWER_EnterSleep(void);

/*!
 * @brief PMC Deep Sleep function call
 *
 * NOTE, the body bias and DCDC, LDO configurations in PMC_PDSLEECFG0 is not covered by this API, please use
 * @ref POWER_EnableSleepRBB or @ref POWER_EnableSleepNBB and @ref POWER_SelectSleepSetpoint for those settings.
 *
 * NOTE, the MAINPLL and AUDIO PLL need special power up sequence, so it can't be power down/on automatically during the
 * mode change. Application need turn off the PLL before the low power mode entry and re-initialize the PLL after
 * wakeup.
 * @param   exclude_from_pd  Bit mask of the SLEEPCON_SLEEPCFG and PMC_PDSLEEPCFG0 ~ PMC_PDSLEEPCFG5 that needs to be
 * powered on during Deep Sleep mode. The configuration for PMC from Compute domain and Sense domain are aggregated, and
 * the higher power mode always wins.
 */
void POWER_EnterDeepSleep(const uint32_t exclude_from_pd[7]);

#if defined(PMC0)
/*!
 * @brief Compute domain enter Deep Sleep Retention mode API.
 * Deep Sleep Retention (DSR) mode is a deeper low power state than Deep Sleep mode.  DSR does not provide the option to
 * keep selected module clocks on for wake-up. DSR mode allows significant portions of the chip to be powered-down while
 * maintaining some level of state retention.
 *
 * NOTE, the body bias and DCDC, LDO configurations in PMC_PDSLEECFG0 is not covered by this API, please use
 * @ref POWER_EnableSleepRBB or @ref POWER_EnableSleepNBB and @ref POWER_SelectSleepSetpoint for those settings.
 *
 * NOTE, the MAINPLL and AUDIO PLL need special power up sequence, so it can't be power down/on automatically during the
 * mode change. Application need turn off the PLL before the low power mode entry and re-initialize the PLL after
 * wakeup.
 *
 * @param   exclude_from_pd  Bit mask of the SLEEPCON_SLEEPCFG and PMC_PDSLEEPCFG0 ~ PMC_PDSLEEPCFG5 that needs to be
 * powered on(bits cleared) during the power mode. The configuration for PMC from Compute domain and Sense domain are
 * aggregated, and the higher power mode always wins.
 */
void POWER_EnterDSR(const uint32_t exclude_from_pd[7]);
#else
/*!
 * @brief Sense domain requests entering Deep Sleep Retention mode API. Deep Sleep Retention (DSR) mode is a deeper low
 * power state than Deep Sleep mode. DSR mode allows significant portions of the chip to be powered-down while
 * maintaining some level of state retention. The Sense domain can enter DSR mode only when all other domains are in DSR
 * mode. If the condition is false, the sense domain will be in a shallower power mode(Deep sleep mode).
 *
 * NOTE, the body bias and DCDC, LDO configurations in PMC_PDSLEECFG0 is not covered by this API, please use
 * @ref POWER_EnableSleepRBB or @ref POWER_EnableSleepNBB and @ref POWER_SelectSleepSetpoint for those settings.
 *
 * @param   exclude_from_pd  Bit mask of the SLEEPCON_SLEEPCFG and PMC_PDSLEEPCFG0 ~ PMC_PDSLEEPCFG5 that needs to be
 * powered on(bits cleared) during the power mode. The configuration for PMC from Compute domain and Sense domain are
 * aggregated, and the higher power mode always wins.
 */
void POWER_RequestDSR(const uint32_t exclude_from_pd[7]);
#endif
/*!
 * @brief The domain requests to enter Deep Power Down mode.
 * The Deep Power Down and Full Deep Power Down can occur only when both domains signal their intent to enter these
 * lower power modes. The configuration for PMC from Compute domain and Sense domain are aggregated, and the higher
 * power mode always wins.
 *
 * @param exclude_from_pd  Bit mask of the SLEEPCON_SLEEPCFG and PMC_PDSLEEPCFG0 ~ PMC_PDSLEEPCFG5 that needs to be
 * powered on during Deep Power Down.
 */
void POWER_RequestDeepPowerDown(const uint32_t exclude_from_pd[7]);

/*!
 * @brief The domain requests to enter Full Deep Power Down mode.
 * The Deep Power Down and Full Deep Power Down can occur only when both domains signal their intent to enter these
 * lower power modes. The configuration for PMC from Compute domain and Sense domain are aggregated, and the higher
 * power mode always wins.
 *
 * @param   exclude_from_pd  Bit mask of the SLEEPCON_SLEEPCFG and PMC_PDSLEEPCFG0 ~ PMC_PDSLEEPCFG5 that needs to be
 * powered on during Deep Power Down.
 */
void POWER_RequestFullDeepPowerDown(const uint32_t exclude_from_pd[7]);

/*!
 * @brief Power Library API to request entering different power mode. This API is used for requesting entering the
 * target mode, the final SOC power mode depends on hardware aggregation. Note, the Sense domain can enter DSR mode only
 * when Compute domain is in DSR. The SOC enters DPD or FDPD when both domain requested entering DPD or FDPD.
 *
 * @param mode  Power mode to enter.
 * @param exclude_from_pd  Bit mask of the SLEEPCON_SLEEPCFG and PMC_PDSLEEPCFG0 ~ PMC_PDSLEEPCFG5 that needs to be
 * powered on during power mode selected.
 */
void POWER_EnterPowerMode(power_mode_cfg_t mode, const uint32_t exclude_from_pd[7]);

/*!
 * @brief Power Library API to return the library version.
 *
 * @return version number of the power library
 */
uint32_t POWER_GetLibVersion(void);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* FSL_POWER_H_ */
