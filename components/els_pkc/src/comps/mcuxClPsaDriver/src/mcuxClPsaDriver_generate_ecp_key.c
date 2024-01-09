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

#include <mcuxClEcc.h>
#include <mcuxClKey.h>
#include <mcuxClMemory_Copy.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>

#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_generate_ecp_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION("PSA_KEY_TYPE_ECC_GET_FAMILY macro comes from external library outside our control")
    psa_ecc_family_t curve = PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION()
    size_t bytes = MCUXCLPSADRIVER_BITS_TO_BYTES(psa_get_key_bits(attributes));

    if(key_buffer_size < bytes)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    //For Montgomery curves
    if(curve == PSA_ECC_FAMILY_MONTGOMERY)
    {
        if(attributes->domain_parameters_size != 0u)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        /* Setup one session to be used by all functions called */
        mcuxClSession_Descriptor_t session;
        //Byte length of a Curve448
        if(bytes == MCUXCLECC_MONT_CURVE448_SIZE_PRIVATEKEY)
        {
            uint32_t pCpuWa[MCUXCLECC_MONT_DHKEYGENERATION_CURVE448_WACPU_SIZE / (sizeof(uint32_t))];
            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONT_DHKEYGENERATION_CURVE448_WACPU_SIZE,
                                     (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONT_DHKEYGENERATION_CURVE448_WAPKC_SIZE));


            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            uint32_t context[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0u};
            mcuxClRandom_Context_t pRng_ctx = (mcuxClRandom_Context_t)context;

            /* Initialize the RNG context */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rngInit_result, rngInit_token, mcuxClRandom_init(&session, pRng_ctx, mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3));

            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != rngInit_token) || (MCUXCLRANDOM_STATUS_OK != rngInit_result))
            {                                                                   
                return PSA_ERROR_GENERIC_ERROR;                                                   
            }                                                                   

            MCUX_CSSL_FP_FUNCTION_CALL_END();                                    

            /* Initialize the PRNG */                                           
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));                        
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))    \
            {                                                                   
                return PSA_ERROR_GENERIC_ERROR;                                                   
            }                                                                   
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Prepare input for key generation */
            MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
            uint32_t privKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE / (sizeof(uint32_t))];
            mcuxClKey_Handle_t privKeyHandler = (mcuxClKey_Handle_t) &privKeyDesc;
            uint8_t pubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
            mcuxClKey_Handle_t pubKeyHandler = (mcuxClKey_Handle_t) &pubKeyDesc;
            MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
            uint8_t pubKeyBuffer[MCUXCLECC_MONT_CURVE448_SIZE_PUBLICKEY]={0};
            uint32_t privKeyLength = 0u;
            uint32_t pubKeyLength = 0u;

            /* Call Dh KeyGeneration for keys generation and check FP and return code */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygeneration_result, keygeneration_token, mcuxClEcc_Mont_DhKeyGeneration(&session,
                                                                 mcuxClKey_Type_Ecc_MontDH_Curve448_KeyPair,
                                                                 mcuxClKey_Protection_None,
                                                                 privKeyHandler, key_buffer, &privKeyLength,
                                                                 pubKeyHandler, pubKeyBuffer, &pubKeyLength));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhKeyGeneration) != keygeneration_token) || (MCUXCLECC_STATUS_OK != keygeneration_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();
            
            *key_buffer_length = (size_t) privKeyLength;

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            return PSA_SUCCESS;
        }

        //Byte length of a Curve25519
        else if(bytes == MCUXCLECC_MONT_CURVE25519_SIZE_PRIVATEKEY)
        {
            uint32_t pCpuWa[MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WACPU_SIZE / (sizeof(uint32_t))];
            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WACPU_SIZE,
                                     (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WAPKC_SIZE));


            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Initialize the RNG */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInit_result, randomInit_token, mcuxClRandom_init(&session,
                                                                       NULL,
                                                                       mcuxClRandomModes_Mode_ELS_Drbg));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != randomInit_token) || (MCUXCLRANDOM_STATUS_OK != randomInit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Initialize the PRNG */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
            /* Prepare input for key generation */
            uint32_t privKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE / (sizeof(uint32_t))];
            mcuxClKey_Handle_t privKeyHandler = (mcuxClKey_Handle_t) &privKeyDesc;
            uint8_t pubKeyDesc[MCUXCLKEY_DESCRIPTOR_SIZE];
            mcuxClKey_Handle_t pubKeyHandler = (mcuxClKey_Handle_t) &pubKeyDesc;
            MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
            uint8_t pubKeyBuffer[MCUXCLECC_MONT_CURVE25519_SIZE_PUBLICKEY]={0};
            uint32_t privKeyLength = 0u;
            uint32_t pubKeyLength = 0u;

            /* Call Dh KeyGeneration for keys generation and check FP and return code */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygeneration_result, keygeneration_token, mcuxClEcc_Mont_DhKeyGeneration(&session,
                                                                  mcuxClKey_Type_Ecc_MontDH_Curve25519_KeyPair,
                                                                  mcuxClKey_Protection_None,
                                                                  privKeyHandler, key_buffer, &privKeyLength,
                                                                  pubKeyHandler, pubKeyBuffer, &pubKeyLength));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhKeyGeneration) != keygeneration_token) || (MCUXCLECC_STATUS_OK != keygeneration_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            *key_buffer_length = (size_t) privKeyLength;

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            return PSA_SUCCESS;
        }
        else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    //For Weierstrass curves, curve_parameters have defined in mcuxClEcc_Constants.c
    else if((curve == PSA_ECC_FAMILY_SECP_R1) || (curve == PSA_ECC_FAMILY_SECP_K1) || (curve == PSA_ECC_FAMILY_BRAINPOOL_P_R1))
    {
        if(attributes->domain_parameters_size != 0u)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        const mcuxClEcc_Weier_DomainParams_t* curveParamData = mcuxClPsaDriver_psa_driver_wrapper_getEccDomainParams(attributes);
        if(NULL == curveParamData)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Initialize buffers on the stack for domain parameters endianess swap (LE -> BE) */
        const uint32_t byteLenP = curveParamData->common.byteLenP;
        const uint32_t byteLenN = curveParamData->common.byteLenN;

        /* Setup one session to be used by all functions called */
        mcuxClSession_Descriptor_t session;

        uint32_t pCpuWa[MCUXCLECC_KEYGEN_WACPU_SIZE(MCUXCLECC_WEIERECC_MAX_SIZE_BASEPOINTORDER) / (sizeof(uint32_t))];
        /* Initialize session with pkcWA on the beginning of PKC RAM */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, sizeof(pCpuWa),
                                 (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_KEYGEN_WAPKC_SIZE(byteLenP,byteLenN)));


        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Initialize the RNG context, with maximum size */
        uint32_t context[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0u};
        mcuxClRandom_Context_t pRng_ctx = (mcuxClRandom_Context_t)context;
        
        mcuxClRandom_Mode_t randomMode = NULL;
        if(byteLenN <= 32u)  /* 128-bit security strength */
        {
          randomMode = mcuxClRandomModes_Mode_ELS_Drbg;
        }
        else  /* 256-bit security strength */
        {
          randomMode = mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3;
        }

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rngInit_result, rngInit_token, mcuxClRandom_init(&session, pRng_ctx, randomMode));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != rngInit_token) || (MCUXCLRANDOM_STATUS_OK != rngInit_result))
        {                                                                   
            return PSA_ERROR_GENERIC_ERROR;                                                   
        }                                                                   

        MCUX_CSSL_FP_FUNCTION_CALL_END();                                    

        /* Initialize the PRNG */                                           
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));                        
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))    \
        {                                                                   
            return PSA_ERROR_GENERIC_ERROR;                                                   
        }                                                                   
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        uint8_t pubKeyBuffer[2u*MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];

        /* Reverse endianess of domain parameters as current ECC component expects domain parameters in big endian */
        uint8_t pG[2u*MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
        uint8_t pA[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
        uint8_t pB[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
        uint8_t pP[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
        uint8_t pN[MCUXCLECC_WEIERECC_MAX_SIZE_BASEPOINTORDER];
        for(uint32_t i = 0; i < byteLenP; i++)
        {
            pA[i] = curveParamData->common.pCurveParam1[byteLenP - i - 1u];
            pB[i] = curveParamData->common.pCurveParam2[byteLenP - i - 1u];
            pP[i] = curveParamData->common.pFullModulusP[byteLenP + MCUXCLPKC_WORDSIZE - i - 1u];
            pG[i] = curveParamData->common.pGx[byteLenP - i - 1u];
            pG[byteLenP + i] = curveParamData->common.pGy[byteLenP - i - 1u];
        }
        for(uint32_t i = 0; i < byteLenN; i++)
        {
            pN[i] = curveParamData->common.pFullModulusN[byteLenN + MCUXCLPKC_WORDSIZE - i - 1u];
        }

        mcuxClEcc_KeyGen_Param_t paramKeyGen =
        {
            .curveParam = (mcuxClEcc_DomainParam_t)
            {
                .pA = pA,
                .pB = pB,
                .pP = pP,
                .pG = pG,
                .pN = pN,
                .misc = mcuxClEcc_DomainParam_misc_Pack(byteLenN, byteLenP)
            },
            .pPrivateKey = key_buffer,
            .pPublicKey = pubKeyBuffer,
            .optLen = 0u
        };

        /* Call KeyGeneration for keys generation and check FP and return code */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygeneration_result, keygeneration_token, mcuxClEcc_KeyGen(&session, &paramKeyGen));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_KeyGen) != keygeneration_token) || (MCUXCLECC_STATUS_OK != keygeneration_result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        *key_buffer_length = byteLenN;
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cleanup_result, cleanup_token, mcuxClSession_cleanup(&session));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup) != cleanup_token) || (MCUXCLSESSION_STATUS_OK != cleanup_result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(destroy_result, destroy_token, mcuxClSession_destroy(&session));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != destroy_token) || (MCUXCLSESSION_STATUS_OK != destroy_result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        return PSA_SUCCESS;
    }
    // Like the twisted Edwards curves Ed25519 and Ed448.
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
}
