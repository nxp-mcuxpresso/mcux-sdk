/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_k4_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flash_k4"
#endif

#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && FLASH_DRIVER_IS_FLASH_RESIDENT
/*!
 * @brief Constants for execute-in-RAM flash function.
 */
enum _ftfx_ram_func_constants
{
    Flash_RunCommandCodeSize     = 6U,  /*!< The flash_run_command code size of execute-in-RAM.*/
    Flash_ErsSequenceCommandSize = 25U, /*!< The flash_erase_sequence func code size of execute-in-RAM.*/
    Flash_PgmSequenceCommandSize = 30U, /*!< The flash_program_sequence func size of execute-in-RAM.*/
};
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*! @brief Init IFR memory related info */
static status_t flash_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t alignmentBaseline);
static status_t pflash_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t *start, uint32_t lengthInBytes, uint32_t alignmentBaseline);
static status_t ifr_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t *start, uint32_t lengthInBytes, uint32_t alignmentBaseline);
static status_t flash_check_user_key(uint32_t key);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t FLASH_Init(flash_config_t *config)
{
    status_t status = kStatus_Fail;

    if (config == NULL)
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else
    {
        /* CM33 flash */
        config->msf1Config[0].flashDesc.blockBase  = FLASH_FEATURE_PFLASH0_START_ADDRESS;
        config->msf1Config[0].flashDesc.blockCount = FLASH_FEATURE_PFLASH0_BLOCK_COUNT;

#if (defined(CPU_KW45B41Z82AFPA) || defined(CPU_KW45B41Z82AFTA) || defined(CPU_KW45B41Z83AFPA) || \
     defined(CPU_KW45B41Z83AFTA) || defined(CPU_KW45Z41082AFPA) || defined(CPU_KW45Z41082AFTA) || \
     defined(CPU_KW45Z41083AFPA) || defined(CPU_KW45Z41083AFTA) || defined(CPU_K32W1480VFTA))
        /* M33 flash size 1MB */
        config->msf1Config[0].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH0_BLOCK_COUNT * FLASH_FEATURE_PFLASH0_BLOCK_SIZE;
#elif (defined(CPU_KW45B41Z52AFPA) || defined(CPU_KW45B41Z52AFTA) || defined(CPU_KW45B41Z53AFPA) || \
       defined(CPU_KW45B41Z53AFTA) || defined(CPU_KW45Z41052AFPA) || defined(CPU_KW45Z41052AFTA) || \
       defined(CPU_KW45Z41053AFPA) || defined(CPU_KW45Z41053AFTA))
        /* M33 flash size 512KB */
        config->msf1Config[0].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH0_BLOCK_COUNT * FLASH_FEATURE_PFLASH0_BLOCK_SIZE_512KB;
#elif (defined(CPU_KW47B42ZB7AFTA_cm33_core0))
        config->msf1Config[0].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH0_BLOCK_COUNT * FLASH_FEATURE_PFLASH0_BLOCK_SIZE;
#elif (defined(CPU_MCXW716CMFTA) || (CPU_MCXW716CMFPA) || (CPU_MCXW716AMFTA) || (CPU_MCXW716AMFPA))
        config->msf1Config[0].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH0_BLOCK_COUNT * FLASH_FEATURE_PFLASH0_BLOCK_SIZE;
#else
#error "No valid CPU defined!"
#endif

        config->msf1Config[0].ifrDesc.pflashIfr0Start   = FLASH_FEATURE_PFLASH0_IFR0_START_ADDRESS;
        config->msf1Config[0].ifrDesc.pflashIfr0MemSize = FLASH_FEATURE_PFLASH0_IFR0_SIZE;

        /* RF flash */
#if (defined(CPU_KW45B41Z82AFPA) || defined(CPU_KW45B41Z82AFTA) || defined(CPU_KW45B41Z83AFPA) || \
     defined(CPU_KW45B41Z83AFTA) || defined(CPU_KW45B41Z52AFPA) || defined(CPU_KW45B41Z52AFTA) || \
     defined(CPU_KW45B41Z53AFPA) || defined(CPU_KW45B41Z53AFTA) || defined(CPU_K32W1480VFTA))
        config->msf1Config[1].flashDesc.blockBase  = FLASH_FEATURE_PFLASH1_START_ADDRESS;
        config->msf1Config[1].flashDesc.blockCount = FLASH_FEATURE_PFLASH1_BLOCK_COUNT;
        config->msf1Config[1].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH1_BLOCK_COUNT * FLASH_FEATURE_PFLASH1_BLOCK_SIZE;

        config->msf1Config[1].ifrDesc.pflashIfr0Start   = FLASH_FEATURE_PFLASH1_IFR0_START_ADDRESS;
        config->msf1Config[1].ifrDesc.pflashIfr0MemSize = FLASH_FEATURE_PFLASH1_IFR0_SIZE;

#elif (defined(CPU_KW45Z41082AFPA) || defined(CPU_KW45Z41082AFTA) || defined(CPU_KW45Z41083AFPA) || \
       defined(CPU_KW45Z41083AFTA) || defined(CPU_KW45Z41052AFPA) || defined(CPU_KW45Z41052AFTA) || \
       defined(CPU_KW45Z41053AFPA) || defined(CPU_KW45Z41053AFTA))
        config->msf1Config[1].flashDesc.blockBase  = FLASH_FEATURE_PFLASH1_START_ADDRESS;
        config->msf1Config[1].flashDesc.blockCount = 0U;
        config->msf1Config[1].flashDesc.totalSize  = 0U;

        config->msf1Config[1].ifrDesc.pflashIfr0Start   = FLASH_FEATURE_PFLASH1_IFR0_START_ADDRESS;
        config->msf1Config[1].ifrDesc.pflashIfr0MemSize = 0U;
#elif (defined(CPU_KW47B42ZB7AFTA_cm33_core0))
        config->msf1Config[1].flashDesc.blockBase  = FLASH_FEATURE_PFLASH1_START_ADDRESS;
        config->msf1Config[1].flashDesc.blockCount = FLASH_FEATURE_PFLASH1_BLOCK_COUNT;
        config->msf1Config[1].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH1_BLOCK_COUNT * FLASH_FEATURE_PFLASH1_BLOCK_SIZE;

        config->msf1Config[1].ifrDesc.pflashIfr0Start   = FLASH_FEATURE_PFLASH1_IFR0_START_ADDRESS;
        config->msf1Config[1].ifrDesc.pflashIfr0MemSize = FLASH_FEATURE_PFLASH1_IFR0_SIZE;
#elif (defined(CPU_MCXW716CMFTA) || (CPU_MCXW716CMFPA) || (CPU_MCXW716AMFTA) || (CPU_MCXW716AMFPA))
        config->msf1Config[1].flashDesc.blockBase  = FLASH_FEATURE_PFLASH1_START_ADDRESS;
        config->msf1Config[1].flashDesc.blockCount = FLASH_FEATURE_PFLASH1_BLOCK_COUNT;
        config->msf1Config[1].flashDesc.totalSize =
            FLASH_FEATURE_PFLASH1_BLOCK_COUNT * FLASH_FEATURE_PFLASH1_BLOCK_SIZE;

        config->msf1Config[1].ifrDesc.pflashIfr0Start   = FLASH_FEATURE_PFLASH1_IFR0_START_ADDRESS;
        config->msf1Config[1].ifrDesc.pflashIfr0MemSize = FLASH_FEATURE_PFLASH1_IFR0_SIZE;
#else
#error "No valid CPU defined!"
#endif

        status = kStatus_FLASH_Success;
    }

    return status;
}

status_t FLASH_Erase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    status_t status = kStatus_Fail;

    status = flash_check_param(config, base, start, lengthInBytes, FLASH_FEATURE_PHRASE_SIZE);
    if ((status == kStatus_FLASH_Success) && (flash_check_user_key(key) == kStatus_FLASH_Success))
    {
        uint32_t endAddress = start + lengthInBytes - 1U;

        while (start <= endAddress)
        {
            status = FLASH_CMD_EraseSector(base, start);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next sector */
                start += FLASH_FEATURE_SECTOR_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_EraseAll(FMU_Type *base, uint32_t key)
{
    status_t status   = kStatus_Fail;
    FMU_Type *baseTmp = (FMU_Type *)((uint32_t)base & FLASH_ADDR_MASK);
#if defined(RF_FMU)
    if (base == NULL || (baseTmp != FLASH && baseTmp != NBU_FLASH))
#else
    if (base == NULL || baseTmp != FLASH)
#endif
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else
    {
        /* Validate the user key */
        status = flash_check_user_key(key);
    }

    if (kStatus_FLASH_Success == status)
    {
        status = FLASH_CMD_EraseAll(base);
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_Program(flash_config_t *config, FMU_Type *base, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t status = kStatus_Fail;

    status = flash_check_param(config, base, start, lengthInBytes, FLASH_FEATURE_PHRASE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        // Align length to whole phrase.
        uint32_t alignedLength = ALIGN_DOWN(lengthInBytes, sizeof(uint8_t) * FLASH_FEATURE_PHRASE_SIZE);
        uint32_t extraBytes    = lengthInBytes - alignedLength;
        uint32_t *srcWord      = (uint32_t *)(uintptr_t)src;

        if (alignedLength > 0U)
        {
            uint32_t endAddress = start + alignedLength - 1U;
            while (start <= endAddress)
            {
                status = FLASH_CMD_ProgramPhrase(base, start, srcWord);
                if (kStatus_FLASH_Success != status)
                {
                    break;
                }
                else
                {
                    /* Increment to the next sector */
                    start += FLASH_FEATURE_PHRASE_SIZE;
                    srcWord += FLASH_FEATURE_PHRASE_SIZE_IN_WORD;
                }
            }
        }
        else
        {
            ; // MISRA
        }

        if ((kStatus_FLASH_Success == status) && (extraBytes > 0U))
        {
            uint32_t extraData[4] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};

            // Copy extra bytes to phrase buffer.
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

            status = FLASH_CMD_ProgramPhrase(base, start, extraData);
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_ProgramPage(flash_config_t *config, FMU_Type *base, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t status = kStatus_Fail;

    status = flash_check_param(config, base, start, lengthInBytes, FLASH_FEATURE_PAGE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        // Align length to whole phrase.
        uint32_t alignedLength = ALIGN_DOWN(lengthInBytes, sizeof(uint8_t) * FLASH_FEATURE_PAGE_SIZE);
        uint32_t extraBytes    = lengthInBytes - alignedLength;
        uint32_t *srcWord      = (uint32_t *)(uintptr_t)src;

        if (alignedLength > 0U)
        {
            uint32_t endAddress = start + alignedLength - 1U;
            while (start <= endAddress)
            {
                status = FLASH_CMD_ProgramPage(base, start, srcWord);
                if (kStatus_FLASH_Success != status)
                {
                    break;
                }
                else
                {
                    /* Increment to the next sector */
                    start += FLASH_FEATURE_PAGE_SIZE;
                    srcWord += FLASH_FEATURE_PAGE_SIZE_IN_WORD;
                }
            }
        }
        else
        {
            ; // MISRA
        }

        if ((kStatus_FLASH_Success == status) && (extraBytes > 0U))
        {
            uint32_t extraData[32] = {
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};

            // Copy extra bytes to page buffer.
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

            status = FLASH_CMD_ProgramPage(base, start, extraData);
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyErasePhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    status_t status    = kStatus_Fail;
    uint32_t startaddr = start;

    status = pflash_check_param(config, base, &startaddr, lengthInBytes, FLASH_FEATURE_PHRASE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        uint32_t endAddress = startaddr + lengthInBytes - 1U;
        while (startaddr <= endAddress)
        {
            status = FLASH_CMD_VerifyErasePhrase(base, startaddr);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next phrase */
                startaddr += FLASH_FEATURE_PHRASE_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyErasePage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    status_t status    = kStatus_Fail;
    uint32_t startaddr = start;

    status = pflash_check_param(config, base, &startaddr, lengthInBytes, FLASH_FEATURE_PAGE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        uint32_t endAddress = startaddr + lengthInBytes - 1U;
        while (startaddr <= endAddress)
        {
            status = FLASH_CMD_VerifyErasePage(base, startaddr);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next page */
                startaddr += FLASH_FEATURE_PAGE_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyEraseSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    status_t status    = kStatus_Fail;
    uint32_t startaddr = start;

    status = pflash_check_param(config, base, &startaddr, lengthInBytes, FLASH_FEATURE_SECTOR_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        uint32_t endAddress = startaddr + lengthInBytes - 1U;
        while (startaddr <= endAddress)
        {
            status = FLASH_CMD_VerifyEraseSector(base, startaddr);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next sector */
                startaddr += FLASH_FEATURE_SECTOR_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyEraseIFRPhrase(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    status_t status    = kStatus_Fail;
    uint32_t startaddr = start;

    status = ifr_check_param(config, base, &startaddr, lengthInBytes, FLASH_FEATURE_PHRASE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        uint32_t endAddress = startaddr + lengthInBytes - 1U;
        while (startaddr <= endAddress)
        {
            status = FLASH_CMD_VerifyEraseIFRPhrase(base, startaddr);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next phrase */
                startaddr += FLASH_FEATURE_PHRASE_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyEraseIFRPage(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    status_t status    = kStatus_Fail;
    uint32_t startaddr = start;

    status = ifr_check_param(config, base, &startaddr, lengthInBytes, FLASH_FEATURE_PAGE_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        uint32_t endAddress = startaddr + lengthInBytes - 1U;
        while (startaddr <= endAddress)
        {
            status = FLASH_CMD_VerifyEraseIFRPage(base, startaddr);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next page */
                startaddr += FLASH_FEATURE_PAGE_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyEraseIFRSector(flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes)
{
    status_t status    = kStatus_Fail;
    uint32_t startaddr = start;

    status = ifr_check_param(config, base, &startaddr, lengthInBytes, FLASH_FEATURE_SECTOR_SIZE);
    if (status == kStatus_FLASH_Success)
    {
        uint32_t endAddress = startaddr + lengthInBytes - 1U;
        while (startaddr <= endAddress)
        {
            status = FLASH_CMD_VerifyEraseIFRSector(base, startaddr);
            if (kStatus_FLASH_Success != status)
            {
                break;
            }
            else
            {
                /* Increment to the next sector */
                startaddr += FLASH_FEATURE_SECTOR_SIZE;
            }
        }
    }
    else
    {
        ; // MISRA
    }

    return status;
}

status_t FLASH_VerifyEraseAll(FMU_Type *base)
{
    status_t status   = kStatus_Fail;
    FMU_Type *baseTmp = (FMU_Type *)((uint32_t)base & FLASH_ADDR_MASK);
#if defined(RF_FMU)
    if (base == NULL || ((baseTmp != FLASH) && (baseTmp != NBU_FLASH)))
#else
    if (base == NULL || baseTmp != FLASH)
#endif
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else
    {
        status = FLASH_CMD_VerifyEraseAll(base);
    }

    return status;
}

status_t FLASH_VerifyEraseBlock(flash_config_t *config, FMU_Type *base, uint32_t blockaddr)
{
    status_t status      = kStatus_Fail;
    uint32_t nsblockaddr = blockaddr & FLASH_ADDR_MASK;
    FMU_Type *baseTmp    = (FMU_Type *)((uint32_t)base & FLASH_ADDR_MASK);

#if defined(RF_FMU)
    if (config == NULL || base == NULL || ((baseTmp != FLASH) && (baseTmp != NBU_FLASH)))
#else
    if (config == NULL || base == NULL || baseTmp != FLASH)
#endif
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else if ((nsblockaddr != config->msf1Config[0].flashDesc.blockBase) &&
             (nsblockaddr != config->msf1Config[1].flashDesc.blockBase))
    {
        status = kStatus_FLASH_AddressError;
    }
    else
    {
        /* K4W1 M33 and NBU flash both have only one block, so 0U is sufficient here */
        status = FLASH_CMD_VerifyEraseBlock(base, 0U);
    }

    return status;
}

status_t Read_Into_MISR(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature)
{
    status_t status    = kStatus_Fail;
    uint32_t startAddr = start;

    if ((start >= ending) || (seed == NULL) ||
        (((ending + FLASH_FEATURE_PHRASE_SIZE) & (FLASH_FEATURE_PAGE_SIZE - 1U)) != 0u))
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else if ((ending & (FLASH_FEATURE_PHRASE_SIZE - 1U)) != 0u)
    {
        status = kStatus_FLASH_AlignmentError;
    }
    else
    {
        status = pflash_check_param(config, base, &startAddr, (ending - start), FLASH_FEATURE_PAGE_SIZE);
        if (status == kStatus_FLASH_Success)
        {
            uint32_t endAddr = startAddr + ending - start;
            status           = FLASH_CMD_ReadIntoMISR(base, startAddr, endAddr, seed, signature);
        }
        else
        {
            ; // MISRA
        }
    }

    return status;
}

status_t Read_IFR_Into_MISR(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature)
{
    status_t status    = kStatus_Fail;
    uint32_t startAddr = start;

    if ((start >= ending) || (seed == NULL) ||
        (((ending + FLASH_FEATURE_PHRASE_SIZE) & (FLASH_FEATURE_PAGE_SIZE - 1U)) != 0U))
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else if ((ending & (FLASH_FEATURE_PHRASE_SIZE - 1U)) != 0u)
    {
        status = kStatus_FLASH_AlignmentError;
    }
    else
    {
        status = ifr_check_param(config, base, &startAddr, (ending - start), FLASH_FEATURE_PAGE_SIZE);
        if (status == kStatus_FLASH_Success)
        {
            uint32_t endAddr = startAddr + ending - start;
            status           = FLASH_CMD_ReadIFRIntoMISR(base, startAddr, endAddr, seed, signature);
        }
        else
        {
            ; // MISRA
        }
    }

    return status;
}

status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    status_t status = kStatus_FLASH_Success;

    switch (whichProperty)
    {
        case kFLASH_PropertyPflash0TotalSize:
            *value = config->msf1Config[0].flashDesc.totalSize;
            break;
        case kFLASH_PropertyPflash0BlockSize:
            *value = config->msf1Config[0].flashDesc.totalSize / config->msf1Config[0].flashDesc.blockCount;
            break;
        case kFLASH_PropertyPflash0BlockCount:
            *value = config->msf1Config[0].flashDesc.blockCount;
            break;
        case kFLASH_PropertyPflash0BlockBaseAddr:
            *value = config->msf1Config[0].flashDesc.blockBase;
            break;
        case kFLASH_PropertyPflash0SectorSize:
            *value = FLASH_FEATURE_SECTOR_SIZE;
            break;
        case kFLASH_PropertyPflash1TotalSize:
            *value = config->msf1Config[1].flashDesc.totalSize;
            break;
        case kFLASH_PropertyPflash1BlockSize:
            *value = config->msf1Config[1].flashDesc.totalSize / config->msf1Config[1].flashDesc.blockCount;
            break;
        case kFLASH_PropertyPflash1BlockCount:
            *value = config->msf1Config[1].flashDesc.blockCount;
            break;
        case kFLASH_PropertyPflash1BlockBaseAddr:
            *value = config->msf1Config[1].flashDesc.blockBase;
            break;
        default:
            status = kStatus_FLASH_UnknownProperty;
            /* To avoid MISRA-C 2012 rule 16.4 issue. */
            break;
    }
    return status;
}

#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && (FLASH_DRIVER_IS_FLASH_RESIDENT == 1)
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__ ((section (".ramfunc")))
#endif
#endif
    void
    flash_cache_disable(void)
{
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_CACHE_CTRL_MASK)) | SMSCM_FLASH_CACHE_CTRL(0x1);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_CACHE_CTRL_MASK)) | SMSCM_FLASH_CACHE_CTRL(0x8);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_SPECULATION_CTRL_MASK)) | SMSCM_FLASH_SPECULATION_CTRL(0x3);
    __ISB();
    __DSB();
}

#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && (FLASH_DRIVER_IS_FLASH_RESIDENT == 1)
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__ ((section (".ramfunc")))
#endif
#endif
    void
    flash_cache_speculation_control(bool isPreProcess, FMU_Type *base)
{
    if (base == FLASH)
    {
        if (isPreProcess == false)
        {
            SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_CACHE_CTRL_MASK)) | SMSCM_FLASH_CACHE_CTRL(0x1);
            SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_SPECULATION_CTRL_MASK)) | SMSCM_FLASH_SPECULATION_CTRL(0x0);
        }
        else
        {
            SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_SPECULATION_CTRL_MASK)) | SMSCM_FLASH_SPECULATION_CTRL(0x3);
        }
    }
#if defined(RF_FMU)
    else if (base == NBU_FLASH)
    {
        if (isPreProcess == false)
        {
            RF_FMCCFG->RFMCCFG = (RF_FMCCFG->RFMCCFG & (~NBU_FLASH_CACHE_CTRL_MASK)) | NBU_FLASH_CACHE_CTRL(0x1);
            RF_FMCCFG->RFMCCFG =
                (RF_FMCCFG->RFMCCFG & (~NBU_FLASH_SPECULATION_CTRL_MASK)) | NBU_FLASH_SPECULATION_CTRL(0x0);
        }
        else
        {
            RF_FMCCFG->RFMCCFG =
                (RF_FMCCFG->RFMCCFG & (~NBU_FLASH_SPECULATION_CTRL_MASK)) | NBU_FLASH_SPECULATION_CTRL(0x3);
        }
    }
#endif
    else
    {
        ; /* No action required */
    }
    /* Memory barriers for good measure.
     * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
    __ISB();
    __DSB();
}

static status_t flash_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t start, uint32_t lengthInBytes, uint32_t alignmentBaseline)
{
    status_t status   = kStatus_FLASH_InvalidArgument;
    FMU_Type *baseTmp = (FMU_Type *)((uint32_t)base & FLASH_ADDR_MASK);

    if (lengthInBytes == 0U)
    {
        status = kStatus_FLASH_Success;
    }
#if defined(RF_FMU)
    else if (config == NULL || base == NULL || ((baseTmp != FLASH) && (baseTmp != NBU_FLASH)))
#else
    else if (config == NULL || base == NULL || baseTmp != FLASH)
#endif
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else if ((start & (alignmentBaseline - 1U)) != 0u)
    {
        /* Verify the start is alignmentBaseline aligned. */
        status = kStatus_FLASH_AlignmentError;
    }
    else
    {
        start = start & FLASH_ADDR_MASK;

        if (baseTmp == FLASH)
        {
            /* Validates the range of the given address */
            if ((start >= config->msf1Config[0].flashDesc.blockBase) &&
                ((start + lengthInBytes) <=
                 (config->msf1Config[0].flashDesc.blockBase + config->msf1Config[0].flashDesc.totalSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else

                if ((start >= config->msf1Config[0].ifrDesc.pflashIfr0Start) &&
                    ((start + lengthInBytes) <=
                     (config->msf1Config[0].ifrDesc.pflashIfr0Start + config->msf1Config[0].ifrDesc.pflashIfr0MemSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else
            {
                status = kStatus_FLASH_AddressError;
            }
        }
        else // if (base == NBU_FLASH || base == NBU_FLASH_NS)
        {
            /* Validates the range of the given address */
            if ((start >= config->msf1Config[1].flashDesc.blockBase) &&
                ((start + lengthInBytes) <=
                 (config->msf1Config[1].flashDesc.blockBase + config->msf1Config[1].flashDesc.totalSize)))
            {
                status = kStatus_FLASH_Success;
            }
            else

                if ((start >= config->msf1Config[1].ifrDesc.pflashIfr0Start) &&
                    ((start + lengthInBytes) <=
                     (config->msf1Config[1].ifrDesc.pflashIfr0Start + config->msf1Config[1].ifrDesc.pflashIfr0MemSize)))
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

static status_t pflash_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t *start, uint32_t lengthInBytes, uint32_t alignmentBaseline)
{
    status_t status   = kStatus_FLASH_InvalidArgument;
    FMU_Type *baseTmp = (FMU_Type *)((uint32_t)base & FLASH_ADDR_MASK);

    if (lengthInBytes == 0U)
    {
        status = kStatus_FLASH_Success;
    }
#if defined(RF_FMU)
    else if ((config == NULL) || (base == NULL) || ((baseTmp != FLASH) && (baseTmp != NBU_FLASH)))
#else
    else if ((config == NULL) || (base == NULL) || (baseTmp != FLASH))
#endif
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else if ((*start & (alignmentBaseline - 1U)) != 0u)
    {
        /* Verify the start is alignmentBaseline aligned. */
        status = kStatus_FLASH_AlignmentError;
    }
    else
    {
        *start &= FLASH_ADDR_MASK;

        if (baseTmp == FLASH)
        {
            /* Validates the range of the given address */
            if ((*start >= config->msf1Config[0].flashDesc.blockBase) &&
                ((*start + lengthInBytes) <=
                 (config->msf1Config[0].flashDesc.blockBase + config->msf1Config[0].flashDesc.totalSize)))
            {
                *start -= config->msf1Config[0].flashDesc.blockBase;
                status = kStatus_FLASH_Success;
            }
            else
            {
                status = kStatus_FLASH_AddressError;
            }
        }
        else // if (base == NBU_FLASH || base == NBU_FLASH_NS)
        {
            /* Validates the range of the given address */
            if ((*start >= config->msf1Config[1].flashDesc.blockBase) &&
                ((*start + lengthInBytes) <=
                 (config->msf1Config[1].flashDesc.blockBase + config->msf1Config[1].flashDesc.totalSize)))
            {
                *start -= config->msf1Config[1].flashDesc.blockBase;
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

static status_t ifr_check_param(
    flash_config_t *config, FMU_Type *base, uint32_t *start, uint32_t lengthInBytes, uint32_t alignmentBaseline)
{
    status_t status   = kStatus_FLASH_InvalidArgument;
    FMU_Type *baseTmp = (FMU_Type *)((uint32_t)base & FLASH_ADDR_MASK);

    if (lengthInBytes == 0U)
    {
        status = kStatus_FLASH_Success;
    }
#if defined(RF_FMU)
    else if (config == NULL || base == NULL || ((baseTmp != FLASH) && (baseTmp != NBU_FLASH)))
#else
    else if (config == NULL || base == NULL || baseTmp != FLASH)
#endif
    {
        status = kStatus_FLASH_InvalidArgument;
    }
    else

        /* Verify the start is alignmentBaseline aligned. */
        if ((*start & (alignmentBaseline - 1U)) != 0u)
    {
        status = kStatus_FLASH_AlignmentError;
    }
    else
    {
        *start &= FLASH_ADDR_MASK;

        if (baseTmp == FLASH)
        {
            if ((*start >= config->msf1Config[0].ifrDesc.pflashIfr0Start) &&
                ((*start + lengthInBytes) <=
                 (config->msf1Config[0].ifrDesc.pflashIfr0Start + config->msf1Config[0].ifrDesc.pflashIfr0MemSize)))
            {
                *start -= config->msf1Config[0].ifrDesc.pflashIfr0Start;
                status = kStatus_FLASH_Success;
            }
            else
            {
                status = kStatus_FLASH_AddressError;
            }
        }
        else // if (base == NBU_FLASH || base == NBU_FLASH_NS)
        {
            if ((*start >= config->msf1Config[1].ifrDesc.pflashIfr0Start) &&
                ((*start + lengthInBytes) <=
                 (config->msf1Config[1].ifrDesc.pflashIfr0Start + config->msf1Config[1].ifrDesc.pflashIfr0MemSize)))
            {
                *start -= config->msf1Config[1].ifrDesc.pflashIfr0Start;
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

/*! @brief Validates the given user key for flash erase APIs.*/
static status_t flash_check_user_key(uint32_t key)
{
    status_t status = kStatus_Fail;

    /* Validate the user key */
    if (key != (uint32_t)kFLASH_ApiEraseKey)
    {
        status = kStatus_FLASH_EraseKeyError;
    }
    else
    {
        status = kStatus_FLASH_Success;
    }

    return status;
}
