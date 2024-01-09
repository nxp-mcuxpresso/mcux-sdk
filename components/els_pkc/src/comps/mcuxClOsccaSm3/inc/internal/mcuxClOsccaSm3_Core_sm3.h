/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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

/** @file  mcuxClOsccaSm3_Core_sm3.h
 *  @brief Internal definitions and declarations of the *CORE* layer dedicated to SAFO SM3
 */

#ifndef MCUXCLOSCCASM3_CORE_SM3_H_
#define MCUXCLOSCCASM3_CORE_SM3_H_

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

/**********************************************************
 * Type declarations
 **********************************************************/

/*
 * \brief Function SM3 Process Message on HW Norm mode
 *
 * \return void
 *
 * \param[out]      workArea   Pointer to buffer after processing
 * \param[in]       data       Pointer to buffer of message that needs to be processed
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm3_Safo_Hash_Norm)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_Safo_Hash_Norm(uint32_t *workArea, uint32_t *data);

/*
 * \brief Function SM3 Process Message on HW Auto mode
 *
 * \return void
 *
 * \param[out]      workArea   Pointer to buffer after processing
 * \param[in]       data       Pointer to buffer of message that needs to be processed
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm3_Safo_Hash_Auto)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_Safo_Hash_Auto(uint32_t *workArea, uint32_t *data);

 /*
 * \brief Function SM3 PreLoad IV or Hash
  *
  * \return void
  *
  * \param[in]  workArea     Pointer to buffer for IV
  */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm3_Safo_Hash_PreLoad)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_Safo_Hash_PreLoad(uint32_t *workArea);

#endif /* MCUXCLOSCCASM3_CORE_SM3_H_ */
