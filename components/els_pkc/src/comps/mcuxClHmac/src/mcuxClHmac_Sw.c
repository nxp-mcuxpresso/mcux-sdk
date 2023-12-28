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

/** @file  mcuxClHMac_Sw.c
 *  @brief Implementation of SW engine functions for the HMAC component */

#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClMac.h>
#include <mcuxClSession.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClHmac_Internal_Functions.h>
#include <internal/mcuxClHmac_Internal_Types.h>
#include <internal/mcuxClHmac_Internal_Macros.h>
#include <internal/mcuxClHmac_Core_Functions_Sw.h>

#define MCUXCLMAC_HMAC_IPAD_BYTE (0x36u)
#define MCUXCLMAC_HMAC_OPAD_BYTE (0x5cu)

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Init_Sw, mcuxClHmac_InitEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Init_Sw(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Init_Sw);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different HMAC context types")
    mcuxClHmac_Context_Sw_t * const pCtxSw = (mcuxClHmac_Context_Sw_t *) pContext;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    const mcuxClHash_AlgorithmDescriptor_t *hashAlgo = ((mcuxClHmac_ModeDescriptor_t *) (pCtxSw->common.pMode->pCustom))->hashAlgorithm;
    mcuxClKey_Descriptor_t * key = pCtxSw->key;
    const uint32_t hashBlockSize = hashAlgo->blockSize;

    uint32_t keySize = mcuxClKey_getSize(key);
    uint8_t *pKeyData = mcuxClKey_getLoadedKeyData(key);
    size_t alreadyFilledKeyDataSize = 0u;
    uint32_t *pPreparedHmacKey = mcuxClSession_allocateWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashBlockSize));
    if(NULL == pPreparedHmacKey)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Init_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /*********************************************************************************************************/
    /* Prepare a block-sized key from the key given in the Hmac context (pContext) and store it in work area */
    /*********************************************************************************************************/
    if(keySize > hashBlockSize) /* key is too long */
    {
        uint32_t hashOutputSize = 0u;
        /* Given key must be hashed and then zero-padded up to hashBlockSize */
        MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_compute, mcuxClHash_compute(session,
                                                                hashAlgo,
                                                                pKeyData,
                                                                keySize,
                                                                (uint8_t *)pPreparedHmacKey,
                                                                &hashOutputSize));

        if(MCUXCLHASH_STATUS_OK != result_Hash_compute)
        {
            /* Free workarea (pPreparedHmacKey) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashBlockSize));
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Init_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
        }
        alreadyFilledKeyDataSize = MCUXCLHASH_OUTPUT_SIZE_SHA_256;
    }
    else /* key is not too long */
    {
        /* Given key must be zero-padded up to hashBlockSize */
        MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pPreparedHmacKey,
                                                               pKeyData,
                                                               keySize,
                                                               hashBlockSize);
        alreadyFilledKeyDataSize = keySize;
    }

    /* Zero-pad the key */
    MCUXCLMEMORY_FP_MEMORY_SET((uint8_t *)pPreparedHmacKey + alreadyFilledKeyDataSize, 0u, hashBlockSize - alreadyFilledKeyDataSize);

    /***************************************************************************************************************/
    /* Store the prepared block-sized key in the Hmac context for later use in the outer hash during finalization  */
    /***************************************************************************************************************/

    MCUXCLMEMORY_FP_MEMORY_COPY(pCtxSw->preparedHmacKey, pPreparedHmacKey, hashBlockSize);

    /********************************************************************/
    /* Initialize a Hash context for multipart within the Hmac context  */
    /********************************************************************/
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    pCtxSw->hashCtx = (mcuxClHash_Context_t) &(pCtxSw->hashContextBuffer); /* The content of the hash context is stored in the Hmac context */
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_init, mcuxClHash_init(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxClHash_Algo_t  algorithm:   */ hashAlgo
    ));
    if(MCUXCLHASH_STATUS_OK != result_Hash_init)
    {
        /* Free workarea (pPreparedHmacKey) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashBlockSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Init_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /*****************************************************************************************************************/
    /* XOR the ipad to the block-sized key in the work area and Hash-process it (the first block of the inner hash)  */
    /*****************************************************************************************************************/
    for(size_t i = 0u; i < hashBlockSize; i++ )
    {
        ((uint8_t *)pPreparedHmacKey)[i] ^= MCUXCLMAC_HMAC_IPAD_BYTE;
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_process, mcuxClHash_process(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxCl_InputBuffer_t in:        */ (uint8_t *) pPreparedHmacKey,
    /* uint32_t inSize:               */ hashBlockSize
    ));
    if(MCUXCLHASH_STATUS_OK != result_Hash_process)
    {
        /* Free workarea (pPreparedHmacKey) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashBlockSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Init_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /* Free workarea (pPreparedHmacKey) */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashBlockSize));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Init_Sw, MCUXCLMAC_STATUS_OK,
          MCUX_CSSL_FP_CONDITIONAL((keySize <= hashBlockSize),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
          ),
          MCUX_CSSL_FP_CONDITIONAL((keySize > hashBlockSize),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)
          ),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)
    );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Update_Sw, mcuxClHmac_UpdateEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Update_Sw(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Update_Sw);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different HMAC context types")
    mcuxClHmac_Context_Sw_t * const pCtxSw = (mcuxClHmac_Context_Sw_t *) pContext;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_process, mcuxClHash_process(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxCl_InputBuffer_t in:        */ pIn,
    /* uint32_t inSize:               */ inLength
    ));
    if(MCUXCLHASH_STATUS_OK != result_Hash_process)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Update_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Update_Sw, MCUXCLMAC_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Finalize_Sw, mcuxClHmac_FinalizeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Finalize_Sw(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    uint8_t *const pOut,
    uint32_t *const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Finalize_Sw);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different HMAC context types")
    mcuxClHmac_Context_Sw_t * const pCtxSw = (mcuxClHmac_Context_Sw_t *) pContext;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    const mcuxClHash_AlgorithmDescriptor_t *hashAlgo = ((mcuxClHmac_ModeDescriptor_t *) (pCtxSw->common.pMode->pCustom))->hashAlgorithm;
    const uint32_t hashSize = hashAlgo->hashSize;
    const uint32_t hashBlockSize = hashAlgo->blockSize;

    /****************************************************************************************************************************************/
    /* Finalize the inner hash by calling Hash-finalize with the Hash context stored in the Hmac context and write the digest to work area  */
    /****************************************************************************************************************************************/

    uint32_t *pInnerHash = mcuxClSession_allocateWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));
    if(NULL == pInnerHash)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_ERROR);
    }

    uint32_t hashOutputSize = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_finish_1, mcuxClHash_finish(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxCl_Buffer_t pOut            */ (uint8_t *) pInnerHash,
    /* uint32_t *const pOutSize,      */ &hashOutputSize
    ));
    if((hashOutputSize != hashSize) || (MCUXCLHASH_STATUS_OK != result_Hash_finish_1))
    {
        /* Free workarea (pInnerHash) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /**********************************************************************/
    /* Initialize a new Hash context (re-using the old context's memory)  */
    /**********************************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_init, mcuxClHash_init(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxClHash_Algo_t  algorithm:   */ hashAlgo
    ));
    if(MCUXCLHASH_STATUS_OK != result_Hash_init)
    {
        /* Free workarea (pInnerHash) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /***********************************************************************************************************************************/
    /* XOR the opad to the block-sized key that is stored in the Hmac context and Hash-process it (the first block of the outer hash)  */
    /***********************************************************************************************************************************/

    uint8_t *pKeyData = (uint8_t *) pCtxSw->preparedHmacKey;

    for(size_t i = 0u; i < hashBlockSize; i++ )
    {
        pKeyData[i] ^= MCUXCLMAC_HMAC_OPAD_BYTE;
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_process_1, mcuxClHash_process(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxCl_InputBuffer_t in:        */ pKeyData,
    /* uint32_t inSize:               */ hashBlockSize
    ));
    if(MCUXCLHASH_STATUS_OK != result_Hash_process_1)
    {
        /* Free workarea (pInnerHash) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /********************************************************************************/
    /* Hash-process the digest from before, residing in work area (the inner hash)  */
    /********************************************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_process_2, mcuxClHash_process(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxCl_InputBuffer_t in:        */ (uint8_t *) pInnerHash,
    /* uint32_t inSize:               */ hashSize
    ));
    if(MCUXCLHASH_STATUS_OK != result_Hash_process_2)
    {
        /* Free workarea (pInnerHash) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /**********************************************************************************************************************/
    /* Finalize the outer hash by calling Hash-finalize, write the resulting digest to pOut and its length to pOutLength  */
    /**********************************************************************************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL(result_Hash_finish_2, mcuxClHash_finish(
    /* mcuxCLSession_Handle_t session: */ session,
    /* mcuxClHash_Context_t context:   */ pCtxSw->hashCtx,
    /* mcuxCl_Buffer_t pOut            */ pOut,
    /* uint32_t *const pOutSize,      */ pOutLength
    ));
    if((*pOutLength != hashSize) || (MCUXCLHASH_STATUS_OK != result_Hash_finish_2))
    {
        /* Free workarea (pInnerHash) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    /* Free workarea (pInnerHash) */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLHMAC_INTERNAL_COMPUTE_CPUWORDS(hashSize));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Sw, MCUXCLMAC_STATUS_OK,
            2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
            2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Oneshot_Sw, mcuxClHmac_ComputeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Oneshot_Sw(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength,
    uint8_t *const pOut,
    uint32_t *const pOutLength)
{
    /* [Design]
    - TODO: In my opinion, we cannot save much when doing Hmac_Oneshot except for the storing of the block-sized key in context.
            We could oneshot the outer hash instead of multipart (with just two parts), but we have a hash context from the
            inner hash anyway, so we can just as well re-use that.
            So it's probably easiest to just call Hmac_Init, Hmac_Update, Hmac_Finalize here.
            Otherwise, here's the slightly optimized design, leaving out the key-storing:

    - Prepare a block-sized key from the key given in the Hmac context (pContext) and store it in work area
      - If keySize > blockSize
        - Hash the key in OneShot
        - Append the digest with (blockSize - digestSize) zero bytes such that it fills one hash block
      - Else just append the key with (blockSize - keySize) zero bytes such that it fills one hash block
    - Initialize a Hash context for multipart
    - XOR the ipad to the block-sized key in the work area and Hash-process it (the first block of the inner hash)
    - Hash-process the input pIn with length inLength using the Hash context
    - Finalize the inner hash by calling Hash-finalize with the Hash context and write the digest to work area
    - Initialize a new Hash context (re-using the old context's memory)
    - XOR ipad^opad (to remove the ipad from before) to the block-sized key in the work area and Hash-process it (the first block of the outer hash)
    - Hash-process the digest from before (the inner hash)
    - Finalize the outer hash by calling Hash-finalize, write the resulting digest to pOut and its length to pOutLength
    */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Oneshot_Sw);

    MCUX_CSSL_FP_FUNCTION_CALL(result_HMAC_init, mcuxClHmac_Engine_Init_Sw(
            session,
            pContext
    ));
    if(MCUXCLMAC_STATUS_OK != result_HMAC_init)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result_HMAC_update, mcuxClHmac_Engine_Update_Sw(
            session,
            pContext,
            pIn,
            inLength
    ));
    if(MCUXCLMAC_STATUS_OK != result_HMAC_update)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result_HMAC_finalize, mcuxClHmac_Engine_Finalize_Sw(
            session,
            pContext,
            pOut,
            pOutLength
    ));
    if(MCUXCLMAC_STATUS_OK != result_HMAC_finalize)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Sw, MCUXCLMAC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Sw, MCUXCLMAC_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Init_Sw),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Update_Sw),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Finalize_Sw));
}

const mcuxClHmac_AlgorithmDescriptor_t mcuxClHmac_AlgorithmDescriptor_Sw = {
    .engineInit = mcuxClHmac_Engine_Init_Sw,
    .protectionToken_engineInit = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Init_Sw),
    .engineUpdate = mcuxClHmac_Engine_Update_Sw,
    .protectionToken_engineUpdate = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Update_Sw),
    .engineFinalize = mcuxClHmac_Engine_Finalize_Sw,
    .protectionToken_engineFinalize = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Finalize_Sw),
    .engineOneshot = mcuxClHmac_Engine_Oneshot_Sw,
    .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Oneshot_Sw),
    .addPadding = NULL,
};
