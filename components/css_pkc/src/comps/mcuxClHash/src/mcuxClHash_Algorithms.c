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

#include <mcuxClHash.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCss.h>

/* Writes the correct hash mode to the hashOptions struct, based on the hashSize parameter */
static inline mcuxClHash_Status_t selectHashMode(uint32_t hashSize, mcuxClCss_HashOption_t *hashOptions)
{
    switch(hashSize)
    {
        case MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_224:
            hashOptions->bits.hashmd = MCUXCLCSS_HASH_MODE_SHA_224;
            break;
        case MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_256:
            hashOptions->bits.hashmd = MCUXCLCSS_HASH_MODE_SHA_256;
            break;
        case MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_384:
            hashOptions->bits.hashmd = MCUXCLCSS_HASH_MODE_SHA_384;
            break;
        case MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_512:
            hashOptions->bits.hashmd = MCUXCLCSS_HASH_MODE_SHA_512;
            break;
        default:
            return MCUXCLHASH_STATUS_ERROR;
    }
    return MCUXCLHASH_STATUS_OK;
}

/* Writes the correct RTF flags to the hashOptions struct, based on the rtf parameter */
static inline mcuxClHash_Status_t selectRtfFlags(mcuxClSession_Rtf_t rtf, mcuxClCss_HashOption_t *hashOptions)
{
    /* Set RTF processing options */
    if(MCUXCLSESSION_RTF_UPDATE_TRUE == rtf)
    {
        hashOptions->bits.rtfupd = MCUXCLCSS_HASH_RTF_UPDATE_ENABLE;
    }
    else if(MCUXCLSESSION_RTF_UPDATE_FALSE == rtf)
    {
        hashOptions->bits.rtfupd = MCUXCLCSS_HASH_RTF_UPDATE_DISABLE;
    }
    else
    {
        return MCUXCLHASH_STATUS_ERROR;
    }
    return MCUXCLHASH_STATUS_OK;
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_skeletonSha2)
static mcuxClHash_Status_Protected_t mcuxClHash_skeletonSha2 (
                        mcuxClSession_Handle_t session,
                        const mcuxClHash_Algo_t *algo,
                        mcuxClHash_ContextData_t *context,
                        mcuxClHash_ContextBuffer_t *buffer,
                        const uint8_t *const in,
                        uint32_t inSize,
                        uint8_t *const out,
                        uint8_t *const rtf,
                        uint32_t options
                        )
{
    /*
        General flow of full implementation (i.e. including accumulation, partial processing)
        - set options for initialization, continuation from external state, or from internal state
        - one call to engine to process data in the accumulation buffer + start of new data, if there
          was data in the accumulation buffer, disable initialization/state loading  if data was processed
        - one call to engine to process the middle blocks with state export set if requested and no
          finalization is requested
        - one or two calls to engine to process the final block with padding added with state export set,
          if finalization requested
    */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_skeletonSha2);

    (void)options; // parameter not used: This oneshot only function has no mode switch.
    (void)context; // parameter not used: This oneshot only function needs no context.
    (void)buffer; // parameter not used: This oneshot only function needs no context buffer.

    /* Start setting initial options for CSS hash */
    mcuxClCss_HashOption_t hash_options;
    hash_options.word.value  = 0u;
    hash_options.bits.hashoe = MCUXCLCSS_HASH_OUTPUT_DISABLE;
    hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_ENABLE;
    hash_options.bits.hashld  = MCUXCLCSS_HASH_LOAD_DISABLE;

    /* Set RTF processing options */
    if(MCUXCLHASH_STATUS_OK != selectRtfFlags(session->rtf, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
    }

    /* Select CSS hash algorithm based on output hash output size */
    if(MCUXCLHASH_STATUS_OK != selectHashMode(algo->hashSize, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
    }

    /* Done setting the options for CSS hash! */

    /* All blocks can be processed in bulk directly from in */
    size_t const sizeOfFullBlocks = (inSize / algo->blockSize) * algo->blockSize;
    if (0u < sizeOfFullBlocks)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                        hash_options.word.value,
                        in, sizeOfFullBlocks,
                        NULL
                        ));

        if (MCUXCLHASH_STATUS_OK != result)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, result);
        }

        hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_DISABLE;
    }

    /* Pointer to the buffer where the last block of data is stored in the finalization phase */
    uint8_t *shablock = (uint8_t*) &(session->cpuWa.buffer[session->cpuWa.used]);
    size_t posdst = inSize - sizeOfFullBlocks;
    size_t buflen = algo->blockSize;

    /* There is no context buffer. Put the rest of the data in the workspace. */
    MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result1, mcuxClMemory_copy(shablock, &in[sizeOfFullBlocks], posdst, buflen));
    if(0u != memcopy_result1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
    }

    buflen -= posdst;
    // add first byte of the padding: (remaining) < (block length) so there is space in the buffer
    shablock[posdst] = 0x80u;
    posdst += 1u;
    buflen -= 1u;

    /* Process partial padded block if needed */
    if ( (algo->blockSize - algo->counterSize) < posdst ) // need room for 64 bit counter and one additional byte
    {
        MCUX_CSSL_FP_FUNCTION_CALL(memset_result1, mcuxClMemory_set(&shablock[posdst], 0x00, buflen, buflen));
        if(0u != memset_result1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
        }

        /* It is currently necessary to set buflen to algo->blockSize to distinguish whether this if-branch was taken
         * (for the conditional expectations in the exit statement!). Otherwise we could set it to posdst here and save
         * some performance overhead */
        buflen = algo->blockSize;
        posdst = 0u;

        MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                            hash_options.word.value,
                            shablock, algo->blockSize,
                            NULL
                            ));

        if (MCUXCLHASH_STATUS_OK != result)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, result);
        }

        hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_DISABLE;
    }

    /* Perform padding by adding data counter */
    MCUX_CSSL_FP_FUNCTION_CALL(memset_result2, mcuxClMemory_set(&shablock[posdst], 0x00, buflen, buflen));
    if(0u != memset_result2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
    }
    posdst = algo->blockSize;
    shablock[--posdst] = (uint8_t)(inSize <<  3u);
    shablock[--posdst] = (uint8_t)(inSize >>  5u);
    shablock[--posdst] = (uint8_t)(inSize >> 13u);
    shablock[--posdst] = (uint8_t)(inSize >> 21u);
    shablock[posdst-1u] = (uint8_t)(inSize >> 29u);

    /* Set output options */
    hash_options.bits.hashoe  = MCUXCLCSS_HASH_OUTPUT_ENABLE;
    hash_options.bits.rtfoe = hash_options.bits.rtfupd;

    /* Process last block */
    MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                    hash_options.word.value,
                    shablock, algo->blockSize,
                    shablock // shablock is large enough to hold internal state of hash algorithm + RTF
    ));

    if (MCUXCLHASH_STATUS_OK != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, result);
    }


    /* Copy RTF to corresponding buffer */
    if(MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result2, mcuxClMemory_copy(rtf, &shablock[algo->hashSize], algo->rtfSize,  algo->rtfSize));
        if(0u != memcopy_result2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
        }
    }

    /* Copy hash digest to output buffer */
    MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result3, mcuxClMemory_copy(out, shablock, algo->hashSize, algo->hashSize));
    if(0u != memcopy_result3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_ERROR);
    }

    /* Set expectations and exit */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2, MCUXCLHASH_STATUS_OK,
                            MCUX_CSSL_FP_CONDITIONAL((0u != sizeOfFullBlocks), algo->protection_token_engine),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                            MCUX_CSSL_FP_CONDITIONAL((buflen == algo->blockSize), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), algo->protection_token_engine),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            (algo->protection_token_engine),
                            MCUX_CSSL_FP_CONDITIONAL((MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf),  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_skeletonSha2_streaming)
static mcuxClHash_Status_Protected_t mcuxClHash_skeletonSha2_streaming (
                        mcuxClSession_Handle_t session,
                        const mcuxClHash_Algo_t *algo,
                        mcuxClHash_ContextData_t *context,
                        mcuxClHash_ContextBuffer_t *buffer,
                        const uint8_t *const in,
                        uint32_t inSize,
                        uint8_t *const out,
                        uint8_t *const rtf,
                        uint32_t options
                        )
{
    /*
        General flow of full implementation (i.e. including accumulation, partial processing)
        - set options for initialization, continuation from external state, or from internal state
        - one call to engine to process data in the accumulation buffer + start of new data, if there
          was data in the accumulation buffer, disable initialization/state loading  if data was processed
        - one call to engine to process the middle blocks with state export set if requested and no
          finalization is requested
        - one or two calls to engine to process the final block with padding added with state export set,
          if finalization requested
    */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_skeletonSha2_streaming);

    /* Total length of unprocessed data */
    size_t unprocessedTotalLength = context->unprocessedLength + inSize;
    /* The amount of unprocessed data that fills complete blocks */
    size_t  unprocessedCompleteBlockLength = (unprocessedTotalLength / algo->blockSize) * (algo->blockSize);
    /* Need to store the initial values of these variables for correct calculation of flow protection values at the end of the function */
    MCUX_CSSL_FP_COUNTER_STMT(const size_t initialUnprocessedCompleteBlockLength = unprocessedCompleteBlockLength);
    MCUX_CSSL_FP_COUNTER_STMT(const size_t initialUnprocessedContextLength = context->unprocessedLength);
    /* Pointer to the buffer where the state is stored. Either it ends up in the work area, or in the state buffer of the context */
    uint8_t *partialdigest = buffer->state;
    /* Input pointer that changes throughout the function */
    const uint8_t *pIn = in;

    /* Start setting initial options for CSS hash */
    mcuxClCss_HashOption_t hash_options;
    hash_options.word.value  = 0u;
    hash_options.bits.hashoe = MCUXCLCSS_HASH_OUTPUT_ENABLE;
    hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_ENABLE;
    hash_options.bits.hashld  = MCUXCLCSS_HASH_LOAD_DISABLE;

    /* Set hash init/load flags depending on whether there is a valid state to load or not */
    if(0u != context->processedLength) {
        /* There is already a valid state in the context -> load state from context */
        hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_DISABLE;
        hash_options.bits.hashld  = MCUXCLCSS_HASH_LOAD_ENABLE;
    }

    /* Set RTF processing options */
    if(MCUXCLHASH_STATUS_OK != selectRtfFlags(session->rtf, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
    }

    /* Select CSS hash algorithm based on output hash output size */
    if(MCUXCLHASH_STATUS_OK != selectHashMode(algo->hashSize, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
    }

    /* Done setting the options for CSS hash! */

    /* Process full blocks, if any are present in the accumulation buffer or in the input provided to the function */
    if(MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) {
        /* The first block can either be completely in `pIn`, or partially in the context buffer. */
        if((0u != unprocessedCompleteBlockLength) && (0u != context->unprocessedLength)) {
            /* There is some data in the context buffer. Append enough data from `pIn` to complete a block. */
            MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result1, mcuxClMemory_copy(buffer->unprocessed + context->unprocessedLength, pIn, algo->blockSize - context->unprocessedLength, sizeof(buffer->unprocessed) - context->unprocessedLength));

            if(0u != memcopy_result1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
            }

            MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                            hash_options.word.value,
                            buffer->unprocessed, algo->blockSize,
                            partialdigest
                            ));

            if (MCUXCLHASH_STATUS_OK != result)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, result);
            }


            hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_DISABLE;
            hash_options.bits.hashld = MCUXCLCSS_HASH_LOAD_DISABLE;

            pIn += algo->blockSize - context->unprocessedLength;

            context->processedLength += algo->blockSize;
            context->unprocessedLength = 0u;

            unprocessedCompleteBlockLength -= algo->blockSize;
            unprocessedTotalLength -= algo->blockSize;
        }

        /* At this point, there is no more data in the context buffer, so remaining blocks can be processed in bulk directly from pIn */
        if (0u != unprocessedCompleteBlockLength)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                            hash_options.word.value,
                            pIn, unprocessedCompleteBlockLength,
                            partialdigest
                            ));

            if (MCUXCLHASH_STATUS_OK != result)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, result);
            }


            hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_DISABLE;
            hash_options.bits.hashld = MCUXCLCSS_HASH_LOAD_DISABLE;

            pIn += unprocessedCompleteBlockLength;

            context->processedLength += unprocessedCompleteBlockLength;

            unprocessedTotalLength -= unprocessedCompleteBlockLength;
        }
    }

    /* Last step in the hash computation: Pad the hash input and process the 1 or 2 last blocks. */
    if(MCUXCLHASH_FINALIZE == (options & MCUXCLHASH_FINALIZE)) {
        /* Pointer to the buffer where the last block of data is stored in the finalization phase */
        uint8_t *shablock = buffer->unprocessed;
        uint8_t *pOut;
        size_t posdst, buflen;
        buflen = algo->blockSize;

        /* There is a context buffer. */
        if(context->unprocessedLength != unprocessedTotalLength)
        {
            /* There is some data in pIn that is not yet in the context buffer? Append it to the context buffer. */
            MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result1, mcuxClMemory_copy(buffer->unprocessed + context->unprocessedLength, pIn, unprocessedTotalLength - context->unprocessedLength, sizeof(buffer->unprocessed) - context->unprocessedLength));

            if(0u != memcopy_result1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
            }
        }

        /* Update the counter for processed bytes, since this is the value that is written in the padding. */
        context->processedLength += unprocessedTotalLength;

        posdst  = unprocessedTotalLength;
        buflen -= unprocessedTotalLength;
        // add first byte of the padding: (remaining) < (block length) so there is space in the buffer
        shablock[posdst] = 0x80;
        posdst += 1u;
        buflen -= 1u;

        /* Process partial padded block if needed */
        if ( algo->blockSize - algo->counterSize - 1u < unprocessedTotalLength ) // need room for 64 bit counter and one additional byte
        {
            MCUX_CSSL_FP_FUNCTION_CALL(memset_result1, mcuxClMemory_set(shablock + posdst, 0x00, buflen, buflen));
            if(0u != memset_result1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
            }
            buflen = algo->blockSize;
            posdst = 0u;

            MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                                hash_options.word.value,
                                shablock, algo->blockSize,
                                partialdigest
                                ));

            if (MCUXCLHASH_STATUS_OK != result)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, result);
            }


            hash_options.bits.hashini = MCUXCLCSS_HASH_INIT_DISABLE;
            hash_options.bits.hashld = MCUXCLCSS_HASH_LOAD_ENABLE;
        }

        /* Perform padding by adding data counter */
        MCUX_CSSL_FP_FUNCTION_CALL(memset_result2, mcuxClMemory_set(shablock + posdst, 0x00, buflen, buflen));
        if(0u != memset_result2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
        }
        posdst = algo->blockSize;
        shablock[--posdst] = (uint8_t)(context->processedLength <<  3u);
        shablock[--posdst] = (uint8_t)(context->processedLength >>  5u);
        shablock[--posdst] = (uint8_t)(context->processedLength >> 13u);
        shablock[--posdst] = (uint8_t)(context->processedLength >> 21u);
        shablock[posdst-1u] = (uint8_t)(context->processedLength >> 29u);

        hash_options.bits.hashoe  = MCUXCLCSS_HASH_OUTPUT_ENABLE;
        pOut = partialdigest;

        /* Set RTF processing options */
        hash_options.bits.rtfoe = hash_options.bits.rtfupd;

        /* Process last block */
        MCUX_CSSL_FP_FUNCTION_CALL(result, algo->engine(
                        hash_options.word.value,
                        shablock, algo->blockSize,
                        pOut
        ));


        if (MCUXCLHASH_STATUS_OK != result)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, result);
        }

        /* Copy RTF to corresponding buffer */
        if(MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result2, mcuxClMemory_copy(rtf, pOut + algo->hashSize, algo->rtfSize,  algo->rtfSize));
            if(0u != memcopy_result2)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
            }
        }

        /* Copy hash digest to output buffer */
        MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result3, mcuxClMemory_copy(out, pOut, algo->hashSize, algo->hashSize));
        if(0u != memcopy_result3)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
        }

        /* Set expectations and exit */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_OK,
                                MCUX_CSSL_FP_CONDITIONAL((MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) && (0u != initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength),
                                                        algo->protection_token_engine, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
                                                        ),
                                MCUX_CSSL_FP_CONDITIONAL((MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) && (((0u != initialUnprocessedCompleteBlockLength) && (0u == initialUnprocessedContextLength)) || ((algo->blockSize < initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength))),
                                                        algo->protection_token_engine
                                                        ),
                                MCUX_CSSL_FP_CONDITIONAL(unprocessedTotalLength > algo->blockSize - algo->counterSize - 1u,
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), algo->protection_token_engine
                                                        ),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                (algo->protection_token_engine),
                                MCUX_CSSL_FP_CONDITIONAL(MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf,  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                MCUX_CSSL_FP_CONDITIONAL((context->unprocessedLength != unprocessedTotalLength), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
    } else {
        /* If finalization should not happen, append the remaining data to the accumulation buffer. */
        if(0u < unprocessedTotalLength) {
            size_t lengthToCopy = unprocessedTotalLength - context->unprocessedLength;

            /* There is some data in the context buffer. Append enough data from `pIn` to complete a block. */
            MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result1, mcuxClMemory_copy(buffer->unprocessed + context->unprocessedLength, pIn, lengthToCopy, sizeof(buffer->unprocessed) - context->unprocessedLength));

            if (0u != memcopy_result1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_ERROR);
            }

            context->unprocessedLength += lengthToCopy;

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_OK,
                        MCUX_CSSL_FP_CONDITIONAL((MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) && (0u != initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength),
                                                algo->protection_token_engine, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
                                                ),
                        MCUX_CSSL_FP_CONDITIONAL((MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) && (((0u != initialUnprocessedCompleteBlockLength) && (0u == initialUnprocessedContextLength)) || ((algo->blockSize < initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength))),
                                                algo->protection_token_engine
                                                ),
                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
        } else {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_skeletonSha2_streaming, MCUXCLHASH_STATUS_OK,
                        MCUX_CSSL_FP_CONDITIONAL((MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) && (0u != initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength),
                                                algo->protection_token_engine, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
                                                ),
                        MCUX_CSSL_FP_CONDITIONAL((MCUXCLHASH_UPDATE == (options & MCUXCLHASH_UPDATE)) && (((0u != initialUnprocessedCompleteBlockLength) && (0u == initialUnprocessedContextLength)) || ((algo->blockSize < initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength))),
                                                algo->protection_token_engine
                                                ));
        }
    }
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_algoEngineSha2)
static mcuxClHash_Status_Protected_t mcuxClHash_algoEngineSha2(
                        uint32_t options,
                        const uint8_t *const in,
                        uint32_t inSize,
                        uint8_t *const out
                        )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_algoEngineSha2, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Hash_Async), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));

    mcuxClCss_HashOption_t hash_options;
    hash_options.word.value = options;
    MCUX_CSSL_FP_FUNCTION_CALL(result_hash, mcuxClCss_Hash_Async(
                        hash_options,
                        in, inSize,
                        out
    ));
    if (MCUXCLCSS_STATUS_OK_WAIT != result_hash)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_algoEngineSha2, MCUXCLHASH_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
    if (MCUXCLCSS_STATUS_OK != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_algoEngineSha2, MCUXCLHASH_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_algoEngineSha2, MCUXCLHASH_STATUS_OK);
}

// PRECONDITION: SHA-direct mode has been enabled
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_algoEngineSha2_direct)
static mcuxClHash_Status_Protected_t mcuxClHash_algoEngineSha2_direct(
                        uint32_t options,
                        const uint8_t *const in,
                        uint32_t inSize,
                        uint8_t *const out
                        )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_algoEngineSha2_direct, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Hash_ShaDirect));

    mcuxClCss_HashOption_t hash_options;
    hash_options.word.value = options;
    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Hash_ShaDirect(
                        hash_options,
                        in, inSize,
                        out,
                        NULL,
                        NULL
    ));
    if (MCUXCLCSS_STATUS_OK != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_algoEngineSha2_direct, MCUXCLHASH_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_algoEngineSha2_direct, MCUXCLHASH_STATUS_OK);
}

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA224_direct = {
    .engine             = mcuxClHash_algoEngineSha2_direct,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_224,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_224,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_224,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_224,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2_direct),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA224 = {
    .engine             = mcuxClHash_algoEngineSha2,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_224,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_224,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_224,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_224,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA256_direct = {
    .engine             = mcuxClHash_algoEngineSha2_direct,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_256,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_256,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_256,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2_direct),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA256 = {
    .engine             = mcuxClHash_algoEngineSha2,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_256,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_256,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_256,
    .rtfSize            = MCUXCLCSS_HASH_RTF_OUTPUT_SIZE,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA384_direct = {
    .engine             = mcuxClHash_algoEngineSha2_direct,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_384,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_384,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_384,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_384,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2_direct),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA384 = {
    .engine             = mcuxClHash_algoEngineSha2,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_384,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_384,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_384,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_384,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA512_direct = {
    .engine             = mcuxClHash_algoEngineSha2_direct,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_512,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_512,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_512,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_512,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2_direct),
};

const mcuxClHash_Algo_t mcuxClHash_AlgoSHA512 = {
    .engine             = mcuxClHash_algoEngineSha2,
    .skeleton           = mcuxClHash_skeletonSha2,
    .streamingSkeleton  = mcuxClHash_skeletonSha2_streaming,
    .blockSize          = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_512,
    .hashSize           = MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_512,
    .stateSize          = MCUXCLCSS_HASH_STATE_SIZE_SHA_512,
    .counterSize        = MCUXCLHASH_COUNTER_SIZE_SHA_512,
    .rtfSize            = 0u,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2),
    .protection_token_streaming_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_skeletonSha2_streaming),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_algoEngineSha2),
};
