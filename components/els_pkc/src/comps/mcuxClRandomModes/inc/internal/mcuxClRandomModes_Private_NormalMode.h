/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

#ifndef MCUXCLRANDOMMODES_PRIVATE_NORMALMODE_H_
#define MCUXCLRANDOMMODES_PRIVATE_NORMALMODE_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClSession.h>
#include <mcuxClRandom_Types.h>
#include <internal/mcuxClRandom_Internal_Types.h>


#ifdef __cplusplus
extern "C" {
#endif

/* Internal function prototypes */

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_NormalMode_initFunction, mcuxClRandom_initFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_initFunction(mcuxClSession_Handle_t pSession);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_NormalMode_reseedFunction, mcuxClRandom_reseedFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_reseedFunction(mcuxClSession_Handle_t pSession);

#ifdef MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_NormalMode_generateFunction_PrDisabled, mcuxClRandom_generateFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_generateFunction_PrDisabled(mcuxClSession_Handle_t pSession, uint8_t *pOut, uint32_t outLength);

extern const mcuxClRandom_OperationModeDescriptor_t mcuxClRandomModes_OperationModeDescriptor_NormalMode_PrDisabled;
#endif /* MCUXCL_FEATURE_RANDOMMODES_PR_DISABLED */


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_NormalMode_selftestFunction, mcuxClRandom_selftestFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_NormalMode_selftestFunction(mcuxClSession_Handle_t pSession, mcuxClRandom_Mode_t mode);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_selftest_VerifyArrays)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_selftest_VerifyArrays(uint32_t wordLength, const uint32_t * const expected, uint32_t *actual);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_PRIVATE_NORMALMODE_H_ */
