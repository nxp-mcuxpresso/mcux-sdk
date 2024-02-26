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

#ifndef MCUXCLMACMODES_WA_H_
#define MCUXCLMACMODES_WA_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <internal/mcuxClMacModes_Internal_Constants.h>
#include <mcuxClAes.h>
#include <internal/mcuxClAes_Wa.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mcuxClMacModes_WorkArea
{
  uint32_t paddingBuff[MCUXCLAES_BLOCK_SIZE_IN_WORDS];       /* Buffer for padding */
} mcuxClMacModes_WorkArea_t;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMACMODES_WA_H_ */
