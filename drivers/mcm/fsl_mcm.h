/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_MCM_H_
#define FSL_MCM_H_

#include "fsl_common.h"

/*!
 * @addtogroup mcm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MCM_LMFATR_TYPE_MASK (0x1U)
#define MCM_LMFATR_MODE_MASK (0x2U)
#define MCM_LMFATR_BUFF_MASK (0x4U)
#define MCM_LMFATR_CACH_MASK (0x8U)
#define MCM_ISCR_STAT_MASK   (0xFFFFU)
#define MCM_ISCR_CPEE_MASK   (0x200000U)

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mcm"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief MCM driver version. */
#define FSL_MCM_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/*! @brief Enum _mcm_interrupt_flag. Interrupt status flag mask.
 *  @anchor _mcm_interrupt_flag
 */
enum
{
    kMCM_CacheWriteBuffer          = MCM_ISCR_CWBEE_MASK, /*!< Cache Write Buffer Error Enable. */
    kMCM_ParityError               = MCM_ISCR_CPEE_MASK,  /*!< Cache Parity Error Enable. */
    kMCM_FPUInvalidOperation       = MCM_ISCR_FIOCE_MASK, /*!< FPU Invalid Operation Interrupt Enable. */
    kMCM_FPUDivideByZero           = MCM_ISCR_FDZCE_MASK, /*!< FPU Divide-by-zero Interrupt Enable. */
    kMCM_FPUOverflow               = MCM_ISCR_FOFCE_MASK, /*!< FPU Overflow Interrupt Enable. */
    kMCM_FPUUnderflow              = MCM_ISCR_FUFCE_MASK, /*!< FPU Underflow Interrupt Enable. */
    kMCM_FPUInexact                = MCM_ISCR_FIXCE_MASK, /*!< FPU Inexact Interrupt Enable. */
    kMCM_FPUInputDenormalInterrupt = MCM_ISCR_FIDCE_MASK, /*!< FPU Input Denormal Interrupt Enable. */
};

/*!
 * @brief The union of buffer fault attribute.
 */

typedef union _mcm_buffer_fault_attribute
{
    uint32_t attribute; /*!< Indicates the faulting attributes, when a properly-enabled cache write buffer
                            error interrupt event is detected. */
    struct _mcm_buffer_fault_attribut
    {
        uint32_t busErrorDataAccessType : 1; /*!< Indicates the type of cache write buffer access. */
        uint32_t busErrorPrivilegeLevel : 1; /*!< Indicates the privilege level of the cache write buffer access. */
        uint32_t reserved3 : 2;
        uint32_t busErrorSize : 2; /*!< Indicates the size of the cache write buffer access. */
        uint32_t reserved2 : 1;
        uint32_t busErrorAccess : 1;   /*!< Indicates the type of system bus access. */
        uint32_t busErrorMasterID : 4; /*!< Indicates the crossbar switch bus master number of the captured cache write
                                          buffer bus error. */
        uint32_t reserved : 19;
        uint32_t busErrorOverrun : 1; /*!< Indicates if another cache write buffer bus error is detected. */
    } attribute_memory;
} mcm_buffer_fault_attribute_t;

/*!
 * @brief The union of LMEM fault attribute.
 */
typedef union _mcm_lmem_fault_attribute
{
    uint32_t attribute; /*!< Indicates the attributes of the LMEM fault detected. */
    struct _mcm_lmem_fault_attribut
    {
        uint32_t parityFaultProtectionSignal : 4; /*!< Indicates the features of parity fault protection signal. */
        uint32_t parityFaultMasterSize : 3;       /*!< Indicates the parity fault master size. */
        uint32_t parityFaultWrite : 1;            /*!< Indicates the parity fault is caused by read or write. */
        uint32_t reserved3 : 7;
        uint32_t
            backdoorAccess : 1; /*!< Indicates the LMEM access fault is initiated by core access or backdoor access. */
        uint32_t parityFaultSyndrome : 8; /*!< Indicates the parity fault syndrome. */
        uint32_t reserved2 : 6;
        uint32_t reserved : 1;
        uint32_t overrun : 1; /*!< Indicates the number of faultss. */
    } attribute_memory;
} mcm_lmem_fault_attribute_t;

/*****************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enables/Disables crossbar round robin.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable crossbar round robin.
 *          - \b true Enable crossbar round robin.
 *          - \b false disable crossbar round robin.
 */
static inline void MCM_EnableCrossbarRoundRobin(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->CPCR |= MCM_CPCR_CBRR_MASK;
    }
    else
    {
        base->CPCR &= ~MCM_CPCR_CBRR_MASK;
    }
}

/*!
 * @brief Enables the interrupt.
 *
 * @param base MCM peripheral base address.
 * @param mask Interrupt status flags mask(@ref _mcm_interrupt_flag).
 */
static inline void MCM_EnableInterruptStatus(MCM_Type *base, uint32_t mask)
{
    base->ISCR |= mask;
}

/*!
 * @brief Disables the interrupt.
 *
 * @param base MCM peripheral base address.
 * @param mask Interrupt status flags mask(@ref _mcm_interrupt_flag).
 */
static inline void MCM_DisableInterruptStatus(MCM_Type *base, uint32_t mask)
{
    base->ISCR &= ~mask;
}

/*!
 * @brief Gets the Interrupt status .
 *
 * @param base MCM peripheral base address.
 */
static inline uint16_t MCM_GetInterruptStatus(MCM_Type *base)
{
    return (uint16_t)(base->ISCR &= MCM_ISCR_STAT_MASK);
}

/*!
 * @brief Clears the Interrupt status .
 *
 * @param base MCM peripheral base address.
 */
static inline void MCM_ClearCacheWriteBufferErroStatus(MCM_Type *base)
{
    base->ISCR &= ~MCM_ISCR_CWBER_MASK;
}

/*!
 * @brief Gets buffer fault address.
 *
 * @param base MCM peripheral base address.
 */
static inline uint32_t MCM_GetBufferFaultAddress(MCM_Type *base)
{
    return base->FADR;
}

/*!
 * @brief Gets buffer fault attributes.
 *
 * @param base MCM peripheral base address.
 */
static inline void MCM_GetBufferFaultAttribute(MCM_Type *base, mcm_buffer_fault_attribute_t *bufferfault)
{
    assert(bufferfault != NULL);
    bufferfault->attribute = base->FATR;
}

/*!
 * @brief Gets buffer fault data.
 *
 * @param base MCM peripheral base address.
 */
static inline uint32_t MCM_GetBufferFaultData(MCM_Type *base)
{
    return base->FDR;
}

/*!
 * @brief Limit code cache peripheral write buffering.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable limit code cache peripheral write buffering.
 *          - \b true Enable limit code cache peripheral write buffering.
 *          - \b false disable limit code cache peripheral write buffering.
 */
static inline void MCM_LimitCodeCachePeripheralWriteBuffering(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->CPCR2 |= MCM_CPCR2_LCCPWB_MASK;
    }
    else
    {
        base->CPCR2 &= ~MCM_CPCR2_LCCPWB_MASK;
    }
}

/*!
 * @brief Bypass fixed code cache map.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable bypass fixed code cache map.
 *          - \b true Enable bypass fixed code cache map.
 *          - \b false disable bypass fixed code cache map.
 */
static inline void MCM_BypassFixedCodeCacheMap(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->CPCR2 |= MCM_CPCR2_PCCMCTRL_MASK;
    }
    else
    {
        base->CPCR2 &= ~MCM_CPCR2_PCCMCTRL_MASK;
    }
}

/*!
 * @brief Enables/Disables code bus cache.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to disable/enable code bus cache.
 *          - \b true Enable code bus cache.
 *          - \b false disable code bus cache.
 */
static inline void MCM_EnableCodeBusCache(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->CPCR2 &= ~MCM_CPCR2_DCBC_MASK;
    }
    else
    {
        base->CPCR2 |= MCM_CPCR2_DCBC_MASK;
    }
}

/*!
 * @brief Force code cache to no allocation.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to force code cache to allocation or no allocation.
 *          - \b true Force code cache to no allocation.
 *          - \b false Force code cache to allocation.
 */
static inline void MCM_ForceCodeCacheToNoAllocation(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->CPCR2 |= MCM_CPCR2_FCCNA_MASK;
    }
    else
    {
        base->CPCR2 &= ~MCM_CPCR2_FCCNA_MASK;
    }
}

/*!
 * @brief Enables/Disables code cache write buffer.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable code cache write buffer.
 *          - \b true Enable code cache write buffer.
 *          - \b false Disable code cache write buffer.
 */
static inline void MCM_EnableCodeCacheWriteBuffer(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->CPCR2 &= ~MCM_CPCR2_DCCWB_MASK;
    }
    else
    {
        base->CPCR2 |= MCM_CPCR2_DCCWB_MASK;
    }
}

/*!
 * @brief Clear code bus cache.
 *
 * @param base MCM peripheral base address.
 */
static inline void MCM_ClearCodeBusCache(MCM_Type *base)
{
    base->CPCR2 |= MCM_CPCR2_CCBC_MASK;
}

/*!
 * @brief Enables/Disables PC Parity Fault Report.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable PC Parity Fault Report.
 *          - \b true Enable PC Parity Fault Report.
 *          - \b false disable PC Parity Fault Report.
 */
static inline void MCM_EnablePcParityFaultReport(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->LMDR2 |= MCM_LMDR2_PCPFE_MASK;
    }
    else
    {
        base->LMDR2 &= ~MCM_LMDR2_PCPFE_MASK;
    }
}

/*!
 * @brief Enables/Disables PC Parity.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable PC Parity.
 *          - \b true Enable PC Parity.
 *          - \b false disable PC Parity.
 */
static inline void MCM_EnablePcParity(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->LMDR2 |= MCM_LMDR2_PCPME_MASK;
    }
    else
    {
        base->LMDR2 &= ~MCM_LMDR2_PCPME_MASK;
    }
}

/*!
 * @brief Lock the configuration state.
 *
 * @param base MCM peripheral base address.
 */
static inline void MCM_LockConfigState(MCM_Type *base)
{
    base->LMDR2 |= MCM_LMDR2_RO_MASK;
}

/*!
 * @brief Enables/Disables cache parity reporting.
 *
 * @param base MCM peripheral base address.
 * @param enable Used to enable/disable cache parity reporting.
 *          - \b true Enable cache parity reporting.
 *          - \b false disable cache parity reporting.
 */
static inline void MCM_EnableCacheParityReporting(MCM_Type *base, bool enable)
{
    if (enable)
    {
        base->LMPECR |= MCM_LMPECR_ECPR_MASK;
    }
    else
    {
        base->LMPECR &= ~MCM_LMPECR_ECPR_MASK;
    }
}

/*!
 * @brief Gets LMEM fault address.
 *
 * @param base MCM peripheral base address.
 */
static inline uint32_t MCM_GetLmemFaultAddress(MCM_Type *base)
{
    return base->LMFAR;
}

/*!
 * @brief Get LMEM fault attributes.
 *
 * @param base MCM peripheral base address.
 */
static inline void MCM_GetLmemFaultAttribute(MCM_Type *base, mcm_lmem_fault_attribute_t *lmemFault)
{
    assert(lmemFault != NULL);
    lmemFault->attribute = base->LMFATR;
}

/*!
 * @brief Gets LMEM fault data.
 *
 * @param base MCM peripheral base address.
 */
static inline uint64_t MCM_GetLmemFaultData(MCM_Type *base)
{
    return ((uint64_t)base->LMFDHR << 32) | base->LMFDLR;
}

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* FSL_MCM_H_ */
