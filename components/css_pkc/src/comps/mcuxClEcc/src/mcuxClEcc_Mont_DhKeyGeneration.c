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
 * @file  mcuxClEcc_Mont_DhKeyGeneration.c
 * @brief mcuxClEcc: implementation of MontDh key generation function
 */

#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>
#include <mcuxClEcc_MemoryConsumption.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxClKey.h>

#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClEcc_Mont_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhKeyGeneration)
mcuxClEcc_Status_Protected_t mcuxClEcc_Mont_DhKeyGeneration(
                        mcuxClSession_Handle_t session,
                        mcuxClKey_Type_t type,
                        mcuxClKey_Protection_t protection,
                        mcuxClKey_Handle_t privKey,
                        uint8_t * pPrivData,
                        uint32_t * const pPrivDataSize,
                        mcuxClKey_Handle_t pubKey,
                        uint8_t * pPubData,
                        uint32_t * const pPubDataSize
                        )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhKeyGeneration);

    mcuxClKey_Descriptor_t * pPrivKey = (mcuxClKey_Descriptor_t *)privKey;
    mcuxClKey_Descriptor_t * pPubKey = (mcuxClKey_Descriptor_t *)pubKey;

	uint32_t backup_cpuWaUsed = session->cpuWa.used;
	uint32_t backup_pkcWaUsed = session->pkcWa.used;

    if((MCUXCLKEY_ALGO_ID_ECC_MONT_GFP | MCUXCLKEY_ALGO_ID_KEY_PAIR) != type.algoId || MCUXCLKEY_SIZE_NOTUSED != type.size)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    mcuxClEcc_Mont_DomainParams_t *pDomainParameters = (mcuxClEcc_Mont_DomainParams_t *)(type.info);
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParameters = (mcuxClEcc_CommonDomainParams_t *)&(pDomainParameters->common);

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
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    mcuxClPkc_State_t *pPkcStateBackup = &pCpuWorkarea->pkcStateBackup;

    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint8_t * ptrS2 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]);

	MCUX_CSSL_FP_FUNCTION_CALL(retCode_Drbg_GetRandom, mcuxClCss_Rng_DrbgRequest_Async(ptrS2, keyLen));
	if(MCUXCLCSS_STATUS_OK_WAIT != retCode_Drbg_GetRandom)
	{
		MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_MONT_RNG_ERROR);
	}
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_WaitForOperation, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

	if(MCUXCLCSS_STATUS_OK != retCode_WaitForOperation)
	{
		MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_MONT_RNG_ERROR);
	}

    MCUX_CSSL_FP_FUNCTION_CALL(retCode_Mont_Dhx, mcuxClEcc_Mont_DhX(session, pDomainParameters, pDomainParameters->pGx));
    if(MCUXCLECC_STATUS_MONT_RNG_ERROR == retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_MONT_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        MCUXCLPKC_WAITFORFINISH();

        MCUX_CSSL_FP_FUNCTION_CALL(retCode_exportPrivKey, mcuxCsslMemory_Copy(
                                    mcuxCsslParamIntegrity_Protect(4u, MCUXCLPKC_OFFSET2PTR((pOperands)[ECC_S2]), pPrivData, keyLen, keyLen),
                                    MCUXCLPKC_OFFSET2PTR((pOperands)[ECC_S2]),
                                    pPrivData,
                                    keyLen,
                                    keyLen));

        if(MCUXCSSLMEMORY_COPY_SUCCESS != retCode_exportPrivKey)
        {

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ret_ExportPubKey, mcuxClMemory_copy(pPubData, MCUXCLPKC_OFFSET2PTR((pOperands)[MONT_X0]), keyLen, keyLen));
        (void) ret_ExportPubKey;

        pPrivKey->type = type;
        pPrivKey->type.algoId ^= (MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PRIVATE_KEY);
        pPrivKey->protection = &protection;
        pPrivKey->pSrcKeyData = pPrivData;

        pPubKey->type = type;
        pPubKey->type.algoId ^= (MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PUBLIC_KEY);
        pPubKey->protection = &protection;
        pPubKey->pSrcKeyData = pPubData;

        *(pPrivDataSize) = keyLen;
        *(pPubDataSize) = keyLen;

        MCUXCLPKC_FP_DEINITIALIZE(pPkcStateBackup);
        session->pkcWa.used = backup_pkcWaUsed;
        session->cpuWa.used = backup_cpuWaUsed;

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_MONT_DHKEYGENERATION_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhSetupEnvironment),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Rng_DrbgRequest_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhX),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize)
            );
    }
}
