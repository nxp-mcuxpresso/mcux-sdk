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

/** @file  mcuxClEcc_Internal_NIST.c
 *  @brief mcuxClEcc: implementation of ECC internal functions for NIST prime curves (a=-3)
 */

#include <mcuxClPkc.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_NIST.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_RepeatPointDouble_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_RepeatPointDouble_NIST(uint32_t iteration)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_RepeatPointDouble_NIST);

    if (1u == iteration)
    {

        MCUXCLECC_FP_CALCFUP_ONE_DOUBLE_NIST();

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_RepeatPointDouble_NIST, MCUXCLECC_STATUS_OK,
            MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE_NIST );
    }

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_RepeatDouble_NIST,
                        mcuxClEcc_Fup_RepeatDouble_NIST_Len);

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

        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_RepeatDouble_NIST, mcuxClEcc_Fup_RepeatDouble_NIST_Len1,
                                   mcuxClEcc_Fup_RepeatDouble_NIST_Len2 + mcuxClEcc_Fup_RepeatDouble_NIST_Len3);
        remIter--;
    }

    MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_RepeatDouble_NIST, mcuxClEcc_Fup_RepeatDouble_NIST_Len1,
                               mcuxClEcc_Fup_RepeatDouble_NIST_Len2);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_RepeatPointDouble_NIST, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_LOOP_ITERATIONS(Doublings, iteration - 2u),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Int_PointMult_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_PointMult_NIST(uint8_t iScalar, uint32_t scalarBitLen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Int_PointMult_NIST);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    const uint32_t *pScalar = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);

    uint32_t scalarWord;
    uint32_t scalarBits;
    uint32_t index = scalarBitLen;

    MCUX_CSSL_FP_LOOP_DECL(PointMult_Double);
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    do
    {
        MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Double);

        index -= 2u;
        scalarWord = pScalar[index / 32u];
        scalarBits = (scalarWord >> (index & 31u)) & 0x3u;
    } while (0u == scalarBits);

    uint32_t offsets_VY_VX = pOperands32[(ECC_X1 / 2u) - 1u + scalarBits];

    uint32_t offsets_VYA_VXA = MCUXCLECC_LOAD_2OFFSETS(pOperands32, ECC_XA, ECC_YA);

    MCUXCLPKC_FP_CALC_OP1_NEG(ECC_ZA, ECC_P);

    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, offsets_VY_VX);

    uint32_t NoOfAdd = 0u;

    MCUX_CSSL_FP_LOOP_DECL(PointMult_Add);
    if (0u == index)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Add,
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST );
        NoOfAdd += 1u;

        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_XA, ECC_VX2, 0u);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_YA, ECC_VY2, 0u);
    }
    else
    {
        MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Double,
            MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE_NIST );

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_T2, ECC_T3);
        MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, offsets_VYA_VXA);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ, ECC_ZA, ECC_Z);
        pOperands[ECC_VZ2] = pOperands[ECC_ZA];

        MCUXCLECC_FP_CALCFUP_ONE_DOUBLE_NIST();

        index -= 2u;
        MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
        scalarWord = pScalar[index / 32u];
        scalarBits = (scalarWord >> (index & 31u)) & 0x3u;

        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, offsets_VYA_VXA);

        if (0u != scalarBits)
        {
            MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Add,
                MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY );
            NoOfAdd += 1u;

            offsets_VY_VX = pOperands32[(ECC_X1 / 2u) - 1u + scalarBits];
            MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, offsets_VY_VX);

            MCUXCLECC_FP_CALCFUP_ADD_ONLY();
        }
    }

    while (0u != index)
    {
        index -= 2u;
        if (0x1Eu == (index & 0x1Fu))
        {
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
            scalarWord = pScalar[index / 32u];
        }
        scalarBits = (scalarWord >> (index & 0x1Fu)) & 0x3u;

        if (0u == scalarBits)
        {
            MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Double,
                MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE_NIST );

            MCUXCLECC_FP_CALCFUP_ONE_DOUBLE_NIST();
        }
        else
        {
            MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Double);
            MCUX_CSSL_FP_LOOP_ITERATION(PointMult_Add,
                MCUXCLECC_FP_CALLED_CALCFUP_DOUBLE_ADD );
            NoOfAdd += 1u;

            offsets_VY_VX = pOperands32[(ECC_X1 / 2u) - 1u + scalarBits];
            MCUXCLPKC_WAITFORREADY();
            MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, offsets_VY_VX);

            MCUXCLECC_FP_CALCFUP_DOUBLE_ADD();
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_PointMult_NIST, MCUXCLECC_STATUS_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
        MCUX_CSSL_FP_LOOP_ITERATIONS(PointMult_Double, scalarBitLen / 2u),
        MCUX_CSSL_FP_LOOP_ITERATIONS(PointMult_Add, NoOfAdd) );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointCheckAffineNR_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointCheckAffineNR_NIST(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointCheckAffineNR_NIST);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_PointCheckAffNR_NIST,
                        mcuxClEcc_Fup_PointCheckAffNR_NIST_Len);

    if (MCUXCLPKC_FLAG_NONZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR_NIST, MCUXCLECC_INTSTATUS_POINTCHECK_NOTOK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    MCUXCLPKC_FP_CALC_OP1_SUB_CONST(ECC_T1, ECC_T0, 1u);
    if (MCUXCLPKC_FLAG_CARRY == MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR_NIST, MCUXCLECC_INTSTATUS_POINTCHECK_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointCheckAffineNR_NIST, MCUXCLECC_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointFullAdd_NIST)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointFullAdd_NIST(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointFullAdd_NIST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS );

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pOperands32 = (uint32_t *) pOperands;

    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_T2, ECC_T3);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len1);

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_VX0, ECC_VT2, ECC_PS);
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_T0,  ECC_P,   ECC_P);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {

        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len1,
                                   mcuxClEcc_Fup_DoubleAdd_Len2);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointFullAdd_NIST, MCUXCLECC_INTSTATUS_POINTADD_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    MCUXCLPKC_FP_CALC_MC1_MA(ECC_T0, ECC_VY0, ECC_VT3, ECC_PS);
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_T0,  ECC_P,   ECC_P);
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointFullAdd_NIST, MCUXCLECC_INTSTATUS_POINTADD_NEUTRAL_POINT,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MA,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
    }

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, ECC_VX0, ECC_VY0);
    MCUXCLECC_FP_CALCFUP_ONE_DOUBLE_NIST();

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointFullAdd_NIST, MCUXCLECC_INTSTATUS_POINTADD_OK,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MA,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE_NIST );
}
