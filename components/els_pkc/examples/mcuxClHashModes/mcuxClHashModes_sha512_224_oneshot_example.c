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

#include <mcuxClEls.h>              // Interface to the entire mcuxClEls component
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClToolchain.h>        // memory segment definitions
#include <mcuxClSession.h>          // Interface to the entire mcuxClSession component
#include <mcuxClHash.h>             // Interface to the entire mcuxClHash component
#include <mcuxClHashModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_RNG_Helper.h>

static const ALIGNED uint8_t data[3] CSS_CONST_SEGMENT = {
    0x61u, 0x62u, 0x63u
};

static const ALIGNED uint8_t hashExpected[28] CSS_CONST_SEGMENT = {
    0x46u, 0x34u, 0x27u, 0x0Fu, 0x70u, 0x7Bu, 0x6Au, 0x54u,
    0xDAu, 0xAEu, 0x75u, 0x30u, 0x46u, 0x08u, 0x42u, 0xE2u,
    0x0Eu, 0x37u, 0xEDu, 0x26u, 0x5Cu, 0xEEu, 0xE9u, 0xA4u,
    0x3Eu, 0x89u, 0x24u, 0xAAu
};

MCUXCLEXAMPLE_FUNCTION(mcuxClHashModes_sha512_224_oneshot_example)
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
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLEXAMPLE_MAX_WA(MCUXCLHASH_MAX_CPU_WA_BUFFER_SIZE, MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE), 0u);

    /* Initialize the PRNG */
    MCUXCLEXAMPLE_INITIALIZE_PRNG(session);

    /**************************************************************************/
    /* Hash computation                                                       */
    /**************************************************************************/

    ALIGNED uint8_t hash[MCUXCLHASH_OUTPUT_SIZE_SHA_512_224];
    MCUXCLBUFFER_INIT_RW(hashBuf, session, hash, sizeof(hash));
    MCUXCLBUFFER_INIT_RO(dataBuf, session, data, sizeof(data));

    uint32_t hashOutputSize = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token2, mcuxClHash_compute(
    /* mcuxClSession_Handle_t session: */ session,
    /* mcuxClHash_Algo_t algorithm:    */ mcuxClHash_Algorithm_Sha512_224,
    /* mcuxCl_InputBuffer_t pIn:       */ dataBuf,
    /* uint32_t inSize:               */ sizeof(data),
    /* mcuxCl_Buffer_t pOut            */ hashBuf,
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
    for(size_t i = 0u; i < sizeof(hash); i++)
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
