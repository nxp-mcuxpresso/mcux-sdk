/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClRandom_PRNG.c
 *  @brief Implementation of the non-cryptographic PRNG functions. */

#include <mcuxClToolchain.h>
#include <mcuxClSession.h>
#include <mcuxClRandom.h>
#include <internal/mcuxClPrng_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_ncInit)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_ncInit(
    mcuxClSession_Handle_t pSession UNUSED_PARAM
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandom_ncInit);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_Init, mcuxClPrng_init());
    if(MCUXCLPRNG_STATUS_ERROR == ret_Prng_Init)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandom_ncInit, MCUXCLRANDOM_STATUS_ERROR, MCUXCLRANDOM_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_init));
    }
    else if(MCUXCLPRNG_STATUS_OK != ret_Prng_Init)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_ncInit, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandom_ncInit, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_init));
    }
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_ncGenerate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_ncGenerate(
    mcuxClSession_Handle_t pSession UNUSED_PARAM,
    uint8_t *             pOut,
    uint32_t              outLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandom_ncGenerate);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom, mcuxClPrng_generate(pOut, outLength));
    if(MCUXCLPRNG_STATUS_ERROR == ret_Prng_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandom_ncGenerate, MCUXCLRANDOM_STATUS_ERROR, MCUXCLRANDOM_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_generate));
    }
    else if(MCUXCLPRNG_STATUS_OK != ret_Prng_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_ncGenerate, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandom_ncGenerate, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_generate));
    }
}
