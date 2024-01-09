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
 * @file  mcuxClEcc_TwEd_Internal_PlainFixScalarMult25519.c
 * @brief Edwards curve plain scalar point multiplication for curve 25519
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal_Ed25519.h>

/* MISRA Ex. 20 - Rule 5.1 */
static const mcuxClEcc_TwEd_PointDoubleFunction_FP_t mcuxClEcc_TwEd_PointDoubleEd25519_FP = {
    .pPointDoubleFct = mcuxClEcc_TwEd_PointDoubleEd25519,
    .pointDoubleFct_FP_FuncId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_PointDoubleEd25519),
};

/* MISRA Ex. 20 - Rule 5.1 */
static const mcuxClEcc_TwEd_MixedPointAddFunction_FP_t mcuxClEcc_TwEd_MixedPointAddEd25519_FP = {
    .pMixedPointAddFct = mcuxClEcc_TwEd_MixedPointAddEd25519,
    .mixedPointAddFct_FP_FuncId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_MixedPointAddEd25519),
};

/* MISRA Ex. 20 - Rule 5.1 */
static const mcuxClEcc_TwEd_PtrSelectFunction_FP_t mcuxClEcc_TwEd_PlainPtrSelectComb_FP = {
    .pPtrSelectFct = mcuxClEcc_TwEd_PlainPtrSelectComb,
    .ptrSelectFct_FP_FuncId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_PlainPtrSelectComb),
};

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PlainFixScalarMult25519, mcuxClEcc_ScalarMultFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainFixScalarMult25519(
    mcuxClSession_Handle_t pSession,                 ///<  [in]  pSession            Handle for the current CL session
    mcuxClEcc_CommonDomainParams_t *pDomainParams,   ///<  [in]  pDomainParams       Pointer to ECC common domain parameters structure
    uint8_t iScalar,                                ///<  [in]  iScalar             Pointer table index of secret scalar lambda
    uint32_t scalarBitLength,                       ///<  [in]  scalarBitLength     Bit length of the scalar; must be a multiple of 4
    uint32_t options                                ///<  [in]  options             Parameter to pass options
)
{
    (void) pSession;
    (void) options;

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_PlainFixScalarMult25519);

    MCUX_CSSL_FP_FUNCTION_CALL(returnScalarMult, mcuxClEcc_TwEd_FixScalarMult(pSession,
            pDomainParams,
            iScalar,
            scalarBitLength,
            &mcuxClEcc_TwEd_MixedPointAddEd25519_FP,
            &mcuxClEcc_TwEd_PointDoubleEd25519_FP,
            &mcuxClEcc_TwEd_PlainPtrSelectComb_FP
        )
    );

    if(MCUXCLECC_STATUS_OK != returnScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PlainFixScalarMult25519, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_PlainFixScalarMult25519, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_FixScalarMult)
    );
}
