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

/** @file  mcuxClRsa_Internal_MemoryConsumption.h
 *  @brief Internal memory consumption definitions of the mcuxClRsa component */

#ifndef MCUXCLRSA_INTERNAL_MEMORY_CONSUMPTION_H_
#define MCUXCLRSA_INTERNAL_MEMORY_CONSUMPTION_H_

#include <mcuxClPkc.h>
#include <mcuxClHash.h>

#include <mcuxClHash_MemoryConsumption.h>

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_privatePlain function.    */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PRIVATEPLAIN_WA MCUXCLRSA_PRIVATEPLAIN_WA
 * @brief Workarea size macros of mcuxClRsa_privatePlain.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PRIVPLAIN_UPTRT_SIZE * sizeof(uint16_t))) \
    + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(keyByteLength))

#define MCUXCLRSA_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength)  \
    (7U * MCUXCLPKC_ROUNDUP_SIZE(keyByteLength) + 10U * MCUXCLPKC_WORDSIZE)

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_privateCRT function.    */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PRIVATECRT_WA MCUXCLRSA_PRIVATECRT_WA
 * @brief Workarea size macros of mcuxClRsa_privateCRT.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PRIVATECRT_BLINDING_SIZE (4UL)

#define MCUXCLRSA_PRIVATECRT_WACPU_SIZE(primeByteLength)  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PRIVCRT_UPTRT_SIZE * sizeof(uint16_t))) \
    + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(primeByteLength))

#define MCUXCLRSA_PRIVATECRT_WAPKC_SIZE(primeByteLength)  \
    (MCUXCLPKC_ROUNDUP_SIZE(primeByteLength * 2u) + MCUXCLPKC_ROUNDUP_SIZE(MCUXCLRSA_PRIVATECRT_BLINDING_SIZE) \
     + MCUXCLRSA_MAX((8U * MCUXCLPKC_ROUNDUP_SIZE(primeByteLength)) + (8U * MCUXCLPKC_ROUNDUP_SIZE(MCUXCLRSA_PRIVATECRT_BLINDING_SIZE)) + (12U * MCUXCLPKC_WORDSIZE), \
                    (6U * MCUXCLPKC_ROUNDUP_SIZE(primeByteLength * 2u)) + (8U * MCUXCLPKC_WORDSIZE)))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_public function.          */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PUBLIC_WA MCUXCLRSA_PUBLIC_WA
 * @brief Workarea size macros of mcuxClRsa_public.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PUBLIC_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_PUBLIC_UPTRT_SIZE * sizeof(uint16_t))))

#define MCUXCLRSA_PUBLIC_WAPKC_SIZE(keyByteLength)  \
    (5U * MCUXCLPKC_ROUNDUP_SIZE(keyByteLength) + 4U * MCUXCLPKC_WORDSIZE)

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_noEncode function.        */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_NOENCODE_WA MCUXCLRSA_NOENCODE_WA
 * @brief Workarea size macros of mcuxClRsa_noEncode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_NOENCODE_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_NOENCODE_UPTRT_SIZE * sizeof(uint16_t))))

#define MCUXCLRSA_NOENCODE_WAPKC_SIZE  \
    0u

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_noVerify function.        */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_NOVERIFY_WA MCUXCLRSA_NOVERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_noVerify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_NOVERIFY_WACPU_SIZE  \
    (MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_NOVERIFY_UPTRT_SIZE * sizeof(uint16_t))))

#define MCUXCLRSA_NOVERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_Mgf1 function.       */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_MGF1_WA MCUXCLRSA_MGF1_WA
 * @brief Workarea size macros of mcuxClRsa_Mgf1.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_MGF1_WACPU_SIZE  \
    (MCUXCLHASH_WA_SIZE_MAX)

#define MCUXCLRSA_MGF1_WAPKC_SIZE(inputLen, hashLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(inputLen + 4U + hashLen))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pssEncode function.       */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PSSENCODE_WA MCUXCLRSA_PSSENCODE_WA
 * @brief Workarea size macros of mcuxClRsa_pssEncode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PSSENCODE_WACPU_SIZE  \
    MCUXCLRSA_MAX(MCUXCLHASH_WA_SIZE_MAX, MCUXCLRSA_MGF1_WACPU_SIZE)

#define MCUXCLRSA_PSSENCODE_WAPKC_SIZE_WO_MGF1(hashLen, saltLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(MCUXCLRSA_PSS_PADDING1_LEN + hashLen + saltLen))

#define MCUXCLRSA_PSSENCODE_WAPKC_SIZE(hashLen, saltLen)  \
    (MCUXCLRSA_PSSENCODE_WAPKC_SIZE_WO_MGF1(hashLen, saltLen) \
     + MCUXCLRSA_MGF1_WAPKC_SIZE(hashLen, hashLen))

#define MCUXCLRSA_PSSENCODE_WAPKC_SIZE_WO_SALTLEN(hashLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(MCUXCLRSA_PSS_PADDING1_LEN + hashLen  /* + saltLen */) \
     + MCUXCLRSA_MGF1_WAPKC_SIZE(hashLen, hashLen))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pssVerify function.       */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PSSVERIFY_WA MCUXCLRSA_PSSVERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_pssVerify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PSSVERIFY_WACPU_SIZE  \
    MCUXCLRSA_MAX(MCUXCLHASH_WA_SIZE_MAX, MCUXCLRSA_MGF1_WACPU_SIZE)

#define MCUXCLRSA_PSSVERIFY_WAPKC_SIZE_WO_MGF1(keyByteLength, hashLen, saltLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(MCUXCLRSA_PSS_PADDING1_LEN + hashLen + saltLen \
                         + keyByteLength - 1U ))

#define MCUXCLRSA_PSSVERIFY_WAPKC_SIZE(keyByteLength, hashLen, saltLen)  \
    (MCUXCLRSA_PSSVERIFY_WAPKC_SIZE_WO_MGF1(keyByteLength, hashLen, saltLen) \
                         + MCUXCLRSA_MGF1_WAPKC_SIZE(hashLen, hashLen))

#define MCUXCLRSA_PSSVERIFY_WAPKC_SIZE_WO_SALTLEN(keyByteLength, hashLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(MCUXCLRSA_PSS_PADDING1_LEN + hashLen  /* + saltLen */ \
                         + keyByteLength - 1U ) \
                         + MCUXCLRSA_MGF1_WAPKC_SIZE(hashLen, hashLen))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pkcs1v15Encode function.  */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PKCS1V15ENCODE_WA MCUXCLRSA_PKCS1V15ENCODE_WA
 * @brief Workarea size macros of mcuxClRsa_pkcs1v15Encode.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PKCS1V15ENCODE_WACPU_SIZE  \
    MCUXCLHASH_WA_SIZE_MAX

#define MCUXCLRSA_PKCS1V15ENCODE_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_pkcs1v15Verify function.  */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_PKCS1V15VERIFY_WA MCUXCLRSA_PKCS1V15VERIFY_WA
 * @brief Workarea size macros of mcuxClRsa_pkcs1v15Verify.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_PKCS1V15VERIFY_WACPU_SIZE  \
    MCUXCLHASH_WA_SIZE_MAX

#define MCUXCLRSA_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength)) + \
    MCUXCLRSA_PKCS1V15ENCODE_WAPKC_SIZE(keyByteLength)

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
#define MCUXCLRSA_VERIFY_OPTION_NOVERIFY_WACPU_SIZE  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_NOVERIFY_WACPU_SIZE,  \
                  MCUXCLRSA_PUBLIC_WACPU_SIZE))

#define MCUXCLRSA_VERIFY_OPTION_PKCS1V15VERIFY_WACPU_SIZE  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PKCS1V15VERIFY_WACPU_SIZE,  \
                  MCUXCLRSA_PUBLIC_WACPU_SIZE))

#define MCUXCLRSA_VERIFY_OPTION_PSSVERIFY_WACPU_SIZE  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PSSVERIFY_WACPU_SIZE,  \
                  MCUXCLRSA_PUBLIC_WACPU_SIZE))

#define MCUXCLRSA_VERIFY_OPTION_NOVERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                  MCUXCLRSA_NOVERIFY_WAPKC_SIZE(keyByteLength)))

#define MCUXCLRSA_VERIFY_OPTION_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                  MCUXCLRSA_PKCS1V15VERIFY_WAPKC_SIZE(keyByteLength)))

#define MCUXCLRSA_VERIFY_OPTION_PSSVERIFY_WAPKC_SIZE(keyByteLength, hashLen, saltLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                  MCUXCLRSA_PSSVERIFY_WAPKC_SIZE(keyByteLength, hashLen, saltLen)))

#define MCUXCLRSA_VERIFY_OPTION_PSSVERIFY_WAPKC_SIZE_WO_SALTLEN(keyByteLength, hashLen)  \
    (MCUXCLPKC_ROUNDUP_SIZE(keyByteLength)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PUBLIC_WAPKC_SIZE(keyByteLength),  \
                  MCUXCLRSA_PSSVERIFY_WAPKC_SIZE_WO_SALTLEN(keyByteLength, hashLen)))

/** @} */

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_sign function.          */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_SIGN_WA MCUXCLRSA_SIGN_WA
 * @brief Workarea size macros of mcuxClRsa_sign.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_SIGN_PLAIN_OPTION_NOENCODE_WACPU_SIZE(keyByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_NOENCODE_WACPU_SIZE,  \
                  MCUXCLRSA_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)))

#define MCUXCLRSA_SIGN_PLAIN_OPTION_PKCS1V15ENCODE_WACPU_SIZE(keyByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PKCS1V15ENCODE_WACPU_SIZE,  \
                  MCUXCLRSA_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)))

#define MCUXCLRSA_SIGN_PLAIN_OPTION_PSSENCODE_WACPU_SIZE(keyByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PSSENCODE_WACPU_SIZE,  \
                  MCUXCLRSA_PRIVATEPLAIN_WACPU_SIZE(keyByteLength)))

#define MCUXCLRSA_SIGN_PLAIN_OPTION_NOENCODE_WAPKC_SIZE(keyByteLength)  \
   MCUXCLRSA_MAX(MCUXCLPKC_ROUNDUP_SIZE(keyByteLength) + MCUXCLRSA_NOENCODE_WAPKC_SIZE,  \
                  MCUXCLRSA_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength))

#define MCUXCLRSA_SIGN_PLAIN_OPTION_PSSENCODE_WAPKC_SIZE_WO_SALTLEN(keyByteLength, hashLen)  \
   MCUXCLRSA_MAX(MCUXCLPKC_ROUNDUP_SIZE(keyByteLength) + MCUXCLRSA_PSSENCODE_WAPKC_SIZE_WO_SALTLEN(hashLen),  \
                  MCUXCLRSA_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength))

#define MCUXCLRSA_SIGN_PLAIN_OPTION_PKCS1V15ENCODE_WAPKC_SIZE(keyByteLength)  \
   MCUXCLRSA_MAX(MCUXCLPKC_ROUNDUP_SIZE(keyByteLength) + MCUXCLRSA_PKCS1V15ENCODE_WAPKC_SIZE(keyByteLength),  \
                  MCUXCLRSA_PRIVATEPLAIN_WAPKC_SIZE(keyByteLength))

#define MCUXCLRSA_SIGN_CRT_OPTION_NOENCODE_WACPU_SIZE(primeByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_NOENCODE_WACPU_SIZE,  \
                  MCUXCLRSA_PRIVATECRT_WACPU_SIZE(primeByteLength)))

#define MCUXCLRSA_SIGN_CRT_OPTION_PKCS1V15ENCODE_WACPU_SIZE(primeByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PKCS1V15ENCODE_WACPU_SIZE,  \
                  MCUXCLRSA_PRIVATECRT_WACPU_SIZE(primeByteLength)))

#define MCUXCLRSA_SIGN_CRT_OPTION_PSSENCODE_WACPU_SIZE(primeByteLength)  \
    (sizeof(mcuxClPkc_State_t)  \
   + MCUXCLRSA_MAX(MCUXCLRSA_PSSENCODE_WACPU_SIZE,  \
                  MCUXCLRSA_PRIVATECRT_WACPU_SIZE(primeByteLength)))

#define MCUXCLRSA_SIGN_CRT_OPTION_NOENCODE_WAPKC_SIZE(primeByteLength)  \
   MCUXCLRSA_MAX(MCUXCLPKC_ROUNDUP_SIZE(2u * primeByteLength) + MCUXCLRSA_NOENCODE_WAPKC_SIZE,  \
                  MCUXCLRSA_PRIVATECRT_WAPKC_SIZE(primeByteLength))

#define MCUXCLRSA_SIGN_CRT_OPTION_PSSENCODE_WAPKC_SIZE_WO_SALTLEN(primeByteLength, hashLen)  \
   MCUXCLRSA_MAX(MCUXCLPKC_ROUNDUP_SIZE(2u * primeByteLength) + MCUXCLRSA_PSSENCODE_WAPKC_SIZE_WO_SALTLEN(hashLen),  \
                  MCUXCLRSA_PRIVATECRT_WAPKC_SIZE(primeByteLength))

#define MCUXCLRSA_SIGN_CRT_OPTION_PKCS1V15ENCODE_WAPKC_SIZE(primeByteLength)  \
   MCUXCLRSA_MAX(MCUXCLPKC_ROUNDUP_SIZE(2u * primeByteLength) + MCUXCLRSA_PKCS1V15ENCODE_WAPKC_SIZE(2u * primeByteLength),  \
                  MCUXCLRSA_PRIVATECRT_WAPKC_SIZE(primeByteLength))

/** @} */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_MEMORY_CONSUMPTION_H_ */
