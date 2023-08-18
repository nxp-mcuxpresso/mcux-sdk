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

/** @file  mcuxClAeadModes_ELS_Functions.h
 *  @brief Internal function declaration for the mcuxClAead component */

#ifndef MCUXCLAEADMODES_ELS_FUNCTIONS_H_
#define MCUXCLAEADMODES_ELS_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClAead_ModeSkeletonAesCcm)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAead_ModeSkeletonAesCcm(
    mcuxClSession_Handle_t session,
    mcuxClAeadModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pNonce,
    uint32_t nonceLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_InputBuffer_t pAdata,
    uint32_t adataLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    mcuxCl_Buffer_t pTag,
    uint32_t tagLength,
    uint32_t options //!< options is a bitmask with one bit reserved for each of the operations
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClAead_ModeEngineAesCcmEls)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAead_ModeEngineAesCcmEls (
    mcuxClSession_Handle_t session,
    mcuxClAeadModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    uint32_t options  //!< options is a bitmask with one bit reserved for each of the operations
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClAead_ModeSkeletonAesGcm)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAead_ModeSkeletonAesGcm(
    mcuxClSession_Handle_t session,
    mcuxClAeadModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pNonce,
    uint32_t nonceLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_InputBuffer_t pAdata,
    uint32_t adataLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    mcuxCl_Buffer_t pTag,
    uint32_t tagLength,
    uint32_t options //!< options is a bitmask with one bit reserved for each of the operations
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClAead_ModeEngineAesGcmEls)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAead_ModeEngineAesGcmEls (
    mcuxClSession_Handle_t session,
    mcuxClAeadModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    uint32_t options  //!< options is a bitmask with one bit reserved for each of the operations
    );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAEADMODES_ELS_FUNCTIONS_H_ */
