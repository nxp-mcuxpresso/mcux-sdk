/*--------------------------------------------------------------------------*/
/* Copyright 2018-2023 NXP                                                  */
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

/*
 * @file: mcuxClOsccaSm2_Ecc.c
 * @brief: OSCCA SM2 ECC functions
 */

#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxClRandom.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>
#include <internal/mcuxClOsccaPkc_Macros.h>

/* check the jacobian coordinates of 2 points if equal mod p */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointCheckCoordinate)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaSm2_EccPointCheckCoordinate(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointCheckCoordinate);
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t cmpX, cmpY;
    uint32_t Ret = 0U;

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_PointCheckCoordinateX,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_PointCheckCoordinateX)));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    MCUX_CSSL_FP_FUNCTION_CALL(EccCmpRet1, mcuxClOsccaSm2_RobustCompareToZero(
            (uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]),
            operandSize));
    if (MCUXCLOSCCASM2_STATUS_CMP_EQUAL == EccCmpRet1)
    {
        cmpX = MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL;
    }
    else
    {
        cmpX = MCUXCLOSCCASM2_STATUS_COORDINATE_NOT_EQUAL;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_PointCheckCoordinateY,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_PointCheckCoordinateY)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(EccCmpRet2,mcuxClOsccaSm2_RobustCompareToZero(
            (uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]),
            operandSize));

    if (MCUXCLOSCCASM2_STATUS_CMP_EQUAL == EccCmpRet2)
    {
        cmpY = MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL;
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
                (const void *)mcuxClOsccaSm2_FUP_PointCheckCoordinateNegY,
                MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_PointCheckCoordinateNegY)));

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

        MCUX_CSSL_FP_FUNCTION_CALL(EccCmpRet3, mcuxClOsccaSm2_RobustCompareToZero(
                (uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]),
                operandSize));
        Ret = EccCmpRet3;
        if (MCUXCLOSCCASM2_STATUS_CMP_EQUAL == Ret)
        {
            cmpY = MCUXCLOSCCASM2_STATUS_COORDINATE_INVERSE_EQUAL;
        }
        else
        {
            cmpY = MCUXCLOSCCASM2_STATUS_COORDINATE_NOT_EQUAL;
        }
    }

    MCUX_CSSL_SC_SUB((uint32_t)EccCmpRet1 + 2u * ((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]) + (uint32_t)operandSize) + (uint32_t)EccCmpRet2
                   + ((MCUXCLOSCCASM2_STATUS_CMP_EQUAL != EccCmpRet2) ? ((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]) + (uint32_t)Ret + (uint32_t)operandSize) : 0u));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccPointCheckCoordinate, (uint32_t)((uint32_t)(cmpX << 16u) | cmpY),
                                                          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                          MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ECC_BALANCE_INIT_PART,
                                                          MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ECC_BALANCE_SECOND_PART,
                                                          MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM2_STATUS_CMP_EQUAL != EccCmpRet2),
                                                             MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ECC_BALANCE_FAIL_PART));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointDouble(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointDouble);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_PointDouble,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_PointDouble)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccPointDouble,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish));

}
/*
 * Compute the relative Jacobian coordinates (X2, Y2, Z2')
 * of P2 = P0 + P1, where P0 is given in Jacobian (X0, Y0, Z0)
 * and P1 in relative Jacobian coordinates (X1, Y1, Z1') w.r.t. P0.
 *
 * Prerequisites:
 *  - The values for X0, Y0, Z0, X1, Y1, and Z1' should be stored in the buffers
 *    of _x0, _y0, _z, _xa, _ya, and _z1, respectively, in Montgomery representation.
 *  - The buffer pointers PTR_VX0 and PTR_VY0 must be different from PTR_XA and PTR_YA.
 *  - The _modulus and _moduluss pointers should point to buffers containing
 *    (p || p') and the shifted modulus, respectively.
 *
 * Result:
 *  - The resulting coordinates are stored in _xa, _ya, _za in Montgomery representation.
 *  - The buffers _s, _t, _u, and _v have been modified.
 *
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointAdd)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointAdd(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointAdd);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *)mcuxClOsccaSm2_FUP_PointAdd,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_PointAdd)));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccPointAdd,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish));

}

/*
* split the scalar by scalar = scalar1 * scalar2 mod n
* for montgomery point mult
*/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointMultSplitScalar)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccPointMultSplitScalar(mcuxClSession_Handle_t session, uint32_t scalarIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointMultSplitScalar);

    uint32_t operandSize = (uint32_t)MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t *pScalar2 = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_scalar2]);

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    MCUXCLMEMORY_FP_MEMORY_CLEAR(pScalar2, bufferSize);
    /* Generate TI_scalar2 = phi = a 64-bit non-zero random, with PRNG. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_ARRAY_OUT_OF_BOUNDS("pScalar2 point a PKC operand ram with size equal operandSize.")
    MCUX_CSSL_FP_FUNCTION_CALL(ret, mcuxClRandom_ncGenerate(session, pScalar2, 8U)); // scalar2 = d1
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ARRAY_OUT_OF_BOUNDS()
    if (MCUXCLRANDOM_STATUS_OK != ret)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccPointMultSplitScalar, MCUXCLOSCCASM2_STATUS_POINTMULTSPLIT_FAIL);
    }
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_ARRAY_OUT_OF_BOUNDS("pScalar2 point a PKC operand ram with size equal operandSize.")
    pScalar2[7] |= 0x80u; //set the msb
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ARRAY_OUT_OF_BOUNDS()

    /* Calculate TI_v = TI_scalar2_inv = TI_scalar2^(-1) * R mod n. */
    MCUXCLOSCCAPKC_FXIMC1_MRED(TI_s, TI_scalar2, TI_n);  /* TI_s = TI_scalar2 * R^-1 mod n */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_t, TI_s, TI_n2, TI_n); /* TI_t = TI_s * R^2 mod R = TI_scalar2 * R mod n */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeModInv(MCUXCLOSCCAPKC_PKCPACKARGS(TI_t, TI_v, TI_n, TI_s), TI_u));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    /* Calculate TI_scalar1 = TI_scalar2^(-1) * scalarIdx mod n  */
    MCUXCLOSCCAPKC_FXIMC1_MRED(TI_s, scalarIdx, TI_n);         /* TI_s = scalarIdx * R^-1 mod n */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_u, TI_s, TI_n2, TI_n);       /* TI_u = scalarIdx * R mod n */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_scalar1, TI_u, TI_v, TI_n);  /* TI_scalar1 = scalarIdx * TI_scalar2^(-1) * R mod n */
    MCUXCLOSCCAPKC_FXIMC1_MRED(TI_v, TI_scalar1, TI_n);        /* TI_scalar1 = TI_scalar1 * R ^(-1) mod n */
    MCUXCLOSCCAPKC_FXIMC1_MSUB(TI_scalar1, TI_v, TI_n, TI_n);  /* TI_scalar1 = (TI_v - TI_n) mod n */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccPointMultSplitScalar, MCUXCLOSCCASM2_STATUS_POINTMULTSPLIT_OK,
                                                     3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeModInv),
                                                     7u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccSecurePointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccSecurePointMult(mcuxClSession_Handle_t session, uint32_t scalarIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccSecurePointMult);

    uint32_t loopTimes = 0U;
    do
    {
        loopTimes++;
        /* mask the original scalar with scalar1 * scalar2 */
        MCUX_CSSL_FP_FUNCTION_CALL(splitRet, mcuxClOsccaSm2_EccPointMultSplitScalar(session, scalarIdx));
        if (MCUXCLOSCCASM2_STATUS_POINTMULTSPLIT_OK != splitRet)
        {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccSecurePointMult, MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_FAIL);
        }
        /* avoid the bad scalar1 = n - 1 */
        MCUXCLOSCCAPKC_FXIOP1_SUB_YC(TI_t, TI_n, 1);
        MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(TI_scalar1, TI_t);
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
        if (true == MCUXCLOSCCAPKC_GETCARRY())
        {
            break;
        }
    }while(loopTimes < UINT32_MAX);

    if (UINT32_MAX == loopTimes)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccSecurePointMult, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* caculate Q = scalar1 * P */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointMultMontgomery(TI_scalar1));
    /* update the z */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_UpdateZ,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_UpdateZ)));
    /* caculate R = scalar2 * Q */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointMultMontgomery(TI_scalar2));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccSecurePointMult, MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK,
                                                     loopTimes * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultSplitScalar)+
                                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)+
                                                                  2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram));
}

/*
 * montgomeryLadder impl
 * notice: the scalar must be less than n
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointMultMontgomery)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointMultMontgomery(uint32_t scalarIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointMultMontgomery);
    uint32_t  valid_bits = 0u, lowbit = 0U;
    int32_t i, msb_found = 0;
    uint32_t j;
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t *pScalar = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[scalarIdx]);
    uint32_t operandSize = (uint32_t)MCUXCLOSCCAPKC_PS1_GETOPLEN();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_EccPointMultMontgomery_InitPoints,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_EccPointMultMontgomery_InitPoints)));

    /* avoid pScalar[i] and Previous PKC operation concurrently accessing to PKC workarea */
    MCUXCLOSCCAPKC_PKC_CPU_ARBITRATION_WORKAROUND();

    for (i = (int32_t)operandSize - 1; i >= 0; i--)
    {
        for (j = 0x80u; j != 0u; j >>= 1u)
        {
            if((0u == (pScalar[i] & j)) && (0 == msb_found))
            {
                continue;
            }
            msb_found = 1;
            /* Due to the limitation of the algorithm, this branch is processed when the last bit of pScalar[0] is 1u.
             * When the pScalar[0] = 1u, the last bit process as: R0 = 2R0, R0 = 2R0 + P
             * In addition, for the case where the last bit of pScalar is 1u, the case that pScalar is equal to 1 should
             * be excluded, because for pScalar = 1U, the R0 is Zero.
            */
            if((0u != (pScalar[i] & j)) && (i == 0) && (j == 0x01u) && (valid_bits != 0U))
            {
                lowbit++;
                /* double the R0 */
                pOperands[TI_xa] = pOperands[TI_sx0];
                pOperands[TI_ya] = pOperands[TI_sy0];
                pOperands[TI_z1] = pOperands[TI_sz0_dash];
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointDouble());

                /* R0 = 2*R0 + P*/
                pOperands[TI_x0] = pOperands[TI_sx];
                pOperands[TI_y0] = pOperands[TI_sy];
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointAdd());
                break;
            }
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("valid_bits can't wrap, because it always smaller than N*8.")
            valid_bits++;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            if(0u != (pScalar[i] & j))
            {
                /* double the R1 */
                pOperands[TI_xa] = pOperands[TI_sx1];
                pOperands[TI_ya] = pOperands[TI_sy1];
                pOperands[TI_z1] = pOperands[TI_sz1_dash];
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointDouble());

                /* R0  = R0 + R1 = 2R1 - P */
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
                        (const void *)mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP0P1,
                        MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP0P1)));

                pOperands[TI_xa] = pOperands[TI_sx0];
                pOperands[TI_ya] = pOperands[TI_sy0];
                pOperands[TI_z1] = pOperands[TI_sz0_dash];
                pOperands[TI_x0] = pOperands[TI_sx];
                pOperands[TI_y0] = pOperands[TI_y_neg];
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointAdd());
            }
            else
            {
                /* double the R0 */
                pOperands[TI_xa] = pOperands[TI_sx0];
                pOperands[TI_ya] = pOperands[TI_sy0];
                pOperands[TI_z1] = pOperands[TI_sz0_dash];
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointDouble());

                /* R1 = R0 + R1 = 2R0 + P*/
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
                        (const void *)mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP1P0,
                        MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_EccPointMultMontgomery_CopyP1P0)));

                pOperands[TI_xa] = pOperands[TI_sx1];
                pOperands[TI_ya] = pOperands[TI_sy1];
                pOperands[TI_z1] = pOperands[TI_sz1_dash];
                pOperands[TI_x0] = pOperands[TI_sx];
                pOperands[TI_y0] = pOperands[TI_sy];
                MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointAdd());
            }
        }
    }
    pOperands[TI_xa] = pOperands[TI_sx0];
    pOperands[TI_ya] = pOperands[TI_sy0];
    pOperands[TI_z1] = pOperands[TI_sz0_dash];

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccPointMultMontgomery,MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                                        lowbit * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointAdd)+
                                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointDouble)),
                                                                        valid_bits * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram)+
                                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointAdd)+
                                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointDouble)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointAddOrDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccPointAddOrDouble(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointAddOrDouble);
    uint32_t cmpX, cmpY;
    mcuxClOsccaSm2_Status_t addRet = MCUXCLOSCCASM2_STATUS_POINTADD_OK;

    MCUX_CSSL_FP_FUNCTION_CALL(cmpXY, mcuxClOsccaSm2_EccPointCheckCoordinate());
    cmpX = (cmpXY >> 16u) & 0xffffu;
    cmpY = cmpXY & 0xffffu;
    if (MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL== cmpX)
    {
        if (MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL== cmpY)
        {
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointDouble());
        }
        else
        {
            addRet = MCUXCLOSCCASM2_STATUS_POINTADD_INFINITE;
        }
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointAdd());
    }
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccPointAddOrDouble,addRet,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointCheckCoordinate),
                              MCUX_CSSL_FP_CONDITIONAL(((MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL== cmpX) && (MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL== cmpY)),
                                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointDouble)),
                              MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL != cmpX),
                                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointAdd)));

}
