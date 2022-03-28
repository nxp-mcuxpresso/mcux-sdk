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
 * @file  mcuxCsslMemory_Compare_asm.h
 * @brief Internal header of mcuxCsslMemory_Compare inline-asm macro
 */


#ifndef MCUXCSSLMEMORY_COMPARE_ASM_H_
#define MCUXCSSLMEMORY_COMPARE_ASM_H_

#include <stdint.h>
#include <stdbool.h>

#if defined( __ICCARM__ ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined(__GNUC__)
#define MCUXCSSLMEMORY_COMPARE_ASM_COMPARISON(retval_, cur_lhs_, cur_rhs_, cnt_, notValid_, result_)  \
do{  \
    uint8_t dat_lhs, dat_rhs;  \
    __asm volatile (  \
        "EOR    %[_retval], %[_result], %[_notValid]\n" /* retval should now be 0xFFFFFFFF */\
        "loop:\n" /* Comparison; in case of equality retval should remain 0xFFFFFFFF throughout the loop. */\
        "LDRB   %[_dat_lhs], [%[_cur_lhs]], #+1\n"        \
        "LDRB   %[_dat_rhs], [%[_cur_rhs]], #+1\n"        \
        "EORS   %[_dat_lhs], %[_dat_lhs], %[_dat_rhs]\n"  \
        "BICS   %[_retval], %[_retval], %[_dat_lhs]\n"    \
        "SUBS   %[_cnt], %[_cnt], #+1\n"                  \
        "MVN    %[_dat_rhs], %[_dat_lhs]\n"               \
        "AND    %[_retval], %[_retval], %[_dat_rhs]\n"    \
        "BNE    loop\n"  \
        : [_retval] "=r" (retval_),    \
          [_cur_lhs] "+r" (cur_lhs_),  \
          [_cur_rhs] "+r" (cur_rhs_),  \
          [_cnt] "+r" (cnt_),          \
          [_dat_lhs] "=r" (dat_lhs),   \
          [_dat_rhs] "=r" (dat_rhs)    \
        : [_notValid] "r" (notValid_), \
          [_result] "r" (result_)      \
    );  \
    (void)dat_lhs;  \
    (void)dat_rhs;  \
}while(false)

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
#define MCUXCSSLMEMORY_COMPARE_ASM_COMPARISON(retval_, cur_lhs_, cur_rhs_, cnt_, notValid_, result_)  \
do{  \
    uint8_t dat_lhs, dat_rhs;  \
    __asm {  \
        EOR retval_, result_, notValid_;  \
loop:  \
        LDRB dat_lhs, [cur_lhs_], +1;  \
        LDRB dat_rhs, [cur_rhs_], +1;  \
        EORS dat_lhs, dat_lhs, dat_rhs;  \
        BICS retval_, retval_, dat_lhs;  \
        SUBS cnt_, cnt_, 1;  \
        MVN dat_rhs, dat_lhs;  \
        AND retval_, retval_, dat_rhs;  \
        BNE loop;  \
    }  \
    (void)dat_lhs;  \
    (void)dat_rhs;  \
}while(false)

#else
    #error "Unsupported compiler. The above section must be manually adapted to support your compiler's inline assembly syntax."
#endif


/* If the binary representation of retval contains a zero,
 * this sequence of instructions will turn retval to zero completely.
 * If retval is 0xFFFFFFFF, it will remain untouched.
 */
#if defined( __ICCARM__ ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined(__GNUC__)
#define MCUXCSSLMEMORY_COMPARE_ASM_CALC_RETVAL(retval_, errCode_)  \
do{  \
    __asm volatile (  \
        "and %[_retval], %[_retval], %[_retval], ror  #1\n"  \
        "and %[_retval], %[_retval], %[_retval], ror  #2\n"  \
        "and %[_retval], %[_retval], %[_retval], ror  #4\n"  \
        "and %[_retval], %[_retval], %[_retval], ror  #8\n"  \
        "and %[_retval], %[_retval], %[_retval], ror #16\n"  \
        "eor %[_retval], %[_retval], %[_errCode]\n"  \
        : [_retval] "+r" (retval_)  \
        : [_errCode] "r" (errCode_)  \
    );  \
}while(false)

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
#define MCUXCSSLMEMORY_COMPARE_ASM_CALC_RETVAL(retval_, errCode_)  \
do{  \
    __asm {  \
        AND retval_, retval_, retval_, ror 1;  \
        AND retval_, retval_, retval_, ror 2;  \
        AND retval_, retval_, retval_, ror 4;  \
        AND retval_, retval_, retval_, ror 8;  \
        AND retval_, retval_, retval_, ror 16;  \
        EOR retval_, retval_, errCode_;  \
    }  \
}while(false)

#else
    #error "Unsupported compiler. The above section must be manually adapted to support your compiler's inline assembly syntax."
#endif


#endif /* MCUXCSSLMEMORY_COMPARE_ASM_H_ */
