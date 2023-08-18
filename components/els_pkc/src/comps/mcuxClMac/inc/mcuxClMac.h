/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022 NXP                                                 */
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
 * @file  mcuxClMac.h
 * @brief Top-level include file for the mcuxClMac component
 *
 * @defgroup mcuxClMac mcuxClMac
 * @brief Message Authentication Code (MAC) component
 * @ingroup mcuxClAPI
 *
 * The mcuxClMac component implements Message Authentication Code (MAC) calculation,
 * based on either HMAC or CMAC.
 *
 * An example of how to use the @ref mcuxClMac component can be found in /mcuxClMac/ex.
 *
 * The MAC can either be computed in one shot, using the mcuxClMac_compute function,
 * or the input can be split into multiple parts. In that case, an initialization
 * has to be performed first by calling the mcuxClMac_init function. Now zero, one,
 * or more messages can be added for authentication by calling mcuxClMac_process.
 * Finally, the MAC is generated when the mcuxClMac_finish function is called.
 *
 * The mode to be used, HMAC or CMAC, is defined by passing the corresponding mode
 * descriptor (mcuxClMac_Mode_t) to mcuxClMac_compute or mcuxClMac_init.
 *
 */

#ifndef MCUXCLMAC_H_
#define MCUXCLMAC_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <mcuxClMac_Functions.h>
#include <mcuxClMac_Constants.h>

#endif /* MCUXCLMAC_H_ */
