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

#include <mcuxClEls.h>               // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClSession.h>           // Interface to the entire mcuxClSession component
#include <mcuxClHash.h>              // Interface to the entire mcuxClHash component
#include <mcuxClHashModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>  // Code flow protection
#include <mcuxClToolchain.h>              // memory segment definitions
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_RNG_Helper.h>

static const uint8_t data1[7] CSS_CONST_SEGMENT = {
    0x65u, 0x78u, 0x61u, 0x6du, 0x70u, 0x6cu, 0x65u //example
};

static const uint8_t data2[4] CSS_CONST_SEGMENT = {
    0x68u, 0x61u, 0x73u, 0x68u  //hash
};

static const uint8_t data3[9] CSS_CONST_SEGMENT = {
    0x73u, 0x74u, 0x72u, 0x65u, 0x61u, 0x6du, 0x69u, 0x6eu, 0x67u //streaming
};

static const uint8_t hashExpected[32] CSS_CONST_SEGMENT = {
    0xb3u, 0xdcu, 0xe3u, 0x33u, 0x68u, 0x24u, 0x6du, 0x98u,
    0x04u, 0x6bu, 0xd4u, 0x52u, 0x6cu, 0x69u, 0xc1u, 0xd0u,
    0x37u, 0x01u, 0x57u, 0x60u, 0x95u, 0xbau, 0x74u, 0x74u,
    0xc6u, 0xcbu, 0xf2u, 0x5eu, 0x3fu, 0xffu, 0xe8u, 0xc4u
};

MCUXCLEXAMPLE_FUNCTION(mcuxClHashModes_sha256_streaming_example)
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

    /* RTF update is set to false by default */

    /**************************************************************************/
    /* Hash computation                                                       */
    /**************************************************************************/

	uint64_t context[MCUXCLHASH_CONTEXT_SIZE_SHA2_256_IN_WORDS / 2u];

	MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result2, token2, mcuxClHash_init(
	/* mcuxCLSession_Handle_t session: */ session,
	/* mcuxClHash_Context_t context:   */ (mcuxClHash_Context_t) context,
	/* mcuxClHash_Algo_t  algorithm:   */ mcuxClHash_Algorithm_Sha256
	));
	// mcuxClHash_init is a flow-protected function: Check the protection token and the return value
	if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init) != token2) || (MCUXCLHASH_STATUS_OK != result2))
	{
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}
	MCUX_CSSL_FP_FUNCTION_CALL_END();

	MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result3, token3, mcuxClHash_process(
	/* mcuxCLSession_Handle_t session: */ session,
	/* mcuxClHash_Context_t context:   */ (mcuxClHash_Context_t) context,
	/* mcuxCl_InputBuffer_t in:        */ data1,
	/* uint32_t inSize:               */ sizeof(data1)
	));
	// mcuxClHash_process is a flow-protected function: Check the protection token and the return value
	if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process) != token3) || (MCUXCLHASH_STATUS_OK != result3))
	{
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}
	MCUX_CSSL_FP_FUNCTION_CALL_END();

	MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result4, token4, mcuxClHash_process(
	/* mcuxCLSession_Handle_t session: */ session,
	/* mcuxClHash_Context_t context:   */ (mcuxClHash_Context_t) context,
	/* mcuxCl_InputBuffer_t in:        */ data2,
	/* uint32_t inSize:               */ sizeof(data2)
	));
	// mcuxClHash_process is a flow-protected function: Check the protection token and the return value
	if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process) != token4) || (MCUXCLHASH_STATUS_OK != result4))
	{
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}
	MCUX_CSSL_FP_FUNCTION_CALL_END();

	MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result5, token5, mcuxClHash_process(
	/* mcuxCLSession_Handle_t session: */ session,
	/* mcuxClHash_Context_t context:   */ (mcuxClHash_Context_t) context,
	/* mcuxCl_InputBuffer_t in:        */ data3,
	/* uint32_t inSize:               */ sizeof(data3)
	));
	// mcuxClHash_process is a flow-protected function: Check the protection token and the return value
	if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process) != token5) || (MCUXCLHASH_STATUS_OK != result5))
	{
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}
	MCUX_CSSL_FP_FUNCTION_CALL_END();

	uint8_t hash[MCUXCLHASH_OUTPUT_SIZE_SHA_256];
    uint32_t hashOutputSize = 0u;

	MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result6, token6, mcuxClHash_finish(
	/* mcuxCLSession_Handle_t session: */ session,
	/* mcuxClHash_Context_t context:   */ (mcuxClHash_Context_t) context,
    /* mcuxCl_Buffer_t pOut            */ hash,
    /* uint32_t *const pOutSize,      */ &hashOutputSize
	));
	// mcuxClHash_finish is a flow-protected function: Check the protection token and the return value
	if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish) != token6) || (MCUXCLHASH_STATUS_OK != result6))
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

	uint8_t hashDifferent = 0u;
	for(size_t i = 0u; i < sizeof(hash); i++)
	{
		if(hashExpected[i] != hash[i])
		{
			hashDifferent |= 1u;
		}
	}
	
	if(hashDifferent)
	{
		return MCUXCLEXAMPLE_STATUS_ERROR;
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
