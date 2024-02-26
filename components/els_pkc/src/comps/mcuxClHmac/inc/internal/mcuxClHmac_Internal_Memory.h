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

/** @file  mcuxClHmac_Internal_Memory.h
 *  @brief Internal definitions of memory sizes for the HMAC component
 */

#ifndef MCUXCLHMAC_INTERNAL_MEMORY_H_
#define MCUXCLHMAC_INTERNAL_MEMORY_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClHashModes_Constants.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClHash_Internal_Memory.h>
#include <internal/mcuxClHashModes_Internal_Memory.h>
#include <internal/mcuxClHmac_Internal_Macros.h>
#include <internal/mcuxClHmac_Internal_Types.h>

#define MCUXCLHMAC_INTERNAL_WACPU_INIT      MCUXCLHASH_BLOCK_SIZE_MAX + MCUXCLHASH_INTERNAL_WACPU_MAX
#define MCUXCLHMAC_INTERNAL_WACPU_FINISH    MCUXCLHASH_MAX_OUTPUT_SIZE

#define MCUXCLHMAC_INTERNAL_MAX_WACPU       MCUXCLHMAC_MAX(MCUXCLHMAC_INTERNAL_WACPU_INIT, MCUXCLHMAC_INTERNAL_WACPU_FINISH)

#define MCUXCLHMAC_INTERNAL_MAX_CONTEXT_SIZE     (sizeof(mcuxClHmac_Context_Sw_t))


#endif /* MCUXCLHMAC_INTERNAL_MEMORY_H_ */

