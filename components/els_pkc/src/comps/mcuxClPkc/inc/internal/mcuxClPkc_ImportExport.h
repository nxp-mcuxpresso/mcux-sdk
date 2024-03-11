/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClPkc_ImportExport.h
 * @brief Declaration of PKC internal import/export functions of mcuxClPkc component
 */


#ifndef MCUXCLPKC_IMPORTEXPORT_H_
#define MCUXCLPKC_IMPORTEXPORT_H_


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClSession.h>
#include <mcuxClMemory.h>

#include <mcuxClPkc_Types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************/
/* Import/export function declaration                     */
/**********************************************************/

/**
 * \brief Function to switch the endianness of the data in a buffer
 *
 * This function switches the endianness of a data buffer of a specified length.
 *
 * \param[in/out]  ptr     pointer to data buffer of which endianness is switched
 * \param[in]      length  length of data buffer pointed to by ptr
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p ptr</dt>
 *       <dd>pointer shall be CPU word aligned.</dd>
 *     <dt>@p length</dt>
 *       <dd>if length is not a multiple of CPU wordsize, this function will:
 *       <br>cause unaligned word access and sometimes byte access, on platform supporting unaligned access;
 *       <br>switch endianness byte-wisely, on platform not supporting unaligned access.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SwitchEndianness)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_SwitchEndianness(uint32_t *ptr, uint32_t length);

/** Helper macro to call #mcuxClPkc_SwitchEndianness with flow protection. */
#define MCUXCLPKC_FP_SWITCHENDIANNESS(ptr, length) \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_SwitchEndianness(ptr, length))

/**
 * \brief Function to import an operand, which is provided in big-endian order
 *
 * This function imports an integer stored as a big-endian octet string with specified length
 * and stores it as an integer in PKC workarea according PKC specification.
 *
 * \param[out]  iTarget  index of PKC operand, where the imported integer will be stored
 * \param[in]   pSource  address of the octet string to be imported
 * \param[in]   length   length of the octet string to be imported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iTarget</dt>
 *       <dd>index of the PKC operand, size = PKC PS1LEN.
 *       <br>The offset (UPTRT[iTarget]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ImportBigEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ImportBigEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_ImportBigEndianToPkc with flow protection. */
#define MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(iTarget, pSource, length) \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_ImportBigEndianToPkc(iTarget, pSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)
#define MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC_BUFFEROFFSET(functionID, iTarget, pBufSource, offset, length) \
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(iTarget, & ((const uint8_t *) (pBufSource))[offset], length)
#define MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFER  MCUXCLPKC_FP_CALLED_IMPORTBIGENDIANTOPKC_BUFFEROFFSET
#define MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC_BUFFER(functionID, iTarget, pBufSource, length) \
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC_BUFFEROFFSET(functionID, iTarget, pBufSource, 0u, length)


/**
 * \brief Function to import an operand, which is provided in little-endian order
 *
 * This function imports an integer stored as a little-endian octet string with specified length
 * and stores it as an integer in PKC workarea according PKC specification.
 *
 * \param[out]  iTarget  index of PKC operand, where the imported integer will be stored
 * \param[in]   pSource  address of the octet string to be imported
 * \param[in]   length   length of the octet string to be imported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iTarget</dt>
 *       <dd>index of the PKC operand, size = PKC PS1LEN.</dd>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_ImportLittleEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ImportLittleEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_ImportLittleEndianToPkc with flow protection. */
#define MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(iTarget, pSource, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_ImportLittleEndianToPkc(iTarget, pSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc)
#define MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET(functionID, iTarget, pBufSource, offset, length) \
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(iTarget, & ((const uint8_t *) (pBufSource))[offset], length)
#define MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFER  MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET
#define MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC_BUFFER(functionID, iTarget, pBufSource, length) \
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET(functionID, iTarget, pBufSource, 0u, length)


/**
 * \brief Function to export an operand to a big-endian integer
 *
 * This function exports a PKC integer in PKC workarea and stores it as a big-endian octet string
 * in a buffer specified by the given address and length.
 *
 * \param[out]  pTarget  address of operand, where the exported integer will be stored
 * \param[in]   iSource  index of PKC operand to be exported
 * \param[in]   length   length of the octet string to be exported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iSource</dt>
 *       <dd>index of the PKC operand, size = PKC PS1LEN.
 *       <br>The offset (UPTRT[iSource]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br>PKC integer stored in source buffer will be destroyed after calling this function.</dd>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ExportBigEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ExportBigEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_ExportBigEndianFromPkc with flow protection. */
#define MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pTarget, iSource, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_ExportBigEndianFromPkc(pTarget, iSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_EXPORTBIGENDIANFROMPKC_BUFFEROFFSET  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc)
#define MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC_BUFFEROFFSET(functionID, pBufTarget, iSource, offset, length) \
    MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(& ((uint8_t *) (pBufTarget))[offset], iSource, length)
#define MCUXCLPKC_FP_CALLED_EXPORTBIGENDIANFROMPKC_BUFFER  MCUXCLPKC_FP_CALLED_EXPORTBIGENDIANFROMPKC_BUFFEROFFSET
#define MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC_BUFFER(functionID, pBufTarget, iSource, length) \
    MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC_BUFFEROFFSET(functionID, pBufTarget, iSource, 0u, length)


/**
 * \brief Function to export an operand to a little-endian integer
 *
 * This function exports a PKC integer in PKC workarea and stores it as a little-endian octet string
 * in a buffer specified by the given address and length.
 *
 * \param[out]  pTarget  address of operand, where the exported integer will be stored
 * \param[in]   iSource  index of PKC operand to be exported
 * \param[in]   length   length of the octet string to be exported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iSource</dt>
 *       <dd>index of the PKC operand, size = PKC PS1LEN.</dd>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ExportLittleEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_ExportLittleEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_ExportLittleEndianFromPkc with flow protection. */
#define MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pTarget, iSource, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_ExportLittleEndianFromPkc(pTarget, iSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_EXPORTLITTLEENDIANFROMPKC_BUFFEROFFSET  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc)
#define MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC_BUFFEROFFSET(functionID, pBufTarget, iSource, offset, length) \
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(& ((uint8_t *) (pBufTarget))[offset], iSource, length)
#define MCUXCLPKC_FP_CALLED_EXPORTLITTLEENDIANFROMPKC_BUFFER  MCUXCLPKC_FP_CALLED_EXPORTLITTLEENDIANFROMPKC_BUFFEROFFSET
#define MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC_BUFFER(functionID, pBufTarget, iSource, length) \
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC_BUFFEROFFSET(functionID, pBufTarget, iSource, 0u, length)


/**
 * \brief Function to securely import an operand, which is provided in big-endian order
 *
 * This function imports an integer stored as a big-endian octet string with specified length
 * and stores it as an integer in PKC workarea according PKC specification, in a secure manner.
 *
 * \param[in]   pSession       handle for the current CL session.
 * \param[out]  iTarget_iTemp  indices of PKC operands (Target and Temp)
 * \param[in]   pSource        address of the octet string to be imported
 * \param[in]   length         length of the octet string to be imported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *      <dt>pSession:</dt>
 *       <dd>The session pointed to by pSession has to be initialized prior to a call to this function.</dd>
 *     <dt>@p iTarget_iTemp</dt>
 *       <dd><code>iTemp</code> (bits 0~7): index of temporary buffer (PKC operand), size = PKC PS1LEN.
 *       <br>The offset (UPTRT[iTemp]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br><code>iTarget</code> (bits 8~15): index of Target (PKC operand), size = PKC PS1LEN,
 *           where the imported integer will be stored.
 *       <br>The offset (UPTRT[iTarget]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClPkc_SecureImportBigEndianToPkc operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t))
 * @retval #MCUXCLPKC_STATUS_OK     The function executed successfully
 * @retval #MCUXCLPKC_STATUS_NOK    The function execution failed
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SecureImportBigEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureImportBigEndianToPkc(mcuxClSession_Handle_t pSession, uint16_t iTarget_iTemp, const uint8_t * pSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_SecureImportBigEndianToPkc with flow protection. */
#define MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC(status, pSession, iTarget, iTemp, pSource, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL(status, mcuxClPkc_SecureImportBigEndianToPkc(pSession, MCUXCLPKC_PACKARGS2(iTarget, iTemp), pSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_SECUREIMPORTBIGENDIANTOPKC_BUFFER  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc)
#define MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC_BUFFER(functionID, status, pSession, iTarget, iTemp, pBufSource, length) \
    MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC(status, pSession, iTarget, iTemp, pBufSource, length)


/**
 * \brief Function to securely import an operand, which is provided in little-endian order
 *
 * This function imports an integer stored as a little-endian octet string with specified length
 * and stores it as an integer in PKC workarea according PKC specification, in a secure manner.
 *
 * \param[out]  iTarget  index of PKC operand, where the imported integer will be stored
 * \param[in]   pSource  address of the octet string to be imported
 * \param[in]   length   length of the octet string to be imported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClPkc_SecureImportLittleEndianToPkc operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t))
 * @retval #MCUXCLPKC_STATUS_OK     The function executed successfully
 * @retval #MCUXCLPKC_STATUS_NOK    The function execution failed
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SecureImportLittleEndianToPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureImportLittleEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_SecureImportLittleEndianToPkc with flow protection. */
#define MCUXCLPKC_FP_SECUREIMPORTLITTLEENDIANTOPKC(status, iTarget,  pSource, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL(status, mcuxClPkc_SecureImportLittleEndianToPkc(iTarget,  pSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_SECUREIMPORTLITTLEENDIANTOPKC_BUFFER  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportLittleEndianToPkc)
#define MCUXCLPKC_FP_SECUREIMPORTLITTLEENDIANTOPKC_BUFFER(functionID, status, iTarget,  pBufSource, length) \
    MCUXCLPKC_FP_SECUREIMPORTLITTLEENDIANTOPKC(status, iTarget,  pBufSource, length)


/**
 * \brief Function to securely export an operand to a big-endian integer
 *
 * This function exports a PKC integer in PKC workarea and stores it as a big-endian octet string
 * in a buffer specified by the given address and length, in a secure manner.
 *
 * \param[in]   pSession       handle for the current CL session.
 * \param[out]  pTarget        address of operand, where the exported integer will be stored
 * \param[in]   iSource_iTemp  indices of PKC operands (Source and Temp)
 * \param[in]   length         length of the octet string to be exported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>pSession:</dt>
 *       <dd>The session pointed to by pSession has to be initialized prior to a call to this function.</dd>
 *     <dt>@p iSource_iTemp</dt>
 *       <dd><code>iTemp</code> (bits 0~7): index of temporary buffer (PKC operand), size = PKC PS1LEN.
 *       <br>The offset (UPTRT[iTemp]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *       <br><code>iSource</code> (bits 8~15): index of Source (PKC operand) to be exported, size = PKC PS1LEN.
 *       <br>The offset (UPTRT[iSource]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *       <br>PKC integer stored in source buffer will be destroyed after calling this function,
 *           but it is not cleared and is still sensitive.</dd>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.</dd>
 *   </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClPkc_SecureExportBigEndianFromPkc operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t))
 * @retval #MCUXCLPKC_STATUS_OK     The function executed successfully
 * @retval #MCUXCLPKC_STATUS_NOK    The function execution failed
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SecureExportBigEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureExportBigEndianFromPkc(mcuxClSession_Handle_t pSession, uint8_t * pTarget, uint16_t iSource_iTemp, uint32_t length);

/** Helper macro to call #mcuxClPkc_SecureExportBigEndianFromPkc with flow protection. */
#define MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC(status, pSession, pTarget, iSource, iTemp, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL(status, mcuxClPkc_SecureExportBigEndianFromPkc(pSession, pTarget, MCUXCLPKC_PACKARGS2(iSource, iTemp), length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_SECUREEXPORTBIGENDIANFROMPKC_BUFFEROFFSET  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc)
#define MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC_BUFFEROFFSET(functionID, status, pSession, pBufTarget, iSource, iTemp, offset, length) \
    MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC(status, pSession, & ((uint8_t *) (pBufTarget))[offset], iSource, iTemp, length)
#define MCUXCLPKC_FP_CALLED_SECUREEXPORTBIGENDIANFROMPKC_BUFFER  MCUXCLPKC_FP_CALLED_SECUREEXPORTBIGENDIANFROMPKC_BUFFEROFFSET
#define MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC_BUFFER(functionID, status, pSession, pBufTarget, iSource, iTemp, length) \
    MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC_BUFFEROFFSET(functionID, status, pSession, pBufTarget, iSource, iTemp, 0u, length)


/**
 * \brief Function to securely export an operand to a little-endian integer
 *
 * This function exports a PKC integer in PKC workarea and stores it as a little-endian octet string
 * in a buffer specified by the given address and length, in a secure manner.
 *
 * \param[out]  pTarget  address of operand, where the exported integer will be stored
 * \param[in]   iSource  index of PKC operand to be exported
 * \param[in]   length   length of the octet string to be exported
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p length</dt>
 *       <dd>it shall be equal to or smaller than PKC PS1LEN.
 *   </dl></dd>
 * </dl>
 *
 * @return Status of the mcuxClPkc_SecureExportLittleEndianFromPkc operation (see @ref MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t))
 * @retval #MCUXCLPKC_STATUS_OK     The function executed successfully
 * @retval #MCUXCLPKC_STATUS_NOK    The function execution failed
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SecureExportLittleEndianFromPkc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_SecureExportLittleEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length);

/** Helper macro to call #mcuxClPkc_SecureExportLittleEndianFromPkc with flow protection. */
#define MCUXCLPKC_FP_SECUREEXPORTLITTLEENDIANFROMPKC(status, pTarget, iSource, length)  \
    MCUX_CSSL_FP_FUNCTION_CALL(status, mcuxClPkc_SecureExportLittleEndianFromPkc(pTarget, iSource, length))

/** Helper macros to use the correct buffer implementation */
#define MCUXCLPKC_FP_CALLED_SECUREEXPORTLITTLEENDIANFROMPKC_BUFFER  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportLittleEndianFromPkc)
#define MCUXCLPKC_FP_SECUREEXPORTLITTLEENDIANFROMPKC_BUFFER(functionID, status, pBufTarget, iSource, length) \
    MCUXCLPKC_FP_SECUREEXPORTLITTLEENDIANFROMPKC(status, pBufTarget, iSource, length)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPKC_IMPORTEXPORT_H_ */
