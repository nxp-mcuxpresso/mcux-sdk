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
 * @file  mcuxClEcc_Mont_DhKeyAgreement.c
 * @brief mcuxClEcc: implementation of MontDh key agreement function acc to rfc 7748
 */

#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>
#include <mcuxClEcc_MemoryConsumption.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslMemory.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <internal/mcuxClEcc_Mont_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhKeyAgreement)
mcuxClEcc_Status_Protected_t mcuxClEcc_Mont_DhKeyAgreement(
                    mcuxClSession_Handle_t session,
                    mcuxClKey_Handle_t key,
                    mcuxClKey_Handle_t otherKey,
                    uint8_t * pOut,
                    uint32_t * const pOutSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhKeyAgreement);

    mcuxClKey_Descriptor_t * pKey = (mcuxClKey_Descriptor_t *)key;
    mcuxClKey_Descriptor_t * pOtherKey = (mcuxClKey_Descriptor_t *)otherKey;

	uint32_t backup_cpuWaUsed = session->cpuWa.used;
	uint32_t backup_pkcWaUsed = session->pkcWa.used;

    if(((MCUXCLKEY_ALGO_ID_ECC_MONT_GFP | MCUXCLKEY_ALGO_ID_PRIVATE_KEY) != pKey->type.algoId) || (MCUXCLKEY_SIZE_NOTUSED != pKey->type.size)
    ||((MCUXCLKEY_ALGO_ID_ECC_MONT_GFP | MCUXCLKEY_ALGO_ID_PUBLIC_KEY) != pOtherKey->type.algoId) || (MCUXCLKEY_SIZE_NOTUSED != pOtherKey->type.size)
    )
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    mcuxClEcc_Mont_DomainParams_t *pDomainParameters = (mcuxClEcc_Mont_DomainParams_t *)(pKey->type.info);
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParameters = &(pDomainParameters->common);

    if(MCUXCLECC_CURVEID_MONT_X25519 != pCommonDomainParameters->curveID)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    uint16_t keyLen = pCommonDomainParameters->byteLenP;

    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) (& session->cpuWa.buffer[session->cpuWa.used]);

    MCUX_CSSL_FP_FUNCTION_CALL(retCode_Mont_DhSetupEnvironment, mcuxClEcc_Mont_DhSetupEnvironment(session,
                                                                 pDomainParameters,
                                                                 ECC_MONTDH_NO_OF_BUFFERS));
    if(MCUXCLECC_STATUS_OK != retCode_Mont_DhSetupEnvironment)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    mcuxClPkc_State_t *pPkcStateBackup = &pCpuWorkarea->pkcStateBackup;

	uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(retCode_importPrivKey, mcuxCsslMemory_Copy(
                                mcuxCsslParamIntegrity_Protect(4u, pKey->pSrcKeyData, MCUXCLPKC_OFFSET2PTR((pOperands)[ECC_S2]), keyLen, keyLen),
                                pKey->pSrcKeyData,
                                MCUXCLPKC_OFFSET2PTR((pOperands)[ECC_S2]),
                                keyLen,
                                keyLen));

    if(MCUXCSSLMEMORY_COPY_SUCCESS != retCode_importPrivKey)
    {

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(retCode_Mont_Dhx, mcuxClEcc_Mont_DhX(session, pDomainParameters, pOtherKey->pSrcKeyData));
    if(MCUXCLECC_STATUS_MONT_RNG_ERROR == retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_MONT_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_ERROR_SMALL_SUBGROUP,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhSetupEnvironment),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhX)
        );
    }
    else
    {

        MCUXCLPKC_WAITFORFINISH();
        MCUX_CSSL_FP_FUNCTION_CALL(retCode_exportSS, mcuxCsslMemory_Copy(
                                    mcuxCsslParamIntegrity_Protect(4u, MCUXCLPKC_OFFSET2PTR((pOperands)[MONT_X0]), pOut, keyLen, keyLen),
                                    MCUXCLPKC_OFFSET2PTR((pOperands)[MONT_X0]),
                                    pOut,
                                    keyLen,
                                    keyLen));

        if(MCUXCSSLMEMORY_COPY_SUCCESS != retCode_exportSS)
        {

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        (*pOutSize) = keyLen;

        MCUXCLPKC_FP_DEINITIALIZE(pPkcStateBackup);
        session->pkcWa.used = backup_pkcWaUsed;
        session->cpuWa.used = backup_cpuWaUsed;

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_MONT_DHKEYAGREEMENT_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhSetupEnvironment),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhX),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize)
            );
    }
}
