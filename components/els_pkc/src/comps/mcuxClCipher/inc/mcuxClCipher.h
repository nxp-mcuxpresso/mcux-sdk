/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

#ifndef MCUXCLCIPHER_H_
#define MCUXCLCIPHER_H_

/** @file  mcuxClCipher.h
 *  @brief Top-level include file for the @ref mcuxClCipher component
 *
 *  This includes headers for all of the functionality provided by the @ref mcuxClCipher component.
 *
 *  @defgroup mcuxClCipher mcuxClCipher
 *  @brief Cipher component
 *
 *  The mcuxClCipher component implements the Encryption and Decryption functionality supported by CLNS.
 *  It supports Symmetric encryption algorithms.
 *
 *  An example of how to use the @ref mcuxClCipher component can be found in /mcuxClCipher/ex.
 *
 *  The component uses the ELS hardware. The ELS hardware has to be initialized, prior to
 *  calling any function of the @ref mcuxClCipher component.
 *
 *  The @ref mcuxClCipher component supports interfaces to either encrypt/decrypt a message
 *  in one shot (mcuxClCipher_crypt) or to encrypt/decrypt it in parts (mcuxClCipher_init,
 *  mcuxClCipher_process, and mcuxClCipher_finish). In case of encrypting/decrypting a message
 *  in parts, first an initialization has to be performed (mcuxClCipher_init), followed by
 *  zero, one or multiple updates (mcuxClCipher_process), followed by a finalization
 *  (mcuxClCipher_finish). The finalization generates the encrypted/decrypted output data and
 *  destroys the context. After the finalization step, no further updates are possible.
 *
 *  The targeted encryption algorithm is selected by passing one of the offered algorithm mode
 *  descriptors, which are available in the @ref mcuxClCipherModes components.
 *
 * */

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCipher_Types.h>
#include <mcuxClCipher_Functions.h>
#include <mcuxClCipher_Constants.h>
#include <mcuxClCipher_Types.h>

#endif /* MCUXCLCIPHER_H_ */
