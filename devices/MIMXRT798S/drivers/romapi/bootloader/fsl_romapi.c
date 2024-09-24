/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_otp.h"
#include "fsl_romapi_nboot.h"
#include "fsl_romapi_iap.h"
#include "fsl_romapi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.romapi"
#endif

/*! @brief Root of the bootloader API tree.
 *
 * An instance of this struct resides in read-only memory in the bootloader. It
 * provides a user application access to APIs exported by the bootloader.
 *
 * @note The order of existing fields must not be changed.
 */
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg);        /*!< Function to start the bootloader executing.*/
    const uint32_t version;                  /*!< Bootloader version number.*/
    const char *copyright;                   /*!< Copyright string.*/
    const uint32_t reserved0[7];             /*!< reserved*/
    const nboot_interface_t *nbootDriver;    /*!< Image authentication API.*/
    const uint32_t reserved7;                /*!< reserved*/
    const ocotp_driver_t *otpDriver;         /*!< OTP driver API. */
    const iap_api_interface_t *iapApiDriver; /*!< IAP driver API. */
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
    return (ROM_API_TREE->version);
}

const char *bootloader_copyright(void)
{
    assert(ROM_API_TREE);
    return (ROM_API_TREE->copyright);
}
