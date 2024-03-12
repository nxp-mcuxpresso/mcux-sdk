/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/** @file  mcuxClHashModes_Core_c_sha1.h
 *  @brief Internal definitions and declarations of the *CORE* layer dedicated
 *         to the software implementation of SHA-1
 */

#ifndef MCUXCLHASHMODES_CORE_C_SHA1_H_
#define MCUXCLHASHMODES_CORE_C_SHA1_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * CONSTANTS
 **********************************************/
#define MCUXCLHASHMODES_SHA_1_NO_OF_ROUNDS           (80U) ///< Number of rounds for SHA-1 algorithm

/**********************************************************
 * Type declarations
 **********************************************************/

/**********************************************************
 * Function declarations
 **********************************************************/

/**
 * @brief Sha-1 core hash processing
 *
 * This function processes one block of input data with the SHA-1 algorithm. Note
 * it does not perform padding. This has to be done before calling the function.
 *
 * @param[in/out] pState   Pointer to the state
 * @param[in/out] pAccBuf  Pointer to the accumulation buffer
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLHASH_STATUS_OK               Hash operation successful
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHashModes_core_c_sha1)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHashModes_core_c_sha1(
                                  uint32_t *pState,
                                  uint32_t *pAccBuf);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_CORE_C_SHA1_H_ */
