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
 * @file  mcuxClEcc_WeierECC_Internal_GenerateDomainParams.c
 * @brief ECC Weierstrass custom domain parameter generation function
 */


#include <mcuxClSession.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClEcc.h>
#include <mcuxClEcc_WeierECC.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_FP.h>
#include <internal/mcuxClEcc_WeierECC_Internal_GenerateDomainParams.h>
#include <internal/mcuxClEcc_WeierECC_Internal_GenerateDomainParams_FUP.h>
#include <internal/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_WeierECC_GenerateDomainParams)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_WeierECC_GenerateDomainParams(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_Weier_DomainParams_t *pEccWeierDomainParams,
    mcuxClEcc_Weier_BasicDomainParams_t *pEccWeierBasicDomainParams,
    uint32_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_WeierECC_GenerateDomainParams);

    /**********************************************************/
    /* Initialization and parameter verification              */
    /**********************************************************/

    /* Get CPU workarea pointers */
    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) (& pSession->cpuWa.buffer[pSession->cpuWa.used]);

    /* Set up the environment. This includes import/calculation of the full moduli p and n incl. their nDash values
     * as well as the calculation of R2P. */
    mcuxClEcc_DomainParam_t curveParam;
    curveParam.pA = pEccWeierBasicDomainParams->pA;
    curveParam.pB = pEccWeierBasicDomainParams->pB;
    curveParam.pP = pEccWeierBasicDomainParams->pP;
    curveParam.pG = pEccWeierBasicDomainParams->pG;
    curveParam.pN = pEccWeierBasicDomainParams->pN;
    curveParam.misc = mcuxClEcc_DomainParam_misc_Pack(pEccWeierBasicDomainParams->nLen, pEccWeierBasicDomainParams->pLen);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_SetupEnvironment,
        mcuxClEcc_Weier_SetupEnvironment(pSession,
                                        &curveParam,
                                        ECC_GENERATEDOMAINPARAMS_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_INVALID_PARAMS == ret_SetupEnvironment)
    {
        /* Session has been cleaned, PKC has been deinitialized in SetupEnvironment. */
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_INVALID_PARAMS, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment) );
    }

    MCUXCLECC_HANDLE_HW_UNAVAILABLE(ret_SetupEnvironment, mcuxClEcc_WeierECC_GenerateDomainParams);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();

    /* Calculate R3N, and then reduce R2N < N and R2P < P. */
    MCUXCLMATH_FP_QDASH(ECC_T3, ECC_NS, ECC_N, ECC_T0, (uint16_t) (2u * operandSize));
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_GenerateDomainParams_Reduce_R2N_R2P,
                        mcuxClEcc_FUP_GenerateDomainParams_Reduce_R2N_R2P_Len);

    const uint32_t byteLenP = pEccWeierBasicDomainParams->pLen;
    const uint32_t byteLenN = pEccWeierBasicDomainParams->nLen;

    /* Import the base point coordinates (x,y) to buffers (ECC_S0,ECC_S1). */
//  MCUXCLPKC_WAITFORFINISH();  <== unnecessary, because buffers ECC_S0/ECC_S1 and offsets ECC_VX0/ECC_VX1 are not used in the FUP, _Reduce_R2N_R2P.
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_S0, pEccWeierBasicDomainParams->pG, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_S1, pEccWeierBasicDomainParams->pG + byteLenP, byteLenP);

    /* Verify correctness of affine coordinates of G in NR. */
    pOperands[WEIER_VX0] = pOperands[ECC_S0];
    pOperands[WEIER_VY0] = pOperands[ECC_S1];
    MCUX_CSSL_FP_FUNCTION_CALL(pointCheckBasePointStatus, mcuxClEcc_PointCheckAffineNR());
    if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckBasePointStatus)
    {
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_INVALID_PARAMS, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUXCLECC_FP_WEIERECC_GENERATEDOMAINPARAMS_INIT_AND_VERIFY,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
    else if (MCUXCLECC_STATUS_OK != pointCheckBasePointStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }


    /**********************************************************/
    /* Optionally, generate the pre-computed point            */
    /**********************************************************/

    if (MCUXCLECC_OPTION_GENERATEPRECPOINT_YES == (options & MCUXCLECC_OPTION_GENERATEPRECPOINT_MASK))
    {
        /* Convert the affine base point coordinates (x,y) stored in ECC_S0 and ECC_S1 to
         * Jacobian coordinates (X:Y:Z=1) in MR and store them in buffers (WEIER_X0,WEIER_Y0,WEIER_Z).
         * Also initialize the relative Z-coordinate Z' as 1 in MR and store it in WEIER_ZA. */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_GenerateDomainParams_Convert_G_toJacMR,
                            mcuxClEcc_FUP_GenerateDomainParams_Convert_G_toJacMR_Len);

        /* Calculate prec point PrecG = 2^(byteLenN * 4) * G using function mcuxClEcc_RepeatPointDouble.
         * Input/output buffers of mcuxClEcc_RepeatPointDouble are set as follows:
         *
         * Input:
         *  - ECC_VX2, ECC_VY2, ECC_VZ is set to the Jacobian coordinates (X:Y:Z=1) of the base point in buffers (WEIER_X0,WEIER_Y0,WEIER_Z)
         *  - ECC_VZ2 is set to the relative Jacobian coordinate Z'=1 stored in WEIER_ZA
         * Output:
         *  - ECC_VX0, ECC_VY0, ECC_VZ0 are set to buffers (WEIER_XA,WEIER_YA,WEIER_ZA) to store the result precG in relative Jacobian coordinates
         * Temp:
         *  - ECC_VT is set to temp buffer ECC_S2
         *
         * NOTE: Since the input Z-coordinate is 1 in MR, the resulting relative Jacobian coordinate is in fact the Z-coordinate
         *       of the result. So, ECC_VX0, ECC_VY0, ECC_VZ0 will effectively contains Jacobian coordinates for precG. */
//      MCUXCLPKC_WAITFORREADY()  <== unnecessary, because VX0/VY0/VZ0/VZ/VX2/VY2/VZ2 are not used in the FUP program before.
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_XA, WEIER_YA);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VZ0, WEIER_VZ,  WEIER_ZA, WEIER_Z);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX2, WEIER_VY2, WEIER_X0, WEIER_Y0);
        pOperands[WEIER_VZ2] = pOperands[WEIER_ZA];
        pOperands[WEIER_VT] = pOperands[ECC_S2];

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEcc_RepeatPointDouble((byteLenN * 8u) / 2u));

        /* Convert precG to affine coordinates in NR and store them in (WEIER_X0,WEIER_Y0). */
        MCUXCLMATH_FP_MODINV(ECC_T0, WEIER_ZA, ECC_P, ECC_T1);
        /* MISRA Ex. 22, while(0) is allowed */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_ConvertJacToAffine,
                            mcuxClEcc_FUP_Weier_ConvertJacToAffine_LEN);
    }
    else if (MCUXCLECC_OPTION_GENERATEPRECPOINT_NO != (options & MCUXCLECC_OPTION_GENERATEPRECPOINT_MASK))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }


    /**********************************************************/
    /* Initialize optimized domain parameters struct at the   */
    /* start of target memory area                            */
    /**********************************************************/

    /* Interpret start of memory area pEccWeierDomainParams as struct of type mcuxClEcc_Weier_DomainParams_t */
    mcuxClEcc_Weier_DomainParams_t *pDomainParams = (mcuxClEcc_Weier_DomainParams_t *) pEccWeierDomainParams;

    /* Initialize pointers to where the domain parameters shall be stored */
    uint8_t *pDomainParamBuffers = (uint8_t *) pEccWeierDomainParams + sizeof(mcuxClEcc_Weier_DomainParams_t);
    pDomainParams->common.pFullModulusP = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_PFULL;
    pDomainParams->common.pFullModulusN = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_NFULL(byteLenP);
    pDomainParams->common.pR2P = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_R2P(byteLenP, byteLenN);
    pDomainParams->common.pR2N = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_R2N(byteLenP, byteLenN);
    pDomainParams->common.pCurveParam1 = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_CP1(byteLenP, byteLenN);
    pDomainParams->common.pCurveParam2 = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_CP2(byteLenP, byteLenN);
    pDomainParams->common.pGx = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_GX(byteLenP, byteLenN);
    pDomainParams->common.pGy = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_GY(byteLenP, byteLenN);
    pDomainParams->common.pPrecPoints = pDomainParamBuffers + MCUXCLECC_CUSTOMPARAMS_OFFSET_PP(byteLenP, byteLenN);


    /**********************************************************/
    /* Fill optimized domain parameters                       */
    /**********************************************************/

    /* Initialize lengths and function pointers in optimized domain parameter struct */
    pDomainParams->common.byteLenP = (uint16_t) byteLenP;
    pDomainParams->common.byteLenN = (uint16_t) byteLenN;
    pDomainParams->common.pSecFixScalarMultFctFP = NULL;
    pDomainParams->common.pSecVarScalarMultFctFP = NULL;
    pDomainParams->common.pPlainFixScalarMultFctFP = NULL;
    pDomainParams->common.pPlainVarScalarMultFctFP = NULL;

    /* Export full moduli for p and n to optimized domain parameter struct. */
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pFullModulusP, ECC_PFULL, byteLenP + MCUXCLPKC_WORDSIZE);
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pFullModulusN, ECC_NFULL, byteLenN + MCUXCLPKC_WORDSIZE);

    /* Export Montgomery parameters R2P and R2N to optimized domain parameter struct. */
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pR2P, ECC_PQSQR, byteLenP);
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pR2N, ECC_NQSQR, byteLenN);

    /* Copy domain parameters a and b to optimized domain parameter struct.
     *
     * NOTE: This is done in two steps via imports to/exports from the PKC RAM
     *       because no ordinary memory copy with endianess reversal exists. */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pEccWeierBasicDomainParams->pA, byteLenP);
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pCurveParam1, ECC_T0, byteLenP);
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pCurveParam2, WEIER_B, byteLenP);

    /* Export base point coordinates to optimized domain parameter struct. */
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pGx, ECC_S0, byteLenP);
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pGy, ECC_S1, byteLenP);

    if(MCUXCLECC_OPTION_GENERATEPRECPOINT_YES == (options & MCUXCLECC_OPTION_GENERATEPRECPOINT_MASK))
    {
        /* Optionally, export prec point coordinates to optimized domain parameter struct. */
        MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pPrecPoints, WEIER_X0, byteLenP);
        MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pDomainParams->common.pPrecPoints + byteLenP, WEIER_Y0, byteLenP);
    }
    else if (MCUXCLECC_OPTION_GENERATEPRECPOINT_NO != (options & MCUXCLECC_OPTION_GENERATEPRECPOINT_MASK))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }


    /**********************************************************/
    /* Clean up                                               */
    /**********************************************************/
    mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
        mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_WeierECC_GenerateDomainParams, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
        MCUXCLECC_FP_WEIERECC_GENERATEDOMAINPARAMS_FINAL(options));
}
