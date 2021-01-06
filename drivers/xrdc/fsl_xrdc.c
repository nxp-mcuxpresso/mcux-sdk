/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xrdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xrdc"
#endif

#define XRDC_DERR_W1_EST_VAL(w1)   (uint8_t)(((w1)&XRDC_DERR_W_EST_MASK) >> XRDC_DERR_W_EST_SHIFT)
#define XRDC_DERR_W1_EPORT_VAL(w1) (uint8_t)(((w1)&XRDC_DERR_W_EPORT_MASK) >> XRDC_DERR_W_EPORT_SHIFT)
#define XRDC_DERR_W1_ERW_VAL(w1)   (uint8_t)(((w1)&XRDC_DERR_W_ERW_MASK) >> XRDC_DERR_W_ERW_SHIFT)
#define XRDC_DERR_W1_EATR_VAL(w1)  (uint8_t)(((w1)&XRDC_DERR_W_EATR_MASK) >> XRDC_DERR_W_EATR_SHIFT)
#define XRDC_DERR_W1_EDID_VAL(w1)  (uint8_t)(((w1)&XRDC_DERR_W_EDID_MASK) >> XRDC_DERR_W_EDID_SHIFT)

#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_DXACP) && FSL_FEATURE_XRDC_NO_MRGD_DXACP)
#define XRDC_MRGD_DXACP_WIDTH (3U) /* The width of XRDC_MRDG_DxACP. */
#elif (defined(FSL_FEATURE_XRDC_HAS_MRGD_DXSEL) && FSL_FEATURE_XRDC_HAS_MRGD_DXSEL)
#define XRDC_MRGD_DXSEL_WIDTH (3U) /* The width of XRDC_MRDG_DxSEL. */
#endif
#define XRDC_PDAC_DXACP_WIDTH (3U) /* The width of XRDC_PDAC_DxACP. */

/* For the force exclusive accesss lock release procedure. */
#define XRDC_FORCE_EXCL_ACS_LOCK_REL_VAL1 (0x02000046U) /* The width of XRDC_MRDG_DxACP. */
#define XRDC_FORCE_EXCL_ACS_LOCK_REL_VAL2 (0x02000052U) /* The width of XRDC_PDAC_DxACP. */

typedef union
{
    xrdc_pid_config_t _pid;
    uint32_t _u32;
} xrdc_pid_reg_t;

typedef union
{
    xrdc_processor_domain_assignment_t _mdaProc;
    xrdc_non_processor_domain_assignment_t _mdaNonProc;
    uint32_t _u32;
} xrdc_mda_reg_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name of XRDC. */
#if (FSL_CLOCK_XRDC_GATE_COUNT > 1)
static const clock_ip_name_t s_xrdcClock[] = XRDC_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

#if ((__CORTEX_M == 0U) && (defined(__ICCARM__)))
/*!
 * @brief Count the leading zeros.
 *
 * Count the leading zeros of an 32-bit data. This function is only defined
 * for CM0 and CM0+ for IAR, because other cortex series have the clz instruction,
 * KEIL and ARMGCC have toolchain build in function for this purpose.
 *
 * @param data The data to process.
 * @return Count of the leading zeros.
 */
static uint8_t XRDC_CountLeadingZeros(uint32_t data)
{
    uint8_t count = 0U;
    uint32_t mask = 0x80000000U;

    while ((data & mask) == 0U)
    {
        count++;
        mask >>= 1U;
    }

    return count;
}
#endif

/*!
 * brief Initializes the XRDC module.
 *
 * This function enables the XRDC clock.
 *
 * param base XRDC peripheral base address.
 */
void XRDC_Init(XRDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

#if (FSL_CLOCK_XRDC_GATE_COUNT > 0)
#if (FSL_CLOCK_XRDC_GATE_COUNT == 1)
    CLOCK_EnableClock(kCLOCK_Xrdc0);
#else
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_xrdcClock); i++)
    {
        CLOCK_EnableClock(s_xrdcClock[i]);
    }
#endif
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief De-initializes the XRDC module.
 *
 * This function disables the XRDC clock.
 *
 * param base XRDC peripheral base address.
 */
void XRDC_Deinit(XRDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

#if (FSL_CLOCK_XRDC_GATE_COUNT > 0)
#if (FSL_CLOCK_XRDC_GATE_COUNT == 1)
    CLOCK_EnableClock(kCLOCK_Xrdc0);
#else
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_xrdcClock); i++)
    {
        CLOCK_DisableClock(s_xrdcClock[i]);
    }
#endif
#endif

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the XRDC hardware configuration.
 *
 * This function gets the XRDC hardware configurations, including number of bus
 * masters, number of domains, number of MRCs and number of PACs.
 *
 * param base XRDC peripheral base address.
 * param config Pointer to the structure to get the configuration.
 */
void XRDC_GetHardwareConfig(XRDC_Type *base, xrdc_hardware_config_t *config)
{
    assert(NULL != config);

    config->masterNumber = (uint8_t)((base->HWCFG0 & XRDC_HWCFG0_NMSTR_MASK) >> XRDC_HWCFG0_NMSTR_SHIFT) + 1U;
    config->domainNumber = (uint8_t)((base->HWCFG0 & XRDC_HWCFG0_NDID_MASK) >> XRDC_HWCFG0_NDID_SHIFT) + 1U;
    config->pacNumber    = (uint8_t)((base->HWCFG0 & XRDC_HWCFG0_NPAC_MASK) >> XRDC_HWCFG0_NPAC_SHIFT) + 1U;
    config->mrcNumber    = (uint8_t)((base->HWCFG0 & XRDC_HWCFG0_NMRC_MASK) >> XRDC_HWCFG0_NMRC_SHIFT) + 1U;
}

/*!
 * brief Gets and clears the first domain error of the current domain.
 *
 * This function gets the first access violation information for the current domain
 * and clears the pending flag. There might be multiple access violations pending
 * for the current domain. This function only processes the first error.
 *
 * param base XRDC peripheral base address.
 * param error Pointer to the error information.
 * return If the access violation is captured, this function returns the kStatus_Success.
 *         The error information can be obtained from the parameter error. If no
 *         access violation is captured, this function returns the kStatus_XRDC_NoError.
 */
status_t XRDC_GetAndClearFirstDomainError(XRDC_Type *base, xrdc_error_t *error)
{
    return XRDC_GetAndClearFirstSpecificDomainError(base, error, XRDC_GetCurrentMasterDomainId(base));
}

/*!
 * brief Gets and clears the first domain error of the specific domain.
 *
 * This function gets the first access violation information for the specific domain
 * and clears the pending flag. There might be multiple access violations pending
 * for the current domain. This function only processes the first error.
 *
 * param base XRDC peripheral base address.
 * param error Pointer to the error information.
 * param domainId The error of which domain to get and clear.
 * return If the access violation is captured, this function returns the kStatus_Success.
 *         The error information can be obtained from the parameter error. If no
 *         access violation is captured, this function returns the kStatus_XRDC_NoError.
 */
status_t XRDC_GetAndClearFirstSpecificDomainError(XRDC_Type *base, xrdc_error_t *error, uint8_t domainId)
{
    assert(NULL != error);

    status_t status;
    uint8_t errorIndex;   /* The index of first domain error. */
    uint32_t errorBitMap; /* Domain error location bit map.   */
    uint32_t regW1;       /* To save XRDC_DERR_W1.            */

    /* Get the error bitmap. */
    errorBitMap = base->DERRLOC[domainId];

    if (0U == errorBitMap) /* No error captured. */
    {
        status = kStatus_XRDC_NoError;
    }
    else
    {
        /* Get the first error controller index. */
#if ((__CORTEX_M == 0U) && (defined(__ICCARM__)))
        errorIndex = 31U - XRDC_CountLeadingZeros(errorBitMap);
#else
        errorIndex        = 31U - __CLZ(errorBitMap);
#endif

#if (defined(FSL_FEATURE_XRDC_HAS_FDID) && FSL_FEATURE_XRDC_HAS_FDID)
        /* Must write FDID[FDID] with the domain ID before reading the Domain Error registers. */
        base->FDID = XRDC_FDID_FDID(domainId);
#endif /* FSL_FEATURE_XRDC_HAS_FDID */
        /* Get the error information. */
        regW1             = base->DERR_W[errorIndex][1];
        error->controller = (xrdc_controller_t)errorIndex;
        error->address    = base->DERR_W[errorIndex][0];
        error->errorState = (xrdc_error_state_t)XRDC_DERR_W1_EST_VAL(regW1);
        error->errorAttr  = (xrdc_error_attr_t)XRDC_DERR_W1_EATR_VAL(regW1);
        error->errorType  = (xrdc_error_type_t)XRDC_DERR_W1_ERW_VAL(regW1);
        error->errorPort  = XRDC_DERR_W1_EPORT_VAL(regW1);
        error->domainId   = XRDC_DERR_W1_EDID_VAL(regW1);

        /* Clear error pending. */
        base->DERR_W[errorIndex][3] = XRDC_DERR_W_RECR(0x01U);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Gets the default PID configuration structure.
 *
 * This function initializes the configuration structure to default values. The default
 * values are:
 *
 * code
 * config->pid       = 0U;
 * config->tsmEnable = 0U;
 * config->sp4smEnable = 0U;
 * config->lockMode  = kXRDC_PidLockSecurePrivilegeWritable;
 * endcode
 *
 * param config Pointer to the configuration structure.
 */
void XRDC_GetPidDefaultConfig(xrdc_pid_config_t *config)
{
    assert(NULL != config);

    xrdc_pid_reg_t pid;
    pid._u32 = 0U;

    *config = pid._pid;
}

/*!
 * brief Configures the PID for a specific bus master.
 *
 * This function configures the PID for a specific bus master. Do not use this
 * function for non-processor bus masters.
 *
 * param base XRDC peripheral base address.
 * param master Which bus master to configure.
 * param config Pointer to the configuration structure.
 */
void XRDC_SetPidConfig(XRDC_Type *base, xrdc_master_t master, const xrdc_pid_config_t *config)
{
    assert(NULL != config);

    xrdc_pid_reg_t pid;
    pid._pid = *config;

    base->PID[master] = pid._u32;
}

/*!
 * brief Gets the default master domain assignment for non-processor bus master.
 *
 * This function gets the default master domain assignment for non-processor bus master.
 * It should only be used for the non-processor bus masters, such as DMA. This function
 * sets the assignment as follows:
 *
 * code
 * assignment->domainId            = 0U;
 * assignment->privilegeAttr       = kXRDC_ForceUser;
 * assignment->privilegeAttr       = kXRDC_ForceSecure;
 * assignment->bypassDomainId      = 0U;
 * assignment->blogicPartId        = 0U;
 * assignment->benableLogicPartId  = 0U;
 * assignment->lock                = 0U;
 * endcode
 *
 * param domainAssignment Pointer to the assignment structure.
 */
void XRDC_GetDefaultNonProcessorDomainAssignment(xrdc_non_processor_domain_assignment_t *domainAssignment)
{
    assert(NULL != domainAssignment);

    xrdc_mda_reg_t mda;

    mda._u32 = 0U;

    *domainAssignment = mda._mdaNonProc;
}

/*!
 * brief Gets the default master domain assignment for the processor bus master.
 *
 * This function gets the default master domain assignment for the processor bus master.
 * It should only be used for the processor bus masters, such as CORE0. This function
 * sets the assignment as follows:
 *
 * code
 * assignment->domainId           = 0U;
 * assignment->domainIdSelect     = kXRDC_DidMda;
 * assignment->dpidEnable         = kXRDC_PidDisable;
 * assignment->pidMask            = 0U;
 * assignment->pid                = 0U;
 * assignment->logicPartId        = 0U;
 * assignment->enableLogicPartId  = 0U;
 * assignment->lock               = 0U;
 * endcode
 *
 * param domainAssignment Pointer to the assignment structure.
 */
void XRDC_GetDefaultProcessorDomainAssignment(xrdc_processor_domain_assignment_t *domainAssignment)
{
    assert(NULL != domainAssignment);

    xrdc_mda_reg_t mda;

    mda._u32 = 0U;

    *domainAssignment = mda._mdaProc;
}

/*!
 * brief Sets the non-processor bus master domain assignment.
 *
 * This function sets the non-processor master domain assignment as valid.
 * One bus master might have multiple domain assignment registers. The parameter
 * \p assignIndex specifies which assignment register to set.
 *
 * Example: Set domain assignment for DMA0.
 * code
 * xrdc_non_processor_domain_assignment_t nonProcessorAssignment;
 *
 * XRDC_GetDefaultNonProcessorDomainAssignment(&nonProcessorAssignment);
 * nonProcessorAssignment.domainId = 1;
 * nonProcessorAssignment.xxx      = xxx;
 *
 * XRDC_SetMasterDomainAssignment(XRDC, kXrdcMasterDma0, 0U, &nonProcessorAssignment);
 * endcode
 *
 * param base XRDC peripheral base address.
 * param master Which master to configure.
 * param assignIndex Which assignment register to set.
 * param domainAssignment Pointer to the assignment structure.
 */
void XRDC_SetNonProcessorDomainAssignment(XRDC_Type *base,
                                          xrdc_master_t master,
                                          uint8_t assignIndex,
                                          const xrdc_non_processor_domain_assignment_t *domainAssignment)
{
    /* Make sure the master is a non-CPU/non-processor master */
    assert(0U != (base->MDACFG[master] & XRDC_MDACFG_NCM_MASK));
    /* Make sure the master has the assignment register. */
    assert(assignIndex < ((base->MDACFG[master] & XRDC_MDACFG_NMDAR_MASK) >> XRDC_MDACFG_NMDAR_SHIFT));
    assert(NULL != domainAssignment);

    xrdc_mda_reg_t mda;

    mda._mdaNonProc = *domainAssignment;

    base->MDA[master].MDA_W[assignIndex] = (mda._u32 | XRDC_MDA_W_VLD_MASK);
}

/*!
 * brief Sets the processor bus master domain assignment.
 *
 * This function sets the processor master domain assignment as valid.
 * One bus master might have multiple domain assignment registers. The parameter
 * \p assignIndex specifies which assignment register to set.
 *
 * Example: Set domain assignment for core 0.
 * In this example, there are 3 assignment registers for core 0.
 *
 * code
 * xrdc_processor_domain_assignment_t processorAssignment;
 *
 * XRDC_GetDefaultProcessorDomainAssignment(&processorAssignment);
 *
 * processorAssignment.domainId = 1;
 * processorAssignment.xxx      = xxx;
 * XRDC_SetMasterDomainAssignment(XRDC, kXrdcMasterCpu0, 0U, &processorAssignment);
 *
 * processorAssignment.domainId = 2;
 * processorAssignment.xxx      = xxx;
 * XRDC_SetMasterDomainAssignment(XRDC, kXrdcMasterCpu0, 1U, &processorAssignment);
 *
 * processorAssignment.domainId = 0;
 * processorAssignment.xxx      = xxx;
 * XRDC_SetMasterDomainAssignment(XRDC, kXrdcMasterCpu0, 2U, &processorAssignment);
 * endcode
 *
 * param base XRDC peripheral base address.
 * param master Which master to configure.
 * param assignIndex Which assignment register to set.
 * param domainAssignment Pointer to the assignment structure.
 */
void XRDC_SetProcessorDomainAssignment(XRDC_Type *base,
                                       xrdc_master_t master,
                                       uint8_t assignIndex,
                                       const xrdc_processor_domain_assignment_t *domainAssignment)
{
    /* Make sure the master is a CPU/processor master */
    assert(0U == (base->MDACFG[master] & XRDC_MDACFG_NCM_MASK));
    /* Make sure the master has the assignment register. */
    assert(assignIndex < ((base->MDACFG[master] & XRDC_MDACFG_NMDAR_MASK) >> XRDC_MDACFG_NMDAR_SHIFT));
    assert(NULL != domainAssignment);

    xrdc_mda_reg_t mda;

    mda._mdaProc = *domainAssignment;

    base->MDA[master].MDA_W[assignIndex] = (mda._u32 | XRDC_MDA_W_VLD_MASK);
}

/*!
 * brief Gets the default memory region access policy.
 *
 * This function gets the default memory region access policy.
 * It sets the policy as follows:
 * code
 * config->enableSema            = false;
 * config->semaNum               = 0U;
 * config->subRegionDisableMask  = 0U;
 * config->size                  = kXrdcMemSizeNone;
 * config->lockMode              = kXRDC_AccessConfigLockWritable;
 * config->baseAddress           = 0U;
 * config->policy[0]             = kXRDC_AccessPolicyNone;
 * config->policy[1]             = kXRDC_AccessPolicyNone;
 * ...
 * config->policy[15]            = kXRDC_AccessPolicyNone;
 * endcode
 *
 * param config Pointer to the configuration structure.
 */
void XRDC_GetMemAccessDefaultConfig(xrdc_mem_access_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    uint8_t i;

#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SE) && FSL_FEATURE_XRDC_NO_MRGD_SE)
    config->enableSema = false;
    config->semaNum    = 0U;
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SE */

#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SZ) && FSL_FEATURE_XRDC_NO_MRGD_SZ)
    config->size = kXRDC_MemSizeNone;
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SZ */
#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SRD) && FSL_FEATURE_XRDC_NO_MRGD_SRD)
    config->subRegionDisableMask = 0U;
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SRD */

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_CR) && FSL_FEATURE_XRDC_HAS_MRGD_CR)
    config->codeRegion = kXRDC_MemCodeRegion0;
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_CR */

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_ACCSET) && FSL_FEATURE_XRDC_HAS_MRGD_ACCSET)
    config->enableAccset1Lock = false;
    config->enableAccset2Lock = false;
    config->accset1           = 0x000U;
    config->accset2           = 0x000U;
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_ACCSET */

    config->lockMode = kXRDC_AccessConfigLockWritable;

    config->baseAddress = 0U;
#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_ENDADDR) && FSL_FEATURE_XRDC_HAS_MRGD_ENDADDR)
    config->endAddress = 0U;
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_ENDADDR */

    for (i = 0U; i < (uint32_t)FSL_FEATURE_XRDC_DOMAIN_COUNT; i++)
    {
#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_DXACP) && FSL_FEATURE_XRDC_NO_MRGD_DXACP)
        config->policy[i] = kXRDC_AccessPolicyNone;
#elif (defined(FSL_FEATURE_XRDC_HAS_MRGD_DXSEL) && FSL_FEATURE_XRDC_HAS_MRGD_DXSEL)
        config->policy[i] = kXRDC_AccessFlagsNone;
#endif
    }

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_EAL) && FSL_FEATURE_XRDC_HAS_MRGD_EAL)
    config->exclAccessLockMode = kXRDC_ExclAccessLockDisabled;
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_EAL */
}

/*!
 * brief Sets the memory region access policy.
 *
 * This function sets the memory region access configuration as valid.
 * There are two methods to use it:
 *
 * Example 1: Set one configuration run time.
 * code
 * xrdc_mem_access_config_t config =
 * {
 *     .mem         = kXRDC_MemMrc0_1,
 *     .baseAddress = 0x20000000U,
 *     .size        = kXRDC_MemSize1K,
 *     .policy[0]   = kXRDC_AccessPolicyAll
 * };
 * XRDC_SetMemAccessConfig(XRDC, &config);
 * endcode
 *
 * Example 2: Set multiple configurations during startup.
 * code
 * xrdc_mem_access_config_t configs[] =
 * {
 *     {
 *         .mem         = kXRDC_MemMrc0_1,
 *         .baseAddress = 0x20000000U,
 *         .size        = kXRDC_MemSize1K,
 *         .policy[0]   = kXRDC_AccessPolicyAll
 *     },
 *     {
 *         .mem         = kXRDC_MemMrc0_2,
 *         .baseAddress = 0x1FFF0000U,
 *         .size        = kXRDC_MemSize2K,
 *         .policy[0]   = kXRDC_AccessPolicyAll
 *     }
 * };
 *
 * for (i=0U; i<((sizeof(configs)/sizeof(configs[0]))); i++)
 * {
 *     XRDC_SetMemAccessConfig(XRDC, &configs[i]);
 * }
 * endcode
 *
 * param base XRDC peripheral base address.
 * param config Pointer to the access policy configuration structure.
 */
void XRDC_SetMemAccessConfig(XRDC_Type *base, const xrdc_mem_access_config_t *config)
{
    assert(NULL != config);
#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SZ) && FSL_FEATURE_XRDC_NO_MRGD_SZ)
    /* Not allowed to set sub-region disable mask for memory region smaller than 256-bytes. */
    assert(!((config->size < kXRDC_MemSize256B) && (0U != config->subRegionDisableMask)));
    /* Memory region minimum size = 32 bytes and base address must be aligned to 0-module-2**(SZ+1). */
    assert(config->size >= kXRDC_MemSize32B);
    assert(0U == (config->baseAddress & ((1UL << ((uint32_t)config->size + 1U)) - 1UL)));
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SZ */

    uint32_t i;
    uint32_t regValue;
    uint8_t index = (uint8_t)config->mem;

    /* Set MRGD_W0. */
    base->MRGD[index].MRGD_W[0] = config->baseAddress;

/* Set MRGD_W1. */
#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SZ) && FSL_FEATURE_XRDC_NO_MRGD_SZ)
    base->MRGD[index].MRGD_W[1] = XRDC_MRGD_W_SZ(config->size) | XRDC_MRGD_W_SRD(config->subRegionDisableMask);
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SZ */

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_ENDADDR) && FSL_FEATURE_XRDC_HAS_MRGD_ENDADDR)
    base->MRGD[index].MRGD_W[1] = config->endAddress;
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_ENDADDR */

    /* Set MRGD_W2. */
    regValue = 0U;
/* Set MRGD_W2[D0ACP ~ D7ACP] or MRGD_W2[D0SEL ~ D2SEL]. */
#if (FSL_FEATURE_XRDC_DOMAIN_COUNT <= 8U)
    i = FSL_FEATURE_XRDC_DOMAIN_COUNT;
#elif (FSL_FEATURE_XRDC_DOMAIN_COUNT <= 16U)
    i = 8U;
#else
#error Does not support more than 16 domain.
#endif

    while (0U != (i--))
    {
#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_DXACP) && FSL_FEATURE_XRDC_NO_MRGD_DXACP)
        regValue <<= XRDC_MRGD_DXACP_WIDTH;
#elif (defined(FSL_FEATURE_XRDC_HAS_MRGD_DXSEL) && FSL_FEATURE_XRDC_HAS_MRGD_DXSEL)
        regValue <<= XRDC_MRGD_DXSEL_WIDTH;
#endif
        regValue |= (uint32_t)config->policy[i];
    }

#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SE) && FSL_FEATURE_XRDC_NO_MRGD_SE)
    regValue |= XRDC_MRGD_W_SE(config->enableSema) | XRDC_MRGD_W_SNUM(config->semaNum);
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SE */

    base->MRGD[index].MRGD_W[2] = regValue;

    /* Set MRGD_W3. */
    regValue = 0U;

#if ((FSL_FEATURE_XRDC_DOMAIN_COUNT > 8U) && (FSL_FEATURE_XRDC_DOMAIN_COUNT <= 16))
    /* Set MRGD_W3[D8ACP ~ D15ACP]. */
    for (i = FSL_FEATURE_XRDC_DOMAIN_COUNT - 1U; i > 7U; i--)
    {
        regValue <<= XRDC_MRGD_DXACP_WIDTH;
        regValue |= (uint32_t)config->policy[i];
    }
#endif

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_CR) && FSL_FEATURE_XRDC_HAS_MRGD_CR)
    regValue |= XRDC_MRGD_W_CR(config->codeRegion);
#endif

#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_W3_VLD) && FSL_FEATURE_XRDC_NO_MRGD_W3_VLD)
    regValue |= XRDC_MRGD_W_VLD_MASK | XRDC_MRGD_W_LK2(config->lockMode);
#endif

    base->MRGD[index].MRGD_W[3] = regValue;

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_EAL) && FSL_FEATURE_XRDC_HAS_MRGD_EAL)
    /*
     * Set MRGD_W3[EAL].
     * If write with a value of MRGD_W3[EAL]=0, then the other fields of MRGD_W3 are updated.
     * If write with a value of MRGD_W3[EAL]!=0, then only the EAL is updated.
     */
    if (kXRDC_ExclAccessLockDisabled != config->exclAccessLockMode)
    {
        base->MRGD[index].MRGD_W[3] = XRDC_MRGD_W_EAL(config->exclAccessLockMode);
    }
#endif

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_ACCSET) && FSL_FEATURE_XRDC_HAS_MRGD_ACCSET)
    /* Set MRGD_W4. */
    base->MRGD[index].MRGD_W[4] = XRDC_MRGD_W_LKAS1(config->enableAccset1Lock) | XRDC_MRGD_W_ACCSET1(config->accset1) |
                                  XRDC_MRGD_W_LKAS2(config->enableAccset2Lock) | XRDC_MRGD_W_ACCSET2(config->accset2) |
                                  XRDC_MRGD_W_VLD_MASK | XRDC_MRGD_W_LK2(config->lockMode);
#endif
}

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_EAL) && FSL_FEATURE_XRDC_HAS_MRGD_EAL)
/*!
 * brief Sets the memory region exclusive access lock mode configuration.
 *
 * Note: Any write to MRGD_W[0-3]_n clears the MRGD_W4_n[VLD] indicator so a coherent register state can be supported.
 *       It is indispensable to re-assert the valid bit when dynamically changing the EAL in the MRGD, which is done in
 * this API.
 *
 * param base XRDC peripheral base address.
 * param mem Which memory region's exclusive access lock mode to configure.
 * param lockMode The exclusive access lock mode to set.
 */
void XRDC_SetMemExclAccessLockMode(XRDC_Type *base, xrdc_mem_t mem, xrdc_excl_access_lock_config_t lockMode)
{
    /* Write kXRDC_ExclAccessLockDisabled is not allowed. */
    assert(kXRDC_ExclAccessLockDisabled != lockMode);

    uint32_t reg = base->MRGD[mem].MRGD_W[4];

    /* Step 1. Set the memory region exclusive access lock mode configuration. */
    base->MRGD[mem].MRGD_W[3] = XRDC_MRGD_W_EAL(lockMode);

    /* Step 2. Set MRGD_W3 will clear the MRGD_W4[VLD]. So should re-assert it. */
    base->MRGD[mem].MRGD_W[4] = reg;
}

/*!
 * brief Forces the release of the memory region exclusive access lock.
 *
 * A lock can be forced to the available state (EAL=10) by a domain that does not own the
 * lock through the forced lock release procedure:
 * The procedure to force a exclusive access lock release is as follows:
 * 1. Write 0x02000046 to W1 register (PAC/MSC) or W3 register (MRC)
 * 2. Write 0x02000052 to W1 register (PAC/MSC) or W3 register (MRC)
 *
 * Note: The two writes must be consecutive, any intervening write to the register resets the sequence.
 *
 * param base XRDC peripheral base address.
 * param mem Which memory region's exclusive access lock to force release.
 */
void XRDC_ForceMemExclAccessLockRelease(XRDC_Type *base, xrdc_mem_t mem)
{
    uint32_t primask;

    primask                   = DisableGlobalIRQ();
    base->MRGD[mem].MRGD_W[3] = XRDC_FORCE_EXCL_ACS_LOCK_REL_VAL1;
    base->MRGD[mem].MRGD_W[3] = XRDC_FORCE_EXCL_ACS_LOCK_REL_VAL2;
    EnableGlobalIRQ(primask);
}
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_EAL */

#if (defined(FSL_FEATURE_XRDC_HAS_MRGD_ACCSET) && FSL_FEATURE_XRDC_HAS_MRGD_ACCSET)
/*!
 * brief Sets the memory region ACCSET (programmable access flags) lock.
 *
 * param base XRDC peripheral base address.
 * param mem Which memory region descriptor to lock.
 * param mem Which set/index of ACCSET to lock.
 * param lock True to set lock, false to set unlock.
 */
void XRDC_SetMemAccsetLock(XRDC_Type *base, xrdc_mem_t mem, xrdc_mem_accset_t accset, bool lock)
{
    uint32_t lkasMask = 0U;

    if (kXRDC_MemAccset1 == accset)
    {
        lkasMask = XRDC_MRGD_W_LKAS1_MASK;
    }
    else
    {
        lkasMask = XRDC_MRGD_W_LKAS2_MASK;
    }

    if (lock)
    {
        base->MRGD[mem].MRGD_W[4] |= lkasMask;
    }
    else
    {
        base->MRGD[mem].MRGD_W[4] &= ~lkasMask;
    }
}
#endif /* FSL_FEATURE_XRDC_HAS_MRGD_ACCSET */

/*!
 * brief Gets the default peripheral access configuration.
 *
 * The default configuration is set as follows:
 * code
 * config->enableSema        = false;
 * config->semaNum           = 0U;
 * config->lockMode          = kXRDC_AccessConfigLockWritable;
 * config->policy[0]         = kXRDC_AccessPolicyNone;
 * config->policy[1]         = kXRDC_AccessPolicyNone;
 * ...
 * config->policy[15]        = kXRDC_AccessPolicyNone;
 * endcode
 *
 * param config Pointer to the configuration structure.
 */
void XRDC_GetPeriphAccessDefaultConfig(xrdc_periph_access_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    uint8_t i;

#if !(defined(FSL_FEATURE_XRDC_NO_PDAC_SE) && FSL_FEATURE_XRDC_NO_PDAC_SE)
    config->enableSema = false;
    config->semaNum    = 0U;
#endif /* FSL_FEATURE_XRDC_NO_PDAC_SE */
    config->lockMode = kXRDC_AccessConfigLockWritable;
#if (defined(FSL_FEATURE_XRDC_HAS_PDAC_EAL) && FSL_FEATURE_XRDC_HAS_PDAC_EAL)
    config->exclAccessLockMode = kXRDC_ExclAccessLockDisabled;
#endif /* FSL_FEATURE_XRDC_HAS_PDAC_EAL */
    for (i = 0U; i < (uint32_t)FSL_FEATURE_XRDC_DOMAIN_COUNT; i++)
    {
        config->policy[i] = kXRDC_AccessPolicyNone;
    }
}

/*!
 * brief Sets the peripheral access configuration.
 *
 * This function sets the peripheral access configuration as valid. Two
 * methods to use it:
 * Method 1: Set for one peripheral, which is used for runtime settings.
 * code
 * xrdc_periph_access_config_t config;
 *
 * config.periph    = kXRDC_PeriphLptmr0;
 * config.policy[0] = kXRDC_AccessPolicyAll;
 * XRDC_SetPeriphAccessConfig(XRDC, &config);
 * endcode
 *
 * Method 2: Set for multiple peripherals, which is used for initialization settings.
 * code
 * xrdc_periph_access_config_t configs[] =
 * {
 *     {
 *         .periph    = kXRDC_PeriphLptmr0,
 *         .policy[0] = kXRDC_AccessPolicyAll,
 *         .policy[1] = kXRDC_AccessPolicyAll
 *     },
 *     {
 *         .periph    = kXRDC_PeriphLpuart0,
 *         .policy[0] = kXRDC_AccessPolicyAll,
 *         .policy[1] = kXRDC_AccessPolicyAll
 *     }
 * };
 *
 * for (i=0U; i<(sizeof(configs)/sizeof(configs[0])), i++)
 * {
 *     XRDC_SetPeriphAccessConfig(XRDC, &config[i]);
 * }
 * endcode
 *
 * param base XRDC peripheral base address.
 * param config Pointer to the configuration structure.
 */
void XRDC_SetPeriphAccessConfig(XRDC_Type *base, const xrdc_periph_access_config_t *config)
{
    assert(NULL != config);

    uint32_t i;
    uint32_t regValue;
    uint8_t index = (uint8_t)config->periph;

    /* Set PDAC_W0[D0ACP ~ D7ACP]. */
    regValue = 0U;
#if (FSL_FEATURE_XRDC_DOMAIN_COUNT <= 8U)
    i = FSL_FEATURE_XRDC_DOMAIN_COUNT;
#elif (FSL_FEATURE_XRDC_DOMAIN_COUNT <= 16U)
    i = 8U;
#else
#error Does not support more than 16 domain.
#endif

    while (0U != (i--))
    {
        regValue <<= XRDC_PDAC_DXACP_WIDTH;
        regValue |= (uint32_t)config->policy[i];
    }

#if !(defined(FSL_FEATURE_XRDC_NO_MRGD_SE) && FSL_FEATURE_XRDC_NO_MRGD_SE)
    regValue |= (XRDC_PDAC_W_SE(config->enableSema) | XRDC_PDAC_W_SNUM(config->semaNum));
#endif /* FSL_FEATURE_XRDC_NO_MRGD_SE */

    /* Set PDAC_W0. */
    base->PDAC_W[index][0U] = regValue;

#if (defined(FSL_FEATURE_XRDC_HAS_PDAC_EAL) && FSL_FEATURE_XRDC_HAS_PDAC_EAL)
    /*
     * If write with a value of PDAC_W1[EAL]=0, then the other fields of PDAC_W1 are updated.
     * If write with a value of PDAC_W1[EAL]!=0, then only the EAL is updated.
     */
    base->PDAC_W[index][1U] = XRDC_PDAC_W_EAL(config->exclAccessLockMode);
#endif

    regValue = 0U;
#if ((FSL_FEATURE_XRDC_DOMAIN_COUNT > 8U) && (FSL_FEATURE_XRDC_DOMAIN_COUNT <= 16))
    /* Set PDAC_W1[D8ACP ~ D15ACP]. */

    for (i = FSL_FEATURE_XRDC_DOMAIN_COUNT - 1U; i > 7U; i--)
    {
        regValue <<= XRDC_PDAC_DXACP_WIDTH;
        regValue |= (uint32_t)config->policy[i];
    }
#endif
    /* Set PDAC_W1. */
    base->PDAC_W[index][1] = regValue | XRDC_PDAC_W_VLD_MASK | XRDC_PDAC_W_LK2(config->lockMode);
}

#if (defined(FSL_FEATURE_XRDC_HAS_PDAC_EAL) && FSL_FEATURE_XRDC_HAS_PDAC_EAL)
/*!
 * brief Forces the release of the peripheral exclusive access lock.
 *
 * A lock can be forced to the available state (EAL=10) by a domain that does not own the
 * lock through the forced lock release procedure:
 * The procedure to force a exclusive access lock release is as follows:
 * 1. Write 0x02000046 to W1 register (PAC/MSC) or W3 register (MRC)
 * 2. Write 0x02000052 to W1 register (PAC/MSC) or W3 register (MRC)
 *
 * Note: The two writes must be consecutive, any intervening write to the register resets the sequence.
 *
 * param base XRDC peripheral base address.
 * param periph Which peripheral's exclusive access lock to force release.
 */
void XRDC_ForcePeriphExclAccessLockRelease(XRDC_Type *base, xrdc_periph_t periph)
{
    uint32_t primask;

    primask                 = DisableGlobalIRQ();
    base->PDAC_W[periph][1] = XRDC_FORCE_EXCL_ACS_LOCK_REL_VAL1;
    base->PDAC_W[periph][1] = XRDC_FORCE_EXCL_ACS_LOCK_REL_VAL2;
    EnableGlobalIRQ(primask);
}
#endif /* FSL_FEATURE_XRDC_HAS_PDAC_EAL */
