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

#ifndef MCUXCLRANDOM_FUNCTIONS_TESTMODE_H_
#define MCUXCLRANDOM_FUNCTIONS_TESTMODE_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClSession.h>
#include <mcuxClRandom_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup mcuxClAPI MCUX CL -- API
 *
 * \defgroup mcuxClRandomTestMode Random TEST_MODE API
 * \brief Random operations in TEST_MODE.
 * \ingroup mcuxClAPI
 */

/**
 * \defgroup clRandomTestMode Random interfaces
 * \brief Interfaces to perform Random handling operations.
 * \ingroup mcuxClRandom
 */

/**
 * \brief This function creates a TEST_MODE descriptor from an existing NORMAL_MODE one
 * \api
 * \ingroup clRandom
 *
 * This function creates a TEST_MODE descriptor from an existing NORMAL_MODE one.
 * The function expects as input a pointer to a buffer to which the user of the CL shall write entropy input to be used for (re)seeding the DRBG.
 * The function shall be called prior to an mcuxClRandom_init call.
 *
 * \param  testMode[out]        Pointer to TEST_MODE descriptor to be initialized
 * \param  normalMode[in]       Pointer to NORMAL_MODE descriptor to be used as basis for the initialization
 * \param  pEntropyInput[in]    Pointer to memory buffer containing entropy input for DRBG (re)seeding
 *
 * \return status
 */
// TODO: Create defines for entropy input sizes using object size filler
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_createTestFromNormalMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_createTestFromNormalMode(
    mcuxClRandom_ModeDescriptor_t *pTestMode,
    mcuxClRandom_Mode_t normalMode,
    const uint32_t * const pEntropyInput
);

/**
 * \brief This function updates the entropy input pointer in a TEST_MODE descriptor
 *
 * \param  testMode[in]         Pointer to TEST_MODE descriptor
 * \param  pEntropyInput[in]    Pointer to memory buffer containing entropy input for DRBG (re)seeding
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK         if the TEST_MODE descriptor generation was successful
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_updateEntropyInput)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_updateEntropyInput(
    mcuxClRandom_ModeDescriptor_t *pTestMode,
    const uint32_t * const pEntropyInput
);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOM_FUNCTIONS_TESTMODE_H_ */
