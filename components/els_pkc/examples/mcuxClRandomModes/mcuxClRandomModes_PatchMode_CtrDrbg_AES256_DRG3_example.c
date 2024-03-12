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
 * @file  mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example.c
 * @brief Example for the mcuxClRandomModes component
 *
 * @example mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example.c
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

#include <mcuxClBuffer.h>

static const ALIGNED uint8_t randomData[] = { 0x8au,0x76u,0x90u,0xd2u,0xd9u,0x55u,0x3cu,0x93u,
                                              0x03u,0x52u,0x3au,0x3cu,0xbeu,0xe1u,0x39u,0xa4u,
                                              0xefu,0xf1u,0xc4u,0xbbu,0xa3u,0xc7u,0x09u,0xf3u,
                                              0xb7u,0x14u,0x07u,0xb2u,0xd8u,0x98u,0xa0u,0xaeu };

/******************************************************************************
 * Local and global function declarations
 ******************************************************************************/
static mcuxClRandom_Status_t RNG_Patch_function(
    mcuxClSession_Handle_t session,
    mcuxClRandom_Context_t pCustomCtx,
    mcuxCl_Buffer_t pOut,
    uint32_t outLength
)
{
    (void)session;
    (void)pCustomCtx;
    uint32_t indexRandomData = 0u;

    for (uint32_t i = 0u; i < outLength; i++)
    {
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(be_status, be_token, mcuxClBuffer_export(pOut, i, (uint8_t const *)&randomData[indexRandomData], 1u));
        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_export) != be_token) || (MCUXCLBUFFER_STATUS_OK != be_status))
        {
          return MCUXCLRANDOM_STATUS_FAULT_ATTACK;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        indexRandomData = (indexRandomData + 1u) % sizeof(randomData);
    }

    return MCUXCLRANDOM_STATUS_OK;
}

/** Performs an example usage of the mcuxClRandom and mcuxClRandomModes components with patch mode.
 * @retval true  The example code completed successfully
 * @retval false The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLRANDOMMODES_MAX_CPU_WA_BUFFER_SIZE, 0u);

    /* Fill mode descriptor with the relevant data */
    uint32_t customModeDescBytes[MCUXCLRANDOMMODES_PATCHMODE_DESCRIPTOR_SIZE_IN_WORDS];
    mcuxClRandom_ModeDescriptor_t *mcuxClRandomModes_Mode_Custom = (mcuxClRandom_ModeDescriptor_t *) customModeDescBytes;

    /**************************************************************************/
    /* RANDOM Patch Mode creation, use custom function RNG_Patch_function     */
    /**************************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(cp_status, cp_token, mcuxClRandomModes_createPatchMode(
                                        mcuxClRandomModes_Mode_Custom,
                                        (mcuxClRandomModes_CustomGenerateAlgorithm_t)RNG_Patch_function,
                                        NULL,
                                        256U
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandomModes_createPatchMode) != cp_token) || (MCUXCLRANDOM_STATUS_OK != cp_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* patch mode initialization                                              */
    /**************************************************************************/
    uint32_t* rngContextPatched = NULL;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(ri_status, init_token, mcuxClRandom_init(
                                        session,
                                        (mcuxClRandom_Context_t)rngContextPatched,
                                        mcuxClRandomModes_Mode_Custom
                                   ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_init) != init_token) || (MCUXCLRANDOM_STATUS_OK != ri_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Generate several random byte strings                                   */
    /**************************************************************************/
    /* Buffers to store the generated random values in. */
    ALIGNED uint8_t drbg_data1[3u];
    MCUXCLBUFFER_INIT(drbgBuf1, NULL, &drbg_data1[0], 3u);
    ALIGNED uint8_t drbg_data2[sizeof(randomData) + 16u];
    MCUXCLBUFFER_INIT(drbgBuf2, NULL, &drbg_data2[0], sizeof(randomData) + 16u);

    /* Generate random values of smaller amount than the size of prepared random data array. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg1_status, generate1_token, mcuxClRandom_generate(
                                        session,
                                        drbgBuf1,
                                        sizeof(drbg_data1)));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate1_token) || (MCUXCLRANDOM_STATUS_OK != rg1_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Check if the generated data meets expectation */
    if(!mcuxClCore_assertEqual(drbg_data1, randomData, sizeof(drbg_data1)))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Generate random values of larger amount than the size of prepared random data array. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(rg2_status, generate2_token, mcuxClRandom_generate(
                                        session,
                                        drbgBuf2,
                                        sizeof(drbg_data2)));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) != generate2_token) || (MCUXCLRANDOM_STATUS_OK != rg2_status))
    {
      return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Check if the generated data meets expectation */
    if(!mcuxClCore_assertEqual(drbg_data2, randomData, sizeof(randomData)))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    if(!mcuxClCore_assertEqual(drbg_data2 + sizeof(randomData), randomData, 16u))
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

    return MCUXCLEXAMPLE_STATUS_OK;
}
