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

#include <mcuxClToolchain.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <mcuxClMemory.h>
#include <mcuxCsslAnalysis.h>

#include <mcuxClRandomModes_Functions_TestMode.h>

#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#include <internal/mcuxClRandomModes_Private_CtrDrbg.h>
#include <internal/mcuxClRandomModes_Private_TestMode.h>
#include <internal/mcuxClMemory_Copy_Internal.h>
#include <internal/mcuxClSession_Internal.h>

#ifdef MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClRandom_OperationModeDescriptor_t mcuxClRandomModes_OperationModeDescriptor_TestMode_PrDisabled =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .initFunction                    = mcuxClRandomModes_TestMode_initFunction,
    .reseedFunction                  = mcuxClRandomModes_TestMode_reseedFunction,
    .generateFunction                = mcuxClRandomModes_NormalMode_generateFunction_PrDisabled,
    .selftestFunction                = mcuxClRandomModes_TestMode_selftestFunction,
    .protectionTokenInitFunction     = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_TestMode_initFunction,
    .protectionTokenReseedFunction   = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_TestMode_reseedFunction,
    .protectionTokenGenerateFunction = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_NormalMode_generateFunction_PrDisabled,
    .protectionTokenSelftestFunction = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_TestMode_selftestFunction,
    .operationMode                   = MCUXCLRANDOMMODES_TESTMODE,
};
#endif /* MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED */



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_createTestFromNormalMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_createTestFromNormalMode(mcuxClRandom_ModeDescriptor_t *pTestMode, mcuxClRandom_Mode_t normalMode, const uint32_t * const pEntropyInput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_createTestFromNormalMode);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_INTEGER_TO_POINTER("For a normal mode, auxParam contains a pointer to mcuxClRandom_OperationModeDescriptor_t")
    pTestMode->pOperationMode   = (mcuxClRandom_OperationModeDescriptor_t *) normalMode->auxParam;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_INTEGER_TO_POINTER()
    pTestMode->pDrbgMode        = normalMode->pDrbgMode;
    pTestMode->auxParam         = (uint32_t) pEntropyInput;
    pTestMode->contextSize      = normalMode->contextSize;
    pTestMode->securityStrength = normalMode->securityStrength;

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandomModes_createTestFromNormalMode, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_updateEntropyInput)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_updateEntropyInput(mcuxClRandom_ModeDescriptor_t *pTestMode, const uint32_t * const pEntropyInput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_updateEntropyInput);

    pTestMode->auxParam         = (uint32_t) pEntropyInput;

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandomModes_updateEntropyInput, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
}


/**
 * \brief This function instantiates a DRBG in TEST_MODE following the lines of the function Instantiate_function specified in NIST SP800-90A
 *
 * This function instantiates a DRBG in TEST_MODE following the lines of the function Instantiate_function specified in NIST SP800-90A.
 * The function reads entropy input for the DRBG seed from a buffer provided by the user of the CL.
 *
 * \param  session[in]          Handle for the current CL session
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK         if the DRBG instantiation finished successfully
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the DRBG instantiation failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_TestMode_initFunction, mcuxClRandom_initFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_TestMode_initFunction(mcuxClSession_Handle_t pSession)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_TestMode_initFunction);

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    mcuxClRandomModes_Context_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_Generic_t *) pSession->randomCfg.ctx;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    mcuxClRandom_Mode_t mode = pSession->randomCfg.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) mode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    /* Derive the initial DRBG state from the generated entropy input */
    MCUX_CSSL_FP_FUNCTION_CALL(result_instantiate, pDrbgMode->pDrbgAlgorithms->instantiateAlgorithm(pSession, (uint8_t *) mode->auxParam));
    if (MCUXCLRANDOM_STATUS_OK != result_instantiate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_TestMode_initFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Initialize the reseedSeedOffset field of the context */
    pRngCtxGeneric->reseedSeedOffset = 0u;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_TestMode_initFunction, MCUXCLRANDOM_STATUS_OK,
        pDrbgMode->pDrbgAlgorithms->protectionTokenInstantiateAlgorithm);
}


/**
 * \brief This function reseeds a DRBG in TEST_MODE following the lines of the function Reseed_function specified in NIST SP800-90A
 *
 * This function reseeds a DRBG in TEST_MODE following the lines of the function Reseed_function specified in NIST SP800-90A.
 * The function reads entropy input for the DRBG seed from a buffer provided by the user of the CL.
 *
 * \param  session[in]          Handle for the current CL session
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK            if the DRBG reseeding finished successfully
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK  if the DRBG reseeding failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_TestMode_reseedFunction, mcuxClRandom_reseedFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_TestMode_reseedFunction(mcuxClSession_Handle_t pSession)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_TestMode_reseedFunction);

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_Context_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_Generic_t *) pSession->randomCfg.ctx;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    mcuxClRandom_Mode_t mode = pSession->randomCfg.mode;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) mode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    /* Derive the initial DRBG state from the user-defined entropy input */
    MCUX_CSSL_FP_FUNCTION_CALL(result_reseed, pDrbgMode->pDrbgAlgorithms->reseedAlgorithm(pSession, (((uint8_t *) mode->auxParam) + pRngCtxGeneric->reseedSeedOffset)));
    if (MCUXCLRANDOM_STATUS_OK != result_reseed)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_TestMode_reseedFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_TestMode_reseedFunction, MCUXCLRANDOM_STATUS_OK,
        pDrbgMode->pDrbgAlgorithms->protectionTokenReseedAlgorithm);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_TestMode_selftestFunction, mcuxClRandom_selftestFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_TestMode_selftestFunction(mcuxClSession_Handle_t pSession UNUSED_PARAM, mcuxClRandom_Mode_t mode UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_TestMode_selftestFunction);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_TestMode_selftestFunction, MCUXCLRANDOM_STATUS_OK);
}
