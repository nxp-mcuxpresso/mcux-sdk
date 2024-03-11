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
#include <mcuxCsslDataIntegrity.h>
#include <mcuxClSession.h>
#include <mcuxClBuffer.h>
#include <mcuxClRandom.h>
#include <internal/mcuxClPrng_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClSession_Internal_EntryExit.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_ncPatch)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_ncPatch(
    mcuxClSession_Handle_t pSession,
    mcuxClRandom_CustomNcGenerateAlgorithm_t prngPatchFunction,
    void *pCustomPrngState
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_ncPatch, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomNcPatchParams, (uint32_t)pSession + (uint32_t) pCustomPrngState);

    /* Set the PRNG patch function to patch the PRNG */
    pSession->randomCfg.prngPatchFunction = prngPatchFunction;
    pSession->randomCfg.pCustomPrngState = pCustomPrngState;

    MCUX_CSSL_DI_RECORD(sumOfRandomNcPatchParams, (uint32_t)pSession + (uint32_t) pCustomPrngState);

    MCUXCLSESSION_EXIT(pSession, mcuxClRandom_ncPatch, diRefValue, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK)
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_ncInit)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_ncInit(
    mcuxClSession_Handle_t pSession
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_ncInit, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomNcInitParams, (uint32_t)pSession);

    /* Reset the PRNG patch function to un-patch the PRNG */
    pSession->randomCfg.prngPatchFunction = NULL;
    pSession->randomCfg.pCustomPrngState = NULL;

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_Init, mcuxClPrng_init());

    MCUX_CSSL_DI_RECORD(sumOfRandomNcInitParams, (uint32_t)pSession);

    if(MCUXCLPRNG_STATUS_ERROR == ret_Prng_Init)
    {
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_ncInit, diRefValue, MCUXCLRANDOM_STATUS_ERROR, MCUXCLRANDOM_STATUS_FAULT_ATTACK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_init))
    }
    else if(MCUXCLPRNG_STATUS_OK != ret_Prng_Init)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_ncInit, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_ncInit, diRefValue, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_init))
    }
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_ncGenerate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_ncGenerate(
    mcuxClSession_Handle_t pSession,
    mcuxCl_Buffer_t        pOut,
    uint32_t              outLength
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_ncGenerate, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomNcGenerateParams, (uint32_t)pSession + (uint32_t)pOut + outLength);

    if(NULL != pSession->randomCfg.prngPatchFunction)
    {
        mcuxClRandom_Status_t result_customAlg = pSession->randomCfg.prngPatchFunction(
                    pSession->randomCfg.pCustomPrngState,
                    pOut,
                    outLength);

        MCUX_CSSL_DI_RECORD(sumOfRandomNcGenerateParams, (uint32_t)pSession + (uint32_t)pOut + outLength);

        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_ncGenerate, diRefValue, result_customAlg, MCUXCLRANDOM_STATUS_FAULT_ATTACK)
    }
    /* Assume normal mode going forward. */

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng_GetRandom, mcuxClPrng_generate(pOut, outLength));

    MCUX_CSSL_DI_RECORD(sumOfRandomNcGenerateParams, (uint32_t)pSession + (uint32_t)pOut + outLength);

    if(MCUXCLPRNG_STATUS_ERROR == ret_Prng_GetRandom)
    {
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_ncGenerate, diRefValue, MCUXCLRANDOM_STATUS_ERROR, MCUXCLRANDOM_STATUS_FAULT_ATTACK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_generate))
    }
    else if(MCUXCLPRNG_STATUS_OK != ret_Prng_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_ncGenerate, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_ncGenerate, diRefValue, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPrng_generate))
    }
}
