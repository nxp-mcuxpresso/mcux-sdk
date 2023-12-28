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

/** @file  mcuxClAeadModes_Els_AesGcm.c
 *  @brief Implementation of the AES GCM skeleton functions of the mcuxClAeadModes component */

#include <mcuxClAead.h>
#include <internal/mcuxClAeadModes_Els_Types.h>
#include <internal/mcuxClAeadModes_Els_Functions.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxClKey.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEls.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClAes.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_SkeletonAesGcm)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAeadModes_SkeletonAesGcm(
    mcuxClSession_Handle_t session,
    mcuxClAeadModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pNonce,
    uint32_t nonceLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_InputBuffer_t pAdata,
    uint32_t adataLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    mcuxCl_Buffer_t pTag,
    uint32_t tagLength,
    uint32_t options //!< options is a bitmask with one bit reserved for each of the operations
    )
{
    /* [Design]
        ATTN: pOutLength will be _incremented_ by the number of bytes of encrypted data that have been
              written to the @p pOut buffer. Except otherwise mentioned processing steps _output_ data
              to pOut and update pOutLength

        - Preconditions
            - aadLength in context has been initialized
            - dataLength in context has been initialized
            - tagLength in context has been initialized
            - key in context has been initialized
            - mode in context has been initialized
            - processedDataLength in context has been initialized and maintained

        - Context usage:
            - the state contains both the counter and the partial MAC

        - Common IV processing (options == oneshot / init)
            - set partialDataLength in context to zero
            - process IV with ELS and output to state in context
                - if the IV length is not 12 use using pEngine(option:iv) to process the complete blocks
                - partialData can be used to padd the IV since it is not used at this time

        - AAD processing (options == oneshot / update aad)
            - if partialDataLength != 0 add the new data from the input to partialData and process using pEngine(option:aad)
              if possible,adapt partialDataLength and processedDataLength (this will never be the case for oneshot)
            - process remaining complete blocks using pEngine(option:aad) from the input, adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength (this can happen
              for oneshot)
            - [Assertion] aadLength <= processedDataLength
            - if aadLength == processedDataLength padd partialData with zeros and process using pEngine(option:aad), set
              partialDataLength to zero

        - Data processing (options == oneshot / update data)
            - if partialDataLength != 0 add the new data from the input to partialData and process using pEngine(option:data)
              if possible,adapt partialDataLength and processedDataLength (this will never be the case for oneshot)
            - process remaining complete blocks using pEngine(option:data)from the input, adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength (this can happen
              for oneshot)
            - [Assertion] aadLength + dataLength  <= processedDataLength
            - if aadLength + dataLength == processedDataLength padd partialData with zeros
              and process using pEngine(option:data), set partialDataLength to zero

        - Finalization processing (options == oneshot / finish / verify)
            - if partialDataLength != 0 exit with ERROR
            - perform the finalize processing using pEngine(option:finish), store tag in partialData in context

        - Finalization processing (options == oneshot / finish)
            - copy tagLength bytes from partialData to the tag
            - clean up context

        - Finalization processing (options == verify)
            - compare tagLength bytes from partialData to the tag
            - clean up context

        - exit
    */

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_SkeletonAesGcm);

    const mcuxClAeadModes_AlgorithmDescriptor_t* const pAlgo = pContext->common.mode->algorithm;

    uint32_t bytesToCopy = 0u;
    uint32_t bytesCopied = 0u;
    uint32_t bytesFullIvBlocks = 0u;
    uint32_t bytesRemainingAad = 0u;
    uint32_t bytesRemainingData = 0u;

/*
        - Common IV processing (options == oneshot / init)
            - set partialDataLength in context to zero
            - process IV with ELS and output to state in context
                - if the IV length is not 12 use using pEngine(option:iv) to process the complete blocks
                - partialData can be used to padd the IV since it is not used at this time
*/

    /* Number of bytes added by the padding. */
    uint32_t padOutLength = 0u;
    if ((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_INIT))
    {
        pContext->partialDataLength = 0u;

        if (nonceLength != 12u)
        {
            uint32_t engineOptions = MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START;

            /* If nonce is not 12 bytes, perform a partial init. Start with the full blocks of the IV */
            bytesFullIvBlocks = (nonceLength / MCUXCLAES_BLOCK_SIZE) * MCUXCLAES_BLOCK_SIZE;
            if(0u != bytesFullIvBlocks)
            {
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                MCUX_CSSL_FP_FUNCTION_CALL(retIV, pAlgo->pEngine(session, pContext,
                                                                   pNonce,
                                                                   bytesFullIvBlocks,
                                                                   NULL,
                                                                   NULL,
                                                                   engineOptions));
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

                if(MCUXCLAEAD_STATUS_OK != retIV)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
                }

                engineOptions = MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_CONT;
            }

            MCUX_CSSL_FP_FUNCTION_CALL(padResult, mcuxClPadding_addPadding_ISO9797_1_Method1(MCUXCLELS_AEAD_IV_BLOCK_SIZE,
                                                                                           pNonce + bytesFullIvBlocks,
                                                                                           nonceLength - bytesFullIvBlocks,
                                                                                           nonceLength,
                                                                                           pContext->partialData,
                                                                                           &padOutLength));

            if (MCUXCLPADDING_STATUS_OK != padResult)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }

            if(MCUXCLELS_AEAD_IV_BLOCK_SIZE == padOutLength)
            {
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                MCUX_CSSL_FP_FUNCTION_CALL(retIV, pAlgo->pEngine(session, pContext,
                                                                    pContext->partialData,
                                                                    MCUXCLELS_AEAD_IV_BLOCK_SIZE,
                                                                    NULL,
                                                                    NULL,
                                                                    engineOptions));
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

                if(MCUXCLAEAD_STATUS_OK != retIV)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
                }

                engineOptions = MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_CONT;
            }


            MCUXCLMEMORY_FP_MEMORY_SET(pContext->partialData, 0u, MCUXCLELS_AEAD_IV_BLOCK_SIZE);

            /* Set nonce length in bits. */
            pContext->partialData[15] = (uint8_t)(nonceLength <<  3u);
            pContext->partialData[14] = (uint8_t)(nonceLength >>  5u);
            pContext->partialData[13] = (uint8_t)(nonceLength >> 13u);
            pContext->partialData[12] = (uint8_t)(nonceLength >> 21u);
            pContext->partialData[11] = (uint8_t)(nonceLength >> 29u);

            /* Finish the nonce initialization. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
            MCUX_CSSL_FP_FUNCTION_CALL(retIVFinal, pAlgo->pEngine(session, pContext,
                                                                          pContext->partialData,
                                                                          MCUXCLELS_AEAD_IV_BLOCK_SIZE,
                                                                          NULL,
                                                                          NULL,
                                                                          engineOptions | MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

            if(MCUXCLAEAD_STATUS_OK != retIVFinal)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }
        }
        else
        {
            /* Nonce is 12 bytes. Pad the nonce. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pContext->partialData,
                                                                   pNonce,
                                                                   12u,
                                                                   MCUXCLELS_AEAD_IV_BLOCK_SIZE);

            pContext->partialData[12] = 0x00u;
            pContext->partialData[13] = 0x00u;
            pContext->partialData[14] = 0x00u;
            pContext->partialData[15] = 0x01u;

            /* Do the nonce initialization. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
            MCUX_CSSL_FP_FUNCTION_CALL(retIV, pAlgo->pEngine(session, pContext,
                                                                     pContext->partialData,
                                                                     MCUXCLELS_AEAD_IV_BLOCK_SIZE,
                                                                     NULL,
                                                                     NULL,
                                                                     MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

            if(MCUXCLAEAD_STATUS_OK != retIV)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }
        }
    }


/*
        - AAD processing (options == oneshot / update aad)
            - if partialDataLength != 0 add the new data from the input to partialData and process using pEngine(option:aad)
              if possible,adapt partialDataLength and processedDataLength (this will never be the case for oneshot)
            - process remaining complete blocks using pEngine(option:aad) from the input, adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength (this can happen
              for oneshot)
            - [Assertion] aadLength <= processedDataLength
            - if aadLength == processedDataLength padd partialData with zeros and process using pEngine(option:aad), set
              partialDataLength to zero
*/
    //below variable definitions are used for flow protection of plaintext data process
    uint32_t aadProFPFlag = 0u;
    uint32_t aadProFPFlag1 = 0u;
    uint32_t aadProFPFlag2 = 0u;
    if ((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_PROCESS_AAD))
    {
        /* Number of bytes to possibly copy into the partial data buffer, which is min(free buffer space, new data). */
        bytesToCopy = (((MCUXCLELS_AEAD_AAD_BLOCK_SIZE - pContext->partialDataLength) < (adataLength)) ?
                                (MCUXCLELS_AEAD_AAD_BLOCK_SIZE - pContext->partialDataLength) : (adataLength));

        if (pContext->partialDataLength != 0u)
        {
            aadProFPFlag1 = 1u;
            /* Add new data into the partial data buffer and process, if possible. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pContext->partialData + pContext->partialDataLength,
                                                                   pAdata,
                                                                   bytesToCopy,
                                                                   MCUXCLELS_AEAD_AAD_BLOCK_SIZE);

            /* Update the number of bytes in the partial data buffer. */
            pContext->partialDataLength += bytesToCopy;

            if (MCUXCLELS_AEAD_AAD_BLOCK_SIZE == pContext->partialDataLength)
            {
                aadProFPFlag2 = 1u;
                /* partialData now contains a full block, so process it. */
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                MCUX_CSSL_FP_FUNCTION_CALL(retAad, pAlgo->pEngine(session, pContext,
                                                                   pContext->partialData,
                                                                   MCUXCLELS_AEAD_AAD_BLOCK_SIZE,
                                                                   NULL,
                                                                   NULL,
                                                                   MCUXCLAEADMODES_ENGINE_OPTION_AAD));
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

                if(MCUXCLAEAD_STATUS_OK != retAad)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
                }

                /* The partial data buffer is now empty. */
                pContext->partialDataLength = 0u;

            }

            /* The bytes copied already should not be taken into account further. */
            bytesCopied += bytesToCopy;
            adataLength -= bytesToCopy;
            pContext->processedDataLength += bytesToCopy;
        }

        bytesRemainingAad = (adataLength / MCUXCLELS_AEAD_AAD_BLOCK_SIZE) * MCUXCLELS_AEAD_AAD_BLOCK_SIZE;
        if(0u != bytesRemainingAad)
        {
            /* Process as many remaining full blocks as possible. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
            MCUX_CSSL_FP_FUNCTION_CALL(retBlkAad, pAlgo->pEngine(session, pContext,
                                                                         pAdata + bytesCopied,
                                                                         bytesRemainingAad,
                                                                         NULL,
                                                                         NULL,
                                                                         MCUXCLAEADMODES_ENGINE_OPTION_AAD));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

            if(MCUXCLAEAD_STATUS_OK != retBlkAad)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }

            /* The bytes copied already should not be taken into account further. */
            bytesCopied += bytesRemainingAad;
            pContext->processedDataLength += bytesRemainingAad;
        }

        bytesRemainingAad = adataLength - bytesRemainingAad;
        if (0u != bytesRemainingAad)
        {
            /* If there is still data in the input, copy it to the partial data buffer for the next iteration. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pContext->partialData,
                                                                   pAdata + bytesCopied,
                                                                   bytesRemainingAad,
                                                                   MCUXCLELS_AEAD_AAD_BLOCK_SIZE);

            pContext->partialDataLength = bytesRemainingAad;
            pContext->processedDataLength += bytesRemainingAad;
        }

        //Check if we done all adata and if we have some remaining data in buffer, this is for
        //the last adata block processing, add zero padding and calc
        if((pContext->processedDataLength == pContext->aadLength) && (0u != pContext->partialDataLength))
        {
            aadProFPFlag = 1u;
            /* There is still AAD which needs to be zero-padded and processed. */
            MCUXCLMEMORY_FP_MEMORY_SET_WITH_BUFF(pContext->partialData + pContext->partialDataLength, 0u, MCUXCLELS_AEAD_AAD_BLOCK_SIZE - pContext->partialDataLength, MCUXCLELS_AEAD_AAD_BLOCK_SIZE);

            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
            MCUX_CSSL_FP_FUNCTION_CALL(retPadAad, pAlgo->pEngine(session, pContext,
                                                                  pContext->partialData,
                                                                  MCUXCLELS_AEAD_AAD_BLOCK_SIZE,
                                                                  NULL,
                                                                  NULL,
                                                                  MCUXCLAEADMODES_ENGINE_OPTION_AAD));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

            if(MCUXCLAEAD_STATUS_OK != retPadAad)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }

            pContext->partialDataLength = 0u;
        }

    }

/*
        - Data processing (options == oneshot / update data)
            - if partialDataLength != 0 add the new data from the input to partialData and process using pEngine(option:data)
              if possible,adapt partialDataLength and processedDataLength (this will never be the case for oneshot)
            - process remaining complete blocks using pEngine(option:data)from the input, adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength (this can happen
              for oneshot)
            - [Assertion] aadLength + dataLength  <= processedDataLength
            - if aadLength + dataLength == processedDataLength padd partialData with zeros
              and process using pEngine(option:data), set partialDataLength to zero
*/

    //below variable definitions are used for flow protection of plaintext data process
    uint32_t dataProFPFlag = 0u;
    uint32_t dataProFPFlag1 = 0u;
    uint32_t dataProFPFlag2 = 0u;
    uint8_t *pOutput = pOut;
    if ((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_PROCESS))
    {
        /* Number of bytes to possibly copy into the partial data buffer. */
        bytesCopied = 0u;
        bytesToCopy = (((MCUXCLAES_BLOCK_SIZE - pContext->partialDataLength) < (inLength)) ?
                        (MCUXCLAES_BLOCK_SIZE - pContext->partialDataLength) : (inLength));

        if (pContext->partialDataLength != 0u)
        {
            dataProFPFlag1 = 1u;
            /* Process input data. */
            /* Add new data into the partial data buffer and process, if possible. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pContext->partialData + pContext->partialDataLength,
                                                                   pIn,
                                                                   bytesToCopy,
                                                                   MCUXCLAES_BLOCK_SIZE);

            /* Update the number of bytes in the partial data buffer. */
            pContext->partialDataLength += bytesToCopy;

            if (MCUXCLAES_BLOCK_SIZE == pContext->partialDataLength)
            {
                dataProFPFlag2 = 1u;
                /* partialData now contains a full block, so process it. */
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                MCUX_CSSL_FP_FUNCTION_CALL(retData, pAlgo->pEngine(session, pContext,
                                                                             pContext->partialData,
                                                                             MCUXCLAES_BLOCK_SIZE,
                                                                             pOutput,
                                                                             NULL,
                                                                             MCUXCLAEADMODES_ENGINE_OPTION_DATA));
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

                if(MCUXCLAEAD_STATUS_OK != retData)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
                }

                /* The partial data buffer is now empty. */
                pContext->partialDataLength = 0u;

                /* Write to pOutLength how many bytes have been written, and update the output buffer */
                *pOutLength += MCUXCLAES_BLOCK_SIZE;
                pOutput += MCUXCLAES_BLOCK_SIZE;
            }

            /* The bytes copied already should not be taken into account further. */
            pContext->processedDataLength += bytesToCopy;
            bytesCopied += bytesToCopy;
            inLength -= bytesToCopy;
        }

        bytesRemainingData = (inLength / MCUXCLAES_BLOCK_SIZE) * MCUXCLAES_BLOCK_SIZE;
        if(0u != bytesRemainingData)
        {
            /* Process as many remaining full blocks as possible. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
            MCUX_CSSL_FP_FUNCTION_CALL(retBlkData, pAlgo->pEngine(session, pContext,
                                                                     pIn + bytesCopied,
                                                                     bytesRemainingData,
                                                                     pOutput,
                                                                     NULL,
                                                                     MCUXCLAEADMODES_ENGINE_OPTION_DATA));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

            if(MCUXCLAEAD_STATUS_OK != retBlkData)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }

            pContext->processedDataLength += bytesRemainingData;
            /* The bytes copied already should not be taken into account further. */
            bytesCopied += bytesRemainingData;
            /* Write to pOutLength how many bytes have been written. */
            *pOutLength += bytesRemainingData;
            pOutput += bytesRemainingData;
        }

        bytesRemainingData = inLength - bytesRemainingData;
        if (0u != bytesRemainingData)
        {
            /* If there is still data in the input, copy it to the partial data buffer for the next iteration. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pContext->partialData,
                                                                pIn + bytesCopied,
                                                                bytesRemainingData,
                                                                MCUXCLAES_BLOCK_SIZE);
            pContext->partialDataLength = bytesRemainingData;
            pContext->processedDataLength += bytesRemainingData;
        }

        //Check if we done all input data and if we have some remaining data in buffer, this is for
        //the last input data block processing, add zero padding and calc
        if((pContext->processedDataLength == pContext->dataLength + pContext->aadLength) && (0u != pContext->partialDataLength))
        {
            dataProFPFlag = 1u;
            /* There is still data which needs to be zero-padded and processed. */
            MCUXCLMEMORY_FP_MEMORY_SET_WITH_BUFF(pContext->partialData + pContext->partialDataLength, 0u, MCUXCLAES_BLOCK_SIZE - pContext->partialDataLength, MCUXCLAES_BLOCK_SIZE);

            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
            MCUX_CSSL_FP_FUNCTION_CALL(redFinalData, pAlgo->pEngine(session, pContext,
                                                                     pContext->partialData,
                                                                     MCUXCLAES_BLOCK_SIZE,
                                                                     pOutput,
                                                                     NULL,
                                                                     MCUXCLAEADMODES_ENGINE_OPTION_DATA_FINAL));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

            if(MCUXCLAEAD_STATUS_OK != redFinalData)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
            }

            /* Write to pOutLength how many bytes have been processed. */
            *pOutLength += pContext->partialDataLength;

            /* The partial data buffer is now empty. */
            pContext->partialDataLength = 0u;
        }

    }

/*
        - Finalization processing (options == oneshot / finish / verify)
            - if partialDataLength != 0 exit with ERROR
            - perform the finalize processing using pEngine(option:finish), store tag in partialData in context
*/

    if ((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_FINISH) || (options == MCUXCLAEADMODES_OPTION_VERIFY))
    {
        if (pContext->partialDataLength != 0u)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
        }

        /* Call the finalize function. */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
        MCUX_CSSL_FP_FUNCTION_CALL(retFinal, pAlgo->pEngine(session, pContext,
                                                                   NULL,
                                                                   0u,
                                                                   pContext->partialData,
                                                                   NULL,
                                                                   MCUXCLAEADMODES_ENGINE_OPTION_FINISH));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

        if(MCUXCLAEAD_STATUS_OK != retFinal)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
        }
    }

/*
        - Finalization processing (options == oneshot / finish)
            - copy tagLength bytes from partialData to the tag
            - clean up context
*/
    if ((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_FINISH))
    {
        MCUXCLMEMORY_FP_MEMORY_COPY(pTag,pContext->partialData,tagLength);
    }

    // TODO: clean up context?

/*
        - Finalization processing (options == verify)
            - compare tagLength bytes from partialData to the tag
            - clean up context

        - exit
*/
    if (options == MCUXCLAEADMODES_OPTION_VERIFY)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(compare_result, mcuxCsslMemory_Compare(mcuxCsslParamIntegrity_Protect(3u, pTag, pContext->partialData, tagLength),
                                                                      pTag,
                                                                      pContext->partialData,
                                                                      tagLength));

        if(compare_result != MCUXCSSLMEMORY_STATUS_EQUAL)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
        }

    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL(((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_INIT)),
            MCUX_CSSL_FP_CONDITIONAL((nonceLength != 12u), MCUX_CSSL_FP_CONDITIONAL((0u != bytesFullIvBlocks), pAlgo->protection_token_engine),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method1),
                                                        MCUX_CSSL_FP_CONDITIONAL((MCUXCLELS_AEAD_IV_BLOCK_SIZE == padOutLength), pAlgo->protection_token_engine),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set)
            ),
            MCUX_CSSL_FP_CONDITIONAL((nonceLength == 12u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
            pAlgo->protection_token_engine
        ),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_PROCESS_AAD))),
            MCUX_CSSL_FP_CONDITIONAL((aadProFPFlag1 == 1u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_CONDITIONAL((aadProFPFlag2 == 1u), pAlgo->protection_token_engine)
            ),
            MCUX_CSSL_FP_CONDITIONAL((0u != ((adataLength / MCUXCLELS_AEAD_AAD_BLOCK_SIZE) * MCUXCLELS_AEAD_AAD_BLOCK_SIZE)), pAlgo->protection_token_engine),
            MCUX_CSSL_FP_CONDITIONAL((bytesRemainingAad != 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
            MCUX_CSSL_FP_CONDITIONAL((aadProFPFlag != 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                                          pAlgo->protection_token_engine)
        ),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_PROCESS))),
            MCUX_CSSL_FP_CONDITIONAL((dataProFPFlag1 == 1u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_CONDITIONAL((dataProFPFlag2 == 1u), pAlgo->protection_token_engine)
            ),
            MCUX_CSSL_FP_CONDITIONAL((0u != ((inLength / MCUXCLAES_BLOCK_SIZE) * MCUXCLAES_BLOCK_SIZE)), pAlgo->protection_token_engine),
            MCUX_CSSL_FP_CONDITIONAL((bytesRemainingData != 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
            MCUX_CSSL_FP_CONDITIONAL((dataProFPFlag != 0u), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                                           pAlgo->protection_token_engine)
        ),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_FINISH) || (options == MCUXCLAEADMODES_OPTION_VERIFY))),
            pAlgo->protection_token_engine
        ),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLAEADMODES_OPTION_ONESHOT) || (options == MCUXCLAEADMODES_OPTION_FINISH))),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
        ),
        MCUX_CSSL_FP_CONDITIONAL(((options == MCUXCLAEADMODES_OPTION_VERIFY)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare)
        )
    );
}
