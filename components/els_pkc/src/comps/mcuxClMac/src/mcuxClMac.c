/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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

/** @file  mcuxClMac.c
 *  @brief Implementation of mcuxClMac component public API */

#include <mcuxClMac.h>
#include <internal/mcuxClMac_Ctx.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_compute)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_compute(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_compute, mode->common.protectionToken_compute);

  MCUX_CSSL_FP_FUNCTION_CALL(result, mode->common.compute(
                                      session,
                                      key,
                                      mode,
                                      pIn,
                                      inLength,
                                      pMac,
                                      pMacLength
  ));

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_compute, result);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_init, mode->common.protectionToken_init);

  pContext->pMode = mode;
  MCUX_CSSL_FP_FUNCTION_CALL(result, mode->common.init(
                                      session,
                                      pContext,
                                      key
  ));

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_init, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_process, pContext->pMode->common.protectionToken_process);

  MCUX_CSSL_FP_FUNCTION_CALL(result, pContext->pMode->common.process(
                                      session,
                                      pContext,
                                      pIn,
                                      inLength
  ));

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_process, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_finish, pContext->pMode->common.protectionToken_finish);

  MCUX_CSSL_FP_FUNCTION_CALL(result, pContext->pMode->common.finish(
                                      session,
                                      pContext,
                                      pMac,
                                      pMacLength
  ));

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_finish, result);
}

