/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClSession.c
 *  @brief Implementation of the Session component to deal with session-based
 *  configurations. This file implements the functions declared in
 *  mcuxClSession.h and mcuxClSession_Internal.h */

#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClMemory.h>
#include <mcuxClToolchain.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_init(
    mcuxClSession_Handle_t pSession,
    uint32_t * const pCpuWaBuffer,
    uint32_t cpuWaLength,
    uint32_t * const pPkcWaBuffer,
    uint32_t pkcWaLength
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_init);


    /* Set CPU Wa in session handle */
    pSession->cpuWa.buffer = pCpuWaBuffer;
    pSession->cpuWa.size = cpuWaLength / (sizeof(uint32_t));
    pSession->cpuWa.used = 0u;
    pSession->cpuWa.dirty = 0u;

    /* Set PKC Wa in session handle */
    pSession->pkcWa.buffer = pPkcWaBuffer;
    pSession->pkcWa.size = pkcWaLength / (sizeof(uint32_t));
    pSession->pkcWa.used = 0u;
    pSession->pkcWa.dirty = 0u;

    /* Set default RTF handling */
    pSession->rtf = MCUXCLSESSION_RTF_UPDATE_FALSE;
    pSession->pRtf = NULL;



    pSession->randomCfg.ctx = NULL;
    pSession->randomCfg.mode = NULL;
    /* Set the PRNG patch function to un-patch the PRNG */
    pSession->randomCfg.prngPatchFunction = NULL;
    pSession->randomCfg.pCustomPrngState = NULL;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_init, MCUXCLSESSION_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_setRtf)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_setRtf(
    mcuxClSession_Handle_t pSession,
    uint8_t *const pRtf,
    mcuxClSession_Rtf_t RtfOptions
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_setRtf);

    pSession->rtf = RtfOptions;
    pSession->pRtf = pRtf;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_setRtf, MCUXCLSESSION_STATUS_OK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_cleanup)
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_DEFINED("It is indeed defined.")
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEFINED_MORE_THAN_ONCE("It defined only once.")
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_cleanup(
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEFINED_MORE_THAN_ONCE()
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_DEFINED()
  mcuxClSession_Handle_t pSession
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_cleanup,
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

    //TODO: Replace the functional memory clear function with a secure one
    /* For 32-bit architectures, the maximum number of bytes in the memory is UINT32_MAX, i.e. the maximum number of words is UINT32_MAX / 4 */
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pSession->cpuWa.dirty, 0u, (UINT32_MAX >> 2u), MCUXCLSESSION_STATUS_ERROR)
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *) pSession->cpuWa.buffer,(sizeof(uint32_t)) * pSession->cpuWa.dirty);

    /* Reset dirty to used, in case not all memory has been freed (and gets used again). */
    pSession->cpuWa.dirty = pSession->cpuWa.used;

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pSession->pkcWa.dirty, 0u, MCUXCLPKC_RAM_SIZE >> 2u, MCUXCLSESSION_STATUS_ERROR)
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *) pSession->pkcWa.buffer,(sizeof(uint32_t)) * pSession->pkcWa.dirty);

    /* Reset dirty to used, in case not all memory has been freed (and gets used again). */
    pSession->pkcWa.dirty = pSession->pkcWa.used;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_cleanup, MCUXCLSESSION_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_destroy)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_destroy(
    mcuxClSession_Handle_t pSession UNUSED_PARAM
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_destroy,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

    MCUX_CSSL_FP_FUNCTION_CALL(cleanupStatus, mcuxClSession_cleanup(pSession) );
    if (MCUXCLSESSION_STATUS_OK != cleanupStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_destroy, MCUXCLSESSION_STATUS_ERROR);
    }

    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *) pSession,sizeof(mcuxClSession_Descriptor_t));


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_destroy, MCUXCLSESSION_STATUS_OK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_setRandom)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_setRandom(
    mcuxClSession_Handle_t session,
    mcuxClRandom_Mode_t randomMode,
    mcuxClRandom_Context_t randomCtx
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_setRandom);
    session->randomCfg.ctx = randomCtx;
    session->randomCfg.mode = randomMode;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_setRandom, MCUXCLSESSION_STATUS_OK);
}
