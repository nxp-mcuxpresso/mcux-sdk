/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClPkc_Macros.h
 * @brief Macros for accessing PKC hardware IP
 */


#ifndef MCUXCLPKC_MACROS_H_
#define MCUXCLPKC_MACROS_H_


#include <stdint.h>
#include <stdbool.h>
#include <platform_specific_headers.h>

#include <mcuxClPkc_Types.h>


/**********************************************************/
/* Internal PKC definitions                               */
/**********************************************************/
#define MCUXCLPKC_RAM_OFFSET_MASK    0x00001FFFu
#define MCUXCLPKC_LOG2_WORDSIZE  3u  ///< log2(PKC wordsize in byte)


/**********************************************************/
/* Helper macros                                          */
/**********************************************************/
/** Helper macro for writing PKC sfr. */
#define MCUXCLPKC_WRITESFR(sfr, value)  \
    do{ PKC->sfr = (value); } while(false)


/**********************************************************/
/* Macros for UPTR table and offsets                      */
/**********************************************************/
/** Sets the address of UPTRT (Universal pointer FUP table). */
#define MCUXCLPKC_SETUPTRT(pUptrt)  MCUXCLPKC_WRITESFR(UPTRT, (uint32_t) (pUptrt))
/** Gets the address of UPTRT (Universal pointer FUP table). */
#define MCUXCLPKC_GETUPTRT()  ((uint16_t *) PKC->UPTRT)

/** Converts CPU pointer to PKC offset. */
#define MCUXCLPKC_PTR2OFFSET(cpuPointer)  \
    ((uint16_t) ((uint32_t) (cpuPointer) & MCUXCLPKC_RAM_OFFSET_MASK))
/** Converts PKC offset to CPU pointer. */
#define MCUXCLPKC_OFFSET2PTR(pkcOffset)  \
    ((uint8_t *) ((uint32_t) (pkcOffset) | (uint32_t) MCUXCLPKC_RAM_START_ADDRESS))


/**********************************************************/
/* Macros for parameter set 1                             */
/**********************************************************/
#define MCUXCLPKC_PS1_SETMODE(mode)  MCUXCLPKC_WRITESFR(MODE1, mode)  ///< Sets either mode of L0 operation or address of L1 microcode of parameter set 1.
#define MCUXCLPKC_PS1_SETXY_REG(offsetY_offsetX)  MCUXCLPKC_WRITESFR(XYPTR1, offsetY_offsetX)  ///< Sets packed offsets to buffers of operands Y and X of parameter set 1.
#define MCUXCLPKC_PS1_SETZR_REG(offsetR_offsetZ)  MCUXCLPKC_WRITESFR(ZRPTR1, offsetR_offsetZ)  ///< Sets packed offsets to buffers of result R and operand Z of parameter set 1.
#define MCUXCLPKC_PS1_SETLENGTH_REG(mclen_oplen)  MCUXCLPKC_WRITESFR(LEN1, mclen_oplen)  ///< Sets packed MCLEN and (OP)LEN of parameter set 1.

#define MCUXCLPKC_PS1_SETXY(offsetX, offsetY)  \
    MCUXCLPKC_PS1_SETXY_REG( ((uint32_t) (offsetY) << 16) | (uint32_t) (offsetX) )  ///< Sets two offsets to buffers of operands Y and X of parameter set 1.
#define MCUXCLPKC_PS1_SETZR(offsetZ, offsetR)  \
    MCUXCLPKC_PS1_SETZR_REG( ((uint32_t) (offsetR) << 16) | (uint32_t) (offsetZ) )  ///< Sets two offsets to buffers of result R and operand Z of parameter set 1.
#define MCUXCLPKC_PS1_SETLENGTH(mclen, oplen)  \
    MCUXCLPKC_PS1_SETLENGTH_REG( ((uint32_t) (mclen) << 16) | (uint32_t) (oplen) )  ///< Sets MCLEN and (OP)LEN of parameter set 1.

#define MCUXCLPKC_PS1_GETLENGTH_REG()  (PKC->LEN1)          ///< Gets packed MCLEN and (OP)LEN of parameter set 1.
#define MCUXCLPKC_PS1_GETOPLEN()       (PKC->LEN1_b.LEN)    ///< Gets (OP)LEN of parameter set 1.
#define MCUXCLPKC_PS1_GETMCLEN()       (PKC->LEN1_b.MCLEN)  ///< Gets MCLEN of parameter set 1.

#define MCUXCLPKC_PS1_UNPACK_OPLEN(lenRegValue)  (((lenRegValue) & PKC_LEN1_LEN_Msk)   >> PKC_LEN1_LEN_Pos)
#define MCUXCLPKC_PS1_UNPACK_MCLEN(lenRegValue)  (((lenRegValue) & PKC_LEN1_MCLEN_Msk) >> PKC_LEN1_MCLEN_Pos)

#define MCUXCLPKC_PS1_START_L0()  MCUXCLPKC_WRITESFR(CTRL_b.GOD1, 1u)  ///< Starts PKC L0 operation with parameter set 1.
#define MCUXCLPKC_PS1_START_L1()  MCUXCLPKC_WRITESFR(CTRL_b.GOM1, 1u)  ///< Starts PKC L1 microcode with parameter set 1.


/**********************************************************/
/* Macros for parameter set 2                             */
/**********************************************************/
#define MCUXCLPKC_PS2_SETMODE(mode)  MCUXCLPKC_WRITESFR(MODE2, mode)  ///< Sets either mode of L0 operation or address of L1 microcode of parameter set 2.
#define MCUXCLPKC_PS2_SETXY_REG(offsetY_offsetX)  MCUXCLPKC_WRITESFR(XYPTR2, offsetY_offsetX)  ///< Sets packed offsets to buffers of operands Y and X of parameter set 2.
#define MCUXCLPKC_PS2_SETZR_REG(offsetR_offsetZ)  MCUXCLPKC_WRITESFR(ZRPTR2, offsetR_offsetZ)  ///< Sets packed offsets to buffers of result R and operand Z of parameter set 2.
#define MCUXCLPKC_PS2_SETLENGTH_REG(mclen_oplen)  MCUXCLPKC_WRITESFR(LEN2, mclen_oplen)  ///< Sets packed MCLEN and (OP)LEN of parameter set 2.

#define MCUXCLPKC_PS2_SETXY(offsetX, offsetY)  \
    MCUXCLPKC_PS2_SETXY_REG( ((uint32_t) (offsetY) << 16) | (uint32_t) (offsetX) )  ///< Sets two offsets to buffers of operands Y and X of parameter set 2.
#define MCUXCLPKC_PS2_SETZR(offsetZ, offsetR)  \
    MCUXCLPKC_PS2_SETZR_REG( ((uint32_t) (offsetR) << 16) | (uint32_t) (offsetZ) )  ///< Sets two offsets to buffers of result R and operand Z of parameter set 2.
#define MCUXCLPKC_PS2_SETLENGTH(mclen, oplen)  \
    MCUXCLPKC_PS2_SETLENGTH_REG( ((uint32_t) (mclen) << 16) | (uint32_t) (oplen) )  ///< Sets MCLEN and (OP)LEN of parameter set 2.

#define MCUXCLPKC_PS2_GETLENGTH_REG()  (PKC->LEN2)          ///< Gets packed MCLEN and (OP)LEN of parameter set 2.
#define MCUXCLPKC_PS2_GETOPLEN()       (PKC->LEN2_b.LEN)    ///< Gets (OP)LEN of parameter set 2.
#define MCUXCLPKC_PS2_GETMCLEN()       (PKC->LEN2_b.MCLEN)  ///< Gets MCLEN of parameter set 2.

#define MCUXCLPKC_PS2_START_L0()  MCUXCLPKC_WRITESFR(CTRL_b.GOD2, 1u)  ///< Starts PKC L0 operation with parameter set 2.
#define MCUXCLPKC_PS2_START_L1()  MCUXCLPKC_WRITESFR(CTRL_b.GOM2, 1u)  ///< Starts PKC L1 microcode with parameter set 2.


/**********************************************************/
/* Other macros                                           */
/**********************************************************/
/* Macros to wait PKC calculation. */
#define MCUXCLPKC_WAITFORFINISH()  \
    do{ while(1u == PKC->STATUS_b.ACTIV) {} } while(false)  ///< Wait until PKC finishes both on-going and pending calculations (if there is any).
#define MCUXCLPKC_WAITFORREADY()  \
    do{ while(1u == PKC->STATUS_b.GOANY) {} } while(false)  ///< Wait until PKC is ready to accept next calculation (i.e., no pending calculation).

/* Macro to wait PKC calculation and then get PKC status. */
#define MCUXCLPKC_WAITFORFINISH_GETSTATUS()  \
    ({  \
        uint32_t pkc_status_;  \
        do{  \
            pkc_status_ = PKC->STATUS;  \
        } while (0u != (pkc_status_ & PKC_STATUS_ACTIV_Msk));  \
        (pkc_status_);  \
    })

/* Macros to enable and disable GF2 calculation mode. */
#define MCUXCLPKC_ENABLEGF2()   MCUXCLPKC_WRITESFR(CTRL_b.GF2CONV, 1u)  ///< Enable GF2 calculation mode.
#define MCUXCLPKC_DISABLEGF2()  MCUXCLPKC_WRITESFR(CTRL_b.GF2CONV, 0u)  ///< Disable GF2 calculation mode.

/* Macros to get PKC carry and zero flags. */
#define MCUXCLPKC_GETCARRY()  (PKC->STATUS_b.CARRY)  ///< Get PKC carry flag.
#define MCUXCLPKC_GETZERO()   (PKC->STATUS_b.ZERO)   ///< Get PKC zero flag.
#define MCUXCLPKC_FLAG_ZERO     1u  ///< PKC zero flag: result is zero
#define MCUXCLPKC_FLAG_NONZERO  0u  ///< PKC zero flag: result is nonzero
#define MCUXCLPKC_FLAG_CARRY    1u  ///< PKC carry flag: carry occurred
#define MCUXCLPKC_FLAG_NOCARRY  0u  ///< PKC carry flag: carry not occurred
#define MCUXCLPKC_STATUS_CARRY_POS  PKC_STATUS_CARRY_Pos  ///< PKC carry flag position in PKC status word
#define MCUXCLPKC_STATUS_CARRY_MSK  PKC_STATUS_CARRY_Msk  ///< PKC carry flag mask
#define MCUXCLPKC_STATUS_ZERO_POS   PKC_STATUS_ZERO_Pos   ///< PKC zero flag position in PKC status word
#define MCUXCLPKC_STATUS_ZERO_MSK   PKC_STATUS_ZERO_Msk   ///< PKC zero flag mask


/** Macro to wait PKC calculation and then get carry flag. */
#define MCUXCLPKC_WAITFORFINISH_GETCARRY()  \
    ((MCUXCLPKC_WAITFORFINISH_GETSTATUS() >> PKC_STATUS_CARRY_Pos) & 0x1u)

/** Macro to wait PKC calculation and then get zero flag. */
#define MCUXCLPKC_WAITFORFINISH_GETZERO()  \
    ((MCUXCLPKC_WAITFORFINISH_GETSTATUS() >> PKC_STATUS_ZERO_Pos) & 0x1u)


/**********************************************************/
/* Other macro                                            */
/**********************************************************/
/* Workaround for niobe4a_cosim, to avoid CPU and PKC concurrently accessing to PKC workarea. */
#define MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND()  do{} while(false)


#endif /* MCUXCLPKC_MACROS_H_ */
