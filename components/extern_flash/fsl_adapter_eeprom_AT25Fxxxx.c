/*
 * Copyright 2018, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "fsl_common.h"
#include "fsl_adapter_spi.h"
#include "fsl_adapter_eeprom.h"
/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#if (!defined(GCOV_DO_COVERAGE) || (GCOV_DO_COVERAGE == 0))
#define EEPROM_STATIC static
#define EEPROM_PUBLIC
#else
#define EEPROM_STATIC __WEAK
#define EEPROM_PUBLIC __WEAK
#endif

#define EEPROM_RDSR      0x05U
#define EEPROM_READ      0x03U
#define EEPROM_WRITE     0x02U
#define EEPROM_WR_ENABLE 0x06U

#define EEPROM_BUSY_FLAG_MASK 0x01U
#define EEPROM_WRITE_ENABLED  0x02U

#define EEPROM_PAGE_SIZE  (256U)
#define EEPROM_BLOCK_SIZE (8U * EEPROM_PAGE_SIZE)
#define EEPROM_PAGE_MASK  (EEPROM_PAGE_SIZE - 1U)

/* adress mask */
#define ADDRESS_MASK 0x000000FFUL
/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
typedef struct _eeprom_state
{
    uint8_t eepromEraseBitmap[32];
    HAL_SPI_MASTER_HANDLE_DEFINE(spiHandle); /*!< spi handle*/
    eeprom_type_t eeType;                    /*!< eeprom type*/
} eeprom_state_t;

EEPROM_STATIC eeprom_state_t s_eeState;
/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Private Memory function
*************************************************************************************
********************************************************************************** */

EEPROM_STATIC void EEPROM_SetSpiTransferValue(
    hal_spi_transfer_t *transferValue, uint8_t *txData, uint8_t *rxData, size_t dataSize, uint32_t flags)
{
    transferValue->txData   = txData;
    transferValue->rxData   = rxData;
    transferValue->dataSize = dataSize;
    transferValue->flags    = flags;
}

EEPROM_STATIC uint8_t EEPROM_ReadStatusReq(void)
{
    uint8_t cmd = EEPROM_RDSR;
    hal_spi_transfer_t xfer;
    uint8_t data[1] = {0U};

    EEPROM_SetSpiTransferValue(&xfer, &cmd, NULL, sizeof(cmd), (SPI_FIFOWR_RXIGNORE(1) | SPI_FIFOWR_EOF(1)));
    (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);

    EEPROM_SetSpiTransferValue(&xfer, NULL, data, 1, (SPI_FIFOWR_TXIGNORE(1) | SPI_FIFOWR_EOF(1) | SPI_FIFOWR_EOT(1)));
    (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);

    return *((uint8_t *)((void *)data));
}

EEPROM_STATIC uint8_t EEPROM_isBusy(void)
{
    return ((EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK) == 0U) ? 0U : 1U;
}

EEPROM_STATIC eeprom_status_t EEPROM_WaitForReady(bool isInfinite)
{
    volatile uint16_t wait = 0x400; /* near 50 ms @ 50 us/cycle */

    while ((bool)EEPROM_isBusy())
    {
        if (!isInfinite)
        {
            if (0U != wait)
            {
                wait--;
            }
            else
            {
                break;
            }
        }
    }

    if (0U != wait)
    {
        return kStatus_EeSuccess;
    }
    return kStatus_EeError;
}

EEPROM_STATIC eeprom_status_t EEPROM_PrepareForWrite()
{
    uint8_t cmd = EEPROM_WR_ENABLE;
    hal_spi_transfer_t xfer;
    uint8_t status = EEPROM_ReadStatusReq();

    if ((status & EEPROM_WRITE_ENABLED) == 0U)
    {
        EEPROM_SetSpiTransferValue(&xfer, &cmd, NULL, sizeof(cmd),
                                   (SPI_FIFOWR_RXIGNORE(1) | SPI_FIFOWR_EOF(1) | SPI_FIFOWR_EOT(1)));
        (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);
    }
    return kStatus_EeSuccess;
}

EEPROM_STATIC eeprom_status_t EEPROM_Command(uint8_t opCode, uint32_t addre)
{
    uint8_t cmd[4];
    hal_spi_transfer_t xfer;

    cmd[0] = opCode;
    cmd[1] = (uint8_t)((addre >> 16) & ADDRESS_MASK);
    cmd[2] = (uint8_t)((addre >> 8) & ADDRESS_MASK);
    cmd[3] = (uint8_t)((addre >> 0) & ADDRESS_MASK);

    EEPROM_SetSpiTransferValue(&xfer, (uint8_t *)cmd, NULL, sizeof(cmd), SPI_FIFOWR_RXIGNORE(1));
    return (eeprom_status_t)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);
}

/*!*********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

eeprom_status_t EEPROM_Init(eeprom_config_t *eepromConfig)
{
    static uint8_t initialized = 0U;

    hal_spi_master_config_t spiMasterConfig = {
        .srcClock_Hz  = eepromConfig->spiSrcClock_Hz,
        .baudRate_Bps = 9600U,
        .enableMaster = true,
        .polarity     = kHAL_SpiClockPolarityActiveHigh,
        .phase        = kHAL_SpiClockPhaseFirstEdge,
        .direction    = kHAL_SpiMsbFirst,
        .instance     = eepromConfig->spiInstance,
    };

    uint32_t i;

    /* Mark Flash as Unerased */
    for (i = 0; i < sizeof(s_eeState.eepromEraseBitmap) / sizeof(s_eeState.eepromEraseBitmap[0]); i++)
    {
        s_eeState.eepromEraseBitmap[i] = 0;
    }

    if (0U == initialized)
    {
        s_eeState.eeType = eepromConfig->eeType;

        (void)HAL_SpiMasterInit((hal_spi_master_handle_t)s_eeState.spiHandle, (void *)&spiMasterConfig);

        initialized = 1;
    }

    return kStatus_EeSuccess;
}

static eeprom_status_t EEPROM_WritePage(uint32_t noOfBytes, uint32_t addre, uint8_t *Outbuf)
{
    hal_spi_transfer_t xfer;

    if (0U == noOfBytes)
    {
        return kStatus_EeSuccess;
    }

    (void)EEPROM_WaitForReady(true);

    (void)EEPROM_PrepareForWrite();

    (void)EEPROM_WaitForReady(true);

    if (kStatus_EeSuccess != EEPROM_Command(EEPROM_WRITE, addre))
    {
        return kStatus_EeError;
    }
    EEPROM_SetSpiTransferValue(&xfer, Outbuf, NULL, noOfBytes, SPI_FIFOWR_EOT(1));
    if (kStatus_HAL_SpiSuccess != HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer))
    {
        return kStatus_EeError;
    }

    return kStatus_EeSuccess;
}
/*****************************************************************************
 *  EEPROM_WriteData
 *
 *  Writes a data buffer into EEPROM, at a given address
 *
 *****************************************************************************/
eeprom_status_t EEPROM_WriteData(uint32_t noOfBytes, uint32_t addr2eeprom, uint8_t *Outbuf)
{
    eeprom_status_t retval;

    while ((addr2eeprom & EEPROM_PAGE_MASK) + noOfBytes > EEPROM_PAGE_MASK)
    {
        uint32_t bytes = EEPROM_PAGE_SIZE - (addr2eeprom & EEPROM_PAGE_MASK);

        retval = EEPROM_WritePage(bytes, addr2eeprom, Outbuf);
        noOfBytes -= bytes;
        addr2eeprom += bytes;

        for (uint32_t j = 0; j < bytes; j++)
        {
            Outbuf++; /*Outbuf += bytes;*/
        }

        if (kStatus_EeSuccess != retval)
        {
            return retval;
        }
    }
    retval = EEPROM_WritePage(noOfBytes, addr2eeprom, Outbuf);

    return retval;
}

/*****************************************************************************
 *  EEPROM_ReadData
 *
 *  Reads a data buffer from EEPROM, from a given address
 *
 *****************************************************************************/
eeprom_status_t EEPROM_ReadData(uint16_t noOfBytes, uint32_t addr2eeprom, uint8_t *inbuf)
{
    hal_spi_transfer_t xfer;
    (void)EEPROM_WaitForReady(true);

    if (kStatus_EeSuccess != EEPROM_Command(EEPROM_READ, addr2eeprom))
    {
        return kStatus_EeError;
    }
    EEPROM_SetSpiTransferValue(&xfer, NULL, inbuf, noOfBytes, SPI_FIFOWR_EOT(1));
    if (kStatus_HAL_SpiSuccess != HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer))
    {
        return kStatus_EeError;
    }

    return kStatus_EeSuccess;
}
