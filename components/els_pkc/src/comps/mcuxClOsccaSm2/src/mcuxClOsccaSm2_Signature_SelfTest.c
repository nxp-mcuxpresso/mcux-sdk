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

/** @file  mcuxClOsccaSm2_Signature_SelfTest.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 sign/verify selftest function
 */
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClKey.h>
#include <mcuxClHash.h>
#include <mcuxClBuffer.h>
#include <mcuxClSignature.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaSm2_Internal_Functions.h>

static const uint8_t message[] =
{
    0x77U,0x69U,0x6fU,0xbaU,0xf3U,0x6bU,0x49U,0xcdU,0x1cU,0x0eU,0x45U,0x6aU,0xd1U,0x86U,0x59U,0xfeU
};

static const uint8_t pIdentifier[] = {0x01u,0x02u,0x03u,0x04u};

static const uint8_t pPublicKey[] =
{
    0xF2, 0x27, 0xA6, 0xE8, 0x30, 0x92, 0x0E, 0x1D, 0xF8, 0xA3, 0x41, 0x03, 0x33, 0xED, 0x32, 0xC7,
    0x55, 0x6F, 0x80, 0x7C, 0x71, 0xCD, 0x2E, 0x68, 0x51, 0xBD, 0xD1, 0x19, 0x7A, 0x43, 0x49, 0xEA,
    0x03, 0x04, 0x4E, 0x76, 0xB3, 0xD1, 0x0C, 0x61, 0xC2, 0x66, 0x94, 0xF4, 0xC9, 0xD0, 0x12, 0x1F,
    0xD7, 0x8A, 0xB1, 0x2A, 0x06, 0x28, 0x96, 0xD8, 0xBE, 0xB6, 0xD6, 0x7C, 0x59, 0x5C, 0x4C, 0xE3
};

static const uint8_t pPrivateKey[] =
{
    0x19, 0x42, 0x14, 0xC1, 0xD9, 0x6F, 0x8F, 0x47, 0x46, 0x89, 0xC2, 0xC4, 0x5F, 0x75, 0x5D, 0x8C,
    0x7F, 0xCE, 0x7B, 0x70, 0x99, 0xCC, 0x18, 0x6F, 0x4A, 0x61, 0x40, 0x64, 0xC7, 0x5F, 0x42, 0xAF
};

static const uint8_t signature[] =
{
    0x78, 0x8C, 0xB8, 0x25, 0x28, 0xAC, 0xD2, 0x07, 0xFB, 0x48, 0x60, 0xC3, 0x9F, 0x5F, 0x77, 0xA9,
    0xA8, 0x6E, 0x09, 0x1A, 0x66, 0x21, 0x4B, 0x4F, 0xE3, 0xD3, 0xA6, 0x83, 0x9A, 0x95, 0xC2, 0x28,
    0x4E, 0x92, 0xF2, 0x55, 0xDF, 0xC6, 0xCB, 0xD3, 0x36, 0x79, 0x07, 0x39, 0xCB, 0xD2, 0xA6, 0x8F,
    0xEF, 0xE7, 0xE5, 0x18, 0x77, 0x21, 0x81, 0xA5, 0x67, 0xCD, 0x4B, 0xB2, 0x59, 0xD0, 0xAF, 0xE9
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_PrepareDigest)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSignature_Status_t) mcuxClOsccaSm2_Signature_PrepareDigest(
   mcuxClSession_Handle_t session,
   mcuxClKey_Handle_t     key,
   uint8_t*              pDigest,
   uint32_t*             pDigestLen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_PrepareDigest);

    /*****************************************************/
    /* Initialization                                    */
    /*****************************************************/
    /* Create buffer for selftest */
    uint8_t * pPrehash = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t));
    if (NULL == pPrehash)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    /****************************************************************/
    /* Compute e = SM3_HASH(Za||M)                                  */
    /****************************************************************/
    uint32_t prehashSize = 0;
    MCUX_CSSL_FP_FUNCTION_CALL(prehashRet, mcuxClOsccaSm2_Signature_PreHash(
      /* mcuxClSession_Handle_t session:   */ session,
      /* mcuxClKey_Handle_t key:           */ key,
      /* mcuxCl_InputBuffer_t pIdentifier: */ pIdentifier,
      /* uint32_t identifierSize:         */ (uint16_t)sizeof(pIdentifier),
      /* mcuxCl_Buffer_t pPrehash:         */ pPrehash,
      /* uint32_t * const prehashSize:    */ &prehashSize));

    if (MCUXCLOSCCASM2_STATUS_OK != prehashRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    /****************************************************************/
    /* SM3 message digest calculation                               */
    /****************************************************************/
    uint8_t * hashCtx = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    if (NULL == hashCtx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pHashCtx = (mcuxClHash_Context_t) hashCtx;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    /* Create parameter structure for Hash component */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    MCUX_CSSL_FP_FUNCTION_CALL(hashInitRet, mcuxClHash_init(session, (mcuxClHash_Context_t)pHashCtx, mcuxClOsccaSm3_Algorithm_Sm3));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if (MCUXCLHASH_STATUS_OK != hashInitRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet, mcuxClHash_process(session,(mcuxClHash_Context_t)pHashCtx, pPrehash, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if (MCUXCLHASH_STATUS_OK != hashProRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet2, mcuxClHash_process(session,(mcuxClHash_Context_t)pHashCtx, message, sizeof(message)));
    if (MCUXCLHASH_STATUS_OK != hashProRet2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(hashFinalRet, mcuxClHash_finish(session, (mcuxClHash_Context_t)pHashCtx, pDigest, pDigestLen));
    if (MCUXCLHASH_STATUS_OK != hashFinalRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    /* free session area */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t) + MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_PrepareDigest, MCUXCLSIGNATURE_STATUS_OK, MCUXCLSIGNATURE_STATUS_FAILURE,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PreHash),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, mcuxClSignature_SelfTestFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSignature_Status_t) mcuxClOsccaSm2_Signature_SignVerify_SelfTest(
    mcuxClSession_Handle_t session,
    mcuxClSignature_Mode_t mode
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_SignVerify_SelfTest);

    /*****************************************************/
    /* Initialization                                    */
    /*****************************************************/
    /* Create buffer for selftest */
    uint8_t * pSigVerifyBuf = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE
                                                                                   + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
    if (NULL == pSigVerifyBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    uint8_t *pPrivKeyDesc = pSigVerifyBuf;
    uint8_t *pPubKeyDesc = pPrivKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);
    uint8_t *pNewSignature = pPubKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);
    uint8_t *pDigest = pNewSignature + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE;
    /****************************************************************/
    /* Preparation: setup SM2 key                                   */
    /****************************************************************/
    /* Initialize SM2 private key */
    mcuxClKey_Handle_t privKey = (mcuxClKey_Handle_t) pPrivKeyDesc;

    MCUX_CSSL_FP_FUNCTION_CALL(priKeyInitRet, mcuxClKey_init(session,
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           privKey,
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Std_Private,
                                                           pPrivateKey,
                                                           sizeof(pPrivateKey)));
    if (MCUXCLKEY_STATUS_OK != priKeyInitRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, MCUXCLSIGNATURE_STATUS_FAILURE,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init));
    }

    /* Initialize SM2 public key */
    mcuxClKey_Handle_t pubKey = (mcuxClKey_Handle_t) pPubKeyDesc;

    MCUX_CSSL_FP_FUNCTION_CALL(pubKeyInitRet, mcuxClKey_init(session,
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           pubKey,
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Std_Public,
                                                           pPublicKey,
                                                           sizeof(pPublicKey)));
    if (MCUXCLKEY_STATUS_OK != pubKeyInitRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, MCUXCLSIGNATURE_STATUS_FAILURE,
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init));
    }

    /****************************************************************/
    /* Compute e = SM3_HASH(Za||M)                                  */
    /****************************************************************/
    uint32_t digestSize = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL(digestPreRet, mcuxClOsccaSm2_Signature_PrepareDigest(session, pubKey, pDigest, &digestSize));
    if (MCUXCLSIGNATURE_STATUS_OK != digestPreRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, digestPreRet,
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PrepareDigest));
    }

    /****************************************************************/
    /* OSCCA SM2 signature verification                             */
    /****************************************************************/
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("digestSize is set by signature PrepareDigest API");
    MCUX_CSSL_FP_FUNCTION_CALL(verifyRet, mcuxClSignature_verify(session,
                                                          pubKey,
                                                          mode,
                                                          pDigest,
                                                          digestSize,
                                                          signature,
                                                          sizeof(signature)));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION();

    if (MCUXCLSIGNATURE_STATUS_OK != verifyRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, verifyRet,
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PrepareDigest),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSignature_verify));
    }

    /****************************************************************/
    /* OSCCA SM2 new signature generation                           */
    /****************************************************************/
    uint32_t signatureSize = 0U;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("digestSize is set by signature PrepareDigest API");
    MCUX_CSSL_FP_FUNCTION_CALL(signRet, mcuxClSignature_sign(session,
                                                      privKey,
                                                      mode,
                                                      pDigest,
                                                      digestSize,
                                                      pNewSignature,
                                                      &signatureSize));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION();
    if (MCUXCLSIGNATURE_STATUS_OK != signRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, signRet,
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PrepareDigest),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSignature_verify),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSignature_sign));
    }

    /****************************************************************/
    /* OSCCA SM2 new signature verification                         */
    /****************************************************************/
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("digestSize is set by signature PrepareDigest API");
    MCUX_CSSL_FP_FUNCTION_CALL(verifyNewRet, mcuxClSignature_verify(session,
                                                             pubKey,
                                                             mode,
                                                             pDigest,
                                                             digestSize,
                                                             pNewSignature,
                                                             signatureSize));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION();

    /* free session area */
    mcuxClSession_freeWords_cpuWa(session, (2u * mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM2_SM2P256_SIZE_SIGNATURE
	                                     + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_SignVerify_SelfTest, verifyNewRet, MCUXCLSIGNATURE_STATUS_FAILURE,
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PrepareDigest),
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSignature_verify),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSignature_sign));

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest, mcuxClSignature_SelfTestFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSignature_Status_t) mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest(
    mcuxClSession_Handle_t session,
    mcuxClSignature_Mode_t mode
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest);

    /*****************************************************/
    /* Initialization                                    */
    /*****************************************************/
    /* Create buffer for selftest */
    uint8_t * pSigVerifyBuf = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, (mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE)
	                                                                               + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
    if (NULL == pSigVerifyBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest, MCUXCLSIGNATURE_STATUS_FAILURE);
    }

    uint8_t *pPubKeyDesc = pSigVerifyBuf;
    uint8_t *pDigest = pPubKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);

    /****************************************************************/
    /* Preparation: setup SM2 key                                   */
    /****************************************************************/
    /* Initialize SM2 public key */
    mcuxClKey_Handle_t pubKey = (mcuxClKey_Handle_t) pPubKeyDesc;

    MCUX_CSSL_FP_FUNCTION_CALL(pubKeyInitRet, mcuxClKey_init(session,
         MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           pubKey,
         MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Std_Public,
                                                           pPublicKey,
                                                           sizeof(pPublicKey)));
    if (MCUXCLKEY_STATUS_OK != pubKeyInitRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest, MCUXCLSIGNATURE_STATUS_FAILURE,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init));
    }

    /****************************************************************/
    /* Compute e = SM3_HASH(Za||M)                                  */
    /****************************************************************/
    uint32_t digestSize = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL(digestPreRet, mcuxClOsccaSm2_Signature_PrepareDigest(session, pubKey, pDigest, &digestSize));
    if (MCUXCLSIGNATURE_STATUS_OK != digestPreRet)
    {
        mcuxClSession_freeWords_cpuWa(session, (mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest, digestPreRet,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PrepareDigest));
    }

    /****************************************************************/
    /* OSCCA SM2 signature verification                             */
    /****************************************************************/
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("digestSize is set by signature PrepareDigest API");
    MCUX_CSSL_FP_FUNCTION_CALL(verifyRet, mcuxClSignature_verify(session,
                                                          pubKey,
                                                          mode,
                                                          pDigest,
                                                          digestSize,
                                                          signature,
                                                          sizeof(signature)));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION();

    /* free session area */
    mcuxClSession_freeWords_cpuWa(session, (mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE) + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3) / sizeof(uint32_t));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_OnlyVerify_SelfTest, verifyRet, MCUXCLSIGNATURE_STATUS_FAULT_ATTACK,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_PrepareDigest),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSignature_verify));

}
