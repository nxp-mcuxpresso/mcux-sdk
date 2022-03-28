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
 * @file  mcuxClEcc_Mont_Internal.h
 * @brief internal header of mcuxClEcc MontDh functionalities
 */

#ifndef MCUXCLECC_MONT_INTERNAL_H_
#define MCUXCLECC_MONT_INTERNAL_H_

#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClPkc.h>

#include <internal/mcuxClPkc_FupMacros.h>

#include <mcuxClEcc_Internal_SetupEnvironment_FUP.h>
#include <mcuxClEcc_Mont_MontDhX_FUP.h>
#include <mcuxClEcc_Internal_SecureScalarMult_XZMontLadder_FUP.h>

#include <mcuxClEcc.h>

#define ECC_P    0x00u
#define ECC_N    0x01u
#define ECC_V0   0x02u
#define ECC_V1   0x03u
#define ECC_V2   0x04u
#define ECC_V3   0x05u
#define ECC_V4   0x06u
#define ECC_V5   0x07u
#define ECC_V6   0x08u
#define ECC_V7   0x09u
#define ECC_V8   0x0Au
#define ECC_V9   0x0Bu
#define ECC_VA   0x0Cu
#define ECC_VB   0x0Du
#define ECC_VC   0x0Eu
#define ECC_VD   0x0Fu

#define ECC_PS     0x10u
#define ECC_NS     0x11u
#define ECC_CP0    0x12u
#define ECC_CP1    0x13u
#define ECC_PFULL  0x14u
#define ECC_NFULL  0x15u
#define ECC_PQSQR  0x16u
#define ECC_NQSQR  0x17u

#define ECC_S0  0x18u
#define ECC_T0  0x19u
#define ECC_S1  0x1Au
#define ECC_T1  0x1Bu
#define ECC_S2  0x1Cu
#define ECC_T2  0x1Du
#define ECC_S3  0x1Eu
#define ECC_T3  0x1Fu

#define ECC_COORD0  0x20u
#define ECC_COORD1  0x21u
#define ECC_COORD2  0x22u
#define ECC_COORD3  0x23u
#define ECC_COORD4  0x24u
#define ECC_COORD5  0x25u
#define ECC_COORD6  0x26u
#define ECC_COORD7  0x27u
#define ECC_COORD8  0x28u
#define ECC_COORD9  0x29u
#define ECC_COORDA  0x2Au
#define ECC_COORDB  0x2Bu

#define ECC_NO_OF_VIRTUALS  ECC_PS

#define MONT_V0   ECC_V0
#define MONT_V1   ECC_V1
#define MONT_V2   ECC_V2
#define MONT_V3   ECC_V3
#define MONT_V4   ECC_V4
#define MONT_V5   ECC_V5
#define MONT_V6   ECC_V6
#define MONT_V7   ECC_V7
#define MONT_V8   ECC_V8
#define MONT_V9   ECC_V9
#define MONT_VX1  ECC_VA
#define MONT_VZ1  ECC_VB
#define MONT_VX2  ECC_VC
#define MONT_VZ2  ECC_VD
#define MONT_X0   ECC_COORD0
#define MONT_Z0   ECC_COORD1
#define MONT_X1   ECC_COORD2
#define MONT_Z1   ECC_COORD3
#define MONT_X2   ECC_COORD4
#define MONT_Z2   ECC_COORD5

#define MCUXCLECC_INTSTATUS_POINTMULT_NEUTRAL_POINT ((mcuxClEcc_Status_t) 0x55AAD22Du)

typedef struct
{
  uint32_t wordNumCpuWa;
  uint32_t wordNumPkcWa;
  mcuxClPkc_State_t pkcStateBackup;
  uint32_t pOperands32[];
} mcuxClEcc_CpuWa_t;

typedef struct
{
  uint32_t curveID;
  uint16_t byteLenP;
  uint16_t byteLenN;
  uint8_t *pFullModulusP;
  uint8_t *pFullModulusN;
  uint8_t *pR2P;
  uint8_t *pR2N;
} mcuxClEcc_CommonDomainParams_t;

struct mcuxClEcc_Mont_DomainParams_t
{
  mcuxClEcc_CommonDomainParams_t common;
  uint16_t c;
  uint16_t t;
  uint8_t *pA;
  uint8_t *pB;
  uint8_t *pGx;
  uint8_t *pGy;
  uint8_t *pA24;
};

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SetupEnvironment(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParams,
    uint8_t noOfBuffers
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_DhSetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhSetupEnvironment(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_Mont_DomainParams_t *pDomainParams,
    uint8_t noOfBuffers
    );

#define MCUXCLECC_MONT_DH_SCALAR_BLINDING_BYTELEN  4u

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_GenerateMultiplicativeBlinding)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_GenerateMultiplicativeBlinding(mcuxClSession_Handle_t pSession);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_DhDecodeScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhDecodeScalar(
    mcuxClEcc_Mont_DomainParams_t *pDomainParameters
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_DhDecodeCoordinate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhDecodeCoordinate(
    mcuxClEcc_Mont_DomainParams_t *pDomainParameters,
    const uint8_t *pCoordinateEnc
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(
    uint8_t iScalar,
    uint32_t scalarBitLen,
    uint32_t optionAffineOrProjective
    );

#define MCUXCLECC_PROJECTIVE        (0xA5A5A5A5u)
#define MCUXCLECC_AFFINE            (0x5A5A5A5Au)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Mont_DhX)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhX(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_Mont_DomainParams_t *pDomainParameters,
    const uint8_t *pCoordinateUEnc
    );

#define mcuxClEcc_FUP_SetupEnvironment_ClearBuffers_LEN  5u

#define mcuxClEcc_FUP_MontDhDecodeScalar_LEN  5u

#define mcuxClEcc_FUP_MontDhX_CalcAffineX_LEN  5u

#define mcuxClEcc_Fup_SecureScalarMult_XZMontLadder_LadderStep_Affine_LEN  19u
#define mcuxClEcc_Fup_SecureScalarMult_XZMontLadder_LadderStep_Projective_LEN  22u

#define ECC_MONTDH_NO_OF_VIRTUALS  0x10u
#define ECC_MONTDH_NO_OF_BUFFERS   0x19u

#endif
