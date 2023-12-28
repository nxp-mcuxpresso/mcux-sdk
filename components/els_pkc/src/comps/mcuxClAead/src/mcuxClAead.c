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

/** @file  mcuxClAead.c
 *  @brief Implementation of the multipart and one shot functions of the mcuxClAead component */

#include <mcuxClAead.h>
#include <internal/mcuxClAead_Internal_Ctx.h>
#include <internal/mcuxClAead_Internal_Descriptor.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_crypt)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAead_crypt(
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
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_crypt);

    MCUX_CSSL_FP_FUNCTION_CALL(status, mode->crypt(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClKey_Handle_t key,                */ key,
      /* mcuxClAead_Mode_t mode,                */ mode,
      /* mcuxCl_InputBuffer_t pNonce,           */ pNonce,
      /* uint32_t nonceLength,                 */ nonceLength,
      /* mcuxCl_InputBuffer_t pIn,              */ pIn,
      /* uint32_t inLength,                    */ inLength,
      /* mcuxCl_InputBuffer_t pAdata,           */ pAdata,
      /* uint32_t adataLength,                 */ adataLength,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      /* mcuxCl_Buffer_t pTag,                  */ pTag,
      /* uint32_t tagLength,                   */ tagLength
    ));

    if(MCUXCLAEAD_STATUS_OK != status)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_crypt, MCUXCLAEAD_STATUS_ERROR,
                                mode->protection_token_crypt);
    }


    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAead_crypt, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                        mode->protection_token_crypt);
}







MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAead_init(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  uint32_t inLength,
  uint32_t adataLength,
  uint32_t tagLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_init);

    MCUX_CSSL_FP_FUNCTION_CALL(status, mode->init(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pContext,
      /* mcuxClKey_Handle_t key,                */ key,
      /* mcuxClAead_Mode_t mode,                */ mode,
      /* mcuxCl_InputBuffer_t pNonce,           */ pNonce,
      /* uint32_t nonceLength,                 */ nonceLength,
      /* uint32_t inLength,                    */ inLength,
      /* uint32_t adataLength,                 */ adataLength,
      /* uint32_t tagLength,                   */ tagLength
    ));

    if(MCUXCLAEAD_STATUS_OK != status)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_init, MCUXCLAEAD_STATUS_ERROR,
                                 mode->protection_token_init);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAead_init, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         mode->protection_token_init);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAead_process(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_process);

    MCUX_CSSL_FP_FUNCTION_CALL(status, pContext->mode->process(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pContext,
      /* mcuxCl_InputBuffer_t pIn,              */ pIn,
      /* uint32_t inLength,                    */ inLength,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength
    ));

    if(MCUXCLAEAD_STATUS_OK != status)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_process, MCUXCLAEAD_STATUS_ERROR,
                                 pContext->mode->protection_token_process);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAead_process, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pContext->mode->protection_token_process);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_process_adata)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAead_process_adata(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_process_adata);

    MCUX_CSSL_FP_FUNCTION_CALL(status, pContext->mode->processAad(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pContext,
      /* mcuxCl_InputBuffer_t pAdata,           */ pAdata,
      /* uint32_t adataLength,                 */ adataLength
    ));

    if(MCUXCLAEAD_STATUS_OK != status)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_process_adata, MCUXCLAEAD_STATUS_ERROR,
                                 pContext->mode->protection_token_processAad);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAead_process_adata, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pContext->mode->protection_token_processAad);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAead_finish(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_finish);


    MCUX_CSSL_FP_FUNCTION_CALL(status, pContext->mode->finish(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pContext,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      /* mcuxCl_Buffer_t pTag,                  */ pTag
    ));

    if(MCUXCLAEAD_STATUS_OK != status)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_finish, MCUXCLAEAD_STATUS_ERROR,
                                 pContext->mode->protection_token_finish);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAead_finish, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pContext->mode->protection_token_finish);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAead_verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAead_verify(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pTag,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAead_verify);

    MCUX_CSSL_FP_FUNCTION_CALL(status, pContext->mode->verify(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pContext,
      /* mcuxCl_InputBuffer_t pTag,             */ pTag,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength
    ));

    if(MCUXCLAEAD_STATUS_OK != status)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_verify, MCUXCLAEAD_STATUS_ERROR,
                                 pContext->mode->protection_token_verify);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAead_verify, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pContext->mode->protection_token_verify);
}

