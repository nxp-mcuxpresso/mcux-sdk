/*
 *     Copyright 2020-2024 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_iped.h"
#include "fsl_flash_ffr.h"

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
        /* Check if region is not out of range */
        if (region >= IPED_REGION_COUNT)
        {
            status = kStatus_NBOOT_InvalidArgument;
            break;
        }

        /* Check if region is not locked */
        if (IPED_IsRegionLocked(base, region))
        {
            return kStatus_IPED_RegionIsLocked;
        }

        /* Disable soft lock for given region first */
        base->IPEDCTXCTRL[0] =
            (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
            (IPED_RW_ENABLE_VAL << (region * 2u));

        volatile uint32_t *reg_start =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0START)) + (IPED_CTX_REG_OFFSET * region));
        volatile uint32_t *reg_end =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0END)) + (IPED_CTX_REG_OFFSET * region));

        *reg_start = start_address;
        *reg_end   = end_address;

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

    do
    {
        /* Check if region is not out of range */
        if (region >= IPED_REGION_COUNT)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        volatile uint32_t *reg_start =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0START)) + (IPED_CTX_REG_OFFSET * region));
        volatile uint32_t *reg_end =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0END)) + (IPED_CTX_REG_OFFSET * region));

        *start_address = *reg_start & FLEXSPI_IPEDCTX0START_start_address_MASK;
        *end_address   = *reg_end;
        status         = kStatus_Success;
    } while (0);

    return status;
}

status_t IPED_SetRegionIV(FLEXSPI_Type *base, iped_region_t region, const uint8_t iv[8])
{
    status_t status = kStatus_Fail;

    do
    {
        /* Check if region is not out of range */
        if (region >= IPED_REGION_COUNT)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        volatile uint32_t *reg_iv0 =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0IV0)) + (IPED_CTX_REG_OFFSET * region));
        volatile uint32_t *reg_iv1 =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0IV1)) + (IPED_CTX_REG_OFFSET * region));

        *reg_iv0 = ((uint32_t *)(uintptr_t)iv)[0];
        *reg_iv1 = ((uint32_t *)(uintptr_t)iv)[1];
        status   = kStatus_Success;
    } while (false);

    return status;
}

status_t IPED_SetRegionAad(FLEXSPI_Type *base, iped_region_t region, const uint8_t aad[8])
{
    status_t status = kStatus_Fail;

    do
    {
        /* Check if region is not out of range */
        if (region >= IPED_REGION_COUNT)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        volatile uint32_t *reg_aad0 =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0AAD0)) + (IPED_CTX_REG_OFFSET * region));
        volatile uint32_t *reg_aad1 =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0AAD1)) + (IPED_CTX_REG_OFFSET * region));

        *reg_aad0 = ((uint32_t *)(uintptr_t)aad)[0];
        *reg_aad1 = ((uint32_t *)(uintptr_t)aad)[1];
        status    = kStatus_Success;
    } while (false);

    return status;
}

status_t IPED_SetRegionConfig(FLEXSPI_Type *base, iped_region_t region, iped_mode_t mode, iped_ahb_bus_err_cfg_t ahbErr)
{
    status_t status = kStatus_Fail;

    do
    {
        /* Check if region is not out of range */
        if (region >= IPED_REGION_COUNT)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        /* Check if region is not locked */
        if (IPED_IsRegionLocked(base, region))
        {
            status = kStatus_IPED_RegionIsLocked;
            break;
        }

        /* Disable soft lock for given region first */
        base->IPEDCTXCTRL[0] =
            (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
            (IPED_RW_ENABLE_VAL << (region * 2u));

        volatile uint32_t *reg_start =
            (volatile uint32_t *)(((uint32_t) & (base->IPEDCTX0START)) + (IPED_CTX_REG_OFFSET * region));
        *reg_start = (*reg_start & FLEXSPI_IPEDCTX0START_start_address_MASK) |
                     (ahbErr << FLEXSPI_IPEDCTX0START_ahbbuserror_dis_SHIFT) |
                     (mode << FLEXSPI_IPEDCTX0START_GCM_SHIFT);
        status = kStatus_Success;

        /* Re-enable soft lock for given region */
        base->IPEDCTXCTRL[0] =
            (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
            (IPED_RW_DISABLE_VAL << (region * 2u));
    } while (false);

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
status_t IPED_Configure(FLEXSPI_Type *base,
                        api_core_context_t *coreCtx,
                        flexspi_iped_region_arg_t *config,
                        iped_lock_t lock,
                        iped_cmpa_t writeCmpa)
{
    status_t status = kStatus_Fail;
    flash_config_t flash_config;
    cmpa_cfg_info_t cmpa_buffer = {0};

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

    /* Configure IPED start and end adress of region */
    status = IPED_SetRegionAddressRange(base, config->option.iped_region, config->start, config->end);

    /* Configure IPED mode */
    status = IPED_SetRegionConfig(base, config->option.iped_region, config->option.iped_mode, kIPED_AhbBusErrorDisable);

    /* Configure IPED via ROM API, ROM API will provide config parameter check */
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
        status = FFR_GetCustomerData(&flash_config, (uint8_t *)&cmpa_buffer, 0u, FLASH_FFR_MAX_PAGE_SIZE);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        cmpa_buffer.ipedRegions[config->option.iped_region].ipedStartAddr =
            (config->start & IPED_ADDRESS_MASK) | (lock & IPED_ENABLE_MASK);
        cmpa_buffer.ipedRegions[config->option.iped_region].ipedEndAddr = config->end;

        /* Write new CMPA page into FFR */
        status = FFR_CustFactoryPageWrite(&flash_config, (uint8_t *)&cmpa_buffer, false /* do not seal PFR memory */);
    }

    /* Lock the IPED IP setting if desired */
    if (lock == kIPED_RegionLock)
    {
        IPED_SetLock(base, config->option.iped_region);
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
status_t IPED_Reconfigure(FLEXSPI_Type *base, api_core_context_t *coreCtx, flexspi_iped_region_arg_t *config)
{
    status_t status   = kStatus_Fail;
    uint32_t IvReg[4] = {0};
    uint32_t ivEraseCounter[4];
    uint32_t ipedConfig[IPED_REGION_COUNT];
    uint32_t ipedStart[IPED_REGION_COUNT];
    uint32_t ipedEnd[IPED_REGION_COUNT];
    uint8_t lockEnable[IPED_REGION_COUNT];
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
            &flash_config, (uint8_t *)ipedConfig, 0,
            sizeof(uint32_t) * IPED_REGION_COUNT * 2u); // multiply by 2 because we are reading end and start address
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        for (iped_region_t region = kIPED_Region0; region <= IPED_REGION_COUNT; region++)
        {
            /* Prepare Lock and Enable values from FFR configuration into array */
            lockEnable[region] = (ipedConfig[region] & IPED_START_ADDR_LOCK_EN_MASK);

            /* Prepare Start address values from FFR configuration into array */
            ipedStart[region] = (ipedConfig[region] & IPED_START_ADDR_MASK);

            /* Prepare End address values from FFR configuration into array */
            ipedEnd[region] = (ipedConfig[region] & IPED_END_ADDR_MASK);
        }

        /* Always use 12 rounds */
        IPED_SetPrinceRounds(base, kIPED_PrinceRounds12);

        /* Iterate for all internal IPED regions */
        for (iped_region_t region = kIPED_Region0; region <= IPED_REGION_COUNT; region++)
        {
            iped_region_t region = kIPED_Region0;
            /* If not enabled, skip to other region */
            if (lockEnable[region] == 0u)
            {
                continue;
            }

            /* Write start & end addresses to IPED registers */
            status = IPED_SetRegionAddressRange(base, (iped_region_t)region, ipedStart[region], ipedEnd[region]);
            if (status != kStatus_Success)
            {
                break;
            }

            /* Configure IPED mode */
            status = IPED_SetRegionConfig(base, config->option.iped_region, config->option.iped_mode,
                                          kIPED_AhbBusErrorDisable);
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
            status = IPED_SetRegionIV(base, (iped_region_t)region, (uint8_t *)IvReg);
            if (status != kStatus_Success)
            {
                return kStatus_Fail;
            }

            /* Lock region if required */
            if ((lockEnable[region] == 0x2u) || (lockEnable[region] == 0x3u))
            {
                IPED_SetLock(base, region);
            }
        }
    }
    else /* Use provided config structure */
    {
        /* Write start & end addresses to IPED registers */
        status =
            IPED_SetRegionAddressRange(base, (iped_region_t)config->option.iped_region, config->start, config->end);

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
        status = IPED_SetRegionIV(base, (iped_region_t)config->option.iped_region, (uint8_t *)IvReg);
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
