/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/**
 * @file mcuxClRandomModes.h
 * @brief Top level header of mcuxClRandomModes component
 *
 * @defgroup mcuxClRandom mcuxClRandom
 * @brief component of random number generation
 */

#ifndef MCUXCLRANDOMMODES_H_
#define MCUXCLRANDOMMODES_H_

#include <mcuxClConfig.h> // Exported features flags header
#ifdef MCUXCL_FEATURE_RANDOMMODES_TESTMODE
#include <mcuxClRandomModes_Functions_TestMode.h>
#endif /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */
#include <mcuxClRandomModes_Functions_PatchMode.h>
#include <mcuxClRandomModes_MemoryConsumption.h>
#include <mcuxClRandomModes_Constants.h>

#endif /* MCUXCLRANDOMMODES_H_ */
