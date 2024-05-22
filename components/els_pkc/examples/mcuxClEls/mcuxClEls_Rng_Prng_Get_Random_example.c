/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022-2023 NXP                                            */
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
 * @file  mcuxClEls_Rng_Prng_Get_Random_example.c
 * @brief Example of getting a random number from PRNG of ELS (CLNS component mcuxClEls)
 *
 * @example mcuxClEls_Rng_Prng_Get_Random_example.c
 * @brief   Example of getting a random number from PRNG of ELS (CLNS component mcuxClEls)
 */

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_ELS_Key_Helper.h>

/** Uses random number from PRNG of ELS.
 * @retval MCUXCLEXAMPLE_STATUS_OK  The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClEls_Rng_Prng_Get_Random_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    // PRNG needs to be initialized; this can be done by calling mcuxClEls_KeyDelete_Async (delete any key slot, can be empty)
    /** deleted 18 keySlot **/
    if(!mcuxClExample_Els_KeyDelete(18))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    uint32_t dummy;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Prng_GetRandomWord(&dummy));
    // mcuxClEls_Prng_GetRandomWord is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandomWord) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_Prng_GetRandomWord operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    uint32_t random[16];  // buffers of 16 CPU words to be filled with random numbers from PRNG.

    // fill the buffer with random numbers from PRNG.
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Prng_GetRandom((uint8_t*) random, sizeof(random)));
    // mcuxClEls_Prng_GetRandom is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandom) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_Prng_GetRandom operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
