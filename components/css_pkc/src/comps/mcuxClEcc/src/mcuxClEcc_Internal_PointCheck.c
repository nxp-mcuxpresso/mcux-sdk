/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClEcc_Internal_PointCheck.c
 *  @brief mcuxClEcc: implementation of ECC internal point check function
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointCheckAffineNR)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointCheckAffineNR(void)

{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointCheckAffineNR);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_PointCheckAffNR,
                        mcuxClEcc_Fup_PointCheckAffNR_LEN);

    if (MCUXCLPKC_FLAG_NONZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR, MCUXCLECC_INTSTATUS_POINTCHECK_NOTOK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    MCUXCLPKC_FP_CALC_OP1_SUB_CONST(ECC_T1, ECC_T0, 1u);
    if (MCUXCLPKC_FLAG_CARRY == MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR, MCUXCLECC_INTSTATUS_POINTCHECK_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR, MCUXCLECC_STATUS_FAULT_ATTACK);
}
