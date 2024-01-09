/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/** @file  mcuxClTrng_ELS.c
 *  @brief Implementation of the Trng component which provides APIs for
 *  handling of Trng random number. This file implements the functions
 *  declared in mcuxClTrng_Internal_Functions.h. */

#include <mcuxClToolchain.h>
#include <mcuxClSession.h>
#include <mcuxClEls.h>
#include <mcuxCsslMemory.h>
#include <internal/mcuxClTrng_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClTrng_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClTrng_Status_t) mcuxClTrng_Init(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClTrng_Init);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_Init, MCUXCLTRNG_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClTrng_getEntropyInput)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClTrng_Status_t) mcuxClTrng_getEntropyInput(
    mcuxClSession_Handle_t pSession UNUSED_PARAM,
    uint32_t *pEntropyInput,
    uint32_t entropyInputLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClTrng_getEntropyInput);

    /**
     * ELS DTRNG output size must be 32 bytes.
     * We first request as much as possible directly, and then use a small buffer
     * to copy up to 32 remaining bytes.
     */

    /**
     * Note: writing to pEntropyInput could be unaligned.
     * This could be improved by: - requesting a 32 bytes
     *                            - copying as many bytes as needed to achieve alignment
     *                            - requesting the following 32 bytes to aligned addresses
     *                            - possibly requesting another 32 bytes to fill the remaining bytes
     */

    /* Check if entropyInputLength is word aligned and pEntropyInput is not NULL*/
    if((0u != (entropyInputLength % sizeof(uint32_t))) || (NULL == pEntropyInput))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_ERROR);
    }

    uint32_t requestSizeELSrawRequest       = MCUXCLTRNG_ELS_TRNG_OUTPUT_SIZE;
    uint32_t remainingNonFullELSblockBytes  = entropyInputLength % requestSizeELSrawRequest;
    uint32_t fullELSblocksBytes             = entropyInputLength - remainingNonFullELSblockBytes;
    uint32_t fullELSblocks                  = fullELSblocksBytes/requestSizeELSrawRequest;

    /* Request as many random bytes as possible with full 32 bytes size. */
    if (fullELSblocksBytes > 0u)
    {
        for(uint32_t i = 0; i < fullELSblocks; i++)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(ret_DTRNG_GetTrng1, mcuxClEls_Rng_DrbgRequestRaw_Async((uint8_t *)&pEntropyInput[i*MCUXCLTRNG_ELS_TRNG_OUTPUT_SIZE/sizeof(uint32_t)]));
            if(MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_DTRNG_GetTrng1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_ERROR,
                    (i+1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequestRaw_Async),
                    i * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
            }
            else if (MCUXCLELS_STATUS_OK_WAIT != ret_DTRNG_GetTrng1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_FAULT_ATTACK);
            }
            else
            {
                /* Intentionally left empty */
            }

            MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_Wait1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
            if((MCUXCLELS_STATUS_HW_OPERATIONAL == ret_DRBG_Wait1) || (MCUXCLELS_STATUS_HW_ALGORITHM == ret_DRBG_Wait1) || (MCUXCLELS_STATUS_HW_BUS == ret_DRBG_Wait1))
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_ERROR,
                    (i+1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequestRaw_Async),
                    (i+1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
            }
            else if (MCUXCLELS_STATUS_OK != ret_DRBG_Wait1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_FAULT_ATTACK);
            }
            else
            {
                /* Intentionally left empty */
            }
        }
    }

    /* If requested size is not a multiple of 32, request one (additional) 32 bytes and use it only partially. */
    if (remainingNonFullELSblockBytes > 0u)
    {
        uint8_t requestRemainingBuffer[MCUXCLTRNG_ELS_TRNG_OUTPUT_SIZE] = {0u};

        MCUX_CSSL_ANALYSIS_START_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
        MCUX_CSSL_FP_FUNCTION_CALL(ret_DTRNG_GetTrng2, mcuxClEls_Rng_DrbgRequestRaw_Async(requestRemainingBuffer));
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
        if(MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_DTRNG_GetTrng2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_ERROR,
                (fullELSblocks + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequestRaw_Async),
                fullELSblocks * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        }
        else if (MCUXCLELS_STATUS_OK_WAIT != ret_DTRNG_GetTrng2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ret_DRBG_Wait2, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
        if((MCUXCLELS_STATUS_HW_OPERATIONAL == ret_DRBG_Wait2) || (MCUXCLELS_STATUS_HW_ALGORITHM == ret_DRBG_Wait2) || (MCUXCLELS_STATUS_HW_BUS == ret_DRBG_Wait2))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_ERROR,
                (fullELSblocks + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequestRaw_Async),
                (fullELSblocks + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        }
        else if (MCUXCLELS_STATUS_OK != ret_DRBG_Wait2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Copy the remaining bytes from the buffer to output. */
        MCUX_CSSL_FP_FUNCTION_CALL(copy_result, mcuxCsslMemory_Copy(
           mcuxCsslParamIntegrity_Protect(4u, requestRemainingBuffer, &pEntropyInput[fullELSblocksBytes/sizeof(uint32_t)], remainingNonFullELSblockBytes, remainingNonFullELSblockBytes),
               requestRemainingBuffer,
               &pEntropyInput[fullELSblocksBytes/sizeof(uint32_t)],
               remainingNonFullELSblockBytes,
               remainingNonFullELSblockBytes)
        );
        if(MCUXCSSLMEMORY_STATUS_OK != copy_result)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_FAULT_ATTACK);
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_OK,
            MCUX_CSSL_FP_CONDITIONAL((fullELSblocksBytes > 0u),
               (entropyInputLength/MCUXCLTRNG_ELS_TRNG_OUTPUT_SIZE) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequestRaw_Async),
               (entropyInputLength/MCUXCLTRNG_ELS_TRNG_OUTPUT_SIZE) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation)),
            MCUX_CSSL_FP_CONDITIONAL((remainingNonFullELSblockBytes > 0u),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_DrbgRequestRaw_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy)));
}
