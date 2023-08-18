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
 * @file  mcuxClMath_ExactDivideOdd_FUP.c
 * @brief mcuxClMath: implementation of exact divide with odd divisor
 */

#include <internal/mcuxClMath_ExactDivideOdd_FUP.h>
#include <internal/mcuxClMath_Internal_ExactDivideOdd.h>

const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_ExactDivideOdd_DivideLoop[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xd5u,0x8bu,0x65u,0xe0u},{0x40u,0x20u,0x02u,0x00u,0x00u,0x00u},{0x40u,0x00u,0x02u,0x00u,0x00u,0x04u},{0x40u,0x1eu,0x00u,0x04u,0x08u,0x05u},{0x00u,0x62u,0x00u,0x01u,0x02u,0x02u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_ExactDivideOdd_NDashY[4] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x8fu,0x8au,0x30u,0x35u},{0x40u,0x00u,0x00u,0x01u,0x00u,0x04u},{0x40u,0x1au,0x00u,0x04u,0x05u,0x04u},{0x40u,0x00u,0x04u,0x00u,0x00u,0x00u}};


/**
 * [DESIGN]
 * Suppose T \equiv (-Y)^(-1) (mod 2^(bit)).
 * Since (T*Y+1) \equiv 0 (mod 2^(bit)), so (T*Y+1)^2 = ((T*Y+2)*T*Y + 1) \equiv 0 (mod 2^(2*bit)).
 * This FUP program calculates: T := (T*Y+2)*T \equiv (-Y)^(-1) (mod 2^(2*bit)).
 */
/* PS2 length = (-, MCUXCLPKC_WORDSIZE) */
/* uptrt[DivOdd_Ri] = 2                */

/**
 * [DESIGN]
 * In iteration i (i = 0 ~ rPkcWord-1), this FUP program calculates R[i], and
 * X{i+1} = (Xi + R[i]*Y) / W = (X0 + R[i~0]*Y) / W^(i+1).
 *
 * CAUTION:
 * The MACCR in this FUP program will access to t+1 PKC words of X, where
 * t = min(yPkcWord, rPkcWord - i) = effectivePkcByteLenY / MCUXCLPKC_WORDSIZE.
 * In the boundary case, t = 1 (when xPkcByteLen = yPkcByteLen = MCUXCLPKC_WORDSIZE),
 * and 2 PKC words of X will be read (but xPkcByteLen = MCUXCLPKC_WORDSIZE).
 */
/* PS1 length = (-, effectivePkcByteLenY) */
/* PS2 length = (-, MCUXCLPKC_WORDSIZE) */
