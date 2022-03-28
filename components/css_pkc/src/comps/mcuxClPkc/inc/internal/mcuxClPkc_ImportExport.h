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

/**
 * @file  mcuxClPkc_ImportExport.h
 * @brief Declaration of PKC internal import/export functions of mcuxClPkc component
 */


#ifndef MCUXCLPKC_IMPORTEXPORT_H_
#define MCUXCLPKC_IMPORTEXPORT_H_

#include <stdbool.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc_Types.h>


/**********************************************************/
/* Import/export function declaration                     */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SwitchEndianness)
mcuxClPkc_Status_Protected_t mcuxClPkc_SwitchEndianness(uint32_t *ptr, uint32_t length);
/** Helper macro to call #mcuxClPkc_SwitchEndianness with flow protection. */
#define MCUXCLPKC_FP_SWITCHENDIANNESS(ptr, length)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_SwitchEndianness(ptr, length));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ImportBigEndianToPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_ImportBigEndianToPkc(uint8_t iTarget, const uint8_t * pSource, uint32_t length);
/** Helper macro to call #mcuxClPkc_ImportBigEndianToPkc with flow protection. */
#define MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(indexTarget, ptrSource, length)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_ImportBigEndianToPkc(indexTarget, ptrSource, length));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ExportBigEndianFromPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_ExportBigEndianFromPkc(uint8_t * pTarget, uint8_t iSource, uint32_t length);
/** Helper macro to call #mcuxClPkc_ExportBigEndianFromPkc with flow protection. */
#define MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(ptrTarget, indexSource, length)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_ExportBigEndianFromPkc(ptrTarget, indexSource, length));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SecureImportBigEndianToPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_SecureImportBigEndianToPkc(uint16_t iTarget_iTemp, const uint8_t * pSource, uint32_t length);
/** Helper macro to call #mcuxClPkc_SecureImportBigEndianToPkc with flow protection. */
#define MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC(indexTarget, ptrSource, indexTemp, length)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_SecureImportBigEndianToPkc(MCUXCLPKC_PACKARGS2(indexTarget, indexTemp), ptrSource, length));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_SecureExportBigEndianFromPkc)
mcuxClPkc_Status_Protected_t mcuxClPkc_SecureExportBigEndianFromPkc(uint8_t * pTarget, uint16_t iSource_iTemp, uint32_t length);
/** Helper macro to call #mcuxClPkc_SecureExportBigEndianFromPkc with flow protection. */
#define MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC(ptrTarget, indexSource, indexTemp, length)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_SecureExportBigEndianFromPkc(ptrTarget, MCUXCLPKC_PACKARGS2(indexSource, indexTemp), length));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

#endif /* MCUXCLPKC_IMPORTEXPORT_H_ */
