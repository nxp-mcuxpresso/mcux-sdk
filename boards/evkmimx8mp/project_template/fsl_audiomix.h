/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_AUDIOMIX_H_
#define _FSL_AUDIOMIX_H_

#include "fsl_common.h"

/*!
 * @addtogroup audiomix
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief AUDIOMIX driver version 2.0.1. */
#define FSL_AUDIOMIX_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*!@brief AUDIOMIX attach id combination */
#define AUDIOMIX_ATTACH_ID(offset, mask, value) \
    ((uint32_t)(offset) | ((uint32_t)(mask) << 16U) | ((uint32_t)(value) << 24U))
#define GET_AUDIOMIX_ATTACH_ID_OFFSET(id) ((uint32_t)(id)&0xFFFFU)
#define GET_AUDIOMIX_ATTACH_ID_MASK(id)   (((uint32_t)(id) >> 16U) & 0xFFU)
#define GET_AUDIOMIX_ATTACH_ID_value(id)  (((uint32_t)(id) >> 24U) & 0xFFU)

/*!@brief audio mix attch clk id */
typedef enum _audiomix_attch_clk
{
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 0U << 1U), /*!< attach SAI1 MCLK2 to SAI1 root */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 1U << 1U), /*!< attach SAI1 MCLK2 to SAI2 root */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 2U << 1U), /*!< attach SAI1 MCLK2 to SAI3 root */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 4U << 1U), /*!< attach SAI1 MCLK2 to SAI5 root */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 5U << 1U), /*!< attach SAI1 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 6U << 1U), /*!< attach SAI1 MCLK2 to SAI7 root */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 7U << 1U), /*!< attach SAI1 MCLK2 to SAI1 MCLK */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 8U << 1U), /*!< attach SAI1 MCLK2 to SAI2 MCLK */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 9U << 1U), /*!< attach SAI1 MCLK2 to SAI3 MCLK */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 11U << 1U), /*!< attach SAI1 MCLK2 to SAI5 MCLK */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 12U << 1U), /*!< attach SAI1 MCLK2 to SAI6 MCLK */
    kAUDIOMIX_Attach_SAI1_MCLK2_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1EU, 13U << 1U), /*!< attach SAI1 MCLK2 to SAI7 MCLK */

    kAUDIOMIX_Attach_SAI1_MCLK1_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1U, 0U), /*!< attach SAI1 MCLK1 to SAI1 root */
    kAUDIOMIX_Attach_SAI1_MCLK1_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X300U, 0x1U, 1U), /*!< attach SAI1 MCLK1 to SAI1 MCLK */

    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 0U << 1U), /*!< attach SAI2 MCLK2 to SAI1 root */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 1U << 1U), /*!< attach SAI2 MCLK2 to SAI2 root */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 2U << 1U), /*!< attach SAI2 MCLK2 to SAI3 root */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 4U << 1U), /*!< attach SAI2 MCLK2 to SAI5 root */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 5U << 1U), /*!< attach SAI2 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 6U << 1U), /*!< attach SAI2 MCLK2 to SAI7 root */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 7U << 1U), /*!< attach SAI2 MCLK2 to SAI1 MCLK */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 8U << 1U), /*!< attach SAI2 MCLK2 to SAI2 MCLK */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 9U << 1U), /*!< attach SAI2 MCLK2 to SAI3 MCLK */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 11U << 1U), /*!< attach SAI2 MCLK2 to SAI5 MCLK */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 12U << 1U), /*!< attach SAI2 MCLK2 to SAI6 MCLK */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 13U << 1U), /*!< attach SAI2 MCLK2 to SAI7 MCLK */
    kAUDIOMIX_Attach_SAI2_MCLK2_To_SPDIF_ExtCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1EU, 14U << 1U), /*!< attach SAI2 MCLK2 to SPDIF EXTCLK */

    kAUDIOMIX_Attach_SAI2_MCLK1_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1U, 0U), /*!< attach SAI2 MCLK1 to SAI2 root */
    kAUDIOMIX_Attach_SAI2_MCLK1_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X304U, 0x1U, 1U), /*!< attach SAI2 MCLK1 to SAI2 MCLK */

    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 0U << 1U), /*!< attach SAI3 MCLK2 to SAI1 root */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 1U << 1U), /*!< attach SAI3 MCLK2 to SAI2 root */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 2U << 1U), /*!< attach SAI3 MCLK2 to SAI3 root */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 4U << 1U), /*!< attach SAI3 MCLK2 to SAI5 root */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 5U << 1U), /*!< attach SAI3 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 6U << 1U), /*!< attach SAI3 MCLK2 to SAI7 root */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 7U << 1U), /*!< attach SAI3 MCLK2 to SAI1 MCLK */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 8U << 1U), /*!< attach SAI3 MCLK2 to SAI2 MCLK */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 9U << 1U), /*!< attach SAI3 MCLK2 to SAI3 MCLK */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 11U << 1U), /*!< attach SAI3 MCLK2 to SAI5 MCLK */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 12U << 1U), /*!< attach SAI3 MCLK2 to SAI6 MCLK */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 13U << 1U), /*!< attach SAI3 MCLK2 to SAI7 MCLK */
    kAUDIOMIX_Attach_SAI3_MCLK2_To_SPDIF_ExtCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1EU, 14U << 1U), /*!< attach SAI3 MCLK2 to SPDIF EXTCLK */

    kAUDIOMIX_Attach_SAI3_MCLK1_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1U, 0U), /*!< attach SAI3 MCLK1 to SAI3 root */
    kAUDIOMIX_Attach_SAI3_MCLK1_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X308U, 0x1U, 1U), /*!< attach SAI3 MCLK1 to SAI3 MCLK */

    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 0U << 1U), /*!< attach SAI5 MCLK2 to SAI1 root */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 1U << 1U), /*!< attach SAI5 MCLK2 to SAI2 root */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 2U << 1U), /*!< attach SAI5 MCLK2 to SAI3 root */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 4U << 1U), /*!< attach SAI5 MCLK2 to SAI5 root */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 5U << 1U), /*!< attach SAI5 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 6U << 1U), /*!< attach SAI5 MCLK2 to SAI7 root */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 7U << 1U), /*!< attach SAI5 MCLK2 to SAI1 MCLK */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 8U << 1U), /*!< attach SAI5 MCLK2 to SAI2 MCLK */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 9U << 1U), /*!< attach SAI5 MCLK2 to SAI3 MCLK */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 11U << 1U), /*!< attach SAI5 MCLK2 to SAI5 MCLK */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 12U << 1U), /*!< attach SAI5 MCLK2 to SAI6 MCLK */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 13U << 1U), /*!< attach SAI5 MCLK2 to SAI7 MCLK */
    kAUDIOMIX_Attach_SAI5_MCLK2_To_SPDIF_ExtCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1EU, 14U << 1U), /*!< attach SAI5 MCLK2 to SPDIF EXTCLK */

    kAUDIOMIX_Attach_SAI5_MCLK1_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1U, 0U), /*!< attach SAI5 MCLK1 to SAI5 root */
    kAUDIOMIX_Attach_SAI5_MCLK1_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X30CU, 0x1U, 1U), /*!< attach SAI5 MCLK1 to SAI5 MCLK */

    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 0U << 1U), /*!< attach SAI6 MCLK2 to SAI1 root */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 1U << 1U), /*!< attach SAI6 MCLK2 to SAI2 root */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 2U << 1U), /*!< attach SAI6 MCLK2 to SAI3 root */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 4U << 1U), /*!< attach SAI6 MCLK2 to SAI5 root */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 5U << 1U), /*!< attach SAI6 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 6U << 1U), /*!< attach SAI6 MCLK2 to SAI7 root */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 7U << 1U), /*!< attach SAI6 MCLK2 to SAI1 MCLK */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 8U << 1U), /*!< attach SAI6 MCLK2 to SAI2 MCLK */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 9U << 1U), /*!< attach SAI6 MCLK2 to SAI3 MCLK */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 11U << 1U), /*!< attach SAI6 MCLK2 to SAI5 MCLK */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 12U << 1U), /*!< attach SAI6 MCLK2 to SAI6 MCLK */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 13U << 1U), /*!< attach SAI6 MCLK2 to SAI7 MCLK */
    kAUDIOMIX_Attach_SAI6_MCLK2_To_SPDIF_ExtCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1EU, 14U << 1U), /*!< attach SAI6 MCLK2 to SPDIF EXTCLK */

    kAUDIOMIX_Attach_SAI6_MCLK1_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1U, 0U), /*!< attach SAI6 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI6_MCLK1_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X310U, 0x1U, 1U), /*!< attach SAI6 MCLK2 to SAI6 MCLK */

    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI1_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 0U << 1U), /*!< attach SAI7 MCLK2 to SAI1 root */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI2_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 1U << 1U), /*!< attach SAI7 MCLK2 to SAI2 root */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI3_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 2U << 1U), /*!< attach SAI7 MCLK2 to SAI3 root */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI5_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 4U << 1U), /*!< attach SAI7 MCLK2 to SAI5 root */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI6_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 5U << 1U), /*!< attach SAI7 MCLK2 to SAI6 root */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 6U << 1U), /*!< attach SAI7 MCLK2 to SAI7 root */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI1_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 7U << 1U), /*!< attach SAI7 MCLK2 to SAI1 MCLK */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI2_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 8U << 1U), /*!< attach SAI7 MCLK2 to SAI2 MCLK */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI3_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 9U << 1U), /*!< attach SAI7 MCLK2 to SAI3 MCLK */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI5_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 11U << 1U), /*!< attach SAI7 MCLK2 to SAI5 MCLK */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI6_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 12U << 1U), /*!< attach SAI7 MCLK2 to SAI6 MCLK */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 13U << 1U), /*!< attach SAI7 MCLK2 to SAI7 MCLK */
    kAUDIOMIX_Attach_SAI7_MCLK2_To_SPDIF_ExtCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1EU, 14U << 1U), /*!< attach SAI7 MCLK2 to SPDIF_ExtCLK */

    kAUDIOMIX_Attach_SAI7_MCLK1_To_SAI7_ROOT =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1U, 0U), /*!< attach SAI7 MCLK1 to SAI7 root */
    kAUDIOMIX_Attach_SAI7_MCLK1_To_SAI7_MCLK =
        AUDIOMIX_ATTACH_ID(0X314U, 0x1U, 1U), /*!< attach SAI7 MCLK1 to SAI7 MCLK */

    kAUDIOMIX_Attach_PDM_Root_to_CCM_PDM =
        AUDIOMIX_ATTACH_ID(0X318U, 0x3U, 0U), /*!< attach PDM ROOT to CCM PDM clock */
    kAUDIOMIX_Attach_PDM_Root_to_SAI_PLL_DVI2 =
        AUDIOMIX_ATTACH_ID(0X318U, 0x3U, 1U), /*!< attach PDM ROOT to sai pll div2 */
    kAUDIOMIX_Attach_PDM_Root_to_SAI1_MCLK = AUDIOMIX_ATTACH_ID(0X318U, 0x3U, 2U), /*!< attach PDM ROOT to SAI1 mclk */
} audiomix_attch_clk_t;

/*!@brief audio mix power control */
enum _audiomix_power_ctrl
{
    kAUDIOMIX_PowerCtrlEDMA  = 1U,   /*!< edma power control */
    kAUDIOMIX_PowerCtrlSDMA2 = 2U,   /*!< SDMA2 power control */
    kAUDIOMIX_PowerCtrlSDMA3 = 4U,   /*!< SDMA3 power control */
    kAUDIOMIX_PowerCtrlPDM   = 8U,   /*!< PDM power control */
    kAUDIOMIX_PowerCtrlSAI1  = 16U,  /*!< SAI1 power control */
    kAUDIOMIX_PowerCtrlSAI2  = 32U,  /*!< SAI2 power control */
    kAUDIOMIX_PowerCtrlSAI3  = 64U,  /*!< SAI3 power control */
    kAUDIOMIX_PowerCtrlSAI5  = 128U, /*!< SAI5 power control */
    kAUDIOMIX_PowerCtrlSAI6  = 256U, /*!< SAI6 power control */
    kAUDIOMIX_PowerCtrlSAI7  = 512U, /*!< SAI7 power control */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name AUDIOMIX clock Setting
 * @{
 */

/*!
 * @brief audiomix attach clock.
 *
 * @param base audiomix base address.
 * @param id attach clock id.
 */
void AUDIOMIX_AttachClk(AUDIOMIX_Type *base, audiomix_attch_clk_t id);

/*!
 * @brief audiomix low power ack bit status.
 *
 * @param base audiomix base address.
 * @param ip reference _audiomix_power_ctrl, can be a value or combine value in _audiomix_power_ctrl
 */
static inline uint32_t AUDIOMIX_GetIPStopAck(AUDIOMIX_Type *base, uint32_t ip)
{
    uint32_t reg = base->IPG_LP_CTRL;

    return reg & (ip << 10U);
}

/*!
 * @brief audiomix low power stop mode
 *
 * @param base audiomix base address.
 * @param ip reference _audiomix_power_ctrl, can be a value or combine value in _audiomix_power_ctrl
 */
static inline void AUDIOMIX_SetIPStop(AUDIOMIX_Type *base, uint32_t ip)
{
    base->IPG_LP_CTRL |= ip & 0x3FFU;
}

/*!
 * @brief audiomix earc reset
 *
 * @param base audiomix base address.
 * @param enable true is reset, flase is release.
 */
static inline void AUDIOMIX_SetEARCReset(AUDIOMIX_Type *base, bool enable)
{
    if (enable)
    {
        base->EARC &= ~AUDIOMIX_EARC_RESETB_MASK;
    }
    else
    {
        base->EARC |= AUDIOMIX_EARC_RESETB_MASK;
    }
}

/*!
 * @brief audiomix earc PHY reset
 *
 * @param base audiomix base address.
 * @param enable true is reset, flase is release.
 */
static inline void AUDIOMIX_SetEARCPhyReset(AUDIOMIX_Type *base, bool enable)
{
    if (enable)
    {
        base->EARC &= ~AUDIOMIX_EARC_PHY_RESETB_MASK;
    }
    else
    {
        base->EARC |= AUDIOMIX_EARC_PHY_RESETB_MASK;
    }
}

/*!
 * @brief Initializes the SAI PLL.
 * note This function can't detect whether the AUDIO PLL has been enabled and
 * used by some IPs.
 *
 * @param base audiomix base address.
 * @param config Pointer to the configuration structure(see ref ccm_analog_frac_pll_config_t enumeration).
 *
 */
void AUDIOMIX_InitAudioPll(AUDIOMIX_Type *base, const ccm_analog_frac_pll_config_t *config);

/*!
 * brief De-initialize the SAI PLL.
 */
void AUDIOMIX_DeinitAudioPll1(AUDIOMIX_Type *base);

/*!
 * @brief Get the sai PLL output freq.
 *
 * @retval sai pll output freq.
 */
uint32_t AUDIOMIX_GetAudioPllFreq(AUDIOMIX_Type *base);
/* @} */

#if defined(__cplusplus)
}
#endif
/* @} */
#endif /* _FSL_AUDIOMIX_H_ */
