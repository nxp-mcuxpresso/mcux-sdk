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
#include <mcuxClBuffer.h>
#include <mcuxClEcc.h>
#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClRsa.h>
#include <mcuxClSession.h>
#include <mcuxClMemory_Copy.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <mcuxClPsaDriver_MemoryConsumption.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClPsaDriver_ExternalMacroWrappers.h>


static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign_ECDSASignLayer(mcuxClKey_Descriptor_t *pKey,
                                               psa_algorithm_t alg,
                                               const uint8_t *input,
                                               size_t input_length,
                                               uint8_t *signature,
                                               size_t signature_size,
                                               size_t *signature_length,
                                               bool isHash) //isHash = true
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    if(signature_size < MCUXCLELS_ECC_SIGNATURE_SIZE)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    uint32_t digest[MCUXCLHASH_OUTPUT_SIZE_SHA_256 / sizeof(uint32_t)];
    const uint8_t* pHash = (uint8_t*)digest;

    if (isHash == false) /* the input needs to be hashed */
    {
        size_t digest_length;
        psa_status_t status = mcuxClPsaDriver_psa_driver_wrapper_hash_compute(MCUXCLPSADRIVER_PSA_ALG_SIGN_GET_HASH(alg), input, input_length, (uint8_t*)digest, MCUXCLHASH_OUTPUT_SIZE_SHA_256, &digest_length);
        if(PSA_SUCCESS != status)
        {
            return status;
        }
    }
    else /* the input already contains a digest */
    {
        if((psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_SIGN_HASH) != PSA_KEY_USAGE_SIGN_HASH)
        {
            return PSA_ERROR_GENERIC_ERROR;
        }

        /* Check if the provided input buffer is big enough to contain a full digest */
        if(input_length < MCUXCLHASH_OUTPUT_SIZE_SHA_256)
        {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Copy the digest into the local digest buffer */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenCopy, mcuxClMemory_copy(
            (uint8_t*)digest,
            input,
            MCUXCLHASH_OUTPUT_SIZE_SHA_256,
            input_length
        ));

        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenCopy)
        {
            return PSA_ERROR_GENERIC_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    }

    mcuxClEls_EccSignOption_t SignOptions = {0}; // Initialize a new configuration for the planned mcuxClEls_EccSign_Async operation
    SignOptions.bits.echashchl = (uint8_t)MCUXCLELS_ECC_HASHED;

    /* Aligned output buffer on stack, needed by ELS */
    uint32_t signatureAligned[MCUXCLELS_ECC_SIGNATURE_SIZE / sizeof(uint32_t)];

    MCUX_CSSL_ANALYSIS_START_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_EccSign_Async(  // Perform signature generation.
            SignOptions,                                                    // Set the prepared configuration.
            (mcuxClEls_KeyIndex_t)mcuxClKey_getLoadedKeySlot(pKey),           // Set index of private key in keystore.
            pHash,                                                          // Set pointer to digest, it affects ELS driver only if options.bits.echashch1 set to MCUXCLELS_ECC_HASHED
            NULL,                                                           // Set pointer to message, it affects ELS driver only if options.bits.echashch1 set to MCUXCLELS_ECC_NOT_HASHED
            0,                                                              // Message length, it is ignored in case of processing digest
            (uint8_t*)signatureAligned                                      // Output buffer, which the operation will write the signature to.
            ));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()

    // mcuxClEls_EccSign_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_EccSign_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return PSA_ERROR_HARDWARE_FAILURE; // Expect that no error occurred, meaning that the mcuxClEls_EccSign_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_EccSign_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return PSA_ERROR_HARDWARE_FAILURE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Copy the computed signature to the provided signature/output buffer */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(tokenCopy, mcuxClMemory_copy(
        signature,
        (uint8_t*)signatureAligned,
        MCUXCLELS_ECC_SIGNATURE_SIZE,
        MCUXCLELS_ECC_SIGNATURE_SIZE
    ));

    if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != tokenCopy)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();

    *signature_length = MCUXCLELS_ECC_SIGNATURE_SIZE;
    return PSA_SUCCESS;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign_message(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    /* Create the key */
    mcuxClKey_Descriptor_t key = {0};
    status = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);
    if(PSA_SUCCESS == status)
    {
        if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(&key))
        {
            /*
             * Check if really ECDSA is requested, in any form. PSA_ALG_IS_SIGN_MESSAGE more generic, not needed there.
             * Additional checks performed to make sure we are in proper case
             */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION("PSA macros come from external library outside our control")
            if((PSA_ALG_IS_ECDSA(alg) != true)
                || (MCUXCLPSADRIVER_PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes)) != PSA_ECC_FAMILY_SECP_R1)
                || (MCUXCLPSADRIVER_PSA_ALG_SIGN_GET_HASH(alg) != PSA_ALG_SHA_256))
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION()
            {
                status = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                status = mcuxClPsaDriver_psa_driver_wrapper_sign_ECDSASignLayer(&key,
                                                       alg,
                                                       input,
                                                       input_length,
                                                       signature,
                                                       signature_size,
                                                       signature_length,
                                                       false);
            }
        }
        else if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(&key))
        {
            if(PSA_ALG_IS_SIGN_MESSAGE(alg) != true)
            {
                /* In this scenario we know that alg is incorrect */
                status = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                status = mcuxClPsaDriver_psa_driver_wrapper_sign(&key,
                                                     alg,
                                                     input,
                                                     input_length,
                                                     signature,
                                                     signature_size,
                                                     signature_length,
                                                     false);
            }
        }
        else
        {
            status = PSA_ERROR_CORRUPTION_DETECTED;
        }

        /* unload key */
        psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);

        /* Overwrite status only when status has no error code */
        if(PSA_SUCCESS == status)
        {
            status = keyStatus;
        }
    }
    return status;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign_hash(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input_hash,
    size_t hash_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    /* Create the key */
    mcuxClKey_Descriptor_t key = {0};
    status = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);
    if(PSA_SUCCESS == status)
    {
        if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(&key))
        {
            /*
             * Check if really ECDSA is requested, in any form. PSA_ALG_IS_SIGN_MESSAGE more generic, not needed there.
             * Additional checks performed to make sure we are in proper case
             */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION("PSA macros come from external library outside our control")
            if((PSA_ALG_IS_ECDSA(alg) != true)
                || (MCUXCLPSADRIVER_PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes)) != PSA_ECC_FAMILY_SECP_R1)
                || psa_get_key_bits(attributes) != 256u)
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_OF_COMPOSITE_EXPRESSION()
            {
                status = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                status = mcuxClPsaDriver_psa_driver_wrapper_sign_ECDSASignLayer(&key,
                                                       alg,
                                                       input_hash,
                                                       hash_length,
                                                       signature,
                                                       signature_size,
                                                       signature_length,
                                                       true);
            }
        }
        else if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(&key))
        {
            if(PSA_ALG_IS_SIGN_MESSAGE(alg) != true)
            {
                /* In this scenario we know that alg is incorrect */
                status = PSA_ERROR_NOT_SUPPORTED;
            }
            else
            {
                status = mcuxClPsaDriver_psa_driver_wrapper_sign(&key,
                                                     alg,
                                                     input_hash,
                                                     hash_length,
                                                     signature,
                                                     signature_size,
                                                     signature_length,
                                                     true);
            }
        }
        else
        {
            status = PSA_ERROR_CORRUPTION_DETECTED;
        }

        /* unload key */
        psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);

        /* Overwrite status only when status has no error code */
        if(PSA_SUCCESS == status)
        {
            status = keyStatus;
        }
    }
    return status;
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length,
    bool isHash
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* WCBRD-1105: Also fallback to sw for determinisitc ecdsa case*/
    if( (!PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg))
        && PSA_ALG_IS_RSA_PSS(alg) != true
        && (MCUXCLPSADRIVER_PSA_ALG_IS_ECDSA(alg) != true || MCUXCLPSADRIVER_PSA_ALG_IS_DETERMINISTIC_ECDSA(alg) == true))
    {
      return PSA_ERROR_NOT_SUPPORTED;
    }

    //for signature it must be a key pair
    if(PSA_KEY_TYPE_IS_KEY_PAIR(psa_get_key_type(attributes)) != true)
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    if(true == isHash)
    {
      if((psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_SIGN_HASH) != PSA_KEY_USAGE_SIGN_HASH)
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    }
    else
    {
      if((psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_SIGN_MESSAGE) != PSA_KEY_USAGE_SIGN_MESSAGE)
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    }

    /* Create the session */
    mcuxClSession_Descriptor_t session;
    /* Buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLPSADRIVER_SIGN_BY_CLNS_WACPU_SIZE_MAX / sizeof(uint32_t)];

    /* Create session */
    MCUX_CSSL_ANALYSIS_START_PATTERN_INVARIANT_EXPRESSION_WORKAREA_CALCULATIONS()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLPSADRIVER_SIGN_BY_CLNS_WACPU_SIZE_MAX,
                                                      (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS,
                                                      MCUXCLPSADRIVER_SIGN_BY_CLNS_WAPKC_SIZE_MAX));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_INVARIANT_EXPRESSION_WORKAREA_CALCULATIONS()
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
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
    if( PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) == true
        || PSA_ALG_IS_RSA_PSS(alg) == true)
    {
      /*
       * Decode key
       */
      const uint8_t * pDerData = mcuxClKey_getLoadedKeyData(pKey);
      /* check and skip the sequence + constructed tag */
      if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&pDerData, 0x10u | 0x20u))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }
      /* Check and skip the version tag */
      if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&pDerData, 0x02u))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }

      mcuxClRsa_KeyEntry_t mod1 = {0};
      mcuxClRsa_KeyEntry_t mod2 = {0};
      mcuxClRsa_KeyEntry_t qInv = {0};
      mcuxClRsa_KeyEntry_t rsaExp1 = {0};
      mcuxClRsa_KeyEntry_t rsaExp2 = {0};
      uint32_t keytype = 0;

      if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &mod1))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }

      /* skip the next integer, it is public exponent e */
      if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&pDerData, 0x02u))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }

      /* Check the length of modulus */
       if(mod1.keyEntryLength == 0u)
       {
         /* The key is in CRT form */

         /* skip the next integer, it is private exponent d */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&pDerData, 0x02u))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         /* get prime p */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &mod1))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         /* get prime q */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &mod2))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         /* get exponent dp */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &rsaExp1))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         /* get exponent dq */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &rsaExp2))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         /* get coefficient qInv */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &qInv))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         keytype = MCUXCLRSA_KEY_PRIVATECRT;
       }
       else if(mod1.keyEntryLength != mcuxClKey_getSize(pKey))  /* verify length of key and modulus */
       {
         return PSA_ERROR_GENERIC_ERROR;
       }
       else
       {
         /* Key in plain form, get private exponent d */
         if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &rsaExp1))
         {
           return PSA_ERROR_GENERIC_ERROR;
         }
         keytype = MCUXCLRSA_KEY_PRIVATEPLAIN;
       }

      /* Create key struct */
      const mcuxClRsa_Key private_key =
      {
        .keytype = keytype,
        .pMod1 = &mod1,
        .pMod2 = &mod2,
        .pQInv = &qInv,
        .pExp1 = &rsaExp1,
        .pExp2 = &rsaExp2,
        .pExp3 = NULL
      };

      /* Set options and related parmeters */
      uint32_t options;
      uint32_t messageLength;
      if(true == isHash)
      {
        options = MCUXCLRSA_OPTION_MESSAGE_DIGEST;
        messageLength = 0;
      }
      else
      {
        options = MCUXCLRSA_OPTION_MESSAGE_PLAIN;
        messageLength = input_length;
      }

      /* Set the signature mode and salt length (in case of PSA_ALG_RSA_PSS the salt length should be equal to the length of the hash) */
      const mcuxClRsa_SignVerifyMode_t * pVerifyMode;
      psa_algorithm_t hash_alg = MCUXCLPSADRIVER_PSA_ALG_SIGN_GET_HASH( alg );
      uint32_t saltLength = 0u;
      if(PSA_ALG_IS_RSA_PSS(alg))
      {
        MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
        switch(hash_alg)
        {
          case PSA_ALG_SHA_224:
            pVerifyMode = &mcuxClRsa_Mode_Sign_Pss_Sha2_224;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_224;
            break;
          case PSA_ALG_SHA_256:
            pVerifyMode = &mcuxClRsa_Mode_Sign_Pss_Sha2_256;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_256;
            break;
          case PSA_ALG_SHA_384:
            pVerifyMode = &mcuxClRsa_Mode_Sign_Pss_Sha2_384;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_384;
            break;
          case PSA_ALG_SHA_512:
            pVerifyMode = &mcuxClRsa_Mode_Sign_Pss_Sha2_512;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_512;
            break;
          default:
            return PSA_ERROR_NOT_SUPPORTED;
        }
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
      }
      else if(PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg))
      {
        MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
        switch(hash_alg)
        {
          case PSA_ALG_SHA_224:
            pVerifyMode = &mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_224;
            break;
          case PSA_ALG_SHA_256:
            pVerifyMode = &mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_256;
            break;
          case PSA_ALG_SHA_384:
            pVerifyMode = &mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_384;
            break;
          case PSA_ALG_SHA_512:
            pVerifyMode = &mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_512;
            break;
          default:
            return PSA_ERROR_NOT_SUPPORTED;
        }
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
      }
      else
      {
        return PSA_ERROR_NOT_SUPPORTED;
      }

      if(true == isHash)
      {
        if(pVerifyMode->pHashAlgo1->hashSize != input_length)
        {
          return PSA_ERROR_INVALID_ARGUMENT;
        }
      }

      if(signature_size < mcuxClKey_getSize(pKey))
      {
          return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(sign_result, sign_token, mcuxClRsa_sign(
        /* mcuxClSession_Handle_t           pSession: */           &session,
        /* const mcuxClRsa_Key * const      pKey: */               &private_key,
        /* mcuxCl_InputBuffer_t             pMessageOrDigest: */   input,
        /* const uint32_t                  messageLength: */      messageLength,
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded due to fixed function API. mcuxClRsa_sign does not modify this array")
        /* const mcuxClRsa_SignVerifyMode   pPaddingMode: */       (mcuxClRsa_SignVerifyMode)pVerifyMode,
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
        /* const uint32_t                  saltLength: */         saltLength,
        /* uint32_t                        options: */            options,
        /* uint8_t * const                 pSignature) */         (mcuxCl_Buffer_t )signature));
      *signature_length = mcuxClKey_getSize(pKey);
      if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_sign) != sign_token) || (MCUXCLRSA_STATUS_SIGN_OK != sign_result))
      {
        return PSA_ERROR_INVALID_SIGNATURE;
      }
      MCUX_CSSL_FP_FUNCTION_CALL_END();

    }
    else
    {
      /* Buffer for hash */
      uint8_t hash_buffer[64 /* maximum size of hash output */] = {0};
      const uint8_t * pHash = input;
      uint32_t hashOutputSize = 0u;
      if(true != isHash)
      {
        /* Select algorithm descriptor */
        psa_algorithm_t hash_alg = MCUXCLPSADRIVER_PSA_ALG_SIGN_GET_HASH( alg );
        const mcuxClHash_AlgorithmDescriptor_t *hashAlgo = mcuxClPsaDriver_psa_driver_wrapper_hash_set_algorithmDescriptor(hash_alg);

        /* Perform the hashing operation */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClHash_compute(
                                                              &session,
                                                              hashAlgo,
                                                              input,
                                                              input_length,
                                                              hash_buffer,
                                                              &hashOutputSize));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) != token) || (MCUXCLHASH_STATUS_OK != result))
        {
          return PSA_ERROR_CORRUPTION_DETECTED;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        pHash = hash_buffer;
      }

      mcuxClEcc_Weier_DomainParams_t * domainParams = (mcuxClEcc_Weier_DomainParams_t *) mcuxClKey_getTypeInfo(pKey);

      /* Initialize buffers on the stack for domain parameters endianess swap (LE -> BE) */
      const uint32_t pLen = domainParams->common.byteLenP;
      const uint32_t nLen = domainParams->common.byteLenN;
      uint8_t a[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t b[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t p[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t G[2u * MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t n[MCUXCLECC_WEIERECC_MAX_SIZE_BASEPOINTORDER];
      for(uint32_t i = 0; i < pLen; i++)
      {
          a[i] = domainParams->common.pCurveParam1[pLen - i - 1u];
          b[i] = domainParams->common.pCurveParam2[pLen - i - 1u];
          p[i] = domainParams->common.pFullModulusP[pLen + MCUXCLPKC_WORDSIZE - i - 1u];
          G[i] = domainParams->common.pGx[pLen - i - 1u];
          G[pLen + i] = domainParams->common.pGy[pLen - i - 1u];
      }
      for(uint32_t i = 0; i < nLen; i++)
      {
          n[i] = domainParams->common.pFullModulusN[nLen + MCUXCLPKC_WORDSIZE - i - 1u];
      }

      MCUXCLBUFFER_INIT_RO(buffA, NULL, a, pLen);
      MCUXCLBUFFER_INIT_RO(buffB, NULL, b, pLen);
      MCUXCLBUFFER_INIT_RO(buffP, NULL, p, pLen);
      MCUXCLBUFFER_INIT_RO(buffG, NULL, G, pLen * 2u);
      MCUXCLBUFFER_INIT_RO(buffN, NULL, n, nLen);

      const uint32_t hashLen = isHash ? input_length : hashOutputSize;
      MCUXCLBUFFER_INIT_RO(buffHash, NULL, pHash, hashLen);
      MCUXCLBUFFER_INIT(buffSignature, NULL, signature, nLen * 2u);

      uint8_t * pPrivateKey = mcuxClKey_getLoadedKeyData(pKey);
      mcuxClEcc_Sign_Param_t paramSign =
      {
        .curveParam = (mcuxClEcc_DomainParam_t)
        {
            .pA = buffA,
            .pB = buffB,
            .pP = buffP,
            .pG = buffG,
            .pN = buffN,
            .misc = mcuxClEcc_DomainParam_misc_Pack(nLen, pLen)
        },
        .pHash = buffHash,
        .pPrivateKey = (const uint8_t *) pPrivateKey,
        .pSignature = buffSignature,
        .optLen = mcuxClEcc_Sign_Param_optLen_Pack((256u <= hashLen) ? 255u : hashLen),
        .pMode = &mcuxClEcc_ECDSA_ProtocolDescriptor
      };

      if(signature_size < 2u * nLen)
      {
          return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      /* Initialize the RNG context, with maximum size */
      uint32_t rng_ctx[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0u};

      mcuxClRandom_Mode_t randomMode = NULL;
      if(nLen <= 32u)  /* 128-bit security strength */
      {
        randomMode = mcuxClRandomModes_Mode_ELS_Drbg;
      }
      else  /* 256-bit security strength */
      {
        randomMode = mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3;
      }

      MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInit_result, randomInit_token,
                                      mcuxClRandom_init(&session,
                                                       (mcuxClRandom_Context_t)rng_ctx,
                                                       randomMode));
      if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != randomInit_token) || (MCUXCLRANDOM_STATUS_OK != randomInit_result))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }
      MCUX_CSSL_FP_FUNCTION_CALL_END();

      MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(sign_result, sign_token,
          mcuxClEcc_Sign(&session, &paramSign) );
      *signature_length = 2u * nLen;

      if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Sign) != sign_token) || (MCUXCLECC_STATUS_OK != sign_result))
      {
        return PSA_ERROR_INVALID_SIGNATURE;
      }
      MCUX_CSSL_FP_FUNCTION_CALL_END();
    }


    /* Destroy the session */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClSession_destroy(&session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_destroy) != token) || (MCUXCLSESSION_STATUS_OK != result))
    {
      return PSA_ERROR_CORRUPTION_DETECTED;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return PSA_SUCCESS;
}
