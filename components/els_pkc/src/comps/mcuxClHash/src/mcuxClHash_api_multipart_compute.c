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

#include <mcuxClHash.h>
#include <internal/mcuxClHash_Internal.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslSecureCounter_Cfg.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHash_finish(
    mcuxClSession_Handle_t session,
    mcuxClHash_Context_t pContext,
    mcuxCl_Buffer_t pOut,
    uint32_t *const pOutSize
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_finish);

    if((NULL == pContext->algo) || (NULL == pContext->algo->finishSkeleton)
#if(1 == MCUX_CSSL_SC_USE_SW_LOCAL)
            || (0u == pContext->algo->protection_token_finishSkeleton)
#endif /* (1 == MCUX_CSSL_SC_USE_SW_LOCAL) */
            )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_finish, MCUXCLHASH_STATUS_INVALID_PARAMS);
    }

    /* Save protection token before context is cleared */
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t token_finish = pContext->algo->protection_token_finishSkeleton);

    MCUX_CSSL_FP_FUNCTION_CALL(result, pContext->algo->finishSkeleton(session,
                                                                     pContext,
                                                                     pOut,
                                                                     pOutSize
                                                                     ));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClHash_finish,
                                         result,
                                         MCUXCLHASH_STATUS_FAULT_ATTACK,
                                         token_finish);
}
