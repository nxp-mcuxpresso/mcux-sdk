/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder.c
 * @brief mcuxClEcc: implementation of ECC internal secure scalar multiplication function montgomery ladder based
 */


#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClRandom.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Mont_Internal.h>
#include <internal/mcuxClEcc_Internal_SecurePointSelect.h>
#include <internal/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder_FUP.h>


/**
 * This function implements secure point scalar multiplication, R = scalar * P, based on XZ coordinates Montgomery ladder.
 *
 * Inputs:
 *   iScalar: index of PKC buffer storing the scalar, which is non-zero and in little-endian;
 *   scalarBitLength: bit length of scalar.
 *   optionAffineOrProjective: Option value specifying whether the input point P is given in affine or randomized projective coordinates
 *
 *
 * Prerequisites:
 *   If optionAffineOrProjective is set to MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT, buffer MONT_X0 contains x in MR
 *   If optionAffineOrProjective is set to MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT, buffers MONT_X0 and MONT_Z0 contain X and Z in MR
 *   buffer buf(iScalar) contains the secret scalar lambda of bit length scalarBitLength
 *   buffer ECC_CP0 contains the ladder constant A24=(A+2)/4 mod p in MR
 *   ps1Len = (operandSize, operandSize)
 *   Buffer ECC_PFULL contains p'||p
 *   Buffer ECC_PS contains the shifted modulus associated to p
 *
 * Result in PKC workarea:
 *   buffers MONT_X0 and MONT_Z0 contain Xres and Zres in MR
 *
 * Other modifications:
 *   buffers ECC_T0, ECC_T1, ECC_T2, ECC_T3, MONT_X1, MONT_X2, MONT_Z1, MONT_Z2 modified
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(mcuxClSession_Handle_t pSession, uint8_t iScalar, uint32_t scalarBitLength, uint32_t optionAffineOrProjective)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder);

    /* Determine pointer table pointer */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy - TODO CLNS-6410: check if this is necessary
    const uint32_t *pScalar = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);  /* MISRA Ex. 9 to Rule 11.3 - PKC word is CPU word aligned. */

    /* Initialize accumulated coordinate buffers for the ladder iteration depending on optionAffineOrProjective
     * NOTE: As discussed with SA, no coordinate or pointer table randomization/re-randomization is needed for the moment. It can easily be added at a later point in time.
     */
    MCUXCLPKC_FP_CALC_OP1_NEG(MONT_X1, ECC_P); /* 1 in MR */
    MCUXCLPKC_FP_CALC_OP1_CONST(MONT_Z1, 0u);

    MCUX_CSSL_FP_SWITCH_DECL(optionAffineOrProjectiveSwitch);
    if(MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT == optionAffineOrProjective)
    {
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_X2, MONT_X0, 0u);
        MCUXCLPKC_FP_CALC_OP1_NEG(MONT_Z2, ECC_P); /* 1 in MR */
        MCUX_CSSL_FP_SWITCH_CASE(optionAffineOrProjectiveSwitch, MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT, MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST, MCUXCLPKC_FP_CALLED_CALC_OP1_NEG);

    }
    else if(MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT == (MCUXCLECC_SCALARMULT_OPTION_INPUT_MASK & optionAffineOrProjective))
    {
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_X2, MONT_X0, 0u);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_Z2, MONT_Z0, 0u);
        MCUX_CSSL_FP_SWITCH_CASE(optionAffineOrProjectiveSwitch, MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT, MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST, MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST);

    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /* Perform ladder iteration to calculate (X_res:Z_res) */
    uint32_t i = scalarBitLength;
    uint32_t maskedCurrentScalarWord = 0u;
    MCUX_CSSL_FP_LOOP_DECL(whileLoop);
    MCUX_CSSL_FP_BRANCH_DECL(ifInWhile);
    while(0u < i)
    {

        /* Update loop counter, deviation from the design to let iterate over unsigned value */
        --i;
        /* Set pointers pOperands(MONT_VX1),...,pOperands(MONT_VZ2) according to the bit to be processed */
        MCUXCLPKC_WAITFORFINISH();
        uint32_t currentScalarBitInWord = i % 32u;
        uint32_t currentScalarWordMask;

        if((i == (scalarBitLength - 1u)) || ((i % 32u) == 31u))
        {
            MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom0, mcuxClRandom_ncGenerate(pSession, (uint8_t*)&currentScalarWordMask, sizeof(uint32_t)));
            if (MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom0)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
            }
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy

            uint32_t currentScalarWordIndex = i / 32u;
            maskedCurrentScalarWord = pScalar[currentScalarWordIndex] ^ currentScalarWordMask;
            MCUX_CSSL_FP_BRANCH_POSITIVE(ifInWhile, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
        }
        uint32_t offsetsP0 = 0xFFFFFFFFu;
        uint32_t offsetsP1 = 0xFFFFFFFFu;
        uint32_t randomMask;

        MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom1, mcuxClRandom_ncGenerate(pSession, (uint8_t*)&randomMask, sizeof(uint32_t)));
        if (MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* When bit of scalar = 0, the macro returns:                  */
        /*   offsetsP0 = pOperands[MONT_Z1] || pOperands[MONT_X1], and */
        /*   offsetsP1 = pOperands[MONT_Z2] || pOperands[MONT_X2];     */
        /* when bit = 1,                                               */
        /*   offsetsP0 = pOperands[MONT_Z2] || pOperands[MONT_X2], and */
        /*   offsetsP1 = pOperands[MONT_Z1] || pOperands[MONT_X1].     */
        MCUXCLECC_SECUREPOINTSELECT(offsetsP0, offsetsP1, pOperands, MONT_X1,
                                   maskedCurrentScalarWord, currentScalarWordMask, randomMask, currentScalarBitInWord);

        MCUXCLPKC_WAITFORREADY();
        uint32_t *pOperands32 = (uint32_t *) pOperands;
        MCUXCLECC_STORE_2OFFSETS(pOperands32, MONT_VX1, MONT_VZ1, offsetsP0);
        MCUXCLECC_STORE_2OFFSETS(pOperands32, MONT_VX2, MONT_VZ2, offsetsP1);

        /* Perform the ladder step to calculate (MONT_VX1,MONT_VZ1) = 2 * (MONT_VX1,MONT_VZ1) and (MONT_VX2, MONT_VZ2) = (MONT_VX1,MONT_VZ1) + (MONT_VX2,MONT_VZ2)*/

        /* FP balancing at the end of loop iteration end as both cases are calling same function */
        if(MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT == (MCUXCLECC_SCALARMULT_OPTION_INPUT_MASK & optionAffineOrProjective))
        {
            MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep,
                                mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep_Projective_LEN);
        }
        else
        {
            MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep,
                    mcuxClEcc_FUP_SecureScalarMult_XZMontLadder_LadderStep_Affine_LEN);
        }

        MCUX_CSSL_FP_LOOP_ITERATION(whileLoop,
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(ifInWhile, (i == (scalarBitLength - 1u)) || ((i % 32u) == 31u)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
            );
    }

    /* Copy resulting coordinates to buffers MONT_X0 and MONT_Z0 */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_X0, MONT_X1, 0u);           /* MONT_X0 = MONT_X1 */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_Z0, MONT_Z1, 0u);           /* MONT_Z0 = MONT_Z1 */

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder, MCUXCLECC_STATUS_OK,
                    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
                    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                    /* switch statement */
                    MCUX_CSSL_FP_SWITCH_TAKEN(
                            optionAffineOrProjectiveSwitch,
                            MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT,
                            MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT == (MCUXCLECC_SCALARMULT_OPTION_INPUT_MASK & optionAffineOrProjective)),
                    MCUX_CSSL_FP_SWITCH_TAKEN(
                            optionAffineOrProjectiveSwitch,
                            MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT,
                            MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT == (MCUXCLECC_SCALARMULT_OPTION_INPUT_MASK & optionAffineOrProjective)),
                    MCUX_CSSL_FP_LOOP_ITERATIONS(whileLoop, scalarBitLength),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
                    MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST
                    );
}
