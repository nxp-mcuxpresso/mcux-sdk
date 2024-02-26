/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021, 2023 NXP                                            */
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
 * @file  mcuxClPkc_UPTRT.c
 * @brief PKC UPTRT (Universal pointer FUP table) generation function
 */


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClRandom.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClPkc_Functions.h>
#include <internal/mcuxClPkc_Macros.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_GenerateUPTRT)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_GenerateUPTRT(
    uint16_t *pUPTRT,
    const uint8_t *pBaseBuffer,
    uint16_t bufferLength,
    uint8_t noOfBuffer)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_GenerateUPTRT);

    uint32_t offset = MCUXCLPKC_PTR2OFFSET(pBaseBuffer);

    for (uint32_t idx = 0; idx < noOfBuffer; idx++)
    {
        pUPTRT[idx] = (uint16_t) offset;
        offset += bufferLength; // TODO-9364: Open violaation to INT30-C for rt700 and s540
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_GenerateUPTRT);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_RandomizeUPTRT)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_RandomizeUPTRT(
    mcuxClSession_Handle_t pSession,
    uint16_t *pUPTRT,
    uint8_t noOfBuffer)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_RandomizeUPTRT);

    MCUX_CSSL_FP_LOOP_DECL(Loop);
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_LOOP_ITERATIONS(Loop, ((uint32_t)noOfBuffer - 1U)));

    /* Randomize entries in UPTRT by Knuth shuffle. */
    for (uint32_t idx = noOfBuffer; idx > 1u; idx--)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(Loop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));


        /* Generate a random number in the range [0, idx-1], where idx <= noOfBuffer <= 255. */
        uint32_t random32;
        MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate, mcuxClRandom_ncGenerate(pSession, (uint8_t *) &random32, sizeof(uint32_t)));
        if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_RandomizeUPTRT, MCUXCLPKC_STATUS_NOK);
        }
        uint32_t random8 = random32 >> 8;
        random8 *= idx;
        random8 >>= 24;

        /* Swap. */
        uint16_t temp0 = pUPTRT[idx - 1u];
        uint16_t temp1 = pUPTRT[random8];
        pUPTRT[random8] = temp0;
        pUPTRT[idx - 1u] = temp1;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_RandomizeUPTRT, MCUXCLPKC_STATUS_OK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ReRandomizeUPTRT)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_ReRandomizeUPTRT(
    mcuxClSession_Handle_t pSession,
    uint16_t *pUPTRT,
    uint16_t bufferLength,
    uint8_t noOfBuffer)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ReRandomizeUPTRT);

    MCUX_CSSL_FP_LOOP_DECL(Loop);
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_LOOP_ITERATIONS(Loop, ((uint32_t)noOfBuffer - 1U)));

    /* Randomize entries in UPTRT by Knuth shuffle. */
    for (uint32_t idx = noOfBuffer; idx > 1u; idx--)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(Loop,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
        /* Generate a random number in the range [0, idx-1], where idx <= noOfBuffer <= 255. */
        uint32_t random32;
        MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate, mcuxClRandom_ncGenerate(pSession, (uint8_t *) &random32, sizeof(uint32_t)));
        if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_ReRandomizeUPTRT, MCUXCLPKC_STATUS_NOK);
        }
        uint32_t random8 = random32 >> 8u;
        random8 *= idx;
        random8 >>= 24u;

        /* Swap. */
        uint16_t offset0 = pUPTRT[idx - 1u];
        uint16_t offset1 = pUPTRT[random8];
        pUPTRT[random8] = offset0;
        pUPTRT[idx - 1u] = offset1;

        /* Caller shall provide UPTR table with all offsets being exactly a multiple of MCUXCLPKC_WORDSIZE. */
        uint32_t *ptr0 = MCUXCLPKC_OFFSET2PTRWORD(offset0);
        uint32_t *ptr1 = MCUXCLPKC_OFFSET2PTRWORD(offset1);

        /* Swap contents of the two buffers, of which the size is a multiple of CPU word. */
        for (uint32_t i = 0u; i < ((uint32_t) bufferLength / 4u); i++)
        {
            uint32_t temp0 = ptr0[i];
            uint32_t temp1 = ptr1[i];
            ptr1[i] = temp0;
            ptr0[i] = temp1;
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_ReRandomizeUPTRT, MCUXCLPKC_STATUS_OK);
}
