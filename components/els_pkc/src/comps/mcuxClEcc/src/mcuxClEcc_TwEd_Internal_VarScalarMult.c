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
 * @file  mcuxClEcc_TwEd_Internal_VarScalarMult.c
 * @brief Scalar multiplication with a variable point P on a twisted Edwards curve
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_Macros.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>
#include <internal/mcuxClEcc_Internal_Convert_FUP.h>
#include <internal/mcuxClEcc_TwEd_Internal_VarScalarMult_FUP.h>

/**
 * Function that performs a scalar multiplication with a variable point P on a twisted Edwards curve
 *
 * Prerequisites:
 *   -  Buffer buf(iScalar) contains the secret scalar lambda of bit length scalarBitLength
 *   -  Buffers TWED_X, TWED_Y and TWED_Z contain the homogeneous coordinates (X:Y:Z) of P in MR
 *   -  Buffer ECC_CP1 contains d in MR
 *   -  ps1Len = (operandSize, operandSize)
 *   -  Buffer ECC_PFULL contains p'||p
 *   -  Buffer ECC_PS contains the shifted modulus associated to p
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_VarScalarMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_VarScalarMult(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_CommonDomainParams_t *pDomainParams,
    uint8_t iScalar,
    uint32_t scalarBitLength,
    uint32_t options,
    const mcuxClEcc_TwEd_PtrSelectFunction_FP_t *pPtrSelectFctFP
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_VarScalarMult);

    /* Determine pointer table pointer */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy - TODO CLNS-6410: check if this is necessary
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("MISRA Ex. 9 to Rule 11.3 - PKC word is CPU word aligned.");
    const uint32_t *pScalar = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();

    /* Step 1: Initialize the accumulated points in YZ-coordinates */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(TWED_ML_Y1, TWED_Z, 0u);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(TWED_ML_Z1, TWED_Z, 0u);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(TWED_ML_Y2, TWED_Y, 0u);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(TWED_ML_Z2, TWED_Z, 0u);

    /* Step 2: Import ladder constant (a/d mod p), convert it to MR modulo p, and store it in buffer ECC_CP0. */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    uint32_t byteLenP = (uint32_t) pDomainParams->byteLenP;
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0, pDomainParams->pLadderConst, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_CP0, ECC_T0, ECC_PQSQR, ECC_P);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
    /* Step 3: Perform ladder loop to calculate YZ-coordinates for the resulting point according to Algorithms 4 and 5 in https://ieeexplore.ieee.org/document/6550581
     * For the pointer selection, the function specified by pPtrSelectFctFP is used.
     */
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
    uint32_t i = scalarBitLength;
    uint32_t currentScalarWord = 0u;
    MCUX_CSSL_FP_LOOP_DECL(whileLoop);
    MCUX_CSSL_FP_BRANCH_DECL(ifInWhile);
    while(0u < i)
    {
        /* Update loop counter, deviation from the design to let iterate over unsigned value */
        --i;

        /* Select pointers pOperands[TWED_VY1],...,pOperands[TWED_VZ2] according to the bit to be processed */
        uint32_t currentScalarBitInWord = i % 32u;
        if((i == (scalarBitLength - 1u)) || ((i % 32u) == 31u))
        {
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
            uint32_t currentScalarWordIndex = i / 32u;
            currentScalarWord = pScalar[currentScalarWordIndex];
            MCUX_CSSL_FP_BRANCH_POSITIVE(ifInWhile);
        }
        MCUX_CSSL_FP_FUNCTION_CALL(ret_PtrSelectFct, pPtrSelectFctFP->pPtrSelectFct(pSession, currentScalarWord, (uint8_t)currentScalarBitInWord));
        if(MCUXCLECC_STATUS_OK != ret_PtrSelectFct)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_VarScalarMult, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Perform the ladder step to calculate (VY2:VZ2) = (VY1:VZ1) + (VY2:VZ2) and (VY1:VZ1) = 2*(VY1:VZ1) */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_VarScalarMult_YZMontLadder_LadderStep, mcuxClEcc_FUP_VarScalarMult_YZMontLadder_LadderStep_LEN);

        /* FP balancing for the loop iteration */
        MCUX_CSSL_FP_LOOP_ITERATION(whileLoop,
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(ifInWhile, (i == (scalarBitLength - 1u)) || ((i % 32u) == 31u)),
            pPtrSelectFctFP->ptrSelectFct_FP_FuncId,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
            );
    }

    /* Step 4: Import curve parameter a, convert it to MR modulo p, and store it in buffer ECC_CP0. */
    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0, pDomainParams->pCurveParam1, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_CP0, ECC_T0, ECC_PQSQR, ECC_P);

    /* Step 5: Recover the missing X-coordinate */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_VarScalarMult_Recover_X_Coordinate, mcuxClEcc_FUP_VarScalarMult_Recover_X_Coordinate_LEN);

    /* Step 6: If requested, convert the result to affine coordinates */
    if(MCUXCLECC_SCALARMULT_OPTION_AFFINE_OUTPUT == (MCUXCLECC_SCALARMULT_OPTION_OUTPUT_MASK & options))
    {
        MCUXCLMATH_FP_MODINV(ECC_T0, TWED_Z, ECC_P, ECC_T1);         /* T0 = Z^(-1)*R^(-1) mod p    */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_ConvertHomToAffine, mcuxClEcc_FUP_ConvertHomToAffine_LEN);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_VarScalarMult, MCUXCLECC_STATUS_OK,
                    4u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
                    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
                    MCUX_CSSL_FP_LOOP_ITERATIONS(whileLoop, scalarBitLength),
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
                    MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
                    MCUX_CSSL_FP_CONDITIONAL((MCUXCLECC_SCALARMULT_OPTION_AFFINE_OUTPUT == (MCUXCLECC_SCALARMULT_OPTION_OUTPUT_MASK & options)),
                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) )
                    );
}
