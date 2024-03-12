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
 * @file  mcuxClMath_Internal_SecModExp.h
 * @brief mcuxClMath: internal header of secure modular exponentiation
 */


#ifndef MCUXCLMATH_INTERNAL_SECMODEXP_H_
#define MCUXCLMATH_INTERNAL_SECMODEXP_H_

#include <mcuxClCore_Platform.h>


/**********************************************************/
/* Indices of operands in PKC workarea and UPTR table     */
/**********************************************************/
#define SECMODEXP_M0     0u
#define SECMODEXP_M2     1u
#define SECMODEXP_M1     2u
#define SECMODEXP_M3     3u
#define SECMODEXP_A0     4u
#define SECMODEXP_A1     5u
#define SECMODEXP_TE     6u
#define SECMODEXP_N      7u
#define SECMODEXP_V0     8u
#define SECMODEXP_V1     9u
#define SECMODEXP_NDASH 10u
#define SECMODEXP_R0    11u
#define SECMODEXP_R1    12u
#define SECMODEXP_R2    13u
#define SECMODEXP_R2H   14u
#define SECMODEXP_ZERO  15u
#define SECMODEXP_ONE   16u
#define SECMODEXP_UPTRT_SIZE  17u

/**********************************************************/
/* Inline asm macro                                       */
/**********************************************************/
/** This macro securely select offsets Mi (i=0~3) according to 2 shares of exponent word.
 * oMsH8 = ROL((M3H, M2H, M1H, M0H), 4);
 * oMsL8 = ROL((M3L, M2L, M1L, M0L), 4),
 * where, e.g., M3H/M3L are the higher/lower 8 bits of the 16-bit offset M3.
 * 
 * **********************************************************
 * pseudocode:
 * 
 * input: oMsH8, oMsL8, bIdx (not modified); rndW (destroyed);
 * input/output: expW0, expW1, ofsA;
 * output: ofsYX
 *
 * Functional algorithm:
 * expW0 ^= rndW (can be skipped in functional version)
 * expW1 ^= rndW (can be skipped in functional version)
 * expW = expW0 ^ expW1
 * expBits = (expW >> (bIdx & 31)) & 3
 * rotateAmount = expBits*8 + 4
 * miH = oMsH8 >>> rotateAmount (right rotate)
 * miL = oMsL8 >>> rotateAmount (right rotate)
 * ofsYX = ((ofsA & 0xFFFF) << 16) | ((miH & 0xFF) << 8) | (miL & 0xFF)
 * ofsA >>>= 16 (swap hi16 and lo16)
 ********************************************************************************
 * It swaps ofsAt and ofsA(1-t) (stored in ofsAs), and outputs ofsYX = ofsA(1-t) || ofsMi.
 */
#if defined(ICCARM_ARMCLANG_GNUC)

#define MCUXCLMATH_SECMODEXP_WRITEOFFSET(ofsY_ofsX,maskVal) MCUXCLPKC_PS1_SETXY_REG(ofsY_ofsX)
#define MCUXCLMATH_SECMODEXP_SECUREOFFSETSELECT(expW0_, expW1_, ofsAs_, ofsYX_, rndW_, bIdx_, oMsH8_, oMsL8_, rnd64_0_, rnd64_1_, mask_)  \
do{  \
    uint32_t temp0, temp1;  /* local variable */  \
    (void) (rnd64_0_); /* unused variable, avoid compiler warning */                  \
    (void) (rnd64_1_); /* unused variable, avoid compiler warning */                  \
    (void) (mask_);    /* unused variable, avoid compiler warning */                  \
    __asm volatile (  \
        "EORS  %[exp0], %[exp0], %[rnd]   \n"  \
        "SUBS  %[tmp0], %[bIdx], #3       \n"  \
        "ROR   %[tmp0], %[exp0], %[tmp0]  \n"  /* rotate exp0[i+1:i] to tmp0[4:3] */  \
\
        "EORS  %[exp1], %[exp1], %[rnd]   \n"  \
        "ROR   %[tmp1], %[exp1], %[bIdx]  \n"  /* rotate exp1[i+1:i] to tmp1[1:0] */  \
        "BFI   %[rnd],  %[tmp1], #3,  #2  \n"  /* insert exp1[i+1:i] to rnd[4:3] */  \
\
        "EORS  %[tmp1], %[rnd],  %[tmp0]  \n"  /* tmp1[4:3] = exp[i+1:i] */  \
        "BIC   %[tmp1], %[tmp1],  #3      \n"  /* clear rnd[1:0] */  \
        "ORR   %[tmp1], %[tmp1],  #4      \n"  /* set rnd[2] */  \
        "ROR   %[tmp0], %[ofL8], %[tmp1]  \n"  /* tmp0[7:0] = Mi[7:0] */  \
        "ROR   %[tmp1], %[ofH8], %[tmp1]  \n"  /* tmp1[7:0] = Mi[15:8] */  \
\
        "BFI   %[rnd],  %[tmp0], #0,  #8  \n"  \
        "BFI   %[rnd],  %[tmp1], #8,  #8  \n"  \
        "BFI   %[rnd],  %[ofAs], #16, #16 \n"  /* set offsetY @hi16 */  \
        "ROR   %[ofAs], %[ofAs], #16      \n"  /* swap A0 and A1, i.e., let t := 1-t. */  \
\
        : [exp0]  "+&r"  (expW0_),  \
          [exp1]  "+&r"  (expW1_),  \
          [ofAs]  "+r"  (ofsAs_),  \
          [rnd]   "+&r"  (rndW_),   \
          [tmp0]  "=&r" (temp0),   \
          [tmp1]  "=&r" (temp1)    \
        : [bIdx]  "r"   (bIdx_),   \
          [ofH8]  "r"   (oMsH8_),  \
          [ofL8]  "r"   (oMsL8_)   \
        : "cc"  \
    );  \
    (ofsYX_) = (rndW_);  \
} while (false)

#else
#warning Unsupported compiler. The above section must be manually adapted to support the inline assembly syntax.
#define MCUXCLMATH_SECMODEXP_WRITEOFFSET(ofsY_ofsX,maskVal) MCUXCLPKC_PS1_SETXY_REG(ofsY_ofsX)
#define MCUXCLMATH_ROR(x,y) (((x) >> (y)) | ((x) << ((32u - (y)) & 31u)))
#define MCUXCLMATH_SECMODEXP_SECUREOFFSETSELECT(expW0, expW1, ofsA, ofsYX, rndW, bIdx, oMsH8, oMsL8,rand64_0,rand64_1,mask)  \
do{                                                                                       \
        (void) (rndW);    /* unused variable, avoid compiler warning */                   \
        (void) (rand64_0); /* unused variable, avoid compiler warning */                  \
        (void) (rand64_1); /* unused variable, avoid compiler warning */                  \
        (void) (mask);     /* unused variable, avoid compiler warning */                  \
        uint32_t expW = (expW0) ^ (expW1);                                                \
        uint32_t expBits = (expW >> ((bIdx) & 31u)) & 3u;                                 \
        uint32_t rotateAmount = expBits * 8u + 4u;                                        \
        uint32_t miH = MCUXCLMATH_ROR((oMsH8), rotateAmount);                              \
        uint32_t miL = MCUXCLMATH_ROR((oMsL8), rotateAmount);                              \
        (ofsYX) = ((((ofsA) & 0xFFFFu) << 16u) | ((miH & 0xFFu) << 8u) | (miL & 0xFFu));  \
        (ofsA) = MCUXCLMATH_ROR((ofsA), 16u);                                              \
} while (false)
#endif

#endif /* MCUXCLMATH_INTERNAL_SECMODEXP_H_ */
