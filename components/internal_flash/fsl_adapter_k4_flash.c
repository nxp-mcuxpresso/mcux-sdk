/*
 * Copyright 2020 NXP
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
#include "fsl_k4_flash.h"
#include "fsl_adapter_flash.h"
/*****************************************************************************
 *****************************************************************************
 * Private macros
 *****************************************************************************
 *****************************************************************************/
#define PGM_SIZE_BYTE FSL_FEATURE_FLASH_PFLASH_PHRASE_SIZE

#if defined(__IAR_SYSTEMS_ICC__)
#define __RAMFUNC __ramfunc
#elif defined(__GNUC__)
#define __RAMFUNC __attribute__((section(".ramfunc"))) __attribute__((__noinline__))
#endif

/* ECC_SIM_OM option is to be used only when simulating ECC faults for test purposes.
 * The controller raises an ECC fault at the first read access to the flash whatever the master.
 * Any intruction fetch from flash would cause the simulated ECC fault to raise, so need to place
 * such code in RAM. Likewise the flash cache must be disabled.
 * These reasons justify the __ECC_FCT_PLACEMENT attribute used for the ECC related functions.
 */
#ifdef ECC_SIM_ON
#define __ECC_FCT_PLACEMENT __RAMFUNC
__ECC_FCT_PLACEMENT static void flash_cache_disable1(void);
#define FLASH_CACHE_DISABLE() flash_cache_disable1()
#else
#define __ECC_FCT_PLACEMENT
#define FLASH_CACHE_DISABLE() flash_cache_disable()
#endif

#define OCMDR0_CF0_DNCBEI_SHIFT (2u + SMSCM_OCMDR0_OCMCF0_SHIFT)
#define OCMDR0_CF0_DNCBED_SHIFT (3u + SMSCM_OCMDR0_OCMCF0_SHIFT)
#define OCMDR0_CF0_DNCBEI_MASK  (1u << OCMDR0_CF0_DNCBEI_SHIFT)
#define OCMDR0_CF0_DNCBED_MASK  (1u << OCMDR0_CF0_DNCBED_SHIFT)

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
        case (status_t)kStatus_FLASH_InvalidArgument:
            flashStatus = kStatus_HAL_Flash_InvalidArgument;
            break;
        case (status_t)kStatus_FLASH_AlignmentError:
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

static flash_property_tag_t HAL_FlashGetPropertyTag(hal_flash_property_tag_t tag)
{
    flash_property_tag_t ret;
    switch (tag)
    {
        case kHAL_Flash_PropertyPflashSectorSize:
            ret = kFLASH_PropertyPflash0SectorSize;
            break;
        case kHAL_Flash_PropertyPflashTotalSize:
            ret = kFLASH_PropertyPflash0TotalSize;
            break;
        case kHAL_Flash_PropertyPflashBlockCount:
            ret = kFLASH_PropertyPflash0BlockCount;
            break;
        case kHAL_Flash_PropertyPflashBlockBaseAddr:
            ret = kFLASH_PropertyPflash0BlockBaseAddr;
            break;
        case kHAL_Flash_PropertyPflashBlockSize:
            ret = kFLASH_PropertyPflash0BlockSize;
            break;
        default:
            /*MISRA rule 16.4*/
            ret = (flash_property_tag_t)-1;
            break;
    }
    return ret;
}

static hal_flash_status_t HAL_FlashProgramAdaptation(uint32_t dest, uint32_t size, uint8_t *pData)
{
    int32_t status;

    uint32_t regPrimask = DisableGlobalIRQ();

    status = FLASH_Program(&s_flashConfig, FLASH, dest, (uint8_t *)pData, size);

    EnableGlobalIRQ(regPrimask);

    return HAL_FlashGetStatus(status);
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
hal_flash_status_t HAL_FlashInit()
{
    static uint32_t flashInit = 0;
    status_t status           = (status_t)kStatus_HAL_Flash_Success;

    uint32_t regPrimask = DisableGlobalIRQ();
    /*  Disable cache/Prefetch */
    flash_cache_disable();
    EnableGlobalIRQ(regPrimask);
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
    int32_t status;
    uint32_t regPrimask = DisableGlobalIRQ();

    (void)margin;
    if (start >= s_flashConfig.msf1Config[0].ifrDesc.pflashIfr0Start)
    {
        status = FLASH_VerifyEraseIFRPhrase(&s_flashConfig, FLASH, start, lengthInBytes);
    }
    else
    {
        status = FLASH_VerifyErasePhrase(&s_flashConfig, FLASH, start, lengthInBytes);
    }
    EnableGlobalIRQ(regPrimask);
    return HAL_FlashGetStatus(status);
}

/*!
 * \brief  Write aligned data to FLASH
 *
 * @param halFlashHandle  Hal flash adapter handle
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

        memcpy(buffer, (uint8_t *)(dest - bytes), PGM_SIZE_BYTE);
        memcpy(&buffer[bytes], pData, unalignedBytes);

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
                memcpy(buffer, (uint8_t *)dest, PGM_SIZE_BYTE);
                memcpy(buffer, pData, size);
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

    status = FLASH_Erase(&s_flashConfig, FLASH, dest, size, (uint32_t)kFLASH_ApiEraseKey);

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

#ifdef ECC_SIM_ON
__ECC_FCT_PLACEMENT static void flash_cache_disable1(void)
{
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_CACHE_CTRL_MASK)) | SMSCM_FLASH_CACHE_CTRL(0x1);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_CACHE_CTRL_MASK)) | SMSCM_FLASH_CACHE_CTRL(0x8);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_FLASH_SPECULATION_CTRL_MASK)) | SMSCM_FLASH_SPECULATION_CTRL(0x3);
    __ISB();
    __DSB();
}
#endif
__ECC_FCT_PLACEMENT static int flash_bus_fault_ecc_non_correctable_err_on_data_fetch(bool enableNdisable)
{
    int st = -1;
    uint32_t reg_val;
    reg_val = SMSCM->OCMDR0;
    if ((reg_val & SMSCM_OCMDR0_RO_MASK) != SMSCM_OCMDR0_RO_MASK)
    {
        FLASH_CACHE_DISABLE();
        // flash_cache_speculation_control(true, FLASH);
        reg_val &= ~SMSCM_OCMDR0_OCMCF0_MASK;
        if (!enableNdisable)
        {
            /* disable bus fault on data read in case of ECC non recoverable error */
            reg_val |= OCMDR0_CF0_DNCBED_MASK;
        }
        SMSCM->OCMDR0 = reg_val;
        st            = 0;
    }
    return st;
}

/*!
 * \brief  Activate or deactivate ECC fault detection without bus faulting
 *
 * Note a RAM version of this function is required when ECC fault simulation is used.
 *
 * @param sav_cfg      pointer of 32 bit location to remember flash cache and
 *                     ECC configuration to be restored
 *
 * @retval 0 if OK might be -1 if configuration is readonly.
 *
 */
__ECC_FCT_PLACEMENT int FLASH_ActivateEccFaultDetection(FMU_Type *base, uint32_t *sav_cfg)
{
    int st;
    uint32_t fcncf_val;
    *sav_cfg = SMSCM->OCMDR0;
    st       = flash_bus_fault_ecc_non_correctable_err_on_data_fetch(false);
    if (0 == st)
    {
        fcncf_val = base->FCNFG;
        fcncf_val |= FMU_FCNFG_DFDIE_MASK;
        /* Command Complete CCIE must remain unset */
        // fcncf_val &= ~FMU_FCNFG_CCIE_MASK;
        base->FCNFG = fcncf_val;
        __ISB();
        __DSB();
    }
    return st;
}

__ECC_FCT_PLACEMENT int FLASH_DeactivateEccFaultDetection(FMU_Type *base, uint32_t restore_cfg)
{
    int st;
    uint32_t fcncf_val;
    st = flash_bus_fault_ecc_non_correctable_err_on_data_fetch(true);

    /* Reenable flash cache and reenable bus fault on  ECC non correctable fault detection */
    SMSCM->OCMDR0 = restore_cfg;
    fcncf_val     = base->FCNFG;
    base->FCNFG   = fcncf_val;
    __ISB();
    __DSB();
    return st;
}

bool HAL_FlashEccStatusRaised(void)
{
    return (FMU0->FSTAT & FLASH_FSTAT_DFDIF_MASK) ? true : false;
}

/*!
 * \brief  Read data from FLASH checking for ECC errors
 *
 * Note a RAM version of this function is required when ECC fault simulation is used.
 *
 * @param scr             The address of the Flash location to be read
 * @param size            The number of bytes to be read
 * @param pData           Pointer to the data to be read from Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *         #kStatus_HAL_Flash_EccError if ECC Fault error got raised.
 *
 */
hal_flash_status_t HAL_FlashReadCheckEccFaults(uint32_t src, uint32_t size, uint8_t *pData)
{
    hal_flash_status_t st = kStatus_HAL_Flash_Success;

    uint32_t sav_cfg;
    uint8_t *addr       = (uint8_t *)src;
    uint8_t *end_addr   = addr + size;
    uint32_t regPrimask = DisableGlobalIRQ();
    FMU0->FSTAT         = FLASH_FSTAT_DFDIF_MASK;
    if (FLASH_ActivateEccFaultDetection(FMU0, &sav_cfg) == 0)
    {
        while (addr < end_addr)
        {
            *pData = *addr;
            if ((FMU0->FSTAT & FLASH_FSTAT_DFDIF_MASK) == FLASH_FSTAT_DFDIF_MASK)
            {
                /* Acknowledge Double ECC Fault event */
                FMU0->FSTAT = FLASH_FSTAT_DFDIF_MASK;
                st          = kStatus_HAL_Flash_EccError;
                break;
            }
            addr++;
            pData++;
        }
        (void)FLASH_DeactivateEccFaultDetection(FMU0, sav_cfg);
    }
    EnableGlobalIRQ(regPrimask);
    return st;
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
    flash_property_tag_t ret;
    if (value == NULL)
    {
        return kStatus_HAL_Flash_InvalidArgument;
    }
    ret = HAL_FlashGetPropertyTag(property);
    if (((flash_property_tag_t)-1) == ret)
    {
        return kStatus_HAL_Flash_NotSupport;
    }
    else
    {
        return HAL_FlashGetStatus(FLASH_GetProperty(&s_flashConfig, ret, value));
    }
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
#if 0
    return HAL_FlashGetStatus(FLASH_GetSecurityState(s_flashConfig, (ftfx_security_state_t *)state));
#else
    return kStatus_HAL_Flash_NotSupport;
#endif
}