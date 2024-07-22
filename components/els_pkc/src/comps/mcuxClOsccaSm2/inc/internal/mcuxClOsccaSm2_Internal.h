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
 * @file  mcuxClOsccaSm2_Internal.h
 * @brief internal header for SM2 curves
 */


#ifndef MCUXCLOSCCASM2_INTERNAL_H_
#define MCUXCLOSCCASM2_INTERNAL_H_


#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2_Types.h>
#include <internal/mcuxClOsccaSm2_Internal_PkcWaLayout.h>
#include <internal/mcuxClOsccaSm2_Internal_FP.h>
#include <internal/mcuxClOsccaSm2_Internal_FUP.h>
#include <internal/mcuxClOsccaSm2_Internal_Helper.h>
#include <internal/mcuxClOsccaSm2_Internal_Ecc.h>
#include <internal/mcuxClOsccaSm2_Internal_Types.h>
#include <internal/mcuxClOsccaSm2_Internal_Functions.h>
#include <internal/mcuxClOsccaSm2_Internal_CryptoUtils.h>
#include <mcuxClBuffer.h>
#ifdef MCUXCL_FEATURE_SM2_INTERNAL
#include <internal/mcuxClOsccaSm2_Internal_ConstructTypes.h>
#endif /* MCUXCL_FEATURE_SM2_INTERNAL */

#endif /* MCUXCLOSCCASM2_INTERNAL_H_ */
