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

#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClMac.h>
#include <mcuxClKey.h>
#include <mcuxClHmac.h>
#include <mcuxClSession.h>
#include <mcuxClMemory.h>
#include <mcuxCsslAnalysis.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <internal/mcuxClRandom_Internal_Memory.h>
#include <internal/mcuxClRandomModes_Internal_SizeDefinitions.h>
#include <internal/mcuxClRandomModes_Internal_HmacDrbg_Functions.h>
#include <internal/mcuxClRandomModes_Private_HmacDrbg.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#include <internal/mcuxClRandomModes_Private_NormalMode.h>
#ifdef MCUXCL_FEATURE_RANDOMMODES_TESTMODE
#include <internal/mcuxClRandomModes_Private_TestMode.h>
#endif /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */
#include <internal/mcuxClRandomModes_Private_PrDisabled.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClKey_Functions_Internal.h>

const mcuxClRandomModes_DrbgAlgorithmsDescriptor_t mcuxClRandomModes_DrbgAlgorithmsDescriptor_HmacDrbg =
{
    .instantiateAlgorithm = mcuxClRandomModes_HmacDrbg_instantiateAlgorithm,
    .reseedAlgorithm = NULL, /* reseed not available */
    .generateAlgorithm = mcuxClRandomModes_HmacDrbg_generateAlgorithm,
    .selftestAlgorithm = NULL, /* selftest not available */
    .protectionTokenInstantiateAlgorithm = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_HmacDrbg_instantiateAlgorithm,
    .protectionTokenReseedAlgorithm = 0u,
    .protectionTokenGenerateAlgorithm = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_HmacDrbg_generateAlgorithm,
    .protectionTokenSelftestAlgorithm = 0u
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_createCustomHmacDrbgMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_createCustomHmacDrbgMode(
    mcuxClRandom_ModeDescriptor_t *randomMode,
    mcuxClMac_Mode_t hmacMode,
    uint32_t initSeedSize,  /* Includes the size of a nonce */
    uint32_t reseedSeedSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_createCustomHmacDrbgMode);

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(hmacMode->common.macByteSize, 0u, MCUXCLHMAC_MAX_OUTPUT_SIZE, MCUXCLRANDOM_STATUS_INVALID_PARAM)

    /************************************
     * Fill top layer information       *
     ************************************/
    randomMode->pOperationMode = &mcuxClRandomModes_OperationModeDescriptor_NormalMode_PrDisabled;
    randomMode->contextSize = sizeof(mcuxClRandomModes_Context_Generic_t) + 2u * hmacMode->common.macByteSize;
#ifdef MCUXCL_FEATURE_RANDOMMODES_TESTMODE
    randomMode->auxParam = (uint32_t *) &mcuxClRandomModes_OperationModeDescriptor_TestMode_PrDisabled;
#else
    randomMode->auxParam = NULL;
#endif /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */
    /* Hash algorithm descriptors do not store security strength, for Sha2 and Sha3 it is half the output size in bits. */
    randomMode->securityStrength = hmacMode->common.macByteSize * 4u;

    /********************************************************************
     * Fill hash algorithm specific DrbgModeDescriptor                  *
     ********************************************************************/
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("Custom drbg mode and variant descriptors are stored in memory behind random mode descriptor.")
    uintptr_t pDrbgModeDescriptorLocation = (uintptr_t) randomMode + sizeof(mcuxClRandom_ModeDescriptor_t);
    uintptr_t pDrbgVariantLocation = pDrbgModeDescriptorLocation + sizeof(mcuxClRandomModes_DrbgModeDescriptor_t);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    /* Insert custom drbg mode into randomMode */
    randomMode->pDrbgMode = (mcuxClRandomModes_DrbgModeDescriptor_t *)pDrbgModeDescriptorLocation;
    mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (mcuxClRandomModes_DrbgModeDescriptor_t *) randomMode->pDrbgMode;
    pDrbgMode->pDrbgAlgorithms = &mcuxClRandomModes_DrbgAlgorithmsDescriptor_HmacDrbg;
    pDrbgMode->pDrbgVariant = (mcuxClRandomModes_DrbgVariantDescriptor_t *)pDrbgVariantLocation;
    pDrbgMode->pDrbgTestVectors = NULL; /* selftest not available */
    pDrbgMode->continuousReseedInterval = 0u;

    /* Insert custom drbg variant into drbg mode */
    mcuxClRandomModes_DrbgVariantDescriptor_t *pDrbgVariant = ((mcuxClRandomModes_DrbgVariantDescriptor_t *)pDrbgMode->pDrbgVariant);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pDrbgVariant pointer is of the right type")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("Variant descriptors is stored in memory behind drbg mode descriptor.")
    pDrbgVariant->reseedInterval = MCUXCLRANDOMMODES_RESEED_INTERVAL_HMAC_DRBG,
    pDrbgVariant->seedLen = 0u, /* Not needed for HMAC_DRBG, UpdateState takes the role of DF */
    pDrbgVariant->initSeedSize = initSeedSize;
    pDrbgVariant->reseedSeedSize = reseedSeedSize;
    pDrbgVariant->drbgVariantSpecifier = (void *) hmacMode;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_createCustomHmacDrbgMode, MCUXCLRANDOM_STATUS_OK);
}

/**
 * \brief This function instantiates an HMAC_DRBG following the lines of the function HMAC_DRBG_Instantiate_algorithm as specified in NIST SP800-90A
 *
 * This function instantiates a HMAC_DRBG in following the lines of the function HMAC_DRBG_Instantiate_algorithm as specified in NIST SP800-90A.
 * The function obtains entropy input for the DRBG seed from the TRNG.
 *
 * \param  pSession                     Handle for the current CL session
 * \param  mode[in]                     Handle for the current Random Mode
 * \param  context[in]                  Handle for the current Random Context
 * \param  pEntropyInputAndNonce[in]    Pointer to entropy input and nonce
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the HMAC_DRBG instantiation finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR           if a memory allocation error occured
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the HMAC_DRBG instantiation failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_HmacDrbg_instantiateAlgorithm, mcuxClRandomModes_instantiateAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_instantiateAlgorithm(
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        uint8_t *pEntropyInputAndNonce
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_HmacDrbg_instantiateAlgorithm);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Cast to a more specific type is allowed")
    mcuxClRandomModes_Context_HmacDrbg_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_HmacDrbg_Generic_t *) context;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_VOID()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) mode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_VOID()
    mcuxClMac_Mode_t hmacMode = (mcuxClMac_Mode_t) pDrbgMode->pDrbgVariant->drbgVariantSpecifier;

    uint8_t *pSeedMaterial = pEntropyInputAndNonce;
    uint32_t seedMaterialSize = pDrbgMode->pDrbgVariant->initSeedSize;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The hmacMode pointer is of the right type")
    size_t hmacOutputLength = hmacMode->common.macByteSize;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pRngCtxGeneric pointer is of the right type")
    uint32_t *pHmacKey = pRngCtxGeneric->state;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint8_t *pHmacVBytes = &(((uint8_t*)(pRngCtxGeneric->state))[hmacOutputLength]);
    uint8_t *pHmacKeyBytes = (uint8_t *) pHmacKey;

    /* Set initial values for V and K */
    for(size_t i = 0u; i < hmacOutputLength; i++)
    {
        pHmacKeyBytes[i]  = 0x00u;
        pHmacVBytes[i]    = 0x01u;
    }

    /* Call HMAC_DRBG_Update. Note that for HMAC-DRBG, this also serves as a derivation function for the instantiate and reseed functions. */
    MCUX_CSSL_FP_FUNCTION_CALL(result_updatestate, mcuxClRandomModes_HmacDrbg_UpdateState(
                pSession,
                mode,
                context,
                pSeedMaterial,
                seedMaterialSize));
    if(MCUXCLRANDOM_STATUS_OK != result_updatestate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_instantiateAlgorithm, result_updatestate,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_HmacDrbg_UpdateState));
    }
    else
    {
        /* Initialize the reseed counter */
        pRngCtxGeneric->reseedCounter = 1u;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_instantiateAlgorithm, MCUXCLRANDOM_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_HmacDrbg_UpdateState));
}


/**
 * \brief This function generates random numbers from an HMAC_DRBG following the lines of the function HMAC_DRBG_Generate_algorithm as specified in NIST SP800-90A
 *
 * \param  pSession             Handle for the current CL session
 * \param  mode[in]             Handle for the current Random Mode
 * \param  context[in]          Handle for the current Random Context
 * \param  pOut[out]            Output buffer to which the generated randomness will be written
 * \param  outLength[in]        Number of requested random bytes
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK              if the random number generation finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR           if a memory allocation error occured
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK    if the random number generation failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_HmacDrbg_generateAlgorithm, mcuxClRandomModes_generateAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_generateAlgorithm(
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        mcuxCl_Buffer_t pOut,
        uint32_t outLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_HmacDrbg_generateAlgorithm);

    /* Get generic HMAC_DRBG context pointer */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Cast to a more specific type is allowed")
    mcuxClRandomModes_Context_HmacDrbg_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_HmacDrbg_Generic_t *) context;
    /* The number of reseed attempts is limited to 2^48 according to NIST SP800-90A */
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pRngCtxGeneric->reseedCounter, 0u, (1uLL << 48u), MCUXCLRANDOM_STATUS_ERROR)
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()


    /********************************************************************************************************/
    /*                                                                                                      */
    /* Perform the actual Generate Process according to NIST SP800-90A:                                     */
    /*                                                                                                      */
    /*   Step 3:  temp = Null.                                                                              */
    /*   Step 4:  While (len (temp) < requested_number_of_bits) do:                                         */
    /*              V = HMAC (Key, V).                                                                      */
    /*              temp = temp || V.                                                                       */
    /*   Step 5:  returned_bits = leftmost (temp, requested_number_of_bits).                                */
    /*   Step 6:  (Key, V) = HMAC_DRBG_Update (additional_input, Key, V).                                   */
    /*   Step 7:  reseed_counter = reseed_counter + 1.                                                      */
    /*   Step 8:  Return (SUCCESS, returned_bits, Key, V, reseed_counter).                                  */
    /*                                                                                                      */
    /* Note that Steps 1-2 are omitted here because reseed counter checking is done in the higher level     */
    /* function and no additional input is supported by the Random component.                               */
    /*                                                                                                      */
    /********************************************************************************************************/

    /* Execute Steps 3-5. Note that no temp buffer is needed, the output is directly written to the destination buffer */
    MCUX_CSSL_FP_FUNCTION_CALL(result_generate,
        mcuxClRandomModes_HmacDrbg_generateOutput(
                    pSession,
                    mode,
                    context,
                    pOut,
                    outLength));
    if(MCUXCLRANDOM_STATUS_ERROR == result_generate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateAlgorithm, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_HmacDrbg_generateOutput));
    }
    else if(MCUXCLRANDOM_STATUS_OK != result_generate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateAlgorithm, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    /* Execute Step 6, i.e. update the state of the HMAC_DRBG */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_CALL(result_updatestate, mcuxClRandomModes_HmacDrbg_UpdateState(
                    pSession,
                    mode,
                    context,
                    NULL,
                    0u));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
    if(MCUXCLRANDOM_STATUS_ERROR == result_updatestate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateAlgorithm, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_HmacDrbg_generateOutput));
    }
    else if (MCUXCLRANDOM_STATUS_OK != result_updatestate)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateAlgorithm, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Step 7: Increment the reseed counter */
        pRngCtxGeneric->reseedCounter += 1u;

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateAlgorithm, MCUXCLRANDOM_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_HmacDrbg_generateOutput),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_HmacDrbg_UpdateState));
    }
}


/**
 * \brief This function updates the internal state of an HMAC_DRBG as specified in NIST SP800-90A
 *
 * \param  session              Handle for the current CL session
 * \param  mode[in]             Handle for the current Random Mode
 * \param  context[in/out]      Handle for the current Random Context
 * \param  pProvidedData[in]    Additional data to incorporate into the state
 * \param  providedDataSize[in] Byte length of the passed provided data
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK            if the state update finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR         if a memory allocation error or an HMAC operation error occured
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK  if the state update failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_HmacDrbg_UpdateState)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_UpdateState(
        mcuxClSession_Handle_t session,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        uint8_t *pProvidedData,
        uint32_t providedDataSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_HmacDrbg_UpdateState);

    /* Get generic HMAC_DRBG context pointer and determine DRBG mode pointer and HMAC mode */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Cast to a more specific type is allowed")
    mcuxClRandomModes_Context_HmacDrbg_Generic_t *pRngCtxGeneric = (mcuxClRandomModes_Context_HmacDrbg_Generic_t *) context;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_VOID()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) mode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_VOID()
    mcuxClMac_Mode_t hmacMode = (mcuxClMac_Mode_t) pDrbgMode->pDrbgVariant->drbgVariantSpecifier;

    /* Determine pointers to the K and V buffers in the context */
    size_t hmacOutputLength = hmacMode->common.macByteSize;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pRngCtxGeneric pointer is of the right type")
    uint32_t *pHmacKey = pRngCtxGeneric->state;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint8_t *pHmacV = &(((uint8_t*)(pRngCtxGeneric->state))[hmacOutputLength]);


    /* Allocate space for a key handle and in CPU workarea and initialize it with the K buffer inside the context */
    uint32_t *pKeyDesc = mcuxClSession_allocateWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t key = (mcuxClKey_Handle_t) pKeyDesc;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == pKeyDesc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR);
    }
    MCUXCLBUFFER_INIT(hmacKeyBuf, NULL, (uint8_t *) pHmacKey, hmacOutputLength);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The key pointer is of the right type")
    MCUX_CSSL_FP_FUNCTION_CALL(result_keyInit, mcuxClKey_init(
                session,
                key,
                mcuxClKey_Type_Hmac_variableLength,
                hmacKeyBuf,
                hmacOutputLength)
    );
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    if(MCUXCLKEY_STATUS_OK != result_keyInit)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Additional key handle initialization required for ELS platforms */
    // TODO Check if still needed after CLNS-8477 is done.
    mcuxClKey_setLoadedKeyData(key, pHmacKey);
    mcuxClKey_setLoadedKeyLength(key, hmacOutputLength);

    /* Allocate space for a MAC context for the upcoming HMAC multipart operations */
    mcuxClMac_Context_t *pHmacCtx = (mcuxClMac_Context_t *) mcuxClSession_allocateWords_cpuWa(session, MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);
    if(NULL == pHmacCtx)
    {
        /* Free CPU workarea used by this function (key descriptor) */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init));
    }

    /* Initialize a byte variable with zero which will be processed by HMAC in the following Update process and can contain the values 0 and 1 */
    uint8_t oneByteHmacInput = 0u;

    /********************************************************************************************************/
    /*                                                                                                      */
    /* Perform the actual UpdateState operations according to NIST SP800-90A:                               */
    /*                                                                                                      */
    /*   Step 1: K = HMAC(K, V || 0x00 || provided_data).                                                   */
    /*   Step 2: V = HMAC(K, V).                                                                            */
    /*   Step 3: If (provided_data = Null), then return K and V.                                            */
    /*   Step 4: K = HMAC(K, V || 0x01 || provided_data).                                                   */
    /*   Step 5: V = HMAC(K, V).                                                                            */
    /*   Step 6: Return (K, V).                                                                             */
    /*                                                                                                      */
    /* This is done in a do-while loop which (depending on whether providedData is provided or not) repeats */
    /* Steps 1-3 a second time with value 0x01 instead of 0x00 for the oneByteHmacInput variable            */
    /*                                                                                                      */
    /********************************************************************************************************/

    MCUX_CSSL_FP_LOOP_DECL(doWhileLoop);
    do
    {
        /*
         * Step 1: K = HMAC(K, V || 0x00 || provided_data).
         */

        /* Initialize a MAC context for multipart HMAC operations */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pHmacCtx pointer is of the right type")
        MCUX_CSSL_FP_FUNCTION_CALL(result_macInit, mcuxClMac_init(
                    session,
                    pHmacCtx,
                    key,
                    hmacMode)
        );
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()
        if(MCUXCLMAC_STATUS_ERROR == result_macInit)
        {
            /* Free CPU workarea used by this function (key descriptor and MAC context) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput));
        }
        else if (MCUXCLMAC_STATUS_OK != result_macInit)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Process V */
        MCUXCLBUFFER_INIT(hmacVBuf, NULL, (uint8_t *) pHmacV, hmacOutputLength);
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_FP_FUNCTION_CALL(result_macProcess1, mcuxClMac_process(
                    session,
                    pHmacCtx,
                    hmacVBuf,
                    hmacOutputLength)
        );
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()
        if(MCUXCLMAC_STATUS_ERROR == result_macProcess1)
        {
            /* Free CPU workarea used by this function (key descriptor and MAC context) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput));
        }
        else if (MCUXCLMAC_STATUS_OK != result_macProcess1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Process byte value 0x00 */
        MCUXCLBUFFER_INIT(oneByteHmacInputBuf, NULL, &oneByteHmacInput, 1u);
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_FP_FUNCTION_CALL(result_macProcess2, mcuxClMac_process(
                    session,
                    pHmacCtx,
                    oneByteHmacInputBuf,
                    1u)
        );
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()
        if(MCUXCLMAC_STATUS_ERROR == result_macProcess2)
        {
            /* Free CPU workarea used by this function (key descriptor and MAC context) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput));
        }
        else if (MCUXCLMAC_STATUS_OK != result_macProcess2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Process provided data */
        MCUXCLBUFFER_INIT(pProvidedDataBuf, NULL, pProvidedData, providedDataSize);
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_FP_FUNCTION_CALL(result_macProcess3, mcuxClMac_process(
                    session,
                    pHmacCtx,
                    pProvidedDataBuf,
                    providedDataSize)
        );
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()
        if(MCUXCLMAC_STATUS_ERROR == result_macProcess3)
        {
            /* Free CPU workarea used by this function (key descriptor and MAC context) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput));
        }
        else if (MCUXCLMAC_STATUS_OK != result_macProcess3)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Finalize calculation of HMAC(K, V || 0x00 || provided_data) and store the result in the K buffer of the context */
        uint32_t macSize = 0u;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_TAINTED_EXPRESSION("Mac Context is initialized in mcuxClMac_init")
        MCUX_CSSL_FP_FUNCTION_CALL(result_macFinish, mcuxClMac_finish(
                    session,
                    pHmacCtx,
                    hmacKeyBuf,
                    &macSize)
        );
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_TAINTED_EXPRESSION()
        if((MCUXCLMAC_STATUS_ERROR == result_macFinish) && (macSize == hmacOutputLength))
        {
            /* Free CPU workarea used by this function (key descriptor and MAC context) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput));
        }
        else if ((MCUXCLMAC_STATUS_OK != result_macFinish) || (macSize != hmacOutputLength))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /*
         * Step 2: V = HMAC(K, V).
         */
        macSize = 0u;
        MCUX_CSSL_FP_FUNCTION_CALL(result_macCompute, mcuxClMac_compute(
                session,
                key,
                hmacMode,
                hmacVBuf,
                hmacOutputLength,
                hmacVBuf,
                &macSize)
        );
        if((MCUXCLMAC_STATUS_ERROR == result_macCompute) && (macSize == hmacOutputLength))
        {
            /* Free CPU workarea used by this function (key descriptor and MAC context) */
            mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_compute),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput));
        }
        else if ((MCUXCLMAC_STATUS_OK != result_macCompute) || (macSize != hmacOutputLength))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Increment oneByteHmacInput and update FP loop iteration information */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("The range of oneByteHmacInput must be in [0, 2]")
        oneByteHmacInput++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        MCUX_CSSL_FP_LOOP_ITERATION(doWhileLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_compute)
            );
    /* Repeat the loop ONCE, if providedData is not empty. Otherwise, exit the loop */
    } while((1u >= oneByteHmacInput) && (0u != providedDataSize));

    /* Free CPU workarea used by this function (key descriptor and MAC context) */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS + MCUXCLHMAC_MAX_CONTEXT_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_UpdateState, MCUXCLRANDOM_STATUS_OK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_LOOP_ITERATIONS(doWhileLoop, oneByteHmacInput)
                );
}


/**
 * \brief This function generates output from the internal state of an HMAC_DRBG as specified in NIST SP800-90A
 *
 * \param  pSession             Handle for the current CL session
 * \param  mode[in]             Handle for the current Random Mode
 * \param  context[in]          Handle for the current Random Context
 * \param  pOut[out]            Output buffer to which the generated randomness will be written
 * \param  outLength[in]        Number of requested random bytes
 *
 * \return
 *   - MCUXCLRANDOM_STATUS_OK            if the random number generation finished successfully
 *   - MCUXCLRANDOM_STATUS_ERROR         if a memory allocation error or an HMAC computation error occured
 *   - MCUXCLRANDOM_STATUS_FAULT_ATTACK  if the random number generation failed due to other unexpected reasons
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_HmacDrbg_generateOutput)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_HmacDrbg_generateOutput(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
        mcuxClSession_Handle_t pSession,
        mcuxClRandom_Mode_t mode,
        mcuxClRandom_Context_t context,
        mcuxCl_Buffer_t pOut,
        uint32_t outLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_HmacDrbg_generateOutput);

    /* Get generic HMAC_DRBG context pointer and determine DRBG mode pointer and HMAC mode */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("Cast to a more specific type is allowed")
    mcuxClRandomModes_Context_HmacDrbg_Generic_t *pCtx = (mcuxClRandomModes_Context_HmacDrbg_Generic_t *) context;
    uint32_t *pState = pCtx->state;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_VOID()
    const mcuxClRandomModes_DrbgModeDescriptor_t *pDrbgMode = (const mcuxClRandomModes_DrbgModeDescriptor_t *) mode->pDrbgMode;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_VOID()
    mcuxClMac_Mode_t hmacMode = (mcuxClMac_Mode_t) pDrbgMode->pDrbgVariant->drbgVariantSpecifier;

    /* Determine pointers to the K and V buffers in the context */
    size_t hmacOutputLength = hmacMode->common.macByteSize;
    uint32_t *pHmacKey = pState;
    uint8_t *pHmacV = &(((uint8_t*)(pState))[hmacOutputLength]);

    /* Allocate space for a key handle and in CPU workarea and initialize it with the K buffer inside the context */
    uint32_t *pKeyDesc = mcuxClSession_allocateWords_cpuWa(pSession, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS);
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClKey_Handle_t key = (mcuxClKey_Handle_t) pKeyDesc;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    if(NULL == pKeyDesc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateOutput, MCUXCLRANDOM_STATUS_ERROR);
    }
    MCUXCLBUFFER_INIT(hmacKeyBuf, NULL, (uint8_t *) pHmacKey, hmacOutputLength);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The key pointer is of the right type");
    MCUX_CSSL_FP_FUNCTION_CALL(result_keyInit, mcuxClKey_init(
                pSession,
                key,
                mcuxClKey_Type_Hmac_variableLength,
                hmacKeyBuf,
                hmacOutputLength)
    );
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    if(MCUXCLKEY_STATUS_OK != result_keyInit)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateOutput, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }

    /* Additional key handle initialization required for ELS platforms */
    // TODO Check if still needed after CLNS-8477 is done.
    mcuxClKey_setLoadedKeyData(key, pHmacKey);
    mcuxClKey_setLoadedKeyLength(key, hmacOutputLength);


    /********************************************************************************************************/
    /*                                                                                                      */
    /* Perform Steps 3-5 of the actual Generate Process according to NIST SP800-90A:                        */
    /*                                                                                                      */
    /*   Step 3:  temp = Null.                                                                              */
    /*   Step 4:  While (len (temp) < requested_number_of_bits) do:                                         */
    /*              V = HMAC (Key, V).                                                                      */
    /*              temp = temp || V.                                                                       */
    /*   Step 5:  returned_bits = leftmost (temp, requested_number_of_bits).                                */
    /*                                                                                                      */
    /* Note that no temp buffer is needed, the output is directly written to the destination buffer.        */
    /* The while loop is implemented in two parts. First, chunks of full HMAC output size are processed,    */
    /* afterwards, the remaining bytes are taken care of.                                                   */
    /*                                                                                                      */
    /********************************************************************************************************/

    /* Determine how many remaining bytes need to be processed after having looped of full HMAC output size chunks */
    uint32_t requestSizeRemainingBytes = outLength;
    uint32_t bytesToReturn = 0u;

    /* Derive and initialize buffers for upcoming HMAC operations */
    MCUXCLBUFFER_INIT(pHmacVBuf, NULL, (uint8_t *) pHmacV, hmacOutputLength);

    /* Request as many random bytes as possible with full HMAC output size. */
    uint32_t outIndex = 0u;

    uint32_t extraIteration = (requestSizeRemainingBytes % hmacOutputLength) == 0u ? 0u : 1u;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("hmacOutputLength must be bigger than 1, so this operation cannot wap")
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t noOfIterations = (requestSizeRemainingBytes / hmacOutputLength) + extraIteration);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    MCUX_CSSL_FP_LOOP_DECL(whileLoop);
    while (0u < requestSizeRemainingBytes)
    {
        /* Determine how many random bytes to return to the caller in this iterations. */
        bytesToReturn = (requestSizeRemainingBytes > hmacOutputLength) ? hmacOutputLength : requestSizeRemainingBytes;

        /* Compute V = HMAC (Key, V) */
        uint32_t macSize = 0u;
        MCUX_CSSL_FP_FUNCTION_CALL(result_macCompute, mcuxClMac_compute(
                pSession,
                key,
                hmacMode,
                pHmacVBuf,
                hmacOutputLength,
                pHmacVBuf,
                &macSize)
        );
        if((MCUXCLMAC_STATUS_ERROR == result_macCompute) && (macSize == hmacOutputLength))
        {
            /* Free CPU workarea used by this function (key descriptor) */
            mcuxClSession_freeWords_cpuWa(pSession, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateOutput, MCUXCLRANDOM_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_compute), /* Compensate this Mac_compute call */
                MCUX_CSSL_FP_LOOP_ITERATIONS(whileLoop, (outIndex/hmacOutputLength)) /* Compensate previous loop iterations */
                );
        }
        else if ((MCUXCLMAC_STATUS_OK != result_macCompute) || (macSize != hmacOutputLength))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateOutput, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Intentionally left empty */
        }

        /* Securely copy the result to the destination buffer. */
        MCUX_CSSL_FP_FUNCTION_CALL(write_status, mcuxClBuffer_write_secure(pOut, outIndex, (uint8_t *)pHmacV, bytesToReturn));
        if(MCUXCLBUFFER_STATUS_OK != write_status)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateOutput, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
        }

        outIndex += bytesToReturn;
        requestSizeRemainingBytes -= bytesToReturn;

        /* Update loop counters and FP loop iteration information */
        MCUX_CSSL_FP_LOOP_ITERATION(whileLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_compute),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_secure)
            );
    }


    /* Free CPU workarea used by this function (key descriptor) */
    mcuxClSession_freeWords_cpuWa(pSession, MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_HmacDrbg_generateOutput, MCUXCLRANDOM_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init),
        MCUX_CSSL_FP_LOOP_ITERATIONS(whileLoop, noOfIterations));
}
