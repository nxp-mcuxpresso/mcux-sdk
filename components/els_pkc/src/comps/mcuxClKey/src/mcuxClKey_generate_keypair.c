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

/** @file  mcuxClKey.c
 *  @brief Implementation of the Key component key pair generation functionality.
 *  mcuxClKey.h. */

#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClSession_Internal_EntryExit.h>
#include <internal/mcuxClKey_Internal.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_generate_keypair)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_generate_keypair(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Generation_t generation,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClKey_generate_keypair, diRefValue, MCUXCLKEY_STATUS_FAULT_ATTACK)

    /* Call protocol specific key pair generation function according to passed generation descriptor. */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_KeyGenFct,
        generation->pKeyGenFct(pSession,
                              generation,
                              privKey,
                              pubKey));

    MCUXCLSESSION_EXIT(pSession, mcuxClKey_generate_keypair, diRefValue, ret_KeyGenFct, MCUXCLKEY_STATUS_FAULT_ATTACK,
        generation->protectionTokenKeyGenFct)
}
