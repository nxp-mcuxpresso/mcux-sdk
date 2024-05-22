/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClSession.h
 *  @brief Top-level include file for the mcuxClSession component
 *
 * @defgroup mcuxClSession mcuxClSession
 *
 * This component provides functions for managing a session. A session groups references to all 
 * the resources that a function to perform its operation needs into one structure. It contains 
 * references to buffers for working memory, random number generation, configuration data (e.g. 
 * for security features), etc...
 *
 * The library exposes the following functionality:
 *  <ol>
 *      <li> Initialization, cleanup and destruction
 *          <ul> <li> #mcuxClSession_init </ul>
 *          <ul> <li> #mcuxClSession_cleanup </ul>
 *          <ul> <li> #mcuxClSession_destroy </ul>
 *      <li> Configuration
 *          <ul> <li> #mcuxClSession_setRtf </ul>
 *  </ol>
 */
 
#ifndef MCUXCLSESSION_H_
#define MCUXCLSESSION_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession_Types.h>
#include <mcuxClSession_Functions.h>

#endif /* MCUXCLSESSION_H_ */
