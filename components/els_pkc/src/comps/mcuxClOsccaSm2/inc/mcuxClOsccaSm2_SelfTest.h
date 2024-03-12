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

/**
 *
 * @file:    mcuxClOsccaSm2_SelfTest.h
 * @brief:   Self test function prototype definitions for the OSCCA SM2 component
 *
 */

#ifndef MCUXCLOSCCA_SM2_SELFTEST_H_
#define MCUXCLOSCCA_SM2_SELFTEST_H_

#include <mcuxClSession.h>
#include <mcuxClHash.h>
#include <mcuxClOsccaSm3_Constants.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C"
{
#endif

/************************************************************************************/
/** \brief SM2 selftest error codes                                                             */
/************************************************************************************/

typedef uint32_t mcuxClOsccaSm2_SelfTest_Status_t;

#define MCUXCLOSCCASM2_STATUS_SELFTEST_OK                                 ((mcuxClOsccaSm2_SelfTest_Status_t) 0x011B2E4FU)
#define MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL                               ((mcuxClOsccaSm2_SelfTest_Status_t) 0x011B53FCU)
#define MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK                       ((mcuxClOsccaSm2_SelfTest_Status_t) 0x011BF0F0U)

/**
 * \brief This function tests the OSCCA SM2 encryption and decryption APIs.
 *
 * \param[in]  session                   Pointer to #mcuxClSession_Descriptor
 *
 * \returns Result of the test
 *
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_OK               Test succeeded
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL             Test failed
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK     Checking security counter failed or APIs returned FAULT_ATTACK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EncDec_SelfTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_SelfTest_Status_t) mcuxClOsccaSm2_EncDec_SelfTest(
    mcuxClSession_Handle_t session
);

/**
 * \brief This function tests the OSCCA SM2 signature and verification APIs.
 *
 * \param[in]  session                   Pointer to #mcuxClSession_Descriptor
 *
 * \returns Result of the test
 *
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_OK               Test succeeded
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL             Test failed
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK     Checking security counter failed or APIs returned FAULT_ATTACK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_SignVerify_SelfTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_SelfTest_Status_t) mcuxClOsccaSm2_SignVerify_SelfTest(
    mcuxClSession_Handle_t session
);

/**
 * \brief This function tests the OSCCA SM2 keyexchange APIs.
 *
 * \param[in]  session                   Pointer to #mcuxClSession_Descriptor
 *
 * \returns Result of the test
 *
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_OK               Test succeeded
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_FAIL             Test failed
 * \retval ::MCUXCLOSCCASM2_STATUS_SELFTEST_FAULT_ATTACK     Checking security counter failed or APIs returned FAULT_ATTACK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_KeyExchange_SelfTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_SelfTest_Status_t) mcuxClOsccaSm2_KeyExchange_SelfTest(
    mcuxClSession_Handle_t session
);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // MCUXCLOSCCA_SM2_SELFTEST_H_
