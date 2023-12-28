/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClEls_KeyManagement.c
 *  @brief ELS implementation for key management.
 * This file implements the functions declared in mcuxClEls_KeyManagement.h. */

#include <platform_specific_headers.h>
#include <mcuxClEls_KeyManagement.h>    // Implement mcuxClEls interface "KeyManagement"
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <stdbool.h>
#include <mcuxClEls.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClEls_Internal.h>


// Implementation of mcuxClEls interface "KeyManagement"

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_KeyDelete_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_KeyDelete_Async(
        mcuxClEls_KeyIndex_t keyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_KeyDelete_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_KeyDelete_Async, (ELS_KS_CNT <= keyIdx));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {   
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyDelete_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

#ifdef MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING
    /* Get key properties */
    mcuxClEls_KeyProp_t key_properties;
    MCUX_CSSL_FP_FUNCTION_CALL(status_keyprop, mcuxClEls_GetKeyProperties(keyIdx, &key_properties));
    if(MCUXCLELS_STATUS_OK != status_keyprop)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyDelete_Async, MCUXCLELS_STATUS_SW_FAULT);
    }
    uint32_t drbg_counter_increase =
            ((key_properties.bits.ksize == MCUXCLELS_KEYPROPERTY_KEY_SIZE_128)
                    ? MCUXCLELS_RNG_DRBG_KEYDELETE128_INCREASE
                    : MCUXCLELS_RNG_DRBG_KEYDELETE256_INCREASE
            );

    /* Increment drbg_block_counter. If the counter overflowed, the interrupt handler will
     * reseed the DRBG and reset the counter after the upcoming ELS operation. */
    mcuxClEls_rng_drbg_block_counter += drbg_counter_increase;

    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties));
#endif /* MCUXCL_FEATURE_ELS_ITERATIVE_SEEDING */

    mcuxClEls_setKeystoreIndex0(keyIdx);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_KDELETE, 0U, ELS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyDelete_Async, MCUXCLELS_STATUS_OK_WAIT);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_KeyImport_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_KeyImport_Async(
    mcuxClEls_KeyImportOption_t options,
    uint8_t const * pImportKey,
    size_t importKeyLength,
    mcuxClEls_KeyIndex_t wrappingKeyIdx,
    mcuxClEls_KeyIndex_t targetKeyIdx)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_KeyImport_Async);
    /* Key indices out of bounds or the source key pointer is NULL although the key format indicates that it should be imported from memory */
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_KeyImport_Async,
                                         (wrappingKeyIdx >= ELS_KS_CNT)
                                         || (targetKeyIdx >= ELS_KS_CNT)
                                         || ((options.bits.kfmt == MCUXCLELS_KEYIMPORT_KFMT_RFC3394) && (importKeyLength == 0u)));
    
    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyImport_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    mcuxClEls_setKeystoreIndex0(wrappingKeyIdx);
    mcuxClEls_setKeystoreIndex1(targetKeyIdx);
    mcuxClEls_setInput0(pImportKey, importKeyLength);
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_KEYIN, options.word.value, ELS_CMD_BIG_ENDIAN);
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyImport_Async, MCUXCLELS_STATUS_OK_WAIT);
}

#ifdef MCUXCL_FEATURE_ELS_PUK_INTERNAL
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_KeyImportPuk_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_KeyImportPuk_Async(
    uint8_t const * pCertificate,
    size_t certificateLength,
    size_t publicKeyOffset,
    uint8_t const * pSignature,
    mcuxClEls_KeyIndex_t verifyingKeyIdx,
    mcuxClEls_KeyProp_t keyProperties,
    mcuxClEls_KeyIndex_t targetKeyIdx,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_KeyImportPuk_Async);

    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_KeyImportPuk_Async, (verifyingKeyIdx >= ELS_KS_CNT) || (targetKeyIdx >= ELS_KS_CNT));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyImportPuk_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }

    mcuxClEls_KeyImportOption_t options;
    options.word.value = 0u;
    options.bits.revf = MCUXCLELS_KEYIMPORT_REVERSEFETCH_ENABLE;
    options.bits.kfmt = MCUXCLELS_KEYIMPORT_KFMT_PBK;

    mcuxClEls_setInput0(pCertificate, certificateLength);
    mcuxClEls_setInput1_fixedSize(pSignature);
    mcuxClEls_setInput2_fixedSize((const uint8_t *) publicKeyOffset);

    mcuxClEls_setRequestedKeyProperties(keyProperties.word.value);
    mcuxClEls_setKeystoreIndex1(targetKeyIdx);
    mcuxClEls_setKeystoreIndex2(verifyingKeyIdx);

    mcuxClEls_setOutput_fixedSize(pOutput);

    mcuxClEls_startCommand(ID_CFG_ELS_CMD_KEYIN, options.word.value, ELS_CMD_BIG_ENDIAN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyImportPuk_Async, MCUXCLELS_STATUS_OK_WAIT);
}
#endif /* MCUXCL_FEATURE_ELS_PUK_INTERNAL */

static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_handleKeyExportError(uint8_t *pOutput, size_t keyLength, mcuxClEls_InterruptOptionEn_t interrupt_state_old)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_handleKeyExportError,
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_ResetIntFlags),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    /* Clear the interrupt state */
    mcuxClEls_InterruptOptionRst_t interrupt_options_1;
    interrupt_options_1.bits.elsint = MCUXCLELS_ELS_RESET_CLEAR;
    // no return value check in this call since mcuxClEls_ResetIntFlags always returns OK
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_ResetIntFlags(interrupt_options_1));

    /* Restore the ELS interrupt settings */
    // no return value check in this call since mcuxClEls_SetIntEnableFlags always returns OK
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_SetIntEnableFlags(interrupt_state_old));

    /* clear the memory to which the key was exported */
    // no return value check in this call since MCUXCLELS_STATUS_SW_FAULT gets returned anyway
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_set(pOutput, 0x00, keyLength, keyLength));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_handleKeyExportError, MCUXCLELS_STATUS_SW_FAULT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_KeyExport_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_KeyExport_Async(
    mcuxClEls_KeyIndex_t wrappingKeyIdx,
    mcuxClEls_KeyIndex_t exportKeyIdx,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_KeyExport_Async);

    /* Key indices out of bounds or the source key pointer is NULL although the key format indicates that it should be imported from memory */
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_KeyExport_Async, wrappingKeyIdx >= ELS_KS_CNT || exportKeyIdx >= ELS_KS_CNT);
    
    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    /* ELS KEYOUT */
    mcuxClEls_setKeystoreIndex0(wrappingKeyIdx);
    mcuxClEls_setKeystoreIndex1(exportKeyIdx);
    mcuxClEls_setOutput_fixedSize(pOutput);
 
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetIntEnableFlags),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags));

    /* Save current ELS interrupts state */
    mcuxClEls_InterruptOptionEn_t interrupt_state;

    MCUX_CSSL_FP_FUNCTION_CALL(status_get, mcuxClEls_GetIntEnableFlags(&interrupt_state));

    if(MCUXCLELS_STATUS_OK != status_get)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_SW_FAULT);
    }

    /* Disable ELS interrupts */
    mcuxClEls_InterruptOptionEn_t interrupt_state_new = interrupt_state;
    interrupt_state_new.bits.elsint = MCUXCLELS_ELS_INTERRUPT_DISABLE;

    MCUX_CSSL_FP_FUNCTION_CALL(status_set, mcuxClEls_SetIntEnableFlags(interrupt_state_new));

    if(MCUXCLELS_STATUS_OK != status_set)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_SW_FAULT);
    }


    /* Start KEYOUT command */
    mcuxClEls_startCommand(ID_CFG_ELS_CMD_KEYOUT, 0U, ELS_CMD_BIG_ENDIAN);



    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));

    /* Wait for operation ELS KEYOUT */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_KEEP)); // flags not cleared because the error is caught in the wait for operation after this function exits

    if(MCUXCLELS_STATUS_OK != status_wait)
    {
        // no return value check in this call since mcuxClEls_SetIntEnableFlags always returns OK
        // In case of interrupt driven operation the error will be caught by the interrupt handler since re-enabling the interrupt when ELS_IRQ is set will immediately trigger an interrupt
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_SetIntEnableFlags(interrupt_state));

        // OK_WAIT is returned here so that the error can be captured by the wait for operation following this function
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_OK_WAIT,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags));
    }

    MCUX_CSSL_FP_EXPECT(
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyImport_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags));

    /* Save key properties */
    mcuxClEls_KeyProp_t key_properties;

    MCUX_CSSL_FP_FUNCTION_CALL(status_keyprop, mcuxClEls_GetKeyProperties(exportKeyIdx, &key_properties));

    if(MCUXCLELS_STATUS_OK != status_keyprop)
    {
        // no return value check in this call since mcuxClEls_SetIntEnableFlags always returns OK
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_SetIntEnableFlags(interrupt_state));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_SW_FAULT,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_SetIntEnableFlags));
    }

    size_t key_length = (key_properties.bits.ksize == MCUXCLELS_KEYPROPERTY_KEY_SIZE_128) ? MCUXCLELS_RFC3394_CONTAINER_SIZE_128 : MCUXCLELS_RFC3394_CONTAINER_SIZE_256;

    /* ELS KDELETE */
    MCUX_CSSL_FP_FUNCTION_CALL(status_delete, mcuxClEls_KeyDelete_Async(exportKeyIdx));

    if(MCUXCLELS_STATUS_OK_WAIT != status_delete)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async,
                                  mcuxClEls_handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }
    
    /* wait for ELS KDELETE */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    if(MCUXCLELS_STATUS_OK != status_wait1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async,
                                  mcuxClEls_handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }

    /* ELS KEYIN */
    mcuxClEls_KeyImportOption_t import_options;
    import_options.word.value = 0U;
    import_options.bits.kfmt = MCUXCLELS_KEYIMPORT_KFMT_RFC3394;
    
    MCUX_CSSL_FP_FUNCTION_CALL(status_import, 
                    mcuxClEls_KeyImport_Async(
                        import_options,
                        pOutput,
                        key_length,
                        wrappingKeyIdx,
                        exportKeyIdx
                    ));
    
    if(MCUXCLELS_STATUS_OK_WAIT != status_import)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async,
                                  mcuxClEls_handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }
    
    /* wait for ELS KEYIN */
    MCUX_CSSL_FP_FUNCTION_CALL(status_wait2, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    if(MCUXCLELS_STATUS_OK != status_wait2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async,
                                  mcuxClEls_handleKeyExportError(pOutput, key_length, interrupt_state),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
    }

    /* Restore ELS interrupt state - will trigger an interrupt immediately if interrupt is enabled since ELS_IRQ is expected to be set at this point */
    MCUX_CSSL_FP_FUNCTION_CALL(status_set1, mcuxClEls_SetIntEnableFlags(interrupt_state));
    if(MCUXCLELS_STATUS_OK != status_set1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_SW_FAULT);
    }

    
    /* Exit function */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_KeyExport_Async, MCUXCLELS_STATUS_OK_WAIT);
}

/** Exports the properties of the keys stored in the ELS internal keystore */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_GetKeyProperties)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_GetKeyProperties(
    mcuxClEls_KeyIndex_t keyIdx,
    mcuxClEls_KeyProp_t * pKeyProp
    ) 
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_GetKeyProperties);
    MCUXCLELS_INPUT_PARAM_CHECK_PROTECTED(mcuxClEls_GetKeyProperties, (ELS_KS_CNT <= keyIdx));

    /* ELS SFRs are not cached => Tell SW to wait for ELS to come back from BUSY state before modifying the SFRs */
    if (mcuxClEls_isBusy())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_GetKeyProperties, MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT);
    } 
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_HARDWARE_ACCESS("Sfr offset from address")
    pKeyProp->word.value = ((const volatile uint32_t *) (&MCUXCLELS_SFR_READ(ELS_KS0)))[keyIdx];
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_HARDWARE_ACCESS()

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_GetKeyProperties, MCUXCLELS_STATUS_OK);
}
