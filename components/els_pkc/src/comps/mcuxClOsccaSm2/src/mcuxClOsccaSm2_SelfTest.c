/*--------------------------------------------------------------------------*/
/* Copyright 2021-2024 NXP                                                  */
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

#include <mcuxClSession.h>
#include <mcuxClHash.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm2_SelfTest.h>
#include <mcuxClOscca_Types.h>
#include <mcuxClKey.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClOsccaSm3_Internal.h>

static const uint8_t pubKey[] = {
    0xF2, 0x27, 0xA6, 0xE8, 0x30, 0x92, 0x0E, 0x1D, 0xF8, 0xA3, 0x41, 0x03, 0x33, 0xED, 0x32, 0xC7,
    0x55, 0x6F, 0x80, 0x7C, 0x71, 0xCD, 0x2E, 0x68, 0x51, 0xBD, 0xD1, 0x19, 0x7A, 0x43, 0x49, 0xEA,
    0x03, 0x04, 0x4E, 0x76, 0xB3, 0xD1, 0x0C, 0x61, 0xC2, 0x66, 0x94, 0xF4, 0xC9, 0xD0, 0x12, 0x1F,
    0xD7, 0x8A, 0xB1, 0x2A, 0x06, 0x28, 0x96, 0xD8, 0xBE, 0xB6, 0xD6, 0x7C, 0x59, 0x5C, 0x4C, 0xE3};

static const uint8_t privKey[] = {
    0x19, 0x42, 0x14, 0xC1, 0xD9, 0x6F, 0x8F, 0x47, 0x46, 0x89, 0xC2, 0xC4, 0x5F, 0x75, 0x5D, 0x8C,
    0x7F, 0xCE, 0x7B, 0x70, 0x99, 0xCC, 0x18, 0x6F, 0x4A, 0x61, 0x40, 0x64, 0xC7, 0x5F, 0x42, 0xAF};

static const uint8_t message[] = {
    0x77U, 0x69U, 0x6fU, 0xbaU,  0xf3U, 0x6bU, 0x49U, 0xcdU,
    0x1cU, 0x0eU, 0x45U, 0x6aU,  0xd1U, 0x86U, 0x59U, 0xfeU,
    0xdeU, 0x3fU, 0xcbU, 0x0cU,  0xceU, 0x69U, 0xa1U, 0xccU,
    0x01U, 0xb4U, 0x5aU, 0x19U,  0xfeU, 0x58U, 0xdbU, 0x8aU,
    0x09U, 0x59U, 0xacU, 0xdeU,  0xf9U, 0x09U, 0x64U, 0x9dU,
    0x44U, 0xceU, 0x62U, 0xfcU,  0x5cU, 0x25U, 0xbeU, 0x01U,
    0x3eU, 0xe7U, 0x7fU, 0xe9U,  0x47U, 0xccU, 0x0fU, 0xc7U,
    0x4aU, 0x2dU, 0xecU, 0x6dU,  0xe1U, 0x0eU, 0x9fU, 0x8fU,
    0x00U, 0x5bU, 0xf2U, 0x26U,  0xd0U, 0x72U, 0x5eU, 0x13U,
    0xbaU, 0xe2U, 0xc3U, 0x05U,  0xc1U, 0x72U, 0x5cU, 0x9cU,
    0x16U, 0x66U, 0xf1U, 0xcfU,  0xe6U, 0xfdU, 0x4eU, 0x8bU,
    0x77U, 0x3eU, 0xf5U, 0x9cU,  0x73U, 0xf4U, 0x10U, 0xd1U,
    0x84U, 0xf8U, 0xa9U, 0x5bU,  0x20U, 0xaeU, 0x1dU, 0x77U,
    0xa7U, 0xd2U, 0xceU, 0x4dU,  0xabU, 0x75U, 0x19U, 0x17U,
    0x8eU, 0x42U, 0x88U, 0x85U,  0x53U, 0x06U, 0x48U, 0x60U,
    0xaeU, 0x70U, 0xddU, 0x6fU,  0x5dU, 0x15U, 0x14U, 0x97U};

static const uint8_t cipher[] = {
    0x07, 0x11, 0x28, 0x09, 0x50, 0x4A, 0xDD, 0xE6, 0x75, 0x7D, 0xE8, 0x7F, 0x68, 0x29, 0xB7, 0x90,
    0xC4, 0xDA, 0xE1, 0xB9, 0x4C, 0x5C, 0x0C, 0x78, 0x21, 0x3C, 0x8D, 0x43, 0x3A, 0xBE, 0xC8, 0x26,
    0x1D, 0x3E, 0xB2, 0x6D, 0x05, 0xBE, 0x93, 0x1B, 0xFD, 0xD8, 0xD2, 0x23, 0x6F, 0x8C, 0x3C, 0xC7,
    0x0A, 0xDA, 0x45, 0xD5, 0xE7, 0x6B, 0x77, 0xEA, 0x7C, 0xE3, 0x25, 0xE6, 0x9B, 0xAA, 0x11, 0x73,
    0x9B, 0xE1, 0x9A, 0x61, 0x42, 0x02, 0x97, 0x52, 0xFD, 0xA8, 0x31, 0x48, 0x16, 0xEE, 0xF8, 0x55,
    0xA6, 0x20, 0x00, 0xAE, 0x15, 0x4B, 0x9F, 0xFE, 0x7F, 0x90, 0xBF, 0xCB, 0x79, 0x08, 0x12, 0x03,
    0xDF, 0x05, 0xBF, 0x3E, 0x34, 0xE1, 0x70, 0xFB, 0x2D, 0xAB, 0x84, 0xA1, 0x86, 0x2A, 0xB1, 0xE7,
    0xEA, 0x0C, 0x17, 0x8D, 0x91, 0x3E, 0xB3, 0xD0, 0xAC, 0x80, 0x43, 0xBB, 0x4D, 0x4A, 0x7E, 0xE6};

static const uint8_t c1[] = {
    0x04, 0x5F, 0x79, 0x55, 0x94, 0x78, 0x05, 0x54, 0xF0, 0x42, 0x7D, 0x08, 0xB8, 0x55, 0xBF, 0x6C,
    0xC1, 0x16, 0x98, 0x82, 0x12, 0xF7, 0x58, 0x6A, 0x51, 0xC4, 0x6B, 0x7A, 0x33, 0x44, 0xD8, 0xB0,
    0x54, 0x4F, 0xB5, 0xB9, 0xEA, 0xBB, 0x1C, 0xAC, 0x78, 0xBF, 0x6A, 0xC5, 0x28, 0x74, 0x6B, 0xD8,
    0x75, 0x31, 0xE0, 0x0E, 0xF1, 0xEA, 0x85, 0xC4, 0x90, 0xED, 0x53, 0x22, 0x0C, 0x3F, 0xAB, 0xFF, 0xE5};

static const uint8_t c3[] = {
    0xDA, 0x6E, 0x6D, 0x4C, 0xF6, 0x23, 0xEA, 0xCB, 0xA9, 0x86, 0xC8, 0x5D, 0xD8, 0x29, 0xAF,0x67,
    0xA7, 0xFD, 0xA2, 0x8B, 0x6E, 0x10, 0xD6, 0xDA, 0x2B, 0xC6, 0x41, 0x33, 0x34, 0xB1, 0xCE,0x25};

static const uint8_t signature[] = {
    0xBD, 0x98, 0xE1, 0xEF, 0xEB, 0x8C, 0xA4, 0x18, 0xAD, 0x17, 0x13, 0x76, 0x19, 0xD8, 0x01, 0xEA,
    0xFF, 0x46, 0x2E, 0x61, 0x7A, 0xAB, 0xEB, 0x9E, 0x6B, 0x49, 0x75, 0x65, 0x6D, 0xE2, 0xDF, 0xC0,
    0x1A, 0x21, 0xA5, 0x6D, 0xCA, 0x87, 0x40, 0xB4, 0x70, 0x18, 0xAA, 0x7F, 0x52, 0x3A, 0xB4, 0xD4,
    0x6F, 0xB0, 0xCF, 0x8E, 0x71, 0xE3, 0x9D, 0x63, 0xF7, 0x35, 0x59, 0xE7, 0xB6, 0x69, 0xBC, 0xF9,
};


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EncDec_SelfTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_SelfTest_Status_t) mcuxClOsccaSm2_EncDec_SelfTest(mcuxClSession_Handle_t session)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EncDec_SelfTest);

    /* Create buffer for ciphertext */
    uint32_t cpuWaUsedWord = (2U * mcuxClOscca_alignSize(sizeof(message)) + (2u * MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP + 4u) +
                                MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 + MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP)) / sizeof(uint32_t);
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    uint8_t * pEncDecBuf = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session,cpuWaUsedWord);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if (NULL == pEncDecBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
    }

    uint8_t *pC1 = pEncDecBuf;
    uint8_t *pC3 = pC1 +  (MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP * 2u + 4u);
    uint8_t *pPlain = pC3 + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint8_t *pCipher = pPlain + mcuxClOscca_alignSize(sizeof(message));
    mcuxClOsccaSm2_EncDecCtx_t *pEncDecCtx = (mcuxClOsccaSm2_EncDecCtx_t *)(pCipher + mcuxClOscca_alignSize(sizeof(message)));

    /*--------------------------------------------------------------*/
    /* Decrypt ciphertext and compare                               */
    /*--------------------------------------------------------------*/

    /* Create a structure for mcuxClOsccaSm2_Decrypt function */
    mcuxClOsccaSm2_Decrypt_Param_t paramsDec;
    paramsDec.pEncDecCtx = (mcuxClOsccaSm2_EncDecCtx_t*)pEncDecCtx;
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsDec.domainParameters, mcuxClOsccaSm2_DomainParams_SM2P256_Std);
    paramsDec.pPrivateKey = privKey;
    paramsDec.pC1 = c1;
    paramsDec.pInput = cipher;
    paramsDec.pC3 = c3;

    paramsDec.pOutput = pPlain;
    paramsDec.inputLength = (uint16_t)sizeof(message);

    paramsDec.options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT;

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    MCUX_CSSL_FP_FUNCTION_CALL(regSM2De, mcuxClOsccaSm2_Decrypt(session, &paramsDec));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if (MCUXCLOSCCASM2_STATUS_DECRYPT_OK != regSM2De)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == regSM2De)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_SelfTest,MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            /* Free workarea allocated in mcuxClOsccaSm2_EncDec_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt));
        }
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet1, mcuxClOsccaSm2_RobustCompareBoolean(paramsDec.pOutput, message, paramsDec.inputLength));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet1)
    {
        MCUX_CSSL_SC_SUB((uint32_t)pPlain + (uint32_t)message + sizeof(message) + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaSm2_EncDec_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    /****************************************************************/
    /* Encrypt message and generate new C1, C2, C3                  */
    /****************************************************************/

    /* Create a structure for mcuxClOsccaSm2_Encrypt function */
    mcuxClOsccaSm2_Encrypt_Param_t paramsEnc;
    paramsEnc.pEncDecCtx = (mcuxClOsccaSm2_EncDecCtx_t*)pEncDecCtx;
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsEnc.domainParameters, mcuxClOsccaSm2_DomainParams_SM2P256_Std);
    paramsEnc.pPublicKey = pubKey;
    paramsEnc.pInput = message;
    paramsEnc.pC1 = pC1;
    paramsEnc.pOutput = pCipher;
    paramsEnc.pC3 = pC3;
    paramsEnc.inputLength = (uint16_t)sizeof(message);
    paramsEnc.options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT;

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    MCUX_CSSL_FP_FUNCTION_CALL(regSM2En, mcuxClOsccaSm2_Encrypt(session, &paramsEnc));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(MCUXCLOSCCASM2_STATUS_ENCRYPT_OK != regSM2En)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == regSM2En)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            MCUX_CSSL_SC_SUB((uint32_t)pPlain + (uint32_t)message + sizeof(message) + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL);
            /* Free workarea allocated in mcuxClOsccaSm2_EncDec_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
        }
    }

    /****************************************************************/
    /*  Decrypt ciphertext and compare again                        */
    /****************************************************************/
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsDec.domainParameters, mcuxClOsccaSm2_DomainParams_SM2P256_Std);
    paramsDec.pPrivateKey = privKey;
    paramsDec.pC1 = pC1;
    paramsDec.pInput = pCipher;
    paramsDec.pC3 = pC3;

    paramsDec.pOutput = pPlain;
    paramsDec.inputLength = (uint16_t)sizeof(message);

    paramsDec.options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT;

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    MCUX_CSSL_FP_FUNCTION_CALL(regSM2De2, mcuxClOsccaSm2_Decrypt(session, &paramsDec));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if (MCUXCLOSCCASM2_STATUS_DECRYPT_OK != regSM2De2)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == regSM2De2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EncDec_SelfTest,MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            MCUX_CSSL_SC_SUB((uint32_t)pPlain + (uint32_t)message + sizeof(message) + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL);
            /* Free workarea allocated in mcuxClOsccaSm2_EncDec_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
        }
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet2, mcuxClOsccaSm2_RobustCompareBoolean(paramsDec.pOutput, message, paramsDec.inputLength));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet2)
    {
        MCUX_CSSL_SC_SUB(2u * ((uint32_t)pPlain + (uint32_t)message + sizeof(message)) + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaSm2_EncDec_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_SC_SUB(2u * ((uint32_t)pPlain + (uint32_t)message + sizeof(message) + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL));
    /* Free workarea allocated in mcuxClOsccaSm2_EncDec_SelfTest */
    mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_EncDec_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_OK, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt),
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_SignVerify_SelfTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_SelfTest_Status_t) mcuxClOsccaSm2_SignVerify_SelfTest(mcuxClSession_Handle_t session)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_SignVerify_SelfTest);

    /* Create buffer for ciphertext */
    uint32_t cpuWaUsedWord = (MCUXCLOSCCASM2_SIGNVERIFY_SELFTEST_SIZEOF_WA_CPU - MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU) / sizeof(uint32_t);
    uint8_t * pSigVerBuf = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, cpuWaUsedWord);
    if (NULL == pSigVerBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
    }

    uint8_t *hashCtx = pSigVerBuf;
    uint8_t *pPreHash = hashCtx + MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS * sizeof(uint32_t);
    uint8_t *pHashResult = pPreHash + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint8_t *pPrivKeyDesc = pHashResult + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint8_t *pPubKeyDesc = pPrivKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);
    uint8_t *pSignature_r = pPubKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);

    /****************************************************************/
    /* Preparation: setup SM2 key                                   */
    /****************************************************************/
    /* Initialize SM2 private key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t privKeyHandle = (mcuxClKey_Handle_t) pPrivKeyDesc;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(priKeyInitRet, mcuxClKey_init(session,
         MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           privKeyHandle,
         MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Std_Private,
                                                           privKey,
                                                           sizeof(privKey)));

    if (MCUXCLKEY_STATUS_OK != priKeyInitRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }
    /* Initialize SM2 public key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t pubKeyHandle = (mcuxClKey_Handle_t) pPubKeyDesc;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(pubKeyInitRet, mcuxClKey_init(session,
         MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           pubKeyHandle,
         MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Std_Public,
                                                           pubKey,
                                                           sizeof(pubKey)));
    if (MCUXCLKEY_STATUS_OK != pubKeyInitRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }

    /****************************************************************/
    /* Compute e = SM3_HASH(Za||M)                                  */
    /****************************************************************/
    static const uint8_t pIdentifier[] = {0x01, 0x02, 0x03, 0x04};

    /* Create parameter structure for function mcuxClOsccaSm2_ComputePrehash */
    mcuxClOsccaSm2_ComputePrehash_Param_t paramsPreHash;
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsPreHash.domainParameters, mcuxClOsccaSm2_DomainParams_SM2P256_Std);
    paramsPreHash.pIdentifier = pIdentifier;
    paramsPreHash.identifierLength = (uint16_t) sizeof(pIdentifier);
    paramsPreHash.pPublicKey = pubKey;
    paramsPreHash.pPrehash = pPreHash;

    /* Call function mcuxClOsccaSm2_ComputePrehash */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2PreHashRet, mcuxClOsccaSm2_ComputePrehash(session, &paramsPreHash));
    if(MCUXCLOSCCASM2_STATUS_COMPUTE_PREHASH_OK != SM2PreHashRet)
    {
        /* FA is the only negative return code from mcuxClOsccaSm2_ComputePrehash. */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }

    /****************************************************************/
    /* SM3 message digest calculation                               */
    /****************************************************************/
    /* Create parameter structure for Hash component */

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pHashCtx = (mcuxClHash_Context_t)hashCtx;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("reinterpret the hashCtx to mcuxClHash_Context_t type.")
    MCUX_CSSL_FP_FUNCTION_CALL(hashInitRet, mcuxClHash_init(session, pHashCtx, mcuxClOsccaSm3_Algorithm_Sm3));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    if(MCUXCLHASH_STATUS_OK != hashInitRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }


    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet, mcuxClHash_process(session,pHashCtx, pPreHash, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if(MCUXCLHASH_STATUS_OK != hashProRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet2, mcuxClHash_process(session,pHashCtx, message, sizeof(message)));
    if(MCUXCLHASH_STATUS_OK != hashProRet2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }

    uint32_t pOutSize = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL(hashFinRet, mcuxClHash_finish(session, pHashCtx, pHashResult, &pOutSize));
    if(MCUXCLHASH_STATUS_OK != hashFinRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL);
    }

    /****************************************************************/
    /* Verify the pre-generated signature                           */
    /****************************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerRet, mcuxClOsccaSm2_Verify(session, pubKeyHandle, mcuxClSignature_Mode_SM2, pHashResult, pOutSize, signature, sizeof(signature)));
    if(MCUXCLOSCCASM2_STATUS_OK != SM2VerRet)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == SM2VerRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            /* Free workarea allocated in mcuxClOsccaSm2_SignVerify_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, (mcuxClOsccaSm2_SelfTest_Status_t)MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_ComputePrehash),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify));
        }
    }

    /****************************************************************/
    /* Generate new signature                                       */
    /****************************************************************/
    uint32_t signatureSize = 0U;
    MCUX_CSSL_FP_FUNCTION_CALL(SM2SignRet, mcuxClOsccaSm2_Sign(session, privKeyHandle, mcuxClSignature_Mode_SM2, pHashResult, pOutSize, pSignature_r, &signatureSize));
    if(MCUXCLOSCCASM2_STATUS_OK != SM2SignRet)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == SM2SignRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            /* Free workarea allocated in mcuxClOsccaSm2_SignVerify_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, (mcuxClOsccaSm2_SelfTest_Status_t)MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_ComputePrehash),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Sign));
        }
    }

    /****************************************************************/
    /* Verify the new signature                                     */
    /****************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerRet2, mcuxClOsccaSm2_Verify(session, pubKeyHandle, mcuxClSignature_Mode_SM2, pHashResult, pOutSize, pSignature_r, signatureSize));
    if(MCUXCLOSCCASM2_STATUS_OK != SM2VerRet2)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == SM2VerRet2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            /* Free workarea allocated in mcuxClOsccaSm2_SignVerify_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, (mcuxClOsccaSm2_SelfTest_Status_t)MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_ComputePrehash),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Sign));
        }
    }


    /* Free workarea allocated in mcuxClOsccaSm2_SignVerify_SelfTest */
    mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_SignVerify_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_OK, (mcuxClOsccaSm2_SelfTest_Status_t)MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_ComputePrehash),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish),
                                                         2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Sign));
}

static const uint8_t Z_A[] = {
    0xE4, 0xD1, 0xD0, 0xC3, 0xCA, 0x4C, 0x7F, 0x11, 0xBC, 0x8F, 0xF8, 0xCB, 0x3F, 0x4C, 0x02, 0xA7,
    0x8F, 0x10, 0x8F, 0xA0, 0x98, 0xE5, 0x1A, 0x66, 0x84, 0x87, 0x24, 0x0F, 0x75, 0xE2, 0x0F, 0x31};

static const uint8_t Z_B[] = {
    0x6B, 0x4B, 0x6D, 0x0E, 0x27, 0x66, 0x91, 0xBD, 0x4A, 0x11, 0xBF, 0x72, 0xF4, 0xFB, 0x50, 0x1A,
    0xE3, 0x09, 0xFD, 0xAC, 0xB7, 0x2F, 0xA6, 0xCC, 0x33, 0x6E, 0x66, 0x56, 0x11, 0x9A, 0xBD, 0x67};

static const uint8_t rand_A[] = {
    0x83, 0xA2, 0xC9, 0xC8, 0xB9, 0x6E, 0x5A, 0xF7, 0x0B, 0xD4, 0x80, 0xB4, 0x72, 0x40, 0x9A, 0x9A,
    0x32, 0x72, 0x57, 0xF1, 0xEB, 0xB7, 0x3F, 0x5B, 0x07, 0x33, 0x54, 0xB2, 0x48, 0x66, 0x85, 0x63};

static const uint8_t pri_key_A[]= {
    0x6F, 0xCB, 0xA2, 0xEF, 0x9A, 0xE0, 0xAB, 0x90, 0x2B, 0xC3, 0xBD, 0xE3, 0xFF, 0x91, 0x5D, 0x44,
    0xBA, 0x4C, 0xC7, 0x8F, 0x88, 0xE2, 0xF8, 0xE7, 0xF8, 0x99, 0x6D, 0x3B, 0x8C, 0xCE, 0xED, 0xEE};

static const uint8_t ephemeral_point_A[] = {
    0x6C, 0xB5, 0x63, 0x38, 0x16, 0xF4, 0xDD, 0x56, 0x0B, 0x1D, 0xEC, 0x45, 0x83, 0x10, 0xCB, 0xCC,
    0x68, 0x56, 0xC0, 0x95, 0x05, 0x32, 0x4A, 0x6D, 0x23, 0x15, 0x0C, 0x40, 0x8F, 0x16, 0x2B, 0xF0,
    0x0D, 0x6F, 0xCF, 0x62, 0xF1, 0x03, 0x6C, 0x0A, 0x1B, 0x6D, 0xAC, 0xCF, 0x57, 0x39, 0x92, 0x23,
    0xA6, 0x5F, 0x7D, 0x7B, 0xF2, 0xD9, 0x63, 0x7E, 0x5B, 0xBB, 0xEB, 0x85, 0x79, 0x61, 0xBF, 0x1A};

static const uint8_t ephemeral_point_B[] = {
    0x17, 0x99, 0xB2, 0xA2, 0xC7, 0x78, 0x29, 0x53, 0x00, 0xD9, 0xA2, 0x32, 0x5C, 0x68, 0x61, 0x29,
    0xB8, 0xF2, 0xB5, 0x33, 0x7B, 0x3D, 0xCF, 0x45, 0x14, 0xE8, 0xBB, 0xC1, 0x9D, 0x90, 0x0E, 0xE5,
    0x54, 0xC9, 0x28, 0x8C, 0x82, 0x73, 0x3E, 0xFD, 0xF7, 0x80, 0x8A, 0xE7, 0xF2, 0x7D, 0x0E, 0x73,
    0x2F, 0x7C, 0x73, 0xA7, 0xD9, 0xAC, 0x98, 0xB7, 0xD8, 0x74, 0x0A, 0x91, 0xD0, 0xDB, 0x3C, 0xF4};

static const uint8_t public_key_B[] = {
    0x24, 0x54, 0x93, 0xD4, 0x46, 0xC3, 0x8D, 0x8C, 0xC0, 0xF1, 0x18, 0x37, 0x46, 0x90, 0xE7, 0xDF,
    0x63, 0x3A, 0x8A, 0x4B, 0xFB, 0x33, 0x29, 0xB5, 0xEC, 0xE6, 0x04, 0xB2, 0xB4, 0xF3, 0x7F, 0x43,
    0x53, 0xC0, 0x86, 0x9F, 0x4B, 0x9E, 0x17, 0x77, 0x3D, 0xE6, 0x8F, 0xEC, 0x45, 0xE1, 0x49, 0x04,
    0xE0, 0xDE, 0xA4, 0x5B, 0xF6, 0xCE, 0xCF, 0x99, 0x18, 0xC8, 0x5E, 0xA0, 0x47, 0xC6, 0x0A, 0x4C};

static const uint8_t expected_common_secret[] = {
    0x55, 0xB0, 0xAC, 0x62, 0xA6, 0xB9, 0x27, 0xBA, 0x23, 0x70, 0x38, 0x32, 0xC8, 0x53, 0xDE, 0xD4};

static const uint8_t S1[] = {
    0x28, 0x4C, 0x8F, 0x19, 0x8F, 0x14, 0x1B, 0x50, 0x2E, 0x81, 0x25, 0x0F, 0x15, 0x81, 0xC7, 0xE9,
    0xEE, 0xB4, 0xCA, 0x69, 0x90, 0xF9, 0xE0, 0x2D, 0xF3, 0x88, 0xB4, 0x54, 0x71, 0xF5, 0xBC, 0x5C};

static const uint8_t SA[] = {
    0x23, 0x44, 0x4D, 0xAF, 0x8E, 0xD7, 0x53, 0x43, 0x66, 0xCB, 0x90, 0x1C, 0x84, 0xB3, 0xBD, 0xBB,
    0x63, 0x50, 0x4F, 0x40, 0x65, 0xC1, 0x11, 0x6C, 0x91, 0xA4, 0xC0, 0x06, 0x97, 0xE6, 0xCF, 0x7A};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_KeyExchange_SelfTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_SelfTest_Status_t) mcuxClOsccaSm2_KeyExchange_SelfTest(mcuxClSession_Handle_t session)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_KeyExchange_SelfTest);

    /* Create buffer for ciphertext */
    uint32_t cpuWaUsedWord = (MCUXCLOSCCASM2_KEYEX_SELFTEST_SIZEOF_WA_CPU - MCUXCLOSCCASM2_KEYEXCHANGE_SIZEOF_WA_CPU) / sizeof(uint32_t);
    uint8_t * pKeyExBuf = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, cpuWaUsedWord);
    if (NULL == pKeyExBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
    }

    uint32_t k_len = 16u;
    /****************************************************************/
    /* CPU and PKC workarea allocation                              */
    /****************************************************************/
    uint8_t *pConfirmR2I = pKeyExBuf;
    uint8_t *pConfirmI2R = pConfirmR2I + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint8_t *pCommonSecret = pConfirmI2R + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;

    /****************************************************************/
    /* OSCCA SM2 KeyExchange                                        */
    /****************************************************************/
    /* Create parameter structure for function mcuxClOsccaSm2_KeyExchange */
    mcuxClOsccaSm2_KeyExchange_Param_t paramsKeyEx;
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsKeyEx.domainParameters, mcuxClOsccaSm2_DomainParams_SM2P256_Ext);
    paramsKeyEx.pPreHashInfoInitiator = Z_A;
    paramsKeyEx.pPreHashInfoResponder = Z_B;
    paramsKeyEx.pPrivateEphemeralScalar = rand_A;
    paramsKeyEx.pPrivateKey = pri_key_A;
    paramsKeyEx.pPublicEphemeralPoint = ephemeral_point_A;
    paramsKeyEx.pPublicEphemeralPointParty2 = ephemeral_point_B;
    paramsKeyEx.pPublicKeyParty2 = public_key_B;
    paramsKeyEx.pConfirmationFromResponderToInitiator = pConfirmR2I;
    paramsKeyEx.pConfirmationFromInitiatorToResponder = pConfirmI2R;
    paramsKeyEx.pCommonSecret = pCommonSecret;
    paramsKeyEx.commonSecretLength = k_len;
    paramsKeyEx.options = MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION | MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_INITIATOR;

    /* Call mcuxClOsccaSm2_KeyExchange and check result */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2KeyExRet, mcuxClOsccaSm2_KeyExchange(session, &paramsKeyEx));
    if(MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_OK != SM2KeyExRet)
    {
        if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == SM2KeyExRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK);
        }
        else
        {
            /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange_SelfTest */
            mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
            MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, (mcuxClOsccaSm2_SelfTest_Status_t)MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange));
        }
    }

    /* Check the result of the key exchange with expected output */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet, mcuxClOsccaSm2_RobustCompareBoolean(expected_common_secret, pCommonSecret, k_len));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet)
    {
        MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet1, mcuxClOsccaSm2_RobustCompareBoolean(S1, pConfirmR2I, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet1)
    {
        MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL +
                        (uint32_t)S1 + (uint32_t)pConfirmR2I + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange),
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet2, mcuxClOsccaSm2_RobustCompareBoolean(SA, pConfirmI2R, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet2)
    {
        MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + 2u * (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL +
                        (uint32_t)S1 + (uint32_t)pConfirmR2I + 2u * MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 +
                        (uint32_t)SA + (uint32_t)pConfirmI2R + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange),
                                                         3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + 3u * (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL +
                    (uint32_t)S1 + (uint32_t)pConfirmR2I + 2u * MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 + (uint32_t)SA + (uint32_t)pConfirmI2R);
    /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange_SelfTest */
    mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange_SelfTest, MCUXCLOSCCASM2_STATUS_SELFTEST_OK, MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange),
                                                         3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
}
