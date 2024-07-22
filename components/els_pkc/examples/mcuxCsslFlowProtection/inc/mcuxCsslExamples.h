/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

#ifndef MCUX_CSSL_EXAMPLES_H_
#define MCUX_CSSL_EXAMPLES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define MCUX_CSSL_EX_FUNCTION(_name) bool _name(void)

#define MCUX_CSSL_EX_OK    true
#define MCUX_CSSL_EX_ERROR false

static inline bool mcuxCsslExamples_assertEqual(const uint8_t * const x, const uint8_t * const y, uint32_t length)
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

MCUX_CSSL_EX_FUNCTION(mcuxCsslFlowProtection_example);

#endif /* MCUX_CSSL_EXAMPLES_H_ */
