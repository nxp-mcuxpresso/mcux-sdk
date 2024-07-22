/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_FLEXSPI_FOLLOWER_H_
#define __FSL_FLEXSPI_FOLLOWER_H_

#include <stddef.h>
#include "fsl_device_registers.h"
#include "fsl_common.h"

/*!
 * @addtogroup flexspi_flr
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief FLEXSPI FOLLOWER driver version. */
#define FSL_FLEXSPI_SLV_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

#define FSL_FEATURE_FLEXSPI_SLV_AXI_RX_BUFFER_SIZE (2*1024)
#define FSL_FEATURE_FLEXSPI_SLV_AXI_TX_BUFFER_SIZE (1024)

#define FLEXSPI_SLV_MAILBOX_CMD(x)     ((x) & 0xFFFFFFFE)
#define FLEXSPI_SLV_MAILBOX_CMD_INT(x) ((x) | 0x1)

#define FLEXSPI_SLV_CMD_DDR(x)         (((x) << 8) | (x))

/*! @brief IO mode enumeration of FLEXSPI FOLLOWER.*/
enum
{
    kFLEXSPI_SLV_IOMODE_SDRx4 = 0,
    kFLEXSPI_SLV_IOMODE_SDRx8 = 1,
    kFLEXSPI_SLV_IOMODE_DDRx4 = 2,
    kFLEXSPI_SLV_IOMODE_DDRx8 = 3
};

/*! @brief Clock frequency enumeration of FLEXSPI FOLLOWER.*/
enum
{
    RootClock_50M   = 50,
    RootClock_66M   = 66,
    RootClock_80M   = 80,
    RootClock_100M  = 100,
    RootClock_133M  = 133,
    RootClock_166M  = 166,
    RootClock_200M  = 200,
    RootClock_400M  = 400,
};

/*! @brief The read fetch size enumeration of FLEXSPI FOLLOWER.*/
enum
{
    Read_Fetch_256Bytes   = 0,
    Read_Fetch_512Bytes   = 1,
    Read_Fetch_1KBytes    = 2,
    Read_Fetch_2KBytes    = 3
};

/*! @brief Clock frequency enumeration of FLEXSPI FOLLOWER.*/
enum
{
    Write_Watermark_32Bytes   = 0,
    Write_Watermark_64Bytes   = 1,
    Write_Watermark_128Bytes  = 2,
    Write_Watermark_256Bytes  = 3
};

/*! @brief Interrupt status flags of FLEXSPI FOLLOWER.*/
enum
{
    kFLEXSPI_SLV_Mail0InterruptFlag   = 0, /*!< Mailbox0 interrupt */
    kFLEXSPI_SLV_Mail1InterruptFlag   = 1, /*!< Mailbox1 interrupt */
    kFLEXSPI_SLV_Mail2InterruptFlag   = 2, /*!< Mailbox2 interrupt */
    kFLEXSPI_SLV_Mail3InterruptFlag   = 3, /*!< Mailbox3 interrupt */
    kFLEXSPI_SLV_Mail4InterruptFlag   = 4, /*!< Mailbox4 interrupt */
    kFLEXSPI_SLV_Mail5InterruptFlag   = 5, /*!< Mailbox5 interrupt */
    kFLEXSPI_SLV_Mail6InterruptFlag   = 6, /*!< Mailbox6 interrupt */
    kFLEXSPI_SLV_Mail7InterruptFlag   = 7, /*!< Mailbox7 interrupt */
    kFLEXSPI_SLV_Mail8InterruptFlag   = 8, /*!< Mailbox8 interrupt */
    kFLEXSPI_SLV_WriteOverflowFlag    = 9, /*!< An IO RX FIFO overflow occurred during
                                                command/address/write data phase */
    kFLEXSPI_SLV_ReadUnderflowFlag    = 10, /*!< IO TX FIFO underflow has occurred
                                                 during a read command */
    kFLEXSPI_SLV_ErrorCommandFlag     = 11, /*!< An unknown command has been received
                                                 from the SPI bus */
    kFLEXSPI_SLV_InvalidInterruptFlag = 12,
};

/*! @brief FLEXSPI FOLLOWER configuration structure. */
typedef struct _flexspi_slv_config
{
    int         clock_freq;
    uint32_t    baseAddr1;    /*!< Read/Write CMD1 Base Address. */
    uint32_t    baseAddr2;    /*!< Read/Write CMD2 Base Address. */
    uint32_t    addrRange1;   /*!< Read/Write CMD1 Addr Range. */
    uint32_t    addrRange2;   /*!< Read/Write CMD2 Addr Range. */
    uint8_t     io_mode;      /*!< IO mode control - SDRx4, SDRx8, DDRx4, DDRx8*/
    uint8_t     rxFetch_size; /*!< Specifies the maximum read size triggered by a single read command. */
    uint8_t     rxWatermark;  /*!< Triggers a new AXI read to fetch more data through the IP AXI header. */
    uint8_t     txWatermark;  /*!< Specifies the watermark value. During the write command, if pending
                                write data equals or exceeds the watermark level, it triggers a new AXI write. */
} flexspi_slv_config_t;

/* Forward declaration of the handle typedef. */
typedef struct _flexspi_slv_handle flexspi_slv_handle_t;

/*! @brief FLEXSPI FOLLOWER interrupt callback function. */
typedef void (*flexspi_slv_interrupt_callback_t)(FLEXSPI_SLV_Type *base,
                                            flexspi_slv_handle_t *handle);

/*! @brief Interrupt handle structure for FLEXSPI FOLLOWER. */
struct _flexspi_slv_handle
{
    uint32_t state;                            /*!< Interrupt state for FLEXSPI FOLLOWER */
    flexspi_slv_interrupt_callback_t callback; /*!< Callback for users while mailbox received or error occurred */
    void *userData;                            /*!< FLEXSPI FOLLOWER callback function parameter.*/
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus. */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Get the instance number for FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER base pointer.
 */
uint32_t FLEXSPI_SLV_GetInstance(FLEXSPI_SLV_Type *base);

/*!
 * @brief Check and clear interrupt flags.
 *
 * @param base FLEXSPI FOLLOWER base pointer.
 * @return Interrupt flag.
 */
uint32_t FLEXSPI_SLV_CheckAndClearInterrupt(FLEXSPI_SLV_Type *base);

/*!
 * @brief Initializes the FLEXSPI FOLLOWER module and internal state.
 *
 * This function enables the clock for FLEXSPI FOLLOWER and also configures the FLEXSPI FOLLOWER
 * with the input configure parameters. Users should call this function before any FLEXSPI
 * FOLLOWER operations.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param config FLEXSPI FOLLOWER configure structure.
 */
void FLEXSPI_SLV_Init(FLEXSPI_SLV_Type *base, const flexspi_slv_config_t *config);

/*!
 * @brief Gets default settings for FLEXSPI FOLLOWER.
 *
 * @param config FLEXSPI FOLLOWER configuration structure.
 */
void FLEXSPI_SLV_GetDefaultConfig(flexspi_slv_config_t *config);

/*!
 * @brief Deinitializes the FLEXSPI FOLLOWER module.
 *
 * Clears the FLEXSPI FOLLOWER state and FLEXSPI FOLLOWER module registers.
 * @param base FLEXSPI FOLLOWER peripheral base address.
 */
void FLEXSPI_SLV_Deinit(FLEXSPI_SLV_Type *base);

/*!
 * @brief Software reset for the FLEXSPI FOLLOWER logic.
 *
 * This function sets the software reset flags for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val 0(Finished) or 1(Initiate)
 */
static inline void FLEXSPI_SLV_SoftwareReset_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->MODULE_CONTROL &= ~FLEXSPI_SLV_MODULE_CONTROL_SWRESET_MASK;
    base->MODULE_CONTROL |= FLEXSPI_SLV_MODULE_CONTROL_SWRESET(val);
}

/*!
 * @brief Set IO mode for the FLEXSPI FOLLOWER module.
 *
 * This function sets the IO mode flags for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val Set IO Mode for FLEXSPI FOLLOWER
 */
static inline void FLEXSPI_SLV_IOMode_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->MODULE_CONTROL &= ~FLEXSPI_SLV_MODULE_CONTROL_IOMODE_MASK;
    base->MODULE_CONTROL |= FLEXSPI_SLV_MODULE_CONTROL_IOMODE(val);
}

/*!
 * @brief Update RW CMD base address and range value for the FLEXSPI FOLLOWER module.
 *
 * This function updates RW CMD base address and range value for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 */
static inline void FLEXSPI_SLV_Update_RWCMD_Base_Range(FLEXSPI_SLV_Type *base)
{
    base->MODULE_CONTROL |= FLEXSPI_SLV_MODULE_CONTROL_CMDRANGEBASEUPDATE_MASK;
}

/*!
 * @brief Set RW command base address1 for the FLEXSPI FOLLOWER module.
 *
 * This function sets the RW command base address1 for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val The high 16-bit base address of the RW command
 */
static inline void FLEXSPI_SLV_RW_CMD_BaseAddr1_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->RW_COMMAND_BASE &= ~FLEXSPI_SLV_RW_COMMAND_BASE_ADDRBASE1_MASK;
    base->RW_COMMAND_BASE |= FLEXSPI_SLV_RW_COMMAND_BASE_ADDRBASE1(val);
}

/*!
 * @brief Set RW command base address2 for the FLEXSPI FOLLOWER module.
 *
 * This function sets the RW command base address2 for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val The high 16-bit base address of the RW command
 */
static inline void FLEXSPI_SLV_RW_CMD_BaseAddr2_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->RW_COMMAND_BASE &= ~FLEXSPI_SLV_RW_COMMAND_BASE_ADDRBASE2_MASK;
    base->RW_COMMAND_BASE |= FLEXSPI_SLV_RW_COMMAND_BASE_ADDRBASE2(val);
}

/*!
 * @brief Set address1/2 range for the FLEXSPI FOLLOWER module.
 *
 * This function sets the address1/2 range for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param i The index of RW command, 0 or 1.
 * @param val The size of the memory range in 1KB units.
 */
static inline void FLEXSPI_SLV_AddrRange_SetVal(FLEXSPI_SLV_Type *base, uint32_t i, uint32_t val)
{
    base->CMD_RANGE[i] = FLEXSPI_SLV_CMD_RANGE_RANGE(val);
}

/*!
 * @brief Enable or disable read water mark  for the FLEXSPI FOLLOWER module.
 *
 * This function enables or disables read water mark for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val 0(Disable) or 1(Enable)
 */
static inline void FLEXSPI_SLV_Read_WMEN_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->READ_COMMAND_CONTROL &= ~FLEXSPI_SLV_READ_COMMAND_CONTROL_WMEN_MASK;
    base->READ_COMMAND_CONTROL |= FLEXSPI_SLV_READ_COMMAND_CONTROL_WMEN(val);
}

/*!
 * @brief Set read water mark level for the FLEXSPI FOLLOWER module.
 *
 * This function sets read water mark level for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val Read watermark level in bytes
 */
static inline void FLEXSPI_SLV_Read_RDWM_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->READ_COMMAND_CONTROL &= ~FLEXSPI_SLV_READ_COMMAND_CONTROL_RDWM_MASK;
    base->READ_COMMAND_CONTROL |= FLEXSPI_SLV_READ_COMMAND_CONTROL_RDWM(val);
}

/*!
 * @brief Sets the maximum read size triggered by a single read command.
 *
 * This function sets the maximum read size for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val The maximum read size
 */
static inline void FLEXSPI_SLV_Read_FetchSizeSet(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->READ_COMMAND_CONTROL &= ~FLEXSPI_SLV_READ_COMMAND_CONTROL_RDFETCHSIZE_MASK;
    base->READ_COMMAND_CONTROL |= FLEXSPI_SLV_READ_COMMAND_CONTROL_RDFETCHSIZE(val);
}

/*!
 * @brief Gets the maximum read size triggered by a single read command.
 *
 * This function gets the maximum read size for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @return The maximum read size 
 */
static inline uint32_t FLEXSPI_SLV_Read_FetchSizeGet(FLEXSPI_SLV_Type *base)
{
    uint32_t regBitVal = base->READ_COMMAND_CONTROL & FLEXSPI_SLV_READ_COMMAND_CONTROL_RDFETCHSIZE_MASK;

    return (regBitVal >> FLEXSPI_SLV_READ_COMMAND_CONTROL_RDFETCHSIZE_SHIFT);
}

/*!
 * @brief Set write water mark level for the FLEXSPI FOLLOWER module.
 *
 * This function sets write water mark level for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val Write watermark level
 */
static inline void FLEXSPI_SLV_Write_WRWM_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->WRITE_COMMAND_CONTROL &= ~FLEXSPI_SLV_WRITE_COMMAND_CONTROL_WRWM_MASK;
    base->WRITE_COMMAND_CONTROL |= FLEXSPI_SLV_WRITE_COMMAND_CONTROL_WRWM(val);
}

/*!
 * @brief Set CS mask value for the FLEXSPI FOLLOWER module.
 *
 * This function sets CS mask value for the FLEXSPI FOLLOWER.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param val 0(Not masked) or 1(Masked)
 */
static inline void FLEXSPI_SLV_CSMASK_SetVal(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->MODULE_CONTROL &= ~FLEXSPI_SLV_MODULE_CONTROL_CSMASK_MASK;
    base->MODULE_CONTROL |= FLEXSPI_SLV_MODULE_CONTROL_CSMASK(val);
}
/* @} */

/*!
 * @name Interrupts
 * @{
 */
/*!
 * @brief Enables the FLEXSPI FOLLOWER interrupts.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param mask FLEXSPI FOLLOWER interrupt source.
 */
static inline void FLEXSPI_SLV_EnableInterrupts(FLEXSPI_SLV_Type *base, uint32_t mask)
{
    base->MODULE_INTEN |= mask;
}

/*!
 * @brief Disable the FLEXSPI FOLLOWER interrupts.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param mask FLEXSPI FOLLOWER interrupt source.
 */
static inline void FLEXSPI_SLV_DisableInterrupts(FLEXSPI_SLV_Type *base, uint32_t mask)
{
    base->MODULE_INTEN &= ~mask;
}

/*!
 * @brief Get the FLEXSPI FOLLOWER enabled interrupts.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 */
static inline uint32_t FLEXSPI_SLV_GetEnabledInterrupts(FLEXSPI_SLV_Type *base)
{
    return (base->MODULE_INTEN);
}

/*!
 * @brief Enable the FLEXSPI FOLLOWER mailbox interrupts.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param enable Whether enable the mailbox interrupt.
 */
static inline void FLEXSPI_SLV_EnableMailInterrupt(FLEXSPI_SLV_Type *base, bool enable)
{
    base->SPI_MAIL_CTRL = FLEXSPI_SLV_SPI_MAIL_CTRL_SPIINTEN(enable ? 1 : 0);
}

/*!
 * @brief Return whether the FLEXSPI FOLLOWER enables the mailbox interrupt.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 */
static inline bool FLEXSPI_SLV_GetEnabledMailInterrupt(FLEXSPI_SLV_Type *base)
{
    return ((base->SPI_MAIL_CTRL & FLEXSPI_SLV_SPI_MAIL_CTRL_SPIINTEN_MASK) ? true : false);
}
/* @} */

/*!
 * @brief Gets the SPI leader read/write out-of-allowed-range count.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param[out] rdCount Pointer through which the current number in the read out-of-allowed-range counter is returned.
 *      Pass NULL if this value is not required.
 * @param[out] wrCount Pointer through which the current number in the write out-of-allowed-range counter is returned
 *      Pass NULL if this value is not required.
 */
static inline void FLEXSPI_SLV_GetOutOfRangeCounts(FLEXSPI_SLV_Type *base, size_t *rdCount, size_t *wrCount)
{
    if (NULL != rdCount)
    {
        *rdCount = ((base->MODULE_STATUS) & FLEXSPI_SLV_MODULE_STATUS_RDOFR_MASK) >> FLEXSPI_SLV_MODULE_STATUS_RDOFR_SHIFT;
    }
    if (NULL != wrCount)
    {
        *wrCount = ((base->MODULE_STATUS) & FLEXSPI_SLV_MODULE_STATUS_WROFR_MASK) >> FLEXSPI_SLV_MODULE_STATUS_WROFR_SHIFT;
    }
}

/*!
 * @name Status
 * @{
 */
/*!
 * @brief Get the FLEXSPI FOLLOWER interrupt status flags.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @retval Interrupt status flag, use status flag to AND the bit mask could get the related status.
 */
static inline uint32_t FLEXSPI_SLV_GetInterruptStatusFlags(FLEXSPI_SLV_Type *base)
{
    return (base->MODULE_INT);
}

/*!
 * @brief Get the FLEXSPI FOLLOWER mailbox interrupt register.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @return Return the index of the FLEXSPI FOLLOWER mail interrupt register
 */
static inline uint32_t FLEXSPI_SLV_GetMailInterruptIndex(FLEXSPI_SLV_Type *base)
{
    uint32_t index;

    for (index = 0; index < FLEXSPI_SLV_SPIMAIL_COUNT; index++)
    {
        if (base->SPIMAIL[index] & 0x1U)
        {
            break;
        }
    }
    return index;
}

/*!
 * @brief Get the FLEXSPI FOLLOWER mailbox data.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param index The index of the mail interrupt register
 * @return Return the FLEXSPI FOLLOWER mailbox data
 */
static inline uint32_t FLEXSPI_SLV_GetMailboxData(FLEXSPI_SLV_Type *base, uint32_t index)
{
    return ((index < FLEXSPI_SLV_SPIMAIL_COUNT) ? base->SPIMAIL[index] : 0U);
}

/*!
 * @brief Clear the FLEXSPI FOLLOWER interrupt status flags.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param mask FLEXSPI FOLLOWER interrupt source.
 */
static inline void FLEXSPI_SLV_ClearInterruptStatusFlags(FLEXSPI_SLV_Type *base, uint32_t mask)
{
    base->MODULE_INT |= mask;
}

/*!
 * @brief Clear the FLEXSPI FOLLOWER mailbox interrupt flag.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 */
static inline void FLEXSPI_SLV_ClearMailInterruptFlag(FLEXSPI_SLV_Type *base)
{
    base->SPI_MAIL_CTRL |= FLEXSPI_SLV_SPI_MAIL_CTRL_CLRINT_MASK;
}

/*! @brief Returns whether the current AXI write leader is busy with a write command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @retval true The current AXI write leader is busy.
 * @retval false The current AXI write leader is not busy.
 */
static inline bool FLEXSPI_SLV_GetAXIWriteBusyStatus(FLEXSPI_SLV_Type *base)
{
    return ((base->MODULE_STATUS & FLEXSPI_SLV_MODULE_STATUS_WIP_MASK) ? true : false);
}

/*! @brief Returns whether the AXI read leader is busy with a read request or else idle with no pending
 *         AXI read request.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @retval true The current AXI read leader is idle.
 * @retval false The current AXI read leader is busy.
 */
static inline bool FLEXSPI_SLV_GetAXIReadIdleStatus(FLEXSPI_SLV_Type *base)
{
    return ((base->MODULE_STATUS & FLEXSPI_SLV_MODULE_STATUS_AXIREADIDLE_MASK) ? true : false);
}

/*! @brief Returns whether the SPI to read/write register queue is idle.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @retval true The SPI to read/write register queue is idle.
 * @retval false The SPI to read/write register queue is busy.
 */
static inline bool FLEXSPI_SLV_GetRegReadWriteIdleStatus(FLEXSPI_SLV_Type *base)
{
    return ((base->MODULE_STATUS & FLEXSPI_SLV_MODULE_STATUS_REGRWIDLE_MASK) ? true : false);
}

/*! @brief Returns whether the SEQ control logic is idle or else busy with an ongoing SPI request.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @retval true The SEQ control logic is idle.
 * @retval false The SEQ control logic is busy.
 */
static inline bool FLEXSPI_SLV_GetSEQIdleStatus(FLEXSPI_SLV_Type *base)
{
    return ((base->MODULE_STATUS & FLEXSPI_SLV_MODULE_STATUS_SEQIDLE_MASK) ? true : false);
}

/*! @brief Returns whether the FLEXSPI FOLLOWER module is busy.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @retval true The SEQ control logic is busy.
 * @retval false The SEQ control logic is idle.
 */
static inline bool FLEXSPI_SLV_GetModuleBusyStatus(FLEXSPI_SLV_Type *base)
{
    uint32_t statusMasks = 0, idleFlags = 0;

    statusMasks = FLEXSPI_SLV_MODULE_STATUS_WIP_MASK |
                  FLEXSPI_SLV_MODULE_STATUS_AXIREADIDLE_MASK |
                  FLEXSPI_SLV_MODULE_STATUS_REGRWIDLE_MASK |
                  FLEXSPI_SLV_MODULE_STATUS_SEQIDLE_MASK;

    idleFlags = FLEXSPI_SLV_MODULE_STATUS_WIP(0) |
                FLEXSPI_SLV_MODULE_STATUS_AXIREADIDLE(1) |
                FLEXSPI_SLV_MODULE_STATUS_REGRWIDLE(1) |
                FLEXSPI_SLV_MODULE_STATUS_SEQIDLE(1);

    return (((base->MODULE_STATUS & statusMasks) != idleFlags) ? true : false);
}
/*@}*/

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Sets the read memory command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param i The read command setting register index
 * @param val The read command value.
 */
static inline void FLEXSPI_SLV_Read_CommandSet(FLEXSPI_SLV_Type *base, uint32_t i, uint32_t val)
{
    base->READ_COMMAND[i] &= ~FLEXSPI_SLV_READ_COMMAND_COMMANDSET_MASK;
    base->READ_COMMAND[i] |= FLEXSPI_SLV_READ_COMMAND_COMMANDSET(val);
}

/*!
 * @brief Gets the read memory command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param i The read command setting register index
 */
static inline uint32_t FLEXSPI_SLV_Read_CommandGet(FLEXSPI_SLV_Type *base, uint32_t i)
{
    uint32_t regBitVal = base->READ_COMMAND[i] & FLEXSPI_SLV_READ_COMMAND_COMMANDSET_MASK;

    return (regBitVal >> FLEXSPI_SLV_READ_COMMAND_COMMANDSET_SHIFT);
}

/*!
 * @brief Sets the dummy cycle for the read memory command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param i The read command dummy cycle setting register index
 * @param val The dummy cycle value of the read command.
 */
static inline void FLEXSPI_SLV_Read_Command_DummyCyclesSet(FLEXSPI_SLV_Type *base, uint32_t i, uint32_t val)
{
    base->READ_COMMAND[i] &= ~FLEXSPI_SLV_READ_COMMAND_DUMMYCYCLES_MASK;
    base->READ_COMMAND[i] |= FLEXSPI_SLV_READ_COMMAND_DUMMYCYCLES(val);
}

/*!
 * @brief Gets the dummy cycle for the read memory command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param i The read command dummy cycle setting register index
 */
static inline uint32_t FLEXSPI_SLV_Read_Command_DummyCyclesGet(FLEXSPI_SLV_Type *base, uint32_t i)
{
    uint32_t regBitVal = base->READ_COMMAND[i] & FLEXSPI_SLV_READ_COMMAND_DUMMYCYCLES_MASK;

    return (regBitVal >> FLEXSPI_SLV_READ_COMMAND_DUMMYCYCLES_SHIFT);
}

/*!
 * @brief Sets the write memory command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param i The write command setting register index
 * @param val The write command value.
 */
static inline void FLEXSPI_SLV_Write_CommandSet(FLEXSPI_SLV_Type *base, uint32_t i, uint32_t val)
{
    base->WRITE_COMMAND[i] &= ~FLEXSPI_SLV_WRITE_COMMAND_COMMANDSET_MASK;
    base->WRITE_COMMAND[i] |= FLEXSPI_SLV_WRITE_COMMAND_COMMANDSET(val);
}

/*!
 * @brief Sets the read register command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param val The read register command value.
 */
static inline void FLEXSPI_SLV_Read_Register_CommandSet(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->READ_REGISTER_COMMAND0 &= ~FLEXSPI_SLV_READ_REGISTER_COMMAND0_COMMANDSET_MASK;
    base->READ_REGISTER_COMMAND0 |= FLEXSPI_SLV_READ_REGISTER_COMMAND0_COMMANDSET(val);
}

/*!
 * @brief Sets the dummy cycle for the read register command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param val The dummy cycle value of the read register command.
 */
static inline void FLEXSPI_SLV_Read_Register_Command_DummyCyclesSet(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->READ_REGISTER_COMMAND0 &= ~FLEXSPI_SLV_READ_REGISTER_COMMAND0_DUMMYCYCLES_MASK;
    base->READ_REGISTER_COMMAND0 |= FLEXSPI_SLV_READ_REGISTER_COMMAND0_DUMMYCYCLES(val);
}

/*!
 * @brief Sets the write register command.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address
 * @param val The write register command value.
 */
static inline void FLEXSPI_SLV_Write_Register_CommandSet(FLEXSPI_SLV_Type *base, uint32_t val)
{
    base->WRITE_REGISTER_COMMAND0 &= ~FLEXSPI_SLV_WRITE_REGISTER_COMMAND0_COMMANDSET_MASK;
    base->WRITE_REGISTER_COMMAND0 |= FLEXSPI_SLV_WRITE_REGISTER_COMMAND0_COMMANDSET(val);
}

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the FLEXSPI FOLLOWER handle which is used in transactional functions.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param handle Pointer to flexspi_slv_handle_t structure to store the interrupt state.
 * @param callback Pointer to user callback function.
 * @param userData User parameter passed to the callback function.
 */
void FLEXSPI_SLV_InterruptCreateHandle(FLEXSPI_SLV_Type *base,
                                       flexspi_slv_handle_t *handle,
                                       flexspi_slv_interrupt_callback_t callback,
                                       void *userData);

/*!
 * @brief Master interrupt handler.
 *
 * @param base FLEXSPI FOLLOWER peripheral base address.
 * @param handle Pointer to flexspi_slv_handle_t structure.
 */
void FLEXSPI_SLV_HandleIRQ(FLEXSPI_SLV_Type *base, flexspi_slv_handle_t *handle);
/*! @} */

#if defined(__cplusplus)
}
#endif /*_cplusplus. */
/*@}*/

#endif /* __FSL_FLEXSPI_FOLLOWER_H_ */

