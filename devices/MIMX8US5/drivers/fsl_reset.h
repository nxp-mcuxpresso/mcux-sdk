/*
 * Copyright 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RESET_H_
#define _FSL_RESET_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup reset
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief reset driver version 2.0.0. */
#define FSL_RESET_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!
 * @brief Enumeration for peripheral reset control bits
 *
 * Defines the enumeration for peripheral reset control in PCC registers
 */
typedef enum _pcc_reset
{
    kRESET_IpInvalid = 0U,

    /* PCC 0 for CM33 */
    kRESET_Wdog0    = (uint32_t)(PCC0_BASE + 0xB0),
    kRESET_Wdog1    = (uint32_t)(PCC0_BASE + 0xB4),
    kRESET_Flexspi0 = (uint32_t)(PCC0_BASE + 0xE4),
    kRESET_Lpit0    = (uint32_t)(PCC0_BASE + 0xEC),
    kRESET_Flexio0  = (uint32_t)(PCC0_BASE + 0xF0),
    kRESET_I3c0     = (uint32_t)(PCC0_BASE + 0xF4),
    kRESET_Lpspi0   = (uint32_t)(PCC0_BASE + 0xF8),
    kRESET_Lpspi1   = (uint32_t)(PCC0_BASE + 0xFC),
    kRESET_Adc0     = (uint32_t)(PCC0_BASE + 0x100),
    kRESET_Dac0     = (uint32_t)(PCC0_BASE + 0x10C),
    kRESET_Dac1     = (uint32_t)(PCC0_BASE + 0x110),

    /* PCC 1 for CM33 */
    kRESET_Flexspi1 = (uint32_t)(PCC1_BASE + 0x48),
    kRESET_Tpm0     = (uint32_t)(PCC1_BASE + 0x54),
    kRESET_Tpm1     = (uint32_t)(PCC1_BASE + 0x58),
    kRESET_Lpi2c0   = (uint32_t)(PCC1_BASE + 0x60),
    kRESET_Lpi2c1   = (uint32_t)(PCC1_BASE + 0x64),
    kRESET_Lpuart0  = (uint32_t)(PCC1_BASE + 0x68),
    kRESET_Lpuart1  = (uint32_t)(PCC1_BASE + 0x6C),
    kRESET_Sai0     = (uint32_t)(PCC1_BASE + 0x70),
    kRESET_Sai1     = (uint32_t)(PCC1_BASE + 0x74),
    kRESET_Adc1     = (uint32_t)(PCC1_BASE + 0x88),
    kRESET_Flexcan  = (uint32_t)(PCC1_BASE + 0xA0),

    /* PCC 2 for FusionF1 */
    kRESET_Wdog2   = (uint32_t)(PCC2_BASE + 0x4),
    kRESET_Tpm2    = (uint32_t)(PCC2_BASE + 0x14),
    kRESET_Tpm3    = (uint32_t)(PCC2_BASE + 0x18),
    kRESET_Mrt     = (uint32_t)(PCC2_BASE + 0x1C),
    kRESET_Lpi2c2  = (uint32_t)(PCC2_BASE + 0x20),
    kRESET_Lpi2c3  = (uint32_t)(PCC2_BASE + 0x24),
    kRESET_I3c1    = (uint32_t)(PCC2_BASE + 0x28),
    kRESET_Lpuart2 = (uint32_t)(PCC2_BASE + 0x2C),
    kRESET_Lpuart3 = (uint32_t)(PCC2_BASE + 0x30),
    kRESET_Lpspi2  = (uint32_t)(PCC2_BASE + 0x34),
    kRESET_Lpspi3  = (uint32_t)(PCC2_BASE + 0x38),
    kRESET_Sai2    = (uint32_t)(PCC2_BASE + 0x3C),
    kRESET_Sai3    = (uint32_t)(PCC2_BASE + 0x40),
    kRESET_Micfil  = (uint32_t)(PCC2_BASE + 0x44),

    /* PCC 3 for CA35 */
    kRESET_Wdog3   = (uint32_t)(PCC3_BASE + 0xA8),
    kRESET_Wdog4   = (uint32_t)(PCC3_BASE + 0xAC),
    kRESET_Lpit1   = (uint32_t)(PCC3_BASE + 0xC8),
    kRESET_Tpm4    = (uint32_t)(PCC3_BASE + 0xCC),
    kRESET_Tpm5    = (uint32_t)(PCC3_BASE + 0xD0),
    kRESET_Flexio1 = (uint32_t)(PCC3_BASE + 0xD4),
    kRESET_I3c2    = (uint32_t)(PCC3_BASE + 0xD8),
    kRESET_Lpi2c4  = (uint32_t)(PCC3_BASE + 0xDC),
    kRESET_Lpi2c5  = (uint32_t)(PCC3_BASE + 0xE0),
    kRESET_Lpuart4 = (uint32_t)(PCC3_BASE + 0xE4),
    kRESET_Lpuart5 = (uint32_t)(PCC3_BASE + 0xE8),
    kRESET_Lpspi4  = (uint32_t)(PCC3_BASE + 0xEC),
    kRESET_Lpspi5  = (uint32_t)(PCC3_BASE + 0xF0),

    /* PCC 4 for CA35 */
    kRESET_Flexspi2 = (uint32_t)(PCC4_BASE + 0x4),
    kRESET_Tpm6     = (uint32_t)(PCC4_BASE + 0x8),
    kRESET_Tpm7     = (uint32_t)(PCC4_BASE + 0xC),
    kRESET_Lpi2c6   = (uint32_t)(PCC4_BASE + 0x10),
    kRESET_Lpi2c7   = (uint32_t)(PCC4_BASE + 0x14),
    kRESET_Lpuart6  = (uint32_t)(PCC4_BASE + 0x18),
    kRESET_Lpuart7  = (uint32_t)(PCC4_BASE + 0x1C),
    kRESET_Sai4     = (uint32_t)(PCC4_BASE + 0x20),
    kRESET_Sai5     = (uint32_t)(PCC4_BASE + 0x24),
    kRESET_Usdhc0   = (uint32_t)(PCC4_BASE + 0x34),
    kRESET_Usdhc1   = (uint32_t)(PCC4_BASE + 0x38),
    kRESET_Usdhc2   = (uint32_t)(PCC4_BASE + 0x3C),
    kRESET_Usb0     = (uint32_t)(PCC4_BASE + 0x40),
    kRESET_Usb0Phy  = (uint32_t)(PCC4_BASE + 0x44),
    kRESET_Usb1     = (uint32_t)(PCC4_BASE + 0x48),
    kRESET_Usb1Phy  = (uint32_t)(PCC4_BASE + 0x4C),
    kRESET_Enet     = (uint32_t)(PCC4_BASE + 0x54),

    /* PCC 5 for HiFi4 */
    kRESET_Tpm8     = (uint32_t)(PCC5_BASE + 0xA0),
    kRESET_Sai6     = (uint32_t)(PCC5_BASE + 0xA4),
    kRESET_Sai7     = (uint32_t)(PCC5_BASE + 0xA8),
    kRESET_Spdif    = (uint32_t)(PCC5_BASE + 0xAC),
    kRESET_Isi      = (uint32_t)(PCC5_BASE + 0xB0),
    kRESET_Csi      = (uint32_t)(PCC5_BASE + 0xBC),
    kRESET_Dsi      = (uint32_t)(PCC5_BASE + 0xC0),
    kRESET_Wdog5    = (uint32_t)(PCC5_BASE + 0xC8),
    kRESET_Epdc     = (uint32_t)(PCC5_BASE + 0xCC),
    kRESET_Pxp      = (uint32_t)(PCC5_BASE + 0xD0),
    kRESET_Gpu2d    = (uint32_t)(PCC5_BASE + 0xF0),
    kRESET_Gpu3d    = (uint32_t)(PCC5_BASE + 0xF4),
    kRESET_Dcnano   = (uint32_t)(PCC5_BASE + 0xF8),
    kRESET_Lpddr4   = (uint32_t)(PCC5_BASE + 0x108),
    kRESET_CsiClkUi = (uint32_t)(PCC5_BASE + 0x10C),
} pcc_reset_t;

/** Array initializers with peripheral reset bits **/
#define DAC_RSTS                 \
    {                            \
        kRESET_Dac0, kRESET_Dac1 \
    } /* Reset bits for DAC peripheral */
#define ENET_RSTS   \
    {               \
        kRESET_Enet \
    } /* Reset bits for ENET peripheral */
#define EPDC_RSTS   \
    {               \
        kRESET_Epdc \
    } /* Reset bits for EPDC peripheral */
#define FLEXCAN_RSTS   \
    {                  \
        kRESET_Flexcan \
    } /* Resets bits for FLEXCAN peripheral */
#define FLEXIO_RSTS                    \
    {                                  \
        kRESET_Flexio0, kRESET_Flexio1 \
    } /* Resets bits for FLEXIO peripheral */
#define FLEXSPI_RSTS                                      \
    {                                                     \
        kRESET_Flexspi0, kRESET_Flexspi1, kRESET_Flexspi2 \
    } /* Resets bits for FLEXSPI peripheral */
#define I3C_RSTS                              \
    {                                         \
        kRESET_I3c0, kRESET_I3c1, kRESET_I3c2 \
    } /* Reset bits for I3C peripheral */
#define ISI_RSTS   \
    {              \
        kRESET_Isi \
    } /* Reset bits for ISI peripheral */
#define LCDIF_RSTS    \
    {                 \
        kRESET_Dcnano \
    } /* Reset bits for LCDIF peripheral */
#define LPADC_RSTS               \
    {                            \
        kRESET_Adc0, kRESET_Adc1 \
    } /* Reset bits for ADC peripheral */
#define LPI2C_RSTS                                                                                               \
    {                                                                                                            \
        kRESET_Lpi2c0, kRESET_Lpi2c1, kRESET_Lpi2c2, kRESET_Lpi2c3, kRESET_Lpi2c4, kRESET_Lpi2c5, kRESET_Lpi2c6, \
            kRESET_Lpi2c7                                                                                        \
    } /* Reset bits for LPI2C peripheral */
#define LPIT_RSTS                  \
    {                              \
        kRESET_Lpit0, kRESET_Lpit1 \
    } /* Reset bits for LPIT peripheral */
#define LPSPI_RSTS                                                                               \
    {                                                                                            \
        kRESET_Lpspi0, kRESET_Lpspi1, kRESET_Lpspi2, kRESET_Lpspi3, kRESET_Lpspi4, kRESET_Lpspi5 \
    } /* Reset bits for LPSPI peripheral */
#define LPUART_RSTS                                                                                     \
    {                                                                                                   \
        kRESET_Lpuart0, kRESET_Lpuart1, kRESET_Lpuart2, kRESET_Lpuart3, kRESET_Lpuart4, kRESET_Lpuart5, \
            kRESET_Lpuart6, kRESET_Lpuart7                                                              \
    } /* Reset bits for LPUART peripheral */
#define MIPI_DSI_RSTS \
    {                 \
        kRESET_Dsi    \
    } /* Reset bits for DSI peripheral */
#define MRT_RSTS   \
    {              \
        kRESET_Mrt \
    } /* Reset bits for MRT peripheral */
#define PXP_RSTS   \
    {              \
        kRESET_Pxp \
    } /* Reset bits for PXP peripheral */
#define SAI_RSTS                                                                                               \
    {                                                                                                          \
        kRESET_Sai0, kRESET_Sai1, kRESET_Sai2, kRESET_Sai3, kRESET_Sai4, kRESET_Sai5, kRESET_Sai6, kRESET_Sai7 \
    } /* Reset bits for SAI peripheral */
#define SPDIF_RSTS   \
    {                \
        kRESET_Spdif \
    } /* Reset bits for SPDIF peripheral */
#define TPM_RSTS                                                                                                \
    {                                                                                                           \
        kRESET_Tpm0, kRESET_Tpm1, kRESET_Tpm2, kRESET_Tpm3, kRESET_Tpm4, kRESET_Tpm5, kRESET_Tpm6, kRESET_Tpm7, \
            kRESET_Tpm8                                                                                         \
    } /* Reset bits for TPM peripheral */
#define USDHC_RSTS                                  \
    {                                               \
        kRESET_Usdhc0, kRESET_Usdhc1, kRESET_Usdhc2 \
    } /* Reset bits for USDHC peripheral */
#define WDOG_RSTS                                                                                          \
    {                                                                                                      \
        kRESET_Wdog0, kRESET_Wdog1, kRESET_Wdog2, kRESET_Wdog3, kRESET_Wdog4, kRESET_Wdog5, kRESET_Invalid \
    } /* Reset bits for WDOG peripheral */

/*!
 * @brief IP reset handle
 */
typedef pcc_reset_t reset_ip_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Assert reset to peripheral.
 *
 * Asserts reset signal to specified peripheral module.
 *
 * @param peripheral Assert reset to this peripheral.
 */
void RESET_SetPeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Clear reset to peripheral.
 *
 * Clears reset signal to specified peripheral module, allows it to operate.
 *
 * @param peripheral Clear reset to this peripheral.
 */
void RESET_ClearPeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Reset peripheral module.
 *
 * Reset peripheral module.
 *
 * @param peripheral Peripheral to reset.
 */
void RESET_PeripheralReset(reset_ip_name_t peripheral);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_RESET_H_ */
