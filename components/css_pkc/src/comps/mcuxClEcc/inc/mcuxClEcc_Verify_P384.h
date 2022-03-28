/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 * @file  mcuxClEcc_Verify_P384.h
 * @brief Header of ECDSA signature verification supporting curve P-384
 */


#ifndef MCUXCLECC_VERIFY_P384_H_
#define MCUXCLECC_VERIFY_P384_H_


#include <mcuxClEcc.h>
#include <mcuxCsslFlowProtection.h>

/**
 * @defgroup mcuxClEcc_Verify_P384 mcuxClEcc_Verify_P384
 * @brief Definitions for the ECDSA signature verification for curve P-384 of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */

/** @addtogroup MCUXCLECC_SIZE_P384_
 * mcuxClEcc size definitions for curve P-384
 * @{ */
#define MCUXCLECC_COORDINATE_SIZE_P384 0x30U ///< Byte length of coordinates of points on curve P-384
#define MCUXCLECC_SIGNATURE_SIZE_P384 0x60U  ///< Byte length of signatures generated using curve P-384
/** @} */


/** implements ECDSA signature verification, supporting curve P-384.
 * @retval #MCUXCLECC_STATUS_VERIFY_OK              if ECDSA Signature is valid;
 * @retval #MCUXCLECC_STATUS_VERIFY_NOT_OK          if ECDSA Signature is invalid;
 * @retval #MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS  if Parameter(s) is invalid;
 * @retval #MCUXCLECC_STATUS_FAULT_ATTACK           if Fault attack (unexpected behavior) is detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Verify_P384)
mcuxClEcc_Status_Protected_t mcuxClEcc_Verify_P384(
    const uint8_t * pHash,       ///< [in] pointer to hash of message (at least 48 bytes). The first 48 bytes of hash will be used.
    const uint8_t * pSignature,  ///< [in] pointer to signature R and S. R is followed by S, and each is 48-byte and in Big-endian.
    const uint8_t * pPublicKey,  ///< [in] pointer to public key. The x coordinate is followed by y coordinate, and each coordinate is 48-byte (384-bit) and in Big-endian.
    uint8_t *       pOutputR     ///< [out] pointer to memory area (48-byte) in which signature R calculated by verify function will be exported (in Big-endian) if signature is valid.
    );

/**
 * @}
 */ /* mcuxClEcc_Verify_P384 */



#endif /* MCUXCLECC_VERIFY_P384_H_ */
