/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_EDMA_REV2_H_
#define _FSL_EDMA_REV2_H_

#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* flag macros */
#define EDMA_HAS_CH_MUX_FLAG EDMA_BIT(0)
#define EDMA_ALLOWS_128B_TRANSFER_FLAG EDMA_BIT(1)
#define EDMA_HAS_MP_MUX_FLAG EDMA_BIT(2)
#define EDMA_HAS_64BIT_TCD_FLAG EDMA_BIT(3)

/* internal utility macros */
#define EDMA_BIT(x) (1 << (x))

#define EDMA_REGISTER_INDEX_SHIFT 0
#define EDMA_REGISTER_ACCESS_SHIFT 16

#define EDMA_REGISTER_INDEX_MASK 0x0000ffff
#define EDMA_REGISTER_ACCESS_MASK 0xffff0000

#define EDMA_REGISTER_MAKE(index, access)\
    (((index) << EDMA_REGISTER_INDEX_SHIFT) |\
    ((access) << EDMA_REGISTER_ACCESS_SHIFT))

/* register indexes */
#define EDMA_MP_CS_INDEX 0
#define EDMA_MP_ES_INDEX 1
#define EDMA_MP_INT_INDEX 2
#define EDMA_MP_HRS_INDEX 3
#define EDMA_MP_CH_GRPRI_INDEX 4
#define EDMA_TCD_CH_CSR_INDEX 5
#define EDMA_TCD_CH_ES_INDEX 6
#define EDMA_TCD_CH_INT_INDEX 7
#define EDMA_TCD_CH_SBR_INDEX 8
#define EDMA_TCD_CH_PRI_INDEX 9
#define EDMA_TCD_SADDR_INDEX 10
#define EDMA_TCD_SOFF_INDEX 11
#define EDMA_TCD_ATTR_INDEX 12
#define EDMA_TCD_NBYTES_INDEX 13
#define EDMA_TCD_SLAST_SDA_INDEX 14
#define EDMA_TCD_DADDR_INDEX 15
#define EDMA_TCD_DOFF_INDEX 16
#define EDMA_TCD_CITER_INDEX 17
#define EDMA_TCD_DLAST_SGA_INDEX 18
#define EDMA_TCD_CSR_INDEX 19
#define EDMA_TCD_BITER_INDEX 20
#define EDMA_MP_INT_LOW_INDEX 21
#define EDMA_MP_INT_HIGH_INDEX 22
#define EDMA_MP_HRS_LOW_INDEX 23
#define EDMA_MP_HRS_HIGH_INDEX 24
#define EDMA_TCD_CH_MUX_INDEX 25
#define EDMA_TCD_CH_MATTR_INDEX 26
#define EDMA_MP_CH_MUX_INDEX 27
#define EDMA_TCD_SADDR_HIGH_INDEX 28
#define EDMA_TCD_DADDR_HIGH_INDEX 29
#define EDMA_TCD_SLAST_SDA_HIGH_INDEX 30
#define EDMA_TCD_DLAST_SGA_HIGH_INDEX 31

/* utility macros - for external and internal usage */
#define EDMA_HAS_MUX(cfg) ((cfg)->flags & EDMA_HAS_CH_MUX_FLAG)

/* register-related macros */
#define EDMA_TCD_ATTR_SSIZE_DSIZE_MASK 0x3
#define EDMA_TCD_ATTR_DSIZE(x) ((x) & EDMA_TCD_ATTR_SSIZE_DSIZE_MASK)
#define EDMA_TCD_ATTR_SSIZE(x) (((x) & EDMA_TCD_ATTR_SSIZE_DSIZE_MASK) << 8)

#define EDMA_TCD_CITER_ELINKNO_MASK 0xf
#define EDMA_TCD_CITER_ELINKNO(x) ((x) & EDMA_TCD_CITER_ELINKNO_MASK)

#define EDMA_TCD_BITER_ELINKNO_MASK 0xf
#define EDMA_TCD_BITER_ELINKNO(x) ((x) & EDMA_TCD_BITER_ELINKNO_MASK)

#define EDMA_TCD_NBYTES_MLOFFNO_MASK 0x3fffffff
#define EDMA_TCD_NBYTES_MLOFFNO(x) ((x) & EDMA_TCD_NBYTES_MLOFFNO_MASK)

#define EDMA_TCD_CSR_INTHALF_MASK EDMA_BIT(2)
#define EDMA_TCD_CSR_INTMAJOR_MASK EDMA_BIT(1)

#define EDMA_TCD_CH_CSR_ACTIVE_MASK EDMA_BIT(31)
#define EDMA_TCD_CH_CSR_DONE_MASK EDMA_BIT(30)
#define EDMA_TCD_CH_CSR_ERQ_MASK EDMA_BIT(0)

#define EDMA_TCD_CH_INT_MASK BIT(1)

/* EDMA registers */
/* common MP-related registers */
#define EDMA_MP_CS EDMA_REGISTER_MAKE(EDMA_MP_CS_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_ES EDMA_REGISTER_MAKE(EDMA_MP_ES_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_INT EDMA_REGISTER_MAKE(EDMA_MP_INT_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_HRS EDMA_REGISTER_MAKE(EDMA_MP_HRS_INDEX, kEDMA_RegAccess32)
/* TODO: access requires validation */
#define EDMA_MP_CH_GRPRI EDMA_REGISTER_MAKE(EDMA_MP_CH_GRPRI_INDEX, kEDMA_RegAccess32)
/* common TCD-related registers */
#define EDMA_TCD_CH_CSR EDMA_REGISTER_MAKE(EDMA_TCD_CH_CSR_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_CH_ES EDMA_REGISTER_MAKE(EDMA_TCD_CH_ES_INDEX,kEDMA_RegAccess32)
#define EDMA_TCD_CH_INT EDMA_REGISTER_MAKE(EDMA_TCD_CH_INT_INDEX, kEDMA_RegAccess32)
/* TODO: access requires validation */
#define EDMA_TCD_CH_SBR EDMA_REGISTER_MAKE(EDMA_TCD_CH_SBR_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_CH_PRI EDMA_REGISTER_MAKE(EDMA_TCD_CH_PRI_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_SADDR EDMA_REGISTER_MAKE(EDMA_TCD_SADDR_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_SOFF EDMA_REGISTER_MAKE(EDMA_TCD_SOFF_INDEX, kEDMA_RegAccess16)
#define EDMA_TCD_ATTR EDMA_REGISTER_MAKE(EDMA_TCD_ATTR_INDEX, kEDMA_RegAccess16)
#define EDMA_TCD_NBYTES EDMA_REGISTER_MAKE(EDMA_TCD_NBYTES_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_SLAST_SDA EDMA_REGISTER_MAKE(EDMA_TCD_SLAST_SDA_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_DADDR EDMA_REGISTER_MAKE(EDMA_TCD_DADDR_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_DOFF EDMA_REGISTER_MAKE(EDMA_TCD_DOFF_INDEX, kEDMA_RegAccess16)
#define EDMA_TCD_CITER EDMA_REGISTER_MAKE(EDMA_TCD_CITER_INDEX, kEDMA_RegAccess16)
#define EDMA_TCD_DLAST_SGA EDMA_REGISTER_MAKE(EDMA_TCD_DLAST_SGA_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_CSR EDMA_REGISTER_MAKE(EDMA_TCD_CSR_INDEX, kEDMA_RegAccess16)
#define EDMA_TCD_BITER EDMA_REGISTER_MAKE(EDMA_TCD_BITER_INDEX, kEDMA_RegAccess16)
/* non-common MP-related registers */
#define EDMA_MP_INT_LOW EDMA_REGISTER_MAKE(EDMA_MP_INT_LOW_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_INT_HIGH EDMA_REGISTER_MAKE(EDMA_MP_INT_HIGH_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_HRS_LOW EDMA_REGISTER_MAKE(EDMA_MP_HRS_LOW_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_HRS_HIGH EDMA_REGISTER_MAKE(EDMA_MP_HRS_HIGH_INDEX, kEDMA_RegAccess32)
#define EDMA_MP_CH_MUX EDMA_REGISTER_MAKE(EDMA_MP_CH_MUX_INDEX, kEDMA_RegAccess32)
/* non-common TCD-related registers */
#define EDMA_TCD_CH_MUX EDMA_REGISTER_MAKE(EDMA_TCD_CH_MUX_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_CH_MATTR EDMA_REGISTER_MAKE(EDMA_TCD_CH_MATTR_INDEX, kEDMA_RegAccess16)
#define EDMA_TCD_SADDR_HIGH EDMA_REGISTER_MAKE(EDMA_TCD_SADDR_HIGH_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_DADDR_HIGH EDMA_REGISTER_MAKE(EDMA_TCD_DADDR_HIGH_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_SLAST_SDA_HIGH EDMA_REGISTER_MAKE(EDMA_TCD_SLAST_SDA_HIGH_INDEX, kEDMA_RegAccess32)
#define EDMA_TCD_DLAST_SGA_HIGH EDMA_REGISTER_MAKE(EDMA_TCD_DLAST_SGA_HIGH_INDEX, kEDMA_RegAccess32)

enum _edma_status {
    /* Passed configuration is invalid */
    kStatus_EDMA_InvalidConfiguration = MAKE_STATUS(kStatusGroup_EDMA, 0),
};

enum _edma_register_access {
    kEDMA_RegAccess16 = 0, /* register requires 16-bit access */
    kEDMA_RegAccess32, /* register requires 32-bit access */
};

enum _edma_transfer_width {
    kEDMA_TransferWidth1B = 1, /* Transfer width of 1 byte */
    kEDMA_TransferWidth2B = 2, /* Transfer width of 2 bytes */
    kEDMA_TransferWidth4B = 4, /* Transfer width of 4 bytes */
    kEDMA_TransferWidth8B = 8, /* Transfer width of 8 bytes */
    kEDMA_TransferWidth16B = 16, /* Transfer width of 16 bytes */
    kEDMA_TransferWidth32B = 32, /* Transfer width of 32 bytes */
    kEDMA_TransferWidth64B = 64, /* Transfer width of 64 bytes */
    kEDMA_TransferWidth128B = 128, /* Transfer width of 128 bytes */
};

enum _edma_transfer_type {
    kEDMA_TransferTypeM2M = 0, /* Memory to memory transfer */
    kEDMA_TransferTypeM2P, /* Memory to peripheral transfer */
    kEDMA_TransferTypeP2M, /* Peripheral to memory transfer */
};

typedef struct _edma_config {
    /* EDMA base address. Should be overwritten by user if working with virtual
     * addresses.
     */
    uint32_t regmap;
    /* Number of channels the EDMA controller has */
    const uint32_t channels;
    /* Offset from EDMA base at which the channel-related reigsters start */
    const uint32_t channelOffset;
    /* Size of the memory region in which a channel's registers reside (also
     * known as channel strobe). For instance, channel 0's registers reside
     * in region 0x0 - channelWidth, channel 1's registers reside in region
     * channelWidth - channelWidth * 2, etc...
     */
    const uint32_t channelWidth;
    const uint32_t flags;
    /* Array describing the registers supported by the EDMA controller */
    const uint32_t *registerLayout;
} edma_config_t;

/*!
 * @brief Check if a transfer width is valid
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param width transfer width to check
 *
 * @return true if transfer width is valid, false otherwise.
 */
static inline bool EDMA_TransferWidthIsValid(edma_config_t *cfg, uint32_t width)
{
    switch (width) {
    case kEDMA_TransferWidth1B:
    case kEDMA_TransferWidth2B:
    case kEDMA_TransferWidth4B:
    case kEDMA_TransferWidth8B:
    case kEDMA_TransferWidth16B:
    case kEDMA_TransferWidth32B:
    case kEDMA_TransferWidth64B:
        return true;
    case kEDMA_TransferWidth128B:
        if (cfg->flags & EDMA_ALLOWS_128B_TRANSFER_FLAG) {
            return true;
        } else {
            return false;
        }
    default:
        return false;
    }

    return false;
}

/*!
 * @brief Function used to write to a channel's register
 *
 * Use this function whenever you need to write a channel's TCD register.
 * Please note that EDMA_MP_CH_GRPRI should also be written using this
 * function.
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param channel which channel's registers are targeted
 * @param reg which register to write
 * @param value what value to write to the register
 */
void EDMA_ChannelRegWrite(edma_config_t *cfg, int channel, uint32_t reg, uint32_t value);

/*!
 * @brief Function used to read a channel's register
 *
 * Use this function whenever you need to read a channel's TCD register.
 * Please note that EDMA_MP_CH_GRPRI should also be read using this
 * function.
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param channel which channel's registers are targeted
 * @param reg which register to read
 *
 * @return value from the targeted register
 */
uint32_t EDMA_ChannelRegRead(edma_config_t *cfg, int channel, uint32_t reg);

/*!
 * @brief Function use to update a channel's register
 *
 * Use this function whenever you need to update a channel's TCD register.
 * Please note that EDMA_MP_CH_GRPRI should also be updated using this
 * function.
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param channel which channel's registers are targeted
 * @param reg which register to update
 * @param set mask indicating which bits to set
 * @param clear mask inidicating which bits to clear
 */
void EDMA_ChannelRegUpdate(edma_config_t *cfg, int channel, uint32_t reg,
			   uint32_t set, uint32_t clear);

/*!
 * @brief Function used to write the MP registers
 *
 * Use this function whenever you need to write one of the
 * MP registers (EDMA_MP_CH_GRPRI is excluded).
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param reg which register to write
 * @param value what value to write to the register
 */
void EDMA_MPRegWrite(edma_config_t *cfg, uint32_t reg, uint32_t value);

/*!
 * @brief Function used to read the MP registers
 *
 * Use this function whenever you need to read one of the
 * MP registers (EDMA_MP_CH_GRPRI is excluded).
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param reg which register to write
 *
 * @return value from the targeted register
 */
uint32_t EDMA_MPRegRead(edma_config_t *cfg, uint32_t reg);

/*!
 * @brief Function used to set the channel MUX value.
 *
 * Use this function to set the EDMA channel MUX value. Before
 * using this function, the user needs to check if the EDMA
 * version support channel multiplexation via the @EDMA_HAS_MUX
 * macro. The user also needs to check if the channel MUX value is
 * already set otherwise this function will raise an error.
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param channel channel for which we're trying to set the mux value
 * @param mux mux value to set
 *
 * @return kStatus_InvalidArgument one of the passed arguments is invalid
 * @return kStatus_EDMA_InvalidConfiguration the configuration we're trying to
 * set is invalid
 * @return kStatus_Busy mux value is already set to a value != 0
 */
status_t EDMA_SetChannelMux(edma_config_t *cfg, int channel, uint32_t mux);

/*!
 * @brief Function use to prepare an EDMA channel for a transfer
 *
 * @param cfg pointer to targeted EDMA's configuration
 * @param channel channel to configure for the transfer
 * @param saddr source address
 * @param daddr destination address
 * @param ssize source data transfer size
 * @param dsize destination data transfer size
 * @param burstSize number of bytes per transfer
 * @param transferSize total number of bytes to transfer
 * @param transferType type of transfer. May be P2M, M2P, M2M.
 *
 * @return kStatus_InvalidArgument one of the passed arguments is invalid
 * @return kStatus_EDMA_InvalidConfiguration the configuration we're trying
 * to use is invalid
 */
status_t EDMA_ConfigureTransfer(edma_config_t *cfg, int channel,
				uint32_t saddr, uint32_t daddr,
				uint32_t ssize, uint32_t dsize,
				uint32_t burstSize, uint32_t transferSize,
				uint32_t transferType);

#if defined(__cplusplus)
}
#endif
#endif /* _FSL_EDMA_REV2_H_ */
