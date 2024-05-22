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

/**
 * @file  mcuxClEcc_Internal_Convert_FUP.c
 * @brief mcuxClEcc: FUP programs for generic ECC coordinate conversion
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_Convert_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_ConvertHomToAffine[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x4eu,0xd7u,0xe8u,0x4cu},{0x80u,0x00u,0x19u,0x16u,0x00u,0x1bu},{0x80u,0x2au,0x00u,0x1bu,0x00u,0x1bu},{0x80u,0x00u,0x1bu,0x20u,0x00u,0x19u},{0x80u,0x2au,0x00u,0x19u,0x00u,0x20u},{0x80u,0x00u,0x1bu,0x21u,0x00u,0x19u},{0x80u,0x2au,0x00u,0x19u,0x00u,0x21u}};



/* Prerequisites:
 *  - Homogeneous X- and Y-coordinates are stored in ECC_COORD00 and ECC_COORD01
 *  - (Z*R)^(-1), where Z is the homogeneous Z-coordinate is stored in ECC_T0 */
