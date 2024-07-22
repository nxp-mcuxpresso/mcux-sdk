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

#ifndef MCUXCLRANDOMMODES_PRIVATE_PRDISABLED_H_
#define MCUXCLRANDOMMODES_PRIVATE_PRDISABLED_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClRandom_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MCUXCLRANDOMMODES_TESTVECTORS_INDEX_ENTROPY_PRDISABLED        ( 0u)
#define MCUXCLRANDOMMODES_TESTVECTORS_INDEX_ENTROPY_RESEED_PRDISABLED ( 1u)
#define MCUXCLRANDOMMODES_TESTVECTORS_INDEX_RANDOMDATA_PRDISABLED     ( 2u)
#define MCUXCLRANDOMMODES_NO_OF_TESTVECTORS_PRDISABLED (MCUXCLRANDOMMODES_TESTVECTORS_INDEX_RANDOMDATA_PRDISABLED + 1u)

#ifdef MCUXCL_FEATURE_RANDOMMODES_CTRDRBG
extern const mcuxClRandomModes_DrbgAlgorithmsDescriptor_t mcuxClRandomModes_DrbgAlgorithmsDescriptor_CtrDrbg_PrDisabled;
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */

/* Internal function prototypes */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_PrDisabled_selftestAlgorithm, mcuxClRandomModes_selftestAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_PrDisabled_selftestAlgorithm(mcuxClSession_Handle_t pSession, mcuxClRandom_Context_t pTestCtx, mcuxClRandom_ModeDescriptor_t *pTestMode);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_PRIVATE_PRDISABLED_H_ */
