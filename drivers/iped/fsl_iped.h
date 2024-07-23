/*
 *     Copyright 2020-2023 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_IPED_H_
#define FSL_IPED_H_

#include <stdint.h>
#include <stddef.h>

#include "fsl_common.h"
#include "fsl_mem_interface.h"
#include "fsl_flash_ffr.h"
#include "mcux_els.h"                // Power Down Wake-up Init
#include <mcuxClEls.h>              // Interface to the entire nxpClEls component
#include <mcuxCsslFlowProtection.h> // Code flow protection

/*!
 * @addtogroup iped
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief IPED driver version. Version 2.2.0.
 *
 * Current version: 2.2.0
 *
 * Change log:
 * - Version 2.2.0
 *   - Renamed CSS to ELS
 * - Version 2.1.1
 *   - Fix build error due to renamed symbols
 * - Version 2.1.0
 *   - Add IPED_Config() (including CMPA write) and IPED_Reconfig() features.
 * - Version 2.0.0
 *   - Initial version
 */
#define FSL_IPED_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @} */

#define kIPED_Region0 (0U) /*!< IPED region 0 */
#define kIPED_Region1 (1U) /*!< IPED region 1 */
#define kIPED_Region2 (2U) /*!< IPED region 2 */
#define kIPED_Region3 (3U) /*!< IPED region 3 */
typedef uint32_t iped_region_t;

#define kIPED_PrinceRounds12 (0U)
#define kIPED_PrinceRounds22 (1U)
typedef uint32_t iped_prince_rounds_t;

/*! @brief IPED fixed tag in flexspi_iped_region_arg_t structure */
#define IPED_TAG       0x49
#define IPED_TAG_SHIFT 24u

/*! @brief IPED region count */
#define IPED_REGION_COUNT 4u

#define IPED_RW_ENABLE_VAL  0x2
#define IPED_RW_DISABLE_VAL 0x1

enum _iped_status
{
    kStatus_IPED_RegionIsLocked = MAKE_STATUS(kStatusGroup_IPED, 0x1),
};

typedef enum _iped_lock
{
    kIPED_RegionUnlock = 1u,
    kIPED_RegionLock   = 3u,
} iped_lock_t;

typedef enum _iped_cmpa
{
    kIPED_SkipCMPA  = 0u,
    kIPED_WriteCMPA = 1u,
} iped_cmpa_t;

typedef struct _flexspi_iped_region_option
{
    uint32_t iped_region : 2; // 0/1/2/3
    uint32_t reserved : 22;
    uint32_t tag : 8; // Fixed to 0x49 ('I')
} flexspi_iped_prot_region_option_t;
typedef struct _flexspi_iped_region_arg
{
    flexspi_iped_prot_region_option_t option;
    uint32_t start;
    uint32_t end;
} flexspi_iped_region_arg_t;

/*! @brief IPED - CMPA page layout */
typedef struct
{
    uint8_t RESERVED_0[144];   /**< Reserved 0, offset: 0x00 */
    __IO uint32_t IPED0_START; /**< IPED0_START, offset: 0x90 */
    __IO uint32_t IPED0_END;   /**< IPED0_END, offset: 0x94 */
    __IO uint32_t IPED1_START; /**< IPED1_START, offset: 0x98 */
    __IO uint32_t IPED1_END;   /**< IPED1_END, offset: 0x9C */
    __IO uint32_t IPED2_START; /**< IPED2_START, offset: 0xA0 */
    __IO uint32_t IPED2_END;   /**< IPED2_END, offset: 0xA4 */
    __IO uint32_t IPED3_START; /**< IPED3_START, offset: 0xA8 */
    __IO uint32_t IPED3_END;   /**< IPED3_END, offset: 0xAC */
    uint8_t RESERVED_1[336];   /**< Reserved 1, offset: 0xB0 */
} IPED_CMPA_page;              /* 144 + (8*4) + 336 = 512 Byte CMPA page */

/*! @brief Define for ELS key store indexes */
#define NXP_DIE_EXT_MEM_ENC_SK 3u
#define NXP_DIE_MEM_IV_ENC_SK  4u
/*! @brief CFPA version and IV indexes (see Protected Flash Region table) */
#define CFPA_VER_OFFSET     0x04u
#define CFPA_IPED_IV_OFFSET 0x20u
/*! @brief CFPA scrach version and IV addresses (see Protected Flash Region table) */
#define CFPA_SCRATCH_VER 0x3dc04
#define CFPA_SCRATCH_IV  0x3dc20
/*! @brief CMPA start address, end address, lock and enable bit-field masks (see Protected Flash Region table) */
#define IPED_START_ADDR_LOCK_EN_MASK 0x3u
#define IPED_START_ADDR_MASK         0xFFFFFF00u
#define IPED_END_ADDR_MASK           0xFFFFFF00u
/*! @brief KDF mask and key properties for NXP_DIE_MEM_IV_ENC_SK (see SYSCON documentation)*/
#define SYSCON_ELS_KDF_MASK 0x07000FCF
/*! @brief CMPA Start address index (see Protected Flash Region table) */
#define CMPA_IPED_START_OFFSET 0x90u
/*! @brief CMPA Start address mask (see Protected Flash Region table) */
#define IPED_ADDRESS_MASK 0xFFFFFF00u
/*! @brief CMPA Start address enable/lock mask bits (see Protected Flash Region table) */
#define IPED_ENABLE_MASK 0x3u
/*! @brief CMPA page size (see Protected Flash Region table) */
#define CMPA_PAGE_SIZE 512u

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enable data encryption.
 *
 * This function enables IPED on-the-fly data encryption.
 *
 * @param base IPED peripheral address.
 */
static inline void IPED_EncryptEnable(FLEXSPI_Type *base)
{
    base->IPEDCTRL |= FLEXSPI_IPEDCTRL_IPED_EN_MASK | FLEXSPI_IPEDCTRL_IPWR_EN_MASK | FLEXSPI_IPEDCTRL_AHBWR_EN_MASK |
                      FLEXSPI_IPEDCTRL_AHBRD_EN_MASK;
}

/*!
 * @brief Disable data encryption.
 *
 * This function disables IPED on-the-fly data encryption.
 *
 * @param base IPED peripheral address.
 */
static inline void IPED_EncryptDisable(FLEXSPI_Type *base)
{
    base->IPEDCTRL &= ~(FLEXSPI_IPEDCTRL_IPED_EN_MASK | FLEXSPI_IPEDCTRL_IPWR_EN_MASK | FLEXSPI_IPEDCTRL_AHBWR_EN_MASK |
                        FLEXSPI_IPEDCTRL_AHBRD_EN_MASK);
}

/*!
 * @brief Locks access for specified region registers or data mask register.
 *
 * This function sets lock on specified region.
 *
 * @param base IPED peripheral address.
 * @param region number to lock
 */
static inline void IPED_SetLock(FLEXSPI_Type *base, iped_region_t region)
{
    /* Unlock soft-lock first */
    base->IPEDCTXCTRL[0] =
        (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
        (IPED_RW_ENABLE_VAL << (region * 2u));
    /* Lock region settings */
    base->IPEDCTXCTRL[1] =
        (base->IPEDCTXCTRL[1] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE1_MASK << (region * 2u))) |
        (IPED_RW_DISABLE_VAL << (region * 2u));
    /* Re-enable soft-lock */
    base->IPEDCTXCTRL[0] =
        (base->IPEDCTXCTRL[0] & ~(FLEXSPI_IPEDCTXCTRLX_IPEDCTXCTRL_CTX0_FREEZE0_MASK << (region * 2u))) |
        (IPED_RW_DISABLE_VAL << (region * 2u));
}

/*!
 * @brief Sets IPED region address range.
 *
 * This function configures IPED region address range.
 *
 * @param base IPED peripheral address.
 * @param region Selection of the IPED region to be configured.
 * @param start_address Start address for region.
 * @param end_address End address for region.
 */
status_t IPED_SetRegionAddressRange(FLEXSPI_Type *base,
                                    iped_region_t region,
                                    uint32_t start_address,
                                    uint32_t end_address);

/*!
 * @brief Gets IPED region base address.
 *
 * This function reads current start and end address settings for selected region.
 *
 * @param base IPED peripheral address.
 * @param region Selection of the IPED region to be configured.
 * @param start_address Start address for region.
 * @param end_address End address for region.
 */
status_t IPED_GetRegionAddressRange(FLEXSPI_Type *base,
                                    iped_region_t region,
                                    uint32_t *start_address,
                                    uint32_t *end_address);

/*!
 * @brief Sets the IPED region IV.
 *
 * This function sets specified AES IV for the given region.
 *
 * @param base IPED peripheral address.
 * @param region Selection of the IPED region to be configured.
 * @param iv 64-bit AES IV in little-endian byte order.
 */
status_t IPED_SetRegionIV(FLEXSPI_Type *base, iped_region_t region, const uint8_t iv[8]);

/*!
 * @brief Sets the IPED region IV.
 *
 * This function sets specified AES IV for the given region.
 *
 * @param base IPED peripheral address.
 * @param rounds Number of PRINCE rounds used during encryption/decryption
 */
static inline void IPED_SetPrinceRounds(FLEXSPI_Type *base, iped_prince_rounds_t rounds)
{
    if (rounds == kIPED_PrinceRounds12)
    {
        base->IPEDCTRL &= ~FLEXSPI_IPEDCTRL_CONFIG_MASK;
    }
    else
    {
        base->IPEDCTRL |= FLEXSPI_IPEDCTRL_CONFIG_MASK;
    }
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
 *
 * @param coreCtx The pointer to the ROM API driver context structure.
 * @param config The pointer to the IPED driver configuration structure.
 * @param lock Locks the IPED configuration, if CMPA write enabled, also sets the IPEDx_START bits[1:0] 01 - Enabled,
 * 10,11 - Enabled & locked
 * @param writeCmpa If selected, IPED configuration will be programmed in PFR flash using ROM API. Note: This can not be
 * reverted!!
 *
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
                        iped_cmpa_t writeCmpa);

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
 * @param config The pointer to the IPED driver configuration structure. If NULL CMPA cinfiguration is read and used.
 * Note: when providing config structure, you have to call Reconfigure for each IPED region individually starting with
 * Region 0. Region 0 must be enabled as a base region.
 *
 * @retval #kStatus_Success
 * @retval #kStatus_Fail
 */
status_t IPED_Reconfigure(api_core_context_t *coreCtx, flexspi_iped_region_arg_t *config);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* FSL_IPED_H_ */
