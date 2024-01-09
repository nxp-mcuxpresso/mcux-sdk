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

/** @file  mcuxClAead_Internal_Descriptor.h
 *  @brief Internal definitions for the mcuxClAead component
 */

#ifndef MCUXCLAEAD_INTERNAL_DESCRIPTOR_H_
#define MCUXCLAEAD_INTERNAL_DESCRIPTOR_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClKey_Types.h>
#include <mcuxClAead_Types.h>
#include <mcuxClCore_Buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_init_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_init_t)(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t *const pContext,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  uint32_t inLength,
  uint32_t adataLength,
  uint32_t tagLength
  ));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_process_aad_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_process_aad_t)(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t *const pContext,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength
  ));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_process_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_process_t)(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
  ));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_finish_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_finish_t)(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t *const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t *const pOutLength,
  mcuxCl_Buffer_t pTag
  ));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_verify_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_verify_t)(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t *const pContext,
  mcuxCl_InputBuffer_t pTag,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
  ));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_crypt_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_crypt_t)(
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
  uint32_t *const pOutLength,
  mcuxCl_Buffer_t pTag,
  uint32_t tagLength
  ));

MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClAead_decrypt_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_decrypt_t)(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceSize,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inSize,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataSize,
  mcuxCl_InputBuffer_t pTag,
  uint32_t tagSize,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutSize
  ));

struct mcuxClAead_ModeDescriptor
{
//------------OneShot

  mcuxClAead_crypt_t crypt;
  uint32_t protection_token_crypt;




//------------MultiPart

  mcuxClAead_init_t init;
  uint32_t protection_token_init;


  mcuxClAead_process_aad_t processAad;
  uint32_t protection_token_processAad;
  mcuxClAead_process_t process;
  uint32_t protection_token_process;
  mcuxClAead_finish_t finish;
  uint32_t protection_token_finish;
  mcuxClAead_verify_t verify;
  uint32_t protection_token_verify;


  //-------------Common
  const struct mcuxClAead_AlgorithmDescriptor *algorithm;

  //TODO add CTR mode - CLNS-4374
  //TODO add macMode (gmac/cbc_mac) - CLNS-4374
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAEAD_INTERNAL_DESCRIPTOR_H_ */
