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
 * @file  mcuxClEcc_Internal_SetupEnvironment.c
 * @brief mcuxClEcc: implementation of mcuxClEcc_SetupEnvironment
 */

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClMemory.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClEcc_Mont_Internal.h>

#define ALIGNED_SIZE(byteLen)  ((((byteLen) + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t))) * (sizeof(uint32_t)))

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SetupEnvironment(mcuxClSession_Handle_t pSession,
                                                                        mcuxClEcc_CommonDomainParams_t *pCommonDomainParams,
                                                                        uint8_t noOfBuffers)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_SetupEnvironment);

    const uint32_t byteLenP = (uint32_t) pCommonDomainParams->byteLenP;
    const uint32_t byteLenN = (uint32_t) pCommonDomainParams->byteLenN;
    const uint32_t byteLenMax = ((byteLenP > byteLenN) ? byteLenP : byteLenN);
    const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenMax);
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) (& pSession->cpuWa.buffer[pSession->cpuWa.used]);
    uint32_t byteLenOperandsTable = (sizeof(uint16_t)) * (ECC_NO_OF_VIRTUALS + (uint32_t) noOfBuffers);
    uint32_t alignedByteLenCpuWa = (sizeof(mcuxClEcc_CpuWa_t)) + ALIGNED_SIZE(byteLenOperandsTable);
    uint32_t wordNumCpuWa = alignedByteLenCpuWa / (sizeof(uint32_t));
    pSession->cpuWa.used += wordNumCpuWa;
    pCpuWorkarea->wordNumCpuWa = wordNumCpuWa;

    const uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
    const uint32_t wordNumPkcWa = (bufferSize * (uint32_t) noOfBuffers) / (sizeof(uint32_t));
    pSession->pkcWa.used += wordNumPkcWa;
    pCpuWorkarea->wordNumPkcWa = wordNumPkcWa;

    MCUXCLPKC_FP_INITIALIZE(& pCpuWorkarea->pkcStateBackup);

    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);

    uint16_t *pOperands = (uint16_t *) pCpuWorkarea->pOperands32;

    MCUXCLPKC_FP_GENERATEUPTRT(& pOperands[ECC_NO_OF_VIRTUALS],
                              pPkcWorkarea,
                              (uint16_t) bufferSize,
                              noOfBuffers);
    MCUXCLPKC_SETUPTRT(pOperands);

    pOperands[ECC_P] = pOperands[ECC_PFULL] + MCUXCLPKC_WORDSIZE;
    pOperands[ECC_N] = pOperands[ECC_NFULL] + MCUXCLPKC_WORDSIZE;
    pOperands[ECC_V0] = 0u;

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_SetupEnvironment_ClearBuffers,
                        mcuxClEcc_FUP_SetupEnvironment_ClearBuffers_LEN);
    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeImportP,
        mcuxClMemory_copy(MCUXCLPKC_OFFSET2PTR(pOperands[ECC_PFULL]),
                         pCommonDomainParams->pFullModulusP,
                         MCUXCLPKC_WORDSIZE + byteLenP, MCUXCLPKC_WORDSIZE + byteLenP));
    (void) retCodeImportP;

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeImportN,
        mcuxClMemory_copy(MCUXCLPKC_OFFSET2PTR(pOperands[ECC_NFULL]),
                         pCommonDomainParams->pFullModulusN,
                         MCUXCLPKC_WORDSIZE + byteLenN, MCUXCLPKC_WORDSIZE + byteLenN));
    (void) retCodeImportN;

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeImportR2P,
        mcuxClMemory_copy(MCUXCLPKC_OFFSET2PTR(pOperands[ECC_PQSQR]),
                         pCommonDomainParams->pR2P,
                         byteLenP, byteLenP));
    (void) retCodeImportR2P;

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeImportR2N,
        mcuxClMemory_copy(MCUXCLPKC_OFFSET2PTR(pOperands[ECC_NQSQR]),
                         pCommonDomainParams->pR2N,
                         byteLenN, byteLenN));
    (void) retCodeImportR2N;

    MCUXCLMATH_FP_SHIFTMODULUS(ECC_PS, ECC_P);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_NS, ECC_N);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_SetupEnvironment, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus) );
}
