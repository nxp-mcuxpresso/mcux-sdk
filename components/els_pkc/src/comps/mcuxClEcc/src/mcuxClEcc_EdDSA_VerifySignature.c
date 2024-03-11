/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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
 * @file  mcuxClEcc_EdDSA_VerifySignature.c
 * @brief Implementation of the EdDSA signature verification functionality
 */


#include <mcuxClCore_Platform.h>

#include <mcuxClSession.h>
#include <mcuxClBuffer.h>
#include <mcuxClKey.h>
#include <mcuxClPkc.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Macros.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>
#include <mcuxClHash.h>

#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClMemory_Copy_Internal.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClEcc_Internal_FUP.h>
#include <internal/mcuxClEcc_TwEd_Internal_FUP.h>
#include <internal/mcuxClEcc_EdDSA_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_FUP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_VerifySignature_Core)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_VerifySignature_Core(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_InputBuffer_t pSignature,
    uint32_t signatureSize )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_VerifySignature_Core);

    /*
     * Step 1: Set up the environment
     */

    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory")
    mcuxClEcc_CpuWa_t * const pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(session, 0u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    mcuxClEcc_EdDSA_DomainParams_t * const pDomainParams = (mcuxClEcc_EdDSA_DomainParams_t *) mcuxClKey_getTypeInfo(key);

    MCUX_CSSL_FP_FUNCTION_CALL(retSetupEnvironment,
        mcuxClEcc_EdDSA_SetupEnvironment(session, pDomainParams, ECC_EDDSA_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_OK != retSetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retSetupEnvironment, mcuxClEcc_EdDSA_VerifySignature_Core);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    const uint32_t encodedLen = (uint32_t) pDomainParams->b / 8u;
    const uint32_t sigLength = encodedLen * 2u;
    const mcuxCl_InputBuffer_t buffSignatureR = pSignature;

    /*
     * Step 2: Verify that the passed signatureSize value is as expected.
     */

    if (signatureSize != sigLength)
    {
        mcuxClSession_freeWords_pkcWa(session, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(session, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,                        /* Clean up */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment));  /* Step 1 */
    }


    /*
     * Step 3: Import signature component S to buffer ECC_S0 and check if it is smaller than n.
     */

    {  /* TODO: CLNS-11671, workaround for Ed448 */
        const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
        const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;
        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize);

        /* Import S to ECC_S0 */
        MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET(mcuxClEcc_EdDSA_VerifySignature_Core, ECC_S0, pSignature, encodedLen, encodedLen);

        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
    }

    /* Check s < n. */
    /* TODO: CLNS-11671, the comparison should include the 57th byte (p8S0[56]) for Ed448 */
    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_S0, ECC_N);
    if (MCUXCLPKC_FLAG_NOCARRY == MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {   /* s >= n. */
        mcuxClSession_freeWords_pkcWa(session, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(session, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_INVALID_SIGNATURE,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,                        /* Clean up */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment),   /* Step 1 */
            MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET,        /* Step 3 */
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP);
    }


    /*
     * Step 4: Calculate P1 = S * G, and store the result in homogeneous coordinates in MR in buffers
     * ECC_COORD00, ECC_COORD01 and ECC_COORD02.
     */
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    MCUX_CSSL_FP_FUNCTION_CALL(leadingZerosN, mcuxClMath_LeadingZeros(ECC_N));
    uint32_t bitLenN = (operandSize * 8u) - leadingZerosN;

    /* Calculate P1 = S * G */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_plainFixScalarMult,
        pDomainParams->common.pPlainFixScalarMultFctFP->pScalarMultFct(
            session,
            (mcuxClEcc_CommonDomainParams_t *)&pDomainParams->common,
            ECC_S0,
            bitLenN,
            MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_OUTPUT));
    if(MCUXCLECC_STATUS_OK != ret_plainFixScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /*
     * Step 5: Back up the coordinates of P1 in buffers ECC_COORD25, ECC_COORD26 and ECC_COORD27.
     */

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD25, ECC_COORD00, 0u);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD26, ECC_COORD01, 0u);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD27, ECC_COORD02, 0u);


    /*
     * Step 6: Derive the hash prefix from the mode parameter and calculate H(prefix||Renc||Qenc||m') mod n
     * and store it in buffer ECC_S0.
     */

    uint8_t *pPubKey = mcuxClKey_getKeyData(key);

    /* Generate digest m' from m in case phflag is set */
    const uint8_t *m =  NULL;
    uint32_t mLen = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL(retPreHash, mcuxClEcc_EdDSA_PreHashMessage(session, pDomainParams, mode->phflag, pIn, inSize, &m, &mLen));
    if (MCUXCLECC_STATUS_OK != retPreHash)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Initialize hash context */
    uint32_t hashContextSizeInWords = mcuxClHash_getContextWordSize(pDomainParams->algoHash);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Return pointer is 32-bit aligned and satisfies the requirement of mcuxClHash_Context_t");
    mcuxClHash_Context_t pCtx = (mcuxClHash_Context_t) mcuxClSession_allocateWords_cpuWa(session, hashContextSizeInWords);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();
    if (NULL == pCtx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLBUFFER_INIT_RO(buffM1, NULL, m, mLen);
    mcuxCl_InputBuffer_t buffM = NULL;
    if (MCUXCLECC_EDDSA_PHFLAG_ONE == mode->phflag)
    {
        buffM = buffM1;
    }
    else if (MCUXCLECC_EDDSA_PHFLAG_ZERO == mode->phflag)
    {
        buffM = pIn;
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(ret_CalcHashModN,
        mcuxClEcc_EdDSA_CalcHashModN(
            session, pCtx, pDomainParams,
            mode->pHashPrefix, mode->hashPrefixLen,
            buffSignatureR,
            (const uint8_t*)pPubKey,
            buffM, mLen) );
    if (MCUXCLECC_STATUS_OK != ret_CalcHashModN)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Free the hash context */
    mcuxClSession_freeWords_cpuWa(session, hashContextSizeInWords);


    /*
     * Step 7: Call function pDomainParams->pDecodePointFct to decode the public key Qenc and store
     * the homogeneous coordinates of the decoded point Q in buffers ECC_COORD00, ECC_COORD01 and ECC_COORD02.
     */

    MCUXCLBUFFER_INIT_RO(buffPubKey, NULL, pPubKey, encodedLen);
    MCUX_CSSL_FP_FUNCTION_CALL(ret_decodePoint,
        pDomainParams->pDecodePointFct(
            pDomainParams,
            buffPubKey) );
    if(MCUXCLECC_STATUS_INVALID_PARAMS == ret_decodePoint)
    {
        mcuxClSession_freeWords_pkcWa(session, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(session, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,                        /* Clean up */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment),   /* Step 1 */
            MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET,        /* Step 3 */
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),            /* Step 4 */
            pDomainParams->common.pPlainFixScalarMultFctFP->scalarMultFct_FP_FuncId,
            3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,                      /* Step 5 */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_PreHashMessage),     /* Step 6 */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_CalcHashModN),
            pDomainParams->pDecodePoint_FP_FuncId);                         /* Step 7 */
    }
    else if(MCUXCLECC_STATUS_OK != ret_decodePoint)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }


    /*
     * Step 8: Call function pDomainParameters->pPlainVarScalarMultFct to calculate
     * P2 = (H(prefix||Renc||Qenc||m') mod n)*Q and store the result in homogeneous coordinates in MR
     * in buffers ECC_COORD00, ECC_COORD01 and ECC_COORD02.
     */

    MCUX_CSSL_FP_FUNCTION_CALL(ret_plainVarScalarMult,
        pDomainParams->common.pPlainVarScalarMultFctFP->pScalarMultFct(
            session,
            &pDomainParams->common,
            ECC_S0,
            bitLenN,
            MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_OUTPUT));
    if(MCUXCLECC_STATUS_OK != ret_plainVarScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /*
     * Step 9: Calculate R' = P1-P2 and store the homogeneous coordinates of R' in ECC_COORD00, ECC_COORD01 and ECC_COORD02.
     */

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_TwEd_PointSubtraction,
                        mcuxClEcc_FUP_TwEd_PointSubtraction_LEN);


    /*
     * Step 10: Derive the encoding (R')enc of R' and store it in ECC_COORD03.
     */

    /* Convert R' to affine coordinates and store them in ECC_COORD00, ECC_COORD01 */
    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_COORD02, ECC_P, ECC_T1);         /* T0 = Z^(-1)*R^(-1) mod p */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_ConvertHomToAffine, mcuxClEcc_FUP_ConvertHomToAffine_LEN);

    /* Derive the encoding (R')enc of R' */
    MCUXCLPKC_WAITFORREADY();                                              /* TODO: PS2 length is not used in the above FUP, but this is required due to unknown reason (CLNS-7276) */
    uint32_t encodedLenPkc = MCUXCLPKC_ALIGN_TO_PKC_WORDSIZE(encodedLen);
    MCUXCLPKC_PS2_SETLENGTH(0u, encodedLenPkc);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_COORD03, 0u);                          /* Clear encodedLenPkc bytes of buffer ECC_COORD03 */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD03, ECC_COORD01, 0u);          /* Copy operandSize < encodedLenPkc bytes of the y-coordinate from ECC_COORD01 to ECC_COORD03 */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pRX = MCUXCLPKC_OFFSET2PTRWORD(pOperands[ECC_COORD00]);
    uint8_t *pREncLastByte = &MCUXCLPKC_OFFSET2PTR(pOperands[ECC_COORD03])[encodedLen - 1u];
    MCUXCLPKC_WAITFORFINISH();
    uint32_t lsbX = (*pRX) & (uint32_t)0x01u;                             /* Loading a word is usually cheaper than loading a byte */
    *pREncLastByte |= ((uint8_t)lsbX << 7u);

    /*
     * Step 11: Import the signature component Renc and compare it against (R')enc.
     */

    /* Import Renc to ECC_S0 */
    {  /* TODO: CLNS-11671, workaround for Ed448 */
        const uint32_t ps1Backup = MCUXCLPKC_PS1_GETLENGTH_REG();
        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETLENGTH(0u, encodedLenPkc);

        MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC_BUFFER(mcuxClEcc_EdDSA_VerifySignature_Core, ECC_S0, buffSignatureR, encodedLen);
        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETLENGTH_REG(ps1Backup);
    }

    /* Compare ECC_S0 against ECC_COORD03 */
    /* TODO: CLNS-11671, the comparison should include the 57th byte (p8S0[56]) for Ed448 */
    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_S0, ECC_COORD03);


    /*
     * Step 12: If (R')enc != Renc, then compare if h*R' and h*R are equal points
     */

    uint32_t zeroFlag_check = MCUXCLPKC_WAITFORFINISH_GETZERO();
    MCUX_CSSL_FP_BRANCH_DECL(RencNotEqual);
    if (MCUXCLPKC_FLAG_ZERO != zeroFlag_check)
    {
        /*
        * Step 12a: Call function pDomainParameters->pPlainVarScalarMultFct to calculate h*R' and store the result in
        * homogeneous coordinates in MR in buffers ECC_COORD00, ECC_COORD01 and ECC_COORD02.
        */

        /* Compute h and store it in ECC_S1 */
        const uint8_t h = (uint8_t) (1u << ((uint32_t) pDomainParams->c & 0x1Fu));      /* c = cofactor exponent, i.e. cofactor: h = 2^c */
        uint8_t *pS1 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S1]);
        pS1[0] = h;
        uint32_t bitLenH = (uint32_t)pDomainParams->c + (uint32_t)1u;

        /* Initialize Z-coordinate to 1 in NR in buffer ECC_COORD02. Together with the affine X- and Y-coordinates of R' in NR,
         * stored in ECC_COORD00 and ECC_COORD01, this yields projective coordinates of R' as input for the scalar multiplication. */
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_T0, 0u);
        MCUXCLPKC_FP_CALC_OP1_ADD_CONST(ECC_COORD02, ECC_T0, 1u);

        /* Compute h*R' */
        MCUX_CSSL_FP_FUNCTION_CALL(ret2_plainVarScalarMult,
        pDomainParams->common.pPlainVarScalarMultFctFP->pScalarMultFct(
            session,
            &pDomainParams->common,
            ECC_S1,
            bitLenH,
            MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_OUTPUT));
        if(MCUXCLECC_STATUS_OK != ret2_plainVarScalarMult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
        }


        /*
        * Step 12b: Back up the coordinates of h*R' in buffers ECC_COORD25, ECC_COORD26 and ECC_COORD27.
        */

        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD25, ECC_COORD00, 0u);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD26, ECC_COORD01, 0u);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD27, ECC_COORD02, 0u);


        /*
        * Step 12c: Call function pDomainParams->pDecodePointFct to decode Renc and store the homogeneous coordinates of
        * the decoded point R in buffers ECC_COORD00, ECC_COORD01 and ECC_COORD02. If the decoding fails, return #MCUXCLECC_STATUS_INVALID_SIGNATURE.
        */

        MCUX_CSSL_FP_FUNCTION_CALL(ret2_decodePoint,
        pDomainParams->pDecodePointFct(
            pDomainParams,
            pSignature) );
        if(MCUXCLECC_STATUS_INVALID_PARAMS == ret2_decodePoint)
        {
            mcuxClSession_freeWords_pkcWa(session, pCpuWorkarea->wordNumPkcWa);
            MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, &pCpuWorkarea->pkcStateBackup,
                mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

            mcuxClSession_freeWords_cpuWa(session, pCpuWorkarea->wordNumCpuWa);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_INVALID_SIGNATURE,
                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,                        /* Clean up */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment),   /* Step 1 */
                MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET,        /* Step 3 */
                MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),            /* Step 4 */
                pDomainParams->common.pPlainFixScalarMultFctFP->scalarMultFct_FP_FuncId,
                3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,                      /* Step 5 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_PreHashMessage),     /* Step 6 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_CalcHashModN),
                pDomainParams->pDecodePoint_FP_FuncId,                          /* Step 7 */
                pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId, /* Step 8 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),                  /* Step 9 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),                  /* Step 10 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
                MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
                MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
                MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFER,              /* Step 11 */
                MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
                MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,                              /* Step 12a */
                MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST,
                pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId,
                3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,                      /* Step 12b */
                pDomainParams->pDecodePoint_FP_FuncId);                         /* Step 12c */
        }
        else if(MCUXCLECC_STATUS_OK != ret2_decodePoint)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }


        /*
        * Step 12d: Call function pDomainParameters->pPlainVarScalarMultFct to calculate h*R and store the result in
        * homogeneous coordinates in MR in buffers ECC_COORD00, ECC_COORD01 and ECC_COORD02.
        */

        MCUX_CSSL_FP_FUNCTION_CALL(ret3_plainVarScalarMult,
        pDomainParams->common.pPlainVarScalarMultFctFP->pScalarMultFct(
            session,
            &pDomainParams->common,
            ECC_S1,
            bitLenH,
            MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_OUTPUT));
        if(MCUXCLECC_STATUS_OK != ret3_plainVarScalarMult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
        }


        /*
        * Step 12e: Bring h*R' and h*R to the same Z-coordinate and compare the coordinates.
        * If the points are not equal, return #MCUXCLECC_STATUS_INVALID_SIGNATURE.
        */
        pOperands[ECC_V0] = pOperands[ECC_COORD25];
        pOperands[ECC_V1] = pOperands[ECC_COORD26];
        pOperands[ECC_V2] = pOperands[ECC_COORD27];
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_PointComparisonHom,
                            mcuxClEcc_FUP_PointComparisonHom_LEN);

        /* The last result is only zero if and only if R'=R */
        if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
        {
            mcuxClSession_freeWords_pkcWa(session, pCpuWorkarea->wordNumPkcWa);
            MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, &pCpuWorkarea->pkcStateBackup,
                mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

            mcuxClSession_freeWords_cpuWa(session, pCpuWorkarea->wordNumCpuWa);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_INVALID_SIGNATURE,
                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,                        /* Clean up */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment),   /* Step 1 */
                MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET,        /* Step 3 */
                MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),            /* Step 4 */
                pDomainParams->common.pPlainFixScalarMultFctFP->scalarMultFct_FP_FuncId,
                3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,                      /* Step 5 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_PreHashMessage),     /* Step 6 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_CalcHashModN),
                pDomainParams->pDecodePoint_FP_FuncId,                          /* Step 7 */
                pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId, /* Step 8 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),                  /* Step 9 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),                  /* Step 10 */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
                MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
                MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
                MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFER,              /* Step 11 */
                MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
                MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,                              /* Step 12a */
                MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST,
                pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId,
                3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,                      /* Step 12b */
                pDomainParams->pDecodePoint_FP_FuncId,                          /* Step 12c */
                pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId, /* Step 12d */
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));                 /* Step 12e */
        }

        MCUX_CSSL_FP_BRANCH_POSITIVE(RencNotEqual,
            /* Step 12a */
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST,
            pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId,
            /* Step 12b */
            3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
            /* Step 12c */
            pDomainParams->pDecodePoint_FP_FuncId,
            /* Step 12d */
            pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId,
            /* Step 12e */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    /*
     * Step 13: Return #MCUXCLECC_STATUS_OK.
     */

    /* Clean up and exit */
    mcuxClSession_freeWords_pkcWa(session, pCpuWorkarea->wordNumPkcWa);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(session, &pCpuWorkarea->pkcStateBackup,
        mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(session, pCpuWorkarea->wordNumCpuWa);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_EdDSA_VerifySignature_Core, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
        /* Step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment),
        /* Step 3 */
        MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFEROFFSET,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        /* Step 4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        pDomainParams->common.pPlainFixScalarMultFctFP->scalarMultFct_FP_FuncId,
        /* Step 5 */
        3u * MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        /* Step 6 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_PreHashMessage),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_CalcHashModN),
        /* Step 7 */
        pDomainParams->pDecodePoint_FP_FuncId,
        /* Step 8 */
        pDomainParams->common.pPlainVarScalarMultFctFP->scalarMultFct_FP_FuncId,
        /* Step 9 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        /* Step 10 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        /* Step 11 */
        MCUXCLPKC_FP_CALLED_IMPORTLITTLEENDIANTOPKC_BUFFER,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        /* Step 12 */
        MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(RencNotEqual, MCUXCLPKC_FLAG_ZERO != zeroFlag_check),
        /* Step 13 */
        MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_VerifySignature)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_VerifySignature(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_InputBuffer_t pSignature,
    uint32_t signatureSize )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_VerifySignature);

    /* Call core function to calculate EdDSA signature */
    MCUX_CSSL_FP_FUNCTION_CALL(verify_result, mcuxClEcc_EdDSA_VerifySignature_Core(
    /* mcuxClSession_Handle_t session:                           */ session,
    /* mcuxClKey_Handle_t key                                    */ key,
    /* const mcuxClEcc_EdDSA_SignatureProtocolDescriptor_t *mode */ mode,
    /* mcuxCl_InputBuffer_t pIn                                  */ pIn,
    /* uint32_t inSize                                          */ inSize,
    /* mcuxCl_InputBuffer_t pSignature                           */ pSignature,
    /* uint32_t pSignatureSize                                  */ signatureSize));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_EdDSA_VerifySignature, verify_result, MCUXCLECC_STATUS_FAULT_ATTACK,
                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_VerifySignature_Core));
}

