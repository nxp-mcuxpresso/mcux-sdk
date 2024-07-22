/*
 * Copyright 2021,2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flash_api.h"
#include "fsl_lpspi_flash.h"
#include "fsl_kb_api.h"
#include "fsl_nboot.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "driver.romapi"
#endif

/*
 *!@brief Structure of version property.
 *
 *!@ingroup bl_core
 */
typedef union StandardVersion
{
    struct
    {
        uint32_t bugfix : 8; /*!< bugfix version [7:0] */
        uint32_t minor : 8;  /*!< minor version [15:8] */
        uint32_t major : 8;  /*!< major version [23:16] */
        uint32_t name : 8;   /*!< name [31:24] */
    };
    uint32_t version; /*!< combined version numbers. */
} standard_version_t;

/*!
 * @brief Root of the bootloader API tree.
 *
 * An instance of this struct resides in read-only memory in the bootloader. It
 * provides a user application access to APIs exported by the bootloader.
 *
 * @note The order of existing fields must not be changed.
 */
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg);                       /*!< Function to start the bootloader executing.*/
    const flash_driver_interface_t *flashDriver;            /*!< Internal Flash driver API.*/
    const kb_interface_t *kbApi;                            /*!< Bootloader API.*/
    const nboot_interface_t *nbootAuthenticate;             /*!< Image authentication API.*/
    const lpspi_flash_driver_interface_t *lpspiFlashDriver; /*!< Internal Flash driver API.*/
    standard_version_t version;                             /*!< Bootloader version number.*/
    const char *copyright;                                  /*!< Copyright string.*/
    uint32_t reserved0;                                     /*!< Reserved for factory use.*/
} bootloader_tree_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t flash_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t alignmentBaseline);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x14816fe0U)

/*******************************************************************************
 * Code
 ******************************************************************************/

/******************************************************
 * Flash driver
 ******************************************************/
/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 */
status_t FLASH_Init(flash_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_init(config);

    return status;
}

/*!
 * @brief Erases the Dflash sectors encompassed by parameters passed into function.
 */
status_t FLASH_Erase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_erase_sector(config, base, start, lengthInBytes, key);

    return status;
}

/*!
 * @brief Programs flash phrases with data at locations passed in through parameters.
 */
status_t FLASH_Program(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t *src, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);
    assert(src);

    status_t status = kStatus_Fail;

    status = flash_check_param(config, base, start, lengthInBytes, FSL_FEATURE_FLASH_PFLASH_PHRASE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        /* Align length to whole phrase */
        uint32_t alignedLength = ALIGN_DOWN(lengthInBytes, sizeof(uint8_t) * FSL_FEATURE_FLASH_PFLASH_PHRASE_SIZE);
        uint32_t extraBytes    = lengthInBytes - alignedLength;
        uint32_t *srcWord      = (uint32_t *)(uintptr_t)src;

        if (alignedLength > 0U)
        {
            uint32_t endAddress = start + alignedLength - 1U;
            while (start <= endAddress)
            {
                status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_program_phrase(
                    config, base, start, srcWord, FSL_FEATURE_FLASH_PFLASH_PHRASE_SIZE);
                if (kStatus_FLASH_Success != status)
                {
                    break;
                }
                else
                {
                    /* Increment to the next phrase */
                    start += FSL_FEATURE_FLASH_PFLASH_PHRASE_SIZE;
                    srcWord += 4U;
                }
            }
        }
        else
        {
            ; /* Do nothing */
        }

        if ((kStatus_FLASH_Success == status) && (extraBytes > 0U))
        {
            uint32_t extraData[4] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};

            /* Copy extra bytes to phrase buffer */
            union
            {
                uint32_t *src;
                const void *srcVoid;
            } srcPtr;
            srcPtr.src = srcWord;

            union
            {
                uint32_t *xData;
                void *xDataVoid;
            } xDataPtr;
            xDataPtr.xData = (uint32_t *)&extraData[0];

            (void)memcpy(xDataPtr.xDataVoid, srcPtr.srcVoid, extraBytes);

            status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_program_phrase(
                config, base, start, extraData, FSL_FEATURE_FLASH_PFLASH_PHRASE_SIZE);
        }
    }
    else
    {
        ; /* Do nothing */
    }

    return status;
}

/*!
 * @brief Programs flash pages with data at locations passed in through parameters.
 */
status_t FLASH_ProgramPage(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t *src, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);
    assert(src);

    status_t status = kStatus_Fail;

    status = flash_check_param(config, base, start, lengthInBytes, FSL_FEATURE_FLASH_PFLASH_PAGE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        /* Align length to whole phrase. */
        uint32_t alignedLength = ALIGN_DOWN(lengthInBytes, sizeof(uint8_t) * FSL_FEATURE_FLASH_PFLASH_PAGE_SIZE);
        uint32_t extraBytes    = lengthInBytes - alignedLength;
        uint32_t *srcWord      = (uint32_t *)(uintptr_t)src;

        if (alignedLength > 0U)
        {
            uint32_t endAddress = start + alignedLength - 1U;
            while (start <= endAddress)
            {
                status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_program_page(
                    config, base, start, srcWord, FSL_FEATURE_FLASH_PFLASH_PAGE_SIZE);
                if (kStatus_FLASH_Success != status)
                {
                    break;
                }
                else
                {
                    /* Increment to the next page */
                    start += FSL_FEATURE_FLASH_PFLASH_PAGE_SIZE;
                    srcWord += 32U;
                }
            }
        }
        else
        {
            ; /* Do nothing */
        }

        if ((kStatus_FLASH_Success == status) && (extraBytes > 0U))
        {
            uint32_t extraData[32] = {
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};

            /* Copy extra bytes to page buffer. */
            union
            {
                uint32_t *src;
                const void *srcVoid;
            } srcPtr;
            srcPtr.src = srcWord;

            union
            {
                uint32_t *xData;
                void *xDataVoid;
            } xDataPtr;
            xDataPtr.xData = (uint32_t *)&extraData[0];

            (void)memcpy(xDataPtr.xDataVoid, srcPtr.srcVoid, extraBytes);

            status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_program_page(config, base, start, extraData,
                                                                                  FSL_FEATURE_FLASH_PFLASH_PAGE_SIZE);
        }
    }
    else
    {
        ; /* Do nothing */
    }

    return status;
}

/*!
 * @brief Verify that the flash phrases are erased
 */
status_t FLASH_VerifyErasePhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_erase_phrase(config, base, start, lengthInBytes);

    return status;
}

/*!
 * @brief Verify that all flash and IFR space is erased
 */
status_t FLASH_VerifyEraseAll(FMU_Type *base)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_erase_all(base);

    return status;
}

/*!
 * @brief Verify that the flash pages are erased
 */
status_t FLASH_VerifyErasePage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_erase_page(config, base, start, lengthInBytes);

    return status;
}

/*!
 * @brief Verify that the flash sector are erased
 */
status_t FLASH_VerifyEraseSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_erase_sector(config, base, start, lengthInBytes);

    return status;
}

/*!
 * @brief Read into MISR
 *
 * The Read into MISR operation generates a signature based on the contents of the selected
 * flash memory using an embedded MISR.
 */
status_t FLASH_ReadIntoMisr(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t endAddr, uint32_t *seed, uint32_t *signature)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);
    assert(seed);
    assert(signature);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_read_into_misr(config, base, start, endAddr, seed, signature);

    return status;
}

/*!
 * @brief Returns the desired flash property.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(value);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->flash_get_property(config, whichProperty, value);

    return status;
}
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__ ((section (".ramfunc")))
#endif
    void
    FLASH_CACHE_Disable(void)
{
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_OCMDR0_OCMCF2_MASK)) | SMSCM_OCMDR0_OCMCF2(0x1);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_OCMDR0_OCMCF2_MASK)) | SMSCM_OCMDR0_OCMCF2(0xC);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_OCMDR0_OCMCF1_MASK)) | SMSCM_OCMDR0_OCMCF1(0x3);
    __ISB();
    __DSB();
}

#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__ ((section (".ramfunc")))
#endif
    void
    FLASH_CACHE_Clear(bool isPreProcess)
{
    if (isPreProcess == false)
    {
        SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_OCMDR0_OCMCF2_MASK)) | SMSCM_OCMDR0_OCMCF2(0x1);
        SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_OCMDR0_OCMCF1_MASK)) | SMSCM_OCMDR0_OCMCF1(0x0);
    }
    else
    {
        SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_OCMDR0_OCMCF1_MASK)) | SMSCM_OCMDR0_OCMCF1(0x3);
    }

    /* Memory barriers for good measure.
     * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
    __ISB();
    __DSB();
}

static status_t flash_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t alignmentBaseline)
{
    assert(config);
    assert(base);

    status_t status = kStatus_FLASH_InvalidArgument;

    if (lengthInBytes == 0U)
    {
        status = kStatus_FLASH_Success;
    }
#if defined(RF_FMU)
    else if ((config == NULL) || (base == NULL) || ((base != FMU0) && (base != RF_FMU)))
    {
        status = kStatus_FLASH_InvalidArgument;
    }
#else
    else if ((config == NULL) || (base == NULL) || (base != FMU0))
    {
        status = kStatus_FLASH_InvalidArgument;
    }
#endif
    /* Verify the start is alignmentBaseline aligned. */
    else if ((start & (alignmentBaseline - 1U)) != 0u)
    {
        status = kStatus_FLASH_AlignmentError;
    }
    else
    {
        start = start & 0xEFFFFFFFU;

        if (base == FMU0)
        {
            /* Validates the range of the given address */
            if ((start >= config->msf1Config[0].flashDesc.blockBase) &&
                ((start + lengthInBytes) <=
                 (config->msf1Config[0].flashDesc.blockBase + config->msf1Config[0].flashDesc.totalSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else if ((start >= config->msf1Config[0].ifrDesc.pflashIfr0Start) &&
                     ((start + lengthInBytes) <= (config->msf1Config[0].ifrDesc.pflashIfr0Start +
                                                  config->msf1Config[0].ifrDesc.pflashIfr0MemSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else
            {
                status = kStatus_FLASH_AddressError;
            }
        }
        else /* if (base == RF_FMU) */
        {
            /* Validates the range of the given address */
            if ((start >= config->msf1Config[1].flashDesc.blockBase) &&
                ((start + lengthInBytes) <=
                 (config->msf1Config[1].flashDesc.blockBase + config->msf1Config[1].flashDesc.totalSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else if ((start >= config->msf1Config[1].ifrDesc.pflashIfr0Start) &&
                     ((start + lengthInBytes) <= (config->msf1Config[1].ifrDesc.pflashIfr0Start +
                                                  config->msf1Config[1].ifrDesc.pflashIfr0MemSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else
            {
                status = kStatus_FLASH_AddressError;
            }
        }
    }

    return status;
}

/******************************************************
 * IFR driver
 ******************************************************/
/*!
 * @brief Verify that the ifr phrases are erased
 */
status_t FLASH_VerifyEraseIFRPhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->ifr_verify_erase_phrase(config, base, start, lengthInBytes);

    return status;
}

/*!
 * @brief Verify that the ifr pages are erased
 */
status_t FLASH_VerifyEraseIFRPage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->ifr_verify_erase_page(config, base, start, lengthInBytes);

    return status;
}

/*!
 * @brief Verify that the ifr sectors are erased
 */
status_t FLASH_VerifyEraseIFRSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->ifr_verify_erase_sector(config, base, start, lengthInBytes);

    return status;
}

/*!
 * @brief Read IFR into MISR
 *
 * The Read IFR into MISR operation generates a signature based on the contents of the
 * selected IFR space using an embedded MISR.
 */
status_t FLASH_ReadIFRIntoMisr(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t endAddr, uint32_t *seed, uint32_t *signature)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(config);
    assert(base);
    assert(seed);
    assert(signature);

    status_t status;
    status = BOOTLOADER_API_TREE_POINTER->flashDriver->ifr_read_into_misr(config, base, start, endAddr, seed, signature);

    return status;
}

/********************************************************************************
 *  Lpspi EEPROM API
 *******************************************************************************/
/*!
 * @brief Initialize SPI NOR/EEPROM
 *
 * @param baudRate Config baudrate for SPI.
 */
status_t SPI_EepromInit(uint32_t baudRate)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->lpspiFlashDriver->spi_eeprom_init(baudRate);
}

/*!
 * @brief Read data via SPI NOR/EEPROM
 */
status_t SPI_EepromRead(uint8_t *dest, uint32_t length, uint32_t address, bool requestFastRead)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(dest);

    return BOOTLOADER_API_TREE_POINTER->lpspiFlashDriver->spi_eeprom_read(dest, length, address, requestFastRead);
}

/*!
 * @brief Write data via SPI NOR/EEPROM
 */
status_t SPI_EepromWrite(uint8_t *data, uint32_t length, uint32_t address)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(data);

    return BOOTLOADER_API_TREE_POINTER->lpspiFlashDriver->spi_eeprom_write(data, length, address);
}

/*!
 * @brief Erase data via SPI NOR/EEPROM
 */
status_t SPI_EepromErase(uint32_t address, eraseOptions_t option)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->lpspiFlashDriver->spi_eeprom_erase(address, option);
}

/*! @brief De-initialize LPSPI
 */
void SPI_EepromFinalize(void)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    BOOTLOADER_API_TREE_POINTER->lpspiFlashDriver->spi_eeprom_finalize();
}

/********************************************************************************
 * Bootloader API
 *******************************************************************************/
/*!
 * @brief This API is used to initialize bootloader and nboot context necessary to process sb3 file format.
 */
status_t KB_Init(void)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->kbApi->kb_init();
}

/*!
 * @brief This API is used to decrypt sb3 file and store signed image contents specified by loader command supported
 * while generating sb3 image through Json configuration. If sb3 file to be processed includes sblaoder command
 * "programFuses" then voltage must be regulated for over-drive and normalize voltage once operation is completed.
 *
 * @param data A Pointer to start of sb file data in memory.
 * @param dataLength sb file data length in bytes.
 * @param isUpdateExt Indicator for update(sb) file start address is in internal or external flash.
 *
 * @retval #kStatus_Success API was executed successfully.
 * @retval #kStatus_Fail API execution failed.
 * @retval #kStatus_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_LPSPI_Busy LPSPI transfer is busy.
 * @retval #kStatusRomLdrDataUnderrun
 */
status_t KB_Execute(const uint8_t *data, uint32_t dataLength, uint32_t isUpdateExt)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(data);

    return BOOTLOADER_API_TREE_POINTER->kbApi->kb_execute(data, dataLength, isUpdateExt);
}

/*!
 * @brief This API is used to release nboot context and finalize sb3 file processing.
 */
status_t KB_Deinit(void)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->kbApi->kb_deinit();
}

/********************************************************************************
 * Interface for image authentication API
 *******************************************************************************/
/*!
 * @brief The function is used for initializing of the nboot context data structure.
 * It should be called prior to any other calls of nboot API.
 */
nboot_status_t NBOOT_ContextInit(nboot_context_t *context)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_context_init(context);
}

/*!
 * @brief The function is used to deinitialize nboot context data structure.
 * Its contents are overwritten with random data so that any sensitive data does not remain in memory.
 */
nboot_status_t NBOOT_ContextFree(nboot_context_t *context)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_context_free(context);
}

/*!
 * @brief Verify NBOOT SB3.1 manifest (header message)
 *
 * This function verifies  the NBOOT SB3.1 manifest, initializes the context and loads keys into the
 * CSS key store so that they can be used by nboot_sb3_load_block function
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 */
nboot_status_t NBOOT_SB3LoaderManifest(nboot_context_t *context, uint32_t *manifest)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(manifest);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_sb3_load_manifest(context, manifest);
}

/*!
 * @brief Verify NBOOT SB3.1 block
 *
 * This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 */
nboot_status_t NBOOT_SB3LoaderBlock(nboot_context_t *context, uint32_t *block)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(block);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_sb3_load_block(context, block);
}

/*!
 * @brief Authenticate and load Sentinel200 firmware at once
 *
 * This function verifies and decrypts SB3.1 file with S200 firmware. Decryption is performed to S200 RAM and firmware
 * automaticly started after sucessfull load. The NBOOT context has to be initialized by the function nboot_context_init
 * before calling this function.
 */
nboot_status_t NBOOT_SB3LoaderS200Fw(nboot_context_t *context, uint32_t *sb3Data)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(sb3Data);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_sb3_load_s200_fw(context, sb3Data);
}

/*!
 * @brief Secure boot image authentication
 *
 * This function authenticates image with asymmetric cryptography.
 */
nboot_status_t NBOOT_ImgAuthenticateEcdsa(nboot_context_t *context,
                                          uint8_t imageStart[],
                                          nboot_bool_t *isSignatureVerified)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(isSignatureVerified);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_img_authenticate_ecdsa(context, imageStart,
                                                                                        isSignatureVerified);
}

/*!
 * @brief Get random number in the highest quality, which is currently avaibale, no delay with TRNG initialization.
 */
nboot_status_t NBOOT_RngRandom(nboot_context_t *context, void *buf, size_t bufLen)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(buf);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_rng_random(context, buf, bufLen);
}

/*!
 * @brief Get high quality random number(s)
 */
nboot_status_t NBOOT_RngRandomHq(nboot_context_t *context, void *buf, size_t bufLen)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(buf);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_rng_random_hq(context, buf, bufLen);
}

/*!
 * @brief Program a fuse word
 * Programs a fuse word at given address with new data.
 */
nboot_status_t NBOOT_FuseProgram(nboot_context_t *context,
                                 uint32_t addr,
                                 uint32_t *data,
                                 uint32_t systemClockFrequencyMHz)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(data);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_fuse_program(context, addr, data,
                                                                              systemClockFrequencyMHz);
}

/*!
 * @brief Reads a fuse word
 * Reads a fuse word.
 */
nboot_status_t NBOOT_FuseRead(nboot_context_t *context, uint32_t addr, uint32_t *data, uint32_t systemClockFrequencyMHz)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(data);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_fuse_read(context, addr, data,
                                                                           systemClockFrequencyMHz);
}

/*!
 * @brief Read property
 * One of the important properties that can be read is the property that last
 * authentication of signed image container has succeeded.
 */
nboot_status_t NBOOT_PropertyGet(nboot_context_t *context, uint32_t propertyId, uint8_t *destData, size_t *dataLen)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    assert(context);
    assert(destData);
    assert(dataLen);

    return BOOTLOADER_API_TREE_POINTER->nbootAuthenticate->nboot_property_get(context, propertyId, destData, dataLen);
}
