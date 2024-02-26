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

/**
 * @file  mcuxClEcc_Weier_KeyGen_FUP.c
 * @brief FUP program for Weierstrass curve key generation
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_KeyGen_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xcfu,0x8du,0x82u,0xabu},{0x80u,0x33u,0x1eu,0x00u,0x01u,0x1cu},{0x80u,0x00u,0x1cu,0x18u,0x01u,0x1eu},{0x80u,0x21u,0x01u,0x19u,0x1cu,0x19u},{0x80u,0x00u,0x19u,0x18u,0x01u,0x1cu},{0x80u,0x2au,0x01u,0x1cu,0x01u,0x1cu},{0x80u,0x2au,0x01u,0x1cu,0x1eu,0x1cu}};



