/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClMacModes_Els_Ctx.h
 *  @brief Internal header for the MAC context for modes using the ELS
 */

#ifndef MCUXCLMACMODES_ELS_CTX_H_
#define MCUXCLMACMODES_ELS_CTX_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMac_Ctx.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClAes.h>
#include <mcuxClEls.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mac context structure for modes using ELS HW
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular Mac mode/algorithm to work.
 */
typedef struct mcuxClMacModes_Context
{
  mcuxClMac_Context_t common;                             ///< Common part of the context, for all modes
  mcuxClKey_Descriptor_t * key;                           ///< Key descriptor of the key to be used
  uint32_t blockBuffer[MCUXCLAES_BLOCK_SIZE_IN_WORDS];  ///< Not yet processed input data from the input stream
  uint32_t blockBufferUsed;                              ///< Used bytes in blockBuffer
  uint32_t state[MCUXCLAES_BLOCK_SIZE_IN_WORDS];        ///< state/intermediate result of the mac operation
  mcuxClEls_CmacOption_t cmac_options;                    ///< Cmac ELS options to be used
  uint32_t totalInput;                                  ///< Total input length
} mcuxClMacModes_Context_t;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMACMODES_ELS_CTX_H_ */
