/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/** @file  mcuxClOsccaSm3_Internal.h
 *  @brief Definitions and declarations of the *INTERNAL* layer of the
 *         @ref mcuxClOsccaSm3 component
 */

#ifndef MCUXCLOSCCASM3_INTERNAL_H_
#define MCUXCLOSCCASM3_INTERNAL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#ifdef MCUXCL_FEATURE_HASH_HW_SM3
#include <internal/mcuxClOsccaSm3_Internal_sm3.h>
#endif /* MCUXCL_FEATURE_HASH_HW_SM3 */

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClOsccaSm3_Internal mcuxClOsccaSm3_Internal
 * @brief Defines all internal of @ref mcuxClOsccaSm3 component
 * @ingroup mcuxClOsccaSm3
 * @{
 */
#define MCUXCLOSCCASM3_BLOCK_SIZE_SM3       (64U) ///< SM3 block size: 512 bit (64 bytes)

#define MCUXCLOSCCASM3_STATE_SIZE_SM3       (32U) ///< SM3 state size: 256 bit (32 bytes)

#define MCUXCLOSCCASM3_COUNTER_SIZE_SM3     (8U)  ///< Counter size for SM3 padding
/**@}*/

/**********************************************
 * Function declarations
 **********************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm3_core_sm3_switch_endianness)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_core_sm3_switch_endianness(uint32_t *ptr, uint32_t length);

#endif /* MCUXCLOSCCASM3_INTERNAL_H_ */
