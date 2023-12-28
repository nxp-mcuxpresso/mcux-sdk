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
 * @file mcuxClEls_Rng.c
 * @brief ELS implementation for  random number generation.
 * This file implements the functions declared in mcuxClEls_Rng.h.
 */

#include <platform_specific_headers.h>
#include <stdbool.h>
#include <mcuxClEls_Rng.h>              // Implement mcuxClEls interface "Rng"
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClToolchain.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>
#include <internal/mcuxClMemory_Copy_Internal.h>

#define RANDOM_BIT_ARRAY_SIZE 4U

#ifdef MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING
uint32_t mcuxClEls_rng_drbg_block_counter = 0u;
#endif /* MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING */

// Command name change -- should move to top level platform header
#ifndef ID_CFG_ELS_CMD_RND_REQ
#define ID_CFG_ELS_CMD_RND_REQ ID_CFG_ELS_CMD_DRBG_REQ
#endif

// Utility code of mcuxClEls implementation for PRNG access

/**
 * Gets a pseudo-random 32-bit integer from the ELS PRNG.
 */
static inline uint32_t els_getPRNGWord(
    void)
{
    return MCUXCLELS_SFR_READ(ELS_PRNG_DATOUT);
}

// Implementation of mcuxClEls interface "Rng"

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_DrbgRequest_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_DrbgRequest_Async(
    uint8_t * pOutput,
    size_t outputLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_DrbgRequest_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Rng_DrbgRequest_Async, (MCUXCLELS_RNG_DRBG_TEST_EXTRACT_OUTPUT_MIN_SIZE > outputLength) || 
                                                                         (MCUXCLELS_RNG_DRBG_TEST_EXTRACT_OUTPUT_MAX_SIZE < outputLength) ||
                                                                         (0U != outputLength % 4U));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgRequest_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

#ifdef MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING
    /* Increment drbg_block_counter. If the counter overflowed, the interrupt handler will
     * reseed the DRBG and reset the counter after the upcoming ELS operation. */
    uint32_t counter_increase = MCUXCLELS_RNG_DRBG_DRBGREQUEST_INCREASE(outputLength);
    mcuxClEls_rng_drbg_block_counter += counter_increase;
#endif /* MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING */


    mcuxClEls_setOutput(pOutput, outputLength);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_RND_REQ, 0U, ELS_CMD_LITTLE_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgRequest_Async, MCUXCLELS_STATUS_OK_WAIT);
}

#ifdef MCUXCL_FEATURE_ELS_RND_RAW
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_DrbgRequestRaw_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_DrbgRequestRaw_Async(
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_DrbgRequestRaw_Async);

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgRequestRaw_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setOutput_fixedSize(pOutput);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_RND_REQ, MCUXCLELS_RNG_RND_REQ_RND_RAW, ELS_CMD_LITTLE_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgRequestRaw_Async, MCUXCLELS_STATUS_OK_WAIT);
}
#endif /* MCUXCL_FEATURE_ELS_RND_RAW */

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_DrbgTestInstantiate_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_DrbgTestInstantiate_Async(
    uint8_t const * pEntropy)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_DrbgTestInstantiate_Async);

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestInstantiate_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0_fixedSize(pEntropy);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_DRBG_TEST, MCUXCLELS_RNG_DRBG_TEST_MODE_INSTANTIATE, ELS_CMD_LITTLE_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestInstantiate_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_DrbgTestExtract_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_DrbgTestExtract_Async(
    uint8_t * pOutput,
    size_t outputLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_DrbgTestExtract_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Rng_DrbgTestExtract_Async, (MCUXCLELS_RNG_DRBG_TEST_EXTRACT_OUTPUT_MIN_SIZE > outputLength) || 
                                                                             (MCUXCLELS_RNG_DRBG_TEST_EXTRACT_OUTPUT_MAX_SIZE < outputLength) ||
                                                                             (0U != outputLength % 4U));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestExtract_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setOutput(pOutput, outputLength);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_DRBG_TEST, MCUXCLELS_RNG_DRBG_TEST_MODE_EXTRACT, ELS_CMD_LITTLE_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestExtract_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_DrbgTestAesEcb_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_DrbgTestAesEcb_Async(
    uint8_t const * pDataKey,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_DrbgTestAesEcb_Async);

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestAesEcb_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput1_fixedSize(pDataKey);
    mcuxClEls_setOutput_fixedSize(pOutput);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_DRBG_TEST, MCUXCLELS_RNG_DRBG_TEST_MODE_AES_ECB, ELS_CMD_LITTLE_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestAesEcb_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_DrbgTestAesCtr_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_DrbgTestAesCtr_Async(
    uint8_t const * pData,
    size_t dataLength,
    uint8_t const * pIvKey,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_DrbgTestAesCtr_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Rng_DrbgTestAesCtr_Async, (0U != (dataLength % 16U)) || (0U == dataLength));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestAesCtr_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0(pData, dataLength);
    mcuxClEls_setInput1_fixedSize(pIvKey);
    mcuxClEls_setOutput_fixedSize(pOutput);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_DRBG_TEST, MCUXCLELS_RNG_DRBG_TEST_MODE_AES_CTR, ELS_CMD_LITTLE_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_DrbgTestAesCtr_Async, MCUXCLELS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_Dtrng_ConfigLoad_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_Dtrng_ConfigLoad_Async(
    uint8_t const * pInput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_Dtrng_ConfigLoad_Async);

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_Dtrng_ConfigLoad_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0_fixedSize(pInput);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_DTRNG_CFG_LOAD, 0U, ELS_CMD_LITTLE_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_Dtrng_ConfigLoad_Async, MCUXCLELS_STATUS_OK_WAIT);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Rng_Dtrng_ConfigEvaluate_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Rng_Dtrng_ConfigEvaluate_Async(
    uint8_t const * pInput,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Rng_Dtrng_ConfigEvaluate_Async);

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_Dtrng_ConfigEvaluate_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_setInput0_fixedSize(pInput);
    mcuxClEls_setOutput_fixedSize(pOutput);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_DTRNG_EVAL, 0U, ELS_CMD_LITTLE_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Rng_Dtrng_ConfigEvaluate_Async, MCUXCLELS_STATUS_OK_WAIT);
}

#ifdef MCUXCL_FEATURE_ELS_PRND_INIT
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Prng_Init_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Prng_Init_Async(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Prng_Init_Async);

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Prng_Init_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_RND_REQ, MCUXCLELS_RNG_RND_REQ_PRND_INIT, ELS_CMD_LITTLE_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Prng_Init_Async, MCUXCLELS_STATUS_OK_WAIT);
}
#endif /* MCUXCL_FEATURE_ELS_PRND_INIT */

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Prng_GetRandomWord)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Prng_GetRandomWord(
    uint32_t * pWord)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Prng_GetRandomWord);

    *pWord = els_getPRNGWord();

    /* check if enough entropy is available */
    if (MCUXCLELS_IS_ERROR_BIT_SET(MCUXCLELS_SFR_ERR_STATUS_PRNG_ERR))
    {
        /* clear ELS error flags */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_ResetErrorFlags());  /* always returns MCUXCLELS_STATUS_OK. */

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Prng_GetRandomWord, MCUXCLELS_STATUS_HW_PRNG,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_ResetErrorFlags));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Prng_GetRandomWord, MCUXCLELS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Prng_GetRandom)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Prng_GetRandom(
    uint8_t * pOutput,
    size_t outputLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Prng_GetRandom);

    uint8_t * bytePtr = pOutput;
    uint8_t * const pOutputEnd = pOutput + outputLength;

    /* Fetch one word of PRNG and fill the leading "not word aligned" bytes */
    if (0u != ((uint32_t) bytePtr & 0x03u))
    {
        uint32_t randomWord = els_getPRNGWord();
        do
        {
            *bytePtr = (uint8_t) (randomWord & 0xFFu);
            bytePtr += 1u;
            randomWord >>= 8u;
        } while ((0u != ((uint32_t) bytePtr & 0x03u)) && (pOutputEnd > bytePtr));
    }

    /* Fill the specified buffer wordwise */
    uint8_t * const pOutputWordEnd = (uint8_t*) ((uint32_t) pOutputEnd & 0xFFFFFFFCu);
    while (pOutputWordEnd > bytePtr)
    {
        mcuxClMemory_StoreLittleEndian32(bytePtr, els_getPRNGWord());
        bytePtr += 4;
    }

    /* Fetch one word of PRNG and fill the remaining "less than one word" bytes */
    if (pOutputEnd > bytePtr)
    {
        uint32_t randomWord = els_getPRNGWord();
        do
        {
            *bytePtr = (uint8_t) (randomWord & 0xFFu);
            bytePtr += 1u;
            randomWord >>= 8u;
        } while (pOutputEnd > bytePtr);
    }

    /* check if enough entropy is available */
    if (MCUXCLELS_IS_ERROR_BIT_SET(MCUXCLELS_SFR_ERR_STATUS_PRNG_ERR))
    {
        /* clear ELS error flags */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_ResetErrorFlags());  /* always returns MCUXCLELS_STATUS_OK. */

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Prng_GetRandom, MCUXCLELS_STATUS_HW_PRNG,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_ResetErrorFlags));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Prng_GetRandom, MCUXCLELS_STATUS_OK);
}

#ifdef MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Dtrng_IterativeReseeding_Reseed)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Dtrng_IterativeReseeding_Reseed(const uint8_t *pDtrngConfig)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Dtrng_IterativeReseeding_Reseed,
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_Dtrng_ConfigLoad_Async),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)
                               );

    /* Reset the counter */
    mcuxClEls_rng_drbg_block_counter = 0u;

    uint8_t keyBuffer[MCUXCLELS_HMAC_PADDED_KEY_SIZE] = {0};
    uint8_t unusedData[MCUXCLELS_HMAC_OUTPUT_SIZE] = {0};
    uint8_t emptyMsg[32U] = {0};

    /* Prepare the options for the HMAC command which is called further down */
    mcuxClEls_HmacOption_t hmac_options = {
        .bits = {
            .extkey = MCUXCLELS_HMAC_EXTERNAL_KEY_ENABLE
        }
    };

    /* Wait for Operation (to avoid crashing a running operation). */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if(MCUXCLELS_STATUS_OK != status_wait1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
    }

    /* Run DTRNG_CFG_LOAD procedure */
    MCUX_CSSL_FP_FUNCTION_CALL(status_dtrng_configLoad1, mcuxClEls_Rng_Dtrng_ConfigLoad_Async(pDtrngConfig));
    if(MCUXCLELS_STATUS_OK_WAIT != status_dtrng_configLoad1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(status_wait2, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if(MCUXCLELS_STATUS_OK != status_wait2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
    }

    /* Request DRBG data for the HMAC Key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
    MCUX_CSSL_FP_FUNCTION_CALL(status_drbgRequest1, mcuxClEls_Rng_DrbgRequest_Async(keyBuffer, MCUXCLELS_HMAC_PADDED_KEY_SIZE));
    if(MCUXCLELS_STATUS_OK_WAIT != status_drbgRequest1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
    }
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()

    MCUX_CSSL_FP_FUNCTION_CALL(status_wait3, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if(MCUXCLELS_STATUS_OK != status_wait3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
    }

    for(uint32_t j = 0; j < (MCUXCLELS_RNG_DRBG_ITERATIVE_SEEDING_ITERATIONS - 1u); j++) {
        /* Run DTRNG_CFG_LOAD procedure */
        MCUX_CSSL_FP_FUNCTION_CALL(status_dtrng_configLoad2, mcuxClEls_Rng_Dtrng_ConfigLoad_Async(pDtrngConfig));
        if(MCUXCLELS_STATUS_OK_WAIT != status_dtrng_configLoad2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(status_wait4, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
        if(MCUXCLELS_STATUS_OK != status_wait4)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
        }

        /* Run HMAC command with external key:
            key = keyBuffer (the DRBG output)
            message = 32 bytes of 0
            output goes into unusedData (array on stack)
        */
        MCUX_CSSL_FP_FUNCTION_CALL(status_hmac, mcuxClEls_Hmac_Async(
                              hmac_options,
                              0U,
                              keyBuffer,
                              emptyMsg,
                              32U,
                              unusedData));
        if (MCUXCLELS_STATUS_OK_WAIT != status_hmac)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(status_wait5, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
        if(MCUXCLELS_STATUS_OK != status_wait5)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
        }

        /* Run DRBG_REQ procedure */
        MCUX_CSSL_ANALYSIS_START_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
        MCUX_CSSL_FP_FUNCTION_CALL(status_drbgRequest2, mcuxClEls_Rng_DrbgRequest_Async(keyBuffer, MCUXCLELS_HMAC_PADDED_KEY_SIZE));
        if(MCUXCLELS_STATUS_OK_WAIT != status_drbgRequest2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
        }
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()

        MCUX_CSSL_FP_FUNCTION_CALL(status_wait6, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
        if(MCUXCLELS_STATUS_OK != status_wait6)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_SW_FAULT);
        }
        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_Dtrng_ConfigLoad_Async),
                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hmac_Async),
                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequest_Async),
                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation)
                           );
    }

    MCUXCLMEMORY_FP_MEMORY_CLEAR(keyBuffer,MCUXCLELS_HMAC_PADDED_KEY_SIZE);


    MCUXCLMEMORY_FP_MEMORY_CLEAR(unusedData,MCUXCLELS_HMAC_OUTPUT_SIZE);


    /* No errors if we have reached this point */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_Reseed, MCUXCLELS_STATUS_OK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Dtrng_IterativeReseeding_CheckAndReseed)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Dtrng_IterativeReseeding_CheckAndReseed(const uint8_t *pDtrngConfig)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Dtrng_IterativeReseeding_CheckAndReseed);

    /* Check if the block counter has overflowed, and if so, call iterative reseeding procedure. */
    if(MCUXCLELS_RNG_DRBG_BLOCK_COUNTER_THRESHOLD <= mcuxClEls_rng_drbg_block_counter)
    {
        /* Back up interrupt enable flags */
        mcuxClEls_InterruptOptionEn_t interrupt_getter;
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_GetIntEnableFlags(&interrupt_getter));

        /* Set interrupt enable flags to DISABLE */
        mcuxClEls_InterruptOptionEn_t interrupt_setter = {0};
        interrupt_setter.bits.elsint = MCUXCLELS_ELS_INTERRUPT_DISABLE;
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_SetIntEnableFlags(interrupt_setter));

        /* Call function for iterative seeding of the DTRNG */
        MCUX_CSSL_FP_FUNCTION_CALL(status_itReseeding, mcuxClEls_Dtrng_IterativeReseeding_Reseed(pDtrngConfig));

        /* Clear interrupt status for the current interrupt before restoring interrupt enable flags to
         * mark this interrupt as handled and ensure that it is not handled again. */
        mcuxClEls_InterruptOptionRst_t interrupt_clear = {0};
        interrupt_clear.bits.elsint = MCUXCLELS_ELS_RESET_CLEAR;
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_ResetIntFlags(interrupt_clear));

        /* Restore interrupt enable flags */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_SetIntEnableFlags(interrupt_getter));

        /* Check error code of iterative seeding function */
        if(MCUXCLELS_STATUS_OK != status_itReseeding)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_CheckAndReseed, MCUXCLELS_STATUS_SW_FAULT);
        }
        MCUX_CSSL_FP_EXPECT(
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetIntEnableFlags),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Dtrng_IterativeReseeding_Reseed),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_ResetIntFlags),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Dtrng_IterativeReseeding_CheckAndReseed, MCUXCLELS_STATUS_OK);
}

#endif /* MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING */
