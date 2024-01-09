/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClMath_SecModExp_FUP.c
 * @brief mcuxClMath: FUP programs of secure modular exponentiation
 */

#include <internal/mcuxClMath_SecModExp_FUP.h>
#include <internal/mcuxClMath_Internal_SecModExp.h>
#include <internal/mcuxClPkc_FupMacros.h>

const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_Aws_Init[3] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xb9u,0xa5u,0xecu,0xd4u},{0x80u,0x00u,0x02u,0x01u,0x07u,0x03u},{0x00u,0x09u,0x00u,0x00u,0x07u,0x04u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_Aws_Rerand[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xfcu,0xe9u,0xf6u,0xcbu},{0x00u,0x22u,0x0bu,0x07u,0x00u,0x00u},{0x00u,0x22u,0x0cu,0x07u,0x02u,0x02u},{0x00u,0x22u,0x0du,0x07u,0x01u,0x01u},{0x00u,0x22u,0x0eu,0x07u,0x03u,0x03u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_CalcQAndInterleave[6] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x15u,0xeau,0xe7u,0x3bu},{0x40u,0x0bu,0x00u,0x04u,0x05u,0x04u},{0x00u,0x04u,0x0bu,0x0bu,0x00u,0x0du},{0x00u,0x14u,0x00u,0x0du,0x10u,0x06u},{0x00u,0x14u,0x00u,0x0eu,0x10u,0x0au},{0x00u,0x06u,0x0cu,0x0cu,0x06u,0x06u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_EuclideanSplit_1[8] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xa7u,0xbdu,0x6au,0x33u},{0xc0u,0x00u,0x04u,0x00u,0x0bu,0x01u},{0xc0u,0x00u,0x05u,0x00u,0x0bu,0x03u},{0x80u,0x33u,0x01u,0x00u,0x0bu,0x00u},{0x80u,0x33u,0x03u,0x00u,0x0bu,0x01u},{0x80u,0x2au,0x0bu,0x00u,0x0bu,0x00u},{0x80u,0x2au,0x0bu,0x01u,0x0bu,0x01u},{0x80u,0x2au,0x0bu,0x00u,0x01u,0x0cu}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_EuclideanSplit_2[7] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xa7u,0x4cu,0x47u,0x09u},{0x40u,0x09u,0x00u,0x00u,0x04u,0x04u},{0x40u,0x6au,0x00u,0x04u,0x01u,0x04u},{0x40u,0x6au,0x00u,0x04u,0x0cu,0x04u},{0x40u,0x09u,0x00u,0x00u,0x05u,0x05u},{0x40u,0x6au,0x00u,0x05u,0x01u,0x05u},{0x40u,0x3eu,0x00u,0x00u,0x0fu,0x00u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_ExactDivideLoop[9] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x26u,0xbfu,0x8au,0x8fu},{0x00u,0x00u,0x08u,0x0au,0x00u,0x0du},{0x00u,0x00u,0x0du,0x0bu,0x00u,0x00u},{0x40u,0x0au,0x00u,0x08u,0x00u,0x08u},{0x00u,0x1eu,0x00u,0x0du,0x0fu,0x08u},{0x00u,0x00u,0x09u,0x0au,0x00u,0x0du},{0x00u,0x00u,0x0du,0x0bu,0x00u,0x00u},{0x40u,0x0au,0x00u,0x09u,0x00u,0x09u},{0x00u,0x1eu,0x00u,0x0du,0x0fu,0x09u}};
const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_PrepareFirstExp[5] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0xd2u,0xcbu,0x98u,0xf8u},{0x00u,0x22u,0x0cu,0x07u,0x02u,0x04u},{0x80u,0x00u,0x04u,0x04u,0x07u,0x01u},{0x80u,0x2au,0x07u,0x01u,0x07u,0x01u},{0x80u,0x33u,0x05u,0x00u,0x07u,0x00u}};


/**
 * [DESIGN]
 * Prepare base number M3 and Accumulator (A0) of exponentiation.
 */
/* PS1 length = (          pkcLenN,           pkcLenN) */

/**
 * [DESIGN]
 * Re-randomize base numbers M0, M1, M2 and M3, by adding in-place random multiples of the modulus.
 *
 * PKC MACC operation is used. It takes the carry into account, to calculate: R = X0 * Y + {c, Z}.
 * The carry is written into the extra PKC word on top of pkcLenN.
 * Thus, even the carry flag is 1, this will affect only the extra PKC word, and will not be used
 * in the following MM on length pkcLenN.
 *
 * In addition, in order to ensure that the result does not overflow beyond pkcLenN, and given that
 * operations are done in-place in each buffer in a loop, the following should hold:
 * log2(iter) + bitLenR <= leadingZeroesN,
 * where leadingZeroesN is the number of leading zero bits in N, iter is the total number of re-randomization
 * iterations, and bitLenR is the bit length of the random number.
 *
 */
/* PS1 length = (          pkcLenN,           pkcLenN) */

/**
 * [DESIGN]
 * Euclidean splitting part #1: calculate "exponent mod b" on both shares of exponent.
 *
 * The modular reduction is implemented based on PKC MR (Modular Reduction).
 * The two shares of exponent are converted to their Montgomery representation
 * modulo b (length = MCUXCLPKC_WORDSIZE) by multiplying them with M0 = QDash.
 * They are converted back to their normal representation by PKC MR, and
 * results are in the range [0, b]. The PKC MS (Modular Subtraction) guarantees
 * the proper results in the range [0, b-1].
 *
 * CAUTION:
 * According to PKC specification, when calculating MM (Modular Multiplication)
 * with OPLEN = MCUXCLPKC_WORDSIZE, PKC will read the least significant PKC word
 * of the result buffer in PKC workarea (M2[0] and M3[0] in this FUP program)
 * before writing any intermediate result to it.
 * This pre-fetch will not affect the result, but caller shall ensure that
 * both PKC words M2[0] and M3[0] are initialized before this FUP program,
 * if the platform requires explicit memory initialization.
 *
 * ps, M2[0] and M3[0] have been initialized (used as temp buffer) when calculating
 * NDash and QDash before this FUP program.
 */
/* PS1 length = (MCUXCLPKC_WORDSIZE, MCUXCLPKC_WORDSIZE) */
/* PS2 length = (    pkcLenExpPlus, MCUXCLPKC_WORDSIZE) */

/**
 * [DESIGN]
 * Euclidean splitting part #2: prepare to calculate exact division:
 * "(exponent - (exponent mod b)) / b", on both shares of exponent.
 *
 * Exact division, x/b = q, assumes the dividend x must be exactly a multiple of
 * divisor b. So there is the quotient q satisfying (-x) + b*q = 0.
 */
/* PS2 length = (                -,     pkcLenExpPlus) */

/**
 * [DESIGN]
 * One iteration of exact division, where the divisor b is of the size, MCUXCLPKC_WORDSIZE.
 *
 * The algorithm of exact division q = x/b is to find q satisfying (-x) + b*q = 0.
 * Let y = -x mod 256^(pkcLenExpPlus), and y[i] and q[i] are the i-th PKC word of y and q.
 *
 * y + b*q[0] \equiv 0 mod Q, where Q = 256^(MCUXCLPKC_WORDSIZE).
 * q[0] = y * (-b)^(-1) mod Q = y[0] * NDash mod Q.
 * Assume for i > 0, y + b*q[i-1 ~ 0] \equiv 0 mod Q^i.
 * Then, q[i] = ((y + b*q[i-1 ~ 0])/(Q^i)) * NDash mod Q.
 *
 * In this implementation, the negative dividend (-x) will be overwritten by
 * quotient q word-wisely.
 */
/* PS1 length = (                -, MCUXCLPKC_WORDSIZE) */
/* PS2 length = (                -,      remainLength) */

/**
 * [DESIGN]
 * Prepare q, and interleaved b and r.
 *
 * First part: calculate q, using PS2.
 * A0 = q = A0 - A1 = ((expA - expB) - ((expA - expB) mod b)) / b = (exp - (exp mod b)) / b
 *
 * Second part: interleave R0 = b and R1 = r, using PS1.
 * The interleaved data is written over two consecutive PKC words in TE and NDASH.
 * The result space of MAC_GF2 takes one extra PKC word and thus also overwrites R0.
 * The 2-FW buffer R2 is used as temp buffer.
 */
/* PS1 length = (                -, MCUXCLPKC_WORDSIZE) */
/* PS2 length = (                -,     pkcLenExpPlus) */

/**
 * [DESIGN]
 * Prepare base numbers for the first exponentiation.
 *
 * First part: randomized calculation of M2 = (m + (r16 * N))^2 mod N = m^2 mod N.
 * PKC MACC operation is used to calculate A0 = R1 * N + M1.
 * MACC takes the carry into account, which is written into the extra PKC word on top of pkcLenN.
 * This extra PKC word is not used in the following MM on length pkcLenN.
 *
 * Second part: prepare M0 = 1 in MR, M0 < N, with a Montgomery reduction of QSquared.
 */
/* PS1 length = (          pkcLenN,           pkcLenN) */

