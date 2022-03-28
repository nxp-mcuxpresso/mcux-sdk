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
 * @file  mcuxClRsa_Internal_Macros.h
 * @brief Internal macros of the mcuxClRsa component
 */

#ifndef MCUXCLRSA_INTERNAL_MACROS_H_
#define MCUXCLRSA_INTERNAL_MACROS_H_

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

/** @} */

/**
 * @defgroup MCUXCLRSA_INTERNAL_MACROS_ MCUXCLRSA_INTERNAL_MACROS_
 * @brief Internal macros of the mcuxClRsa component.
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_MAX(value0, value1) \
    ((value0) > (value1) ? (value0) : (value1))

#define MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(size) \
    ((((size) + sizeof(uint32_t) - 1U ) / (sizeof(uint32_t))) * (sizeof(uint32_t)))

#define MCUXCLRSA_CALC_MODLEN_FROM_CRTKEY(pKey, keyBitLength) \
	do {  \
		  uint32_t pBitLength = ((pKey)->pMod1->keyEntryLength - 1u) * 8u; \
		  uint32_t qBitLength = ((pKey)->pMod2->keyEntryLength - 1u) * 8u; \
		  uint8_t tmpByte = (uint8_t) (pKey)->pMod1->pKeyEntryData[0]; \
		  while (tmpByte != 0u) \
		  { \
		    ++pBitLength; \
		    tmpByte = (uint8_t) (tmpByte >> 1u); \
		  } \
		  tmpByte = (uint8_t) (pKey)->pMod2->pKeyEntryData[0]; \
		  while (tmpByte != 0u)  \
		  { \
		    ++qBitLength; \
		    tmpByte = (uint8_t) (tmpByte >> 1u); \
		  } \
	      (keyBitLength) = (pBitLength + qBitLength); \
	} while(false)

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRSA_INTERNAL_MACROS_H_ */
