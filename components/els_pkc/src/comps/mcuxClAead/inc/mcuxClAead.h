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

/** @file  mcuxClAead.h
 *  @brief Top-level include file for the @ref mcuxClAead component
 *
 *  This includes headers for all of the functionality provided by the @ref mcuxClAead component.
 *
 *  @defgroup mcuxClAead mcuxClAead
 *  @brief Hash component
 *
 *  The mcuxClAead component implements the Authenticated Encryption with Associated Data (AEAD)
 *  operations supported by CLNS.
 *
 *  An example of how to use the @ref mcuxClAead component can be found in /mcuxClAead/ex.
 *
 *  The component uses the ELS hardware. The ELS hardware has to be initialized, prior to
 *  calling any function of the @ref mcuxClAead component.
 *
 *  The @ref mcuxClAead component supports interfaces to either authenticate and encrypt or
 *  verify and decrypt a message in one shot (mcuxClAead_crypt) or to either authenticate and
 *  encrypt or verify and decrypt it in parts (mcuxClAead_init, mcuxClAead_process,
 *  mcuxClAead_process_adata and mcuxClAead_finish). In case of processing a message in parts,
 *  first an initialization has to be performed (mcuxClAead_init), followed by zero, one
 *  or multiple updates (mcuxClAead_process_adata and mcuxClAead_process), followed by a
 *  finalization or verification (mcuxClAead_finish/mcuxClAead_verify). The finalization generates
 *  the output tag and destroys the context. The verification generates and compares the output
 *  tag and destroys the context. After the finalization/verification step, no further updates
 *  are possible.
 *
 *  The targeted AEAD algorithm is selected by passing one of the offered algorithm mode
 *  descriptors (@ref mcuxClAead_Modes), which are listed in file mcuxClAead_Modes.h
 *
 * */

#ifndef MCUXCLAEAD_H_
#define MCUXCLAEAD_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClAead_Types.h>
#include <mcuxClAead_Functions.h>
#include <mcuxClAead_Constants.h>


#endif /* MCUXCLAEAD_H_ */
