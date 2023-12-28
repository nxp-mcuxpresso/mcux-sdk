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
 * @file  mcuxClPkc_Operations.h
 * @brief Mnemonics and macros for PKC calculation
 */


#ifndef MCUXCLPKC_OPERATIONS_H_
#define MCUXCLPKC_OPERATIONS_H_


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc_Functions.h>
#include <internal/mcuxClPkc_Macros.h>


/**
 * In order to ease CLib programming, improve code readability and reduce maintenance cost,
 * please use help macros, e.g., MCUXCLPKC_FP_CALC_OP1_MUL(...) to start a PKC operation,
 * and corresponding function identifiers, e.g.,  MCUXCLPKC_FP_CALLED_CALC_OP1_MUL in FP balancing.
 */


/**********************************************************/
/* Mnemonic of PKC L0 operations (OP)                     */
/**********************************************************/
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "For completeness, all PKC operations are defined.")
#define MCUXCLPKC_OP_MUL            0x00u  ///< Pure multiplication of a PKC word X0 by a MPI Y
#define MCUXCLPKC_OP_MAC            0x02u  ///< Multiply-Accumulate of a PKC word X0 with a MPI Y and a MPI Z
#define MCUXCLPKC_OP_MAC_NEG        0x03u  ///< Multiply-Subtract   of a PKC word X0 with a MPI Y and a MPI Z
#define MCUXCLPKC_OP_MUL_GF2        0x04u  ///< Pure multiplication of a PKC word X0 by a MPI Y over GF(2)
#define MCUXCLPKC_OP_MAC_GF2        0x06u  ///< Multiply-Accumulate of a PKC word X0 with a MPI Y and a MPI Z over GF(2)
#define MCUXCLPKC_OP_NEG            0x09u  ///< Two's complement of MPI Z
#define MCUXCLPKC_OP_ADD            0x0Au  ///< Addition    of a MPI Y with a MPI Z
#define MCUXCLPKC_OP_SUB            0x0Bu  ///< Subtraction of a MPI Y with a MPI Z
#define MCUXCLPKC_OP_AND            0x0Du  ///< Logical AND of a MPI Y with a MPI Z
#define MCUXCLPKC_OP_OR             0x0Eu  ///< Logical OR  of a MPI Y with a MPI Z
#define MCUXCLPKC_OP_XOR            0x0Fu  ///< Logical XOR of a MPI Y with a MPI Z
#define MCUXCLPKC_OP_MAC_CONST_GF2  0x10u  ///< Multiply-Accumulate of a PKC word X0 with a MPI Y and a CONST over GF(2)
#define MCUXCLPKC_OP_MAC_CONST      0x12u  ///< Multiply-Accumulate of a PKC word X0 with a MPI Y and a CONST
#define MCUXCLPKC_OP_MAC_NEG_CONST  0x13u  ///< Multiply-Subtract   of a PKC word X0 with a MPI Y and a CONST
#define MCUXCLPKC_OP_SHL            0x14u  ///< Shift left   of a MPI Y by CONST positions
#define MCUXCLPKC_OP_SHR            0x15u  ///< Shift right  of a MPI Y by CONST positions
#define MCUXCLPKC_OP_ROTL           0x16u  ///< Rotate left  of a MPI Y by CONST positions
#define MCUXCLPKC_OP_ROTR           0x17u  ///< Rotate right of a MPI Y by CONST positions
#define MCUXCLPKC_OP_ADD_CONST      0x1Au  ///< Addition    of a MPI Y with a CONST
#define MCUXCLPKC_OP_SUB_CONST      0x1Bu  ///< Subtraction of a MPI Y with a CONST
#define MCUXCLPKC_OP_AND_CONST      0x1Du  ///< Logical AND of a MPI Y with a CONST
#define MCUXCLPKC_OP_OR_CONST       0x1Eu  ///< Logical OR  of a MPI Y with a CONST
#define MCUXCLPKC_OP_XOR_CONST      0x1Fu  ///< Logical XOR of a MPI Y with a CONST
#define MCUXCLPKC_OP_MUL1           0x20u  ///< Plain multiplication of 1 PKC word modulo word size
#define MCUXCLPKC_OP_MACC           0x22u  ///< Multiply-Accumulate  of a PKC word X0 with a MPI Y and a MPI Z extended by carry overhead
#define MCUXCLPKC_OP_MUL1_GF2       0x24u  ///< Plain multiplication of 1 PKC word modulo word size over GF(2)
#define MCUXCLPKC_OP_MACC_GF2       0x26u  ///< Multiply-Accumulate  of a PKC word X0 with a MPI Y and a MPI Z over GF(2)
#define MCUXCLPKC_OP_ADDC           0x2Au  ///< Addition    of a MPI Y incl. carry overhead with a MPI Z
#define MCUXCLPKC_OP_SUBC           0x2Bu  ///< Subtraction of a MPI Y incl. carry overhead with a MPI Z
#define MCUXCLPKC_OP_LSB0s          0x2Du  ///< Determines the number of consecutive zero bits (up to 8) of MPI Z starting from LSB
#define MCUXCLPKC_OP_MSB0s          0x2Fu  ///< Determines the number of consecutive zero bits (up to 8) of MPI Z starting from MSB
#define MCUXCLPKC_OP_CONST          0x3Eu  ///< Initializes memory with a CONST
#define MCUXCLPKC_OP_CMP            0x4Bu  ///< Compares two MPIs by subtracting MPI Z from MPI Y
#define MCUXCLPKC_OP_MACCR          0x62u  ///< Multiply-Accumulate of the internal register Reg_i with a MPI Y and a MPI Z extended by carry
#define MCUXCLPKC_OP_MACCR_GF2      0x66u  ///< Multiply-Accumulate of the internal register Reg_i with a MPI Y and a MPI Z over GF(2)
#define MCUXCLPKC_OP_ADD_Z0         0x6Au  ///< Addition of a MPI Y with a single PKC word Z0
#define MCUXCLPKC_OP_XOR_Z0         0x6Fu  ///< XOR      of a MPI Y with a single PKC word Z0
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)


/**********************************************************/
/* Mnemonic of PKC L1 microcodes (MC)                     */
/**********************************************************/
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "For completeness, all PKC operations are defined.")
#define MCUXCLPKC_MC_MM             0x00u  ///< Modular Multiplication of a MPI X with a MPI Y modulo a MPI Z (Montgomery Reduction)
#define MCUXCLPKC_MC_MM_GF2         0x00u  ///< Modular Multiplication of a MPI X with a MPI Y modulo a MPI Z (Montgomery Reduction) over GF(2)
#define MCUXCLPKC_MC_PM             0x13u  ///< Plain Multiplication of a MPI X with a MPI Y
#define MCUXCLPKC_MC_PM_GF2         0x13u  ///< Plain Multiplication of a MPI X with a MPI Y over GF(2)
#define MCUXCLPKC_MC_PMA            0x1Du  ///< Plain Multiplication with Addition of a MPI X with a MPI Y and a MPI Z
#define MCUXCLPKC_MC_PMA_GF2        0x1Du  ///< Plain Multiplication with Addition of a MPI X with a MPI Y and a MPI Z over GF(2)
#define MCUXCLPKC_MC_MA             0x21u  ///< Modular Addition    of a MPI Y with a MPI Z modulo a MPI X
#define MCUXCLPKC_MC_MS             0x2Au  ///< Modular Subtraction of a MPI Y with a MPI Z modulo a MPI X
#define MCUXCLPKC_MC_MR             0x33u  ///< Modular Reduction of a MPI X and a MPI Z
#define MCUXCLPKC_MC_MR_GF2         0x33u  ///< Modular Reduction of a MPI X and a MPI Z over GF(2)

#define MCUXCLPKC_MC_MMP2           0x53u  ///< Modular Multiplication of a MPI X and a MPI Y modulo 2^LEN(Y)
#define MCUXCLPKC_MC_MMAP2          0x5Au  ///< Modular Multiplication with Addition of a MPI X with a MPI Y and a MPI Z modulo 2^LEN(Y)
#define MCUXCLPKC_MC_MI             0x5Du  ///< Modular Inversion of a MPI Y module a MPI X
#define MCUXCLPKC_MC_MI_GF2         0x5Du  ///< Modular Inversion of a MPI Y module a MPI X over GF(2)
#define MCUXCLPKC_MC_PM_PATCH       0x9Du  ///< Plain Multiplication of a MPI X with a MPI Y (patched version)
#define MCUXCLPKC_MC_PM_PATCH_GF2   0x9Du  ///< Plain Multiplication of a MPI X with a MPI Y over GF(2) (patched version)
#define MCUXCLPKC_MC_GCD            0xA7u  ///< Greatest common divider (GCD) of MPI Y and MPI Z
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)


/**********************************************************/
/* Macros for encoding L0/L1 and parameter set 1/2        */
/**********************************************************/
#define MCUXCLPKC_PARAM_L0   0x00u
#define MCUXCLPKC_PARAM_L1   0x80u
#define MCUXCLPKC_PARAM_PS1  0x00u
#define MCUXCLPKC_PARAM_PS2  0x40u
#define MCUXCLPKC_PARAM_OP1  ((uint16_t) MCUXCLPKC_PARAM_L0 | (uint16_t) MCUXCLPKC_PARAM_PS1)
#define MCUXCLPKC_PARAM_OP2  ((uint16_t) MCUXCLPKC_PARAM_L0 | (uint16_t) MCUXCLPKC_PARAM_PS2)
#define MCUXCLPKC_PARAM_MC1  ((uint16_t) MCUXCLPKC_PARAM_L1 | (uint16_t) MCUXCLPKC_PARAM_PS1)
#define MCUXCLPKC_PARAM_MC2  ((uint16_t) MCUXCLPKC_PARAM_L1 | (uint16_t) MCUXCLPKC_PARAM_PS2)

#define MCUXCLPKC_PARAMMODE_OP1(symbo)  ((MCUXCLPKC_PARAM_OP1 << 8) | MCUXCLPKC_OP_ ## symbo)
#define MCUXCLPKC_PARAMMODE_OP2(symbo)  ((MCUXCLPKC_PARAM_OP2 << 8) | MCUXCLPKC_OP_ ## symbo)
#define MCUXCLPKC_PARAMMODE_MC1(symbo)  ((MCUXCLPKC_PARAM_MC1 << 8) | MCUXCLPKC_MC_ ## symbo)
#define MCUXCLPKC_PARAMMODE_MC2(symbo)  ((MCUXCLPKC_PARAM_MC2 << 8) | MCUXCLPKC_MC_ ## symbo)


/**********************************************************/
/* Macros to start PKC calculation w/o flow protection    */
/**********************************************************/
#define MCUXCLPKC_CALC_OP1Z(symbo,R,X,Y,Z)  mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_OP1(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z))
#define MCUXCLPKC_CALC_OP2Z(symbo,R,X,Y,Z)  mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_OP2(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z))
#define MCUXCLPKC_CALC_MC1Z(symbo,R,X,Y,Z)  mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_MC1(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z))
#define MCUXCLPKC_CALC_MC2Z(symbo,R,X,Y,Z)  mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_MC2(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z))
#define MCUXCLPKC_CALC_OP1C(symbo,R,X,Y,C)  mcuxClPkc_CalcConst(MCUXCLPKC_PARAMMODE_OP1(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,C))
#define MCUXCLPKC_CALC_OP2C(symbo,R,X,Y,C)  mcuxClPkc_CalcConst(MCUXCLPKC_PARAMMODE_OP2(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,C))


/**********************************************************/
/* Macros to start PKC calculation with flow protection   */
/**********************************************************/
#define MCUXCLPKC_FP_CALC_OP1Z(symbo,R,X,Y,Z)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_OP1(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z)))
#define MCUXCLPKC_FP_CALC_OP2Z(symbo,R,X,Y,Z)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_OP2(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z)))
#define MCUXCLPKC_FP_CALC_MC1Z(symbo,R,X,Y,Z)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_MC1(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z)))
#define MCUXCLPKC_FP_CALC_MC2Z(symbo,R,X,Y,Z)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_MC2(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,Z)))
#define MCUXCLPKC_FP_CALC_OP1C(symbo,R,X,Y,C)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_CalcConst(MCUXCLPKC_PARAMMODE_OP1(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,C)))
#define MCUXCLPKC_FP_CALC_OP2C(symbo,R,X,Y,C)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_CalcConst(MCUXCLPKC_PARAMMODE_OP2(symbo), MCUXCLPKC_PACKARGS4(R,X,Y,C)))


/**********************************************************/
/* Helper macros to start specified PKC calculation,      */
/* without flow protection                                */
/**********************************************************/
/* Argument(s) not used is set to R (or other index provided). */
/* Or if Z is not used, call mcuxClPkc_CalcConst(...).          */

/* L0 operation (OP) with parameter set 1. */
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "For completeness, all PKC operations are defined.")
#define MCUXCLPKC_CALC_OP1_MUL(R,X,Y)              MCUXCLPKC_CALC_OP1C(MUL,           R,X,Y,0)  /* Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP1_MAC(R,X,Y,Z)            MCUXCLPKC_CALC_OP1Z(MAC,           R,X,Y,Z)
#define MCUXCLPKC_CALC_OP1_MAC_NEG(R,X,Y,Z)        MCUXCLPKC_CALC_OP1Z(MAC_NEG,       R,X,Y,Z)
#define MCUXCLPKC_CALC_OP1_MUL_GF2(R,X,Y)          MCUXCLPKC_CALC_OP1C(MUL_GF2,       R,X,Y,0)  /* Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP1_MAC_GF2(R,X,Y,Z)        MCUXCLPKC_CALC_OP1Z(MAC_GF2,       R,X,Y,Z)
#define MCUXCLPKC_CALC_OP1_NEG(R,Z)                MCUXCLPKC_CALC_OP1Z(NEG,           R,R,R,Z)  /* X and Y not used */
#define MCUXCLPKC_CALC_OP1_ADD(R,Y,Z)              MCUXCLPKC_CALC_OP1Z(ADD,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_SUB(R,Y,Z)              MCUXCLPKC_CALC_OP1Z(SUB,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_AND(R,Y,Z)              MCUXCLPKC_CALC_OP1Z(AND,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_OR(R,Y,Z)               MCUXCLPKC_CALC_OP1Z(OR,            R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_XOR(R,Y,Z)              MCUXCLPKC_CALC_OP1Z(XOR,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_MAC_CONST_GF2(R,X,Y,C)  MCUXCLPKC_CALC_OP1C(MAC_CONST_GF2, R,X,Y,C)
#define MCUXCLPKC_CALC_OP1_MAC_CONST(R,X,Y,C)      MCUXCLPKC_CALC_OP1C(MAC_CONST,     R,X,Y,C)
#define MCUXCLPKC_CALC_OP1_MAC_NEG_CONST(R,X,Y,C)  MCUXCLPKC_CALC_OP1C(MAC_NEG_CONST, R,X,Y,C)
#define MCUXCLPKC_CALC_OP1_SHL(R,Y,C)              MCUXCLPKC_CALC_OP1C(SHL,           R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_SHR(R,Y,C)              MCUXCLPKC_CALC_OP1C(SHR,           R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_ROTL(R,Y,C)             MCUXCLPKC_CALC_OP1C(ROTL,          R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_ROTR(R,Y,C)             MCUXCLPKC_CALC_OP1C(ROTR,          R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_ADD_CONST(R,Y,C)        MCUXCLPKC_CALC_OP1C(ADD_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_SUB_CONST(R,Y,C)        MCUXCLPKC_CALC_OP1C(SUB_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_AND_CONST(R,Y,C)        MCUXCLPKC_CALC_OP1C(AND_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_OR_CONST(R,Y,C)         MCUXCLPKC_CALC_OP1C(OR_CONST,      R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_XOR_CONST(R,Y,C)        MCUXCLPKC_CALC_OP1C(XOR_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP1_MUL1(X,Y)               MCUXCLPKC_CALC_OP1C(MUL1,          Y,X,Y,0)  /* R and Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP1_MACC(R,X,Y,Z)           MCUXCLPKC_CALC_OP1Z(MACC,          R,X,Y,Z)
#define MCUXCLPKC_CALC_OP1_MUL1_GF2(X,Y)           MCUXCLPKC_CALC_OP1C(MUL1_GF2,      Y,X,Y,0)  /* R and Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP1_MACC_GF2(R,X,Y,Z)       MCUXCLPKC_CALC_OP1Z(MACC_GF2,      R,X,Y,Z)
#define MCUXCLPKC_CALC_OP1_ADDC(R,Y,Z)             MCUXCLPKC_CALC_OP1Z(ADDC,          R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_SUBC(R,Y,Z)             MCUXCLPKC_CALC_OP1Z(SUBC,          R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_LSB0s(Z)                MCUXCLPKC_CALC_OP1Z(LSB0s,         Z,Z,Z,Z)  /* R, X and Y not used */
#define MCUXCLPKC_CALC_OP1_MSB0s(Z)                MCUXCLPKC_CALC_OP1Z(MSB0s,         Z,Z,Z,Z)  /* R, X and Y not used */
#define MCUXCLPKC_CALC_OP1_CONST(R,C)              MCUXCLPKC_CALC_OP1C(CONST,         R,R,R,C)  /* X and Y not used */
#define MCUXCLPKC_CALC_OP1_CMP(Y,Z)                MCUXCLPKC_CALC_OP1Z(CMP,           Y,Z,Y,Z)  /* R and X not used */
#define MCUXCLPKC_CALC_OP1_MACCR(R,Y,Z)            MCUXCLPKC_CALC_OP1Z(MACCR,         R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_MACCR_GF2(R,Y,Z)        MCUXCLPKC_CALC_OP1Z(MACCR_GF2,     R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_ADD_Z0(R,Y,Z)           MCUXCLPKC_CALC_OP1Z(ADD_Z0,        R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP1_XOR_Z0(R,Y,Z)           MCUXCLPKC_CALC_OP1Z(XOR_Z0,        R,R,Y,Z)  /* X not used */

/* L1 microcode (MC) with parameter set 1. */
#define MCUXCLPKC_CALC_MC1_MM(R,X,Y,N)             MCUXCLPKC_CALC_MC1Z(MM,            R,X,Y,N)
#define MCUXCLPKC_CALC_MC1_MM_GF2(R,X,Y,N)         MCUXCLPKC_CALC_MC1Z(MM_GF2,        R,X,Y,N)
#define MCUXCLPKC_CALC_MC1_PM(R,X,Y)               MCUXCLPKC_CALC_MC1Z(PM,            R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC1_PM_GF2(R,X,Y)           MCUXCLPKC_CALC_MC1Z(PM_GF2,        R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC1_PMA(R,X,Y,Z)            MCUXCLPKC_CALC_MC1Z(PMA,           R,X,Y,Z)
#define MCUXCLPKC_CALC_MC1_PMA_GF2(R,X,Y,Z)        MCUXCLPKC_CALC_MC1Z(PMA_GF2,       R,X,Y,Z)
#define MCUXCLPKC_CALC_MC1_MA(R,Y,Z,N)             MCUXCLPKC_CALC_MC1Z(MA,            R,N,Y,Z)
#define MCUXCLPKC_CALC_MC1_MS(R,Y,Z,N)             MCUXCLPKC_CALC_MC1Z(MS,            R,N,Y,Z)
#define MCUXCLPKC_CALC_MC1_MR(R,X,N)               MCUXCLPKC_CALC_MC1Z(MR,            R,X,R,N)  /* Y not used */
#define MCUXCLPKC_CALC_MC1_MR_GF2(R,X,N)           MCUXCLPKC_CALC_MC1Z(MR_GF2,        R,X,R,N)  /* Y not used */
#define MCUXCLPKC_CALC_MC1_MMP2(R,X,Y)             MCUXCLPKC_CALC_MC1Z(MMP2,          R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC1_MMAP2(R,X,Y,Z)          MCUXCLPKC_CALC_MC1Z(MMAP2,         R,X,Y,Z)
#define MCUXCLPKC_CALC_MC1_MI(R,Y,N,Z)             MCUXCLPKC_CALC_MC1Z(MI,            R,N,Y,Z)  /* Z buffer needs to be initialized to 1 */
#define MCUXCLPKC_CALC_MC1_MI_GF2(R,Y,N,Z)         MCUXCLPKC_CALC_MC1Z(MI_GF2,        R,N,Y,Z)  /* Z buffer needs to be initialized to 1 */
#define MCUXCLPKC_CALC_MC1_PM_PATCH(R,X,Y)         MCUXCLPKC_CALC_MC1Z(PM_PATCH,      R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC1_PM_PATCH_GF2(R,X,Y)     MCUXCLPKC_CALC_MC1Z(PM_PATCH_GF2,  R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC1_GCD(Y,Z)                MCUXCLPKC_CALC_MC1Z(GCD,           Z,Y,Y,Z)  /* X = Y, R = Z (result in-place) */

/* L0 operation (OP) with parameter set 2. */
#define MCUXCLPKC_CALC_OP2_MUL(R,X,Y)              MCUXCLPKC_CALC_OP2C(MUL,           R,X,Y,0)  /* Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP2_MAC(R,X,Y,Z)            MCUXCLPKC_CALC_OP2Z(MAC,           R,X,Y,Z)
#define MCUXCLPKC_CALC_OP2_MAC_NEG(R,X,Y,Z)        MCUXCLPKC_CALC_OP2Z(MAC_NEG,       R,X,Y,Z)
#define MCUXCLPKC_CALC_OP2_MUL_GF2(R,X,Y)          MCUXCLPKC_CALC_OP2C(MUL_GF2,       R,X,Y,0)  /* Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP2_MAC_GF2(R,X,Y,Z)        MCUXCLPKC_CALC_OP2Z(MAC_GF2,       R,X,Y,Z)
#define MCUXCLPKC_CALC_OP2_NEG(R,Z)                MCUXCLPKC_CALC_OP2Z(NEG,           R,R,R,Z)  /* X and Y not used */
#define MCUXCLPKC_CALC_OP2_ADD(R,Y,Z)              MCUXCLPKC_CALC_OP2Z(ADD,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_SUB(R,Y,Z)              MCUXCLPKC_CALC_OP2Z(SUB,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_AND(R,Y,Z)              MCUXCLPKC_CALC_OP2Z(AND,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_OR(R,Y,Z)               MCUXCLPKC_CALC_OP2Z(OR,            R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_XOR(R,Y,Z)              MCUXCLPKC_CALC_OP2Z(XOR,           R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_MAC_CONST_GF2(R,X,Y,C)  MCUXCLPKC_CALC_OP2C(MAC_CONST_GF2, R,X,Y,C)
#define MCUXCLPKC_CALC_OP2_MAC_CONST(R,X,Y,C)      MCUXCLPKC_CALC_OP2C(MAC_CONST,     R,X,Y,C)
#define MCUXCLPKC_CALC_OP2_MAC_NEG_CONST(R,X,Y,C)  MCUXCLPKC_CALC_OP2C(MAC_NEG_CONST, R,X,Y,C)
#define MCUXCLPKC_CALC_OP2_SHL(R,Y,C)              MCUXCLPKC_CALC_OP2C(SHL,           R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_SHR(R,Y,C)              MCUXCLPKC_CALC_OP2C(SHR,           R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_ROTL(R,Y,C)             MCUXCLPKC_CALC_OP2C(ROTL,          R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_ROTR(R,Y,C)             MCUXCLPKC_CALC_OP2C(ROTR,          R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_ADD_CONST(R,Y,C)        MCUXCLPKC_CALC_OP2C(ADD_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_SUB_CONST(R,Y,C)        MCUXCLPKC_CALC_OP2C(SUB_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_AND_CONST(R,Y,C)        MCUXCLPKC_CALC_OP2C(AND_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_OR_CONST(R,Y,C)         MCUXCLPKC_CALC_OP2C(OR_CONST,      R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_XOR_CONST(R,Y,C)        MCUXCLPKC_CALC_OP2C(XOR_CONST,     R,R,Y,C)  /* X not used */
#define MCUXCLPKC_CALC_OP2_MUL1(X,Y)               MCUXCLPKC_CALC_OP2C(MUL1,          Y,X,Y,0)  /* R and Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP2_MACC(R,X,Y,Z)           MCUXCLPKC_CALC_OP2Z(MACC,          R,X,Y,Z)
#define MCUXCLPKC_CALC_OP2_MUL1_GF2(X,Y)           MCUXCLPKC_CALC_OP2C(MUL1_GF2,      Y,X,Y,0)  /* R and Z not used, use CalcConst */
#define MCUXCLPKC_CALC_OP2_MACC_GF2(R,X,Y,Z)       MCUXCLPKC_CALC_OP2Z(MACC_GF2,      R,X,Y,Z)
#define MCUXCLPKC_CALC_OP2_ADDC(R,Y,Z)             MCUXCLPKC_CALC_OP2Z(ADDC,          R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_SUBC(R,Y,Z)             MCUXCLPKC_CALC_OP2Z(SUBC,          R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_LSB0s(Z)                MCUXCLPKC_CALC_OP2Z(LSB0s,         Z,Z,Z,Z)  /* R, X and Y not used */
#define MCUXCLPKC_CALC_OP2_MSB0s(Z)                MCUXCLPKC_CALC_OP2Z(MSB0s,         Z,Z,Z,Z)  /* R, X and Y not used */
#define MCUXCLPKC_CALC_OP2_CONST(R,C)              MCUXCLPKC_CALC_OP2C(CONST,         R,R,R,C)  /* X and Y not used */
#define MCUXCLPKC_CALC_OP2_CMP(Y,Z)                MCUXCLPKC_CALC_OP2Z(CMP,           Y,Z,Y,Z)  /* R and X not used */
#define MCUXCLPKC_CALC_OP2_MACCR(R,Y,Z)            MCUXCLPKC_CALC_OP2Z(MACCR,         R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_MACCR_GF2(R,Y,Z)        MCUXCLPKC_CALC_OP2Z(MACCR_GF2,     R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_ADD_Z0(R,Y,Z)           MCUXCLPKC_CALC_OP2Z(ADD_Z0,        R,R,Y,Z)  /* X not used */
#define MCUXCLPKC_CALC_OP2_XOR_Z0(R,Y,Z)           MCUXCLPKC_CALC_OP2Z(XOR_Z0,        R,R,Y,Z)  /* X not used */

/* L1 microcode (MC) with parameter set 2. */
#define MCUXCLPKC_CALC_MC2_MM(R,X,Y,N)             MCUXCLPKC_CALC_MC2Z(MM,            R,X,Y,N)
#define MCUXCLPKC_CALC_MC2_MM_GF2(R,X,Y,N)         MCUXCLPKC_CALC_MC2Z(MM_GF2,        R,X,Y,N)
#define MCUXCLPKC_CALC_MC2_PM(R,X,Y)               MCUXCLPKC_CALC_MC2Z(PM,            R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC2_PM_GF2(R,X,Y)           MCUXCLPKC_CALC_MC2Z(PM_GF2,        R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC2_PMA(R,X,Y,Z)            MCUXCLPKC_CALC_MC2Z(PMA,           R,X,Y,Z)
#define MCUXCLPKC_CALC_MC2_PMA_GF2(R,X,Y,Z)        MCUXCLPKC_CALC_MC2Z(PMA_GF2,       R,X,Y,Z)
#define MCUXCLPKC_CALC_MC2_MA(R,Y,Z,N)             MCUXCLPKC_CALC_MC2Z(MA,            R,N,Y,Z)
#define MCUXCLPKC_CALC_MC2_MS(R,Y,Z,N)             MCUXCLPKC_CALC_MC2Z(MS,            R,N,Y,Z)
#define MCUXCLPKC_CALC_MC2_MR(R,X,N)               MCUXCLPKC_CALC_MC2Z(MR,            R,X,R,N)  /* Y not used */
#define MCUXCLPKC_CALC_MC2_MR_GF2(R,X,N)           MCUXCLPKC_CALC_MC2Z(MR_GF2,        R,X,R,N)  /* Y not used */
#define MCUXCLPKC_CALC_MC2_MMP2(R,X,Y)             MCUXCLPKC_CALC_MC2Z(MMP2,          R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC2_MMAP2(R,X,Y,Z)          MCUXCLPKC_CALC_MC2Z(MMAP2,         R,X,Y,Z)
#define MCUXCLPKC_CALC_MC2_MI(R,Y,N,Z)             MCUXCLPKC_CALC_MC2Z(MI,            R,N,Y,Z)  /* Z buffer needs to be initialized to 1 */
#define MCUXCLPKC_CALC_MC2_MI_GF2(R,Y,N,Z)         MCUXCLPKC_CALC_MC2Z(MI_GF2,        R,N,Y,Z)  /* Z buffer needs to be initialized to 1 */
#define MCUXCLPKC_CALC_MC2_PM_PATCH(R,X,Y)         MCUXCLPKC_CALC_MC2Z(PM_PATCH,      R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC2_PM_PATCH_GF2(R,X,Y)     MCUXCLPKC_CALC_MC2Z(PM_PATCH_GF2,  R,X,Y,R)  /* Z not used */
#define MCUXCLPKC_CALC_MC2_GCD(Y,Z)                MCUXCLPKC_CALC_MC2Z(GCD,           Z,Y,Y,Z)  /* X = Y, R = Z (result in-place) */
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)


/**********************************************************/
/* Helper macros to start specified PKC calculation,      */
/* with flow protection                                   */
/**********************************************************/
/* Argument(s) not used is set to R (or other index provided). */
/* Or if Z is not used, call mcuxClPkc_CalcConst(...).          */

/* L0 operation (OP) with parameter set 1, supporting flow protection. */
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "For completeness, all PKC operations are defined.")
#define MCUXCLPKC_FP_CALC_OP1_MUL(R,X,Y)           MCUXCLPKC_FP_CALC_OP1C(MUL,        R,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP1_MAC(R,X,Y,Z)         MCUXCLPKC_FP_CALC_OP1Z(MAC,        R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_MAC_NEG(R,X,Y,Z)     MCUXCLPKC_FP_CALC_OP1Z(MAC_NEG,    R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_MUL_GF2(R,X,Y)       MCUXCLPKC_FP_CALC_OP1C(MUL_GF2,    R,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP1_MAC_GF2(R,X,Y,Z)     MCUXCLPKC_FP_CALC_OP1Z(MAC_GF2,    R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_NEG(R,Z)             MCUXCLPKC_FP_CALC_OP1Z(NEG,        R,R,R,Z)
#define MCUXCLPKC_FP_CALC_OP1_ADD(R,Y,Z)           MCUXCLPKC_FP_CALC_OP1Z(ADD,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_SUB(R,Y,Z)           MCUXCLPKC_FP_CALC_OP1Z(SUB,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_AND(R,Y,Z)           MCUXCLPKC_FP_CALC_OP1Z(AND,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_OR(R,Y,Z)            MCUXCLPKC_FP_CALC_OP1Z(OR,         R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_XOR(R,Y,Z)           MCUXCLPKC_FP_CALC_OP1Z(XOR,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_MAC_CONST_GF2(R,X,Y,C)  MCUXCLPKC_FP_CALC_OP1C(MAC_CONST_GF2, R,X,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_MAC_CONST(R,X,Y,C)   MCUXCLPKC_FP_CALC_OP1C(MAC_CONST,  R,X,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_MAC_NEG_CONST(R,X,Y,C)  MCUXCLPKC_FP_CALC_OP1C(MAC_NEG_CONST, R,X,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_SHL(R,Y,C)           MCUXCLPKC_FP_CALC_OP1C(SHL,        R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_SHR(R,Y,C)           MCUXCLPKC_FP_CALC_OP1C(SHR,        R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_ROTL(R,Y,C)          MCUXCLPKC_FP_CALC_OP1C(ROTL,       R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_ROTR(R,Y,C)          MCUXCLPKC_FP_CALC_OP1C(ROTR,       R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_ADD_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP1C(ADD_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_SUB_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP1C(SUB_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_AND_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP1C(AND_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_OR_CONST(R,Y,C)      MCUXCLPKC_FP_CALC_OP1C(OR_CONST,   R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_XOR_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP1C(XOR_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP1_MUL1(X,Y)            MCUXCLPKC_FP_CALC_OP1C(MUL1,       Y,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP1_MACC(R,X,Y,Z)        MCUXCLPKC_FP_CALC_OP1Z(MACC,       R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_MUL1_GF2(X,Y)        MCUXCLPKC_FP_CALC_OP1C(MUL1_GF2,   Y,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP1_MACC_GF2(R,X,Y,Z)    MCUXCLPKC_FP_CALC_OP1Z(MACC_GF2,   R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_ADDC(R,Y,Z)          MCUXCLPKC_FP_CALC_OP1Z(ADDC,       R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_SUBC(R,Y,Z)          MCUXCLPKC_FP_CALC_OP1Z(SUBC,       R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_LSB0s(Z)             MCUXCLPKC_FP_CALC_OP1Z(LSB0s,      Z,Z,Z,Z)
#define MCUXCLPKC_FP_CALC_OP1_MSB0s(Z)             MCUXCLPKC_FP_CALC_OP1Z(MSB0s,      Z,Z,Z,Z)
#define MCUXCLPKC_FP_CALC_OP1_CONST(R,C)           MCUXCLPKC_FP_CALC_OP1C(CONST,      R,R,R,C)
#define MCUXCLPKC_FP_CALC_OP1_CMP(Y,Z)             MCUXCLPKC_FP_CALC_OP1Z(CMP,        Y,Z,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_MACCR(R,Y,Z)         MCUXCLPKC_FP_CALC_OP1Z(MACCR,      R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_MACCR_GF2(R,Y,Z)     MCUXCLPKC_FP_CALC_OP1Z(MACCR_GF2,  R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_ADD_Z0(R,Y,Z)        MCUXCLPKC_FP_CALC_OP1Z(ADD_Z0,     R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP1_XOR_Z0(R,Y,Z)        MCUXCLPKC_FP_CALC_OP1Z(XOR_Z0,     R,R,Y,Z)

/* L1 microcode (MC) with parameter set 1, supporting flow protection. */
#define MCUXCLPKC_FP_CALC_MC1_MM(R,X,Y,N)          MCUXCLPKC_FP_CALC_MC1Z(MM,         R,X,Y,N)
#define MCUXCLPKC_FP_CALC_MC1_MM_GF2(R,X,Y,N)      MCUXCLPKC_FP_CALC_MC1Z(MM_GF2,     R,X,Y,N)
#define MCUXCLPKC_FP_CALC_MC1_PM(R,X,Y)            MCUXCLPKC_FP_CALC_MC1Z(PM,         R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC1_PM_GF2(R,X,Y)        MCUXCLPKC_FP_CALC_MC1Z(PM_GF2,     R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC1_PMA(R,X,Y,Z)         MCUXCLPKC_FP_CALC_MC1Z(PMA,        R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_PMA_GF2(R,X,Y,Z)     MCUXCLPKC_FP_CALC_MC1Z(PMA_GF2,    R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_MA(R,Y,Z,N)          MCUXCLPKC_FP_CALC_MC1Z(MA,         R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_MS(R,Y,Z,N)          MCUXCLPKC_FP_CALC_MC1Z(MS,         R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_MR(R,X,N)            MCUXCLPKC_FP_CALC_MC1Z(MR,         R,X,R,N) 
#define MCUXCLPKC_FP_CALC_MC1_MR_GF2(R,X,N)        MCUXCLPKC_FP_CALC_MC1Z(MR_GF2,     R,X,R,N)
#define MCUXCLPKC_FP_CALC_MC1_MMP2(R,X,Y)          MCUXCLPKC_FP_CALC_MC1Z(MMP2,       R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC1_MMAP2(R,X,Y,Z)       MCUXCLPKC_FP_CALC_MC1Z(MMAP2,      R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_MI(R,Y,N,Z)          MCUXCLPKC_FP_CALC_MC1Z(MI,         R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_MI_GF2(R,Y,N,Z)      MCUXCLPKC_FP_CALC_MC1Z(MI_GF2,     R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC1_PM_PATCH(R,X,Y)      MCUXCLPKC_FP_CALC_MC1Z(PM_PATCH,   R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC1_PM_PATCH_GF2(R,X,Y)  MCUXCLPKC_FP_CALC_MC1Z(PM_PATCH_GF2,  R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC1_GCD(Y,Z)             MCUXCLPKC_FP_CALC_MC1Z(GCD,        Z,Y,Y,Z)

/* L0 operation (OP) with parameter set 2, supporting flow protection. */
#define MCUXCLPKC_FP_CALC_OP2_MUL(R,X,Y)           MCUXCLPKC_FP_CALC_OP2C(MUL,        R,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP2_MAC(R,X,Y,Z)         MCUXCLPKC_FP_CALC_OP2Z(MAC,        R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_MAC_NEG(R,X,Y,Z)     MCUXCLPKC_FP_CALC_OP2Z(MAC_NEG,    R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_MUL_GF2(R,X,Y)       MCUXCLPKC_FP_CALC_OP2C(MUL_GF2,    R,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP2_MAC_GF2(R,X,Y,Z)     MCUXCLPKC_FP_CALC_OP2Z(MAC_GF2,    R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_NEG(R,Z)             MCUXCLPKC_FP_CALC_OP2Z(NEG,        R,R,R,Z)
#define MCUXCLPKC_FP_CALC_OP2_ADD(R,Y,Z)           MCUXCLPKC_FP_CALC_OP2Z(ADD,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_SUB(R,Y,Z)           MCUXCLPKC_FP_CALC_OP2Z(SUB,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_AND(R,Y,Z)           MCUXCLPKC_FP_CALC_OP2Z(AND,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_OR(R,Y,Z)            MCUXCLPKC_FP_CALC_OP2Z(OR,         R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_XOR(R,Y,Z)           MCUXCLPKC_FP_CALC_OP2Z(XOR,        R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_MAC_CONST_GF2(R,X,Y,C)  MCUXCLPKC_FP_CALC_OP2C(MAC_CONST_GF2, R,X,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_MAC_CONST(R,X,Y,C)   MCUXCLPKC_FP_CALC_OP2C(MAC_CONST,  R,X,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_MAC_NEG_CONST(R,X,Y,C)  MCUXCLPKC_FP_CALC_OP2C(MAC_NEG_CONST, R,X,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_SHL(R,Y,C)           MCUXCLPKC_FP_CALC_OP2C(SHL,        R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_SHR(R,Y,C)           MCUXCLPKC_FP_CALC_OP2C(SHR,        R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_ROTL(R,Y,C)          MCUXCLPKC_FP_CALC_OP2C(ROTL,       R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_ROTR(R,Y,C)          MCUXCLPKC_FP_CALC_OP2C(ROTR,       R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_ADD_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP2C(ADD_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_SUB_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP2C(SUB_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_AND_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP2C(AND_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_OR_CONST(R,Y,C)      MCUXCLPKC_FP_CALC_OP2C(OR_CONST,   R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_XOR_CONST(R,Y,C)     MCUXCLPKC_FP_CALC_OP2C(XOR_CONST,  R,R,Y,C)
#define MCUXCLPKC_FP_CALC_OP2_MUL1(X,Y)            MCUXCLPKC_FP_CALC_OP2C(MUL1,       Y,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP2_MACC(R,X,Y,Z)        MCUXCLPKC_FP_CALC_OP2Z(MACC,       R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_MUL1_GF2(X,Y)        MCUXCLPKC_FP_CALC_OP2C(MUL1_GF2,   Y,X,Y,0)
#define MCUXCLPKC_FP_CALC_OP2_MACC_GF2(R,X,Y,Z)    MCUXCLPKC_FP_CALC_OP2Z(MACC_GF2,   R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_ADDC(R,Y,Z)          MCUXCLPKC_FP_CALC_OP2Z(ADDC,       R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_SUBC(R,Y,Z)          MCUXCLPKC_FP_CALC_OP2Z(SUBC,       R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_LSB0s(Z)             MCUXCLPKC_FP_CALC_OP2Z(LSB0s,      Z,Z,Z,Z)
#define MCUXCLPKC_FP_CALC_OP2_MSB0s(Z)             MCUXCLPKC_FP_CALC_OP2Z(MSB0s,      Z,Z,Z,Z)
#define MCUXCLPKC_FP_CALC_OP2_CONST(R,C)           MCUXCLPKC_FP_CALC_OP2C(CONST,      R,R,R,C)
#define MCUXCLPKC_FP_CALC_OP2_CMP(Y,Z)             MCUXCLPKC_FP_CALC_OP2Z(CMP,        Y,Z,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_MACCR(R,Y,Z)         MCUXCLPKC_FP_CALC_OP2Z(MACCR,      R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_MACCR_GF2(R,Y,Z)     MCUXCLPKC_FP_CALC_OP2Z(MACCR_GF2,  R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_ADD_Z0(R,Y,Z)        MCUXCLPKC_FP_CALC_OP2Z(ADD_Z0,     R,R,Y,Z)
#define MCUXCLPKC_FP_CALC_OP2_XOR_Z0(R,Y,Z)        MCUXCLPKC_FP_CALC_OP2Z(XOR_Z0,     R,R,Y,Z)

/* L1 microcode (MC) with parameter set 2, supporting flow protection. */
#define MCUXCLPKC_FP_CALC_MC2_MM(R,X,Y,N)          MCUXCLPKC_FP_CALC_MC2Z(MM,         R,X,Y,N)
#define MCUXCLPKC_FP_CALC_MC2_MM_GF2(R,X,Y,N)      MCUXCLPKC_FP_CALC_MC2Z(MM_GF2,     R,X,Y,N)
#define MCUXCLPKC_FP_CALC_MC2_PM(R,X,Y)            MCUXCLPKC_FP_CALC_MC2Z(PM,         R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC2_PM_GF2(R,X,Y)        MCUXCLPKC_FP_CALC_MC2Z(PM_GF2,     R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC2_PMA(R,X,Y,Z)         MCUXCLPKC_FP_CALC_MC2Z(PMA,        R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_PMA_GF2(R,X,Y,Z)     MCUXCLPKC_FP_CALC_MC2Z(PMA_GF2,    R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_MA(R,Y,Z,N)          MCUXCLPKC_FP_CALC_MC2Z(MA,         R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_MS(R,Y,Z,N)          MCUXCLPKC_FP_CALC_MC2Z(MS,         R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_MR(R,X,N)            MCUXCLPKC_FP_CALC_MC2Z(MR,         R,X,R,N)
#define MCUXCLPKC_FP_CALC_MC2_MR_GF2(R,X,N)        MCUXCLPKC_FP_CALC_MC2Z(MR_GF2,     R,X,R,N)
#define MCUXCLPKC_FP_CALC_MC2_MMP2(R,X,Y)          MCUXCLPKC_FP_CALC_MC2Z(MMP2,       R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC2_MMAP2(R,X,Y,Z)       MCUXCLPKC_FP_CALC_MC2Z(MMAP2,      R,X,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_MI(R,Y,N,Z)          MCUXCLPKC_FP_CALC_MC2Z(MI,         R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_MI_GF2(R,Y,N,Z)      MCUXCLPKC_FP_CALC_MC2Z(MI_GF2,     R,N,Y,Z)
#define MCUXCLPKC_FP_CALC_MC2_PM_PATCH(R,X,Y)      MCUXCLPKC_FP_CALC_MC2Z(PM_PATCH,   R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC2_PM_PATCH_GF2(R,X,Y)  MCUXCLPKC_FP_CALC_MC2Z(PM_PATCH_GF2,  R,X,Y,R)
#define MCUXCLPKC_FP_CALC_MC2_GCD(Y,Z)             MCUXCLPKC_FP_CALC_MC2Z(GCD,        Z,Y,Y,Z)
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)


/**********************************************************/
/* Helper macros of function identifier,                  */
/* for function called by helper macros                   */
/**********************************************************/

/* Function identifier of L0 operation (OP) with parameter set 1. */
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "For completeness, all PKC operations are defined.")
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MUL            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MAC            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MAC_NEG        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MUL_GF2        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MAC_GF2        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_NEG            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_ADD            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_SUB            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_AND            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_OR             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_XOR            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MAC_CONST_GF2  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MAC_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MAC_NEG_CONST  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_SHL            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_SHR            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_ROTL           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_ROTR           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_SUB_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_AND_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_XOR_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MUL1           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MACC           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MUL1_GF2       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MACC_GF2       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_ADDC           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_SUBC           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_LSB0s          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MSB0s          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_CONST          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_CMP            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MACCR          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_MACCR_GF2      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_Z0         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP1_XOR_Z0         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)

/* Function identifier of L1 microcode (MC) with parameter set 1. */
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MM             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MM_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_PM             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_PM_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_PMA            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_PMA_GF2        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MA             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MS             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MR             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MR_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MMP2           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MMAP2          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MI             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_MI_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_PM_PATCH       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_PM_PATCH_GF2   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC1_GCD            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)

/* Function identifier of L0 operation (OP) with parameter set 2. */
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MUL            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MAC            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MAC_NEG        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MUL_GF2        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MAC_GF2        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_NEG            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_ADD            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_SUB            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_AND            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_OR             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_XOR            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MAC_CONST_GF2  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MAC_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MAC_NEG_CONST  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_SHL            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_SHR            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_ROTL           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_ROTR           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_ADD_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_SUB_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_AND_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_OR_CONST       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_XOR_CONST      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MUL1           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MACC           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MUL1_GF2       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MACC_GF2       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_ADDC           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_SUBC           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_LSB0s          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MSB0s          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_CONST          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcConst)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_CMP            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MACCR          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_MACCR_GF2      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_ADD_Z0         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_OP2_XOR_Z0         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)

/* Function identifier of L1 microcode (MC) with parameter set 2. */
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MM             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MM_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_PM             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_PM_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_PMA            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_PMA_GF2        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MA             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MS             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MR             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MR_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MMP2           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MMAP2          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MI             MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_MI_GF2         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_PM_PATCH       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_PM_PATCH_GF2   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
#define MCUXCLPKC_FP_CALLED_CALC_MC2_GCD            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Calc)
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)


#endif /* MCUXCLPKC_OPERATIONS_H_ */
