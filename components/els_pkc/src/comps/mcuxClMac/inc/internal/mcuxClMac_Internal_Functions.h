/*--------------------------------------------------------------------------*/
/* Copyright      2023 NXP                                                  */
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

/** @file  mcuxClMac_Internal_Functions.h
 *  @brief Internal header for the MAC internal functions
 */

#ifndef MCUXCLMAC_INTERNAL_FUNCTIONS_H_
#define MCUXCLMAC_INTERNAL_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMac_Ctx.h>

#include <mcuxCsslFlowProtection.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Computes the CRC for a MAC context struct (without the CRC value member) and saves it in the struct.
 * 
 * When the MAC_CONTEXT_INTEGRITY_PROTECTION feature is not active, the function does nothing.
 * 
 * @param[in,out]     pCtx            Pointer to the MAC context struct.
 * @param[in]         contextSize     Size of the MAC context struct in bytes (including the CRC value member).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_computeContextCrc)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMac_computeContextCrc(mcuxClMac_Context_t * const pCtx, uint32_t contextSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_computeContextCrc);


  MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMac_computeContextCrc);
}

/**
 * @brief Verifies the CRC of a MAC context struct.
 * 
 * The function computes the CRC for a MAC context struct (without the CRC value member) and checks if it is equal
 * to the saved CRC value within the struct.
 * When the MAC_CONTEXT_INTEGRITY_PROTECTION feature is not active, the function always returns MCUXCLMAC_STATUS_OK.
 * 
 * @param[in]         pCtx            Pointer to the MAC context struct.
 * @param[in]         contextSize     Size of the MAC context struct in bytes (including the CRC value member).
 * 
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_STATUS_OK               Mac operation successful
 * @retval MCUXCLMAC_STATUS_FAULT_ATTACK     Fault attack detected    
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_verifyContextCrc)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_verifyContextCrc(mcuxClMac_Context_t * const pCtx, uint32_t contextSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_verifyContextCrc);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_verifyContextCrc, MCUXCLMAC_STATUS_OK);
  
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMAC_INTERNAL_FUNCTIONS_H_ */
