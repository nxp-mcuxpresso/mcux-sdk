/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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


/** @file  mcuxClOsccaMacModes_Ctx.h
 *  @brief Internal header for the MAC context for modes using the SM4
 */

#ifndef MCUXCLOSCCAMACMODES_CTX_H_
#define MCUXCLOSCCAMACMODES_CTX_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMac_Ctx.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <mcuxClKey_Types.h>
#include <internal/mcuxClOsccaSm4_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mac context structure for modes using SM4
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular Mac mode/algorithm to work.
 */
typedef struct mcuxClOsccaMacModes_Context
{
  mcuxClMac_Context_t common;                         /* Common field of the context, for all modes */
  mcuxClKey_Descriptor_t * pKey;                      ///< Key descriptor of the key to be used
  uint8_t stateIn[MCUXCLOSCCASM4_BLOCK_SIZE];         ///< state of the mac operation
  uint8_t stateIv[MCUXCLOSCCASM4_BLOCK_SIZE];         ///< intermediate result of the mac operation
  uint32_t nrOfUnprocessedBytes;                     ///< number of not yet processed bytes
  uint32_t dataProcessed;                            ///< Indicate, whether data has been processed
} mcuxClOsccaMacModes_Context_t;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCAMACMODES_CTX_H_ */
