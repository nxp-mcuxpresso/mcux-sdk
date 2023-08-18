/*
 *     Copyright 2020-2023 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_iped.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iped"
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t IPED_ELS_check_key(uint8_t keyIdx, mcuxClEls_KeyProp_t *pKeyProp);
static status_t IPED_ELS_gen_iv_key(void);
static status_t IPED_ELS_enable(void);
static status_t IPED_ELS_calculate_iv(uint32_t *IvReg);
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t IPED_SetRegionAddressRange(FLEXSPI_Type *base,
                                    iped_region_t region,
                                    uint32_t start_address,
                                    uint32_t end_address)
{
    status_t status = kStatus_Fail;

    do
    {
        /* Check if region is not locked */
        if ((base->IPEDCTXCTRL[1] & (FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE1_MASK << (region * 2u))) !=
            (IPED_RW_ENABLE_VAL << (region * 2u)))
        {
            status = kStatus_IPED_RegionIsLocked;
            break;
        }

        /* Disable soft lock for given region first */
        base->IPEDCTXCTRL[0] =
            (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
            (IPED_RW_ENABLE_VAL << (region * 2u));

        switch (region)
        {
            case kIPED_Region0:
                base->IPEDCTX0START = start_address;
                base->IPEDCTX0END   = end_address;
                status              = kStatus_Success;
                break;

            case kIPED_Region1:
                base->IPEDCTX1START = start_address;
                base->IPEDCTX1END   = end_address;
                status              = kStatus_Success;
                break;

            case kIPED_Region2:
                base->IPEDCTX2START = start_address;
                base->IPEDCTX2END   = end_address;
                status              = kStatus_Success;
                break;

            case kIPED_Region3:
                base->IPEDCTX3START = start_address;
                base->IPEDCTX3END   = end_address;
                status              = kStatus_Success;
                break;

            default:
                status = kStatus_InvalidArgument;
                break;
        }

        /* Re-enable soft lock for given region */
        base->IPEDCTXCTRL[0] =
            (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
            (IPED_RW_DISABLE_VAL << (region * 2u));
    } while (0);

    return status;
}

status_t IPED_GetRegionAddressRange(FLEXSPI_Type *base,
                                    iped_region_t region,
                                    uint32_t *start_address,
                                    uint32_t *end_address)
{
    status_t status = kStatus_Fail;

    switch (region)
    {
        case kIPED_Region0:
            *start_address = base->IPEDCTX0START;
            *end_address   = base->IPEDCTX0END;
            status         = kStatus_Success;
            break;

        case kIPED_Region1:
            *start_address = base->IPEDCTX1START;
            *end_address   = base->IPEDCTX1END;
            status         = kStatus_Success;
            break;

        case kIPED_Region2:
            *start_address = base->IPEDCTX2START;
            *end_address   = base->IPEDCTX2END;
            status         = kStatus_Success;
            break;

        case kIPED_Region3:
            *start_address = base->IPEDCTX3START;
            *end_address   = base->IPEDCTX3END;
            status         = kStatus_Success;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

status_t IPED_SetRegionIV(FLEXSPI_Type *base, iped_region_t region, const uint8_t iv[8])
{
    status_t status = kStatus_Fail;

    switch (region)
    {
        case kIPED_Region0:
            base->IPEDCTX0IV0 = ((uint32_t *)(uintptr_t)iv)[0];
            base->IPEDCTX0IV1 = ((uint32_t *)(uintptr_t)iv)[1];
            status            = kStatus_Success;
            break;

        case kIPED_Region1:
            base->IPEDCTX1IV0 = ((uint32_t *)(uintptr_t)iv)[0];
            base->IPEDCTX1IV1 = ((uint32_t *)(uintptr_t)iv)[1];
            status            = kStatus_Success;
            break;

        case kIPED_Region2:
            base->IPEDCTX2IV0 = ((uint32_t *)(uintptr_t)iv)[0];
            base->IPEDCTX2IV1 = ((uint32_t *)(uintptr_t)iv)[1];
            status            = kStatus_Success;
            break;

        case kIPED_Region3:
            base->IPEDCTX3IV0 = ((uint32_t *)(uintptr_t)iv)[0];
            base->IPEDCTX3IV1 = ((uint32_t *)(uintptr_t)iv)[1];
            status            = kStatus_Success;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

/*!
 * @brief Configures IPED setting.
 *
 * This function does the initial IPED configuration via ROM IAP API call.
 * IPED_SR_x configuration for each region configuration is stored into FFR (CMPA).
 * IPED IV erase counters (MCTR_INT_IV_CTRx) in CFPA are updated accordingly.
 *
 * Note: This function is expected to be called once in the device lifetime,
 * typically during the initial device provisioning (especially if programming the CMPA pages in PFR flash is enabled).
 * Note: Disabling IPED can be only done via ISP/SB file commands provided before ROM boot execution.
 * these commands will have to set IPED start & end addresses and ENABLE bits in CMPA page accordingly.
 *
 * @param coreCtx The pointer to the ROM API driver context structure.
 * @param config The pointer to the IPED driver configuration structure.
 * @param lock The CMPA IPEDx_START bits[1:0] 01 - Enabled, 10,11 - Enabled & locked
 * @param writeCmpa If selected, IPED configuration will be programmed in PFR flash using ROM API. Note: This can not be
 * reverted!!
 *
 * @retval #kStatus_Success
 * @retval #kStatus_CommandUnsupported
 * @retval #kStatus_InvalidArgument
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatusMemoryRangeInvalid
 * @retval #kStatus_Fail
 * @retval #kStatus_OutOfRange
 * @retval #kStatus_SPI_BaudrateNotSupport
 */
status_t IPED_Configure(api_core_context_t *coreCtx,
                        flexspi_iped_region_arg_t *config,
                        iped_lock_t lock,
                        iped_cmpa_t writeCmpa)
{
    status_t status = kStatus_Fail;
    flash_config_t flash_config;
    IPED_CMPA_page cmpa_buffer = {0};

    /* Enable ELS and check keys */
    if (kStatus_Success != IPED_ELS_enable())
    {
        return kStatus_Fail;
    }

    /* Check input argument */
    if (((lock != kIPED_RegionLock) && (lock != kIPED_RegionUnlock)) ||
        ((writeCmpa != kIPED_SkipCMPA) && (writeCmpa != kIPED_WriteCMPA)))
    {
        return kStatus_InvalidArgument;
    }

    /* Prepare IPED configuration structure */
    uint32_t config_option_iped[3] = {(IPED_TAG << IPED_TAG_SHIFT) | config->option.iped_region, config->start,
                                      config->end};

    /* Configure IPED via ROM API, ROM API will provide config parameter check */
    status = MEM_Config(coreCtx, config_option_iped, kMemoryFlexSpiNor);
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (writeCmpa == kIPED_WriteCMPA)
    {
        /* Clean up Flash driver structure and Init*/
        memset(&flash_config, 0, sizeof(flash_config_t));
        if (FLASH_Init(&flash_config) != kStatus_Success)
        {
            return kStatus_Fail;
        }

        /* FFR Init */
        if (FFR_Init(&flash_config) != kStatus_Success)
        {
            return kStatus_Fail;
        }

        /* Read whole CMPA page */
        status = FFR_GetCustomerData(&flash_config, (uint8_t *)&cmpa_buffer, 0u, CMPA_PAGE_SIZE);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        switch (config->option.iped_region)
        {
            case kIPED_Region0:
                cmpa_buffer.IPED0_START = (config->start & IPED_ADDRESS_MASK) | (lock & IPED_ENABLE_MASK);
                cmpa_buffer.IPED0_END   = config->end;
                break;
            case kIPED_Region1:
                cmpa_buffer.IPED1_START = (config->start & IPED_ADDRESS_MASK) | (lock & IPED_ENABLE_MASK);
                cmpa_buffer.IPED1_END   = config->end;
                break;
            case kIPED_Region2:
                cmpa_buffer.IPED2_START = (config->start & IPED_ADDRESS_MASK) | (lock & IPED_ENABLE_MASK);
                cmpa_buffer.IPED2_END   = config->end;
                break;
            case kIPED_Region3:
                cmpa_buffer.IPED3_START = (config->start & IPED_ADDRESS_MASK) | (lock & IPED_ENABLE_MASK);
                cmpa_buffer.IPED3_END   = config->end;
                break;
            default:
                return kStatus_InvalidArgument;
        }
        /* Write new CMPA page into FFR */
        status = FFR_CustFactoryPageWrite(&flash_config, (uint8_t *)&cmpa_buffer, false /* do not seal PFR memory */);
    }

    /* Lock the IPED IP setting if desired */
    if (lock == kIPED_RegionLock)
    {
        IPED_SetLock(FLEXSPI0, config->option.iped_region);
    }

    return status;
}

/*!
 * @brief Configures IPED setting.
 *
 * This function is used to re-configure IPED IP based on configuration stored in FFR.
 * This function also needs to be called after wake up from power-down mode to regenerate IV
 * encryption key in ELS key store whose presence is necessary for correct IPED operation
 * during erase and write operations to encrypted regions of internal flash memory
 * (dependency for correct operation of MEM_Erase() and MEM_Write() after wake up from power-down mode).
 *
 * @param coreCtx The pointer to the ROM API driver context structure.
 * @param config The pointer to the IPED driver configuration structure. If NULL CMPA configuration is used instead.
 * Note: when providing config structure, you have to call Reconfigure for each IPED region individually starting with
 * Region 0. Region 0 must be enabled as a base region.
 *
 * @retval #kStatus_Success
 * @retval #kStatus_Fail
 */
status_t IPED_Reconfigure(api_core_context_t *coreCtx, flexspi_iped_region_arg_t *config)
{
    status_t status   = kStatus_Fail;
    uint32_t IvReg[4] = {0};
    uint32_t ivEraseCounter[4];
    uint32_t ipedConfig[8];
    uint32_t ipedStart[4];
    uint32_t ipedEnd[4];
    uint8_t lockEnable[4];
    uint32_t uuid[4];
    flash_config_t flash_config;

    /* Enable ELS and check keys */
    status = IPED_ELS_enable();
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    /* Clean up Flash driver structure and Init*/
    memset(&flash_config, 0, sizeof(flash_config_t));
    if (FLASH_Init(&flash_config) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* FFR Init */
    if (FFR_Init(&flash_config) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Get UUID from FFR */
    status = FFR_GetUUID(&flash_config, (uint8_t *)uuid);
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    /* Check version of CFPA scratch first */
    uint32_t cfpaScratchVer = 0u;
    memcpy(&cfpaScratchVer, (void *)(CFPA_SCRATCH_VER), sizeof(uint32_t));

    /* Get CFPA version using FFR ROM API */
    uint32_t cfpaVer = 0u;
    if (kStatus_Success !=
        FFR_GetCustomerInfieldData(&flash_config, (uint8_t *)&cfpaVer, CFPA_VER_OFFSET, sizeof(uint32_t)))
    {
        status = kStatus_Fail;
        return status;
    }

    /* Compare the version of CFPA scratch and version of CFPA returned by ROM API */
    if (cfpaScratchVer > cfpaVer)
    {
        /* Get IPED_IV_CTRs from CFPA scratch */
        memcpy(&ivEraseCounter, (void *)CFPA_SCRATCH_IV, sizeof(uint32_t) * IPED_REGION_COUNT);
    }
    else
    {
        /* Get IPED_IV_CTRs IVs from CFPA ping/pong page */
        status = FFR_GetCustomerInfieldData(&flash_config, (uint8_t *)ivEraseCounter, CFPA_IPED_IV_OFFSET,
                                            sizeof(uint32_t) * IPED_REGION_COUNT);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }
    }

    if (config == NULL) /* Read configuration from CMPA */
    {
        /* Get IPED start address, end address and lock setting from FFR CMPA */
        status = FFR_GetCustomerData(
            &flash_config, (uint8_t *)ipedConfig, CMPA_IPED_START_OFFSET,
            sizeof(uint32_t) * IPED_REGION_COUNT * 2u); // multiply by 2 because we are reading end and start address
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        /* Prepare Lock and Enable values from FFR configuration into array */
        lockEnable[0] = (ipedConfig[0] & IPED_START_ADDR_LOCK_EN_MASK);
        lockEnable[1] = (ipedConfig[2] & IPED_START_ADDR_LOCK_EN_MASK);
        lockEnable[2] = (ipedConfig[4] & IPED_START_ADDR_LOCK_EN_MASK);
        lockEnable[3] = (ipedConfig[5] & IPED_START_ADDR_LOCK_EN_MASK);
        /* Prepare Start address values from FFR configuration into array */
        ipedStart[0] = (ipedConfig[0] & IPED_START_ADDR_MASK);
        ipedStart[1] = (ipedConfig[2] & IPED_START_ADDR_MASK);
        ipedStart[2] = (ipedConfig[4] & IPED_START_ADDR_MASK);
        ipedStart[3] = (ipedConfig[6] & IPED_START_ADDR_MASK);
        /* Prepare End address values from FFR configuration into array */
        ipedEnd[0] = (ipedConfig[1] & IPED_END_ADDR_MASK);
        ipedEnd[1] = (ipedConfig[3] & IPED_END_ADDR_MASK);
        ipedEnd[2] = (ipedConfig[5] & IPED_END_ADDR_MASK);
        ipedEnd[3] = (ipedConfig[7] & IPED_END_ADDR_MASK);

        /* Always use 12 rounds */
        IPED_SetPrinceRounds(FLEXSPI0, kIPED_PrinceRounds12);

        /* Iterate for all internal IPED regions */
        for (iped_region_t region = kIPED_Region0; region <= kIPED_Region3; region++)
        {
            iped_region_t region = kIPED_Region0;
            /* If not enabled, skip to other region */
            if (lockEnable[region] == 0u)
            {
                continue;
            }

            /* Write start & end addresses to IPED registers */
            status = IPED_SetRegionAddressRange(FLEXSPI0, (iped_region_t)region, ipedStart[region], ipedEnd[region]);
            if (status != kStatus_Success)
            {
                break;
            }

            /* Prepare ivSeed for current region */
            IvReg[0] = uuid[0];
            IvReg[1] = uuid[1];
            IvReg[2] = uuid[2] ^ region;
            IvReg[3] = ivEraseCounter[region];

            /* Calculate IV as IvReg = AES_ECB_ENC(DUK_derived_key, {ctx_erase_counter, ctx_id}) */
            status = IPED_ELS_calculate_iv(IvReg);
            if (status != kStatus_Success)
            {
                return kStatus_Fail;
            }

            /* Load IV into IPED registers */
            status = IPED_SetRegionIV(FLEXSPI0, (iped_region_t)region, (uint8_t *)IvReg);
            if (status != kStatus_Success)
            {
                return kStatus_Fail;
            }

            /* Lock region if required */
            if ((lockEnable[region] == 0x2u) || (lockEnable[region] == 0x3u))
            {
                IPED_SetLock(FLEXSPI0, region);
            }
        }
    }
    else /* Use provided config structure */
    {
        /* Write start & end addresses to IPED registers */
        status =
            IPED_SetRegionAddressRange(FLEXSPI0, (iped_region_t)config->option.iped_region, config->start, config->end);

        /* Prepare ivSeed for current region */
        IvReg[0] = uuid[0];
        IvReg[1] = uuid[1];
        IvReg[2] = uuid[2] ^ (iped_region_t)config->option.iped_region;
        IvReg[3] = ivEraseCounter[(iped_region_t)config->option.iped_region];

        /* Calculate IV as IvReg = AES_ECB_ENC(DUK_derived_key, {ctx_erase_counter, ctx_id}) */
        status = IPED_ELS_calculate_iv(IvReg);
        if (status != kStatus_Success)
        {
            return kStatus_Fail;
        }

        /* Load IV into IPED registers */
        status = IPED_SetRegionIV(FLEXSPI0, (iped_region_t)config->option.iped_region, (uint8_t *)IvReg);
        if (status != kStatus_Success)
        {
            return kStatus_Fail;
        }
    }

    /* Check if error occured during IPED configuration */
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return status;
}

static status_t IPED_ELS_check_key(uint8_t keyIdx, mcuxClEls_KeyProp_t *pKeyProp)
{
    /* Check if ELS required keys are available in ELS keystore */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClEls_GetKeyProperties(keyIdx, pKeyProp)); // Get key propertis from the ELS.
    // mcuxClEls_GetKeyProperties is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties) != token) || (MCUXCLELS_STATUS_OK != result))
        return kStatus_Fail;
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return kStatus_Success;
}

static status_t IPED_ELS_gen_iv_key(void)
{
    /* The NXP_DIE_MEM_IV_ENC_SK is not loaded and needs to be regenerated (power-down wakeup) */
    /* Set KDF mask and key properties for NXP_DIE_MEM_IV_ENC_SK */
    SYSCON->ELS_KDF_MASK            = SYSCON_ELS_KDF_MASK;
    static const uint32_t ddata2[3] = {0x62032504, 0x72f04280, 0x87a2bbae};
    mcuxClEls_KeyProp_t keyProp;
    /* Set key properties in structure */
    keyProp.word.value = MCUXCLELS_KEYPROPERTY_VALUE_AES | MCUXCLELS_KEYPROPERTY_VALUE_GENERAL_PURPOSE_SLOT |
                         MCUXCLELS_KEYPROPERTY_VALUE_ACTIVE;
    status_t status = kStatus_Fail;

    /* Generate the key using CKDF */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
        result, token,
        mcuxClEls_Ckdf_Sp800108_Async((mcuxClEls_KeyIndex_t)0, (mcuxClEls_KeyIndex_t)NXP_DIE_MEM_IV_ENC_SK, keyProp,
                                      (uint8_t const *)ddata2));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Ckdf_Sp800108_Async) != token) && (MCUXCLELS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Wait for CKDF to finish */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) == token) && (MCUXCLELS_STATUS_OK == result))
    {
        status = kStatus_Success;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return status;
}

static status_t IPED_ELS_enable(void)
{
    mcuxClEls_KeyProp_t key_properties;
    status_t status = kStatus_Fail;

    /* Enable ELS and related clocks */
    status = ELS_PowerDownWakeupInit(ELS);
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Check if MEM_ENC_SK key is available in ELS keystore */
    status = IPED_ELS_check_key(NXP_DIE_EXT_MEM_ENC_SK, &key_properties);
    if (status != kStatus_Success || key_properties.bits.kactv != 1u)
    {
        return kStatus_Fail;
    }

    /* Check if MEM_IV_ENC_SK key is available in ELS keystore */
    status = IPED_ELS_check_key(NXP_DIE_MEM_IV_ENC_SK, &key_properties);
    if (status != kStatus_Success || key_properties.bits.kactv != 1u)
    {
        return IPED_ELS_gen_iv_key();
    }

    return kStatus_Success;
}

static status_t IPED_ELS_calculate_iv(uint32_t *IvReg)
{
    mcuxClEls_CipherOption_t cipherOptions = {0};
    status_t status                        = kStatus_Fail;

    /* Configure ELS for AES ECB-128, using NXP_DIE_MEM_IV_ENC_SK key */
    cipherOptions.bits.cphmde = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB;
    cipherOptions.bits.dcrpt  = MCUXCLELS_CIPHER_ENCRYPT;
    cipherOptions.bits.extkey = MCUXCLELS_CIPHER_INTERNAL_KEY;

    do
    {
        /* Calculate IV as IvReg = AES_ECB_ENC(NXP_DIE_MEM_IV_ENC_SK, ivSeed[127:0]) */
        /* ivSeed[127:0] = {UUID[96:0] ^ regionNumber[1:0], ivEraseCounter[31:0]} */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
            result, token,
            mcuxClEls_Cipher_Async(cipherOptions, (mcuxClEls_KeyIndex_t)NXP_DIE_MEM_IV_ENC_SK, NULL,
                                   MCUXCLELS_CIPHER_KEY_SIZE_AES_128, (uint8_t *)IvReg, MCUXCLELS_CIPHER_BLOCK_SIZE_AES,
                                   NULL, (uint8_t *)IvReg));
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
            break;
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
            result, token,
            mcuxClEls_WaitForOperation(
                MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Enable_Async operation to complete.
        // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) == token) && (MCUXCLELS_STATUS_OK == result))
        {
            status = kStatus_Success;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
    } while (0);

    return status;
}
