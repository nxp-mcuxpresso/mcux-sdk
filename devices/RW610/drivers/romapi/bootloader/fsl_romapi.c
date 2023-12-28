/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_romapi_otp.h"
#include "fsl_romapi_nboot.h"
#include "fsl_romapi_flexspi.h"
#include "fsl_romapi_iap.h"
#include "fsl_romapi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.romapi"
#endif

//! @brief Boot mode can be selected by user application
//! @note  For master boot, valid boot insterfaces for user application are USART I2C SPI USB-HID USB-DFU SD MMC
//!        For ISP boot, valid boot interfaces for user application are USART I2C SPI
enum
{
    kUserAppBootMode_MasterBoot = 0u,
    kUserAppBootMode_IspBoot    = 1u,
};

//! @brief Boot interface can be selected by user application
//! @note  For USB-HID QSPI USB-DFU SD MMC, these interfaces are invalid for ISP boot
enum
{
    kUserAppBootPeripheral_UART    = 0u,
    kUserAppBootPeripheral_I2C     = 1u,
    kUserAppBootPeripheral_SPI     = 2u,
    kUserAppBootPeripheral_USB_HID = 3u,
    kUserAppBootPeripheral_FLEXSPI = 4u,
    kUserAppBootPeripheral_DFU     = 5u
};

//! @brief Root of the bootloader API tree.
//!
//! An instance of this struct resides in read-only memory in the bootloader. It
//! provides a user application access to APIs exported by the bootloader.
//!
//! @note The order of existing fields must not be changed.
//!
//! @ingroup context
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg); //!< Function to start the bootloader executing.
    standard_version_t version;       //!< Bootloader version number.
    const char *copyright;            //!< Copyright string.
    const uint32_t UNUSED;
    const nboot_interface_t *nbootDriver;               //!< Image authentication API.
    const flexspi_nor_flash_driver_t *flexspiNorDriver; //!< FlexSPI NOR FLASH Driver API.
    const ocotp_driver_t *otpDriver;                    //!< OTP driver API.
    const uint32_t *iapApiDriver;                       //!< IAP driver API.
} bootloader_tree_t;

#define ROM_API_TREE ((bootloader_tree_t *)ROM_API_TREE_ADDR)

void bootloader_user_entry(void *arg)
{
    assert(ROM_API_TREE);
    ROM_API_TREE->runBootloader(arg);
}

uint32_t bootloader_version(void)
{
    assert(ROM_API_TREE);
    return (ROM_API_TREE->version.version);
}

const char *bootloader_copyright(void)
{
    assert(ROM_API_TREE);
    return (ROM_API_TREE->copyright);
}
