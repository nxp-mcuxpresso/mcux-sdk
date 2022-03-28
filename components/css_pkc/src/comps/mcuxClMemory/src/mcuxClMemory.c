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

#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <toolchain.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_copy)
mcuxClMemory_Status_Protected_t mcuxClMemory_copy (uint8_t *dst, uint8_t const *src, size_t len, size_t buflen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_copy);

    size_t i;
    MCUX_CSSL_FP_LOOP_DECL(mcuxClMemory_copy_loop);

    // First loop on words
    // Start at byte 0, increment by 4 bytes. To understand the loop condition, consider without loss of generality a
    // byte array b_i of len=4 and buflen=4.
    //
    // |0                             3|4     4|
    // +-------+-------+-------+-------+-------+
    // |  b_0  |  b_1  |  b_2  |  b_3  |       |
    // +-------+-------+-------+-------+-------+
    //
    // In order to determine whether a full word can be copied, check with regard to the copying position i:
    // * Starting from i=0, a full word can be copied. i+4 is the first position that is outside of the valid range,
    //   and it is equal to len.
    // * Starting from i=1, 2 or 3, no full word can be copied. i+4 is greater than len.
    // Therefore, checking that i+4 <= len and i+4 <= buflen is a valid condition to check whether a full word can be
    // copied.
    for (i = 0u; ((i + sizeof(uint32_t)) <= len) && ((i + sizeof(uint32_t)) <= buflen); i += sizeof(uint32_t))
    {
        /* MISRA Ex. 9 - Rule 11.3 - Use of UNALIGNED keyword. */
        *(UNALIGNED uint32_t*)dst = *(UNALIGNED uint32_t const*)src;
        dst += sizeof(uint32_t);
        src += sizeof(uint32_t);

        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
    }

    //loop on remaining bytes
    for (; (i < len) && (i < buflen); i++)
    {
        *dst = *src;
        dst++;
        src++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_copy_loop);
    }
    
    size_t lenExceeded = len - i;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMemory_copy,
                              lenExceeded,
                              MCUX_CSSL_FP_LOOP_ITERATIONS(mcuxClMemory_copy_loop,
                                                          (i / sizeof(uint32_t)) + (i & 0x3U)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_set)
mcuxClMemory_Status_Protected_t mcuxClMemory_set (uint8_t *dst, uint8_t val, size_t len, size_t buflen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_set);
    
    size_t i;
    uint32_t unalignedBytes = ((sizeof(uint32_t)) - (uint32_t)dst) & ((sizeof(uint32_t)) - 1u);
    MCUX_CSSL_FP_LOOP_DECL(mcuxClMemory_set_loop);
    uint32_t wordVal = ((uint32_t)val << 24) | ((uint32_t)val << 16) | ((uint32_t)val << 8) | (uint32_t)val;

    //clear unaligned bytes first, if any
    for(i = 0u; (i < len) && (i < buflen) && (i < unalignedBytes); i++)
    {
        *dst = val;
        dst++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
    }

    //loop on words. See mcuxClMemory_copy for an explanation of the condition
    while(((i + sizeof(uint32_t)) <= len) && ((i + sizeof(uint32_t)) <= buflen))
    {
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        /* MISRA Ex. 9 - Rule 11.3 - Use of UNALIGNED keyword. */
        *(UNALIGNED uint32_t*)dst = wordVal;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        dst += sizeof(uint32_t);
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
        i += sizeof(uint32_t);
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
    }

    //loop on remaining bytes
    for(; (i < len) && (i < buflen); i++)
    {
        *dst = val;
        dst++;
        MCUX_CSSL_FP_LOOP_ITERATION(mcuxClMemory_set_loop);
    }

    size_t lenExceeded = len - i;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMemory_set,
                              lenExceeded,
                              MCUX_CSSL_FP_LOOP_ITERATIONS(mcuxClMemory_set_loop,
                                                          ((len <= buflen) ? len : buflen)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMemory_clear)
mcuxClMemory_Status_Protected_t mcuxClMemory_clear (uint8_t *dst, size_t len, size_t buflen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMemory_clear, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    MCUX_CSSL_FP_FUNCTION_CALL(setResult, mcuxClMemory_set(dst, 0U, len, buflen));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMemory_clear,
                              setResult);
}
