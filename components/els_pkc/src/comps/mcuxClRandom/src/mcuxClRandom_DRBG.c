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

/** @file  mcuxClRandom_DRBG.c
 *  @brief Implementation of the Random component which provides APIs for
 *  handling of DRBG random number generators. This file implements the functions
 *  declared in mcuxClRandom.h. */

#include <mcuxClToolchain.h>
#include <mcuxClSession.h>
#include <mcuxClRandom.h>
#include <mcuxCsslDataIntegrity.h>
#include <mcuxClBuffer.h>

#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandom_Internal_Memory.h>
#include <internal/mcuxClRandom_Internal_Functions.h>

#include <internal/mcuxClSession_Internal_EntryExit.h>

/**
 * @brief This function verifies a Random mode
 *
 * @param  mode[in]   Random mode to be verified
 *
 * @return Status of the operation:
 * @retval #MCUXCLRANDOM_STATUS_OK             if the Random mode is valid
 * @retval #MCUXCLRANDOM_STATUS_INVALID_PARAM  if the Random mode is invalid
 * @retval #MCUXCLRANDOM_STATUS_FAULT_ATTACK   if a fault attack is detected.
 *
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_verifyMode)
static inline mcuxClRandom_Status_t mcuxClRandom_verifyMode(mcuxClRandom_Mode_t mode)
{
    // TODO CLNS-7923: Need to be discussed whether INVALID_PARAM or FAULT_ATTACK should be returned
    if(mode == NULL)
    {
        return MCUXCLRANDOM_STATUS_INVALID_PARAM;
    }
    return MCUXCLRANDOM_STATUS_OK;
}


/**
 * @brief This function verifies a Random context
 *
 * @param  pRngCtx[in]   Random context to be verified
 *
 * @return Status of the operation:
 * @retval #MCUXCLRANDOM_STATUS_OK             if the Random context is valid
 * @retval #MCUXCLRANDOM_STATUS_FAULT_ATTACK   if the Random context is invalid or a fault attack is detected.
 *
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_verifyContext)
static inline mcuxClRandom_Status_t mcuxClRandom_verifyContext(mcuxClRandom_Context_t pRngCtx UNUSED_PARAM)
{
    // TODO CLNS-7390: To be implemented
    return MCUXCLRANDOM_STATUS_OK;
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_generate_internal)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_generate_internal(
    mcuxClSession_Handle_t pSession,
    mcuxCl_Buffer_t        pOut,
    uint32_t              outLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandom_generate_internal);

    /* Verify context integrity */
    mcuxClRandom_Context_t pRngCtx = pSession->randomCfg.ctx;
    mcuxClRandom_Status_t retCode_verifyContext = mcuxClRandom_verifyContext(pRngCtx);
    if(MCUXCLRANDOM_STATUS_OK != retCode_verifyContext)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_generate_internal, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    mcuxClRandom_Mode_t sessionMode = pSession->randomCfg.mode;

    /* Call generate function from randommodes */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_generateFunction, sessionMode->pOperationMode->generateFunction(pSession, sessionMode, pRngCtx, pOut, outLength));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandom_generate_internal, retCode_generateFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK,
                            sessionMode->pOperationMode->protectionTokenGenerateFunction);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_init(
    mcuxClSession_Handle_t pSession,
    mcuxClRandom_Context_t pContext,
    mcuxClRandom_Mode_t    mode
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_init, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomInitParams, (uint32_t)pSession + (uint32_t)pContext + (uint32_t)mode);

    /* Verify passed mode parameter */
    mcuxClRandom_Status_t retCode_verifyMode = mcuxClRandom_verifyMode(mode);
    if(MCUXCLRANDOM_STATUS_OK != retCode_verifyMode)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_init, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Store context in session. */
    pSession->randomCfg.ctx = pContext;

    /* Store mode in session. */
    pSession->randomCfg.mode = mode;

    /* Call internal init function */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_initFunction, mode->pOperationMode->initFunction(pSession, mode, pContext));

    MCUX_CSSL_DI_RECORD(sumOfRandomInitParams, (uint32_t)pSession + (uint32_t)pContext + (uint32_t)mode);

    MCUXCLSESSION_EXIT(pSession, mcuxClRandom_init, diRefValue, retCode_initFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK, mode->pOperationMode->protectionTokenInitFunction)
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_reseed)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_reseed(
    mcuxClSession_Handle_t pSession
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_reseed, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomReseedParams,  (uint32_t)pSession);

    /* Verify context integrity */
    mcuxClRandom_Context_t pRngCtx = pSession->randomCfg.ctx;
    mcuxClRandom_Status_t retCode_verifyContext = mcuxClRandom_verifyContext(pRngCtx);
    if(MCUXCLRANDOM_STATUS_OK != retCode_verifyContext)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_reseed, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    mcuxClRandom_Mode_t sessionMode = pSession->randomCfg.mode;

    /* Call internal reseed function */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_reseedFunction, sessionMode->pOperationMode->reseedFunction(pSession, sessionMode, pRngCtx));

    MCUX_CSSL_DI_RECORD(sumOfRandomReseedParams, (uint32_t)pSession);

    MCUXCLSESSION_EXIT(pSession, mcuxClRandom_reseed, diRefValue, retCode_reseedFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK, sessionMode->pOperationMode->protectionTokenReseedFunction)
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_generate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_generate(
    mcuxClSession_Handle_t pSession,
    mcuxCl_Buffer_t        pOut,
    uint32_t              outLength
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_generate, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_RECORD(sumOfRandomGenerateParams, (uint32_t)pSession + (uint32_t)pOut + outLength);

    /* Call internal generate function */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_generateInternal, mcuxClRandom_generate_internal(pSession, pOut, outLength));

    MCUXCLSESSION_EXIT(pSession, mcuxClRandom_generate, diRefValue, retCode_generateInternal, MCUXCLRANDOM_STATUS_FAULT_ATTACK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate_internal))
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_uninit)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_uninit(
  mcuxClSession_Handle_t pSession
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_uninit, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomUninitParams, (uint32_t)pSession);

    mcuxClRandom_Mode_t sessionMode = pSession->randomCfg.mode;
    /* In patch mode the context is not used so the context integrity check and clearing needs to be skipped */
    if(0u == sessionMode->contextSize)
    {
        /* Clear pointers stored in the session. */
        pSession->randomCfg.ctx = NULL;
        pSession->randomCfg.mode = NULL;
        MCUX_CSSL_DI_RECORD(sumOfRandomUninitParams, (uint32_t)pSession);
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_uninit, diRefValue, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK)
    }

    /* Verify context integrity */
    mcuxClRandom_Context_t pRngCtx = pSession->randomCfg.ctx;
    mcuxClRandom_Status_t retCode_verifyContext = mcuxClRandom_verifyContext(pRngCtx);
    if(MCUXCLRANDOM_STATUS_OK != retCode_verifyContext)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_uninit, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Clear the context */
    MCUXCLRANDOM_SECURECLEAR(mcuxClRandom_uninit, MCUXCLRANDOM_STATUS_ERROR, (uint8_t *) pSession->randomCfg.ctx, sessionMode->contextSize);

    /* Clear pointers stored in the session. */
    pSession->randomCfg.ctx = NULL;
    pSession->randomCfg.mode = NULL;

    MCUX_CSSL_DI_RECORD(sumOfRandomUninitParams, (uint32_t)pSession);

    MCUXCLSESSION_EXIT(pSession, mcuxClRandom_uninit, diRefValue, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK, MCUXCLRANDOM_FP_CALLED_SECURECLEAR)
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_selftest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_selftest(
    mcuxClSession_Handle_t pSession,
    mcuxClRandom_Mode_t    mode
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_selftest, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomSelftestParams, (uint32_t)pSession + (uint32_t)mode);

    /* Verify passed mode parameter */
    mcuxClRandom_Status_t retCode_verifyMode = mcuxClRandom_verifyMode(mode);
    if(MCUXCLRANDOM_STATUS_OK != retCode_verifyMode)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandom_selftest, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Call internal selftest function. */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_selftestFunction, mode->pOperationMode->selftestFunction(pSession, mode));

    MCUX_CSSL_DI_RECORD(sumOfRandomSelftestParams, (uint32_t)pSession + (uint32_t)mode);

    MCUXCLSESSION_EXIT(pSession, mcuxClRandom_selftest, diRefValue, retCode_selftestFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK, mode->pOperationMode->protectionTokenSelftestFunction)
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandom_checkSecurityStrength)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_checkSecurityStrength(
    mcuxClSession_Handle_t pSession,
    uint32_t              securityStrength
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClRandom_checkSecurityStrength, diRefValue, MCUXCLRANDOM_STATUS_FAULT_ATTACK)

    MCUX_CSSL_DI_EXPUNGE(sumOfRandomCheckSecurityStrengthParams, (uint32_t)pSession + (uint32_t)securityStrength);

    mcuxClRandom_Mode_t sessionMode = pSession->randomCfg.mode;

    MCUX_CSSL_DI_RECORD(sumOfRandomCheckSecurityStrengthParams, (uint32_t)pSession + (uint32_t)securityStrength);

    if (securityStrength > sessionMode->securityStrength)
    {
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_checkSecurityStrength, diRefValue, MCUXCLRANDOM_STATUS_LOW_SECURITY_STRENGTH, MCUXCLRANDOM_STATUS_FAULT_ATTACK)
    }
    else
    {
        MCUXCLSESSION_EXIT(pSession, mcuxClRandom_checkSecurityStrength, diRefValue, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK)
    }
}
