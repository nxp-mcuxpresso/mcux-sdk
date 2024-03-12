/*--------------------------------------------------------------------------*/
/* Copyright 2018-2024 NXP                                                  */
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

/*
 * @file: mcuxClOsccaSm2_CryptoUtils.c
 * @brief: OSCCA SM2 Crypto Utils functions
 */

#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClSession.h>
#include <mcuxClMemory.h>
#include <mcuxClHash.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClRandom.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClOsccaSm2_Internal_Hash.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>
#include <internal/mcuxClOsccaSm2_Internal_CryptoUtils.h>
#include <mcuxClCrc.h>
#include <internal/mcuxClBuffer_Internal.h>

/** Key Derivation Function needed by SM2 enc and dec
 * Calculates the key used for encrypting the message
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_KDF)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_KDF(mcuxClSession_Handle_t session, mcuxClOsccaSm2_KDF_Param_t *pKDFParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_KDF);
    uint32_t remainingLength = pKDFParam->keyLength;
    uint32_t counter = 0U;
    uint32_t outOffset = 0U;

    /* Add length to Security Counter */
    MCUX_CSSL_SC_ADD((uint32_t)(remainingLength));

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pCtx = (mcuxClHash_Context_t)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if (NULL == pCtx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_FAIL);
    }
    /* Hash X2||Y2 */
    uint32_t hashRet = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHINITPRO(session, pCtx, mcuxClOsccaSm3_Algorithm_Sm3, pKDFParam->pX2, pKDFParam->domainParameters.p.wNumBytes, hashRet);
    if(MCUXCLHASH_STATUS_OK != hashRet)
    {
        /* don't balance SC because it will return fault attack in caller */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_FAIL);
    }

    uint32_t hashPro = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx, pKDFParam->pY2, pKDFParam->domainParameters.p.wNumBytes, hashPro);
    if(MCUXCLHASH_STATUS_OK != hashPro)
    {
        /* don't balance SC because it will return fault attack in caller */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_FAIL);
    }

    /* for key exchange */
    hashPro = MCUXCLHASH_STATUS_FAULT_ATTACK;
    if ((NULL != pKDFParam->pZA) && (NULL != pKDFParam->pZB))
    {
        MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx, pKDFParam->pZA, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, hashPro);
        if(MCUXCLHASH_STATUS_OK != hashPro)
        {
            /* don't balance SC because it will return fault attack in caller */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_FAIL);
        }

        MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx, pKDFParam->pZB, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, hashPro);
        if(MCUXCLHASH_STATUS_OK != hashPro)
        {
            /* don't balance SC because it will return fault attack in caller */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_FAIL);
        }

    }
    else
    {
        // Do nothing, just balance to avoid misra violation.
    }

    /* Backup HashCtx */
    MCUXCLOSCCASM2_FP_CONTEXT_HASHCOPY(pKDFParam->hashCtxBackup, pCtx);

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(remainingLength, 1u, UINT32_MAX - 1u, MCUXCLCIPHER_STATUS_INVALID_INPUT)
    while(remainingLength > 0u)
    {
        /* Determine if full block length is needed, or if the last block is processed */
        uint32_t neededLength = remainingLength >= MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 ? MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 : remainingLength;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Counter can't wrap because it's smaller then remainingLength.")
        counter++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

        /* Change endianes of counter since Hash requires big endian as input */
        uint32_t bigEndianCounter = MCUXCLOSCCASM2_SWAP32(counter);

        uint32_t hashFin = MCUXCLHASH_STATUS_FAULT_ATTACK;
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pCtx->unprocessedLength, 0u, 64u, MCUXCLOSCCASM2_STATUS_KDF_FAIL)
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("pCtx is always valid pointer")
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_ESCAPING_LOCAL_ADDRESS("Address of bigEndianCounter is for internal use only and does not escape")
        MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pCtx, (uint8_t*) &bigEndianCounter, sizeof(bigEndianCounter), pKDFParam->tempHashState, hashFin);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ESCAPING_LOCAL_ADDRESS()
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()
        if(MCUXCLHASH_STATUS_OK != hashFin)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_FAIL);
        }

        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("outOffset is always smaller than remainingLength, never overflow.")
        MCUX_CSSL_FP_FUNCTION_CALL(writeStatus, mcuxClBuffer_write(pKDFParam->pKeyBuffer, outOffset, pKDFParam->tempHashState, neededLength));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        /* Don't check the return value since it always return OK */
        (void)writeStatus;

        /* Restore previous HashCtx */
        MCUXCLOSCCASM2_FP_CONTEXT_HASHCOPY(pCtx, pKDFParam->hashCtxBackup);

        /* Decrease loop counter and increase the output pointer*/
        remainingLength -= neededLength;
        outOffset += neededLength;
    }

    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    /*
     * Balance the security counter
     */
    counter = MCUXCLOSCCASM2_CEILING((uint32_t)pKDFParam->keyLength, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3);
    MCUX_CSSL_SC_SUB(outOffset);

    /* Subtract Key and Message pointer from Security counter */
    /* security counter will only be balanced if no loop iteration was skipped */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KDF, MCUXCLOSCCASM2_STATUS_KDF_OK,
                                            2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                            2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                            MCUX_CSSL_FP_CONDITIONAL((NULL != pKDFParam->pZA && NULL != pKDFParam->pZB),
                                                2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)),
                                            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                            counter * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write)
                                                     + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
}

/***************************************************************/
/**   Validate Context for SM2 Encryption or Decryption       **/
/***************************************************************/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_ValidateEncDecCtx)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_ValidateEncDecCtx(
        mcuxClOsccaSm2_Internal_EncDecCtx_t *pCtx,
        uint32_t pLen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_ValidateEncDecCtx);

    MCUX_CSSL_ANALYSIS_COVERITY_ASSERT(pLen, 1u, 80u, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL)
    MCUX_CSSL_FP_FUNCTION_CALL(crcVal, mcuxClCrc_computeCRC16((uint8_t*)&(pCtx)->crc + sizeof(uint16_t),
                                                    (uint32_t)offsetof(mcuxClOsccaSm2_Internal_EncDecCtx_t, tZeroOrNot) + sizeof(uint16_t) + (pLen)
                                                    - (offsetof(mcuxClOsccaSm2_Internal_EncDecCtx_t, crc) + sizeof(uint16_t))));
    if(crcVal != pCtx->crc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ValidateEncDecCtx,MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }

    if((MCUXCLOSCCASM2_T_ZERO != pCtx->tZeroOrNot) && (MCUXCLOSCCASM2_T_NOT_ZERO != pCtx->tZeroOrNot))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ValidateEncDecCtx,MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ValidateEncDecCtx, MCUXCLOSCCASM2_STATUS_VALIDATE_ENCDEC_CTX_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCrc_computeCRC16));
}

/***************************************************************************************************************/
/**   This function performs several operations required in the init phase of SM2 Encryption Decryption       **/
/***************************************************************************************************************/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_SecondPartOfInitPhase)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_SecondPartOfInitPhase(
        mcuxClSession_Handle_t session,
        uint32_t primeLength,
        uint8_t const*pX2, mcuxClOsccaSm2_Internal_EncDecCtx_t *pCtx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_SecondPartOfInitPhase);

    uint8_t *pY2 = (uint8_t *)mcuxClOscca_alignAddressWithOffset(pCtx, sizeof(mcuxClOsccaSm2_Internal_EncDecCtx_t));
    uint32_t hashRet = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHINITPRO(session, pCtx->hashCtxC3, mcuxClOsccaSm3_Algorithm_Sm3, pX2, primeLength, hashRet);
    if(MCUXCLHASH_STATUS_OK != hashRet)
    {
        /* needn't balance SC because it will return fault attack in caller */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SecondPartOfInitPhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }

    /* Securely copy HashCtxC3 to a hash context HashCtxT inside EncDecCtx */
    MCUXCLOSCCASM2_FP_CONTEXT_HASHCOPY(pCtx->hashCtxT, pCtx->hashCtxC3);

    /* Change context inside pHashParams for C2 and update it with y2 */
    uint32_t hashPro = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx->hashCtxT, pY2, primeLength, hashPro);
    if(MCUXCLHASH_STATUS_OK != hashPro)
    {
        /* needn't balance SC because it will return fault attack in caller */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SecondPartOfInitPhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }

    /*Initialize the rest of ctx fields which will be used later */
    pCtx->kdfCounter = 0u;
    pCtx->unusedBytesInKdfCache = 0u;
    pCtx->tZeroOrNot = MCUXCLOSCCASM2_T_ZERO;

    /* Initialize KdfCache with random data. Declare 8-bit pointer to allow bytewise access */
    MCUX_CSSL_FP_FUNCTION_CALL(randCryptoRet, mcuxClRandom_ncGenerate(session, (uint8_t*) pCtx->kdfCache, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if (MCUXCLRANDOM_STATUS_OK != randCryptoRet)
    {
        /* needn't balance SC because it will return fault attack in caller */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SecondPartOfInitPhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SecondPartOfInitPhase, MCUXCLOSCCASM2_STATUS_SECOND_PART_INIT_OK,
                                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
}


/****************************************************************************/
/**   Shared operations of update phase of SM2 Encryption and Decryption   **/
/****************************************************************************/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EncDec_UpdatePhase_Common)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EncDec_UpdatePhase_Common(
        mcuxClSession_Handle_t session,
        mcuxClOsccaSm2_Internal_EncDecCtx_t *pCtx,
        uint8_t *pTemp1,
        uint32_t xorLen,
        uint32_t offset,
        uint32_t functionCode)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EncDec_UpdatePhase_Common);

    /*
     * PKC workarea layout
     * pTemp1 || pHashCtxT(pTemp2)
     */
    /* Reserve space for the hash context workarea for KDF */
    uint8_t *pTemp2 = pTemp1 + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;

    /* Declare 8-bit pointer, to allow bytewise access of pCtx->kdfCache and pCtx->kdfMask */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    uint8_t *pKdfCache = (uint8_t*) pCtx->kdfCache;
    uint8_t *pKdfMask = (uint8_t*) pCtx->kdfMask;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* During encryption the plaintext, which is needed for the C3 computation, is passed from the user; Decryption needs to retrieve the plaintext first*/
    if(MCUXCLOSCCASM2_ENCRYPT == functionCode)
    {
        /* Hash the plaintext for C3 computation */
        uint32_t hashPro = MCUXCLHASH_STATUS_FAULT_ATTACK;
        MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx->hashCtxC3, pTemp1, xorLen, hashPro);
        if(MCUXCLHASH_STATUS_OK != hashPro)
        {
            /* needn't balance SC because it will return fault attack in caller */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase_Common, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
        }

        /* Copy pTemp1 into Pkc memory buffer; after XOR of plaintext and kdfCache, compare 2 ciphertexts; if non equal -> FA, else go through */
        /* XOR plaintext with kdfMask */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pTemp2, mcuxClOscca_alignAddress(pTemp1), (((uint8_t*) pCtx->kdfMask) + offset), xorLen));

        /* XOR plaintext with kdfMask */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pTemp1, pTemp1, (&pKdfMask[offset]), xorLen));

        /* Compute ciphertext No.1 */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pTemp1, pTemp1, (&pKdfCache[offset]), xorLen));

        /* Compute ciphertext No.2 */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pTemp2, pTemp2, (&pKdfCache[offset]), xorLen));

        MCUX_CSSL_FP_FUNCTION_CALL(SM2EDComBoRet1, mcuxClOsccaSm2_RobustCompareBoolean(pTemp1, pTemp2, xorLen));
        if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2EDComBoRet1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase_Common, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
        }
    }
    else
    {
        /* After this XOR, pTemp1 contains masked plaintext */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pTemp1, pTemp1, (&pKdfCache[offset]), xorLen));

        /* Unmask plaintext and be ready to export it to the user*/
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pTemp1, pTemp1, (pKdfMask + offset), xorLen));

        /* Use unmasked plaintext for part of C3 calculation */
        uint32_t hashPro2 = MCUXCLHASH_STATUS_FAULT_ATTACK;
        MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx->hashCtxC3, pTemp1, xorLen, hashPro2);
        if(MCUXCLHASH_STATUS_OK != hashPro2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase_Common, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
        }

        /* balance the SC */
        MCUX_CSSL_SC_ADD((uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL + xorLen + (uint32_t)pTemp2 + (uint32_t)pTemp1);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2EDComBoRet2, mcuxClOsccaSm2_RobustCompareBoolean(&pKdfCache[offset], &pKdfMask[offset], xorLen));
    /* Securely and robustly compare kdfCache to zero. In case t' !=?0, set tZeroOrNot := MCUXCLOSCCASM2_T_NOT_ZERO. Done by comparing kdfCache to kdfMask */
    if (MCUXCLOSCCASM2_STATUS_NOT_EQUAL == SM2EDComBoRet2)
    {
        pCtx->tZeroOrNot = MCUXCLOSCCASM2_T_NOT_ZERO;
    }

    MCUX_CSSL_SC_SUB((uint32_t)SM2EDComBoRet2 + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL
                     + (uint32_t)pTemp2 + (uint32_t)pTemp1 + 2u * xorLen
                     + (uint32_t) (&pKdfCache[offset]) + (uint32_t) (&pKdfMask[offset]));


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase_Common, MCUXCLOSCCASM2_STATUS_ENCDEC_PHASE_OK,
                                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                                  MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM2_ENCRYPT == functionCode),
                                                                       4U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor),
                                                                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean)),
                                                                  MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM2_DECRYPT == functionCode),
                                                                       2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)),
                                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
}

MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_DEFINED("It is indeed defined.")
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEFINED_MORE_THAN_ONCE("It defined only once.")
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EncDec_UpdatePhase)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EncDec_UpdatePhase(
        mcuxClSession_Handle_t session,
        mcuxClOsccaSm2_EncDec_Common_Param_t *pParams,
        uint32_t functionCode)
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEFINED_MORE_THAN_ONCE()
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_DEFINED()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EncDec_UpdatePhase);

    /* Allocate workarea usage in mcuxClOsccaSm2_EncDec_UpdatePhase */
    uint8_t *pPkcWa = (uint8_t*)mcuxClSession_allocateWords_pkcWa(session, (MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 + MCUXCLOSCCASM3_CONTEXT_SIZE) / sizeof(uint32_t));
    if(NULL == pPkcWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }
    /* Declare local variables which will be set depending on the functionCode */
    uint32_t remainingLength = 0U;
    mcuxCl_InputBuffer_t pSrcBuf = NULL;
    mcuxCl_Buffer_t pDestBuf = NULL;
    uint32_t scFlags = 0u;
    uint32_t outOffset = 0u;
    uint32_t inOffset = 0u;

    if(MCUXCLOSCCASM2_ENCRYPT == functionCode)
    {
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        remainingLength = ((mcuxClOsccaSm2_Encrypt_Param_t *)pParams)->inputLength;
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pSrcBuf = ((mcuxClOsccaSm2_Encrypt_Param_t *)pParams)->pInput;
        pDestBuf = ((mcuxClOsccaSm2_Encrypt_Param_t *)pParams)->pOutput;
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    }
    else if(MCUXCLOSCCASM2_DECRYPT == functionCode)
    {
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        remainingLength = ((mcuxClOsccaSm2_Decrypt_Param_t *)pParams)->inputLength;
        pSrcBuf = ((mcuxClOsccaSm2_Decrypt_Param_t *)pParams)->pInput;
        pDestBuf = ((mcuxClOsccaSm2_Decrypt_Param_t *)pParams)->pOutput;
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    }
    else
    {
        /* If different functionCode, return FAULT_ATTACK */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }
    /* Check the length of the message to be processed; length == 0 is not accepted */
    if(0u == remainingLength)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
    }

    /* In each round xorLen is subtracted from SC; at the end pDest and pSrc are added to SC */
    /* The caller must subtract address of pInput, address of pOutput and input length from SC for it to be balanced */

    /*
     * PKC workarea layout
     * pTemp1 || pHashCtxT(pTemp2)
     */
    uint8_t *pTemp1 = mcuxClOscca_alignAddress(pPkcWa);
    mcuxClOsccaSm2_Internal_EncDecCtx_t *pCtx = (mcuxClOsccaSm2_Internal_EncDecCtx_t *)pParams->pEncDecCtx;

    /* Reserve space for the hash context workarea for KDF */
    uint8_t *pHashCtxT = pTemp1 + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;

    /* Declare variable for processed length within each round of loop */
    uint32_t xorLen = 0u;
    uint32_t unusedBytes = pCtx->unusedBytesInKdfCache;
    uint32_t loopTimes1 = 0U;
    if(0u < unusedBytes)
    {
        xorLen = MCUXCLCORE_MIN(remainingLength, pCtx->unusedBytesInKdfCache);

        /*Copy chunk of the plaintext/cipertext to perform encryption/decryption and compute part of C3*/
        MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read(pSrcBuf, inOffset, pTemp1, xorLen));
        /* Don't check the return value since it always return OK */
        (void)readStatus;

        MCUX_CSSL_FP_FUNCTION_CALL(updateComRet, mcuxClOsccaSm2_EncDec_UpdatePhase_Common(session, pCtx, pTemp1, xorLen, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 - pCtx->unusedBytesInKdfCache, functionCode));
        if(MCUXCLOSCCASM2_STATUS_ENCDEC_PHASE_OK != updateComRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, updateComRet);
        }

        /* Copy chunk of ciphertext/plaintext back to the user */
        MCUX_CSSL_FP_FUNCTION_CALL(writeStatus, mcuxClBuffer_write(pDestBuf, outOffset, pTemp1, xorLen));
        /* Don't check the return value since it always return OK */
        (void)writeStatus;
        outOffset += xorLen;
        inOffset += xorLen;
        remainingLength -= xorLen;
        pCtx->unusedBytesInKdfCache -= xorLen;

    } /* End of if(0u < pCtx->unusedBytesInKdfCache) */

    uint32_t bigEndianCounter = 0u;

    /* With every call to UPDATE, KdfMask is set to random data. */
    if(0u == pCtx->unusedBytesInKdfCache)
    {
        scFlags++;
        /* In case pCtx->unusedBytesInKdfCache is zero set KdfMask to random data */
        MCUX_CSSL_FP_FUNCTION_CALL(randCryptoRet, mcuxClRandom_ncGenerate(session, (uint8_t*) pCtx->kdfMask, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
        if (MCUXCLRANDOM_STATUS_OK != randCryptoRet)
        {
            /* needn't balance SC because it will return fault attack in caller */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
        }
    }
    else
    {
        // Do nothing, just balance to avoid misra violation.
    }

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(remainingLength, 1u, (uint32_t)UINT16_MAX - 1u, MCUXCLCIPHER_STATUS_INVALID_INPUT)
    while(0u < remainingLength)
    {
        loopTimes1++;
        /* Increase kdfCounter for kdf computation */
        pCtx->kdfCounter += 1u;
        /* Securely initialize the HashCtx for KDF calculation, it will have to be restored after each round*/
        /* set hash context as backup instance, will be reuse in each hash finalize for KDF*/
        MCUXCLOSCCASM2_FP_CONTEXT_HASHCOPY(pHashCtxT, pCtx->hashCtxT);

        /* Update KDF with counter string and perform Hashing with FINALIZE*/
        bigEndianCounter = MCUXCLOSCCASM2_SWAP32(pCtx->kdfCounter);

        uint32_t hashFin = MCUXCLHASH_STATUS_FAULT_ATTACK;
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pCtx->unprocessedLength, 0u, 64u, MCUXCLOSCCASM2_STATUS_KDF_FAIL)
        MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pHashCtxT, (uint8_t*) &bigEndianCounter, sizeof(uint32_t), pTemp1, hashFin);
        if(MCUXCLHASH_STATUS_OK != hashFin)
        {
            /* needn't balance SC because it will return fault attack in caller */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, MCUXCLOSCCASM2_STATUS_ENCDEC_INTERNAL_FAIL);
        }

        /*current loop state will proceed full block or last, not aligned block */
        xorLen = MCUXCLCORE_MIN(remainingLength, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3);

        /* Mask output from kdf from pTemp1 and put it into pCtx->kdfCache, kdfMask is already in place */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor((uint8_t*) pCtx->kdfCache, pTemp1, (uint8_t*) pCtx->kdfMask, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));

        /*Import chunk of the plaintext/cipertext to perform encryption/decryption and compute part of C3*/
        MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read(pSrcBuf, inOffset, pTemp1, xorLen));
        /* Don't check the return value since it always return OK */
        (void)readStatus;
        MCUX_CSSL_FP_FUNCTION_CALL(updateComRet, mcuxClOsccaSm2_EncDec_UpdatePhase_Common(session, pCtx, pTemp1, xorLen, 0U, functionCode));
        if(MCUXCLOSCCASM2_STATUS_ENCDEC_PHASE_OK != updateComRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, updateComRet);
        }
        /*Export chunk of ciphertext back to the user*/
        MCUX_CSSL_FP_FUNCTION_CALL(writeStatus, mcuxClBuffer_write(pDestBuf, outOffset, pTemp1, xorLen));
        /* Don't check the return value since it always return OK */
        (void)writeStatus;
        remainingLength -= xorLen;
        outOffset += xorLen;
        inOffset += xorLen;

        /* Update unusedBytesInKdfCache for next UPDATE call by number of unused bytes already generated by KDF*/
        pCtx->unusedBytesInKdfCache = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 - xorLen;
    }

    /* Free workarea allocated in mcuxClOsccaSm2_EncDec_UpdatePhase */
    mcuxClSession_freeWords_pkcWa(session, (MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 + MCUXCLOSCCASM3_CONTEXT_SIZE) / sizeof(uint32_t));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_UpdatePhase, MCUXCLOSCCASM2_STATUS_ENCDEC_PHASE_OK,
                                                                scFlags * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                                                MCUX_CSSL_FP_CONDITIONAL((unusedBytes > 0U), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                                                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),
                                                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EncDec_UpdatePhase_Common)),
                                                                loopTimes1 * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)
                                                                   + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)
                                                                   + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)
                                                                   + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
                                                                   + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)
                                                                   + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write)
                                                                   + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EncDec_UpdatePhase_Common)));

}
