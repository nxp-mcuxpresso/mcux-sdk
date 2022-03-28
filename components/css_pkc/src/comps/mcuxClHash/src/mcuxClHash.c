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

#include <mcuxClHash.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCss.h>
#include <mcuxClMemory.h>

/* ONESHOT */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_compute)
mcuxClHash_Status_Protected_t mcuxClHash_compute(
  mcuxClSession_Handle_t session,
  const mcuxClHash_Algo_t *algo,
  const uint8_t *const in,
  uint32_t inSize,
  uint8_t *const hash,
  uint8_t *const rtf
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_compute, algo->protection_token_skeleton);
    uint32_t options  = MCUXCLHASH_INIT | MCUXCLHASH_UPDATE | MCUXCLHASH_FINALIZE;
    mcuxClHash_ContextData_t ctx_data;
    ctx_data.unprocessedLength = 0u;
    ctx_data.processedLength = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL(result, algo->skeleton (
                        session,
                        algo,
                        &ctx_data,
                        NULL,
                        in,
                        inSize,
                        hash,
                        rtf,
                        options
                        ));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_compute, result);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_init)
mcuxClHash_Status_Protected_t mcuxClHash_init(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t * context,
    const mcuxClHash_Algo_t * algo
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_init);

    (void)session; // parameter not used

    context->data.unprocessedLength = 0u;
    context->data.processedLength = 0u;
    context->algo = algo;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_init, MCUXCLHASH_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_update)
mcuxClHash_Status_Protected_t mcuxClHash_update(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t * context,
    const uint8_t * const in,
    uint32_t inSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_update, context->algo->protection_token_streaming_skeleton);
    uint32_t options  = MCUXCLHASH_UPDATE;

    MCUX_CSSL_FP_FUNCTION_CALL(result, context->algo->streamingSkeleton (
                        session,
                        context->algo,
                        &(context->data),
                        &(context->buffer),
                        in,
                        inSize,
                        NULL,
                        NULL,
                        options
                        ));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_update, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_finish)
mcuxClHash_Status_Protected_t mcuxClHash_finish(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t * context,
    uint8_t * const hash,
    uint8_t * const rtf
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_finish, context->algo->protection_token_streaming_skeleton);
    uint32_t options  = MCUXCLHASH_FINALIZE;

    MCUX_CSSL_FP_FUNCTION_CALL(result, context->algo->streamingSkeleton (
                        session,
                        context->algo,
                        &(context->data),
                        &(context->buffer),
                        NULL,
                        NULL,
                        hash,
                        rtf,
                        options
                        ));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_finish, result);
}

