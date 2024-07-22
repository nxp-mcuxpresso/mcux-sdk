/*--------------------------------------------------------------------------*/
/* Copyright  2022-2024 NXP                                                 */
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

/** @file  mcuxClOsccaAeadModes_Constants.c
 *  @brief Definition of the mode descriptors for all provided aead modes
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <mcuxClOsccaAeadModes_Modes.h>
#include <internal/mcuxClAead_Descriptor.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Types.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Functions.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Algorithms.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClAead_ModeDescriptor_t mcuxClOsccaAeadModes_ModeDescriptor_CCM_ENC = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
  .crypt = mcuxClOsccaAeadModes_crypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_crypt),

  .init = mcuxClOsccaAeadModes_init,
  .processAad = mcuxClOsccaAeadModes_process_adata,
  .process = mcuxClOsccaAeadModes_process,
  .finish = mcuxClOsccaAeadModes_finish,
  .verify = mcuxClOsccaAeadModes_verify,
  .protection_token_init =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_init),
  .protection_token_processAad = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_process_adata),
  .protection_token_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_process),
  .protection_token_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_finish),
  .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_verify),
  .algorithm = (const struct mcuxClAead_AlgorithmDescriptor *)&mcuxClOsccaAead_algorithm_CCM_ENC
};

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClAead_ModeDescriptor_t mcuxClOsccaAeadModes_ModeDescriptor_CCM_DEC = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
  .crypt = mcuxClOsccaAeadModes_crypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_crypt),

  .init = mcuxClOsccaAeadModes_init,
  .processAad = mcuxClOsccaAeadModes_process_adata,
  .process = mcuxClOsccaAeadModes_process,
  .finish = mcuxClOsccaAeadModes_finish,
  .verify = mcuxClOsccaAeadModes_verify,
  .protection_token_init =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_init),
  .protection_token_processAad = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_process_adata),
  .protection_token_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_process),
  .protection_token_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_finish),
  .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_verify),
  .algorithm = (const struct mcuxClAead_AlgorithmDescriptor *)&mcuxClOsccaAead_algorithm_CCM_DEC
};

