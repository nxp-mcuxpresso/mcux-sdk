/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClHash_Functions.h
 *  @brief Top-level API of the mcuxClHash component */

#ifndef MCUXCLHASH_FUNCTIONS_H_
#define MCUXCLHASH_FUNCTIONS_H_

#include <mcuxClSession_Types.h>
#include <mcuxClHash_Types.h>
#include <mcuxCsslFlowProtection.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClHash_Functions mcuxClHash_Functions
 * @brief Defines all functions of @ref mcuxClHash
 * @ingroup mcuxClHash
 * @{
 */

/**
 * @brief One-shot hash computation
 *
 * This function computes the hash over the input message \p in using the hash function provided by the
 * \p algo input parameter.
 *
 * The input parameter \p session has to be initialized by the function mcuxClSession_init prior to
 * calling this function. Certain \ref mcuxClHashAlgorithms support maintaining a Runtime Fingerprint (RTF).
 * Updating of the RTF has to be enabled/disabled by calling the mcuxClSession_setRtf function on the session
 * prior to calling this function.
 *
 * @param session   Session to be used with the hash function.
 * @param algo      Algorithm to be used with the hash function.
 * @param in        Pointer to the input message
 * @param inSize    Length of the input message
 * @param hash      Computed hash value over the input message
 * @param rtf       Updated RTF value after the hash operation. Only supported on platforms with CSS (Platform specific)
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLHASH_STATUS_OK      Hash operation successful
 * @retval MCUXCLHASH_STATUS_ERROR   Error occured during Hash operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHash_compute)
mcuxClHash_Status_Protected_t mcuxClHash_compute(
    mcuxClSession_Handle_t session,
    const mcuxClHash_Algo_t *algo,
    const uint8_t *const in,
    uint32_t inSize,
    uint8_t *const hash,
    uint8_t *const rtf
);



/**********************************************************************/
/* MULTIPART                                                          */
/**********************************************************************/

/**
 * @brief Initializes the context for a new hash computation.
 *
 * The function initializes the context for the selected hash algorithm.
 *
 * Up to 2^32 bytes of data can be hashed with a single context.
 *
 * @param session   Session to be used with the hash function.
 * @param context   The context to initialize.
 * @param algo      The selected hashing algorithm. This parameter must point to a statically allocated object (static
 *                  or global variable).
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLHASH_STATUS_OK      Hash operation successful
 * @retval MCUXCLHASH_STATUS_ERROR   Error occured during Hash operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHash_init)
mcuxClHash_Status_Protected_t mcuxClHash_init(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t * context,
    const mcuxClHash_Algo_t * algo
);

/**
 * @brief Adds a chunk of data to an ongoing hash computation.
 *
 * This function appends the additional data to the context.
 *
 * Up to 2^32 bytes of data can be hashed with a single context.
 *
 * @param session   Session to be used with the hash function.
 * @param context   The hash context.
 * @param in        Pointer to the data to be added to the hash.
 * @param inSize    Size of the data to be added to the hash.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLHASH_STATUS_OK      Hash operation successful
 * @retval MCUXCLHASH_STATUS_ERROR   Error occured during Hash operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHash_update)
mcuxClHash_Status_Protected_t mcuxClHash_update(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t * context,
    const uint8_t * const in,
    uint32_t inSize
);

/**
 * @brief Finishes a hash computation.
 *
 * This function processes the padding and outputs the resulting hash to the given buffer.
 *
 * @param session   Session to be used with the hash function.
 * @param context   The hash context.
 * @param hash      Pointer to the location where the function should write the resulting hash.
 * @param rtf       Pointer to the location where the function should write the run-time fingerprint (RTF). Only
 *                  supported on platforms with CSSv2. If RTF updates are not enabled in the session, this pointer may
 *                  be NULL.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLHASH_STATUS_OK      Hash operation successful
 * @retval MCUXCLHASH_STATUS_ERROR   Error occured during Hash operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHash_finish)
mcuxClHash_Status_Protected_t mcuxClHash_finish(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t * context,
    uint8_t * const hash,
    uint8_t * const rtf
);


/**
 * @}
 */ /* mcuxClHash_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASH_FUNCTIONS_H_ */

