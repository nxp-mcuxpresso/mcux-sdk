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
 * @file  mcuxClEcc_Mont_DhKeyGeneration.c
 * @brief mcuxClEcc: implementation of MontDh key generation function
 */


#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClEcc.h>
#include <mcuxClEcc_MemoryConsumption.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxClKey.h>
#include <mcuxClRandom.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClEcc_Internal_Random.h>
#include <internal/mcuxClEcc_Mont_Internal.h>


#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
#define MCUXCLECC_FP_MONT_DHKEYGEN_SECSTRENGTH  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength)
#else
#define MCUXCLECC_FP_MONT_DHKEYGEN_SECSTRENGTH  (0u)
#endif

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhKeyGeneration)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhKeyGeneration(
                        mcuxClSession_Handle_t pSession,
                        mcuxClKey_Type_t type,
                        mcuxClKey_Protection_t protection,
                        mcuxClKey_Handle_t privKey,
                        uint8_t * pPrivData,
                        uint32_t * const pPrivDataLength,
                        mcuxClKey_Handle_t pubKey,
                        uint8_t * pPubData,
                        uint32_t * const pPubDataLength
                        )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhKeyGeneration);

    mcuxClKey_Descriptor_t * pPrivKey = (mcuxClKey_Descriptor_t *)privKey;
    mcuxClKey_Descriptor_t * pPubKey = (mcuxClKey_Descriptor_t *)pubKey;

    if(   ((MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR) != type->algoId)
       || (MCUXCLKEY_SIZE_NOTUSED != type->size) )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    /* Set up the environment */
    mcuxClEcc_MontDH_DomainParams_t *pDomainParameters = (mcuxClEcc_MontDH_DomainParams_t *)(type->info);
    mcuxClEcc_CommonDomainParams_t *pCommonDomainParameters = (mcuxClEcc_CommonDomainParams_t *)&(pDomainParameters->common);

    /* For Curve25519 and Curve448, private and public keys have the same length as the prime p */
    uint16_t keyLen = pCommonDomainParameters->byteLenP;

    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(pSession, 0u);
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_MontDH_SetupEnvironment, mcuxClEcc_MontDH_SetupEnvironment(pSession,
                                                                 pDomainParameters,
                                                                 ECC_MONTDH_NO_OF_BUFFERS));
    if(MCUXCLECC_STATUS_OK != retCode_MontDH_SetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retCode_MontDH_SetupEnvironment, mcuxClEcc_Mont_DhKeyGeneration);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();

    /* Generate a M byte random private key d using the DRBG and store it in PKC buffer ECC_S2, M equals to dp->nLen */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    uint8_t * ptrS2 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]);

    /* Derive the security strength required for the RNG from bitLenN/2 and check whether it can be provided. */
#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
    MCUX_CSSL_FP_FUNCTION_CALL(ret_checkSecurityStrength, mcuxClRandom_checkSecurityStrength(pSession, ((uint32_t) pCommonDomainParameters->byteLenN * 8u) / 2u));
    if (MCUXCLRANDOM_STATUS_OK != ret_checkSecurityStrength)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_SetupEnvironment),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength) );
    }
#endif

    MCUXCLECC_FP_RANDOM_HQRNG_PKCWA(mcuxClEcc_Mont_DhKeyGeneration, pSession, ptrS2, keyLen);

    /* Call mcuxClEcc_MontDH_X to calculate the public key q=MontDhX(d,Gx) and store it in buffer MONT_X0. If the function returns NEUTRAL_POINT, return MCUXCLECC_STATUS_FAULT_ATTACK */
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_Mont_Dhx, mcuxClEcc_MontDH_X(pSession, pDomainParameters, pDomainParameters->common.pGx));

    if(MCUXCLECC_STATUS_RNG_ERROR == retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_SetupEnvironment),
            MCUXCLECC_FP_MONT_DHKEYGEN_SECSTRENGTH,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_X));
    }
    else if(MCUXCLECC_STATUS_OK != retCode_Mont_Dhx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Securely export the private key d from PKC buffer ECC_S2 and export the public key q from MONT_X0 */
        MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExport, mcuxClPkc_SecureExportLittleEndianFromPkc(pPrivData, ECC_S2, keyLen));
        if (MCUXCLPKC_STATUS_OK != ret_SecExport)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Export x-coordinate of the public key in Little Endian */
        MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pPubData, MONT_X0, keyLen);

        /* Fill key_handle_t structures */
        mcuxClKey_TypeDescriptor_t keyType_private = { type->algoId ^ MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PRIVATE_KEY,
                                                      type->size, type->info }; // TODO CLNS-5165: move the generation of these types into the key component
        mcuxClKey_setTypeDescriptor(pPrivKey, keyType_private);
        mcuxClKey_setProtectionType(pPrivKey, protection);
        mcuxClKey_setKeyData(pPrivKey, pPrivData);

        mcuxClKey_TypeDescriptor_t keyType_public = { type->algoId ^ MCUXCLKEY_ALGO_ID_KEY_PAIR ^ MCUXCLKEY_ALGO_ID_PUBLIC_KEY,
                                                     type->size, type->info }; // TODO CLNS-5165: move the generation of these types into the key component
        mcuxClKey_setTypeDescriptor(pPubKey, keyType_public);
        mcuxClKey_setProtectionType(pPubKey, protection);
        mcuxClKey_setKeyData(pPubKey, pPubData);

        *(pPrivDataLength) = keyLen;
        *(pPubDataLength) = keyLen;

        /* Create link between private and public key handles */
        MCUX_CSSL_FP_FUNCTION_CALL(ret_linkKeyPair, mcuxClKey_linkKeyPair(pSession, privKey, pubKey));
        if (MCUXCLKEY_STATUS_OK != ret_linkKeyPair)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Return OK and exit */
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_Mont_DhKeyGeneration, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_SetupEnvironment),
            MCUXCLECC_FP_MONT_DHKEYGEN_SECSTRENGTH,
            MCUXCLECC_FP_CALLED_RANDOM_HQRNG_PKCWA,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_X),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportLittleEndianFromPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_linkKeyPair),
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
}
