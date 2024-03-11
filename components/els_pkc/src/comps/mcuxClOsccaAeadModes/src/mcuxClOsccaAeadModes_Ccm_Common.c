/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

/** @file  mcuxClOsccaAeadModes_Ccm_Common.c
 *  @brief implementation of the SM4 CCM common functions of the mcuxClOsccaAeadModes component */

#include <mcuxClAead.h>
#include <mcuxClOsccaAeadModes.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxClCore_Examples.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Types.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Functions.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_Ccm_Internal_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_Init(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_InputBuffer_t pNonce,
    uint32_t nonceLength,
    uint32_t inLength,
    uint32_t adataLength,
    uint32_t tagLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_Ccm_Internal_Init);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm const * to mcuxClOsccaAeadModes_algorithm_t const *")
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) pCtx->common.mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    /* Init tag. For CCM, the state store the tag value */
    MCUXCLMEMORY_FP_MEMORY_SET(pCtx->state, 0u, MCUXCLOSCCASM4_BLOCK_SIZE);

    pCtx->partialDataLength = 0u;

    /* Generate the plain tag -> CBC-MAC with zero IV */
    // Clear first blocks to guarantee zero padding
    MCUXCLMEMORY_FP_MEMORY_SET(pCtx->partialData, 0u, MCUXCLOSCCASM4_BLOCK_SIZE);

    //Determine whether the nonceLength is less than MCUXCLOSCCASM4_BLOCK_SIZE -1 to prevent memory overflow later
    //Determine whether the tagLength is less than 2u to prevent memory overflow later
    //Determine pNonce not NULL to avoid dereferencing pNonce
    if((nonceLength >= MCUXCLOSCCASM4_BLOCK_SIZE - 1u) || (tagLength < 2u) || (pNonce == NULL))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Init, MCUXCLAEAD_STATUS_ERROR);
    }

    // Get length of auth field from parameter
    uint8_t t = (uint8_t)((tagLength - 2u) / 2u);
    // Get q-1 from parameter
    uint8_t q = (uint8_t)(15u - nonceLength);
    // Assemble the flags byte for B0
    // --------------------------------------------
    // |     7    |   6   |    5..3     |   2..0  |
    // | Reserved | Adata | [(t-2)/2]_3 | [q-1]_3 |
    // --------------------------------------------
    uint8_t isheaderLen = (uint8_t)(adataLength > 0u);
    pCtx->partialData[0u] = (uint8_t)((uint8_t)((isheaderLen << 6u) | (t << 3u)) | (q - 1u));

    // Create B0
    // ----------------------------------
    // |   0   | 1 .. 15-q | 16-q .. 15 |
    // | Flags |     N     |      Q     |
    // ----------------------------------

    // Copy nonce N
    MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pNonce, 0u, &pCtx->partialData[1u], nonceLength));
    (void)statusBufferRead; // No need to check it because the function only returns OK.

    // Create Q
    uint32_t inMask = 0x000000FFu;
    for(int32_t it = 15; it >= (16 - ((int32_t)q)); --it)
    {
        pCtx->partialData[it] = (uint8_t)((inLength & inMask) >> (((15u - (uint8_t)it) * 8u) & 0x0Fu));
        inMask = inMask << 8u;
    }

    //Calculate tag over B0
    //process the first block using pEngine(option: auth) with zero IV and output to state in context
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(authRet, pAlgo->pEngine(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                      session,
                                                      pCtx,
                                                      pCtx->partialData,
                                                      MCUXCLOSCCASM4_BLOCK_SIZE,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                      NULL,
                                                      NULL,
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                      MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH | MCUXCLOSCCAAEADMODES_ENGINE_OPTION_INIT));

    if(MCUXCLAEAD_STATUS_OK != authRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Init, MCUXCLAEAD_STATUS_ERROR);
    }

    // Formatting of the associated data
    // Encode a and concatenate with associated data
    // Check if AAD has to be processed
    if(0u == adataLength)
    {
        pCtx->partialDataLength = 0u;
    }
    // If 0 < a < 2^{16}-2^{8}, then a is encoded as [a]_16, i.e., two octets.
    else if(adataLength < ((1UL << 16u) - (1UL << 8u)))
    {
        // a < 2^{16}-2^{8}
        pCtx->partialData[0] = (uint8_t)((adataLength & 0x0000FF00u) >> 8u);
        pCtx->partialData[1] = (uint8_t)((adataLength & 0x000000FFu) >> 0u);

        pCtx->partialDataLength = 2u;
    }
    // If 2^{16}-2^{8} <= a < 2^{32}, then a is encoded as 0xff || 0xfe || [a]_32, i.e., six octets.
    else
    {
        // a >= 2^{16}-2^{8}
        pCtx->partialData[0] = (uint8_t)0xFFu;
        pCtx->partialData[1] = (uint8_t)0xFEu;
        pCtx->partialData[2] = (uint8_t)((adataLength & 0xFF000000u) >> 24u);
        pCtx->partialData[3] = (uint8_t)((adataLength & 0x00FF0000u) >> 16u);
        pCtx->partialData[4] = (uint8_t)((adataLength & 0x0000FF00u) >> 8u);
        pCtx->partialData[5] = (uint8_t)((adataLength & 0x000000FFu) >> 0u);

        pCtx->partialDataLength = 6u;
    }

    // If 2^{32} <= a < 2^{64}, then a is encoded as 0xff || 0xff || [a]_64, i.e., ten octets.
    // This case is not supported in CL and hence does not occur since inLength is uint32_t

    /*  Generate the counter for CTR mode encryption */
    // &pCtx->state[32] won't be used in CCM mode, so write it to store the counter0Data.
    // Use &pCtx->state[48] to store the counterData
    // Clear counter first
    MCUXCLMEMORY_FP_MEMORY_SET(&pCtx->state[32], 0u, MCUXCLOSCCASM4_BLOCK_SIZE);

    // Assemble the flags byte
    // ------------------------------------------
    // |     7    |     6    |  5..3  |   2..0  |
    // | Reserved | Reserved |   000  | [q-1]_3 |
    // ------------------------------------------
    pCtx->state[32] = q - 1u;

    // Create CTR0
    // ----------------------------------
    // |   0   | 1 .. 15-q | 16-q .. 15 |
    // | Flags |     N     |      0     |
    // ----------------------------------

    // Copy nonce into counter block

    MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead1, mcuxClBuffer_read(pNonce, 0u, &pCtx->state[33], nonceLength));
    (void)statusBufferRead1; // No need to check it because the function only returns OK.

    MCUXCLMEMORY_FP_MEMORY_COPY(&pCtx->state[48],&pCtx->state[32],MCUXCLOSCCASM4_BLOCK_SIZE);

    // Last X bytes of counterData are always equal zero, set last byte to one for the next computation
    pCtx->state[63] = 0x1u;

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_Ccm_Internal_Init, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
            3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
            pAlgo->protection_token_engine);
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_InputBuffer_t pAdata,
    uint32_t adataLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad);

    mcuxClAead_Mode_t mode = pCtx->common.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    uint32_t partialDataLenOri = pCtx->partialDataLength;
    uint32_t lenToCopy = adataLength;            // adataLength is the length of AAD for this AAD process call

    MCUX_CSSL_FP_BRANCH_DECL(atleastOneBlock);
    if(0u != lenToCopy)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (partialDataLenOri + lenToCopy) can't be larger than max(uint32_t) ")
        if((partialDataLenOri + lenToCopy) >= MCUXCLOSCCASM4_BLOCK_SIZE)
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW(" MCUXCLOSCCASM4_BLOCK_SIZE > pCtx->partialDataLength ")
            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pAdata, 0u, &pCtx->partialData[pCtx->partialDataLength], MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength));
            (void)statusBufferRead; // No need to check it because the function only returns OK.
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

            MCUXCLBUFFER_UPDATE(pAdata, MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);

            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" lenToCopy >= (MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength) ")
            lenToCopy -= (MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            pCtx->partialDataLength = 0u;

            MCUXCLBUFFER_INIT_RO(pBufferPartialData, session, pCtx->partialData, MCUXCLOSCCASM4_BLOCK_SIZE);
            //Calculate tag over adata
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
            MCUX_CSSL_FP_FUNCTION_CALL(aadAuthRet, pAlgo->pEngine(
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                                session,
                                                                pCtx,
                                                                pBufferPartialData,
                                                                MCUXCLOSCCASM4_BLOCK_SIZE,
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                                NULL,
                                                                NULL,
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                                MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH));

            if(MCUXCLAEAD_STATUS_OK != aadAuthRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad, MCUXCLAEAD_STATUS_ERROR);
            }

            MCUX_CSSL_FP_BRANCH_DECL(multiBlocks);
            if(lenToCopy >= MCUXCLOSCCASM4_BLOCK_SIZE)
            {
                uint32_t adataBlocks = lenToCopy / MCUXCLOSCCASM4_BLOCK_SIZE;
                // ignored misra violation -> false positive
                // misra_c_2012_rule_11_9_violation: Literal 0 shall not be used as null pointer constant.
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
                MCUX_CSSL_FP_FUNCTION_CALL(aadBlkAuthRet, pAlgo->pEngine(
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                                       session,
                                                                       pCtx,
                                                                       pAdata,
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("adataBlocks can't be larger than max(uint32_t) ")
                                                                       adataBlocks * MCUXCLOSCCASM4_BLOCK_SIZE,
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                                       NULL,
                                                                       NULL,
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                                       MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH));

                if(MCUXCLAEAD_STATUS_OK != aadBlkAuthRet)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad, MCUXCLAEAD_STATUS_ERROR);
                }
                MCUXCLBUFFER_UPDATE(pAdata, adataBlocks * MCUXCLOSCCASM4_BLOCK_SIZE);
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" lenToCopy >= (adataBlocks * MCUXCLOSCCASM4_BLOCK_SIZE) ")
                lenToCopy -= (adataBlocks * MCUXCLOSCCASM4_BLOCK_SIZE);
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

                MCUX_CSSL_FP_BRANCH_POSITIVE(multiBlocks, pAlgo->protection_token_engine);
            }

            MCUX_CSSL_FP_BRANCH_DECL(remainBlock);
            if(0u != lenToCopy)
            {
                //copy remaining data into partialData
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("lenToCopy can't be larger than max(uint32_t) ")
                MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead1, mcuxClBuffer_read(pAdata, 0u, pCtx->partialData, lenToCopy));
                (void)statusBufferRead1; // No need to check it because the function only returns OK.
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" pCtx->partialDataLength += lenToCopy can't be larger than max(uint32_t) ")
                pCtx->partialDataLength = lenToCopy;
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

                MCUX_CSSL_FP_BRANCH_POSITIVE(remainBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
            }

            MCUX_CSSL_FP_BRANCH_POSITIVE(atleastOneBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                                          pAlgo->protection_token_engine,
                                          MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(multiBlocks, (partialDataLenOri + adataLength - MCUXCLOSCCASM4_BLOCK_SIZE) >= MCUXCLOSCCASM4_BLOCK_SIZE),
                                          MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(remainBlock, lenToCopy != 0u));
        }
        else
        {
            //bytes in buffer and new adata is less then blockSize - save data into partialData
            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pAdata, 0u, &pCtx->partialData[pCtx->partialDataLength], lenToCopy));
            (void)statusBufferRead; // No need to check it because the function only returns OK.
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW(" pCtx->partialDataLength += lenToCopy can't be larger than max(uint32_t) ")
            pCtx->partialDataLength += lenToCopy;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

            MCUX_CSSL_FP_BRANCH_NEGATIVE(atleastOneBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
        }
    }

    //update adata size to processedDataLength in ctx
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW(" pCtx->processedDataLength += adataLength can't be larger than max(uint32_t) ")
    pCtx->processedDataLength += adataLength;//The processedDataLength add the length of each processing
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    //Check if we done all adata and if we have some remaining data in buffer, this is for
    //the last adata block processing, add zero padding and calc pretag
    MCUX_CSSL_FP_BRANCH_DECL(lastBlock);
    if((pCtx->processedDataLength == pCtx->aadLength) && (0u != pCtx->partialDataLength))
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("(MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength) can't be larger than max(uint32_t) ")
        /* Apply the padding function specified in the mode on the partial data. */
        MCUXCLMEMORY_FP_MEMORY_SET(&pCtx->partialData[pCtx->partialDataLength], 0x00u, MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        //Process remaining adata and create pretag
        MCUXCLBUFFER_INIT_RO(pBufferPartialData, session, pCtx->partialData, MCUXCLOSCCASM4_BLOCK_SIZE);
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
        MCUX_CSSL_FP_FUNCTION_CALL(aadPadAuthRet, pAlgo->pEngine(
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                               session,
                                                               pCtx,
                                                               pBufferPartialData,
                                                               MCUXCLOSCCASM4_BLOCK_SIZE,
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                               NULL,
                                                               NULL,
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                               MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH));

        if(MCUXCLAEAD_STATUS_OK != aadPadAuthRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad, MCUXCLAEAD_STATUS_ERROR);
        }
        pCtx->partialDataLength = 0u;

        MCUX_CSSL_FP_BRANCH_POSITIVE(lastBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                                 pAlgo->protection_token_engine);
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(atleastOneBlock, (adataLength != 0u) && (((partialDataLenOri + adataLength)) >= MCUXCLOSCCASM4_BLOCK_SIZE)),
            MCUX_CSSL_FP_BRANCH_TAKEN_NEGATIVE(atleastOneBlock, (adataLength != 0u) && (((partialDataLenOri + adataLength)) < MCUXCLOSCCASM4_BLOCK_SIZE)),
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(lastBlock, ((partialDataLenOri + adataLength) % MCUXCLOSCCASM4_BLOCK_SIZE != 0u) && (pCtx->processedDataLength >= pCtx->aadLength)));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_Ccm_Internal_Process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_Process(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_Ccm_Internal_Process);

    mcuxClAead_Mode_t mode = pCtx->common.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    uint32_t partDataLenMed = pCtx->partialDataLength;
    uint32_t inLenOri = inLength;
    uint32_t proDataLen = pCtx->processedDataLength;

    MCUX_CSSL_FP_BRANCH_DECL(atleastOneBlock);
    if(0u != inLenOri)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (partDataLenMed + inLenOri) can't be larger than max(uint32_t) ")
        if((partDataLenMed + inLenOri) >= MCUXCLOSCCASM4_BLOCK_SIZE)
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW(" pCtx->partialDataLength must be less than MCUXCLOSCCASM4_BLOCK_SIZE and inLength,proDataLen can't be larger than max(uint32_t)")
            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, 0u, &pCtx->partialData[pCtx->partialDataLength], MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength));
            (void)statusBufferRead; // No need to check it because the function only returns OK.

            MCUXCLBUFFER_UPDATE(pIn, MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
            inLength -= (MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
            //update processed input data length to processedDataLength
            proDataLen += (MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            pCtx->partialDataLength = 0u;

            MCUXCLBUFFER_INIT_RO(pBufferPartialData, session, pCtx->partialData, MCUXCLOSCCASM4_BLOCK_SIZE);
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
            MCUX_CSSL_FP_FUNCTION_CALL(inAeadRet, pAlgo->pEngine(
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                                session,
                                                                pCtx,
                                                                pBufferPartialData,
                                                                MCUXCLOSCCASM4_BLOCK_SIZE,
                                                                pOut,
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                                NULL,
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                                MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AEAD));

            if(MCUXCLAEAD_STATUS_OK != inAeadRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Process, MCUXCLAEAD_STATUS_ERROR);
            }

            MCUXCLBUFFER_UPDATE(pOut, MCUXCLOSCCASM4_BLOCK_SIZE);
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
            *pOutLength += MCUXCLOSCCASM4_BLOCK_SIZE;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

            MCUX_CSSL_FP_BRANCH_DECL(multiBlocks);
            if(inLength >= MCUXCLOSCCASM4_BLOCK_SIZE)
            {
                uint32_t inputBlocks = inLength / MCUXCLOSCCASM4_BLOCK_SIZE;

                MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
                MCUX_CSSL_FP_FUNCTION_CALL(inBlkAeadRet, pAlgo->pEngine(
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                                       session,
                                                                       pCtx,
                                                                       pIn,
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("inputBlocks can't be larger than max(uint32_t) ")
                                                                       inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE,
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
                                                                       pOut,
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                                       NULL,
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                                       MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AEAD));

                if(MCUXCLAEAD_STATUS_OK != inBlkAeadRet)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Process, MCUXCLAEAD_STATUS_ERROR);
                }

                MCUXCLBUFFER_UPDATE(pIn, inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE);
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" inLength must can't be less than inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE ")
                inLength -= inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE;
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
                //update processed input data length to processedDataLength
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
                proDataLen += inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE;
                MCUXCLBUFFER_UPDATE(pOut, inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE);
                *pOutLength += inputBlocks * MCUXCLOSCCASM4_BLOCK_SIZE;
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

                MCUX_CSSL_FP_BRANCH_POSITIVE(multiBlocks, pAlgo->protection_token_engine);
            }

            MCUX_CSSL_FP_BRANCH_DECL(remainBlock);
            if(0u != inLength)
            {
                //copy remaining data into blockBuffer
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("inLength can't be larger than max(uint32_t) ")
                MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead1, mcuxClBuffer_read(pIn, 0u, pCtx->partialData, inLength));
                (void)statusBufferRead1; // No need to check it because the function only returns OK.

                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
                MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" pCtx->partialDataLength and proDataLen can't be larger than max(uint32_t) ")
                pCtx->partialDataLength = inLength;
                //update processed input data length to processedDataLength
                proDataLen += inLength;
                MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

                MCUX_CSSL_FP_BRANCH_POSITIVE(remainBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
            }

            MCUX_CSSL_FP_BRANCH_POSITIVE(atleastOneBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                                          pAlgo->protection_token_engine,
                                          MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(multiBlocks, (partDataLenMed + inLenOri - MCUXCLOSCCASM4_BLOCK_SIZE) >= MCUXCLOSCCASM4_BLOCK_SIZE),
                                          MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(remainBlock, inLength != 0u));
        }
        else
        {
            //bytes in buffer and new adata is less then blockSize - save data into partialData
            MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pIn, 0u, &pCtx->partialData[pCtx->partialDataLength], inLength));
            (void)statusBufferRead; // No need to check it because the function only returns OK.

            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" pCtx->partialDataLength and proDataLen can't be larger than max(uint32_t) ")
            pCtx->partialDataLength += inLength;
            //update processed input data length to processedDataLength
            proDataLen += inLength;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

            MCUX_CSSL_FP_BRANCH_NEGATIVE(atleastOneBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read));
        }
    }


    pCtx->processedDataLength = proDataLen;
    //Check if we done all input data and if we have some remaining data in buffer, this is for
    //the last input data block processing, add zero padding and calc final tag
    MCUX_CSSL_FP_BRANCH_DECL(lastBlock);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (pCtx->dataLength + pCtx->aadLength) can't be larger than max(uint32_t) ")
    if((pCtx->processedDataLength == pCtx->dataLength + pCtx->aadLength) && (0u != pCtx->partialDataLength))
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("(pCtx->partialDataLength) and MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength can't be larger than max(uint32_t) ")
        MCUXCLMEMORY_FP_MEMORY_SET(&pCtx->partialData[(pCtx->partialDataLength)%MCUXCLOSCCASM4_BLOCK_SIZE], 0u, MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        //This last block length less then MCUXCLOSCCASM4_BLOCK_SIZE, so can't directly write result to pOut
        //&pCtx->state[16] have not been used, so can re-write it to store the CTR result
        MCUXCLBUFFER_INIT_RO(pBufferPartialData, session, pCtx->partialData, MCUXCLOSCCASM4_BLOCK_SIZE);
        MCUXCLBUFFER_INIT(pBufferState16Out, session, &pCtx->state[16], MCUXCLOSCCASM4_BLOCK_SIZE);
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
        MCUX_CSSL_FP_FUNCTION_CALL(inPaddEncRet, pAlgo->pEngine(
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                               session,
                                                               pCtx,
                                                               pBufferPartialData,
                                                               MCUXCLOSCCASM4_BLOCK_SIZE,
                                                               pBufferState16Out,
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                               NULL,
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                               MCUXCLOSCCAAEADMODES_ENGINE_OPTION_ENC));

        if(MCUXCLAEAD_STATUS_OK != inPaddEncRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Process, MCUXCLAEAD_STATUS_ERROR);
        }

        /* Copy the padding to the output and update pOutLength accordingly. */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW(" pCtx->partialDataLength won't be overflow ")
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pOut, 0u, &pCtx->state[16], pCtx->partialDataLength));
        (void)statusBufferWrite; // No need to check it because the function only returns OK.

        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not to wrap")
        *pOutLength += pCtx->partialDataLength;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

        if(MCUXCLOSCCASM4_ENCRYPT == pCtx->direction)
        {
            //Process remaining data and create pretag
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
            MCUX_CSSL_FP_FUNCTION_CALL(inPaddAuthRet, pAlgo->pEngine(
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                                    session,
                                                                    pCtx,
                                                                    pBufferPartialData,
                                                                    MCUXCLOSCCASM4_BLOCK_SIZE,
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                                    NULL,
                                                                    NULL,
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                                    MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH));

            if(MCUXCLAEAD_STATUS_OK != inPaddAuthRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Process, MCUXCLAEAD_STATUS_ERROR);
            }
         }
        else
        {
            //Process remaining data and create pretag
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW(" MCUXCLOSCCASM4_BLOCK_SIZE > pCtx->partialDataLength ")
            MCUXCLMEMORY_FP_MEMORY_SET(&pCtx->state[16u + pCtx->partialDataLength], 0x00u, MCUXCLOSCCASM4_BLOCK_SIZE - pCtx->partialDataLength);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

            MCUXCLBUFFER_INIT_RO(pBufferState16In, session, &pCtx->state[16], MCUXCLOSCCASM4_BLOCK_SIZE);
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
            MCUX_CSSL_FP_FUNCTION_CALL(inPaddAuthRet, pAlgo->pEngine(
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                                    session,
                                                                    pCtx,
                                                                    pBufferState16In,
                                                                    MCUXCLOSCCASM4_BLOCK_SIZE,
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                                    NULL,
                                                                    NULL,
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                                    MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH));

            if(MCUXCLAEAD_STATUS_OK != inPaddAuthRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Process, MCUXCLAEAD_STATUS_ERROR);
            }
        }
        pCtx->partialDataLength = 0u;

        MCUX_CSSL_FP_BRANCH_POSITIVE(lastBlock, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                               2u * pAlgo->protection_token_engine,
                                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write));
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_Ccm_Internal_Process, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(atleastOneBlock, (inLenOri != 0u) && ((partDataLenMed + inLenOri) >= MCUXCLOSCCASM4_BLOCK_SIZE)),
            MCUX_CSSL_FP_BRANCH_TAKEN_NEGATIVE(atleastOneBlock, (inLenOri != 0u) && ((partDataLenMed + inLenOri) < MCUXCLOSCCASM4_BLOCK_SIZE)),
            MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(lastBlock, (pCtx->processedDataLength == pCtx->dataLength + pCtx->aadLength) && ((partDataLenMed + inLenOri) % MCUXCLOSCCASM4_BLOCK_SIZE != 0u)),
            MCUX_CSSL_FP_CONDITIONAL(((pCtx->processedDataLength == pCtx->dataLength + pCtx->aadLength) && ((partDataLenMed + inLenOri) % MCUXCLOSCCASM4_BLOCK_SIZE != 0u)),
                MCUX_CSSL_FP_CONDITIONAL((MCUXCLOSCCASM4_DECRYPT == pCtx->direction),MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set))));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_Ccm_Internal_Finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_Ccm_Internal_Finish(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pCtx,
    mcuxCl_Buffer_t pTag,
    uint32_t options //!< options is a bitmask with one bit reserved for each of the operations
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_Ccm_Internal_Finish);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm const * to mcuxClOsccaAeadModes_algorithm_t const *")
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) pCtx->common.mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    if (0u != pCtx->partialDataLength)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Finish, MCUXCLAEAD_STATUS_ERROR);
    }

    //reset counter value to 'zero' (leaving the other fields intact)
    MCUXCLMEMORY_FP_MEMORY_COPY(&pCtx->state[48],&pCtx->state[32],MCUXCLOSCCASM4_BLOCK_SIZE);

    MCUXCLBUFFER_INIT_RO(pBufferState, session, pCtx->state, MCUXCLOSCCASM4_BLOCK_SIZE);
    MCUXCLBUFFER_INIT(pBufferPartialData, session, pCtx->partialData, MCUXCLOSCCASM4_BLOCK_SIZE);

    //Encrypt pretag with counter0 to get final tag
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(finalTagEncRet, pAlgo->pEngine(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                                            session,
                                                            pCtx,
                                                            pBufferState,
                                                            MCUXCLOSCCASM4_BLOCK_SIZE,
                                                            pBufferPartialData,
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
                                                            NULL,
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
                                                            MCUXCLOSCCAAEADMODES_ENGINE_OPTION_ENC));

    if(MCUXCLAEAD_STATUS_OK != finalTagEncRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Finish, MCUXCLAEAD_STATUS_ERROR);
    }

    if ((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_FINISH))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write(pTag, 0u, pCtx->partialData, pCtx->tagLength));
        (void)statusBufferWrite; // No need to check it because the function only returns OK.
    }
    else
    {
        uint8_t tag[MCUXCLOSCCASM4_BLOCK_SIZE];
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read(pTag, 0u, tag, pCtx->tagLength));
        (void)statusBufferRead; // No need to check it because the function only returns OK.

        if(true != mcuxClCore_assertEqual(tag, pCtx->partialData, pCtx->tagLength))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_Ccm_Internal_Finish, MCUXCLAEAD_STATUS_ERROR);
        }
    }
    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_Ccm_Internal_Finish, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                pAlgo->protection_token_engine,
                MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_FINISH))),
                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write)),
                MCUX_CSSL_FP_CONDITIONAL((((options != MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) && (options != MCUXCLOSCCAAEADMODES_OPTION_FINISH))),
                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)));
}
