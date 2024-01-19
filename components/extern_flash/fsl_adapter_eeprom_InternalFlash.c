/*
 * Copyright 2018, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_eeprom.h"
#include "fsl_adapter_flash.h"

/******************************************************************************
*******************************************************************************
* Private Macros
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Private type definitions
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Private Memory Declarations
*******************************************************************************
******************************************************************************/

typedef struct _eeprom_state
{
    uint8_t eepromEraseBitmap[32];
    uint32_t eepromParams_StartOffset;
    uint32_t eepromParams_TotalSize;
    uint32_t eepromParams_SectorSize;
    eeprom_type_t eeType;
} eeprom_state_t;

static eeprom_state_t s_eeState;
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
static eeprom_status_t EEPROM_CleanEraseFlag(uint32_t noOfBytes, uint32_t addr)
{
    uint32_t i;
    uint32_t startBlk, endBlk;
    /* Obtain the first and last block that need to be erased */
    startBlk = addr / s_eeState.eepromParams_SectorSize;
    endBlk   = (addr + noOfBytes) / s_eeState.eepromParams_SectorSize;

    if ((addr + noOfBytes) & s_eeState.eepromParams_SectorSize)
    {
        endBlk++;
    }
    for (i = startBlk; i <= endBlk; i++)
    {
        s_eeState.eepromEraseBitmap[i / 8] &= ~(1U << (i % 8));
    }
    return kStatus_EeSuccess;
}
static eeprom_status_t EEPROM_PrepareForWrite(uint32_t noOfBytes, uint32_t addr)
{
    uint32_t i;
    uint32_t startBlk, endBlk;
    /* Obtain the first and last block that need to be erased */
    startBlk = addr / s_eeState.eepromParams_SectorSize;
    endBlk   = (addr + noOfBytes) / s_eeState.eepromParams_SectorSize;

    if ((addr + noOfBytes) & s_eeState.eepromParams_SectorSize)
    {
        endBlk++;
    }

    /* Check if the block was previousley erased */
    for (i = startBlk; i <= endBlk; i++)
    {
        if ((s_eeState.eepromEraseBitmap[i / 8] & (1U << (i % 8))) == 0)
        {
            if (EEPROM_EraseBlock(i * s_eeState.eepromParams_SectorSize, s_eeState.eepromParams_SectorSize) !=
                kStatus_EeSuccess)
            {
                return kStatus_EeError;
            }
            s_eeState.eepromEraseBitmap[i / 8] |= 1U << (i % 8);
        }
    }

    return kStatus_EeSuccess;
}
/******************************************************************************
*******************************************************************************
* Public Memory
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Public Functions
*******************************************************************************
******************************************************************************/

/*****************************************************************************
 *  EEPROM_Init
 *
 *  Initializes the EEPROM_ peripheral
 *
 *****************************************************************************/
eeprom_status_t EEPROM_Init(eeprom_config_t *eepromConfig)
{
    uint32_t pflashBlockBase = 0;
    uint32_t pflashTotalSize = 0;
    uint32_t eepromTotalSize = 0;

    memset(s_eeState.eepromEraseBitmap, 0x00, 32);

    HAL_FlashInit();
    HAL_FlashGetProperty(kHAL_Flash_PropertyPflashBlockBaseAddr, &pflashBlockBase);
    HAL_FlashGetProperty(kHAL_Flash_PropertyPflashTotalSize, &pflashTotalSize);
    HAL_FlashGetProperty(kHAL_Flash_PropertyPflashSectorSize, &s_eeState.eepromParams_SectorSize);
    eepromTotalSize = pflashTotalSize / 2 - ((pflashTotalSize / 2) & (s_eeState.eepromParams_SectorSize - 1));
    s_eeState.eepromParams_TotalSize   = (eepromTotalSize > 32 * 8 * s_eeState.eepromParams_SectorSize) ?
                                             32 * 8 * s_eeState.eepromParams_SectorSize :
                                             eepromTotalSize;
    s_eeState.eepromParams_StartOffset = pflashBlockBase + pflashTotalSize - s_eeState.eepromParams_TotalSize;
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
    uint32_t i, endAddr;
    endAddr = s_eeState.eepromParams_TotalSize;

    for (i = 0; i < endAddr; i += s_eeState.eepromParams_SectorSize)
    {
        if (kStatus_EeSuccess != EEPROM_EraseBlock(i, s_eeState.eepromParams_SectorSize))
        {
            return kStatus_EeError;
        }
    }
    return kStatus_EeSuccess;
}

/*****************************************************************************
 *  EEPROM_EraseSector4K
 *
 *  Erase 4K of memory to 0xFF
 *
 *****************************************************************************/
eeprom_status_t EEPROM_EraseBlock(uint32_t addr, uint32_t size)
{
    eeprom_status_t status;

    if (size != s_eeState.eepromParams_SectorSize)
    {
        status = kStatus_EeError;
    }
    else if (HAL_FlashEraseSector(s_eeState.eepromParams_StartOffset + addr, size) != kStatus_HAL_Flash_Success)
    {
        status = kStatus_EeError;
    }
    else
    {
        status = kStatus_EeSuccess;
    }

    return status;
}

/*****************************************************************************
 *  EEPROM_WriteData
 *
 *  Writes a data buffer into EEPROM, at a given address
 *
 *****************************************************************************/
eeprom_status_t EEPROM_WriteData(uint32_t noOfBytes, uint32_t addr, uint8_t *Outbuf)
{
    /* If Erase is done during write, no need to erase here */
    if (kStatus_EeSuccess != EEPROM_PrepareForWrite(noOfBytes, addr))
    {
        return kStatus_EeError;
    }

    /* Write data to FLASH */
    if (HAL_FlashProgramUnaligned(s_eeState.eepromParams_StartOffset + addr, noOfBytes, Outbuf) !=
        kStatus_HAL_Flash_Success)
    {
        return kStatus_EeError;
    }
    EEPROM_CleanEraseFlag(noOfBytes, addr);
    return kStatus_EeSuccess;
}

/*****************************************************************************
 *  EEPROM_ReadData
 *
 *  Reads a data buffer from EEPROM, from a given address
 *
 *****************************************************************************/
eeprom_status_t EEPROM_ReadData(uint16_t noOfBytes, uint32_t addr, uint8_t *inbuf)
{
    if (HAL_FlashRead(s_eeState.eepromParams_StartOffset + addr, noOfBytes, inbuf) != kStatus_HAL_Flash_Success)
    {
        return kStatus_EeError;
    }

    return kStatus_EeSuccess;
}
#if (defined(GET_EEPROM_SIZE) && (GET_EEPROM_SIZE > 0))
eeprom_status_t EEPROM_GetProperty(eeprom_property_tag_t property, uint32_t *value)
{
    if (value == NULL)
    {
        return kStatus_EeInvalidArgument;
    }

    switch (property)
    {
        case kEEPROM_PropertyTotalSize:

            *value = s_eeState.eepromParams_TotalSize; /* 512 KBytes */
            break;

        case kEEPROM_PropertySectorSize:
            *value = s_eeState.eepromParams_SectorSize; /* 2 KBytes */
            break;

        default: /* catch inputs that are not recognized */
            return kStatus_EeInvalidArgument;
    }

    return kStatus_EeSuccess;
}
#endif
