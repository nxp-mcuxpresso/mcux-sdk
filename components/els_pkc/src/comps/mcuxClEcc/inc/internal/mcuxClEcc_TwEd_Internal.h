/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClEcc_TwEd_Internal.h
 * @brief internal header of mcuxClEcc Twisted Edward's functionalities
 */


#ifndef MCUXCLECC_TWED_INTERNAL_H_
#define MCUXCLECC_TWED_INTERNAL_H_

#include <stdint.h>

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClMemory.h>
#include <mcuxClPkc.h>
#include <mcuxClHash_Types.h>

#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_PkcWaLayout.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Internal return codes of mcuxClEcc_TwEd                 */
/**********************************************************/

// None


/**********************************************************/
/* Internal mcuxClEcc_TwEd function defines                */
/**********************************************************/

#define MCUXCLECC_TWED_FIXSCALARMULT_DIGITSIZE (4u)
#define MCUXCLECC_TWED_FIXSCALARMULT_DIGITMASK (0xFu)
#define MCUXCLECC_TWED_FIXSCALARMULT_NOOFPRECPOINTS (8u)


/**********************************************************/
/* Internal mcuxClEcc_TwEd functions                       */
/**********************************************************/

/**
 * Declaration of function to perform plain (not protected against side-channel attacks) scalar multiplication with variable input point
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PlainVarScalarMult, mcuxClEcc_ScalarMultFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainVarScalarMult(
    mcuxClSession_Handle_t pSession,                          ///<  [in]  pSession            Handle for the current CL session
    mcuxClEcc_CommonDomainParams_t *pDomainParams,            ///<  [in]  pDomainParams       Pointer to ECC common domain parameters structure
    uint8_t iScalar,                                         ///<  [in]  iScalar             Pointer table index of secret scalar lambda
    uint32_t scalarBitLength,                                ///<  [in]  scalarBitLength     Bit length of the scalar
    uint32_t options                                         ///<  [in]  options             Parameter to pass options
 );

/**
 * Declaration of the mixed point addition function
 * and structure containing the function pointer and its associated flow protection ID.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClEcc_TwEd_MixedPointAddFunction_t,
    typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) (*mcuxClEcc_TwEd_MixedPointAddFunction_t)(void));
typedef struct
{
    mcuxClEcc_TwEd_MixedPointAddFunction_t pMixedPointAddFct;   ///< mixed point addition function
    uint32_t mixedPointAddFct_FP_FuncId;                       ///< FP ID of the function
} mcuxClEcc_TwEd_MixedPointAddFunction_FP_t;

/**
 * Declaration of the point doubling function
 * and structure containing the function pointer and its associated flow protection ID.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClEcc_TwEd_PointDoubleFunction_t,
    typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) (*mcuxClEcc_TwEd_PointDoubleFunction_t)(void));
typedef struct
{
    mcuxClEcc_TwEd_PointDoubleFunction_t pPointDoubleFct;   ///< point doubling function
    uint32_t pointDoubleFct_FP_FuncId;                     ///< FP ID of the function
} mcuxClEcc_TwEd_PointDoubleFunction_FP_t;

/**
 * Declaration of the comb method pointer selection function
 * and structure containing the function pointer and its associated flow protection ID.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClEcc_TwEd_PtrSelectFunction_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) (*mcuxClEcc_TwEd_PtrSelectFunction_t)(
    mcuxClSession_Handle_t pSession, ///<  [in]  pSession            Handle for the current CL session
    uint32_t scalarWord,            ///<  [in]  scalarWord          CPU word containing the scalar bits to be processed
    uint8_t scalarOffset            ///<  [in]  scalarDigitOffset   Offset in scalarWord of scalar bit(s) to be processed
));
typedef struct
{
    mcuxClEcc_TwEd_PtrSelectFunction_t pPtrSelectFct; ///< Pointer selection function
    uint32_t ptrSelectFct_FP_FuncId;                 ///< FP ID of the function
} mcuxClEcc_TwEd_PtrSelectFunction_FP_t;

/**
 * Declaration of the plain (not protected against side-channel attacks) comb method pointer selection function
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PlainPtrSelectComb, mcuxClEcc_TwEd_PtrSelectFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainPtrSelectComb(
    mcuxClSession_Handle_t pSession, ///<  [in]  pSession            Handle for the current CL session
    uint32_t scalarWord,            ///<  [in]  scalarWord          CPU word containing the digit (i3i2i1i0)_2
    uint8_t scalarDigitOffset       ///<  [in]  scalarDigitOffset   Bit offset in scalarWord of the digit (i3i2i1i0)_2
);

/**
 * Declaration of the plain (not protected against side-channel attacks) Montgomery ladder pointer selection function
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PlainPtrSelectML, mcuxClEcc_TwEd_PtrSelectFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PlainPtrSelectML(
    mcuxClSession_Handle_t pSession, ///<  [in]  pSession            Handle for the current CL session
    uint32_t scalarWord,            ///<  [in]  scalarWord          CPU word containing the current scalar bit b
    uint8_t scalarBitOffset         ///<  [in]  scalarBitOffset     Offset in scalarWord of scalar bit b
);

/**
 * Declaration of function to import, convert and validate pre-computed points
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_PrecPointImportAndValidate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_PrecPointImportAndValidate(
    mcuxClSession_Handle_t pSession, ///<  [in]  pSession            Handle for the current CL session
    uint8_t iDst,                   ///<  [in]  iDst                Pointer table index of buffer to which the x-coordinate shall be copied
    uint8_t *pSrc,                  ///<  [in]  pSrc                Pointer to the pre-computed point x-coordinate
    uint16_t byteLenP               ///<  [in]  byteLenP            Byte length of P
);

/**
 * Declaration of function to perform scalar multiplication with the base point
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_FixScalarMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_FixScalarMult(
    mcuxClSession_Handle_t pSession,                          			///<  [in]  pSession           Handle for the current CL session
    mcuxClEcc_CommonDomainParams_t *pDomainParams,            			///<  [in]  pDomainParams      Pointer to ECC common domain parameters structure
    uint8_t iScalar,                                         			///<  [in]  iScalar            Pointer table index of secret scalar lambda
    uint32_t scalarBitLength,                                			///<  [in]  scalarBitLength    Bit length of the scalar; must be a multiple of 4
	const mcuxClEcc_TwEd_MixedPointAddFunction_FP_t *pMixedPointAddFctFP,///<  [in]  pMixedPointAddFct  Curve dependent function to perform mixed point addition on twisted Edwards curve
	const mcuxClEcc_TwEd_PointDoubleFunction_FP_t *pPointDoubleFctFP,    ///<  [in]  pPointDoubleFct    Curve dependent function to perform point doubling on twisted Edwards curve
	const mcuxClEcc_TwEd_PtrSelectFunction_FP_t *pPtrSelectFctFP         ///<  [in]  pPtrSelectFct      Function to select pre-computed point to be added
 );


/**
 * Declaration of function to perform scalar multiplication with variable input point
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_TwEd_VarScalarMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_TwEd_VarScalarMult(
    mcuxClSession_Handle_t pSession,                                ///<  [in]  pSession           Handle for the current CL session
    mcuxClEcc_CommonDomainParams_t *pDomainParams,                  ///<  [in]  pDomainParams      Pointer to ECC common domain parameters structure
    uint8_t iScalar,                                               ///<  [in]  iScalar            Pointer table index of secret scalar lambda
    uint32_t scalarBitLength,                                      ///<  [in]  scalarBitLength    Bit length of the scalar
    uint32_t options,                                              ///<  [in]  options            Parameter to pass options
    const mcuxClEcc_TwEd_PtrSelectFunction_FP_t *pPtrSelectFctFP    ///<  [in]  pPtrSelectFct      Function to select accumulated ladder points
 );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_TWED_INTERNAL_H_ */
