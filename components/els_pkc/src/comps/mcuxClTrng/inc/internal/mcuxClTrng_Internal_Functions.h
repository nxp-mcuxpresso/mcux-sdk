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

/**
 * @file  mcuxClTrng_Internal_Functions.h
 * @brief Top level APIs of mcuxClTrng component
 */

#ifndef MCUXCLTRNG_INTERNAL_FUNCTIONS_H_
#define MCUXCLTRNG_INTERNAL_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <stdint.h>
#include <mcuxClSession.h>

#include <internal/mcuxClTrng_Internal_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* APIs of mcuxClTrng                                      */
/**********************************************************/
/**
 * @defgroup mcuxClTrng_Internal_Functions mcuxClTrng_Internal_Functions
 * @brief Defines all internal functions of @ref mcuxClTrng
 * @ingroup mcuxClTrng
 * @{
 */

/**
 * @brief Function to draw an entropy input string from the TRNG
 *
 * @param[in]   pSession            Handle for the current CL session.
 * @param[out]  pEntropyInput       Pointer to where entropy input string shall be written. Must be word-aligned.
 * @param[in]   entropyInputLength  Number of entropy input bytes to be drawn. Must be a multiple of word size.
 *
 * @return Status of the operation:
 * @retval #MCUXCLTRNG_STATUS_OK             The operation was successful
 * @retval #MCUXCLTRNG_STATUS_ERROR          The operation failed
 * @retval #MCUXCLTRNG_STATUS_FAULT_ATTACK   A fault attack is detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClTrng_getEntropyInput)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClTrng_Status_t) mcuxClTrng_getEntropyInput(
    mcuxClSession_Handle_t pSession,
    uint32_t *pEntropyInput,
    uint32_t entropyInputLength
    );

/**
 * @brief Function to init TRNG before use
 *
 * @return Status of the operation:
 * @retval #MCUXCLTRNG_STATUS_OK             The init operation was successful
 * @retval #MCUXCLTRNG_STATUS_FAULT_ATTACK   A fault attack is detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClTrng_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClTrng_Status_t) mcuxClTrng_Init(void);

#ifdef MCUXCL_FEATURE_TRNG_SA_TRNG
/**
 * @brief Function to check that TRNG is properly configured
 *
 * @return Status of the operation:
 * @retval #MCUXCLTRNG_STATUS_OK             The check operation was successful
 * @retval #MCUXCLTRNG_STATUS_ERROR          TRNG is not properly configured
 * @retval #MCUXCLTRNG_STATUS_FAULT_ATTACK   A fault attack is detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClTrng_checkConfig)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClTrng_Status_t) mcuxClTrng_checkConfig(void);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * @}
 */ /* mcuxClTrng_Internal_Functions */

#endif /* MCUXCLTRNG_INTERNAL_FUNCTIONS_H_ */
