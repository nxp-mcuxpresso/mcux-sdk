/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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

/** @file  mcuxClEcc_Internal_SecureScalarMult_XZMontLadder.c
 *  @brief mcuxClEcc: implementation of ECC internal secure scalar multiplication function montgomery ladder based
 */

#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Mont_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(uint8_t iScalar, uint32_t scalarBitLen, uint32_t optionAffineOrProjective)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    const uint32_t *pScalar = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);

    MCUXCLPKC_FP_CALC_OP1_NEG(MONT_X1, ECC_P);
    MCUXCLPKC_FP_CALC_OP1_CONST(MONT_Z1, 0u);

    MCUX_CSSL_FP_SWITCH_DECL(optionAffineOrProjectiveSwitch);
    if(MCUXCLECC_AFFINE == optionAffineOrProjective)
    {
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_X2, MONT_X0, 0u);
        MCUXCLPKC_FP_CALC_OP1_NEG(MONT_Z2, ECC_P);
        MCUX_CSSL_FP_SWITCH_CASE(optionAffineOrProjectiveSwitch, MCUXCLECC_AFFINE, MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST, MCUXCLPKC_FP_CALLED_CALC_OP1_NEG);

    }
    else if(MCUXCLECC_PROJECTIVE == optionAffineOrProjective)
    {
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_X2, MONT_X0, 0u);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_Z2, MONT_Z0, 0u);
        MCUX_CSSL_FP_SWITCH_CASE(optionAffineOrProjectiveSwitch, MCUXCLECC_PROJECTIVE, MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST, MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST);

    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    uint32_t i = scalarBitLen;
    MCUX_CSSL_FP_LOOP_DECL(whileLoop);
    while(0u < i)
    {

    	--i;

    	MCUXCLPKC_WAITFORFINISH();
        uint32_t currentScalarBitInWord = i % 32u;
        uint32_t currentScalarWordIndex = i / 32u;
        uint32_t currentScalarWord = pScalar[currentScalarWordIndex];

        uint32_t mask = (((uint32_t)1u) << (currentScalarBitInWord + 1u)) - 1u;
        uint32_t currentScalarBit = (currentScalarWord & mask) >> currentScalarBitInWord;
        MCUX_CSSL_FP_SWITCH_DECL(currentScalarBitSwitch);
        MCUXCLPKC_WAITFORFINISH();
        if(1u == currentScalarBit)
        {
            pOperands[MONT_VX1] = pOperands[MONT_X2];
            pOperands[MONT_VZ1] = pOperands[MONT_Z2];
            pOperands[MONT_VX2] = pOperands[MONT_X1];
            pOperands[MONT_VZ2] = pOperands[MONT_Z1];
            MCUX_CSSL_FP_SWITCH_CASE(currentScalarBitSwitch, 1u);
        }
        else if (0u == currentScalarBit)
        {
            pOperands[MONT_VX1] = pOperands[MONT_X1];
            pOperands[MONT_VZ1] = pOperands[MONT_Z1];
            pOperands[MONT_VX2] = pOperands[MONT_X2];
            pOperands[MONT_VZ2] = pOperands[MONT_Z2];
            MCUX_CSSL_FP_SWITCH_CASE(currentScalarBitSwitch, 0u);
        }
        else {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        MCUXCLPKC_WAITFORFINISH();

        if(MCUXCLECC_PROJECTIVE == optionAffineOrProjective)
        {
            MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_SecureScalarMult_XZMontLadder_LadderStep,
        	        mcuxClEcc_Fup_SecureScalarMult_XZMontLadder_LadderStep_Projective_LEN);
        }
        else
        {
            MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_SecureScalarMult_XZMontLadder_LadderStep,
                    mcuxClEcc_Fup_SecureScalarMult_XZMontLadder_LadderStep_Affine_LEN);
        }

        MCUX_CSSL_FP_LOOP_ITERATION(whileLoop,
            MCUX_CSSL_FP_SWITCH_TAKEN(currentScalarBitSwitch, 1u, 1u == currentScalarBit),
            MCUX_CSSL_FP_SWITCH_TAKEN(currentScalarBitSwitch, 0u, 0u == currentScalarBit),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
            );
    }

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_X0, MONT_X1, 0u);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(MONT_Z0, MONT_Z1, 0u);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder, MCUXCLECC_STATUS_OK,
                    MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
                    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,

                    MCUX_CSSL_FP_SWITCH_TAKEN(optionAffineOrProjectiveSwitch, MCUXCLECC_AFFINE, MCUXCLECC_AFFINE == optionAffineOrProjective),
                    MCUX_CSSL_FP_SWITCH_TAKEN(optionAffineOrProjectiveSwitch, MCUXCLECC_PROJECTIVE, MCUXCLECC_PROJECTIVE == optionAffineOrProjective),
                    MCUX_CSSL_FP_LOOP_ITERATIONS(whileLoop, scalarBitLen),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
                    MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST
                    );
}
