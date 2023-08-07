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
#include "fsl_adapter_gpio.h"
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

#define EEPROM_RDSR    0xD7U
#define EEPROM_READ    0x03U
#define EEPROM_READ_HF 0x0BU

#define EEPROM_ERASE_256B 0x81U
#define EEPROM_ERASE_2K   0x50U

#define EEPROM_WRITE_BYTES 0x02U

#define EEPROM_BUSY_FLAG_MASK 0x80U
#define EEPROM_PAGE_SIZE      (256U)
#define EEPROM_BLOCK_SIZE     (8U * EEPROM_PAGE_SIZE)
#define EEPROM_PAGE_MASK      (EEPROM_PAGE_SIZE - 1U)

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
    GPIO_HANDLE_DEFINE(gpioHandle);          /*!< gpio handle*/
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
EEPROM_STATIC void EEPROM_AssertCsGpio(void)
{
    (void)HAL_GpioSetOutput(s_eeState.gpioHandle, 0);
}

EEPROM_STATIC void EEPROM_DeassertCsGpio(void)
{
    (void)HAL_GpioSetOutput(s_eeState.gpioHandle, 1);
}

EEPROM_STATIC void EEPROM_SetSpiTransferValue(hal_spi_transfer_t *transferValue,
                                              uint8_t *txData,
                                              uint8_t *rxData,
                                              size_t dataSize)
{
    transferValue->txData   = txData;
    transferValue->rxData   = rxData;
    transferValue->dataSize = dataSize;
}

EEPROM_STATIC uint16_t EEPROM_ReadStatusReq(void)
{
    const uint8_t cmd = EEPROM_RDSR;
    hal_spi_transfer_t xfer;
    uint8_t data[2] = {0U, 0U};

    EEPROM_AssertCsGpio();

    EEPROM_SetSpiTransferValue(&xfer, (uint8_t *)(uint32_t)cmd, NULL, sizeof(cmd));
    (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);

    EEPROM_SetSpiTransferValue(&xfer, NULL, data, 2);
    (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);

    EEPROM_DeassertCsGpio();

    return *((uint16_t *)((void *)data));
}
EEPROM_STATIC uint8_t EEPROM_isBusy(void)
{
    return ((EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK) == 0U) ? 1U : 0U;
}
EEPROM_STATIC eeprom_status_t EEPROM_WaitForReady(bool isInfinite)
{
    volatile uint16_t wait = 0x400; /* near 50 ms @ 50 us/cycle */

    /* Byte1 - Bit:   7       6      5:2       1         0
     *             RDY/BUSY  COMP  DENSITY  PROTECT  PAGE_SIZE
     *
     * Byte2 - Bit:   7       6    5    4    3    2    1    0
     *             RDY/BUSY  RES  EPE  RES  SLE  PS2  PS1  ES
     */
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

EEPROM_STATIC eeprom_status_t EEPROM_PrepareForWrite(uint32_t noOfBytes, uint32_t addre)
{
    uint32_t i;
    eeprom_status_t ret = kStatus_EeSuccess;
    uint32_t startBlk, endBlk;
    /* Obtain the block number */
    startBlk = addre / EEPROM_BLOCK_SIZE;
    endBlk   = (addre + noOfBytes) / EEPROM_BLOCK_SIZE;

    if (0U != ((addre + noOfBytes) % EEPROM_BLOCK_SIZE))
    {
        endBlk++;
    }

    for (i = startBlk; i <= endBlk; i++)
    {
        if (0U == (s_eeState.eepromEraseBitmap[i >> 3U] & (1U << (i & 7U))))
        {
            (void)EEPROM_EraseBlock(i * EEPROM_BLOCK_SIZE, EEPROM_BLOCK_SIZE);

            s_eeState.eepromEraseBitmap[i >> 3U] |= (1U << (i & 7U));
            (void)EEPROM_WaitForReady(true);
        }
    }
    return ret;
}

EEPROM_STATIC eeprom_status_t EEPROM_Command(uint8_t opCode, uint32_t addre)
{
    uint8_t cmd[4];
    hal_spi_transfer_t xfer;

    cmd[0] = opCode;
    cmd[1] = (uint8_t)((addre >> 16) & ADDRESS_MASK);
    cmd[2] = (uint8_t)((addre >> 8) & ADDRESS_MASK);
    cmd[3] = (uint8_t)((addre >> 0) & ADDRESS_MASK);

    EEPROM_AssertCsGpio();
    EEPROM_SetSpiTransferValue(&xfer, (uint8_t *)cmd, NULL, sizeof(cmd));
    return (eeprom_status_t)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);
}
EEPROM_STATIC eeprom_status_t EEPROM_WritePage(uint32_t noOfBytes, uint32_t addre, uint8_t *Outbuf)
{
    hal_spi_transfer_t xfer;
    if (0U == noOfBytes)
    {
        return kStatus_EeSuccess;
    }

    while (0U != EEPROM_isBusy())
    {
    }

    /*CS will remain ASSERTED */
    if (kStatus_EeSuccess != EEPROM_Command(EEPROM_WRITE_BYTES, addre))
    {
        EEPROM_DeassertCsGpio();
        return kStatus_EeError;
    }
    EEPROM_SetSpiTransferValue(&xfer, Outbuf, NULL, noOfBytes);
    if (kStatus_HAL_SpiSuccess != HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer))
    {
        EEPROM_DeassertCsGpio();
        return kStatus_EeError;
    }

    EEPROM_DeassertCsGpio();

    return kStatus_EeSuccess;
}
/*!*********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

eeprom_status_t EEPROM_Init(eeprom_config_t *eepromConfig)
{
    static uint8_t initialized = 0U;
    eeprom_status_t retval;
    hal_spi_transfer_t xfer;
    hal_gpio_pin_config_t controlPin;

    uint8_t cmd[] = {0x3D, 0x2A, 0x80, 0xA6};

    hal_spi_master_config_t spiMasterConfig = {
        .srcClock_Hz  = eepromConfig->spiSrcClock_Hz,
        .baudRate_Bps = 500000U,
        .enableMaster = true,
        .polarity     = kHAL_SpiClockPolarityActiveHigh,
        .phase        = kHAL_SpiClockPhaseFirstEdge,
        .direction    = kHAL_SpiMsbFirst,
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
        controlPin.port      = eepromConfig->csGpioPort;
        controlPin.pin       = eepromConfig->csGpiopin;
        controlPin.direction = kHAL_GpioDirectionOut;
        controlPin.level     = 0U;
        (void)HAL_GpioInit((hal_gpio_handle_t)s_eeState.gpioHandle, &controlPin);

        retval = EEPROM_WaitForReady(false);
        if (kStatus_EeSuccess != retval)
        {
            return retval;
        }
        /* Set page size to 256bits: */
        EEPROM_AssertCsGpio();
        EEPROM_SetSpiTransferValue(&xfer, (uint8_t *)cmd, NULL, sizeof(cmd));
        (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);
        EEPROM_DeassertCsGpio();
        initialized = 1;
    }

    return kStatus_EeSuccess;
}

/*****************************************************************************
 *  EEPROM_ChipErase
 *
 *  Erase all memory to 0xFF
 *
 *****************************************************************************/
eeprom_status_t EEPROM_ChipErase(void)
{
    uint8_t cmd[] = {0xC7, 0x94, 0x80, 0x9A};
    hal_spi_transfer_t xfer;
    (void)EEPROM_WaitForReady(true);

    EEPROM_AssertCsGpio();
    EEPROM_SetSpiTransferValue(&xfer, (uint8_t *)cmd, NULL, sizeof(cmd));
    (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);
    EEPROM_DeassertCsGpio();

    return kStatus_EeSuccess;
}

/*****************************************************************************
 *  EEPROM_EraseBlock
 *
 *  Erase a block of memory to 0xFF
 *
 *****************************************************************************/
eeprom_status_t EEPROM_EraseBlock(uint32_t addr2eeprom, uint32_t size)
{
    uint8_t cmd[4];
    hal_spi_transfer_t xfer;
    eeprom_status_t status = kStatus_EeSuccess;
    (void)EEPROM_WaitForReady(true);

    switch (size)
    {
        case EEPROM_BLOCK_SIZE:
            cmd[0] = EEPROM_ERASE_2K;
            break;
        case EEPROM_PAGE_SIZE:
            cmd[0] = EEPROM_ERASE_256B;
            break;
        default:
            status = kStatus_EeError;
            break;
    }

    cmd[1] = (uint8_t)((addr2eeprom >> 16) & ADDRESS_MASK);
    cmd[2] = (uint8_t)((addr2eeprom >> 8) & ADDRESS_MASK);
    cmd[3] = (uint8_t)((addr2eeprom >> 0) & ADDRESS_MASK);

    EEPROM_AssertCsGpio();
    EEPROM_SetSpiTransferValue(&xfer, (uint8_t *)cmd, NULL, sizeof(cmd));
    (void)HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer);
    EEPROM_DeassertCsGpio();

    return status;
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
    if (0U == noOfBytes)
    {
        return kStatus_EeSuccess;
    }

    (void)EEPROM_WaitForReady(true);

    (void)EEPROM_PrepareForWrite(noOfBytes, addr2eeprom);

    (void)EEPROM_WaitForReady(true);

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
        EEPROM_DeassertCsGpio();
        return kStatus_EeError;
    }
    EEPROM_SetSpiTransferValue(&xfer, NULL, inbuf, noOfBytes);
    if (kStatus_HAL_SpiSuccess != HAL_SpiMasterTransferBlocking(s_eeState.spiHandle, &xfer))
    {
        EEPROM_DeassertCsGpio();
        return kStatus_EeError;
    }
    EEPROM_DeassertCsGpio();

    return kStatus_EeSuccess;
}

#if (defined(GET_EEPROM_SIZE) && (GET_EEPROM_SIZE > 0))
eeprom_status_t EEPROM_GetProperty(eeprom_property_tag_t property, uint32_t *value)
{
    eeprom_status_t status = kStatus_EeSuccess;
    if (NULL == value)
    {
        return kStatus_EeInvalidArgument;
    }

    if (property == kEEPROM_PropertyTotalSize)
    {
        if (s_eeState.eeType == kEEPROM_DeviceAT45DB161E)
        {
            *value = 0x00200000U; /* 2 MBytes */
        }
        else if (s_eeState.eeType == kEEPROM_DeviceAT26DF081A)
        {
            *value = 0x00100000U; /* 1 MBytes */
        }
        else if (s_eeState.eeType == kEEPROM_DeviceAT45DB021E)
        {
            *value = 0x00040000U; /* 256 KBytes */
        }
        else if (s_eeState.eeType == kEEPROM_DeviceAT45DB041E)
        {
            *value = 0x00080000U; /* 512 KBytes */
        }
        else
        {
            /*MISRA rule 15.7*/
        }
    }
    else if (property == kEEPROM_PropertySectorSize)
    {
        if (s_eeState.eeType == kEEPROM_DeviceAT45DB161E)
        {
            *value = (4 * 1024); /* 4 KBytes */
        }
        else if (s_eeState.eeType == kEEPROM_DeviceAT26DF081A)
        {
            *value = (4 * 1024); /* 4 KBytes */
        }
        else if (s_eeState.eeType == kEEPROM_DeviceAT45DB021E)
        {
            *value = (2 * 1024); /* 2 KBytes */
        }
        else if (s_eeState.eeType == kEEPROM_DeviceAT45DB041E)
        {
            *value = (2 * 1024); /* 2 KBytes */
        }
        else
        {
            /*MISRA rule 15.7*/
        }
    }
    else /* catch inputs that are not recognized */
    {
        status = kStatus_EeInvalidArgument;
    }

    return status;
}
#endif
