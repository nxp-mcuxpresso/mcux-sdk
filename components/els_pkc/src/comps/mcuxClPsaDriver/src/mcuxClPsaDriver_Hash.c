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

#include "common.h"

#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClCipherModes.h>
#include <mcuxClSession.h>
#include <mcuxClMemory_Copy.h>
#include <mcuxClMemory_Clear.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClPsaDriver_Functions.h>


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClHash_AlgorithmDescriptor_t * mcuxClPsaDriver_psa_driver_wrapper_hash_set_algorithmDescriptor(
    psa_algorithm_t alg)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
    switch(alg)
    {
    case PSA_ALG_SHA_224:
        return mcuxClHash_Algorithm_Sha224;
    case PSA_ALG_SHA_256:
        return mcuxClHash_Algorithm_Sha256;
    case PSA_ALG_SHA_384:
        return mcuxClHash_Algorithm_Sha384;
    case PSA_ALG_SHA_512:
        return mcuxClHash_Algorithm_Sha512;
    default:
        return NULL;
    }
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_setup(
    psa_hash_operation_t *operation,
    psa_algorithm_t alg)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Select algorithm descriptor */
    const mcuxClHash_AlgorithmDescriptor_t *hashAlgo = mcuxClPsaDriver_psa_driver_wrapper_hash_set_algorithmDescriptor(alg);

    if(NULL == hashAlgo)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Initialize the hash operation */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Hash_t * pClnsHashData = (mcuxClPsaDriver_ClnsData_Hash_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClHash_init(
                    /* mcuxCLSession_Handle_t session: */ NULL,
                    /* mcuxClHash_Context_t context:   */ &pClnsHashData->ctx,
                    /* mcuxClHash_Algo_t  algo:        */ hashAlgo));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init) != token) || (MCUXCLHASH_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Set PSA algorithm ID */
    operation->id = psa_driver_wrapper_get_clns_operation_id();

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
 psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_update(
    psa_hash_operation_t *operation,
    const uint8_t *input,
    size_t input_length )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Allocate workarea space */
    uint32_t cpuWorkarea[MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_MAX / sizeof(uint32_t)];
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Hash_t * pClnsHashData = (mcuxClPsaDriver_ClnsData_Hash_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(pClnsHashData->ctx.algo == NULL)
    {
        return PSA_ERROR_BAD_STATE;
    }

    /* Create session */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(
                                                          session,
                                                          cpuWorkarea,
                                                          MCUXCLHASH_PROCESS_CPU_WA_BUFFER_SIZE_MAX,
                                                          NULL,
                                                          0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Perform the hashing operation */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClHash_process(
                                                          session,
                                                          &pClnsHashData->ctx,
                                                          input,
                                                          input_length));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process) != token) || (MCUXCLHASH_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}

/*
 * Hashing functions
 */

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_compute(
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Select algorithm descriptor */
    const mcuxClHash_AlgorithmDescriptor_t *hashAlgo = mcuxClPsaDriver_psa_driver_wrapper_hash_set_algorithmDescriptor(alg);

    if(NULL == hashAlgo)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Allocate workarea space */
    uint32_t cpuWorkarea[MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MAX / sizeof(uint32_t)];

    /* Create session */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(
                                                          session,
                                                          cpuWorkarea,
                                                          MCUXCLHASH_COMPUTE_CPU_WA_BUFFER_SIZE_MAX,
                                                          NULL,
                                                          0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Check if output buffer has a valid size, otherwise return */
    if(hashAlgo->hashSize > hash_size)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Perform the hashing operation */
    uint32_t hashOutputSize = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClHash_compute(
                                                          session,
                                                          hashAlgo,
                                                          input,
                                                          input_length,
                                                          hash,
                                                          &hashOutputSize));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) != token) || (MCUXCLHASH_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Update the hash length */
    if(hash_length != NULL) {
        *hash_length = hashAlgo->hashSize;
    }

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_finish(
    psa_hash_operation_t *operation,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Allocate workarea space */
    uint32_t cpuWorkarea[MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MAX / sizeof(uint32_t)];

    /* Create session */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    /* Set hash_length and check consistency with Algo->hashSize */
    *hash_length = hash_size;
    
    /* Set hash_length correctly and check consistency with hash_size */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Hash_t * pClnsHashData = (mcuxClPsaDriver_ClnsData_Hash_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(pClnsHashData->ctx.algo->hashSize > hash_size)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }
	
    /* Update the actual hashsize from algorithum*/
    *hash_length = pClnsHashData->ctx.algo->hashSize;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(
                                                      session,
                                                      cpuWorkarea,
                                                      MCUXCLHASH_FINISH_CPU_WA_BUFFER_SIZE_MAX,
                                                      NULL,
                                                      0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Perform the hashing operation */
    uint32_t hashOutputSize = 0;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClHash_finish(
                                                       session,
                                                       &pClnsHashData->ctx,
                                                       hash,
                                                       &hashOutputSize));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish) != token) || (MCUXCLHASH_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_clone(
    const psa_hash_operation_t *source_operation,
    psa_hash_operation_t *target_operation )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{

    /* Copy hash context to target hash operation handle */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (
                                                      target_operation->ctx.clns_data,
                                                      source_operation->ctx.clns_data,
                                                      MCUXCLPSADRIVER_CLNSDATA_HASH_SIZE,
                                                      MCUXCLPSADRIVER_CLNSDATA_HASH_SIZE));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    target_operation->id = source_operation->id;

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_abort(
    psa_hash_operation_t *operation )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    /* Clear hash clns data (context) */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_clear (
                                                        operation->ctx.clns_data,
                                                        MCUXCLPSADRIVER_CLNSDATA_HASH_SIZE,
                                                        MCUXCLPSADRIVER_CLNSDATA_HASH_SIZE));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear) != token)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    return PSA_SUCCESS;

}


