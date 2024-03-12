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

#ifndef MCUXCLSIGNATURE_CONSTANTS_H_
#define MCUXCLSIGNATURE_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/* New Error codes */
#define MCUXCLSIGNATURE_STATUS_OK                      (0x0FF72E03u)
#define MCUXCLSIGNATURE_STATUS_FAULT_ATTACK            (0x0FF7F0F0u)

// Old Error Codes
#define MCUXCLSIGNATURE_STATUS_FAILURE              (0x0FF75330u)
#define MCUXCLSIGNATURE_FAILURE                     MCUXCLSIGNATURE_STATUS_FAILURE ///< @deprecated Please use #MCUXCLSIGNATURE_STATUS_FAILURE instead
#define MCUXCLSIGNATURE_OK                          MCUXCLSIGNATURE_STATUS_OK ///< @deprecated Please use #MCUXCLSIGNATURE_STATUS_OK instead
#define MCUXCLSIGNATURE_STATUS_NOT_OK               (0x0FF753FCu)
#define MCUXCLSIGNATURE_NOT_OK                      MCUXCLSIGNATURE_STATUS_NOT_OK ///< @deprecated Please use #MCUXCLSIGNATURE_STATUS_NOT_OK instead
#define MCUXCLSIGNATURE_STATUS_INVALID_PARAMS       (0x0FF753F8u)
#define MCUXCLSIGNATURE_INVALID_PARAMS              MCUXCLSIGNATURE_STATUS_INVALID_PARAMS ///< @deprecated Please use #MCUXCLSIGNATURE_STATUS_INVALID_PARAMS instead
#define MCUXCLSIGNATURE_STATUS_NOT_SUPPORTED        (0x0FF75370u)
#define MCUXCLSIGNATURE_NOT_SUPPORTED               MCUXCLSIGNATURE_STATUS_NOT_SUPPORTED  ///< @deprecated Please use #MCUXCLSIGNATURE_STATUS_NOT_SUPPORTED instead

#endif /* MCUXCLSIGNATURE_CONSTANTS_H_ */
