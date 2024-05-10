/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi_flr.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexspi_flr"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Typedef for interrupt handler. */
typedef void (*flexspi_slv_isr_t)(FLEXSPI_SLV_Type *base, flexspi_slv_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void FLEXSPI_SLV_Memset(void *src, uint8_t value, size_t length);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to Flexspi Follower bases for each instance. */
static FLEXSPI_SLV_Type *const s_flexspiSlvBases[] = FLEXSPI_SLV_BASE_PTRS;

/*! @brief Pointers to Flexspi Follower IRQ number for each instance. */
static const IRQn_Type s_flexspiSlvIrqs[] = { FLEXSPI_SLV_IRQn };

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name array */
static const clock_ip_name_t s_flexspiSlvClock[] = FLEXSPI_SLV_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ) && FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ
/*! @brief Pointers to Flexspi Follower handles for each instance. */
static flexspi_slv_handle_t *s_flexspiSlvHandle[ARRAY_SIZE(s_flexspiSlvBases)];
#endif

#if defined(FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ) && FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ
/*! @brief Pointer to Flexspi Follower IRQ handler. */
static flexspi_slv_isr_t s_flexspiSlvIsr;
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
/* To avoid compiler opitimizing this API into memset() in library. */
#if defined(__ICCARM__)
#pragma optimize = none
#endif /* defined(__ICCARM__) */
static void FLEXSPI_SLV_Memset(void *src, uint8_t value, size_t length)
{
    assert(src != NULL);
    uint8_t *p = src;

    for (uint32_t i = 0U; i < length; i++)
    {
        *p = value;
        p++;
    }
}

/*!
 * brief Gets the index of the FLEXSPI FOLLOWER in the array according to the base address.
 *
 * param base FLEXSPI FOLLOWER peripheral base address.
 */
uint32_t FLEXSPI_SLV_GetInstance(FLEXSPI_SLV_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_flexspiSlvBases); instance++)
    {
        if (s_flexspiSlvBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_flexspiSlvBases));

    return instance;
}

/*!
 * brief Returns the interrupt status and clear the interrupt flag.
 *
 * param base FLEXSPI FOLLOWER peripheral base address.
 */
uint32_t FLEXSPI_SLV_CheckAndClearInterrupt(FLEXSPI_SLV_Type *base)
{
    uint32_t status = FLEXSPI_SLV_GetInterruptStatusFlags(base);
    uint32_t intEnableStatus = FLEXSPI_SLV_GetEnabledInterrupts(base);

    /* Check for interrupt. */
    status &= intEnableStatus;
    if (0U != status)
    {
        /* Clear the flags. */
        FLEXSPI_SLV_ClearInterruptStatusFlags(base, status);

        /* Select the correct interrupt flag. */
        if (0U != (status & (uint32_t)FLEXSPI_SLV_MODULE_INT_WOF_MASK))
        {
            status = kFLEXSPI_SLV_WriteOverflowFlag;
        }
        else if (0U != (status & (uint32_t)FLEXSPI_SLV_MODULE_INT_RUF_MASK))
        {
            status = kFLEXSPI_SLV_ReadUnderflowFlag;
        }
        else if (0U != (status & (uint32_t)FLEXSPI_SLV_MODULE_INT_ERRCMD_MASK))
        {
            status = kFLEXSPI_SLV_ErrorCommandFlag;
        }
        else
        {
            status = kFLEXSPI_SLV_InvalidInterruptFlag;
        }
    }
    else if (FLEXSPI_SLV_GetEnabledMailInterrupt(base))
    {
        status = FLEXSPI_SLV_GetMailInterruptIndex(base);
        if (status >= FLEXSPI_SLV_SPIMAIL_COUNT)
        {
            status = kFLEXSPI_SLV_InvalidInterruptFlag;
        }
        /* Clear the flag. */
        FLEXSPI_SLV_ClearMailInterruptFlag(base);
    }
    else
    {
        status = kFLEXSPI_SLV_InvalidInterruptFlag;
    }

    return status;
}

/*!
 * brief Sets the root clock of the FLEXSPI FOLLOWER.
 *
 * param clock_freq The expected root clock of the FLEXSPI FOLLOWER.
 */
void FLEXSPI_SLV_ClkRootFrq(int clock_freq)
{
    clock_root_config_t rootCfg = {0};

    switch (clock_freq) {
        case RootClock_50M:
            /* Configure FLEXSPI_SLV using OSC_RC_400M */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxOscRc400M;
            rootCfg.div = 8;
            break;

        case RootClock_66M:
            /* Configure FLEXSPI_SLV using SYS_PLL2_CLK */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll2Out;
            rootCfg.div = 8;
            break;

        case RootClock_80M:
            /* Configure FLEXSPI_SLV using OSC_RC_400M */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxOscRc400M;
            rootCfg.div = 5;
            break;

        case RootClock_100M:
            /* Configure FLEXSPI_SLV using OSC_RC_400M */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxOscRc400M;
            rootCfg.div = 4;
            break;

        case RootClock_166M:
            /* Configure FLEXSPI_SLV using SYS_PLL1_CLK */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll1Out;
            rootCfg.div = 6;
            break;

        case RootClock_200M:
            /* Configure FLEXSPI_SLV using SYS_PLL1_CLK */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll1Out;
            rootCfg.div = 5;
            break;

        case RootClock_400M:
            /* Configure FLEXSPI_SLV using OSC_RC_400M */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxOscRc400M;
            rootCfg.div = 1;
            break;

	default:
            /* RootClock_133M: Configure FLEXSPI_SLV using SYS_PLL2_CLK */
            rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll2Out;
            rootCfg.div = 4;
            break;
    }
    CLOCK_SetRootClock(kCLOCK_Root_Flexspi_Slv, &rootCfg);
}

/*!
 * brief Initializes the FLEXSPI FOLLOWER module and internal state.
 *
 * This function enables the clock for FLEXSPI FOLLOWER and also configures the FLEXSPI
 * FOLLOWER with the input configure parameters. Users should call this function before
 * any FLEXSPI FOLLOWER operations.
 *
 * param base FLEXSPI FOLLOWER peripheral base address.
 * param config FLEXSPI FOLLOWER configure structure.
 */
void FLEXSPI_SLV_Init(FLEXSPI_SLV_Type *base, const flexspi_slv_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the flexspi follower clock */
    (void)CLOCK_EnableClock(s_flexspiSlvClock[FLEXSPI_SLV_GetInstance(base)]);
    FLEXSPI_SLV_ClkRootFrq(config->clock_freq);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset peripheral before configuring it. */
    FLEXSPI_SLV_SoftwareReset_SetVal(base, 1);
    FLEXSPI_SLV_SoftwareReset_SetVal(base, 0);

    /* Set IO mode. */
    FLEXSPI_SLV_IOMode_SetVal(base, config->io_mode);

    /* Set RW base address and range */
    FLEXSPI_SLV_RW_CMD_BaseAddr1_SetVal(base, (config->baseAddr1) >> 16);
    FLEXSPI_SLV_RW_CMD_BaseAddr2_SetVal(base, (config->baseAddr2) >> 16);
    FLEXSPI_SLV_Update_RWCMD_Base_Range(base);

    FLEXSPI_SLV_AddrRange_SetVal(base, 0x0, config->addrRange1);
    FLEXSPI_SLV_AddrRange_SetVal(base, 0x1, config->addrRange2);
    FLEXSPI_SLV_Update_RWCMD_Base_Range(base);

    /* Set read water mark level */
    FLEXSPI_SLV_Read_WMEN_SetVal(base, 1);
    FLEXSPI_SLV_Read_RDWM_SetVal(base, config->rxWatermark);

    FLEXSPI_SLV_Read_FetchSizeSet(base, config->rxFetch_size);

    /* Set write water mark level */
    FLEXSPI_SLV_Write_WRWM_SetVal(base, config->txWatermark);

    /* Clear CS mask*/
    FLEXSPI_SLV_CSMASK_SetVal(base, 0);
}

/*!
 * brief Gets default settings for FLEXSPI FOLLOWER.
 *
 * param config FLEXSPI FOLLOWER configuration structure.
 */
void FLEXSPI_SLV_GetDefaultConfig(flexspi_slv_config_t *config)
{
    /* Initializes the configure structure to zero. */
    FLEXSPI_SLV_Memset(config, 0, sizeof(*config));

    config->clock_freq     = RootClock_133M;
    config->baseAddr1      = 0;
    config->baseAddr2      = 0x1000;
    config->addrRange1     = 0;
    config->addrRange2     = 0;
    config->io_mode        = kFLEXSPI_SLV_IOMODE_SDRx4;
    config->rxFetch_size   = Read_Fetch_256Bytes;
    config->rxWatermark    = 0;
    config->txWatermark    = Write_Watermark_128Bytes;
}

/*!
 * brief Deinitializes the FLEXSPI FOLLOWER module.
 *
 * Clears the FLEXSPI FOLLOWER state and FLEXSPI FOLLOWER module registers.
 *
 * param base FLEXSPI FOLLOWER peripheral base address.
 */
void FLEXSPI_SLV_Deinit(FLEXSPI_SLV_Type *base)
{
    /* Reset peripheral. */
    while (FLEXSPI_SLV_GetModuleBusyStatus(base));
    FLEXSPI_SLV_SoftwareReset_SetVal(base, 1);
}

/*!
 * brief Initializes the FLEXSPI FOLLOWER handle which is used in transactional functions.
 *
 * param base FLEXSPI FOLLOWER peripheral base address.
 * param handle Pointer to flexspi_slv_handle_t structure to store the interrupt state.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 */
void FLEXSPI_SLV_InterruptCreateHandle(FLEXSPI_SLV_Type *base,
                                       flexspi_slv_handle_t *handle,
                                       flexspi_slv_interrupt_callback_t callback,
                                       void *userData)
{
    assert(NULL != handle);

    uint32_t instance = FLEXSPI_SLV_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

#if defined(FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ) && FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ
    /* Save the context in global variables to support the double weak mechanism. */
    s_flexspiSlvHandle[instance] = handle;
    s_flexspiSlvIsr              = FLEXSPI_SLV_HandleIRQ;
#endif

    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_flexspiSlvIrqs[instance]);

    FLEXSPI_SLV_EnableInterrupts(base, *(uint32_t *)userData);
#if defined(FSL_DRIVER_FOLLOWER_MAILBOX_IRQ) && FSL_DRIVER_FOLLOWER_MAILBOX_IRQ
    FLEXSPI_SLV_EnableMailInterrupt(base, true);
#endif
}

/*!
 * brief Master interrupt handler.
 *
 * param base FLEXSPI FOLLOWER peripheral base address.
 * param handle Pointer to flexspi_slv_handle_t structure.
 */
void FLEXSPI_SLV_HandleIRQ(FLEXSPI_SLV_Type *base, flexspi_slv_handle_t *handle)
{

    handle->state = FLEXSPI_SLV_CheckAndClearInterrupt(base);

    /* Check if interrupt is enabled and status is alerted. */
    if ((handle->state != kFLEXSPI_SLV_InvalidInterruptFlag) &&
        (handle->callback != NULL))
    {
        handle->callback(base, handle);
    }
}

#if defined(FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ) && FSL_DRIVER_FOLLOWER_DOUBLE_WEAK_IRQ
#if defined(FLEXSPI_SLV)
void FLEXSPI_SLV_DriverIRQHandler(void);
void FLEXSPI_SLV_DriverIRQHandler(void)
{
    s_flexspiSlvIsr(FLEXSPI_SLV, s_flexspiSlvHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
#endif

