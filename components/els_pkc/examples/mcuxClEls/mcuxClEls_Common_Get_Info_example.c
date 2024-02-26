/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022-2023 NXP                                            */
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
 * @file  mcuxClEls_Common_Get_Info_example.c
 * @brief Example of version and configuration load functions.
 *
 * @example mcuxClEls_Common_Get_Info_example.c
 * @brief   Example of version and configuration load functions.
 */

#include <mcuxCl_clns.h> // Test the CLNS component-independent functionality
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>

MCUXCLEXAMPLE_FUNCTION(mcuxClEls_Common_Get_Info_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    // Read the ELS hardware version.
    mcuxClEls_HwVersion_t hw_version;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GetHwVersion(&hw_version));
    // mcuxClEls_GetHwVersion is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwVersion) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    // Access and store hw_version struct elements
    uint32_t revision = hw_version.bits.revision;                                        // Extended revision version
    uint32_t minor = hw_version.bits.minor;                                              // Minor version
    uint32_t major = hw_version.bits.major;                                              // Major version
    (void) revision;
    (void) minor;
    (void) major;
#if MCUXCL_FEATURE_ELS_GET_FW_VERSION == 0
    uint32_t level = hw_version.bits.level;                                              // Release level version
    (void) level;
#else /* MCUXCL_FEATURE_ELS_GET_FW_VERSION == 0 */
    uint32_t fw_revision = hw_version.bits.fw_revision;                                  // Firmware Extended revision version
    uint32_t fw_minor = hw_version.bits.fw_minor;                                        // Firmware Minor version
    uint32_t fw_major = hw_version.bits.fw_major;                                        // Firmware Major version
    (void) fw_revision;
    (void) fw_minor;
    (void) fw_major;
#endif /* MCUXCL_FEATURE_ELS_GET_FW_VERSION == 0 */

#ifdef MCUXCL_FEATURE_ELS_HWCONFIG
    // Read the ELS hardware configuration bitmap.
    mcuxClEls_HwConfig_t config;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GetHwConfig(&config));
    // mcuxClEls_GetHwConfig is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetHwConfig) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    // Access and store config struct elements
    uint32_t ciphersup = config.bits.ciphersup;                                          // cipher command not supported
    uint32_t authciphersup = config.bits.authciphersup;                                  // auth_cipher command not supported
    uint32_t ecsignsup = config.bits.ecsignsup;                                          // ecsign command not supported
    uint32_t ecvfysup = config.bits.ecvfysup;                                            // ecvfy command not supported
    uint32_t eckxchsup = config.bits.eckxchsup;                                          // dhkey_xch command is supported
    uint32_t keygensup = config.bits.keygensup;                                          // keygen command not supported
    uint32_t keyinsup = config.bits.keyinsup;                                            // keyin command not supported
    uint32_t keyoutsup = config.bits.keyoutsup;                                          // keyout command  not supported
    uint32_t kdeletesup = config.bits.kdeletesup;                                        // kdelete command not supported
    uint32_t ckdfsup = config.bits.ckdfsup;                                              // ckdf command not supported
    uint32_t hkdfsup = config.bits.hkdfsup;                                              // hkdf command not supported
    uint32_t tlsinitsup = config.bits.tlsinitsup;                                        // tls_init command not supported
    uint32_t hashsup = config.bits.hashsup;                                              // hash command not supported
    uint32_t hmacsup = config.bits.hmacsup;                                              // hmac command not supported
    uint32_t drbgreqsub = config.bits.drbgreqsub;                                        // drbg_req command not supported
    uint32_t dtrgncfgloadsup = config.bits.dtrgncfgloadsup;                              // dtrng_cfg_load command is not supported
    uint32_t dtrngevalsup = config.bits.dtrngevalsup;                                    // dtrng_eval command not supported

    char const* sw_version = mcuxCl_GetVersion();                                         // Read the CLNS version string that uniquely identifies this release of the CLNS.
                                                                                         // MCUXCL_VERSION_MAX_SIZE is the maximum size in bytes of the version string.

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
#endif
    return MCUXCLEXAMPLE_STATUS_OK;
}

