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

#include <mcuxClEls.h>
#include <mcuxClEcc.h>
#include <mcuxClMemory_Copy.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClPsaDriver_Oracle.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClRsa.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClEcc_Mont_Internal.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClKey_Internal.h>


static inline psa_status_t mcuxClPsaDriver_psa_driver_wrapper_export_key_buffer_internal(
                                                    const uint8_t *key_buffer,
                                                    size_t key_buffer_size,
                                                    uint8_t *data,
                                                    size_t data_size,
                                                    size_t *data_length )
{
    if( key_buffer_size > data_size )
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (data,
                                                                     key_buffer,
                                                                     key_buffer_size,
                                                                     key_buffer_size));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenClear, mcuxClMemory_clear(
                                                        data + key_buffer_size,
                                                        data_size - key_buffer_size,
                                                        data_size - key_buffer_size));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear) != tokenClear)
    {
        return PSA_ERROR_CORRUPTION_DETECTED;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    *data_length = key_buffer_size;
    return PSA_SUCCESS;
}

static inline psa_status_t mcuxClPsaDriver_psa_driver_wrapper_export_rsa_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length )
{
    /* MISRA Ex. 9 to Rule 11.3 */
    /* parses the RSA PrivateKey */
    /* Check and skip the version tag */
    mcuxClRsa_KeyEntry_t rsaPrivateN = {0};
    mcuxClRsa_KeyEntry_t rsaPrivateE = {0};
            
    /* check and skip the sequence tag */
    if (PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&key_buffer, 0x10u | 0x20u))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* check and skip the version tag */
    if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&key_buffer, 0x02u))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    const uint8_t *originKey = key_buffer;
    
    /* Modulus*/
    if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&key_buffer, &rsaPrivateN))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    /* Public Exponent*/
    if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&key_buffer, &rsaPrivateE))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    
    size_t pubKeyLen = ((size_t)key_buffer - (size_t)originKey);
    /* Start the public key with sequence, tag and length of public key*/
    size_t seqAndTagLen= 0x04u;
    data[0] = 0x30;
    data[1] = 0x82;        
    data[2] = MBEDTLS_BYTE_1( pubKeyLen );
    data[3] = MBEDTLS_BYTE_0( pubKeyLen );    

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy(data + seqAndTagLen,
                                                                 originKey,
                                                                 pubKeyLen,
                                                                 pubKeyLen));
    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    *data_length = pubKeyLen + seqAndTagLen;

    return PSA_SUCCESS;
}

static inline psa_status_t mcuxClPsaDriver_psa_driver_wrapper_export_ecp_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length )
{
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION("PSA_KEY_TYPE_ECC_GET_FAMILY macro comes from external library outside our control")
    psa_ecc_family_t curve = PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION()
    size_t bytes = MCUXCLPSADRIVER_BITS_TO_BYTES(psa_get_key_bits(attributes));

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
            uint32_t pCpuWa[MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE448_WACPU_SIZE / (sizeof(uint32_t))];
            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE448_WACPU_SIZE,
                                     (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE448_WAPKC_SIZE));


            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Initialize the RNG context */
            uint32_t rng_ctx[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0u};
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInit_result, randomInit_token, mcuxClRandom_init(&session,
                                                                   (mcuxClRandom_Context_t)rng_ctx,
                                                                   mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3));
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

            /* Create and fill common structures*/
            mcuxClKey_Descriptor_t privKeyData;
            privKeyData.type.size = MCUXCLKEY_SIZE_NOTUSED;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            privKeyData.type.info = (void *) &mcuxClEcc_MontDH_DomainParams_Curve448;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            privKeyData.type.algoId = (MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR) ^
                                      (MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PRIVATE_KEY);
            privKeyData.protection = mcuxClKey_Protection_None;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            privKeyData.container.pData = (uint8_t *)key_buffer;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

            mcuxClKey_Descriptor_t pubKeyData;
            pubKeyData.type.size = MCUXCLKEY_SIZE_NOTUSED;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            pubKeyData.type.info = (void *) &mcuxClEcc_MontDH_DomainParams_Curve448;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            pubKeyData.type.algoId = (MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR) ^
                                      (MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PUBLIC_KEY);
            pubKeyData.protection = mcuxClKey_Protection_None;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            mcuxClEcc_MontDH_DomainParams_t *pDomainParameters = (mcuxClEcc_MontDH_DomainParams_t *)(&mcuxClEcc_MontDH_DomainParams_Curve448);
            pubKeyData.container.pData = (uint8_t *)pDomainParameters->common.pGx;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

            /* Call Dh KeyAgreement for public keys generation and check FP and return code */
            uint32_t outLength = 0u;
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyagreement_result, keyagreement_token, mcuxClEcc_Mont_DhKeyAgreement(&session,
                                                                                            (mcuxClKey_Handle_t) &privKeyData,
                                                                                            (mcuxClKey_Handle_t) &pubKeyData,
                                                                                            (uint8_t *)(data+1u),
                                                                                            &outLength));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhKeyAgreement) != keyagreement_token) || (MCUXCLECC_STATUS_OK != keyagreement_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            *data_length = (size_t)outLength;

            *data = 0x04;
            *data_length += 1u;

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
            uint32_t pCpuWa[MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WACPU_SIZE / (sizeof(uint32_t))];
            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WACPU_SIZE,
                                     (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WAPKC_SIZE));


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

            mcuxClKey_Descriptor_t privKeyData;
            privKeyData.type.size = MCUXCLKEY_SIZE_NOTUSED;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            privKeyData.type.info = (void *) &mcuxClEcc_MontDH_DomainParams_Curve25519;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            privKeyData.type.algoId = (MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR) ^
                                      (MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PRIVATE_KEY);
            privKeyData.protection = mcuxClKey_Protection_None;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            privKeyData.container.pData = (uint8_t *)key_buffer;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

            mcuxClKey_Descriptor_t pubKeyData;
            pubKeyData.type.size = MCUXCLKEY_SIZE_NOTUSED;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            pubKeyData.type.info = (void *) &mcuxClEcc_MontDH_DomainParams_Curve25519;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            pubKeyData.type.algoId = (MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR) ^
                                      (MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PUBLIC_KEY);
            pubKeyData.protection = mcuxClKey_Protection_None;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            mcuxClEcc_MontDH_DomainParams_t *pDomainParameters = (mcuxClEcc_MontDH_DomainParams_t *)(&mcuxClEcc_MontDH_DomainParams_Curve25519);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
            pubKeyData.container.pData = (uint8_t *)pDomainParameters->common.pGx;

            /* Call Dh KeyAgreement for public keys generation and check FP and return code */
            uint32_t outLength = 0u;
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyagreement_result, keyagreement_token, mcuxClEcc_Mont_DhKeyAgreement(&session,
                                                                                            (mcuxClKey_Handle_t) &privKeyData,
                                                                                            (mcuxClKey_Handle_t) &pubKeyData,
                                                                                            (uint8_t *)(data+1u),
                                                                                            &outLength));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhKeyAgreement) != keyagreement_token) || (MCUXCLECC_STATUS_OK != keyagreement_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            *data_length = (size_t)outLength;

            *data = 0x04;
            *data_length += 1u;

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
    //For Weierstrass curves, curve_parameters have defined in mcuxClEcc_Constants.h
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

        mcuxClEcc_PointMult_Param_t params =
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
            .pScalar = key_buffer,
            .pPoint = pG,
            .pResult = (uint8_t *) (data + 1),
            .optLen = 0u
        };

        /* Setup one session to be used by all functions called */
        mcuxClSession_Descriptor_t session;

        uint32_t pCpuWa[MCUXCLECC_POINTMULT_WACPU_SIZE / sizeof(uint32_t)];
        /* Initialize session with pkcWA on the beginning of PKC RAM */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_POINTMULT_WACPU_SIZE,
                                 (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_POINTMULT_WAPKC_SIZE(byteLenP,byteLenN)));


        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
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

        /* Call PointMult for public keys generation and check FP and return code */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pointMult_result, pointMult_token, mcuxClEcc_PointMult(&session, &params));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointMult) != pointMult_token) || (MCUXCLECC_STATUS_OK != pointMult_result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        *data_length = 2u*byteLenP + 1u;
        *data = 0x04;

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
    else
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_export_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    uint8_t *data,
    size_t data_size,
    size_t *data_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t type = attributes->core.type;

    /* Reject a zero-length output buffer now, since this can never be a
     * valid key representation. This way we know that data must be a valid
     * pointer and we can do things like memset(data, ..., data_size). */
    if( data_size == 0u )
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    psa_status_t psa_status = PSA_ERROR_NOT_SUPPORTED;
    mcuxClKey_Descriptor_t key = {0};

    psa_status = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);

    if (PSA_SUCCESS != psa_status)
    {
        return psa_status;
    }

    if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(&key))
    {
        /* This function keeps the output of the first KeyGen (mcuxClPsaDriver_psa_driver_wrapper_createClKey)
           in RAM without running KeyGen again as opposed to mcuxClPsaDriver_psa_driver_wrapper_export_s50_public */
        status = mcuxClPsaDriver_Oracle_ExportPublicKey (&key, data, data_size, data_length, false);
    }
    else
    {
        if( key_type_is_raw_bytes(type) )
        {
            status = mcuxClPsaDriver_psa_driver_wrapper_export_key_buffer_internal(key_buffer, key_buffer_size,
                                                   data, data_size, data_length);
        }

        if( PSA_KEY_TYPE_IS_RSA(type) || PSA_KEY_TYPE_IS_ECC(type) )
        {
            if( PSA_KEY_TYPE_IS_PUBLIC_KEY( type ) )
            {
                /* Exporting public -> public */
                status = mcuxClPsaDriver_psa_driver_wrapper_export_key_buffer_internal(
                            key_buffer, key_buffer_size,
                            data, data_size, data_length);
            }
            /* If its not a public key, only then go and check for RSA or ECC key pairs*/
            else
            {
                /* Need to export the public part of a private key,
                 * so conversion is needed. Try the accelerators first. */
                if( !PSA_KEY_TYPE_IS_KEY_PAIR(type) )
                {
                    return PSA_ERROR_INVALID_ARGUMENT;
                }

                //PSA_KEY_TYPE_RSA_KEY_PAIR
                if( PSA_KEY_TYPE_IS_RSA(type) )
                {
                    status = mcuxClPsaDriver_psa_driver_wrapper_export_rsa_public_key(attributes,
                                                          key_buffer, key_buffer_size,
                                                          data, data_size, data_length);
                }
                //PSA_KEY_TYPE_ECC_KEY_PAIR_BASE
                else
                {
                    status = mcuxClPsaDriver_psa_driver_wrapper_export_ecp_public_key(attributes,
                                                          key_buffer, key_buffer_size,
                                                          data, data_size, data_length);
                }
            }
        }
        else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    /* unload key */
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);

    /* Overwrite status only when status has no error code */
    if(PSA_SUCCESS == status)
    {
        status = keyStatus;
    }
    return status;
}

