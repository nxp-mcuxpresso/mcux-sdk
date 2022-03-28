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

/**
 * @file  mcuxClKey_Protections.h
 * @brief Provide API of the mcuxClKey_Protection functions
 */

#ifndef MCUXCLKEY__PROTECTIONS_H_
#define MCUXCLKEY__PROTECTIONS_H_


/**********************************************
 * CONSTANTS
 **********************************************/
/* None */

/**********************************************
 * TYPEDEFS
 **********************************************/
/* None */

/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * @brief Protection function pointer for empty key handling functions.
 * @ingroup mcuxClKey_Functions
 *
 * See #mcuxClKey_Protection for the structure definition.
 * Initializing #mcuxClKey_Handle_t with this pointer (via #mcuxClKey_init) to use empty key handling.
 * <dl>
 * <dt>Parameters defined by protection function</dt>
 * <dd><dl>
 *   <dt>#mcuxClKey_init</dt>
 *   <dd><dl>
 *     <dt>srcKeyData</dt>
 *     <dd>RFU.</dd>
 *     <dt>srcAuxData</dt>
 *     <dd>RFU.</dd>
 *     <dt>srcAuxSlot</dt>
 *     <dd>RFU.</dd>
 *   </dl></dd>
 *   <dt>#mcuxClKey_loadCopro</dt>
 *   <dd>This function shall not be used by this protection mechanism.</dd>
 *   <dt>#mcuxClKey_loadMemory</dt>
 *   <dd><dl>
 *     <dt>dstData</dt>
 *     <dd>Pointer to destination key memory. Must not be NULL.</dd>
 *   </dl></dd>
 * </dl></dd>
 * </dl>
 */
extern const mcuxClKey_Protection_t mcuxClKey_protection_none;

/**
 * @brief Protection function pointer for CSS internal CKDF based key generation.
 * @ingroup mcuxClKey_Functions
 *
 * See #mcuxClKey_Protection for the structure definition.
 * Initializing #mcuxClKey_Handle_t with this pointer (via #mcuxClKey_init) to use CSS internal CKDF based key generation.
 * <dl>
 * <dt>Parameters defined by protection function</dt>
 * <dd><dl>
 *   <dt>#mcuxClKey_init</dt>
 *   <dd><dl>
 *     <dt>srcKeyData</dt>
 *     <dd>RFU.</dd>
 *     <dt>srcAuxData</dt>
 *     <dd>Pointer to key derivation data.</dd>
 *     <dt>srcAuxSlot</dt>
 *     <dd>Master key slot.</dd>
 *   </dl></dd>
 *   <dt>#mcuxClKey_loadCopro</dt>
 *   <dd><dl>
 *     <dt>dstSlot</dt>
 *     <dd>Destination key slot of key.</dd>
 *   </dl></dd>
 *   <dt>#mcuxClKey_loadMemory</dt>
 *   <dd>This function shall not be used by this protection mechanism.</dd>
 * </dl></dd>
 * </dl>
 */
extern const mcuxClKey_Protection_t mcuxClKey_protection_ckdf;

#endif /* MCUXCLKEY__PROTECTIONS_H_ */
