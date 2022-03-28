/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
 * @file  mcuxClEcc_Mont_MontDhX.c
 * @brief mcuxClEcc: implementation of MontDhX functions
 */

#include <mcuxClEcc_Mont_MontDhX_FUP.h>

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_MontDhDecodeScalar[5], 4u) = {{0x10u,0x00u,0x3bu,0xfbu,0x7bu,0xf5u},{0x00u,0x15u,0x00u,0x1cu,0x02u,0x1eu},{0x00u,0x14u,0x00u,0x1eu,0x03u,0x1eu},{0x00u,0x1au,0x00u,0x1eu,0x04u,0x1eu},{0x00u,0x17u,0x00u,0x1eu,0x05u,0x1eu}};

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_MontDhX_CalcAffineX[5], 4u) = {{0x10u,0x00u,0x11u,0x0bu,0x8fu,0x7du},{0x80u,0x00u,0x1bu,0x16u,0x00u,0x19u},{0x80u,0x00u,0x20u,0x19u,0x00u,0x1bu},{0x80u,0x33u,0x1bu,0x00u,0x00u,0x20u},{0x80u,0x2au,0x00u,0x20u,0x00u,0x20u}};


