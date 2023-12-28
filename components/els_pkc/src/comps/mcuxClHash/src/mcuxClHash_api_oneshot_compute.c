/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_compute)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHash_compute(
    mcuxClSession_Handle_t session,
    mcuxClHash_Algo_t algorithm,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_Buffer_t pOut,
    uint32_t *const pOutSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_compute);

    /*Validate input parameters */
    if((NULL == algorithm) || (NULL == algorithm->oneShotSkeleton)
#if(1 == MCUX_CSSL_SC_USE_SW_LOCAL)
            || (0u == algorithm->protection_token_oneShotSkeleton)
#endif /* (1 == MCUX_CSSL_SC_USE_SW_LOCAL) */
            )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_compute, MCUXCLHASH_STATUS_INVALID_PARAMS);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result, algorithm->oneShotSkeleton (session,
                                                                  algorithm,
                                                                  pIn,
                                                                  inSize,
                                                                  pOut,
                                                                  pOutSize
                                                                  ));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClHash_compute, result, MCUXCLHASH_STATUS_FAULT_ATTACK, algorithm->protection_token_oneShotSkeleton);
}
