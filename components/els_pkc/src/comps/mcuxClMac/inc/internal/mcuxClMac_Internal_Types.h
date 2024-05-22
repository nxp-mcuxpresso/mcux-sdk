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

/** @file  mcuxClMac_Internal_Types.h
 *  @brief Internal header for MAC types
 */

#ifndef MCUXCLMAC_INTERNAL_TYPES_H_
#define MCUXCLMAC_INTERNAL_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <mcuxClMac_Constants.h>
#include <mcuxClKey_Types.h>
#include <mcuxClCore_Buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Mode/Skeleton function types
 */

/**
 * @brief Mac Oneshot Compute function type
 *
 * This function will perform the actual MAC compute operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClMac_ComputeFunc_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_ComputeFunc_t)(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
));

/**
 * @brief Mac Multipart Init function type
 *
 * This function will perform the actual MAC init operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClMac_InitFunc_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_InitFunc_t)(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxClKey_Handle_t key
));

/**
 * @brief Mac Multipart Process function type
 *
 * This function will perform the actual MAC process operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClMac_ProcessFunc_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_ProcessFunc_t)(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength
));

/**
 * @brief Mac Multipart Finish function type
 *
 * This function will perform the actual MAC finish operation based on the given mode
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClMac_FinishFunc_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_FinishFunc_t)(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
));



/**
 * Internal structures
 */

/**
 * @brief Mac common mode descriptor structure
 *
 * This structure captures all the information that the MAC interfaces need
 * to know about a particular MAC mode/algorithm.
 */
typedef struct mcuxClMac_CommonModeDescriptor
{
  mcuxClMac_ComputeFunc_t     compute;
  uint32_t                   protectionToken_compute;
  mcuxClMac_InitFunc_t        init;
  uint32_t                   protectionToken_init;
  mcuxClMac_ProcessFunc_t     process;
  uint32_t                   protectionToken_process;
  mcuxClMac_FinishFunc_t      finish;
  uint32_t                   protectionToken_finish;
  uint32_t                   macByteSize; /* output size of the MAC computation in bytes */
  void *                     pAlgorithm;  /* pointer to algorithm specifics, individual structures can be assigned here */
} mcuxClMac_CommonModeDescriptor_t;

/**
 * @brief Mac top-level mode/algorithm descriptor structure
 *
 * This structure contains common information for all MAC modes.
 */
struct mcuxClMac_ModeDescriptor
{
  mcuxClMac_CommonModeDescriptor_t common;   /* top-level mode information */
  void * pCustom;                           /* additional mode-specific data structure */
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMAC_INTERNAL_TYPES_H_ */
