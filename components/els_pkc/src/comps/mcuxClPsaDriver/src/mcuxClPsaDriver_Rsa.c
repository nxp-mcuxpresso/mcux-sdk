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
#include <mcuxClMemory_Copy.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClRsa.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPsaDriver_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClPsaDriver_Functions.h>

static const uint8_t defaultExponent[] = {0x01u, 0x00u, 0x01u};

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_computeRsa_D(
    mcuxClSession_Handle_t pSession, uint8_t *key_CrtBuf,
    uint8_t *key_PublicBuf, mcuxClRsa_KeyEntry_t dKey)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClRsa_Key *pRsaCrtKey = (mcuxClRsa_Key *) key_CrtBuf;
    mcuxClRsa_Key *pRsaPubKey = (mcuxClRsa_Key *) key_PublicBuf;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if((pRsaCrtKey->keytype != MCUXCLRSA_KEY_PRIVATECRT)
        || (pRsaPubKey->keytype != MCUXCLRSA_KEY_PUBLIC))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /*
     * Calculate parameter D through P and Q from CRT KEY
     *  d := e^(-1) mod lcm(p-1, q-1)
     *
     * Used functions: mcuxClRsa_ComputeD
    */
    uint32_t backup_pkcWaUsed = pSession->pkcWa.used;
    uint32_t backup_cpuWaUsed = pSession->cpuWa.used;
    // Initialize PKC.
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClPkc_State_t * pPkcStateBackup = (mcuxClPkc_State_t *) &pSession->cpuWa.buffer[pSession->cpuWa.used];
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    pSession->cpuWa.used += (sizeof(mcuxClPkc_State_t) / (sizeof(uint32_t)));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_PROTECTED(pkcInitialize_token, mcuxClPkc_Initialize(pPkcStateBackup));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize) != pkcInitialize_token))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    //Allocate buffers in PKC RAM
    const uint32_t byteLenPrime = pRsaCrtKey->pMod1->keyEntryLength;
    const uint32_t byteLenKey = byteLenPrime * 2u;
    const uint32_t pkcByteLenKey = MCUXCLPKC_ROUNDUP_SIZE(byteLenKey);
    const uint32_t pkcByteLenPrime = MCUXCLPKC_ROUNDUP_SIZE(byteLenPrime);
    uint8_t * pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
    uint8_t * pPkcBufferP = pPkcWorkarea + MCUXCLPKC_WORDSIZE;
    uint8_t * pPkcBufferQ = pPkcBufferP + pkcByteLenPrime + MCUXCLPKC_WORDSIZE;
    uint8_t * pPkcBufferE = pPkcBufferQ + pkcByteLenPrime;
    uint8_t * pPkcBufferD = pPkcBufferE + pkcByteLenKey + MCUXCLPKC_WORDSIZE;
    /* Allocate space in session for p, q and e for now */
    pSession->pkcWa.used += (2u * (pkcByteLenPrime + MCUXCLPKC_WORDSIZE) + pkcByteLenKey) / (sizeof(uint32_t));
    //copy parameter to pkc address firstly
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (pPkcBufferE,
                                                                     pRsaPubKey->pExp1->pKeyEntryData,
                                                                     pRsaPubKey->pExp1->keyEntryLength,
                                                                     pRsaPubKey->pExp1->keyEntryLength));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (pPkcBufferP,
                                                                     pRsaCrtKey->pMod1->pKeyEntryData,
                                                                     pRsaCrtKey->pMod1->keyEntryLength,
                                                                     pRsaCrtKey->pMod1->keyEntryLength));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (pPkcBufferQ,
                                                                     pRsaCrtKey->pMod2->pKeyEntryData,
                                                                     pRsaCrtKey->pMod2->keyEntryLength,
                                                                     pRsaCrtKey->pMod2->keyEntryLength));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    uint32_t byteLenE;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClRsa_VerifyE(pRsaPubKey->pExp1, &byteLenE));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_VerifyE) != token) || (MCUXCLRSA_STATUS_KEYGENERATION_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    mcuxClRsa_KeyEntry_t e;
    e.keyEntryLength = byteLenE;
    e.pKeyEntryData = pPkcBufferE;
    mcuxClRsa_KeyEntry_t p;
    p.keyEntryLength = byteLenPrime;
    p.pKeyEntryData = pPkcBufferP;
    mcuxClRsa_KeyEntry_t q;
    q.keyEntryLength = byteLenPrime;
    q.pKeyEntryData = pPkcBufferQ;
    mcuxClRsa_KeyEntry_t d;
    d.keyEntryLength = byteLenKey; /* it will be computed by mcuxClRsa_ComputeD */
    d.pKeyEntryData = pPkcBufferD;

    pSession->pkcWa.used += pkcByteLenKey / (sizeof(uint32_t)); // allocate space for the D
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClRsa_ComputeD(pSession, &e, &p, &q, &d, byteLenKey * 8u));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_ComputeD) != token) || (MCUXCLRSA_STATUS_KEYGENERATION_OK != result))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (dKey.pKeyEntryData,
                                                                     d.pKeyEntryData,
                                                                     d.keyEntryLength,
                                                                     d.keyEntryLength));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    dKey.keyEntryLength = d.keyEntryLength;

    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    /* De-initialize PKC */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_PROTECTED(pkcDeInitialize_token, mcuxClPkc_Deinitialize(pPkcStateBackup));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) != pkcDeInitialize_token))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Recover session info */
    pSession->pkcWa.used = backup_pkcWaUsed;
    pSession->cpuWa.used = backup_cpuWaUsed;
    return PSA_SUCCESS;
}

static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_rsa_key_der(
    mcuxClSession_Handle_t pSession, uint8_t *key_CrtBuf,
    uint8_t *key_PublicBuf, mcuxClRsa_KeyEntry dKey, uint8_t *encoded_key, size_t *key_buffer_length)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClRsa_Key *pRsaCrtKey = (mcuxClRsa_Key *) key_CrtBuf;
    mcuxClRsa_Key *pRsaPubKey = (mcuxClRsa_Key *) key_PublicBuf;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if((pRsaCrtKey->keytype != MCUXCLRSA_KEY_PRIVATECRT)
        || (pRsaPubKey->keytype != MCUXCLRSA_KEY_PUBLIC))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /*
     * The final RSA key output format is:
     RSAPrivateKey ::= SEQUENCE {
        version           Version,  -- 0u
        modulus           INTEGER,  -- n
        publicExponent    INTEGER,  -- e
        privateExponent   INTEGER,  -- d
        prime1            INTEGER,  -- p
        prime2            INTEGER,  -- q
        exponent1         INTEGER,  -- d mod (p-1)
        exponent2         INTEGER,  -- d mod (q-1)
        coefficient       INTEGER,  -- (inverse of q) mod p
      }
    */
    encoded_key[0] = 0x30u; /* Sequence tag */
    /* Constructed fields need to be shifted after construction
       since it is too complex to calculate total constructed
       fields length beforehand due to length encoding method of each constructed field
       At most 5 bytes can be used for length (encoded_key[1] - encoded_key[5] reserved) */
    /*
     * Version field
     */
    encoded_key[6] = 0x02u;
    encoded_key[7] = 0x01u;
    encoded_key[8] = 0x00u;

    uint8_t *pDerOtherData = &encoded_key[9];
    /*
     * Get parameter N
     */
    psa_status_t status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaPubKey->pMod1);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    /*
     * Get parameter E
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaPubKey->pExp1);
    if(PSA_SUCCESS != status)
    {
        return status;
    }
    
    /*
     * Get parameter D
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, dKey);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    /*
     * Get parameter P
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaCrtKey->pMod1);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    /*
     * Get parameter Q
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaCrtKey->pMod2);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    /*
     * Get parameter d mod (p-1)
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaCrtKey->pExp1);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    /*
     * Get parameter d mod (q-1)
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaCrtKey->pExp2);
    if(PSA_SUCCESS != status)
    {
        return status;
    }
    /*
     * Get parameter: (inverse of q) mod p
     */
    status = mcuxClPsaDriver_psa_driver_wrapper_der_integer(&pDerOtherData, pRsaCrtKey->pQInv);
    if(PSA_SUCCESS != status)
    {
        return status;
    }

    uint32_t constructed_fields_length = (uint32_t)pDerOtherData - (uint32_t)(&encoded_key[6]);
    uint8_t *ptr = &encoded_key[1];
    uint32_t ptrPluslen = 0u;

    if(constructed_fields_length > 0x7Fu) //long form
    {
        uint8_t h3_byte = (uint8_t)((constructed_fields_length & 0xFF000000u) >> 24u);
        uint8_t h2_byte = (uint8_t)((constructed_fields_length & 0xFF0000u) >> 16u);
        uint8_t h1_byte = (uint8_t)((constructed_fields_length & 0xFF00u) >> 8u);
        uint8_t h0_byte =  (uint8_t)(constructed_fields_length & 0xFFu);
        if(h3_byte != 0u)
        {
            ptr[0u] = 0x84u;
            ptr[1u] = h3_byte;
            ptr[2u] = h2_byte;
            ptr[3u] = h1_byte;
            ptr[4u] = h0_byte;
            ptrPluslen = 5u;
        }
        else if(h2_byte != 0u)
        {
            ptr[0u] = 0x83u;
            ptr[1u] = h2_byte;
            ptr[2u] = h1_byte;
            ptr[3u] = h0_byte;
            ptrPluslen = 4u;
        }
        else if(h1_byte != 0u)
        {
            ptr[0u] = 0x82u;
            ptr[1u] = h1_byte;
            ptr[2u] = h0_byte;
            ptrPluslen = 3u;
        }
        else
        {
            ptr[0u] = 0x81u;
            ptr[1u] = h0_byte;
            ptrPluslen = 2u;
        }
    }
    else  //short from
    {
        ptr[0u] = (uint8_t)constructed_fields_length;
        ptrPluslen = 1u;
    }

    uint32_t i = 0u;
    for(i = 0u; i < constructed_fields_length; ++i)
    {
        ptr[ptrPluslen++] = encoded_key[6u + i];
    }

    *key_buffer_length = (uint32_t)ptr + (uint32_t)ptrPluslen - (uint32_t)(&encoded_key[0]);

    while((ptr + ptrPluslen) != &encoded_key[6u + i + 1u])
    {
        ptr[ptrPluslen++] = 0u;
    }

    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_rsa_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    size_t bitLength = psa_get_key_bits(attributes);
    size_t bytes = MCUXCLPSADRIVER_BITS_TO_BYTES(bitLength);

    if(key_buffer_size < bytes)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if((bitLength != MCUXCLKEY_SIZE_2048)&&
       (bitLength != MCUXCLKEY_SIZE_3072)&&
       (bitLength != MCUXCLKEY_SIZE_4096))
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Setup one session to be used by all functions called */
    mcuxClSession_Descriptor_t session;
    uint32_t pCpuWa[MCUXCLPSADRIVER_RSA_KEY_GEN_BY_CLNS_WACPU_SIZE_MAX / (sizeof(uint32_t))];
    /* Initialize session with pkcWA on the beginning of PKC RAM */
    MCUX_CSSL_ANALYSIS_START_PATTERN_INVARIANT_EXPRESSION_WORKAREA_CALCULATIONS()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(si_status, si_token, mcuxClSession_init(&session, pCpuWa, MCUXCLPSADRIVER_RSA_KEY_GEN_BY_CLNS_WACPU_SIZE_MAX/sizeof(uint32_t),
                             (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS, MCUXCLPSADRIVER_RSA_KEY_GEN_BY_CLNS_WAPKC_SIZE_MAX/sizeof(uint32_t)));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_INVARIANT_EXPRESSION_WORKAREA_CALCULATIONS()


    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != si_token) || (MCUXCLSESSION_STATUS_OK != si_status))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Initialize the RNG context, with maximum size */
    uint32_t rng_ctx[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0u};
    mcuxClRandom_Mode_t randomMode = NULL;
    if(bitLength == MCUXCLKEY_SIZE_4096)  /* 256-bit security strength */
    {
      randomMode = mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3;
    }
    else  /* 128-bit security strength */
    {
      randomMode = mcuxClRandomModes_Mode_ELS_Drbg;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInit_result, randomInit_token, mcuxClRandom_init(&session,
                                                           (mcuxClRandom_Context_t)rng_ctx,
                                                           randomMode));
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

    /* Public exponent */
    mcuxClRsa_KeyEntry_t pubEKey = {0};
    if(NULL == attributes->domain_parameters)
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
        pubEKey.pKeyEntryData = (uint8_t *)defaultExponent;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
        pubEKey.keyEntryLength = 3u;
    }
    else
    {
        pubEKey.pKeyEntryData = (uint8_t*) attributes->domain_parameters;
        pubEKey.keyEntryLength = attributes->domain_parameters_size;
    }


    /* Key type structures */
    mcuxClKey_TypeDescriptor_t type;
    type.algoId = MCUXCLKEY_ALGO_ID_RSA | MCUXCLKEY_ALGO_ID_KEY_PAIR;
    type.size = (uint16_t) bitLength;
    type.info = (void * ) &pubEKey;

    /* Key handle for RSA key type private CRT */
    mcuxClKey_Descriptor_t privKey, pubKey;
    uint8_t pubKeyBuf[MCUXCLRSA_KEYGENERATION_PUBLIC_KEY_DATA_4096_SIZE] = {0U};
    uint32_t pubKeySize = 0u;
    uint8_t priCrtKeyBuf[MCUXCLRSA_KEYGENERATION_CRT_KEY_DATA_4096_SIZE] = {0U};
    uint32_t priCrtKeySize = 0u;

    /* Call key generation and check FP and return code */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(keygen_ret, keygen_token, mcuxClRsa_KeyGeneration_Crt(&session, &type, mcuxClKey_Protection_None,
                                                             (mcuxClKey_Handle_t)&privKey, priCrtKeyBuf, &priCrtKeySize,
                                                             (mcuxClKey_Handle_t)&pubKey, pubKeyBuf, &pubKeySize));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_KeyGeneration_Crt) != keygen_token) || (MCUXCLRSA_STATUS_KEYGENERATION_OK != keygen_ret))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Calculate d and n through CRT key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClRsa_Key *pRsaCrtKey = (mcuxClRsa_Key *) priCrtKeyBuf;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint32_t pD[MCUXCLKEY_SIZE_4096_IN_WORDS];
    mcuxClRsa_KeyEntry_t dKey =
    {
        .pKeyEntryData = (uint8_t*) pD,
        .keyEntryLength = pRsaCrtKey->pMod1->keyEntryLength * 2u
    };
    if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_computeRsa_D(&session, priCrtKeyBuf, pubKeyBuf, dKey))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Combine keys to become the final ASN.1 Der output */
    if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_rsa_key_der(&session, priCrtKeyBuf, pubKeyBuf, &dKey, key_buffer, key_buffer_length))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

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
