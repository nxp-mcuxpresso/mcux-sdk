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

/** @file  mcuxClOsccaMacModes.c
 *  @brief Implementation of mcuxClOsccaMacModes functions for SM4-based and SM3-HMAC modes
 */

#include <mcuxClMac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxClSession.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaMacModes_Internal_Functions.h>
#include <internal/mcuxClOsccaMacModes_Ctx.h>
#include <internal/mcuxClOsccaMacModes_Types.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_compute, mcuxClMac_ComputeFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_compute(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
)
{
  mcuxClOsccaMacModes_Algorithm_t pAlgo = (mcuxClOsccaMacModes_Algorithm_t) mode->common.pAlgorithm;
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_compute, pAlgo->protectionToken_engineOneshot);


  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineOneshot(session, mode, key, pIn, inLength, pMac, pMacLength));

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_compute, result);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_init, mcuxClMac_InitFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxClKey_Handle_t key)
{
  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  mcuxClOsccaMacModes_Context_t * const pCtx = (mcuxClOsccaMacModes_Context_t *) pContext;
  mcuxClOsccaMacModes_Algorithm_t pAlgo = (mcuxClOsccaMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_init, pAlgo->protectionToken_engineInit);

  pCtx->pKey = (mcuxClKey_Descriptor_t *) key;

  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineInit(session, pCtx));
  if (MCUXCLMAC_STATUS_OK != result)
  {
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaMacModes_Context_t));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_init, result,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
  }

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_init, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_process, mcuxClMac_ProcessFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength)
{
  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  mcuxClOsccaMacModes_Context_t * const pCtx = (mcuxClOsccaMacModes_Context_t *) pContext;
  mcuxClOsccaMacModes_Algorithm_t pAlgo = (mcuxClOsccaMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_process, pAlgo->protectionToken_engineUpdate);

  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineUpdate(session, pCtx, pIn, inLength));
  if (MCUXCLMAC_STATUS_OK != result)
  {
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaMacModes_Context_t));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_process, result,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
  }
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_process, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_finish, mcuxClMac_FinishFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const pContext,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength)
{
  MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
  mcuxClOsccaMacModes_Context_t * const pCtx = (mcuxClOsccaMacModes_Context_t *) pContext;
  mcuxClOsccaMacModes_Algorithm_t pAlgo = (mcuxClOsccaMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;
  MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_finish, pAlgo->protectionToken_engineFinalize,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineFinalize(session, pCtx, pMac, pMacLength));

  MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaMacModes_Context_t));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_finish, result);
}
