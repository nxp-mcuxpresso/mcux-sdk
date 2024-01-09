/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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

/** @file  mcuxClAead_Internal_Ctx.h
 *  @brief Internal structure of the context for the mcuxClAead component
 */

#ifndef MCUXCLAEAD_INTERNAL_CTX_H_
#define MCUXCLAEAD_INTERNAL_CTX_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>

#include <internal/mcuxClAead_Internal_Descriptor.h>

struct mcuxClAead_Context
{
  const mcuxClAead_ModeDescriptor_t *mode;
};

#endif /* MCUXCLAEAD_INTERNAL_CTX_H_ */
