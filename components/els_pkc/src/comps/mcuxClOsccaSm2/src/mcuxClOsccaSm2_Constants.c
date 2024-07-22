/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/**
 * @file  mcuxClOsccaSm2_Constants.c
 * @brief Provides constants definitions for domain parameters
 */

#include <mcuxCsslAnalysis.h>
#include <mcuxClOsccaSm2.h>
#include <internal/mcuxClOsccaSm2_Internal_Types.h>
#include <internal/mcuxClOsccaSm2_Internal_Functions.h>
#ifdef MCUXCL_FEATURE_SM2_INTERNAL
#include <internal/mcuxClOsccaSm2_Internal_ConstructTypes.h>
#ifdef MCUXCL_FEATURE_SM2_SIGNATURE
#include <mcuxClSignature.h>
#include <internal/mcuxClSignature_Internal.h>
#endif /* MCUXCL_FEATURE_SM2_SIGNATURE */
#ifdef MCUXCL_FEATURE_SM2_CIPHER
#include <mcuxClCipher.h>
#include <internal/mcuxClCipher_Internal.h>
#endif /* MCUXCL_FEATURE_SM2_CIPHER */
#ifdef MCUXCL_FEATURE_SM2_KEYAGREEMENT
#include <internal/mcuxClKey_Types_Internal.h>
#endif /* MCUXCL_FEATURE_SM2_KEYAGREEMENT */
#endif /* MCUXCL_FEATURE_SM2_INTERNAL */

/**********************************************************/
/* SM2 domain parameters                                  */
/**********************************************************/
/* Standard Curve SM2 256bits domain parameters */

static const uint8_t pCurveSm2_256_FullP[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP] __attribute__ ((aligned (4))) =
{
    /* p = 0xFFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF 00000000 FFFFFFFF FFFFFFFF [BE] */
    0xFFu, 0xFFu, 0xFFu, 0xFEu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu
};

static const uint8_t pCurveSm2_256_FullN[MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER] __attribute__ ((aligned (4))) =
{
    /* n = 0xFFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF 7203DF6B 21C6052B 53BBF409 39D54123 [BE] */
    0xFFu, 0xFFu, 0xFFu, 0xFEu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0x72u, 0x03u, 0xDFu, 0x6Bu, 0x21u, 0xC6u, 0x05u, 0x2Bu,
    0x53u, 0xBBu, 0xF4u, 0x09u, 0x39u, 0xD5u, 0x41u, 0x23u
};

static const uint8_t pCurveSm2_256_PointG[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP * 2U] __attribute__ ((aligned (4))) =
{
    /* PointGX = 0x32C4AE2C 1F198119 5F990446 6A39C994 8FE30BBF F2660BE1 715A4589 334C74C7 [BE] */
    0x32u, 0xC4u, 0xAEu, 0x2Cu,  0x1Fu, 0x19u, 0x81u, 0x19u,
    0x5Fu, 0x99u, 0x04u, 0x46u,  0x6Au, 0x39u, 0xC9u, 0x94u,
    0x8Fu, 0xE3u, 0x0Bu, 0xBFu,  0xF2u, 0x66u, 0x0Bu, 0xE1u,
    0x71u, 0x5Au, 0x45u, 0x89u,  0x33u, 0x4Cu, 0x74u, 0xC7u,
    /* PointGY = 0xBC3736A2 F4F6779C 59BDCEE3 6B692153 D0A9877C C62A4740 02DF32E5 2139F0A0 [BE] */
    0xBCu, 0x37u, 0x36u, 0xA2u,  0xF4u, 0xF6u, 0x77u, 0x9Cu,
    0x59u, 0xBDu, 0xCEu, 0xE3u,  0x6Bu, 0x69u, 0x21u, 0x53u,
    0xD0u, 0xA9u, 0x87u, 0x7Cu,  0xC6u, 0x2Au, 0x47u, 0x40u,
    0x02u, 0xDFu, 0x32u, 0xE5u,  0x21u, 0x39u, 0xF0u, 0xA0u
};

static const uint8_t pCurveSm2_256_A[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP] __attribute__ ((aligned (4))) =
{
    /* A = 0xFFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF 00000000 FFFFFFFF FFFFFFFC [BE] */
    0xFFu, 0xFFu, 0xFFu, 0xFEu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u,
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFCu
};

static const uint8_t pCurveSm2_256_B[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP] __attribute__ ((aligned (4))) =
{
    /* B = 0x28E9FA9E 9D9F5E34 4D5A9E4B CF6509A7 F39789F5 15AB8F92 DDBCBD41 4D940E93 [BE] */
    0x28u, 0xE9u, 0xFAu, 0x9Eu, 0x9Du, 0x9Fu, 0x5Eu, 0x34u,
    0x4Du, 0x5Au, 0x9Eu, 0x4Bu, 0xCFu, 0x65u, 0x09u, 0xA7u,
    0xF3u, 0x97u, 0x89u, 0xF5u, 0x15u, 0xABu, 0x8Fu, 0x92u,
    0xDDu, 0xBCu, 0xBDu, 0x41u, 0x4Du, 0x94u, 0x0Eu, 0x93u
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClOsccaSm2_DomainParam_t mcuxClOsccaSm2_DomainParams_SM2P256_Std =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .pA = (uint8_t*)&pCurveSm2_256_A,
    .pB = (uint8_t*)&pCurveSm2_256_B,
    .p.pMPInt = (uint8_t*)&pCurveSm2_256_FullP,
    .p.wNumBytes= MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP,
    .pG = (uint8_t*)&pCurveSm2_256_PointG,
    .n.pMPInt = (uint8_t*)&pCurveSm2_256_FullN,
    .n.wNumBytes = MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER,
};


/* Extend Curve SM2 256bits domain parameters */

static const uint8_t pCurveSm2_256_Ext_FullP[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP] __attribute__ ((aligned (4))) =
{
    /* p = 0x8542D69E 4C044F18 E8B92435 BF6FF7DE 45728391 5C45517D 722EDB8B 08F1DFC3 [BE] */
    0x85u, 0x42u, 0xD6u, 0x9Eu, 0x4Cu, 0x04u, 0x4Fu, 0x18u,
    0xE8u, 0xB9u, 0x24u, 0x35u, 0xBFu, 0x6Fu, 0xF7u, 0xDEu,
    0x45u, 0x72u, 0x83u, 0x91u, 0x5Cu, 0x45u, 0x51u, 0x7Du,
    0x72u, 0x2Eu, 0xDBu, 0x8Bu, 0x08u, 0xF1u, 0xDFu, 0xC3u
};

static const uint8_t pCurveSm2_256_Ext_FullN[MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER] __attribute__ ((aligned (4))) =
{
    /* n = 0x8542D69E 4C044F18 E8B92435 BF6FF7DD 29772063 0485628D 5AE74EE7 C32E79B7 [BE] */
    0x85u, 0x42u, 0xD6u, 0x9Eu, 0x4Cu, 0x04u, 0x4Fu, 0x18u,
    0xE8u, 0xB9u, 0x24u, 0x35u, 0xBFu, 0x6Fu, 0xF7u, 0xDDu,
    0x29u, 0x77u, 0x20u, 0x63u, 0x04u, 0x85u, 0x62u, 0x8Du,
    0x5Au, 0xE7u, 0x4Eu, 0xE7u, 0xC3u, 0x2Eu, 0x79u, 0xB7u
};

static const uint8_t pCurveSm2_256_Ext_PointG[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP * 2U] __attribute__ ((aligned (4))) =
{
    /* PointGX = 0x421DEBD6 1B62EAB6 746434EB C3CC315E 32220B3B ADD50BDC 4C4E6C14 7FEDD43D [BE] */
    0x42u, 0x1Du, 0xEBu, 0xD6u, 0x1Bu, 0x62u, 0xEAu, 0xB6u,
    0x74u, 0x64u, 0x34u, 0xEBu, 0xC3u, 0xCCu, 0x31u, 0x5Eu,
    0x32u, 0x22u, 0x0Bu, 0x3Bu, 0xADu, 0xD5u, 0x0Bu, 0xDCu,
    0x4Cu, 0x4Eu, 0x6Cu, 0x14u, 0x7Fu, 0xEDu, 0xD4u, 0x3Du,
    /* PointGY = 0x0680512B CBB42C07 D47349D2 153B70C4 E5D7FDFC BFA36EA1 A85841B9 E46E09A2 [BE] */
    0x06u, 0x80u, 0x51u, 0x2Bu, 0xCBu, 0xB4u, 0x2Cu, 0x07u,
    0xD4u, 0x73u, 0x49u, 0xD2u, 0x15u, 0x3Bu, 0x70u, 0xC4u,
    0xE5u, 0xD7u, 0xFDu, 0xFCu, 0xBFu, 0xA3u, 0x6Eu, 0xA1u,
    0xA8u, 0x58u, 0x41u, 0xB9u, 0xE4u, 0x6Eu, 0x09u, 0xA2u
};

static const uint8_t pCurveSm2_256_Ext_A[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP] __attribute__ ((aligned (4))) =
{
    /* A = 0x787968B4 FA32C3FD 2417842E 73BBFEFF 2F3C848B 6831D7E0 EC65228B 3937E498 [BE] */
    0x78u, 0x79u, 0x68u, 0xB4u, 0xFAu, 0x32u, 0xC3u, 0xFDu,
    0x24u, 0x17u, 0x84u, 0x2Eu, 0x73u, 0xBBu, 0xFEu, 0xFFu,
    0x2Fu, 0x3Cu, 0x84u, 0x8Bu, 0x68u, 0x31u, 0xD7u, 0xE0u,
    0xECu, 0x65u, 0x22u, 0x8Bu, 0x39u, 0x37u, 0xE4u, 0x98u
};

static const uint8_t pCurveSm2_256_Ext_B[MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP] __attribute__ ((aligned (4))) =
{
    /* B = 0x63E4C6D3 B23B0C84 9CF84241 484BFE48 F61D59A5 B16BA06E 6E12D1DA 27C5249A [BE] */
    0x63u, 0xE4u, 0xC6u, 0xD3u, 0xB2u, 0x3Bu, 0x0Cu, 0x84u,
    0x9Cu, 0xF8u, 0x42u, 0x41u, 0x48u, 0x4Bu, 0xFEu, 0x48u,
    0xF6u, 0x1Du, 0x59u, 0xA5u, 0xB1u, 0x6Bu, 0xA0u, 0x6Eu,
    0x6Eu, 0x12u, 0xD1u, 0xDAu, 0x27u, 0xC5u, 0x24u, 0x9Au
};


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClOsccaSm2_DomainParam_t mcuxClOsccaSm2_DomainParams_SM2P256_Ext =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .pA = (uint8_t*)&pCurveSm2_256_Ext_A,
    .pB = (uint8_t*)&pCurveSm2_256_Ext_B,
    .p.pMPInt = (uint8_t*)&pCurveSm2_256_Ext_FullP,
    .p.wNumBytes= MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP,
    .pG = (uint8_t*)&pCurveSm2_256_Ext_PointG,
    .n.pMPInt = (uint8_t*)&pCurveSm2_256_Ext_FullN,
    .n.wNumBytes = MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER,
};

#ifdef MCUXCL_FEATURE_SM2_SIGNATURE
/* no y coordinate shall be exported */
const mcuxClOsccaSm2_SignatureProtocolDescriptor_t mcuxClOsccaSm2_Sm2ProtocolDescriptor =
{
    .options  = 0u
};


#ifdef MCUXCL_FEATURE_SIGNATURE_SELFTEST
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClSignature_TestDescriptor_t mcuxClSignature_TestDescriptor_SM2_VerifyOnly =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .pSelfTestFct = mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest,
    .protection_token_selftest = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest)
};

const mcuxClSignature_TestDescriptor_t mcuxClSignature_TestDescriptor_SM2_SignVerify =
{
    .pSelfTestFct = mcuxClOsccaSm2_Signature_SignVerify_SelfTest,
    .protection_token_selftest = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_SignVerify_SelfTest)
};
#endif /* MCUXCL_FEATURE_SIGNATURE_SELFTEST */

const mcuxClSignature_ModeDescriptor_t mcuxClSignature_ModeDescriptor_SM2 =
{
#ifdef MCUXCL_FEATURE_SIGNATURE_ONESHOT
    .pSignFct = mcuxClOsccaSm2_Sign,
    .protection_token_sign = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Sign),
    .pVerifyFct   = mcuxClOsccaSm2_Verify,
    .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify),
#endif /* MCUXCL_FEATURE_SIGNATURE_ONESHOT */
    .pProtocolDescriptor = (const void *)&mcuxClOsccaSm2_Sm2ProtocolDescriptor
};

#endif /* MCUXCL_FEATURE_SM2_SIGNATURE */

#ifdef MCUXCL_FEATURE_SM2_CIPHER

static const mcuxClCipher_ModeFunctions_t mcuxClOscca_CipherModeFunctions_OsccaSM2 = {
  .crypt = mcuxClOsccaSm2_Cipher_SkeletonSM2,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Cipher_SkeletonSM2),
};


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t mcuxClOsccaSm2_CipherAlgorithmDesc_Sm2Enc =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
  /* Fill cipher algorithm parameters for SM2 with SM2 encryption and decryption */
  .pEncryptMode = mcuxClOsccaSm2_Encrypt,
  .pDecryptMode = mcuxClOsccaSm2_Decrypt,
  .encrypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt),
  .decrypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
  .direction = MCUXCLOSCCASM2_ENCRYPT
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM2_ENC =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
  .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaSM2,
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
  .pAlgorithm = (void*)&mcuxClOsccaSm2_CipherAlgorithmDesc_Sm2Enc
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t mcuxClOsccaSm2_CipherAlgorithmDesc_Sm2Dec =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
  /* Fill cipher algorithm parameters for SM2 with SM2 encryption and decryption */
  .pEncryptMode = mcuxClOsccaSm2_Encrypt,
  .pDecryptMode = mcuxClOsccaSm2_Decrypt,
  .encrypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt),
  .decrypt_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
  .direction = MCUXCLOSCCASM2_DECRYPT
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClCipher_ModeDescriptor_t mcuxClOscca_Cipher_ModeDesc_SM2_DEC =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
  .pModeFunctions = (const void *) &mcuxClOscca_CipherModeFunctions_OsccaSM2,
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the algorithm.")
  .pAlgorithm = (void*)&mcuxClOsccaSm2_CipherAlgorithmDesc_Sm2Dec
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
};
#endif /* MCUXCL_FEATURE_SM2_CIPHER */

#ifdef MCUXCL_FEATURE_SM2_KEYAGREEMENT
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClOsccaSm2_AgreementProtocolDescriptor_t mcuxClOsccaSm2_AgreementDescriptor_Initiator =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .options  = MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_INITIATOR | MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClOsccaSm2_AgreementProtocolDescriptor_t mcuxClOsccaSm2_AgreementDescriptor_Responder =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .options  = MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_RESPONDER | MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClKey_AgreementDescriptor_t mcuxClOsccaSm2_AgreementDesc_Initiator =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
  .pAgreementFct = mcuxClOsccaSm2_key_agreement,
  .protectionTokenAgreementFct = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_key_agreement),
  .pProtocolDescriptor = (const void*)&mcuxClOsccaSm2_AgreementDescriptor_Initiator
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClKey_AgreementDescriptor_t mcuxClOsccaSm2_AgreementDesc_Responder =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
  .pAgreementFct = mcuxClOsccaSm2_key_agreement,
  .protectionTokenAgreementFct = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_key_agreement),
  .pProtocolDescriptor = (const void*)&mcuxClOsccaSm2_AgreementDescriptor_Responder
};

const mcuxClKey_TestDescriptor_t mcuxClKey_TestDescriptor_SM2_Agreement =
{
    .pSelfTestFct = mcuxClOsccaSm2_KeyAgreement_SelfTest,
    .protectionTokenSelfTestFct = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyAgreement_SelfTest)
};
#endif /* MCUXCL_FEATURE_SM2_KEYAGREEMENT */
