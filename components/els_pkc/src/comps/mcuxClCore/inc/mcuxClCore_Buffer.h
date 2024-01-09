/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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

#ifndef MCUXCLCORE_BUFFER_H_
#define MCUXCLCORE_BUFFER_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>

/**
 * \addtogroup mcuxClAPI MCUX CL -- API
 *
 * \addtogroup mcuxClCore Core API
 * \brief Essential types and functionality.
 * \ingroup mcuxClAPI
 */

/**
 * \defgroup clCoreTypes Core type definitions
 * \brief Types used by basically all operations.
 * \ingroup mcuxClCore
 */


/**
 * \brief Input buffer type
 * \ingroup clCoreTypes
 *
 * This type provides a pointer to the memory location that should be used to
 * read input data from.
 */
typedef const uint8_t * const mcuxCl_InputBuffer_t;

/**
 * \brief Generic buffer type
 * \ingroup clCoreTypes
 *
 * This type provides a pointer to the memory location that can be used for
 * both reading input data and writing output data.
 */
typedef uint8_t * const mcuxCl_Buffer_t;


#endif /* MCUXCLCORE_BUFFER_H_ */
