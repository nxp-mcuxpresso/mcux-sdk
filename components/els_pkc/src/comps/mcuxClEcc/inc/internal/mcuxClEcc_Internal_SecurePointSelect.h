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
 * @file  mcuxClEcc_Internal_SecurePointSelect.h
 * @brief Internal header of mcuxClEcc SecurePointSelect macro
 */


#ifndef MCUXCLECC_INTERNAL_SECUREPOINTSELECT_H_
#define MCUXCLECC_INTERNAL_SECUREPOINTSELECT_H_

#include <stdint.h>
#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header

/**
 * This macro securely loads ofsP0 and ofsP1 from pOps[] table.
 * When b = "the bit at bitOffset of (scalarW0 XOR scalarW1)" = 0,
 * it returns ofsP0 = pOps_[iBase + 1] || pOps_[iBase], and
 *            ofsP1 = pOps_[iBase + 3] || pOps_[iBase + 2];
 * when b = 1,
 * it returns ofsP0 = pOps_[iBase + 3] || pOps_[iBase + 2], and
 *            ofsP1 = pOps_[iBase + 1] || pOps_[iBase].
 */
#if defined(__RISCV32)

#define CREATE_ROR_TEMP  \
    uint32_t temp3
#define ALLOCATE_ROR_TEMP  \
    , [tmp3] "=&r" (temp3)
#define ROTATE_RIGHT(dest, src, bitsToRotate, tmp) \
    "neg   "#tmp", "#bitsToRotate"\n"\
    "sll   "#tmp", "#src", "#tmp"\n"\
    "srl   "#dest", "#src", "#bitsToRotate"\n"\
    "or    "#dest", "#dest", "#tmp"\n"

#define MCUXCLECC_SECUREPOINTSELECT(ofsP0_, ofsP1_, pOps_, iBase, scalarW0_, scalarW1_, randomWord_, bitOffset_)  \
    do{  \
        uint32_t temp0;  \
        uint32_t temp1 = (bitOffset_);  \
        uint32_t temp2 = (randomWord_);  \
        CREATE_ROR_TEMP;  \
        __asm volatile (  \
            "addi  %[tmp1], %[tmp1], -2\n"\
            ROTATE_RIGHT(%[tmp0], %[s0], %[tmp1], %[tmp3])  /* t0 = ( s0 .... ) ||  b0 || .. */\
            "andi  %[tmp2], %[tmp2], -5\n"                  /* t2 = ( rand .. ) ||   0 || .. */\
            "xor   %[tmp0], %[tmp0], %[tmp2]\n"             /* t0 = ( s0^rand ) ||  b0 || .. */\
            ROTATE_RIGHT(%[tmp1], %[s1], %[tmp1], %[tmp3])  /* t1 = ( s1 .... ) ||  b1 || .. */\
            "xor   %[tmp0], %[tmp0], %[tmp1]\n"             /* t0 = ( s^rand  ) ||   b || .. */\
            "or    %[tmp0], %[tmp0], %[tmp2]\n"             /* t0 = ( s|rand  ) ||   b || .. */\
            "sub   %[tmp1], %[pOps], %[tmp2]\n"\
            "addi  %[tmp2], %[tmp2], 4\n"                   /* t2 = ( rand .. ) ||   1 || .. */\
            "and   %[tmp2], %[tmp2], %[tmp0]\n"             /* t2 = ( rand .. ) ||   b || .. */\
            "add   %[tmp0], %[tmp1], %[tmp2]\n"             /* update address offset */\
            "lw    %[tmp0], %[ofsX0](%[tmp0])\n"\
            "xori  %[tmp2], %[tmp2], 4\n"                   /* t2 = ( rand .. ) || 1-b || .. */\
            "add   %[tmp1], %[tmp1], %[tmp2]\n"             /* update address offset */\
            "lw    %[tmp1], %[ofsX0](%[tmp1])\n"\
            : [tmp0] "=&r" (temp0),  \
              [tmp1] "+&r" (temp1),  \
              [tmp2] "+&r" (temp2)  \
              ALLOCATE_ROR_TEMP  \
            : [pOps]  "r" (pOps_),  \
              [s0]    "r" (scalarW0_),  \
              [s1]    "r" (scalarW1_),  \
              [ofsX0] "i" ((iBase) * 2u)  \
        );  \
        (ofsP0_) = temp0;  \
        (ofsP1_) = temp1;  \
    } while (false)

#elif defined(ICCARM_ARMCC_GNUC)

#define MCUXCLECC_SECUREPOINTSELECT(ofsP0_, ofsP1_, pOps_, iBase, scalarW0_, scalarW1_, randomWord_, bitOffset_)  \
    do{  \
        uint32_t temp0;  \
        uint32_t temp1 = (bitOffset_);  \
        uint32_t temp2 = (randomWord_);  \
        __asm volatile (  \
            "SUBS  %[tmp1], %[tmp1], #2\n"\
            "ROR   %[tmp0], %[s0], %[tmp1]\n"    /* t0 = ( s0 .... ) ||  b0 || .. */\
            "BIC   %[tmp2], %[tmp2], #4\n"       /* t2 = ( rand .. ) ||   0 || .. */\
            "EORS  %[tmp0], %[tmp0], %[tmp2]\n"  /* t0 = ( s0^rand ) ||  b0 || .. */\
            "ROR   %[tmp1], %[s1], %[tmp1]\n"    /* t1 = ( s1 .... ) ||  b1 || .. */\
            "EORS  %[tmp0], %[tmp0], %[tmp1]\n"  /* t0 = ( s^rand  ) ||   b || .. */\
            "ORRS  %[tmp0], %[tmp0], %[tmp2]\n"  /* t0 = ( s|rand ) ||   b || .. */\
            "SUBS  %[tmp1], %[pOps], %[tmp2]\n"\
            "ADDS  %[tmp2], %[tmp2], #4\n"       /* t2 = ( rand .. ) ||   1 || .. */\
            "ADDS  %[tmp1], %[tmp1], %[ofsX0]\n"\
            "ANDS  %[tmp2], %[tmp2], %[tmp0]\n"  /* t2 = ( rand .. ) ||   b || .. */\
            "LDR   %[tmp0], [%[tmp1], %[tmp2]]\n"\
            "EOR   %[tmp2], %[tmp2], #4\n"       /* t2 = ( rand .. ) || 1-b || .. */\
            "LDR   %[tmp1], [%[tmp1], %[tmp2]]\n"\
            : [tmp0] "=&r" (temp0),  \
              [tmp1] "+&r" (temp1),  \
              [tmp2] "+&r" (temp2)  \
            : [pOps]  "r" (pOps_),  \
              [s0]    "r" (scalarW0_),  \
              [s1]    "r" (scalarW1_),  \
              [ofsX0] "i" ((iBase) * 2u)  \
            : "cc"  \
        );  \
        (ofsP0_) = temp0;  \
        (ofsP1_) = temp1;  \
    } while (false)

#else
    #error Unsupported compiler. The above section must be manually adapted to support the inline assembly syntax.
#endif


#endif /* MCUXCLECC_INTERNAL_SECUREPOINTSELECT_H_ */
