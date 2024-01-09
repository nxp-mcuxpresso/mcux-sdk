/*--------------------------------------------------------------------------*/
/* Copyright 2018-2022 NXP                                                  */
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
 * @file  mcuxClOsccaPkc_Macros.h
 * @brief Macros for accessing PKC hardware IP
 */


#ifndef MCUXCLOSCCAPKC_MACROS_H_
#define MCUXCLOSCCAPKC_MACROS_H_


#include <stdint.h>
#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <platform_specific_headers.h>
#include <mcuxClToolchain.h>

#include <mcuxClOsccaPkc_Types.h>
#include <internal/mcuxClOsccaPkc_SfrAccess.h>

/**********************************************************/
/* Macros for UPTR table and offsets                      */
/**********************************************************/
#define MCUXCLOSCCAPKC_PKCOFFSETTOPTR(offset)        (uint8_t *)(MCUXCLOSCCAPKC_PKC_RAM_BASEADDR + (offset))
#define MCUXCLOSCCAPKC_PTRTOPKCOFFSET(ptr)           (uint16_t)((uint32_t)(ptr) - MCUXCLOSCCAPKC_PKC_RAM_BASEADDR)

/**********************************************************/
/* Macros for parameter set                               */
/**********************************************************/
/**
 * @def MCUXCLOSCCAPKC_WAITFORGOANY
 * @brief busy wait until PKC GOANY status bit low
 */
#define MCUXCLOSCCAPKC_WAITFORGOANY()                                            \
    do{} while(0u != MCUXCLOSCCAPKC_SFR_BITREAD(STATUS, GOANY))

/**
 * @def MCUXCLOSCCAPKC_WAITFORFINISH
 * @brief busy wait until PKC calculation finishes
 */
#define MCUXCLOSCCAPKC_WAITFORFINISH()                                           \
    do{} while(0u != MCUXCLOSCCAPKC_SFR_BITREAD(STATUS, ACTIV))

/**
 * @def MCUXCLOSCCAPKC_OPERANDS
 * @brief set PKC operands XPTR, YPTR, ZPTR and RPTR
 */
#define MCUXCLOSCCAPKC_OPERANDS1(offset_x, offset_y, offset_z, offset_r)                                                               \
    do{                                                                                                                               \
        MCUXCLOSCCAPKC_SFR_WRITE(XYPTR1, ((uint32_t) (offset_y) << MCUXCLOSCCAPKC_SFR_BITPOS(XYPTR1, YPTR)) | (uint32_t) (offset_x));   \
		MCUXCLOSCCAPKC_SFR_WRITE(ZRPTR1, ((uint32_t) (offset_r) << MCUXCLOSCCAPKC_SFR_BITPOS(ZRPTR1, RPTR)) | (uint32_t) (offset_z));   \
    } while(0)

#define MCUXCLOSCCAPKC_OPERANDS2(offset_x, offset_y, offset_z, offset_r)                                                               \
    do{                                                                                                                               \
        MCUXCLOSCCAPKC_SFR_WRITE(XYPTR2, ((uint32_t) (offset_y) << MCUXCLOSCCAPKC_SFR_BITPOS(XYPTR2, YPTR)) | (uint32_t) (offset_x));   \
		MCUXCLOSCCAPKC_SFR_WRITE(ZRPTR2, ((uint32_t) (offset_r) << MCUXCLOSCCAPKC_SFR_BITPOS(ZRPTR2, RPTR)) | (uint32_t) (offset_z));   \
    } while(0)

/**
 * @def MCUXCLOSCCAPKC_OPERANDX
 * @brief set start address of X operand of selected parameter set
 */
#define MCUXCLOSCCAPKC_OPERANDX1(offset_x)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(XYPTR1, XPTR, (uint32_t)offset_x);                                             \
    } while(0)
#define MCUXCLOSCCAPKC_OPERANDX2(offset_x)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(XYPTR2, XPTR, (uint32_t)offset_x);                                             \
    } while(0)

/**
 * @def MCUXCLOSCCAPKC_OPERANDY
 * @brief set start address of Y operand of selected parameter set
 */
#define MCUXCLOSCCAPKC_OPERANDY1(offset_y)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(XYPTR1, YPTR, (uint32_t)offset_y);                                             \
    } while(0)
#define MCUXCLOSCCAPKC_OPERANDY2(offset_y)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(XYPTR2, YPTR, (uint32_t)offset_y);                                             \
    } while(0)

/**
 * @def MCUXCLOSCCAPKC_OPERANDZ
 * @brief set start address of Z operand in bytes or constant operand for ZFIX
 */
#define MCUXCLOSCCAPKC_OPERANDZ1(offset_z)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(ZRPTR1, ZPTR, (uint32_t)offset_z);                                             \
    } while(0)
#define MCUXCLOSCCAPKC_OPERANDZ2(offset_z)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(ZRPTR2, ZPTR, (uint32_t)offset_z);                                             \
    } while(0)

/**
 * @def MCUXCLOSCCAPKC_OPERANDR
 * @brief set start address of calculation result R of selected parameter set in bytes
 */
#define MCUXCLOSCCAPKC_OPERANDR1(offset_r)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(ZRPTR1, RPTR, (uint32_t)offset_r);                                             \
    } while(0)

#define MCUXCLOSCCAPKC_OPERANDR2(offset_r)                                                                          \
    do{                                                                                                            \
        MCUXCLOSCCAPKC_SFR_BITVALSET(ZRPTR2, RPTR, (uint32_t)offset_r);                                             \
    } while(0)
/**
 * @def MCUXCLOSCCAPKC_PS1_LEN
 * @brief Sets MCLEN and (OP)LEN of parameter set 1.
 */
#define MCUXCLOSCCAPKC_PS1_SETLENGTH(mclen, oplen)                                                                           \
    do{                                                                                                                     \
        MCUXCLOSCCAPKC_SFR_WRITE(LEN1, ((uint32_t) (mclen) << MCUXCLOSCCAPKC_SFR_BITPOS(LEN1, MCLEN)) | (uint32_t) (oplen) ); \
    } while(false)


/**
 * @def MCUXCLOSCCAPKC_PS2_LEN
 * @brief Sets MCLEN and (OP)LEN of parameter set 2.
 */
#define MCUXCLOSCCAPKC_PS2_SETLENGTH(mclen, oplen)                                                                           \
    do{                                                                                                                     \
        MCUXCLOSCCAPKC_SFR_WRITE(LEN2, ((uint32_t) (mclen) << MCUXCLOSCCAPKC_SFR_BITPOS(LEN2, MCLEN)) | (uint32_t) (oplen) ); \
    } while(false)


/**
 * @def MCUXCLOSCCAPKC_MODE
 * @brief set PKC mode
 */
#define MCUXCLOSCCAPKC_MODE1(mode)                                                    \
    do{                                                                              \
        MCUXCLOSCCAPKC_SFR_WRITE(MODE1, (uint32_t) mode);                             \
    } while(false)

#define MCUXCLOSCCAPKC_MODE2(mode)                                                    \
    do{                                                                              \
        MCUXCLOSCCAPKC_SFR_WRITE(MODE2, (uint32_t) mode);                             \
    } while(false)

#define MCUXCLOSCCAPKC_SETUPTRT(pUptrt)                                               \
    do{                                                                              \
        MCUXCLOSCCAPKC_SFR_WRITE(UPTRT, (uint32_t) pUptrt);                           \
    } while(false)

#define MCUXCLOSCCAPKC_GETUPTRT()            (uint16_t *)(MCUXCLOSCCAPKC_SFR_READ(UPTRT))

#define MCUXCLOSCCAPKC_SETWORDSIZE(redmul)                                            \
    do {                                                                             \
         MCUXCLOSCCAPKC_SFR_BITVALSET(CTRL, REDMUL, (uint32_t)redmul);                \
    } while(0)

#define MCUXCLOSCCAPKC_GETREDMUL()           (MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, REDMUL))

/**
 * @def MCUXCLOSCCAPKC_PS1_L0_Start
 * @brief start PKC kernel operation with parameter set 1
 */
#define MCUXCLOSCCAPKC_PS1_L0_START()                                                                          \
    do {                                                                                                      \
         MCUXCLOSCCAPKC_SFR_BITSET(CTRL, GOD1);                                                                \
    } while (0)


/**
 * @def MCUXCLOSCCAPKC_PS2_L0_Start
 * @brief start PKC kernel operation with parameter set 2
 */
#define MCUXCLOSCCAPKC_PS2_L0_START()                                                                          \
    do {                                                                                                      \
         MCUXCLOSCCAPKC_SFR_BITSET(CTRL, GOD2);                                                                \
    } while (0)

/**
 * @def MCUXCLOSCCAPKC_PS1_L1_Start
 * @brief execute PKC MC pattern with parameter set 1
 */
#define MCUXCLOSCCAPKC_PS1_L1_START()                                                                          \
    do {                                                                                                      \
         MCUXCLOSCCAPKC_SFR_BITSET(CTRL, GOM1);                                                                \
    } while (0)

/**
 * @def MCUXCLOSCCAPKC_PS2_L1_Start
 * @brief execute PKC MC pattern with parameter set 2
 */
#define MCUXCLOSCCAPKC_PS2_L1_START()                                                                          \
    do {                                                                                                      \
         MCUXCLOSCCAPKC_SFR_BITSET(CTRL, GOM2);                                                                \
    } while (0)

#define MCUXCLOSCCAPKC_START_FUP()                                                                             \
    do {                                                                                                      \
         MCUXCLOSCCAPKC_SFR_BITSET(CTRL, GOU);                                                                 \
    } while (false)

/**
 * @def MCUXCLOSCCAPKC_GetCarry
 * @brief retrieve PKCC carry flag
 */
#define MCUXCLOSCCAPKC_GETCARRY()                (MCUXCLOSCCAPKC_SFR_BITREAD(STATUS, CARRY) == 1U)

/**
 * @def MCUXCLOSCCAPKC_GetZero
 * @brief retrieve PKCC zero flag
 */
#define MCUXCLOSCCAPKC_GETZERO()                 (MCUXCLOSCCAPKC_SFR_BITREAD(STATUS, ZERO) == 1U)

#define MCUXCLOSCCAPKC_PS1_GETOPLEN()              (MCUXCLOSCCAPKC_SFR_BITREAD(LEN1, LEN))
#define MCUXCLOSCCAPKC_PS1_GETMCLEN()              (MCUXCLOSCCAPKC_SFR_BITREAD(LEN1, MCLEN))
#define MCUXCLOSCCAPKC_PS2_GETOPLEN()              (MCUXCLOSCCAPKC_SFR_BITREAD(LEN2, LEN))
#define MCUXCLOSCCAPKC_PS2_GETMCLEN()              (MCUXCLOSCCAPKC_SFR_BITREAD(LEN2, MCLEN))

#endif /*MCUXCLOSCCAPKC_MACROS_H_*/
