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

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_RemoveBlinding_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClRsa_RemoveBlinding_FUP[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x6cu,0x62u,0x79u,0x15u},{0x00u,0x3eu,0x00u,0x00u,0x06u,0x05u},{0x00u,0x6au,0x00u,0x05u,0x00u,0x04u},{0x80u,0x00u,0x04u,0x02u,0x01u,0x05u},{0x80u,0x2au,0x01u,0x05u,0x01u,0x04u}};


/*
 * FUP program to convert result of the exponentiation to normal representation modulo Nb.
 */
