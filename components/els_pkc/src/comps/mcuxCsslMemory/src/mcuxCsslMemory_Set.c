/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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
 * @file  mcuxCsslMemory_Set.c
 * @brief mcuxCsslMemory: implementation of memory set function
 */


#include <stddef.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslFlowProtection_FunctionIdentifiers.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslAnalysis.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxCsslMemory_Set)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxCsslMemory_Status_t) mcuxCsslMemory_Set
(
    mcuxCsslParamIntegrity_Checksum_t chk,
    void * pDst,
    uint8_t val,
    size_t length,
    size_t bufLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxCsslMemory_Set,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslParamIntegrity_Validate));

    MCUX_CSSL_FP_FUNCTION_CALL(retCode_paramIntegrityValidate, mcuxCsslParamIntegrity_Validate(chk, 4u, pDst, val, length, bufLength));

    if (MCUXCSSLPARAMINTEGRITY_CHECK_VALID != retCode_paramIntegrityValidate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Set, MCUXCSSLMEMORY_STATUS_FAULT);
    }

    if ((NULL == pDst) || (0u == length))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Set, MCUXCSSLMEMORY_STATUS_INVALID_PARAMETER);
    }

    size_t copyLen = bufLength < length ? bufLength : length;
    uint32_t remainLength = (uint32_t) copyLen;
    uint32_t wordVal = ((uint32_t)val << 24) | ((uint32_t)val << 16) | ((uint32_t)val << 8) | (uint32_t)val;
    const uint32_t cpuWordSize = sizeof(uint32_t);

    volatile uint8_t *p8Dst = (volatile uint8_t *) pDst; // needs to be aligned

#ifdef __COVERITY__
#pragma coverity compliance block deviate MISRA_C_2012_Rule_11_6 "Exception 6: casting void pointer to security counter type"
#endif
   MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pDst will be in the valid range pDst[0 ~ copyLen].")
   MCUX_CSSL_SC_ADD((uint32_t) pDst + copyLen);
   MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
#ifdef __COVERITY__
#pragma coverity compliance end_block MISRA_C_2012_Rule_11_6
#endif

    MCUX_CSSL_FP_LOOP_DECL(FirstByteLoop);
    MCUX_CSSL_FP_LOOP_DECL(SecondByteLoop);
    MCUX_CSSL_FP_LOOP_DECL(WordLoop);

    while ((0u != ((uint32_t) p8Dst & (cpuWordSize - 1u))) && (0u != remainLength))
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "p8Dst will be in the valid range pDst[0 ~ copyLen].")
        MCUX_CSSL_FP_LOOP_ITERATION(FirstByteLoop);
        *p8Dst = val;
        p8Dst++;
        remainLength--;
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }


#ifdef __COVERITY__
#pragma coverity compliance block deviate MISRA_C_2012_Rule_11_3 "Exception 9: re-interpreting the memory"
#endif
    volatile uint32_t *p32Dst = (volatile uint32_t *) p8Dst;  /* p8Dst is CPU word-aligned after the previous loop. */
#ifdef __COVERITY__
#pragma coverity compliance end_block MISRA_C_2012_Rule_11_3
#endif
    while (cpuWordSize <= remainLength)
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "p32Dst will be in the valid range pDst[0 ~ copyLen].")
        MCUX_CSSL_FP_LOOP_ITERATION(WordLoop);
        *p32Dst = wordVal;
        p32Dst++;
        remainLength -= cpuWordSize;
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    p8Dst = (volatile uint8_t *) p32Dst;
    while (0u != remainLength)
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "p8Dst will be in the valid range pDst[0 ~ copyLen].")
        MCUX_CSSL_FP_LOOP_ITERATION(SecondByteLoop);
        *p8Dst = val;
        p8Dst++;
        remainLength--;
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    MCUX_CSSL_SC_SUB((uint32_t) p8Dst);
#ifdef __COVERITY__
#pragma coverity compliance block deviate MISRA_C_2012_Rule_11_6 "Exception 6: casting void pointer to security counter type"
#endif
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "modular arithmetic, mod 4")
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t noOfBytesToAlignment = ((0u - ((uint32_t) pDst)) % cpuWordSize));
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
#ifdef __COVERITY__
#pragma coverity compliance end_block MISRA_C_2012_Rule_11_6
#endif
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t firstByteIteration = (copyLen > noOfBytesToAlignment)
                             ? noOfBytesToAlignment
                             : copyLen);
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t wordIteration = (copyLen > firstByteIteration)
                             ? ((copyLen - firstByteIteration) / cpuWordSize)
                             : 0u);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Set, MCUXCSSLMEMORY_STATUS_OK,
        MCUX_CSSL_FP_LOOP_ITERATIONS(FirstByteLoop, firstByteIteration),
        MCUX_CSSL_FP_LOOP_ITERATIONS(WordLoop, wordIteration),
        MCUX_CSSL_FP_LOOP_ITERATIONS(SecondByteLoop, copyLen - (wordIteration * cpuWordSize) - firstByteIteration));
}
