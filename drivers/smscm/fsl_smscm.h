/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_SMSCM_H_
#define FSL_SMSCM_H_

#include "fsl_common.h"

/*!
 * @addtogroup smscm
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief SMSCM driver version 2.0.0. */
#define FSL_MSCM_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

/*!
 * @brief SMSCM debug enable type.
 */
enum _smscm_debug
{
    kSMSCM_InvasiveDebug          = SMSCM_DBGEN_DBGEN(2),
    kSMSCM_SecureInvasiveDebug    = SMSCM_DBGEN_SPIDEN(2),
    kSMSCM_NonInvasiveDebug       = SMSCM_DBGEN_NIDEN(2),
    kSMSCM_SecureNonInvasiveDebug = SMSCM_DBGEN_SPNIDEN(2),
    kSMSCM_AltInvasiveDebug       = SMSCM_DBGEN_ALTDBGEN(2),
    kSMSCM_AltDebug               = SMSCM_DBGEN_ALTEN(2),
};

/*!
 * @brief SMSCM On-Chip Memory Descriptor Register.
 */
typedef enum _smscm_mem
{
    kSMSCM_Mem0 = 0,
    kSMSCM_Mem2 = 2,
    kSMSCM_Mem3 = 3,
    kSMSCM_Mem5 = 5,
} smscm_mem_t;

/*!
 * @brief SMSCM ECC control type of On-Chip Memory.
 */
typedef enum _smscm_ecc_ctrl
{
    kSMSCM_EccDisable              = 0,
    kSMSCM_EccEnableOnWrite        = 1,
    kSMSCM_EccEnableOnRead         = 2,
    kSMSCM_EccEnableOnWriteAndRead = 3,
} smscm_ecc_ctrl_t;

/*!
 * @brief SMSCM attribute.
 */
typedef struct smscm_ecc_fault_attr
{
    uint8_t eccSyn;        /* ECC Fault Syndrome */
    uint8_t eccMasterNum;  /* ECC Fault Master Number */
    bool eccWrite;         /* ECC Fault Write */
    uint8_t eccMasterSize; /* ECC Fault Master Size */
    uint8_t eccProtect;    /* ECC Fault Protection */
} smscm_ecc_fault_attr_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enable the Debug function.
 * DebugToEnable could be bitwise OR of _smscm_debug_enable.
 *
 * @param base SMSCM peripheral address.
 * @param debugToEnable debug enable type.
 */
static inline void SMSCM_EnableDebug(SMSCM_Type *base, uint32_t debugToEnable)
{
    base->DBGEN   = debugToEnable;
    base->DBGEN_B = ~debugToEnable;
}

/*!
 * @brief Disables the Debug function.
 * DebugToDisable could be bitwise OR of _smscm_debug_disable.
 *
 * @param base SMSCM peripheral address.
 * @param debugToDisable debug disable type.
 */
static inline void SMSCM_DisableDebug(SMSCM_Type *base, uint32_t debugToDisable)
{
    base->DBGEN   = ~debugToDisable;
    base->DBGEN_B = debugToDisable;
}

/*!
 * @brief Lock the debug function.
 *
 * @param base SMSCM peripheral base address.
 */
static inline void SMSCM_DebugLock(SMSCM_Type *base)
{
    base->DBGEN_LOCK = SMSCM_DBGEN_LOCK_LOCK(0) | SMSCM_DBGEN_LOCK_ALT_DBGEN_LOCK(0) | SMSCM_DBGEN_LOCK_ALT_EN_LOCK(0);
}

/*!
 * @brief Get value in Security Counter Register (SCTR).
 *
 * @param base SMSCM peripheral base address.
 * @return SMSCM SCTR value.
 */
static inline uint32_t SMSCM_GetSecurityCount(SMSCM_Type *base)
{
    return base->SCTR;
}

/*!
 * @brief Set value in Security Counter Register (SCTR).
 *
 * @param base SMSCM peripheral base address.
 * @param val  SCTR value to set.
 */
static inline void SMSCM_SetSecurityCount(SMSCM_Type *base, uint32_t val)
{
    base->SCTR = val;
}

/*!
 * @brief Write value to be plused in Security Counter Register (SCTR).
 *
 * The entire contents of the write data word are added to the security counter,
 * and next-state SCTR =current-state SCTR + DATA32.
 * @param base SMSCM peripheral base address.
 * @param val  SCTR value to plus.
 */
static inline void SMSCM_IncreaseSecurityCount(SMSCM_Type *base, uint32_t val)
{
    base->SCTRPX = val;
}

/*!
 * @brief Write value to be minused in Security Counter Register (SCTR).
 *
 * The entire contents of the write data word are added to the security counter,
 * and next-state SCTR =current-state SCTR - DATA32.
 * @param base SMSCM peripheral base address.
 * @param val  SCTR value to be minused.
 */
static inline void SMSCM_DecreaseSecurityCount(SMSCM_Type *base, uint32_t val)
{
    base->SCTRMX = val;
}

/*!
 * @brief Increase security counter rigister by 1.
 *
 * @param base SMSCM peripheral base address.
 */
static inline void SMSCM_IncreaseSecurityCountBy1(SMSCM_Type *base)
{
    base->SCTRP1 = SMSCM_SCTRP1_DONTCARE32_MASK;
}

/*!
 * @brief Decrease security counter rigister by 1.
 *
 * @param base SMSCM peripheral base address.
 */
static inline void SMSCM_DecreaseSecurityCountBy1(SMSCM_Type *base)
{
    base->SCTRM1 = SMSCM_SCTRM1_DONTCARE32_MASK;
}

/*!
 * @brief Lock the on-chip memory descriptor.
 * This register bit provides a mechanism to “lock” the configuration state defined by OCMDRn[11:0].
 * Once asserted, attempted writes to the OCMDRn[11:0] register are ignored until the next reset
 * clears the flag.
 *
 * @param base SMSCM peripheral address.
 * @param mem  Select OCMDRn to enable read-only mode.
 */
static inline void SMSCM_LockMemControlReg(SMSCM_Type *base, smscm_mem_t mem)
{
    switch (mem)
    {
        case kSMSCM_Mem0:
            base->OCMDR0 |= SMSCM_OCMDR0_RO(1);
            break;
        case kSMSCM_Mem2:
            base->OCMDR2 |= SMSCM_OCMDR2_RO(1);
            break;
        case kSMSCM_Mem3:
            base->OCMDR3 |= SMSCM_OCMDR3_RO(1);
            break;
        case kSMSCM_Mem5:
            base->OCMDR5 |= SMSCM_OCMDR5_RO(1);
            break;

        default:
            /* Empty, for MISRA C-2012 Rule 16.4 */
            break;
    }
}

/*!
 * @brief Enable or disable the on-chip memory flash cache.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableFlashCache(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF2(8);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF2(8);
    }
}

/*!
 * @brief Enable flash instruction cache.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableFlashInstructionCache(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF2(4);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF2(4);
    }
}

/*!
 * @brief Enable flash data cache.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableFlashDataCache(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF2(2);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF2(2);
    }
}

/*!
 * @brief Clear the on-chip memory flash cache.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_ClearFlashCache(SMSCM_Type *base)
{
    base->OCMDR0 |= SMSCM_OCMDR0_OCMCF2(1);
}

/*!
 * @brief Lock IFR1 by flash controller.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_LockFlashIFR1(SMSCM_Type *base)
{
    base->OCMDR0 |= SMSCM_OCMDR0_OCMCF1(8);
}

/*!
 * @brief SMSCM Flash Speculate enable.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableFlashSpeculate(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF1(2);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF1(2);
    }
}

/*!
 * @brief SMSCM Data Prefetch enable.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableDataPrefetch(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF1(1);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF1(1);
    }
}

/*!
 * @brief Disable non-correctable bus errors on flash data fetches.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableFlashDataNonCorrectableBusError(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF0(8);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF0(8);
    }
}

/*!
 * @brief Disable non-correctable bus errors on flash instruction fetches.
 *
 * @param base SMSCM peripheral address.
 */
static inline void SMSCM_EnableFlashInstructionNonCorrectableBusError(SMSCM_Type *base, bool enable)
{
    if (enable)
    {
        base->OCMDR0 &= ~SMSCM_OCMDR0_OCMCF0(4);
    }
    else
    {
        base->OCMDR0 |= SMSCM_OCMDR0_OCMCF0(4);
    }
}

/*!
 * @brief Select ecc control type in OCMDRn.
 *
 * @param base SMSCM peripheral address.
 * @param mem  Select OCMDRn.
 * @param eccCtrl Select ecc control type.
 */
static inline void SMSCM_SetMemEccControl(SMSCM_Type *base, smscm_mem_t mem, smscm_ecc_ctrl_t eccCtrl)
{
    switch (mem)
    {
        case kSMSCM_Mem0:
        case kSMSCM_Mem2:
            base->OCMDR2 = SMSCM_OCMDR2_OCMCF0(eccCtrl);
            break;
        case kSMSCM_Mem3:
            base->OCMDR3 = SMSCM_OCMDR3_OCMCF0(eccCtrl);
            break;
        case kSMSCM_Mem5:
            base->OCMDR5 = SMSCM_OCMDR5_OCMCF0(eccCtrl);
            break;

        default:
            /* Empty, for MISRA C-2012 16.4. */
            break;
    }
}

/*!
 * @brief Enable RAM ECC 1 bit and non-correctable reporting.
 *
 * @param base SMSCM peripheral base address.
 */
static inline void SMSCM_EnableEccReport(SMSCM_Type *base)
{
    base->OCMECR = SMSCM_OCMECR_ENCR_MASK | SMSCM_OCMECR_E1BR_MASK;
}

/*!
 * @brief Get the ECC location valid states.
 *
 * @param base SMSCM peripheral base address.
 * @return State of ECC Error Location field.
 */
static inline bool SMSCM_GetEccValid(SMSCM_Type *base)
{
    return (0U != (base->OCMEIR & SMSCM_OCMEIR_VALID_MASK));
}

/*!
 * @brief Get the ECC location.
 *
 * @param base SMSCM peripheral base address.
 * @return ECC fault location.
 */
static inline uint8_t SMSCM_GetEccLocation(SMSCM_Type *base)
{
    return (uint8_t)((base->OCMEIR & SMSCM_OCMEIR_EELOC_MASK) >> SMSCM_OCMEIR_EELOC_SHIFT);
}

/*!
 * @brief Clear each 1-bit correctable or non-correctable error.
 * @param base SMSCM peripheral address.
 * @param errLocation ECC Error Location
 */
void SMSCM_ClearEccError(SMSCM_Type *base, uint8_t errLocation);

/*!
 * @brief Get the ECC fault address.
 *
 * @param base SMSCM peripheral base address.
 * @return ECC fault address.
 */
static inline uint32_t SMSCM_GetEccAddress(SMSCM_Type *base)
{
    return base->OCMFAR & SMSCM_OCMFAR_EFADD_MASK;
}

/*!
 * @brief Get ECC attribute.
 * @param base SMSCM peripheral address.
 * @param eccAttribute Ecc attribute.
 */
void SMSCM_GetEccAttribute(SMSCM_Type *base, smscm_ecc_fault_attr_t *eccAttribute);

/*!
 * @brief Get ECC Fault Data High
 *
 * This read-only field specifies the upper 32-bit read data word (data[63:32]) from the last
 * captured ECCevent. For ECC events that occur in 32-bit RAMs, this 32-bit field will return 32'h0.
 * @param base SMSCM peripheral base address.
 * @return The higher 32-bit read data word.
 */
static inline uint32_t SMSCM_GetEccFaultDataHigh(SMSCM_Type *base)
{
    return base->OCMFDRH;
}

/*!
 * @brief Get ECC Fault Data Low
 *
 * @param base SMSCM peripheral base address.
 * @return The lower 32-bit read data word.
 */
static inline uint32_t SMSCM_GetEccFaultDataLow(SMSCM_Type *base)
{
    return base->OCMFDRL;
}

/*! @} */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* FSL_SMSCM_H_ */
