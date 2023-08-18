/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

#ifndef MCUXCLCORE_EXAMPLES_H_
#define MCUXCLCORE_EXAMPLES_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>

/**
 * \def MCUXCLEXAMPLE_FUNCTION
 * \brief Macro to indicate that the symbol is an example function.
 */
// TODO CLNS-3599: #define MCUXCLEXAMPLE_FUNCTION(_name) uint32_t _name(void)
#define MCUXCLEXAMPLE_FUNCTION(_name) bool _name(void)

/**
 * \def MCUXCLEXAMPLE_OK
 * \brief Example execution completed successfully.
 */
#define MCUXCLEXAMPLE_OK      true // TODO CLNS-3599: 0xC001C0DEu

/**
 * \def MCUXCLEXAMPLE_ERROR
 * \brief Example execution resulted in an unexpected error.
 */
#define MCUXCLEXAMPLE_ERROR   false // TODO CLNS-3599: 0xEEEEEEEEu

/**
 * \def MCUXCLEXAMPLE_FAILURE
 * \brief Example execution resulted in an expected failure.
 */
#define MCUXCLEXAMPLE_FAILURE  false // TODO CLNS-3599: 0xFFFFFFFFu

/**
 * \brief Macro to calculate the maximum of two values.
 */
#define MCUXCLEXAMPLE_MAX( x, y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )

/**
 * \brief Assert whether two buffers are equal.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCore_assertEqual)
static inline bool mcuxClCore_assertEqual(const uint8_t * const x, const uint8_t * const y, uint32_t length)
{
  for (uint32_t i = 0; i < length; ++i)
  {
    if (x[i] != y[i])
    {
      return false;
    }
  }

  return true;
}

#endif /* MCUXCLCORE_EXAMPLES_H_ */
