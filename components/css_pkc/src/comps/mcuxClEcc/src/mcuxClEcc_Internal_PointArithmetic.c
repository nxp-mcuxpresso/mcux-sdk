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

/** @file  mcuxClEcc_Internal_PointArithmetic.c
 *  @brief mcuxClEcc: implementation of ECC internal point arithmetic functions
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_RepeatPointDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_RepeatPointDouble(uint32_t iteration)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_RepeatPointDouble);

    if (1u == iteration)
    {

        MCUXCLECC_FP_CALCFUP_ONE_DOUBLE();

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_RepeatPointDouble, MCUXCLECC_STATUS_OK,
            MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE );
    }

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_RepeatDouble,
                        mcuxClEcc_Fup_RepeatDouble_Len);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, ECC_VX0, ECC_VY0);
    pOperands[ECC_VZ2] = pOperands[ECC_VZ0];

    uint32_t remIter = iteration - 1u;
    MCUX_CSSL_FP_LOOP_DECL(Doublings);
    while(remIter > 1u)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(Doublings,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_RepeatDouble, mcuxClEcc_Fup_RepeatDouble_Len1,
                                   mcuxClEcc_Fup_RepeatDouble_Len2 + mcuxClEcc_Fup_RepeatDouble_Len3);
        remIter--;
    }

    MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_RepeatDouble, mcuxClEcc_Fup_RepeatDouble_Len1,
                               mcuxClEcc_Fup_RepeatDouble_Len2);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_RepeatPointDouble, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_LOOP_ITERATIONS(Doublings, iteration - 2u),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointFullAdd)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointFullAdd(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointFullAdd,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS );

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pOperands32 = (uint32_t *) pOperands;

    MCUXCLPKC_WAITFORREADY();

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_T2, ECC_T3);
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len1);

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T1, ECC_VX0, ECC_VT2, ECC_PS);
    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T0, ECC_T1,  ECC_P);
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_T0,  ECC_P,   ECC_P);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {

        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len1,
                                   mcuxClEcc_Fup_DoubleAdd_Len2);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointFullAdd, MCUXCLECC_INTSTATUS_POINTADD_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    MCUXCLPKC_FP_CALC_MC1_MA(ECC_T1, ECC_VY0, ECC_VT3, ECC_PS);
    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T0, ECC_T1,  ECC_P);
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_T0,  ECC_P,   ECC_P);
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointFullAdd, MCUXCLECC_INTSTATUS_POINTADD_NEUTRAL_POINT,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MA,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
    }

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, ECC_VX0, ECC_VY0);
    MCUXCLECC_FP_CALCFUP_ONE_DOUBLE();

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointFullAdd, MCUXCLECC_INTSTATUS_POINTADD_OK,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MA,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE );
}
