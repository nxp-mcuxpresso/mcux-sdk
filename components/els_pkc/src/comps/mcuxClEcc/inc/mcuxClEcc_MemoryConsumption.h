/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClEcc_MemoryConsumption.h
 * @brief Defines the memory consumption for the mcuxClEcc component
 */

#ifndef MCUXCLECC_MEMORYCONSUMPTION_H_
#define MCUXCLECC_MEMORYCONSUMPTION_H_


/**
 * @defgroup mcuxClEcc_MemoryConsumption mcuxClEcc_MemoryConsumption
 * @brief Defines the memory consumption for the @ref mcuxClEcc component
 * @ingroup mcuxClEcc
 * @{
 */

/**
 * @addtogroup MCUXCLECC_WACPU_
 * @brief Define the CPU workarea size required by mcuxClEcc APIs.
 * @{
 */
#define MCUXCLECC_ALIGN_SIZE_CPU(byteLen)  ((((byteLen) + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t))) * (sizeof(uint32_t)))

#ifdef MCUXCL_FEATURE_PROJECT_NIOBE4ANALOG

#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
#define MCUXCLECC_KEYGEN_WACPU_SIZE(byteLenN)  (96u + MCUXCLECC_ALIGN_SIZE_CPU(byteLenN + 8u))  ///< CPU workarea size (in bytes) for #mcuxClEcc_KeyGen.
#define MCUXCLECC_SIGN_WACPU_SIZE(byteLenN)    (96u + MCUXCLECC_ALIGN_SIZE_CPU(byteLenN + 8u))  ///< CPU workarea size (in bytes) for #mcuxClEcc_Sign.
#else /* ! MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND */
#define MCUXCLECC_KEYGEN_WACPU_SIZE(byteLenN)        96u  ///< CPU workarea size (in bytes) for #mcuxClEcc_KeyGen. Parameter byteLenN is just to keep the API consistent.
#define MCUXCLECC_SIGN_WACPU_SIZE(byteLenN)          96u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Sign. Parameter byteLenN is just to keep the API consistent.
#endif /* MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND */

#define MCUXCLECC_VERIFY_WACPU_SIZE     104u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Verify.
#define MCUXCLECC_POINTMULT_WACPU_SIZE  96u  ///< CPU workarea size (in bytes) for #mcuxClEcc_PointMult.
#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WACPU_SIZE  88u  ///< CPU workarea size (in bytes) for #mcuxClEcc_WeierECC_GenerateDomainParams.


/**
 * @}
 */  /* MCUXCLECC_WACPU_ */

/**
 * @addtogroup MCUXCLECC_MONTDH_WACPU_
 * @brief Define the CPU workarea size required by mcuxClEcc MontDH APIs.
 * @{
 */
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WACPU_SIZE    92u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration.
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE448_WACPU_SIZE      92u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration.

#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WACPU_SIZE     88u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement.
#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE448_WACPU_SIZE       88u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement.
/**
 * @}
 */  /* MCUXCLECC_MONTDH_WACPU_ */

 /**
 * @addtogroup MCUXCLECC_EDDSA_WACPU_
 * @brief Define the CPU workarea size required by mcuxClEcc EdDSA APIs.
 * @{
 */
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WACPU_SIZE    360u  ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair for Ed25519.
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED448_WACPU_SIZE      196u    ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair for Ed448.

#define MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WACPU_SIZE  540u  ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature for Ed25519.
#define MCUXCLECC_EDDSA_GENERATESIGNATURE_ED448_WACPU_SIZE    132u    ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature for Ed448.

#define MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WACPU_SIZE    540u  ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature for Ed25519.
#define MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED448_WACPU_SIZE      132u    ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature for Ed448.

#else

#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
#define MCUXCLECC_KEYGEN_WACPU_SIZE(byteLenN)  (416u + MCUXCLECC_ALIGN_SIZE_CPU(byteLenN + 8u))  ///< CPU workarea size (in bytes) for #mcuxClEcc_KeyGen.
#define MCUXCLECC_SIGN_WACPU_SIZE(byteLenN)    (416u + MCUXCLECC_ALIGN_SIZE_CPU(byteLenN + 8u))  ///< CPU workarea size (in bytes) for #mcuxClEcc_Sign.
#else /* ! MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND */
#define MCUXCLECC_KEYGEN_WACPU_SIZE(byteLenN)        416u  ///< CPU workarea size (in bytes) for #mcuxClEcc_KeyGen. Parameter byteLenN is just to keep the API consistent.
#define MCUXCLECC_SIGN_WACPU_SIZE(byteLenN)          416u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Sign. Parameter byteLenN is just to keep the API consistent.
#endif /* MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND */

#define MCUXCLECC_VERIFY_WACPU_SIZE     424u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Verify.
#define MCUXCLECC_POINTMULT_WACPU_SIZE  416u  ///< CPU workarea size (in bytes) for #mcuxClEcc_PointMult.
#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WACPU_SIZE  88u  ///< CPU workarea size (in bytes) for #mcuxClEcc_WeierECC_GenerateDomainParams.


/**
 * @}
 */  /* MCUXCLECC_WACPU_ */

/**
 * @addtogroup MCUXCLECC_MONTDH_WACPU_
 * @brief Define the CPU workarea size required by mcuxClEcc MontDH APIs.
 * @{
 */
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WACPU_SIZE    444u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration.
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE448_WACPU_SIZE      468u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration.

#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WACPU_SIZE     88u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement.
#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE448_WACPU_SIZE       88u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement.
/**
 * @}
 */  /* MCUXCLECC_MONTDH_WACPU_ */

 /**
 * @addtogroup MCUXCLECC_EDDSA_WACPU_
 * @brief Define the CPU workarea size required by mcuxClEcc EdDSA APIs.
 * @{
 */
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WACPU_SIZE    680u  ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair for Ed25519.
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED448_WACPU_SIZE      516u    ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair for Ed448.

#define MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WACPU_SIZE  540u  ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature for Ed25519.
#define MCUXCLECC_EDDSA_GENERATESIGNATURE_ED448_WACPU_SIZE    132u    ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature for Ed448.

#define MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WACPU_SIZE    540u  ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature for Ed25519.
#define MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED448_WACPU_SIZE      132u    ///< CPU workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature for Ed448.

#endif
/**
 * @}
 */  /* MCUXCLECC_EDDSA_WACPU_ */


/**
 * @addtogroup MCUXCLECC_WAPKC_
 * @brief Define the PKC workarea size required by mcuxClEcc APIs.
 * @{
 */

/**
 * @brief PKC wordsize in ECC component.
 */
#define MCUXCLECC_PKC_WORDSIZE  8u

/**
 * @brief Helper macro to get the maximum of two given constants.
 */
#define MCUXCLECC_MAX(value0, value1)  (((value0) > (value1)) ? (value0) : (value1))

/**
 * @brief Helper macro to calculate size aligned to PKC word.
 */
#define MCUXCLECC_ALIGN_SIZE_PKC(size)  ((((size) + MCUXCLECC_PKC_WORDSIZE - 1u) / MCUXCLECC_PKC_WORDSIZE) * MCUXCLECC_PKC_WORDSIZE)

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_KeyGen for arbitrary lengths of p and n.
 */
#define MCUXCLECC_KEYGEN_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))


/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Sign for arbitrary lengths of p and n.
 */
#define MCUXCLECC_SIGN_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))


/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Verify for arbitrary lengths of p and n.
 */

#define MCUXCLECC_VERIFY_WAPKC_SIZE(pByteLen,nByteLen)  \
    (28u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))


/**
 * PKC workarea size (in bytes) for #mcuxClEcc_PointMult for arbitrary lengths of p and n.
 */
#define MCUXCLECC_POINTMULT_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))


/**
 * PKC workarea size (in bytes) for #mcuxClEcc_WeierECC_GenerateDomainParams for arbitrary lengths of p and n.
 */
#ifdef MCUXCL_FEATURE_PLATFORM_RW61X

#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE(pByteLen,nByteLen)  \
    (22u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))

#else

#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))

#endif

#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE_128 (528u )
#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE_256 (880u )
#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE_384 (1232u )
#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE_512 (1584u )
#define MCUXCLECC_WEIERECC_GENERATEDOMAINPARAMS_WAPKC_SIZE_640 (1936u )




/**
 * @}
 */  /* MCUXCLECC_WAPKC_ */


/**
 * @addtogroup MCUXCLECC_MONTDH_WAPKC_
 * @brief Define the PKC workarea size required by mcuxClEcc_Mont APIs.
 * @{
 */

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration for Curve25519.
 */
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WAPKC_SIZE  880u

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement for Curve25519.
 */
#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WAPKC_SIZE  880u

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration for Curve448.
 */
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE448_WAPKC_SIZE  1408u

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement for Curve448.
 */
#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE448_WAPKC_SIZE  1408u

/**
 * @}
 */  /* MCUXCLECC_MONTDH_WAPKC_ */

/**
 * @addtogroup MCUXCLECC_EDDSA_WAPKC_
 * @brief Define the PKC workarea size required by mcuxClEcc EdDSA APIs.
 * @{
 */

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair.
 */
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED25519_WAPKC_SIZE    1760u  ///< PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair for Ed25519.
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_ED448_WAPKC_SIZE    2816u  ///< PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateKeyPair for Ed448.

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature.
 */
#define MCUXCLECC_EDDSA_GENERATESIGNATURE_ED25519_WAPKC_SIZE  1760u  ///< PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature for Ed25519.
#define MCUXCLECC_EDDSA_GENERATESIGNATURE_ED448_WAPKC_SIZE  2816u  ///< PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_GenerateSignature for Ed448.

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature.
 */
#define MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED25519_WAPKC_SIZE    1760u  ///< PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature for Ed25519.
#define MCUXCLECC_EDDSA_VERIFYSIGNATURE_ED448_WAPKC_SIZE    2816u  ///< PKC workarea size (in bytes) for #mcuxClEcc_EdDSA_VerifySignature for Ed448.

/**
 * @}
 */  /* MCUXCLECC_EDDSA_WAPKC_ */

/**
 * @brief Define for the buffer size (in bytes) for optimized custom ECC Weierstrass domain parameters
 */
#define MCUXCLECC_CUSTOMWEIERECCDOMAINPARAMS_SIZE(byteLenP, byteLenN)  \
    MCUXCLECC_ALIGN_SIZE_CPU(76u  \
                            + 8u * (byteLenP)  \
                            + 2u * (byteLenN) )

/**
 * @addtogroup MCUXCLECC_EDDSA_GENKEYPAIR_DESC_SIZE_
 * @brief Define for the EdDSA key pair generation descriptor size.
 * @{
 */
#define MCUXCLECC_EDDSA_GENERATEKEYPAIR_DESCRIPTOR_SIZE    8u  ///< EdDSA key pair generation descriptor size.
/**
 * @}
 */  /* MCUXCLECC_EDDSA_GENKEYPAIR_DESC_SIZE_ */

/**
 * @addtogroup MCUXCLECC_EDDSA_SIGNATURE_PROTOCOL_DESC_SIZE_
 * @brief Define for the EdDSA signature protocol descriptor size.
 * @{
 */
#define MCUXCLECC_EDDSA_SIGNATURE_PROTOCOL_DESCRIPTOR_SIZE 20u  ///< EdDSA signature generation descriptor size.
/**
 * @}
 */  /* MCUXCLECC_EDDSA_SIGNATURE_PROTOCOL_DESC_SIZE_ */



/**
 * @}
 */  /* mcuxClEcc_MemoryConsumption */

#endif /* MCUXCLECC_MEMORYCONSUMPTION_H_ */
