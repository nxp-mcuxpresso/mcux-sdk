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

#ifndef MCUXCLEXAMPLE_RNG_HELPER_H_
#define MCUXCLEXAMPLE_RNG_HELPER_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

// always allocate a minimum size buffer to avoid issues
// The size is given in bytes and allocated in words
#define MCUXCLEXAMPLE_ALLOCATE_RNG_CTXT(rngCtxLength) (rngCtxLength?((rngCtxLength + sizeof(uint32_t) - 1u) / sizeof(uint32_t)):1u)  


/**
 * Random data generator and Non-cryptographic PRNG initialization function via mcuxClRandom_init and mcuxClRandom_ncInit.
 * [in]     pSession        Handle for the current CL session.
 * [in]     rngCtxLength    Size (in bytes) of the RNG context need to be allocated based on the mode.
 * [in]     mode            Mode of operation for random data generator.
 **/

#define MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_RNG(pSession, rngCtxLength, mode)                                               \
    uint32_t context[MCUXCLEXAMPLE_ALLOCATE_RNG_CTXT(rngCtxLength)] = {0};                                                    \
    mcuxClRandom_Context_t pRng_ctx = (mcuxClRandom_Context_t)context;                                                         \
                                                                                                                             \
    /* Initialize the RNG context */                                                                                         \
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInit_result, randomInit_token, mcuxClRandom_init(pSession,                          \
                                                                                          pRng_ctx,                          \
                                                                                          mode));                            \
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != randomInit_token) || (MCUXCLRANDOM_STATUS_OK != randomInit_result))  \
    {                                                                                                                        \
        return MCUXCLEXAMPLE_STATUS_ERROR;                                                                                    \
    }                                                                                                                        \
    MCUX_CSSL_FP_FUNCTION_CALL_END();                                                                                         \
    /* Initialize the PRNG */                                                                                                \
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(pSession));                          \
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))    \
    {                                                                                                                        \
        return MCUXCLEXAMPLE_STATUS_ERROR;                                                                                    \
    }                                                                                                                        \
    MCUX_CSSL_FP_FUNCTION_CALL_END();

#define MCUXCLEXAMPLE_INITIALIZE_PRNG(session)                                                                               \
    /* Initialize the PRNG */                                                                                               \
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(prngInit_result, prngInit_token, mcuxClRandom_ncInit(session));                          \
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != prngInit_token) || (MCUXCLRANDOM_STATUS_OK != prngInit_result))   \
    {                                                                                                                       \
        return MCUXCLEXAMPLE_STATUS_ERROR;                                                                                   \
    }                                                                                                                       \
    MCUX_CSSL_FP_FUNCTION_CALL_END();

#endif /* MCUXCLEXAMPLE_RNG_HELPER_H_ */
