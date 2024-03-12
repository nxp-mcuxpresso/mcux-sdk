/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClRandom_Internal_Functions.h
 * @brief Internal functions definitions of mcuxClRandom component
 */

#ifndef MCUXCLRANDOM_INTERNAL_FUNCTIONS_H_
#define MCUXCLRANDOM_INTERNAL_FUNCTIONS_H_

#include <mcuxClSession.h>
#include <mcuxClRandom.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Random data generation function (internal).
 * This function should be used instead of mcuxClRandom_generate() if called
 * from within the CL. This should be done in order to allow cross-function DI protection.
 *
 * This function generates random data based on the information contained in
 * the Random context referenced in the session handle.
 *
 * @param [in]     pSession  Handle for the current CL session.
 * @param [out]    pOut      Buffer in which the generated random data must be
 *                           written.
 * @param [in]     outLength Number of random data bytes that must be written in the
 *                           @p pOut buffer.
 *
 * @return status
 *
 * Data Integrity: Expunge(pSession + pOut + outLength)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandom_generate_internal)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandom_generate_internal(
    mcuxClSession_Handle_t pSession,
    mcuxCl_Buffer_t        pOut,
    uint32_t              outLength);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOM_INTERNAL_FUNCTIONS_H_ */
