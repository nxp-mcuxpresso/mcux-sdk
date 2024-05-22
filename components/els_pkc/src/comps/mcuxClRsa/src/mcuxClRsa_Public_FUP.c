/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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

#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClRsa_Public_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClRsa_Public_ReductionME_FUP[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x60u,0x2du,0x26u,0xfdu},{0x80u,0x33u,0x04u,0x00u,0x02u,0x01u},{0x80u,0x2au,0x02u,0x01u,0x02u,0x05u}};


/*
 * FUP to do montgomery reduction and normalize the result
 */
