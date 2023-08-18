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
 * @file  mcuxClOsccaPkc_FupMacros.h
 * @brief Macros for PKC FUP program composing
 */

#ifndef MCUXCLOSCCAPKC_FUPMACROS_H_
#define MCUXCLOSCCAPKC_FUPMACROS_H_


#include <stdint.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

/**********************************************************/
/* Macros to create FUP program                           */
/**********************************************************/
/**
 * @brief FUP programs data structure
 */
typedef struct mcuxClOsccaPkc_FUPEntry
{
    uint8_t a;
    uint8_t b;
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t r;
}mcuxClOsccaPkc_FUPEntry_t;

/**
 * Macro to create FUP program, e.g., a FUP program with 2 entries:
 * MCUXCLPKC_FUP_EXT_ROM(FupProgram1, FUP_MMUL(0,1,1), FUP_MMUL(1,0,0));
 */
#define MCUXCLOSCCAPKC_FUP_EXT_ROM(name, ...)  \
    const mcuxClOsccaPkc_FUPEntry_t name[] __attribute__((aligned(4),section("PH_CL_FUP_PROGRAMS_MAGIC_AREA"))) = { __VA_ARGS__ }
#define MCUXCLOSCCAPKC_FUP_LEN(pFupProgram)  ((uint8_t) ((sizeof(pFupProgram)) / sizeof(mcuxClOsccaPkc_FUPEntry_t)))

/**********************************************************/
/* Macros for FUP CRC entry                               */
/**********************************************************/
/**
 * Macro to reserve space for a CRC entry in FUP program.
 * The CRC32 value is temporarily set to 0x00000000, and will be updated (filled) by build system.
 */
#define MCUXCLOSCCAPKC_FUP_DATA                       (0x0U)
#define MCUXCLOSCCAPKC_FUP_CRC                        (0x10U)
#define MCUXCLOSCCAPKC_CRC_ENTRY                      {MCUXCLOSCCAPKC_FUP_CRC, 0, 0, 0, 0, 0}

/** Helper macro to pack CRC entry. */
#define MCUXCLOSCCAPKC_FUP_CRC_ENTRY(crc32)           {MCUXCLOSCCAPKC_FUP_CRC, 0, (crc32) & 0xFFu, ((crc32) >> 8) & 0xFFu, ((crc32) >> 16) & 0xFFu, ((crc32) >> 24) & 0xFFu}

/**********************************************************/
/* Helper macros for FUP program composing                */
/**********************************************************/
#define FUP_AND(R, Y, Z)                                {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_AND, 0, Y, Z, R}
#define FUP_OR(R, Y, Z)                                 {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_OR, 0, Y, Z, R}
#define FUP_XOR(R, Y, Z)                                {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_XOR, 0, Y, Z, R}
#define FUP_SUB(R, Y, Z)                                {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_SUB, 0, Y, Z, R}
#define FUP_MMUL(R, X, Y, Z)                            {MCUXCLOSCCAPKC_FUP_MC1, MCUXCLOSCCAPKC_FMC_MMUL, X, Y, Z, R}
#define FUP_MADD(R, Y, Z, X)                            {MCUXCLOSCCAPKC_FUP_MC1, MCUXCLOSCCAPKC_FMC_MADD, X, Y, Z, R}
#define FUP_MSUB(R, Y, Z, X)                            {MCUXCLOSCCAPKC_FUP_MC1, MCUXCLOSCCAPKC_FMC_MSUB, X, Y, Z, R}
#define FUP_MRED(R, X, Z)                               {MCUXCLOSCCAPKC_FUP_MC1, MCUXCLOSCCAPKC_FMC_MRED, X, 0, Z, R}
#define FUP_SBX0(R, Z)                                  {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_SBX0, 0, 0, Z, R}
#define FUP_ROTL(R, Y, Z)                               {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_ROTL, 0, Y, Z, R}
#define FUP_SHL(R, Y, C)                                {MCUXCLOSCCAPKC_FUP_OP2, MCUXCLOSCCAPKC_FOP_SHL, 0, Y, C, R}
#define FUP_ADD(R, Y, Z)                                {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_ADD, 0, Y, Z, R}
#define FUP_ADD_CONST(R, Y, C)                          {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_ADD_YC, 0, Y, C, R}
#define FUP_NEG(R, Z)                                   {MCUXCLOSCCAPKC_FUP_OP1, MCUXCLOSCCAPKC_FOP_NEG, 0, 0, Z, R}

#endif /*MCUXCLOSCCAPKC_FUPMACROS_H_*/
