/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>
#include <mcuxClEcc_MemoryConsumption.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslMemory.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClEcc_Mont_Internal.h>
#include <internal/mcuxClPkc_Macros.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhKeyAgreement)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhKeyAgreement(
                    mcuxClSession_Handle_t pSession,
                    mcuxClKey_Handle_t key,
                    mcuxClKey_Handle_t otherKey,
                    uint8_t * pOut,
                    uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhKeyAgreement);

    mcuxClKey_Descriptor_t * pKey = (mcuxClKey_Descriptor_t *)key;
    mcuxClKey_Descriptor_t * pOtherKey = (mcuxClKey_Descriptor_t *)otherKey;

    if(((MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_PRIVATE_KEY) != mcuxClKey_getAlgoId(pKey)) || (MCUXCLKEY_SIZE_NOTUSED != mcuxClKey_getSize(pKey))
    ||((MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_PUBLIC_KEY) != mcuxClKey_getAlgoId(pOtherKey)) || (MCUXCLKEY_SIZE_NOTUSED != mcuxClKey_getSize(pOtherKey))
    )
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Set up the environment */
    mcuxClEcc_MontDH_DomainParams_t *pDomainParameters = (mcuxClEcc_MontDH_DomainParams_t *)mcuxClKey_getTypeInfo(pKey);
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParameters = &(pDomainParameters->common);

    /* For Curve25519 and Curve448, private and public keys have the same length as the prime p */
    uint16_t keyLen = pCommonDomainParameters->byteLenP;

    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(pSession, 0u);
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_MontDH_SetupEnvironment, mcuxClEcc_MontDH_SetupEnvironment(pSession,
                                                                 pDomainParameters,
                                                                 ECC_MONTDH_NO_OF_BUFFERS));
    if(MCUXCLECC_STATUS_OK != retCode_MontDH_SetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retCode_MontDH_SetupEnvironment, mcuxClEcc_Mont_DhKeyAgreement);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Securely import private key d to PKC buffer ECC_S2 */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_importPrivKey, mcuxClPkc_SecureImportLittleEndianToPkc(ECC_S2, mcuxClKey_getKeyData(pKey), keyLen));

    /* Check the return code of mcuxClPkc_SecureImportLittleEndianToPkc */
    if(MCUXCLPKC_STATUS_OK != retCode_importPrivKey)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Call mcuxClEcc_Mont_DhX to calculate the public key q=MontDhX(d,Gx) and store it in buffer MONT_X0. If the function returns NEUTRAL_POINT, return MCUXCLECC_STATUS_FAULT_ATTACK */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_Mont_Dhx, mcuxClEcc_MontDH_X(pSession, pDomainParameters, mcuxClKey_getKeyData(pOtherKey)));

    if(MCUXCLECC_STATUS_RNG_ERROR == retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_ERROR_SMALL_SUBGROUP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_SetupEnvironment),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportLittleEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_X)
        );
    }
    else
    {
        /* Securely export shared secret from MONT_X0 */
        MCUX_CSSL_FP_FUNCTION_CALL(retCode_exportSS, mcuxClPkc_SecureExportLittleEndianFromPkc(pOut, MONT_X0, keyLen));

        /* Check the return code of mcuxClPkc_SecureExportLittleEndianFromPkc */
        if(MCUXCLPKC_STATUS_OK != retCode_exportSS)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        *pOutLength = keyLen;

        /* Return OK and exit */
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_Mont_DhKeyAgreement, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_SetupEnvironment),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportLittleEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_X),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportLittleEndianFromPkc),
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
}
