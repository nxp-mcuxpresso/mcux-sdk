/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 *  mcuxClSession.h. */


#include <mcuxClSession.h>
#include <mcuxClMemory.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_init)
mcuxClSession_Status_Protected_t mcuxClSession_init(
    mcuxClSession_Handle_t session,
    uint32_t * const cpuWaBuffer,
    uint32_t cpuWaSize,
    uint32_t * const pkcWaBuffer,
    uint32_t pkcWaSize
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_init);

    /* set CPU Wa in session handle */
    session->cpuWa.buffer = cpuWaBuffer;
    session->cpuWa.size = cpuWaSize;
    session->cpuWa.used = 0u;

    /* Set PKC Wa in session handle */
    session->pkcWa.buffer = pkcWaBuffer;
    session->pkcWa.size = pkcWaSize;
    session->pkcWa.used = 0u;

    /* Set default RTF handling */
    session->rtf = MCUXCLSESSION_RTF_UPDATE_FALSE;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_init, MCUXCLSESSION_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_setRtf)
mcuxClSession_Status_Protected_t mcuxClSession_setRtf(
    mcuxClSession_Handle_t session,
    mcuxClSession_Rtf_t RtfOptions
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_setRtf);

    session->rtf = RtfOptions;
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_setRtf, MCUXCLSESSION_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_cleanup)
mcuxClSession_Status_Protected_t mcuxClSession_cleanup(
  mcuxClSession_Handle_t session
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_cleanup,
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

    //TODO: Replace the functional memory clear function with a secure one
    MCUX_CSSL_FP_FUNCTION_CALL(retCode, mcuxClMemory_clear((uint8_t *) session->cpuWa.buffer, session->cpuWa.size, session->cpuWa.size));
    if(0U != retCode)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_cleanup, MCUXCLSESSION_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(retCode1, mcuxClMemory_clear((uint8_t *) session->pkcWa.buffer, session->pkcWa.size, session->pkcWa.size));
    if(0U != retCode1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_cleanup, MCUXCLSESSION_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_cleanup, MCUXCLSESSION_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_destroy)
mcuxClSession_Status_Protected_t mcuxClSession_destroy(
    mcuxClSession_Handle_t session
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClSession_destroy);

    //Empty function as there is no dedicated mechanism on this platform to free the memory space.
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClSession_destroy, MCUXCLSESSION_STATUS_OK);
}
