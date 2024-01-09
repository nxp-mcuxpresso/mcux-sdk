/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClHmac_Internal_Functions.h
 *  @brief Internal definitions of helper functions for the HMAC component
 */

#ifndef MCUXCLHMAC_INTERNAL_FUNCTIONS_H_
#define MCUXCLHMAC_INTERNAL_FUNCTIONS_H_

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClMac_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClSession_Types.h>
#include <internal/mcuxClMac_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif


/****************************/
/* Skeleton functions       */
/****************************/

/**
 * @brief HMAC Oneshot Compute function
 *
 * This function acts as an intermediate layer between the mcuxClMac_compute API and specific HMAC algorithm cores
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHmac_compute, mcuxClMac_ComputeFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_compute(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    mcuxClMac_Mode_t mode,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pMac,
    uint32_t * const pMacLength
);


/**
 * @brief HMAC Multipart Init function
 *
 * This function acts as an intermediate layer between the mcuxClMac_init API and specific HMAC algorithm cores
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHmac_init, mcuxClMac_InitFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_init(
    mcuxClSession_Handle_t session,
    mcuxClMac_Context_t * const pContext,
    mcuxClKey_Handle_t key
);

/**
 * @brief HMAC Multipart Process function
 *
 * This function acts as an intermediate layer between the mcuxClMac_process API and specific HMAC algorithm cores
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHmac_process, mcuxClMac_ProcessFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_process(
    mcuxClSession_Handle_t session,
    mcuxClMac_Context_t * const pContext,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength
);

/**
 * @brief HMAC Multipart Finish function
 *
 * This function acts as an intermediate layer between the mcuxClMac_finish API and specific HMAC algorithm cores
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHmac_finish, mcuxClMac_FinishFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_finish(
    mcuxClSession_Handle_t session,
    mcuxClMac_Context_t * const pContext,
    mcuxCl_Buffer_t pMac,
    uint32_t * const pMacLength
);



/****************************/
/* Helper functions         */
/****************************/

/**
 * Prepares the given HMAC key by hashing and/or padding it to a length of MCUXCLELS_HMAC_PADDED_KEY_SIZE bytes.
 * Both the input key and the output padded key are taken from/written to the context.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHmac_prepareHMACKey)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_prepareHMACKey(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    uint32_t * preparedHmacKey
);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHMAC_INTERNAL_FUNCTIONS_H_ */
