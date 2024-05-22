/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClPrng_Internal_Functions.h
 * @brief Top level APIs of mcuxClPrng component
 */

#ifndef MCUXCLPRNG_INTERNAL_FUNCTIONS_H_
#define MCUXCLPRNG_INTERNAL_FUNCTIONS_H_

#include <internal/mcuxClPrng_Internal_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* APIs of mcuxClPrng                                      */
/**********************************************************/
/**
 * @brief Non-cryptographic PRNG initialization function.
 *
 * This function performs the initialization of the non-cryptographic random number
 * generator.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPrng_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPrng_Status_t) mcuxClPrng_init(
  void
);

/**
 * @brief Non-cryptographic PRNG data generation function.
 *
 * This function generates non-cryptographic random data
 *
 * @param [out]    pOut      Buffer in which the generated random data must be
 *                           written.
 * @param [in]     outLength Number of random data bytes that must be written in the
 *                           @p pOut buffer.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPrng_generate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPrng_Status_t) mcuxClPrng_generate(
  uint8_t *             pOut,
  uint32_t              outLength
);


#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * @}
 */ /* mcuxClPrng_Internal_Functions */

#endif /* MCUXCLPRNG_INTERNAL_FUNCTIONS_H_ */
