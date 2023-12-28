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

/** @file  mcuxClHashModes_Core_els_sha2.h
 *  @brief Internal definitions and declarations of the *CORE* layer dedicated to ELS
 */

#ifndef MCUXCLHASHMODES_CORE_ELS_SHA2_H_
#define MCUXCLHASHMODES_CORE_ELS_SHA2_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClHash_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************
 * Type declarations
 **********************************************************/

/**
 * @brief Hash Core function type
 *
 * This function will process one or more blocks of the Hash algorithm
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHashModes_els_AlgoCore_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) (*mcuxClHashModes_els_AlgoCore_t)(
                        uint32_t options,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize,
                        mcuxCl_Buffer_t pOut));

/**********************************************************
 * Function declarations
 **********************************************************/

/**
 * @brief ELS hash processing
 *
 * This function calls mcuxClEls_Hash_Async to call ELS to process a input data. Note
 * it does not perform padding. This has to be done before calling the function.
 *
 * @param options   ELS options
 * @param in        Pointer to the input message
 * @param out       Result of processed input data
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLHASH_STATUS_OK               Hash operation successful
 * @retval MCUXCLHASH_STATUS_FAILURE          Error occured during Hash operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHashModes_els_core_sha2, mcuxClHashModes_els_AlgoCore_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHashModes_els_core_sha2(
                        uint32_t options,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize,
                        mcuxCl_Buffer_t pOut);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_CORE_ELS_SHA2_H_ */
