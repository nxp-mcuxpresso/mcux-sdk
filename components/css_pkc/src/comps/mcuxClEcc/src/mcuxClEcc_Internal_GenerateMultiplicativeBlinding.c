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

/**
 * @file  mcuxClEcc_Internal_GenerateMultiplicativeBlinding.c
 * @brief mcuxClEcc: implementation of GenerateMultiplicativeBlinding functions
 */

#include <stdint.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCss.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClEcc_Mont_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_GenerateMultiplicativeBlinding)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_GenerateMultiplicativeBlinding(mcuxClSession_Handle_t pSession)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_GenerateMultiplicativeBlinding);

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);

    const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();

    uint8_t *pS0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);

    MCUXCLPKC_WAITFORFINISH();
    volatile uint32_t *p32S0 = (volatile uint32_t *) pS0;

    MCUX_CSSL_FP_FUNCTION_CALL(retGetRandom, mcuxClCss_Prng_GetRandom(pS0, MCUXCLECC_MONT_DH_SCALAR_BLINDING_BYTELEN));
    if (MCUXCLCSS_STATUS_OK != retGetRandom)
    {

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_GenerateMultiplicativeBlinding, MCUXCLECC_STATUS_MONT_RNG_ERROR,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST );
    }

    *p32S0 |= 0x80000001u;

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_S1, ECC_S0, 0u);

    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_S1, ECC_N, ECC_T1);

    MCUXCLPKC_FP_CALC_MC1_MM(ECC_S1, ECC_S3, ECC_T0, ECC_N);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, ECC_S1, ECC_NQSQR, ECC_N);
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_S1, ECC_T0, ECC_N, ECC_N);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_GenerateMultiplicativeBlinding, MCUXCLECC_STATUS_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS
		);
}
