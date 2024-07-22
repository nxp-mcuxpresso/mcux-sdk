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

/** @file  mcuxClTrng_Internal_SA_TRNG.h
 *  @brief Provide macros for mcuxClTrng internal use.
 * This header declares internal macros to deduplicate code and support for internal use only. */

#ifndef MCUXCLTRNG_INTERNAL_SA_TRNG_H_
#define MCUXCLTRNG_INTERNAL_SA_TRNG_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>
#include <internal/mcuxClTrng_SfrAccess.h>
#include <internal/mcuxClTrng_Internal_Constants.h>

#define MCUXCLTRNG_ERROR_LIMIT                          (4u)
#define MCUXCLTRNG_SA_TRNG_HW_DUAL_OSCILLATOR_MODE      (1u)

#ifdef MCUXCL_FEATURE_TRNG_SA_TRNG_256
#define MCUXCLTRNG_SA_TRNG_NUMBEROFENTREGISTERS         (8u)
#else
#error "Build configuration issue: SA_TRNG component included but neither DTRNG_256 nor DTRNG_512 are defined"
#endif

#define  MCUXCLTRNG_SA_TRNG_WAITFORREADY(noOfTrngErrors)                                                 \
    do                                                                                                  \
    {                                                                                                   \
        /* Check whether a TRNG error occurred */                                                       \
        if (0u != (MCUXCLTRNG_SFR_BITREAD(MCTL, ERR)))                                                   \
        {                                                                                               \
            /* TRNG hardware error detected (ERR bit == 1): */                                          \
            /* Check how many errors occurred so far */                                                 \
            if (MCUXCLTRNG_ERROR_LIMIT >= (noOfTrngErrors))                                              \
            {                                                                                           \
                /* Increase TRNG error counter */                                                       \
                (noOfTrngErrors) += 1u;                                                                 \
                /* Write 1 to clear ERR flag. */                                                        \
                /* TODO: check behavior is correct */                                                   \
                MCUXCLTRNG_SFR_BITSET(MCTL, ERR);                                                        \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                /* Number of TRNG errors exceeded the limit, */                                         \
                /* trigger Fault Attack. */                                                             \
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClTrng_getEntropyInput, MCUXCLTRNG_STATUS_FAULT_ATTACK);    \
            }                                                                                           \
        }                                                                                               \
    } while(0u == (MCUXCLTRNG_SFR_BITREAD(MCTL, ENT_VAL)))                                               \

#endif /* MCUXCLTRNG_INTERNAL_SA_TRNG_H_ */
