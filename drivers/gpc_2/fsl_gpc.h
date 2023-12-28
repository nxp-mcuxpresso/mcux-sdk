/*
 * Copyright 2017-2020, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_GPC_H_
#define FSL_GPC_H_

#include "fsl_common.h"

/*!
 * @addtogroup gpc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief GPC driver version 2.2.0. */
#define FSL_GPC_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @} */

/* Re-map the register and bitfields name for different ARM cortex M cores. */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
#define GPC_PGC_CPU_0_1_MAPPING_MF_DOMAIN_MASK GPC_PGC_CPU_0_1_MAPPING_MF_M4_DOMAIN_MASK

#define GPC_IMR           IMR_M4
#define GPC_IMR_COUNT     GPC_IMR_M4_COUNT
#define GPC_IMR_IMR1_MASK GPC_IMR_M4_IMR1_M4_MASK
#define GPC_IMR_IMR2_MASK GPC_IMR_M4_IMR2_M4_MASK
#define GPC_IMR_IMR3_MASK GPC_IMR_M4_IMR3_M4_MASK
#define GPC_IMR_IMR4_MASK GPC_IMR_M4_IMR4_M4_MASK

#define GPC_ISR ISR_M4

#define GPC_LPCR                       LPCR_M4
#define GPC_LPCR_CPU_CLK_ON_LPM_MASK   GPC_LPCR_M4_CPU_CLK_ON_LPM_MASK
#define GPC_LPCR_EN_PDN_MASK           GPC_LPCR_M4_EN_M4_PDN_MASK
#define GPC_LPCR_EN_PUP_MASK           GPC_LPCR_M4_EN_M4_PUP_MASK
#define GPC_LPCR_LPM0_MASK             GPC_LPCR_M4_LPM0_MASK
#define GPC_LPCR_MASK_DSM_TRIGGER_MASK GPC_LPCR_M4_MASK_DSM_TRIGGER_MASK
#define GPC_LPCR_MASK_WFI_MASK         GPC_LPCR_M4_MASK_M4_WFI_MASK

#define GPC_MISC_PDN_REQ_MASK_MASK GPC_MISC_M4_PDN_REQ_MASK_MASK

#define GPC_PGC_ACK_SEL                          PGC_ACK_SEL_M4
#define GPC_PGC_ACK_SEL_DUMMY_PGC_PUP_ACK_MASK   GPC_PGC_ACK_SEL_M4_M4_DUMMY_PGC_PUP_ACK_MASK
#define GPC_PGC_ACK_SEL_VIRTUAL_PGC_PUP_ACK_MASK GPC_PGC_ACK_SEL_M4_M4_VIRTUAL_PGC_PUP_ACK_MASK
#define GPC_PGC_ACK_SEL_DUMMY_PGC_PDN_ACK_MASK   GPC_PGC_ACK_SEL_M4_M4_DUMMY_PGC_PDN_ACK_MASK
#define GPC_PGC_ACK_SEL_VIRTUAL_PGC_PDN_ACK_MASK GPC_PGC_ACK_SEL_M4_M4_VIRTUAL_PGC_PDN_ACK_MASK
#define GPC_PGC_ACK_SEL_NOC_PGC_PUP_ACK          GPC_PGC_ACK_SEL_M4_NOC_PGC_PUP_ACK_MASK
#define GPC_PGC_ACK_SEL_NOC_PGC_PDN_ACK          GPC_PGC_ACK_SEL_M4_NOC_PGC_PDN_ACK_MASK

#define GPC_SLPCR_EN_FASTWUP_WAIT_MODE_MASK GPC_SLPCR_EN_M4_FASTWUP_WAIT_MODE_MASK
#define GPC_SLPCR_EN_FASTWUP_STOP_MODE_MASK GPC_SLPCR_EN_M4_FASTWUP_STOP_MODE_MASK

#define GPC_SLT_CFG_PU_PDN_SLOT_CONTROL_MASK GPC_SLT_CFG_PU_M4_PDN_SLOT_CONTROL_MASK
#define GPC_SLT_CFG_PU_PUP_SLOT_CONTROL_MASK GPC_SLT_CFG_PU_M4_PUP_SLOT_CONTROL_MASK
#elif defined __CORTEX_M && (__CORTEX_M == 7U)
#define GPC_IMR           IMR_M7
#define GPC_IMR_COUNT     GPC_IMR_M7_COUNT
#define GPC_IMR_IMR1_MASK GPC_IMR_M7_IMR1_M7_MASK
#define GPC_IMR_IMR2_MASK GPC_IMR_M7_IMR2_M7_MASK
#define GPC_IMR_IMR3_MASK GPC_IMR_M7_IMR3_M7_MASK
#define GPC_IMR_IMR4_MASK GPC_IMR_M7_IMR4_M7_MASK
#if (defined(GPC_IMR_M7_COUNT) && (GPC_IMR_M7_COUNT == 5U))
#define GPC_IMR_IMR5_MASK GPC_IMR_M7_IMR5_M7_MASK
#endif

#define GPC_ISR ISR_M7

#define GPC_LPCR                       LPCR_M7
#define GPC_LPCR_CPU_CLK_ON_LPM_MASK   GPC_LPCR_M7_CPU_CLK_ON_LPM_MASK
#define GPC_LPCR_EN_PDN_MASK           GPC_LPCR_M7_EN_M7_PDN_MASK
#define GPC_LPCR_EN_PUP_MASK           GPC_LPCR_M7_EN_M7_PUP_MASK
#define GPC_LPCR_LPM0_MASK             GPC_LPCR_M7_LPM0_MASK
#define GPC_LPCR_MASK_DSM_TRIGGER_MASK GPC_LPCR_M7_MASK_DSM_TRIGGER_MASK
#define GPC_LPCR_MASK_WFI_MASK         GPC_LPCR_M7_MASK_M7_WFI_MASK

#define GPC_MISC_PDN_REQ_MASK_MASK GPC_MISC_M7_PDN_REQ_MASK_MASK

#define GPC_PGC_ACK_SEL                          PGC_ACK_SEL_M7
#define GPC_PGC_ACK_SEL_DUMMY_PGC_PUP_ACK_MASK   GPC_PGC_ACK_SEL_M7_M7_DUMMY_PGC_PUP_ACK_MASK
#define GPC_PGC_ACK_SEL_VIRTUAL_PGC_PUP_ACK_MASK GPC_PGC_ACK_SEL_M7_M7_VIRTUAL_PGC_PUP_ACK_MASK
#define GPC_PGC_ACK_SEL_DUMMY_PGC_PDN_ACK_MASK   GPC_PGC_ACK_SEL_M7_M7_DUMMY_PGC_PDN_ACK_MASK
#define GPC_PGC_ACK_SEL_VIRTUAL_PGC_PDN_ACK_MASK GPC_PGC_ACK_SEL_M7_M7_VIRTUAL_PGC_PDN_ACK_MASK
#define GPC_PGC_ACK_SEL_NOC_PGC_PUP_ACK          GPC_PGC_ACK_SEL_M7_NOC_PGC_PUP_ACK_MASK
#define GPC_PGC_ACK_SEL_NOC_PGC_PDN_ACK          GPC_PGC_ACK_SEL_M7_NOC_PGC_PDN_ACK_MASK

#define GPC_SLPCR_EN_FASTWUP_WAIT_MODE_MASK GPC_SLPCR_EN_M7_FASTWUP_WAIT_MODE_MASK
#define GPC_SLPCR_EN_FASTWUP_STOP_MODE_MASK GPC_SLPCR_EN_M7_FASTWUP_STOP_MODE_MASK

#if !(defined(GPC_SLT_CFG_PU1_COUNT) && GPC_SLT_CFG_PU1_COUNT)
#define GPC_SLT_CFG_PU_PDN_SLOT_CONTROL_MASK GPC_SLT_CFG_PU_M7_PDN_SLOT_CONTROL_MASK
#define GPC_SLT_CFG_PU_PUP_SLOT_CONTROL_MASK GPC_SLT_CFG_PU_M7_PUP_SLOT_CONTROL_MASK
#else
#define GPC_SLT_CFG_PU_PDN_SLOT_CONTROL_MASK GPC_SLT_CFG_PU1_M7_PDN_SLOT_CONTROL_MASK
#define GPC_SLT_CFG_PU_PUP_SLOT_CONTROL_MASK GPC_SLT_CFG_PU1_M7_PUP_SLOT_CONTROL_MASK
#endif /* GPC_SLT_CFG_PU1_COUNT */
#endif

/*! @brief Total number of the timeslot */
#define GPC_PCG_TIME_SLOT_TOTAL_NUMBER GPC_SLT_CFG_PU_COUNT

/*! @brief GPC LPM mode definition */
enum _gpc_lpm_mode
{
    kGPC_RunMode  = 0U, /*!< run mode */
    kGPC_WaitMode = 1U, /*!< wait mode */
    kGPC_StopMode = 2U, /*!< stop mode */
};

/*! @brief PGC ack signal selection  */
enum _gpc_pgc_ack_sel
{
    kGPC_DummyPGCPowerUpAck     = GPC_PGC_ACK_SEL_DUMMY_PGC_PUP_ACK_MASK,   /*!< dummy power up ack signal */
    kGPC_VirtualPGCPowerUpAck   = GPC_PGC_ACK_SEL_VIRTUAL_PGC_PUP_ACK_MASK, /*!< virtual pgc power up ack signal */
    kGPC_DummyPGCPowerDownAck   = GPC_PGC_ACK_SEL_DUMMY_PGC_PDN_ACK_MASK,   /*!< dummy power down ack signal */
    kGPC_VirtualPGCPowerDownAck = GPC_PGC_ACK_SEL_VIRTUAL_PGC_PDN_ACK_MASK, /*!< virtual pgc power down ack signal */
    kGPC_NocPGCPowerUpAck       = GPC_PGC_ACK_SEL_NOC_PGC_PUP_ACK,          /*!< NOC power up ack signal */
    kGPC_NocPGCPowerDownAck     = GPC_PGC_ACK_SEL_NOC_PGC_PDN_ACK,          /*!< NOC power  */
};

/*! @brief Standby counter which GPC will wait between PMIC_STBY_REQ negation and assertion of PMIC_READY  */
enum _gpc_standby_count
{
    kGPC_StandbyCounter4CkilClk   = 0U, /*!< 4 ckil clocks */
    kGPC_StandbyCounter8CkilClk   = 1U, /*!< 8 ckil clocks */
    kGPC_StandbyCounter16CkilClk  = 2U, /*!< 16 ckil clocks */
    kGPC_StandbyCounter32CkilClk  = 3U, /*!< 32 ckil clocks */
    kGPC_StandbyCounter64CkilClk  = 4U, /*!< 64 ckil clocks */
    kGPC_StandbyCounter128CkilClk = 5U, /*!< 128 ckil clocks */
    kGPC_StandbyCounter256CkilClk = 6U, /*!< 256 ckil clocks */
    kGPC_StandbyCounter512CkilClk = 7U, /*!< 512 ckil clocks */
};

/*!< configuration for enter LPM mode */
typedef struct _gpc_lpm_config
{
    bool enFastWakeUp;          /*!< enable fast wake up from lpm mode */
    bool enCpuClk;              /*!< enable CPU clock when LPM enter */
    bool enVirtualPGCPowerup;   /*!< enable virtual PGC power up with LPM enter */
    bool enVirtualPGCPowerdown; /*!< enable virtual PGC power down with LPM enter */
    bool enWfiMask;             /*!< enable WFI Mask */
    bool enDsmMask;             /*!< enable DSM Mask */
} gpc_lpm_config_t;

/*!< configuration for enter DSM mode */
typedef struct _gpc_dsm_config
{
    bool disableRamLpctl; /*!< Memory can be defined to go to retention mode or not */

    bool enPMICStandBy;         /*!< PMIC can be defined to be stand-by mode or not */
    uint8_t pmicStandByCounter; /*!< PMIC standby counter, reference _gpc_standby_count */
    uint8_t regBypassCounter; /*!< if PMIC standby is request, regulator bypass should be enable, and the counter can be
                                 defined */

} gpc_dsm_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Allow all the IRQ/Events within the charge of GPC.
 *
 * @param base GPC peripheral base address.
 */
static inline void GPC_AllowIRQs(GPC_Type *base)
{
    base->MISC &= ~GPC_MISC_GPC_IRQ_MASK_MASK; /* Events would not be masked. */
}

/*!
 * @brief Disallow all the IRQ/Events within the charge of GPC.
 *
 * @param base GPC peripheral base address.
 */
static inline void GPC_DisallowIRQs(GPC_Type *base)
{
    base->MISC |= GPC_MISC_GPC_IRQ_MASK_MASK; /* Mask all the events. */
}

/*!
 * @brief Get current LPM mode.
 *
 * @param base GPC peripheral base address.
 * @retval lpm mode, reference _gpc_lpm_mode
 */
static inline uint32_t GPC_GetLpmMode(GPC_Type *base)
{
    return base->GPC_LPCR & GPC_LPCR_LPM0_MASK;
}

/*!
 * @brief Enable the IRQ.
 *
 * @param base GPC peripheral base address.
 * @param irqId ID number of IRQ to be enabled, available range is 0-127,reference SOC headerfile IRQn_Type.
 */
void GPC_EnableIRQ(GPC_Type *base, uint32_t irqId);

/*!
 * @brief Disable the IRQ.
 *
 * @param base GPC peripheral base address.
 * @param irqId ID number of IRQ to be disabled, available range is 0-127,reference SOC headerfile IRQn_Type.
 */
void GPC_DisableIRQ(GPC_Type *base, uint32_t irqId);

/*!
 * @brief Get the IRQ/Event flag.
 *
 * @param base GPC peripheral base address.
 * @param irqId ID number of IRQ to be enabled, available range is 0-127,reference SOC headerfile IRQn_Type.
 * @return Indicated IRQ/Event is asserted or not.
 */
bool GPC_GetIRQStatusFlag(GPC_Type *base, uint32_t irqId);

/*!
 * @brief Mask the DSM trigger.
 *
 * @param base GPC peripheral base address.
 * @param enable true to enable mask, false to disable mask.
 */
static inline void GPC_DsmTriggerMask(GPC_Type *base, bool enable)
{
    if (enable)
    {
        base->GPC_LPCR |= GPC_LPCR_MASK_DSM_TRIGGER_MASK;
    }
    else
    {
        base->GPC_LPCR &= ~GPC_LPCR_MASK_DSM_TRIGGER_MASK;
    }
}

/*!
 * @brief Mask the WFI.
 *
 * @param base GPC peripheral base address.
 * @param enable true to enable mask, false to disable mask.
 */
static inline void GPC_WFIMask(GPC_Type *base, bool enable)
{
    if (enable)
    {
        base->GPC_LPCR |= GPC_LPCR_MASK_WFI_MASK;
    }
    else
    {
        base->GPC_LPCR &= ~GPC_LPCR_MASK_WFI_MASK;
    }
}

/*!
 * @brief Select the PGC ACK signal.
 *
 * @param base GPC peripheral base address.
 * @param mask reference _gpc_pgc_ack_sel.
 */
static inline void GPC_SelectPGCAckSignal(GPC_Type *base, uint32_t mask)
{
    base->GPC_PGC_ACK_SEL |= mask;
}

/*!
 * @brief Power down request to virtual PGC mask or not.
 *
 * @param base GPC peripheral base address.
 * @param enable true to mask, false to not mask.
 */
static inline void GPC_PowerDownRequestMask(GPC_Type *base, bool enable)
{
    if (enable)
    {
        base->MISC &= ~GPC_MISC_PDN_REQ_MASK_MASK;
    }
    else
    {
        base->MISC |= GPC_MISC_PDN_REQ_MASK_MASK;
    }
}

/*!
 * @brief PGC CPU Mapping.
 *
 * @param base GPC peripheral base address.
 * @param mask mask value reference PGC CPU mapping definition.
 */
static inline void GPC_PGCMapping(GPC_Type *base, uint32_t mask)
{
#if !(defined(GPC_PGC_CPU_M7_MAPPING_MIX0_SUPERMIXM7_DOMAIN_MASK) && GPC_PGC_CPU_M7_MAPPING_MIX0_SUPERMIXM7_DOMAIN_MASK)
    base->PGC_CPU_0_1_MAPPING |= mask & 0xFFFD0000U;
#else
    base->PGC_CPU_M7_MAPPING |= mask & 0x3FFFFFUL;
#endif /* GPC_PGC_CPU_M7_MAPPING_MIX0_SUPERMIXM7_DOMAIN_MASK */
}

/*!
 * @brief Time slot configure.
 *
 * @param base GPC peripheral base address.
 * @param slotIndex time slot index.
 * @param value value to be configured
 */
static inline void GPC_TimeSlotConfigureForPUS(GPC_Type *base, uint8_t slotIndex, uint32_t value)
{
    assert(slotIndex < GPC_PCG_TIME_SLOT_TOTAL_NUMBER);

#if !(defined(GPC_SLT_CFG_PU1_COUNT) && GPC_SLT_CFG_PU1_COUNT)
    base->SLT_CFG_PU[slotIndex] |= value;
#else
    base->SLTn_CFG_PU[slotIndex].SLT_CFG_PU = value;
#endif /* GPC_SLT_CFG_PU1_COUNT */
}

#if defined(GPC_SLT_CFG_PU1_COUNT) && GPC_SLT_CFG_PU1_COUNT
/*!
 * @brief Time slot configure of extended PUs
 *
 * @param base GPC peripheral base address.
 * @param slotIndex Time slot index.
 * @param value The value of extended PUs, please refer to the reference manual for details.
 */
static inline void GPC_TimeSlotConfigureForExtendedPUS(GPC_Type *base, uint8_t slotIndex, uint32_t value)
{
    assert(slotIndex < GPC_PCG_TIME_SLOT_TOTAL_NUMBER);

    base->SLTn_CFG_PU[slotIndex].SLT_CFG_PU1 = value;
}
#endif /* GPC_SLT_CFG_PU1_COUNT */

/*!
 * @brief Enter WAIT mode.
 *
 * @param base GPC peripheral base address.
 * @param config lpm mode configurations.
 */
void GPC_EnterWaitMode(GPC_Type *base, gpc_lpm_config_t *config);

/*!
 * @brief Enter STOP mode.
 *
 * @param base GPC peripheral base address.
 * @param config lpm mode configurations.
 */
void GPC_EnterStopMode(GPC_Type *base, gpc_lpm_config_t *config);

/*!
 * @brief GPC init function.
 *
 * @param base GPC peripheral base address.
 * @param powerUpSlot power up slot number.
 * @param powerDownSlot power down slot number.
 */
void GPC_Init(GPC_Type *base, uint32_t powerUpSlot, uint32_t powerDownSlot);

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* FSL_GPC_H_ */
