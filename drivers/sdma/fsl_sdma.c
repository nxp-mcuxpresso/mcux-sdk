/*
 * Copyright  2016-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdma.h"
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
#include "fsl_memory.h"
#endif
#include "fsl_sdma_script.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sdma"
#endif

/*! @brief SDMA P2P macro definition */
#define SDMA_P2P_LOW_WATERMARK_MASK  (0xFFU)
#define SDMA_P2P_LOW_WATERMARK_SHIFT (0U)
#define SDMA_P2P_LOW_WATERMARK(val)  ((uint32_t)(val)&SDMA_P2P_LOW_WATERMARK_MASK)

#define SDMA_P2P_HIGH_WATERMARK_SHIFT (16U)
#define SDMA_P2P_HIGH_WATERMARK_MASK  (0xFFUL << SDMA_P2P_HIGH_WATERMARK_SHIFT)
#define SDMA_P2P_HIGH_WATERMARK(val)  (((uint32_t)(val) << SDMA_P2P_HIGH_WATERMARK_SHIFT) & SDMA_P2P_HIGH_WATERMARK_MASK)

#define SDMA_P2P_SOURCE_SPBA_SHIFT    (11U)
#define SDMA_P2P_SOURCE_SPBA_MASK     (1UL << SDMA_P2P_SOURCE_SPBA_SHIFT)
#define SDMA_P2P_SOURCE_SPBA_VAL(val) (((uint32_t)(val) << SDMA_P2P_SOURCE_SPBA_SHIFT) & SDMA_P2P_SOURCE_SPBA_MASK)

#define SDMA_P2P_DEST_SPBA_SHIFT (12U)
#define SDMA_P2P_DEST_SPBA_MASK  (1UL << SDMA_P2P_DEST_SPBA_SHIFT)
#define SDMA_P2P_DEST_SPBA(val)  (((uint32_t)(val) << SDMA_P2P_DEST_SPBA_SHIFT) & SDMA_P2P_DEST_SPBA_MASK)

#define SDMA_P2P_LOWER_EVENT_REG_SHIFT (28U)
#define SDMA_P2P_LOWER_EVENT_REG_MASK  (1UL << SDMA_P2P_LOWER_EVENT_REG_SHIFT)
#define SDMA_P2P_LOWER_EVENT_REG(val) \
    (((uint32_t)(val) << SDMA_P2P_LOWER_EVENT_REG_SHIFT) & SDMA_P2P_LOWER_EVENT_REG_MASK)

#define SDMA_P2P_HIGHER_EVENT_REG_SHIFT (29U)
#define SDMA_P2P_HIGHER_EVENT_REG_MASK  (1UL << SDMA_P2P_HIGHER_EVENT_REG_SHIFT)
#define SDMA_P2P_HIGHER_EVENT_REG(val) \
    (((uint32_t)(val) << SDMA_P2P_HIGHER_EVENT_REG_SHIFT) & SDMA_P2P_HIGHER_EVENT_REG_MASK)

#define SDMA_P2P_CONT_SHIFT (31U)
#define SDMA_P2P_CONT_MASK  (1UL << SDMA_P2P_CONT_SHIFT)
#define SDMA_P2P_CONT(val)  (((uint32_t)(val) << SDMA_P2P_CONT_SHIFT) & SDMA_P2P_CONT_MASK)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for SDMA.
 *
 * @param base SDMA peripheral base address.
 */
static uint32_t SDMA_GetInstance(SDMAARM_Type *base);

/*!
 * @brief Run scripts for channel0.
 *
 * Channel0 is by default used as the boot channel for SDMA, also the scripts for channel0 will download scripts
 * for other channels from ARM platform to SDMA RAM context.
 *
 * @param base SDMA peripheral base address.
 */
static void SDMA_RunChannel0(SDMAARM_Type *base);

/*!
 * @brief Load the SDMA contex from ARM memory into SDMA RAM region.
 *
 * @param base SDMA peripheral base address.
 * @param channel SDMA channel number.
 * @param tcd Point to TCD structure.
 */
static void SDMA_LoadContext(sdma_handle_t *handle, const sdma_transfer_config_t *config);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Array to map SDMA instance number to base pointer. */
static SDMAARM_Type *const s_sdmaBases[] = SDMAARM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map SDMA instance number to clock name. */
static const clock_ip_name_t s_sdmaClockName[] = SDMA_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Array to map SDMA instance number to IRQ number. */
static const IRQn_Type s_sdmaIRQNumber[FSL_FEATURE_SOC_SDMA_COUNT] = SDMAARM_IRQS;

/*! @brief Pointers to transfer handle for each SDMA channel. */
static sdma_handle_t *s_SDMAHandle[FSL_FEATURE_SOC_SDMA_COUNT][FSL_FEATURE_SDMA_MODULE_CHANNEL];

/*! @brief channel 0 Channel control blcok */
AT_NONCACHEABLE_SECTION_ALIGN(
    static sdma_channel_control_t s_SDMACCB[FSL_FEATURE_SOC_SDMA_COUNT][FSL_FEATURE_SDMA_MODULE_CHANNEL], 4);

/*! @brief channel 0 buffer descriptor */
AT_NONCACHEABLE_SECTION_ALIGN(
    static sdma_buffer_descriptor_t s_SDMABD[FSL_FEATURE_SOC_SDMA_COUNT][FSL_FEATURE_SDMA_MODULE_CHANNEL], 4);
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SDMA_GetInstance(SDMAARM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_sdmaBases); instance++)
    {
        if (s_sdmaBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_sdmaBases));

    return instance;
}

static void SDMA_RunChannel0(SDMAARM_Type *base)
{
    /* Start channel 0 */
    SDMA_StartChannelSoftware(base, 0U);

    /* Waiting for channel 0 finished */
    while ((base->STOP_STAT & 0x1U) == 1U)
    {
    }

    /* Clear the channel interrupt status */
    SDMA_ClearChannelInterruptStatus(base, 0x1U);

    /* Set SDMA context switch to dynamic switching */
    SDMA_SetContextSwitchMode(base, kSDMA_ContextSwitchModeDynamic);
}

static uint32_t SDMA_GetScriptAddr(sdma_peripheral_t peripheral, sdma_transfer_type_t type)
{
    uint32_t val = 0;

    if (type == kSDMA_MemoryToMemory)
    {
        val = FSL_FEATURE_SDMA_M2M_ADDR;
    }
    else if (type == kSDMA_MemoryToPeripheral)
    {
        switch (peripheral)
        {
            case kSDMA_PeripheralTypeUART:
            case kSDMA_PeripheralNormal:
                val = FSL_SDMA_M2P_ADDR;
                break;
            case kSDMA_PeripheralTypeUART_SP:
            case kSDMA_PeripheralNormal_SP:
            case kSDMA_PeripheralASRCM2P:
                val = FSL_SDMA_M2SHP_ADDR;
                break;
            case kSDMA_PeripheralTypeSPDIF:
                val = FSL_SDMA_M2SPDIF_ADDR;
                break;
            case kSDMA_PeripheralMultiFifoSaiTX:
                val = FSL_SDMA_MULTI_FIFO_SAI_TX_ADDR;
                break;
            default:
                assert(false);
                break;
        }
    }
    else if (type == kSDMA_PeripheralToMemory)
    {
        switch (peripheral)
        {
            case kSDMA_PeripheralTypeUART:
                val = FSL_SDMA_UART2M_ADDR;
                break;
            case kSDMA_PeripheralNormal:
                val = FSL_SDMA_P2M_ADDR;
                break;
            case kSDMA_PeripheralTypeUART_SP:
                val = FSL_SDMA_UARTSH2M_ADDR;
                break;
            case kSDMA_PeripheralNormal_SP:
            case kSDMA_PeripheralASRCP2M:
                val = FSL_SDMA_SHP2M_ADDR;
                break;
            case kSDMA_PeripheralTypeSPDIF:
                val = FSL_SDMA_SPDIF2M_ADDR;
                break;
            case kSDMA_PeripheralMultiFifoPDM:
            case kSDMA_PeripheralMultiFifoSaiRX:
                val = FSL_SDMA_MULTI_FIFO_SAI_RX_ADDR;
                break;
            default:
                assert(false);
                break;
        }
    }
    else
    {
        val = FSL_SDMA_PERIPHERAL_TO_PERIPHERAL_ADDR;
    }

    return val;
}

static void SDMA_LoadContext(sdma_handle_t *handle, const sdma_transfer_config_t *config)
{
    uint32_t instance            = SDMA_GetInstance(handle->base);
    sdma_context_data_t *context = handle->context;

    (void)memset(context, 0, sizeof(sdma_context_data_t));

    /* Set SDMA core's PC to the channel script address */
    context->PC = (uint16_t)config->scriptAddr;
    if (config->type == kSDMA_PeripheralToPeripheral)
    {
        context->GeneralReg[0] = config->eventMask1;
        context->GeneralReg[1] = config->eventMask0;
        context->GeneralReg[2] = (uint32_t)config->srcAddr;
        context->GeneralReg[6] = (uint32_t)config->destAddr;
        context->GeneralReg[7] = config->watermarkLevel;
    }
    else
    {
        /* Set the request source into context */
        if (config->eventSource >= 32U)
        {
            context->GeneralReg[0] = (1UL << (config->eventSource - 32U));
        }
        else
        {
            context->GeneralReg[1] = (1UL << config->eventSource);
        }

        /* Set source address and dest address for p2p, m2p and p2m */
        if (config->type == kSDMA_MemoryToPeripheral)
        {
            context->GeneralReg[2] = (uint32_t)config->destAddr;
            context->GeneralReg[6] = (uint32_t)config->destAddr;
        }
        else
        {
            context->GeneralReg[2] = (uint32_t)config->srcAddr;
            context->GeneralReg[6] = (uint32_t)config->srcAddr;
        }

        /* Set watermark, multi fifo for p2p, m2p and p2m into context */
        context->GeneralReg[7] =
            ((config->bytesPerRequest & (uint32_t)kSDMA_MultiFifoWatermarkLevelMask)
             << kSDMA_MultiFifoWatermarkLevelShift) |
            ((config->multiFifo.fifoNums & (uint32_t)kSDMA_MultiFifoNumsMask) << kSDMA_MultiFifoNumsShift) |
            ((config->multiFifo.fifoOffset & (uint32_t)kSDMA_MultiFifoOffsetMask) << kSDMA_MultiFifoOffsetShift) |
            ((config->swDone.enableSwDone ? (uint32_t)kSDMA_MultiFifoSwDoneMask : 0UL) << kSDMA_MultiFifoSwDoneShift) |
            ((config->swDone.swDoneSel & (uint32_t)kSDMA_MultiFifoSwDoneSelectorMask)
             << kSDMA_MultiFifoSwDoneSelectorShift);
    }
    s_SDMABD[instance][0].command = (uint8_t)kSDMA_BDCommandSETDM;
    s_SDMABD[instance][0].status =
        (uint8_t)kSDMA_BDStatusDone | (uint8_t)kSDMA_BDStatusWrap | (uint8_t)kSDMA_BDStatusInterrupt;
    s_SDMABD[instance][0].count = sizeof(*context) / 4U;
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    s_SDMABD[instance][0].bufferAddr = MEMORY_ConvertMemoryMapAddress((uint32_t)context, kMEMORY_Local2DMA);
#else
    s_SDMABD[instance][0].bufferAddr     = (uint32_t)context;
#endif
    s_SDMABD[instance][0].extendBufferAddr = 2048UL + (sizeof(*context) / 4UL) * handle->channel;

    /* Run channel0 scripts after context prepared */
    SDMA_RunChannel0(handle->base);
}

void SDMA_LoadScript(SDMAARM_Type *base, uint32_t destAddr, void *srcAddr, size_t bufferSizeBytes)
{
    /* Set the descriptor to 0 */
    uint32_t instance   = SDMA_GetInstance(base);
    uint32_t bufferAddr = 0U;

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    bufferAddr = MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)srcAddr, kMEMORY_Local2DMA);
#else
    bufferAddr                           = (uint32_t)srcAddr;
#endif

    s_SDMABD[instance][0].command = (uint8_t)kSDMA_BDCommandSETPM;
    s_SDMABD[instance][0].status =
        (uint8_t)kSDMA_BDStatusDone | (uint8_t)kSDMA_BDStatusWrap | (uint8_t)kSDMA_BDStatusExtend;
    s_SDMABD[instance][0].count            = (uint16_t)bufferSizeBytes;
    s_SDMABD[instance][0].bufferAddr       = bufferAddr;
    s_SDMABD[instance][0].extendBufferAddr = destAddr;

    /* Run channel0 scripts */
    SDMA_RunChannel0(base);
}

void SDMA_DumpScript(SDMAARM_Type *base, uint32_t srcAddr, void *destAddr, size_t bufferSizeBytes)
{
    /* Set the descriptor to 0 */
    uint32_t instance   = SDMA_GetInstance(base);
    uint32_t bufferAddr = 0U;

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    bufferAddr = MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)destAddr, kMEMORY_Local2DMA);
#else
    bufferAddr                           = (uint32_t)destAddr;
#endif

    s_SDMABD[instance][0].command = (uint8_t)kSDMA_BDCommandGETPM;
    s_SDMABD[instance][0].status =
        (uint8_t)kSDMA_BDStatusDone | (uint8_t)kSDMA_BDStatusWrap | (uint8_t)kSDMA_BDStatusExtend;
    s_SDMABD[instance][0].count            = (uint16_t)bufferSizeBytes;
    s_SDMABD[instance][0].bufferAddr       = bufferAddr;
    s_SDMABD[instance][0].extendBufferAddr = srcAddr;

    /* Run channel0 scripts */
    SDMA_RunChannel0(base);
}

#if defined FSL_FEATURE_SOC_SPBA_COUNT && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
bool SDMA_IsPeripheralInSPBA(uint32_t addr)
{
    uint32_t spbaNum = FSL_FEATURE_SOC_SPBA_COUNT;
    uint32_t i       = 0;
    SPBA_Type *spbaBase;
    SPBA_Type *spbaArray[FSL_FEATURE_SOC_SPBA_COUNT] = SPBA_BASE_PTRS;

    for (i = 0; i < spbaNum; i++)
    {
        spbaBase = spbaArray[i];

        if ((addr >= (uint32_t)FSL_FEATURE_SPBA_STARTn(spbaBase)) &&
            (addr <= (uint32_t)FSL_FEATURE_SPBA_ENDn(spbaBase)))
        {
            return true;
        }
    }

    return false;
}
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

void SDMA_Init(SDMAARM_Type *base, const sdma_config_t *config)
{
    assert(config != NULL);

    uint32_t tmpreg;
    uint32_t instance = SDMA_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate SDMA periphral clock */
    CLOCK_EnableClock(s_sdmaClockName[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Clear the channel CCB */
    (void)memset(&s_SDMACCB[instance][0], 0,
                 sizeof(sdma_channel_control_t) * (uint32_t)FSL_FEATURE_SDMA_MODULE_CHANNEL);

    /* Reset all SDMA registers */
    SDMA_ResetModule(base);

    /* Init the CCB for channel 0 */
    (void)memset(&s_SDMABD[instance][0], 0, sizeof(sdma_buffer_descriptor_t));
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    s_SDMACCB[instance][0].currentBDAddr =
        MEMORY_ConvertMemoryMapAddress((uint32_t)(&s_SDMABD[instance][0]), kMEMORY_Local2DMA);
    s_SDMACCB[instance][0].baseBDAddr =
        MEMORY_ConvertMemoryMapAddress((uint32_t)(&s_SDMABD[instance][0]), kMEMORY_Local2DMA);
#else
    s_SDMACCB[instance][0].currentBDAddr = (uint32_t)(&s_SDMABD[instance][0]);
    s_SDMACCB[instance][0].baseBDAddr    = (uint32_t)(&s_SDMABD[instance][0]);
#endif

    /* Set channel 0 priority */
    SDMA_SetChannelPriority(base, 0, 7U);

    /* Set channel 0 ownership */
    base->HOSTOVR = 0U;
    base->EVTOVR  = 1U;

    /* Configure SDMA peripheral according to the configuration structure. */
    tmpreg = base->CONFIG;
    tmpreg &= ~(SDMAARM_CONFIG_ACR_MASK | SDMAARM_CONFIG_RTDOBS_MASK);
    /* Channel 0 shall use static context switch method */
    tmpreg |= (SDMAARM_CONFIG_ACR(config->ratio) | SDMAARM_CONFIG_RTDOBS(config->enableRealTimeDebugPin) |
               SDMAARM_CONFIG_CSM(0U));
    base->CONFIG = tmpreg;

    tmpreg = base->SDMA_LOCK;
    tmpreg &= ~SDMAARM_SDMA_LOCK_SRESET_LOCK_CLR_MASK;
    tmpreg |= SDMAARM_SDMA_LOCK_SRESET_LOCK_CLR(config->isSoftwareResetClearLock);
    base->SDMA_LOCK = tmpreg;

    /* Set the context size to 32 bytes */
    base->CHN0ADDR = 0x4050U;

/* Set channle 0 CCB address */
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    base->MC0PTR = MEMORY_ConvertMemoryMapAddress((uint32_t)(&s_SDMACCB[instance][0]), kMEMORY_Local2DMA);
#else
    base->MC0PTR                         = (uint32_t)(&s_SDMACCB[instance][0]);
#endif
}

void SDMA_Deinit(SDMAARM_Type *base)
{
    /* Clear the MC0PTR register */
    base->MC0PTR = 0U;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate SDMA periphral clock */
    CLOCK_DisableClock(s_sdmaClockName[SDMA_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void SDMA_GetDefaultConfig(sdma_config_t *config)
{
    assert(config != NULL);

    config->enableRealTimeDebugPin   = false;
    config->isSoftwareResetClearLock = true;
    config->ratio                    = kSDMA_HalfARMClockFreq;
}

void SDMA_ResetModule(SDMAARM_Type *base)
{
    uint32_t i = 0, status;

    base->MC0PTR = 0;
    status       = base->INTR;
    SDMA_ClearChannelInterruptStatus(base, status);
    status = base->STOP_STAT;
    SDMA_ClearChannelStopStatus(base, status);
    base->EVTOVR  = 0;
    base->DSPOVR  = 0xFFFFFFFFU;
    base->HOSTOVR = 0;
    status        = base->EVTPEND;
    SDMA_ClearChannelPendStatus(base, status);
    base->INTRMASK = 0;

    /* Disable all events */
    for (i = 0; i < (uint32_t)FSL_FEATURE_SDMA_EVENT_NUM; i++)
    {
        SDMA_SetSourceChannel(base, i, 0);
    }

    /* Clear all channel priority */
    for (i = 0; i < (uint32_t)FSL_FEATURE_SDMA_MODULE_CHANNEL; i++)
    {
        SDMA_SetChannelPriority(base, i, 0);
    }
}

void SDMA_ConfigBufferDescriptor(sdma_buffer_descriptor_t *bd,
                                 uint32_t srcAddr,
                                 uint32_t destAddr,
                                 sdma_transfer_size_t busWidth,
                                 size_t bufferSize,
                                 bool isLast,
                                 bool enableInterrupt,
                                 bool isWrap,
                                 sdma_transfer_type_t type)
{
    uint8_t status = 0U;

    /* Set the descriptor to 0 */
    (void)memset(bd, 0, sizeof(sdma_buffer_descriptor_t));
    if (type == kSDMA_PeripheralToMemory)
    {
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
        bd->bufferAddr = MEMORY_ConvertMemoryMapAddress(destAddr, kMEMORY_Local2DMA);
#else
        bd->bufferAddr = destAddr;
#endif
    }
    else
    {
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
        bd->bufferAddr = MEMORY_ConvertMemoryMapAddress(srcAddr, kMEMORY_Local2DMA);
#else
        bd->bufferAddr = srcAddr;
#endif
    }
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    bd->extendBufferAddr = MEMORY_ConvertMemoryMapAddress(destAddr, kMEMORY_Local2DMA);
#else
    bd->extendBufferAddr                                   = destAddr;
#endif
    if (isLast)
    {
        status |= (uint8_t)kSDMA_BDStatusLast;
    }
    else
    {
        status |= (uint8_t)kSDMA_BDStatusContinuous;
    }

    /* Set interrupt and wrap feature */
    if (enableInterrupt)
    {
        status |= (uint8_t)kSDMA_BDStatusInterrupt;
    }
    if (isWrap)
    {
        status |= (uint8_t)kSDMA_BDStatusWrap;
    }

    status |= (uint8_t)kSDMA_BDStatusDone;

    /* Configure the command according to bus width */
    bd->status  = status;
    bd->command = (uint8_t)busWidth;
    bd->count   = (uint16_t)bufferSize;
}

void SDMA_SetContextSwitchMode(SDMAARM_Type *base, sdma_context_switch_mode_t mode)
{
    uint32_t val = base->CONFIG & (~SDMAARM_CONFIG_CSM_MASK);
    val |= (uint32_t)mode;
    base->CONFIG = val;
}

bool SDMA_GetRequestSourceStatus(SDMAARM_Type *base, uint32_t source)
{
    if (source < 32U)
    {
        return ((base->EVT_MIRROR & (1UL << source)) >> source) != 0UL;
    }
    else
    {
        source -= 32U;
        return ((base->EVT_MIRROR2 & (1UL << source)) >> source) != 0UL;
    }
}

void SDMA_CreateHandle(sdma_handle_t *handle, SDMAARM_Type *base, uint32_t channel, sdma_context_data_t *context)
{
    assert(handle != NULL);
    assert(channel < (uint32_t)FSL_FEATURE_SDMA_MODULE_CHANNEL);

    uint32_t sdmaInstance;

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    handle->base    = base;
    handle->channel = (uint8_t)channel;
    handle->bdCount = 1U;
    handle->context = context;
    /* Get the DMA instance number */
    sdmaInstance                        = SDMA_GetInstance(base);
    s_SDMAHandle[sdmaInstance][channel] = handle;

/* Set channel CCB, default is the static buffer descriptor if not use EDMA_InstallBDMemory */
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    s_SDMACCB[sdmaInstance][channel].currentBDAddr =
        MEMORY_ConvertMemoryMapAddress((uint32_t)(&s_SDMABD[sdmaInstance][channel]), kMEMORY_Local2DMA);
    s_SDMACCB[sdmaInstance][channel].baseBDAddr =
        MEMORY_ConvertMemoryMapAddress((uint32_t)(&s_SDMABD[sdmaInstance][channel]), kMEMORY_Local2DMA);
#else
    s_SDMACCB[sdmaInstance][channel].baseBDAddr            = (uint32_t)(&s_SDMABD[sdmaInstance][channel]);
    s_SDMACCB[sdmaInstance][channel].currentBDAddr         = (uint32_t)(&s_SDMABD[sdmaInstance][channel]);
#endif
    /* Enable interrupt */
    (void)EnableIRQ(s_sdmaIRQNumber[sdmaInstance]);
}

void SDMA_InstallBDMemory(sdma_handle_t *handle, sdma_buffer_descriptor_t *BDPool, uint32_t BDCount)
{
    assert((handle != NULL) && (BDPool != NULL) && (BDCount != 0UL));

    uint32_t sdmaInstance = SDMA_GetInstance(handle->base);

    /* Send user defined buffer descrptor pool to handle */
    handle->BDPool = BDPool;

    handle->bdCount = BDCount;

/* Update the CCB contents */
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    s_SDMACCB[sdmaInstance][handle->channel].baseBDAddr =
        MEMORY_ConvertMemoryMapAddress((uint32_t)(handle->BDPool), kMEMORY_Local2DMA);
    s_SDMACCB[sdmaInstance][handle->channel].currentBDAddr =
        MEMORY_ConvertMemoryMapAddress((uint32_t)(handle->BDPool), kMEMORY_Local2DMA);
#else
    s_SDMACCB[sdmaInstance][handle->channel].baseBDAddr    = (uint32_t)(handle->BDPool);
    s_SDMACCB[sdmaInstance][handle->channel].currentBDAddr = (uint32_t)(handle->BDPool);
#endif
}

void SDMA_SetCallback(sdma_handle_t *handle, sdma_callback callback, void *userData)
{
    assert(handle != NULL);

    handle->callback = callback;
    handle->userData = userData;
}

void SDMA_SetMultiFifoConfig(sdma_transfer_config_t *config, uint32_t fifoNums, uint32_t fifoOffset)
{
    assert(config != NULL);

    config->multiFifo.fifoNums   = (uint8_t)fifoNums;
    config->multiFifo.fifoOffset = (uint8_t)fifoOffset;
}

void SDMA_EnableSwDone(SDMAARM_Type *base, sdma_transfer_config_t *config, uint8_t sel, sdma_peripheral_t type)
{
    assert(config != NULL);

    config->swDone.swDoneSel    = sel;
    config->swDone.enableSwDone = true;

    /* enable sw done function */
    if (type == kSDMA_PeripheralMultiFifoPDM)
    {
        base->DONE0_CONFIG |= 0x80U;
    }
}

void SDMA_SetDoneConfig(SDMAARM_Type *base,
                        sdma_transfer_config_t *config,
                        sdma_peripheral_t type,
                        sdma_done_src_t doneSrc)
{
    assert(config != NULL);

    uint32_t doneChannel           = 0U;
    volatile uint32_t *doneAddress = NULL, doneValue = 0U, channelOffset = 0U;

    /* channel number per peripheral */
    switch (type)
    {
        case kSDMA_PeripheralMultiFifoPDM:
            doneChannel = (uint32_t)kSDMA_DoneChannel0;
            doneValue   = base->DONE0_CONFIG;
            doneAddress = &base->DONE0_CONFIG;
            break;
        default:
            doneAddress = NULL;
            break;
    }

    if (NULL != doneAddress)
    {
        if (doneSrc == kSDMA_DoneSrcSW)
        {
            config->swDone.swDoneSel    = 0U;
            config->swDone.enableSwDone = true;
            doneValue |= (1UL << ((doneChannel - channelOffset) * 8U + 7U));
            doneValue &= ~(1UL << ((doneChannel - channelOffset) * 8U + 6U));
        }
        else
        {
            doneValue &= ~(1UL << ((doneChannel - channelOffset) * 8U + 7U));
            doneValue |= (1UL << ((doneChannel - channelOffset) * 8U + 6U));
            doneValue &= ~((uint32_t)SDMAARM_DONE0_CONFIG_CH_SEL0_MASK << ((doneChannel - channelOffset) * 8U));
            doneValue |= SDMAARM_DONE0_CONFIG_CH_SEL0((uint32_t)doneSrc - 1U) << ((doneChannel - channelOffset) * 8U);
        }

        *doneAddress = doneValue;
    }
}

void SDMA_PrepareTransfer(sdma_transfer_config_t *config,
                          uint32_t srcAddr,
                          uint32_t destAddr,
                          uint32_t srcWidth,
                          uint32_t destWidth,
                          uint32_t bytesEachRequest,
                          uint32_t transferSize,
                          uint32_t eventSource,
                          sdma_peripheral_t peripheral,
                          sdma_transfer_type_t type)
{
    assert(config != NULL);
    assert((srcWidth == 1U) || (srcWidth == 2U) || (srcWidth == 3U) || (srcWidth == 4U));
    assert((destWidth == 1U) || (destWidth == 2U) || (destWidth == 3U) || (destWidth == 4U));

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    config->srcAddr  = MEMORY_ConvertMemoryMapAddress(srcAddr, kMEMORY_Local2DMA);
    config->destAddr = MEMORY_ConvertMemoryMapAddress(destAddr, kMEMORY_Local2DMA);
#else
    config->srcAddr                                        = srcAddr;
    config->destAddr                                       = destAddr;
#endif
    config->bytesPerRequest = bytesEachRequest;
    config->transferSzie    = transferSize;
    config->type            = type;

    if (srcWidth == 1U)
    {
        config->srcTransferSize = kSDMA_TransferSize1Bytes;
    }
    else if (srcWidth == 2U)
    {
        config->srcTransferSize = kSDMA_TransferSize2Bytes;
    }
    else if (srcWidth == 3U)
    {
        config->srcTransferSize = kSDMA_TransferSize3Bytes;
    }
    else
    {
        config->srcTransferSize = kSDMA_TransferSize4Bytes;
    }

    if (destWidth == 1U)
    {
        config->destTransferSize = kSDMA_TransferSize1Bytes;
    }
    else if (destWidth == 2U)
    {
        config->destTransferSize = kSDMA_TransferSize2Bytes;
    }
    else if (destWidth == 3U)
    {
        config->destTransferSize = kSDMA_TransferSize3Bytes;
    }
    else
    {
        config->destTransferSize = kSDMA_TransferSize4Bytes;
    }

    switch (type)
    {
        case kSDMA_MemoryToMemory:
            config->scriptAddr          = FSL_FEATURE_SDMA_M2M_ADDR;
            config->isEventIgnore       = true;
            config->isSoftTriggerIgnore = false;
            config->eventSource         = 0;
            break;
        case kSDMA_MemoryToPeripheral:
            config->scriptAddr          = SDMA_GetScriptAddr(peripheral, kSDMA_MemoryToPeripheral);
            config->isEventIgnore       = false;
            config->isSoftTriggerIgnore = true;
            config->eventSource         = eventSource;
            break;
        case kSDMA_PeripheralToMemory:
            config->scriptAddr          = SDMA_GetScriptAddr(peripheral, kSDMA_PeripheralToMemory);
            config->isEventIgnore       = false;
            config->isSoftTriggerIgnore = true;
            config->eventSource         = eventSource;
            break;
        default:
            assert(false);
            break;
    }
}

void SDMA_PrepareP2PTransfer(sdma_transfer_config_t *config,
                             uint32_t srcAddr,
                             uint32_t destAddr,
                             uint32_t srcWidth,
                             uint32_t destWidth,
                             uint32_t bytesEachRequest,
                             uint32_t transferSize,
                             uint32_t eventSource,
                             uint32_t eventSource1,
                             sdma_peripheral_t peripheral,
                             sdma_p2p_config_t *p2p)
{
    assert((config != NULL) && (p2p != NULL));
    assert((srcWidth == 1U) || (srcWidth == 2U) || (srcWidth == 4U));
    assert((destWidth == 1U) || (destWidth == 2U) || (destWidth == 4U));

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
    config->srcAddr  = MEMORY_ConvertMemoryMapAddress(srcAddr, kMEMORY_Local2DMA);
    config->destAddr = MEMORY_ConvertMemoryMapAddress(destAddr, kMEMORY_Local2DMA);
#else
    config->srcAddr                                        = srcAddr;
    config->destAddr                                       = destAddr;
#endif
    config->bytesPerRequest = bytesEachRequest;
    config->transferSzie    = transferSize;
    config->type            = kSDMA_PeripheralToPeripheral;

    if (srcWidth == 1U)
    {
        config->srcTransferSize = kSDMA_TransferSize1Bytes;
    }
    else if (srcWidth == 2U)
    {
        config->srcTransferSize = kSDMA_TransferSize2Bytes;
    }
    else
    {
        config->srcTransferSize = kSDMA_TransferSize4Bytes;
    }

    if (destWidth == 1U)
    {
        config->destTransferSize = kSDMA_TransferSize1Bytes;
    }
    else if (destWidth == 2U)
    {
        config->destTransferSize = kSDMA_TransferSize2Bytes;
    }
    else
    {
        config->destTransferSize = kSDMA_TransferSize4Bytes;
    }

    config->scriptAddr          = SDMA_GetScriptAddr(peripheral, kSDMA_PeripheralToPeripheral);
    config->isEventIgnore       = false;
    config->isSoftTriggerIgnore = true;
    config->eventSource         = eventSource;
    config->eventSource1        = eventSource1;

    if (eventSource1 > 31UL)
    {
        config->watermarkLevel |= SDMA_P2P_HIGHER_EVENT_REG_MASK;
    }

    if (eventSource > 31UL)
    {
        config->watermarkLevel |= SDMA_P2P_LOWER_EVENT_REG_MASK;
    }

    if (SDMA_IsPeripheralInSPBA(srcAddr))
    {
        config->watermarkLevel |= SDMA_P2P_SOURCE_SPBA_MASK;
    }

    if (SDMA_IsPeripheralInSPBA(destAddr))
    {
        config->watermarkLevel |= SDMA_P2P_DEST_SPBA_MASK;
    }

    if (p2p->continuousTransfer)
    {
        config->watermarkLevel |= SDMA_P2P_CONT_MASK;
    }

    if (p2p->sourceWatermark > p2p->destWatermark)
    {
        config->watermarkLevel |=
            SDMA_P2P_LOW_WATERMARK(p2p->destWatermark) | SDMA_P2P_HIGH_WATERMARK(p2p->sourceWatermark);
        config->eventMask0 = (1UL << (config->eventSource % 32U));
        config->eventMask1 = (1UL << (config->eventSource1 % 32U));
    }
    else
    {
        config->watermarkLevel |=
            SDMA_P2P_LOW_WATERMARK(p2p->sourceWatermark) | SDMA_P2P_HIGH_WATERMARK(p2p->destWatermark);
        config->eventMask0 = (1UL << (config->eventSource1 % 32U));
        config->eventMask1 = (1UL << (config->eventSource % 32U));
    }
}

void SDMA_SubmitTransfer(sdma_handle_t *handle, const sdma_transfer_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);

    uint32_t val      = 0U;
    uint32_t instance = SDMA_GetInstance(handle->base);

    handle->eventSource  = config->eventSource;
    handle->eventSource1 = config->eventSource1;

    /* Set event source channel */
    if (config->type != kSDMA_MemoryToMemory)
    {
        val = handle->base->CHNENBL[config->eventSource];
        val |= (1UL << (handle->channel));
        SDMA_SetSourceChannel(handle->base, config->eventSource, val);
        if (config->type == kSDMA_PeripheralToPeripheral)
        {
            val = handle->base->CHNENBL[config->eventSource1];
            val |= (1UL << (handle->channel));
            SDMA_SetSourceChannel(handle->base, config->eventSource1, val);
        }
    }

    /* DO register shall always set */
    handle->base->DSPOVR |= (1UL << handle->channel);

    /* Configure EO bit */
    if (config->isEventIgnore)
    {
        handle->base->EVTOVR |= (1UL << handle->channel);
    }
    else
    {
        handle->base->EVTOVR &= ~(1UL << handle->channel);
    }

    /* Configure HO bits */
    if (config->isSoftTriggerIgnore)
    {
        handle->base->HOSTOVR |= (1UL << handle->channel);
    }
    else
    {
        handle->base->HOSTOVR &= ~(1UL << handle->channel);
    }

    /* If use default buffer descriptor, configure the buffer descriptor */
    if (handle->BDPool == NULL)
    {
        (void)memset(&s_SDMABD[instance][handle->channel], 0, sizeof(sdma_buffer_descriptor_t));
        if (config->type == kSDMA_MemoryToPeripheral)
        {
            SDMA_ConfigBufferDescriptor(&s_SDMABD[instance][handle->channel], config->srcAddr, config->destAddr,
                                        config->destTransferSize, config->transferSzie, true, true, false,
                                        config->type);
        }
        else
        {
            SDMA_ConfigBufferDescriptor(&s_SDMABD[instance][handle->channel], config->srcAddr, config->destAddr,
                                        config->srcTransferSize, config->transferSzie, true, true, false, config->type);
        }
    }

    /*Load the context */
    SDMA_LoadContext(handle, config);
}

void SDMA_StartTransfer(sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Set the channel priority */
    if (handle->priority == 0U)
    {
        handle->priority = (uint8_t)handle->base->SDMA_CHNPRI[handle->channel];
    }

    /* Set priority if regsiter bit is 0*/
    if (handle->base->SDMA_CHNPRI[handle->channel] == 0UL)
    {
        SDMA_SetChannelPriority(handle->base, handle->channel, handle->priority);
    }

    if ((handle->eventSource != 0UL) || (handle->eventSource1 != 0UL))
    {
        SDMA_StartChannelEvents(handle->base, handle->channel);
    }
    else
    {
        SDMA_StartChannelSoftware(handle->base, handle->channel);
    }
}

void SDMA_StopTransfer(sdma_handle_t *handle)
{
    assert(handle != NULL);

    SDMA_StopChannel(handle->base, handle->channel);
}

void SDMA_AbortTransfer(sdma_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t val = 0;

    SDMA_StopTransfer(handle);

    /* Clear the event map. */
    val = handle->base->CHNENBL[handle->eventSource];
    val &= ~(1UL << (handle->channel));
    SDMA_SetSourceChannel(handle->base, handle->eventSource, val);

    if (handle->eventSource1 != 0UL)
    {
        /* Clear the event map. */
        val = handle->base->CHNENBL[handle->eventSource1];
        val &= ~(1UL << (handle->channel));
        SDMA_SetSourceChannel(handle->base, handle->eventSource1, val);
    }

    /* Clear the channel priority */
    SDMA_SetChannelPriority(handle->base, handle->channel, 0);
}

uint32_t SDMA_GetTransferredBytes(sdma_handle_t *handle)
{
    uint32_t instance = SDMA_GetInstance(handle->base);
    uint32_t val      = 0;

    if (handle->BDPool == NULL)
    {
        val = s_SDMABD[instance][handle->channel].count - 1UL;
    }
    else
    {
        val = 0;
    }

    return val;
}

void SDMA_HandleIRQ(sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Set the current BD address to the CCB */
    if (handle->BDPool != NULL)
    {
        /* Set the DONE bits */
        handle->bdIndex                             = (handle->bdIndex + 1U) % handle->bdCount;
        s_SDMACCB[0][handle->channel].currentBDAddr = (uint32_t)(&handle->BDPool[handle->bdIndex]);
    }
    else
    {
        s_SDMACCB[0][handle->channel].currentBDAddr = s_SDMACCB[0][handle->channel].baseBDAddr;
    }

    if (handle->callback != NULL)
    {
        (handle->callback)(handle, handle->userData, true, handle->bdIndex);
    }
}
#if defined(SDMAARM)
void SDMA_DriverIRQHandler(void);
void SDMA_DriverIRQHandler(void)
{
    uint32_t i = 1U, val;

    /* Clear channel 0 */
    SDMA_ClearChannelInterruptStatus(SDMAARM, 1U);
    /* Ignore channel0, as channel0 is only used for download */
    val = (SDMAARM->INTR) >> 1U;
    while (val)
    {
        if ((val & 0x1UL) != 0UL)
        {
            SDMA_ClearChannelInterruptStatus(s_SDMAHandle[0][i]->base, 1UL << i);
            SDMA_HandleIRQ(s_SDMAHandle[0][i]);
        }
        i++;
        val >>= 1U;
    }
}
#endif
#if defined(SDMAARM1)
void SDMA1_DriverIRQHandler(void);
void SDMA1_DriverIRQHandler(void)
{
    uint32_t i = 1U, val;

    /* Clear channel 0 */
    SDMA_ClearChannelInterruptStatus(SDMAARM1, 1U);
    /* Ignore channel0, as channel0 is only used for download */
    val = (SDMAARM1->INTR) >> 1U;
    while (val != 0UL)
    {
        if ((val & 0x1UL) != 0UL)
        {
            SDMA_ClearChannelInterruptStatus(s_SDMAHandle[0][i]->base, 1UL << i);
            SDMA_HandleIRQ(s_SDMAHandle[0][i]);
        }
        i++;
        val >>= 1U;
    }
}
#endif
#if defined(SDMAARM2)
void SDMA2_DriverIRQHandler(void);
void SDMA2_DriverIRQHandler(void)
{
    uint32_t i = 1U, val;

    /* Clear channel 0 */
    SDMA_ClearChannelInterruptStatus(SDMAARM2, 1U);
    /* Ignore channel0, as channel0 is only used for download */
    val = (SDMAARM2->INTR) >> 1U;
    while (val != 0UL)
    {
        if ((val & 0x1UL) != 0UL)
        {
            SDMA_ClearChannelInterruptStatus(s_SDMAHandle[1][i]->base, 1UL << i);
            SDMA_HandleIRQ(s_SDMAHandle[1][i]);
        }
        i++;
        val >>= 1U;
    }
}
#endif

#if defined(SDMAARM3)
void SDMA3_DriverIRQHandler(void);
void SDMA3_DriverIRQHandler(void)
{
    uint32_t i = 1U, val;

    /* Clear channel 0 */
    SDMA_ClearChannelInterruptStatus(SDMAARM3, 1U);
    /* Ignore channel0, as channel0 is only used for download */
    val = (SDMAARM3->INTR) >> 1U;
    while (val != 0UL)
    {
        if ((val & 0x1UL) != 0UL)
        {
            SDMA_ClearChannelInterruptStatus(s_SDMAHandle[2][i]->base, 1UL << i);
            SDMA_HandleIRQ(s_SDMAHandle[2][i]);
        }
        i++;
        val >>= 1U;
    }
}
#endif
