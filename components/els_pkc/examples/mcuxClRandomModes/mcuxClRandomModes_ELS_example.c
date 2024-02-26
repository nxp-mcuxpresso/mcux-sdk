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

/**
 * @file  mcuxClRandomModes_ELS_example.c
 * @brief Example for the mcuxClRandomModes component
 *
 * @example mcuxClRandomModes_ELS_example.c
 * @brief   Example for the mcuxClRandomModes component
 */

#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h> // Defines and assertions for examples
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>

/** Performs an example usage of the mcuxClRandom and mcuxClRandomModes components with ELS mode.
 * @retval true  The example code completed successfully
 * @retval false The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRandomModes_ELS_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Buffers to store the generated random values in. */
    uint8_t prng_buffer[10u];

    uint8_t drbg_buffer1[3u];
    uint8_t drbg_buffer2[4u];
    uint8_t drbg_buffer3[5u];

    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;
    //Allocate and initialize session
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, 0u, 0u);

    /* We don't need a context for ELS Rng. */
    mcuxClRandom_Context_t context = NULL;

    /**************************************************************************/
    /* Random init                                                            */
    /**************************************************************************/

    /* Initialize the Random session with ELS mode. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInitresult, token, mcuxClRandom_init(
                                                  session,
                                                  context,
                                                  mcuxClRandomModes_Mode_ELS_Drbg));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != token) || (MCUXCLRANDOM_STATUS_OK != randomInitresult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate random values.                                                */
    /**************************************************************************/

    /* Generate random values of smaller amount than one word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomGenerateresult1, token, mcuxClRandom_generate(
                                                  session,
                                                  drbg_buffer1,
                                                  sizeof(drbg_buffer1)));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != token) || (MCUXCLRANDOM_STATUS_OK != randomGenerateresult1))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values of multiple of word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomGenerateresult2, token, mcuxClRandom_generate(
                                                  session,
                                                  drbg_buffer2,
                                                  sizeof(drbg_buffer2)));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != token) || (MCUXCLRANDOM_STATUS_OK != randomGenerateresult2))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values of larger amount than but not multiple of one word size. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomGenerateresult3, token, mcuxClRandom_generate(
                                                  session,
                                                  drbg_buffer3,
                                                  sizeof(drbg_buffer3)));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != token) || (MCUXCLRANDOM_STATUS_OK != randomGenerateresult3))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate non-cryptographic random values.                              */
    /**************************************************************************/

    /* Initialize non-cryptographic Rng. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomNcInitresult, token, mcuxClRandom_ncInit(session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncInit) != token) || (MCUXCLRANDOM_STATUS_OK != randomNcInitresult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomNcGenerateresult, token, mcuxClRandom_ncGenerate(
                                                  session,
                                                  prng_buffer,
                                                  sizeof(prng_buffer)));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate) != token) || (MCUXCLRANDOM_STATUS_OK != randomNcGenerateresult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Cleanup                                                                */
    /**************************************************************************/

    /* Random uninit. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomUninitresult, token, mcuxClRandom_uninit(session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_uninit) != token) || (MCUXCLRANDOM_STATUS_OK != randomUninitresult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(session))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
