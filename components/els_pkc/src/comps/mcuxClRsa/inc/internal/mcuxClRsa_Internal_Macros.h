/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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
 * @file  mcuxClRsa_Internal_Macros.h
 * @brief Internal macros of the mcuxClRsa component
 */

#ifndef MCUXCLRSA_INTERNAL_MACROS_H_
#define MCUXCLRSA_INTERNAL_MACROS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup MCUXCLRSA_INTERNAL_DEFINES_ MCUXCLRSA_INTERNAL_DEFINES_
 * @brief Internal macros of the mcuxClRsa component.
 * @ingroup mcuxClRsa_Internal_Defines
 * @{
 */
#define MCUXCLRSA_PSS_PADDING1_LEN (8u)
    ///< Define for the PSS padding1 length.

#define MCUXCLRSA_HASH_MAX_SIZE (64u)
    ///< Defines the maximum sizes of the hash algorithms

#define MCUXCLRSA_MAX_MODLEN (512u)
/** @} */


/**
 * @defgroup MCUXCLRSA_INTERNAL_MACROS_ MCUXCLRSA_INTERNAL_MACROS_
 * @brief Internal macros of the mcuxClRsa component.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_MAX(value0, value1) \
    ((value0) > (value1) ? (value0) : (value1))
    ///< Macro computing the maximum value of value0 and value1.

#define MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(size) \
    ((((size) + sizeof(uint32_t) - 1U ) / (sizeof(uint32_t))) * (sizeof(uint32_t)))
    ///< Round up a size (in bytes) to a multiple of the CPU wordsize (4 bytes).

#define MCUXCLRSA_CALC_MODLEN_FROM_CRTKEY(pKey, keyBitLength) \
    do {  \
          uint32_t pBitLength = ((pKey)->pMod1->keyEntryLength - 1u) * 8u; /* Lengths without first byte */ \
          uint32_t qBitLength = ((pKey)->pMod2->keyEntryLength - 1u) * 8u; \
          uint8_t tmpByte = (uint8_t) (pKey)->pMod1->pKeyEntryData[0]; \
          while (tmpByte != 0u) /* Iterate through first byte of p and add to bit length */ \
          { \
            ++pBitLength; \
            tmpByte = (uint8_t) (tmpByte >> 1u); \
          } \
          tmpByte = (uint8_t) (pKey)->pMod2->pKeyEntryData[0]; \
          while (tmpByte != 0u) /* Iterate through first byte of q and add to bit length */  \
          { \
            ++qBitLength; \
            tmpByte = (uint8_t) (tmpByte >> 1u); \
          } \
          (keyBitLength) = (pBitLength + qBitLength); \
    } while(false)
    ///< Obtain bit-length of modulus by counting leading zeroes of P and Q (CRT key).
    ///< Note that the most significant byte of P and Q should be non-zero.

#define MCUXCLRSA_GET_MINIMUM_SECURITY_STRENGTH(keyBitLength) \
        (((keyBitLength) <= 2048u) ? 112u : \
        (((keyBitLength) <= 3072u) ? 128u : \
                                     152u))   ///< Macro to determine the minimal security strength that
                                              ///< needs to be provided by the RNG for RSA keys with
                                              ///< lengths from 2048 bits to 4096 bits.
                                              ///< Numbers taken from NIST SP 800-56B REV. 2, Table 2

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_MACROS_H_ */

