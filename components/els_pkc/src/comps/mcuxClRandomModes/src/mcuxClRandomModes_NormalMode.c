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

#include <mcuxClToolchain.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <mcuxCsslAnalysis.h>

#include <mcuxClRandomModes_MemoryConsumption.h>
#include <mcuxClRandomModes_Functions_TestMode.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#include <internal/mcuxClRandomModes_Private_CtrDrbg.h>
#include <internal/mcuxClRandomModes_Private_NormalMode.h>
#include <internal/mcuxClTrng_Internal.h>

#ifdef MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClRandom_OperationModeDescriptor_t mcuxClRandomModes_OperationModeDescriptor_NormalMode_PrDisabled = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    .initFunction                    = mcuxClRandomModes_NormalMode_initFunction,
    .reseedFunction                  = mcuxClRandomModes_NormalMode_reseedFunction,
    .generateFunction                = mcuxClRandomModes_NormalMode_generateFunction_PrDisabled,
    .selftestFunction                = mcuxClRandomModes_NormalMode_selftestFunction,
    .protectionTokenInitFunction     = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_NormalMode_initFunction,
    .protectionTokenReseedFunction   = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_NormalMode_reseedFunction,
    .protectionTokenGenerateFunction = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_NormalMode_generateFunction_PrDisabled,
    .protectionTokenSelftestFunction = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_NormalMode_selftestFunction,
    .operationMode                   = MCUXCLRANDOMMODES_NORMALMODE,
};
#endif /* MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED */


/**
 * \brief This function instantiates a DRBG in NORMAL_MODE following the lines of the function Instantiate_function specified in NIST SP800-90A
 *
 * This function instantiates a DRBG in NORMAL_MODE following the lines of the function Instantiate_function specified in NIST SP800-90A.
 * The function obtains entropy input for the DRBG seed from the TRNG.
 *
 * \param  pSession[in]          Handle for the current CL session
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the DRBG instantiation finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR           if a memory allocation error or non-critical TRNG error occured
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the DRBG instantiation failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_NormalMode_initFunction, mcuxClRandom_initFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_initFunction(mcuxClSession_Handle_t pSession)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_NormalMode_initFunction);

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    mcuxClRandomModes_Context_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_Generic_t *) pSession->randomCfg.ctx;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    mcuxClRandom_Mode_t sessionMode = pSession->randomCfg.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) sessionMode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    /* Initialize buffer in CPU workarea for the entropy input to derive the DRBG seed */
    uint32_t *pEntropyInput = mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->initSeedSize));
    if(NULL == pEntropyInput)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_ERROR);
    }

    /* Call TRNG initialization function to ensure it's properly configured for upcoming TRNG accesses */
    MCUX_CSSL_FP_FUNCTION_CALL(result_trngInit, mcuxClTrng_Init());
    if (MCUXCLTRNG_STATUS_OK != result_trngInit)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Generate entropy input using the TRNG */
    MCUX_CSSL_FP_FUNCTION_CALL(result_trng,
      mcuxClTrng_getEntropyInput(pSession, pEntropyInput, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->initSeedSize)*sizeof(uint32_t))
      );
    if(MCUXCLTRNG_STATUS_ERROR == result_trng)
    {
        /* Free workarea (pEntropyInput) */
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->initSeedSize));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_Init),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_getEntropyInput));
    }
    else if (MCUXCLTRNG_STATUS_OK != result_trng)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    /* Derive the initial DRBG state from the generated entropy input  */
    MCUX_CSSL_FP_FUNCTION_CALL(result_instantiate, pDrbgMode->pDrbgAlgorithms->instantiateAlgorithm(pSession, (uint8_t *) pEntropyInput));
    if(MCUXCLRANDOM_STATUS_ERROR == result_instantiate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_Init),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_getEntropyInput),
            pDrbgMode->pDrbgAlgorithms->protectionTokenInstantiateAlgorithm);
    }
    else if (MCUXCLRANDOM_STATUS_OK != result_instantiate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Initialize the reseedSeedOffset field of the context */
        pRngCtxGeneric->reseedSeedOffset = 0u;

        /* Free workarea (pEntropyInput) */
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->initSeedSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_initFunction, MCUXCLRANDOM_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_Init),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_getEntropyInput),
            pDrbgMode->pDrbgAlgorithms->protectionTokenInstantiateAlgorithm);
    }
}


/**
 * \brief This function reseeds a DRBG in NORMAL_MODE following the lines of the function Reseed_function specified in NIST SP800-90A
 *
 * This function reseed a DRBG in NORMAL_MODE following the lines of the function Reseed_function specified in NIST SP800-90A.
 * The function obtains entropy input for the DRBG seed from the TRNG.
 *
 * \param  pSession[in]          Handle for the current CL session
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the DRBG reseeding finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR           if a memory allocation error or non-critical TRNG error occured
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the DRBG reseeding failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_NormalMode_reseedFunction, mcuxClRandom_reseedFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_reseedFunction(mcuxClSession_Handle_t pSession)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_NormalMode_reseedFunction);

    mcuxClRandom_Mode_t sessionMode = pSession->randomCfg.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) sessionMode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    /* Initialize buffer in CPU workarea for the entropy input to derive the DRBG seed */
    uint32_t *pEntropyInput = mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->reseedSeedSize));
    if(NULL == pEntropyInput)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_reseedFunction, MCUXCLRANDOM_STATUS_ERROR);
    }

    /* Generate entropy input using the TRNG */
    MCUX_CSSL_FP_FUNCTION_CALL(result_trng,
        mcuxClTrng_getEntropyInput(pSession, pEntropyInput, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->reseedSeedSize) * sizeof(uint32_t))
        );
    if(MCUXCLTRNG_STATUS_ERROR == result_trng)
    {
        /* Free workarea (pEntropyInput) */
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->reseedSeedSize));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_reseedFunction, MCUXCLRANDOM_STATUS_ERROR);
    }
    else if (MCUXCLTRNG_STATUS_OK != result_trng)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_reseedFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    /* Derive the initial DRBG state from the generated entropy input  */
    MCUX_CSSL_FP_FUNCTION_CALL(result_reseed, pDrbgMode->pDrbgAlgorithms->reseedAlgorithm(pSession,(uint8_t *) pEntropyInput));
    if(MCUXCLRANDOM_STATUS_ERROR == result_reseed)
    {
        /* Free workarea (pEntropyInput) */
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->reseedSeedSize));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_reseedFunction, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_getEntropyInput),
            pDrbgMode->pDrbgAlgorithms->protectionTokenReseedAlgorithm);
    }
    else if (MCUXCLRANDOM_STATUS_OK != result_reseed)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_reseedFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Free workarea (pEntropyInput) */
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pDrbgMode->pDrbgVariant->reseedSeedSize));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_reseedFunction, MCUXCLRANDOM_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClTrng_getEntropyInput),
            pDrbgMode->pDrbgAlgorithms->protectionTokenReseedAlgorithm);
    }
}


#ifdef MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED
/**
 * \brief This function generates random numbers from a DRBG in NORMAL_MODE following the lines of the function Generate_function specified in NIST SP800-90A
 * and reseeds according to the DRG.3 security level.
 *
 * This function generates random numbers from a DRBG in NORMAL_MODE following the lines of the function Generate_function specified in NIST SP800-90A.
 * If reseedCounter overflowed, the DRBG will be reseeded before the randomness generation.
 * If so, the function obtains entropy input for the DRBG seed from the TRNG.
 *
 * \param  pSession[in]         Handle for the current CL session
 * \param  pOut[out]            Output buffer to which the generated randomness will be written
 * \param  outLength            Number of requested random bytes
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the random number generation finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR           if the DRBG could not be reseeded or if the generation failed because a non-critical HW error occurred
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the random number generation failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, mcuxClRandom_generateFunction_t)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_generateFunction_PrDisabled(mcuxClSession_Handle_t pSession, uint8_t *pOut, uint32_t outLength)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_Context_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_Generic_t *) pSession->randomCfg.ctx;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    mcuxClRandom_Mode_t pMode = pSession->randomCfg.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) pMode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled,
          MCUX_CSSL_FP_CONDITIONAL((pRngCtxGeneric->reseedCounter >= pDrbgMode->pDrbgVariant->reseedInterval),
                 pMode->pOperationMode->protectionTokenReseedFunction));


    /* Reseed the DRBG state if the reseed counter overflowed */
    if (pRngCtxGeneric->reseedCounter >= pDrbgMode->pDrbgVariant->reseedInterval)

    {
        MCUX_CSSL_FP_FUNCTION_CALL(result_reseed, pMode->pOperationMode->reseedFunction(pSession));
        if(MCUXCLRANDOM_STATUS_ERROR == result_reseed)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, MCUXCLRANDOM_STATUS_ERROR);
        }
        else if (MCUXCLRANDOM_STATUS_OK != result_reseed)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }
    }

    /* Generate random bytes */
    MCUX_CSSL_FP_FUNCTION_CALL(result_generate, pDrbgMode->pDrbgAlgorithms->generateAlgorithm(pSession, pOut, outLength));
    if(MCUXCLRANDOM_STATUS_ERROR == result_generate)
    {
         MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, MCUXCLRANDOM_STATUS_ERROR,
            pDrbgMode->pDrbgAlgorithms->protectionTokenGenerateAlgorithm);
    }
    else if (MCUXCLRANDOM_STATUS_OK != result_generate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, MCUXCLRANDOM_STATUS_OK,
            pDrbgMode->pDrbgAlgorithms->protectionTokenGenerateAlgorithm);
    }
}
#endif /* MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED */



/**
 * \brief This function performs a selftest of a DRBG in NORMAL_MODE
 *
 * The specific test pattern depends on the drbgMode.
 *
 * @param  pSession[in]    Handle for the current CL session
 * @param  mode[in]        Mode of operation for random data generator.
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the selftest executed finished successfully
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the selftest failed
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_NormalMode_selftestFunction, mcuxClRandom_selftestFunction_t)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_selftestFunction(mcuxClSession_Handle_t pSession, mcuxClRandom_Mode_t mode)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_NormalMode_selftestFunction);
    /* Back up Random configuration of current session */
    mcuxClRandom_Mode_t modeBackup = pSession->randomCfg.mode;
    mcuxClRandom_Context_t ctxBackup = pSession->randomCfg.ctx;

    /* Allocate space for new testMode */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Return pointer is 32-bit aligned and satisfies the requirement of mcuxClRandom_ModeDescriptor_t")
    mcuxClRandom_ModeDescriptor_t *pTestModeDesc = (mcuxClRandom_ModeDescriptor_t *)mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
    if(NULL == pTestModeDesc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_selftestFunction, MCUXCLRANDOM_STATUS_ERROR);
    }

    /* Derive testMode from passed mode */
    MCUX_CSSL_FP_FUNCTION_CALL(result_create, mcuxClRandomModes_createTestFromNormalMode(pTestModeDesc, mode, NULL));
    if (MCUXCLRANDOM_STATUS_OK != result_create)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_selftestFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Allocate space for ctxBuffer according to the contextSize */
    uint32_t *ctxBuffer = mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pTestModeDesc->contextSize));
    if(NULL == ctxBuffer)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_selftestFunction, MCUXCLRANDOM_STATUS_ERROR);
    }
    mcuxClRandom_Context_t pTestCtx = (mcuxClRandom_Context_t) ctxBuffer;

    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) mode->pDrbgMode;

    /* Call function executing the DRBG mode specific selftest algorithm */
    MCUX_CSSL_FP_FUNCTION_CALL(result_selftest, pDrbgMode->pDrbgAlgorithms->selftestAlgorithm(pSession, pTestCtx, pTestModeDesc));
    if(MCUXCLRANDOM_STATUS_OK != result_selftest)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_selftestFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Restore Random configuration of session */
    pSession->randomCfg.mode = modeBackup;
    pSession->randomCfg.ctx = ctxBackup;

    /* Free workarea (pTestModeDesc and ctxBuffer) */
    mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE) + MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(pTestModeDesc->contextSize));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_NormalMode_selftestFunction, MCUXCLRANDOM_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode),
        pDrbgMode->pDrbgAlgorithms->protectionTokenSelftestAlgorithm);
}


/**
 * \brief This function performs a comparison of two arrays
 *
 * @param  wordLength[in]   Length of arrays to compare in word size
 * @param  expected[in]     Input buffer with expected value
 * @param  actual[in]       Input buffer with actual value, to be compared with expected value
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the arrays are equal
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the arrays are not equal
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_selftest_VerifyArrays)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_selftest_VerifyArrays(uint32_t wordLength, const uint32_t * const expected, uint32_t *actual)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_selftest_VerifyArrays);

    for (uint32_t i = 0u; i < wordLength; i++)
    {
        if (expected[i] != actual[i])
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_selftest_VerifyArrays, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_selftest_VerifyArrays, MCUXCLRANDOM_STATUS_OK);
}
