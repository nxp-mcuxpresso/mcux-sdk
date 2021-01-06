/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_edma.h"
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dma3"
#endif

#define EDMA_TRANSFER_ENABLED_MASK 0x80U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for EDMA.
 *
 * @param base EDMA peripheral base address.
 */
static uint32_t EDMA_GetInstance(DMA_Type *base);

/*!
 * @brief Configure tcd contents accroding to the configure.
 *
 * @param handle edma handle pointer.
 * @param channel EDMA channel number.
 * @param config EDMA configure pointer.
 * @param nextTcd Point to next TCD structure if there is.
 */
static void EDMA_HandleTransferConfig(edma_handle_t *handle,
                                      uint32_t channel,
                                      const edma_transfer_config_t *config,
                                      edma_tcd_t *nextTcd);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map EDMA instance number to base pointer. */
static DMA_Type *const s_edmaBases[] = DMA_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if !(defined(FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE) && (FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE))
/*! @brief Array to map EDMA instance number to clock name. */
static const clock_ip_name_t s_edmaClockName[] = EDMA_CLOCKS;
#endif /* FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

static const IRQn_Type s_edmaIRQNumber[][FSL_FEATURE_EDMA_MODULE_CHANNEL] = DMA_IRQS;

/*! @brief Pointers to transfer handle for each EDMA channel. */
static edma_handle_t *s_EDMAHandle[FSL_FEATURE_EDMA_MODULE_CHANNEL * FSL_FEATURE_SOC_EDMA_COUNT];

/*! @brief EDMA enabled channel. */
static bool s_EDMAEnabledChannel[FSL_FEATURE_SOC_EDMA_COUNT][FSL_FEATURE_EDMA_MODULE_CHANNEL];
/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t EDMA_GetInstance(DMA_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_edmaBases); instance++)
    {
        if (s_edmaBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_edmaBases));

    return instance;
}

void EDMA_InstallTCD(DMA_Type *base, uint32_t channel, edma_tcd_t *tcd)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    /* Push tcd into hardware TCD register */
    base->CH[channel].TCD_SADDR          = tcd->SADDR;
    base->CH[channel].TCD_SOFF           = tcd->SOFF;
    base->CH[channel].TCD_ATTR           = tcd->ATTR;
    base->CH[channel].TCD_NBYTES_MLOFFNO = tcd->NBYTES;
    base->CH[channel].TCD_SLAST_SDA      = tcd->SLAST;
    base->CH[channel].TCD_DADDR          = tcd->DADDR;
    base->CH[channel].TCD_DOFF           = tcd->DOFF;
    base->CH[channel].TCD_CITER_ELINKNO  = tcd->CITER;
    base->CH[channel].TCD_DLAST_SGA      = tcd->DLAST_SGA;
    /* Clear DONE bit first, otherwise ESG cannot be set */
    base->CH[channel].TCD_CSR           = 0;
    base->CH[channel].TCD_CSR           = tcd->CSR;
    base->CH[channel].TCD_BITER_ELINKNO = tcd->BITER;
}

static void EDMA_HandleTransferConfig(edma_handle_t *handle,
                                      uint32_t channel,
                                      const edma_transfer_config_t *config,
                                      edma_tcd_t *nextTcd)
{
    assert((handle != NULL) && (config != NULL));

/* If there is address offset, convert the address */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    nextTcd = (edma_tcd_t *)(MEMORY_ConvertMemoryMapAddress((uint32_t)nextTcd, kMEMORY_Local2DMA));
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
    EDMA_SetTransferConfig(handle->base, channel, config, nextTcd);
}

/*!
 * brief Initializes the eDMA peripheral.
 *
 * This function ungates the eDMA clock and configures the eDMA peripheral
 * according
 * to the configuration structure.
 *
 * param base eDMA peripheral base address.
 * param config A pointer to the configuration structure, see "edma_config_t".
 * note This function enables the minor loop map feature.
 */
void EDMA_Init(DMA_Type *base, const edma_config_t *config)
{
    assert(config != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if !(defined(FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE) && (FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE))
    CLOCK_EnableClock(s_edmaClockName[EDMA_GetInstance(base)]);
#endif /* FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE */
#endif /* FSL_FEATURE_EDMA_HAS_CLOCK_GATE */

#if defined(FSL_FEATURE_HAVE_DMA_CONTROL_REGISTER_ACCESS_PERMISSION) && \
    FSL_FEATURE_HAVE_DMA_CONTROL_REGISTER_ACCESS_PERMISSION
    uint32_t tmpreg;
    /* Configure EDMA peripheral according to the configuration structure. */
    tmpreg = base->MP_CSR;
    tmpreg &= ~(DMA_MP_CSR_HAE_MASK | DMA_MP_CSR_ERCA_MASK | DMA_MP_CSR_EDBG_MASK);

    tmpreg = (tmpreg & (~DMA_MP_CSR_GMRC_MASK)) | DMA_MP_CSR_GMRC(config->enableMasterIdReplication);

#if !(defined FSL_FEATURE_EDMA_HAS_NO_MP_CSR_EBW && FSL_FEATURE_EDMA_HAS_NO_MP_CSR_EBW)
    tmpreg = (tmpreg & (~DMA_MP_CSR_EBW_MASK)) | DMA_MP_CSR_EBW(config->enableBufferedWrites);
#endif

    tmpreg |= (DMA_MP_CSR_HAE(config->enableHaltOnError) | DMA_MP_CSR_ERCA(config->enableRoundRobinArbitration) |
               DMA_MP_CSR_EDBG(config->enableDebugMode));

    base->MP_CSR = tmpreg;
    base->MP_CSR &= (~DMA_MP_CSR_HALT_MASK);
#endif /* FSL_FETURE_HAVE_DMA_CONTROL_REGISTER_ACCESS_PERMISSION */
}

/*!
 * brief Deinitializes the eDMA peripheral.
 *
 * This function gates the eDMA clock.
 *
 * param base eDMA peripheral base address.
 */
void EDMA_Deinit(DMA_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if !(defined(FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE) && (FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE))
    /* Gate EDMA periphral clock */
    CLOCK_DisableClock(s_edmaClockName[EDMA_GetInstance(base)]);
#endif /* FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* reset all the enabled channel status */
    (void)memset(s_EDMAEnabledChannel, 0, sizeof(s_EDMAEnabledChannel));
}

/*!
 * brief Gets the eDMA default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values:
 * code
 *   config.enableMasterIdReplication = true;
 *   config.enableHaltOnError = true;
 *   config.enableRoundRobinArbitration = false;
 *   config.enableDebugMode = false;
 *   config.enableBufferedWrites = false;
 * endcode
 *
 * param config A pointer to the eDMA configuration structure.
 */
void EDMA_GetDefaultConfig(edma_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableMasterIdReplication = true;

    config->enableHaltOnError           = true;
    config->enableRoundRobinArbitration = false;
    config->enableDebugMode             = false;

#if !(defined FSL_FEATURE_EDMA_HAS_NO_MP_CSR_EBW && FSL_FEATURE_EDMA_HAS_NO_MP_CSR_EBW)
    config->enableBufferedWrites = false;
#endif
}

/*!
 * brief Sets all TCD registers to default values.
 *
 * This function sets TCD registers for this channel to default values.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * note This function must not be called while the channel transfer is ongoing
 *       or it causes unpredictable results.
 * note This function enables the auto stop request feature.
 */
void EDMA_ResetChannel(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    /* Clear DONE bit and ERR bit */
    base->CH[channel].CH_ES |= DMA_CH_ES_ERR_MASK;
    base->CH[channel].CH_CSR |= DMA_CH_CSR_DONE_MASK;

    /* Reset channel TCD */
    base->CH[channel].TCD_SADDR          = 0U;
    base->CH[channel].TCD_SOFF           = 0U;
    base->CH[channel].TCD_ATTR           = 0U;
    base->CH[channel].TCD_NBYTES_MLOFFNO = 0U;
    base->CH[channel].TCD_SLAST_SDA      = 0U;
    base->CH[channel].TCD_DADDR          = 0U;
    base->CH[channel].TCD_DOFF           = 0U;
    base->CH[channel].TCD_CITER_ELINKNO  = 0U;
    base->CH[channel].TCD_DLAST_SGA      = 0U;
    base->CH[channel].TCD_CSR            = 0U;
    base->CH[channel].TCD_BITER_ELINKNO  = 0U;
}

/*!
 * brief Configures the eDMA transfer attribute.
 *
 * This function configures the transfer attribute, including source address,
 * destination address,
 * transfer size, address offset, and so on. It also configures the scatter
 * gather feature if the
 * user supplies the TCD address.
 * Example:
 * code
 *  edma_transfer_config_t config;
 *  edma_tcd_t tcd;
 *  config.srcAddr = ..;
 *  config.destAddr = ..;
 *  ...
 *  EDMA_SetTransferConfig(DMA0, channel, &config, &stcd);
 * endcode
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param config Pointer to eDMA transfer configuration structure.
 * param nextTcd Point to TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * note If nextTcd is not NULL, it means scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the eDMA_ResetChannel.
 */
void EDMA_SetTransferConfig(DMA_Type *base, uint32_t channel, const edma_transfer_config_t *config, edma_tcd_t *nextTcd)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);
    assert(config != NULL);
    assert(((uint32_t)nextTcd & 0x1FU) == 0U);

    EDMA_TcdSetTransferConfig((edma_tcd_t *)((uint32_t)&base->CH[channel] + 0x00000020U), config, nextTcd);
}

/*!
 * brief Configures the eDMA minor offset feature.
 *
 * The minor offset means that the signed-extended value is added to the source
 * address or destination
 * address after each minor loop.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param config A pointer to the minor offset configuration structure.
 */
void EDMA_SetMinorOffsetConfig(DMA_Type *base, uint32_t channel, const edma_minor_offset_config_t *config)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);
    assert(config != NULL);

    EDMA_TcdSetMinorOffsetConfig((edma_tcd_t *)((uint32_t)&base->CH[channel] + 0x00000020U), config);
}

/*!
 * brief Sets the channel link for the eDMA transfer.
 *
 * This function configures either the minor link or the major link mode. The
 * minor link means that the channel link is
 * triggered every time CITER decreases by 1. The major link means that the
 * channel link is triggered when the CITER is
 * exhausted.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param type A channel link type, which can be one of the following:
 *   arg kEDMA_LinkNone
 *   arg kEDMA_MinorLink
 *   arg kEDMA_MajorLink
 * param linkedChannel The linked channel number.
 * note Users should ensure that DONE flag is cleared before calling this
 * interface, or the configuration is invalid.
 */
void EDMA_SetChannelLink(DMA_Type *base, uint32_t channel, edma_channel_link_type_t type, uint32_t linkedChannel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);
    assert(linkedChannel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    EDMA_TcdSetChannelLink((edma_tcd_t *)((uint32_t)&base->CH[channel] + 0x00000020U), type, linkedChannel);
}

/*!
 * brief Sets the bandwidth for the eDMA transfer.
 *
 * Because the eDMA processes the minor loop, it continuously generates
 * read/write sequences
 * until the minor count is exhausted. The bandwidth forces the eDMA to stall
 * after the completion of
 * each read/write access to control the bus request bandwidth seen by the
 * crossbar switch.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param bandWidth A bandwidth setting, which can be one of the following:
 *     arg kEDMABandwidthStallNone
 *     arg kEDMABandwidthStall4Cycle
 *     arg kEDMABandwidthStall8Cycle
 */
void EDMA_SetBandWidth(DMA_Type *base, uint32_t channel, edma_bandwidth_t bandWidth)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    base->CH[channel].TCD_CSR =
        (uint16_t)((base->CH[channel].TCD_CSR & (~DMA_TCD_CSR_BWC_MASK)) | DMA_TCD_CSR_BWC(bandWidth));
}

/*!
 * brief Sets the source modulo and the destination modulo for the eDMA
 * transfer.
 *
 * This function defines a specific address range specified to be the value
 * after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the
 * ability to implement a circular data
 * queue easily.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param srcModulo A source modulo value.
 * param destModulo A destination modulo value.
 */
void EDMA_SetModulo(DMA_Type *base, uint32_t channel, edma_modulo_t srcModulo, edma_modulo_t destModulo)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    EDMA_TcdSetModulo((edma_tcd_t *)((uint32_t)&base->CH[channel] + 0x00000020U), srcModulo, destModulo);
}

/*!
 * brief Enables the interrupt source for the eDMA transfer.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_EnableChannelInterrupts(DMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    /* Enable error interrupt */
    if ((mask & (uint32_t)kEDMA_ErrorInterruptEnable) != 0U)
    {
        base->CH[channel].CH_CSR = (base->CH[channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) | DMA_CH_CSR_EEI_MASK;
    }

    /* Enable Major interrupt or Half major interrupt */
    else
    {
        EDMA_TcdEnableInterrupts((edma_tcd_t *)((uint32_t)&base->CH[channel] + 0x00000020U), mask);
    }
}

/*!
 * brief Disables the interrupt source for the eDMA transfer.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of the interrupt source to be set. Use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_DisableChannelInterrupts(DMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    /* Disable error interrupt */
    if ((mask & (uint32_t)kEDMA_ErrorInterruptEnable) != 0U)
    {
        base->CH[channel].CH_CSR = (base->CH[channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) & ~DMA_CH_CSR_EEI_MASK;
    }

    /* Disable Major interrupt or Half major interrupt */
    else
    {
        EDMA_TcdDisableInterrupts((edma_tcd_t *)((uint32_t)&base->CH[channel] + 0x00000020U), mask);
    }
}

/*!
 * brief Sets all fields to default values for the TCD structure.
 *
 * This function sets all fields for this TCD structure to default value.
 *
 * param tcd Pointer to the TCD structure.
 * note This function enables the auto stop request feature.
 */
void EDMA_TcdReset(edma_tcd_t *tcd)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    /* Reset channel TCD */
    tcd->SADDR     = 0U;
    tcd->SOFF      = 0U;
    tcd->ATTR      = 0U;
    tcd->NBYTES    = 0U;
    tcd->SLAST     = 0U;
    tcd->DADDR     = 0U;
    tcd->DOFF      = 0U;
    tcd->CITER     = 0U;
    tcd->DLAST_SGA = 0U;
    /* Enable auto disable request feature */
    tcd->CSR   = DMA_TCD_CSR_DREQ(true);
    tcd->BITER = 0U;
}

/*!
 * brief Configures the eDMA TCD transfer attribute.
 *
 * The TCD is a transfer control descriptor. The content of the TCD is the same
 * as the hardware TCD registers.
 * The STCD is used in the scatter-gather mode.
 * This function configures the TCD transfer attribute, including source
 * address, destination address,
 * transfer size, address offset, and so on. It also configures the scatter
 * gather feature if the
 * user supplies the next TCD address.
 * Example:
 * code
 *   edma_transfer_config_t config = {
 *   ...
 *   }
 *   edma_tcd_t tcd __aligned(32);
 *   edma_tcd_t nextTcd __aligned(32);
 *   EDMA_TcdSetTransferConfig(&tcd, &config, &nextTcd);
 * endcode
 *
 * param tcd Pointer to the TCD structure.
 * param config Pointer to eDMA transfer configuration structure.
 * param nextTcd Pointer to the next TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * note TCD address should be 32 bytes aligned or it causes an eDMA error.
 * note If the nextTcd is not NULL, the scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the EDMA_TcdReset.
 */
void EDMA_TcdSetTransferConfig(edma_tcd_t *tcd, const edma_transfer_config_t *config, edma_tcd_t *nextTcd)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);
    assert(config != NULL);
    assert(((uint32_t)nextTcd & 0x1FU) == 0U);
    assert((config->srcAddr % (1UL << (uint32_t)config->srcTransferSize)) == 0U);
    assert((config->destAddr % (1UL << (uint32_t)config->destTransferSize)) == 0U);

/* source address */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    tcd->SADDR = MEMORY_ConvertMemoryMapAddress(config->srcAddr, kMEMORY_Local2DMA);
    /* destination address */
    tcd->DADDR = MEMORY_ConvertMemoryMapAddress(config->destAddr, kMEMORY_Local2DMA);
#else
    tcd->SADDR = config->srcAddr;
    /* destination address */
    tcd->DADDR = config->destAddr;
#endif
    /* Source data and destination data transfer size */
    tcd->ATTR = DMA_TCD_ATTR_SSIZE(config->srcTransferSize) | DMA_TCD_ATTR_DSIZE(config->destTransferSize);
    /* Source address signed offset */
    tcd->SOFF = (uint16_t)config->srcOffset;
    /* Destination address signed offset */
    tcd->DOFF = (uint16_t)config->destOffset;
    /* Minor byte transfer count */
    tcd->NBYTES = config->minorLoopBytes;
    /* Current major iteration count */
    tcd->CITER = (uint16_t)config->majorLoopCounts;
    /* Starting major iteration count */
    tcd->BITER = (uint16_t)config->majorLoopCounts;
    /* Enable scatter/gather processing */
    if (nextTcd != NULL)
    {
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        tcd->DLAST_SGA = MEMORY_ConvertMemoryMapAddress((uint32_t)nextTcd, kMEMORY_Local2DMA);
#else
        tcd->DLAST_SGA = (uint32_t)nextTcd;
#endif
        /*
            Before call EDMA_TcdSetTransferConfig or EDMA_SetTransferConfig,
            user must call EDMA_TcdReset or EDMA_ResetChannel which will set
            DREQ, so must use "|" or "&" rather than "=".

            Clear the DREQ bit because scatter gather has been enabled, so the
            previous transfer is not the last transfer, and channel request should
            be enabled at the next transfer(the next TCD).
        */
        tcd->CSR = (tcd->CSR | (uint16_t)DMA_TCD_CSR_ESG_MASK) & ~(uint16_t)DMA_TCD_CSR_DREQ_MASK;
    }
}

/*!
 * brief Configures the eDMA TCD minor offset feature.
 *
 * A minor offset is a signed-extended value added to the source address or a
 * destination
 * address after each minor loop.
 *
 * param tcd A point to the TCD structure.
 * param config A pointer to the minor offset configuration structure.
 */
void EDMA_TcdSetMinorOffsetConfig(edma_tcd_t *tcd, const edma_minor_offset_config_t *config)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    uint32_t tmpreg;

    tmpreg = tcd->NBYTES;
    tmpreg &=
        ~(DMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK | DMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK | DMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK);
    tmpreg |= (DMA_TCD_NBYTES_MLOFFYES_SMLOE(config->enableSrcMinorOffset) |
               DMA_TCD_NBYTES_MLOFFYES_DMLOE(config->enableDestMinorOffset) |
               DMA_TCD_NBYTES_MLOFFYES_MLOFF(config->minorOffset));
    tcd->NBYTES = tmpreg;
}

/*!
 * brief Sets the channel link for the eDMA TCD.
 *
 * This function configures either a minor link or a major link. The minor link
 * means the channel link is
 * triggered every time CITER decreases by 1. The major link means that the
 * channel link  is triggered when the CITER is
 * exhausted.
 *
 * note Users should ensure that DONE flag is cleared before calling this
 * interface, or the configuration is invalid.
 * param tcd Point to the TCD structure.
 * param type Channel link type, it can be one of:
 *   arg kEDMA_LinkNone
 *   arg kEDMA_MinorLink
 *   arg kEDMA_MajorLink
 * param linkedChannel The linked channel number.
 */
void EDMA_TcdSetChannelLink(edma_tcd_t *tcd, edma_channel_link_type_t type, uint32_t linkedChannel)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);
    assert(linkedChannel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    if (type == kEDMA_MinorLink) /* Minor link config */
    {
        uint16_t tmpreg;

        /* Enable minor link */
        tcd->CITER |= DMA_TCD_CITER_ELINKYES_ELINK_MASK;
        tcd->BITER |= DMA_TCD_BITER_ELINKYES_ELINK_MASK;
        /* Set likned channel */
        tmpreg = tcd->CITER & (~(uint16_t)DMA_TCD_CITER_ELINKYES_LINKCH_MASK);
        tmpreg |= DMA_TCD_CITER_ELINKYES_LINKCH(linkedChannel);
        tcd->CITER = tmpreg;
        tmpreg     = tcd->BITER & (~(uint16_t)DMA_TCD_BITER_ELINKYES_LINKCH_MASK);
        tmpreg |= DMA_TCD_BITER_ELINKYES_LINKCH(linkedChannel);
        tcd->BITER = tmpreg;
    }
    else if (type == kEDMA_MajorLink) /* Major link config */
    {
        uint16_t tmpreg;

        /* Enable major link */
        tcd->CSR |= DMA_TCD_CSR_MAJORELINK_MASK;
        /* Set major linked channel */
        tmpreg   = tcd->CSR & (~(uint16_t)DMA_TCD_CSR_MAJORLINKCH_MASK);
        tcd->CSR = tmpreg | DMA_TCD_CSR_MAJORLINKCH(linkedChannel);
    }
    else /* Link none */
    {
        tcd->CITER &= ~(uint16_t)DMA_TCD_CITER_ELINKYES_ELINK_MASK;
        tcd->BITER &= ~(uint16_t)DMA_TCD_BITER_ELINKYES_ELINK_MASK;
        tcd->CSR &= ~(uint16_t)DMA_TCD_CSR_MAJORELINK_MASK;
    }
}

/*!
 * brief Sets the source modulo and the destination modulo for the eDMA TCD.
 *
 * This function defines a specific address range specified to be the value
 * after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the
 * ability to implement a circular data
 * queue easily.
 *
 * param tcd A pointer to the TCD structure.
 * param srcModulo A source modulo value.
 * param destModulo A destination modulo value.
 */
void EDMA_TcdSetModulo(edma_tcd_t *tcd, edma_modulo_t srcModulo, edma_modulo_t destModulo)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    uint16_t tmpreg;

    tmpreg    = tcd->ATTR & (~(uint16_t)(DMA_TCD_ATTR_SMOD_MASK | DMA_TCD_ATTR_DMOD_MASK));
    tcd->ATTR = tmpreg | DMA_TCD_ATTR_DMOD(destModulo) | DMA_TCD_ATTR_SMOD(srcModulo);
}

/*!
 * brief Enables the interrupt source for the eDMA TCD.
 *
 * param tcd Point to the TCD structure.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdEnableInterrupts(edma_tcd_t *tcd, uint32_t mask)
{
    assert(tcd != NULL);

    /* Enable Major interrupt */
    if ((mask & (uint32_t)kEDMA_MajorInterruptEnable) != 0U)
    {
        tcd->CSR |= DMA_TCD_CSR_INTMAJOR_MASK;
    }

    /* Enable Half major interrupt */
    if ((mask & (uint32_t)kEDMA_HalfInterruptEnable) != 0U)
    {
        tcd->CSR |= DMA_TCD_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Disables the interrupt source for the eDMA TCD.
 *
 * param tcd Point to the TCD structure.
 * param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdDisableInterrupts(edma_tcd_t *tcd, uint32_t mask)
{
    assert(tcd != NULL);

    /* Disable Major interrupt */
    if ((mask & (uint32_t)kEDMA_MajorInterruptEnable) != 0U)
    {
        tcd->CSR &= ~(uint16_t)DMA_TCD_CSR_INTMAJOR_MASK;
    }

    /* Disable Half major interrupt */
    if ((mask & (uint32_t)kEDMA_HalfInterruptEnable) != 0U)
    {
        tcd->CSR &= ~(uint16_t)DMA_TCD_CSR_INTHALF_MASK;
    }
}

/*!
 * brief Gets the Remaining major loop count from the eDMA current channel TCD.
 *
 * This function checks the TCD (Task Control Descriptor) status for a specified
 * eDMA channel and returns the number of major loop count that has not
 * finished.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * return Major loop count which has not been transferred yet for the current
 * TCD.
 * note 1. This function can only be used to get unfinished major loop count of
 * transfer without
 *          the next TCD, or it might be inaccuracy.
 *       2. The unfinished/remaining transfer bytes cannot be obtained directly
 * from registers while
 *          the channel is running.
 *          Because to calculate the remaining bytes, the initial NBYTES
 * configured in DMA_TCDn_NBYTES_MLNO
 *          register is needed while the eDMA IP does not support getting it
 * while a channel is active.
 *          In another word, the NBYTES value reading is always the actual
 * (decrementing) NBYTES value the dma_engine
 *          is working with while a channel is running.
 *          Consequently, to get the remaining transfer bytes, a software-saved
 * initial value of NBYTES (for example
 *          copied before enabling the channel) is needed. The formula to
 * calculate it is shown below:
 *          RemainingBytes = RemainingMajorLoopCount * NBYTES(initially
 * configured)
 */
uint32_t EDMA_GetRemainingMajorLoopCount(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t remainingCount = 0;

    if ((DMA_CH_CSR_DONE_MASK & base->CH[channel].CH_CSR) != 0U)
    {
        remainingCount = 0;
    }
    else
    {
        /* Calculate the unfinished bytes */
        if ((base->CH[channel].TCD_CITER_ELINKNO & DMA_TCD_CITER_ELINKNO_ELINK_MASK) != 0U)
        {
            remainingCount = ((uint32_t)(base->CH[channel].TCD_CITER_ELINKNO) & DMA_TCD_CITER_ELINKYES_CITER_MASK) >>
                             DMA_TCD_CITER_ELINKYES_CITER_SHIFT;
        }
        else
        {
            remainingCount = ((uint32_t)(base->CH[channel].TCD_CITER_ELINKNO) & DMA_TCD_CITER_ELINKNO_CITER_MASK) >>
                             DMA_TCD_CITER_ELINKNO_CITER_SHIFT;
        }
    }

    return remainingCount;
}

/*!
 * brief Gets the eDMA channel status flags.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * return The mask of channel status flags. Users need to use the
 *         _edma_channel_status_flags type to decode the return variables.
 */
uint32_t EDMA_GetChannelStatusFlags(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t retval = 0;

    /* Get DONE bit flag */
    retval |= ((base->CH[channel].CH_CSR & DMA_CH_CSR_DONE_MASK) >> DMA_CH_CSR_DONE_SHIFT);
    /* Get ERROR bit flag */
    retval |= (((base->CH[channel].CH_ES & DMA_CH_ES_ERR_MASK) >> DMA_CH_ES_ERR_SHIFT) << 1U);
    /* Get INT bit flag */
    retval |= (((base->CH[channel].CH_INT & DMA_CH_INT_INT_MASK) >> DMA_CH_INT_INT_SHIFT) << 2U);

    return retval;
}

/*!
 * brief Clears the eDMA channel status flags.
 *
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 * param mask The mask of channel status to be cleared. Users need to use
 *             the defined _edma_channel_status_flags type.
 */
void EDMA_ClearChannelStatusFlags(DMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    /* Clear DONE bit flag */
    if ((mask & (uint32_t)kEDMA_DoneFlag) != 0U)
    {
        base->CH[channel].CH_CSR |= DMA_CH_CSR_DONE_MASK;
    }
    /* Clear ERROR bit flag */
    if ((mask & (uint32_t)kEDMA_ErrorFlag) != 0U)
    {
        base->CH[channel].CH_ES |= DMA_CH_ES_ERR_MASK;
    }
    /* Clear INT bit flag */
    if ((mask & (uint32_t)kEDMA_InterruptFlag) != 0U)
    {
        base->CH[channel].CH_INT |= DMA_CH_INT_INT_MASK;
    }
}

/*!
 * brief Creates the eDMA handle.
 *
 * This function is called if using the transactional API for eDMA. This
 * function
 * initializes the internal state of the eDMA handle.
 *
 * param handle eDMA handle pointer. The eDMA handle stores callback function
 * and
 *               parameters.
 * param base eDMA peripheral base address.
 * param channel eDMA channel number.
 */
void EDMA_CreateHandle(edma_handle_t *handle, DMA_Type *base, uint32_t channel)
{
    assert(handle != NULL);
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL);

    uint32_t edmaInstance;
    uint32_t channelIndex;

    handle->base    = base;
    handle->channel = (uint8_t)channel;
    /* Get the DMA instance number */
    edmaInstance               = EDMA_GetInstance(base);
    channelIndex               = (edmaInstance * (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL) + channel;
    s_EDMAHandle[channelIndex] = handle;
    /* record enabled channel */
    s_EDMAEnabledChannel[edmaInstance][channel] = true;
    /* Enable NVIC interrupt */
    (void)EnableIRQ(s_edmaIRQNumber[edmaInstance][channel]);

    /*
       Reset TCD registers to zero. Unlike the EDMA_TcdReset(DREQ will be set),
       CSR will be 0. Because in order to suit EDMA busy check mechanism in
       EDMA_SubmitTransfer, CSR must be set 0.
    */
    EDMA_ResetChannel(base, channel);
}

/*!
 * brief Installs the TCDs memory pool into the eDMA handle.
 *
 * This function is called after the EDMA_CreateHandle to use scatter/gather
 * feature.
 *
 * param handle eDMA handle pointer.
 * param tcdPool A memory pool to store TCDs. It must be 32 bytes aligned.
 * param tcdSize The number of TCD slots.
 */
void EDMA_InstallTCDMemory(edma_handle_t *handle, edma_tcd_t *tcdPool, uint32_t tcdSize)
{
    assert(handle != NULL);
    assert(((uint32_t)tcdPool & 0x1FU) == 0U);

    /* Initialize tcd queue attibute. */
    handle->header  = 0;
    handle->tail    = 0;
    handle->tcdUsed = 0;
    handle->tcdSize = (int8_t)tcdSize;
    handle->flags   = 0;
    handle->tcdPool = tcdPool;
}

/*!
 * brief Installs a callback function for the eDMA transfer.
 *
 * This callback is called in the eDMA IRQ handler. Use the callback to do
 * something after
 * the current major loop transfer completes.
 *
 * param handle eDMA handle pointer.
 * param callback eDMA callback function pointer.
 * param userData A parameter for the callback function.
 */
void EDMA_SetCallback(edma_handle_t *handle, edma_callback callback, void *userData)
{
    assert(handle != NULL);

    handle->callback = callback;
    handle->userData = userData;
}

/*!
 * brief Prepares the eDMA transfer structure configurations.
 *
 * This function prepares the transfer configuration structure according to the
 * user input.
 *
 * param config The user configuration structure of type edma_transfer_config_t.
 * param srcAddr eDMA transfer source address.
 * param srcWidth eDMA transfer source address width(bytes).
 * param srcOffset eDMA transfer source address offset
 * param destAddr eDMA transfer destination address.
 * param destWidth eDMA transfer destination address width(bytes).
 * param destOffset eDMA transfer destination address offset
 * param bytesEachRequest eDMA transfer bytes per channel request.
 * param transferBytes eDMA transfer bytes to be transferred.
 *
 * note The data address and the data width must be consistent. For example, if
 * the SRC is 4 bytes, the source address must be 4 bytes aligned, or it results
 * in source address error (SAE).
 */
void EDMA_PrepareTransferConfig(edma_transfer_config_t *config,
                                void *srcAddr,
                                uint32_t srcWidth,
                                int16_t srcOffset,
                                void *destAddr,
                                uint32_t destWidth,
                                int16_t destOffset,
                                uint32_t bytesEachRequest,
                                uint32_t transferBytes)
{
    assert(config != NULL);
    assert(srcAddr != NULL);
    assert(destAddr != NULL);
    assert((srcWidth == 1U) || (srcWidth == 2U) || (srcWidth == 4U) || (srcWidth == 8U) || (srcWidth == 16U) ||
           (srcWidth == 32U));
    assert((destWidth == 1U) || (destWidth == 2U) || (destWidth == 4U) || (destWidth == 8U) || (destWidth == 16U) ||
           (destWidth == 32U));
    assert(transferBytes % bytesEachRequest == 0U);
    assert(((uint32_t)(uint32_t *)srcAddr % srcWidth) == 0U);
    assert(((uint32_t)(uint32_t *)destAddr % destWidth) == 0U);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    config->srcAddr  = MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)srcAddr, kMEMORY_Local2DMA);
    config->destAddr = MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)destAddr, kMEMORY_Local2DMA);
#else
    config->destAddr = (uint32_t)destAddr;
    config->srcAddr  = (uint32_t)srcAddr;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

    config->minorLoopBytes  = bytesEachRequest;
    config->majorLoopCounts = transferBytes / bytesEachRequest;
    switch (srcWidth)
    {
        case 1U:
            config->srcTransferSize = kEDMA_TransferSize1Bytes;
            break;
        case 2U:
            config->srcTransferSize = kEDMA_TransferSize2Bytes;
            break;
        case 4U:
            config->srcTransferSize = kEDMA_TransferSize4Bytes;
            break;
        case 8U:
            config->srcTransferSize = kEDMA_TransferSize8Bytes;
            break;
        case 16U:
            config->srcTransferSize = kEDMA_TransferSize16Bytes;
            break;
        case 32U:
            config->srcTransferSize = kEDMA_TransferSize32Bytes;
            break;
        case 64U:
            config->srcTransferSize = kEDMA_TransferSize64Bytes;
            break;
        default:
            assert(false);
            break;
    }
    switch (destWidth)
    {
        case 1U:
            config->destTransferSize = kEDMA_TransferSize1Bytes;
            break;
        case 2U:
            config->destTransferSize = kEDMA_TransferSize2Bytes;
            break;
        case 8U:
            config->destTransferSize = kEDMA_TransferSize8Bytes;
            break;
        case 4U:
            config->destTransferSize = kEDMA_TransferSize4Bytes;
            break;
        case 16U:
            config->destTransferSize = kEDMA_TransferSize16Bytes;
            break;
        case 32U:
            config->destTransferSize = kEDMA_TransferSize32Bytes;
            break;
        case 64U:
            config->destTransferSize = kEDMA_TransferSize64Bytes;
            break;
        default:
            assert(false);
            break;
    }

    config->destOffset = destOffset;
    config->srcOffset  = srcOffset;
}

/*!
 * brief Prepares the eDMA transfer structure.
 *
 * This function prepares the transfer configuration structure according to the
 * user input.
 *
 * param config The user configuration structure of type edma_transfer_config_t.
 * param srcAddr eDMA transfer source address.
 * param srcWidth eDMA transfer source address width(bytes).
 * param destAddr eDMA transfer destination address.
 * param destWidth eDMA transfer destination address width(bytes).
 * param bytesEachRequest eDMA transfer bytes per channel request.
 * param transferBytes eDMA transfer bytes to be transferred.
 * param type eDMA transfer type.
 * note The data address and the data width must be consistent. For example, if
 * the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results
 * in
 *       source address error (SAE).
 */
void EDMA_PrepareTransfer(edma_transfer_config_t *config,
                          void *srcAddr,
                          uint32_t srcWidth,
                          void *destAddr,
                          uint32_t destWidth,
                          uint32_t bytesEachRequest,
                          uint32_t transferBytes,
                          edma_transfer_type_t type)
{
    assert(config != NULL);

    int16_t srcOffset = 0, destOffset = 0;

    switch (type)
    {
        case kEDMA_MemoryToMemory:
            destOffset = (int16_t)destWidth;
            srcOffset  = (int16_t)srcWidth;
            break;
        case kEDMA_MemoryToPeripheral:
            destOffset = 0;
            srcOffset  = (int16_t)srcWidth;
            break;
        case kEDMA_PeripheralToMemory:
            destOffset = (int16_t)destWidth;
            srcOffset  = 0;
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            assert(false);
            break;
    }

    EDMA_PrepareTransferConfig(config, srcAddr, srcWidth, srcOffset, destAddr, destWidth, destOffset, bytesEachRequest,
                               transferBytes);
}

/*!
 * brief Submits the eDMA transfer request.
 *
 * This function submits the eDMA transfer request according to the transfer
 * configuration structure.
 * If submitting the transfer request repeatedly, this function packs an
 * unprocessed request as
 * a TCD and enables scatter/gather feature to process it in the next time.
 *
 * param handle eDMA handle pointer.
 * param config Pointer to eDMA transfer configuration structure.
 * retval kStatus_EDMA_Success It means submit transfer request succeed.
 * retval kStatus_EDMA_QueueFull It means TCD queue is full. Submit transfer
 * request is not allowed.
 * retval kStatus_EDMA_Busy It means the given channel is busy, need to submit
 * request later.
 */
status_t EDMA_SubmitTransfer(edma_handle_t *handle, const edma_transfer_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);

    edma_tcd_t *tcdRegs = (edma_tcd_t *)((uint32_t)&handle->base->CH[handle->channel] + 0x00000020U);

    if (handle->tcdPool == NULL)
    {
        /*
            Check if EDMA is busy: if major loop count is not zero, then the channel is busying transfer
        */
        if (EDMA_GetRemainingMajorLoopCount(handle->base, handle->channel) != 0U)
        {
            return kStatus_EDMA_Busy;
        }
        else
        {
            EDMA_HandleTransferConfig(handle, handle->channel, config, NULL);
            /* Enable auto disable request feature */
            handle->base->CH[handle->channel].TCD_CSR |= DMA_TCD_CSR_DREQ_MASK;
            /* Enable major interrupt */
            handle->base->CH[handle->channel].TCD_CSR |= DMA_TCD_CSR_INTMAJOR_MASK;

            return kStatus_Success;
        }
    }
    else /* Use the TCD queue. */
    {
        uint32_t primask;
        uint16_t csr;
        int8_t currentTcd;
        int8_t previousTcd;
        int8_t nextTcd;
        uint32_t temp = 0;

        /* Check if tcd pool is full. */
        primask = DisableGlobalIRQ();
        if (handle->tcdUsed >= handle->tcdSize)
        {
            EnableGlobalIRQ(primask);

            return kStatus_EDMA_QueueFull;
        }
        currentTcd = handle->tail;
        handle->tcdUsed++;
        /* Calculate index of next TCD */
        nextTcd = currentTcd + 1;
        if (nextTcd == handle->tcdSize)
        {
            nextTcd = 0;
        }
        /* Advance queue tail index */
        handle->tail = nextTcd;
        EnableGlobalIRQ(primask);
        /* Calculate index of previous TCD */
        previousTcd = currentTcd != 0 ? currentTcd - 1 : handle->tcdSize - 1;
        /* Configure current TCD block. */
        EDMA_TcdReset(&handle->tcdPool[currentTcd]);

        EDMA_TcdSetTransferConfig(&handle->tcdPool[currentTcd], config, NULL);
        /* Enable major interrupt */
        handle->tcdPool[currentTcd].CSR |= DMA_TCD_CSR_INTMAJOR_MASK;
/* Link current TCD with next TCD for identification of current TCD */
/* If defined TCM offet, do a offset to the address */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        temp = MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA);
#else
        temp = (uint32_t)&handle->tcdPool[nextTcd];
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        handle->tcdPool[currentTcd].DLAST_SGA = temp;
        /* Chain from previous descriptor unless tcd pool size is 1(this descriptor
         * is its own predecessor). */
        if (currentTcd != previousTcd)
        {
            /* Enable scatter/gather feature in the previous TCD block. */
            csr =
                (handle->tcdPool[previousTcd].CSR | (uint16_t)DMA_TCD_CSR_ESG_MASK) & ~(uint16_t)DMA_TCD_CSR_DREQ_MASK;
            handle->tcdPool[previousTcd].CSR = csr;
/*
    Check if the TCD block in the registers is the previous one (points to
   current TCD block). It
    is used to check if the previous TCD linked has been loaded in TCD register.
   If so, it need to
    link the TCD register in case link the current TCD with the dead chain when
   TCD loading occurs
    before link the previous TCD block.
*/
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            temp = MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[currentTcd], kMEMORY_Local2DMA);
#else
            temp = (uint32_t)&handle->tcdPool[currentTcd];
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
            if (tcdRegs->DLAST_SGA == temp)
            {
                /* Enable scatter/gather also in the TCD registers. */
                csr = (tcdRegs->CSR | (uint16_t)DMA_TCD_CSR_ESG_MASK) & ~(uint16_t)DMA_TCD_CSR_DREQ_MASK;
                /* Must write the CSR register one-time, because the transfer maybe
                 * finished anytime. */
                tcdRegs->CSR = csr;
                /*
                    It is very important to check the ESG bit!
                    Because this hardware design: if DONE bit is set, the ESG bit can
                   not be set. So it can
                    be used to check if the dynamic TCD link operation is successful. If
                   ESG bit is not set
                    and the DLAST_SGA is not the next TCD address(it means the dynamic
                   TCD link succeed and
                    the current TCD block has been loaded into TCD registers), it means
                   transfer finished
                    and TCD link operation fail, so must install TCD content into TCD
                   registers and enable
                    transfer again. And if ESG is set, it means transfer has
                   notfinished, so TCD dynamic
                    link succeed.
                */
                if ((tcdRegs->CSR & DMA_TCD_CSR_ESG_MASK) != 0U)
                {
                    return kStatus_Success;
                }
/*
    Check whether the current TCD block is already loaded in the TCD registers.
   It is another
    condition when ESG bit is not set: it means the dynamic TCD link succeed and
   the current
    TCD block has been loaded into TCD registers.
*/
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                temp = MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA);
#else
                temp = (uint32_t)&handle->tcdPool[nextTcd];
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                if (tcdRegs->DLAST_SGA == temp)
                {
                    return kStatus_Success;
                }
                /*
                    If go to this, means the previous transfer finished, and the DONE
                   bit is set.
                    So shall configure TCD registers.
                */
            }
            else if (tcdRegs->DLAST_SGA != 0U)
            {
                /* The current TCD block has been linked successfully. */
                return kStatus_Success;
            }
            else
            {
                /*
                    DLAST_SGA is 0 and it means the first submit transfer, so shall
                   configure
                    TCD registers.
                */
            }
        }
        /* There is no live chain, TCD block need to be installed in TCD registers.
         */
        EDMA_InstallTCD(handle->base, handle->channel, &handle->tcdPool[currentTcd]);
        /* Enable channel request again. */
        if ((handle->flags & EDMA_TRANSFER_ENABLED_MASK) != 0U)
        {
            handle->base->CH[handle->channel].CH_CSR =
                (handle->base->CH[handle->channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) | DMA_CH_CSR_ERQ_MASK;
        }

        return kStatus_Success;
    }
}

/*!
 * brief eDMA starts transfer.
 *
 * This function enables the channel request. Users can call this function after
 * submitting the transfer request
 * or before submitting the transfer request.
 *
 * param handle eDMA handle pointer.
 */
void EDMA_StartTransfer(edma_handle_t *handle)
{
    assert(handle != NULL);

    if (handle->tcdPool == NULL)
    {
        handle->base->CH[handle->channel].CH_CSR =
            (handle->base->CH[handle->channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) | DMA_CH_CSR_ERQ_MASK;
    }
    else /* Use the TCD queue. */
    {
        uint32_t primask;
        edma_tcd_t *tcdRegs = (edma_tcd_t *)((uint32_t)&handle->base->CH[handle->channel] + 0x00000020U);

        handle->flags |= EDMA_TRANSFER_ENABLED_MASK;

        /* Check if there was at least one descriptor submitted since reset (TCD in
         * registers is valid) */
        if (tcdRegs->DLAST_SGA != 0U)
        {
            primask = DisableGlobalIRQ();
            /* Check if channel request is actually disable. */
            if ((handle->base->CH[handle->channel].CH_CSR & DMA_CH_CSR_ERQ_MASK & (1U << handle->channel)) == 0U)
            {
                /* Check if transfer is paused. */
                if ((!((handle->base->CH[handle->channel].CH_CSR & DMA_CH_CSR_DONE_MASK) != 0U)) ||
                    ((tcdRegs->CSR & DMA_TCD_CSR_ESG_MASK) != 0u))
                {
                    /*
                        Re-enable channel request must be as soon as possible, so must put
                       it into
                        critical section to avoid task switching or interrupt service
                       routine.
                    */
                    handle->base->CH[handle->channel].CH_CSR =
                        (handle->base->CH[handle->channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) | DMA_CH_CSR_ERQ_MASK;
                }
            }
            EnableGlobalIRQ(primask);
        }
    }
}

/*!
 * brief eDMA stops transfer.
 *
 * This function disables the channel request to pause the transfer. Users can
 * call EDMA_StartTransfer()
 * again to resume the transfer.
 *
 * param handle eDMA handle pointer.
 */
void EDMA_StopTransfer(edma_handle_t *handle)
{
    assert(handle != NULL);

    handle->flags &= (uint8_t)(~EDMA_TRANSFER_ENABLED_MASK);
    handle->base->CH[handle->channel].CH_CSR =
        (handle->base->CH[handle->channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) & ~DMA_CH_CSR_ERQ_MASK;
}

/*!
 * brief eDMA aborts transfer.
 *
 * This function disables the channel request and clear transfer status bits.
 * Users can submit another transfer after calling this API.
 *
 * param handle DMA handle pointer.
 */
void EDMA_AbortTransfer(edma_handle_t *handle)
{
    handle->base->CH[handle->channel].CH_CSR =
        (handle->base->CH[handle->channel].CH_CSR & (~DMA_CH_CSR_DONE_MASK)) & ~DMA_CH_CSR_ERQ_MASK;
    /*
        Clear CSR to release channel. Because if the given channel started
       transfer,
        CSR will be not zero. Because if it is the last transfer, DREQ will be
       set.
        If not, ESG will be set.
    */
    handle->base->CH[handle->channel].TCD_CSR = 0;
    /* Cancel all next TCD transfer. */
    handle->base->CH[handle->channel].TCD_DLAST_SGA = 0;
}

/*!
 * brief eDMA IRQ handler for the current major loop transfer completion.
 *
 * This function clears the channel major interrupt flag and calls
 * the callback function if it is not NULL.
 *
 * param handle eDMA handle pointer.
 */
void EDMA_HandleIRQ(edma_handle_t *handle)
{
    assert(handle != NULL);

    bool transfer_done;

    /* Check if transfer is already finished. */
    transfer_done = ((handle->base->CH[handle->channel].CH_CSR & DMA_CH_CSR_DONE_MASK) != 0U);

    /* Clear EDMA interrupt flag */
    handle->base->CH[handle->channel].CH_INT |= DMA_CH_INT_INT_MASK;

    if (handle->tcdPool == NULL)
    {
        if (handle->callback != NULL)
        {
            (handle->callback)(handle, handle->userData, transfer_done, 0);
        }
    }
    else /* Use the TCD queue. */
    {
        uint32_t sga = handle->base->CH[handle->channel].TCD_DLAST_SGA;
        uint32_t sga_index;
        int32_t tcds_done;
        uint8_t new_header;
        uint32_t temp = 0;

/* Get the offset of the current transfer TCD blocks. */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        temp = MEMORY_ConvertMemoryMapAddress((uint32_t)handle->tcdPool, kMEMORY_Local2DMA);
#else
        temp = (uint32_t)handle->tcdPool;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        sga -= temp;
        /* Get the index of the current transfer TCD blocks. */
        sga_index = sga / sizeof(edma_tcd_t);
        /* Adjust header positions. */
        if (transfer_done)
        {
            /* New header shall point to the next TCD (current one is already
             * finished) */
            new_header = (uint8_t)sga_index;
        }
        else
        {
            /* New header shall point to this descriptor (not finished yet) */
            new_header = sga_index != 0U ? (uint8_t)sga_index - 1U : (uint8_t)handle->tcdSize - 1U;
        }
        /* Calculate the number of finished TCDs */
        if (new_header == (uint8_t)handle->header)
        {
            if (handle->tcdUsed == handle->tcdSize)
            {
                tcds_done = handle->tcdUsed;
            }
            else
            {
                /* Internal error occurs. */
                tcds_done = 0;
            }
        }
        else
        {
            tcds_done = (int32_t)new_header - (int32_t)handle->header;
            if (tcds_done < 0)
            {
                tcds_done += handle->tcdSize;
            }
        }
        /* Advance header to the point beyond the last finished TCD block. */
        handle->header = (int8_t)new_header;
        /* Release TCD blocks. */
        handle->tcdUsed -= (int8_t)tcds_done;
        /* Invoke callback function. */
        if (handle->callback != NULL)
        {
            (handle->callback)(handle, handle->userData, transfer_done, tcds_done);
        }

        /* clear the DONE bit here is meaningful for below cases:
         *1.A new TCD has been loaded to EDMA already:
         * need to clear the DONE bit in the IRQ handler to avoid TCD in EDMA been overwritten
         * if peripheral request isn't coming before next transfer request.
         *2.A new TCD has not been loaded to EDMA:
         * for the case that transfer request occur in the privious edma callback, this is a case that doesn't
         * need scatter gather, so keep DONE bit during the next transfer request will re-install the TCD.
         */
        if (transfer_done)
        {
            handle->base->CH[handle->channel].CH_CSR |= DMA_CH_CSR_DONE_MASK;
        }
    }
}

#ifdef DMA0
void DMA0_DriverIRQHandler(void);
void DMA0_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    uint32_t instance    = EDMA_GetInstance(DMA0);
    uint32_t prevChannel = FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = FSL_FEATURE_EDMA_INSTANCE_CHANNELn(DMA0);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(DMA0, i) & kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef ADMA__EDMA0
void ADMA_EDMA0_INT_DriverIRQHandler(void);
void ADMA_EDMA0_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = ADMA__EDMA0;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef ADMA__EDMA1
void ADMA_EDMA1_INT_DriverIRQHandler(void);
void ADMA_EDMA1_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = ADMA__EDMA1;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef ADMA__EDMA2
void ADMA_EDMA2_INT_DriverIRQHandler(void);
void ADMA_EDMA2_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = ADMA__EDMA2;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef ADMA__EDMA3
void ADMA_EDMA3_INT_DriverIRQHandler(void);
void ADMA_EDMA3_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = ADMA__EDMA3;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef AUDIO__EDMA0
void AUDIO_EDMA0_INT_DriverIRQHandler(void);
void AUDIO_EDMA0_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = AUDIO__EDMA0;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif
    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(AUDIO__EDMA0, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef AUDIO__EDMA1
void AUDIO_EDMA1_INT_DriverIRQHandler(void);
void AUDIO_EDMA1_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = AUDIO__EDMA1;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif
    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(AUDIO__EDMA1, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef DMA__EDMA0
void DMA_EDMA0_INT_DriverIRQHandler(void);
void DMA_EDMA0_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = DMA__EDMA0;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif
    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(DMA__EDMA0, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef DMA__EDMA1
void DMA_EDMA1_INT_DriverIRQHandler(void);
void DMA_EDMA1_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = DMA__EDMA1;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif
    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(DMA__EDMA1, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef CONNECTIVITY__EDMA
void CONNECTIVITY__EDMA_INT_DriverIRQHandler(void);
void CONNECTIVITY__EDMA_INT_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = CONNECTIVITY__EDMA;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif
    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }
}
#endif

#ifdef EDMA1
void EDMA1_0_15_DriverIRQHandler(void);
void EDMA1_0_15_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = EDMA1;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate
  overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void EDMA1_16_31_DriverIRQHandler(void);
void EDMA1_16_31_DriverIRQHandler(void)
{
    uint32_t channel     = FSL_FEATURE_EDMA_MODULE_CHANNEL;
    uint32_t i           = 0;
    DMA_Type *base       = EDMA1;
    uint32_t instance    = EDMA_GetInstance(base);
    uint32_t prevChannel = (uint32_t)FSL_FEATURE_EDMA_MODULE_CHANNEL * instance;

#if defined FSL_FEATURE_EDMA_INSTANCE_CHANNELn
    channel = (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base);
#endif

    for (i = 0; i < channel; i++)
    {
        if (s_EDMAEnabledChannel[instance][i])
        {
            if ((EDMA_GetChannelStatusFlags(base, i) & (uint32_t)kEDMA_InterruptFlag) != 0U)
            {
                EDMA_HandleIRQ(s_EDMAHandle[prevChannel + i]);
            }
        }
    }

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate
  overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif
