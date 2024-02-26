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

/** @file  mcuxClRsa_Internal_MemoryConsumption.h
 *  @brief Internal memory consumption definitions of the mcuxClRsa component */

#ifndef MCUXCLRSA_INTERNAL_MEMORY_CONSUMPTION_H_
#define MCUXCLRSA_INTERNAL_MEMORY_CONSUMPTION_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClHash_Internal_Memory.h>
#include <internal/mcuxClRandomModes_Internal_SizeDefinitions.h>

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_Types.h>



#include <mcuxClPkc_Functions.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_privatePlain function.    */
/****************************************************************************/
#define MCUXCLRSA_INTERNAL_PRIVATEPLAIN_BLINDING_SIZE (4UL)

/**
 * @defgroup MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WA MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WA
 * @brief Workarea size macros of mcuxClRsa_privatePlain.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PRIVATEPLAIN_INPUT_SIZE(keyByteLength) \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength) + 2U * MCUXCLRSA_PKC_WORDSIZE)
    ///< Size of the input buffer for mcuxClRsa_privatePlain, that is allocated in PKC RAM.

#define MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PRIVPLAIN_UPTRT_SIZE * sizeof(uint16_t))) \
     + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(keyByteLength))
    ///< Definition of CPU workarea size for the mcuxClRsa_privatePlain function depending on the key byte-length.
    ///< Internally, it depends on the byte-length of the exponent, and it is rounded up here, based on the fact that d < n.

#define MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength)  \
    (6U * (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength) + MCUXCLRSA_PKC_ROUNDUP_SIZE(MCUXCLRSA_INTERNAL_PRIVATEPLAIN_BLINDING_SIZE)) + 12U * MCUXCLRSA_PKC_WORDSIZE \
     + MCUXCLRSA_PKC_ROUNDUP_SIZE(MCUXCLRSA_INTERNAL_PRIVATEPLAIN_BLINDING_SIZE))
    ///< Definition of PKC workarea size for the mcuxClRsa_privatePlain function depending on the key byte-length.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_privateCRT function.      */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PRIVATECRT_WA MCUXCLRSA_INTERNAL_PRIVATECRT_WA
 * @brief Workarea size macros of mcuxClRsa_privateCRT.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PRIVATECRT_BLINDING_SIZE (4UL)

#define MCUXCLRSA_INTERNAL_PRIVATECRT_WACPU_SIZE(primeByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PRIVCRT_UPTRT_SIZE * sizeof(uint16_t))) \
     + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(primeByteLength))
    ///< Definition of CPU workarea size for the mcuxClRsa_privateCRT function depending on the byte-length of p (equal to the byte-length of q).
    ///< Internally, it depends on the byte-lengths of the exponents dp and dq, and it is rounded up here, based on the fact that dp and dq are smaller than p and q.

#define MCUXCLRSA_INTERNAL_PRIVATECRT_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(MCUXCLRSA_INTERNAL_PRIVATECRT_BLINDING_SIZE) \
     + MCUXCLRSA_MAX((8U * MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength)) + (8U * MCUXCLRSA_PKC_ROUNDUP_SIZE(MCUXCLRSA_INTERNAL_PRIVATECRT_BLINDING_SIZE)) + (14U * MCUXCLRSA_PKC_WORDSIZE), \
                    (6U * MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength * 2u)) + (8U * MCUXCLRSA_PKC_WORDSIZE)))
    ///< Definition of PKC workarea size for the mcuxClRsa_privateCRT function depending on the byte-length of p.
/** @} */


/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_public function.          */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PUBLIC_WA MCUXCLRSA_INTERNAL_PUBLIC_WA
 * @brief Workarea size macros of mcuxClRsa_public.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PUBLIC_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PUBLIC_UPTRT_SIZE * sizeof(uint16_t))))
    ///< Definition of CPU workarea size for the mcuxClRsa_public function.

#define MCUXCLRSA_INTERNAL_PUBLIC_WAPKC_SIZE(keyByteLength)  \
    (5U * MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength) + 4U * MCUXCLRSA_PKC_WORDSIZE)
    ///< Definition of PKC workarea size for the mcuxClRsa_public function depending on the key byte-length.
/** @} */


/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_noEncode function.        */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_NOENCODE_WA MCUXCLRSA_INTERNAL_NOENCODE_WA
 * @brief Workarea size macros of mcuxClRsa_noEncode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_NOENCODE_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_NOENCODE_UPTRT_SIZE * sizeof(uint16_t))))
    ///< Definition of CPU workarea size for the mcuxClRsa_noEncode function.

#define MCUXCLRSA_INTERNAL_NOENCODE_WAPKC_SIZE  \
    0u
    ///< Definition of PKC workarea size for the mcuxClRsa_noEncode function.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_noVerify function.        */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_NOVERIFY_WA MCUXCLRSA_INTERNAL_NOVERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_noVerify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_NOVERIFY_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_NOVERIFY_UPTRT_SIZE * sizeof(uint16_t))))
    ///< Definition of CPU workarea size for the mcuxClRsa_noVerify function.

#define MCUXCLRSA_INTERNAL_NOVERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_noVerify function depending on the key byte-length.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_Mgf1 function.            */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_MGF1_WA MCUXCLRSA_INTERNAL_MGF1_WA
 * @brief Workarea size macros of mcuxClRsa_Mgf1.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_MGF1_WACPU_SIZE  \
    (MCUXCLHASH_INTERNAL_WACPU_MAX)
    ///< Definition of CPU workarea size for the mcuxClRsa_Mgf1 function.

#define MCUXCLRSA_INTERNAL_MGF1_WAPKC_SIZE(inputLen, hashLen)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE((inputLen) + 4U + (hashLen)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Mgf1 function.

/*
 * Definitions of maximum size of PKC workarea for the mcuxClRsa_Mgf1 function
 * for PSSENCODE and PSSVERIFY.
 * This function allocate space for Input, Hash output and 4B of the counter.
 * This macro takes into account the fact that:
 * inputLength = hashLen <= MCUXCLRSA_HASH_MAX_SIZE
 */
 #define MCUXCLRSA_INTERNAL_PSS_MGF1_MAX_WAPKC_SIZE  \
    (MCUXCLRSA_INTERNAL_MGF1_WAPKC_SIZE(MCUXCLRSA_HASH_MAX_SIZE, MCUXCLRSA_HASH_MAX_SIZE))
    ///< Definition of PKC workarea size for the mcuxClRsa_Mgf1 function.

/*
 * Definitions of maximum size of PKC workarea for the mcuxClRsa_Mgf1 function
 * for OAEPENCODE and OAEPDECODE.
 * This function allocate space for Input, Hash output and 4B of the counter.
 * This macro takes into account the fact that:
 * a. inputLength = keyByteLength - hLen - 1 or inputLength = hLen
 * b. keyByteLength >= mLen + 2*hLen + 2 which means, that keyByteLength - hLen - 1 >= mLen + hLen + 1  > hLen
 */
 #define MCUXCLRSA_INTERNAL_OAEP_MGF1_MAX_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength + 3u))

    ///< Definition of PKC workarea size for the mcuxClRsa_Mgf1 function.

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pssEncode function.       */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PSSENCODE_WA MCUXCLRSA_INTERNAL_PSSENCODE_WA
 * @brief Workarea size macros of mcuxClRsa_pssEncode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */

#define MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WAPKC_SIZE_WO_MGF1(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(((keyByteLength) - 2U) + MCUXCLRSA_PSS_PADDING1_LEN))
    ///< Maximum size for the temp buffer in mcuxClRsa_pssEncode, based on the fact that emLen >= hLen + sLen + 2.

#define MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WACPU_SIZE  \
    MCUXCLRSA_MAX(MCUXCLHASH_INTERNAL_WACPU_MAX, MCUXCLRSA_INTERNAL_MGF1_WACPU_SIZE)
    ///< Definitions of maximum size of CPU workarea for the mcuxClRsa_pssEncode function.

#define MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WAPKC_SIZE_WO_MGF1(keyByteLength) \
     + MCUXCLRSA_INTERNAL_PSS_MGF1_MAX_WAPKC_SIZE)
    ///< Definitions of maximum size of PKC workarea for the mcuxClRsa_pssEncode function.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pssVerify function.       */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PSSVERIFY_WA MCUXCLRSA_INTERNAL_PSSVERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_pssVerify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */

#define MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WACPU_SIZE  \
    (MCUXCLRSA_MAX(MCUXCLHASH_INTERNAL_WACPU_MAX, MCUXCLRSA_INTERNAL_MGF1_WACPU_SIZE))
    ///< Definition of CPU workarea size for the mcuxClRsa_pssVerify function.

/*
 * Definitions of maximum size of PKC workarea for the mcuxClRsa_pssVerify function without workarea size for MGF1 function.
 * This macro specifies the size of the space allocated for Hash (size hLen), salt (sLen) and padding1.
 * It takes into account the condition that emLen >= hLen + sLen + 2 => hLen + sLen <= emLen - 2,
 * where emLen = keyByteLength (only byte-level granularity of keys is supported, thus keyBitLength is a multiple of 8).
 * Having sLen rounding up to CPU word additionally 3B must be added.
 */
#define MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WAPKC_SIZE_WO_MGF1(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE((((keyByteLength) - 2U /* hLen + sLen */ + 3U /* round up sLen to CPU word */) + MCUXCLRSA_PSS_PADDING1_LEN) \
     + ((keyByteLength) - 1U) /* maskedDB  + H' */))
    ///< Definitions of maximum size of PKC workarea for the mcuxClRsa_pssVerify function without workarea size for MGF1 function.

#define MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WAPKC_SIZE_WO_MGF1(keyByteLength) \
     + MCUXCLRSA_INTERNAL_PSS_MGF1_MAX_WAPKC_SIZE) \
    ///< Definitions of maximum size of PKC workarea for the mcuxClRsa_pssVerify function.

/** @} */

/*********************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pkcs1v15Encode_sign function.  */
/*********************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WA MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WA
 * @brief Workarea size macros of mcuxClRsa_pkcs1v15Encode_sign.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WACPU_SIZE  \
    MCUXCLHASH_INTERNAL_WACPU_MAX
    ///< Definition of CPU workarea size for the mcuxClRsa_pkcs1v15Encode_sign function.

#define MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_pkcs1v15Encode_sign function.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pkcs1v15Verify function.  */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PKCS1V15VERIFY_WA MCUXCLRSA_INTERNAL_PKCS1V15VERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_pkcs1v15Verify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PKCS1V15VERIFY_WACPU_SIZE  \
    MCUXCLHASH_INTERNAL_WACPU_MAX
    ///< Definition of CPU workarea size for the mcuxClRsa_pkcs1v15Verify function.

#define MCUXCLRSA_INTERNAL_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength)) + \
     MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WAPKC_SIZE(keyByteLength)
    ///< Definition of PKC workarea size for the mcuxClRsa_pkcs1v15Verify function.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_oaepEncode function.      */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_OAEPENCODE_WA MCUXCLRSA_INTERNAL_OAEPENCODE_WA
 * @brief Workarea size macros of mcuxClRsa_oaepEncode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_OAEPENCODE_WACPU_SIZE  \
    MCUXCLRSA_MAX(MCUXCLHASH_INTERNAL_WACPU_MAX, MCUXCLRSA_INTERNAL_MGF1_WACPU_SIZE)
    ///< Definition of CPU workarea size for the mcuxClRsa_oaepEncode function.

#define MCUXCLRSA_INTERNAL_OAEPENCODE_WAPKC_SIZE_WO_MGF1(keyByteLength)  \
    (2u * MCUXCLRSA_PKC_ROUNDUP_SIZE((keyByteLength)-1u))
    ///< Definition of PKC workarea size for the mcuxClRsa_oaepEncode function, without taking into account the PKC WA usage of the MGF1

#define MCUXCLRSA_INTERNAL_OAEPENCODE_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_OAEPENCODE_WAPKC_SIZE_WO_MGF1(keyByteLength) \
     + MCUXCLRSA_INTERNAL_OAEP_MGF1_MAX_WAPKC_SIZE(keyByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_oaepEncode function.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_oaepDecode function.      */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_OAEPDECODE_WA MCUXCLRSA_INTERNAL_OAEPDECODE_WA
 * @brief Workarea size macros of mcuxClRsa_oaepDecode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_OAEPDECODE_WACPU_SIZE  \
    MCUXCLRSA_MAX(MCUXCLHASH_INTERNAL_WACPU_MAX, MCUXCLRSA_INTERNAL_MGF1_WACPU_SIZE)
    ///< Definition of CPU workarea size for the mcuxClRsa_oaepDecode function.

#define MCUXCLRSA_INTERNAL_OAEPDECODE_WAPKC_SIZE_WO_MGF1(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_oaepDecode function, without taking into account the PKC WA usage of the MGF1

#define MCUXCLRSA_INTERNAL_OAEPDECODE_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_OAEPDECODE_WAPKC_SIZE_WO_MGF1(keyByteLength) \
     + MCUXCLRSA_INTERNAL_OAEP_MGF1_MAX_WAPKC_SIZE(keyByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_oaepDecode function.
/** @} */

/****************************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pkcs1v15Encode_encrypt function.      */
/****************************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_ENCRYPT_WA MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_ENCRYPT_WA
 * @brief Workarea size macros of mcuxClRsa_pkcs1v15Encode_encrypt.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_ENCRYPT_WACPU_SIZE (0u)
    ///< Definition of CPU workarea size for the mcuxClRsa_pkcs1v15Encode_encrypt function.

#define MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_ENCRYPT_WAPKC_SIZE (0u)
    ///< Definition of PKC workarea size for the mcuxClRsa_pkcs1v15Encode_encrypt function.
/** @} */

/****************************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pkcs1v15Decode_decrypt function.      */
/****************************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_PKCS1V15DECODE_DECRYPT_WA MCUXCLRSA_INTERNAL_PKCS1V15DECODE_DECRYPT_WA
 * @brief Workarea size macros of mcuxClRsa_pkcs1v15Decode_decrypt.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_PKCS1V15DECODE_DECRYPT_WACPU_SIZE (0u)
    ///< Definition of CPU workarea size for the mcuxClRsa_pkcs1v15Decode_decrypt function.

#define MCUXCLRSA_INTERNAL_PKCS1V15DECODE_DECRYPT_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_pkcs1v15Decode_decrypt function.
/** @} */


/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_verify function.          */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_VERIFY_WA MCUXCLRSA_VERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_verify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */

#define MCUXCLRSA_INTERNAL_SIZEOF_PKCSTATEBACKUP (sizeof(mcuxClPkc_State_t))

#define MCUXCLRSA_INTERNAL_VERIFY_NOVERIFY_WACPU_SIZE  \
    (MCUXCLRSA_INTERNAL_SIZEOF_PKCSTATEBACKUP  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_NOVERIFY_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PUBLIC_WACPU_SIZE))
    ///< Definition of CPU workarea size for the mcuxClRsa_verify function using NOVERIFY option.

#define MCUXCLRSA_INTERNAL_VERIFY_PKCS1V15VERIFY_WACPU_SIZE  \
    (MCUXCLRSA_INTERNAL_SIZEOF_PKCSTATEBACKUP  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PKCS1V15VERIFY_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PUBLIC_WACPU_SIZE))
    ///< Definition of CPU workarea size for the mcuxClRsa_verify function using PKCS1V15VERIFY option.


#define MCUXCLRSA_INTERNAL_VERIFY_PSSVERIFY_WACPU_SIZE  \
    (MCUXCLRSA_INTERNAL_SIZEOF_PKCSTATEBACKUP  \
   + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WACPU_SIZE,  \
                  MCUXCLRSA_INTERNAL_PUBLIC_WACPU_SIZE))
    ///< Definition of CPU workarea size for the mcuxClRsa_verify function using PSSVERIFY option.

#define MCUXCLRSA_INTERNAL_VERIFY_NOVERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                    MCUXCLRSA_INTERNAL_NOVERIFY_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Verify function using NOVERIFY option depending on the key byte-length.

#define MCUXCLRSA_INTERNAL_VERIFY_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                    MCUXCLRSA_INTERNAL_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Verify function using PKCS1V15VERIFY option depending on the key byte-length.

#define MCUXCLRSA_INTERNAL_VERIFY_PSSVERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                    MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Verify function using PSSVERIFY option.

#define MCUXCLRSA_INTERNAL_VERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_MAX(MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_VERIFY_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength), \
                               MCUXCLRSA_INTERNAL_VERIFY_PSSVERIFY_WAPKC_SIZE(keyByteLength)), \
                  MCUXCLRSA_INTERNAL_VERIFY_NOVERIFY_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Verify function depending on the key byte-length.


/** @} */


/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_sign function.            */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_SIGN_WA MCUXCLRSA_SIGN_WA
 * @brief Workarea size macros of mcuxClRsa_sign.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_NOENCODE_WACPU_SIZE(keyByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_NOENCODE_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)))
    ///< Definition of CPU workarea size for the mcuxClRsa_sign function using NOENCODE option and a private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_PKCS1V15ENCODE_WACPU_SIZE(keyByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)))
    ///< Definition of CPU workarea size for the mcuxClRsa_sign function with pkcs1v15 encoding and a private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_PSSENCODE_WACPU_SIZE(keyByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)))
    ///< Definitions of CPU workarea size for the mcuxClRsa_sign function with pss encoding and a private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_NOENCODE_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_PRIVATEPLAIN_INPUT_SIZE(keyByteLength)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_NOENCODE_WAPKC_SIZE,  \
                    MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Sign function using NOENCODE option and a private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_PSSENCODE_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_PRIVATEPLAIN_INPUT_SIZE(keyByteLength)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WAPKC_SIZE(keyByteLength),  \
                    MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_sign function with pss encoding and a private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_PKCS1V15ENCODE_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_INTERNAL_PRIVATEPLAIN_INPUT_SIZE(keyByteLength)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WAPKC_SIZE(keyByteLength),  \
                    MCUXCLRSA_INTERNAL_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_sign function with pkcs1v15 encoding and a private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_PLAIN_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLRSA_MAX(MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_SIGN_PLAIN_PKCS1V15ENCODE_WAPKC_SIZE(keyByteLength), \
                               MCUXCLRSA_INTERNAL_SIGN_PLAIN_PSSENCODE_WAPKC_SIZE(keyByteLength)), \
                  MCUXCLRSA_INTERNAL_SIGN_PLAIN_NOENCODE_WAPKC_SIZE(keyByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_sign function keyByteLength private plain key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_NOENCODE_WACPU_SIZE(primeByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_NOENCODE_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PRIVATECRT_WACPU_SIZE(primeByteLength)))
    ///< Definition of CPU workarea size for the mcuxClRsa_sign function using NOENCODE option and a private CRT key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_PKCS1V15ENCODE_WACPU_SIZE(primeByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WACPU_SIZE,  \
                    MCUXCLRSA_INTERNAL_PRIVATECRT_WACPU_SIZE(primeByteLength)))
    ///< Definition of CPU workarea size for the mcuxClRsa_sign function with pkcs1v15 encoding and a private CRT key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_PSSENCODE_WACPU_SIZE(primeByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WACPU_SIZE,  \
                  MCUXCLRSA_INTERNAL_PRIVATECRT_WACPU_SIZE(primeByteLength)))
   ///< Definitions of CPU workarea size for the mcuxClRsa_sign function with pss encoding and a private CRT key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_NOENCODE_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(2u * primeByteLength) + \
     MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_NOENCODE_WAPKC_SIZE, MCUXCLRSA_INTERNAL_PRIVATECRT_WAPKC_SIZE(primeByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_Sign function using NOENCODE option and a private CRT key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_PSSENCODE_WAPKC_SIZE(primeByteLength)  \
    ((MCUXCLRSA_PKC_ROUNDUP_SIZE(2u * primeByteLength) + \
     MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WAPKC_SIZE(2u * primeByteLength), MCUXCLRSA_INTERNAL_PRIVATECRT_WAPKC_SIZE(primeByteLength))))
    ///< Definition of PKC workarea size for the mcuxClRsa_sign function with pss encoding and a private CRT key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_PKCS1V15ENCODE_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(2u * primeByteLength) + \
     MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_PKCS1V15ENCODE_SIGN_WAPKC_SIZE(2u * primeByteLength), MCUXCLRSA_INTERNAL_PRIVATECRT_WAPKC_SIZE(primeByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_sign function with pkcs1v15 encoding and a private CRT key.

#define MCUXCLRSA_INTERNAL_SIGN_CRT_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLRSA_MAX(MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_SIGN_CRT_PKCS1V15ENCODE_WAPKC_SIZE(primeByteLength), \
                               MCUXCLRSA_INTERNAL_SIGN_CRT_PSSENCODE_WAPKC_SIZE(primeByteLength)), \
                  MCUXCLRSA_INTERNAL_SIGN_CRT_NOENCODE_WAPKC_SIZE(primeByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_sign function keyByteLength CRT key.

/** @} */



/*****************************************************************************************/
/* Definitions of workarea size for the mcuxClRsa_MillerRabinTest function.               */
/*****************************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_MILLERRABINTEST_WA MCUXCLRSA_INTERNAL_MILLERRABINTEST_WA
 * @brief Workarea size macros of mcuxClRsa_MillerRabinTest
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
#define MCUXCLRSA_INTERNAL_MILLERRABINTEST_WACPU_SIZE_WO_RNG(primeByteLength)  \
    MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(primeByteLength)
///< Definition of CPU workarea size for the mcuxClRsa_MillerRabinTest function depending on the byte-length of primeByteLength.
#else
//The parameters are just to keep the API consistent
#define MCUXCLRSA_INTERNAL_MILLERRABINTEST_WACPU_SIZE_WO_RNG(primeByteLength)  \
    (0u)
///< Definition of CPU workarea size for the mcuxClRsa_MillerRabinTest function depending on the byte-length of primeByteLength.
#endif

#define MCUXCLRSA_INTERNAL_MILLERRABINTEST_WACPU_SIZE(primeByteLength)  \
    (MCUXCLRSA_INTERNAL_MILLERRABINTEST_WACPU_SIZE_WO_RNG(primeByteLength) + MCUXCLRANDOMMODES_CPUWA_MAXSIZE)

#define MCUXCLRSA_INTERNAL_MILLERRABINTEST_T_BUFFER_SIZE(primeByteLength)  \
    (9u * MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength) + 11u * MCUXCLRSA_PKC_WORDSIZE)
    ///< Definition of PKC workarea size for the mcuxClRsa_MillerRabinTest function depending on the byte-length of primeByteLength.
/** @} */

/*****************************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_TestPrimeCandidate function.           */
/*****************************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WA MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WA
 * @brief Workarea size macros of mcuxClRsa_TestPrimeCandidate
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */

#define MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WACPU_SIZE_WO_MILLERRABIN \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_TESTPRIME_UPTRT_SIZE * sizeof(uint16_t))))
///< Definition of CPU workarea size for the mcuxClRsa_TestPrimeCandidate function depending on the byte-length of primeByteLength without mcuxClRsa_MillerRabinTest

#define MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WACPU_SIZE(primeByteLength)  \
    ((MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WACPU_SIZE_WO_MILLERRABIN)  \
     + MCUXCLRSA_INTERNAL_MILLERRABINTEST_WACPU_SIZE(primeByteLength))

#define MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLRSA_MAX(2u * MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength), \
                  MCUXCLRSA_INTERNAL_MILLERRABINTEST_T_BUFFER_SIZE(primeByteLength)))
    ///< Definition of PKC workarea size for the mcuxClRsa_TestPrimeCandidate function depending on the byte-length of primeByteLength.
/** @} */

/*****************************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_GenerateProbablePrime function.        */
/*****************************************************************************************/
/**
 * @defgroup MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WA MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WA
 * @brief Workarea size macros of mcuxClRsa_GenerateProbablePrime
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#ifndef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
//The parameters are just to keep the API consistent
#define MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE_WO_TESTPRIME_AND_MILLERRABIN(primeByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_GENPRIME_UPTRT_SIZE * sizeof(uint16_t))))
    ///< Definition of CPU workarea size for the mcuxClRsa_GenerateProbablePrime function depending on the byte-length of primeByteLength without mcuxClRsa_TestPrimeCandidate and mcuxClRsa_MillerRabinTest
#else
#define MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE_WO_TESTPRIME_AND_MILLERRABIN(primeByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_GENPRIME_UPTRT_SIZE * sizeof(uint16_t))) \
    + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(primeByteLength))
    ///< Definition of CPU workarea size for the mcuxClRsa_GenerateProbablePrime function depending on the byte-length of primeByteLength without mcuxClRsa_TestPrimeCandidate and mcuxClRsa_MillerRabinTest
#endif

#define MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE(primeByteLength)  \
    (MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE_WO_TESTPRIME_AND_MILLERRABIN(primeByteLength) \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WACPU_SIZE(primeByteLength), \
                    MCUXCLRANDOMMODES_CPUWA_MAXSIZE))
    ///< Definition of CPU workarea size for the mcuxClRsa_GenerateProbablePrime function depending on the byte-length of primeByteLength.


#define MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WAPKC_SIZE(primeByteLength)  \
    ((2u * MCUXCLRSA_PKC_WORDSIZE) \
     + MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WAPKC_SIZE(primeByteLength))
    ///< Definition of PKC workarea size for the mcuxClRsa_GenerateProbablePrime function depending on the byte-length of primeByteLength.
/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_ComputeD function.        */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_COMPD_WA MCUXCLRSA_COMPD_WA
 * @brief Workarea size macros of mcuxClRsa_ComputeD
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */

#define MCUXCLRSA_INTERNAL_COMPUTED_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_COMPD_UPTRT_SIZE * sizeof(uint16_t))))

#define MCUXCLRSA_INTERNAL_COMPUTED_WAPKC_SIZE(primeByteLength)  \
    ((2u * (MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength)))  \
     + (3u * MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength * 2u)) + (2u * MCUXCLRSA_PKC_WORDSIZE))
    ///< Definition of PKC workarea size for the mcuxClRsa_ComputeD function depending on the byte-length of p.
/** @} */

/*************************************************************************************************************************/
/* Definitions of generated key data size for the mcuxClRsa_KeyGeneration_Crt and mcuxClRsa_KeyGeneration_Plain functions. */
/*************************************************************************************************************************/
#ifndef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
#define MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(sizeof(mcuxClPkc_State_t)) \
     + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_UPTRT_SIZE * sizeof(uint16_t))) \
     + MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE(0))
#else
#define MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_WACPU_SIZE(primeByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(sizeof(mcuxClPkc_State_t)) \
     + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_UPTRT_SIZE * sizeof(uint16_t))) \
     + MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE(primeByteLength))
#endif

#define MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength) \
     + (2u * (MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength) + MCUXCLRSA_PKC_WORDSIZE)) \
     + MCUXCLRSA_MAX(MCUXCLRSA_MAX(MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength * 2u) + 3u * ((MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength) + MCUXCLRSA_PKC_WORDSIZE)) , \
                                 (6u * (MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength) + MCUXCLRSA_PKC_WORDSIZE) + MCUXCLRSA_PKC_WORDSIZE)), \
                                  MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WAPKC_SIZE(primeByteLength)))

#ifndef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
#define MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_WACPU_SIZE  \
     (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(sizeof(mcuxClPkc_State_t)) \
     + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_UPTRT_SIZE * sizeof(uint16_t)) \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE(0), MCUXCLRSA_INTERNAL_COMPUTED_WACPU_SIZE))
#else
#define MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_WACPU_SIZE(primeByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(sizeof(mcuxClPkc_State_t)) \
     + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_UPTRT_SIZE * sizeof(uint16_t)) \
     + MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE(primeByteLength), MCUXCLRSA_INTERNAL_COMPUTED_WACPU_SIZE))
#endif

#define MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_WAPKC_SIZE(keyByteLength)  \
    ((2u * (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength / 2u) + MCUXCLRSA_PKC_WORDSIZE)) \
      + MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength) \
      + MCUXCLRSA_MAX((2u *  MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength)), /* D and N */ \
                     MCUXCLRSA_MAX(MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WAPKC_SIZE(keyByteLength / 2u), \
                                  (MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength) + MCUXCLRSA_PKC_WORDSIZE) /* D + FW */ \
                                   + MCUXCLRSA_INTERNAL_COMPUTED_WAPKC_SIZE(keyByteLength / 2u))))

/**
 * @defgroup MCUXCLRSA_INTERNAL_KEYGENERATION_KEY_DATA_SIZE MCUXCLRSA_INTERNAL_KEYGENERATION_KEY_DATA_SIZE
 * @brief Definitions of bufer sizes for the mcuxClRsa_KeyGeneration_Crt and mcuxClRsa_KeyGeneration_Plain functions.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */

#define MCUXCLRSA_INTERNAL_KEYGENERATION_PLAIN_KEY_DATA_SIZE(keyByteLength)  \
    (sizeof(mcuxClRsa_Key) + (2u * (sizeof(mcuxClRsa_KeyEntry_t) + keyByteLength)))
    ///< Definition of buffer size for the key generation functions for private plain key (key type and key entries followed by the key data, i.e.: n, d).

#define MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_KEY_DATA_SIZE(keyByteLength)  \
    (sizeof(mcuxClRsa_Key) + (5U * (sizeof(mcuxClRsa_KeyEntry_t) + ((keyByteLength + 1u) / 2u))))
    ///< Definition of buffer size for the key generation functions for private CRT key (key type and key entries followed by the key data, i.e.: p, q, qInv, dp, dq).

#define MCUXCLRSA_INTERNAL_KEYGENERATION_PUBLIC_KEY_DATA_SIZE(keyByteLength)  \
    (sizeof(mcuxClRsa_Key) + (2u * (sizeof(mcuxClRsa_KeyEntry_t) + keyByteLength)))
    ///< Definition of buffer size for the key generation functions for public key (key type and key entries followed by the key data, i.e.: n, e).


/** @} */



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_MEMORY_CONSUMPTION_H_ */

