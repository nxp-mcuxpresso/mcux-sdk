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
 * @file  mcuxClEcc_TwEd_Internal_FixScalarMult.c
 * @brief EdDSA internal function for scalar multiplication with the base points
 */


#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClMath.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>

MCUX_CSSL_ANALYSIS_START_SUPPRESS_TEXT_IN_COMMENTS("Links are allowed in comments.")
/**
 * This function implements a scalar multiplication lambda*G for a given secret scalar lambda in {1,...,n-1}
 * and the base point G on a twisted Edwards curves. The result will be returned in homogeneous coordinates (Xres:Yres:Zres).
 * The scalar multiplication is implemented using a regular comb method processing 4 bits at a time. To achieve regularity,
 * the scalar is recoded into a non-zero BSD representation and the comb method is implemented by doing a double-and-add-or-subtract
 * loop using pre-computed points
 *
 *      P_(i3 i2 i1)_2 = G_0 + (-1)^(1 - i1) * G1 + (-1)^(1-i2) * G2 + (-1)^(1-i3) * G3,
 *
 * where Gi = 2^(i*scalarBitLength/4), which are provided by the EdDSA Domain Parameters.
 *
 * For the point arithmetic executed during the scalar multiplication iterations, extended homogeneous coordinates are used
 * as described in https://eprint.iacr.org/2008/522.pdf which represent a point (x,y) by (X:Y:Z:T) with x=X/Z, y=Y/Z and x*y=T/Z.
 * Due to the fact that with the chosen regular scalar multiplication algorithm we don't have consecutive doublings, there's no point
 * in mixing extended homogeneous with homogeneous coordinates as suggested in Section 4.3 of https://eprint.iacr.org/2008/522.pdf.
 *
 * Input:
 *  - pSession          Handle for the current CL session
 *  - pDomainParams     Pointer to ECC common domain parameters structure
 *  - iScalar Pointer   table index of secret scalar lambda
 *  - scalarBitLength   Bit length of the scalar; must coincide with the bit length of n
 *  - pMixedPointAddFct Curve dependent function to perform mixed point addition on twisted Edwards curve
 *  - pPointDoubleFct   Curve dependent function to perform point doubling on twisted Edwards curve
 *  - pPtrSelectFctFP   Function to select pre-computed point to be added
 *
 * Prerequisites:
 *  - Buffer buf(iScalar) contains the secret scalar lambda of bit length scalarBitLength
 *  - ps1Len = (operandSize, operandSize)
 *  - Buffers ECC_CP0 and ECC_CP1 contain the curve parameters a and d in MR
 *  - Buffer ECC_PFULL contains p'||p
 *  - Buffer ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - Buffers TWED_X, TWED_Y and TWED_Z contain Xres, Yres and Zres in MR
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TEXT_IN_COMMENTS()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_TwEd_FixScalarMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_FixScalarMult(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_CommonDomainParams_t *pDomainParams,
    uint8_t iScalar,
    uint32_t scalarBitLength,
    const mcuxClEcc_TwEd_MixedPointAddFunction_FP_t *pMixedPointAddFctFP,
    const mcuxClEcc_TwEd_PointDoubleFunction_FP_t *pPointDoubleFctFP,
    const mcuxClEcc_TwEd_PtrSelectFunction_FP_t *pPtrSelectFctFP
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_TwEd_FixScalarMult);

    const uint32_t byteLenP = pDomainParams->byteLenP;

    /* Determine pointer table pointer */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy - TODO CLNS-6410: check if this is necessary


    /*
     * Step 1: Ensure that the scalar used subsequently is odd by negating it modulo n
     *
     * NOTE: As a prerequisite of this function, the passed scalarBitLength equals the bit length of n.
     *       Hence, scalarBitLength is also an appropriate scalar length for the negative scalar.
     */
    // TODO: hardening
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("MISRA Ex. 9 to Rule 11.3 - pOperands is 32-bit aligned");
    uint32_t *pScalar = (uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();
    MCUXCLPKC_WAITFORFINISH();
    const uint32_t scalarLsb = pScalar[0u] & 0x1u;
    if(0u == scalarLsb)
    {
        MCUXCLPKC_FP_CALC_OP1_SUB(iScalar, ECC_N, iScalar);
    }

    /*
     * Step 2: Call function mcuxClEcc_RecodeAndReorderScalar to obtain the recoded
     *         and reordered secret scalar lambda' in buffer buf(iScalar).
     */

    /* Round scalar length up to the next multiple of f as this is required by the reordering and comb method. */
    scalarBitLength = MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE * ((scalarBitLength + (MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE - 1u)) / MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE);

    /* Recode and reorder scalar. */
    MCUXCLECC_FP_RECODEANDREORDERSCALAR(iScalar, MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE, scalarBitLength);

    /*
     * Step 3: Initialize the accumulated point P in buffers TWED_X, TWED_Y, TWED_Z and TWED_T with
     *         the coordinates of the neutral point given in extended homogeneous coordinates (0:Z:Z:0) for some Z (!==) 0 modp (in MR).
     */
    MCUXCLPKC_FP_CALC_OP1_CONST(TWED_X, 0u);
    MCUXCLPKC_FP_CALC_OP1_NEG(TWED_Y, ECC_P);
    MCUXCLPKC_FP_CALC_OP1_NEG(TWED_Z, ECC_P);
    MCUXCLPKC_FP_CALC_OP1_CONST(TWED_T, 0u);

    /*
     * Step 4: For each of the 8 pre-computed points Pi, i = 0,...,7, call function mcuxClEcc_TwEd_PrecPointImportAndValidate to
     *          - import its x- and y-coordinates, convert them to extended affine coordinates in MR and in range [0,p-1]
     *            and store them in buffers TWED_PP_Xi TWED_PP_Yi.
     *          - calculate the t-coordinates (ti = xi * yi) in MR in range [0,p-1] and store them in buffers TWED_PP_Ti.
     *          - verify that the point lies on the curve
     */
    for(uint32_t i = 0u; i < MCUXCLECC_TWED_FIXSCALARMULT_NOOFPRECPOINTS; i++)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(importPointStatus,
            mcuxClEcc_TwEd_PrecPointImportAndValidate(pSession, (uint8_t)(TWED_PP_X0 + (TWED_PP_X1 - TWED_PP_X0) * i), pDomainParams->pPrecPoints + (2u * i * byteLenP), (uint16_t)byteLenP));
        if(MCUXCLECC_STATUS_OK != importPointStatus)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_FixScalarMult, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
    }

    /*
     * Step 5: For i from (scalarBitLength - 4) down to 0:
     *          - Call point doubling routine defined by pPointDoubleFct to compute P = 2*P
     *          - Get digit (i3 i2 i1 i0)_2 at offset i in buf(iScalar), and set PP = P_((i3 i2 i1)_2 ^ (i0 i0 i0)_2 ^ (1 1 1)_2)
     *          - Call pointer selection routine specified by pPtrSelectFct to set TWED_PP_VX0 to the buffer storing the X-coordinate of PP and
     *             - if i0 = 1, set TWED_PP_VY0 and TWED_PP_VT0 to the buffers storing the Y- and T-coordinates of PP.
     *             - if i0 = 0, set TWED_PP_VY0 and TWED_PP_VT0 to buffers ECC_T2 and ECC_T3 and store the negative Y- and T-coordinates of PP in buffers ECC_T2 and ECC_T3.
     *          - Call mixed point addition routine defined by pMixedPointAddFct to compute P = P + PP.
     */
    uint32_t currentDigitBitIndex = scalarBitLength; /* scalarBitLength is multiple of MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE, so index can be unsigned. */
    uint32_t currentScalarWord = 0u;
    MCUX_CSSL_FP_LOOP_DECL(whileLoop);
    MCUX_CSSL_FP_BRANCH_DECL(ifInWhile);
    while(currentDigitBitIndex > 0u)
    {
        /* Update loop counter, deviation from the design to let iterate over unsigned value */
        currentDigitBitIndex -= MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE;

        /* Read next scalar word if needed. */
        uint32_t currentDigitInWordIndex  = currentDigitBitIndex % 32u;
        if(((uint32_t)currentDigitBitIndex == (scalarBitLength - 4u)) || (currentDigitInWordIndex  == (32u - MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE)))
        {
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
            uint32_t currentScalarWordIndex = currentDigitBitIndex / 32u;
            currentScalarWord = pScalar[currentScalarWordIndex];
            MCUX_CSSL_FP_BRANCH_POSITIVE(ifInWhile);
        }

        /* Call point doubling routine defined by pPointDoubleFct to compute P = 2*P */
        MCUX_CSSL_FP_FUNCTION_CALL(ret_DoubleFct, pPointDoubleFctFP->pPointDoubleFct());

        /* Call pointer selection routine specified by pPtrSelectFct to set TWED_PP_VX0, TWED_PP_VY0 and TWED_PP_VT0
         * to the buffers storing the X-, Y- and T-coordinates of PP. */
        MCUX_CSSL_FP_FUNCTION_CALL(ret_PtrSelectFct, pPtrSelectFctFP->pPtrSelectFct(pSession, currentScalarWord, currentDigitInWordIndex));

        /* Call mixed point addition routine defined by pMixedPointAddFct to compute P = P + PP. */
        MCUX_CSSL_FP_FUNCTION_CALL(ret_MixedAddFct, pMixedPointAddFctFP->pMixedPointAddFct());

        if((MCUXCLECC_STATUS_OK != ret_DoubleFct) || (MCUXCLECC_STATUS_OK != ret_PtrSelectFct) || (MCUXCLECC_STATUS_OK != ret_MixedAddFct))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_FixScalarMult, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* FP balancing for the loop iteration */
        MCUX_CSSL_FP_LOOP_ITERATION(whileLoop,
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(ifInWhile,
                                              (currentDigitBitIndex == (scalarBitLength - 1u)) || (currentDigitInWordIndex == (32u - MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE))),
            pPointDoubleFctFP->pointDoubleFct_FP_FuncId,
            pPtrSelectFctFP->ptrSelectFct_FP_FuncId,
            pMixedPointAddFctFP->mixedPointAddFct_FP_FuncId
            );
    }

    /*
     * Step 6: Restore the original scalar and negate the resulting point if needed.
     */
    if(0u == scalarLsb)
    {
        MCUXCLPKC_FP_CALC_OP1_SUB(iScalar, ECC_N, iScalar);
        MCUXCLPKC_FP_CALC_MC1_MS(TWED_X, ECC_P, TWED_X, ECC_PS);
    }


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_TwEd_FixScalarMult, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_CONDITIONAL((0u == scalarLsb),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SUB),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_RecodeAndReorderScalar),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLECC_TWED_FIXSCALARMULT_NOOFPRECPOINTS * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_TwEd_PrecPointImportAndValidate),
        MCUX_CSSL_FP_LOOP_ITERATIONS(whileLoop, (scalarBitLength / MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE)),
        MCUX_CSSL_FP_CONDITIONAL((0u == scalarLsb),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SUB,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS)
    );
}
