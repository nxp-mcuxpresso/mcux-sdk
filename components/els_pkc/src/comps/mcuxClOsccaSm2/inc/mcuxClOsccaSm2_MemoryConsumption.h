/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClOsccaSm2_MemoryConsumption.h
 * @brief Defines the memory consumption for the mcuxClOsccaSm2 component
 */

#ifndef MCUXCLOSCCASM2_MEMORYCONSUMPTION_H_
#define MCUXCLOSCCASM2_MEMORYCONSUMPTION_H_

/**
 * @defgroup mcuxClOsccaSm2_MemoryConsumption mcuxClOsccaSm2_MemoryConsumption
 * @brief Defines the memory consumption for the @ref mcuxClOsccaSm2 component
 * @ingroup mcuxClOsccaSm2
 * @{
 */
/*********************************************************************************************/
/** @brief  Definition of CPU workarea size in bytes for SM2 API functions                   */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU (84u)

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 signature generation             */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_SIGN_SIZEOF_WA_CPU(nLength) (84u + mcuxClOscca_alignSize(nLength))

/*********************************************************************************************/
/** @brief  Definition of CPU workarea size in bytes for SM2 invert private key              */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_CPU (84u)

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 pre-hash calculation             */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU (160u)

/*************************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 key generation through internal call */
/*************************************************************************************************/
#define MCUXCLOSCCASM2_KEY_GENERATEKEYPAIR_SIZEOF_WA_CPU (84u)

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 signature verification           */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_VERIFY_SIZEOF_WA_CPU (84u)


/*********************************************************************************************/
/** @brief Definition (constant part) of CPU workarea size in bytes for SM2 encryption       */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_ENCRYPT_SIZEOF_FIXED_WA_CPU   (84u)

/*********************************************************************************************/
/** @brief Definition (constant part) of CPU workarea size in bytes for SM2 decryption       */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_DECRYPT_SIZEOF_FIXED_WA_CPU   (84u)

/******************************************************************************************************/
/** @brief Platform-independent definition of CPU workarea sizes in bytes for SM2 encryption          */
/******************************************************************************************************/   
#define MCUXCLOSCCASM2_ENCRYPT_SIZEOF_WA_CPU(pLength) (212u + mcuxClOscca_alignSize(3u * (uint32_t)pLength + 1u))

/******************************************************************************************************/
/** @brief Platform-independent definition of CPU workarea sizes in bytes for SM2 decryption          */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_DECRYPT_SIZEOF_WA_CPU(pLength) (212u + mcuxClOscca_alignSize(pLength))

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 selftest through internal call   */
/*********************************************************************************************/
#if defined(MCUXCL_FEATURE_SM2_SIGNATURE) && defined (MCUXCL_FEATURE_SIGNATURE_SELFTEST)
#define MCUXCLOSCCASM2_SIGNATURE_SELFTEST_SIZEOF_WA_CPU  (400u)
#endif /* MCUXCL_FEATURE_SM2_SIGNATURE && MCUXCL_FEATURE_SIGNATURE_SELFTEST */

/******************************************************************************************************/
/** @brief Platform-independent definition of context size in bytes for SM2 Encryption and Decryption */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pLength) (328u + mcuxClOscca_alignSize(pLength))

/******************************************************************************************************/
/** @brief Platform-dependent definition of context size in bytes for SM2 Cipher Enc and Dec          */
/******************************************************************************************************/
#ifdef MCUXCL_FEATURE_SM2_CIPHER

#define MCUXCLOSSCASM2_CIPHER_CRYPT_CONTEXT_SIZE (60u)

#endif /* MCUXCL_FEATURE_SM2_CIPHER */

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 enc/dec through internal call    */
/*********************************************************************************************/
#ifdef MCUXCL_FEATURE_SM2_CIPHER
#define MCUXCLOSCCASM2_CIPHER_ENCDEC_FIXED_SIZEOF_WA_CPU       (56u)
#define MCUXCLOSCCASM2_CIPHER_ENCDEC_SIZEOF_WA_CPU(pLength)    (56u +  \
                                                               MCUXCLOSSCASM2_CIPHER_CRYPT_CONTEXT_SIZE+       \
                                                               MCUXCLOSCCASM2_ENCRYPT_SIZEOF_WA_CPU(pLength)+  \
                                                               MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pLength)+       \
                                                               mcuxClOscca_alignSize(2U*(uint32_t)pLength+1U))

#endif /* MCUXCL_FEATURE_SM2_CIPHER */

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 sign/verify selftest             */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_SIGNVERIFY_SELFTEST_SIZEOF_WA_CPU    (528u)

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 enc/dec selftest                 */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_ENCDEC_SELFTEST_SIZEOF_WA_CPU    (1028u)

/******************************************************************************************************/
/** @brief Platform-independent definition of CPU workarea sizes in bytes for SM2 key exchange        */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_KEYEXCHANGE_SIZEOF_WA_CPU        (484u)

/************************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 key agreement through internal call */
/************************************************************************************************/
#ifdef MCUXCL_FEATURE_SM2_KEYAGREEMENT
#define MCUXCLOSCCASM2_KEYAGREEMENT_SIZEOF_WA_CPU    (484u)
#define MCUXCLOSCCASM2_KEYAGREEMENT_SELFTEST_SIZEOF_WA_CPU    (676u)
#endif /* MCUXCL_FEATURE_SM2_KEYAGREEMENT */

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 Keyexchange selftest             */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_KEYEX_SELFTEST_SIZEOF_WA_CPU    (564u)

/*********************************************************************************************/
/** @brief Definition of CPU workarea size in bytes for SM2 selftest                         */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_SELFTEST_SIZEOF_WA_CPU    (MCUXCLCORE_MAX(MCUXCLOSCCASM2_KEYEX_SELFTEST_SIZEOF_WA_CPU, \
                                                 MCUXCLCORE_MAX(MCUXCLOSCCASM2_ENCDEC_SELFTEST_SIZEOF_WA_CPU,\
                                                                   MCUXCLOSCCASM2_SIGNVERIFY_SELFTEST_SIZEOF_WA_CPU)))

/******************************************************************************************************/
/** @brief  Definition of PKC workarea size in bytes for pre-hashing                                  */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_PKC    (4u)

/**
 * @brief PKC wordsize in SM2 component.
 */
#define MCUXCLOSCCASM2_PKC_WORDSIZE  8u

/******************************************************************************************************/
/** @brief Macro to determine PKC workarea size for arbitrary byte lengths of p and n and defines    */
/** @brief for PKC workarea sizes for standard key lengths                                           */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen) \
    (30u * (MCUXCLCORE_ALIGN_TO_WORDSIZE(MCUXCLOSCCASM2_PKC_WORDSIZE, MCUXCLCORE_MAX(MCUXCLCORE_MAX((uint32_t)pLen,(uint32_t)nLen),32u)) + MCUXCLOSCCASM2_PKC_WORDSIZE))

/******************************************************************************************************/
/** @brief  Definition of PKC workarea size in bytes for SM2 signature verification                   */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_VERIFY_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/******************************************************************************************************/
/** @brief Definition of SM2 verify PKC workarea size for bit length up to 256                        */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_VERIFY_SIZEOF_WA_PKC_256()  (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief Definition of PKC workarea size in bytes for invert-private-key calculation                */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_PKC(pLen, nLen) \
    (9u * (MCUXCLCORE_ALIGN_TO_WORDSIZE(MCUXCLOSCCASM2_PKC_WORDSIZE, MCUXCLCORE_MAX(MCUXCLCORE_MAX((uint32_t)pLen,(uint32_t)nLen), 32u)) + MCUXCLOSCCASM2_PKC_WORDSIZE))

/******************************************************************************************************/
/** @brief Definition of PKC workarea size for invert-private-key calculation for bit length up to 256*/
/******************************************************************************************************/
#define MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_PKC_256()  (MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief  Definition of PKC workarea size in bytes for SM2 signature generation                     */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_SIGN_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/******************************************************************************************************/
/** @brief Definition of SM2 sign PKC workarea size for bit length up to 256                          */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_SIGN_SIZEOF_WA_PKC_256()   (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief Definition of SM2 selftest PKC workarea size for bit length up to 256 through internal call*/
/******************************************************************************************************/
#if defined(MCUXCL_FEATURE_SM2_SIGNATURE) && defined (MCUXCL_FEATURE_SIGNATURE_SELFTEST)
#define MCUXCLOSCCASM2_SIGNATURE_SELFTEST_SIZEOF_WA_PKC_256()   MCUXCLCORE_MAX(MCUXCLOSCCASM2_SIGN_SIZEOF_WA_PKC_256(),\
                                                                                 MCUXCLOSCCASM2_VERIFY_SIZEOF_WA_PKC_256())
#endif /* MCUXCL_FEATURE_SM2_SIGNATURE && MCUXCL_FEATURE_SIGNATURE_SELFTEST */


/******************************************************************************************************/
/** @brief Definition of PKC workarea size in bytes for SM2 key generation                            */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_KEYGEN_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/*************************************************************************************************************/
/** @brief Definition of SM2 key generation PKC workarea size through internal call                          */
/*************************************************************************************************************/
#define MCUXCLOSCCASM2_KEY_GENERATEKEYPAIR_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/*************************************************************************************************************/
/** @brief Definition of SM2 key generation PKC workarea size for bit length up to 256 through internal call */
/*************************************************************************************************************/
#define MCUXCLOSCCASM2_KEY_GENERATEKEYPAIR_SIZEOF_WA_PKC_256()    (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief Definition of PKC workarea size in bytes for SM2 encryption                                */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_ENCRYPT_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/******************************************************************************************************/
/** @brief Definition of SM2 encryption PKC workarea size for bit length up to 256                    */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_ENCRYPT_SIZEOF_WA_PKC_256()  (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief Definition of PKC workarea size in bytes for SM2 decryption                                */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_DECRYPT_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/******************************************************************************************************/
/** @brief Definition of SM2 decryption PKC workarea size for bit length up to 256                   */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_DECRYPT_SIZEOF_WA_PKC_256() (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief Definition of SM2 enc/dec PKC workarea size through internal call                          */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_CIPHER_ENCDEC_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/******************************************************************************************************/
/** @brief Definition of SM2 enc/dec PKC workarea size for bit length up to 256 through internal call */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_CIPHER_ENCDEC_SIZEOF_WA_PKC_256()    (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))

/******************************************************************************************************/
/** @brief Definition of PKC workarea size in bytes for SM2 key exchange                              */
/******************************************************************************************************/
#define MCUXCLOSCCASM2_KEYEXCHANGE_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)

/*********************************************************************************************/
/** @brief Definition of PKC workarea size in bytes for SM2 selftest                         */
/*********************************************************************************************/
#define MCUXCLOSCCASM2_SELFTEST_SIZEOF_WA_PKC    MCUXCLCORE_MAX(MCUXCLCORE_MAX(MCUXCLCORE_MAX(MCUXCLCORE_MAX( \
    MCUXCLCORE_MAX(MCUXCLCORE_MAX(                                  \
    MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_PKC_256(),           \
    MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_PKC),                 \
    MCUXCLOSCCASM2_SIGN_SIZEOF_WA_PKC_256()),                      \
    MCUXCLOSCCASM2_VERIFY_SIZEOF_WA_PKC_256()),                    \
    MCUXCLOSCCASM2_ENCRYPT_SIZEOF_WA_PKC_256()),                   \
    MCUXCLOSCCASM2_DECRYPT_SIZEOF_WA_PKC_256()),                   \
	MCUXCLOSCCASM2_KEYEXCHANGE_SIZEOF_WA_PKC(MCUXCLOSCCASM2_SM2P256_SIZE_PRIMEP, MCUXCLOSCCASM2_SM2P256_SIZE_BASEPOINTORDER))

/************************************************************************************************************/
/** @brief Definition of SM2 key agreement PKC workarea size through internal call                          */
/************************************************************************************************************/
#ifdef MCUXCL_FEATURE_SM2_KEYAGREEMENT
#define MCUXCLOSCCASM2_KEYAGREEMENT_SIZEOF_WA_PKC(pLen, nLen)    MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pLen, nLen)
#define MCUXCLOSCCASM2_KEYAGREEMENT_SELFTEST_SIZEOF_WA_PKC       (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))
#endif /* MCUXCL_FEATURE_SM2_KEYAGREEMENT */

/************************************************************************************************************/
/** @brief Definition of SM2 key agreement PKC workarea size for bit length up to 256 through internal call */
/************************************************************************************************************/
#ifdef MCUXCL_FEATURE_SM2_KEYAGREEMENT
#define MCUXCLOSCCASM2_KEYAGREEMENT_SIZEOF_WA_PKC_256()    (MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(32u, 32u))
#endif /* MCUXCL_FEATURE_SM2_KEYAGREEMENT */

/**
 * @}
 */ /* mcuxClOsccaSm2_MemoryConsumption */

#endif /* MCUXCLOSCCASM2_MEMORYCONSUMPTION_H_ */

