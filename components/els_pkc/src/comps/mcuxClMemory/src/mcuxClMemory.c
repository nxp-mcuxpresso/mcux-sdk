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

#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslAnalysis.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_copy)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMemory_copy (uint8_t *pDst, uint8_t const *pSrc, size_t length, size_t bufLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_copy);

    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "modular arithmetic, mod 4")
    uint32_t unalignedBytes = (0u - (uint32_t)pDst) % (sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    MCUX_CSSL_FP_LOOP_DECL(mcuxClMemory_copy_loop);

    // Loop on unaligned bytes if any.
    // Loop on words
    // Start at first aligned address, increment by 4 bytes. To understand the loop condition, consider without loss of generality a
    // byte array b_i of length=4 and bufLength=4.
    //
    // |0                             3|4     4|
    // +-------+-------+-------+-------+-------+
    // |  b_0  |  b_1  |  b_2  |  b_3  |       |
    // +-------+-------+-------+-------+-------+
    //
    // In order to determine whether a full word can be copied, check with regard to the copying position i:
    // * Starting from i=0, a full word can be copied. i+4 is the first position that is outside of the valid range,
    //   and it is equal to length.
    // Therefore, checking that i+4 <= length and i+4 <= bufLength is a valid condition to check whether a full word can be
    // copied.
    // Loop on remaining bytes.

    //copy unaligned bytes first, if any
    size_t i = 0u;
    for(i = 0u; (i < length) && (i < bufLength) && (i < unalignedBytes); i++)
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pDst will be in the valid range pDst[0 ~ bufLength] and pSrc will be in the valid range pSrc[0 ~ length].")
        *pDst = *pSrc;
        pDst++;
        pSrc++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("The pointer is CPU word aligned. So, it's safe to cast it to uint32_t*")
    uint32_t* p32Dst = (uint32_t *) pDst;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    
    //loop on words
    for (; ((i + sizeof(uint32_t)) <= length) && ((i + sizeof(uint32_t)) <= bufLength); i += sizeof(uint32_t))
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "p32Dst will be in the valid range pDst[0 ~ bufLength] and pSrc will be in the valid range pSrc[0 ~ length].")
        /* Volatile keyword is added to avoid any chance of optimization (i.e. full word read) */
        uint32_t crtWordVal = (uint32_t)*(volatile const uint8_t *)pSrc;
        pSrc++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
        crtWordVal |= (uint32_t)*(volatile const uint8_t *)pSrc << 8u;
        pSrc++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
        crtWordVal |= (uint32_t)*(volatile const uint8_t *)pSrc << 16u;
        pSrc++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
        crtWordVal |= (uint32_t)*(volatile const uint8_t *)pSrc << 24u;
        pSrc++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
        *p32Dst++ = crtWordVal;
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    pDst = (uint8_t *) p32Dst;
    //loop on remaining bytes
    for (; (i < length) && (i < bufLength); i++)
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pDst will be in the valid range pDst[0 ~ bufLength] and pSrc will be in the valid range pSrc[0 ~ length].")
        *pDst = *pSrc;
        pDst++;
        pSrc++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMemory_copy,
                              length - i,
                              MCUX_CSSL_FP_LOOP_ITERATIONS(mcuxClMemory_copy_loop,
                                                          ((length <= bufLength) ? length : bufLength)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_copy_reversed)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMemory_copy_reversed (uint8_t *pDst, uint8_t const *pSrc, size_t length, size_t bufLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_copy_reversed);
    uint32_t len = length;
    uint32_t diff;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("diff is non-negative distance between pSrc and pDst, caculated according to platform architecture.")
    if (pDst > pSrc)
    {
        diff = (uint32_t)pDst - (uint32_t)pSrc;
    }
    else
    {
        diff = (uint32_t)pSrc - (uint32_t)pDst;
    }
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    if (bufLength < length)
    {
        length = bufLength;
    }

    MCUX_CSSL_FP_LOOP_DECL(mcuxClMemory_copy_reversed_loop);

    //non-overlap case
    if (diff >= length)
    {
        diff = length;
    }

    uint8_t *pDstBt;
    const uint8_t *pSrcBt;
    if (pSrc > pDst)
    {
        // first copy the non-overlop part
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pDstBt will be in the valid range pDst[0 ~ bufLength] and pSrc will be in the valid range pSrc[0 ~ length].")
        pSrcBt = pSrc + len - 1U;
        pDstBt = (uint8_t *)pDst;

        while (len > length - diff)
        {
            *pDstBt = *pSrcBt;
            pDstBt++;
            pSrcBt--;
            len--;
            MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_reversed_loop);
        }
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        //then swap the overlap part
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pDstBt2 will be in the valid range pDst[0 ~ bufLength].")
        uint8_t *pDstBt2 = pDstBt + len - 1u;
        while (len > 1U)
        {
            uint8_t tempByte = *pDstBt2;
            *pDstBt2 = *pDstBt;
            pDstBt2--;
            MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_reversed_loop);
            *pDstBt = tempByte;
            pDstBt++;
            len -= 2U;
            MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_reversed_loop);
        }
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }
    else
    {
        // first copy the non-overlop part
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pDstBt will be in the valid range pDst[0 ~ bufLength].")
        pDstBt = (uint8_t *)pDst + len - 1U;
        pSrcBt = pSrc;

        while (len > length - diff)
        {
            *pDstBt = *pSrcBt;
            pDstBt--;
            pSrcBt++;
            len--;
            MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_reversed_loop);
        }
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        //then swap the overlap part
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pDstBt2 will be in the valid range pDst[0 ~ bufLength], pDstBt will be in the valid range pDst[0 ~ bufLength].")
        uint8_t *pDstBt2 = pDstBt - len + 1u;
        while (len > 1U)
        {
            uint8_t tempByte = *pDstBt2;
            *pDstBt2 = *pDstBt;
            pDstBt2++;
            MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_reversed_loop);
            *pDstBt = tempByte;
            pDstBt--;
            len -= 2U;
            MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_reversed_loop);
        }
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMemory_copy_reversed,
                              MCUX_CSSL_FP_LOOP_ITERATIONS(mcuxClMemory_copy_reversed_loop, (length - len)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_set)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMemory_set (uint8_t *pDst, uint8_t val, size_t length, size_t bufLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_set);

    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "modular arithmetic, mod 4")
    uint32_t unalignedBytes = (0u - (uint32_t)pDst) % (sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    MCUX_CSSL_FP_LOOP_DECL(mcuxClMemory_set_loop);
    uint32_t wordVal = ((uint32_t)val << 24) | ((uint32_t)val << 16) | ((uint32_t)val << 8) | (uint32_t)val;

    //clear unaligned bytes first, if any
    size_t i = 0u;
    for(i = 0u; (i < length) && (i < bufLength) && (i < unalignedBytes); i++)
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pDst will be in the valid range pDst[0 ~ bufLength].")
        *pDst = val;
        pDst++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("The pointer is CPU word aligned. So, it's safe to cast it to uint32_t*")
    uint32_t* p32Dst = (uint32_t *) pDst;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

    //loop on words. See mcuxClMemory_copy for an explanation of the condition
    while(((i + sizeof(uint32_t)) <= length) && ((i + sizeof(uint32_t)) <= bufLength))
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "p32Dst will be in the valid range pDst[0 ~ bufLength] and pSrc will be in the valid range pSrc[0 ~ length].")
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        *p32Dst = wordVal;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        p32Dst++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        i += sizeof(uint32_t);
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    pDst = (uint8_t *) p32Dst;
    //loop on remaining bytes
    for(; (i < length) && (i < bufLength); i++)
    {
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pDst will be in the valid range pDst[0 ~ bufLength].")
        *pDst = val;
        pDst++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMemory_set,
                              length - i,
                              MCUX_CSSL_FP_LOOP_ITERATIONS(mcuxClMemory_set_loop,
                                                          ((length <= bufLength) ? length : bufLength)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_clear)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMemory_clear (uint8_t *pDst, size_t length, size_t bufLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_clear, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_set(pDst, 0U, length, bufLength));

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMemory_clear);
}
