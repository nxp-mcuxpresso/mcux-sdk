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
 * @file  mcuxClPkc_ImportExport.c
 * @brief mcuxClPkc: implementation of PKC internal import/export functions
 */


#include <stdint.h>
#include <toolchain.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClCss_Rng.h>
#include <mcuxClMemory.h>

#include <mcuxClPkc.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>


/** Helper macro to call #mcuxClMemory_copy with flow protection. */
#define MCUXCLPKC_FP_MEMORY_COPY(pTarget, pSource, byteLen)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retCodeTemp,  \
            mcuxClMemory_copy((uint8_t *) (pTarget), (const uint8_t *) (pSource), byteLen, byteLen)); \
        (void) retCodeTemp;  \
    } while(false)


/** Implementation of PKC internal import/export functions. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SwitchEndianness)
mcuxClPkc_Status_Protected_t mcuxClPkc_SwitchEndianness(uint32_t *ptr, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SwitchEndianness);

    uint32_t *ptrL32 = ptr;
    /* MISRA Ex. 9 - Rule 11.3 - Use of UNALIGNED keyword. */
    uint32_t UNALIGNED *ptrH32 = (uint32_t UNALIGNED *) ((uint8_t *) ptr + length - 4u);

    /* While there are >= 4 bytes to switch the endianness. */
    while (ptrH32 >= ptrL32)
    {
        uint32_t wordL = *ptrL32;
        uint32_t wordH = *ptrH32;

        wordL = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(wordL);
        wordH = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(wordH);

        *ptrH32 = wordL;
        ptrH32--;
        *ptrL32 = wordH;
        ptrL32++;
    }

    /* If ptrH <= ptrL - 4, nothing more to do. */
    /* If ptrH == ptrL - 3, swap ptrL[0] with ptrH[3] = ptrL[0], i.e., nothing to do. */
    /* If ptrH == ptrL - 2, swap ptrL[0] with ptrH[3] = ptrL[1]. */
    /* If ptrH == ptrL - 1, swap ptrL[0] with ptrH[3] = ptrL[2], and leave ptrL[1] unchanged. */
    uint8_t *ptrL8 = (uint8_t *) ptrL32;
    uint8_t *ptrH8 = (uint8_t *) ptrH32 + 3u;
    if (ptrH8 > ptrL8)
    {
        uint8_t byteL = *ptrL8;
        uint8_t byteH = *ptrH8;

        *ptrH8 = byteL;
        *ptrL8 = byteH;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SwitchEndianness, MCUXCLPKC_STATUS_OK);
}


/** This function imports a big-endian octet string with specified length and stores it in PKC workarea.
 *
 * Inputs:
 *   iTarget: index of PKC operand, where the integer converted from the octet string will be stored;
 *   pSource: address of the octet string to be imported;
 *   length: length of the octet string to be imported.
 *
 * Inputs in pOperands[] and PKC workarea: N/A
 *
 * Prerequisites: N/A
 *
 * Result in PKC workarea:
 *   buffer iTarget contains the integer converted from the imported octet string.
 *
 * Other modifications: N/A
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ImportBigEndianToPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_ImportBigEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ImportBigEndianToPkc);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t * pTarget = MCUXCLPKC_OFFSET2PTR(pOperands[iTarget]);

    if (operandSize != length)
    {
        MCUXCLPKC_FP_CALC_OP1_CONST(iTarget, 0u);
    }
    MCUXCLPKC_WAITFORFINISH();

    MCUXCLPKC_FP_MEMORY_COPY(pTarget, pSource, length);
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pTarget, length);  /* PKC buffer is CPU word aligned. */

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_ImportBigEndianToPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_CONDITIONAL((operandSize != length),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness) );
}


/** This function exports an integer stored in PKC workarea to be a big-endian octet string.
 *
 * Inputs:
 *   pTarget: address of the buffer where the octet string will be stored;
 *   iSource: index of PKC operand to be exported;
 *   length: length of the octet string to be exported.
 *
 * Inputs in pOperands[] and PKC workarea:
 *   the first length bytes of buffer iSource contain the integer to be exported.
 *
 * Prerequisites: N/A
 *
 * Result in PKC workarea: N/A
 *
 * Other modifications:
 *   the integer stored in first length bytes of buffer iTarget will be converted to big-endian octet string.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ExportBigEndianFromPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_ExportBigEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_ExportBigEndianFromPkc);

    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t * pSource = MCUXCLPKC_OFFSET2PTR(pOperands[iSource]);

    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pSource, length);  /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_MEMORY_COPY(pTarget, pSource, length);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_ExportBigEndianFromPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
}


/** This function securely imports a big-endian octet string with specified length and stores it in PKC workarea.
 *
 * Inputs:
 *   iTarget: index of PKC operand, where the integer converted from the octet string will be stored;
 *   pSource: address of the octet string to be imported;
 *   iTemp: index of PKC buffer as temp;
 *   length: length of the octet string to be imported.
 *
 * Inputs in pOperands[] and PKC workarea: N/A
 *
 * Prerequisites:
 *   ps1 OPLEN should be set and longer than length.
 *
 * Result in PKC workarea:
 *   buffer iTarget contains the integer converted from the imported octet string;
 *   buffer iTemp contains a length-byte random number.
 *
 * Other modifications: N/A
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SecureImportBigEndianToPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_SecureImportBigEndianToPkc(uint16_t iTarget_iTemp, const uint8_t * pSource, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SecureImportBigEndianToPkc);

    uint8_t iTemp = (uint8_t) (iTarget_iTemp & 0xFFu);
    uint8_t iTarget = (uint8_t) (iTarget_iTemp >> 8);

    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pTemp   = MCUXCLPKC_OFFSET2PTR(pOperands[iTemp]);
    uint8_t *pTarget = MCUXCLPKC_OFFSET2PTR(pOperands[iTarget]);

    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL(ret_MemoryClear, mcuxClMemory_clear(& pTarget[length], operandSize - length, operandSize - length));
    (void) ret_MemoryClear;
    MCUXCLPKC_FP_MEMORY_COPY(pTarget, pSource, length);  /* TODO: CLNS-1173, use secure memory copy (blocked by CLNS-1121). */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClCss_Prng_GetRandom(pTemp, length));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportBigEndianToPkc, MCUXCLPKC_STATUS_NOK);
    }

    MCUXCLPKC_FP_CALC_OP1_XOR(iTarget, iTarget, iTemp);

    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pTemp, length);    /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pTarget, length);  /* PKC buffer is CPU word aligned. */

    MCUXCLPKC_FP_CALC_OP1_XOR(iTarget, iTarget, iTemp);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureImportBigEndianToPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUXCLPKC_FP_CALLED_CALC_OP1_XOR );
}


/** This function securely exports an integer stored in PKC workarea to be a big-endian octet string.
 *
 * Inputs:
 *   pTarget: address of the buffer where the octet string will be stored;
 *   iSource: index of PKC operand to be exported;
 *   iTemp: index of PKC buffer as temp;
 *   length: length of the octet string to be exported.
 *
 * Inputs in pOperands[] and PKC workarea:
 *   the first length bytes of buffer iSource contain the integer to be exported.
 *
 * Prerequisites:
 *   ps1 OPLEN should be set and longer than length.
 *
 * Result in PKC workarea: N/A
 *
 * Other modifications:
 *   the integer stored in first length bytes of buffer iTarget will be converted to big-endian octet string.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_SecureExportBigEndianFromPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_SecureExportBigEndianFromPkc(uint8_t * pTarget, uint16_t iSource_iTemp, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_SecureExportBigEndianFromPkc);

    uint8_t iTemp = (uint8_t) (iSource_iTemp & 0xFFu);
    uint8_t iSource = (uint8_t) (iSource_iTemp >> 8);

    const uint16_t * pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pTemp   = MCUXCLPKC_OFFSET2PTR(pOperands[iTemp]);
    uint8_t *pSource = MCUXCLPKC_OFFSET2PTR(pOperands[iSource]);

    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClCss_Prng_GetRandom(pTemp, length));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportBigEndianFromPkc, MCUXCLPKC_STATUS_NOK);
    }

    MCUXCLPKC_FP_CALC_OP1_XOR(iSource, iSource, iTemp);

    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pTemp, length);    /* PKC buffer is CPU word aligned. */
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pSource, length);  /* PKC buffer is CPU word aligned. */

    MCUXCLPKC_FP_CALC_OP1_XOR(iSource, iSource, iTemp);

    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_FP_MEMORY_COPY(pTarget, pSource, length);  /* TODO: CLNS-1173, use secure memory copy (blocked by CLNS-1121). */

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_SecureExportBigEndianFromPkc, MCUXCLPKC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUXCLPKC_FP_CALLED_CALC_OP1_XOR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
}
