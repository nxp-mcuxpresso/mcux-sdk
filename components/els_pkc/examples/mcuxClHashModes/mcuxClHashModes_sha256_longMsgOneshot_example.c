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

#include <mcuxClEls.h>              // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClSession.h>          // Interface to the entire mcuxClSession component
#include <mcuxClHash.h>             // Interface to the entire mcuxClHash component
#include <mcuxClHashModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClToolchain.h>             // memory segment definitions
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_RNG_Helper.h>

/* Test vector from CAVS 11.0 "SHA-256 LongMsg" */
static const uint8_t data[] = {
    0x45u, 0x11u, 0x01u, 0x25u, 0x0eu, 0xc6u, 0xf2u, 0x66u,
    0x52u, 0x24u, 0x9du, 0x59u, 0xdcu, 0x97u, 0x4bu, 0x73u,
    0x61u, 0xd5u, 0x71u, 0xa8u, 0x10u, 0x1cu, 0xdfu, 0xd3u,
    0x6au, 0xbau, 0x3bu, 0x58u, 0x54u, 0xd3u, 0xaeu, 0x08u,
    0x6bu, 0x5fu, 0xddu, 0x45u, 0x97u, 0x72u, 0x1bu, 0x66u,
    0xe3u, 0xc0u, 0xdcu, 0x5du, 0x8cu, 0x60u, 0x6du, 0x96u,
    0x57u, 0xd0u, 0xe3u, 0x23u, 0x28u, 0x3au, 0x52u, 0x17u,
    0xd1u, 0xf5u, 0x3fu, 0x2fu, 0x28u, 0x4fu, 0x57u, 0xb8u,
    0x5cu, 0x8au, 0x61u, 0xacu, 0x89u, 0x24u, 0x71u, 0x1fu,
    0x89u, 0x5cu, 0x5eu, 0xd9u, 0x0eu, 0xf1u, 0x77u, 0x45u,
    0xedu, 0x2du, 0x72u, 0x8au, 0xbdu, 0x22u, 0xa5u, 0xf7u,
    0xa1u, 0x34u, 0x79u, 0xa4u, 0x62u, 0xd7u, 0x1bu, 0x56u,
    0xc1u, 0x9au, 0x74u, 0xa4u, 0x0bu, 0x65u, 0x5cu, 0x58u,
    0xedu, 0xfeu, 0x0au, 0x18u, 0x8au, 0xd2u, 0xcfu, 0x46u,
    0xcbu, 0xf3u, 0x05u, 0x24u, 0xf6u, 0x5du, 0x42u, 0x3cu,
    0x83u, 0x7du, 0xd1u, 0xffu, 0x2bu, 0xf4u, 0x62u, 0xacu,
    0x41u, 0x98u, 0x00u, 0x73u, 0x45u, 0xbbu, 0x44u, 0xdbu,
    0xb7u, 0xb1u, 0xc8u, 0x61u, 0x29u, 0x8cu, 0xdfu, 0x61u,
    0x98u, 0x2au, 0x83u, 0x3au, 0xfcu, 0x72u, 0x8fu, 0xaeu,
    0x1eu, 0xdau, 0x2fu, 0x87u, 0xaau, 0x2cu, 0x94u, 0x80u,
    0x85u, 0x8bu, 0xecu
};

static const uint8_t hashExpected[MCUXCLHASH_OUTPUT_SIZE_SHA_256] = {
    0x3cu, 0x59u, 0x3au, 0xa5u, 0x39u, 0xfdu, 0xcdu, 0xaeu,
    0x51u, 0x6cu, 0xdfu, 0x2fu, 0x15u, 0x00u, 0x0fu, 0x66u,
    0x34u, 0x18u, 0x5cu, 0x88u, 0xf5u, 0x05u, 0xb3u, 0x97u,
    0x75u, 0xfbu, 0x9au, 0xb1u, 0x37u, 0xa1u, 0x0au, 0xa2u
};


MCUXCLEXAMPLE_FUNCTION(mcuxClHashModes_sha256_longMsgOneshot_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/


    /** Initialize ELS, MCUXCLELS_RESET_DO_NOT_CANCEL **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Initialize session */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    /* Allocate and initialize session */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLHASH_MAX_CPU_WA_BUFFER_SIZE + MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE, 0u);

    /* Initialize the PRNG */
    MCUXCLEXAMPLE_INITIALIZE_PRNG(session);

    /**************************************************************************/
    /* Hash computation                                                       */
    /**************************************************************************/

    uint8_t hash[MCUXCLHASH_OUTPUT_SIZE_SHA_256];
    uint32_t hashOutputSize = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token2, mcuxClHash_compute(
    /* mcuxClSession_Handle_t session: */ session,
    /* mcuxClHash_Algo_t algorithm:    */ mcuxClHash_Algorithm_Sha256,
    /* mcuxCl_InputBuffer_t pIn:       */ data,
    /* uint32_t inSize:               */ sizeof(data),
    /* mcuxCl_Buffer_t pOut            */ hash,
    /* uint32_t *const pOutSize,      */ &hashOutputSize
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) != token2) || (MCUXCLHASH_STATUS_OK != result))
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
        if(hashExpected[i] != hash[i])  // Expect that the resulting hash matches our expected output
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
