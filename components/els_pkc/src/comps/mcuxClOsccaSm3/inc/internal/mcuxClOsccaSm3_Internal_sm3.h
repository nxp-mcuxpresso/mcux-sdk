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

/** @file  mcuxClOsccaSm3_Internal_sm3.h
 *  @brief Internal definitions and declarations of the *INTERNAL* layer dedicated to OSCCA SM3
 */

#ifndef MCUXCLOSCCASM3_INTERNAL_SM3_H_
#define MCUXCLOSCCASM3_INTERNAL_SM3_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>

/**********************************************************
 * Type declarations
 **********************************************************/
/** \brief Definition of HW SM3 message size for the mcuxClOscca_SM3_*_Sgi function in bytes */
#define MCUXCLOSCCASM3_SGI_LOOP_SIZE                             ( 8U )

#endif /* MCUXCLOSCCASM3_INTERNAL_SM3_H_ */
