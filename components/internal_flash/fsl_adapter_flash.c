/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!*********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "fsl_flash.h"
#include "fsl_adapter_flash.h"
/*****************************************************************************
 *****************************************************************************
 * Private macros
 *****************************************************************************
 *****************************************************************************/
#define PGM_SIZE_BYTE FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE
/*!*********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */
static flash_config_t s_flashConfig;
/*!*********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
static hal_flash_status_t HAL_FlashProgramAdaptation(uint32_t dest, uint32_t size, uint8_t *pData);
/*!*********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

/*****************************************************************************
 *****************************************************************************
 * Private functions
 *****************************************************************************
 *****************************************************************************/
static hal_flash_status_t HAL_FlashGetStatus(status_t status)
{
#if (defined(HAL_FLASH_TRANSFER_MODE) && (HAL_FLASH_TRANSFER_MODE > 0U))
    hal_flash_status_t flashStatus = kStatus_HAL_Flash_Error;
    switch (status)
    {
        case (status_t)kStatus_Success:
            flashStatus = kStatus_HAL_Flash_Success;
            break;
        case (status_t)kStatus_FTFx_InvalidArgument:
            flashStatus = kStatus_HAL_Flash_InvalidArgument;
            break;
        case (status_t)kStatus_FTFx_AlignmentError:
            flashStatus = kStatus_HAL_Flash_AlignmentError;
            break;
        default:
            /*MISRA rule 16.4*/
            break;
    }
    return flashStatus;
#else
    return (hal_flash_status_t)status;
#endif
}

static hal_flash_status_t HAL_FlashProgramAdaptation(uint32_t dest, uint32_t size, uint8_t *pData)
{
    return HAL_FlashGetStatus(FLASH_Program(&s_flashConfig, dest, pData, size));
}

/*!*********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function initializes the Flash module for the other Flash APIs.
 *
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_HAL_Flash_PartitionStatusUpdateFailure Failed to update the partition status.
 */
hal_flash_status_t HAL_FlashInit(void)
{
    static uint32_t flashInit = 0;
    status_t status           = (status_t)kStatus_HAL_Flash_Success;

    if (0U == flashInit)
    {
        /* Init Flash */
        status    = FLASH_Init(&s_flashConfig);
        flashInit = 1U;
    }
    return HAL_FlashGetStatus(status);
}

/*!
 * \brief  Verify erase data in Flash
 *
 * @param start           The address of the Flash location
 * @param lengthInBytes   The number of bytes to be checked
 * @param margin          Flash margin value
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 */
hal_flash_status_t HAL_FlashVerifyErase(uint32_t start, uint32_t lengthInBytes, hal_flash_margin_value_t margin)
{
    status_t status;

    uint32_t regPrimask = DisableGlobalIRQ();
    status              = FLASH_VerifyErase(&s_flashConfig, start, lengthInBytes, (ftfx_margin_value_t)margin);
    EnableGlobalIRQ(regPrimask);
    return HAL_FlashGetStatus(status);
}

/*!
 * \brief  Write alligned data to FLASH
 *
 * @param dest            The address of the Flash location
 * @param size            The number of bytes to be programed
 * @param pData           Pointer to the data to be programmed to Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashProgram(uint32_t dest, uint32_t size, uint8_t *pData)
{
    return HAL_FlashProgramAdaptation(dest, size, pData);
}

/*!
 * \brief  Write data to FLASH
 *
 * @param dest        The address of the Flash location
 * @param size        The number of bytes to be programed
 * @param pData       Pointer to the data to be programmed to Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashProgramUnaligned(uint32_t dest, uint32_t size, uint8_t *pData)
{
    uint8_t buffer[PGM_SIZE_BYTE];
    uint32_t bytes            = dest & ((uint32_t)PGM_SIZE_BYTE - 1U);
    hal_flash_status_t status = kStatus_HAL_Flash_Success;

    if (bytes != 0U)
    {
        uint32_t unalignedBytes = (uint32_t)PGM_SIZE_BYTE - bytes;

        if (unalignedBytes > size)
        {
            unalignedBytes = size;
        }

        (void)memcpy(buffer, (uint8_t *)(dest - bytes), PGM_SIZE_BYTE);
        (void)memcpy(&buffer[bytes], pData, unalignedBytes);

        status = HAL_FlashProgramAdaptation(dest - bytes, PGM_SIZE_BYTE, buffer);
        if (kStatus_HAL_Flash_Success == status)
        {
            dest += (uint32_t)PGM_SIZE_BYTE - bytes;
            pData += unalignedBytes;
            size -= unalignedBytes;
        }
    }

    if (kStatus_HAL_Flash_Success == status)
    {
        bytes = size & ~((uint32_t)PGM_SIZE_BYTE - 1U);

        if (bytes != 0U)
        {
            status = HAL_FlashProgramAdaptation(dest, bytes, pData);
            if (kStatus_HAL_Flash_Success == status)
            {
                dest += bytes;
                pData += bytes;
                size -= bytes;
            }
        }

        if (kStatus_HAL_Flash_Success == status)
        {
            if (size != 0U)
            {
                (void)memcpy(buffer, (uint8_t *)dest, PGM_SIZE_BYTE);
                (void)memcpy(buffer, pData, size);
                status = HAL_FlashProgramAdaptation(dest, PGM_SIZE_BYTE, buffer);
            }
        }
    }
    return status;
}
/*!
 * \brief  Erase to 0xFF one or more FLASH sectors.
 *
 * @param dest            The start address of the first sector to be erased
 * @param size            The amount of flash to be erased (multiple of sector size)
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashEraseSector(uint32_t dest, uint32_t size)
{
    int32_t status;

    uint32_t regPrimask = DisableGlobalIRQ();
    status              = FLASH_Erase(&s_flashConfig, dest, size, (uint32_t)kFLASH_ApiEraseKey);
    EnableGlobalIRQ(regPrimask);
    return HAL_FlashGetStatus(status);
}

/*!
 * \brief  Read data from FLASH
 *
 * @param scr             The address of the Flash location to be read
 * @param size            The number of bytes to be read
 * @param pData           Pointer to the data to be read from Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashRead(uint32_t src, uint32_t size, uint8_t *pData)
{
    (void)memcpy(pData, (uint8_t *)src, size);

    return kStatus_HAL_Flash_Success;
}

/*!
 * @brief Returns the desired hal flash property.
 *
 * @param Property        The desired property from the list of properties in
 *                        enum hal_flash_property_tag_t
 * @param value           A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_NotSupport Flash currently not support.
 */
hal_flash_status_t HAL_FlashGetProperty(hal_flash_property_tag_t property, uint32_t *value)
{
    return HAL_FlashGetStatus(FLASH_GetProperty(&s_flashConfig, (flash_property_tag_t)property, value));
}

/*!
 * @brief Set the desired hal flash property.
 *
 * @param Property        The desired property from the list of properties in
 *                        enum hal_flash_property_tag_t
 * @param value           The value would be set to the desired flash property.
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_NotSupport Flash currently not support.
 */
hal_flash_status_t HAL_FlashSetProperty(hal_flash_property_tag_t property, uint32_t value)
{
    return kStatus_HAL_Flash_NotSupport;
}

/*!
 * @brief Returns the security state via the pointer passed into the function.
 *
 * This function retrieves the current flash security status, including the
 * security enabling state and the backdoor key enabling state.
 *
 * @param state           A pointer to the value returned for the current security status
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_NotSupport Flash currently not support.
 */
hal_flash_status_t HAL_FlashGetSecurityState(hal_flash_security_state_t *state)
{
    return HAL_FlashGetStatus(FLASH_GetSecurityState(&s_flashConfig, (ftfx_security_state_t *)((void *)state)));
}
