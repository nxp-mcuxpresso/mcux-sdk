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

/** @file  mcuxClEcc_Internal_SecurePointSelect.h
 *  @brief Internal header of mcuxClEcc SecurePointSelect macro
 */

#ifndef MCUXCLECC_INTERNAL_SECUREPOINTSELECT_H_
#define MCUXCLECC_INTERNAL_SECUREPOINTSELECT_H_

#include <stdint.h>
#include <stdbool.h>
#include <internal/mcuxClEcc_Internal.h>

#if defined(__ICCARM__) || defined(__ARMCC_VERSION) || defined(__CC_ARM) || defined(__GNUC__)

#define MCUXCLECC_SECUREPOINTSELECT(ofsP0_, ofsP1_, pOps_, scalarW0_, scalarW1_, randomWord_, bitOffset_)  \
    do{  \
        uint32_t temp0;  \
        uint32_t temp1 = (bitOffset_);  \
        uint32_t temp2 = (randomWord_);  \
        __asm volatile (  \
            "SUBS  %[tmp1], %[tmp1], #2\n"\
            "ROR   %[tmp0], %[s0], %[tmp1]\n"    \
            "BIC   %[tmp2], %[tmp2], #4\n"       \
            "EORS  %[tmp0], %[tmp0], %[tmp2]\n"  \
            "ROR   %[tmp1], %[s1], %[tmp1]\n"    \
            "EORS  %[tmp0], %[tmp0], %[tmp1]\n"  \
            "ORRS  %[tmp0], %[tmp0], %[tmp2]\n"  \
            "SUBS  %[tmp1], %[pOps], %[tmp2]\n"\
            "ADDS  %[tmp2], %[tmp2], #4\n"       \
            "ADDS  %[tmp1], %[tmp1], %[ofsX0]\n"\
            "ANDS  %[tmp2], %[tmp2], %[tmp0]\n"  \
            "LDR   %[tmp0], [%[tmp1], %[tmp2]]\n"\
            "EOR   %[tmp2], %[tmp2], #4\n"       \
            "LDR   %[tmp1], [%[tmp1], %[tmp2]]\n"\
            : [tmp0] "=&r" (temp0),  \
              [tmp1] "+&r" (temp1),  \
              [tmp2] "+&r" (temp2)   \
            : [pOps]  "r" (pOps_),  \
              [s0]    "r" (scalarW0_),  \
              [s1]    "r" (scalarW1_),  \
              [ofsX0] "i" (ECC_X0 * 2u)  \
            : "cc"  \
        );  \
        (ofsP0_) = temp0;  \
        (ofsP1_) = temp1;  \
    } while (false)

#else
    #error Unsupported compiler. The above section must be manually adapted to support the inline assembly syntax.
#endif

#endif
