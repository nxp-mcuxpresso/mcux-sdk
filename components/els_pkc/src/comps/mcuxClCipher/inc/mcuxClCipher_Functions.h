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

/** @file  mcuxClCipher_Functions.h
 *  @brief Top-level API of the mcuxClCipher component */

#ifndef MCUXCLCIPHER_FUNCTIONS_H_
#define MCUXCLCIPHER_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClCipher_Types.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_Buffer.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup mcuxClAPI MCUX CL -- API
 *
 * @defgroup mcuxClCipher Cipher API
 * @brief Cipher operations.
 * @ingroup mcuxClAPI
 */


/**
 * @defgroup clCipherOneShot One-shot Cipher interfaces
 * @brief Interfaces to perform Cipher operations in one shot.
 * @ingroup mcuxClCipher
 */

/**
 * @brief One-shot encryption/decryption function
 * @api
 *
 * This function performs an encryption/decryption operation in one shot. The
 * algorithm to be used will be determined based on the mode that is provided.
 *
 * For example, to perform an AES encryption/decryption operation with a 128-bit key in
 * CBC mode on padded data, the following needs to be provided:
 *  - AES128 key
 *  - CBC mode for encryption, without padding
 *  - IV, same size as the AES block size
 *  - Plain input data, size must be a multiple of the AES block size
 *  - Output data buffer, with the same size as the input data
 *  - Output size buffer, to store the amount of written bytes
 *
 * @param      session    Handle for the current CL session.
 * @param      key        Key to be used to encrypt the data.
 * @param      mode       Cipher mode that should be used during the encryption/decryption
 *                        operation.
 * @param[in]  pIv        Pointer to the buffer that contains the IV, if needed
 *                        for the chosen @p mode, otherwise ignored.
 * @param      ivLength   Number of bytes of data in the @p pIv buffer.
 * @param[in]  pIn        Pointer to the input buffer that contains the plain
 *                        data that needs to be encrypted.
 * @param      inLength   Number of bytes of plain data in the @p pIn buffer.
 * @param[out] pOut       Pointer to the output buffer where the encrypted data
 *                        needs to be written.
 * @param[out] pOutLength Will be incremented by the number of bytes of encrypted
 *                        data that have been written to the @p pOut buffer.
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCipher_crypt)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_crypt(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClCipher_Mode_t mode,
  mcuxCl_InputBuffer_t pIv,
  uint32_t ivLength,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
);



/**
 * @defgroup clCipherMultiPart Multi-part Cipher interfaces
 * @brief Interfaces to perform Cipher operations in multiple parts.
 * @ingroup mcuxClCipher
 */

/**
 * @brief Multi-part encryption/decryption initialization function
 * @api
 *
 * This function performs the initialization for a multi part encryption/decryption
 * operation. The algorithm to be used will be determined based on the mode
 * that is provided.
 *
 * @param      session  Handle for the current CL session.
 * @param      pContext Cipher context which is used to maintain the state and
 *                      store other relevant information about the operation.
 * @param      key      Key to be used to encrypt the data.
 * @param      mode     Cipher mode that should be used during the encryption/decryption
 *                      operation.
 * @param[in]  pIv      Pointer to the buffer that contains the IV, if needed
 *                      for the chosen @p mode, otherwise ignored.
 * @param      ivLength Number of bytes of data in the @p pIv buffer.
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCipher_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_init(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClCipher_Mode_t mode,
  mcuxCl_InputBuffer_t pIv,
  uint32_t ivLength
); /* init */

/**
 * @brief Multi-part encryption/decryption processing function
 * @api
 *
 * This function performs the processing of (a part of) a data stream for an
 * encryption/decryption operation. The algorithm and key to be used will be
 * determined based on the context that is provided.
 * Data is processed in full blocks only. Remaining data is stored in the context
 * to be handled in later process or finish calls.
 *
 * @param      session    Handle for the current CL session.
 * @param      pContext   Cipher context which is used to maintain the state and
 *                        store other relevant information about the operation.
 * @param[in]  pIn        Pointer to the input buffer that contains the data that
 *                        needs to be processed.
 * @param      inLength   Number of bytes of data in the @p pIn buffer.
 * @param[out] pOut       Pointer to the output buffer where the processed data
 *                        needs to be written.
 * @param[out] pOutLength Will be incremented by the number of bytes of processed
 *                        data that have been written to the @p pOut buffer.
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCipher_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_process(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
); /* update */

/**
 * @brief Multi-part encryption/decryption finalization function
 * @api
 *
 * This function performs the finalization of an encryption or decryption
 * operation. The algorithm and key to be used will be determined based on the
 * context that is provided.
 * No new data is accepted but remaining data in the context is processed.
 *
 * @param      session    Handle for the current CL session.
 * @param      pContext   Cipher context which is used to maintain the state and
 *                        store other relevant information about the operation.
 * @param[out] pOut       Pointer to the output buffer where the processed data
 *                        needs to be written.
 * @param[out] pOutLength Will be incremented by the number of bytes of processed
 *                        data that have been written to the @p pOut buffer.
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCipher_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipher_finish(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
); /* finalize */





#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCIPHER_FUNCTIONS_H_ */
