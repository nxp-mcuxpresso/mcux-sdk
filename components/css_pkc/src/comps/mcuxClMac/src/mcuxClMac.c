/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 *  @brief implementation of mcuxClMac component */

#include <mcuxClMac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>
#include <internal/mcuxClMac_internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_compute)
mcuxClMac_Status_Protected_t mcuxClMac_compute(
                       mcuxClSession_Handle_t session,
                       const mcuxClKey_Handle_t key,
                       const mcuxClMac_Mode_t mode,
                       const uint8_t * const in,
                       uint32_t inSize,
                       uint8_t * const mac)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_compute, mode.protectionTokenOneshot);
    //currently only key in keyslot is supported
    uint32_t outSize = mode.macByteSize;
    mcuxClMac_Context_t context = {0};
    context.key = (mcuxClKey_Descriptor_t*)key;
    context.session = session;
    MCUX_CSSL_FP_FUNCTION_CALL(result, mode.engineOneshot(&context, in, inSize, mac, &outSize));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_compute, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_init)
mcuxClMac_Status_Protected_t mcuxClMac_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const context,
  const mcuxClKey_Handle_t key,
  const mcuxClMac_Mode_t mode)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_init, mode.protectionTokenInit);
  context->key = (mcuxClKey_Descriptor_t*)key;
  context->session = session;
  context->mode = mode;
  uint32_t outSize = 0;
  MCUX_CSSL_FP_FUNCTION_CALL(result, mode.engineInit(context, NULL, 0, NULL, &outSize));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_init, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_process)
mcuxClMac_Status_Protected_t mcuxClMac_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const context,
  const uint8_t *const in,
  uint32_t inSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_process, context->mode.protectionTokenUpdate);
  uint32_t outSize = 0;
  context->session = session;
  MCUX_CSSL_FP_FUNCTION_CALL(result, context->mode.engineUpdate(context, in, inSize, NULL, &outSize));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_process, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_finish)
mcuxClMac_Status_Protected_t mcuxClMac_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const context,
  uint8_t *const mac)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_finish, context->mode.protectionTokenFinalize);
  uint32_t outSize = context->mode.macByteSize;
  context->session = session;
  MCUX_CSSL_FP_FUNCTION_CALL(result, context->mode.engineFinalize(context, NULL, 0, mac, &outSize));
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_finish, result);
}
