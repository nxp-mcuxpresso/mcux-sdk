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

#include <mcuxClCore_Platform.h>
#include <mcuxClHash_Types.h>
#include <mcuxClSession.h>
#include <internal/mcuxClHash_Internal.h>
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
#define MCUXCLOSCCASM3_WACPU_SIZE_SM3       (128u)

#define MCUXCLOSCCASM3_BLOCK_SIZE_SM3       (64U) ///< SM3 block size: 512 bit (64 bytes)

#define MCUXCLOSCCASM3_STATE_SIZE_SM3       (32U) ///< SM3 state size: 256 bit (32 bytes)

#define MCUXCLOSCCASM3_COUNTER_SIZE_SM3     (8U)  ///< Counter size for SM3 padding

#define MCUXCLOSCCASM3_CONTEXT_SIZE_SM3     (sizeof(mcuxClHash_ContextDescriptor_t) + MCUXCLOSCCASM3_BLOCK_SIZE_SM3 + MCUXCLOSCCASM3_STATE_SIZE_SM3)    ///< Context size for SM3 mulit-part

/**********************************************************/
/* Internal APIs of mcuxClOsccaSm3                         */
/**********************************************************/
/**
 * @defgroup mcuxClOsccaSm3_Internal_Functions mcuxClOsccaSm3_Internal_Functions
 * @brief Defines all internal functions of @ref mcuxClOsccaSm3 component
 * @ingroup mcuxClOsccaSm3
 * @{
 */
/**@}*/

#endif /* MCUXCLOSCCASM3_INTERNAL_H_ */
