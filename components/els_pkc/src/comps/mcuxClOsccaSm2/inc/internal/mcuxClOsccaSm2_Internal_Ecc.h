/*--------------------------------------------------------------------------*/
/* Copyright 2018-2023 NXP                                                  */
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
 * @file  mcuxClOsccaSm2_Internal_Ecc.h
 * @brief mcuxClOsccaSm2: internal implementation of SM2 ECC function
 */


#ifndef MCUXCLOSCCASM2_INTERNAL_ECC_H_
#define MCUXCLOSCCASM2_INTERNAL_ECC_H_

#include <mcuxClOsccaSm2_Types.h>
#include <mcuxClSession_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal_Types.h>

#define     MCUXCLOSCCASM2_STATUS_COORDINATE_EQUAL                 (0x4D9AU)
#define     MCUXCLOSCCASM2_STATUS_COORDINATE_NOT_EQUAL             (0xB265U)
#define     MCUXCLOSCCASM2_STATUS_COORDINATE_INVERSE_EQUAL         (0x4DA5U)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccInit)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccInit(mcuxClSession_Handle_t session, mcuxClOsccaSm2_DomainParam_t *pParams, uint32_t stackSize, uint32_t bufferInfo);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPrepareParameters)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPrepareParameters(mcuxClOsccaSm2_DomainParam_t *pDomainParameters);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccGenerateZ)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccGenerateZ(mcuxClSession_Handle_t session, uint32_t iZ, uint32_t iTmp);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccJacPointCheck)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccJacPointCheck(uint32_t iX, uint32_t iY);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPointConvert2Affine)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointConvert2Affine(void);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccGenRandomBytes)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccGenRandomBytes(mcuxClSession_Handle_t session, uint32_t opsIndex, uint32_t len);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccImportInputPointWithInit)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccImportInputPointWithInit(uint32_t iP, uint8_t const *pP, uint32_t byteCountP);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccImportInputPointYNegNoInit(uint32_t iYneg, uint8_t const *pY, uint32_t byteCountY);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccTransAffinePoint2Jac)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccTransAffinePoint2Jac(void);


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPointCheckCoordinate)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaSm2_EccPointCheckCoordinate(void);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPointDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointDouble(void);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPointAdd)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointAdd(void);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccSecurePointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccSecurePointMult(mcuxClSession_Handle_t session, uint32_t scalarIdx);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPointMultMontgomery)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointMultMontgomery(uint32_t scalarIdx);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSm2_EccPointAddOrDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccPointAddOrDouble(void);
#endif /* MCUXCLOSCCASM2_INTERNAL_ECC_H_ */
