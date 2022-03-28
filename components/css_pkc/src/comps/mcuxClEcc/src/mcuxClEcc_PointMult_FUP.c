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

/** @file  mcuxClEcc_PointMult.fup.fup.c
 *  @brief mcuxClEcc: FUP program of ECDSA point multiplication
 */

#include <mcuxClEcc_PointMult_FUP.h>

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClEcc_PointMult_SplitScalar_ConvertPoint2MR[10], 4u) = {{0x10u,0x00u,0x42u,0xa3u,0x3fu,0x9fu},{0x80u,0x00u,0x1cu,0x17u,0x01u,0x19u},{0xc0u,0x00u,0x1au,0x19u,0x01u,0x1cu},{0xc0u,0x00u,0x1bu,0x19u,0x01u,0x1du},{0x80u,0x00u,0x26u,0x16u,0x00u,0x24u},{0x80u,0x00u,0x27u,0x16u,0x00u,0x25u},{0x00u,0x09u,0x00u,0x00u,0x00u,0x23u},{0x80u,0x2au,0x11u,0x1du,0x1cu,0x1du},{0x80u,0x33u,0x1du,0x00u,0x01u,0x1cu},{0x80u,0x2au,0x01u,0x1cu,0x01u,0x19u}};


