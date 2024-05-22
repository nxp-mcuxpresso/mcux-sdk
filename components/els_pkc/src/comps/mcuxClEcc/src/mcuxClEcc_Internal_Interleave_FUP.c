/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

/**
 * @file  mcuxClEcc_Internal_Interleave_FUP.c
 * @brief mcuxClEcc: FUP program for internal interleave function
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_Interleave_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Interleave[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xb8u,0x7cu,0x09u,0x1du},{0x00u,0x14u,0x00u,0x04u,0x07u,0x19u},{0xc0u,0x13u,0x05u,0x05u,0x00u,0x1bu},{0x00u,0x14u,0x00u,0x1bu,0x02u,0x1bu},{0x40u,0x15u,0x00u,0x19u,0x07u,0x04u},{0xc0u,0x13u,0x04u,0x04u,0x00u,0x19u},{0x00u,0x0eu,0x00u,0x19u,0x1bu,0x04u}};



/* Prerequisites:                                                              */
/* ECC_V3 = shifting amount to have higher half of scalar aligned to PKC word; */
/* VY0 points to higher half of buffer T0.                                     */
