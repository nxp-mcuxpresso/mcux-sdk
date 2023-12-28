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
 * @file  mcuxClOsccaPkc_Functions.h
 * @brief APIs of mcuxClOsccaPkc component
 */


#ifndef MCUXCLOSCCAPKC_FUNCTIONS_H_
#define MCUXCLOSCCAPKC_FUNCTIONS_H_


#include <stdint.h>
#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

/**
 * @defgroup mcuxClOsccaPkc_Functions mcuxClOsccaPkc_Functions
 * @brief Defines all functions of @ref mcuxClOsccaPkc
 * @ingroup mcuxClOsccaPkc
 * @{
 */

/**
 * @brief Structure of PKC state backup.
 */
typedef struct mcuxClOsccaPkc_State_t
{
    uint32_t cfg;
    uint32_t ctrl;
}mcuxClOsccaPkc_State_t;

/** @brief type of FUP program address. */
typedef const struct mcuxClOsccaPkc_FUPEntry * mcuxClOsccaPkc_PtrFUPEntry_t;

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_Reset) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_Reset(mcuxClOsccaPkc_State_t *state) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_Init) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_Init(mcuxClOsccaPkc_State_t *state) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_SetWordSize) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_SetWordSize(uint32_t redmul) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_GetWordSize) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaPkc_GetWordSize(void) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_WaitforFinish) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_WaitforFinish(void) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_SetFupTable) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_SetFupTable(void *pUPTRT) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_Op) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_Op(uint32_t mode, uint32_t iRiXiYiZ) ;
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_StartFupProgram) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_StartFupProgram(mcuxClOsccaPkc_PtrFUPEntry_t fupProgram, uint32_t fupProgramSize);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_ComputeNDash) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_ComputeNDash(uint32_t iNiTiXiX);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_ComputeQSquared) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_ComputeQSquared(uint32_t iQiMiTiX, uint16_t iMs);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_GeneratePointerTable) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_GeneratePointerTable(uint16_t *pOperandsBase, uint8_t *pBufferBase, uint32_t bufferSize, uint32_t bufferNums);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_MultipleShiftRotate_Index) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_MultipleShiftRotate_Index(uint32_t iModuluss, uint32_t iModulus, uint32_t leadingZeroBits, _Bool shiftLeft);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_LeadingZeros) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaPkc_LeadingZeros(uint8_t *pNum, uint32_t numLen);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_ComputeModInv) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_ComputeModInv(uint32_t iRiIiNiT, uint32_t iT2);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaPkc_CalcMontInverse) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_CalcMontInverse(uint32_t iIiRiNiT, uint32_t R2);


/**
 * @}
 */ /* mcuxClOsccaPkc_Functions */

#endif /*MCUXCLOSCCAPKC_FUNCTIONS_H_*/
