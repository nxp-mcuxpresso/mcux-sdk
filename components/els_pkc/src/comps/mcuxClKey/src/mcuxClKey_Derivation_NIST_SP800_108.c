/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/** @file  mcuxClKey_Derivation_NIST_SP800_108.c
 *  @brief Implementation of SP800-108 Key Derivation */

#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>

#include <mcuxClMac.h>
#include <mcuxClMacModes.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClMac_Internal_Constants.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxCsslAnalysis.h>
#include <mcuxClKey_DerivationAlgorithms_NIST_SP800_108.h>
#include <internal/mcuxClKey_DerivationAlgorithms_NIST_SP800_108_Internal.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
/* Defines to extract actual sizes from option bits */
#define MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_REQUESTED_KEYLENGTH_ENCODING_SIZE_FROM_OPTIONS(options) \
    ((((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_REQUESTED_KEYLENGTH_ENCODING_SIZE_MASK & (~(options))) >> MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_REQUESTED_KEYLENGTH_ENCODING_SIZE_SHIFT) + 1u) * 8u)

#define MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_COUNTER_SIZE_FROM_OPTIONS(options) \
    ((((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_COUNTER_SIZE_MASK & (options)) >> MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_COUNTER_SIZE_SHIFT) + 1u) * 8u)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_Derivation_ModeConstructor_NIST_SP800_108)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Derivation_ModeConstructor_NIST_SP800_108(
  mcuxClKey_DerivationMode_t * pDerivationMode,
  const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm,
  mcuxClMac_Mode_t macMode,
  uint32_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_Derivation_ModeConstructor_NIST_SP800_108);

    pDerivationMode->derivationAlgorithm = derivationAlgorithm;
    pDerivationMode->macMode = macMode;
    pDerivationMode->options = options;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_Derivation_ModeConstructor_NIST_SP800_108, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_derivationEngine_NIST_SP800_108, mcuxClKey_DerivationEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivationEngine_NIST_SP800_108(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Derivation_t derivationMode,
    mcuxClKey_Handle_t derivationKey,
    mcuxClKey_DerivationInput_t inputs[], // inputs[0] = Label, inputs[1] = Context, inputs[2] = IV (only for Feedback mode)
    uint32_t numberOfInputs,
    mcuxClKey_Handle_t derivedKey)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_derivationEngine_NIST_SP800_108);

    const uint32_t mode = derivationMode->options & MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_MASK;
    const uint32_t flagIncludeCounter = derivationMode->options & MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_COUNTER_INCLUSION_MASK;
    const uint32_t flagSeparatorEnable = MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_SEPARATOR_MASK & derivationMode->options;
    const uint32_t flagEndianess = MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_ENDIANESS_MASK & derivationMode->options;

    /* input validation */
    if(((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_FEEDBACK == mode) && (numberOfInputs < 3u))
        || ((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_FEEDBACK != mode) && (numberOfInputs < 2u)))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_INVALID_INPUT);
    }
    if(derivedKey->type.size > derivedKey->container.length)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_ERROR);
    }

    /* r = bit-length of the binary representation of the counter i (encoded in the derivation options) = counterByteLen * 8
     * L = derivedKeySizeInBits = length of the derived key material in bits (derivedKey->type.size * 8u)
     * h = output length of the MAC in bits (derivationMode->macMode->common.macByteSize * 8u)
     * n = nOfIterations = ceiling(L/h)
     */
    const uint32_t derivedKeySizeInBits = derivedKey->type.size << 3;
    uint32_t counterBitLen = 0u;
    uint32_t counterByteLen = 0u;

    /* Compute the number of operations and the byte-length of the last processing step's output (outputBytesLastIteration).
         - The number of operations depends on the requested size of the derived output key,
           and on the output size of the chosen MAC.
         - The outputBytesLastIteration will be < macByteSize if the requested key's size is
           not a multiple of the MAC output size (1 <= outputBytesLastIteration <= macByteSize).
    */
    uint32_t nOfIterations = derivedKey->type.size / derivationMode->macMode->common.macByteSize;
    uint32_t outputBytesLastIteration = derivedKey->type.size % derivationMode->macMode->common.macByteSize;

    if(outputBytesLastIteration != 0u)
    {
        /* Increase the number of iterations to also handle the last "incomplete" output block */
        nOfIterations++;
    }
    else
    {
        /* The remaining output bytes for the last processing step are a full MAC output block */
        outputBytesLastIteration = derivationMode->macMode->common.macByteSize;
    }

    /* If n > 2^r-1 when the counter is encoded in the input-string, then indicate an error and stop. */
    if ((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_COUNTER == mode)
            || (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_INCLUDE_COUNTER == flagIncludeCounter))
    {
        counterBitLen = MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_COUNTER_SIZE_FROM_OPTIONS(derivationMode->options);
        if ((uint64_t)nOfIterations >= (1uLL << counterBitLen))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_INVALID_INPUT);

        }
        counterByteLen = (counterBitLen / 8u); /* byte-length of the counter i when encoded in the input-string */
    }

    /* The derived output key may be of any size, i.e. it does not have to be a multiple of the MAC's output size.
     * We need to handle the last iteration seperately:
     * 1. Compute the resulting MACs of all full output blocks (except the last one) in a loop and put
          the result directly to the output buffer.
         1.1 If it is Double-Pipeline mode, Compute A(i) := MAC(Key_In, A(i-1)), (A(0) := Label || 0x00 || Context || [L]2, 0x00 is optional).
         1.2 Compute K(i).
         1.2.1 If it is Feedback mode, MAC process K(i-1), K(0) = IV; if it is Double-Pipeline mode, MAC process A(i).
         1.2.2 If it is Counter mode or INCLUDE_COUNTER is set for Feedback and Double-Pipeline mode, MAC process [i]2.
         1.2.3 MAC process Label || 0x00 || Context || [L]2, 0x00 is optional.
         1.2.4 Finish MAC computation and put the result directly to the output buffer.
     * 2. Compute the resulting MAC of the last iteration (share 1.1 - 1.2.3). The MAC API does not support truncated MACs,
          so we use a temporary, block-sized output buffer for the MAC compuation. Then only the needed/requested bytes
          are copied to the actual output buffer (1 <= outputBytesLastIteration <= macByteSize).

     * If [i]2 is included in the input, we need to update the i in the inputData for each iteration.
     */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKeyDerivation_WorkArea_t *pWa = (mcuxClKeyDerivation_WorkArea_t *) mcuxClSession_allocateWords_cpuWa(pSession, sizeof(mcuxClKeyDerivation_WorkArea_t) / sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_ERROR);
    }

    uint32_t macOutSize = 0u;
    uint8_t *pMac = derivedKey->container.pData;
    MCUXCLBUFFER_INIT(pOutBuf, pSession, pMac, derivedKey->type.size);
    uint8_t* inputData = pWa->input_Wa; // a buffer for [i]2 (use the first 4 bytes) and [L]2 (use the last 4 bytes)

    MCUXCLMEMORY_FP_MEMORY_CLEAR(pWa->context_Wa, MCUXCLMAC_MAX_CONTEXT_SIZE);
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClMac_Context_t * const pMacContext = (mcuxClMac_Context_t *)pWa->context_Wa;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint8_t* pMacResult = pWa->macResult_Wa;
    MCUXCLBUFFER_INIT_RO(pMacRetInBuf, pSession, pMacResult, MCUXCLMAC_MAX_OUTPUT_SIZE);
    MCUXCLBUFFER_INIT(pMacRetOutBuf, pSession, pMacResult, MCUXCLMAC_MAX_OUTPUT_SIZE);

    /* copy the bit-length L adjusting the endianness */
    const uint32_t sizeOfEncodedOutputSize = MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_REQUESTED_KEYLENGTH_ENCODING_SIZE_FROM_OPTIONS(derivationMode->options) / 8u;
    uint8_t *pL = inputData + 4u;
    if(MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_ENDIANESS_BIG_ENDIAN == flagEndianess)
    {
        mcuxClMemory_StoreBigEndian32(pL, derivedKeySizeInBits);
        /* in big endian we need to skip some upper bytes */
        pL += (sizeof(uint32_t) - sizeOfEncodedOutputSize);
    }
    else if(MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_ENDIANESS_LITTLE_ENDIAN == flagEndianess)
    {
        mcuxClMemory_StoreLittleEndian32(pL, derivedKeySizeInBits);
    }
    else
    {
        /* Considered options are complete */
    }

    uint32_t offset = 0U;
    MCUX_CSSL_FP_LOOP_DECL(loopCommon);
    MCUX_CSSL_FP_LOOP_DECL(loopProcessFeedback);
    MCUX_CSSL_FP_LOOP_DECL(loopProcessDoublePipeline);
    MCUX_CSSL_FP_LOOP_DECL(loopProcessCounter);
    for(uint32_t i = 1u; i <= nOfIterations; i++)
    {
        /* Compute A(i) for Double-Pipeline mode */
        if (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_DOUBLE_PIPELINE == mode)
        {
            /* Init Mac context */
            MCUX_CSSL_FP_FUNCTION_CALL(MacInit, mcuxClMac_init(
                pSession,
                pMacContext,
                derivationKey,
                derivationMode->macMode));

            if (MCUXCLMAC_STATUS_OK != MacInit)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

            if (1u == i)
            {
                /* Process the label */
                MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_label, mcuxClMac_process(
                    pSession,
                    pMacContext,
                    inputs[0].input,
                    inputs[0].size));

                if (MCUXCLMAC_STATUS_OK != MacProcessInput_label)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                }

                if (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_SEPARATOR_ENABLED == flagSeparatorEnable)
                {
                    /* Process the fixed 0-byte */
                    inputData[0u]= 0u;
                    MCUXCLBUFFER_INIT_RO(pInBuf, pSession, inputData, 1u);
                    MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_0, mcuxClMac_process(
                        pSession,
                        pMacContext,
                        pInBuf,
                        1u));

                    if (MCUXCLMAC_STATUS_OK != MacProcessInput_0)
                    {
                        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                    }
                }

                /* Process the context */
                MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_context, mcuxClMac_process(
                    pSession,
                    pMacContext,
                    inputs[1].input,
                    inputs[1].size));

                if (MCUXCLMAC_STATUS_OK != MacProcessInput_context)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                }

                /* Process [L]2 */
                MCUXCLBUFFER_INIT_RO(pLBuf, pSession, pL, sizeOfEncodedOutputSize);
                MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_l, mcuxClMac_process(
                    pSession,
                    pMacContext,
                    pLBuf,
                    sizeOfEncodedOutputSize));

                if (MCUXCLMAC_STATUS_OK != MacProcessInput_l)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                }

            }
            else
            {
                /* Process A(i-1) */
                MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_AMinusOne, mcuxClMac_process(
                    pSession,
                    pMacContext,
                    pMacRetInBuf,
                    derivationMode->macMode->common.macByteSize));

                if (MCUXCLMAC_STATUS_OK != MacProcessInput_AMinusOne)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                }
            }

            MCUX_CSSL_FP_FUNCTION_CALL(MacFinalize, mcuxClMac_finish(
                pSession,
                pMacContext,
                pMacRetOutBuf,
                &macOutSize
            ));

            if (MCUXCLMAC_STATUS_OK != MacFinalize)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

            /* Balance the security counter */
            MCUX_CSSL_FP_LOOP_ITERATION(loopProcessDoublePipeline,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_CONDITIONAL(1u == i, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process)*2u),
                MCUX_CSSL_FP_CONDITIONAL((1u == i) && (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_SEPARATOR_ENABLED == flagSeparatorEnable),
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish));
            macOutSize = 0u;
        }

        /* Init Mac context */
        MCUX_CSSL_FP_FUNCTION_CALL(MacInit, mcuxClMac_init(
            pSession,
            pMacContext,
            derivationKey,
            derivationMode->macMode));

        if (MCUXCLMAC_STATUS_OK != MacInit)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }


        /* Process K(i-1) for Feedback mode */
        if (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_FEEDBACK == mode)
        {
            if(1u != i)
            {
                MCUXCLBUFFER_INIT_RO(pMacInBuf, pSession, pMac + offset - derivationMode->macMode->common.macByteSize, derivationMode->macMode->common.macByteSize);
                MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_KiMinusOne, mcuxClMac_process(
                    pSession,
                    pMacContext,
                    pMacInBuf,
                    derivationMode->macMode->common.macByteSize));

                if (MCUXCLMAC_STATUS_OK != MacProcessInput_KiMinusOne)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                }
            }
            else
            {
                MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_KiMinusOne, mcuxClMac_process(
                    pSession,
                    pMacContext,
                    inputs[2].input,
                    inputs[2].size));

                if (MCUXCLMAC_STATUS_OK != MacProcessInput_KiMinusOne)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
                }
            }
            /* Balance the security counter */
            MCUX_CSSL_FP_LOOP_ITERATION(loopProcessFeedback,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process));
        }
        else if (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_DOUBLE_PIPELINE == mode) /* Process A(i) for Double-Pipline mode */
        {
            MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_Ai, mcuxClMac_process(
                pSession,
                pMacContext,
                pMacRetInBuf,
                derivationMode->macMode->common.macByteSize));

            if (MCUXCLMAC_STATUS_OK != MacProcessInput_Ai)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

            /* Balance the security counter */
            MCUX_CSSL_FP_LOOP_ITERATION(loopProcessDoublePipeline,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process));
        }
        else
        {
           /* Do nothing for Counter Mode */
        }

        /* Process the counter [i]2 */
        if ((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_COUNTER == mode)
             || (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_INCLUDE_COUNTER == flagIncludeCounter))
        {
            /* copy the counter i in correct format according to the endianness */
            uint8_t *pI = inputData;
            if(MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_ENDIANESS_BIG_ENDIAN == flagEndianess)
            {
                mcuxClMemory_StoreBigEndian32(pI, i);
                /* in big endian we need to skip some upper bytes */
                pI += (sizeof(uint32_t) - counterByteLen);
            }
            else if(MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_ENDIANESS_LITTLE_ENDIAN == flagEndianess)
            {
                mcuxClMemory_StoreLittleEndian32(pI, i);
            }
            else
            {
                /* Considered options are complete */
            }

            MCUXCLBUFFER_INIT_RO(pIBuf, pSession, pI, counterByteLen);
            MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_i, mcuxClMac_process(
                pSession,
                pMacContext,
                pIBuf,
                counterByteLen));

            if (MCUXCLMAC_STATUS_OK != MacProcessInput_i)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

            /* Balance the security counter */
            MCUX_CSSL_FP_LOOP_ITERATION(loopProcessCounter,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process));
        }

        /* Process the label */
        MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_label, mcuxClMac_process(
            pSession,
            pMacContext,
            inputs[0].input,
            inputs[0].size));

        if (MCUXCLMAC_STATUS_OK != MacProcessInput_label)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }

        if (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_SEPARATOR_ENABLED == flagSeparatorEnable)
        {
            /* Process the fixed 0-byte */
            inputData[0u]= 0u;
            MCUXCLBUFFER_INIT_RO(pInBuf, pSession, inputData, 1u);
            MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_0, mcuxClMac_process(
                pSession,
                pMacContext,
                pInBuf,
                1u));

            if (MCUXCLMAC_STATUS_OK != MacProcessInput_0)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

        }

        /* Process the context */
        MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_context, mcuxClMac_process(
            pSession,
            pMacContext,
            inputs[1].input,
            inputs[1].size));

        if (MCUXCLMAC_STATUS_OK != MacProcessInput_context)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }

        /* Process [L]2 */
        MCUXCLBUFFER_INIT_RO(pLBuf, pSession, pL, sizeOfEncodedOutputSize);
        MCUX_CSSL_FP_FUNCTION_CALL(MacProcessInput_l, mcuxClMac_process(
            pSession,
            pMacContext,
            pLBuf,
            sizeOfEncodedOutputSize));

        if (MCUXCLMAC_STATUS_OK != MacProcessInput_l)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }

        if (i != nOfIterations)
        {
            /* Generate Mac output */
            MCUX_CSSL_FP_FUNCTION_CALL(MacFinalize, mcuxClMac_finish(
                pSession,
                pMacContext,
                pOutBuf,
                &macOutSize));

            if (MCUXCLMAC_STATUS_OK != MacFinalize)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }
        }
        else
        {
            /* Handle the last iteration, which might involve a needed output smaller than the MAC output size.
               Use a buffer on stack to generate the last MAC, and copy only the needed amount of bytes to the pMac buffer. */
            MCUX_CSSL_FP_FUNCTION_CALL(MacFinalize, mcuxClMac_finish(
                pSession,
                pMacContext,
                pMacRetOutBuf,
                &macOutSize
            ));

            if (MCUXCLMAC_STATUS_OK != MacFinalize)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_FAULT_ATTACK);
            }

            MCUX_CSSL_FP_FUNCTION_CALL(write_result, mcuxClBuffer_write(pOutBuf, 0u, (uint8_t *) MCUXCLBUFFER_GET(pMacRetOutBuf), outputBytesLastIteration));
            if(MCUXCLBUFFER_STATUS_OK != write_result)
            {
                /* clean-up the CPU work-area. */
                mcuxClSession_freeWords_cpuWa(pSession, sizeof(mcuxClKeyDerivation_WorkArea_t) / sizeof(uint32_t));
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, write_result);
            }
            MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)MCUXCLBUFFER_GET(pMacRetOutBuf), MCUXCLMAC_MAX_OUTPUT_SIZE);
        }

        MCUXCLBUFFER_UPDATE(pOutBuf, derivationMode->macMode->common.macByteSize);
        offset += derivationMode->macMode->common.macByteSize;
        macOutSize = 0u;

        /* Balance the security counter */
        MCUX_CSSL_FP_LOOP_ITERATION(loopCommon,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_CONDITIONAL(MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_SEPARATOR_ENABLED == flagSeparatorEnable,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish));
    }


    /* clean-up the CPU work-area. */
    mcuxClSession_freeWords_cpuWa(pSession, sizeof(mcuxClKeyDerivation_WorkArea_t) / sizeof(uint32_t));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_derivationEngine_NIST_SP800_108, MCUXCLKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear), /* Before the main loop */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write), /* In the last iteration of the main loop */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear), /* In the last iteration of the main loop */
        MCUX_CSSL_FP_LOOP_ITERATIONS(loopCommon, nOfIterations),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_COUNTER == mode) || (MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_INCLUDE_COUNTER == flagIncludeCounter)),
            MCUX_CSSL_FP_LOOP_ITERATIONS(loopProcessCounter, nOfIterations)),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_FEEDBACK == mode),
            MCUX_CSSL_FP_LOOP_ITERATIONS(loopProcessFeedback, nOfIterations)),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_DOUBLE_PIPELINE == mode),
            MCUX_CSSL_FP_LOOP_ITERATIONS(loopProcessDoublePipeline, 2u * nOfIterations)));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClKey_DerivationAlgorithmDescriptor_t mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_108 = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    .pDerivationEngine = mcuxClKey_derivationEngine_NIST_SP800_108,
    .protectionTokenDerivationEngine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_derivationEngine_NIST_SP800_108)
};

/* KDF in Counter Mode for CMAC */
/* \deprecated{Use ModeConstructor instead.} */
const mcuxClKey_DerivationMode_t mcuxClKey_DerivationMode_SP800_108_CM_CMAC = {
  .derivationAlgorithm = &mcuxClKey_DerivationAlgorithmDescriptor_NIST_SP800_108,
  .macMode =  (mcuxClMac_Mode_t)&mcuxClMac_ModeDescriptor_CMAC,
  .options = MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_COUNTER_SIZE_8
            | MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_REQUESTED_KEYLENGTH_ENCODING_SIZE_32
            | MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_ENDIANESS_BIG_ENDIAN
            | MCUXCLKEY_DERIVATION_OPTIONS_NIST_SP800_108_MODE_COUNTER
};

