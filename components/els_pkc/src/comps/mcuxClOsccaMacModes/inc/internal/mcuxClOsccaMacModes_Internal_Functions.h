/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/** @file  mcuxClOsccaMacModes_Internal_Functions.h
 *  @brief Internal definitions of helper functions for the mcuxClOsccaMacModes component
 */

#ifndef MCUXCLOSCCAMACMODES_INTERNAL_FUNCTIONS_H_
#define MCUXCLOSCCAMACMODES_INTERNAL_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClSession_Types.h>

/**
 * @brief Skeleton functions for the MAC modes
 */

/**
 * @brief Mac Oneshot Compute function type
 *
 * This function will perform the actual MAC compute operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaMacModes_compute, mcuxClMac_ComputeFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_compute(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
);



/**
 * @brief MacModes Multipart Init function type
 *
 * This function will perform the actual MAC init operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaMacModes_init, mcuxClMac_InitFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxClKey_Handle_t key
);

/**
 * @brief MacModes Multipart Process function type
 *
 * This function will perform the actual MAC process operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaMacModes_process, mcuxClMac_ProcessFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength
);

/**
 * @brief MacModes Multipart Finish function type
 *
 * This function will perform the actual MAC finish operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaMacModes_finish, mcuxClMac_FinishFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClOsccaMacModes_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
);


#ifdef MCUXCL_FEATURE_MACMODES_CMAC_SM4
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaMacModes_SM4_Gen_K1K2)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaMacModes_SM4_Gen_K1K2(uint8_t *output, uint8_t * input);
#endif /* MCUXCL_FEATURE_MACMODES_CMAC_SM4 */

#endif /* MCUXCLOSCCAMACMODES_INTERNAL_FUNCTIONS_H_ */
