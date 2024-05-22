/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClEcc_Weier_Internal_PointCheck.c
 * @brief Weierstrass curve internal point check
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_PointCheck_FUP.h>


/**
 * This function checks a point, if y^2 == x^3 + a*x + b (mod p).
 * @retval #MCUXCLECC_STATUS_OK
 * @retval #MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK
 *
 * Inputs in pOperands[] and PKC workarea:
 *   buffers (VX0,VY0) contain the point, affine, normal representation.
 *
 * Prerequisites:
 *   buffer WEIER_A contains curve coefficient a, Montgomery representation;
 *   buffer WEIER_B contains curve coefficient b, normal representation;
 *   ps1Len = (operandSize, operandSize);
 *   curve order p in P, NDash of p in PFULL,
 *   shifted modulus of p in PS, QSquare of p in PQSQR.
 *
 * Result in PKC workarea:
 *   buffer T0 contains (- y^2 + x^3 + a*x + b) mod p, in the range [0, p-1].
 *
 * Other modifications:
 *   buffers T1 and T2 are modified (as temp).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointCheckAffineNR)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointCheckAffineNR(void)

{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointCheckAffineNR);

    /* Calculate t0 = (- y^2 + x^3 + ax + b) mod p. */
    /* MISRA Ex. 22, while(0) is allowed */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_PointCheckAffNR,
                        mcuxClEcc_FUP_Weier_PointCheckAffNR_LEN);

    /* Check: if t0 != 0. */
    if (MCUXCLPKC_FLAG_NONZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR, MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    /* Check (2nd): if t0 == 0. */
    MCUXCLPKC_FP_CALC_OP1_SUB_CONST(ECC_T1, ECC_T0, 1u);
    if (MCUXCLPKC_FLAG_CARRY == MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR, MCUXCLECC_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR, MCUXCLECC_STATUS_FAULT_ATTACK);
}
