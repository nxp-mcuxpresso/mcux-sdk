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

/** @file  mcuxClMacModes_Helper.c
 *  @brief implementation of helper functions of mcuxClMacModes component */

#include <mcuxClToolchain.h>
#include <mcuxClMac.h>

#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxClHash.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>
#include <internal/mcuxClMacModes_Internal_Constants.h>
#include <internal/mcuxClMacModes_Internal_Functions.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_prepareHMACKey)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_prepareHMACKey(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    uint32_t * preparedHmacKey)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_prepareHMACKey);

    size_t alreadyFilledKeyDataSize = 0u;
    uint8_t *pPreparedHmacKey = (uint8_t *) preparedHmacKey;
    uint8_t *pKeyData = mcuxClKey_getLoadedKeyData(key);
    uint32_t keySize = mcuxClKey_getSize(key);

    if(mcuxClKey_getSize(key) <= MCUXCLMAC_HMAC_PADDED_KEY_SIZE)
    {
        /* Given key must be zero-padded up to MCUXCLMAC_HMAC_PADDED_KEY_SIZE */
        // TODO: use secure memory copy?
        MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pPreparedHmacKey,
                                                               pKeyData,
                                                               keySize,
                                                               MCUXCLMAC_HMAC_PADDED_KEY_SIZE);

        alreadyFilledKeyDataSize = keySize;
    }
    else
    {
        uint32_t hashOutputSize = 0u;
        /* Given key must be hashed and then zero-padded up to MCUXCLMAC_HMAC_PADDED_KEY_SIZE */
        MCUX_CSSL_FP_FUNCTION_CALL(hashResult, mcuxClHash_compute(session,
                                                                mcuxClHash_Algorithm_Sha256,
                                                                pKeyData,
                                                                (uint32_t) keySize,
                                                                pPreparedHmacKey,
                                                                &hashOutputSize));

        if(MCUXCLHASH_STATUS_OK != hashResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_prepareHMACKey, MCUXCLMAC_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute));
        }

        alreadyFilledKeyDataSize = MCUXCLHASH_OUTPUT_SIZE_SHA_256;
    }

    /* Zero-pad the key */
    MCUXCLMEMORY_FP_MEMORY_SET(pPreparedHmacKey + alreadyFilledKeyDataSize, 0u, MCUXCLMAC_HMAC_PADDED_KEY_SIZE - alreadyFilledKeyDataSize);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_prepareHMACKey, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL((mcuxClKey_getSize(key) <= MCUXCLMAC_HMAC_PADDED_KEY_SIZE),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
        ),
        MCUX_CSSL_FP_CONDITIONAL((mcuxClKey_getSize(key) > MCUXCLMAC_HMAC_PADDED_KEY_SIZE),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)
        ),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set)
    );
}
