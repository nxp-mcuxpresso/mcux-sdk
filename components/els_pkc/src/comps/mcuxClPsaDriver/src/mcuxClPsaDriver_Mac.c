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

#include <mcuxCsslAnalysis.h>
#include <mcuxClKey.h>
#include <mcuxClMac.h>
#include <mcuxClMacModes.h>
#include <mcuxClHmac.h>
#include <mcuxClMemory_Copy.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClMac_Internal_Constants.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer_internal(
        psa_mac_operation_t *operation,
        mcuxClKey_Descriptor_t *pKey,
        psa_algorithm_t alg);

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_updateLayer(
    psa_mac_operation_t *operation,
    const uint8_t *input,
    size_t input_length )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Mac_t * pClnsMacData = (mcuxClPsaDriver_ClnsData_Mac_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* No support for multipart Hmac in CL */
    if(PSA_ALG_IS_HMAC(pClnsMacData->alg) == true)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    uint32_t cpuWorkarea[MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE_IN_WORDS];
    /* Create session */
    mcuxClSession_Descriptor_t session;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session,
                                                                    cpuWorkarea,
                                                                    MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE,
                                                                    NULL,
                                                                    0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call the mcuxClMac_process */
    mcuxClKey_Descriptor_t * keyDesc = &pClnsMacData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
   MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Ctx is created from internal type and casted to API")
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(processResult, processToken, mcuxClMac_process(&session,
                                                                                  (mcuxClMac_Context_t *) &pClnsMacData->ctx,
                                                                                  input,
                                                                                  input_length));

   MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process) != processToken) || (MCUXCLMAC_STATUS_OK != processResult))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_computeLayer(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    const mcuxClMac_ModeDescriptor_t * mode;
    mode = mcuxClPsaDriver_psa_driver_wrapper_mac_getMode(attributes, alg);
    if (mode == NULL)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ( mac_size == 0u ||  mac_size > mode->common.macByteSize)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    // INIT
    struct psa_mac_operation_s operation = psa_mac_operation_init();
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Mac_t * pClnsMacData = (mcuxClPsaDriver_ClnsData_Mac_t *) operation.ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* Set alg in clns_data for update and finalize */
    pClnsMacData->alg = alg;

    /* No support for multipart Hmac */
    if(PSA_ALG_IS_HMAC(alg) == true)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    mcuxClKey_Descriptor_t * keyDesc = &pClnsMacData->keydesc;
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, keyDesc);
    if(PSA_SUCCESS != keyStatus)
    {
        return keyStatus;
    }
    status = mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer_internal(&operation,
                                                                       keyDesc,
                                                                       alg);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    // UPDATE
    uint32_t cpuWorkarea[MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE_IN_WORDS];
    /* Create session */
    mcuxClSession_Descriptor_t session;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session,
                                                                    cpuWorkarea,
                                                                    MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE,
                                                                    NULL,
                                                                    0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call the mcuxClMac_process */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(processResult, processToken, mcuxClMac_process(&session,
MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
                                                                                  (mcuxClMac_Context_t *) &pClnsMacData->ctx,
MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
                                                                                  input,
                                                                                  input_length));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process) != processToken) || (MCUXCLMAC_STATUS_OK != processResult))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    // FINALIZE
    uint32_t outputSize = 0u;
	uint8_t tempMaxMac[MCUXCLMAC_MAX_OUTPUT_SIZE];
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(finishResult, finishToken, mcuxClMac_finish(&session,
MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
                                                                               (mcuxClMac_Context_t *) &pClnsMacData->ctx,
MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
                                                                               tempMaxMac,
                                                                               &outputSize
                                                                               ));

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish) != finishToken) || (MCUXCLMAC_STATUS_OK != finishResult))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* user should ensure that 0 < mac_size <  MCUXCLMAC_MAX_OUTPUT_SIZE */
    mcuxClKey_AlgorithmId_t keyAlgorithm = mcuxClKey_getAlgorithm(keyDesc);
    psa_key_type_t keyType = 0u;
    size_t keySize = mcuxClKey_getSize(keyDesc);

    if(MCUXCLKEY_ALGO_ID_HMAC == keyAlgorithm)
    {
      keyType = PSA_KEY_TYPE_HMAC;
    }
    else if(MCUXCLKEY_ALGO_ID_AES == keyAlgorithm)
    {
      keyType = PSA_KEY_TYPE_AES;
    }
    else
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Set the MAC size for the specified algorithm */
    *mac_length = PSA_MAC_LENGTH(keyType, keySize, alg);

    /* Check to ensure that MAC size is not larger than output buffer */
    if(*mac_length > mac_size)
    {
      *mac_length = 0u;
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenNxpClMemory_copy,mcuxClMemory_copy (
                                                                                mac,
                                                                                tempMaxMac,
                                                                                *mac_length,
                                                                                *mac_length));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenNxpClMemory_copy)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
	MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_finalizeLayer(
    psa_mac_operation_t *operation,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Mac_t * pClnsMacData = (mcuxClPsaDriver_ClnsData_Mac_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    /* No support for multipart Hmac in CL */
    if(PSA_ALG_IS_HMAC(pClnsMacData->alg) == true)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE_IN_WORDS];

    /* Create session */
    mcuxClSession_Descriptor_t session;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session,
                                                                    cpuWorkarea,
                                                                    MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE,
                                                                    NULL,
                                                                    0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /* Call the mcuxClMac_finish */
    mcuxClKey_Descriptor_t * keyDesc = &pClnsMacData->keydesc;

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    uint32_t outputSize = 0u;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Ctx is created from internal type and casted to API")
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(finishResult, finishToken, mcuxClMac_finish(&session,
                                                                               (mcuxClMac_Context_t *) &pClnsMacData->ctx,
                                                                               mac,
                                                                               &outputSize
                                                                               ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish) != finishToken) || (MCUXCLMAC_STATUS_OK != finishResult))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return PSA_SUCCESS;
}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClMac_ModeDescriptor_t * mcuxClPsaDriver_psa_driver_wrapper_mac_getMode(const psa_key_attributes_t *attributes, psa_algorithm_t alg)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    if(attributes->core.type == PSA_KEY_TYPE_AES)
    {
        MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
        switch(PSA_ALG_FULL_LENGTH_MAC(alg))
        {
            //AES based algorithms and paddings
            case PSA_ALG_CMAC:
                return mcuxClMac_Mode_CMAC;
            case PSA_ALG_CBC_MAC:
                /* PSA standard does not specify CBC-MAC with padding. ISO Padding Method2 was chosen here because it is the most commonly used padding for CBC-MAC. */
                return mcuxClMac_Mode_CBCMAC_PaddingISO9797_1_Method2;
            default:
                return NULL;
        }
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
    }
    else if(PSA_ALG_IS_HMAC(alg) == true)
    {
        if(PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_256)
        {
            return mcuxClMac_Mode_HMAC_SHA2_256_ELS;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer_internal(
        psa_mac_operation_t *operation,
        mcuxClKey_Descriptor_t *pKey,
        psa_algorithm_t alg)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    const mcuxClMac_ModeDescriptor_t * mode = mcuxClPsaDriver_psa_driver_wrapper_mac_getMode(attributes, alg);
    if (mode == NULL)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Key buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE_IN_WORDS];

    /* Create session */
    mcuxClSession_Descriptor_t session;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_init(&session,
                                                                    cpuWorkarea,
                                                                    MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE,
                                                                    NULL,
                                                                    0u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Create input in a way supported by mcuxClMac_init */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Cast needed because ctx was created from size define")
    mcuxClPsaDriver_ClnsData_Mac_t * pClnsMacData = (mcuxClPsaDriver_ClnsData_Mac_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClMac_init(&session,
MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                                (mcuxClMac_Context_t *) &pClnsMacData->ctx,
MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                                (mcuxClKey_Handle_t)pKey,
                                                                mode
                                                                ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init) != token) || (MCUXCLMAC_STATUS_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /*if reach this place, it is properly handled already, so id have to be set*/
    operation->id = psa_driver_wrapper_get_clns_operation_id();

    /* Return with success */
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_mac_operation_t *operation,
    psa_algorithm_t alg )
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPsaDriver_ClnsData_Mac_t * pClnsMacData = (mcuxClPsaDriver_ClnsData_Mac_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    
    /* Set alg in clns_data for update and finalize */
    pClnsMacData->alg = alg;

    /* No support for multipart Hmac */
    if(PSA_ALG_IS_HMAC(alg) == true)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    
    mcuxClKey_Descriptor_t * keyDesc = &pClnsMacData->keydesc;
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, keyDesc);
    if(PSA_SUCCESS != keyStatus)
    {
        return keyStatus;
    }
    status = mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer_internal(operation,
                                                                       keyDesc,
                                                                       alg);

    if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(keyDesc))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

	return status;

}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_abort(psa_mac_operation_t *operation)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
	mcuxClPsaDriver_ClnsData_Mac_t * pClnsMacData = (mcuxClPsaDriver_ClnsData_Mac_t *) operation->ctx.clns_data;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

	if(PSA_SUCCESS !=  mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&pClnsMacData->keydesc))
	{
		return PSA_ERROR_GENERIC_ERROR;
	}

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenClear, mcuxClMemory_clear((uint8_t *)pClnsMacData,
                                                                       MCUXCLPSADRIVER_CLNSDATA_MAC_SIZE,
                                                                       MCUXCLPSADRIVER_CLNSDATA_MAC_SIZE));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear) != tokenClear)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
	 
    /* Return with success */
    return PSA_SUCCESS;
}


