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

/** @file  mcuxClEcc_Internal.c
 *  @brief mcuxClEcc: implementation of ECC internal functions
 */

#include <mcuxClEcc_Internal_FUP.h>

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClEcc_Fup_Interleave[7], 4u) = {{0x10u,0x00u,0x50u,0xddu,0xacu,0x4cu},{0x00u,0x14u,0x00u,0x04u,0x07u,0x1cu},{0xc0u,0x13u,0x05u,0x05u,0x00u,0x1du},{0x00u,0x14u,0x00u,0x1du,0x06u,0x1du},{0x40u,0x15u,0x00u,0x1cu,0x07u,0x04u},{0xc0u,0x13u,0x04u,0x04u,0x00u,0x1cu},{0x00u,0x0eu,0x00u,0x1cu,0x1du,0x04u}};


