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

#include <mcuxCsslMemory.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxCsslFlowProtection.h>
#include <impl/mcuxCsslMemory_Copy_asm.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxCsslMemory_Copy)
mcuxCsslMemory_CopyResult_t mcuxCsslMemory_Copy
(
    mcuxCsslParamIntegrity_Checksum_t chk,
    void const * src,
    void * dst,
    size_t dst_size,
    size_t cnt
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxCsslMemory_Copy,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslParamIntegrity_Validate)
    );

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxCsslParamIntegrity_Validate(chk, 4u, src, dst, dst_size, cnt));
    
    if(result != MCUXCSSLPARAMINTEGRITY_CHECK_VALID) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Copy, MCUXCSSLMEMORY_COPY_FAULT);
    }
    
    if((NULL == src) || (NULL == dst) || (cnt > dst_size) || (0u == cnt)) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Copy, MCUXCSSLMEMORY_COPY_INVALID_PARAMETER);
    }

    uint32_t retval = (uint32_t) MCUXCSSLMEMORY_COPY_FAULT;
    
    const uint32_t nwords = cnt / 4U;
    const uint32_t success = (uint32_t)MCUXCSSLMEMORY_COPY_SUCCESS ^ (uint32_t)MCUXCSSLMEMORY_COPY_FAULT;
    uint32_t word = 0U;
    uint32_t xorword = 0U;
    uint32_t byte = 0U;
    uint32_t cha = nwords;
    uint32_t chb = 0xFFFFFFFFU;
    uint32_t datareg = 0U;
    
    MCUX_CSSL_SC_ADD(word); // -> should be 0
    MCUX_CSSL_SC_ADD(xorword); // -> should be 0
    MCUX_CSSL_SC_SUB(2U * nwords); // -> corresponds to `cha ^ chb + word` after the below assembly has executed
    // The following value is essentially a precalculation of the function xorchain(n) = 1 ^ 2 ^ 3 ^ 4 ^ 5 ^ ... ^ n (a chain of XOR operations), where n is substituted by nwords.
    // If n % 4 == 0, then xorchain(n) == n.
    // If n % 4 == 1, then xorchain(n) == 1.
    // If n % 4 == 2, then xorchain(n) == n + 1.
    // If n % 4 == 3, then xorchain(n) == 0.
    // The following is just a branchless way to do the case distinction.
    // In the loop afterwards, this value is calculated by actually cumulatively XORing the value of the variable "word" in each loop iteration, which starts at 0 and increments up to nwords.
    MCUX_CSSL_SC_SUB(nwords - (nwords % 2U) * nwords + ((nwords % 2U) ^ ((nwords % 4U) >> 1U))); // -> precalculation of xorword
    MCUX_CSSL_SC_SUB(cnt); // -> corresponds to `byte` after the below assembly has executed

    MCUXCSSLMEMORY_COPY_ASM(word, byte, cha, chb, xorword, retval, datareg, src, dst, nwords, cnt, success);

    MCUX_CSSL_SC_ADD(~(cha ^ chb));
    MCUX_CSSL_SC_ADD(xorword);
    MCUX_CSSL_SC_ADD(word);
    MCUX_CSSL_SC_ADD(byte);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxCsslMemory_Copy, retval);
}
