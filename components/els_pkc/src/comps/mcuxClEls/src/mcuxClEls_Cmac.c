/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

/** @file  mcuxClEls_Cmac.c
 *  @brief ELS implementation for CMAC support.
 * This file implements the functions declared in mcuxClEls_Cmac.h. */

#include <platform_specific_headers.h>
#include <mcuxClEls_Cmac.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

#define MCUXCLELS_CMAC_STATE_IN_DISABLE     0U ///< Set #mcuxClEls_CmacOption_t.sie to this value to use the CMAC state that is present inside ELS
#define MCUXCLELS_CMAC_STATE_IN_ENABLE      1U ///< Set #mcuxClEls_CmacOption_t.sie to this value to import the CMAC state from memory
#define MCUXCLELS_CMAC_STATE_OUT_DISABLE    0U ///< Set #mcuxClEls_CmacOption_t.soe to this value to keep the CMAC state inside ELS at the end of the command
#define MCUXCLELS_CMAC_STATE_OUT_ENABLE     1U ///< Set #mcuxClEls_CmacOption_t.soe to this value to export the CMAC state to memory at the end of the command

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_Cmac_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Cmac_Async(
    mcuxClEls_CmacOption_t options,
    mcuxClEls_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pMac)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_Cmac_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_Cmac_Async, (MCUXCLELS_CMAC_EXTERNAL_KEY_DISABLE == options.bits.extkey && ELS_KS_CNT <= keyIdx) || (MCUXCLELS_CMAC_EXTERNAL_KEY_ENABLE == options.bits.extkey && ((MCUXCLELS_CMAC_KEY_SIZE_128 != keyLength) && (MCUXCLELS_CMAC_KEY_SIZE_256 != keyLength))));


    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Cmac_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    if(MCUXCLELS_CMAC_INITIALIZE_ENABLE == options.bits.initialize)
    {
        options.bits.sie = MCUXCLELS_CMAC_STATE_IN_DISABLE;
    }
    else
    {
        options.bits.sie = MCUXCLELS_CMAC_STATE_IN_ENABLE;
    }
    if(MCUXCLELS_CMAC_FINALIZE_ENABLE == options.bits.finalize)
    {
        options.bits.soe = MCUXCLELS_CMAC_STATE_OUT_DISABLE;
    }
    else
    {
         options.bits.soe = MCUXCLELS_CMAC_STATE_OUT_ENABLE;
    }

    if (0U == options.bits.extkey)
    {
        mcuxClEls_setKeystoreIndex0(keyIdx);
    }
    else
    {
        mcuxClEls_setInput2(pKey, keyLength);
    }

    mcuxClEls_setInput0(pInput, inputLength);
    mcuxClEls_setInput1_fixedSize(pMac);
    mcuxClEls_setOutput_fixedSize(pMac);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_CMAC, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_Cmac_Async, MCUXCLELS_STATUS_OK_WAIT);
}
