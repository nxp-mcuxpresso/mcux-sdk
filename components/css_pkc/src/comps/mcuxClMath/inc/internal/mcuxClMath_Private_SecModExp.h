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
 * @file  mcuxClMath_Private_SecModExp.h
 * @brief mcuxClMath: private header of secure modular exponentiation
 */

#ifndef MCUXCLMATH_PRIVATE_SECMODEXP_H_
#define MCUXCLMATH_PRIVATE_SECMODEXP_H_

#include <stdint.h>
#include <stdbool.h>

#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClPkc_FupMacros.h>
#include <mcuxClMath_Types.h>

#include <mcuxClMath_SecModExp_FUP.h>

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
#define SECMODEXP_R0    10u
#define SECMODEXP_R1    11u
#define SECMODEXP_R2    12u
#define SECMODEXP_ZERO  13u
#define SECMODEXP_UPTRT_SIZE  14u

#define mcuxClMath_Fup_Aws_Init_LEN  5u

#define mcuxClMath_Fup_EuclideanSplit_1_LEN  8u

#define mcuxClMath_Fup_EuclideanSplit_2_LEN  7u

#define mcuxClMath_Fup_ExactDivideLoop_LEN  9u

#if defined(__ICCARM__) || defined(__ARMCC_VERSION) || defined(__GNUC__)

#define MCUXCLMATH_SECMODEXP_SECUREOFFSETSELECT(expW0_, expW1_, ofsAs_, ofsYX_, rndW_, bIdx_, oMsH8_, oMsL8_)  \
do{  \
    uint32_t temp0, temp1;    \
    __asm volatile (  \
        "EORS  %[exp0], %[exp0], %[rnd]   \n"  \
        "SUBS  %[tmp0], %[bIdx], #3       \n"  \
        "ROR   %[tmp0], %[exp0], %[tmp0]  \n"    \
\
        "EORS  %[exp1], %[exp1], %[rnd]   \n"  \
        "ROR   %[tmp1], %[exp1], %[bIdx]  \n"    \
        "BFI   %[rnd],  %[tmp1], #3,  #2  \n"    \
\
        "EORS  %[tmp1], %[rnd],  %[tmp0]  \n"    \
        "BIC   %[tmp1], %[tmp1],  #3      \n"    \
        "ORR   %[tmp1], %[tmp1],  #4      \n"    \
        "ROR   %[tmp0], %[ofL8], %[tmp1]  \n"    \
        "ROR   %[tmp1], %[ofH8], %[tmp1]  \n"    \
\
        "BFI   %[rnd],  %[tmp0], #0,  #8  \n"  \
        "BFI   %[rnd],  %[tmp1], #8,  #8  \n"  \
        "BFI   %[rnd],  %[ofAs], #16, #16 \n"    \
        "ROR   %[ofAs], %[ofAs], #16      \n"    \
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
#error Unsupported compiler. The above section must be manually adapted to support the inline assembly syntax.
#endif

#endif
