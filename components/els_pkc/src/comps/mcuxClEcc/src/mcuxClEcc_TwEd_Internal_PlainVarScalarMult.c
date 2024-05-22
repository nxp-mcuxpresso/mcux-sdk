/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/**
 * @file  mcuxClEcc_TwEd_Internal_PlainVarScalarMult.c
 * @brief Plain scalar multiplication with a variable point P on a twisted Edwards curve
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>

static const mcuxClEcc_TwEd_PtrSelectFunction_FP_t mcuxClEcc_TwEd_PlainPtrSelectML_FP = {
    .pPtrSelectFct = mcuxClEcc_TwEd_PlainPtrSelectML,
    .ptrSelectFct_FP_FuncId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_PlainPtrSelectML),
};

/**
 * Function that performs a scalar multiplication with a variable point P on a twisted Edwards curve, unprotected against SCA.
 * This function is a wrapper to mcuxClEcc_TwEd_VarScalarMult.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_PlainVarScalarMult, mcuxClEcc_ScalarMultFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainVarScalarMult(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_CommonDomainParams_t *pDomainParams,
    uint8_t iScalar,
    uint32_t scalarBitLength,
    uint32_t options
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_PlainVarScalarMult);

    MCUX_CSSL_FP_FUNCTION_CALL(returnScalarMult,
        mcuxClEcc_TwEd_VarScalarMult(pSession, pDomainParams, iScalar, scalarBitLength, options, &mcuxClEcc_TwEd_PlainPtrSelectML_FP));

    if(MCUXCLECC_STATUS_OK != returnScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PlainVarScalarMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PlainVarScalarMult, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_VarScalarMult)
    );
}
