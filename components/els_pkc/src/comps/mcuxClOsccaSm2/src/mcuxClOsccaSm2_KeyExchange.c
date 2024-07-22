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

/** @file  mcuxClOsccaSm2_KeyExchange.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 KeyExchange function
 */

#include <mcuxClMemory.h>
#include <mcuxClRandom.h>
#include <mcuxClHash.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClOsccaSm2_Internal_Hash.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_ComputeKeyConfirmation_Init)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_ComputeKeyConfirmation_Init(
    mcuxClSession_Handle_t session,
    uint8_t *pHash,
    mcuxClOsccaSm2_KeyExchange_Param_t *pParams,
    uint8_t* pXuSwithEnd)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_ComputeKeyConfirmation_Init);

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pCtx = (mcuxClHash_Context_t)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pCtx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /*------------------------------------------------------------------------*/
    /* Compute Hash(U.x||ZA||ZB||RA.x||RA.y||RB.x||RB.y)                      */
    /*------------------------------------------------------------------------*/

    /* Hash: init and update with U.x (internal buffer). */
    uint32_t hashPro = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("mcuxClHash_Context_t equal mcuxClHash_ContextDescriptor_t *.")
    MCUXCLOSCCASM2_FP_CALC_HASHINITPRO(session, pCtx, mcuxClOsccaSm3_Algorithm_Sm3, pXuSwithEnd, pParams->domainParameters.p.wNumBytes, hashPro);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
    if(MCUXCLHASH_STATUS_OK != hashPro)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Hash: update with Z_A (external input). */
    uint32_t hashPro2 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx, pParams->pPreHashInfoInitiator, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, hashPro2);
    if(MCUXCLHASH_STATUS_OK != hashPro2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Hash: update with Z_B (external input). */
    uint32_t hashPro3 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx, pParams->pPreHashInfoResponder, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, hashPro3);
    if(MCUXCLHASH_STATUS_OK != hashPro3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Prepare pointers to RA and RB according to the role in key exchange. */
    uint8_t const *pRA = NULL;
    uint8_t const *pRB = NULL;
    if (MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_RESPONDER ==
            (pParams->options & MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_MASK))
    {
        pRA = pParams->pPublicEphemeralPointParty2;
        pRB = pParams->pPublicEphemeralPoint;
    }
    else if (MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_INITIATOR ==
        (pParams->options & MCUXCLOSCCASM2_OPT_KEYEXCHANGE_ROLE_MASK))
    {
        pRA = pParams->pPublicEphemeralPoint;
        pRB = pParams->pPublicEphemeralPointParty2;
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Hash: update with RA = RA.x||RA.y (external input). */
    uint32_t hashPro4 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx, pRA, 2u * ((uint32_t)pParams->domainParameters.p.wNumBytes), hashPro4);
    if(MCUXCLHASH_STATUS_OK != hashPro4)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Hash: update with RB = RB.x||RB.y (external input) and finalize. */
    uint32_t hashFin = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pCtx, pRB, (2u * (uint32_t)pParams->domainParameters.p.wNumBytes), pHash, hashFin);
    if(MCUXCLHASH_STATUS_OK != hashFin)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_ComputeKeyConfirmation_Init, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_OK,
                            5U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_HandleKeyConfirmation)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_HandleKeyConfirmation(
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_KeyExchg_WaCpu_t *pWaCpu,
    mcuxClOsccaSm2_KeyExchange_Param_t *pParams,
    uint8_t* pXuSwithEnd,
    uint8_t* pYuSwithEnd)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_HandleKeyConfirmation);

    if (MCUXCLOSCCASM2_OPT_KEYEXCHANGE_NO_KEYCONFIRMATION ==
            (pParams->options & MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION_MASK))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_OK);
    }

    if ((MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION !=
                (pParams->options & MCUXCLOSCCASM2_OPT_KEYEXCHANGE_KEYCONFIRMATION_MASK)))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Allocate buffers for two hash results. */
    uint8_t *pHashTmp = (uint8_t *) pWaCpu->keyExchgBuf;
    /*------------------------------------------------------------------------*/
    /* Compute Hash(U.x||ZA||ZB||RA.x||RA.y||RB.x||RB.y)                      */
    /*------------------------------------------------------------------------*/
    MCUX_CSSL_FP_FUNCTION_CALL(statusComputeKeyConfirmationInit, mcuxClOsccaSm2_ComputeKeyConfirmation_Init(session, pHashTmp, pParams, pXuSwithEnd));
    if (MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_OK != statusComputeKeyConfirmationInit)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /*------------------------------------------------------------------------*/
    /* Compute confirmationFromResponderToInitiator (S1/SB)                   */
    /*         = Hash(0x02||U.y||Hash(U.x||ZA||ZB||RA.x||RA.y||RB.x||RB.y))   */
    /*------------------------------------------------------------------------*/
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pCtx1 = (mcuxClHash_Context_t)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pCtx1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }
    /* The y coordinate (in big-endian) is placed from the 2nd PKC word of buffer _u. */
    /* The first PKC word of buffer _u is reserved for this prefix byte.              */
    uint8_t pUyBE_prefixByte = 0x02u;

    /* Hash: init and update with 0x02||U.y (internal buffer). */
    uint32_t hashRet1 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("mcuxClHash_Context_t equal mcuxClHash_ContextDescriptor_t *.")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_ESCAPING_LOCAL_ADDRESS("Address of pUyBE_prefixByte is for internal use only and does not escape")
    MCUXCLOSCCASM2_FP_CALC_HASHINITPRO(session, pCtx1, mcuxClOsccaSm3_Algorithm_Sm3, &pUyBE_prefixByte, 1u, hashRet1);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ESCAPING_LOCAL_ADDRESS()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
    if(MCUXCLHASH_STATUS_OK != hashRet1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    uint32_t hashPro1 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx1, pYuSwithEnd, (uint32_t)pParams->domainParameters.p.wNumBytes, hashPro1);
    if(MCUXCLHASH_STATUS_OK != hashPro1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Hash: update with Hash(U.x||ZA||ZB||RA.x||RA.y||RB.x||RB.y) (internal buffer) and finalize. */
    uint32_t hashFin1 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pCtx1, pHashTmp, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, pParams->pConfirmationFromResponderToInitiator, hashFin1);
    if(MCUXCLHASH_STATUS_OK != hashFin1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);

    /*------------------------------------------------------------------------*/
    /* Compute confirmationFromInitiatorToResponder (S2/SA)                   */
    /*         = Hash(0x03||U.y||Hash(U.x||ZA||ZB||RA.x||RA.y||RB.x||RB.y))   */
    /*------------------------------------------------------------------------*/
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClHash_Context_t pCtx2 = (mcuxClHash_Context_t)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pCtx2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }
    pUyBE_prefixByte = 0x03u;

    /* Hash: init and update with 0x03||U.y (internal buffer). */
    uint32_t hashRet2 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("mcuxClHash_Context_t equal mcuxClHash_ContextDescriptor_t *.")
    MCUXCLOSCCASM2_FP_CALC_HASHINITPRO(session, pCtx2, mcuxClOsccaSm3_Algorithm_Sm3, &pUyBE_prefixByte, 1u, hashRet2);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
    if(MCUXCLHASH_STATUS_OK != hashRet2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    uint32_t hashPro2 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(session, pCtx2, pYuSwithEnd, (uint32_t)pParams->domainParameters.p.wNumBytes, hashPro2);
    if(MCUXCLHASH_STATUS_OK != hashPro2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }

    /* Hash: update with Hash(U.x||ZA||ZB||RA.x||RA.y||RB.x||RB.y) (internal buffer) and finalize. */
    uint32_t hashFin2 = MCUXCLHASH_STATUS_FAULT_ATTACK;
    MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pCtx2, pHashTmp, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, pParams->pConfirmationFromInitiatorToResponder, hashFin2);
    if(MCUXCLHASH_STATUS_OK != hashFin2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_FAIL);
    }
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM3_CONTEXT_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_HandleKeyConfirmation, MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_OK,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_ComputeKeyConfirmation_Init),
                            6U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),
                            2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),
                            2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_KeyExchange_Init)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_KeyExchange_Init(
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_KeyExchange_Param_t *pParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_KeyExchange_Init);

    /* inititlize the pkc and ECC parameters */
    MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, &(pParams->domainParameters), 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0,
                MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
    if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(&(pParams->domainParameters)));

    MCUX_CSSL_FP_FUNCTION_CALL(genZRetKeyEx, mcuxClOsccaSm2_EccGenerateZ(session, TI_z, TI_s));
    if (MCUXCLOSCCASM2_STATUS_ECCGENZ_OK != genZRetKeyEx)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_KEYEXCHANGE_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange_Init, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_INIT_OK,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_KeyExchange)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_KeyExchange(
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_KeyExchange_Param_t *pParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_KeyExchange);
    uint16_t *pOperands;
    uint32_t operandSize, bufferSize;
    uint32_t w, wBytes;
    uint32_t byteLenP, byteLenN;
    uint8_t *pXExt;

    /* Allocate workarea usage in mcuxClOsccaSm2_KeyExchange */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClOsccaSm2_KeyExchg_WaCpu_t *pWaCpu = (mcuxClOsccaSm2_KeyExchg_WaCpu_t *)mcuxClSession_allocateWords_cpuWa(session,
                                                                                (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pWaCpu)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_INTERNAL_ERROR);
    }
    uint32_t pkcWaByteSizeUsed = MCUXCLOSCCASM2_KEYEXCHANGE_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes);

    /* Initializ the pCommonSecret buffer with random data */
    MCUX_CSSL_FP_FUNCTION_CALL(randomGenRet3, mcuxClRandom_ncGenerate(session, pParams->pCommonSecret, pParams->commonSecretLength));
    if (MCUXCLRANDOM_STATUS_OK != randomGenRet3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_NOK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
    }

    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClOsccaSm2_KDF_Param_t *pKDFParam = &pWaCpu->KDFParam;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    uint8_t *pXu, *pYu, *pXuSwithEnd, *pYuSwithEnd ;

    MCUXCLOSCCASM2_FP_REQUEST_PKC(session, mcuxClOsccaSm2_KeyExchange);

    MCUX_CSSL_FP_FUNCTION_CALL(statusKeyExchangeInit, mcuxClOsccaSm2_KeyExchange_Init(session, pParams));
    if (MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_INIT_OK != statusKeyExchangeInit)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    pOperands = MCUXCLOSCCAPKC_GETUPTRT();

    /* compute the w */
    MCUX_CSSL_FP_FUNCTION_CALL(nLeadingZeros, mcuxClOsccaPkc_LeadingZeros(
            MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_n]), operandSize));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("w + 7 can't wrap because operandSize is 32 if external caller set sm2 domain parameters properly.")
    w = (operandSize * 8u - nLeadingZeros + 1u) / 2u - 1u;
    wBytes = MCUXCLOSCCASM2_BYTELEN(w);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    /* Import wBytes LSBytes of R_Ext.x to _scalar */
    byteLenP = (uint32_t) pParams->domainParameters.p.wNumBytes;
    pXExt = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_scalar]);
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(byteLenP, wBytes, 80u, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK)
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_scalar,
                         pParams->pPublicEphemeralPointParty2 + (byteLenP - wBytes),
                         wBytes,
                         bufferSize));

    /* Clear higher bits (w+1 ~ ...) and set bit w */
    uint8_t twoToWModEight = (1u << (w & 7u));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("twoToWModEight is always bigger than 1.")
    pXExt[w >> 3] = (pXExt[w >> 3] & (twoToWModEight - 1u)) | twoToWModEight;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    /* import the point RB */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1,
            pParams->pPublicEphemeralPointParty2, pParams->domainParameters.p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg,
            pParams->pPublicEphemeralPointParty2 + pParams->domainParameters.p.wNumBytes,
            pParams->domainParameters.p.wNumBytes));

    /* check if the RB is valid */
    pOperands[TI_xa] = pOperands[TI_sx1];
    pOperands[TI_ya] = pOperands[TI_sy1];
    pOperands[TI_z1] = pOperands[TI_sz1_dash];
    MCUX_CSSL_FP_FUNCTION_CALL(KeyExJacPoRet1, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == KeyExJacPoRet1)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaByteSizeUsed / sizeof(uint32_t));
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_KeyExchange);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_INVALID_PARAMS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_INIT,
                                                         MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                         MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }

    /* compute the [x2]RB */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointMultMontgomery((uint32_t)TI_scalar));
    MCUX_CSSL_FP_FUNCTION_CALL(KeyExJacPoRet2, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == KeyExJacPoRet2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* import the PB */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1,
            pParams->pPublicKeyParty2, pParams->domainParameters.p.wNumBytes));

    pOperands[TI_x0] = pOperands[TI_sx1];
    pOperands[TI_y0] = pOperands[TI_sy1];

    /* compute the PB + [x2]RB */
    MCUX_CSSL_FP_FUNCTION_CALL(KeyExPointADRet, mcuxClOsccaSm2_EccPointAddOrDouble());
    if (MCUXCLOSCCASM2_STATUS_POINTADD_INFINITE == KeyExPointADRet)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaByteSizeUsed / sizeof(uint32_t));
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_KeyExchange);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_NOK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART1,
                                                         MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                         MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(KeyExJacPoRet3, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == KeyExJacPoRet3)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaByteSizeUsed / sizeof(uint32_t));
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_KeyExchange);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_INVALID_PARAMS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART2,
                                                         MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                         MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);

    }

    /* update the z, _sx1, _sy1 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
            (const void *)mcuxClOsccaSm2_FUP_UpdateZ,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_UpdateZ)));

    /* Import wBytes LSBytes of R_Ext.x to _scalar */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_scalar,
            pParams->pPublicEphemeralPoint + (byteLenP - wBytes),
            wBytes,
            bufferSize));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("twoToWModEight is always bigger than 1.")
    pXExt[w >> 3] = (pXExt[w >> 3] & (twoToWModEight - 1u)) | twoToWModEight;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    /****************************************************************************/
    /* Securely compute tA = (d + R.x * r) mod n                                 */
    /****************************************************************************/
    /* Securely import private key d and ephemeral scalar r to _s and _t, respectively. */
    byteLenN = (uint32_t) pParams->domainParameters.n.wNumBytes;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_s, pParams->pPrivateKey, byteLenN, bufferSize));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_t, pParams->pPrivateEphemeralScalar, byteLenN, bufferSize));
    MCUX_CSSL_FP_FUNCTION_CALL(randomRetKeyEx, mcuxClRandom_ncGenerate(session, MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]), operandSize));
    if (MCUXCLRANDOM_STATUS_OK != randomRetKeyEx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /*
     * Compute tA = (d + R.x * r) mod n where _s = d, _t = r, _scalar = x, _u = rnd,
     * _modulus = n
     */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *)mcuxClOsccaSm2_FUP_KeyExchgCalcTa,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_KeyExchgCalcTa)));
    MCUXCLOSCCAPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL(KeyExCmpRet,  mcuxClOsccaSm2_RobustCompareToZero((uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_scalar]), operandSize));

    if (MCUXCLOSCCASM2_STATUS_CMP_EQUAL == KeyExCmpRet)
    {
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_scalar]) + operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL);
        /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
        mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaByteSizeUsed / sizeof(uint32_t));
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_KeyExchange);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_NOK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                         MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART3,
                                                         MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                         MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }

    /* compute the [tA]*(PB + [x2]RB) */
    MCUX_CSSL_FP_FUNCTION_CALL(pointMulRet, mcuxClOsccaSm2_EccSecurePointMult(session, (uint32_t)TI_scalar));
    if (MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK != pointMulRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL(KeyExJacPoRet4, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == KeyExJacPoRet4)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());

    pXu = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_xa]);
    pYu = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_ya]);
    uint32_t offset = mcuxClOscca_alignSize(pParams->domainParameters.p.wNumBytes) - pParams->domainParameters.p.wNumBytes;
    uint32_t alignedLength = mcuxClOscca_alignSize(pParams->domainParameters.p.wNumBytes);
    pXuSwithEnd = pXu + offset;
    pYuSwithEnd = pYu + offset;
    /* Change endianess of x2 and y2, cause Hash needs big endian representation */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pXu and pYu word aligned from uint8_t* to uint32_t* to improve access.")
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_switch_endianness((uint32_t*)pXu, alignedLength));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_switch_endianness((uint32_t*)pYu, alignedLength));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    pKDFParam->pX2 = pXuSwithEnd;
    pKDFParam->pY2 = pYuSwithEnd;
    pKDFParam->pZA = pParams->pPreHashInfoInitiator;
    pKDFParam->pZB = pParams->pPreHashInfoResponder;
    pKDFParam->pKeyBuffer = pParams->pCommonSecret;
    pKDFParam->keyLength = pParams->commonSecretLength;
    pKDFParam->domainParameters.p.wNumBytes =  pParams->domainParameters.p.wNumBytes;
    /* computer the common secret by the KDF */
    MCUX_CSSL_FP_FUNCTION_CALL(KeyExKdfRet, mcuxClOsccaSm2_KDF(session, pKDFParam));
    if (MCUXCLOSCCASM2_STATUS_KDF_OK != KeyExKdfRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* optional, compute the key confirmation */
    MCUX_CSSL_FP_FUNCTION_CALL(statusHandleKeyConfirmation, mcuxClOsccaSm2_HandleKeyConfirmation(session, pWaCpu, pParams, pXuSwithEnd, pYuSwithEnd));
    if (MCUXCLOSCCASM2_STATUS_HANDLEKEYCONFIRMATION_OK != statusHandleKeyConfirmation)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_scalar]) + operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
    /* Free workarea allocated in mcuxClOsccaSm2_KeyExchange */
    mcuxClSession_freeWords_cpuWa(session, (sizeof(mcuxClOsccaSm2_KeyExchg_WaCpu_t) + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, pkcWaByteSizeUsed / sizeof(uint32_t));

    MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_KeyExchange);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_KeyExchange, MCUXCLOSCCASM2_STATUS_KEYEXCHANGE_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART4,
                                                MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
}
