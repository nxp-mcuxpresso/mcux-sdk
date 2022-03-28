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

/** @file  mcuxClEcc_Internal_KeyGen.c
 *  @brief mcuxClEcc: implementation of ECC internal key generation functions
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClCss_Rng.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Int_CoreKeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_CoreKeyGen(mcuxClSession_Handle_t pSession,
                                                                      uint32_t byteLenN)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Int_CoreKeyGen,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST );

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    const uint32_t mcLen_opLen = MCUXCLPKC_PS1_GETLENGTH_REG();
    const uint32_t opLen = MCUXCLPKC_PS1_UNPACK_OPLEN(mcLen_opLen);

    const uint32_t *ptr32N = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_N]);
    const uint32_t wordNumN = (byteLenN + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t));
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint32_t nMSWord = ptr32N[wordNumN - 1u];
    uint32_t nMSWord_LeadZeros = __CLZ(nMSWord);
    uint32_t bitLenN65 = (wordNumN * (sizeof(uint32_t)) * 8u) - nMSWord_LeadZeros + 65u;
    uint32_t pkcByteLenN65 = (bitLenN65 + (MCUXCLPKC_WORDSIZE * 8u) - 1u) / (MCUXCLPKC_WORDSIZE * 8u) * MCUXCLPKC_WORDSIZE;

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);

    MCUXCLPKC_PS2_SETLENGTH(0u, pkcByteLenN65);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_S2, 0u);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_S3, 0u);

    uint32_t *ptr32S0 = (uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);

    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng1, mcuxClCss_Prng_GetRandom((uint8_t*)&ptr32S0[0], (2U * sizeof(uint32_t))));
    if (MCUXCLCSS_STATUS_OK != ret_Prng1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_INTSTATUS_RNG_ERROR);
    }
    ptr32S0[0] |= 0x00000001u;
    ptr32S0[1] |= 0x80000000u;

    uint8_t *ptrS2 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_GetRandom_c, mcuxClCss_Rng_DrbgRequest_Async(ptrS2, (wordNumN * (sizeof(uint32_t))) + 8u));
    if (MCUXCLCSS_STATUS_OK_WAIT != ret_DRBG_GetRandom_c)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_INTSTATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Rng_DrbgRequest_Async));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_Wait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
    if (MCUXCLCSS_STATUS_OK != ret_DRBG_Wait)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_INTSTATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Rng_DrbgRequest_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
    }

    uint8_t *ptrS3 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom_r, mcuxClCss_Prng_GetRandom(ptrS3, (wordNumN * (sizeof(uint32_t))) + 8u));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom_r)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_INTSTATUS_RNG_ERROR);
    }

    pOperands[ECC_VT] = (uint16_t) nMSWord_LeadZeros;
    const uint32_t constants_0000_0001 = 1u;
    MCUXCLECC_STORE_2OFFSETS(pOperands, ECC_VT2, ECC_VT3, constants_0000_0001);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Int_CoreKeyGen_Steps34,
                        mcuxClEcc_Int_CoreKeyGen_Steps34_LEN);

    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_ZA, ECC_N, ECC_S1);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(pkcByteLenN65, opLen);

    MCUXCLMATH_FP_REDUCEMODEVEN(ECC_S1, ECC_S2, ECC_Z, ECC_XA, ECC_S1, ECC_YA, ECC_ZA);

    MCUXCLMATH_FP_REDUCEMODEVEN(ECC_S2, ECC_S3, ECC_Z, ECC_XA, ECC_S2, ECC_YA, ECC_ZA);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH_REG(mcLen_opLen);
    MCUXCLPKC_PS2_SETLENGTH(0u, opLen * 2u);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Int_CoreKeyGen_Steps56,
                        mcuxClEcc_Int_CoreKeyGen_Steps56_LEN);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH(opLen * 2u, opLen);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Int_CoreKeyGen_Steps78,
                        mcuxClEcc_Int_CoreKeyGen_Steps78_LEN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_STATUS_OK,

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Rng_DrbgRequest_Async),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ReduceModEven),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ReduceModEven),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}
