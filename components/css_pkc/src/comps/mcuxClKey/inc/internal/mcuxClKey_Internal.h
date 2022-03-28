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
 * @file  mcuxClKey_Internal.h
 * @brief Provide macros of the mcuxClKey component which are for crypto library
 *        internal use only
 */

#ifndef MCUXCLKEY_INTERNAL_H_
#define MCUXCLKEY_INTERNAL_H_

/**********************************************
 * CONSTANTS
 **********************************************/

/* Convenience macros for internal use only */
/*!
  \def MCUXCLKEY_GET_KEYSIZE(key)
  Returns the keysize of key handle \a key.
*/
#define MCUXCLKEY_GET_KEYSIZE(key) ((key)->type.size)

/*!
  \def MCUXCLKEY_GET_ALGOID(key)
  Returns the algorithm id of key handle \a key.
*/
#define MCUXCLKEY_GET_ALGOID(key)  ((key)->type.algoId & MCUXCLKEY_ALGO_ID_ALGO_MASK)

/*!
  \def MCUXCLKEY_GET_KEYUSAGE(key)
  Returns the usage (public/private/symmetric) of key handle \a key.
*/
#define MCUXCLKEY_GET_KEYUSAGE(key)  ((key)->type.algoId & MCUXCLKEY_ALGO_ID_USAGE_MASK)

/*!
  \def MCUXCLKEY_GET_KEYSLOT(key)
  Returns the destination key slot of key handle \a key.
*/
#define MCUXCLKEY_GET_KEYSLOT(key) ((key)->dstKey.slot)

/*!
  \def MCUXCLKEY_GET_KEYDATA(key)
  Returns a pointer to the destination memory buffer of key handle \a key.
*/
#define MCUXCLKEY_GET_KEYDATA(key) ((key)->dstKey.pData)

/*!
  \def MCUXCLKEY_GET_LOADLOCATION(key)
  Returns the location type of the loaded key of key handle \a key.
*/
#define MCUXCLKEY_GET_KEYLOADLOCATION(key) ((key)->dstKey.loadLocation)

/**********************************************
 * TYPEDEFS
 **********************************************/
/* None */


/**********************************************
 * INTERNAL FUNCTIONS
 **********************************************/
/*! None  */

#endif /* MCUXCLKEY_INTERNAL_H_ */
