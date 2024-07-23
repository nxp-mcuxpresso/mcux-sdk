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

#include "common.h"

#include <mcuxClEls.h>
#include <mcuxClBuffer.h>
#include <mcuxClEcc.h>
#include <mcuxClKey.h>
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
#include <internal/mcuxClPkc_Macros.h>


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
    data[2] = MCUXCLPSADRIVER_MBEDTLS_BYTE_1( pubKeyLen );
    data[3] = MCUXCLPSADRIVER_MBEDTLS_BYTE_0( pubKeyLen );

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
    psa_ecc_family_t curve = MCUXCLPSADRIVER_PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION()
    size_t bytes = MCUXCLPSADRIVER_BITS_TO_BYTES(psa_get_key_bits(attributes));

    //For Montgomery curves
    if(curve == PSA_ECC_FAMILY_MONTGOMERY)
    {
        /* Setup one session to be used by all functions called */
        mcuxClSession_Descriptor_t session;

        /* Initialize the PRNG */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        //Byte length of a Curve448
        if(bytes == MCUXCLECC_MONTDH_CURVE448_SIZE_PRIVATEKEY)
        {
            uint32_t pCpuWa[MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE448_WACPU_SIZE / (sizeof(uint32_t))];
            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE448_WACPU_SIZE,
                                     (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE448_WAPKC_SIZE));


            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Create and fill common structures*/
            mcuxClKey_Descriptor_t privKeyData;

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(privkeyinit_result, privkeyinit_token, mcuxClKey_init(
            /* mcuxClSession_Handle_t session         */ &session,
            /* mcuxClKey_Handle_t key                 */ &privKeyData,
            /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve448_PrivateKey,
            /* const uint8_t * pKeyData              */ key_buffer,
            /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE448_SIZE_PRIVATEKEY));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != privkeyinit_token) || (MCUXCLKEY_STATUS_OK != privkeyinit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            mcuxClKey_Descriptor_t pubKeyData;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            mcuxClEcc_MontDH_DomainParams_t *pDomainParameters = (mcuxClEcc_MontDH_DomainParams_t *)(&mcuxClEcc_MontDH_DomainParams_Curve448);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pubkeyinit_result, pubkeyinit_token, mcuxClKey_init(
            /* mcuxClSession_Handle_t session         */ &session,
            /* mcuxClKey_Handle_t key                 */ &pubKeyData,
            /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve448_PublicKey,
            /* const uint8_t * pKeyData              */ pDomainParameters->common.pGx,
            /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE448_SIZE_PUBLICKEY));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != pubkeyinit_token) || (MCUXCLKEY_STATUS_OK != pubkeyinit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Call Dh KeyAgreement for public keys generation and check FP and return code */
            uint32_t outLength = 0u;
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyagreement_result, keyagreement_token, mcuxClEcc_MontDH_KeyAgreement(&session,
                                                                                            (mcuxClKey_Handle_t) &privKeyData,
                                                                                            (mcuxClKey_Handle_t) &pubKeyData,
                                                                                            (uint8_t *)(data),
                                                                                            &outLength));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_KeyAgreement) != keyagreement_token) || (MCUXCLECC_STATUS_OK != keyagreement_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            *data_length = (size_t)outLength;

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
        else if(bytes == MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY)
        {
            uint32_t pCpuWa[MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WACPU_SIZE / (sizeof(uint32_t))];
            /* Initialize session with pkcWA on the beginning of PKC RAM */
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WACPU_SIZE,
                                     (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLECC_MONTDH_KEYAGREEMENT_CURVE25519_WAPKC_SIZE));


            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            mcuxClKey_Descriptor_t privKeyData;

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(privkeyinit_result, privkeyinit_token, mcuxClKey_init(
            /* mcuxClSession_Handle_t session         */ &session,
            /* mcuxClKey_Handle_t key                 */ &privKeyData,
            /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PrivateKey,
            /* const uint8_t * pKeyData              */ key_buffer,
            /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PRIVATEKEY));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != privkeyinit_token) || (MCUXCLKEY_STATUS_OK != privkeyinit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            mcuxClKey_Descriptor_t pubKeyData;
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
            mcuxClEcc_MontDH_DomainParams_t *pDomainParameters = (mcuxClEcc_MontDH_DomainParams_t *)(&mcuxClEcc_MontDH_DomainParams_Curve25519);
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pubkeyinit_result, pubkeyinit_token, mcuxClKey_init(
            /* mcuxClSession_Handle_t session         */ &session,
            /* mcuxClKey_Handle_t key                 */ &pubKeyData,
            /* mcuxClKey_Type_t type                  */ mcuxClKey_Type_Ecc_MontDH_Curve25519_PublicKey,
            /* const uint8_t * pKeyData              */ pDomainParameters->common.pGx,
            /* uint32_t keyDataLength                */ MCUXCLECC_MONTDH_CURVE25519_SIZE_PUBLICKEY));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != pubkeyinit_token) || (MCUXCLKEY_STATUS_OK != pubkeyinit_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            /* Call Dh KeyAgreement for public keys generation and check FP and return code */
            uint32_t outLength = 0u;
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keyagreement_result, keyagreement_token, mcuxClEcc_MontDH_KeyAgreement(&session,
                                                                                            (mcuxClKey_Handle_t) &privKeyData,
                                                                                            (mcuxClKey_Handle_t) &pubKeyData,
                                                                                            (uint8_t *)(data),
                                                                                            &outLength));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_KeyAgreement) != keyagreement_token) || (MCUXCLECC_STATUS_OK != keyagreement_result))
            {
                return PSA_ERROR_GENERIC_ERROR;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            *data_length = (size_t)outLength;

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
    //For Weierstrass curves, curve_parameters have defined in mcuxClEcc_Types.h
    else if((curve == PSA_ECC_FAMILY_SECP_R1) || (curve == PSA_ECC_FAMILY_SECP_K1) || (curve == PSA_ECC_FAMILY_BRAINPOOL_P_R1))
    {
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

        MCUXCLBUFFER_INIT_RO(buffA, NULL, pA, byteLenP);
        MCUXCLBUFFER_INIT_RO(buffB, NULL, pB, byteLenP);
        MCUXCLBUFFER_INIT_RO(buffP, NULL, pP, byteLenP);
        MCUXCLBUFFER_INIT_RO(buffG, NULL, pG, byteLenP * 2u);
        MCUXCLBUFFER_INIT_RO(buffN, NULL, pN, byteLenN);

        MCUXCLBUFFER_INIT_RO(buffScalar, NULL, key_buffer, byteLenN);
        MCUXCLBUFFER_INIT(buffResult, NULL, (uint8_t *) (data + 1), byteLenP * 2u);

        mcuxClEcc_PointMult_Param_t params =
        {
            .curveParam = (mcuxClEcc_DomainParam_t)
            {
                .pA = buffA,
                .pB = buffB,
                .pP = buffP,
                .pG = buffG,
                .pN = buffN,
                .misc = mcuxClEcc_DomainParam_misc_Pack(byteLenN, byteLenP)
            },
            .pScalar = buffScalar,
            .pPoint = buffG,
            .pResult = buffResult,
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
    psa_key_type_t type = psa_get_key_type(attributes);

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
        if( PSA_KEY_TYPE_IS_RSA(type) || PSA_KEY_TYPE_IS_ECC(type) )
        {
            if( PSA_KEY_TYPE_IS_PUBLIC_KEY( type ) )
            {
                /* Exporting public -> public */
                status = mcuxClPsaDriver_psa_driver_wrapper_export_key_buffer_internal(
                            key.location.pData, key.location.length,
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
                                                          key.location.pData, key.location.length,
                                                          data, data_size, data_length);
                }
                //PSA_KEY_TYPE_ECC_KEY_PAIR_BASE
                else
                {
                    status = mcuxClPsaDriver_psa_driver_wrapper_export_ecp_public_key(attributes,
                                                          key.location.pData, key.location.length,
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

