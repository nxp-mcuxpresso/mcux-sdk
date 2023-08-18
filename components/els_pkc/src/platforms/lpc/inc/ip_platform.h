/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
/*                                                                          */
/* All rights are reserved. Reproduction in whole or in part is prohibited  */
/* without the prior written consent of the copy-right owner.               */
/* This source code and any compilation or derivative thereof is the sole   */
/* property of NXP N.V. and is provided pursuant to a Software License      */
/* Agreement. This code is the proprietary information of NXP N.V. and      */
/* is confidential in nature. Its use and dissemination by any party other  */
/* than NXP N.V. is strictly limited by the confidential information        */
/* provisions of the agreement referenced above.                            */
/*--------------------------------------------------------------------------*/

/** @file  ip_platform.h
 *  @brief Include file for the IP.
 *
 * This includes the CMSIS for all of the functionality provided by the ELS IP and provides support for external base address linking. */

#ifndef IP_PLATFORM_H
#define IP_PLATFORM_H

#include "fsl_device_registers.h"

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define MCUXCL_FEATURE_TRNG_RNG4_256

#define GDET_EVTCNT             ELS_GDET_EVTCNT
#define GDET_EVTCNT_CLR_DONE    ELS_GDET_EVTCNT_CLR

#define S50_ELS_GDET_EVTCNT_ELS_GDET_EVTCNT_MASK             S50_ELS_GDET_EVTCNT_GDET_EVTCNT_MASK
#define S50_ELS_GDET_EVTCNT_ELS_GDET_EVTCNT_SHIFT            S50_ELS_GDET_EVTCNT_GDET_EVTCNT_SHIFT
#define S50_ELS_GDET_EVTCNT_ELS_GDET_EVTCNT_CLR_MASK     S50_ELS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_MASK
#define S50_ELS_GDET_EVTCNT_ELS_GDET_EVTCNT_CLR_SHIFT    S50_ELS_GDET_EVTCNT_CLR_GDET_EVTCNT_CLR_SHIFT

// Define base address of ELS
#define ELS_SFR_BASE            ELS         ///< base of ELS SFRs
#define ELS_SFR_NAME(sfr)       sfr         ///< full name of SFR
#define ELS_SFR_PREFIX          S50_        ///< sfr field name prefix


// Define base address of PKC
#define PKC_SFR_BASE            PKC         ///< base of PKC SFRs
#define PKC_SFR_NAME(sfr)       PKC_ ## sfr ///< full name of SFR
#define PKC_SFR_PREFIX          PKC_PKC_    ///< sfr field name prefix
#define PKC_SFR_SUFFIX_MSK      _MASK       ///< sfr field name suffix for mask
#define PKC_SFR_SUFFIX_POS      _SHIFT      ///< sfr field name suffix for bit position

// PKC_RAM base address is not defined in any header file
#define PKC_RAM_ADDR  ((uint32_t)0x20002000UL)
#define PKC_WORD_SIZE  8u
#define PKC_RAM_SIZE  ((uint32_t)0x1000u) /* TODO Check that value if its correct*/

#define CSS_INTERRUPT_BUSY_NUMBER  54
#define CSS_INTERRUPT_ERR_NUMBER   112
#define CSS_INTERRUPT_IRQ_NUMBER   54

#define     SYSCON_CSS_CLK_CTRL_SET        *(volatile uint32_t*)0x500009b4
#define     SYSCON_PERIPH_CTRL_RST         *(volatile uint32_t*)0x50000108
#define     SYSCON_RAM_INTERLEAVE          *(volatile uint32_t*)0x50000470

#define IP_PUF_BASE      0x5003A000UL
#define PUF_SRAM_CFG     *(volatile uint32_t *) (IP_PUF_BASE + 0x300)
#define PUF_SR           *(volatile uint32_t *) (IP_PUF_BASE + 0x8)
#define PUF_OR           *(volatile uint32_t *) (IP_PUF_BASE + 0x4)
#define PUF_CR           *(volatile uint32_t *) (IP_PUF_BASE + 0x0)
#define PUF_KEY_DEST     *(volatile uint32_t *) (IP_PUF_BASE + 0x20)
#define PUF_DIR          *(volatile uint32_t *) (IP_PUF_BASE + 0xA0)
#define PUF_DOR          *(volatile uint32_t *) (IP_PUF_BASE + 0xA8)

// ELS version
#define ELS_HW_VERSION_REVISION            0
#define ELS_HW_VERSION_MINOR               19
#define ELS_HW_VERSION_MAJOR               2
#define ELS_HW_VERSION_LEVEL               0

#ifdef NXPCL_FEATURE_ELS_LINK_BASE_ADDRESS
/* If we are supposed to determine the CSSv2 base address at link time, do not use the definitions from the platform header file
 * Redefine IP_CSS as an extern pointer.
 */
#undef ELS_SFR_BASE
extern void * ip_css_base;
#define ELS_SFR_BASE           ((S50_Type *) ip_css_base)
#endif /* NXPCL_FEATURE_ELS_LINK_BASE_ADDRESS */

#endif
