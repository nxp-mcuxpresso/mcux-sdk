/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdbool.h>

#include "fsl_edma_rev2.h"

#define EDMA_READ(base, access)\
    ((access) == kEDMA_RegAccess16 ?\
    (uint32_t)EDMA_Read16(base) :\
    EDMA_Read32(base))

#define EDMA_WRITE(base, value, access)\
    ((access) == kEDMA_RegAccess16 ?\
    EDMA_Write16(base, (uint16_t)value) :\
    EDMA_Write32(base, value))

#define EDMA_REG_ACCESS(reg)\
    (((reg) & EDMA_REGISTER_ACCESS_MASK) >> EDMA_REGISTER_ACCESS_SHIFT)

#define EDMA_REG_INDEX(reg) ((reg) & EDMA_REGISTER_INDEX_MASK)

static void EDMA_Write32(uint32_t addr, uint32_t value)
{
    *(volatile uint32_t *)(uintptr_t)addr = value;
}

static uint32_t EDMA_Read32(uint32_t addr)
{
    return *(volatile uint32_t *)(uintptr_t)addr;
}

static void EDMA_Write16(uint32_t addr, uint16_t value)
{
    *(volatile uint16_t *)(uintptr_t)addr = value;
}

static uint16_t EDMA_Read16(uint32_t addr)
{
    return *(volatile uint16_t *)(uintptr_t)addr;
}

static uint32_t EDMA_GetChannelBase(edma_config_t *cfg, int channel)
{
    return cfg->regmap + cfg->channelOffset + channel * cfg->channelWidth;
}

static uint32_t EDMA_GetChannelRegBase(edma_config_t *cfg, int channel, uint32_t reg)
{
    uint32_t index = EDMA_REG_INDEX(reg);

    if (reg == EDMA_MP_CH_GRPRI || reg == EDMA_MP_CH_MUX) {
        return cfg->regmap + cfg->registerLayout[index] + channel * 0x4;
    } else {
        return EDMA_GetChannelBase(cfg, channel) + cfg->registerLayout[index];
    }
}

static bool EDMA_TransferTypeIsValid(uint32_t transferType)
{
    switch (transferType) {
    case kEDMA_TransferTypeM2M:
    case kEDMA_TransferTypeM2P:
    case kEDMA_TransferTypeP2M:
        return true;
    default:
        return false;
    }

    return false;
}

void EDMA_ChannelRegWrite(edma_config_t *cfg, int channel, uint32_t reg, uint32_t value)
{
    uint32_t base = EDMA_GetChannelRegBase(cfg, channel, reg);

    EDMA_WRITE(base, value, EDMA_REG_ACCESS(reg));
}

uint32_t EDMA_ChannelRegRead(edma_config_t *cfg, int channel, uint32_t reg)
{
    uint32_t base = EDMA_GetChannelRegBase(cfg, channel, reg);

    return EDMA_READ(base, EDMA_REG_ACCESS(reg));
}

void EDMA_ChannelRegUpdate(edma_config_t *cfg, int channel, uint32_t reg,
			   uint32_t set, uint32_t clear)
{
    uint32_t base, val;

    base = EDMA_GetChannelRegBase(cfg, channel, reg);
    val = EDMA_READ(base, EDMA_REG_ACCESS(reg));

    val &= ~clear;
    val |= set;

    EDMA_WRITE(base, val, EDMA_REG_ACCESS(reg));
}

void EDMA_MPRegWrite(edma_config_t *cfg, uint32_t reg, uint32_t value)
{
    uint32_t base = cfg->regmap + cfg->registerLayout[EDMA_REG_INDEX(reg)];

    EDMA_WRITE(base, value, EDMA_REG_ACCESS(reg));
}

uint32_t EDMA_MPRegRead(edma_config_t *cfg, uint32_t reg)
{
    uint32_t base = cfg->regmap + cfg->registerLayout[EDMA_REG_INDEX(reg)];

    return EDMA_READ(base, EDMA_REG_ACCESS(reg));
}

status_t EDMA_SetChannelMux(edma_config_t *cfg, int channel, uint32_t mux)
{
    uint32_t muxReg;

    if (channel >= cfg->channels) {
        return kStatus_InvalidArgument;
    }

    if (!EDMA_HAS_MUX(cfg)) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (cfg->flags & EDMA_HAS_MP_MUX_FLAG) {
        muxReg = EDMA_MP_CH_MUX;
    } else {
        muxReg = EDMA_TCD_CH_MUX;
    }

    if (EDMA_ChannelRegRead(cfg, channel, muxReg) != 0 && mux != 0) {
        return kStatus_Busy;
    }

    EDMA_ChannelRegWrite(cfg, channel, muxReg, mux);

    return kStatus_Success;
}

static uint32_t EDMA_ConvertTransferWidth(uint32_t width)
{
    switch (width) {
    case kEDMA_TransferWidth1B:
        return 0;
    case kEDMA_TransferWidth2B:
        return 1;
    case kEDMA_TransferWidth4B:
        return 2;
    case kEDMA_TransferWidth8B:
        return 3;
    case kEDMA_TransferWidth16B:
        return 4;
    case kEDMA_TransferWidth32B:
        return 5;
    case kEDMA_TransferWidth64B:
        return 6;
    case kEDMA_TransferWidth128B:
        return 7;
    default:
        return 0;
	}

    return 0;
}

status_t EDMA_ConfigureTransfer(edma_config_t *cfg, int channel,
				uint32_t saddr, uint32_t daddr,
				uint32_t ssize, uint32_t dsize,
				uint32_t burstSize, uint32_t transferSize,
				uint32_t transferType)
{
    uint32_t attr, biter, soff, doff;

    /* check if configuration is valid */
    if (!saddr || !daddr) {
        return kStatus_InvalidArgument;
    }

    if (transferSize % burstSize) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (!EDMA_TransferWidthIsValid(cfg, ssize)) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (!EDMA_TransferWidthIsValid(cfg, dsize)) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (channel >= cfg->channels) {
        return kStatus_InvalidArgument;
    }

    if (saddr % ssize) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (daddr % dsize) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (burstSize % ssize) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (burstSize % dsize) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    if (!EDMA_TransferTypeIsValid(transferType)) {
        return kStatus_EDMA_InvalidConfiguration;
    }

    soff = ssize;
    doff = dsize;

    /* convert SSIZE and DSIZE to the format we can write to EDMA ATTR */
    ssize = EDMA_ConvertTransferWidth(ssize);
    dsize = EDMA_ConvertTransferWidth(dsize);

    attr = EDMA_TCD_ATTR_SSIZE(ssize) | EDMA_TCD_ATTR_DSIZE(dsize);
    biter = transferSize / burstSize;

    switch (transferType) {
    case kEDMA_TransferTypeM2P:
        doff = 0;
        break;
    case kEDMA_TransferTypeP2M:
        soff = 0;
        break;
    }

    /* notes:
     * 1) SOFF and DOFF are currently set to SSIZE and DSIZE.
     * 2) channel linking is not currently supported.
     */
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_SADDR, saddr);
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_DADDR, daddr);
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_ATTR, attr);
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_SOFF, soff);
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_DOFF, doff);
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_CITER, EDMA_TCD_CITER_ELINKNO(biter));
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_BITER, EDMA_TCD_BITER_ELINKNO(biter));
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_NBYTES, EDMA_TCD_NBYTES_MLOFFNO(burstSize));

    if (cfg->flags & EDMA_HAS_64BIT_TCD_FLAG) {
        /* EDMA version has 64-bit TCD but 64-bit addresses are not currently
         * supported by the API. Pad higher 32 bits with 0s.
         */
        EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_SADDR_HIGH, 0x0);
        EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_DADDR_HIGH, 0x0);
    }

    /* clean registers to make sure there's no leftover config */
    EDMA_ChannelRegWrite(cfg, channel, EDMA_TCD_CSR, 0);

    return kStatus_Success;
}
