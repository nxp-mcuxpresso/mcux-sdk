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

/** @file  mcuxClOsccaSm2_Keyagreement_SelfTest.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 keyagreement selftest function
 */
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm2_SelfTest.h>
#include <mcuxClOscca_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>

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

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_KeyAgreement_SelfTest, mcuxClKey_Agreement_SelfTestFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClOsccaSm2_KeyAgreement_SelfTest(
   mcuxClSession_Handle_t session,
   mcuxClKey_Agreement_t agreement
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_KeyAgreement_SelfTest);

    /* Create buffer for keyagreement selftest */
    uint32_t cpuWaUsedWord = (MCUXCLOSCCASM2_KEYAGREEMENT_SELFTEST_SIZEOF_WA_CPU -
                            MCUXCLOSCCASM2_KEYAGREEMENT_SIZEOF_WA_CPU) / sizeof(uint32_t);
    uint8_t * pKeyExBuf = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, cpuWaUsedWord);
    if (NULL == pKeyExBuf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_ERROR);
    }

    uint32_t k_len = sizeof(expected_common_secret);
    /****************************************************************/
    /* CPU and PKC workarea allocation                              */
    /****************************************************************/
    uint8_t *pPrivKeyDesc = pKeyExBuf;
    uint8_t *pPubKeyDesc = pPrivKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);
    uint8_t *pConfirmR2I = pPubKeyDesc + mcuxClOscca_alignSize(MCUXCLKEY_DESCRIPTOR_SIZE);
    uint8_t *pConfirmI2R = pConfirmR2I + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint8_t *pCommonSecret = pConfirmI2R + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;

    /****************************************************************/
    /* Preparation: setup SM2 key                                   */
    /****************************************************************/
    /* Initialize SM2 private key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t privKeyA = (mcuxClKey_Handle_t) pPrivKeyDesc;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(priKeyInitRet, mcuxClKey_init(session,
         MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           privKeyA,
         MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Ext_Private,
                                                           pri_key_A,
                                                           sizeof(pri_key_A)));
    if (MCUXCLKEY_STATUS_OK != priKeyInitRet)
    {
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_FAILURE,
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init));
    }

    /* Initialize SM2 public key */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t pubKeyB = (mcuxClKey_Handle_t) pPubKeyDesc;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(pubKeyInitRet, mcuxClKey_init(session,
         MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
                                                           pubKeyB,
         MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
                                                           mcuxClKey_Type_SM2P256_Ext_Public,
                                                           public_key_B,
                                                           sizeof(public_key_B)));
    if (MCUXCLKEY_STATUS_OK != pubKeyInitRet)
    {
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_FAILURE,
                                                        2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init));
    }

    /****************************************************************/
    /* OSCCA SM2 KeyExchange                                        */
    /****************************************************************/
    mcuxClKey_Agreement_AdditionalInput_t additionalInputs[MCUXCLOSCCASM2_KEYAGREEMENT_NUM_OF_ADDITIONAL_INPUTS] = {
            {.input = Z_A, .size = sizeof(Z_A)},
            {.input = Z_B, .size = sizeof(Z_B)},
            {.input = rand_A, .size = sizeof(rand_A)},
            {.input = ephemeral_point_A, .size = sizeof(ephemeral_point_A)},
            {.input = ephemeral_point_B, .size = sizeof(ephemeral_point_B)},
            {.input = pConfirmR2I, .size = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3},
            {.input = pConfirmI2R, .size = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3}
        };

    MCUX_CSSL_FP_FUNCTION_CALL(agreementRet, mcuxClKey_agreement(
      /* mcuxClSession_Handle_t session:   */ session,
      /* mcuxClKey_Agreement_t agreement:  */ agreement,
      /* mcuxClKey_Handle_t key:           */ privKeyA,
      /* mcuxClKey_Handle_t otherKey:      */ pubKeyB,
      /* mcuxClKey_AgreementInput_t :      */ additionalInputs,
      /* uint32_t numberOfInputs:         */ MCUXCLOSCCASM2_KEYAGREEMENT_NUM_OF_ADDITIONAL_INPUTS,
      /* uint8_t * pOut:                  */ pCommonSecret,
      /* uint32_t * const pOutLength:     */ &k_len
    ));

    if (MCUXCLKEY_STATUS_OK != agreementRet)
    {
        /* Free workarea allocated in mcuxClOsccaMacModes_Sm4CbcMac_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_FAILURE, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_agreement));
    }

    /* Check the result of the key exchange with expected output */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet, mcuxClOsccaSm2_RobustCompareBoolean(expected_common_secret, pCommonSecret, k_len));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet)
    {
        MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaMacModes_Sm4CbcMac_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_FAILURE, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_agreement),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet1, mcuxClOsccaSm2_RobustCompareBoolean(S1, pConfirmR2I, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet1)
    {
        MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL +
                        (uint32_t)S1 + (uint32_t)pConfirmR2I + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaMacModes_Sm4CbcMac_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_FAILURE, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_agreement),
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2SelfTestComBoRet2, mcuxClOsccaSm2_RobustCompareBoolean(SA, pConfirmI2R, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SelfTestComBoRet2)
    {
        MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + 2u * (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL +
                        (uint32_t)S1 + (uint32_t)pConfirmR2I + 2u * MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 +
                        (uint32_t)SA + (uint32_t)pConfirmI2R + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        /* Free workarea allocated in mcuxClOsccaMacModes_Sm4CbcMac_SelfTest */
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_FAILURE, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_agreement),
                                                         3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
    }

    MCUX_CSSL_SC_SUB((uint32_t)expected_common_secret + (uint32_t)pCommonSecret + k_len + 3u * (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL +
                    (uint32_t)S1 + (uint32_t)pConfirmR2I + 2u * MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 +
                    (uint32_t)SA + (uint32_t)pConfirmI2R);

    /* Free workarea allocated in mcuxClOsccaMacModes_Sm4CbcMac_SelfTest */
    mcuxClSession_freeWords_cpuWa(session, cpuWaUsedWord);
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyAgreement_SelfTest, MCUXCLKEY_STATUS_OK, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_agreement),
                                                         3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean));
}

