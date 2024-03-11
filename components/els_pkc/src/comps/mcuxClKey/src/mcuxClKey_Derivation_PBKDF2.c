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

/** @file  mcuxClKey_Derivation_PBKDF2.c
 *  @brief Implementation of PBKDF2 Key Derivation */

#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClMemory.h>
#include <mcuxClBuffer.h>
#include <mcuxClSession.h>
#include <mcuxClKey.h>
#include <mcuxClMac.h>
#include <mcuxClHmac.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClMac_Internal_Constants.h>
#include <internal/mcuxClHmac_Internal_Types.h>


/**
 * @brief Simple unsecure xor of two buffers of the same size.
 * 
 * @param[out]  pDst        Destination buffer
 * @param[in]   pSrc1       First source buffer
 * @param[in]   pSrc2       Second source buffer
 * @param[in]   length      Byte length of source and destination
 * 
 * @details There are no length checks in place. Ensure no buffer is shorter than length
 */
static inline void mcuxClKey_derivation_xor_buffers(uint8_t* pDst, const uint8_t* pSrc1, const uint8_t* pSrc2, uint32_t length)
{
    for(uint32_t i = 0u; i < length; i++)
    {
        pDst[i] = pSrc1[i] ^ pSrc2[i];
    }
}

/**
 * @brief Computes a HMAC digest using the mcuxClMac API
 * 
 * @param[in]   pSession 
 * @param[in]   hmacMode    Mac mode to be used, must be an Hmac mode
 * @param[in]   hmacKey     Key to be used for the Hmac computation
 * @param[in]   salt        The salt will form the first part of the input for the Hmac computation
 * @param[in]   pIndex      pIndex will form the second part of the input for the Hmac computation. Must be 4 Byte in size.
 * @param[out]  pOutput     Output buffer to store the computed digest. Must be large enough to hold a digest according to hmacMode.
 * 
 * @details 
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_derivation_pbkdf2_computeHmac)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivation_pbkdf2_computeHmac(
    mcuxClSession_Handle_t       pSession,
    mcuxClMac_Mode_t             hmacMode,
    mcuxClKey_Handle_t           hmacKey,
    mcuxClKey_DerivationInput_t  salt,
    uint8_t *                   pIndex,
    uint8_t *                   pOutput
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_derivation_pbkdf2_computeHmac);
    /* Allocate space for the MAC context. */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClMac_Context_t *hmacContext =  (mcuxClMac_Context_t *) mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == hmacContext)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivation_pbkdf2_computeHmac, MCUXCLKEY_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(init_result, mcuxClMac_init(
        pSession,
        hmacContext,
        hmacKey,
        hmacMode));
    if(MCUXCLMAC_STATUS_OK != init_result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivation_pbkdf2_computeHmac, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    /* Process the salt. */
    MCUX_CSSL_FP_FUNCTION_CALL(process_result1, mcuxClMac_process(
            pSession,
            hmacContext,
            salt.input,
            salt.size
    ));
    if(MCUXCLMAC_STATUS_OK != process_result1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivation_pbkdf2_computeHmac, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    /* Process the input */
    MCUXCLBUFFER_INIT_RO(pIndexBuf, pSession, pIndex, sizeof(uint32_t));
    MCUX_CSSL_FP_FUNCTION_CALL(process_result2, mcuxClMac_process(
            pSession,
            hmacContext,
            pIndexBuf,
            sizeof(uint32_t)
    ));
    if(MCUXCLMAC_STATUS_OK != process_result2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivation_pbkdf2_computeHmac, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    uint32_t outSize = 0u;

    /* Create the digest. */
    MCUXCLBUFFER_INIT(pOutputBuf, pSession, pOutput, sizeof(uint32_t));
    MCUX_CSSL_FP_FUNCTION_CALL(finish_result, mcuxClMac_finish(
            pSession,
            hmacContext,
            pOutputBuf,
            &outSize
    ));
    if(MCUXCLMAC_STATUS_OK != finish_result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivation_pbkdf2_computeHmac, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    /* clean-up the CPU work-area: hmacContext */
    mcuxClSession_freeWords_cpuWa(pSession, MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivation_pbkdf2_computeHmac, MCUXCLKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
        2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_Derivation_ModeConstructor_PBKDF2)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Derivation_ModeConstructor_PBKDF2(
    mcuxClKey_DerivationMode_t * pDerivationMode,
    const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm,
    mcuxClMac_Mode_t macMode,
    uint32_t iterationCount)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_Derivation_ModeConstructor_PBKDF2);

    pDerivationMode->derivationAlgorithm = derivationAlgorithm;
    pDerivationMode->macMode = macMode;
    pDerivationMode->options = iterationCount;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_Derivation_ModeConstructor_PBKDF2, MCUXCLKEY_STATUS_OK);
}


/**
 * @brief Top-level function of the implementation of PBKDF2 Key Derivation
 * 
 * @param[in]   pSession
 * @param[in]   derivationMode      Mode that specifies algorithm details
 * @param[in]   derivationKey       Key handle holding the source key
 * @param[in]   inputs              Array holding information about the salt to be used
 * @param[in]   numberOfInputs      Number of inputs, expected to be 1
 * @param[out]  derivedKey          Key handle to receive resulting key
 * 
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_derivationEngine_PBKDF2, mcuxClKey_DerivationEngine_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivationEngine_PBKDF2(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Derivation_t derivationMode,
    mcuxClKey_Handle_t derivationKey,
    mcuxClKey_DerivationInput_t inputs[], /* inputs[0] = salt */
    uint32_t numberOfInputs,
    mcuxClKey_Handle_t derivedKey)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_derivationEngine_PBKDF2);

    /* Salt is required */
    if(1u != numberOfInputs)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_INVALID_INPUT);
    }

    /* Requested key size shall not be 0 or larger than the available buffer space. */
    if((derivedKey->type.size == 0u) || (derivedKey->type.size > derivedKey->container.length))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_ERROR);
    }

    /* HMAC mode needs to be provided */
    if((NULL == derivationMode->macMode) || (NULL == derivationMode->macMode->pCustom))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_INVALID_INPUT);
    }

    /* Salt shall to be at least 8 Bytes. Not enforced */
    /* Iteration count shall be at least 1000. Not enforced */

    /* DESIGN:
     * Follow the algorithm described in section 5.2 of RFC 2898:
     * Step 1: Compute l = ceil(dkLen / hLen) [The number of blocks]
     * Step 2: Compute r = dkLen - (l - 1) * hLen [The number of Bytes needed from the output of the last block]
     * Step 3: Compute T_1, ..., T_l [The block outputs], where
     *      T_i := F(password [aka. derivationKey], salt, c, i);
     *      F(password, salt, c, i) := U_1 xor U_2 xor ... xor U_c;
     *      U_1 := HMAC(Password [used as key], salt || BE32(i));
     *      U_{j+1} := HMAC(Password, U_j);
     *      BE32(i) := [The 32-Bit Big-Endian representation of the counter value i]
     * Step 4: T = T_1 || T_2 || ... || T_l.
     * Output the first dkLen Bytes of T [i.e. only use r Bytes from T_l].
     */

    uint32_t macByteSize = derivationMode->macMode->common.macByteSize;
    uint32_t numberOfBlocks = derivedKey->type.size / macByteSize;
    uint32_t outputBytesLastBlock = derivedKey->type.size % macByteSize;

    if(outputBytesLastBlock != 0u)
    {
        /* Increase the number of iterations to also handle the last "incomplete" output block */
        numberOfBlocks++;
    }
    else
    {
        /* The remaining output bytes for the last processing step are a full MAC output block */
        outputBytesLastBlock = macByteSize;
    }

    /* Allocate space for intermediate Hmac results */
    uint8_t *pMacOutput = (uint8_t *)mcuxClSession_allocateWords_cpuWa(pSession, macByteSize / sizeof(uint32_t));
    if(NULL == pMacOutput)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_ERROR);
    }

    /* Allocate space for big endian counter value */
    uint8_t *pBigEndianI = (uint8_t *)mcuxClSession_allocateWords_cpuWa(pSession, 1u);
    if(NULL == pBigEndianI)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_ERROR);
    }

    /* Allocate space for outputKey (used as T_i buffer) */
    uint8_t *pT_i_buffer = (uint8_t *)mcuxClSession_allocateWords_cpuWa(pSession, macByteSize / sizeof(uint32_t));
    if(NULL == pT_i_buffer)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_ERROR);
    }

    uint8_t* pOutputKey = derivedKey->container.pData;
    /* Compute T_i blocks */
    for(size_t i = 1u; i <= numberOfBlocks; i++)
    {
        /* Compute U_1 */
        mcuxClMemory_StoreBigEndian32(pBigEndianI, i);
        MCUX_CSSL_FP_FUNCTION_CALL(u1_result, mcuxClKey_derivation_pbkdf2_computeHmac(
                pSession,
                derivationMode->macMode,
                derivationKey,
                inputs[0],
                pBigEndianI,
                pMacOutput
        ));
        if(MCUXCLKEY_STATUS_OK != u1_result)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, u1_result);
        }

        /* Copy U_1 to T_i buffer */
        MCUXCLMEMORY_FP_MEMORY_COPY(pT_i_buffer, pMacOutput, macByteSize);

        /* Compute U_2 ... U_c */
        for(size_t j = 1u; j < derivationMode->options; j++)
        {
            uint32_t outSize = 0;
            MCUXCLBUFFER_INIT_RO(pMacInBuf, pSession, pMacOutput, macByteSize);
            MCUXCLBUFFER_INIT(pMacOutBuf, pSession, pMacOutput, macByteSize);
            MCUX_CSSL_FP_FUNCTION_CALL(compute_result, mcuxClMac_compute(
                    pSession,
                    derivationKey,
                    derivationMode->macMode,
                    pMacInBuf,
                    macByteSize,
                    pMacOutBuf,
                    &outSize
            ));
            if(MCUXCLMAC_STATUS_OK != compute_result)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }
            /* Xor T_i buffer with U_j. TODO: CLNS-8939 Replace with a proper central Xor implementation. */
            mcuxClKey_derivation_xor_buffers(pT_i_buffer, pT_i_buffer, (uint8_t *) MCUXCLBUFFER_GET(pMacOutBuf), macByteSize);
        }

        if(i != numberOfBlocks)
        {
            MCUXCLBUFFER_INIT(pOutputKeyBuf, pSession, pOutputKey, macByteSize);
            /* If not last iteration: Copy T_i buffer to derivedKey */
            MCUX_CSSL_FP_FUNCTION_CALL(write_result, mcuxClBuffer_write(
                    pOutputKeyBuf,
                    (i - 1u) * macByteSize,
                    pT_i_buffer,
                    macByteSize
            ));
            if(MCUXCLBUFFER_STATUS_OK != write_result)
            {
                /* clean-up the CPU work-area: pBigEndianI, pMacOutput, pT_i_buffer */
                mcuxClSession_freeWords_cpuWa(pSession, 1u + 2u * (macByteSize / sizeof(uint32_t)));
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, write_result);
            }
        }
        else
        {
            MCUXCLBUFFER_INIT(pOutputKeyBuf, pSession, pOutputKey, outputBytesLastBlock);
            /* If last iteration: Copy first outputBytesLastBlock bytes of T_i buffer to derivedKey */
            MCUX_CSSL_FP_FUNCTION_CALL(write_result, mcuxClBuffer_write(
                    pOutputKeyBuf,
                    (i - 1u) * macByteSize,
                    pT_i_buffer,
                    outputBytesLastBlock
            ));
            if(MCUXCLBUFFER_STATUS_OK != write_result)
            {
                /* clean-up the CPU work-area: pBigEndianI, pMacOutput, pT_i_buffer */
                mcuxClSession_freeWords_cpuWa(pSession, 1u + 2u * (macByteSize / sizeof(uint32_t)));
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, write_result);
            }
        }
    }

    /* clean-up the CPU work-area: pBigEndianI, pMacOutput, pT_i_buffer */
    mcuxClSession_freeWords_cpuWa(pSession, 1u + 2u * (macByteSize / sizeof(uint32_t)));

    /* FP balancing and exit */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_PBKDF2, MCUXCLKEY_STATUS_OK,
        numberOfBlocks * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_derivation_pbkdf2_computeHmac),
        numberOfBlocks * (derivationMode->options - 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_compute),
        numberOfBlocks * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        numberOfBlocks * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write)
    );
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_PBKDF2 = {
    .pDerivationEngine = mcuxClKey_derivationEngine_PBKDF2,
    .protectionTokenDerivationEngine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_derivationEngine_PBKDF2)
};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

