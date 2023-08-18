/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022 NXP                                                 */
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
 * @file  mcuxClMath_NDash_FUP.c
 * @brief mcuxClMath: FUP program used in mcuxClMath_NDash
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClMath_Internal_NDash.h>
#include <internal/mcuxClMath_NDash_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClMath_NDash_Fup[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x33u,0x15u,0x36u,0x51u},{0x40u,0x00u,0x02u,0x01u,0x00u,0x00u},{0x40u,0x1au,0x00u,0x00u,0x03u,0x00u},{0x40u,0x00u,0x00u,0x02u,0x00u,0x00u},{0x40u,0x1eu,0x00u,0x00u,0x04u,0x02u}};



/**
 * [DESIGN]
 * Since the operand NDash is of the size MCUXCLPKC_WORDSIZE,
 * the result of multiplication (OP2_MUL) is stored in T (2 * MCUXCLPKC_WORDSIZE),
 * and then copied to NDash.
 */
