/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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
 * @file  mcuxClEcc_DeterministicECDSA_Internal_BlindedSecretKeyGen.c
 * @brief Internal function for generating the deterministic ephemeral key for deterministic ECDSA in a blinded way.
 */

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClHashModes.h>
#include <mcuxClRandomModes.h>
#include <mcuxClRandom.h>
#include <mcuxClHmac.h>
#include <mcuxClMath.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClRandomModes_Internal_HmacDrbg_Functions.h>
#include <internal/mcuxClHmac_Internal_Memory.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClMemory_Internal.h>
#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_Operations.h>

#include <internal/mcuxClEcc_ECDSA_Internal.h>
#include <internal/mcuxClEcc_ECDSA_Internal_FUP.h>

#include <mcuxClCore_Macros.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen(
    mcuxClSession_Handle_t pSession,
    uint32_t nByteLength,
    const mcuxClEcc_Sign_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();

    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;

    /* Reserve space for Random mode descriptors to be created:
     *  - one for an HMAC_DRBG in normal mode associated to the given HMAC mode
     *  - one for an associated HMAC_DRBG in test mode which allows to initialize the HMAC_DRBG with a given seed as required by the deterministic ECDSA ephemeral key construction. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory")
    mcuxClRandom_ModeDescriptor_t *pTestModeDesc = (mcuxClRandom_ModeDescriptor_t *) mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory")
    mcuxClRandom_ModeDescriptor_t *pHmacDrbgMode = (mcuxClRandom_ModeDescriptor_t *) mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    if ((NULL == pTestModeDesc) || (NULL == pHmacDrbgMode))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    // TODO-CLNS-10703: Can there be some of the init stuff shared with higher level functions e.g. sign?


    /*********************************************************************************************/
    /* Create HMAC_DRBG associated to the given HMAC mode.                                       */
    /*                                                                                           */
    /* NOTE: The seed sizes passed to the function are chosen in a way that that the HMAC_DRBG   */
    /*       can later (in test mode) be seeded upon initialization                              */
    /*        - with the properly encoded private key as entropy input and                       */
    /*        - with the properly encoded message digest as nonce                                */
    /*       as specified in NIST SP800-90A.                                                     */
    /*********************************************************************************************/
    mcuxClMac_Mode_t hmacMode = pParam->pMode->pHmacModeDesc;
    uint32_t initSeedSize = 2u * byteLenN;
    uint32_t reseedSeedSize = byteLenN;
    MCUX_CSSL_FP_FUNCTION_CALL(retCreateNormalMode, mcuxClRandomModes_createCustomHmacDrbgMode(
        pHmacDrbgMode,
        hmacMode,
        initSeedSize,
        reseedSeedSize
    ));
    if (MCUXCLRANDOM_STATUS_OK != retCreateNormalMode)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /*********************************************************************************************/
    /* Prepare the seed material (entropy_input || nonce) to be used during instantiation of the */
    /* HMAC_DRBG below:                                                                          */
    /*   - Prepare the entropy input, i.e. the private key encoded using primitive int2octets as */
    /*     specified in rfc6979, at the start of buffer ECC_S0                                   */
    /*   - Prepare the nonce, i.e. the message digest encoded using primitive bits2octets as     */
    /*     specified in rfc6979, directly behind the entropy input                               */
    /*                                                                                           */
    /*         |            ECC_S0               ||              ECC_T0            |             */
    /*         ---------------------------------------------------------------------             */
    /*         | int2octets(private key) | bits2octets(digest) | ***************** |             */
    /*                                                                                           */
    /*********************************************************************************************/
    uint32_t *pEntropyInput = MCUXCLPKC_OFFSET2PTRWORD(pOperands[ECC_S0]);
    uint8_t *pNonce = (uint8_t *) pEntropyInput + byteLenN;

    /* Import digest (up to byteLenN bytes are enough) to ECC_T1.
     *
     * NOTES: - Copying the digest without endianess reversal ensures that its endianess is already in line with the bits2octets encoding
     *        - The digest is imported to ECC_T1 instead of to its (potentially not PKC aligned) final destination to facilitate PKC operations
     *          needed for its proper encoding.
     *        - During the import, the digest is already padded with zeros or truncated to byte length depending on the relation between its byte length
     *          and the byte length of n
     *        - If the hash byte length is larger than the one of n, further bit level truncation is taken care of after th import. */
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_T1, 0u);
    uint32_t byteLenHash = (pParam->optLen & mcuxClEcc_Sign_Param_optLen_byteLenHash_mask) >> mcuxClEcc_Sign_Param_optLen_byteLenHash_offset;
    uint32_t byteLenHashImport = MCUXCLCORE_MIN(byteLenHash, byteLenN);
    uint8_t *pDigestImportDst = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T1]) + byteLenN - byteLenHashImport;
    MCUXCLPKC_WAITFORFINISH();
    MCUXCLMEMORY_FP_MEMORY_COPY(pDigestImportDst, pParam->pHash, byteLenHashImport)

    /* Truncate message hash if its bit length is longer than that of n. */
    if (byteLenHash >= byteLenN)
    {
        /* Count leading zeros in MSByte of n. */
        const volatile uint8_t * ptrN = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_N]);
        uint8_t nMSByte = ptrN[byteLenN - 1u];
        uint32_t nMSByte_LeadZeros = (uint32_t) mcuxClMath_CountLeadingZerosWord((uint32_t) nMSByte) - (8u * ((sizeof(uint32_t)) - 1u));

        /* Only keep the first bitLenN bits of hash. */
        MCUXCLPKC_FP_CALC_OP1_SHR(ECC_T1, ECC_T1, (uint8_t) nMSByte_LeadZeros);

        /* Reduce the value modulo n */
        MCUXCLPKC_FP_CALC_MC1_MS(ECC_T1, ECC_T1, ECC_N, ECC_N);
    }

    /* Shift the nonce to its destination address */
    uint8_t *pNoncePkcAligned = pNonce - (byteLenN % MCUXCLPKC_WORDSIZE);
    uint32_t byteLenNPkcAligned = MCUXCLCORE_ALIGN_TO_WORDSIZE(MCUXCLPKC_WORDSIZE, byteLenN);
    MCUXCLPKC_WAITFORREADY();
    pOperands[ECC_V0] = MCUXCLPKC_PTR2OFFSET(pNoncePkcAligned);
    MCUXCLPKC_PS2_SETLENGTH(0u, MCUXCLCORE_ALIGN_TO_WORDSIZE(MCUXCLPKC_WORDSIZE, byteLenNPkcAligned));
    MCUXCLPKC_FP_CALC_OP2_SHL(ECC_V0, ECC_T1, (uint8_t) 8u * (byteLenN % MCUXCLPKC_WORDSIZE));
    MCUXCLPKC_WAITFORFINISH();

    /* Securely copy the private key to its (PKC word aligned) destination address pEntropyInput before the nonce.
     * Due to the copy without endianess reversal, the private key is already correctly encoded afterwards (using int2octets) */
    MCUX_CSSL_FP_FUNCTION_CALL(retCopyPrivKey, mcuxClMemory_copy_secure_int((uint8_t *) pEntropyInput, pParam->pPrivateKey, byteLenN));
    if (MCUXCLMEMORY_STATUS_OK != retCopyPrivKey)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /*********************************************************************************************/
    /* Create an HMAC_DRBG test mode which shall use the seed material prepared above for        */
    /* seeding during below instantiation and instantiate it.                                    */
    /*                                                                                           */
    /* NOTE: Since mcuxClRandomModes_createTestFromNormalMode requires the custom seed input      */
    /*       pointer to be aligned, we first shift the seed material again to an aligned         */
    /*       address. Use ECC_S1 || ECC_T1 as temp buffers here.                                 */
    /*********************************************************************************************/

    /* Create test mode utilizing the seed prepared above. */
    MCUX_CSSL_FP_FUNCTION_CALL(retCreateTestMode, mcuxClRandomModes_createTestFromNormalMode(
        pTestModeDesc,
        pHmacDrbgMode,
        pEntropyInput
    ));
    if (MCUXCLRANDOM_STATUS_OK != retCreateTestMode)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
    /* Derive the security strength required for the RNG from bitLenN/2 and check whether it can be provided.
     *
     * NOTE: The function mcuxClRandom_checkSecurityStrength can't be used for this because it reads the security strength from the Random config stored in the session. */
    if (MCUXCLCORE_MIN((byteLenN * 8u) / 2u, 256u) > pTestModeDesc->securityStrength)
    {
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
        mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createCustomHmacDrbgMode),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            MCUXCLPKC_FP_CALLED_CALC_OP2_SHL,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy_secure_int),
            MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                MCUXCLPKC_FP_CALLED_CALC_MC1_MS),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode));
    }
#endif

    /* Instantiate HMAC_DRBG */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Return pointer is 32-bit aligned and satisfies the requirement of mcuxClRandom_Context_t");
    mcuxClRandom_Context_t pRandomCtx = (mcuxClRandom_Context_t) mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();
    if (NULL == pRandomCtx)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL(retTestModeInit, pTestModeDesc->pOperationMode->initFunction(pSession, pTestModeDesc, pRandomCtx));
    if (MCUXCLRANDOM_STATUS_OK != retTestModeInit)
    {
        if (MCUXCLRANDOM_STATUS_ERROR == retTestModeInit)
        {
            mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS);
            mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
            mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createCustomHmacDrbgMode),
                MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUXCLPKC_FP_CALLED_CALC_OP2_SHL,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy_secure_int),
                MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                    MCUXCLPKC_FP_CALLED_CALC_MC1_MS),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode),
                pTestModeDesc->pOperationMode->protectionTokenInitFunction);
        }

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /*********************************************************************************************/
    /* Generate an ephemeral key k using the HMAC_DBRG in test mode in a loop as specified in    */
    /* rfc6979. If the generated value is not in range [1,n-1], repeat.                          */
    /*********************************************************************************************/

    do // TODO-CLNS-12395: Flow protection needed here?
    {
        /*********************************************************************************************/
        /* Generate a candidate ephemeral key k using the HMAC_DBRG in test mode                     */
        /*********************************************************************************************/

        /* Initialize PS2 to perform plain additions and subtractions for the computation of (k + r) - (n + r). */
        const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
        const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;
        MCUXCLPKC_PS2_SETLENGTH(0u, bufferSize);

        /* Generate ephemeral key k using the HMAC_DRBG */
        MCUXCLPKC_FP_CALC_OP2_CONST(ECC_S2, 0u);
        uint32_t* pK = MCUXCLPKC_OFFSET2PTRWORD(pOperands[ECC_S2]);
        MCUXCLBUFFER_INIT(pKBuff, NULL, (uint8_t *) pK, byteLenN);
        MCUXCLPKC_WAITFORFINISH();
        MCUX_CSSL_FP_FUNCTION_CALL(retTestModeGenerate, pTestModeDesc->pOperationMode->generateFunction(pSession, pTestModeDesc, pRandomCtx, pKBuff, byteLenN));
        if (MCUXCLRANDOM_STATUS_OK != retTestModeGenerate)
        {
            if (MCUXCLRANDOM_STATUS_ERROR == retTestModeGenerate)
            {
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS);
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
                    /* Balancing function calls before the loop */
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createCustomHmacDrbgMode),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                    MCUXCLPKC_FP_CALLED_CALC_OP2_SHL,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy_secure_int),
                    MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                        MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                        MCUXCLPKC_FP_CALLED_CALC_MC1_MS),
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode),
                    pTestModeDesc->pOperationMode->protectionTokenInitFunction,
                    /* Balancing function inside the loop until this point */
                    MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
                    pTestModeDesc->pOperationMode->protectionTokenGenerateFunction);
            }

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Revert the endianess of the generated k so that in can be considered an integer by the PKC. */
        MCUXCLPKC_FP_SWITCHENDIANNESS(pK, byteLenN);

        /* Encode k using the bits2int procedure as specified in rfc6979, i.e. truncate it to the bit length of n. */
        const volatile uint8_t * ptrN = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_N]);
        uint8_t nMSByte = ptrN[byteLenN - 1u];
        uint32_t nMSByte_LeadZeros = (uint32_t) mcuxClMath_CountLeadingZerosWord((uint32_t) nMSByte) - (8u * ((sizeof(uint32_t)) - 1u));
        MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S2, ECC_S2, (uint8_t) nMSByte_LeadZeros);


        /*********************************************************************************************/
        /* Check if k is smaller than n in an additively blinded way. If not, repeat.                */
        /*********************************************************************************************/

        /* Generate additive blinding value rnd of length byteLenN in buffer T2 for additive blinding of k.
         *
         * NOTE: To avoid garbage propagation, the full buffer ECC_T2 is cleared in advance. */
        MCUXCLPKC_FP_CALC_OP2_CONST(ECC_T2, 0u);
        uint8_t* pR = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T2]);
        MCUXCLBUFFER_INIT(pRBuff, NULL, pR, byteLenN);
        MCUXCLPKC_WAITFORFINISH();
        MCUX_CSSL_FP_FUNCTION_CALL(retNcGenerate_1, mcuxClRandom_ncGenerate(pSession, pRBuff, bufferSize - 1u));
        if (MCUXCLRANDOM_STATUS_OK != retNcGenerate_1)
        {
            if (MCUXCLRANDOM_STATUS_ERROR == retNcGenerate_1)
            {
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS);
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
                    /* Balancing function calls before the loop */
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createCustomHmacDrbgMode),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                    MCUXCLPKC_FP_CALLED_CALC_OP2_SHL,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy_secure_int),
                    MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                        MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                        MCUXCLPKC_FP_CALLED_CALC_MC1_MS),
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode),
                    pTestModeDesc->pOperationMode->protectionTokenInitFunction,
                    /* Balancing function inside the loop until this point */
                    MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
                    pTestModeDesc->pOperationMode->protectionTokenGenerateFunction,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                    MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
            }

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Compute (k+rnd) - (n+rnd) in a FUP program. If the PKC CARRY flag is not set,
         * k is not smaller than n and a new candidate needs to be generated. */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK,
                            mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_CheckNSmallerK_LEN);

        /* Balance FP for the loop so far. */
        MCUX_CSSL_FP_EXPECT(
            MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
            pTestModeDesc->pOperationMode->protectionTokenGenerateFunction,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
            MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
        );

        /* Check PKC CARRY Flag, and if it is not set, repeat */
        if (MCUXCLPKC_FLAG_NOCARRY == MCUXCLPKC_WAITFORFINISH_GETCARRY())
        {
            continue;
        }


        /*********************************************************************************************/
        /* Blind the ephemeral key k multiplicatively with a 64 bit blinding k0 (with MSBit set to 1)*/
        /* to obtain k1 = k0^(-1) * k mod n. In blinded form check if it is zero. If so, repeat.     */
        /*********************************************************************************************/

        /* Generate a 64 bit random multiplicative blinding value k0 */
        uint8_t* pK0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);
        MCUXCLBUFFER_INIT(pK0Buff, NULL, pK0, 8u); // TODO-CLNS-10703: Add define for 8u
        MCUXCLPKC_WAITFORFINISH();
        MCUX_CSSL_FP_FUNCTION_CALL(retNcGenerate_2, mcuxClRandom_ncGenerate(pSession, pK0Buff, 8u));
        if (MCUXCLRANDOM_STATUS_OK != retNcGenerate_2)
        {
            if (MCUXCLRANDOM_STATUS_ERROR == retNcGenerate_2)
            {
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS);
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
                mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
                    /* Balancing function calls before the loop */
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createCustomHmacDrbgMode),
                    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                    MCUXCLPKC_FP_CALLED_CALC_OP2_SHL,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy_secure_int),
                    MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                        MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                        MCUXCLPKC_FP_CALLED_CALC_MC1_MS),
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode),
                    pTestModeDesc->pOperationMode->protectionTokenInitFunction,
                    /* Balancing function inside the if-block until this point */
                    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
            }

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Set MSBit of k0 (to ensure k0 != 0) using the PKC.
         *
         * NOTES:
         *  - PKC PS1 can be used, because operandSize >= 64.
         *  - Clear operand S3 and set bit 64 to 1 */
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S3, 0u);
        uint32_t *ptr32S3 = MCUXCLPKC_OFFSET2PTRWORD(pOperands[ECC_S3]);
        MCUXCLPKC_WAITFORFINISH();
        ptr32S3[1] = 0x80000000u;
        MCUXCLPKC_FP_CALC_OP1_OR(ECC_S0, ECC_S0, ECC_S3);

        /* Compute modular inverse of k0 mod n and store it in buffer T0. */
        /* ZA = k0, duplicate because ModInv(k0) will destroy input k0. */
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(WEIER_ZA, ECC_S0, 0u);
        /* T0 = k0^(-1) = ModInv(k0), with temp S1. */
        MCUXCLMATH_FP_MODINV(ECC_T0, WEIER_ZA, ECC_N, ECC_S1);

        /* Compute k1 in a blinded way and in blinded form check if k is zero
         *
         * NOTE: After the FUP program, the PKC ZERO flag is set iff k is zero */
        // TODO-CLNS-12395: compute it in a blinded way re-using the blinding from the beginning of the loop
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK,
                            mcuxClEcc_FUP_DeterministicECDSA_BlindedSecretKeyGen_BlindK_CheckZeroK_LEN);

        /* Balance the FP for the final part of the loop. */
        MCUX_CSSL_FP_EXPECT(
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR,
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
        );

    /* Check if k1 is zero, and if so, repeat */
    } while(MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO());

    mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MAX_CONTEXT_SIZE_IN_WORDS);
    mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS);
    mcuxClSession_freeWords_cpuWa(pSession, MCUXCLRANDOMMODES_HMAC_DRBG_MODE_DESCRIPTOR_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_DeterministicECDSA_BlindedSecretKeyGen, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createCustomHmacDrbgMode),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUXCLPKC_FP_CALLED_CALC_OP2_SHL,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy_secure_int),
        MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode),
        pTestModeDesc->pOperationMode->protectionTokenInitFunction
        );

    // TODO-CLNS-12395: Clear sensitive data in CPU workarea before returning
}
