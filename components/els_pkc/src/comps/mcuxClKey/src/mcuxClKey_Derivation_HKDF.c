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

/** @file  mcuxClKey_Derivation_HKDF.c
 *  @brief Implementation of RFC5869 Key Derivation */

#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>

#include <mcuxClMac.h>
#include <mcuxClMacModes.h>
#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <mcuxClHmac.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClMac_Internal_Constants.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClHmac_Internal_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxCsslAnalysis.h>

#define MCUXCLKEY_DERIVATION_HKDF_MAX_OUTPUT_SIZE_FACTOR    255u  /* As defined by RFC5869 */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_Derivation_ModeConstructor_HKDF)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Derivation_ModeConstructor_HKDF(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
  mcuxClKey_DerivationMode_t * pDerivationMode,
  const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm,
  mcuxClMac_Mode_t macMode,
  uint32_t options UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_Derivation_ModeConstructor_HKDF);

    pDerivationMode->derivationAlgorithm = derivationAlgorithm;
    pDerivationMode->macMode = macMode;
    pDerivationMode->options = 0u; // no options for this mode

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_Derivation_ModeConstructor_HKDF, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_derivationEngine_HKDF, mcuxClKey_DerivationEngine_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivationEngine_HKDF(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Derivation_t derivationMode,
    mcuxClKey_Handle_t derivationKey,
    mcuxClKey_DerivationInput_t inputs[], // inputs[0] = info, {inputs[1] = salt}
    uint32_t numberOfInputs,
    mcuxClKey_Handle_t derivedKey)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_derivationEngine_HKDF);

    /* No input is required , (info and salt are optional) */
    if(2u < numberOfInputs)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_INVALID_INPUT);
    }

    /* Requested key size shall not be 0 or larger than the available buffer space. */
    if((derivedKey->type.size == 0u) || (derivedKey->type.size > derivedKey->container.length))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_ERROR);
    }

    /* HMAC mode needs to be provided */
    if((NULL == derivationMode->macMode) || (NULL == derivationMode->macMode->pCustom))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_INVALID_INPUT);
    }

    /* Requested key size shall not be larger than 255*HashLen */
    const mcuxClHash_AlgorithmDescriptor_t *hashAlgo = ((mcuxClHmac_ModeDescriptor_t *) (derivationMode->macMode->pCustom))->hashAlgorithm;
    if(derivedKey->type.size > (MCUXCLKEY_DERIVATION_HKDF_MAX_OUTPUT_SIZE_FACTOR * hashAlgo->hashSize))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_INVALID_INPUT);
    }

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKeyDerivation_WorkArea_t *pWa = (mcuxClKeyDerivation_WorkArea_t *) mcuxClSession_allocateWords_cpuWa(pSession, sizeof(mcuxClKeyDerivation_WorkArea_t) / sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_ERROR);
    }

    MCUXCLMEMORY_FP_MEMORY_CLEAR(pWa->context_Wa, MCUXCLMAC_MAX_CONTEXT_SIZE_HMAC);
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClMac_Context_t * const pMacContext = (mcuxClMac_Context_t *)pWa->context_Wa;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint8_t* pMacResult = pWa->macResult_Wa;
    MCUXCLBUFFER_INIT(pMacResultBuf, pSession, pMacResult, derivationMode->macMode->common.macByteSize);
    uint32_t macOutSize = 0u;
    uint8_t *pMac = derivedKey->container.pData;
    MCUXCLBUFFER_INIT(pOutBuf, pSession, pMac, derivedKey->type.size);

    /* Compute the number of operations and the byte-length of the last processing step's output (outputBytesLastIteration).
         - The number of operations depends on the requested size of the derived output key,
           and on hashAlgo->hashSize.
         - The outputBytesLastIteration will be < hashAlgo->hashSize if the requested key's size is
           not a multiple of hashAlgo->hashSize.
    */

    /* derivedKey->type.size has been checked, so it safe to do the casting */
    uint8_t nOfIterations = (uint8_t)(derivedKey->type.size / hashAlgo->hashSize);
    uint32_t outputBytesLastIteration = derivedKey->type.size % hashAlgo->hashSize;

    if(outputBytesLastIteration != 0u)
    {
        /* Increase the number of iterations to also handle the last "incomplete" output block */
        nOfIterations++;
    }
    else
    {
        /* The remaining output bytes for the last processing step are a full MAC output block */
        outputBytesLastIteration = hashAlgo->hashSize;
    }

    /* Allocate space for the Hmac key handle */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t hmacKeyHandle = (mcuxClKey_Handle_t) mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == hmacKeyHandle)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_ERROR);
    }

     /* Step 1: Use the salt as key and derivationKey as message for HMAC to obtain PRK.
      * If no salt is given, create a zero-string of size hashSize as default-salt.
      */

    if (0u != inputs[1].size)
    {
        hmacKeyHandle->type.size = inputs[1].size;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to create a mock key")
        hmacKeyHandle->location.pData = (uint8_t*)MCUXCLBUFFER_GET(inputs[1].input);
        hmacKeyHandle->container.pData = (uint8_t*)MCUXCLBUFFER_GET(inputs[1].input);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
    }
    else
    {
        /* Use pWa->macResult_Wa to store a zero-string of size hashSize */
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pWa->macResult_Wa, hashAlgo->hashSize);
        hmacKeyHandle->type.size = hashAlgo->hashSize;
        hmacKeyHandle->location.pData = pWa->macResult_Wa;
        hmacKeyHandle->container.pData = pWa->macResult_Wa;
    }

    /* Init Mac context */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
    MCUX_CSSL_FP_FUNCTION_CALL(MacInitPRK, mcuxClMac_init(
        pSession,
        pMacContext,
        hmacKeyHandle,
        derivationMode->macMode));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

    if (MCUXCLMAC_STATUS_OK != MacInitPRK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    /* Process IKM */
    uint8_t * pDerivationKey = mcuxClKey_getLoadedKeyData(derivationKey);
    uint32_t derivationKeySize = mcuxClKey_getSize(derivationKey);
    MCUXCLBUFFER_INIT_RO(pDerivationKeyBuf, pSession, pDerivationKey, derivationKeySize);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
    MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_IKM, mcuxClMac_process(
        pSession,
        pMacContext,
        pDerivationKeyBuf,
        derivationKeySize));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

    if (MCUXCLMAC_STATUS_OK != MacProcessInput_IKM)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
    MCUX_CSSL_FP_FUNCTION_CALL(MacFinalizePRK, mcuxClMac_finish(
        pSession,
        pMacContext,
        pMacResultBuf,
        &macOutSize));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

    if (MCUXCLMAC_STATUS_OK != MacFinalizePRK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    /* Step 2:
     * n = ceil(L / hashSize).
     * T(0)= empty string.
     * T(i) = HMAC(PRK, T(i-1) || info || i).
     * T = T(1) || T(2) || ... || T(n).
     * Output the first L Bytes of T.
     * If no info is given, consider info to be the empty string.
     */

    /* Set PRK as the HMAC key */
    hmacKeyHandle->location.pData = (uint8_t*)MCUXCLBUFFER_GET(pMacResultBuf);
    hmacKeyHandle->container.pData = (uint8_t*)MCUXCLBUFFER_GET(pMacResultBuf);
    hmacKeyHandle->type.size = hashAlgo->hashSize;
    macOutSize = 0u;

    uint32_t offset = 0U;
    MCUX_CSSL_FP_LOOP_DECL(loop);
    for(uint8_t i = 1u; i <= nOfIterations; i++)
    {
        /* Init Mac context */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_FP_FUNCTION_CALL(MacInit, mcuxClMac_init(
            pSession,
            pMacContext,
            hmacKeyHandle,
            derivationMode->macMode));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

        if (MCUXCLMAC_STATUS_OK != MacInit)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }


        /* Process T(i-1) if i > 1 */
        if (i > 1u)
        {
            MCUXCLBUFFER_INIT_RO(pInTBuf, pSession, pMac + offset - derivationMode->macMode->common.macByteSize, derivationMode->macMode->common.macByteSize);
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
            MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_TiMinusOne, mcuxClMac_process(
                pSession,
                pMacContext,
                pInTBuf,
                hashAlgo->hashSize));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

            if (MCUXCLMAC_STATUS_OK != MacProcessInput_TiMinusOne)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }
        }

        /* Process info */
        if (0u != inputs[0].size)
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
            MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_info, mcuxClMac_process(
                pSession,
                pMacContext,
                inputs[0].input,
                inputs[0].size));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

            if (MCUXCLMAC_STATUS_OK != MacProcessInput_info)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }
        }

        /* Process i */
        MCUXCLBUFFER_INIT_RO(pInIBuf, pSession, &i, 1u);
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_i, mcuxClMac_process(
            pSession,
            pMacContext,
            pInIBuf,
            1u));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

        if (MCUXCLMAC_STATUS_OK != MacProcessInput_i)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }

        if (i != nOfIterations)
        {
            /* Generate Mac output */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
            MCUX_CSSL_FP_FUNCTION_CALL(MacFinalize, mcuxClMac_finish(
                pSession,
                pMacContext,
                pOutBuf,
                &macOutSize));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

            if (MCUXCLMAC_STATUS_OK != MacFinalize)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }
        }
        else
        {
            /* Handle the last iteration, which might involve a needed output smaller than the MAC output size.
               Use a workarea buffer to generate the last MAC, and copy only the needed amount of bytes to the pMac buffer. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
            MCUX_CSSL_FP_FUNCTION_CALL(MacFinalize, mcuxClMac_finish(
                pSession,
                pMacContext,
                pMacResultBuf,
                &macOutSize));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()

            if (MCUXCLMAC_STATUS_OK != MacFinalize)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

            MCUX_CSSL_FP_FUNCTION_CALL(write_result, mcuxClBuffer_write(pOutBuf, 0u, (uint8_t *) MCUXCLBUFFER_GET(pMacResultBuf), outputBytesLastIteration));
            if(MCUXCLBUFFER_STATUS_OK != write_result)
            {
                /* clean-up the CPU work-area. */
                mcuxClSession_freeWords_cpuWa(pSession, (sizeof(mcuxClKeyDerivation_WorkArea_t) / sizeof(uint32_t))
                                             + (sizeof(mcuxClKey_Descriptor_t) / sizeof(uint32_t)));
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, write_result);
            }
            MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *) MCUXCLBUFFER_GET(pMacResultBuf), hashAlgo->hashSize);
        }

        MCUXCLBUFFER_UPDATE(pOutBuf, derivationMode->macMode->common.macByteSize);
        offset += derivationMode->macMode->common.macByteSize;
        macOutSize = 0u;

        /* Balance the security counter */
        MCUX_CSSL_FP_LOOP_ITERATION(loop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
            MCUX_CSSL_FP_CONDITIONAL(i > 1u, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process)),
            MCUX_CSSL_FP_CONDITIONAL(0u != inputs[0].size, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish));
    }

    /* clean-up the CPU work-area. */
    mcuxClSession_freeWords_cpuWa(pSession, (sizeof(mcuxClKeyDerivation_WorkArea_t) / sizeof(uint32_t))
                                         + (MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_HKDF, MCUXCLKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear), /* Clear pWa->context_Wa */
        MCUX_CSSL_FP_CONDITIONAL(0u == inputs[1].size, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)), /* Clear pWa->macResult_Wa */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),     /* In the step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),  /* In the step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish),   /* In the step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),  /* In the last iteration of step 2 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear), /* In the last iteration of step 2 */
        MCUX_CSSL_FP_LOOP_ITERATIONS(loop, nOfIterations));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_HKDF = {
    .pDerivationEngine = mcuxClKey_derivationEngine_HKDF,
    .protectionTokenDerivationEngine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_derivationEngine_HKDF)
};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
