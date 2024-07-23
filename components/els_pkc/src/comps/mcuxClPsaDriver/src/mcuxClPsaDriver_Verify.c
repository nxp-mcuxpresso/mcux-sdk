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
#include <mcuxClBuffer.h>
#include <mcuxClEls.h>
#include <mcuxClEcc.h>
#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClPsaDriver_Oracle.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClRsa.h>
#include <mcuxClSession.h>
#include <mcuxClCore_Macros.h>

#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <mcuxClPsaDriver_MemoryConsumption.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClPsaDriver_ExternalMacroWrappers.h>


static psa_status_t mcuxClPsaDriver_psa_driver_wrapper_verify_internal(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature,
    size_t signature_length,
    bool isHash
)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =(psa_key_attributes_t *)mcuxClKey_getAuxData(pKey);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    if( PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) != true
        && PSA_ALG_IS_RSA_PSS(alg) != true
        && PSA_ALG_IS_ECDSA(alg)  != true)
    {
      return PSA_ERROR_NOT_SUPPORTED;
    }

    if((PSA_KEY_TYPE_IS_KEY_PAIR(psa_get_key_type(attributes)) != true)
        && (PSA_KEY_TYPE_IS_PUBLIC_KEY(psa_get_key_type(attributes)) != true))
    {
        /* Invalid key type detected, The response shall be  PSA_ERROR_NOT_SUPPORTED */
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if(true == isHash)
    {
      if(PSA_ALG_IS_SIGN_HASH(alg) != true)
      {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      if((psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_VERIFY_HASH) != PSA_KEY_USAGE_VERIFY_HASH)
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    }
    else
    {
      if(PSA_ALG_IS_SIGN_MESSAGE(alg) != true)
      {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      if((psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_VERIFY_MESSAGE) != PSA_KEY_USAGE_VERIFY_MESSAGE)
      {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    }

    /* Create the session */
    mcuxClSession_Descriptor_t session;
    /* Buffer for the CPU workarea in memory. */
    uint32_t cpuWorkarea[MCUXCLPSADRIVER_VERIFY_BY_CLNS_WACPU_SIZE_MAX / sizeof(uint32_t)];

    /* Create session */
    MCUX_CSSL_ANALYSIS_START_PATTERN_INVARIANT_EXPRESSION_WORKAREA_CALCULATIONS()
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultSessionInit, tokenSessionInit,
                                    mcuxClSession_init(&session,
                                                      cpuWorkarea,
                                                      MCUXCLPSADRIVER_VERIFY_BY_CLNS_WACPU_SIZE_MAX,
                                                      (uint32_t *) MCUXCLPKC_RAM_START_ADDRESS,
                                                      MCUXCLPSADRIVER_VERIFY_BY_CLNS_WAPKC_SIZE_MAX));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_INVARIANT_EXPRESSION_WORKAREA_CALCULATIONS()
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_init) != tokenSessionInit) || (MCUXCLSESSION_STATUS_OK != resultSessionInit))
    {
      return PSA_ERROR_GENERIC_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Initialize the PRNG */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(&session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) ||
        (MCUXCLRANDOM_STATUS_OK != prngInit_result))
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

      if (PSA_KEY_TYPE_IS_PUBLIC_KEY(psa_get_key_type(attributes)) != true)
      {
        /* check and skip the version tag */
        if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(&pDerData, 0x02u))
        {
          return PSA_ERROR_GENERIC_ERROR;
        }
      }

      /* get modulus N */
      mcuxClRsa_KeyEntry_t mod1 = {0};
      if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &mod1))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }

      /* verify length of key and modulus */
      if(mod1.keyEntryLength != mcuxClKey_getSize(pKey))  /* verify length of key and modulus */
      {
        return PSA_ERROR_GENERIC_ERROR;
      }

      /* verify length of signature */
      if (mod1.keyEntryLength != signature_length)
      {
        return PSA_ERROR_INVALID_SIGNATURE;
      }

      /* get public exponent e */
      mcuxClRsa_KeyEntry_t exp1 = {0};
      if(PSA_SUCCESS != mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(&pDerData, &exp1))
      {
        return PSA_ERROR_GENERIC_ERROR;
      }

      /* Create key struct of type MCUXCLRSA_KEY_PUBLIC */
      const mcuxClRsa_Key public_key_other =
      {
        .keytype = MCUXCLRSA_KEY_PUBLIC,
        .pMod1 = &mod1,
        .pMod2 = NULL,
        .pQInv = NULL,
        .pExp1 = &exp1,
        .pExp2 = NULL,
        .pExp3 = NULL
      };

      /* Set options and related parmeters */
      uint32_t messageLength;
      uint32_t options;
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

      /* Set the verification mode (in case of PSA_ALG_RSA_PSS the salt length should be equal to the length of the hash) */
      const mcuxClRsa_SignVerifyMode_t * pVerifyMode;
      psa_algorithm_t hash_alg = MCUXCLPSADRIVER_PSA_ALG_SIGN_GET_HASH(alg);
      uint32_t saltLength = 0u;

      if(PSA_ALG_IS_RSA_PSS(alg))
      {
        MCUX_CSSL_ANALYSIS_START_PATTERN_SWITCH_STATEMENT_RETURN_TERMINATION()
        switch(hash_alg)
        {
          case PSA_ALG_SHA_224:
            pVerifyMode = &mcuxClRsa_Mode_Verify_Pss_Sha2_224;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_224;
            break;
          case PSA_ALG_SHA_256:
            pVerifyMode = &mcuxClRsa_Mode_Verify_Pss_Sha2_256;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_256;
            break;
          case PSA_ALG_SHA_384:
            pVerifyMode = &mcuxClRsa_Mode_Verify_Pss_Sha2_384;
            saltLength = MCUXCLHASH_OUTPUT_SIZE_SHA_384;
            break;
          case PSA_ALG_SHA_512:
            pVerifyMode = &mcuxClRsa_Mode_Verify_Pss_Sha2_512;
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
            pVerifyMode = &mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_224;
            break;
          case PSA_ALG_SHA_256:
            pVerifyMode = &mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_256;
            break;
          case PSA_ALG_SHA_384:
            pVerifyMode = &mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_384;
            break;
          case PSA_ALG_SHA_512:
            pVerifyMode = &mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_512;
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

      if (true == isHash)
      {
        if(pVerifyMode->pHashAlgo1->hashSize != input_length)
        {
          return PSA_ERROR_INVALID_ARGUMENT;
        }
      }

      MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(verify_result, verify_token, mcuxClRsa_verify(
        /* mcuxClSession_Handle_t           pSession: */           &session,
        /* const mcuxClRsa_Key * const      pKey: */               &public_key_other,
        /* mcuxCl_InputBuffer_t             pMessageOrDigest: */   input,
        /* const uint32_t                  messageLength: */      messageLength,
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded due to fixed function API. mcuxClRsa_verify does not modify those arguments.")
        /* mcuxCl_Buffer_t                  pSignature: */         (uint8_t *)signature,
        /* const mcuxClRsa_SignVerifyMode   pVerifyMode: */        (mcuxClRsa_SignVerifyMode)pVerifyMode,
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
        /* const uint32_t                  saltLength: */         saltLength,
        /* uint32_t                        options: */            options,
        /* mcuxCl_Buffer_t                  pOutput: */            NULL));
      if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_verify) != verify_token) || (MCUXCLRSA_STATUS_VERIFY_OK != verify_result))
      {
        return PSA_ERROR_INVALID_SIGNATURE;
      }
      MCUX_CSSL_FP_FUNCTION_CALL_END();
    }
    else
    {
      // Perform signature verificaton
      mcuxClEcc_Weier_DomainParams_t * domainParams = (mcuxClEcc_Weier_DomainParams_t *) mcuxClKey_getTypeInfo(pKey);
      if(domainParams == NULL)
      {
        return PSA_ERROR_GENERIC_ERROR;
      }
      const uint32_t pLen = domainParams->common.byteLenP;
      const uint32_t nLen = domainParams->common.byteLenN;
      uint8_t pOutputR[MCUXCLECC_WEIERECC_MAX_SIZE_BASEPOINTORDER];

      /* buffer for hash */
      uint8_t hash_buffer[64] = {0};
      const uint8_t * pHash = NULL;
      uint32_t hashSize = 0u;
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
                                                              &hashSize));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) != token) || (MCUXCLHASH_STATUS_OK != result))
        {
          return PSA_ERROR_CORRUPTION_DETECTED;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
        pHash = hash_buffer;
      }
      else
      {
        /* Needs to be truncated before calling ECC in case input_length value is too large to be represented
           using optLen bits in verify function  */
        hashSize = MCUXCLCORE_MIN(input_length, nLen);
        pHash = input;
      }

      /* Initialize buffers on the stack for domain parameters endianess swap (LE -> BE) */
      uint8_t a[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t b[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t p[MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t G[2u * MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t precP[2u * MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];
      uint8_t n[MCUXCLECC_WEIERECC_MAX_SIZE_BASEPOINTORDER];
      for(uint32_t i = 0u; i < pLen; i++)
      {
          a[i] = domainParams->common.pCurveParam1[pLen - i - 1u];
          b[i] = domainParams->common.pCurveParam2[pLen - i - 1u];
          p[i] = domainParams->common.pFullModulusP[pLen + MCUXCLPKC_WORDSIZE - i - 1u];
          G[i] = domainParams->common.pGx[pLen - i - 1u];
          G[pLen + i] = domainParams->common.pGy[pLen - i - 1u];
          precP[i] = domainParams->common.pPrecPoints[pLen - i - 1u];
          precP[pLen + i] = domainParams->common.pPrecPoints[(2u * pLen) - i - 1u];
      }
      for(uint32_t i = 0u; i < nLen; i++)
      {
          n[i] = domainParams->common.pFullModulusN[nLen + MCUXCLPKC_WORDSIZE - i - 1u];
      }

      uint8_t publicKey[2u * MCUXCLECC_WEIERECC_MAX_SIZE_PRIMEP];

      uint8_t * pKeyData = mcuxClKey_getLoadedKeyData(pKey);

      MCUXCLBUFFER_INIT_RO(buffA, NULL, a, pLen);
      MCUXCLBUFFER_INIT_RO(buffB, NULL, b, pLen);
      MCUXCLBUFFER_INIT_RO(buffP, NULL, p, pLen);
      MCUXCLBUFFER_INIT_RO(buffG, NULL, G, pLen * 2u);
      MCUXCLBUFFER_INIT_RO(buffN, NULL, n, nLen);

      /* Decode as described in ANSI X9.62
         Octet String to Elliptic Curve Point Conversion */
      if (PSA_KEY_TYPE_IS_PUBLIC_KEY(psa_get_key_type(attributes)) == true)
      {
        if(pKeyData == NULL)
        {
          return PSA_ERROR_GENERIC_ERROR;
        }

        /* Currently only uncompressed format is supported */
        if(MCUXCLPSADRIVER_PREFIX_ANSI_X9_62_UNCOMPRESSED_POINT != *pKeyData)
        {
          return(PSA_ERROR_NOT_SUPPORTED);
        }

        for(uint32_t i = 0u; i < 2u * pLen; ++i)
        {
          publicKey[i] = pKeyData[i + 1u];
        }
      }
      else
      {
        if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pKey))
        {
          size_t pubKeyLen = 0u;
          psa_status_t exportPublicKeyStatus = mcuxClPsaDriver_Oracle_ExportPublicKey(
            pKey,
            publicKey,
            sizeof(publicKey),
            &pubKeyLen,
            true);

          if((2u * pLen != pubKeyLen)
             || (PSA_SUCCESS != exportPublicKeyStatus))
          {
            return PSA_ERROR_GENERIC_ERROR;
          }
        }
        else
        {
          if(pKeyData == NULL)
          {
            return PSA_ERROR_GENERIC_ERROR;
          }

          MCUXCLBUFFER_INIT_RO(buffScalar, NULL, pKeyData,  nLen);
          MCUXCLBUFFER_INIT(buffResult,    NULL, publicKey, pLen * 2u);

          /* Calculate public point */
          mcuxClEcc_PointMult_Param_t params = {
              .curveParam = (mcuxClEcc_DomainParam_t){.pA   = buffA,
              .pB   = buffB,
              .pP   = buffP,
              .pG   = buffG,
              .pN   = buffN,
              .misc = mcuxClEcc_DomainParam_misc_Pack(nLen, pLen)},
              .pScalar    = buffScalar,
              .pPoint     = buffG,
              .pResult    = buffResult,
              .optLen     = 0u};

          /* Call PointMult for public keys calculation and check FP and return code */
          MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(pointMult_result, pointMult_token, mcuxClEcc_PointMult(&session, &params));
          if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointMult) != pointMult_token) ||
            (MCUXCLECC_STATUS_OK != pointMult_result))
          {
            return PSA_ERROR_GENERIC_ERROR;
          }
          MCUX_CSSL_FP_FUNCTION_CALL_END();
        }
      }

      MCUXCLBUFFER_INIT_RO(buffPrecP,     NULL, precP,     pLen * 2u);
      MCUXCLBUFFER_INIT_RO(buffHash,      NULL, pHash,     hashSize);
      MCUXCLBUFFER_INIT_RO(buffSignature, NULL, signature, signature_length);
      MCUXCLBUFFER_INIT(buffOutputR,      NULL, pOutputR,  nLen);

      mcuxClEcc_Verify_Param_t paramVerify =
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
        .pPrecG = buffPrecP,
        .pHash = buffHash,
        .pSignature = buffSignature,
        .pPublicKey = publicKey,
        .pOutputR = buffOutputR,
        .optLen = mcuxClEcc_Verify_Param_optLen_Pack(hashSize)
      };
      MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(verify_result, verify_token, mcuxClEcc_Verify(&session, &paramVerify));

      if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Verify) != verify_token) || (MCUXCLECC_STATUS_OK != verify_result))
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

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_verify(const psa_key_attributes_t *attributes,
                                                      const uint8_t *key_buffer,
                                                      size_t key_buffer_size,
                                                      psa_algorithm_t alg,
                                                      const uint8_t *input,
                                                      size_t input_length,
                                                      const uint8_t *signature,
                                                      size_t signature_length,
                                                      bool isHash
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
        /* Create the key */
    mcuxClKey_Descriptor_t key = {0};
    psa_status_t keyStatus = mcuxClPsaDriver_psa_driver_wrapper_createClKey(attributes, key_buffer, key_buffer_size, &key);
    if(PSA_SUCCESS == keyStatus)
    {
        status = mcuxClPsaDriver_psa_driver_wrapper_verify_internal( &key,
                                                                    alg,
                                                                    input,
                                                                    input_length,
                                                                    signature,
                                                                    signature_length,
                                                                    isHash);

        keyStatus = mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(&key);

        if(PSA_SUCCESS !=  keyStatus)
        {
            return keyStatus;
        }

        /* Retrun psa status as it is from here*/
        return status;
    }
    else if(keyStatus != PSA_ERROR_NOT_SUPPORTED)
    {
        return keyStatus;
    }
    else
    {
      return status;
    }
}
