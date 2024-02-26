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
 * @file  mcuxClPkc_FupMacros.h
 * @brief Macros for PKC FUP program composing
 */


#ifndef MCUXCLPKC_FUPMACROS_H_
#define MCUXCLPKC_FUPMACROS_H_


#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <internal/mcuxClPkc_Operations.h>


/**********************************************************/
/* Macros to create FUP program                           */
/**********************************************************/
/**
 * @brief FUP programs data structure
 */
typedef struct mcuxClPkc_FUPEntry
{
  uint8_t CALCparam0;
  uint8_t CALCparam1;
  uint8_t XPTRind;
  uint8_t YPTRind;
  uint8_t TOPPind;
  uint8_t RPTRind;
} mcuxClPkc_FUPEntry_t;


/**
 * Macro to declare external constant FUP program.
 */
#define MCUXCLPKC_FUP_EXT_ROM_DECLARE(name)  \
    extern const mcuxClPkc_FUPEntry_t name[]

/**
 * Macro to create FUP program, e.g., a FUP program with 2 entries:
 * MCUXCLPKC_FUP_EXT_ROM(FupProgram1, FUP_OP1_MUL(0,1,1), FUP_OP1_MUL(1,0,0));
 */
#define MCUXCLPKC_FUP_EXT_ROM(name, ...)  \
    MCUX_CSSL_ANALYSIS_START_PATTERN_FUP() \
    const mcuxClPkc_FUPEntry_t name[] __attribute__((aligned(4),section("PH_CL_FUP_PROGRAMS_MAGIC_AREA"))) = { __VA_ARGS__ } \
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_FUP()

#define MCUXCLPKC_FUP_LEN(pFupProgram)  ((uint8_t) ((sizeof(pFupProgram)) / 6u))


/**********************************************************/
/* Macros to pack parameters of FUP entry                 */
/**********************************************************/
/**
 * Macro to pack 6 parameters: CALCparam0, CALCparam1, XPTRind, YPTRind, ZPTRind, RPTRind,
 * of a PKC calculation to an entry in FUP program.
 */
#define MCUXCLPKC_FUP_PACKARGS6(calcP0, calcP1, iX, iY, iZ, iR)  \
    {calcP0, calcP1, iX, iY, iZ, iR}


/** Helper macro to pack parameters of L0 operation (OP) with parameter set 1. */
#define MCUXCLPKC_FUP_OP1(symbol, iR, iX, iY, iZ, repeat)  MCUXCLPKC_FUP_PACKARGS6(MCUXCLPKC_PARAM_OP1 | ((repeat) & 0x0Fu), MCUXCLPKC_OP_ ## symbol, iX, iY, iZ, iR)
/** Helper macro to pack parameters of L1 microcode (MC) with parameter set 1. */
#define MCUXCLPKC_FUP_MC1(symbol, iR, iX, iY, iZ, repeat)  MCUXCLPKC_FUP_PACKARGS6(MCUXCLPKC_PARAM_MC1 | ((repeat) & 0x0Fu), MCUXCLPKC_MC_ ## symbol, iX, iY, iZ, iR)
/** Helper macro to pack parameters of L0 operation (OP) with parameter set 2. */
#define MCUXCLPKC_FUP_OP2(symbol, iR, iX, iY, iZ, repeat)  MCUXCLPKC_FUP_PACKARGS6(MCUXCLPKC_PARAM_OP2 | ((repeat) & 0x0Fu), MCUXCLPKC_OP_ ## symbol, iX, iY, iZ, iR)
/** Helper macro to pack parameters of L1 microcode (MC) with parameter set 2. */
#define MCUXCLPKC_FUP_MC2(symbol, iR, iX, iY, iZ, repeat)  MCUXCLPKC_FUP_PACKARGS6(MCUXCLPKC_PARAM_MC2 | ((repeat) & 0x0Fu), MCUXCLPKC_MC_ ## symbol, iX, iY, iZ, iR)


/**********************************************************/
/* Macros for FUP CRC entry                               */
/**********************************************************/
#define MCUXCLPKC_PARAM_CRC  0x10u  ///< CALCparam0 of CRC entry
/** Helper macro to pack CRC entry. */
#define FUP_CRC_ENTRY(crc32)  MCUXCLPKC_FUP_PACKARGS6(MCUXCLPKC_PARAM_CRC, 0, (crc32) & 0xFFu, ((crc32) >> 8) & 0xFFu, ((crc32) >> 16) & 0xFFu, ((crc32) >> 24) & 0xFFu)

/**
 * Macro to reserve space for a CRC entry in FUP program.
 * The CRC32 value is temporarily set to 0x00000000, and will be updated (filled) by build system.
 */
#define PH_CLNS_UTILS_FAME_CRC_ENTRY  {MCUXCLPKC_PARAM_CRC,0, 0,0,0,0}


/**********************************************************/
/* Helper macros for FUP program composing                */
/**********************************************************/
/* R, X, Y and Z/C are 8-bit constant indices of UPTRT[].       */
/* Argument(s) (index) not used is set to 0.                    */  /* TODO: CLNS-916, replace by other used index, e.g., R, to avoid PKC loading UPTRT[0] into UPTRT cache. */
/* For PKC operations with a constant, e.g., ADD_CONST and SHL, */
/* the constant parameter shall be stored in UPTRT[C].          */

/* L0 operation (OP) with parameter set 1, without repeating. */
MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_2_5, "For completeness, all FUP operations are defined.")
#define FUP_OP1_MUL(R,X,Y)              MCUXCLPKC_FUP_OP1(MUL,           R,X,Y,0, 0)
#define FUP_OP1_MAC(R,X,Y,Z)            MCUXCLPKC_FUP_OP1(MAC,           R,X,Y,Z, 0)
#define FUP_OP1_MAC_NEG(R,X,Y,Z)        MCUXCLPKC_FUP_OP1(MAC_NEG,       R,X,Y,Z, 0)
#define FUP_OP1_MUL_GF2(R,X,Y)          MCUXCLPKC_FUP_OP1(MUL_GF2,       R,X,Y,0, 0)
#define FUP_OP1_MAC_GF2(R,X,Y,Z)        MCUXCLPKC_FUP_OP1(MAC_GF2,       R,X,Y,Z, 0)
#define FUP_OP1_NEG(R,Z)                MCUXCLPKC_FUP_OP1(NEG,           R,0,0,Z, 0)
#define FUP_OP1_ADD(R,Y,Z)              MCUXCLPKC_FUP_OP1(ADD,           R,0,Y,Z, 0)
#define FUP_OP1_SUB(R,Y,Z)              MCUXCLPKC_FUP_OP1(SUB,           R,0,Y,Z, 0)
#define FUP_OP1_AND(R,Y,Z)              MCUXCLPKC_FUP_OP1(AND,           R,0,Y,Z, 0)
#define FUP_OP1_OR(R,Y,Z)               MCUXCLPKC_FUP_OP1(OR,            R,0,Y,Z, 0)
#define FUP_OP1_XOR(R,Y,Z)              MCUXCLPKC_FUP_OP1(XOR,           R,0,Y,Z, 0)
#define FUP_OP1_MAC_CONST_GF2(R,X,Y,C)  MCUXCLPKC_FUP_OP1(MAC_CONST_GF2, R,X,Y,C, 0)
#define FUP_OP1_MAC_CONST(R,X,Y,C)      MCUXCLPKC_FUP_OP1(MAC_CONST,     R,X,Y,C, 0)
#define FUP_OP1_MAC_NEG_CONST(R,X,Y,C)  MCUXCLPKC_FUP_OP1(MAC_NEG_CONST, R,X,Y,C, 0)
#define FUP_OP1_SHL(R,Y,C)              MCUXCLPKC_FUP_OP1(SHL,           R,0,Y,C, 0)
#define FUP_OP1_SHR(R,Y,C)              MCUXCLPKC_FUP_OP1(SHR,           R,0,Y,C, 0)
#define FUP_OP1_ROTL(R,Y,C)             MCUXCLPKC_FUP_OP1(ROTL,          R,0,Y,C, 0)
#define FUP_OP1_ROTR(R,Y,C)             MCUXCLPKC_FUP_OP1(ROTR,          R,0,Y,C, 0)
#define FUP_OP1_ADD_CONST(R,Y,C)        MCUXCLPKC_FUP_OP1(ADD_CONST,     R,0,Y,C, 0)
#define FUP_OP1_SUB_CONST(R,Y,C)        MCUXCLPKC_FUP_OP1(SUB_CONST,     R,0,Y,C, 0)
#define FUP_OP1_AND_CONST(R,Y,C)        MCUXCLPKC_FUP_OP1(AND_CONST,     R,0,Y,C, 0)
#define FUP_OP1_OR_CONST(R,Y,C)         MCUXCLPKC_FUP_OP1(OR_CONST,      R,0,Y,C, 0)
#define FUP_OP1_XOR_CONST(R,Y,C)        MCUXCLPKC_FUP_OP1(XOR_CONST,     R,0,Y,C, 0)
#define FUP_OP1_MUL1(X,Y)               MCUXCLPKC_FUP_OP1(MUL1,          0,X,Y,0, 0)
#define FUP_OP1_MACC(R,X,Y,Z)           MCUXCLPKC_FUP_OP1(MACC,          R,X,Y,Z, 0)
#define FUP_OP1_MUL1_GF2(X,Y)           MCUXCLPKC_FUP_OP1(MUL1_GF2,      0,X,Y,0, 0)
#define FUP_OP1_MACC_GF2(R,X,Y,Z)       MCUXCLPKC_FUP_OP1(MACC_GF2,      R,X,Y,Z, 0)
#define FUP_OP1_ADDC(R,Y,Z)             MCUXCLPKC_FUP_OP1(ADDC,          R,0,Y,Z, 0)
#define FUP_OP1_SUBC(R,Y,Z)             MCUXCLPKC_FUP_OP1(SUBC,          R,0,Y,Z, 0)
#define FUP_OP1_LSB0s(Z)                MCUXCLPKC_FUP_OP1(LSB0s,         0,0,0,Z, 0)
#define FUP_OP1_MSB0s(Z)                MCUXCLPKC_FUP_OP1(MSB0s,         0,0,0,Z, 0)
#define FUP_OP1_CONST(R,C)              MCUXCLPKC_FUP_OP1(CONST,         R,0,0,C, 0)
#define FUP_OP1_CMP(Y,Z)                MCUXCLPKC_FUP_OP1(CMP,           0,0,Y,Z, 0)
#define FUP_OP1_MACCR(R,Y,Z)            MCUXCLPKC_FUP_OP1(MACCR,         R,0,Y,Z, 0)
#define FUP_OP1_MACCR_GF2(R,Y,Z)        MCUXCLPKC_FUP_OP1(MACCR_GF2,     R,0,Y,Z, 0)
#define FUP_OP1_ADD_Z0(R,Y,Z)           MCUXCLPKC_FUP_OP1(ADD_Z0,        R,0,Y,Z, 0)
#define FUP_OP1_XOR_Z0(R,Y,Z)           MCUXCLPKC_FUP_OP1(XOR_Z0,        R,0,Y,Z, 0)

/* L1 microcode (MC) with parameter set 1, without repeating. */
#define FUP_MC1_MM(R,X,Y,N)             MCUXCLPKC_FUP_MC1(MM,            R,X,Y,N, 0)
#define FUP_MC1_MM_GF2(R,X,Y,N)         MCUXCLPKC_FUP_MC1(MM_GF2,        R,X,Y,N, 0)
#define FUP_MC1_PM(R,X,Y)               MCUXCLPKC_FUP_MC1(PM,            R,X,Y,0, 0)
#define FUP_MC1_PM_GF2(R,X,Y)           MCUXCLPKC_FUP_MC1(PM_GF2,        R,X,Y,0, 0)
#define FUP_MC1_PMA(R,X,Y,Z)            MCUXCLPKC_FUP_MC1(PMA,           R,X,Y,Z, 0)
#define FUP_MC1_PMA_GF2(R,X,Y,Z)        MCUXCLPKC_FUP_MC1(PMA_GF2,       R,X,Y,Z, 0)
#define FUP_MC1_MA(R,Y,Z,N)             MCUXCLPKC_FUP_MC1(MA,            R,N,Y,Z, 0)
#define FUP_MC1_MS(R,Y,Z,N)             MCUXCLPKC_FUP_MC1(MS,            R,N,Y,Z, 0)
#define FUP_MC1_MR(R,X,N)               MCUXCLPKC_FUP_MC1(MR,            R,X,0,N, 0)
#define FUP_MC1_MR_GF2(R,X,N)           MCUXCLPKC_FUP_MC1(MR_GF2,        R,X,0,N, 0)
#define FUP_MC1_MMP2(R,X,Y)             MCUXCLPKC_FUP_MC1(MMP2,          R,X,Y,0, 0)
#define FUP_MC1_MMAP2(R,X,Y,Z)          MCUXCLPKC_FUP_MC1(MMAP2,         R,X,Y,Z, 0)
#define FUP_MC1_MI(R,Y,N,Z)             MCUXCLPKC_FUP_MC1(MI,            R,N,Y,Z, 0)  /* Z buffer needs to be initialized to 1 */
#define FUP_MC1_MI_GF2(R,Y,N,Z)         MCUXCLPKC_FUP_MC1(MI_GF2,        R,N,Y,Z, 0)  /* Z buffer needs to be initialized to 1 */
#define FUP_MC1_PM_PATCH(R,X,Y)         MCUXCLPKC_FUP_MC1(PM_PATCH,      R,X,Y,0, 0)
#define FUP_MC1_PM_PATCH_GF2(R,X,Y)     MCUXCLPKC_FUP_MC1(PM_PATCH_GF2,  R,X,Y,0, 0)
#define FUP_MC1_GCD(Y,Z)                MCUXCLPKC_FUP_MC1(GCD,           Z,Y,Y,Z, 0)  /* X = Y, R = Z (result in-place) */

/* L0 operation (OP) with parameter set 2, without repeating. */
#define FUP_OP2_MUL(R,X,Y)              MCUXCLPKC_FUP_OP2(MUL,           R,X,Y,0, 0)
#define FUP_OP2_MAC(R,X,Y,Z)            MCUXCLPKC_FUP_OP2(MAC,           R,X,Y,Z, 0)
#define FUP_OP2_MAC_NEG(R,X,Y,Z)        MCUXCLPKC_FUP_OP2(MAC_NEG,       R,X,Y,Z, 0)
#define FUP_OP2_MUL_GF2(R,X,Y)          MCUXCLPKC_FUP_OP2(MUL_GF2,       R,X,Y,0, 0)
#define FUP_OP2_MAC_GF2(R,X,Y,Z)        MCUXCLPKC_FUP_OP2(MAC_GF2,       R,X,Y,Z, 0)
#define FUP_OP2_NEG(R,Z)                MCUXCLPKC_FUP_OP2(NEG,           R,0,0,Z, 0)
#define FUP_OP2_ADD(R,Y,Z)              MCUXCLPKC_FUP_OP2(ADD,           R,0,Y,Z, 0)
#define FUP_OP2_SUB(R,Y,Z)              MCUXCLPKC_FUP_OP2(SUB,           R,0,Y,Z, 0)
#define FUP_OP2_AND(R,Y,Z)              MCUXCLPKC_FUP_OP2(AND,           R,0,Y,Z, 0)
#define FUP_OP2_OR(R,Y,Z)               MCUXCLPKC_FUP_OP2(OR,            R,0,Y,Z, 0)
#define FUP_OP2_XOR(R,Y,Z)              MCUXCLPKC_FUP_OP2(XOR,           R,0,Y,Z, 0)
#define FUP_OP2_MAC_CONST_GF2(R,X,Y,C)  MCUXCLPKC_FUP_OP2(MAC_CONST_GF2, R,X,Y,C, 0)
#define FUP_OP2_MAC_CONST(R,X,Y,C)      MCUXCLPKC_FUP_OP2(MAC_CONST,     R,X,Y,C, 0)
#define FUP_OP2_MAC_NEG_CONST(R,X,Y,C)  MCUXCLPKC_FUP_OP2(MAC_NEG_CONST, R,X,Y,C, 0)
#define FUP_OP2_SHL(R,Y,C)              MCUXCLPKC_FUP_OP2(SHL,           R,0,Y,C, 0)
#define FUP_OP2_SHR(R,Y,C)              MCUXCLPKC_FUP_OP2(SHR,           R,0,Y,C, 0)
#define FUP_OP2_ROTL(R,Y,C)             MCUXCLPKC_FUP_OP2(ROTL,          R,0,Y,C, 0)
#define FUP_OP2_ROTR(R,Y,C)             MCUXCLPKC_FUP_OP2(ROTR,          R,0,Y,C, 0)
#define FUP_OP2_ADD_CONST(R,Y,C)        MCUXCLPKC_FUP_OP2(ADD_CONST,     R,0,Y,C, 0)
#define FUP_OP2_SUB_CONST(R,Y,C)        MCUXCLPKC_FUP_OP2(SUB_CONST,     R,0,Y,C, 0)
#define FUP_OP2_AND_CONST(R,Y,C)        MCUXCLPKC_FUP_OP2(AND_CONST,     R,0,Y,C, 0)
#define FUP_OP2_OR_CONST(R,Y,C)         MCUXCLPKC_FUP_OP2(OR_CONST,      R,0,Y,C, 0)
#define FUP_OP2_XOR_CONST(R,Y,C)        MCUXCLPKC_FUP_OP2(XOR_CONST,     R,0,Y,C, 0)
#define FUP_OP2_MUL1(X,Y)               MCUXCLPKC_FUP_OP2(MUL1,          0,X,Y,0, 0)
#define FUP_OP2_MACC(R,X,Y,Z)           MCUXCLPKC_FUP_OP2(MACC,          R,X,Y,Z, 0)
#define FUP_OP2_MUL1_GF2(X,Y)           MCUXCLPKC_FUP_OP2(MUL1_GF2,      0,X,Y,0, 0)
#define FUP_OP2_MACC_GF2(R,X,Y,Z)       MCUXCLPKC_FUP_OP2(MACC_GF2,      R,X,Y,Z, 0)
#define FUP_OP2_ADDC(R,Y,Z)             MCUXCLPKC_FUP_OP2(ADDC,          R,0,Y,Z, 0)
#define FUP_OP2_SUBC(R,Y,Z)             MCUXCLPKC_FUP_OP2(SUBC,          R,0,Y,Z, 0)
#define FUP_OP2_LSB0s(Z)                MCUXCLPKC_FUP_OP2(LSB0s,         0,0,0,Z, 0)
#define FUP_OP2_MSB0s(Z)                MCUXCLPKC_FUP_OP2(MSB0s,         0,0,0,Z, 0)
#define FUP_OP2_CONST(R,C)              MCUXCLPKC_FUP_OP2(CONST,         R,0,0,C, 0)
#define FUP_OP2_CMP(Y,Z)                MCUXCLPKC_FUP_OP2(CMP,           0,0,Y,Z, 0)
#define FUP_OP2_MACCR(R,Y,Z)            MCUXCLPKC_FUP_OP2(MACCR,         R,0,Y,Z, 0)
#define FUP_OP2_MACCR_GF2(R,Y,Z)        MCUXCLPKC_FUP_OP2(MACCR_GF2,     R,0,Y,Z, 0)
#define FUP_OP2_ADD_Z0(R,Y,Z)           MCUXCLPKC_FUP_OP2(ADD_Z0,        R,0,Y,Z, 0)
#define FUP_OP2_XOR_Z0(R,Y,Z)           MCUXCLPKC_FUP_OP2(XOR_Z0,        R,0,Y,Z, 0)

/* L1 microcode (MC) with parameter set 2, without repeating. */
#define FUP_MC2_MM(R,X,Y,N)             MCUXCLPKC_FUP_MC2(MM,            R,X,Y,N, 0)
#define FUP_MC2_MM_GF2(R,X,Y,N)         MCUXCLPKC_FUP_MC2(MM_GF2,        R,X,Y,N, 0)
#define FUP_MC2_PM(R,X,Y)               MCUXCLPKC_FUP_MC2(PM,            R,X,Y,0, 0)
#define FUP_MC2_PM_GF2(R,X,Y)           MCUXCLPKC_FUP_MC2(PM_GF2,        R,X,Y,0, 0)
#define FUP_MC2_PMA(R,X,Y,Z)            MCUXCLPKC_FUP_MC2(PMA,           R,X,Y,Z, 0)
#define FUP_MC2_PMA_GF2(R,X,Y,Z)        MCUXCLPKC_FUP_MC2(PMA_GF2,       R,X,Y,Z, 0)
#define FUP_MC2_MA(R,Y,Z,N)             MCUXCLPKC_FUP_MC2(MA,            R,N,Y,Z, 0)
#define FUP_MC2_MS(R,Y,Z,N)             MCUXCLPKC_FUP_MC2(MS,            R,N,Y,Z, 0)
#define FUP_MC2_MR(R,X,N)               MCUXCLPKC_FUP_MC2(MR,            R,X,0,N, 0)
#define FUP_MC2_MR_GF2(R,X,N)           MCUXCLPKC_FUP_MC2(MR_GF2,        R,X,0,N, 0)
#define FUP_MC2_MMP2(R,X,Y)             MCUXCLPKC_FUP_MC2(MMP2,          R,X,Y,0, 0)
#define FUP_MC2_MMAP2(R,X,Y,Z)          MCUXCLPKC_FUP_MC2(MMAP2,         R,X,Y,Z, 0)
#define FUP_MC2_MI(R,Y,N,Z)             MCUXCLPKC_FUP_MC2(MI,            R,N,Y,Z, 0)  /* Z buffer needs to be initialized to 1 */
#define FUP_MC2_MI_GF2(R,Y,N,Z)         MCUXCLPKC_FUP_MC2(MI_GF2,        R,N,Y,Z, 0)  /* Z buffer needs to be initialized to 1 */
#define FUP_MC2_PM_PATCH(R,X,Y)         MCUXCLPKC_FUP_MC2(PM_PATCH,      R,X,Y,0, 0)
#define FUP_MC2_PM_PATCH_GF2(R,X,Y)     MCUXCLPKC_FUP_MC2(PM_PATCH_GF2,  R,X,Y,0, 0)
#define FUP_MC2_GCD(Y,Z)                MCUXCLPKC_FUP_MC2(GCD,           Z,Y,Y,Z, 0)  /* X = Y, R = Z (result in-place) */
MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_2_5)


#endif /* MCUXCLPKC_FUPMACROS_H_ */
