/*--------------------------------------------------------------------------*/
/* Copyright 2018-2019, 2021-2024 NXP                                       */
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
 * @file: mcuxClOsccaSm2_ComputePrehash.c
 * @brief: OSCCA SM2 compute pre-hash
 */

#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClHash.h>
#include <mcuxClMemory.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>

/**
 * The function mcuxClOsccaSm2_ComputePrehash pre-hash ID and domain parameters
 *
 * Returns:
 *  - MCUXCLOSCCASM2_STATUS_COMPUTE_PREHASH_OK  if the function successfully hashed the input
 *  - MCUXCLOSCCASM2_STATUS_FAULT_ATTACK        possible attack detected, and also invalid inputs
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_ComputePrehash)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_ComputePrehash(mcuxClSession_Handle_t session, mcuxClOsccaSm2_ComputePrehash_Param_t *pParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_ComputePrehash);

    uint8_t * const pCpuWorakara = (uint8_t*)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    if (NULL == pCpuWorakara)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* identifierLength < 2^6, so identifierLengthBits < 2^{12} */
    uint32_t identifierLengthBits = (uint32_t)pParams->identifierLength * 8u;
    uint8_t identifierLengthBigEndian[2] = {(uint8_t)(identifierLengthBits >> 8), (uint8_t)(identifierLengthBits & 0xffu)};

    /* Create buffer for prehash */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pContext = (mcuxClHash_Context_t)pCpuWorakara;
    MCUX_CSSL_FP_FUNCTION_CALL(hashInitRet, mcuxClHash_init(session, pContext, mcuxClOsccaSm3_Algorithm_Sm3));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if (MCUXCLHASH_STATUS_OK != hashInitRet)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_ESCAPING_LOCAL_ADDRESS("Address of identifierLengthBigEndian is for internal use only and does not escape")
    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet, mcuxClHash_process(session, pContext, identifierLengthBigEndian, 2u));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ESCAPING_LOCAL_ADDRESS()
    if (MCUXCLHASH_STATUS_OK != hashProRet)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Hash identifier */
    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet2, mcuxClHash_process(session, pContext, pParams->pIdentifier, pParams->identifierLength));
    if (MCUXCLHASH_STATUS_OK != hashProRet2)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Hash a */
    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet3, mcuxClHash_process(session, pContext, pParams->domainParameters.pA, pParams->domainParameters.p.wNumBytes));
    if (MCUXCLHASH_STATUS_OK != hashProRet3)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Hash b */
    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet4, mcuxClHash_process(session, pContext, pParams->domainParameters.pB, pParams->domainParameters.p.wNumBytes));
    if (MCUXCLHASH_STATUS_OK != hashProRet4)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Hash G coordinates */
    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet5, mcuxClHash_process(session, pContext, pParams->domainParameters.pG, 2u * (uint32_t)pParams->domainParameters.p.wNumBytes));
    if (MCUXCLHASH_STATUS_OK != hashProRet5)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Hash Q coordinates */
    MCUX_CSSL_FP_FUNCTION_CALL(hashProRet6, mcuxClHash_process(session, pContext, pParams->pPublicKey, 2u * (uint32_t)pParams->domainParameters.p.wNumBytes));
    if (MCUXCLHASH_STATUS_OK != hashProRet6)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    uint32_t hashOutLen = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL(finishRet, mcuxClHash_finish(session, pContext, pParams->pPrehash, &hashOutLen));
    if (MCUXCLHASH_STATUS_OK != finishRet)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara, MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUXCLMEMORY_FP_MEMORY_CLEAR(pCpuWorakara,MCUXCLOSCCASM2_COMPUTE_PREHASH_SIZEOF_WA_CPU);

    /* Free workarea allocated in mcuxClOsccaSm2_ComputePrehash */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_ComputePrehash, MCUXCLOSCCASM2_STATUS_COMPUTE_PREHASH_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                                                     6u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

}
