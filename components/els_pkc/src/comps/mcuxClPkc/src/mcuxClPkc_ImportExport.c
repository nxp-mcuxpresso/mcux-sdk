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
 * @file  mcuxClPkc_ImportExport.c
 * @brief mcuxClPkc: implementation of PKC internal import/export functions
 */


#include <mcuxClToolchain.h>
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClRandom.h>
#include <mcuxCsslMemory.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>

#include <mcuxClPkc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClMemory_Copy_Internal.h>


/**
 * [Design]
 * This function reverses a byte string in-place (switches the endianness).
 *
 * The buffer address shall be CPU word (4-byte) aligned.
 *
 * For platforms not supporting unaligned access to PKC workarea, this function
 * accesses to the byte string word-wisely if length is a multiple of CPU wordsize,
 * and byte-wisely if length is not a multiple of CPU wordsize.
 *
 * For platforms supporting unaligned access to PKC workarea, this function
 * intentionally declares some memory accesses as UNALIGNED.
 * When length = 0, this function does nothing.
 * When length = 8n+t, this function accesses the first 4n bytes and the last 4n
 * bytes word-wisely. Accesses to the last 4n bytes are declared as UNALIGNED.
 * For the t bytes in between, there are 2 scenarios:
 *   when t = 1~3, this function accesses these t-byte byte-wisely;
 *   when t = 4~7, this function accesses these t-byte word-wisely.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SwitchEndianness)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_SwitchEndianness(uint32_t *ptr, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SwitchEndianness);
    if(0u == length)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_SwitchEndianness);
    }
#ifdef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
    if (0u != (length % (sizeof(uint32_t))))
    {
        uint8_t *ptrL = (uint8_t *) ptr;
        uint8_t *ptrH = & ((uint8_t *) ptr)[length];

        uint32_t remainLength = length / 2u;
        while (0u < remainLength)
        {
            MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "ptrH will be in the valid range [ptr+length-(length/2), ptr+length] and ptrL will be in the valid range [ptr, ptr+length/2].")
            ptrH--;
            uint8_t byteH = *ptrH;
            uint8_t byteL = *ptrL;

            *ptrL = byteH;
            *ptrH = byteL;
            ptrL++;
            MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)

            remainLength--;
        }

        MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_SwitchEndianness);
    }

    /* When the length is a multiple of CPU word size, fall down to the original implementation. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("ptr is CPU word aligned, and length is a multiple of CPU word size.")
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "ptrH32 will not be dereferenced outside the range [ptr, ptr+length-1] because of the condition (ptrH32 >= ptrL32).")
    uint32_t *ptrH32 = (uint32_t *) & ((uint8_t *) ptr)[length - 4u];
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
#else
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("use of UNALIGNED keyword")
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "ptrH32 will not be dereferenced outside the range [ptr, ptr+length-1] because of the condition (ptrH32 >= ptrL32).")
    uint32_t UNALIGNED *ptrH32 = (uint32_t UNALIGNED *) & ((uint8_t *) ptr)[length - 4u];
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
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
        MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "ptrH32 and ptrL32 will not be dereferenced outside the range [ptr, ptr+length-1] because of the condition (ptrH32 >= ptrL32).")
        uint32_t wordL = *ptrL32;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("UNALIGNED keyword is used for ptrH32 definition")
        uint32_t wordH = *ptrH32;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()

        wordL = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(wordL);
        wordH = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(wordH);

        *ptrH32 = wordL;
        ptrH32--;
        *ptrL32 = wordH;
        ptrL32++;
        MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
    }

#ifdef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
    /* Now, ptrH32 = phtL32 - 4 or ptrL32 - 8, nothing more to do. */
#else
    /* If ptrH <= ptrL - 4, nothing more to do. */
    /* If ptrH == ptrL - 3, swap ptrL[0] with ptrH[3] = ptrL[0], i.e., nothing to do. */
    /* If ptrH == ptrL - 2, swap ptrL[0] with ptrH[3] = ptrL[1]. */
    /* If ptrH == ptrL - 1, swap ptrL[0] with ptrH[3] = ptrL[2], and leave ptrL[1] unchanged. */
    uint8_t *ptrL8 = (uint8_t *) ptrL32;
    uint8_t *ptrH8 = & ((uint8_t *) ptrH32)[3u];
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

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_SwitchEndianness);
}


/**
 * [Design]
 * This function imports an integer stored as a big-endian octet string to PKC workarea.
 *
 * (1) clear the target PKC buffer by PKC if the passed length is not equal to (PS1 OPLEN);
 * (2) copy the string to the target PKC buffer with offset, (pTarget+offset)[],
 *     where offset = (0 - length) % (CPU word size);
 * (3) switch the endianness of the string (with the offset zero byte(s) in the beginning)
 *     in-place in the target PKC buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ImportBigEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ImportBigEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ImportBigEndianToPkc);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t * p32Target = MCUXCLPKC_OFFSET2PTRWORD(pOperands[iTarget]);  /* Caller shall provide PKC-word aligned operand iTarget. */

    if (operandSize != length)
    {
        MCUXCLPKC_FP_CALC_OP1_CONST(iTarget, 0u);
    }

    MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(CERT_INT30_C, "modular arithmetic.")
    uint32_t offset = (0u - length) % (sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(CERT_INT30_C)
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("offset in range [0,3], and length <= alignedLength <= PKC PS1LEN.")
    uint32_t alignedLength = length + offset;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    MCUXCLPKC_WAITFORFINISH();

    /* PKC buffer size is a multiple of MCUXCLPKC_WORDSIZE (also CPU wordsize). */
    /* When length is not a multiple of CPU word size (i.e., offset != 0),     */
    /* there will be offset bytes beyond the specified length of the target.   */
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "offset in range [0,3], and length <= alignedLength <= PKC PS1LEN.")
    MCUXCLMEMORY_FP_MEMORY_COPY(& ((uint8_t *) p32Target)[offset], pSource, length);
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Target, alignedLength);  /* PKC buffer is CPU word aligned. */
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_ImportBigEndianToPkc,
        MCUX_CSSL_FP_CONDITIONAL((operandSize != length),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness) );
}


/**
 * [Design]
 * This function imports an integer stored as a little-endian octet string to PKC workarea.
 *
 * (1) clear the target PKC buffer by PKC if the passed length is not equal to (PS1 OPLEN);
 * (2) copy the string to the target PKC buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ImportLittleEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ImportLittleEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ImportLittleEndianToPkc);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t * pTarget = MCUXCLPKC_OFFSET2PTR(pOperands[iTarget]);

    if (operandSize != length)
    {
        MCUXCLPKC_FP_CALC_OP1_CONST(iTarget, 0u);
    }
    MCUXCLPKC_WAITFORFINISH();

    MCUXCLMEMORY_FP_MEMORY_COPY(pTarget, pSource, length);

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_ImportLittleEndianToPkc,
        MCUX_CSSL_FP_CONDITIONAL((operandSize != length),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
}


/**
 * [Design]
 * This function exports a PKC operand (with specified length) and stores it as
 * a big-endian octet string in the target buffer.
 *
 * (0) the PKC operand is stored as a little-endian octet string in PKC workarea;
 * (1) switch the endianness of the string of "aligned length" in-place in the PKC operand buffer,
 *     where "aligned length" is equal to length rounding up to a multiple of CPU word size;
 * (2) copy the result (a big-endian octet string of the specified length, at
 *     (pSource+offset)[], where offset = "aligned length" - length) to the target buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ExportBigEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ExportBigEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ExportBigEndianFromPkc);

    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t * p32Source = MCUXCLPKC_OFFSET2PTRWORD(pOperands[iSource]);  /* Caller shall provide PKC-word aligned operand iSource. */

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("modular arithmetic.")
    uint32_t offset = (0u - length) % (sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("offset in range [0,3], and length <= alignedLength <= PKC PS1LEN.")
    uint32_t alignedLength = length + offset;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    MCUXCLPKC_WAITFORFINISH();

    /* PKC buffer size is a multiple of MCUXCLPKC_WORDSIZE (also CPU wordsize). */
    /* When length is not a multiple of CPU word size (i.e., offset != 0),     */
    /* there will be offset bytes beyond the specified length of the source.   */
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "offset in range [0,3], and length <= alignedLength <= PKC PS1LEN.")
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Source, alignedLength);  /* PKC buffer is CPU word aligned. */
    MCUXCLMEMORY_FP_MEMORY_COPY(pTarget, & ((uint8_t *) p32Source)[offset], length);
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_ExportBigEndianFromPkc,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
}


/**
 * [Design]
 * This function exports a PKC operand (with specified length) and stores it as
 * a little-endian octet string in the target buffer.
 *
 * (0) the PKC operand is stored as a little-endian octet string in PKC workarea;
 * (1) copy the little-endian octet string of the specified length to the target buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ExportLittleEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ExportLittleEndianFromPkc(uint8_t *pTarget, uint8_t iSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ExportLittleEndianFromPkc);

    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    const uint8_t * pSource = MCUXCLPKC_OFFSET2PTR(pOperands[iSource]);

    MCUXCLPKC_WAITFORFINISH();
    MCUXCLMEMORY_FP_MEMORY_COPY(pTarget, pSource, length);

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_ExportLittleEndianFromPkc,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
}


/**
 * [Design]
 * This function imports an integer stored as a big-endian octet string to PKC workarea,
 * in a secure manner.
 *
 * (1) clear the extra space (from the passed length to (PS1 OPLEN)) of the target PKC buffer by CPU;
 * (2) securely copy the string to the target PKC buffer;
 * (3) generate a random string (its length = (PS1 OPLEN)) in the temp PKC buffer;
 * (4) mask (XOR) the target PKC operand with the temp PKC operand;
 * (5) switch the endianness of both strings (target and temp) in-place in the PKC buffers;
 * (6) unmask (XOR) the target PKC operand.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SecureImportBigEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureImportBigEndianToPkc(mcuxClSession_Handle_t pSession, uint16_t iTarget_iTemp, const uint8_t * pSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SecureImportBigEndianToPkc);

    uint8_t iTemp = (uint8_t) (iTarget_iTemp & 0xFFu);
    uint8_t iTarget = (uint8_t) (iTarget_iTemp >> 8);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *p32Temp   = MCUXCLPKC_OFFSET2PTRWORD(pOperands[iTemp]);    /* Caller shall provide PKC-word aligned operand iTemp. */
    uint32_t *p32Target = MCUXCLPKC_OFFSET2PTRWORD(pOperands[iTarget]);  /* Caller shall provide PKC-word aligned operand iTarget. */
    uint8_t *pTarget = (uint8_t* ) p32Target;

    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("length <= operandSize = PKC PS1LEN.")
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_clear(&pTarget[length], operandSize - length, operandSize - length));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    MCUX_CSSL_FP_FUNCTION_CALL(ret_CsslMemoryCopy,
        mcuxCsslMemory_Copy(mcuxCsslParamIntegrity_Protect(4u, pSource, pTarget, length, length),
                           pSource, pTarget, length, length) );
    if (MCUXCSSLMEMORY_STATUS_OK != ret_CsslMemoryCopy)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportBigEndianToPkc, MCUXCLPKC_STATUS_NOK);
    }

#define MCUXCLPKC_SECIMPORTBE_FP_CALLED_MEMCOPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy)

    /* Caution: the whole temp buffer needs to be initialized before PKC XOR */
    /*          if the platform requests an explicit memory initialization.  */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate, mcuxClRandom_ncGenerate(pSession, (uint8_t *) p32Temp, operandSize));
    if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportBigEndianToPkc, MCUXCLPKC_STATUS_NOK);
    }

    MCUXCLPKC_FP_CALC_OP1_XOR(iTarget, iTarget, iTemp);

#ifdef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
    uint32_t alignedLength = (length + (sizeof(uint32_t)) - 1u) & (~ ((sizeof(uint32_t)) - 1u));

    MCUXCLPKC_WAITFORFINISH();

    /* Switch endianness of Temp and Target with aligned length. */
    /* Few (0~3) extra bytes will be moved to the beginning of the strings. */
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Temp,   alignedLength);  /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Target, alignedLength);  /* PKC buffer is CPU word aligned. */

    MCUXCLPKC_FP_CALC_OP1_XOR(iTarget, iTarget, iTemp);

    /* Clear the extra byte(s) by right-shifting. */
    MCUXCLPKC_FP_CALC_OP1_SHR(iTarget, iTarget, (alignedLength - length) * 8u);

#define MCUXCLPKC_SECIMPORTBE_FP_CALLED_REV  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,                         \
    MCUXCLPKC_FP_CALLED_CALC_OP1_SHR
#else
    MCUXCLPKC_WAITFORFINISH();

    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Temp,   length);  /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Target, length);  /* PKC buffer is CPU word aligned. */

    MCUXCLPKC_FP_CALC_OP1_XOR(iTarget, iTarget, iTemp);

#define MCUXCLPKC_SECIMPORTBE_FP_CALLED_REV  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_XOR
#endif /* MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS */

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportBigEndianToPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
        MCUXCLPKC_SECIMPORTBE_FP_CALLED_MEMCOPY,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,
        MCUXCLPKC_SECIMPORTBE_FP_CALLED_REV );
}


/**
 * [Design]
 * This function imports an integer stored as a little-endian octet string to PKC workarea,
 * in a secure manner.
 *
 * (1) clear the extra space (from the passed length to (PS1 OPLEN)) of the target PKC buffer by CPU;
 * (2) securely copy the string to the target PKC buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SecureImportLittleEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureImportLittleEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SecureImportLittleEndianToPkc);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pTarget = MCUXCLPKC_OFFSET2PTR(pOperands[iTarget]);

    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("length <= operandSize = PKC PS1LEN.")
    MCUXCLMEMORY_FP_MEMORY_CLEAR(&pTarget[length], operandSize - length);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    MCUX_CSSL_FP_FUNCTION_CALL(ret_CsslMemoryCopy,
        mcuxCsslMemory_Copy(mcuxCsslParamIntegrity_Protect(4u, pSource, pTarget, length, length),
                           pSource, pTarget, length, length) );
    if (MCUXCSSLMEMORY_STATUS_OK != ret_CsslMemoryCopy)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportLittleEndianToPkc, MCUXCLPKC_STATUS_NOK);
    }

#define MCUXCLPKC_SECIMPORTLE_FP_CALLED_MEMCOPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy)

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportLittleEndianToPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
        MCUXCLPKC_SECIMPORTLE_FP_CALLED_MEMCOPY );
}


/**
 * [Design]
 * This function exports a PKC operand (with specified length) and stores it as
 * a big-endian octet string in the target buffer, in a secure manner.
 *
 * (0) the source PKC operand is stored as a little-endian octet string in PKC workarea;
 * (1) generate a random byte string of the specified length in the temp PKC operand;
 * (2) mask (XOR) the source PKC operand with the temp PKC operand;
 * (3) switch the endianness of both strings (source and temp) in-place in the PKC buffers;
 * (4) unmask (XOR) the source PKC operand;
 * (5) securely copy the result (a big-endian octet string, of the specified length)
 *     to the target buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SecureExportBigEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureExportBigEndianFromPkc(mcuxClSession_Handle_t pSession, uint8_t * pTarget, uint16_t iSource_iTemp, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SecureExportBigEndianFromPkc);

    uint8_t iTemp = (uint8_t) (iSource_iTemp & 0xFFu);
    uint8_t iSource = (uint8_t) (iSource_iTemp >> 8);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *p32Temp   = MCUXCLPKC_OFFSET2PTRWORD(pOperands[iTemp]);    /* Caller shall provide PKC-word aligned operand iTemp. */
    uint32_t *p32Source = MCUXCLPKC_OFFSET2PTRWORD(pOperands[iSource]);  /* Caller shall provide PKC-word aligned operand iSource. */

    MCUXCLPKC_WAITFORFINISH();

    /* Caution: the whole temp buffer needs to be initialized before PKC XOR */
    /*          if the platform requests an explicit memory initialization.  */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate, mcuxClRandom_ncGenerate(pSession, (uint8_t *) p32Temp, operandSize));
    if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportBigEndianFromPkc, MCUXCLPKC_STATUS_NOK);
    }

    MCUXCLPKC_FP_CALC_OP1_XOR(iSource, iSource, iTemp);

#ifdef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
    uint32_t alignedLength = (length + (sizeof(uint32_t)) - 1u) & (~ ((sizeof(uint32_t)) - 1u));

    MCUXCLPKC_WAITFORFINISH();

    /* Switch endianness of Temp and Source with aligned length. */
    /* Few (0~3) extra bytes will be moved to the beginning of the strings. */
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Temp,   alignedLength);  /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Source, alignedLength);  /* PKC buffer is CPU word aligned. */

    MCUXCLPKC_FP_CALC_OP1_XOR(iSource, iSource, iTemp);

    /* Clear the extra byte(s) by right-shifting. */
    MCUXCLPKC_FP_CALC_OP1_SHR(iSource, iSource, (alignedLength - length) * 8u);

#define MCUXCLPKC_SECEXPORTBE_FP_CALLED_REV  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,                         \
    MCUXCLPKC_FP_CALLED_CALC_OP1_SHR
#else
    MCUXCLPKC_WAITFORFINISH();

    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Temp,   length);  /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_SWITCHENDIANNESS(p32Source, length);  /* PKC buffer is CPU word aligned. */

    MCUXCLPKC_FP_CALC_OP1_XOR(iSource, iSource, iTemp);

#define MCUXCLPKC_SECEXPORTBE_FP_CALLED_REV  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),  \
    MCUXCLPKC_FP_CALLED_CALC_OP1_XOR
#endif

    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(ret_CsslMemoryCopy,
        mcuxCsslMemory_Copy(mcuxCsslParamIntegrity_Protect(4u, (const uint8_t *) p32Source, pTarget, length, length),
                           (const uint8_t *) p32Source, pTarget, length, length) );
    if (MCUXCSSLMEMORY_STATUS_OK != ret_CsslMemoryCopy)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportBigEndianFromPkc, MCUXCLPKC_STATUS_NOK);
    }

#define MCUXCLPKC_SECEXPORTBE_FP_CALLED_MEMCOPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy)

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportBigEndianFromPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,
        MCUXCLPKC_SECEXPORTBE_FP_CALLED_REV,
        MCUXCLPKC_SECEXPORTBE_FP_CALLED_MEMCOPY );
}


/**
 * [Design]
 * This function exports a PKC operand (with specified length) and stores it as
 * a little-endian octet string in the target buffer, in a secure manner.
 *
 * (0) the PKC operand is stored as a little-endian octet string in PKC workarea;
 * (1) securely copy the little-endian octet string of the specified length to the target buffer.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SecureExportLittleEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureExportLittleEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SecureExportLittleEndianFromPkc);

    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    const uint8_t * pSource = MCUXCLPKC_OFFSET2PTR(pOperands[iSource]);

    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(ret_CsslMemoryCopy,
        mcuxCsslMemory_Copy(mcuxCsslParamIntegrity_Protect(4u, pSource, pTarget, length, length),
                           pSource, pTarget, length, length) );
    if (MCUXCSSLMEMORY_STATUS_OK != ret_CsslMemoryCopy)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportLittleEndianFromPkc, MCUXCLPKC_STATUS_NOK);
    }

#define MCUXCLPKC_SECEXPORTLE_FP_CALLED_MEMCOPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy)

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportLittleEndianFromPkc, MCUXCLPKC_STATUS_OK,
        MCUXCLPKC_SECEXPORTLE_FP_CALLED_MEMCOPY );
}
