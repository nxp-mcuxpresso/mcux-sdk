/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SERIAL_PORT_SPI_H__
#define __SERIAL_PORT_SPI_H__

#include "fsl_adapter_spi.h"

/*!
 * @addtogroup serial_port_uart
 * @ingroup serialmanager
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief serial port uart handle size*/
#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
#define SERIAL_PORT_SPI_MASTER_HANDLE_SIZE (36U + HAL_SPI_MASTER_HANDLE_SIZE + HAL_SPI_MASTER_DMA_HANDLE_SIZE)
#else
#define SERIAL_PORT_SPI_MASTER_HANDLE_SIZE (36U + HAL_SPI_MASTER_HANDLE_SIZE)
#endif
#else
#define SERIAL_PORT_SPI_MASTER_HANDLE_SIZE (HAL_SPI_MASTER_HANDLE_SIZE)
#endif

#if (defined(SERIAL_MANAGER_NON_BLOCKING_MODE) && (SERIAL_MANAGER_NON_BLOCKING_MODE > 0U))
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
#define SERIAL_PORT_SPI_SLAVE_HANDLE_SIZE (36U + HAL_SPI_SLAVE_HANDLE_SIZE + HAL_SPI_SLAVE_DMA_HANDLE_SIZE)
#else
#define SERIAL_PORT_SPI_SLAVE_HANDLE_SIZE (36U + HAL_SPI_SLAVE_HANDLE_SIZE)
#endif
#else
#define SERIAL_PORT_SPI_SLAVE_HANDLE_SIZE (HAL_SPI_SLAVE_HANDLE_SIZE)
#endif

#ifndef SERIAL_USE_CONFIGURE_STRUCTURE
#define SERIAL_USE_CONFIGURE_STRUCTURE (0U) /*!< Enable or disable the confgure structure pointer */
#endif

/*! @brief spi clock polarity configuration.*/
typedef enum _serial_spi_clock_polarity
{
    kSerial_SpiClockPolarityActiveHigh = 0x0U, /*!< Active-high spi clock (idles low). */
    kSerial_SpiClockPolarityActiveLow          /*!< Active-low spi clock (idles high). */
} serial_spi_clock_polarity_t;

/*! @brief spi clock phase configuration.*/
typedef enum _serial_spi_clock_phase
{
    kSerial_SpiClockPhaseFirstEdge = 0x0U, /*!< First edge on SPSCK occurs at the middle of the first
                                            *   cycle of a data transfer. */
    kSerial_SpiClockPhaseSecondEdge        /*!< First edge on SPSCK occurs at the start of the
                                            *   first cycle of a data transfer. */
} serial_spi_clock_phase_t;

/*! @brief spi data shifter direction options.*/
typedef enum _serial_spi_shift_direction
{
    kSerial_SpiMsbFirst = 0x0U, /*!< Data transfers start with most significant bit. */
    kSerial_SpiLsbFirst         /*!< Data transfers start with least significant bit. */
} serial_spi_shift_direction_t;

/*! @brief spi master user configure structure.*/
typedef struct _serial_spi_master_config
{
    uint32_t srcClock_Hz;                   /*!< Clock source for spi in Hz */
    uint32_t baudRate_Bps;                  /*!< Baud Rate for spi in Hz */
    serial_spi_clock_polarity_t polarity;   /*!< Clock polarity */
    serial_spi_clock_phase_t phase;         /*!< Clock phase */
    serial_spi_shift_direction_t direction; /*!< MSB or LSB */
    uint8_t instance;                       /*!< Instance of the spi */
    bool enableMaster;                      /*!< Enable spi at initialization time */
    uint32_t configFlags;                   /*!< Transfer config Flags */
#if (defined(HAL_SPI_MASTER_DMA_ENABLE) && (HAL_SPI_MASTER_DMA_ENABLE > 0U))
    bool enableDMA;  /*!< Enable DMA at initialization time */
    void *dmaConfig; /*!< DMA configure pointer */
#endif
} serial_spi_master_config_t;

/*! @brief spi slave user configure structure.*/
typedef struct _serial_spi_slave_config
{
    hal_spi_clock_polarity_t polarity;   /*!< Clock polarity */
    hal_spi_clock_phase_t phase;         /*!< Clock phase */
    hal_spi_shift_direction_t direction; /*!< MSB or LSB */
    uint8_t instance;                    /*!< Instance of the spi */
    bool enableSlave;                    /*!< Enable spi at initialization time */
    uint32_t configFlags;                /*!< Transfer config Flags */
#if (defined(HAL_SPI_SLAVE_DMA_ENABLE) && (HAL_SPI_SLAVE_DMA_ENABLE > 0U))
    bool enableDMA;  /*!< Enable DMA at initialization time */
    void *dmaConfig; /*!< DMA configure pointer */
#endif
} serial_spi_slave_config_t;

/*! @brief spi transfer structure */
typedef struct _serial_spi_transfer
{
    uint8_t *txData; /*!< Send buffer */
    uint8_t *rxData; /*!< Receive buffer */
    size_t dataSize; /*!< Transfer bytes */
    uint32_t flags;  /*!< spi control flag.*/
} serial_spi_transfer_t;

/*! @} */
#endif /* __SERIAL_PORT_SPI_H__ */
