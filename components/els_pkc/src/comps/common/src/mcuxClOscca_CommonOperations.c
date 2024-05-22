/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClOscca_CommonOperations.c
 *  @brief implementation of common functions */

#include <mcuxClToolchain.h>
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClMemory.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

/**********************************************************
 * Helper functions
 **********************************************************/
/**
 * This function reverses a byte string in-place (switches the endianness).
 *
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOscca_switch_endianness)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOscca_switch_endianness(uint32_t *ptr, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOscca_switch_endianness);
    if(0u == length)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOscca_switch_endianness);
    }
#ifdef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
    if (0u != (length % (sizeof(uint32_t))))
    {
        uint8_t *ptrL = (uint8_t *) ptr;
        uint8_t *ptrH = & ((uint8_t *) ptr)[length];

        uint32_t remainLength = length / 2u;
        while (0u < remainLength)
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("ptrH will be in the valid range [ptr+length-(length/2), ptr+length] and ptrL will be in the valid range [ptr, ptr+length/2].")
            ptrH--;
            uint8_t byteH = *ptrH;
            uint8_t byteL = *ptrL;

            *ptrL = byteH;
            *ptrH = byteL;
            ptrL++;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

            remainLength--;
        }

        MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOscca_switch_endianness);
    }

    /* When the length is a multiple of CPU word size, fall down to the original implementation. */
    /* length is a multiple of CPU word size (4). */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("ptr is CPU word aligned, and length is a multiple of CPU word size.")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("ptrH32 will not be dereferenced outside the range [ptr, ptr+length-1] because of the condition (ptrH32 >= ptrL32).")
    uint32_t *ptrH32 = (uint32_t *) ((uint8_t *) ptr + length - 4u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
#else
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("use of UNALIGNED keyword")
    MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(CERT_EXP36_C, "use of UNALIGNED keyword")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("ptrH32 will not be dereferenced outside the range [ptr, ptr+length-1] because of the condition (ptrH32 >= ptrL32).")
    uint32_t UNALIGNED *ptrH32 = (uint32_t UNALIGNED *) ((uint8_t *) ptr + length - 4u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(CERT_EXP36_C)
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
#endif
   uint32_t *ptrL32 = ptr;

    /* While there are >= 4 bytes to switch the endianness. */
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(MISRA_C_2012_Rule_18_3, "both ptrH32 and ptrL32 point into ptr[].")
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(CERT_ARR36_C, "both ptrH32 and ptrL32 point into ptr[].")
    while (ptrH32 >= ptrL32)
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(CERT_ARR36_C)
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(MISRA_C_2012_Rule_18_3)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("ptrH32 and ptrL32 will not be dereferenced outside the range [ptr, ptr+length-1] because of the condition (ptrH32 >= ptrL32).")
        uint32_t wordL = *ptrL32;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("ptrH32 = (uint32_t *) ((uint8_t *) ptr + length - 4u) is safe.")
        uint32_t wordH = *ptrH32;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

        wordL = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(wordL);
        wordH = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(wordH);

        *ptrH32 = wordL;
        ptrH32--;
        *ptrL32 = wordH;
        ptrL32++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }
#ifdef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
    /* Now, ptrH32 = phtL32 - 4 or ptrL32 - 8, nothing more to do. */
#else
    /* If ptrH <= ptrL - 4, nothing more to do. */
    /* If ptrH == ptrL - 3, swap ptrL[0] with ptrH[3] = ptrL[0], i.e., nothing to do. */
    /* If ptrH == ptrL - 2, swap ptrL[0] with ptrH[3] = ptrL[1]. */
    /* If ptrH == ptrL - 1, swap ptrL[0] with ptrH[3] = ptrL[2], and leave ptrL[1] unchanged. */

    /* Wrongly reports MISRA violation to Rule 11.8 that ptrH8 and ptrL8 are not point into the same object */
    uint8_t *ptrL8 = (uint8_t *) ptrL32;
    uint8_t *ptrH8 = (uint8_t *) ptrH32 + 3u;
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(MISRA_C_2012_Rule_18_3, "both ptrH8 and ptrL8 point into ptr[].")
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(CERT_ARR36_C, "both ptrH32 and ptrL32 point into ptr[].")
    if (ptrH8 > ptrL8)
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(CERT_ARR36_C)
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(MISRA_C_2012_Rule_18_3)
    {
        uint8_t byteL = *ptrL8;
        uint8_t byteH = *ptrH8;

        *ptrH8 = byteL;
        *ptrL8 = byteH;
    }
#endif
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOscca_switch_endianness);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOscca_FastSecureXor)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOscca_FastSecureXor(void *pTgt,
        void *pSrc1,
        void *pSrc2,
        uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOscca_FastSecureXor);
    uint8_t *pTgtBt = pTgt;
    uint32_t *pTgtWd = pTgt;
    uint8_t *pSrc1Bt = pSrc1;
    uint8_t *pSrc2Bt = pSrc2;
    uint32_t *pSrc1Wd = pSrc1;
    uint32_t *pSrc2Wd = pSrc2;
    uint32_t i;
    uint32_t wordSize = sizeof(uint32_t);

    /* xor by word if aligned */
    /* MISRA Ex.2 - Rule 11.6 */
    if ((length >= wordSize) && (0U == ((uint32_t)pTgt & (wordSize - 1U)))
                && (0U == ((uint32_t)pSrc1 & (wordSize - 1U)))
                && (0U == ((uint32_t)pSrc2 & (wordSize - 1U))))
    {
        i = 0U;
        while (length >= wordSize)
        {
            pTgtWd[i] = pSrc1Wd[i] ^ pSrc2Wd[i];
            length -= wordSize;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("The size of i is big enough, it cannot overflow.")
            i++;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("In the actual situation, i * wordSize cannot overflow.")
        pTgtBt = pTgtBt + i * wordSize;
        pSrc1Bt = pSrc1Bt + i * wordSize;
        pSrc2Bt = pSrc2Bt + i * wordSize;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }


    if (0U < length)
    {
        /* xor the remain bytes */
        for (i = 0U; i < length; i++)
        {
            pTgtBt[i] = pSrc1Bt[i] ^ pSrc2Bt[i];
        }
    }
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOscca_FastSecureXor);
}
