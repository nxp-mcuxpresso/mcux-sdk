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
 * @file  mcuxCsslMemory_Clear.c
 * @brief mcuxCsslMemory: implementation of robust memory clear function
 */


#include <stddef.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslMemory_Clear.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxCsslMemory_Clear)
mcuxCsslMemory_ClearResult_t mcuxCsslMemory_Clear
(
    mcuxCsslParamIntegrity_Checksum_t chk,
    void * pDst,
    size_t dst_size,
    size_t cnt
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxCsslMemory_Clear,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslParamIntegrity_Validate) );

    MCUX_CSSL_FP_FUNCTION_CALL(retCode_paramIntegrityValidate, mcuxCsslParamIntegrity_Validate(chk, 3u, pDst, dst_size, cnt));

    if ((retCode_paramIntegrityValidate != MCUXCSSLPARAMINTEGRITY_CHECK_VALID))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Clear, MCUXCSSLMEMORY_CLEAR_FAULT);
    }

    if ((NULL == pDst) || (cnt > dst_size) || (0u == cnt))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Clear, MCUXCSSLMEMORY_CLEAR_INVALID_PARAMETER);
    }

    MCUX_CSSL_SC_ADD((uint32_t) pDst + cnt);

    MCUX_CSSL_FP_LOOP_DECL(ByteLoop);
    MCUX_CSSL_FP_LOOP_DECL(WordLoop);

    volatile uint8_t *p8Dst = (volatile uint8_t *) pDst;
    uint32_t remainLength = (uint32_t) cnt;
    const uint32_t cpuWordSize = sizeof(uint32_t);

    while ((0u != ((uint32_t) p8Dst & (cpuWordSize - 1u))) && (0u != remainLength))
    {
        MCUX_CSSL_FP_LOOP_ITERATION(ByteLoop);
        *p8Dst = 0u;
        p8Dst++;
        remainLength--;
    }

    volatile uint32_t *p32Dst = (volatile uint32_t *) p8Dst;  /* p8Dst is CPU word-aligned after the previous loop. */
    while (4u <= remainLength)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(WordLoop);
        *p32Dst = 0u;
        p32Dst++;
        remainLength -= 4u;
    }

    p8Dst = (volatile uint8_t *) p32Dst;
    while (0u != remainLength)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(ByteLoop);
        *p8Dst = 0u;
        p8Dst++;
        remainLength--;
    }

    MCUX_CSSL_SC_SUB((uint32_t) p8Dst);
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t fractionBytesInFirstWord = ((0u - (uint32_t) pDst) & (cpuWordSize - 1u)));
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t wordIteration = (cnt > fractionBytesInFirstWord)
                             ? ((cnt - fractionBytesInFirstWord) / cpuWordSize)
                             : 0u);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Clear, MCUXCSSLMEMORY_CLEAR_SUCCESS,
        MCUX_CSSL_FP_LOOP_ITERATIONS(WordLoop, wordIteration),
        MCUX_CSSL_FP_LOOP_ITERATIONS(ByteLoop, cnt - (wordIteration * cpuWordSize)) );
}
