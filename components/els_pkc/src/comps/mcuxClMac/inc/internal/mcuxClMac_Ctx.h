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

/** @file  mcuxClMac_Ctx.h
 *  @brief Internal header for MAC types
 */

#ifndef MCUXCLMAC_CTX_H_
#define MCUXCLMAC_CTX_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mac context structure
 *
 * This structure is used in the multi-part interfaces to store the
 * information about the current operation and the relevant internal state.
 * This is the common part of the context needed by cipher modes.
 */
struct mcuxClMac_Context
{
  const mcuxClMac_ModeDescriptor_t * pMode;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMAC_CTX_H_ */
