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

/*
 * @file: mcuxClOsccaSm2_EccUtils.c
 * @brief: OSCCA SM2 ECC Utils functions
 */

#include <mcuxClToolchain.h>
#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClSession.h>
#include <mcuxClMemory.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClRandom.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccInit)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccInit(
                                               mcuxClSession_Handle_t session,
                                               mcuxClOsccaSm2_DomainParam_t *pParams,
                                               uint32_t stackSize UNUSED_PARAM,
                                               uint32_t bufferInfo)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccInit);

    /* Allocate cpu workare in mcuxClOsccaSm2_EccInit */
    uint32_t *pCpuWa = (uint32_t*)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
    if(NULL == pCpuWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccInit, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClOsccaPkc_State_t *pkcBackup = (mcuxClOsccaPkc_State_t*)pCpuWa;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint8_t noOfVirtuals = (uint8_t) ((bufferInfo >> 8) & 0xFFU);
    uint8_t noOfBuffers = (uint8_t) (bufferInfo & 0xFFU);


    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Init(pkcBackup));

    uint32_t pkcWordSize = MCUXCLOSCCAPKC_WORD_SIZE;
    /*
     * the min operand size is 32 for avoid Ndash calculate overwrite pkc buffer
     * followed
     */
    uint32_t operandSize = MCUXCLOSCCASM2_CEILING(
                            MCUXCLCORE_MAX(pParams->p.wNumBytes,
                            MCUXCLCORE_MAX(pParams->n.wNumBytes, 32u)),
                            pkcWordSize) * pkcWordSize;
    uint32_t bufferSize = operandSize + pkcWordSize;
    uint32_t *pPkcWa = (uint32_t*)mcuxClSession_allocateWords_pkcWa(session, bufferSize * noOfBuffers / sizeof(uint32_t));
    if(NULL == pPkcWa)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Decrypt_Internal_Init */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU /sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccInit, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t*)pPkcWa, noOfBuffers * bufferSize);
    /*
     * Allocate memory for the pointer table and reserve the PKC RAM for the
     * RNG call
     */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("pCpuWa+sizeof(mcuxClOsccaPkc_State_t) is 16bit aligned")
    uint16_t * pOperands = (uint16_t *) ((uint8_t *)pCpuWa + sizeof(mcuxClOsccaPkc_State_t));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()

    uint8_t * pFx = (uint8_t *)pPkcWa;

    /* Set up FUP parameters */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_SetFupTable(pOperands));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_SetWordSize(0x2));
    MCUXCLOSCCAPKC_PS1_SETLENGTH(operandSize, operandSize);

    /* Generate the pointer table. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_GeneratePointerTable(pOperands + noOfVirtuals, pFx, bufferSize, (uint8_t) noOfBuffers));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("PKC operand table initialize in mcuxClOsccaPkc_GeneratePointerTable properly.")
    pOperands[TI_modulus] = (uint16_t) (pOperands[TI_modulusf] + pkcWordSize);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    MCUXCLOSCCAPKC_PS2_SETLENGTH(0u, bufferSize);
    MCUXCLOSCCAPKC_FXIOP2_XOR(TI_const0, TI_const0, TI_const0);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccInit, MCUXCLOSCCASM2_STATUS_ECCINIT_OK,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Init),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_SetFupTable),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_SetWordSize),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_GeneratePointerTable),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPrepareParameters)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPrepareParameters(mcuxClOsccaSm2_DomainParam_t *pDomainParameters)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPrepareParameters);
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;

    /* clear to avoid length difference */;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_modulus,
            pDomainParameters->p.pMPInt,
            pDomainParameters->p.wNumBytes, operandSize));

    /* Compute Montgomery modulus in _modulusf */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeNDash(MCUXCLOSCCAPKC_PKCPACKARGS(TI_modulus, TI_s, 0, 0)));

    /* Compute shifted modulus (aligned to next PKC word boundary) in _moduluss */
    MCUX_CSSL_FP_FUNCTION_CALL(leadingZeros1, mcuxClOsccaPkc_LeadingZeros(
            MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_modulus]), operandSize));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_MultipleShiftRotate_Index(TI_moduluss, TI_modulus, leadingZeros1, true));

    /* Compute the montgomery constant parameters R^2 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeQSquared(MCUXCLOSCCAPKC_PKCPACKARGS(TI_q2, TI_modulus, TI_s, TI_v), TI_moduluss));

    /* Reserve a pkc word for ndash */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("PKC operand table has initialized properly before.")
    pOperands[TI_n] = pOperands[TI_nf] + MCUXCLOSCCAPKC_WORD_SIZE;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_n, pDomainParameters->n.pMPInt,
            pDomainParameters->n.wNumBytes, operandSize));
    /* compute the ndash for later use*/
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeNDash(MCUXCLOSCCAPKC_PKCPACKARGS(TI_n, TI_s, 0, 0)));

    /* Compute shifted modulus n */
    MCUX_CSSL_FP_FUNCTION_CALL(leadingZeros2,mcuxClOsccaPkc_LeadingZeros(
            MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_n]), operandSize));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_MultipleShiftRotate_Index(TI_nshift, TI_n, leadingZeros2, true));

    /* Compute the Montgomery constant parameters R^2 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeQSquared(MCUXCLOSCCAPKC_PKCPACKARGS(TI_n2, TI_n, TI_s, TI_v), TI_nshift));

    /* Import curve parameter a into _u */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_u,
            pDomainParameters->pA, pDomainParameters->p.wNumBytes, bufferSize));

    /* Import curve parameter b into _t */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_t,
            pDomainParameters->pB, pDomainParameters->p.wNumBytes, bufferSize));

    /* Transform parameter a, b to Montgomery representation in _a */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_a, TI_u, TI_q2, TI_modulus);
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_b, TI_t, TI_q2, TI_modulus);

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccPrepareParameters,4u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeNDash),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_LeadingZeros),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_MultipleShiftRotate_Index),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeQSquared),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccGenerateZ)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccGenerateZ(mcuxClSession_Handle_t session, uint32_t iZ, uint32_t iTmp UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccGenerateZ);
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();

    /* Avoid CPU and on-going PKC operation concurrently accessing to PKC workarea */
    MCUXCLOSCCAPKC_PKC_CPU_ARBITRATION_WORKAROUND();

    MCUX_CSSL_FP_FUNCTION_CALL(ret, mcuxClRandom_ncGenerate(session,
            MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[iZ]), operandSize));

    if (MCUXCLRANDOM_STATUS_OK != ret)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccGenerateZ, MCUXCLOSCCASM2_STATUS_ECCGENZ_FAIL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccGenerateZ, MCUXCLOSCCASM2_STATUS_ECCGENZ_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccJacPointCheck)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccJacPointCheck(uint32_t iX UNUSED_PARAM, uint32_t iY UNUSED_PARAM)
{
    /* just use the curve equation to check if the point is on the curve
     *
     * Y^2 = X^3 + aXZ^4 + bZ^6
     *
     */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccJacPointCheck);
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    mcuxClOsccaSm2_Status_t pointCheckRet;

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *)mcuxClOsccaSm2_FUP_JacPointCheck,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_JacPointCheck)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    MCUX_CSSL_FP_FUNCTION_CALL(cmpRet, mcuxClOsccaSm2_RobustCompareToZero((uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]), operandSize));

    if (MCUXCLOSCCASM2_STATUS_NOT_EQUAL == cmpRet)
    {
        pointCheckRet = MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL;
    }
    else
    {
        pointCheckRet = MCUXCLOSCCASM2_STATUS_ECCJACPOINT_EQUAL;
    }

    MCUX_CSSL_SC_SUB((uint32_t)cmpRet + (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + operandSize);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccJacPointCheck, pointCheckRet,
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero));

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccPointConvert2Affine)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccPointConvert2Affine(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccPointConvert2Affine);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_EccPointConvert2Affine_PrepareZ3,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_EccPointConvert2Affine_PrepareZ3)));

    /* get the inverse of z^2 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeModInv(
            MCUXCLOSCCAPKC_PKCPACKARGS(TI_v, TI_t, TI_modulus, TI_s), TI_u));
    /*convert to affine : x / z^2 */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_s, TI_t, TI_xa, TI_modulus);
    MCUXCLOSCCAPKC_FXIMC1_MRED(TI_xa, TI_s, TI_modulus);

    /* z3 ^ 3 in NR*/
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_t, TI_v, TI_z1, TI_modulus);
    /* get the inverse of z^3 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeModInv(
            MCUXCLOSCCAPKC_PKCPACKARGS(TI_t, TI_v, TI_modulus, TI_s), TI_u));
    /*convert to affine : y / z^3 */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_s, TI_v, TI_ya, TI_modulus);
    MCUXCLOSCCAPKC_FXIMC1_MRED(TI_ya, TI_s, TI_modulus);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccPointConvert2Affine,
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeModInv),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                    5u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccGenRandomBytes)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_EccGenRandomBytes(mcuxClSession_Handle_t session, uint32_t opsIndex, uint32_t len)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccGenRandomBytes);
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();

    /* Avoid CPU and on-going PKC operation concurrently accessing to PKC workarea */
    MCUXCLOSCCAPKC_PKC_CPU_ARBITRATION_WORKAROUND();

    MCUXCLMEMORY_FP_MEMORY_CLEAR(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[opsIndex]),operandSize + MCUXCLOSCCAPKC_WORD_SIZE);
    MCUX_CSSL_FP_FUNCTION_CALL(EccGenRandomRet, mcuxClRandom_generate(session,
                                                  MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[opsIndex]),
                                                  len));
    if (MCUXCLRANDOM_STATUS_OK != EccGenRandomRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccGenRandomBytes, MCUXCLOSCCASM2_STATUS_ECCGENRAND_FAIL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_EccGenRandomBytes, MCUXCLOSCCASM2_STATUS_ECCGENRAND_OK,
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate));
}

/*
 * import the point
 * iP is for X, iP+1 is for Y, iP+2 is for Z
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccImportInputPointWithInit)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccImportInputPointWithInit(
        uint32_t iP,
        uint8_t const *pP,
        uint32_t byteCountP)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccImportInputPointWithInit);
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_EccImportInputPointInputPointWithInit_PrepareZ23,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_EccImportInputPointInputPointWithInit_PrepareZ23)));

    /* Import  the point P */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_v, pP, byteCountP, bufferSize));
    /* X*Z^2*R */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(iP, TI_v, TI_s, TI_modulus);

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_v, &pP[byteCountP], byteCountP, bufferSize));
    /* Y*Z^3*R */
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(iP, 0u, TI_indexmax,)
    MCUXCLOSCCAPKC_FXIMC1_MMUL(iP+1u, TI_v, TI_u, TI_modulus);

    /* Z = 1 in MR */
    MCUXCLOSCCAPKC_FXIOP1_NEG(iP+2u, TI_modulus);

    /* don't need waitforfinish, because it will be called in PointAdd */
     MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit,
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                                    3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccImportInputPointYNegNoInit(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
        uint32_t iYneg,
        uint8_t const *pY,
        uint32_t byteCountY)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccImportInputPointYNegNoInit);
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;

    /* Import  the point Y */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(iYneg, pY, byteCountY, bufferSize));
    MCUXCLOSCCAPKC_FXIMC1_MSUB(TI_v, TI_modulus, iYneg, TI_modulus);
    MCUXCLOSCCAPKC_FXIMC1_MMUL(iYneg, TI_v, TI_u, TI_modulus);

    /* don't need waitforfinish, because it will be called in PointAdd */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit,
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));
}

/* transfer a pkc buffer point from affine to jacobian coordinates*/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_EccTransAffinePoint2Jac)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm2_EccTransAffinePoint2Jac(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_EccTransAffinePoint2Jac);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_EccTransAffinePoint2Jac,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_EccTransAffinePoint2Jac)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm2_EccTransAffinePoint2Jac, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish));

}

