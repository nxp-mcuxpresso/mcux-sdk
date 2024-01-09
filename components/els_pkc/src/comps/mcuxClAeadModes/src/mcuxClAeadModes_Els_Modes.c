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

/** @file  mcuxClAeadModes_Els_Modes.c
 *  @brief Definition of the mode descriptors for all provided Cipher modes
 */

#include <internal/mcuxClAeadModes_Els_Algorithms.h>
#include <internal/mcuxClAead_Internal_Descriptor.h>
#include <internal/mcuxClAeadModes_Els_Types.h>
#include <internal/mcuxClAeadModes_Common_Functions.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClAeadModes_Modes.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_GCM_ENC = {
  .crypt = mcuxClAeadModes_crypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_crypt),

  .init = mcuxClAeadModes_init,
  .protection_token_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_init),
  .processAad = mcuxClAeadModes_process_adata,
  .protection_token_processAad = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process_adata),
  .process = mcuxClAeadModes_process,
  .protection_token_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process),
  .finish = mcuxClAeadModes_finish,
  .protection_token_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_finish),
  .verify = mcuxClAeadModes_verify,
  .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_verify),
  .algorithm = &mcuxClAeadModes_AlgorithmDescriptor_Aes_Gcm_enc
};

const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_GCM_DEC = {
  .crypt = mcuxClAeadModes_crypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_crypt),

  .init = mcuxClAeadModes_init,
  .protection_token_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_init),
  .processAad = mcuxClAeadModes_process_adata,
  .protection_token_processAad = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process_adata),
  .process = mcuxClAeadModes_process,
  .protection_token_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process),
  .finish = mcuxClAeadModes_finish,
  .protection_token_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_finish),
  .verify = mcuxClAeadModes_verify,
  .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_verify),
  .algorithm = &mcuxClAeadModes_AlgorithmDescriptor_Aes_Gcm_dec
};


const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_CCM_ENC = {
  .crypt = mcuxClAeadModes_crypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_crypt),

  .init = mcuxClAeadModes_init,
  .protection_token_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_init),
  .processAad = mcuxClAeadModes_process_adata,
  .protection_token_processAad = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process_adata),
  .process = mcuxClAeadModes_process,
  .protection_token_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process),
  .finish = mcuxClAeadModes_finish,
  .protection_token_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_finish),
  .verify = mcuxClAeadModes_verify,
  .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_verify),
  .algorithm = &mcuxClAeadModes_AlgorithmDescriptor_Aes_Ccm_enc
};

const mcuxClAead_ModeDescriptor_t mcuxClAead_ModeDescriptor_AES_CCM_DEC = {
  .crypt = mcuxClAeadModes_crypt,
  .protection_token_crypt = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_crypt),

  .init = mcuxClAeadModes_init,
  .protection_token_init = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_init),
  .processAad = mcuxClAeadModes_process_adata,
  .protection_token_processAad = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process_adata),
  .process = mcuxClAeadModes_process,
  .protection_token_process = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_process),
  .finish = mcuxClAeadModes_finish,
  .protection_token_finish = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_finish),
  .verify = mcuxClAeadModes_verify,
  .protection_token_verify = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_verify),
  .algorithm = &mcuxClAeadModes_AlgorithmDescriptor_Aes_Ccm_dec
};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
