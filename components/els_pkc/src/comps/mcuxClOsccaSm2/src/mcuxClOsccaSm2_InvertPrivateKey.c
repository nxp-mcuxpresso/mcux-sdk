/*--------------------------------------------------------------------------*/
/* Copyright 2018-2024 NXP                                                  */
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
 *
 * @file: mcuxClOsccaSm2_InvertPrivateKey.c
 * @brief: OSCCA SM2 compute the inverse of a private key
 *
 */

#include <mcuxClMemory.h>
#include <mcuxClRandom.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_InvertPrivateKey_EccInit)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_InvertPrivateKey_EccInit(
                                               mcuxClSession_Handle_t session,
                                               mcuxClOsccaSm2_DomainParam_t *pParams,
                                               uint32_t bufferInfo)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_InvertPrivateKey_EccInit);

    /* Allocate cpu workarea in mcuxClOsccaSm2_InvertPrivateKey_EccInit */
    uint32_t *pCpuWa = (uint32_t*)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_CPU / sizeof(uint32_t));
    if(NULL == pCpuWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_InvertPrivateKey_EccInit, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClOsccaPkc_State_t *pkcBackup = (mcuxClOsccaPkc_State_t*)pCpuWa;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint8_t noOfVirtuals = (uint8_t) ((bufferInfo >> 8U) & 0xFFU);
    uint8_t noOfBuffers = (uint8_t) (bufferInfo & 0xFFU);


    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_Init(pkcBackup));

    /*
     * the min operand size is 32 for avoid Ndash calculate overwrite pkc buffer
     * followed
     */
    uint32_t operandSize = MCUXCLOSCCASM2_CEILING(MCUXCLCORE_MAX((uint32_t)pParams->p.wNumBytes, MCUXCLCORE_MAX((uint32_t)pParams->n.wNumBytes, 32u)), MCUXCLOSCCAPKC_WORD_SIZE) * MCUXCLOSCCAPKC_WORD_SIZE;
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    uint32_t *pPkcWa = (uint32_t*)mcuxClSession_allocateWords_pkcWa(session, bufferSize * noOfBuffers / sizeof(uint32_t));
    if(NULL == pPkcWa)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Decrypt_Internal_Init */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU /sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_InvertPrivateKey_EccInit, MCUXCLOSCCASM2_STATUS_FAILURE,
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Init));
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
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_SetWordSize(0x2u));
    MCUXCLOSCCAPKC_PS1_SETLENGTH(operandSize, operandSize);

    /* Generate the pointer table. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_GeneratePointerTable(pOperands + noOfVirtuals, pFx, bufferSize, (uint8_t) noOfBuffers));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_InvertPrivateKey_EccInit, MCUXCLOSCCASM2_STATUS_ECCINIT_OK,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Init),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_SetFupTable),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_SetWordSize),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_GeneratePointerTable),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_PrivateKey_Check)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_PrivateKey_Check(
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_InvertPrivateKey_Param_t *pParams
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_PrivateKey_Check);

    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    /* Allocate memory for the pointer table and save the PKC RAM size for the exit gate  */
    uint32_t operandSize = MCUXCLOSCCASM2_CEILING((uint32_t)MCUXCLCORE_MAX(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes), MCUXCLOSCCAPKC_WORD_SIZE) * MCUXCLOSCCAPKC_WORD_SIZE;
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("PKC operand table initialize in mcuxClOsccaPkc_GeneratePointerTable properly.")
    pOperands[TI_m] += (uint16_t)MCUXCLOSCCAPKC_WORD_SIZE;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    /* Import modulus n into _modulus */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import((uint32_t)TI_m, pParams->domainParameters.n.pMPInt, pParams->domainParameters.n.wNumBytes, operandSize));

    /* Compute shifted modulus (aligned to next PKC word boundary) */
    MCUX_CSSL_FP_FUNCTION_CALL(leadingZerosN, mcuxClOsccaPkc_LeadingZeros(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_m]), operandSize));
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(leadingZerosN, 0u, 255u, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK)
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_MultipleShiftRotate_Index(TI_ms, TI_m, leadingZerosN, true));

    /* Compute Montgomery constants for n */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeNDash(MCUXCLOSCCAPKC_PKCPACKARGS(TI_m, TI_tmp1, 0, 0)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_SecureImport(TI_privateKey, pParams->pPrivateKey, pParams->domainParameters.n.wNumBytes, bufferSize));

    /* Generate random in _tmp1 */
    MCUX_CSSL_FP_FUNCTION_CALL(randRetInvertPriKey1, mcuxClRandom_ncGenerate(session,MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_tmp1]), operandSize));
    if (MCUXCLRANDOM_STATUS_OK != randRetInvertPriKey1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_PrivateKey_Check, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Generate random in _tmp2, just shorter 1 bit than n */
    MCUX_CSSL_FP_FUNCTION_CALL(randRetInvertPriKey2, mcuxClRandom_ncGenerate(session,MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_tmp3]), operandSize));
    if (MCUXCLRANDOM_STATUS_OK != randRetInvertPriKey2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_PrivateKey_Check, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    uint8_t *pFx = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_tmp3]);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_ARRAY_OUT_OF_BOUNDS("pFx point a PKC operand ram with size equal operandSize.")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("operandSize is always bigger than 1.")
    pFx[operandSize - 1u] |= 0x80u;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ARRAY_OUT_OF_BOUNDS()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("leadingZeros + 1 can't be overflow")
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_MultipleShiftRotate_Index(TI_tmp2, TI_tmp3, leadingZerosN + 1u, false));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *)mcuxClOsccaSm2_FUP_InvertPrivateKey,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_InvertPrivateKey)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(InvertPriKeyCmpRet, mcuxClOsccaSm2_RobustCompareToZero((uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_tmp2]), operandSize));
    /* t2 == 0, invalid d */
    if (MCUXCLOSCCASM2_STATUS_CMP_EQUAL == InvertPriKeyCmpRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_PrivateKey_Check, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    //Need to sub mcuxClOsccaSm2_RobustCompareToZero input param before exit
    MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_tmp2]) + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL + operandSize);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_PrivateKey_Check, MCUXCLOSCCASM2_STATUS_OK,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_SecureImport),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_LeadingZeros),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_MultipleShiftRotate_Index),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeNDash),
                                                     2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero));
}

/**
 * The function mcuxClOsccaSm2_InvertPrivateKey (d+1)^{-1} with d a private key
 *
 * Returns:
 *  - MCUXCLOSCCASM2_STATUS_INVERT_PRIVATE_KEY_OK  if the function successfully inverses the key
 *  - MCUXCLOSCCASM2_STATUS_FAULT_ATTACK           possible attack detected, and also invalid inputs
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_InvertPrivateKey)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_InvertPrivateKey(mcuxClSession_Handle_t session, mcuxClOsccaSm2_InvertPrivateKey_Param_t *pParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_InvertPrivateKey);

    /******************************************************************/
    /* Step 1: Set-up material                                        */
    /******************************************************************/

    /* inititlize the pkc and ECC parameters */
    MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_InvertPrivateKey_EccInit(session, &(pParams->domainParameters),
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, MCUXCLOSCCASM2_INVERTPRIVATEKEY_NO_OF_VIRTUALS, MCUXCLOSCCASM2_INVERTPRIVATEKEY_NO_OF_BUFFERS)));
    if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_InvertPrivateKey, MCUXCLOSCCASM2_STATUS_FAILURE,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_InvertPrivateKey_EccInit));
    }

    /******************************************************************/
    /* Step 2: Check privateKey != n-1                                */
    /******************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL(CheckPriKeyRet, mcuxClOsccaSm2_PrivateKey_Check(session, pParams));
    if (MCUXCLOSCCASM2_STATUS_OK != CheckPriKeyRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_InvertPrivateKey, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /******************************************************************/
    /* Step 3: Compute the inverse of privateKey + 1                  */
    /******************************************************************/
    /* t2 = ((d + 1) * r2')^-1 * R mod n */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeModInv(MCUXCLOSCCAPKC_PKCPACKARGS(TI_tmp4, TI_tmp2, TI_m, TI_tmp0), (uint32_t)TI_tmp3));

    /*
     * t3 = ((d + 1) * r2')^-1 mod n
     * since t3 != 0 mod n, and the result of MRed() <= n,
     * so t3 is in the range [1, n-1]
     *
     */
    MCUXCLOSCCAPKC_FXIMC1_MRED(TI_tmp3, TI_tmp2, TI_m);

    /*
     * t4 = (d + 1)^-1 mod n
     * since t1 and t3 are both in the range [1, n-1],
     * the resulte of MMul < (n*n + R*n)/R < 2n
     * i.e., in the range [1, 2n-1]
     */
    MCUXCLOSCCAPKC_FXIMC1_MMUL(TI_tmp4, TI_tmp1, TI_tmp3, TI_m);
    /* [1, n-1] */
    MCUXCLOSCCAPKC_FXIMC1_MSUB(TI_privateKeyInverse, TI_tmp4, TI_m, TI_m);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_privateKeyInverse, pParams->pPrivateKeyInverse,
            pParams->domainParameters.n.wNumBytes));

    /* Free workarea allocated in mcuxClOsccaSm2_InvertPrivateKey */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_CPU / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_INVERTPRIVATEKEY_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes) / sizeof(uint32_t));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_InvertPrivateKey,MCUXCLOSCCASM2_STATUS_INVERT_PRIVATE_KEY_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_InvertPrivateKey_EccInit),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_PrivateKey_Check),
                                                        MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_INVERTPRIVATEKEY_BALANCE_FINAL_PART);
}
