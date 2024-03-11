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

#include <mcuxClSession.h>          // Interface to the entire mcuxClSession component
#include <mcuxClHash.h>             // Interface to the entire mcuxClHash component
#include <mcuxClHashModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_RNG_Helper.h>

/* Test vector from CAVS 11.0 "SHA-1 LongMsg" */
static const uint8_t data[] = {
    0x7cu, 0x9cu, 0x67u, 0x32u, 0x3au, 0x1du, 0xf1u, 0xadu,
    0xbfu, 0xe5u, 0xceu, 0xb4u, 0x15u, 0xeau, 0xefu, 0x01u,
    0x55u, 0xecu, 0xe2u, 0x82u, 0x0fu, 0x4du, 0x50u, 0xc1u,
    0xecu, 0x22u, 0xcbu, 0xa4u, 0x92u, 0x8au, 0xc6u, 0x56u,
    0xc8u, 0x3fu, 0xe5u, 0x85u, 0xdbu, 0x6au, 0x78u, 0xceu,
    0x40u, 0xbcu, 0x42u, 0x75u, 0x7au, 0xbau, 0x7eu, 0x5au,
    0x3fu, 0x58u, 0x24u, 0x28u, 0xd6u, 0xcau, 0x68u, 0xd0u,
    0xc3u, 0x97u, 0x83u, 0x36u, 0xa6u, 0xefu, 0xb7u, 0x29u,
    0x61u, 0x3eu, 0x8du, 0x99u, 0x79u, 0x01u, 0x62u, 0x04u,
    0xbfu, 0xd9u, 0x21u, 0x32u, 0x2fu, 0xddu, 0x52u, 0x22u,
    0x18u, 0x35u, 0x54u, 0x44u, 0x7du, 0xe5u, 0xe6u, 0xe9u,
    0xbbu, 0xe6u, 0xedu, 0xf7u, 0x6du, 0x7bu, 0x71u, 0xe1u,
    0x8du, 0xc2u, 0xe8u, 0xd6u, 0xdcu, 0x89u, 0xb7u, 0x39u,
    0x83u, 0x64u, 0xf6u, 0x52u, 0xfau, 0xfcu, 0x73u, 0x43u,
    0x29u, 0xaau, 0xfau, 0x3du, 0xcdu, 0x45u, 0xd4u, 0xf3u,
    0x1eu, 0x38u, 0x8eu, 0x4fu, 0xafu, 0xd7u, 0xfcu, 0x64u,
    0x95u, 0xf3u, 0x7cu, 0xa5u, 0xcbu, 0xabu, 0x7fu, 0x54u,
    0xd5u, 0x86u, 0x46u, 0x3du, 0xa4u, 0xbfu, 0xeau, 0xa3u,
    0xbau, 0xe0u, 0x9fu, 0x7bu, 0x8eu, 0x92u, 0x39u, 0xd8u,
    0x32u, 0xb4u, 0xf0u, 0xa7u, 0x33u, 0xaau, 0x60u, 0x9cu,
    0xc1u, 0xf8u, 0xd4u
};

static const uint8_t hashExpected[MCUXCLHASH_OUTPUT_SIZE_SHA_1] = {
    0xd8u, 0xfdu, 0x6au, 0x91u, 0xefu, 0x3bu, 0x6cu, 0xedu,
    0x05u, 0xb9u, 0x83u, 0x58u, 0xa9u, 0x91u, 0x07u, 0xc1u,
    0xfau, 0xc8u, 0xc8u, 0x07u
};


MCUXCLEXAMPLE_FUNCTION(mcuxClHashModes_sha1_longMsgOneshot_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /* Initialize session */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    /* Allocate and initialize session */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLEXAMPLE_MAX_WA(MCUXCLHASH_MAX_CPU_WA_BUFFER_SIZE, MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE), 0u);

    /* Initialize the PRNG */
    MCUXCLEXAMPLE_INITIALIZE_PRNG(session);

    /**************************************************************************/
    /* Hash computation                                                       */
    /**************************************************************************/

    uint32_t hashOutputSize = 0u;
    uint8_t hash[MCUXCLHASH_OUTPUT_SIZE_SHA_1];
    MCUXCLBUFFER_INIT_RW(hashBuf, session, hash, sizeof(hash));

    MCUXCLBUFFER_INIT_RO(dataBuf, session, data, sizeof(data));

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(compute_result, compute_token, mcuxClHash_compute(
    /* mcuxClSession_Handle_t session: */ session,
    /* mcuxClHash_Algo_t algorithm:    */ mcuxClHash_Algorithm_Sha1,
    /* mcuxCl_InputBuffer_t pIn:       */ dataBuf,
    /* uint32_t inSize:               */ sizeof(data),
    /* mcuxCl_Buffer_t pOut            */ hashBuf,
    /* uint32_t *const pOutSize,      */ &hashOutputSize)
    );

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) != compute_token) || (MCUXCLHASH_STATUS_OK != compute_result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    if(sizeof(hash) != hashOutputSize)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* Verification                                                           */
    /**************************************************************************/
    for(size_t i = 0U; i < sizeof(hash); i++)
    {
        if(hashExpected[i] != hash[i]) // Expect that the resulting hash matches our expected output
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /**************************************************************************/
    /* Session clean-up                                                       */
    /**************************************************************************/
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
