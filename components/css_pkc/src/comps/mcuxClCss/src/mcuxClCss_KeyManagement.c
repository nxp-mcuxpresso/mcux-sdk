/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClCss_KeyManagement.c
 *  @brief CSSv2 implementation for key management.
 * This file implements the functions declared in mcuxClCss_KeyManagement.h. */

#include <mcuxClCss_KeyManagement.h>    // Implement mcuxClCss interface "KeyManagement"
#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClCss.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClCss_Internal.h>


// Implementation of mcuxClCss interface "KeyManagement"

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_KeyDelete_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_KeyDelete_Async(
        mcuxClCss_KeyIndex_t keyIdx)
{   
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_KeyDelete_Async);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_KeyDelete_Async, (CSS_KS_CNT <= keyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {   
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyDelete_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    MCUXCLCSS_SETKEYSTOREINDEX0(keyIdx);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_KDELETE, 0U, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyDelete_Async, MCUXCLCSS_STATUS_OK_WAIT);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_KeyImport_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_KeyImport_Async(
    mcuxClCss_KeyImportOption_t options,
    uint8_t const * pImportKey,
    size_t importKeyLength,
    mcuxClCss_KeyIndex_t wrappingKeyIdx,
    mcuxClCss_KeyIndex_t targetKeyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_KeyImport_Async);
    /* Key indices out of bounds or the source key pointer is NULL although the key format indicates that it should be imported from memory */
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_KeyImport_Async,
                                         (wrappingKeyIdx >= CSS_KS_CNT)
                                         || (targetKeyIdx >= CSS_KS_CNT)
                                         || ((options.bits.kfmt == MCUXCLCSS_KEYIMPORT_KFMT_RFC3394) && (importKeyLength == 0u)));
    
    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyImport_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    MCUXCLCSS_SETKEYSTOREINDEX0(wrappingKeyIdx);
    MCUXCLCSS_SETKEYSTOREINDEX1(targetKeyIdx);
    MCUXCLCSS_SETCSSINPUT0(pImportKey, importKeyLength);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_KEYIN, options.word.value, CSS_CMD_BIG_ENDIAN);
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyImport_Async, MCUXCLCSS_STATUS_OK_WAIT);
}


static mcuxClCss_Status_Protected_t handleKeyExportError(uint8_t *pOutput, size_t key_length, mcuxClCss_InterruptOptionEn_t interrupt_state_old)
{
    /* Clear the interrupt state */
    mcuxClCss_InterruptOptionRst_t interrupt_options_1 = {0U};
    interrupt_options_1.bits.cssint = MCUXCLCSS_CSS_RESET_CLEAR;
    // no FP in this call since mcuxClCss_ResetIntFlags always returns OK
    (void)mcuxClCss_ResetIntFlags(interrupt_options_1);

    /* Restore the CSS interrupt settings */
    // no FP in this call since mcuxClCss_SetIntEnableFlags always returns OK
    (void)mcuxClCss_SetIntEnableFlags(interrupt_state_old);

    /* clear the memory to which the key was exported */
    // no FP in this call since MCUXCLCSS_STATUS_SW_FAULT gets returned anyway
    (void)mcuxClMemory_set(pOutput, 0x00, key_length, key_length);

    return MCUXCLCSS_STATUS_SW_FAULT;
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_KeyExport_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_KeyExport_Async(
    mcuxClCss_KeyIndex_t wrappingKeyIdx,
    mcuxClCss_KeyIndex_t exportKeyIdx,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_KeyExport_Async);
    /* Key indices out of bounds or the source key pointer is NULL although the key format indicates that it should be imported from memory */
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_KeyExport_Async, wrappingKeyIdx >= CSS_KS_CNT || exportKeyIdx >= CSS_KS_CNT);
    
    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    /* CSS KEYOUT */
    MCUXCLCSS_SETKEYSTOREINDEX0(wrappingKeyIdx);
    MCUXCLCSS_SETKEYSTOREINDEX1(exportKeyIdx);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pOutput);
 
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetIntEnableFlags),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_SetIntEnableFlags));

    /* Save current CSS interrupts state */
    mcuxClCss_InterruptOptionEn_t interrupt_state;

    MCUX_CSSL_FP_FUNCTION_CALL(status_get, mcuxClCss_GetIntEnableFlags(&interrupt_state));

    if(MCUXCLCSS_STATUS_OK != status_get)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_SW_FAULT);
    }

    /* Disable CSS interrupts */
    mcuxClCss_InterruptOptionEn_t interrupt_state_new = interrupt_state;
    interrupt_state_new.bits.cssint = MCUXCLCSS_CSS_INTERRUPT_DISABLE;

    MCUX_CSSL_FP_FUNCTION_CALL(status_set, mcuxClCss_SetIntEnableFlags(interrupt_state_new));

    if(MCUXCLCSS_STATUS_OK != status_set)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_SW_FAULT);
    }

    /* Start KEYOUT command */
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_KEYOUT, 0U, CSS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));

    /* Wait for operation CSS KEYOUT */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_KEEP)); // flags not cleared because the error is caught in the wait for operation after this function exits

    if(MCUXCLCSS_STATUS_OK != status_wait)
    {
        // no FP in this call since mcuxClCss_SetIntEnableFlags always returns OK
        // In case of interrupt driven operation the error will be caught by the interrupt handler since re-enabling the interrupt when CSS_IRQ is set will immediately trigger an interrupt
        (void)mcuxClCss_SetIntEnableFlags(interrupt_state);

        // OK_WAIT is returned here so that the error can be captured by the wait for operation following this function
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_OK_WAIT);
    }

    MCUX_CSSL_FP_EXPECT(
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetKeyProperties),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_KeyDelete_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_KeyImport_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_SetIntEnableFlags));

    /* Save key properties */
    mcuxClCss_KeyProp_t key_properties;

    MCUX_CSSL_FP_FUNCTION_CALL(status_keyprop, mcuxClCss_GetKeyProperties(exportKeyIdx, &key_properties));

    if(MCUXCLCSS_STATUS_OK != status_keyprop)
    {
        // no FP in this call since mcuxClCss_SetIntEnableFlags always returns OK
        (void)mcuxClCss_SetIntEnableFlags(interrupt_state);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_SW_FAULT);
    }

    size_t key_length = (key_properties.bits.ksize == MCUXCLCSS_KEYPROPERTY_KEY_SIZE_128) ? MCUXCLCSS_RFC3394_CONTAINER_SIZE_128 : MCUXCLCSS_RFC3394_CONTAINER_SIZE_256;

    /* CSS KDELETE */
    MCUX_CSSL_FP_FUNCTION_CALL(status_delete, mcuxClCss_KeyDelete_Async(exportKeyIdx));

    if(MCUXCLCSS_STATUS_OK_WAIT != status_delete)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async,
                                  handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }
    
    /* wait for CSS KDELETE */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait1, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

    if(MCUXCLCSS_STATUS_OK != status_wait1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async,
                                  handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }

    /* CSS KEYIN */
    mcuxClCss_KeyImportOption_t import_options;
    import_options.word.value = 0U;
    import_options.bits.kfmt = MCUXCLCSS_KEYIMPORT_KFMT_RFC3394;
    
    MCUX_CSSL_FP_FUNCTION_CALL(status_import, 
                    mcuxClCss_KeyImport_Async(
                        import_options,
                        pOutput,
                        key_length,
                        wrappingKeyIdx,
                        exportKeyIdx
                    ));
    
    if(MCUXCLCSS_STATUS_OK_WAIT != status_import)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async,
                                  handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }
    
    /* wait for CSS KEYIN */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait2, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

    if(MCUXCLCSS_STATUS_OK != status_wait2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async,
                                  handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }

    /* Restore CSS interrupt state - will trigger an interrupt immediately if interrupt is enabled since CSS_IRQ is expected to be set at this point */
    MCUX_CSSL_FP_FUNCTION_CALL(status_set1, mcuxClCss_SetIntEnableFlags(interrupt_state));
    if(MCUXCLCSS_STATUS_OK != status_set1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_SW_FAULT);
    }

    
    /* Exit function */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_KeyExport_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

/** Exports the properties of the keys stored in the CSS internal keystore */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetKeyProperties)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetKeyProperties(
    mcuxClCss_KeyIndex_t keyIdx,
    mcuxClCss_KeyProp_t * pKeyProp
    ) 
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetKeyProperties);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_GetKeyProperties, (CSS_KS_CNT <= keyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetKeyProperties, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    } 

    pKeyProp->word.value = ((const volatile uint32_t *) (&IP_CSS->CSS_KS0))[keyIdx];

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetKeyProperties, MCUXCLCSS_STATUS_OK);
}
