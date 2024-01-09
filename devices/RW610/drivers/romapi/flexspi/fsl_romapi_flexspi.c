/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi_flexspi.h"
#include "fsl_romapi.h"

#define FLEXSPI_FLASH_API_TREE ((flexspi_nor_flash_driver_t *)(((uint32_t *)ROM_API_TREE_ADDR)[5]))

uint32_t flexspi_nor_flash_version(void)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->version;
}

//!@brief Initialize Serial NOR devices via FlexSPI
status_t flexspi_nor_flash_init(uint32_t instance, flexspi_nor_config_t *config)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->init(instance, config);
}

//!@brief Wait until Serial NOR device is idle
status_t flexspi_nor_flash_wait_busy(uint32_t instance, flexspi_nor_config_t *config, uint32_t address, bool keepState)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->wait_busy(instance, config, address, keepState);
}
//!@brief Program data to Serial NOR via FlexSPI
status_t flexspi_nor_flash_page_program(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src, bool keepState)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->page_program(instance, config, dstAddr, src, keepState);
}

//!@brief Erase all the Serial NOR devices connected on FlexSPI
status_t flexspi_nor_flash_erase_all(uint32_t instance, flexspi_nor_config_t *config)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->erase_all(instance, config);
}

//!@brief Erase Flash Region specified by address and length
status_t flexspi_nor_flash_erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->erase(instance, config, start, length);
}

//!@brief Erase one sector specified by address
status_t flexspi_nor_flash_erase_sector(uint32_t instance, flexspi_nor_config_t *config, uint32_t address)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->erase_sector(instance, config, address);
}

//!@brief Erase one block specified by address
status_t flexspi_nor_flash_erase_block(uint32_t instance, flexspi_nor_config_t *config, uint32_t address)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->erase_block(instance, config, address);
}

//!@brief Read data from Serial NOR
status_t flexspi_nor_flash_read(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->read(instance, config, dst, start, bytes);
}

//!@brief Configure Clock for FlexSPI
void flexspi_clock_config(uint32_t instance, uint32_t freq, uint32_t sampleClkMode)
{
    assert(FLEXSPI_FLASH_API_TREE);
    FLEXSPI_FLASH_API_TREE->config_clock(instance, freq, sampleClkMode);
}

//!@brief Set the clock source for FlexSPI NOR
status_t flexspi_nor_set_clock_source(uint32_t clockSource)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->set_clock_source(clockSource);
}

//!@brief Get FlexSPI NOR Configuration Block based on specified option
status_t flexspi_nor_get_config(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->get_config(instance, config, option);
}

//!@brief Reset FlexSPI NOR Flash
void flexspi_nor_hw_reset(uint32_t instance, uint32_t reset_logic)
{
    assert(FLEXSPI_FLASH_API_TREE);
    FLEXSPI_FLASH_API_TREE->hw_reset(instance, reset_logic);
}

//!@brief Perform FlexSPI command
status_t flexspi_command_xfer(uint32_t instance, flexspi_xfer_t *xfer)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->xfer(instance, xfer);
}

//!@brief Configure FlexSPI Lookup table
status_t flexspi_update_lut(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->update_lut(instance, seqIndex, lutBase, numberOfSeq);
}

//!@brief Partially Program data to Serial NOR via FlexSPI
status_t flexspi_nor_flash_partial_program(uint32_t instance,
                                           flexspi_nor_config_t *config,
                                           uint32_t dstAddr,
                                           const uint32_t *src,
                                           uint32_t length,
                                           bool keepState)
{
    assert(FLEXSPI_FLASH_API_TREE);
    return FLEXSPI_FLASH_API_TREE->partial_program(instance, config, dstAddr, src, length, keepState);
}
