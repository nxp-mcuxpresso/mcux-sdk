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
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#include <internal/mcuxClRandomModes_Private_PatchMode.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static const mcuxClRandom_OperationModeDescriptor_t mcuxClRandomModes_OperationModeDescriptor_PatchMode = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    .initFunction                    = mcuxClRandomModes_PatchMode_initFunction,
    .reseedFunction                  = mcuxClRandomModes_PatchMode_reseedFunction,
    .generateFunction                = mcuxClRandomModes_PatchMode_generateFunction,
    .selftestFunction                = mcuxClRandomModes_PatchMode_selftestFunction,
    .protectionTokenInitFunction     = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_PatchMode_initFunction,
    .protectionTokenReseedFunction   = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_PatchMode_reseedFunction,
    .protectionTokenGenerateFunction = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_PatchMode_generateFunction,
    .protectionTokenSelftestFunction = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_PatchMode_selftestFunction,
    .operationMode                   = MCUXCLRANDOMMODES_PATCHMODE,
};

/**
 * \brief This function creates a PATCH_MODE descriptor
 *
 * This function creates a PATCH_MODE descriptor.
 * The function expects as input a custom function to be used inside the CL functions for random number generation as well as
 * a pointer to a context buffer which can be used by the custom generate function.
 * The custom generate function may also use all CPU workarea allocated for the mcuxClRandom_generate function.
 * The function shall be called prior to an mcuxClRandom_init call.
 *
 * \param  patchMode[out]               Pointer to PATCH_MODE descriptor to be initialized
 * \param  customGenerateAlgorithm[in]  Pointer to the custom generate function
 * \param  pCustomCtx[in]               Pointer to a custom context which shall be used by the passed custom generate function
 * \param  securityStrength[in]         Pointer to the supported security strength of DRBG
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK         if the PATCH_MODE descriptor generation was successful
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_createPatchMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_createPatchMode(mcuxClRandom_ModeDescriptor_t *patchMode, mcuxClRandomModes_CustomGenerateAlgorithm_t customGenerateAlgorithm, mcuxClRandom_Context_t pCustomCtx, uint32_t securityStrength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_createPatchMode);

    patchMode->pOperationMode = &mcuxClRandomModes_OperationModeDescriptor_PatchMode;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_STRUCT("As pDrbgMode is used for multiple purposes due to memory saving it must be a void pointer.")
    patchMode->pDrbgMode = (void*)customGenerateAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_STRUCT()
    patchMode->contextSize = 0u;
    patchMode->auxParam = (uint32_t) pCustomCtx;
    patchMode->securityStrength = (uint16_t) securityStrength;

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRandomModes_createPatchMode, MCUXCLRANDOM_STATUS_OK, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
}


/**
 * \brief Empty function called during mcuxClRandom_init when PATCH_MODE is activated
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_PatchMode_initFunction, mcuxClRandom_initFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_PatchMode_initFunction(mcuxClSession_Handle_t session UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_PatchMode_initFunction);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_PatchMode_initFunction, MCUXCLRANDOM_STATUS_OK);
}

/**
 * \brief Empty function called during mcuxClRandom_reseed when PATCH_MODE is activated
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_PatchMode_reseedFunction, mcuxClRandom_reseedFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_PatchMode_reseedFunction(mcuxClSession_Handle_t session UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_PatchMode_reseedFunction);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_PatchMode_reseedFunction, MCUXCLRANDOM_STATUS_OK);
}

/**
 * \brief Function called during mcuxClRandom_generate when PATCH_MODE is activated in order to call the custom generate function
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_PatchMode_generateFunction, mcuxClRandom_generateFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_PatchMode_generateFunction(mcuxClSession_Handle_t session, uint8_t *pOut, uint32_t outLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_PatchMode_generateFunction);

    mcuxClRandom_Mode_t mode = (mcuxClRandom_Mode_t) session->randomCfg.mode;
    mcuxClRandom_Context_t pCustomCtx = (mcuxClRandom_Context_t) mode->auxParam;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_STRUCT("As pDrbgMode is used for multiple purposes due to memory saving it must be a void pointer.")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST("Type is a function pointer. const qualifier is meaningless on cast type")
    mcuxClRandomModes_CustomGenerateAlgorithm_t pCustomAlg = (mcuxClRandomModes_CustomGenerateAlgorithm_t) mode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_STRUCT()

    mcuxClRandom_Status_t result_customAlg = pCustomAlg(session, pCustomCtx, pOut, outLength);
    if(MCUXCLRANDOM_STATUS_OK != result_customAlg)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_PatchMode_generateFunction, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_PatchMode_generateFunction, MCUXCLRANDOM_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_PatchMode_selftestFunction, mcuxClRandom_selftestFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_PatchMode_selftestFunction(mcuxClSession_Handle_t session UNUSED_PARAM, mcuxClRandom_Mode_t mode UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_PatchMode_selftestFunction);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_PatchMode_selftestFunction, MCUXCLRANDOM_STATUS_OK);
}
