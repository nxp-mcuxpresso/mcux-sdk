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
 * @file  mcuxCsslMemory_Copy_asm.h
 * @brief Internal header of mcuxCsslMemory_Copy inline-asm macro
 */


#ifndef MCUXCSSLMEMORY_COPY_ASM_H_
#define MCUXCSSLMEMORY_COPY_ASM_H_


#if defined( __ICCARM__ ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined(__GNUC__)
#define MCUXCSSLMEMORY_COPY_ASM(word, byte, cha, chb, xorword, retval, datareg, src, dst, nwords, cnt, success)  \
do{  \
    __asm (  \
        "MOV    %[_word], #0\n"  \
        "MOV    %[_datareg], #0\n"  \
        "MOV    %[_xorword], #0\n"  \
        "CMP    %[_word], %[_nwords]\n"  \
        "BLT    mcuxCsslMemory_Copy_word_loop\n"  \
        "BGE    mcuxCsslMemory_Copy_word_loop_end\n"  \
        "B      mcuxCsslMemory_Copy_fault\n"  \
        "mcuxCsslMemory_Copy_word_loop:\n"  \
        "LDR    %[_datareg], [%[_src], %[_word], LSL #2]\n"  \
        "EORS   %[_cha], %[_cha], %[_datareg]\n"  \
        "STR    %[_datareg], [%[_dst], %[_word], LSL #2]\n"  \
        "EORS   %[_chb], %[_chb], %[_datareg]\n"  \
        "ADDS   %[_word], %[_word], #+1\n"  \
        "EORS   %[_xorword], %[_xorword], %[_word]\n"  \
        "CMP    %[_word], %[_nwords]\n"  \
        "BLT    mcuxCsslMemory_Copy_word_loop\n"  \
        "mcuxCsslMemory_Copy_word_loop_end:\n"  \
        "LSLS   %[_byte], %[_word], #2\n"  \
        "MOV    %[_datareg], #0\n"  \
        "CMP    %[_byte], %[_nbytes]\n"  \
        "BLT    mcuxCsslMemory_Copy_byte_loop\n"  \
        "BGE    mcuxCsslMemory_Copy_byte_loop_end\n"  \
        "B      mcuxCsslMemory_Copy_fault\n"  \
        "mcuxCsslMemory_Copy_byte_loop:\n"  \
        "LDRB   %[_datareg], [%[_src], %[_byte]]\n"  \
        "EORS   %[_cha], %[_cha], %[_datareg]\n"  \
        "STRB   %[_datareg], [%[_dst], %[_byte]]\n"  \
        "EORS   %[_chb], %[_chb], %[_datareg]\n"  \
        "ADDS   %[_byte], %[_byte], #+1\n"  \
        "CMP    %[_byte], %[_nbytes]\n"  \
        "BLT    mcuxCsslMemory_Copy_byte_loop\n"  \
        "mcuxCsslMemory_Copy_byte_loop_end:\n"  \
        "MOV    %[_datareg], #0\n"  \
        "EORS   %[_retval], %[_retval], %[_success]\n"  \
        "mcuxCsslMemory_Copy_fault:\n"  \
        : [_word] "+&r" (word)  \
        , [_byte] "+&r" (byte)  \
        , [_cha] "+&r" (cha)  \
        , [_chb] "+&r" (chb)  \
        , [_xorword] "+&r" (xorword)  \
        , [_retval] "+r" (retval)  \
        , [_datareg] "+&r" (datareg)  \
        : [_src] "r" (src)  \
        , [_dst] "r" (dst)  \
        , [_nwords] "r" (nwords)  \
        , [_nbytes] "r" (cnt)  \
        , [_success] "r" (success)  \
        : "cc", "memory"  \
    );  \
}while(false)

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
#define MCUXCSSLMEMORY_COPY_ASM(word, byte, cha, chb, xorword, retval, datareg, src, dst, nwords, cnt, success)  \
do{  \
    __asm {  \
        MOV    word, #0;  \
        MOV    datareg, #0;  \
        MOV    xorword, #0;  \
        CMP    word, nwords;  \
        BLT    mcuxCsslMemory_Copy_word_loop;  \
        BGE    mcuxCsslMemory_Copy_word_loop_end;  \
        B      mcuxCsslMemory_Copy_fault;  \
mcuxCsslMemory_Copy_word_loop:  \
        LDR    datareg, [src, word, LSL #2];  \
        EORS   cha, cha, datareg;  \
        STR    datareg, [dst, word, LSL #2];  \
        EORS   chb, chb, datareg;  \
        ADDS   word, word, #+1;  \
        EORS   xorword, xorword, word;  \
        CMP    word, nwords;  \
        BLT    mcuxCsslMemory_Copy_word_loop;  \
mcuxCsslMemory_Copy_word_loop_end:  \
        LSLS   byte, word, #2;  \
        MOV    datareg, #0;  \
        CMP    byte, cnt;  \
        BLT    mcuxCsslMemory_Copy_byte_loop;  \
        BGE    mcuxCsslMemory_Copy_byte_loop_end;  \
        B      mcuxCsslMemory_Copy_fault;  \
mcuxCsslMemory_Copy_byte_loop:  \
        LDRB   datareg, [src, byte];  \
        EORS   cha, cha, datareg;  \
        STRB   datareg, [dst, byte];  \
        EORS   chb, chb, datareg;  \
        ADDS   byte, byte, #+1;  \
        CMP    byte, cnt;  \
        BLT    mcuxCsslMemory_Copy_byte_loop;  \
mcuxCsslMemory_Copy_byte_loop_end:  \
        MOV    datareg, #0;  \
        EORS   retval, retval, success;  \
mcuxCsslMemory_Copy_fault:  \
    }  \
    (void)datareg;  \
    (void)success;  \
}while(false)

#else
    #error "Unsupported compiler. The above section must be manually adapted to support your compiler's inline assembly syntax."
#endif


#endif /* MCUXCSSLMEMORY_COPY_ASM_H_ */
