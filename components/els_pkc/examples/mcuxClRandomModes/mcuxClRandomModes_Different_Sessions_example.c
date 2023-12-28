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
 * @file  mcuxClRandomModes_Different_Sessions_example.c
 * @brief Example for the mcuxClRandomModes component
 *
 * @example mcuxClRandomModes_Different_Sessions_example.c
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

/** Performs an example usage of the mcuxClRandom and mcuxClRandomModes components
 * @retval true  The example code completed successfully
 * @retval false The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRandomModes_Different_Sessions_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    uint32_t context[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0};
    mcuxClRandom_Mode_t mcuxClRandomModes_Mode = mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG3 ;

    /* Buffers to store the generated random values in. */
    uint8_t drbg_buffer1[3u];
    uint8_t drbg_buffer2[16u];
    uint8_t drbg_buffer3[31u];

    { /* session_0 Scope */
        mcuxClSession_Descriptor_t sessionDesc_0;
        mcuxClSession_Handle_t session_0 = &sessionDesc_0;
        MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session_0, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE, 0u);

        /**************************************************************************/
        /* DRBG selftest.                                                         */
        /**************************************************************************/
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rs_status, selftest_token, mcuxClRandom_selftest(
                                            session_0,
                                            mcuxClRandomModes_Mode
                                       ));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_selftest) != selftest_token) || (MCUXCLRANDOM_STATUS_OK != rs_status))
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /**************************************************************************/
        /* DRBG initialization                                                    */
        /**************************************************************************/

        /* Initialize an AES-128 CTR_DRBG DRG.3 */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ri_status, init_token, mcuxClRandom_init(
                                            session_0,
                                            (mcuxClRandom_Context_t)context,
                                            mcuxClRandomModes_Mode
                                       ));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != init_token) || (MCUXCLRANDOM_STATUS_OK != ri_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /**************************************************************************/
        /* Generate several random byte strings and reseed the DRBG in between.   */
        /**************************************************************************/

        /* Generate random values of smaller amount than one word size. */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg1_status, generate1_token, mcuxClRandom_generate(
                                            session_0,
                                            drbg_buffer1,
                                            sizeof(drbg_buffer1)));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate1_token) || (MCUXCLRANDOM_STATUS_OK != rg1_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /** Destroy session_0 and cleanup session_0 **/
        if(!mcuxClExample_Session_Clean(session_0))
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    { /* session_1 Scope */
        mcuxClSession_Descriptor_t sessionDesc_1;
        mcuxClSession_Handle_t session_1 = &sessionDesc_1;
        mcuxClRandom_Context_t pContext = (mcuxClRandom_Context_t)&context;
        MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session_1, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE, 0u);

        /*  Set random context that was previously assigned to session_0 */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(setRandom_status, setRandom_token, mcuxClSession_setRandom(
                                        session_1,
                                        mcuxClRandomModes_Mode,
                                        pContext));


        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_setRandom) != setRandom_token) || (MCUXCLSESSION_STATUS_OK != setRandom_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Generate random values of multiple of word size. */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg2_status, generate2_token, mcuxClRandom_generate(
                                            session_1,
                                            drbg_buffer2,
                                            sizeof(drbg_buffer2)));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate2_token) || (MCUXCLRANDOM_STATUS_OK != rg2_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Reseed */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rr_status, reseed_token, mcuxClRandom_reseed(session_1));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_reseed) != reseed_token) || (MCUXCLRANDOM_STATUS_OK != rr_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Generate random values of larger amount than but not multiple of one word size. */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg3_status, generate3_token, mcuxClRandom_generate(
                                            session_1,
                                            drbg_buffer3,
                                            sizeof(drbg_buffer3)));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate3_token) || (MCUXCLRANDOM_STATUS_OK != rg3_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /**************************************************************************/
        /* Cleanup                                                                */
        /**************************************************************************/

        /* Random uninit. */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ru_status, uninit_token, mcuxClRandom_uninit(session_1));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_uninit) != uninit_token) || (MCUXCLRANDOM_STATUS_OK != ru_status))
        {
          return MCUXCLEXAMPLE_STATUS_ERROR;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /** Destroy session_1 and cleanup session_1 **/
        if(!mcuxClExample_Session_Clean(session_1))
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }
    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
