/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_els_pkc_entropy.c
 *
 * This file contains the implementation of the entry points associated
 * to the entropy capability as described by the PSA Cryptoprocessor
 * Driver interface specification
 *
 */

#include "mbedtls/build_info.h"
#include "entropy_poll.h"

#if defined(MBEDTLS_MCUX_ENTROPY) && (MBEDTLS_MCUX_ENTROPY == 1)

#include "mcux_psa_els_pkc_entropy.h"
#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
#include "fsl_trng.h"
#define MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED
#endif

/* function initializes the rng*/
static status_t trigger_rng_init(void)
{
#if defined(MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED)
  
#if defined(TRNG)
#define TRNG0 TRNG
#endif
  status_t result;
  trng_config_t trngConfig;
  
  result = TRNG_GetDefaultConfig(&trngConfig);
  
  if(result == kStatus_Success)
  {
    /* Set sample mode of the TRNG ring oscillator to Von Neumann, for better random data.*/
    /* Initialize TRNG */
    result = TRNG_Init(TRNG0, &trngConfig);
  }
  
  return result;
#else
  return kStatus_Success;
#endif  
}
     
/** \defgroup psa_entropy PSA driver entry points for entropy collection
 *
 *  Entry points for entropy collection from the TRNG source as described by the
 *  PSA Cryptoprocessor Driver interface specification. The TRNG
 *  operates by sampling the output of a fast free-running ring oscillator in a
 *  different (slower) clock domain
 *
 *  @{
 */
psa_status_t els_pkc_get_entropy(uint32_t flags, size_t *estimate_bits,
                                 uint8_t *output, size_t output_size)
{
  status_t result              = kStatus_Success;
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
  
  if (output == NULL || estimate_bits == NULL || output_size == 0u) {
    status = PSA_ERROR_INVALID_ARGUMENT;
  }
  else
  {
    
    /*
    * The order of functions in psa_crypto_init() is not correct as
    * driver init is called after call to random number generator. To
    * avoid circular dependency add initialization here.
    */
    result = CRYPTO_InitHardware();
    if (result != kStatus_Success) {
      status = PSA_ERROR_GENERIC_ERROR;
    }
    else
    {
      
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
      if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        status = PSA_ERROR_GENERIC_ERROR;
      }
      else
      {
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
        
        /* Initialize trng */
        static bool rng_init_is_done = false;
        if(rng_init_is_done == false)
        {
          result = trigger_rng_init();
        }
        /* If trng init is a success, then proceed*/      
        if (result != kStatus_Success) {
          status = PSA_ERROR_GENERIC_ERROR;
        }
        else
        {
          /* update the variable for successful trng initialization */
          rng_init_is_done = true;
          
#if defined(MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED)
#ifndef TRNG0
#define TRNG0 TRNG
#endif
          
          /* Get random data from trng driver*/
          result = TRNG_GetRandomData(TRNG0, output, output_size);
#else
          /* Call ELS to get random data */
          MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(els_result, token, mcuxClEls_Prng_GetRandom(output, output_size));
          if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandom) != token) || (MCUXCLELS_STATUS_OK != els_result))
          {
            result = kStatus_Fail;
          }
          MCUX_CSSL_FP_FUNCTION_CALL_END();
#endif
          
          if (result == kStatus_Success)
          {
            *estimate_bits = output_size;
            status = PSA_SUCCESS;
          }
          else
          {
            status = PSA_ERROR_GENERIC_ERROR;
          }
        }
        
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
      }
      if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        status = PSA_ERROR_GENERIC_ERROR;
      }
#endif
    }
  }
  
  return status;
}
/** @} */ // end of psa_entropy

/*
 * FixMe: This function is required to integrate into Mbed TLS as the PSA
 * subsystem does not yet support entropy entry points. See the header
 * entropy_poll.h for details. This needs to be revised once Mbed TLS adds
 * support for entropy.
 */
int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{

    int status = els_pkc_get_entropy(0, olen, output, len);
    return status;
}
#endif /* MBEDTLS_MCUX_ENTROPY */