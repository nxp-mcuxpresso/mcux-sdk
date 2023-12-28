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
 * @file  mcuxClEcc_EdDSA_GenerateKeyPair.c
 * @brief Implementation of EdDSA key pair generation functionality
 */


#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClKey.h>
#include <mcuxClPkc.h>
#include <mcuxClMemory.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_Random.h>
#include <internal/mcuxClEcc_EdDSA_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_Hash.h>
#include <internal/mcuxClEcc_EdDSA_GenerateKeyPair_FUP.h>


#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
#define MCUXCLECC_FP_GENKEYPAIR_SECSTRENGTH  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength)
#else
#define MCUXCLECC_FP_GENKEYPAIR_SECSTRENGTH  (0u)
#endif


MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_EdDSA_GenerateKeyPair_Core)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateKeyPair_Core(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
);
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_GenerateKeyPair_Core)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateKeyPair_Core(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_GenerateKeyPair_Core);

    /*
     * Step 1: Set up the environment
     */

    /* Verify that the key handles are correctly initialized for the EdDSA use case */
    if((MCUXCLKEY_ALGO_ID_ECC_EDDSA != mcuxClKey_getAlgorithm(privKey))
            || (MCUXCLKEY_ALGO_ID_ECC_EDDSA != mcuxClKey_getAlgorithm(pubKey))
            || (mcuxClKey_getTypeInfo(privKey) != mcuxClKey_getTypeInfo(pubKey))
            || (MCUXCLKEY_ALGO_ID_PRIVATE_KEY != mcuxClKey_getKeyUsage(privKey))
            || (MCUXCLKEY_ALGO_ID_PUBLIC_KEY != mcuxClKey_getKeyUsage(pubKey)) )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_INVALID_PARAMS, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory")
    mcuxClEcc_CpuWa_t * const pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(pSession, 0u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    mcuxClEcc_EdDSA_DomainParams_t * const pDomainParams = (mcuxClEcc_EdDSA_DomainParams_t *) (privKey->type.info);

    MCUX_CSSL_FP_FUNCTION_CALL(retSetupEnvironment,
        mcuxClEcc_EdDSA_SetupEnvironment(pSession,
                                        pDomainParams,
                                        ECC_EDDSA_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_OK != retSetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retSetupEnvironment, mcuxClEcc_EdDSA_GenerateKeyPair_Core);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* private and public key length = M = 32-byte for Ed25519 (b = 256 = 32*8) */
    /*                                  or 57-byte for Ed448 (b = 456 = 57*8).  */
    const uint32_t keyLength = (uint32_t) pDomainParams->b / 8u;
    uint8_t * pPrivKey = NULL;


    /*
     * Step 2: Determine whether the private key is passed to the function or needs to be generated. In the latter case, generate the private key d.
     */
    uint32_t options = mode->options;
    uint8_t *pPrivData = privKey->container.pData;
    MCUX_CSSL_FP_BRANCH_DECL(privKeyOption);
    if (MCUXCLECC_EDDSA_PRIVKEY_GENERATE == options)
    {
        /* Derive the security strength required for the RNG from (keyLength * 8) / 2 and check whether it can be provided. */
#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
        MCUX_CSSL_FP_FUNCTION_CALL(ret_checkSecurityStrength, mcuxClRandom_checkSecurityStrength(pSession, (keyLength * 8u) / 2u));
        if (MCUXCLRANDOM_STATUS_OK != ret_checkSecurityStrength)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_RNG_ERROR);
        }
#endif
        /* Reserve space on CPU workarea for the private key. */
        const uint32_t privKeyWords = MCUXCLECC_ALIGNED_SIZE(keyLength) / (sizeof(uint32_t));
        pPrivKey = (uint8_t *) mcuxClSession_allocateWords_cpuWa(pSession, privKeyWords);
        pCpuWorkarea->wordNumCpuWa += privKeyWords;

        MCUX_CSSL_FP_FUNCTION_CALL(retRandom, mcuxClRandom_generate(pSession, pPrivKey, keyLength) );

        if (MCUXCLRANDOM_STATUS_OK != retRandom)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_RNG_ERROR);
        }

        MCUX_CSSL_FP_BRANCH_POSITIVE(privKeyOption,
                                                   MCUXCLECC_FP_GENKEYPAIR_SECSTRENGTH,
                                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) );
    }
    else if (MCUXCLECC_EDDSA_PRIVKEY_INPUT == options)
    {
        pPrivKey = mode->pPrivKeyInput;
        if(NULL == pPrivKey)
        {
            /* Invalid mode passed */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUX_CSSL_FP_BRANCH_NEGATIVE(privKeyOption);
    }
    else
    {
        /* invalid option */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /*
     * Step 3: Hash the private key using the hash function specified in the EdDSA domain parameters and store
     *         the hash result (h_0,...,h_{2b-1}) in buffers ECC_T2 and ECC_S3 with offset such that the second half
     *         (h_b,...,h_{2b-1}) is stored at the beginning of ECC_S3.
     */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pS3 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]);
    uint8_t *pPrivKeyHashPkc = pS3 - keyLength;

    /* Calculate 2b-bit hash of private key. */
    MCUXCLECC_FP_EDDSA_KEYGEN_HASH_PRIVKEY(pSession,
                                          pDomainParams->algoHash,
                                          pPrivKey, pPrivKeyHashPkc,
                                          keyLength);


    /*
     * Step 4: Derive the secret scalar s from the first half (h_b,..,h_{2b-1}) of the private key hash and store it in buffer ECC_S2.
     */

    /* The bits 0~(b-1) of private key hash is placed before and adjacent to PKC operand S3. */
    const uint32_t b = pDomainParams->b;  /* = 256 (Ed25519); 456 (Ed448) */
    const uint32_t c = pDomainParams->c;  /* =   3 (Ed25519);   2 (Ed448) */
    const uint32_t t = pDomainParams->t;  /* = 254 (Ed25519); 447 (Ed448) */
    const uint32_t offsetS3 = (uint32_t) pOperands[ECC_S3];
    /* V0 = PKC operand containing the first half of private key hash.       */
    /* V1 = V0 for Ed25519 (64/128-bit PkcWord) and Ed448 (128-bit PkcWord); */
    /*    = V0 + 64-bit for Ed448 (64-bit PkcWord).                          */
    /* ps, PKC will ignore non-aligned part of offsets.                      */
    pOperands[ECC_V0] = (uint16_t) (offsetS3 - (b/8u));
    pOperands[ECC_V1] = (uint16_t) (offsetS3 - (t/8u));
    /* V2/V3/V4 are shift/rotate amounts used in FUP program below. */
    /* V2 = 2 (Ed25519); 9 (Ed448). */
    /* V3 = -252 \equiv  4 (Ed25519);                */
    /*      -446 \equiv  2 (Ed448, 64-bit PkcWord)   */
    /*               or 66 (Ed448, 128-bit PkcWord). */
    pOperands[ECC_V2] = (uint16_t) (b - t);
    pOperands[ECC_V3] = (uint16_t) (c - 1u - t);
    pOperands[ECC_V4] = (uint16_t) c;
    uint32_t keyLengthPkc = MCUXCLPKC_ROUNDUP_SIZE(keyLength);
    MCUXCLPKC_PS2_SETLENGTH(0u, keyLengthPkc);
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S,
                        mcuxClEcc_FUP_EdDSA_GenerateKeyPair_Prepare_S_LEN);


    /*
     * Step 5: Perform a blinded scalar multiplication Q = s*G and store the resulting point in encoded form Q_enc in buffer ECC_COORD02.
     */

    /* Call the BlindedScalarMult function.
     * If the function returns OK, ECC_COORD00 and ECC_COORD01 contain the affine x- and y-coordinates of Q.
     * If the function returns NEUTRAL_POINT, ECC_COORD00 and ECC_COORD01 are set to the coordinates of the neutral point (0,1). */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_BlindedScalarMult, mcuxClEcc_BlindedScalarMult(pSession, (mcuxClEcc_CommonDomainParams_t *) &pDomainParams->common) );
    if (MCUXCLECC_STATUS_RNG_ERROR == ret_BlindedScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if (MCUXCLECC_STATUS_NEUTRAL_POINT == ret_BlindedScalarMult)
    {
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_COORD00, 0u);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_COORD01, 0u);
        MCUXCLPKC_FP_CALC_OP1_ADD_CONST(ECC_COORD01, ECC_COORD01, 1u);
    }
    else if (MCUXCLECC_STATUS_OK != ret_BlindedScalarMult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    /* Derive the encoding Q_enc of Q and store it in buffer ECC_COORD02.
     *
     * NOTE: PS2 lengths are still set to (0u, keyLengthPkc) */
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_COORD02, 0u);                    /* Clear keyLengthPkc bytes of buffer ECC_COORD02 */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_COORD02, ECC_COORD01, 0u);    /* Copy operandSize < keyLengthPkc bytes of the y-coordinate from ECC_COORD01 to ECC_COORD02 */
    uint8_t *pQX = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_COORD00]);
    uint8_t *pQEncLsbXByte = &MCUXCLPKC_OFFSET2PTR(pOperands[ECC_COORD02])[keyLength - 1u];
    MCUXCLPKC_WAITFORFINISH();
    uint8_t lsbX = (*pQX) & 0x01u;
    *pQEncLsbXByte |= (lsbX << 7u);


    /*
     * Step 6: (Securely) copy the key data to the key handles and link the key pair.
     */
    // TODO: Is this copy function secure enough?
    MCUXCLMEMORY_FP_MEMORY_COPY(pPrivData, pPrivKey, keyLength);


    /* Securely export the scalar s from PKC buffer ECC_S2. */
    const uint32_t scalarSLength = (t + 7u) >> 3u;
    MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportScalarS, mcuxClPkc_SecureExportLittleEndianFromPkc((uint8_t *) &pPrivData[keyLength], ECC_S2, scalarSLength));
    if (MCUXCLPKC_STATUS_OK != ret_SecExportScalarS)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Securely export the private key hash (h_b,...,h_{2b-1}) from PKC buffer ECC_S3. */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportHash, mcuxClPkc_SecureExportLittleEndianFromPkc((uint8_t *) &pPrivData[keyLength + scalarSLength], ECC_S3, keyLength));
    if (MCUXCLPKC_STATUS_OK != ret_SecExportHash)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Export the public key to the public key handle. */
    MCUXCLPKC_FP_EXPORTLITTLEENDIANFROMPKC(pubKey->container.pData, ECC_COORD02, keyLength);

    /* Create link between private and public key handles */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_linkKeyPair, mcuxClKey_linkKeyPair(pSession, privKey, pubKey));
    if (MCUXCLKEY_STATUS_OK != ret_linkKeyPair)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /* Clean up and exit */
    mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
        mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_EdDSA_GenerateKeyPair_Core, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
        /* Step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_SetupEnvironment),
        /* Step 2 */
        MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(privKeyOption, MCUXCLECC_EDDSA_PRIVKEY_GENERATE == options),
        MCUX_CSSL_FP_BRANCH_TAKEN_NEGATIVE(privKeyOption, MCUXCLECC_EDDSA_PRIVKEY_INPUT == options),
        /* Step 3 */
        MCUXCLECC_FP_CALLED_EDDSA_KEYGEN_HASH_PRIVKEY,
        /* Step 4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        /* Step 5 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_BlindedScalarMult),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLECC_STATUS_NEUTRAL_POINT == ret_BlindedScalarMult),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST),
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        /* Step 6 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportLittleEndianFromPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportLittleEndianFromPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportLittleEndianFromPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_linkKeyPair),
        /* Step 7 */
        MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_GenerateKeyPair)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_GenerateKeyPair(
    mcuxClSession_Handle_t pSession,
    const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_GenerateKeyPair);

    /* Call core function to calculate EdDSA signature */
    MCUX_CSSL_FP_FUNCTION_CALL(keygen_result, mcuxClEcc_EdDSA_GenerateKeyPair_Core(
    /* mcuxClSession_Handle_t pSession:                          */ pSession,
    /* const mcuxClEcc_EdDSA_GenerateKeyPairDescriptor_t *mode   */ mode,
    /* mcuxClKey_Handle_t privKey                                */ privKey,
    /* mcuxClKey_Handle_t privKey                                */ pubKey));

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_EdDSA_GenerateKeyPair, keygen_result, MCUXCLECC_STATUS_FAULT_ATTACK,
                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_EdDSA_GenerateKeyPair_Core));
}
