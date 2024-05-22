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

/** @file  mcuxClMac_Internal_Constants.h
 *  @brief Internal header for MAC constants
 */

#ifndef MCUXCLMAC_INTERNAL_CONSTANTS_H_
#define MCUXCLMAC_INTERNAL_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMacModes_Constants.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>
#include <mcuxClHmac_Constants.h>
#include <internal/mcuxClHmac_Internal_Memory.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define maximum output size for mcuxClHmac modes */
#define MCUXCLMAC_MAX_OUTPUT_SIZE_HMAC                       (MCUXCLHMAC_MAX_OUTPUT_SIZE)

/* Define maximum output size for mcuxClMacModes modes */
#define MCUXCLMAC_MAX_OUTPUT_SIZE_MACMODES                   (MCUXCLMACMODES_MAX_OUTPUT_SIZE)

#define MCUXCLMAC_MAX_OUTPUT_SIZE                            ((MCUXCLMAC_MAX_OUTPUT_SIZE_HMAC > MCUXCLMAC_MAX_OUTPUT_SIZE_MACMODES) ? MCUXCLMAC_MAX_OUTPUT_SIZE_HMAC : MCUXCLMAC_MAX_OUTPUT_SIZE_MACMODES)
#define MCUXCLMAC_MAX_OUTPUT_SIZE_IN_WORDS                   (MCUXCLMAC_MAX_OUTPUT_SIZE / sizeof(uint32_t))


/* Define maximum context size for mcuxClHmac modes */
#define MCUXCLMAC_MAX_CONTEXT_SIZE_HMAC                       (MCUXCLHMAC_INTERNAL_MAX_CONTEXT_SIZE)

/* Define maximum context size for mcuxClMacModes modes */
#define MCUXCLMAC_MAX_CONTEXT_SIZE_MACMODES                   (sizeof(mcuxClMacModes_Context_t))

#define MCUXCLMAC_MAX_CONTEXT_SIZE                            ((MCUXCLMAC_MAX_CONTEXT_SIZE_HMAC > MCUXCLMAC_MAX_CONTEXT_SIZE_MACMODES) ? MCUXCLMAC_MAX_CONTEXT_SIZE_HMAC : MCUXCLMAC_MAX_CONTEXT_SIZE_MACMODES)
#define MCUXCLMAC_MAX_CONTEXT_SIZE_IN_WORDS                   (MCUXCLMAC_MAX_CONTEXT_SIZE / sizeof(uint32_t))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMAC_INTERNAL_CONSTANTS_H_ */
