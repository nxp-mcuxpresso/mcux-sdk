/*
 * Copyright 2017, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RM67191_H_
#define _FSL_RM67191_H_

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*
 * Change log:
 *
 *   1.1.0
 *     - Fix MISRA-C 2012 issues.
 *     - Change rm67191_resource_t structure.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RM67191_NOP        (0x00)
#define RM67191_SWRESET    (0x01)
#define RM67191_RDDID      (0x04)
#define RM67191_RDNUMED    (0x05)
#define RM67191_RDDPM      (0x0A)
#define RM67191_RDDMADCTR  (0x0B)
#define RM67191_RDDCOLMOD  (0x0C)
#define RM67191_RDDIM      (0x0D)
#define RM67191_RDDSM      (0x0E)
#define RM67191_RDDSDR     (0x0F)
#define RM67191_SLPIN      (0x10)
#define RM67191_SLPOUT     (0x11)
#define RM67191_INVOFF     (0x20)
#define RM67191_INVON      (0x21)
#define RM67191_ALLPOFF    (0x22)
#define RM67191_ALLPON     (0x23)
#define RM67191_DISPOFF    (0x28)
#define RM67191_DISPON     (0x29)
#define RM67191_RAMWR      (0x2C)
#define RM67191_TEOFF      (0x34)
#define RM67191_TEON       (0x35)
#define RM67191_MADCTR     (0x36)
#define RM67191_IDMOFF     (0x38)
#define RM67191_IDMON      (0x39)
#define RM67191_COLMOD     (0x3A)
#define RM67191_RAMWRC     (0x3C)
#define RM67191_STES       (0x44)
#define RM67191_GSL        (0x45)
#define RM67191_DSTBON     (0x4F)
#define RM67191_WRDISBV    (0x51)
#define RM67191_RDDISBV    (0x52)
#define RM67191_WRCTRLD    (0x53)
#define RM67191_RDCTRLD    (0x54)
#define RM67191_WRRADACL   (0x55)
#define RM67191_RDRADACL   (0x56)
#define RM67191_WRCE       (0x58)
#define RM67191_RDCE       (0x59)
#define RM67191_WRCE1      (0x5A)
#define RM67191_RDCE1      (0x5B)
#define RM67191_WRCE2      (0x5C)
#define RM67191_RDCE2      (0x5D)
#define RM67191_WRTMR      (0x62)
#define RM67191_RDTMR      (0x63)
#define RM67191_WRPA       (0x64)
#define RM67191_RDPA       (0x65)
#define RM67191_WRWB       (0x66)
#define RM67191_RDWB       (0x67)
#define RM67191_WRCEMODE   (0x68)
#define RM67191_RDCEMODE   (0x69)
#define RM67191_RDDDBS     (0xA1)
#define RM67191_RDDDBC     (0xA8)
#define RM67191_RDFC       (0xAA)
#define RM67191_RDCC       (0xAF)
#define RM67191_SETDSIMODE (0xC2)
#define RM67191_RDCTRLD1   (0xDA)
#define RM67191_RDCTRLD2   (0xDB)
#define RM67191_RDCTRLD3   (0xDC)
#define RM67191_WRMAUCCTR  (0xFE)
#define RM67191_RDMAUCCTR  (0xFF)

/*!
 * @brief RM67191 resource.
 */
typedef struct _rm67191_resource
{
    mipi_dsi_device_t *dsiDevice;      /*!< MIPI DSI device. */
    void (*pullResetPin)(bool pullUp); /*!< Function to pull reset pin high or low. */
} rm67191_resource_t;

extern const display_operations_t rm67191_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t RM67191_Init(display_handle_t *handle, const display_config_t *config);

status_t RM67191_Deinit(display_handle_t *handle);

status_t RM67191_Start(display_handle_t *handle);

status_t RM67191_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_RM67191_H_ */
