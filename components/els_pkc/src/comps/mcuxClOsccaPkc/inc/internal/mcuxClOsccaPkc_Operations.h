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
 * @file  mcuxClOsccaPkc_Operations.h
 * @brief Mnemonics and macros for PKC calculation
 */


#ifndef MCUXCLOSCCAPKC_OPERATIONS_H_
#define MCUXCLOSCCAPKC_OPERATIONS_H_


#include <stdint.h>
#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

#include <mcuxClOsccaPkc_Functions.h>
#include <internal/mcuxClOsccaPkc_Macros.h>

/**
 * In order to ease CLib programming, improve code readability and reduce maintenance cost,
 * please use help macros, e.g., MCUXCLOSCCAPKC_FXIOP1_MUL(...) to start a PKC operation,
 * and corresponding function identifiers, e.g.,  MCUXCLOSCCAPKC_FXIOP1_MUL in FP balancing.
 */

/**********************************************************/
/* Macros for encoding L0/L1 and parameter set 1/2        */
/**********************************************************/
#define MCUXCLOSCCAPKC_FUP_OP                         (0x00U)
#define MCUXCLOSCCAPKC_FUP_MC                         (0x80U)
#define MCUXCLOSCCAPKC_FUP_PS1                        (0x00U)
#define MCUXCLOSCCAPKC_FUP_PS2                        (0x40U)

#define MCUXCLOSCCAPKC_FUP_OP_ZFIX                    (0x20U)

#define MCUXCLOSCCAPKC_FUP_OP1                        (0x00U)
#define MCUXCLOSCCAPKC_FUP_OP2                        (0x40U)
#define MCUXCLOSCCAPKC_FUP_MC1                        (0x80U)
#define MCUXCLOSCCAPKC_FUP_MC2                        (0xc0U)

MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "PKC operations are defined.")
/**********************************************************/
/* Mnemonic of PKC L0 operations (OP)                     */
/**********************************************************/
#define MCUXCLOSCCAPKC_FOP_MUL                        (0x0U)
#define MCUXCLOSCCAPKC_FOP_MAC                        (0x2U)
#define MCUXCLOSCCAPKC_FOP_NEG                        (0x9U)
#define MCUXCLOSCCAPKC_FOP_ADD                        (0xaU)
#define MCUXCLOSCCAPKC_FOP_SUB                        (0xbU)
#define MCUXCLOSCCAPKC_FOP_AND                        (0xdU)
#define MCUXCLOSCCAPKC_FOP_OR                         (0xeU)
#define MCUXCLOSCCAPKC_FOP_XOR                        (0xfU)
#define MCUXCLOSCCAPKC_FOP_SHL                        (0x14U)
#define MCUXCLOSCCAPKC_FOP_SHR                        (0x15U)
#define MCUXCLOSCCAPKC_FOP_ADD_YC                     (0x1aU)
#define MCUXCLOSCCAPKC_FOP_SUB_YC                     (0x1bU)
#define MCUXCLOSCCAPKC_FOP_AND_YC                     (0x1dU)
#define MCUXCLOSCCAPKC_FOP_OR_YC                      (0x1eU)
#define MCUXCLOSCCAPKC_FOP_SBX0                       (0x38U)
#define MCUXCLOSCCAPKC_FOP_CMP_YZ                     (0x4bU)
#define MCUXCLOSCCAPKC_FOP_ROTL                       (0x16U)

/**********************************************************/
/* Mnemonic of PKC L1 microcodes (MC)                     */
/**********************************************************/
#define MCUXCLOSCCAPKC_FMC_MMUL                       (0x0U)
#define MCUXCLOSCCAPKC_FMC_MADD                       (0x21U)
#define MCUXCLOSCCAPKC_FMC_MSUB                       (0x2aU)
#define MCUXCLOSCCAPKC_FMC_MRED                       (0x33U)
#define MCUXCLOSCCAPKC_FMC_TMUL                       (0x13U)
#define MCUXCLOSCCAPKC_FMC_MONTINV                    (0x5DU)
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)

/**********************************************************/
/* Helper macros to start specified PKC calculation,      */
/* with flow protection                                   */
/**********************************************************/
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "PKC operations are defined.")
/* L0 operation (OP) with parameter set 1. */
#define MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)       (((uint32_t)(R) << 24) | ((uint32_t)(X) << 16) | ((uint32_t)(Y) << 8) | ((uint32_t)(Z)))
#define MCUXCLOSCCAPKC_FXIOP1_SBX0(R, Z)              MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_SBX0), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, 0, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_MUL(R, X, Y)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_MUL), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, 0)))
#define MCUXCLOSCCAPKC_FXIOP1_MAC(R, X, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_MAC), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_SHL_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_SHL), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_SHR_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_SHR), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_SUB_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_SUB_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_ADD_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_ADD_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_OR_YC(R, Y, Z)          MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_OR_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_AND(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_AND), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_AND_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_AND_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_OR(R, Y, Z)             MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_OR), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_XOR(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_XOR), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_NEG(R, Z)               MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_NEG), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, 0, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_ADD(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_ADD), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_SUB(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_SUB), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_CMP_YZ), MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP1_ROTL(R, Y, Z)           MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP1 << 8) | (MCUXCLOSCCAPKC_FOP_ROTL), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))

/* L1 microcode (MC) with parameter set 1. */
#define MCUXCLOSCCAPKC_FXIMC1_MMUL(R, X, Y, Z)        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC1 << 8) | (MCUXCLOSCCAPKC_FMC_MMUL), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIMC1_MADD(R, Y, Z, X)        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC1 << 8) | (MCUXCLOSCCAPKC_FMC_MADD), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIMC1_MSUB(R, Y, Z, X)        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC1 << 8) | (MCUXCLOSCCAPKC_FMC_MSUB), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIMC1_MRED(R, X, Z)           MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC1 << 8) | (MCUXCLOSCCAPKC_FMC_MRED), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, 0, Z)))
#define MCUXCLOSCCAPKC_FXIMC1_TMUL(R, X, Y)           MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC1 << 8) | (MCUXCLOSCCAPKC_FMC_TMUL), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, 0)))
#define MCUXCLOSCCAPKC_FXIMC1_MONTINV(R, X, Y, Z)     MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC1 << 8) | (MCUXCLOSCCAPKC_FMC_MONTINV), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))

/* L0 operation (OP) with parameter set 2. */
#define MCUXCLOSCCAPKC_FXIOP2_SBX0(R, Z)              MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_SBX0), ((R) << 24) | (Z)))
#define MCUXCLOSCCAPKC_FXIOP2_MUL(R, X, Y)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_MUL), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, 0)))
#define MCUXCLOSCCAPKC_FXIOP2_MAC(R, X, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_MAC), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_SHL_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_SHL), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_SHR_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_SHR), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_SUB_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_SUB_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_ADD_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_ADD_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_OR_YC(R, Y, Z)          MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_OR_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_AND(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_AND), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_AND_YC(R, Y, Z)         MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op((((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 | MCUXCLOSCCAPKC_FUP_OP_ZFIX) << 8) | (MCUXCLOSCCAPKC_FOP_AND_YC), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_OR(R, Y, Z)             MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_OR), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_XOR(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_XOR), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_NEG(R, Z)               MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_NEG), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, 0, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_ADD(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_ADD), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))
#define MCUXCLOSCCAPKC_FXIOP2_SUB(R, Y, Z)            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_OP2 << 8) | (MCUXCLOSCCAPKC_FOP_SUB), MCUXCLOSCCAPKC_PKCPACKARGS(R, 0, Y, Z)))

/* L1 microcode (MC) with parameter set 2. */
#define MCUXCLOSCCAPKC_FXIMC2_MMUL(R, X, Y, Z)        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC2 << 8) | (MCUXCLOSCCAPKC_FMC_MMUL), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIMC2_MADD(R, Y, Z, X)        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC2 << 8) | (MCUXCLOSCCAPKC_FMC_MADD), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIMC2_MSUB(R, Y, Z, X)        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC2 << 8) | (MCUXCLOSCCAPKC_FMC_MSUB), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
#define MCUXCLOSCCAPKC_FXIMC2_MRED(R, X, Z)           MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC2 << 8) | (MCUXCLOSCCAPKC_FMC_MRED), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, 0, Z)))
#define MCUXCLOSCCAPKC_FXIMC2_MONTINV(R, X, Y, Z)     MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Op(((uint16_t)MCUXCLOSCCAPKC_FUP_MC2 << 8) | (MCUXCLOSCCAPKC_FMC_MONTINV), MCUXCLOSCCAPKC_PKCPACKARGS(R, X, Y, Z)))
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)

#endif /*MCUXCLOSCCAPKC_OPERATIONS_H_*/
