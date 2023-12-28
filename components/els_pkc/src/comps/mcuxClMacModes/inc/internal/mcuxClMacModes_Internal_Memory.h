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

#ifndef MCUXCLMACMODES_INTERNAL_MEMORY_H_
#define MCUXCLMACMODES_INTERNAL_MEMORY_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <internal/mcuxClMacModes_Wa.h>
#include <internal/mcuxClMacModes_Internal_Types.h>
#include <internal/mcuxClMacModes_Internal_Macros.h>

#define MCUXCLMACMODES_INTERNAL_WASIZE    MCUXCLMACMODES_INTERNAL_ALIGN_SIZE_TO_CPUWORDS(sizeof(mcuxClMacModes_WorkArea_t))

#endif /* MCUXCLMACMODES_INTERNAL_MEMORY_H_ */

