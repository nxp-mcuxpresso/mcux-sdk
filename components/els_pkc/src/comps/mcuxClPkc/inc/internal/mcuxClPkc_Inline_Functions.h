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
 * @file  mcuxClPkc_Inline_Functions.h
 * @brief Inline functions for accessing PKC hardware IP
 */


#ifndef MCUXCLPKC_INLINE_FUNCTIONS_H_
#define MCUXCLPKC_INLINE_FUNCTIONS_H_


#include <platform_specific_headers.h>

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc_Types.h>
#include <internal/mcuxClPkc_SfrAccess.h>


/**********************************************************/
/* Inline functions for UPTR table and offsets            */
/**********************************************************/
/** Inline function to set the address of UPTRT (Universal pointer FUP table). */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_setUptrt)
static inline void mcuxClPkc_inline_setUptrt(const uint16_t * pUptrt)
{
    MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_11_4, "Convert pointer to address.")
    uint32_t uptrtAddr = (uint32_t) pUptrt;
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_11_4)

    MCUXCLPKC_SFR_WRITE(UPTRT, uptrtAddr);
}

/** Inline function to get the address of UPTRT (Universal pointer FUP table). */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_getUptrt)
static inline uint16_t * mcuxClPkc_inline_getUptrt(void)
{
    uint32_t uptrtAddr = MCUXCLPKC_SFR_READ(UPTRT);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_INTEGER_TO_POINTER("Convert UPTRT address to pointer.")
    return (uint16_t *) uptrtAddr;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_INTEGER_TO_POINTER()
}

/** Inline function to convert CPU pointer to PKC offset. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ptr2Offset)
static inline uint16_t mcuxClPkc_inline_ptr2Offset(const uint8_t * cpuPointer)
{
    MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(MISRA_C_2012_Rule_11_4, "calculate PKC operand offset.")
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(CERT_STR30_C, "it's a pointer to PKC operand, but not string literal.")

    uint32_t maskedAddress = (uint32_t) cpuPointer & MCUXCLPKC_RAM_OFFSET_MASK;

    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(CERT_STR30_C)
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(MISRA_C_2012_Rule_11_4)

    return (uint16_t) maskedAddress;
}

/** Inline function to convert PKC offset to CPU pointer. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_offset2Ptr)
static inline uint8_t * mcuxClPkc_inline_offset2Ptr(uint16_t pkcOffset)
{
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_INTEGER_TO_POINTER("convert PKC operand offset to pointer.")

    uint32_t address = (uint32_t) pkcOffset | (uint32_t) MCUXCLPKC_RAM_START_ADDRESS;
    uint8_t * ptr = (uint8_t *) address;

    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_INTEGER_TO_POINTER()

    return ptr;
}

/** Inline function to convert PKC offset to CPU word-aligned pointer. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_offset2PtrWord)
static inline uint32_t * mcuxClPkc_inline_offset2PtrWord(uint16_t pkcOffset)
{
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_TYPECAST_INTEGER_TO_POINTER("convert PKC operand offset (PKC-word aligned) to pointer.")

    uint32_t address = (uint32_t) pkcOffset | (uint32_t) MCUXCLPKC_RAM_START_ADDRESS;
    uint32_t * ptrWord = (uint32_t *) address;

    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TYPECAST_INTEGER_TO_POINTER()

    return ptrWord;
}


/**********************************************************/
/* Inline functions for parameter set 1 and 2             */
/**********************************************************/
/** Inline function to set packed MCLEN and (OP)LEN of parameter set 1. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ps1_setLengthReg)
static inline void mcuxClPkc_inline_ps1_setLengthReg(uint32_t mclen_oplen)
{
    MCUXCLPKC_SFR_WRITE(LEN1, mclen_oplen);
}

/** Inline function to set packed MCLEN and (OP)LEN of parameter set 2. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ps2_setLengthReg)
static inline void mcuxClPkc_inline_ps2_setLengthReg(uint32_t mclen_oplen)
{
    MCUXCLPKC_SFR_WRITE(LEN2, mclen_oplen);
}

/** Inline function to get packed MCLEN and (OP)LEN of parameter set 1. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ps1_getLengthReg)
static inline uint32_t mcuxClPkc_inline_ps1_getLengthReg(void)
{
    uint32_t lengths = MCUXCLPKC_SFR_READ(LEN1);
    return lengths;
}

/** Inline function to get packed MCLEN and (OP)LEN of parameter set 2. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ps2_getLengthReg)
static inline uint32_t mcuxClPkc_inline_ps2_getLengthReg(void)
{
    uint32_t lengths = MCUXCLPKC_SFR_READ(LEN2);
    return lengths;
}

/** Inline function to get (OP)LEN of parameter set 1. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ps1_getOplen)
static inline uint16_t mcuxClPkc_inline_ps1_getOplen(void)
{
    uint32_t opLen =  MCUXCLPKC_SFR_BITREAD(LEN1, LEN);
    return (uint16_t) opLen;
}

/** Inline function to get MCLEN of parameter set 1. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_ps1_getMclen)
static inline uint16_t mcuxClPkc_inline_ps1_getMclen(void)
{
    uint32_t mcLen = MCUXCLPKC_SFR_BITREAD(LEN1, MCLEN);
    return (uint16_t) mcLen;
}


/**********************************************************/
/* Inline functions to wait PKC computations              */
/**********************************************************/
/** Inline function to wait until PKC finishes both on-going and pending calculations (if there is any). */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_waitForFinish)
static inline void mcuxClPkc_inline_waitForFinish(void)
{
    do{} while(0u != MCUXCLPKC_SFR_BITREAD(STATUS, ACTIV));
}

/** Inline function to wait until PKC is ready to accept next calculation (i.e., no pending calculation). */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_waitForReady)
static inline void mcuxClPkc_inline_waitForReady(void)
{
    do{} while(0u != MCUXCLPKC_SFR_BITREAD(STATUS, GOANY));
}

/** Inline function to wait PKC calculation and then get PKC status. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_inline_waitForFinishGetStatus)
static inline uint32_t mcuxClPkc_inline_waitForFinishGetStatus(void)
{
    uint32_t pkc_status;
    do {
        pkc_status = MCUXCLPKC_SFR_READ(STATUS);
    } while (0u != (pkc_status & MCUXCLPKC_SFR_BITMSK(STATUS, ACTIV)));

    return pkc_status;
}


#endif /* MCUXCLPKC_INLINE_FUNCTIONS_H_ */
