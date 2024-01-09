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

/** @file  mcuxClPrng_ELS.c
 *  @brief Implementation of the non-cryptographic PRNG functions using ELS. */

#include <internal/mcuxClPrng_Internal.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPrng_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPrng_Status_t) mcuxClPrng_init(
    void
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPrng_init);

#ifdef MCUXCL_FEATURE_ELS_PRND_INIT

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_Init, mcuxClEls_Prng_Init_Async());
    if(MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_Prng_Init)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_ERROR,
                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_Init_Async));
    }
    else if(MCUXCLELS_STATUS_OK_WAIT != ret_Prng_Init)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Wait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if(MCUXCLELS_LEVEL1_ERROR(ret_Wait))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_ERROR,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_Init_Async),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
    }
    else if (MCUXCLELS_STATUS_OK != ret_Wait)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_OK,
                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_Init_Async),
                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
    }

#else /* MCUXCL_FEATURE_ELS_PRND_INIT */

    /* Check whether the current security strength is sufficient. */
    mcuxClEls_HwState_t hwState = {0};

    MCUX_CSSL_FP_FUNCTION_CALL(ret_GetHwState, mcuxClEls_GetHwState(&hwState));
    if(MCUXCLELS_STATUS_OK != ret_GetHwState)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_FAULT_ATTACK);
    }

    /* If the security strength is already sufficient, finish here. */
    if((uint8_t)MCUXCLELS_STATUS_DRBGENTLVL_NONE != hwState.bits.drbgentlvl)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_OK,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState));
    }

    /**
     * If the current security strength is not sufficient, do the init procedure:
     * Loop through the key slots until an unused slot is found.
     * Delete that key in order to force PRNG initialization.
     */
    mcuxClEls_KeyProp_t keyProp = {0};
    uint32_t keyIdx = 0u;

    for(keyIdx = 0u; keyIdx < MCUXCLELS_KEY_SLOTS; keyIdx++)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ret_GetKeyProperties, mcuxClEls_GetKeyProperties(keyIdx, &keyProp));
        if(MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_GetKeyProperties)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_ERROR,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState),
                                        (keyIdx + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties));
        }
        else if(MCUXCLELS_STATUS_OK != ret_GetKeyProperties)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        if ((uint8_t)MCUXCLELS_KEYPROPERTY_ACTIVE_FALSE == keyProp.bits.kactv)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(ret_KeyDelete_Async, mcuxClEls_KeyDelete_Async(keyIdx));
            if(MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == ret_KeyDelete_Async)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_ERROR,
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState),
                                            (keyIdx + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties),
                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async));
            }
            else if(MCUXCLELS_STATUS_OK_WAIT != ret_KeyDelete_Async)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_FAULT_ATTACK);
            }
            else
            {
                /* Intentionally left empty */
            }

            MCUX_CSSL_FP_FUNCTION_CALL(ret_Wait2, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
            if(MCUXCLELS_LEVEL1_ERROR(ret_Wait2))
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_ERROR,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState),
                                                     (keyIdx + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
            }
            else if(MCUXCLELS_STATUS_OK != ret_Wait2)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_FAULT_ATTACK);
            }
            else
            {
                /* Assume PRNG is properly initialized. */
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_OK,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState),
                                                     (keyIdx + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
            }
        }
    }

    /* PRNG could not be properly initialized. No free key slot? */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_init, MCUXCLPRNG_STATUS_ERROR,
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwState),
                                MCUXCLELS_KEY_SLOTS * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties));

#endif /* MCUXCL_FEATURE_ELS_PRND_INIT */
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPrng_generate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPrng_Status_t) mcuxClPrng_generate(
    uint8_t *             pOut,
    uint32_t              outLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPrng_generate);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom, mcuxClEls_Prng_GetRandom(pOut, outLength));
    if(MCUXCLELS_STATUS_HW_PRNG == ret_Prng_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_generate, MCUXCLPRNG_STATUS_ERROR,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandom));        
    }
    else if (MCUXCLELS_STATUS_OK != ret_Prng_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_generate, MCUXCLPRNG_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPrng_generate, MCUXCLPRNG_STATUS_OK,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Prng_GetRandom));
    }
}
