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

/** @file  mcuxClOsccaAeadModes_Internal_Functions.h
 *  @brief Internal function declaration for the mcuxClOsccaAeadModes component */

#ifndef MCUXCLOSCCAAEADMODES_INTERNAL_FUNCTIONS_H_
#define MCUXCLOSCCAAEADMODES_INTERNAL_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClBuffer.h>
#include <mcuxClAead.h>
#include <mcuxClKey_Types.h>
#include <mcuxClSession_Types.h>
#include <internal/mcuxClAead_Ctx.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Types.h>

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_init, mcuxClAead_init_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_init(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  uint32_t inLength,
  uint32_t adataLength,
  uint32_t tagLength
);


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_process_adata, mcuxClAead_process_aad_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_process_adata(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_process, mcuxClAead_process_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_process(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_finish, mcuxClAead_finish_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_finish(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_verify, mcuxClAead_verify_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_verify(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pTag,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_crypt, mcuxClAead_crypt_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_crypt(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag,
  uint32_t tagLength
);


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_SkeletonCcm, mcuxClOsccaAeadModes_Skeleton_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_SkeletonCcm(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pContext,
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

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_EngineCcm, mcuxClOsccaAeadModes_Engine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_EngineCcm (
  mcuxClSession_Handle_t session,
  mcuxClOsccaAeadModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t options  //!< options is a bitmask with one bit reserved for each of the operations
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_SM4_Crypt_Internal_Ctr)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_SM4_Crypt_Internal_Ctr(
    uint32_t* roundKeys, mcuxCl_InputBuffer_t pIn, uint32_t inputLen, uint8_t* pIV, mcuxCl_Buffer_t pOut);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_Ccm_Internal_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_Init(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_InputBuffer_t pNonce,
    uint32_t nonceLength,
    uint32_t inLength,
    uint32_t adataLength,
    uint32_t tagLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_InputBuffer_t pAdata,
    uint32_t adataLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_Ccm_Internal_Process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_Process(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaAeadModes_Ccm_Internal_Finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_Finish(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_Buffer_t pTag,
    uint32_t options //!< options is a bitmask with one bit reserved for each of the operations
);

#endif /*MCUXCLOSCCAAEADMODES_INTERNAL_FUNCTIONS_H_*/
