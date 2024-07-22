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


#ifndef MCUXCLOSCCACIPHERMODES_FUNCTONS_INTERNAL_H_
#define MCUXCLOSCCACIPHERMODES_FUNCTONS_INTERNAL_H_

#include <mcuxClCore_Platform.h>
#include <mcuxClBuffer.h>

#include <mcuxClKey_Types.h>
#include <internal/mcuxClOsccaCipherModes_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Skeleton functions
 * */
#ifdef MCUXCL_FEATURE_CIPHERMODES_SM4

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaCipherModes_SkeletonSM4_Pre)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaCipherModes_SkeletonSM4_Pre(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxClCipher_Mode_t pMode
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaCipherModes_SkeletonSM4_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_Init(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxClKey_Handle_t pKey,
    mcuxCl_InputBuffer_t pIv,
    uint32_t ivLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaCipherModes_SkeletonSM4_Process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_Process(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaCipherModes_SkeletonSM4_Finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_Finish(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
);


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaCipherModes_SkeletonSM4_OneShot)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_OneShot(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t pKey,
    mcuxClCipher_Mode_t pMode,
    mcuxCl_InputBuffer_t pIv,
    uint32_t ivLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaCipherModes_SkeletonSM4, mcuxClCipher_CryptFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxClKey_Handle_t pKey,
  mcuxClCipher_Mode_t pMode,
  mcuxCl_InputBuffer_t pIv,
  uint32_t ivLength,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t steps //!< steps is a bitmask with one bit reserved for each of the steps below
);


#endif /* MCUXCL_FEATURE_CIPHERMODES_SM4 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCACIPHERMODES_FUNCTONS_INTERNAL_H_ */
