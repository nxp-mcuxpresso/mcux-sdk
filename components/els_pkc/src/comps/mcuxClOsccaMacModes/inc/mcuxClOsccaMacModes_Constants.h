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

/** @file  mcuxClOsccaMacModes_Constants.h
 *  @brief header for mac constants.
 */

#ifndef MCUXCLOSCCAMACMODES_CONSTANTS_H_
#define MCUXCLOSCCAMACMODES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header


/**********************************************
 * CONSTANTS
 **********************************************/
/* Output sizes */
#ifdef MCUXCL_FEATURE_MACMODES_CMAC_SM4
#define MCUXCLOSCCASM4_CMAC_OUTPUT_SIZE    16u
#endif /* MCUXCL_FEATURE_MACMODES_CMAC_SM4 */

#ifdef MCUXCL_FEATURE_MACMODES_CBCMAC_SM4
#define MCUXCLOSCCASM4_CBCMAC_OUTPUT_SIZE  16u
#endif /* MCUXCL_FEATURE_MACMODES_CBCMAC_SM4 */


#endif /* MCUXCLOSCCAMACMODES_CONSTANTS_H_ */
