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
 * @file  mcuxClRandomModes_TestMode_CtrDrbg_AES256_DRG4_example.c
 * @brief Example for the mcuxClRandomModes component
 *
 * @example mcuxClRandomModes_TestMode_CtrDrbg_AES256_DRG4_example.c
 * @brief   Example for the mcuxClRandomModes component
 */

#include <mcuxClToolchain.h>
#include <mcuxClRandom.h>
#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClCore_Macros.h>
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>


/* CAVP test vectors */
static const uint32_t entropyAndNonceInputInit[MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLRANDOMMODES_TESTMODE_CTR_DRBG_AES256_INIT_ENTROPY_SIZE)] =
{
    0x5d97e604u, 0x45bf8250u, 0x93fdc193u, 0x240602c2u, 0x667688eeu, 0xc7fec3ceu, 0x37cd6b3du, 0x0f3fba6cu,
    0x7e7cc018u, 0x143a77f6u, 0x929e7f5au, 0x2ccdb36cu, 0xb366cc42u, 0x1cec520au, 0x4796757au, 0x85399312u,
    0x2db4e8f5u, 0x007f04au
};

/* Last byte is not used, because reseed entropy size is 55 bytes */
static const uint32_t entropyInputReseed[MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLRANDOMMODES_TESTMODE_CTR_DRBG_AES256_RESEED_ENTROPY_SIZE)] =
{
    0x20cfe741u, 0xd987b4e5u, 0x7aed81d9u, 0x2d878601u, 0x0b614e77u, 0x5a6c244eu, 0xf4a19d89u, 0x058c53a0u,
    0x973bd4c6u, 0x60555726u, 0x11c4a6d3u, 0xa6cb397fu, 0x65ef9ebau, 0x009d46a8u
};

static const uint32_t refOutput[64u / sizeof(uint32_t)] =
{
    0x8199928eu, 0x61249be5u, 0x163bc982u, 0x00790f1au, 0xff5ba6b1u, 0x3dab7965u, 0x04ac13bfu, 0x96b79e0eu,
    0x7ee1234cu, 0xe6d553ceu, 0x46aedc8au, 0x6fb0fec9u, 0x1f60484du, 0xcedb8334u, 0xaa14c399u, 0x925fa977u
};

/** Performs an example usage of the mcuxClRandom and mcuxClRandomModes components with test mode.
 * @retval true  The example code completed successfully
 * @retval false The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRandomModes_TestMode_CtrDrbg_AES256_DRG4_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE, 0u);

    /* Allocate space for a test mode descriptor for an AES-256 CTR_DRBG DRG4. */
    uint32_t testModeDescBytes[MCUXCLRANDOMMODES_TESTMODE_DESCRIPTOR_SIZE_IN_WORDS];
    mcuxClRandom_ModeDescriptor_t *pTestModeDesc = (mcuxClRandom_ModeDescriptor_t *) testModeDescBytes;

    /**************************************************************************/
    /* Test mode creation for an AES-256 CTR_DRBG DRG4 and preparation of     */
    /* known entropy and nonce input for later DRBG instantiation             */
    /**************************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cp_status, cp_token, mcuxClRandomModes_createTestFromNormalMode(
                                        pTestModeDesc,
                                        mcuxClRandomModes_Mode_CtrDrbg_AES256_DRG4,
                                        entropyAndNonceInputInit
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createTestFromNormalMode) != cp_token) || (MCUXCLRANDOM_STATUS_OK != cp_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Test mode initialization with known entropy and nonce input            */
    /**************************************************************************/
    uint32_t context[MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE_IN_WORDS] = {0};

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ri_status, init_token, mcuxClRandom_init(
                                        session,
                                        (mcuxClRandom_Context_t)context,
                                        pTestModeDesc
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != init_token) || (MCUXCLRANDOM_STATUS_OK != ri_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Reseed the DRBG with a known entropy, and generate two random bytes    */
    /* strings                                                                */
    /**************************************************************************/
    /* Buffers to store the generated random values in. */
    ALIGNED uint8_t drbg_data1[64u] = {0u};
    MCUXCLBUFFER_INIT(drbgBuf1, NULL, &drbg_data1[0], 64u);
    ALIGNED uint8_t drbg_data2[64u] = {0u};
    MCUXCLBUFFER_INIT(drbgBuf2, NULL, &drbg_data2[0], 64u);

    /* Update entropy input to be taken for the upcoming reseeding */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ue_status, ue_token, mcuxClRandomModes_updateEntropyInput(pTestModeDesc, entropyInputReseed));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_updateEntropyInput) != ue_token) || (MCUXCLRANDOM_STATUS_OK != ue_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Reseed the DRBG with known entropy input */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rr_status, reseed_token, mcuxClRandom_reseed(session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_reseed) != reseed_token) || (MCUXCLRANDOM_STATUS_OK != rr_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values of 512 bits */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg1_status, generate1_token, mcuxClRandom_generate(
                                        session,
                                        drbgBuf1,
                                        sizeof(drbg_data1)));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate1_token) || (MCUXCLRANDOM_STATUS_OK != rg1_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Generate random values of 512 bits */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg2_status, generate2_token, mcuxClRandom_generate(
                                        session,
                                        drbgBuf2,
                                        sizeof(drbg_data2)));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate2_token) || (MCUXCLRANDOM_STATUS_OK != rg2_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Compare the last generated random output to the expected output        */
    /**************************************************************************/

    bool outputIsExpected = mcuxClCore_assertEqual((const uint8_t*)drbg_data2, (const uint8_t*)refOutput, sizeof(drbg_data2));

    /* Return error if buffers are unequal */
    if(!outputIsExpected)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* Cleanup                                                                */
    /**************************************************************************/

    /* Random uninit. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ru_status, uninit_token, mcuxClRandom_uninit(session));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_uninit) != uninit_token) || (MCUXCLRANDOM_STATUS_OK != ru_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(session))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
