/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * This includes the CMSIS for all of the functionality provided by the CSSv2 IP and provides support for external base
 * address linking. */

#ifndef IP_PLATFORM_H
#define IP_PLATFORM_H

#include "board.h"
#include "cssv2.h"
#include "fame3.h"

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#undef IP_CSS
#define IP_CSS ((ip_css_Type *)CSS_BASE)

#undef PKC
#undef PKC_BASE
#undef PKC_Type
#define PKC_BASE 0x5002F000UL
#define PKC      ((ip_pkc_Type *)PKC_BASE)
#define PKC_Type ip_pkc_Type

// extern const uint32_t __ICFEDIT_region_RAM_PKC_start__;
//#define PKC_RAM_ADDR  (&__ICFEDIT_region_RAM_PKC_start__)
#define PKC_RAM_ADDR  (0x30002000)
#define PKC_RAM_SIZE  0x2000 // 8KB (second half of RAM bank A)
#define PKC_WORD_SIZE 8u
#define MCUXCL_FEATURE_ECC_MONTGOMERY_DH


#endif
