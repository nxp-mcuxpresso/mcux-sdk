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

/** @file  mcuxClEcc_Internal_SecurePointMult_CoZMontLadder.c
 *  @brief mcuxClEcc: implementation of ECC internal secure PointMult function
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClCss_Rng.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_SecurePointSelect.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_SecurePointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SecurePointMult(uint8_t iScalar,
                                                                       uint32_t scalarBitLen)

{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_SecurePointMult,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord),
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
        MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    const uint32_t *pScalar = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);

    uint8_t *pZA = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_ZA]);
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom0, mcuxClCss_Prng_GetRandom(pZA, operandSize));
    if (MCUXCLCSS_STATUS_OK != ret_Prng_GetRandom0)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_INTSTATUS_RNG_ERROR);
    }
    pOperands[ECC_VT] = 0x01u;
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1,
                        mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1
                        + mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2);

    uint32_t scalarBitIndex = scalarBitLen - 1u;
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint32_t scalarWord0 = pScalar[scalarBitIndex / 32u];
    uint32_t scalarWord1;

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandWord, mcuxClCss_Prng_GetRandomWord(&scalarWord1));
    if (MCUXCLCSS_STATUS_OK != ret_Prng_GetRandWord)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_INTSTATUS_RNG_ERROR);
    }
    while (0u == scalarWord0)
    {
        scalarBitIndex -= 32u;
        scalarWord0 = pScalar[scalarBitIndex / 32u];
    }
    scalarBitIndex = (scalarBitIndex | 31u) - __CLZ(scalarWord0);
    scalarWord0 ^= scalarWord1;

    MCUXCLPKC_FP_CALC_OP1_NEG(ECC_ZA, ECC_P);

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ, ECC_ZA, ECC_Z);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, ECC_X0, ECC_Y0);
    pOperands[ECC_VZ2] = pOperands[ECC_ZA];
    pOperands[ECC_VT]  = pOperands[ECC_T3];
    MCUXCLECC_FP_CALCFUP_ONE_DOUBLE();

    MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1,
                               mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1,
                               mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2);

    MCUX_CSSL_FP_LOOP_DECL(MainLoop);
    MCUX_CSSL_FP_LOOP_DECL(RandomizeInMainLoop);
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_LOOP_ITERATIONS(MainLoop, scalarBitIndex),
        MCUX_CSSL_FP_LOOP_ITERATIONS(RandomizeInMainLoop, scalarBitIndex/32u) );

    pOperands[ECC_VT] = 0x01u;

    while (0u != scalarBitIndex)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(MainLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

        scalarBitIndex -= 1u;
        uint32_t bitOffset = scalarBitIndex & 0x1Fu;
        if (0x1Fu == bitOffset)
        {
            MCUX_CSSL_FP_LOOP_ITERATION(RandomizeInMainLoop,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ReRandomizeUPTRT),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord));

            MCUXCLPKC_WAITFORFINISH();
            MCUX_CSSL_FP_FUNCTION_CALL(retReRandomUptrt,
                                      mcuxClPkc_ReRandomizeUPTRT(&pOperands[ECC_X0],
                                                                (uint16_t) operandSize,
                                                                (ECC_Y1 - ECC_X0 + 1u)) );
            if (MCUXCLPKC_STATUS_OK != retReRandomUptrt)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_INTSTATUS_RNG_ERROR);
            }

            MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom1, mcuxClCss_Prng_GetRandom(pZA, operandSize));
            if (MCUXCLCSS_STATUS_OK != ret_Prng_GetRandom1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_INTSTATUS_RNG_ERROR);
            }

            MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1,
                                mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN);

            MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_innerloop, mcuxClCss_Prng_GetRandomWord(&scalarWord1));
            if (MCUXCLCSS_STATUS_OK != ret_PRNG_innerloop)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_INTSTATUS_RNG_ERROR);
            }
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
            scalarWord0 = pScalar[scalarBitIndex / 32u] ^ scalarWord1;
        }

        uint32_t offsetsP0;
        uint32_t offsetsP1;
        uint32_t randomMask;

        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_loop, mcuxClCss_Prng_GetRandomWord(&randomMask));
        if (MCUXCLCSS_STATUS_OK != ret_PRNG_loop)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_INTSTATUS_RNG_ERROR);
        }

        MCUXCLECC_SECUREPOINTSELECT(offsetsP0, offsetsP1, pOperands,
                                   scalarWord0, scalarWord1, randomMask, bitOffset);

        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, offsetsP0);
        MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, offsetsP1);

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_CoZPointAddSub, mcuxClEcc_Fup_CoZPointAddSub_LEN);
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_CoZPointAddSub, mcuxClEcc_Fup_CoZPointAddSub_LEN1);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_OK);
}
