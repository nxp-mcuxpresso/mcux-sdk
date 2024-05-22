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
 * @file  mcuxClEcc_Internal_BlindedScalarMult.c
 * @brief mcuxClEcc: implementation of mcuxClEcc_BlindedScalarMult
 */


#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_UPTRT_access.h>


/**
 * This function implements the scalar multiplication k*G for a secret scalar k in {0,...,n-1}
 * and the base point G of order n on the given curve. If the scalar k is zero, the function
 * returns MCUXCLECC_STATUS_NEUTRAL_POINT. If it is not zero, the function generates a blinded
 * multiplicative splitting of the scalar k and performs two secure scalar multiplications,
 * the first with the blinded scalar and the second with the blinding by calling the generic
 * function mcuxClEcc_BlindedScalarMult.
 *
 * Input:
 *  - pSession          Handle for the current CL session
 *  - pDomainParameters Pointer to common domain parameters
 *
 * Return values:
 *  - MCUXCLECC_STATUS_OK            if the function executed successfully
 *  - MCUXCLECC_STATUS_NEUTRAL_POINT if the scalar is zero
 *  - MCUXCLECC_STATUS_RNG_ERROR     random number generation (PRNG) error (unexpected behavior)
 *  - MCUXCLECC_STATUS_FAULT_ATTACK  fault attack (unexpected behavior) is detected
 *
 * Prerequisites:
 *  - The secret scalar k is contained in buffer ECC_S2
 *  - ps1Len = (operandSize, operandSize)
 *  - Buffers ECC_CP0 and ECC_CP1 contain the curve parameters a and d in MR
 *  - Buffer ECC_PFULL contains p'||p
 *  - Buffer ECC_NFULL contains n'||n
 *  - Buffers ECC_PS and ECC_NS contain the shifted moduli associated to p and n
 *
 * Result:
 *  - If MCUXCLECC_STATUS_OK is returned, the result k*G is stored in curve dependent coordinates in buffers ECC_COORD00, ECC_COORD01,....
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_BlindedScalarMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_BlindedScalarMult(mcuxClSession_Handle_t pSession,
                                                                         mcuxClEcc_CommonDomainParams_t *pCommonDomainParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_BlindedScalarMult);

    /*
     * Step 1: Securely compare k against zero and return MCUXCLECC_STATUS_NEUTRAL_POINT if k is zero.
     */
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_T0, 0u);
    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_S2, ECC_T0);
    uint32_t zeroFlag = MCUXCLPKC_WAITFORFINISH_GETZERO();
    if (MCUXCLPKC_FLAG_ZERO == zeroFlag)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_NEUTRAL_POINT,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP );
    }


    /*
     * Step 2: Securely generate a multiplicative decomposition (sigma,phi) of k with a 32 bit random phi
     *         with MSBit and LSBit set to 1 stored in ECC_S0 and sigma = phi^(-1)*k mod n stored in ECC_S1
     *         by calling function mcuxClEcc_GenerateMultiplicativeBlinding.
     */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_GenMulBlind,
        mcuxClEcc_GenerateMultiplicativeBlinding(pSession, ECC_S2));
    if (MCUXCLECC_STATUS_OK != ret_GenMulBlind)
    {
        /* GenerateMultiplicativeBlinding is returning only OK or RNG_ERROR */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_RNG_ERROR);
    }


    /*
     * Step 3: Call pDomainParameters->pSecFixScalarMultFct to securely calculate the scalar multiplication sigma*G
     *         and store the result P' in curve dependent coordinates in MR in buffers ECC_COORD00, ECC_COORD01,....
     */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    uint32_t leadingZeroN;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_LeadingZeros(ECC_N, &leadingZeroN));
    uint32_t bitLenN = (operandSize * 8u) - leadingZeroN;

    MCUX_CSSL_FP_FUNCTION_CALL(ret_secFixScalarMult,
        pCommonDomainParams->pSecFixScalarMultFctFP->pScalarMultFct(
            pSession,
            pCommonDomainParams,
            ECC_S1,
            bitLenN,
            0));
    if(MCUXCLECC_STATUS_RNG_ERROR == ret_secFixScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != ret_secFixScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }


    /*
     * Step 4: Call pDomainParameters->pSecVarScalarMultFct to securely calculate the scalar multiplication phi*P'
     *         and store the result P in curve dependent coordinates in MR in buffers ECC_COORD00, ECC_COORD01,....
     */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_secVarScalarMult,
        pCommonDomainParams->pSecVarScalarMultFctFP->pScalarMultFct(
            pSession,
            pCommonDomainParams,
            ECC_S0,
            MCUXCLECC_SCALARBLINDING_BITSIZE,
            MCUXCLECC_SCALARMULT_OPTION_AFFINE_OUTPUT));
    if(MCUXCLECC_STATUS_RNG_ERROR == ret_secVarScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != ret_secVarScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_BlindedScalarMult, MCUXCLECC_STATUS_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_GenerateMultiplicativeBlinding),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        pCommonDomainParams->pSecFixScalarMultFctFP->scalarMultFct_FP_FuncId,
        pCommonDomainParams->pSecVarScalarMultFctFP->scalarMultFct_FP_FuncId);
}
