/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClMacModes_Els_Functions.c
 *  @brief Implementation of mcuxClMacModes functions for ELS-based modes
 */

#include <mcuxClMac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClMacModes_Internal_Functions.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>
#include <internal/mcuxClMacModes_Els_Types.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_compute)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_compute(
mcuxClSession_Handle_t session,
mcuxClKey_Handle_t key,
mcuxClMac_Mode_t mode,
mcuxCl_InputBuffer_t pIn,
uint32_t inLength,
mcuxCl_Buffer_t pMac,
uint32_t * const pMacLength)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different MacModes Algorithm types")
  mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) mode->common.pAlgorithm;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_compute, pAlgo->protectionToken_engineOneshot);
  mcuxClMacModes_Context_t context = {0u};
  context.common.pMode = mode;
  context.key = (mcuxClKey_Descriptor_t *) key;
  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineOneshot(session, &context, pIn, inLength, pMac, pMacLength));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_compute, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxClKey_Handle_t key)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different MacModes Algorithm types")
  mcuxClMacModes_Context_t * const pCtx = (mcuxClMacModes_Context_t *) pContext;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
  mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_init, pAlgo->protectionToken_engineInit);
  pCtx->key = (mcuxClKey_Descriptor_t *) key;
  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineInit(session, pCtx));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_init, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different MacModes Algorithm types")
  mcuxClMacModes_Context_t * const pCtx = (mcuxClMacModes_Context_t *) pContext;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
  mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_process, pAlgo->protectionToken_engineUpdate);
  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineUpdate(session, pCtx, pIn, inLength));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_process, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different MacModes Algorithm types")
  mcuxClMacModes_Context_t * const pCtx = (mcuxClMacModes_Context_t *) pContext;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
  mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_finish, pAlgo->protectionToken_engineFinalize);
  MCUX_CSSL_FP_FUNCTION_CALL(result, pAlgo->engineFinalize(session, pCtx, pMac, pMacLength));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_finish, result);
}
