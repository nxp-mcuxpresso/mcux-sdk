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

/** @file  mcuxClAeadModes_ELS_Algorithms.h
 *  @brief Internal exports of the algorithm descriptors for the mcuxClAeadModes component
 */

#ifndef MCUXCLAEADMODES_ELS_ALGORITHMS_H_
#define MCUXCLAEADMODES_ELS_ALGORITHMS_H_

#include <internal/mcuxClAeadModes_ELS_Types.h>

extern const mcuxClAead_algorithm_t mcuxClAead_algorithm_AES_CCM_DEC;

extern const mcuxClAead_algorithm_t mcuxClAead_algorithm_AES_CCM_ENC;

extern const mcuxClAead_algorithm_t mcuxClAead_algorithm_AES_GCM_DEC;

extern const mcuxClAead_algorithm_t mcuxClAead_algorithm_AES_GCM_ENC;


#endif /* MCUXCLAEADMODES_ELS_ALGORITHMS_H_ */

