/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClPrng_Internal_ELS.h
 * @brief Functionality required to draw pseudorandom data from ELS
 */


#ifndef MCUXCLPRNG_INTERNAL_ELS_H_
#define MCUXCLPRNG_INTERNAL_ELS_H_

#include <stdint.h>
#include <platform_specific_headers.h>
#include <internal/mcuxClEls_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Non-cryptographic PRNG data word generation function.
 *
 * This function returns a non-cryptographic random data word
 *
 * @return 32-bit random data
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPrng_generate_word)
static inline uint32_t mcuxClPrng_generate_word(void)
{
    return mcuxClEls_readPrngOut(); // read from PRNG SFR
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPRNG_INTERNAL_ELS_H_ */
