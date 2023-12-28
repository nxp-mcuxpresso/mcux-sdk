/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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

/** @file  mcuxClHashModes_Internal_els_sha2.h
 *  @brief Internal definitions and declarations of the *INTERNAL* layer dedicated to ELS
 */

#ifndef MCUXCLHASHMODES_INTERNAL_ELS_SHA2_H_
#define MCUXCLHASHMODES_INTERNAL_ELS_SHA2_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************
 * Type declarations
 **********************************************************/

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
/**
 * @brief DMA protection function type
 *
 * This function will verify if the DMA transfer of the last hardware accelerator operation finished on the expected address
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHashModes_AlgoDmaProtection_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) (*mcuxClHashModes_AlgoDmaProtection_t)(uint8_t *startAddress,
                                                        size_t expectedLength));

#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

/**********************************************************
 * Function declarations
 **********************************************************/
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_INTERNAL_ELS_SHA2_H_ */
