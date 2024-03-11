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

/** @file  mcuxClOsccaMacModes_CBCMAC.c
 *  @brief implementation of the SM4 CBCMAC part of mcuxClOsccaMacModes component */

#include <mcuxClToolchain.h>
#include <mcuxClMac.h>
#include <mcuxClMemory.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <internal/mcuxClOsccaSm4_Internal_Constants.h>
#include <internal/mcuxClPadding_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClOsccaMacModes_Internal_Functions.h>
#include <internal/mcuxClOsccaMacModes_Types.h>
#include <internal/mcuxClOsccaMacModes_Ctx.h>
#include <internal/mcuxClOsccaMacModes_SM4_CBCMAC.h>
#include <internal/mcuxClOsccaMacModes_Algorithms.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
#ifdef MCUXCL_FEATURE_MACMODES_CBCMAC_SM4
const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_NoPadding = {
  .engineInit = mcuxClOsccaMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClOsccaMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClOsccaMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_None,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_None),
};

const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingISO9797_1_Method1 = {
  .engineInit = mcuxClOsccaMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClOsccaMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClOsccaMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method1,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method1),
};

const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingISO9797_1_Method2 = {
  .engineInit = mcuxClOsccaMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClOsccaMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClOsccaMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method2,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method2),
};

const mcuxClOsccaMacModes_AlgorithmDescriptor_t mcuxClOsccaMacModes_AlgorithmDescriptor_CBCMAC_SM4_PaddingPKCS7 = {
  .engineInit = mcuxClOsccaMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClOsccaMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClOsccaMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_PKCS7,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_PKCS7),
};
#endif /* MCUXCL_FEATURE_MACMODES_CBCMAC_SM4 */
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_Engine_CBCMAC_Init, mcuxClOsccaMac_InitEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_Engine_CBCMAC_Init(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClOsccaMacModes_Context_t * const pContext
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_Engine_CBCMAC_Init);
    mcuxClOsccaMacModes_Context_t* pCtx = (mcuxClOsccaMacModes_Context_t *)pContext;

    /* No IV input situation */
    MCUXCLMEMORY_FP_MEMORY_SET(pCtx->stateIv, 0x00u, MCUXCLOSCCASM4_BLOCK_SIZE);

    /* No partial data after init. */
    pCtx->nrOfUnprocessedBytes = 0u;
    pCtx->dataProcessed = 0u;
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaMacModes_Engine_CBCMAC_Init, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAILURE,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_Engine_CBCMAC_Update, mcuxClOsccaMac_UpdateEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_Engine_CBCMAC_Update(
    mcuxClSession_Handle_t session,
    mcuxClOsccaMacModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    mcuxClOsccaMacModes_Context_t* pCtx = (mcuxClOsccaMacModes_Context_t *)pContext;
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_Engine_CBCMAC_Update,
            MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM4_BLOCK_SIZE > (pCtx->nrOfUnprocessedBytes + inLength)), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)),
            MCUX_CSSL_FP_CONDITIONAL(((pCtx->nrOfUnprocessedBytes + inLength) >= MCUXCLOSCCASM4_BLOCK_SIZE),
               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_ScheduleSM4Key),
               MCUX_CSSL_FP_CONDITIONAL((0u != pCtx->nrOfUnprocessedBytes), MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM4_BLOCK_SIZE > pCtx->nrOfUnprocessedBytes),MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)),
                                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor),
                                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine))));

    uint32_t lastBlockRemainingBytes = 0u;
    uint32_t fullBlocksRemainingBytes = 0u;
    uint32_t inOffset = 0u;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("(pCtx->nrOfUnprocessedBytes + inLength) can't be larger than max(uint32_t)")
    if(MCUXCLOSCCASM4_BLOCK_SIZE > (pCtx->nrOfUnprocessedBytes + inLength))
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    {
        /* Store bytes in context */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, inOffset, pCtx->stateIn + pCtx->nrOfUnprocessedBytes, inLength));
        (void)statusBufferRead; // No need to check it because the function only returns OK.
        pCtx->nrOfUnprocessedBytes += inLength;
        pCtx->dataProcessed += inLength;
    }
    else /* At least one block of data to process */
    {
        uint32_t* pRoundKeys = (uint32_t*)mcuxClSession_allocateWords_cpuWa(session,  MCUXCLOSCCASM4_RK_WORDS);
        if(NULL == pRoundKeys)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_FAILURE);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(setupResult, mcuxClOsccaSm4_ScheduleSM4Key(pRoundKeys, pCtx->pKey->container.pData, MCUXCLOSCCASM4_ENCRYPT));
        if(MCUXCLOSCCASM4_STATUS_LOADKEY_OK != setupResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_FAILURE);
        }

        if(0u != pCtx->nrOfUnprocessedBytes) /* Process 1 block from context */
        {
            if(MCUXCLOSCCASM4_BLOCK_SIZE > pCtx->nrOfUnprocessedBytes)
            {
                uint32_t emptyBytes = MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->nrOfUnprocessedBytes;
                /* Add new data into the partial data buffer and process */
                MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, inOffset, pCtx->stateIn + pCtx->nrOfUnprocessedBytes, emptyBytes));
                (void)statusBufferRead; // No need to check it because the function only returns OK.

                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("inLength must be larger than emptyBytes and pCtx->dataProcessed, inOffset += emptyBytes can't be larger than max(uint32_t)")
                /* The bytes copied already should not be taken into account further. */
                inOffset += emptyBytes;
                pCtx->dataProcessed += emptyBytes;
                inLength -= emptyBytes;
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            }

            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->stateIn, pCtx->stateIn, pCtx->stateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
            MCUX_CSSL_FP_FUNCTION_CALL(engineRet, mcuxClOsccaSm4_Engine(pRoundKeys, pCtx->stateIn, pCtx->stateIv, MCUXCLOSCCASM4_ENCRYPT));
            if(engineRet != MCUXCLOSCCASM4_STATUS_CRYPT_OK)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_FAILURE);
            }

            /* The partial data buffer is now empty. */
            pCtx->nrOfUnprocessedBytes = 0u;
        }

        /* Process remaining full blocks from input buffer */
        lastBlockRemainingBytes = inLength % MCUXCLOSCCASM4_BLOCK_SIZE;
        fullBlocksRemainingBytes = inLength - lastBlockRemainingBytes;
        while((fullBlocksRemainingBytes / MCUXCLOSCCASM4_BLOCK_SIZE) > 0U)
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pIn[inOffset] can't exceed the pIn buffer")
            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, inOffset, pCtx->stateIn, MCUXCLOSCCASM4_BLOCK_SIZE));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            (void)statusBufferRead; // No need to check it because the function only returns OK.

            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->stateIn, pCtx->stateIn, pCtx->stateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
            MCUX_CSSL_FP_FUNCTION_CALL(engineRet, mcuxClOsccaSm4_Engine(pRoundKeys, pCtx->stateIn, pCtx->stateIv, MCUXCLOSCCASM4_ENCRYPT));
            if(engineRet != MCUXCLOSCCASM4_STATUS_CRYPT_OK)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_FAILURE);
            }

            /* The bytes copied already should not be taken into account further. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("inOffset += MCUXCLOSCCASM4_BLOCK_SIZE can't be larger than max(uint32_t) duo to inLength <= max(uint32_t)")
            inOffset += MCUXCLOSCCASM4_BLOCK_SIZE;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            fullBlocksRemainingBytes -= MCUXCLOSCCASM4_BLOCK_SIZE;
            pCtx->dataProcessed += MCUXCLOSCCASM4_BLOCK_SIZE;
        }

        if(0U != lastBlockRemainingBytes)
        {
            /* Add last data into the partial data buffer*/
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pIn[inOffset] can't exceed the pIn buffer")
            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, inOffset, pCtx->stateIn, lastBlockRemainingBytes));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            (void)statusBufferRead; // No need to check it because the function only returns OK.

            pCtx->nrOfUnprocessedBytes = lastBlockRemainingBytes;
            pCtx->dataProcessed += lastBlockRemainingBytes;
        }
        /* Free CPU WA */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM4_RK_WORDS);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAILURE,
            ((inLength - lastBlockRemainingBytes) / MCUXCLOSCCASM4_BLOCK_SIZE) * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)
                                                                                + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)
                                                                                + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine)),
            MCUX_CSSL_FP_CONDITIONAL((0U != lastBlockRemainingBytes), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize, mcuxClOsccaMac_FinishEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_Engine_CBCMAC_Finalize(
    mcuxClSession_Handle_t session,
    mcuxClOsccaMacModes_Context_t * const pContext,
    mcuxCl_Buffer_t pOut,
    uint32_t *const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize);
    mcuxClOsccaMacModes_Context_t* pCtx = (mcuxClOsccaMacModes_Context_t *)pContext;
    mcuxClOsccaMacModes_Algorithm_t pAlgo = (mcuxClOsccaMacModes_Algorithm_t) pCtx->common.pMode->common.pAlgorithm;

    /* Number of bytes added by the padding. */
    uint32_t padOutLength = 0u;

    /* Apply the padding function, for CBCMAC */
    MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(MCUXCLOSCCASM4_BLOCK_SIZE, pCtx->stateIn, pCtx->nrOfUnprocessedBytes,
                                         pCtx->dataProcessed, pCtx->stateIn, &padOutLength));
    if (padResult != MCUXCLPADDING_STATUS_OK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_FAILURE);
    }
    if (padOutLength > 0u)
    {
      uint32_t* pRoundKeys = (uint32_t*)mcuxClSession_allocateWords_cpuWa(session,  MCUXCLOSCCASM4_RK_WORDS);
      if(NULL == pRoundKeys)
      {
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_FAILURE);
      }
      MCUX_CSSL_FP_FUNCTION_CALL(setupResult, mcuxClOsccaSm4_ScheduleSM4Key(pRoundKeys, pCtx->pKey->container.pData, MCUXCLOSCCASM4_ENCRYPT));
      if(MCUXCLOSCCASM4_STATUS_LOADKEY_OK != setupResult)
      {
          MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pRoundKeys, MCUXCLOSCCASM4_RK_WORDS * sizeof(uint32_t));
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_FAILURE);
      }

      /* If padding was added, process the data in the partial data buffer. */
      MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pCtx->stateIn, pCtx->stateIn, pCtx->stateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
      MCUX_CSSL_FP_FUNCTION_CALL(engineRet, mcuxClOsccaSm4_Engine(pRoundKeys, pCtx->stateIn, pCtx->stateIv, MCUXCLOSCCASM4_ENCRYPT));
      if(engineRet != MCUXCLOSCCASM4_STATUS_CRYPT_OK)
      {
          MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pRoundKeys, MCUXCLOSCCASM4_RK_WORDS * sizeof(uint32_t));
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_FAILURE);
      }
      /* Copy the padding to the output and update pOutLength accordingly. */
      MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, pCtx->stateIv, padOutLength));
      (void)statusBufferWrite; // No need to check it because the function only returns OK.

      MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
      *pOutLength += padOutLength;
      MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

      /* Free CPU WA */
      MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pRoundKeys, MCUXCLOSCCASM4_RK_WORDS * sizeof(uint32_t));
      mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM4_RK_WORDS);
    }
    else
    {
      /* Copy the output and update pOutLength accordingly. */
      MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, pCtx->stateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
      (void)statusBufferWrite; // No need to check it because the function only returns OK.

      MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
      *pOutLength += MCUXCLOSCCASM4_BLOCK_SIZE;
      MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAILURE,
              pAlgo->protectionToken_addPadding,
              MCUX_CSSL_FP_CONDITIONAL((padOutLength > 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor),
                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_ScheduleSM4Key),
                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine)),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write)
              );
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, mcuxClOsccaMac_ComputeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot(
    mcuxClSession_Handle_t session,            /*! CBC-MAC session handle */
    mcuxClMac_Mode_t mode,
    mcuxClKey_Handle_t key,
    mcuxCl_InputBuffer_t pIn,                                /*! CBC-MAC input */
    uint32_t inLength,                                      /*! Input size */
    mcuxCl_Buffer_t pOut,                                    /*! CBC-MAC output */
    uint32_t *const pOutLength                              /*! Output size */
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_ScheduleSM4Key),
                                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
    mcuxClOsccaMacModes_Algorithm_t pAlgo = (mcuxClOsccaMacModes_Algorithm_t) mode->common.pAlgorithm;
    uint32_t* pCbcMacOneshotBuf = (uint32_t*)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM4_BLOCK_SIZE_WORDS * 2u + MCUXCLOSCCASM4_RK_WORDS);
    if(NULL == pCbcMacOneshotBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_FAILURE);
    }

    uint32_t* pRoundKeys = pCbcMacOneshotBuf;
    uint8_t *pStateIn = (uint8_t*)(pRoundKeys + MCUXCLOSCCASM4_RK_WORDS);
    uint8_t *pStateIv = pStateIn + MCUXCLOSCCASM4_BLOCK_SIZE;

    MCUX_CSSL_FP_FUNCTION_CALL(setupResult, mcuxClOsccaSm4_ScheduleSM4Key(pRoundKeys, key->container.pData, MCUXCLOSCCASM4_ENCRYPT));
    if(MCUXCLOSCCASM4_STATUS_LOADKEY_OK != setupResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_FAILURE);
    }

    /* No IV input situation */
    MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pOut, 0u, pStateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
    (void)statusBufferRead; // No need to check it because the function only returns OK.

    uint32_t inLenOri = inLength;
    uint32_t inOffset = 0u;
    while(inLenOri >= MCUXCLOSCCASM4_BLOCK_SIZE)
    {
        /* Add data into the pState buffer and process */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead1, mcuxClBuffer_read(pIn, inOffset, pStateIn, MCUXCLOSCCASM4_BLOCK_SIZE));
        (void)statusBufferRead1; // No need to check it because the function only returns OK.

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pStateIn, pStateIn, pStateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
        MCUX_CSSL_FP_FUNCTION_CALL(engineRet, mcuxClOsccaSm4_Engine(pRoundKeys, pStateIn, pStateIv, MCUXCLOSCCASM4_ENCRYPT));
        if(engineRet != MCUXCLOSCCASM4_STATUS_CRYPT_OK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_FAILURE);
        }

        /* The bytes copied already should not be taken into account further. */
        inLenOri -= MCUXCLOSCCASM4_BLOCK_SIZE;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("inOffset += MCUXCLOSCCASM4_BLOCK_SIZE can't be larger than max(uint32_t) duo to inLength <= max(uint32_t)")
        inOffset += MCUXCLOSCCASM4_BLOCK_SIZE;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    if (inLenOri != 0u)
    {
        // Get input data for last block
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead2, mcuxClBuffer_read(pIn, inOffset, pStateIn, inLenOri));
        (void)statusBufferRead2; // No need to check it because the function only returns OK.
    }

    /* Number of bytes added by the padding. */
    uint32_t padOutLength = 0u;
    /* Apply the padding function specified in the mode on the partial data. */
    MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(MCUXCLOSCCASM4_BLOCK_SIZE, pStateIn, inLenOri,
                                         inLength, pStateIn, &padOutLength));
    if (padResult != MCUXCLPADDING_STATUS_OK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_FAILURE);
    }

    if (padOutLength > 0u)
    {
        /* If padding was added, process the data in the pStateIn buffer. */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_FastSecureXor(pStateIn, pStateIn, pStateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
        MCUX_CSSL_FP_FUNCTION_CALL(engineRet, mcuxClOsccaSm4_Engine(pRoundKeys, pStateIn, pStateIv, MCUXCLOSCCASM4_ENCRYPT));
        if(engineRet != MCUXCLOSCCASM4_STATUS_CRYPT_OK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_FAILURE);
        }
        /* Copy the padding to the output and update pOutLength accordingly. */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, pStateIv, padOutLength));
        (void)statusBufferWrite; // No need to check it because the function only returns OK.

        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
        *pOutLength += padOutLength;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }
    else
    {
        /* Copy the padding to the output and update pOutLength accordingly. */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, pStateIv, MCUXCLOSCCASM4_BLOCK_SIZE));
        (void)statusBufferWrite; // No need to check it because the function only returns OK.

        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
        *pOutLength += MCUXCLOSCCASM4_BLOCK_SIZE;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    /* Free CPU WA */
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCbcMacOneshotBuf, sizeof(uint32_t) * (MCUXCLOSCCASM4_BLOCK_SIZE_WORDS * 2u + MCUXCLOSCCASM4_RK_WORDS));
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM4_BLOCK_SIZE_WORDS * 2u + MCUXCLOSCCASM4_RK_WORDS);
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAILURE,
           (inLength / MCUXCLOSCCASM4_BLOCK_SIZE) * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)
                                                    + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor)
                                                    + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine)),
           MCUX_CSSL_FP_CONDITIONAL((inLenOri > 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)),
           pAlgo->protectionToken_addPadding,
           MCUX_CSSL_FP_CONDITIONAL((padOutLength > 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_FastSecureXor),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Engine)
                                  ),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write)
          );
}
