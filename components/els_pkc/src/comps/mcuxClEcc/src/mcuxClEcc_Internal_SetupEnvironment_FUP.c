/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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
 * @file  mcuxClEcc_Internal_SetupEnvironment_FUP.c
 * @brief mcuxClEcc: FUP program for of mcuxClEcc_SetupEnvironment
 */


#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Internal_SetupEnvironment_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_SetupEnvironment_ClearBuffers[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x2fu,0x3bu,0x1bu,0x01u},{0x00u,0x3eu,0x00u,0x00u,0x03u,0x00u},{0x00u,0x3eu,0x00u,0x00u,0x03u,0x01u},{0x00u,0x3eu,0x00u,0x00u,0x03u,0x16u},{0x00u,0x3eu,0x00u,0x00u,0x03u,0x17u}};



