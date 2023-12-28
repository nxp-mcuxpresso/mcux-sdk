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
 * @file  mcuxClMath_Utils_Math.h
 * @brief platform independent abstraction over math related builtin functions
 */

#ifndef MCUXCLMATH_INTERNAL_UTILS_H_
#define MCUXCLMATH_INTERNAL_UTILS_H_

#include <mcuxClCore_Platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Count leading zeros of non-zero value.
 * If the value is 0, the result is undefined.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_CountLeadingZerosWord)
static inline uint32_t mcuxClMath_CountLeadingZerosWord(uint32_t value)
{
#ifdef __CLZ
	return __CLZ(value);
#else
    return (uint32_t)__builtin_clz(value);
#endif
}

/*
 * Count trailing zeros of non-zero value.
 * If the value is 0, the result is undefined.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_CountTrailingZeroesWord)
static inline uint32_t mcuxClMath_CountTrailingZeroesWord(uint32_t value)
{
#if defined(__CLZ) && defined(__RBIT)
  return  __CLZ(__RBIT(value));
#else
  uint32_t zeroes = 0u;
  uint32_t valueShifted = value;
  uint32_t lsb = valueShifted & 0x01u;
  while((lsb == 0u) && (zeroes < 32u) )
  {
    zeroes++;
    valueShifted >>= 1u;
    lsb = valueShifted & 0x01u;
  }
  return zeroes;
#endif
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*MCUXCLMATH_INTERNAL_UTILS_H_ */
