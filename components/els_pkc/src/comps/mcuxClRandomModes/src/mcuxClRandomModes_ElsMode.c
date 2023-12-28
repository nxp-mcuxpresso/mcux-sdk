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

/** @file  mcuxClRandomModes_ElsMode.c
 *  @brief Implementation of the Random component which provides APIs for
 *  handling of random number generators. This file implements the functions
 *  declared in mcuxClRandom.h. */

#include <mcuxClToolchain.h>
#include <mcuxClSession.h>
#include <mcuxClEls.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_ElsMode_init)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_init(
    mcuxClSession_Handle_t pSession
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_ElsMode_reseed)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_reseed(
    mcuxClSession_Handle_t pSession
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_ElsMode_selftest)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_selftest(
    mcuxClSession_Handle_t pSession,
    mcuxClRandom_Mode_t mode
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_ElsMode_generate)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_generate(
    mcuxClSession_Handle_t pSession,
    uint8_t *             pOut,
    uint32_t              outLength
);

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_ElsMode_init)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_init(
    mcuxClSession_Handle_t pSession UNUSED_PARAM
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_ElsMode_init);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_init, MCUXCLRANDOM_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_ElsMode_reseed)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_reseed(
    mcuxClSession_Handle_t pSession UNUSED_PARAM
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_ElsMode_reseed);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_reseed, MCUXCLRANDOM_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_ElsMode_selftest)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_selftest(
    mcuxClSession_Handle_t pSession UNUSED_PARAM,
    mcuxClRandom_Mode_t mode
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_ElsMode_selftest);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_selftest, MCUXCLRANDOM_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_ElsMode_generate)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_ElsMode_generate(
    mcuxClSession_Handle_t pSession UNUSED_PARAM,
    uint8_t *             pOut,
    uint32_t              outLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_ElsMode_generate);

    /**
     * ELS DRBG output size must be a multiple of 4.
     * We first request as much as possible directly, and then use a small buffer
     * to copy up to 3 remaining bytes.
     */

    /**
     * Note: writing to pOut could be unaligned.
     * This could be improved by: - requesting a single word
     *                            - copying as many bytes as needed to achieve alignment
     *                            - requesting the following words to aligned addresses
     *                            - possibly requesting another single word to fill the remaining bytes
     */

    uint32_t requestSizeMin = MCUXCLELS_RNG_DRBG_TEST_EXTRACT_OUTPUT_MIN_SIZE;
    uint32_t requestSizeRemainingBytes = outLength % requestSizeMin;
    uint32_t requestSizeFullWordsBytes = outLength - requestSizeRemainingBytes;

    /* Request as many random bytes as possible with full word size. */
    if (requestSizeFullWordsBytes > 0u)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_GetRandom1, mcuxClEls_Rng_DrbgRequest_Async(pOut, requestSizeFullWordsBytes));
        if (MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_DRBG_GetRandom1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async));
        }
        else if(MCUXCLELS_STATUS_OK_WAIT != ret_DRBG_GetRandom1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_Wait1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
        if(MCUXCLELS_LEVEL1_ERROR(ret_DRBG_Wait1))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        }
        else if (MCUXCLELS_STATUS_OK != ret_DRBG_Wait1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }
    }

    /* If requested size is not a multiple of 4, request one (additional) word and use it only partially. */
    if (requestSizeRemainingBytes > 0u)
    {
        uint8_t requestRemainingBuffer[MCUXCLELS_RNG_DRBG_TEST_EXTRACT_OUTPUT_MIN_SIZE] = {0u};
        
        MCUX_CSSL_ANALYSIS_START_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
        MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_GetRandom2, mcuxClEls_Rng_DrbgRequest_Async(requestRemainingBuffer,
                                                                                     requestSizeMin));
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()   
        if (MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_DRBG_GetRandom2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_ERROR,
                2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        }
        else if (MCUXCLELS_STATUS_OK_WAIT != ret_DRBG_GetRandom2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_Wait2, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
        if(MCUXCLELS_LEVEL1_ERROR(ret_DRBG_Wait2))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_ERROR,
                2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        }
        else if (MCUXCLELS_STATUS_OK != ret_DRBG_Wait2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Copy the remaining bytes from the buffer to output. */
        for(uint32_t i = 0u; i < requestSizeRemainingBytes; i++)
        {
            pOut[requestSizeFullWordsBytes + i] = requestRemainingBuffer[i];
        }

    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_ElsMode_generate, MCUXCLRANDOM_STATUS_OK,
            MCUX_CSSL_FP_CONDITIONAL((requestSizeFullWordsBytes > 0u),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation)),
            MCUX_CSSL_FP_CONDITIONAL((requestSizeRemainingBytes > 0u),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation)));
}


static const mcuxClRandom_OperationModeDescriptor_t mcuxClRandomModes_OperationModeDescriptor_ELS_Drbg = {
    .initFunction                    = mcuxClRandomModes_ElsMode_init,
    .reseedFunction                  = mcuxClRandomModes_ElsMode_reseed,
    .generateFunction                = mcuxClRandomModes_ElsMode_generate,
    .selftestFunction                = mcuxClRandomModes_ElsMode_selftest,
    .protectionTokenInitFunction     = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_ElsMode_init),
    .protectionTokenReseedFunction   = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_ElsMode_reseed),
    .protectionTokenGenerateFunction = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_ElsMode_generate),
    .protectionTokenSelftestFunction = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_ElsMode_selftest),
    .operationMode                   = MCUXCLRANDOMMODES_ELSMODE
};


const mcuxClRandom_ModeDescriptor_t mcuxClRandomModes_mdELS_Drbg = {
    .pOperationMode   = &mcuxClRandomModes_OperationModeDescriptor_ELS_Drbg,
    .pDrbgMode        = NULL,
    .contextSize      = 0u,
    .auxParam         = 0u,
    .securityStrength = 128u
};
