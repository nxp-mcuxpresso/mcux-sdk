/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

#ifndef MCUXCLMACMODES_COMMON_MEMORY_H_
#define MCUXCLMACMODES_COMMON_MEMORY_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <internal/mcuxClMacModes_Common_Wa.h>
#include <internal/mcuxClMacModes_Common_Types.h>
#include <mcuxClCore_Macros.h>

#define MCUXCLMACMODES_INTERNAL_WASIZE    MCUXCLCORE_ALIGN_TO_CPU_WORDSIZE(sizeof(mcuxClMacModes_WorkArea_t))

#endif /* MCUXCLMACMODES_COMMON_MEMORY_H_ */

