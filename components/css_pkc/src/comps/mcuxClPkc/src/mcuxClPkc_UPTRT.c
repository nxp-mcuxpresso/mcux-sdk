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

/**
 * @file  mcuxClPkc_UPTRT.c
 * @brief PKC UPTRT (Universal pointer FUP table) generation function
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClCss_Rng.h>

#include <mcuxClPkc_Types.h>
#include <mcuxClPkc_Functions.h>
#include <internal/mcuxClPkc_Macros.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_GenerateUPTRT)
mcuxClPkc_Status_Protected_t mcuxClPkc_GenerateUPTRT(uint16_t *pUPTRT,
                            const uint8_t *pBaseBuffer,
                            uint16_t bufferSize,
                            uint8_t noOfBuffer)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_GenerateUPTRT);

    uint32_t offset = MCUXCLPKC_PTR2OFFSET(pBaseBuffer);

    for (uint32_t idx = 0; idx < noOfBuffer; idx++)
    {
        pUPTRT[idx] = (uint16_t) offset;
        offset += bufferSize;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_GenerateUPTRT, MCUXCLPKC_STATUS_OK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_RandomizeUPTRT)
mcuxClPkc_Status_Protected_t mcuxClPkc_RandomizeUPTRT(uint16_t *pUPTRT,
                                                    uint8_t noOfBuffer)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_RandomizeUPTRT);

    MCUX_CSSL_FP_LOOP_DECL(Loop);
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_LOOP_ITERATIONS(Loop, ((uint32_t)noOfBuffer - 1U)));

    /* Randomize entries in UPTRT by Knuth shuffle. */
    for (uint32_t idx = noOfBuffer; idx > 1u; idx--)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(Loop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord));

        /* Generate a random number in the range [0, idx-1], where idx <= noOfBuffer <= 255. */
        uint32_t random32;
        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_randWord, mcuxClCss_Prng_GetRandomWord(&random32));
        if (MCUXCLCSS_STATUS_OK != ret_PRNG_randWord)
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
mcuxClPkc_Status_Protected_t mcuxClPkc_ReRandomizeUPTRT(uint16_t *pUPTRT,
                                                      uint16_t bufferSize,
                                                      uint8_t noOfBuffer)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ReRandomizeUPTRT);

    MCUX_CSSL_FP_LOOP_DECL(Loop);
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_LOOP_ITERATIONS(Loop, ((uint32_t)noOfBuffer - 1U)));

    /* Randomize entries in UPTRT by Knuth shuffle. */
    for (uint32_t idx = noOfBuffer; idx > 1u; idx--)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(Loop,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord));
        /* Generate a random number in the range [0, idx-1], where idx <= noOfBuffer <= 255. */
        uint32_t random32;
        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_randWord, mcuxClCss_Prng_GetRandomWord(&random32));
        if (MCUXCLCSS_STATUS_OK != ret_PRNG_randWord)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_ReRandomizeUPTRT, MCUXCLPKC_STATUS_NOK);
        }
        uint32_t random8 = random32 >> 8;
        random8 *= idx;
        random8 >>= 24;

        /* Swap. */
        uint16_t offset0 = pUPTRT[idx - 1u];
        uint16_t offset1 = pUPTRT[random8];
        pUPTRT[random8] = offset0;
        pUPTRT[idx - 1u] = offset1;

        /* PKC buffer is CPU word aligned. */
        uint32_t *ptr0 = (uint32_t *) MCUXCLPKC_OFFSET2PTR(offset0);
        uint32_t *ptr1 = (uint32_t *) MCUXCLPKC_OFFSET2PTR(offset1);

        /* Swap contents of the two buffers, of which the size is a multiple of CPU word. */
        for (uint32_t i = 0; i < ((uint32_t) bufferSize / 4u); i++)
        {
            uint32_t temp0 = ptr0[i];
            uint32_t temp1 = ptr1[i];
            ptr1[i] = temp0;
            ptr0[i] = temp1;
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_ReRandomizeUPTRT, MCUXCLPKC_STATUS_OK);
}
