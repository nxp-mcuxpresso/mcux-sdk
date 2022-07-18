/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file driver_KSDK_NVM.c
    \brief middleware driver for NVM on Kinetis devices
*/
#include "sensor_fusion.h"
#include "driver_KSDK_NVM.h"

#ifndef CPU_LPC54114J256BD64_cm4
#include "fsl_flash.h"
#else
#include "fsl_flashiap.h"
#endif

#define ERROR 1
#define SUCCESS 0;
#ifndef CPU_LPC54114J256BD64_cm4
byte NVM_SetBlockFlash(uint8_t *Source, uint32_t Dest, uint16_t Count)
{
    byte retVal=0;
    status_t result;
    uint32_t pflashSectorSize = ERROR;
    flash_config_t flashDriver;                                            // Flash driver Structure

    // Clean up Flash driver Structure
    memset(&flashDriver, 0, sizeof(flash_config_t));
    // Setup flash driver structure for device and initialize variables.
    result = FLASH_Init(&flashDriver);
    if (kStatus_FLASH_Success == result)
    {
        FLASH_GetProperty(&flashDriver, FLASH_SECTOR_SIZE_PROPERTY, &pflashSectorSize);
        result = FLASH_Erase(&flashDriver, Dest, pflashSectorSize,  FLASH_ERASE_KEY);

        if (kStatus_FLASH_Success == result) {
            result = FLASH_Program(&flashDriver, Dest, Source, Count);
            if (kStatus_FLASH_Success == result)  retVal=SUCCESS;
        }
    }
    return(retVal);
}
#else
byte checkIAPStatus(status_t result) {
    byte retVal=0;
      switch (result) {
      case kStatus_FLASHIAP_Success:
        retVal = SUCCESS;
        break;
      case kStatus_FLASHIAP_InvalidCommand :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_SrcAddrError :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_DstAddrError :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_SrcAddrNotMapped :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_DstAddrNotMapped :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_CountError :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_InvalidSector :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_NotPrepared :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_CompareError :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_Busy :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_ParamError :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_AddrError :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_AddrNotMapped :
        retVal = ERROR;
        break;
       case kStatus_FLASHIAP_NoPower :
        retVal = ERROR;
        break;
      case kStatus_FLASHIAP_NoClock :
        retVal = ERROR;
        break;
      default:
        break;
      }
      return retVal;
}

byte NVM_SetBlockFlash(uint8_t *Source, uint32_t Dest, uint16_t Count)
{
    byte retVal=ERROR;
    status_t result;
    result = FLASHIAP_PrepareSectorForWrite(NVM_SECTOR_NUMBER, NVM_SECTOR_NUMBER);
    if (result == kStatus_FLASHIAP_Success) {
      result = FLASHIAP_ErasePage(NVM_PAGE_NUMBER, NVM_PAGE_NUMBER, SystemCoreClock);
      if (result == kStatus_FLASHIAP_Success) {
        result = FLASHIAP_PrepareSectorForWrite(NVM_SECTOR_NUMBER, NVM_SECTOR_NUMBER);
        if (result == kStatus_FLASHIAP_Success) {

            result = FLASHIAP_CopyRamToFlash(CALIBRATION_NVM_ADDR, (uint32_t *) Source, (uint32_t) Count, SystemCoreClock);
            //if (result == kStatus_FLASHIAP_Success) retVal = SUCCESS;
            retVal = checkIAPStatus(result);
        }
      }
    }
    return(retVal);
}
#endif
