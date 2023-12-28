/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder.c
 * @brief Weierstrass curve internal secure point multiplication
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Internal_Random.h>
#include <internal/mcuxClEcc_Internal_SecurePointSelect.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder_FUP.h>
#include <internal/mcuxClEcc_Weier_Internal_PointArithmetic_FUP.h>


/** This function implements secure point scalar multiplication, R = scalar * P, based on Co-Z Montgomery ladder.
 *
 * Inputs:
 *   pSession: pointer to mcuxClSession_Descriptor.
 *   iScalar: index of PKC buffer storing the scalar, which is non-zero and in little-endian;
 *   scalarBitLength: bit length of scalar.
 *
 * Inputs in pOperands[] and PKC workarea:
 *   P in (X0,Y0, Z) Jacobian.
 *
 * Prerequisites:
 *   buffer VA contains curve coefficient a, Montgomery representation;
 *   ps1Len = (operandSize, operandSize);
 *   curve order p in P, NDash of p in PFULL, shifted modulus of p in PS.
 *
 * Result in PKC workarea:
 *   buffers (X0,Y0, Z) contain result R, Jacobian.
 *
 * Other modifications:
 *   buffers T0, T1, T2 and T3 are modified (as temp);
 *   buffers ZA, X1 and Y1 are modified;
 *   offsets pOperands[VX0/VY0/VZ0/VZ/VX1/VY1/VX2/VY2/VZ2/VT] are modified;
 *   pOperands[X0/Y0/X1/Y1] and location of corresponding buffers are randomized.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_SecurePointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SecurePointMult(mcuxClSession_Handle_t pSession,
                                                                       uint8_t iScalar,
                                                                       uint32_t scalarBitLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_SecurePointMult,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,
        MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("MISRA Ex. 9 to Rule 11.3 - PKC word is CPU word aligned.");
    const uint32_t *pScalar = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[iScalar]);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();

    /**
     * Step 1: Randomize input point P coordinates (X0, Y0, Z)
     */

    /* Generate a randomized relative Z-coordinate in ZA */
    uint8_t *pZA = MCUXCLPKC_OFFSET2PTR(pOperands[WEIER_ZA]);
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom0, mcuxClRandom_ncGenerate(pSession, pZA, operandSize));
    if (MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom0)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }

    /* Reduce ZA modulo p, update the Z-coordinate and update the coordinates of P0 to the new Z-coordinate */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1,
                        mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1      /* PrepareZ */
                        + mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2);  /* UpdateZ and P0 */


    /**
     * Step 2: Skip leading scalar zeros and read and XOR-mask first non-zero scalar word
     */

    /* Initialize scalar word shares variables and generate XOR-mask for the first non-zero scalar word */
    uint32_t scalarBitIndex = scalarBitLength - 1u;
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    uint32_t scalarWord0 = pScalar[scalarBitIndex / 32u];
    uint32_t scalarWord1;

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandWord, mcuxClRandom_ncGenerate(pSession, (uint8_t*)&scalarWord1, sizeof(uint32_t)));
    if (MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandWord)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }

    /* Scan scalar and skip leading zero bits. */
    while (0u == scalarWord0)
    {
        scalarBitIndex -= 32u;
        scalarWord0 = pScalar[scalarBitIndex / 32u];
    }
    scalarBitIndex = (scalarBitIndex | 31u) - mcuxClMath_CountLeadingZerosWord(scalarWord0);  /* bit position of most significant non-zero bit */
    scalarWord0 ^= scalarWord1;


    /**
     * Step 3: Prepare accumulated ladder points R0 (X0, Y0, Z) and R1 (X1, Y1, Z) and ensure that their
     *         X- and Y-coordinates are in range [0,p-1], a prerequisite for each ladder step.
     */

    /* Initialize z' = 1 in MR. */
    MCUXCLPKC_FP_CALC_OP1_NEG(WEIER_ZA, ECC_P);

    /* Calculate R1 = P + P = 2*R0                               */
    /* Input:  R0 in (X0,Y0, ZA=1) relative-Z (w.r.t. ZRef in Z) */
    /* Output: R1 in (X1,Y1, ZA)   relative-Z                    */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X1, WEIER_Y1);  /* R1 */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VZ0, WEIER_VZ, WEIER_ZA, WEIER_Z);    /* R1.z and ZRef */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX2, WEIER_VY2, WEIER_X0, WEIER_Y0);  /* R0 */
    pOperands[WEIER_VZ2] = pOperands[WEIER_ZA];  /* R0.z */
    pOperands[WEIER_VT]  = pOperands[ECC_T3];    /* 5th temp */
    MCUXCLECC_FP_CALCFUP_ONE_DOUBLE();

    /* Ensure that X1 and Y1 are in range [0,p-1] as a prerequisite for the scalar multiplication loop.
     * Also ensure ZA < p as a prerequisite for the upcoming coordinate update*/
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP, mcuxClEcc_FUP_Weier_SecurePointMult_Reduce_X1_Y1_ZA_ModP_LEN);

    /* Update z = z * z', so R1: (X1,Y1, ZA) relative-z -> (X1,Y1, Z) Jacobian.
     * Update Jacobian coordinates in MR of R0 (X0,Y0, Z).
     *
     * NOTE: Since ZA < p before the FUP program, the same holds for X0 and Y0 after the FUP program
     *       which is a prerequisite for the scalar multiplication loop */
    MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1,
                               mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1,   /* Skip the first part (PrepareZA) */
                               mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2);  /* Only UpdateZ and P0 */


    /**
     * Step 4: Execute Montgomery ladder to process the remaining scalar words and compute the result
     *
     * NOTES:
     *   - It is ensured that before and after every ladder step the X- and Y-coordinates of the accumulated points are in range [0,p-1].
     *     This shall help to avoid side-channel leakage.
     *   - For every new scalar word, the coordinates of the accumulated points are re-randomized with a fresh random Z-coordinate and
     *     also buffers are shuffled
     */

    /* FP balance here, to avoid keeping another copy of scalarBitIndex. */
    MCUX_CSSL_FP_LOOP_DECL(MainLoop);
    MCUX_CSSL_FP_LOOP_DECL(RandomizeInMainLoop);  /* This needs to be declared outside the loop. */
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_LOOP_ITERATIONS(MainLoop, scalarBitIndex),
        MCUX_CSSL_FP_LOOP_ITERATIONS(RandomizeInMainLoop, scalarBitIndex/32u) );

    /* The remaining iteration(s) of Montgomery ladder. */
    while (0u != scalarBitIndex)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(MainLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

        scalarBitIndex -= 1u;
        uint32_t bitOffset = scalarBitIndex & 0x1Fu;
        if (0x1Fu == bitOffset)
        {
            MCUX_CSSL_FP_LOOP_ITERATION(RandomizeInMainLoop,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ReRandomizeUPTRT),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate) );

            /* Randomize offsets UPTRT XA/YA/ZA/Z/X0/Y0/X1/Y1. */
            /* (pkcwa order is changed accordingly)            */
            MCUXCLPKC_WAITFORFINISH();
            MCUX_CSSL_FP_FUNCTION_CALL(retReRandomUptrt,
                                      mcuxClPkc_ReRandomizeUPTRT(pSession,
                                                                &pOperands[WEIER_XA],
                                                                (uint16_t) operandSize,
                                                                (WEIER_Y1 - WEIER_XA + 1u)) );
            if (MCUXCLPKC_STATUS_OK != retReRandomUptrt)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_RNG_ERROR);
            }

            /* After rerandomization, pointer pZA (used in mcuxClRandom_ncGenerate call)         */
            /* and pOperands[WEIER_VZ] (used by double-and-add FUP program) need to be updated. */
            pOperands[WEIER_VZ]  = pOperands[WEIER_Z];
            pZA = MCUXCLPKC_OFFSET2PTR(pOperands[WEIER_ZA]);
            /* Rerandomize R0 (X0,Y0, Z) and R1 (X1,Y1, Z) and ensure that the X- and Y-coordinates are in range [0,p-1]. */
            MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom1, mcuxClRandom_ncGenerate(pSession, pZA, operandSize));
            if (MCUXCLRANDOM_STATUS_OK != ret_Prng_GetRandom1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_RNG_ERROR);
            }

            MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1,
                                mcuxClEcc_FUP_Weier_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN);

            /* Read next CPU word of scalar. */
            MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_innerloop, mcuxClRandom_ncGenerate(pSession, (uint8_t*)&scalarWord1, sizeof(uint32_t)));
            if (MCUXCLRANDOM_STATUS_OK != ret_PRNG_innerloop)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_RNG_ERROR);
            }

            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
            scalarWord0 = pScalar[scalarBitIndex / 32u] ^ scalarWord1;
        }

        uint32_t offsetsP0;
        uint32_t offsetsP1;
        uint32_t randomMask;

        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_loop, mcuxClRandom_ncGenerate(pSession, (uint8_t*)&randomMask, sizeof(uint32_t)));
        if (MCUXCLRANDOM_STATUS_OK != ret_PRNG_loop)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_RNG_ERROR);
        }
        /* When bit of scalar = 0, the macro returns:                    */
        /*   offsetsP0 = pOperands[WEIER_Y0] || pOperands[WEIER_X0], and */
        /*   offsetsP1 = pOperands[WEIER_Y1] || pOperands[WEIER_X1];     */
        /* when bit = 1,                                                 */
        /*   offsetsP0 = pOperands[WEIER_Y1] || pOperands[WEIER_X1], and */
        /*   offsetsP1 = pOperands[WEIER_Y0] || pOperands[WEIER_X0].     */
        MCUXCLECC_SECUREPOINTSELECT(offsetsP0, offsetsP1, pOperands, WEIER_X0,
                                   scalarWord0, scalarWord1, randomMask, bitOffset);

        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_STORE_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, offsetsP0);
        MCUXCLECC_STORE_2OFFSETS(pOperands32, WEIER_VX1, WEIER_VY1, offsetsP1);

        /* Perform double-and-add step.
         *
         * NOTE: Since X0, Y0, X1, Y1 < p before the double-and-add step, the same holds for those coordinates afterwards. */
        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_FUP_Weier_CoZPointAddSub,
                                   mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN1,
                                   mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN2);
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_CoZPointAddSub, mcuxClEcc_FUP_Weier_CoZPointAddSub_LEN);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SecurePointMult, MCUXCLECC_STATUS_OK);
}
