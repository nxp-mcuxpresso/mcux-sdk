/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_TRDC_SOC_H_
#define _FSL_TRDC_SOC_H_

#include "fsl_common.h"

/*!
 * @addtogroup trdc_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.0. */
#define FSL_TRDC_SOC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#define TRDC_DACFG_NCM_MASK                     TRDC_MBC2_DACFG_NCM_MASK
#define TRDC_MBC_MEM_GLBCFG_NBLKS_MASK          TRDC_MBC2_MBC_MEM_GLBCFG_NBLKS_MASK
#define TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_MASK      TRDC_MBC2_MBC_MEM_GLBCFG_SIZE_LOG2_MASK
#define TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_SHIFT     TRDC_MBC2_MBC_MEM_GLBCFG_SIZE_LOG2_SHIFT
#define TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL0_SHIFT TRDC_MBC2_MBC_NSE_BLK_CLR_ALL_DID_SEL0_SHIFT
#define TRDC_MDA_W_DFMT0_LK1_MASK               TRDC_MBC2_MDA_W_DFMT0_LK1_MASK
#define TRDC_MDA_W_DFMT0_VLD_MASK               TRDC_MBC2_MDA_W_DFMT0_VLD_MASK
#define TRDC_MDA_W_DFMT1_LK1_MASK               TRDC_MBC2_MDA_W_DFMT1_LK1_MASK
#define TRDC_MDA_W_DFMT1_VLD_MASK               TRDC_MBC2_MDA_W_DFMT1_VLD_MASK
#define TRDC_MRC_DOM0_RGD_W_MRACSEL_MASK        TRDC_MBC2_MRC_DOM0_RGD_W_MRACSEL_MASK
#define TRDC_MRC_DOM0_RGD_W_NSE_MASK            TRDC_MBC2_MRC_DOM0_RGD_W_NSE_MASK
#define TRDC_MRC_DOM0_RGD_W_VLD_MASK            TRDC_MBC2_MRC_DOM0_RGD_W_VLD_MASK
#define TRDC_MRC_GLBCFG_NRGNS_MASK              TRDC_MBC2_MRC_GLBCFG_NRGNS_MASK
#define TRDC_MRC_GLBCFG_NRGNS_SHIFT             TRDC_MBC2_MRC_GLBCFG_NRGNS_SHIFT
#define TRDC_TRDC_CR_GVLDB_MASK                 TRDC_MBC2_TRDC_CR_GVLDB_MASK
#define TRDC_TRDC_CR_GVLDM_MASK                 TRDC_MBC2_TRDC_CR_GVLDM_MASK
#define TRDC_TRDC_CR_GVLDR_MASK                 TRDC_MBC2_TRDC_CR_GVLDR_MASK
#define TRDC_TRDC_FLW_CTL_LK_MASK               TRDC_MBC2_TRDC_FLW_CTL_LK_MASK
#define TRDC_TRDC_FLW_CTL_V_MASK                TRDC_MBC2_TRDC_FLW_CTL_V_MASK
#define TRDC_TRDC_HWCFG0_NDID_MASK              TRDC_MBC2_TRDC_HWCFG0_NDID_MASK
#define TRDC_TRDC_HWCFG0_NDID_SHIFT             TRDC_MBC2_TRDC_HWCFG0_NDID_SHIFT
#define TRDC_TRDC_HWCFG0_NMBC_MASK              TRDC_MBC2_TRDC_HWCFG0_NMBC_MASK
#define TRDC_TRDC_HWCFG0_NMBC_SHIFT             TRDC_MBC2_TRDC_HWCFG0_NMBC_SHIFT
#define TRDC_TRDC_HWCFG0_NMRC_MASK              TRDC_MBC2_TRDC_HWCFG0_NMRC_MASK
#define TRDC_TRDC_HWCFG0_NMRC_SHIFT             TRDC_MBC2_TRDC_HWCFG0_NMRC_SHIFT
#define TRDC_TRDC_HWCFG0_NMSTR_MASK             TRDC_MBC2_TRDC_HWCFG0_NMSTR_MASK
#define TRDC_TRDC_HWCFG0_NMSTR_SHIFT            TRDC_MBC2_TRDC_HWCFG0_NMSTR_SHIFT
#define TRDC_TRDC_HWCFG1_DID_MASK               TRDC_MBC2_TRDC_HWCFG1_DID_MASK
#define TRDC_TRDC_HWCFG1_DID_SHIFT              TRDC_MBC2_TRDC_HWCFG1_DID_SHIFT
#define TRDC_TRDC_IDAU_CR_VLD_MASK              TRDC_MBC2_TRDC_IDAU_CR_VLD_MASK
#define TRDC_W1_EATR_MASK                       TRDC_MBC2_W1_EATR_MASK
#define TRDC_W1_EATR_SHIFT                      TRDC_MBC2_W1_EATR_SHIFT
#define TRDC_W1_EDID_MASK                       TRDC_MBC2_W1_EDID_MASK
#define TRDC_W1_EPORT_MASK                      TRDC_MBC2_W1_EPORT_MASK
#define TRDC_W1_EPORT_SHIFT                     TRDC_MBC2_W1_EPORT_SHIFT
#define TRDC_W1_ERW_MASK                        TRDC_MBC2_W1_ERW_MASK
#define TRDC_W1_ERW_SHIFT                       TRDC_MBC2_W1_ERW_SHIFT
#define TRDC_W1_EST_MASK                        TRDC_MBC2_W1_EST_MASK
#define TRDC_W1_EST_SHIFT                       TRDC_MBC2_W1_EST_SHIFT
#define TRDC_MBC_NSE_BLK_CLR_ALL_MEMSEL         TRDC_MBC2_MBC_NSE_BLK_CLR_ALL_MEMSEL
#define TRDC_MRC_DOM0_RGD_W_MRACSEL             TRDC_MBC2_MRC_DOM0_RGD_W_MRACSEL
#define TRDC_MRC_DOM0_RGD_W_NSE                 TRDC_MBC2_MRC_DOM0_RGD_W_NSE
#define TRDC_MRC_DOM0_RGD_W_VLD                 TRDC_MBC2_MRC_DOM0_RGD_W_VLD
#define TRDC_TRDC_FDID_FDID                     TRDC_MBC2_TRDC_FDID_FDID
#define TRDC_TRDC_FLW_CTL_LK                    TRDC_MBC2_TRDC_FLW_CTL_LK
#define TRDC_TRDC_FLW_CTL_V                     TRDC_MBC2_TRDC_FLW_CTL_V
#define TRDC_W3_RECR                            TRDC_MBC2_W3_RECR

/*!@brief TRDC base table */
#define TRDC_BASE_PTRS                \
    {                                 \
        (TRDC_Type *)0u, TRDC1, TRDC2 \
    }

/*!
 * @brief Enumeration for TRDC master mapping
 *
 * Defines the enumeration for TRDC master resource collections.
 */

typedef enum _trdc_master
{
    kTRDC1_MasterReserved = 0U, /**< Reserved */
    kTRDC1_MasterCM33     = 1U, /**< CM33 */
    kTRDC1_MasterEDMA1    = 2U, /**< EDMA1 */
    kTRDC1_MasterMTR_FBX  = 3U, /**< MTR FBX */
    kTRDC1_MasterMTR      = 4U, /**< MTR */

    kTRDC2_MasterReserved0 = 0U, /**< Reserved0 */
    kTRDC2_MasterReserved1 = 1U, /**< Reserved1 */
    kTRDC2_MasterDAP       = 2U, /**< DAP AHB_AP_SYS */
    kTRDC2_MasterCoreSight = 3U, /**< CoreSight */
    kTRDC2_MasterEDMA2     = 4U, /**< EDMA2 */

    kTRDC3_MasterUSDHC1   = 0U, /**< uSDHC1 */
    kTRDC3_MasterUSDHC2   = 1U, /**< uSDHC2 */
    kTRDC3_MasterTestPort = 2U, /**< Test port */
    kTRDC3_MasterUSDHC3   = 3U, /**< USDHC3 */
    kTRDC3_MasterENET0    = 4U, /**< ENET0 */
    kTRDC3_MasterENET1    = 5U, /**< ENET1 */
    kTRDC3_MasterENETQos  = 6U, /**< ENET Qos */

    kTRDC3_MasterCA55Read  = 0U, /**< CA55 read channel */
    kTRDC3_MasterCA55Write = 1U, /**< CA55 write channel */
    kTRDC3_MasterNPUm0     = 2U, /**< NPU m0 */
    kTRDC3_MasterNPUm1     = 3U, /**< NPU m1 */

    kTRDC_MediaMix_MasterISI_M   = 0U, /**< ISI M */
    kTRDC_MediaMix_MasterISI_U_V = 1U, /**< ISI U&V */
    kTRDC_MediaMix_MasterPXP     = 2U, /**< PXP */
    kTRDC_MediaMix_MasterLCDIF   = 3U, /**< Lcdif */

    kTRDC_HSIOMix_MasterUSB1 = 0U, /**< USB1 */
    kTRDC_HSIOMix_MasterUSB2 = 1U, /**< USB2 */
} trdc_master_t;

/* @} */

/*!@brief TRDC base address convert macro */
#define TRDC_GENERAL_OFFSET           0UL
#define TRDC_FLW_OFFSET               0x1E0UL
#define TRDC_DOMAIN_ERROR_OFFSET      0x1FCUL
#define TRDC_DOMAIN_ASSIGNMENT_OFFSET 0x700UL
#define TRDC_MBC_OFFSET(x)            0x10000UL
#define TRDC_MBC_ARRAY_STEP           0x2000UL
#define TRDC_MRC_OFFSET(x)            0x14000UL
#define TRDC_MRC_ARRAY_STEP           0x1000UL

/*!@brief TRDC typedef */
typedef void TRDC_Type;
/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_TRDC_SOC_H_ */
