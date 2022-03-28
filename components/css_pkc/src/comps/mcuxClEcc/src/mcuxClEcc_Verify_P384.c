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

/** @file  mcuxClEcc_Verify_P384.c
 *  @brief mcuxClEcc: implementation of ECDSA signature verification for curve P-384
 */

#include <stdint.h>
#include <stddef.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClMemory.h>
#include <mcuxCsslMemory_Compare.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslParamIntegrity.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <mcuxClEcc_Verify_P384.h>
#include <internal/mcuxClEcc_Verify_FUP_programs.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_NIST.h>
#include <internal/mcuxClEcc_Curve_P384.h>

static const uint32_t pCurveP384_b[MCUXCLECC_CURVE_P384_PRIME_P_BYTELEN / (sizeof(uint32_t))] =
{ MCUXCLECC_CURVE_P384_COEFFICIENT_B };

static const uint32_t pCurveP384_pNDash_pLowHalf[(MCUXCLPKC_WORDSIZE + MCUXCLECC_CURVE_P384_PRIME_P_LOWHALF_BYTELEN) / (sizeof(uint32_t))] =
{ MCUXCLECC_CURVE_P384_PRIME_P_NDASH, MCUXCLECC_CURVE_P384_PRIME_P_LO192 };

static const uint32_t pCurveP384_pQSqr[MCUXCLECC_CURVE_P384_PRIME_P_BYTELEN / (sizeof(uint32_t))] =
{ MCUXCLECC_CURVE_P384_PRIME_P_QSQR };

static const uint32_t pCurveP384_nNDash_nLowHalf[(MCUXCLPKC_WORDSIZE + MCUXCLECC_CURVE_P384_ORDER_N_LOWHALF_BYTELEN) / (sizeof(uint32_t))] =
{ MCUXCLECC_CURVE_P384_ORDER_N_NDASH, MCUXCLECC_CURVE_P384_ORDER_N_LO192 };

static const uint32_t pCurveP384_BasePoint[(2u * MCUXCLECC_CURVE_P384_PRIME_P_BYTELEN) / (sizeof(uint32_t))] =
{ MCUXCLECC_CURVE_P384_BASEPOINT_X, MCUXCLECC_CURVE_P384_BASEPOINT_Y} ;

static const uint32_t pCurveP384_PrecBP[(2u * MCUXCLECC_CURVE_P384_PRIME_P_BYTELEN) / (sizeof(uint32_t))] =
{ MCUXCLECC_CURVE_P384_PRECBP_X, MCUXCLECC_CURVE_P384_PRECBP_Y };

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_SwitchEndianness_P384)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SwitchEndianness_P384(uint32_t *ptr)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_SwitchEndianness_P384);

    const uint32_t opSizeInCPUWord = 384u / ((sizeof(uint32_t)) * 8u);

    uint32_t *ptrLo = ptr;
    uint32_t *ptrHi = ptr + opSizeInCPUWord;

    for (uint32_t i = (opSizeInCPUWord / 2u); i > 0u; i--)
    {
        uint32_t tempLo = *ptrLo;
        ptrHi--;
        uint32_t tempHi = *ptrHi;

        tempLo = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(tempLo);
        tempHi = MCUXCLMEMORY_SWITCH_4BYTE_ENDIANNESS(tempHi);

        *ptrHi = tempLo;
        *ptrLo = tempHi;
        ptrLo++;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SwitchEndianness_P384, MCUXCLECC_STATUS_OK);
}

#define MCUXCLECC_FP_SWITCHENDIANNESS_P384(ptr)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_SwitchEndianness_P384(ptr));  \
        (void) retValTemp;    \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Verify_P384)
mcuxClEcc_Status_Protected_t mcuxClEcc_Verify_P384(const uint8_t * pHash,
                                                 const uint8_t * pSignature,
                                                 const uint8_t * pPublicKey,
                                                 uint8_t *       pOutputR)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Verify_P384,

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),

        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,

        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST );

    MCUXCLPKC_FP_INITIALIZE(NULL);

    const uint32_t byteLenP = MCUXCLECC_CURVE_P384_PRIME_P_BYTELEN;
    const uint32_t byteLenN = MCUXCLECC_CURVE_P384_ORDER_N_BYTELEN;
    const uint32_t byteLenMax = ((byteLenP > byteLenN) ? byteLenP : byteLenN);
    const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenMax);
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;
    const uint32_t halfOperandSize = operandSize / 2u;

    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
    MCUXCLPKC_PS2_SETLENGTH(0u, halfOperandSize);

    uint32_t pOperands32[(ECC_VERIFY_P384_NO_OF_VIRTUALS + ECC_VERIFY_P384_NO_OF_BUFFERS + 1u) / 2u];

    uint16_t * pOperands = (uint16_t *) pOperands32;
    MCUXCLPKC_FP_GENERATEUPTRT(pOperands + ECC_VERIFY_P384_NO_OF_VIRTUALS,
                              (const uint8_t *) MCUXCLPKC_RAM_START_ADDRESS,
                              (uint16_t) bufferSize,
                              ECC_VERIFY_P384_NO_OF_BUFFERS);
    MCUXCLPKC_SETUPTRT(pOperands);

    uint32_t nOffset_pOffset = MCUXCLECC_LOAD_2OFFSETS(pOperands32, ECC_PFULL, ECC_NFULL);
    nOffset_pOffset += ((MCUXCLPKC_WORDSIZE << 16) | MCUXCLPKC_WORDSIZE);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_P, ECC_N, nOffset_pOffset);

    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_PS, ECC_NS, nOffset_pOffset);

    nOffset_pOffset += ((halfOperandSize << 16) | halfOperandSize);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, nOffset_pOffset);

    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_PFULL, pCurveP384_pNDash_pLowHalf, MCUXCLPKC_WORDSIZE + halfOperandSize);
    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_PQSQR, pCurveP384_pQSqr, byteLenP);

    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_NFULL, pCurveP384_nNDash_nLowHalf, MCUXCLPKC_WORDSIZE + halfOperandSize);

    pOperands[ECC_VB] = pOperands[ECC_R1];
    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_VB, pCurveP384_b, byteLenP);

    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_T0, pSignature, byteLenN);
    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_T1, pSignature + byteLenN, byteLenN);

    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T0]));
    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T1]));

    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_VT2, 0xFFu);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_VT3, 0xFFu);

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_T2, 0xAAu);
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_T3, 0x55u);

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T2, ECC_T0, ECC_N, ECC_N);

    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_N);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T3, ECC_T1, ECC_N, ECC_N);

    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
    }

    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_S3, pSignature, byteLenN);
    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_S1, pSignature + byteLenN, byteLenN);

    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]));
    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S1]));

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_S2, ECC_S3, 0x00u);
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T2, ECC_S3);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_CALC_OP1_AND_CONST(ECC_S0, ECC_S1, 0xFFu);
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T3, ECC_S1);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_S2, pHash, byteLenN);

    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]));

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_S2, ECC_S2, ECC_N, ECC_N);
    uint32_t checkHashZero = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T2, ECC_T1, ECC_N);
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T2, ECC_N, ECC_T3);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_InitZ_CalcU1U2,
                        mcuxClEcc_Fup_InitZ_CalcU1U2_LEN);

    if (checkHashZero != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLECC_FP_INTERLEAVE(MCUXCLPKC_PACKARGS2(ECC_S0, ECC_S1), byteLenN * 8u);

    if (MCUXCLPKC_FLAG_ZERO != checkHashZero)
    {

        MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
        MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_X1, pCurveP384_BasePoint,byteLenP);
        MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_Y1, (const uint8_t *) pCurveP384_BasePoint + byteLenP, byteLenP);

        MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_X2, pCurveP384_PrecBP, byteLenP);
        MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_Y2, (const uint8_t *) pCurveP384_PrecBP + byteLenP, byteLenP);

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
        if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR_NIST())
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X2, ECC_Y2);
        if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR_NIST())
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Convert_G_PrecG_toMR,
                            mcuxClEcc_Fup_Convert_G_PrecG_toMR_LEN);

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_X2, ECC_Y2);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X3, ECC_Y3);
        pOperands[ECC_VZ0] = pOperands[ECC_Z];
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, ECC_XA, ECC_YA);
        MCUXCLECC_FP_CALCFUP_ADD_ONLY();

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Update_G_to_Prec1,
                            mcuxClEcc_Fup_Convert_G_PrecG_toMR_LEN);

        pOperands[ECC_VT] = pOperands[ECC_S2];
        MCUXCLECC_FP_INT_POINTMULT_NIST(ECC_S0, byteLenN * 8u);

        MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, ECC_Z, ECC_ZA, ECC_P);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_Z, ECC_T0, 0u);
    }

    MCUXCLPKC_FP_CALC_OP1_NEG(ECC_ZA, ECC_P);

    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_X1, pPublicKey, byteLenP);
    MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOperands, ECC_Y1, pPublicKey + byteLenP, byteLenP);

    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_X1]));
    MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_Y1]));

    MCUX_CSSL_FP_EXPECT(

        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_OP1_AND_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,

        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,

        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Interleave),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_NONZERO == checkHashZero),
            MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
            MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
            MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
            MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult_NIST),
            MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST),
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,

        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST) );

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
    if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR_NIST())
    {
        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
    }

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Convert_pubkeyQ_toJacobianMR,
                        mcuxClEcc_Fup_Convert_pubkeyQ_toJacobianMR_LEN);

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X3, ECC_Y3);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ,  ECC_ZA, ECC_Z);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, ECC_X0, ECC_Y0);
    pOperands[ECC_VZ2] = pOperands[ECC_ZA];
    pOperands[ECC_VT] = pOperands[ECC_S2];
    MCUXCLECC_FP_REPEATPOINTDOUBLE_NIST((byteLenN * 8u) / 2u);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_X2, ECC_Y2);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X3, ECC_Y3);
    pOperands[ECC_VZ0] = pOperands[ECC_ZA];
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, ECC_X0, ECC_Y0);
    MCUXCLECC_FP_CALCFUP_ADD_ONLY();

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Update_pubkeyQ_P1_z,
                        mcuxClEcc_Fup_Update_pubkeyQ_P1_z_LEN);

    MCUXCLECC_FP_INT_POINTMULT_NIST(ECC_S1, byteLenN * 8u);

    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_RepeatPointDouble_NIST),
        MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult_NIST),

        MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointFullAdd_NIST)) );

    if (MCUXCLPKC_FLAG_ZERO != checkHashZero)
    {

        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_XA, ECC_YA);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ,  ECC_ZA, ECC_Z);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, ECC_X0, ECC_Y0);
        if (MCUXCLECC_INTSTATUS_POINTADD_NEUTRAL_POINT == MCUXCLECC_FP_POINTFULLADD_NIST())
        {
            MCUXCLPKC_FP_DEINITIALIZE(NULL);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_NOT_OK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
        }
    }

    MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, ECC_Z, ECC_ZA, ECC_P);
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T0, ECC_P, ECC_T2);
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Convert_P1plusP2_toAffineNR_CalcR,
                        mcuxClEcc_Fup_Convert_P1plusP2_toAffineNR_CalcR_LEN);

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X0, ECC_Y0);
    if (MCUXCLECC_INTSTATUS_POINTCHECK_NOTOK == MCUXCLECC_FP_POINTCHECKAFFINENR_NIST())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_EXPECT(
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR_NIST),

        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP );

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_X1, ECC_S3);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    uint8_t *pImportR = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]);
    uint8_t *pCalcR   = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_X1]);
    mcuxCsslParamIntegrity_Checksum_t compareR_paramChkSum = mcuxCsslParamIntegrity_Protect(3u, pImportR, pCalcR, operandSize);
    MCUX_CSSL_FP_FUNCTION_CALL(cmpareR_result, mcuxCsslMemory_Compare(compareR_paramChkSum, pImportR, pCalcR, operandSize));
    if (MCUXCSSLMEMORY_COMPARE_EQUAL == cmpareR_result)
    {

        MCUXCLECC_FP_SWITCHENDIANNESS_P384((uint32_t *) pCalcR);

        MCUXCLECC_FP_MEMORY_COPY(pOutputR, pCalcR, byteLenN);

        MCUXCLPKC_FP_DEINITIALIZE(NULL);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_VERIFY_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare),

            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SwitchEndianness_P384),
            MCUXCLECC_FP_CALLED_MEMORY_COPY,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify_P384, MCUXCLECC_STATUS_FAULT_ATTACK);
}
