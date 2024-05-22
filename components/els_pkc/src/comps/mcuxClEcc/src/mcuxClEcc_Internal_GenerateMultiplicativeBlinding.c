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
 * @file  mcuxClEcc_Internal_GenerateMultiplicativeBlinding.c
 * @brief mcuxClEcc: implementation of GenerateMultiplicativeBlinding functions
 */


#include <stdint.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxClRandom.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Internal.h>



/**
 * \brief This function securely generates a multiplicative decomposition (sigma, phi)
 * of a secret scalar k with a 32-bit random phi with MSBit and LSBit set to 1 and
 * sigma = phi^(-1) * k mod n.
 *
 * Inputs:
 *   pSession: handle for the current CL session;
 *   scalarIndex: table index of buffer storing the scalar k to be blinded.
 *
 * Prerequisites:
 *  - The decoded secret scalar k is contained in buffer scalarIndex;
 *  - ps1Len = (operandSize, operandSize).
 *
 * Results:
 *  - the 32-bit blinding phi is contained in buffer ECC_S0;
 *  - the blinded scalar sigma is contained in buffer ECC_S1.
 *
 * Other modifications:
 *  - buffers ECC_T0 and ECC_T1 are modified (as temp).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_GenerateMultiplicativeBlinding)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_GenerateMultiplicativeBlinding(mcuxClSession_Handle_t pSession, uint8_t scalarIndex)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_GenerateMultiplicativeBlinding);

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);

    const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();

    uint8_t *pS0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);

    /* Generate S0 = phi = a 32-bit non-zero random, with PRNG. */
    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("PKC buffer is CPU word aligned.")
    volatile uint32_t *p32S0 = (volatile uint32_t *) pS0;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

    MCUX_CSSL_FP_FUNCTION_CALL(retGetRandom, mcuxClRandom_ncGenerate(pSession, pS0, MCUXCLECC_SCALARBLINDING_BYTELEN));
    if (MCUXCLRANDOM_STATUS_OK != retGetRandom)
    {
        /* if it fails, error code is related to RNG issue, so translated to generic return code */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_GenerateMultiplicativeBlinding, MCUXCLECC_STATUS_RNG_ERROR,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST);
    }

    /* Set MSBit and LSBit of phi */
    *p32S0 |= 0x80000001u;

    /* Copy S0 = phi to S1 before calling ModInv (which will destroy input). */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_S1, ECC_S0, 0u);

    /* Calculate T0 = phi^(-1) mod n. */
    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_S1, ECC_N, ECC_T1);

    /* Calculate S1 = sigma = phi^(-1) * k mod n, in the range [1, n-1]. */
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_S1, scalarIndex, ECC_T0, ECC_N);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, ECC_S1, ECC_NQSQR, ECC_N);  /* since NQSQR < n, the result is in [1, 2n-2]. */
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_S1, ECC_T0, ECC_N, ECC_N);      /* sigma in range [1, n-1]. */

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_GenerateMultiplicativeBlinding, MCUXCLECC_STATUS_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
}
