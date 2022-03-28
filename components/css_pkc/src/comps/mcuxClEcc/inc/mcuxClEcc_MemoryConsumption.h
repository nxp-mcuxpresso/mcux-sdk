/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
#define MCUXCLECC_KEYGEN_WACPU_SIZE     0u  ///< CPU workarea size (in bytes) for #mcuxClEcc_KeyGen.
#define MCUXCLECC_SIGN_WACPU_SIZE       0u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Sign.
#define MCUXCLECC_VERIFY_WACPU_SIZE     0u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Verify.
#define MCUXCLECC_POINTMULT_WACPU_SIZE  0u  ///< CPU workarea size (in bytes) for #mcuxClEcc_PointMult.
/**
 * @}
 */  /* MCUXCLECC_WACPU_ */
#ifdef MCUXCL_FEATURE_ECC_MONTGOMERY_DH
 /**
 * @addtogroup MCUXCLECC_MONT_WACPU_
 * @brief Define the CPU workarea size required by mcuxClEcc_Mont APIs.
 * @{
 */
#define MCUXCLECC_MONT_DHKEYGENERATION_WACPU_SIZE      100u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyGeneration.
#define MCUXCLECC_MONT_DHKEYAGREEMENT_WACPU_SIZE       100u  ///< CPU workarea size (in bytes) for #mcuxClEcc_Mont_DhKeyAgreement.
/**
 * @}
 */  /* MCUXCLECC_MONT_WACPU_ */
#endif

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
 * PKC workarea size (in bytes) for #mcuxClEcc_KeyGen for arbitrary lengths of p and n (in bytes).
 */
#define MCUXCLECC_KEYGEN_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Sign for arbitrary lengths of p and n (in bytes).
 */
#define MCUXCLECC_SIGN_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Verify for arbitrary lengths of p and n (in bytes).
 */
#define MCUXCLECC_VERIFY_WAPKC_SIZE(pByteLen,nByteLen)  \
    (28u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_PointMult for arbitrary lengths of p and n (in bytes).
 */
#define MCUXCLECC_POINTMULT_WAPKC_SIZE(pByteLen,nByteLen)  \
    (24u * (MCUXCLECC_ALIGN_SIZE_PKC(MCUXCLECC_MAX(pByteLen,nByteLen)) + MCUXCLECC_PKC_WORDSIZE))

/**
 * @}
 */  /* MCUXCLECC_WAPKC_ */

#ifdef MCUXCL_FEATURE_ECC_MONTGOMERY_DH

/**
 * @addtogroup MCUXCLECC_WAPKC_
 * @brief Define the PKC workarea size required by mcuxClEcc APIs.
 * @{
 */

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_KeyGen for arbitrary lengths of p and n (in bytes).
 */
#define MCUXCLECC_MONT_DHKEYGENERATION_CURVE25519_WAPKC_SIZE  \
    (1000u)

/**
 * PKC workarea size (in bytes) for #mcuxClEcc_Sign for arbitrary lengths of p and n (in bytes).
 */
#define MCUXCLECC_MONT_DHKEYAGREEMENT_CURVE25519_WAPKC_SIZE  \
    (1000u)

/**
 * @}
 */  /* MCUXCLECC_WAPKC_ */

#endif
/**
 * @}
 */ /* mcuxClEcc_MemoryConsumption */


#endif /* MCUXCLECC_MEMORYCONSUMPTION_H_ */
