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

#include <mcuxClRandom.h>
#include <mcuxClSession.h>
#include <mcuxClEls.h>
#include <mcuxClMemory.h>
#include <mcuxClAes.h>

#include <mcuxClEls.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_CtrDrbg.h>
#include <internal/mcuxClRandomModes_Private_CtrDrbg_BlockCipher.h>
#include <internal/mcuxClRandomModes_Private_NormalMode.h>
#include <internal/mcuxClTrng_Internal.h>
#include <internal/mcuxClMemory_Copy_Internal.h>
#include <internal/mcuxClEls_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_DRBG_AES_Internal_blockcipher)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_DRBG_AES_Internal_blockcipher(
    uint32_t const *pV,
    uint32_t const *pKey,
    uint8_t *pOut,
    uint32_t keyLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRandomModes_DRBG_AES_Internal_blockcipher);

    uint8_t elsOut[MCUXCLAES_BLOCK_SIZE];

    mcuxClEls_CipherOption_t cipher_options = {0};
    cipher_options.bits.cphmde = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB;
    cipher_options.bits.dcrpt = MCUXCLELS_CIPHER_ENCRYPT;
    cipher_options.bits.extkey = MCUXCLELS_CIPHER_EXTERNAL_KEY;
    MCUX_CSSL_ANALYSIS_START_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()
    MCUX_CSSL_FP_FUNCTION_CALL(result_cipher, mcuxClEls_Cipher_Async(
                cipher_options,
                (mcuxClEls_KeyIndex_t)0U,
                (uint8_t const *)pKey,
                keyLength,
                (uint8_t const *)pV,
                MCUXCLAES_BLOCK_SIZE,
                NULL,
                elsOut));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_ADDRESS_IN_SFR_IS_NOT_REUSED_OUTSIDE()    
    if (MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT == result_cipher)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_DRBG_AES_Internal_blockcipher, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async));
    }
    else if (MCUXCLELS_STATUS_OK_WAIT != result_cipher)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_DRBG_AES_Internal_blockcipher, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result_wait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if(MCUXCLELS_LEVEL1_ERROR(result_wait))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_DRBG_AES_Internal_blockcipher, MCUXCLRANDOM_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async));
    }
    else if (MCUXCLELS_STATUS_OK != result_wait)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_DRBG_AES_Internal_blockcipher, MCUXCLRANDOM_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Intentionally left empty */
    }

    /* Copy the bytes from the buffer to output. */
    MCUXCLMEMORY_FP_MEMORY_COPY(pOut, elsOut, MCUXCLAES_BLOCK_SIZE);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRandomModes_DRBG_AES_Internal_blockcipher, MCUXCLRANDOM_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async));
}
