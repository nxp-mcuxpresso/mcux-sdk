/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/** @file  mcuxClOsccaCipherModes_SM4_Crypt_Internal.c
 *  @brief implementation of the Internal functions of the mcuxClOsccaCipherModes component */

#include <mcuxClMemory.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClKey.h>
#include <mcuxClPadding.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClCipher_Internal.h>
#include <internal/mcuxClOsccaCipherModes_Internal_Types.h>
#include <internal/mcuxClOsccaCipherModes_Internal_Functions.h>
#include <internal/mcuxClOsccaCipherModes_Algorithms.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4_Pre)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaCipherModes_SkeletonSM4_Pre(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxClCipher_Mode_t pMode
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4_Pre);

    /* Correct algorithm type for SM4 Skeleton */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for mcuxClOsccaCipherModes_Context_Sm4_t types")
    pCtx->common.pMode = pMode;
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *)pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    if ((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
            (MCUXCLOSCCACIPHER_DECRYPT == pAlgo->direction))
    {
        pCtx->out = 2u; pCtx->iv = 1u; pCtx->in = 0u;
    }
    else
    {
        pCtx->out = 0u; pCtx->iv = 1u; pCtx->in = 2u;
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaCipherModes_SkeletonSM4_Pre);
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_Init(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxClKey_Handle_t pKey,
    mcuxCl_InputBuffer_t pIv,
    uint32_t ivLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4_Init);

    if (((ivLength != 0u) && (ivLength != MCUXCLOSCCASM4_BLOCK_SIZE)) || ((ivLength != 0u) && (pIv == NULL)))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_Init, MCUXCLCIPHER_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    uint32_t direction;
    if (MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR == pAlgo->mode)
    {
        direction = MCUXCLOSCCASM4_ENCRYPT;
    }
    else
    {
        direction = pAlgo->direction;
    }
    MCUX_CSSL_FP_FUNCTION_CALL(setupResult, mcuxClOsccaSm4_ScheduleSM4Key(pCtx->roundKeys, pKey->container.pData, direction));
    if (MCUXCLOSCCASM4_STATUS_LOADKEY_OK != setupResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_Init, MCUXCLCIPHER_STATUS_ERROR,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_ScheduleSM4Key));
    }

    /* If there is an IV, copy it to the state buffer. */
    if (ivLength != 0u)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIv, 0u, pCtx->state[pCtx->iv], ivLength));
        (void)statusBufferRead;
    }

    /* No partial data for oneshot, this will always be zero. */
    pCtx->common.blockBufferUsed = 0u;
    /* Total number of bytes that were encrypted is initialized with zero */
    pCtx->common.totalInputLength = 0u;

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4_Init, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_ScheduleSM4Key),
        MCUX_CSSL_FP_CONDITIONAL((ivLength != 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SM4_Crypt_IncCounter)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaCipherModes_SM4_Crypt_IncCounter(uint8_t *pCounter)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SM4_Crypt_IncCounter);
    uint8_t *pCounterByte = pCounter;
    for(uint32_t i = MCUXCLOSCCASM4_BLOCK_SIZE; i > 0u; --i)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("The integer wrap is intentional.")
        pCounterByte[i-1u]++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        if(0u != pCounterByte[i-1u])
        {
          break;
        }
    }
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaCipherModes_SM4_Crypt_IncCounter);
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro);

    MCUX_CSSL_FP_FUNCTION_CALL(engineResult, mcuxClOsccaSm4_Engine(pCtx->roundKeys, pCtx->state[pCtx->iv], pCtx->state[pCtx->out], MCUXCLOSCCACIPHER_ENCRYPT ));
    if (MCUXCLOSCCASM4_STATUS_CRYPT_OK != engineResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro, MCUXCLCIPHER_STATUS_ERROR,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine));
    }
    /* Update the IV = IV + 1 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaCipherModes_SM4_Crypt_IncCounter(pCtx->state[pCtx->iv]));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->state[pCtx->out], pCtx->state[pCtx->out], pCtx->state[pCtx->in], MCUXCLOSCCASM4_BLOCK_SIZE));

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine),
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SM4_Crypt_IncCounter),
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    if ((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
        (MCUXCLOSCCACIPHER_ENCRYPT == pAlgo->direction))
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->state[pCtx->in], pCtx->state[pCtx->in], pCtx->state[pCtx->iv], MCUXCLOSCCASM4_BLOCK_SIZE));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(engineResult, mcuxClOsccaSm4_Engine(pCtx->roundKeys, pCtx->state[pCtx->in], pCtx->state[pCtx->out], pAlgo->direction));
    if (MCUXCLOSCCASM4_STATUS_CRYPT_OK != engineResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro, MCUXCLCIPHER_STATUS_ERROR,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine),
                                            MCUX_CSSL_FP_CONDITIONAL(((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) && (MCUXCLOSCCACIPHER_ENCRYPT == pAlgo->direction)),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)));
    }

    if ((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
                (MCUXCLOSCCACIPHER_DECRYPT == pAlgo->direction))
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->state[pCtx->out], pCtx->state[pCtx->out], pCtx->state[pCtx->iv], MCUXCLOSCCASM4_BLOCK_SIZE));
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine),
                                            MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4_Process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_Process(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4_Process);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    uint32_t loopTimes = 0u;
    uint32_t loopTimes1 = 0u;
    uint32_t inputLen = inLength;
    uint32_t inOffset = 0u;
    uint32_t outOffset = 0u;

    while (inputLen > 0u)
    {
        /* Number of bytes to possibly copy into the partial data buffer. */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("MCUXCLOSCCASM4_BLOCK_SIZE can't be less than pCtx->common.blockBufferUsed")
        uint32_t bytesToCopy = ((MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->common.blockBufferUsed) > inputLen) ? inputLen: (MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->common.blockBufferUsed);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        /* Add new data into the partial data buffer and process, if possible. */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, inOffset, pCtx->state[pCtx->in] + pCtx->common.blockBufferUsed, bytesToCopy));
        (void)statusBufferRead;

        /* The bytes copied already should not be taken into account further. */
        inputLen -= bytesToCopy;
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(inOffset, 0u, UINT32_MAX - bytesToCopy, MCUXCLCIPHER_STATUS_FAULT_ATTACK)
        inOffset += bytesToCopy;
        pCtx->common.blockBufferUsed += bytesToCopy;
        /* Update total number of bytes that were encrypted */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("*loopTimes and pCtx->common.totalInputLength can't be larger than max(uint32_t)")
        pCtx->common.totalInputLength += bytesToCopy;
        loopTimes++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

        if (pCtx->common.blockBufferUsed == MCUXCLOSCCASM4_BLOCK_SIZE)
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("*loopTimes1 can't be larger than max(uint32_t)")
            loopTimes1++;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            if (MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR == pAlgo->mode)
            {
                MCUX_CSSL_FP_FUNCTION_CALL(ctrResult, mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro(pCtx));
                if (MCUXCLCIPHER_STATUS_OK != ctrResult)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_Process, MCUXCLCIPHER_STATUS_ERROR,
                                              loopTimes * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                                              (loopTimes1 - 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),
                                              loopTimes1 * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro));
                }
            }
            if (MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR != pAlgo->mode)
            {
                MCUX_CSSL_FP_FUNCTION_CALL(noCtrResult, mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro(pCtx));
                if (MCUXCLCIPHER_STATUS_OK != noCtrResult)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_Process, MCUXCLCIPHER_STATUS_ERROR,
                                              loopTimes * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                                              (loopTimes1 - 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),
                                              loopTimes1 * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro));
                }
            }

            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, outOffset, pCtx->state[pCtx->out], MCUXCLOSCCASM4_BLOCK_SIZE));
            (void)statusBufferWrite;

            /* Write to pOutLength how many bytes have been written. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
            *pOutLength += MCUXCLOSCCASM4_BLOCK_SIZE;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(outOffset, 0u, UINT32_MAX - MCUXCLOSCCASM4_BLOCK_SIZE, MCUXCLCIPHER_STATUS_FAULT_ATTACK)
            outOffset += MCUXCLOSCCASM4_BLOCK_SIZE;
            /* The partial data buffer is now empty. */
            pCtx->common.blockBufferUsed = 0u;

            /* The bytes copied already should not be taken into account further. */
            if (MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR != pAlgo->mode)
            {
                pCtx->iv += 2u; pCtx->in += 2u; pCtx->out += 2u;
                pCtx->iv %= 3u; pCtx->in %= 3u; pCtx->out %= 3u;
            }
        }
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4_Process, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                            loopTimes * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                                            loopTimes1 * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),
                                            MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR == pAlgo->mode),
                                                        loopTimes1 * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4Ctr_BlockPro)),
                                            MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR != pAlgo->mode),
                                                        loopTimes1 * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_BlockPro)));
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    /* Number of bytes added by the padding. */
    uint32_t padOutLength = 0u;

    if (pAlgo->addPadding == NULL)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro, MCUXCLCIPHER_STATUS_ERROR);
    }

    /* Apply the padding function specified in the mode on the partial data. */
    MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(MCUXCLOSCCASM4_BLOCK_SIZE, pCtx->state[pCtx->in], pCtx->common.blockBufferUsed,
                                         pCtx->common.totalInputLength,
                                         pCtx->state[pCtx->in], &padOutLength));

    if (padResult != MCUXCLPADDING_STATUS_OK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro, MCUXCLCIPHER_STATUS_ERROR,
                                            pAlgo->protection_token_addPadding);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(engineResult, mcuxClOsccaSm4_Engine(pCtx->roundKeys, pCtx->state[pCtx->iv], pCtx->state[pCtx->out], MCUXCLOSCCACIPHER_ENCRYPT ));
    if (MCUXCLOSCCASM4_STATUS_CRYPT_OK != engineResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro, MCUXCLCIPHER_STATUS_ERROR,
                                            pAlgo->protection_token_addPadding,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine));
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->state[pCtx->out], pCtx->state[pCtx->out], pCtx->state[pCtx->in], MCUXCLOSCCASM4_BLOCK_SIZE));
    /* Copy the last non-full block data to the output and update pOutLength accordingly. */
    MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, pCtx->state[pCtx->out], pCtx->common.blockBufferUsed));
    (void)statusBufferWrite;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
    *pOutLength += pCtx->common.blockBufferUsed;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                            pAlgo->protection_token_addPadding,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine),
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor),
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    /* Number of bytes added by the padding. */
    uint32_t padOutLength = 0u;

    if (pAlgo->addPadding == NULL)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro, MCUXCLCIPHER_STATUS_ERROR);
    }

    /* Apply the padding function specified in the mode on the partial data. */
    MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(MCUXCLOSCCASM4_BLOCK_SIZE, pCtx->state[pCtx->in], pCtx->common.blockBufferUsed,
                                         pCtx->common.totalInputLength,
                                         pCtx->state[pCtx->in], &padOutLength));

    if (padResult != MCUXCLPADDING_STATUS_OK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro, MCUXCLCIPHER_STATUS_ERROR,
                                            pAlgo->protection_token_addPadding);
    }

    if (padOutLength > 0u)
    {
        if ((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
            (MCUXCLOSCCACIPHER_ENCRYPT == pAlgo->direction))
        {
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->state[pCtx->in], pCtx->state[pCtx->in], pCtx->state[pCtx->iv], MCUXCLOSCCASM4_BLOCK_SIZE));
        }

        MCUX_CSSL_FP_FUNCTION_CALL(engineResult, mcuxClOsccaSm4_Engine(pCtx->roundKeys, pCtx->state[pCtx->in], pCtx->state[pCtx->out], pAlgo->direction));
        if (MCUXCLOSCCASM4_STATUS_CRYPT_OK != engineResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro, MCUXCLCIPHER_STATUS_ERROR,
                                      pAlgo->protection_token_addPadding,
                                      MCUX_CSSL_FP_CONDITIONAL(((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
                                                               (MCUXCLOSCCACIPHER_ENCRYPT == pAlgo->direction)),
                                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)),
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine));
        }
        /* Copy the padding to the output and update pOutLength accordingly. */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, pCtx->state[pCtx->out], padOutLength));
        (void)statusBufferWrite;

        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
        *pOutLength += padOutLength;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                            pAlgo->protection_token_addPadding,
                                            MCUX_CSSL_FP_CONDITIONAL((padOutLength > 0u),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),
                                                        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
                                                                                (MCUXCLOSCCACIPHER_ENCRYPT == pAlgo->direction)),
                                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor))));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4_Finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_Finish(
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4_Finish);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    if ((pCtx->common.blockBufferUsed > 0u) && (MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR == pAlgo->mode))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(lastProResult, mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro(pCtx, pOut, pOutLength));
        if (MCUXCLCIPHER_STATUS_OK != lastProResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_Finish, MCUXCLCIPHER_STATUS_ERROR,
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro));
        }
    }
    if(MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR != pAlgo->mode)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(lastProResult, mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro(pCtx, pOut, pOutLength));
        if (MCUXCLCIPHER_STATUS_OK != lastProResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_Finish, MCUXCLCIPHER_STATUS_ERROR,
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro));
        }
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4_Finish, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                            MCUX_CSSL_FP_CONDITIONAL((((pCtx->common.blockBufferUsed > 0u) && (MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR == pAlgo->mode))),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4Ctr_LastBlockPro)),
                                            MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR != pAlgo->mode),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4NoCtr_LastBlockPro)));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaCipherModes_SkeletonSM4_OneShot)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaCipherModes_SkeletonSM4_OneShot(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t pKey,
    mcuxClCipher_Mode_t pMode,
    mcuxCl_InputBuffer_t pIv,
    uint32_t ivLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaCipherModes_SkeletonSM4_OneShot);

    if(NULL == session)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_OneShot, MCUXCLCIPHER_STATUS_ERROR);
    }
    /* Create context for OneShot */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for mcuxClOsccaCipherModes_Context_Sm4_t* types")
    mcuxClOsccaCipherModes_Context_Sm4_t * pCtx = (mcuxClOsccaCipherModes_Context_Sm4_t *)mcuxClSession_allocateWords_cpuWa(session,  (sizeof(mcuxClOsccaCipherModes_Context_Sm4_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    if(NULL == pCtx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_OneShot, MCUXCLCIPHER_STATUS_FAILURE);
    }
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret structure for mcuxClOsccaCipherModes_Context_Sm4_t types")
    pCtx->common.pMode = pMode;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer to mcuxClCipherModes_AlgorithmDescriptor_SM4_t* types")
    mcuxClCipherModes_AlgorithmDescriptor_SM4_t *pAlgo = (mcuxClCipherModes_AlgorithmDescriptor_SM4_t *)pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    if ((MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC == pAlgo->mode) &&
            (MCUXCLOSCCACIPHER_DECRYPT == pAlgo->direction))
    {
        pCtx->out = 2u; pCtx->iv = 1u; pCtx->in = 0u;
    }
    else
    {
        pCtx->out = 0u; pCtx->iv = 1u; pCtx->in = 2u;
    }

    MCUX_CSSL_FP_FUNCTION_CALL(initResult, mcuxClOsccaCipherModes_SkeletonSM4_Init(pCtx, pKey, pIv, ivLength));
    if (MCUXCLCIPHER_STATUS_OK != initResult)
    {
        /* Free context in Session */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaCipherModes_Context_Sm4_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_OneShot, MCUXCLCIPHER_STATUS_ERROR,
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Init));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(processResult, mcuxClOsccaCipherModes_SkeletonSM4_Process(pCtx, pIn, inLength, pOut, pOutLength));
    if (MCUXCLCIPHER_STATUS_OK != processResult)
    {
        /* Free context in Session */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaCipherModes_Context_Sm4_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_OneShot, MCUXCLCIPHER_STATUS_ERROR,
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Process),
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Init));
    }
    MCUXCLBUFFER_UPDATE(pOut, *pOutLength);

    MCUX_CSSL_FP_FUNCTION_CALL(finishResult, mcuxClOsccaCipherModes_SkeletonSM4_Finish(pCtx, pOut, pOutLength));
    if (MCUXCLCIPHER_STATUS_OK != finishResult)
    {
        /* Free context in Session */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaCipherModes_Context_Sm4_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaCipherModes_SkeletonSM4_OneShot, MCUXCLCIPHER_STATUS_ERROR,
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Init),
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Process),
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Finish));
    }

    /* Free context in Session */
    mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaCipherModes_Context_Sm4_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaCipherModes_SkeletonSM4_OneShot, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Init),
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Process),
                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaCipherModes_SkeletonSM4_Finish));
}