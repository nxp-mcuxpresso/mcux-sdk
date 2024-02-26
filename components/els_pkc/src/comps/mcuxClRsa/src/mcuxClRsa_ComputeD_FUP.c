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
#include <internal/mcuxClRsa_ComputeD_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClRsa_ComputeD_Steps123_FUP[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x3bu,0x6du,0xecu,0xd6u},{0x00u,0x1bu,0x00u,0x00u,0x09u,0x04u},{0x00u,0x1bu,0x00u,0x01u,0x09u,0x05u},{0x80u,0x13u,0x04u,0x05u,0x00u,0x06u},{0x80u,0xa7u,0x04u,0x04u,0x05u,0x05u},{0x00u,0x14u,0x00u,0x05u,0x09u,0x05u}};


/*
 * FUP code to do the below steps
 * 1. Compute p' = p-1
 * 2. Compute q' = q-1
 * 3. Compute lcm(p−1, q−1)=|(p−1)(q−1)|/gcd(p-1,q−1)
 * 3.1 Compute a = (p−1)(q−1)
 * 3.2 Compute b = gcd(p-1,q−1)
 */
