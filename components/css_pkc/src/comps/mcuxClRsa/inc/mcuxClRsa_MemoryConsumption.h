/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClRsa_MemoryConsumption.h
 * @brief Defines the memory consumption for the mcuxClRsa component 
 */

#ifndef MCUXCLRSA_MEMORYCONSUMPTION_H_
#define MCUXCLRSA_MEMORYCONSUMPTION_H_

/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_sign function.            */
/****************************************************************************/

/**
 * @defgroup MCUXCLRSA_SIGN_WA MCUXCLRSA_SIGN_WA
 * @brief Definitions of workarea sizes for the mcuxClRsa_sign function.
 * @ingroup mcuxClRsa_Macros
 * @{
 */
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_1024_WACPU_SIZE    (148u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_2048_WACPU_SIZE    (276u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_3072_WACPU_SIZE    (404u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_4096_WACPU_SIZE    (532u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_WACPU_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_4096_WACPU_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_3072_WACPU_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_2048_WACPU_SIZE : \
		                             MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_1024_WACPU_SIZE)))  ///< Macro to extract CPU workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_1024_WAPKC_SIZE     (976u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_2048_WAPKC_SIZE     (1872u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_3072_WAPKC_SIZE     (2768u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_4096_WAPKC_SIZE     (3664u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_NoEncode.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_WAPKC_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_4096_WAPKC_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_3072_WAPKC_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_2048_WAPKC_SIZE : \
		                             MCUXCLRSA_SIGN_PLAIN_OPTIONNOENCODE_1024_WAPKC_SIZE)))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_1024_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_2048_WACPU_SIZE    (276u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_3072_WACPU_SIZE    (404u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_4096_WACPU_SIZE    (532u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_WACPU_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_4096_WACPU_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_3072_WACPU_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_2048_WACPU_SIZE : \
		                             MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_1024_WACPU_SIZE)))  ///< Macro to extract CPU workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_1024_WAPKC_SIZE(saltLen)     (976u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_2048_WAPKC_SIZE(saltLen)     (1872u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_3072_WAPKC_SIZE(saltLen)     (2768u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_4096_WAPKC_SIZE(saltLen)     (3664u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA224_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_1024_WAPKC_SIZE(saltLen)     (976u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_2048_WAPKC_SIZE(saltLen)     (1872u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_3072_WAPKC_SIZE(saltLen)     (2768u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_4096_WAPKC_SIZE(saltLen)     (3664u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA256_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_1024_WAPKC_SIZE(saltLen)     (976u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_2048_WAPKC_SIZE(saltLen)     (1872u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_3072_WAPKC_SIZE(saltLen)     (2768u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_4096_WAPKC_SIZE(saltLen)     (3664u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA384_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_1024_WAPKC_SIZE(saltLen)     (976u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_2048_WAPKC_SIZE(saltLen)     (1872u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_3072_WAPKC_SIZE(saltLen)     (2768u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_4096_WAPKC_SIZE(saltLen)     (3664u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_PLAIN_OPTIONPSSENCODE_SHA512_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.
		                             
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_1024_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_2048_WACPU_SIZE    (276u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_3072_WACPU_SIZE    (404u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_4096_WACPU_SIZE    (532u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_WACPU_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_4096_WACPU_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_3072_WACPU_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_2048_WACPU_SIZE : \
		                             MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_1024_WACPU_SIZE)))  ///< Macro to extract CPU workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_1024_WAPKC_SIZE     (976u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 1024-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_2048_WAPKC_SIZE     (1872u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 2048-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_3072_WAPKC_SIZE     (2768u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 3072-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.
#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_4096_WAPKC_SIZE     (3664u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function for 4096-bit private plain keys using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*.

#define MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_WAPKC_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_4096_WAPKC_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_3072_WAPKC_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_2048_WAPKC_SIZE : \
		                             MCUXCLRSA_SIGN_PLAIN_OPTIONPKCS1V15ENCODE_1024_WAPKC_SIZE)))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATEPLAIN.

#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_512_WACPU_SIZE    (104u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1024_WACPU_SIZE    (168u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1536_WACPU_SIZE    (232u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_2048_WACPU_SIZE    (296u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_WACPU_SIZE(keyBitLength) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_2048_WACPU_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1536_WACPU_SIZE : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1024_WACPU_SIZE : \
		                             MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_512_WACPU_SIZE)))  ///< Macro to extract CPU workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_512_WAPKC_SIZE     (968u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1024_WAPKC_SIZE     (1864u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1536_WAPKC_SIZE     (2760u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_2048_WAPKC_SIZE     (3656u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_NoEncode, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_WAPKC_SIZE(keyBitLength) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_2048_WAPKC_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1536_WAPKC_SIZE : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_1024_WAPKC_SIZE : \
		                             MCUXCLRSA_SIGN_CRT_OPTIONNOENCODE_512_WAPKC_SIZE)))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_512_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_1024_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_1536_WACPU_SIZE    (232u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_2048_WACPU_SIZE    (296u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_*, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_WACPU_SIZE(keyBitLength) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_2048_WACPU_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_1536_WACPU_SIZE : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_1024_WACPU_SIZE : \
		                             MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_512_WACPU_SIZE)))  ///< Macro to extract CPU workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_512_WAPKC_SIZE(saltLen)     (968u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_1024_WAPKC_SIZE(saltLen)     (1864u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_1536_WAPKC_SIZE(saltLen)     (2760u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_2048_WAPKC_SIZE(saltLen)     (3656u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_224, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_WAPKC_SIZE(keyBitLength, saltLen) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_2048_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_1536_WAPKC_SIZE(saltLen) : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_1024_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA224_512_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_512_WAPKC_SIZE(saltLen)     (968u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_1024_WAPKC_SIZE(saltLen)     (1864u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_1536_WAPKC_SIZE(saltLen)     (2760u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_2048_WAPKC_SIZE(saltLen)     (3656u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_256, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_WAPKC_SIZE(keyBitLength, saltLen) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_2048_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_1536_WAPKC_SIZE(saltLen) : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_1024_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA256_512_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_512_WAPKC_SIZE(saltLen)     (968u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_1024_WAPKC_SIZE(saltLen)     (1864u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_1536_WAPKC_SIZE(saltLen)     (2760u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_2048_WAPKC_SIZE(saltLen)     (3656u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_384, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_WAPKC_SIZE(keyBitLength, saltLen) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_2048_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_1536_WAPKC_SIZE(saltLen) : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_1024_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA384_512_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_512_WAPKC_SIZE(saltLen)     (968u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_1024_WAPKC_SIZE(saltLen)     (1864u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_1536_WAPKC_SIZE(saltLen)     (2760u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_2048_WAPKC_SIZE(saltLen)     (3656u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_Pss_Sha2_512, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_WAPKC_SIZE(keyBitLength, saltLen) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_2048_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_1536_WAPKC_SIZE(saltLen) : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_1024_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_SIGN_CRT_OPTIONPSSENCODE_SHA512_512_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_512_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1024_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1536_WACPU_SIZE    (232u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_2048_WACPU_SIZE    (296u) ///< Definition of CPU workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_WACPU_SIZE(keyBitLength) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_2048_WACPU_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1536_WACPU_SIZE : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1024_WACPU_SIZE : \
		                             MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_512_WACPU_SIZE)))  ///< Macro to extract CPU workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.

#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_512_WAPKC_SIZE     (968u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 512-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1024_WAPKC_SIZE     (1864u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 1024-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1536_WAPKC_SIZE     (2760u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 1536-bit primes p,q.
#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_2048_WAPKC_SIZE     (3656u) ///< Definition of PKC workarea size for the mcuxClRsa_sign function using mode mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_*, for CRT keys with 2048-bit primes p,q.

#define MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_WAPKC_SIZE(keyBitLength) \
		((1536u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_2048_WAPKC_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1536_WAPKC_SIZE : \
		((512u < (keyBitLength)) ? MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_1024_WAPKC_SIZE : \
		                             MCUXCLRSA_SIGN_CRT_OPTIONPKCS1V15ENCODE_512_WAPKC_SIZE)))  ///< Macro to extract PKC workarea size to be used with a non-standard key length, with a key of type MCUXCLRSA_KEY_PRIVATECRT or MCUXCLRSA_KEY_PRIVATECRT_DFA.
/** @} */


/****************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_verify function.          */
/****************************************************************************/
/**
 * @defgroup MCUXCLRSA_VERIFY_WA MCUXCLRSA_VERIFY_WA
 * @brief Definitions of workarea sizes for the mcuxClRsa_verify function.
 * @ingroup mcuxClRsa_Macros
 * @{
 */
#define MCUXCLRSA_VERIFY_OPTIONNOVERIFY_WACPU_SIZE    (16u) ///< Definition of CPU workarea size for the mcuxClRsa_verify function using mode mcuxClRsa_Mode_Verify_NoVerify.

#define MCUXCLRSA_VERIFY_OPTIONNOVERIFY_1024_WAPKC_SIZE     (800u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 1024-bit keys using mode mcuxClRsa_Mode_Verify_NoVerify.
#define MCUXCLRSA_VERIFY_OPTIONNOVERIFY_2048_WAPKC_SIZE     (1568u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 2048-bit keys using mode mcuxClRsa_Mode_Verify_NoVerify.
#define MCUXCLRSA_VERIFY_OPTIONNOVERIFY_3072_WAPKC_SIZE     (2336u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 3072-bit keys using mode mcuxClRsa_Mode_Verify_NoVerify.
#define MCUXCLRSA_VERIFY_OPTIONNOVERIFY_4096_WAPKC_SIZE     (3104u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 4096-bit keys using mode mcuxClRsa_Mode_Verify_NoVerify.

#define MCUXCLRSA_VERIFY_OPTIONNOVERIFY_WAPKC_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONNOVERIFY_4096_WAPKC_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONNOVERIFY_3072_WAPKC_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONNOVERIFY_2048_WAPKC_SIZE : \
		                             MCUXCLRSA_VERIFY_OPTIONNOVERIFY_1024_WAPKC_SIZE)))  ///< Macro to extract PKC workarea size to be used with a non-standard key length.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_verify function using mode mcuxClRsa_Mode_Verify_PssVerify.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_1024_WAPKC_SIZE(saltLen)     (800u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 1024-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_224.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_2048_WAPKC_SIZE(saltLen)     (1568u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 2048-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_224.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_3072_WAPKC_SIZE(saltLen)     (2336u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 3072-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_224.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_4096_WAPKC_SIZE(saltLen)     (3104u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 4096-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_224.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA224_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_1024_WAPKC_SIZE(saltLen)     (800u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 1024-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_256.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_2048_WAPKC_SIZE(saltLen)     (1568u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 2048-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_256.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_3072_WAPKC_SIZE(saltLen)     (2336u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 3072-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_256.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_4096_WAPKC_SIZE(saltLen)     (3104u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 4096-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_256.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA256_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_1024_WAPKC_SIZE(saltLen)     (800u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 1024-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_384.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_2048_WAPKC_SIZE(saltLen)     (1568u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 2048-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_384.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_3072_WAPKC_SIZE(saltLen)     (2336u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 3072-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_384.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_4096_WAPKC_SIZE(saltLen)     (3104u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 4096-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_384.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA384_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_1024_WAPKC_SIZE(saltLen)     (800u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 1024-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_512.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_2048_WAPKC_SIZE(saltLen)     (1568u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 2048-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_512.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_3072_WAPKC_SIZE(saltLen)     (2336u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 3072-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_512.
#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_4096_WAPKC_SIZE(saltLen)     (3104u) + (saltLen) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 4096-bit keys using mode mcuxClRsa_Mode_Verify_Pss_Sha2_512.

#define MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_WAPKC_SIZE(keyBitLength, saltLen) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_4096_WAPKC_SIZE(saltLen) : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_3072_WAPKC_SIZE(saltLen) : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_2048_WAPKC_SIZE(saltLen) : \
		                            MCUXCLRSA_VERIFY_OPTIONPSSVERIFY_SHA512_1024_WAPKC_SIZE(saltLen))))  ///< Macro to extract PKC workarea size to be used with a non-standard key length.

#define MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_WACPU_SIZE    (196u) ///< Definition of CPU workarea size for the mcuxClRsa_verify function using mode mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_*.

#define MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_1024_WAPKC_SIZE     (800u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 1024-bit keys using mode mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_*.
#define MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_2048_WAPKC_SIZE     (1568u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 2048-bit keys using mode mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_*.
#define MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_3072_WAPKC_SIZE     (2336u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 3072-bit keys using mode mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_*.
#define MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_4096_WAPKC_SIZE     (3104u) ///< Definition of PKC workarea size for the mcuxClRsa_verify function for 4096-bit keys using mode mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_*.

#define MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_WAPKC_SIZE(keyBitLength) \
		((3072u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_4096_WAPKC_SIZE : \
		((2048u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_3072_WAPKC_SIZE : \
		((1024u < (keyBitLength)) ? MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_2048_WAPKC_SIZE : \
		                             MCUXCLRSA_VERIFY_OPTIONPKCS1V15VERIFY_1024_WAPKC_SIZE)))  ///< Macro to extract PKC workarea size to be used with a non-standard key length.
/** @} */

#ifdef MCUXCL_FEATURE_RSA_KEYGENERATION

/**********************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_KeyGeneration_Crt function.     */
/**********************************************************************************/
/**
 * @defgroup MCUXCLRSA_KEYGENERATON_CRT_WA MCUXCLRSA_KEYGENERATON_CRT_WA
 * @brief Definitions of workarea sizes for the mcuxClRsa_KeyGeneration_Crt function.
 * @ingroup mcuxClRsa_Macros
 * @{
 */
#define MCUXCLRSA_KEYGENERATON_CRT_2048_WACPU_SIZE    (0u) ///< Definition of CPU workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Crt function for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_CRT_3072_WACPU_SIZE    (0u) ///< Definition of CPU workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Crt function for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_CRT_4096_WACPU_SIZE    (0u) ///< Definition of CPU workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Crt function for 4096-bit keys

#define MCUXCLRSA_KEYGENERATON_CRT_WACPU_SIZE(keyBitLength) \
    ((3072u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_CRT_4096_WACPU_SIZE : \
    ((2048u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_CRT_3072_WACPU_SIZE : \
                                MCUXCLRSA_KEYGENERATON_CRT_2048_WACPU_SIZE))  ///< Macro to extract CPU workarea size for the given key length.


#define MCUXCLRSA_KEYGENERATON_CRT_2048_WAPKC_SIZE    (0u) ///< Definition of PKC workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Crt function for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_CRT_3072_WAPKC_SIZE    (0u) ///< Definition of PKC workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Crt function for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_CRT_4096_WAPKC_SIZE    (0u) ///< Definition of PKC workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Crt function for 4096-bit keys

#define MCUXCLRSA_KEYGENERATON_CRT_WAPKC_SIZE(keyBitLength) \
    ((3072u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_CRT_4096_WAPKC_SIZE : \
    ((2048u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_CRT_3072_WAPKC_SIZE : \
                                MCUXCLRSA_KEYGENERATON_CRT_2048_WAPKC_SIZE))  ///< Macro to extract PKC workarea size (in bytes) for the given key length.

/** @} */

/********************************************************************************/
/* Definitions of workarea sizes for the mcuxClRsa_KeyGeneration_Plain function. */
/********************************************************************************/
/**
 * @defgroup MCUXCLRSA_KEYGENERATON_PLAIN_WA MCUXCLRSA_KEYGENERATON_PLAIN_WA
 * @brief Definitions of workarea sizes for the mcuxClRsa_KeyGeneration_Plain function.
 * @ingroup mcuxClRsa_Macros
 * @{
 */
#define MCUXCLRSA_KEYGENERATON_PLAIN_2048_WACPU_SIZE    (0u) ///< Definition of CPU workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Plain function for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_PLAIN_3072_WACPU_SIZE    (0u) ///< Definition of CPU workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Plain function for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_PLAIN_4096_WACPU_SIZE    (0u) ///< Definition of CPU workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Plain function for 4096-bit keys

#define MCUXCLRSA_KEYGENERATON_PLAIN_WACPU_SIZE(keyBitLength) \
    ((3072u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_PLAIN_4096_WACPU_SIZE : \
    ((2048u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_PLAIN_3072_WACPU_SIZE : \
                                MCUXCLRSA_KEYGENERATON_PLAIN_2048_WACPU_SIZE))  ///< Macro to extract CPU workarea size for the given key length.


#define MCUXCLRSA_KEYGENERATON_PLAIN_2048_WAPKC_SIZE    (0u) ///< Definition of PKC workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Plain function for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_PLAIN_3072_WAPKC_SIZE    (0u) ///< Definition of PKC workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Plain function for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_PLAIN_4096_WAPKC_SIZE    (0u) ///< Definition of PKC workarea size (in bytes) for the mcuxClRsa_KeyGeneration_Plain function for 4096-bit keys

#define MCUXCLRSA_KEYGENERATON_PLAIN_WAPKC_SIZE(keyBitLength) \
    ((3072u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_PLAIN_4096_WAPKC_SIZE : \
    ((2048u < (keyBitLength)) ? MCUXCLRSA_KEYGENERATON_PLAIN_3072_WAPKC_SIZE : \
                                MCUXCLRSA_KEYGENERATON_PLAIN_2048_WAPKC_SIZE))  ///< Macro to extract PKC workarea size for the given key length.

/** @} */

/*************************************************************************************************************************/
/* Definitions of generated key data size for the mcuxClRsa_KeyGeneration_Crt and mcuxClRsa_KeyGeneration_Plain functions. */
/*************************************************************************************************************************/
/**
 * @defgroup MCUXCLRSA_KEYGENERATON_KEY_DATA_SIZE MCUXCLRSA_KEYGENERATON_KEY_DATA_SIZE
 * @brief Definitions of bufer sizes for the mcuxClRsa_KeyGeneration_Crt and mcuxClRsa_KeyGeneration_Plain functions.
 * @ingroup mcuxClRsa_Macros
 * @{
 */
#define MCUXCLRSA_KEYGENERATON_PLAIN_KEY_DATA_2048_SIZE     ($(mcuxClRsa_KeyGeneration_Plain_2048)u)  ///< Definition of bufer size (in bytes) for the private plain key data for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_PLAIN_KEY_DATA_3072_SIZE     ($(mcuxClRsa_KeyGeneration_Plain_3072)u)  ///< Definition of bufer size (in bytes) for the private plain key data for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_PLAIN_KEY_DATA_4096_SIZE     ($(mcuxClRsa_KeyGeneration_Plain_4096)u)  ///< Definition of bufer size (in bytes) for the private plain key data for 4096-bit keys

#define MCUXCLRSA_KEYGENERATON_PRIVATECRT_KEY_DATA_2048_SIZE       ($(mcuxClRsa_KeyGeneration_PrivateCRT_2048)u)  ///< Definition of bufer size (in bytes) for the private CRT key data for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_PRIVATECRT_KEY_DATA_3072_SIZE       ($(mcuxClRsa_KeyGeneration_PrivateCRT_3072)u)  ///< Definition of bufer size (in bytes) for the private CRT key data for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_PRIVATECRT_KEY_DATA_4096_SIZE       ($(mcuxClRsa_KeyGeneration_PrivateCRT_4096)u)  ///< Definition of bufer size (in bytes) for the private CRT key data for 4096-bit keys

#define MCUXCLRSA_KEYGENERATON_PUBLIC_KEY_DATA_2048_SIZE           ($(mcuxClRsa_KeyGeneration_Public_2048)u)  ///< Definition of bufer size (in bytes) for the public key data for 2048-bit keys
#define MCUXCLRSA_KEYGENERATON_PUBLIC_KEY_DATA_3072_SIZE           ($(mcuxClRsa_KeyGeneration_Public_3072)u)  ///< Definition of bufer size (in bytes) for the public key data for 3072-bit keys
#define MCUXCLRSA_KEYGENERATON_PUBLIC_KEY_DATA_4096_SIZE           ($(mcuxClRsa_KeyGeneration_Public_4096)u)  ///< Definition of bufer size (in bytes) for the public key data for 4096-bit keys


/** @} */

#endif /* MCUXCL_FEATURE_RSA_KEYGENERATION */

#endif /* MCUXCLRSA_MEMORYCONSUMPTION_H_ */
