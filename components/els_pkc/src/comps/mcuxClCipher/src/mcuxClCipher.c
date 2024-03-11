/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClSession_Internal_EntryExit.h>

#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>

#include <mcuxClBuffer.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <internal/mcuxClCipher_Internal.h>

#include <mcuxCsslDataIntegrity.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipher_crypt)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_crypt(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClCipher_Mode_t mode,
  mcuxCl_InputBuffer_t pIv,
  uint32_t ivLength,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipher_crypt);

  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION("The required fields in mcuxClCipherModFunctions_t are declared using the macro MCUXCLCIPHER_CRYPT_MODEFUNCTIONS");
  const mcuxClCipher_ModeFunctions_t *pModeFunctions = (const mcuxClCipher_ModeFunctions_t *)mode->pModeFunctions;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION();
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
  MCUX_CSSL_FP_FUNCTION_CALL(status, pModeFunctions->crypt(
                                              session,
                                              NULL, /* pContext */
                                              key,
                                              mode,
                                              pIv,
                                              ivLength,
                                              pIn,
                                              inLength,
                                              pOut,
                                              pOutLength,
                                              MCUXCLCIPHER_OPTION_ONESHOT));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

  if(MCUXCLCIPHER_STATUS_OK != status)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipher_crypt, status, pModeFunctions->protection_token_crypt);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipher_crypt, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                       pModeFunctions->protection_token_crypt);

}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipher_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_init(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClCipher_Mode_t mode,
  mcuxCl_InputBuffer_t pIv,
  uint32_t ivLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipher_init);

  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION("The required fields in mcuxClCipherModFunctions_t are declared using the macro MCUXCLCIPHER_CRYPT_MODEFUNCTIONS");
  const mcuxClCipher_ModeFunctions_t *pModeFunctions = (const mcuxClCipher_ModeFunctions_t *)mode->pModeFunctions;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION();
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
  MCUX_CSSL_FP_FUNCTION_CALL(status, pModeFunctions->crypt(
                                              session,
                                              pContext,
                                              key,
                                              mode,
                                              pIv,
                                              ivLength,
                                              NULL, /* pIn */
                                              0u,   /* inLength */
                                              NULL, /* pOut */
                                              0u,   /* pOutLength */
                                              MCUXCLCIPHER_OPTION_INIT));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT() 

  if(MCUXCLCIPHER_STATUS_OK != status)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipher_init, status, pModeFunctions->protection_token_crypt);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipher_init, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                       pModeFunctions->protection_token_crypt);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipher_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_process(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipher_process);

  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION("The required fields in mcuxClCipherModFunctions_t are declared using the macro MCUXCLCIPHER_CRYPT_MODEFUNCTIONS");
  const mcuxClCipher_ModeFunctions_t *pModeFunctions = (const mcuxClCipher_ModeFunctions_t *)pContext->pMode->pModeFunctions;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION();
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
  MCUX_CSSL_FP_FUNCTION_CALL(status, pModeFunctions->crypt(
                                              session,
                                              pContext,
                                              NULL, /* pKey, is already stored in context */
                                              NULL, /* pMode, is already stored in context */
                                              NULL, /* pIv */
                                              0u,   /* ivLength */
                                              pIn,
                                              inLength,
                                              pOut,
                                              pOutLength,
                                              MCUXCLCIPHER_OPTION_PROCESS));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

  if(MCUXCLCIPHER_STATUS_OK != status)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipher_process, status, pModeFunctions->protection_token_crypt);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipher_process, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                       pModeFunctions->protection_token_crypt);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipher_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_finish(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipher_finish);

  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION("The required fields in mcuxClCipherModFunctions_t are declared using the macro MCUXCLCIPHER_CRYPT_MODEFUNCTIONS");
  const mcuxClCipher_ModeFunctions_t *pModeFunctions = (const mcuxClCipher_ModeFunctions_t *)pContext->pMode->pModeFunctions;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_VOIDPTR_TO_FUNCTION();
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
  MCUX_CSSL_FP_FUNCTION_CALL(status, pModeFunctions->crypt(
                                              session,
                                              pContext,
                                              NULL, /* pKey, is already stored in context */
                                              NULL, /* pMode, is already stored in context */
                                              NULL, /* pIv */
                                              0u,   /* ivLength */
                                              NULL, /* pIn */
                                              0u,   /* inLength */
                                              pOut,
                                              pOutLength,
                                              MCUXCLCIPHER_OPTION_FINISH));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

  if(MCUXCLCIPHER_STATUS_OK != status)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipher_finish, status, pModeFunctions->protection_token_crypt);
  }
  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipher_finish, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                       pModeFunctions->protection_token_crypt);
}


