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
 * @file  mcuxClRandomModes_CtrDrbg_AES256_ELS_example.c
 * @brief Example for the mcuxClRandomModes component
 *
 * @example mcuxClRandomModes_CtrDrbg_AES256_ELS_example.c
 * @brief   Example for the mcuxClRandomModes component
 */

#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h> // Defines and assertions for examples
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>


/** Performs an example usage of the mcuxClRandom and mcuxClRandomModes components with ELS mode.
 * @retval true  The example code completed successfully
 * @retval false The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRandomModes_CtrDrbg_AES256_ELS_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    //Allocate and initialize session
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE, 0u);

    /* selftest */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(selftestresult, token, mcuxClRandom_selftest(
                                                  session,
                                                  mcuxClRandomModes_Mode_CtrDrbg_AES256));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_selftest) != token) || (MCUXCLRANDOM_STATUS_OK != selftestresult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    uint32_t context[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0};

    /**************************************************************************/
    /* Random init                                                            */
    /**************************************************************************/

    /* Initialize the Random session with aes256 mode. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomInitresult, token, mcuxClRandom_init(
                                                  session,
                                                  (mcuxClRandom_Context_t)context,
                                                  mcuxClRandomModes_Mode_CtrDrbg_AES256));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != token) || (MCUXCLRANDOM_STATUS_OK != randomInitresult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate random values.                                                */
    /**************************************************************************/

    /* Buffers to store the generated random values in. */
    uint8_t drbg_buffer1[3u];
    uint8_t drbg_buffer2[4u];
    uint8_t drbg_buffer3[5u];


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

    /* reseed */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(randomReseedresult, token, mcuxClRandom_reseed(
                                                  session));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_reseed) != token) || (MCUXCLRANDOM_STATUS_OK != randomReseedresult))
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
