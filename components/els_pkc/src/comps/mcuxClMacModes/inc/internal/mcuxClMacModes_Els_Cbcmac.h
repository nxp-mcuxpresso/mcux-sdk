/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

#ifndef MCUXCLMACMODES_ELS_CBCMAC_H_
#define MCUXCLMACMODES_ELS_CBCMAC_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClKey_Types.h>
#include <mcuxClSession_Types.h>
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Engine functions
 */

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMacModes_Engine_CBCMAC_Oneshot)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Oneshot(
  mcuxClSession_Handle_t session,           /*! CBC-MAC session handle */
  mcuxClMacModes_Context_t * const pContext,/*! CBC-MAC context */
  const uint8_t * const pIn,               /*! CBC-MAC input */
  uint32_t inLength,                       /*! Input size */
  uint8_t * const pOut,                    /*! CBC-MAC output */
  uint32_t * const pOutLength              /*! Output size */
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMacModes_Engine_CBCMAC_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Init(
  mcuxClSession_Handle_t session,           /*! CBC-MAC session handle */
  mcuxClMacModes_Context_t * const pContext /*! CBC-MAC context */
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMacModes_Engine_CBCMAC_Update)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Update(
  mcuxClSession_Handle_t session,           /*! CBC-MAC session handle */
  mcuxClMacModes_Context_t * const pContext,/*! CBC-MAC context */
  const uint8_t * const pIn,               /*! CBC-MAC input */
  uint32_t inLength                        /*! Input size */
);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMacModes_Engine_CBCMAC_Finalize)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Finalize(
  mcuxClSession_Handle_t session,           /*! CBC-MAC session handle */
  mcuxClMacModes_Context_t * const pContext,/*! CBC-MAC context */
  uint8_t * const pOut,                    /*! CBC-MAC output */
  uint32_t * const pOutLength              /*! Output size */
);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMACMODES_ELS_CBCMAC_H_ */
