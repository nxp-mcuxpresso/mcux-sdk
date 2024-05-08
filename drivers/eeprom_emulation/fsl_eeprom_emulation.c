/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_eeprom_emulation.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.eeprom_emulation"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t EE_PreInitCheck(eeprom_emulation_handle_t *handle);
static uint32_t EE_InitAltSector(eeprom_emulation_handle_t *handle, uint8_t *number);
static uint32_t EE_InitActiveSector(eeprom_emulation_handle_t *handle, uint8_t number);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Start address of the current active sector */
static uint32_t g_currentActiveSector;

/* The blank address of the current active sector
   where the next data record is written */
static uint32_t g_freeSpaceAddress;
static uint32_t g_eeEndAddress;
#if (defined(FLASH_PGM_SIZE) && (FLASH_PGM_SIZE == 16))
static uint32_t g_eraseCycles[4];
#else
static uint32_t g_eraseCycles[2];
#endif
static eeprom_emulation_data_record_t g_dataRecord;

#if (EE_USE_ASYNCHRONOUS_MODEL == true)
static uint32_t g_addressToMain;
static uint32_t g_endAddressToMain;
static uint8_t g_numErase = 0x00u;
#endif

/* Flag to keep track of Erase State*/
static volatile eeprom_emulation_state_type_t g_eraseStatusFlag;

#if EE_CALLBACK_ENABLE
/* A function pointer to the CallBack function */
PEE_FUNCPOINTER g_EECallBack;
#endif /* EE_CALLBACK_ENABLE */

/*******************************************************************************
 * Code
 ******************************************************************************/
void EE_GetDefaultConfig(eeprom_emulation_config_t *config)
{
    config->eeRetryMax           = 0x02U;
    config->ftfxPGMCheckSize     = 0x04U;
    config->flashReadMargin      = 0x01U;
    config->flashStartAddress    = 0x00U;
    config->eeSectorActIndOffset = 0x00U;
}

void EE_SetEepromEmulationInfo(eeprom_emulation_handle_t *handle, eeprom_emulation_config_t *config)
{
    /* Number of actual alternative sectors alloted for emulation Eeprom is enough or not */
    assert(config->eeActualReadySectors >= config->eeMinActualReadySectors);

    /* Flash sector size */
    handle->flashSectorSize = config->flashSectorSize;
    /* Start address for emulated eeprom */
    handle->eeStartAddress = config->eeStartAddress;
    /* Program size for ftfx module */
    handle->ftfxProgramSize = config->ftfxProgramSize;
    /* Data value size in one record */
    handle->eeDataValueSize = config->eeDataValueSize;
    /* Sector size for emulated eeprom */
    handle->eeSectorSize = config->eeSectorSize;
    /* The total raw data user wants to emulate in byte */
    handle->eeMemorySize = config->eeMemorySize;
    /* Active ready sector numbers */
    handle->eeActualReadySectors = config->eeActualReadySectors;
    /* Extra ready sector numbers */
    handle->eeExtraReadySectors = config->eeExtraReadySectors;
    /* Extra active sector numbers */
    handle->eeExtraActiveSectors = config->eeExtraActiveSectors;
    /* Number of retry if failed to program sector indicator or erase sector */
    handle->eeRetryMax = config->eeRetryMax;
    /* Program size for program check function */
    handle->ftfxPGMCheckSize = config->ftfxPGMCheckSize;
    /* Read one sector size for ftfx module */
    handle->ftfxRD1SECSize = config->ftfxRD1SECSize;
    /* Read margin */
    handle->flashReadMargin = config->flashReadMargin;

    /* Calculate complement size */
    if (config->eccSize == 0x02U)
    {
        handle->complementSize = handle->ftfxProgramSize;
    }
    else
    {
        handle->complementSize = 0;
    }

    /* Calculate eeprom emulation sector header size */
    handle->eeSectorHeaderSize = (0x03U * handle->ftfxProgramSize) + handle->complementSize;

    /* number of bit to make programable size */
    if (FTFx_LONGWORD_SIZE == handle->ftfxProgramSize)
    {
        handle->ftfxBitNumber      = 0x02U;
        handle->ftfxProgramCommand = 0x06U;
    }
    else if (FTFx_PHRASE_SIZE == handle->ftfxProgramSize)
    {
        handle->ftfxBitNumber      = 0x03U;
        handle->ftfxProgramCommand = 0x07U;
    }
    else
    {
        /* Should not be here */
    }

    /* Calculate eeprom emulation sector record length */
    if (0x00U != GET_MOD(handle->eeDataValueSize, handle->ftfxProgramSize))
    {
        handle->eeSectorRecordLength =
            (((handle->eeDataValueSize >> handle->ftfxBitNumber) + 0x01U) << handle->ftfxBitNumber) +
            (2U * handle->ftfxProgramSize) + handle->complementSize;
    }
    else
    {
        handle->eeSectorRecordLength =
            handle->eeDataValueSize + (2U * handle->ftfxProgramSize) + handle->complementSize;
    }

    /* Calculate active indecator, dead indicator and erase cycle offset */
    handle->eeSectorActIndOffset     = config->eeSectorActIndOffset;
    handle->eeSectorDeadIndOffset    = handle->ftfxProgramSize;
    handle->eeSectorEraseCycleOffset = handle->ftfxProgramSize << 0x01U;

    /* Calculate record ID and record status offset */
    handle->eeRecordIDOffset = handle->eeSectorRecordLength - EE_RECORD_ID_SIZE - handle->complementSize;
    if (FTFx_PHRASE_SIZE == handle->ftfxProgramSize)
    {
        handle->eeGapSize = 0x04U;
        handle->eeRecordStatusOffset =
            handle->eeSectorRecordLength - FTFx_LONGWORD_SIZE - EE_RECORD_STATUS_SIZE - handle->complementSize;
    }
    else if (FTFx_DPHRASE_SIZE == handle->ftfxProgramSize)
    {
        handle->eeGapSize = handle->ftfxProgramSize; /* The gap between ID with STATUS. */
        handle->eeRecordStatusOffset =
            handle->eeSectorRecordLength - handle->ftfxProgramSize - EE_RECORD_STATUS_SIZE - handle->complementSize;
    }
    else
    {
        handle->eeGapSize            = 0x02U;
        handle->eeRecordStatusOffset = handle->eeSectorRecordLength - handle->ftfxProgramSize - handle->complementSize;
    }

    /* Calculate eeprom emulation sector waste size */
    handle->eeSectorWaste = (handle->eeSectorSize - handle->eeSectorHeaderSize) % handle->eeSectorRecordLength;

    /* Calculate ready sectors number*/
    handle->eeReadySectors = handle->eeActualReadySectors + handle->eeExtraReadySectors;

    /* Number of Data Records is calculated if we know the total Data Size */
    if (0x00U != GET_MOD(handle->eeMemorySize, handle->eeDataValueSize))
    {
        handle->eeMaxRecordNumber = (uint16_t)(GET_INT(handle->eeMemorySize, handle->eeDataValueSize) + 0x01u);
    }
    else
    {
        handle->eeMaxRecordNumber = (uint16_t)(GET_INT(handle->eeMemorySize, handle->eeDataValueSize));
    }

    /* Calculate capacity */
    handle->eeSectorCapacity = GET_INT(handle->eeSectorSize - handle->eeSectorHeaderSize, handle->eeSectorRecordLength);

    /* Calculate required active sector */
    if (0x00U != GET_MOD(((uint32_t)handle->eeMaxRecordNumber + 0x01u), handle->eeSectorCapacity))
    {
        handle->eeActiveSectorRequired =
            (GET_INT(((uint32_t)handle->eeMaxRecordNumber + 0x01u), handle->eeSectorCapacity) + 0x01u);
    }
    else
    {
        handle->eeActiveSectorRequired =
            GET_INT(((uint32_t)handle->eeMaxRecordNumber + 0x01u), handle->eeSectorCapacity);
    }

    /* Total number of active sectors alloted */
    handle->eeActiveSectors = handle->eeExtraActiveSectors + handle->eeActiveSectorRequired;

    /* Total number of sectors alloted will also include some 'alternative sectors' */
    handle->eeAllotedSectors = handle->eeActiveSectors + handle->eeReadySectors;

    /* End address of eeprom emulation from Flash */
    handle->eeEndAddress = handle->eeStartAddress + handle->eeAllotedSectors * handle->eeSectorSize;
}

/*******************************************************************************
 *
 *  Function Name    : CheckErrorCode
 *  Description      : Check error bit of each flash command.
 *  Purpose          : to optimize code size since this function is called multiple times.
 *  Arguments        : N/A
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_FlashCheckErrorCode(void)
{
    uint32_t returnCode;
    returnCode = EE_OK;
    /* checking all errors */
    if (0u != FMU_CHECK_ERR)
    {
        returnCode = EE_NOT_OK;
    }
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_FlashEraseAll
 *  Description      : Erase one EE sector in Flash with synchronous model and verify as well
 *  Arguments        :
 *                     - destination: the offset address to flash base
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_FlashEraseAll(eeprom_emulation_handle_t *handle))
{
    uint32_t result = EE_OK;

    /* load FCCOB registers */
    FMU0->FCCOB[0] = ERSALL;

    /* Check if previous command complete, wait for CCIF set */
    while (0x00U == (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /* clear CMDABT & ACCERR & PVIOL flag in flash status register */
    FMU0->FSTAT = (FLASH_FSTAT_CMDABT_MASK | FLASH_FSTAT_ACCERR_MASK | FLASH_FSTAT_PVIOL_MASK);

    FMU0->FSTAT = FLASH_FSTAT_CCIF_MASK;
    while (0x00U != (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    while (0x00U == (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /* Check for errors */
    if (0x00U != (FMU0->FSTAT & FMU_FSTAT_FAIL_MASK))
    {
        result = EE_NOT_OK;
    }

    return result;
}

/*******************************************************************************
 *
 *  Function Name    : EE_SyncFlashErase
 *  Description      : Erase one EE sector in Flash with synchronous model and verify as well
 *  Arguments        :
 *                     - destination: the offset address to flash base
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_SyncFlashErase(eeprom_emulation_handle_t *handle, uint32_t destination))
{
    uint32_t dest   = destination;
    uint32_t result = EE_OK;
    uint32_t i;

    destination -= handle->flashStartAddress;

    while (dest < (destination + handle->eeSectorSize))
    {
        /*Clear status*/
        FMU0->FSTAT = FMU_FSTAT_ACCERR_MASK | FMU_FSTAT_PVIOL_MASK | FMU_FSTAT_CMDABT_MASK;

        /* load FCCOB registers */
        FMU0->FCCOB[0] = ERSSCR;
        FMU0->FCCOB[1] = 0x00U;

        /*Clear CCIF to launch the command*/
        FMU0->FSTAT = FMU_FSTAT_CCIF_MASK;

        /*wait for writes to get enabled*/
        while (0x00U == (FMU0->FSTAT & FMU_FSTAT_PEWEN_MASK))
        {
        }

        /* writing 4 consecutive words to flash. */
        for (i = 0; i < 4U; i++)
        {
            *((uint32_t *)(dest + i * 4U)) = 0x00U;
        }

        while (0x00U == (FMU0->FSTAT & FMU_FSTAT_PERDY_MASK))
        {
        }

        /* Clear PERDY status */
        FMU0->FSTAT = FMU_FSTAT_PERDY_MASK;

        /* wait until command complete */
        while (0x00U == (FMU0->FSTAT & FMU_FSTAT_CCIF_MASK))
        {
        }

        /*check for errors*/
        if (0x00U != (FMU0->FSTAT & FMU_FSTAT_FAIL_MASK))
        {
            result = EE_NOT_OK;
            break;
        }

        dest += handle->flashSectorSize;
    }

    /* need to verify section here */
    if (result != EE_NOT_OK)
    {
        result = EE_FlashEraseVerifySection(handle, destination + handle->flashStartAddress,
                                            (uint16_t)(handle->eeSectorSize / handle->ftfxRD1SECSize),
                                            handle->flashReadMargin);
    }

    return result;
}

/*******************************************************************************
 *
 *  Function Name    : EE_AsyncFlashErase
 *  Description      : Erase one EE sector in Flash with synchronous model and verify as well
 *  Arguments        :
 *                     - destination: the offset address to flash base
 *  Return Value     : N/A
 *
 *******************************************************************************/
#if (EE_USE_ASYNCHRONOUS_MODEL == true)
void EE_AsyncFlashErase(eeprom_emulation_handle_t *handle, uint32_t destination)
{
    destination -= handle->flashStartAddress;
    /* load FCCOB registers */
    REG_WRITE(FTFx_FCCOB0, FTFx_ERASE_SECTOR);
    REG_WRITE(FTFx_FCCOB1, (uint8_t)(destination >> 16u));
    REG_WRITE(FTFx_FCCOB2, (uint8_t)((destination >> 8u) & 0xFFu));
    REG_WRITE(FTFx_FCCOB3, (uint8_t)(destination & 0xFFu));

    /* Update erase status */
    g_eraseStatusFlag = BUSY;
    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    /* it is impossible to launch command if any error bit set */
    REG_WRITE(FTFx_FSTAT, FTFx_FSTAT_CLEAR_ERR);
    /* clear CCIF bit to start command */
    REG_WRITE(FTFx_FSTAT, FTFx_FSTAT_CCIF);
    /* Enable command complete interrupt */
    REG_BIT_SET(FTFx_FCNFG, FTFx_FCNFG_CCIE);
}
#endif /* of EE_USE_ASYNCHRONOUS_MODEL*/

/*******************************************************************************
 *
 *  Function Name    : EE_FlashEraseVerifySection
 *  Description      : Erase verify Number*FTFx_RD1SEC_SIZE bytes in Flash
 *  Arguments        :
 *                     - destination: offset address to pflash base
 *                     - number: number of verify section aligned unit
 *                     - marginLevel: margin level used to verify
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_FlashEraseVerifySection(
    eeprom_emulation_handle_t *handle, uint32_t destination, uint16_t Number, uint8_t marginLevel))
{
    uint32_t result = EE_OK;
    uint32_t dest   = destination;
    uint32_t margin = marginLevel;

    /* load FCCOB registers */
    FMU0->FCCOB[0] = RD1SCR;
    FMU0->FCCOB[1] = margin;
    FMU0->FCCOB[2] = dest;

    /*Check if previous command complete, wait for CCIF set */
    while (0U == (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /*Clear status*/
    FMU0->FSTAT = FMU_FSTAT_ACCERR_MASK | FMU_FSTAT_PVIOL_MASK | FMU_FSTAT_CMDABT_MASK;

    /*Clear CCIF to launch the command*/
    FMU0->FSTAT = FMU_FSTAT_CCIF_MASK;
    while (0U != (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /* wait until command complete */
    while (0U == (FMU0->FSTAT & FMU_FSTAT_CCIF_MASK))
    {
    }

    /*check for errors*/
    if (0U != (FMU0->FSTAT & FMU_FSTAT_FAIL_MASK))
    {
        result = EE_NOT_OK;
    }

    return result;
}

/*******************************************************************************
 *
 *  Function Name    : EE_SingleProgram
 *  Description      : Program 1 programmable size to Flash
 *  Arguments        :
 *                     - destination: offset address to flash block base
 *                     - pData: pointer to point to data to be programmed.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_SingleProgram(eeprom_emulation_handle_t *handle,
                                                      uint32_t destination,
                                                      uint8_t *pData))
{
    assert(handle != NULL);

    uint32_t i;
    uint32_t const *src = (uint32_t const *)(void const *)pData;
    uint32_t result     = EE_OK;

    destination -= handle->flashStartAddress;

    /*Load Program PHR command*/
    FMU0->FCCOB[0] = PGMPHR;

    /* Check if previous command complete, wait for CCIF set*/
    while (0x00U == (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /* clear CMDABT & ACCERR & PVIOL flag in flash status register */
    FMU0->FSTAT = (FLASH_FSTAT_CMDABT_MASK | FLASH_FSTAT_ACCERR_MASK | FLASH_FSTAT_PVIOL_MASK);

    /* clear ccif */
    FMU0->FSTAT = FLASH_FSTAT_CCIF_MASK;
    while (0x00U != (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /* program */
    while (0x00U == (FMU0->FSTAT & FLASH_FSTAT_PEWEN_MASK))
    {
    }

    /* Must be write 4 consecutive words */
    for (i = 0; i < 4U; i++)
    {
        *((uint32_t *)(destination + i * 4U)) = src[i];
    }

    while (0x00U == (FMU0->FSTAT & FLASH_FSTAT_PERDY_MASK))
    {
    }

    FMU0->FSTAT = FLASH_FSTAT_PERDY_MASK;
    while (0x00U != (FMU0->FSTAT & FLASH_FSTAT_PERDY_MASK))
    {
    }

    /* wait for command complete */
    while (0x00U == (FMU0->FSTAT & FLASH_FSTAT_CCIF_MASK))
    {
    }

    /*check for errors*/
    if (0x00U != (FMU0->FSTAT & FMU_FSTAT_FAIL_MASK))
    {
        result = EE_NOT_OK;
    }

    return result;
}

/*******************************************************************************
 *
 *  Function Name    : EE_SingleProgramCheck
 *  Description      : Program check for 1 program check size in PFlash
 *  Arguments        :
 *                     - destination: offset address to pflash block base
 *                     - pExpectedData: expected data to be verified
 *                     - margin level: margin level to be verified.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_SingleProgramCheck(eeprom_emulation_handle_t *handle,
                               uint32_t destination,
                               uint8_t *pExpectedData,
                               uint8_t marginLevel)
{
    assert(handle != NULL);
    assert(pExpectedData != NULL);

    uint32_t result = EE_OK;
    uint32_t tmp;

    destination -= handle->flashStartAddress;

    tmp = *((uint32_t *)(void *)pExpectedData);

    if (READ32(destination) != tmp)
    {
        result = EE_NOT_OK;
    }

    return result;
}

/*  Disable cache within flash controller */
void FLASH_CACHE_Disable(void)
{
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_CACHE_CLEAR_MASK)) | SMSCM_CACHE_CLEAR(0x1);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_CACHE_CLEAR_MASK)) | SMSCM_CACHE_CLEAR(0x8);
    SMSCM->OCMDR0 = (SMSCM->OCMDR0 & (~SMSCM_SPECULATION_DISABLE_MASK)) | SMSCM_SPECULATION_DISABLE_MASK;
    __ISB();
    __DSB();
}

/*middle*/
/*******************************************************************************
 *
 *  Function Name    : EE_NextSector
 *  Description      : This function is used to get address of the next sector in
 *                     the round-robin sequence
 *  Arguments        :
 *                     - addr: address of the current sector
 *  Return Value     :
 *                     - address of the next sector
 *
 *******************************************************************************/
uint32_t EE_NextSector(eeprom_emulation_handle_t *handle, uint32_t addr)
{
    uint32_t nextSectorAddr;

    if (addr == (g_eeEndAddress - (uint32_t)handle->eeSectorSize))
    {
        nextSectorAddr = handle->eeStartAddress;
    }
    else
    {
        nextSectorAddr = addr + (uint32_t)handle->eeSectorSize;
    }

    return nextSectorAddr;
}

/*******************************************************************************
 *
 *  Function Name    : EE_PrevSector
 *  Description      : This function is used to get address of the previous
 *                     sector in the round-robin sequence
 *  Arguments        :
 *                     - addr: address of the current sector
 *  Return Value     :
 *                     - address of the next sector
 *
 *******************************************************************************/
uint32_t EE_PrevSector(eeprom_emulation_handle_t *handle, uint32_t addr)
{
    uint32_t prevSectorAddr;

    if (addr == handle->eeStartAddress)
    {
        prevSectorAddr = g_eeEndAddress - handle->eeSectorSize;
    }
    else
    {
        prevSectorAddr = addr - handle->eeSectorSize;
    }

    return prevSectorAddr;
}

/*******************************************************************************
 *
 *  Function Name    : EE_VerifyRecordStatus
 *  Description      : This function is to verify the record status.
 *  Arguments        :
 *                     - dest: destination point to record status.
 *                     - expData: the expected data at record status location.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_VerifyRecordStatus(eeprom_emulation_handle_t *handle, uint32_t dest, uint32_t expData)
{
    uint32_t programCheckSize = handle->ftfxPGMCheckSize;

    if (handle->ftfxProgramSize != FTFx_LONGWORD_SIZE)
    {
        dest = (dest / programCheckSize) * programCheckSize;
        return (EE_SingleProgramCheck(handle, dest, (uint8_t *)&expData, handle->flashReadMargin));
    }
    else
    {
        uint32_t returnCode = EE_OK;
        if ((uint16_t)(expData >> 16u) != READ16(dest))
        {
            returnCode = EE_NOT_OK;
        }
        return (returnCode);
    }
}

/*******************************************************************************
 *
 *  Function Name    : EE_VerifySectorHeader
 *  Description      : This function is to verify the data in sector header.
 *  Arguments        :
 *                     - dest: destination need to verify.
 *                     - expData: the expected data at destination.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_VerifySectorHeader(eeprom_emulation_handle_t *handle, uint32_t dest, uint32_t expData)
{
    return (EE_SingleProgramCheck(handle, dest, (uint8_t *)&expData, handle->flashReadMargin));
}

/*******************************************************************************
 *
 *  Function Name    : EE_MultiProgram
 *  Description      : This function will program a range of contiguous Flash
 *                     locations (multiple programmable size) and verify them.
 *  Arguments        :
 *                     - dest: destination to program
 *                     - size: size to be programmed
 *                     - pData: source data
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_MultiProgram(eeprom_emulation_handle_t *handle, uint32_t dest, uint32_t size, uint8_t *pData)
{
    /* Declaration of the local variables */
    uint32_t returnCode  = EE_OK;
    uint32_t programSize = handle->ftfxProgramSize;
    uint8_t *pPtr;
    pPtr = pData;

    while ((size > 0x00u) && (returnCode == EE_OK))
    {
        /* PFlashProgram function called */
        returnCode = EE_SingleProgram(handle, dest, pPtr);

        dest += programSize;
        size -= programSize;
        pPtr += programSize;
    }
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_CopyRecord
 *  Description      : writes user data into Flash in a record format to
 *                     g_freeSpaceAddress.
 *  Arguments        :
 *                     - dataRecord: store record addr and record ID need to be
 *                       copied.
 *                     - remainData: the buffer to store remaining data in case
 *                       of writing new record. In case swapping, this input
 *                       must be 0xFFFFFFFF.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_CopyRecord(eeprom_emulation_handle_t *handle,
                       eeprom_emulation_data_record_t dataRecord,
                       uint8_t remainData[])
{
    uint32_t returnCode = EE_OK;
    uint32_t alginedSize;
    uint32_t remainingSize;
    uint32_t address = dataRecord.dataAddr;

    /*Calculate data value aligned part and remaining part */
    alginedSize   = handle->eeDataValueSize - (handle->eeDataValueSize % handle->ftfxProgramSize);
    remainingSize = handle->eeSectorRecordLength - alginedSize - handle->ftfxProgramSize - handle->complementSize;

    /* when writing new data, source data is in ram, so it is word address */
    if (remainData == (uint8_t *)0xFFFFFFFFu) /* copy data */
    {
        alginedSize = handle->eeSectorRecordLength;
        /* when copy data, source address is in flash, so it is byte address */
        address = dataRecord.dataAddr;
    }
    /* for swapping, entire record is written within EE_MultiProgram*/
    /* for writing new data, need to write aligned part first, and then write remaining data, and then write status*/
    returnCode = EE_MultiProgram(handle, g_freeSpaceAddress, alginedSize, (uint8_t *)address);
    if (remainData != (uint8_t *)0xFFFFFFFFu) /* write new data, need to program ID and over-program status*/
    {
        /* remaining data including ID*/
        if (returnCode == EE_OK)
        {
            returnCode = EE_MultiProgram(handle, g_freeSpaceAddress + alginedSize + handle->ftfxProgramSize,
                                         handle->ftfxProgramSize, remainData);
        }

        /* 0xFF setting. */
        remainData[(uint8_t)remainingSize - 0x01U] = 0xFF;
        remainData[(uint8_t)remainingSize - 0x02U] = 0xFF;

        /*and then program status*/
        if (returnCode == EE_OK)
        {
            remainData[(uint8_t)remainingSize - 0x02u] = (uint8_t)((uint16_t)EE_RECORD_STATUS_VALID & 0x00FFu);
            remainData[(uint8_t)remainingSize - 0x01u] = (uint8_t)((uint16_t)EE_RECORD_STATUS_VALID >> 0x08u);
            returnCode = EE_MultiProgram(handle, g_freeSpaceAddress + alginedSize, handle->ftfxProgramSize, remainData);
        }
    }
#if EE_CACHETABLE_ENABLE
    if (returnCode == EE_OK)
    {
        /* this record is written successful, so update cache table */
        /* Check if the ID is a cache table entry */
        if (EE_CACHETABLE_MAX_ENTRY >= dataRecord.dataID)
        {
            /* Update the cache table item with new value */
            WRITE32(EE_CACHETABLE_ITEM_ADDR(dataRecord.dataID), g_freeSpaceAddress);
        }
    }
#endif
    g_freeSpaceAddress += handle->eeSectorRecordLength;
    return (returnCode);
}

/*******************************************************************************
*
*  Function Name    : EE_SwapSector
*  Description      : Swaps the contents of the oldest active sector to
                      the new sector
*  Arguments        : N/A
*  Return Value     :
*                     - EE_OK if successful
*                     - EE_NOT_OK if failed in erase oldest active sector
*                     - EE_ERR_UPDATE fail when copy records swapping
*
*******************************************************************************/
uint32_t EE_SwapSector(eeprom_emulation_handle_t *handle)
{
    eeprom_emulation_data_record_t dataRecord;
    uint32_t oldSectorAddress;
    uint32_t newActSectorAddr;
    uint32_t bk_currentActiveSector;
    uint32_t recordAddress;
    uint32_t recFoundAddress;
    const uint32_t dataSource = 0xFFFFFFFFu; /* Used to indicate swapping while copying data */
    uint32_t returnCode       = EE_OK;
    uint32_t blankCheck;
    uint32_t aliveCheck;
    uint16_t dataID;

    /* backup current active sector for later usage*/
    bk_currentActiveSector = g_currentActiveSector;
    newActSectorAddr       = g_currentActiveSector;

    /* The first Alternative or ready sector after the current active sector is the sector
    used for update. At this time, next sector can be Dead, ready or alternative only.
    So, need to check if next sector is not DEAD, it means this sector is ready or alternative*/
    do
    {
        newActSectorAddr = EE_NextSector(handle, newActSectorAddr);
        blankCheck       = EE_VerifySectorHeader(handle, newActSectorAddr + handle->eeSectorDeadIndOffset,
                                           (uint32_t)EE_DATA_STATUS_BLANK);
        aliveCheck       = EE_VerifySectorHeader(handle, newActSectorAddr + handle->eeSectorDeadIndOffset,
                                           (uint32_t)EE_DATA_STATUS_ALIVE);
    } while ((EE_OK != blankCheck) && (EE_OK != aliveCheck));

    g_freeSpaceAddress = newActSectorAddr + (uint32_t)handle->eeSectorHeaderSize;
    /* At this time, sure new sector is active one, so need to update g_currentActiveSector to this sector */
    g_currentActiveSector = newActSectorAddr;

    /* find the oldest active sector */
    oldSectorAddress = EE_FindActSector(handle, handle->eeStartAddress, false, false);
    /* point to last record in oldest active sector */
    recordAddress = oldSectorAddress + handle->eeSectorSize - handle->eeSectorWaste - handle->eeSectorRecordLength;

    /* Decrement copy */
    while (recordAddress >= (oldSectorAddress + handle->eeSectorHeaderSize))
    {
        /* only read record ID if record status is VALID*/
        if (EE_OK == EE_VerifyRecordStatus(handle, recordAddress + handle->eeRecordStatusOffset,
                                           (((uint32_t)(EE_RECORD_STATUS_VALID) << 16u) | 0x0000FFFFu)))
        {
            dataID = READ16(recordAddress + handle->eeRecordIDOffset);

            /* search this ID in all active sectors from bottom up and from newest to oldest one */
            recFoundAddress = EE_SearchLoop(handle, dataID);
            /* Means this is latest ID, which is only one in all sectors, and no rewrite it
               again with new data at this same daia-id , and need to copy it */
            if (recFoundAddress == recordAddress)
            {
                /* copy this ID to new sector */
                dataRecord.dataID   = dataID;
                dataRecord.dataAddr = recFoundAddress;
                /* Means This unique data-ID is the same as the data-ID to be written, ignore rewrite */
                if (dataRecord.dataID == g_dataRecord.dataID)
                {
                    recordAddress -= handle->eeSectorRecordLength;
                    continue;
                }

                returnCode = EE_CopyRecord(handle, dataRecord, (uint8_t *)dataSource);
                if (returnCode != EE_OK)
                {
                    returnCode = EE_ERR_UPDATE;
                    break;
                }
            }
        }
        /* point to next record */
        recordAddress -= handle->eeSectorRecordLength;
    }

    /* finish copying */
    /* make new sector as active */
    if (returnCode == EE_OK)
    {
        returnCode = EE_ValidateActIndicator(handle, newActSectorAddr);
        if (returnCode != EE_OK)
        {
            returnCode = EE_ERR_UPDATE;
        }
    }
    else
    {
        g_currentActiveSector = bk_currentActiveSector;
        g_freeSpaceAddress    = g_currentActiveSector + handle->eeSectorSize - handle->eeSectorWaste;
/* update cache table to restore the address of all ID like before copying */
#if (EE_CACHETABLE_ENABLE == true)
        EE_UpdateCacheTable(handle);
#endif
    }

    if (returnCode == EE_OK)
    {
        /* At this time, new sector is already be active successfully*/
        /* backup erase cycle of old active sector */
        g_eraseCycles[0] = READ32(oldSectorAddress + handle->eeSectorEraseCycleOffset);
        if (g_eraseCycles[0] != (uint32_t)EE_MAX_ERASING_CYCLE_VALUE)
        {
            /* increase erase cycle if it is not maximum value */
            g_eraseCycles[0]++;
        }
/* synchronous model */
#if (EE_USE_ASYNCHRONOUS_MODEL != true)
        /* erase the old active sector. */
        returnCode = EE_ReEraseEeprom(handle, oldSectorAddress);
        if (returnCode == EE_OK)
        {
            /* only program erase cycle if validate sector successfully and this is not dead sector */
            returnCode = EE_ValidateEraseCycle(handle, oldSectorAddress, (uint8_t *)&g_eraseCycles);
            if (returnCode != EE_OK)
            {
                returnCode = EE_CheckAvailabilityStatus(handle);
            }
        }
        if (returnCode == EE_MAKEDEAD_OK)
        {
            returnCode = EE_CheckAvailabilityStatus(handle);
        }

#else /* asynchronous model */
        g_addressToMain    = oldSectorAddress; /* initialize g_addressToMain variable */
        g_endAddressToMain = oldSectorAddress + handle->eeSectorSize;
        EE_AsyncFlashErase(handle, g_addressToMain);
#endif
    }
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_SearchInSector
 *  Description      : Searches the latest record in given sector.
 *  Arguments        :
 *                     - dataID: expected ID to search
 *                     - sectorAddress: start address of sector to be searched
 *  Return Value     :
 *                     - address of found record
 *                     - 0xFFFFFFFF If not found
 *
 *******************************************************************************/
uint32_t EE_SearchInSector(eeprom_emulation_handle_t *handle, uint16_t expID, uint32_t sectorAddress)
{
    uint32_t returnCode = 0xFFFFFFFFu;
    uint32_t recordAddress;
#if EE_CALLBACK_ENABLE
    uint32_t counter = 0x00u;
#endif

    if (sectorAddress == g_currentActiveSector)
    {
        /* point to last record of current active sector */
        recordAddress = g_freeSpaceAddress;
    }
    else
    {
        /* point to end of sector if this is not current active sector because it is full of data */
        recordAddress = sectorAddress + handle->eeSectorSize - handle->eeSectorWaste;
    }
    /* point to beginning of the first record */
    sectorAddress += handle->eeSectorHeaderSize;
    /* Search all the records of the sector */
    do
    {
        /* Decrement recordAddress by EE_RECORD_LENGTH to point to next record*/
        recordAddress -= handle->eeSectorRecordLength;
        /* verify if record status is valid */
        if (EE_OK == EE_VerifyRecordStatus(handle, recordAddress + handle->eeRecordStatusOffset,
                                           (((uint32_t)(EE_RECORD_STATUS_VALID) << 16u) | 0x0000FFFFu)))
        {
            /* read record ID */
            if (expID == READ16(recordAddress + handle->eeRecordIDOffset))
            {
                returnCode = recordAddress;
                break;
            }
        }
        /* If CallBack is enabled, then serve callback function if counter reaches limitation */
#if EE_CALLBACK_ENABLE
        /* Check if need to serve callback function */
        counter++;
        if (counter >= (uint32_t)EE_CALLBACK_COUNTER)
        {
            g_EECallBack();
            /* Reset counter */
            counter = 0x00u;
        }
#endif
    } while (recordAddress > sectorAddress);
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_SearchBlankSpace
 *  Description      : To find blank space for each sector
 *  Arguments        :
 *                     - sectorAddress: start address of sector to find blank space.
 *  Return Value     :
 *                     - blank space of this sector
 *
 *******************************************************************************/
uint32_t EE_SearchBlankSpace(eeprom_emulation_handle_t *handle, uint32_t sectorAddress)
{
    uint32_t searchAddress;
#if EE_CALLBACK_ENABLE
    uint32_t counter = 0x00u;
#endif
    /* flag to indicate this record is blank or not */
    bool blankFlag;
    /* backup blank flag. Initilize it as true to handle with the first search is non blanked record */
    bool bkBlankFlag = true;

    /* point to the beginning of each record. Start with the last record within each sector */
    searchAddress = sectorAddress + handle->eeSectorSize - handle->eeSectorWaste;
    /* point to beginning of the first record */
    sectorAddress += (uint32_t)handle->eeSectorHeaderSize;
    /* Search all the records of the sector */
    do
    {
        /* Decrement searchAddress by EE_RECORD_LENGTH */
        searchAddress -= handle->eeSectorRecordLength;
        /* Do blank check for every record length from bottom up*/
        if (EE_OK == EE_BlankCheck(handle, searchAddress, handle->eeSectorRecordLength))
        {
            blankFlag = true; /* this record is blanked */
        }
        else /* this record is not blank */
        {
            if (bkBlankFlag == true) /* and the next record is blank */
            {
                /* point to blank space */
                searchAddress = searchAddress + handle->eeSectorRecordLength;
                break;
            }
        }

        /* backup dataID for the next search */
        bkBlankFlag = blankFlag;

        /* If CallBack is enabled, then serve callback function if counter reaches limitation */
#if EE_CALLBACK_ENABLE
        /* Check if need to serve callback function */
        counter++;

        if (counter >= (uint32_t)EE_CALLBACK_COUNTER)
        {
            g_EECallBack();
            /* Reset counter */
            counter = 0x00u;
        }
#endif
    } while (searchAddress > sectorAddress);

    return (searchAddress);
}

/*******************************************************************************
 *
 *  Function Name    : EE_SearchInCache
 *  Description      : Searches record with a specific record ID in cache table
 *  Arguments        :
 *                     - dataID: the ID required to search
 *  Return Value     :
 *                     - address of found record
 *                     - 0xFFFFFFFF If not found
 *
 *******************************************************************************/
#if EE_CACHETABLE_ENABLE
uint32_t EE_SearchInCache(uint16_t dataID)
{
    uint32_t returnCode = 0xFFFFFFFFu;
    /* Check if the DataID is in the cache table */
    if (EE_CACHETABLE_MAX_ENTRY >= dataID)
    {
        returnCode = READ32(EE_CACHETABLE_ITEM_ADDR(dataID));
    }
    return (returnCode); /* not found return 0xFFFFFFFFu */
}
#endif

/*******************************************************************************
 *
 *  Function Name    : EE_SearchInAllActive
 *  Description      : Searches record with a specific record ID in all
 *                     active sector from bottom up and from newest to oldest
 *                     active sector. Don't search in cache table.
 *  Arguments        :
 *                     - dataID is the expected ID to be searched.
 *  Return Value     :
 *                     - address of found record
 *                     - 0xFFFFFFFF If not found
 *
 *******************************************************************************/
uint32_t EE_SearchInAllActives(eeprom_emulation_handle_t *handle, uint16_t dataID)
{
    uint32_t sectorAddress = g_currentActiveSector;
    uint32_t recordAddress;
    uint32_t returnCode = 0xFFFFFFFFu;
    uint8_t actNum;
    actNum = (uint8_t)handle->eeActiveSectors;
    /* Search in the ACTIVE sectors only. Start with current active sector */
    do
    {
        /* only search in the active sector, ignore alt, ready and dead sectors */
        if (EE_SECTOR_ACTIVE == EE_GetSectorStatus(handle, sectorAddress))
        {
            actNum--;
            recordAddress = EE_SearchInSector(handle, dataID, sectorAddress);
            if (recordAddress != 0xFFFFFFFFu)
            {
                /* break if found the expected ID */
                returnCode = recordAddress;
                break;
            }
        }
        /* search the previous sector */
        sectorAddress = EE_PrevSector(handle, sectorAddress);
    } while (actNum > 0x00u);
    return (returnCode); /* not found return 0xFFFFFFFFu */
}

/*******************************************************************************
 *
 *  Function Name    : EE_SearchLoop
 *  Description      : Searches record with a specific record ID in cache table
 *                     first. If not found in cache, continue to search in all
 *                     active sectors from newest to oldest and from bottom to
 *                     top.
 *  Arguments        :
 *                     - dataID: required ID to be searched.
 *  Return Value     :
 *                     - address of found record
 *                     - 0xFFFFFFFF If not found
 *
 *******************************************************************************/
uint32_t EE_SearchLoop(eeprom_emulation_handle_t *handle, uint16_t dataID)
{
    uint32_t recordAddress = 0xFFFFFFFFu;
    /* Check if cache table is enabled and data is in valid range of cache, search in cache first */
#if EE_CACHETABLE_ENABLE
    if (dataID <= (uint16_t)EE_CACHETABLE_MAX_ENTRY)
    {
        recordAddress = EE_SearchInCache(dataID);
        return recordAddress;
    }
#endif

#if EE_CACHETABLE_ENABLE
    if (dataID > (uint16_t)EE_CACHETABLE_MAX_ENTRY)
    {
#endif
        /* ID is not in the cache table, need to search in all active sectors */
        recordAddress = EE_SearchInAllActives(handle, dataID);
#if EE_CACHETABLE_ENABLE
    }
#endif

    return recordAddress;
}

/*******************************************************************************
 *
 *  Function Name    : EE_BlankCheck
 *  Description      : Do blank check for a specific flash range.
 *  Arguments        :
 *                     - address: address needs to do blank check.
 *                     - size: size to do blank check.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_BlankCheck(eeprom_emulation_handle_t *handle, uint32_t address, uint32_t size)
{
    uint32_t returnCode      = EE_OK;
    uint32_t read1SectorSize = handle->ftfxRD1SECSize;

    while ((size > 0x00u) && (returnCode == EE_OK))
    {
        if ((GET_MOD(address, read1SectorSize) != 0x00u) || (size < read1SectorSize))
        {
            /* blank check by READ32 if address is not aligned or size < FTFx_RD1SEC_SIZE*/
            returnCode = EE_VerifySectorHeader(handle, address, 0xFFFFFFFFu);
            if (returnCode == EE_OK)
            {
                address += FTFx_LONGWORD_SIZE;
                size -= FTFx_LONGWORD_SIZE;
            }
            else
            {
                returnCode = EE_NOT_OK;
            }
        }
        else
        {
            /* blank check by verify section if address is aligned
            and size is larger than 1 RD1PHR aligned size*/
            returnCode = EE_FlashEraseVerifySection(handle, address, (uint16_t)(size / read1SectorSize),
                                                    handle->flashReadMargin);
            if (returnCode == EE_OK)
            {
                /* if erase verify section returns OK, mean entire sector is blank*/
                address += (size / read1SectorSize) * read1SectorSize;
                size -= (size / read1SectorSize) * read1SectorSize;
            }
            else
            {
                returnCode = EE_NOT_OK;
            }
        }
    }
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_GetSectorStatus
 *  Description      : This function returns the status of the sector by ignoring
 *                     the validation of erase cycle value.
 *  Arguments        :
 *                     - sectorAddress: start address of sector
 *  Return Value     :
 *                     - status of sector
 *
 *******************************************************************************/
uint8_t EE_GetSectorStatus(eeprom_emulation_handle_t *handle, uint32_t sectorAddress)
{
    uint8_t returnCode    = 0x00u;
    uint32_t deadIndValue = 0x00u; /* data in dead indicator */
    uint32_t actIndValue  = 0x00u; /* data in active indicator */

    if (EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorDeadIndOffset, EE_DATA_STATUS_BLANK) == EE_OK)
    {
        deadIndValue = (uint32_t)EE_DATA_STATUS_BLANK;
    }
    if (EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorActIndOffset, EE_DATA_STATUS_BLANK) == EE_OK)
    {
        actIndValue = (uint32_t)EE_DATA_STATUS_BLANK;
    }

    if (deadIndValue != (uint32_t)EE_DATA_STATUS_BLANK)
    {
        /* if dead indicator is not blank or alive, this is dead sector */
        returnCode = EE_SECTOR_DEAD;
    }
    if (returnCode != EE_SECTOR_DEAD)
    {
        if (actIndValue != EE_DATA_STATUS_BLANK)
        {
            if (EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorEraseCycleOffset, 0xFFFFFFFFu) != EE_OK)
            {
                returnCode = EE_SECTOR_ACTIVE;
            }
            else
            {
                returnCode = EE_SECTOR_INVALID;
            }
        }
        else
        {
            /* From now on, active indicator is blank,
            dead indicator is blank or alive,
            sector area exclusive sector header is blank.*/
            if (EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorEraseCycleOffset, 0xFFFFFFFFu) != EE_OK)
            {
                if (EE_BlankCheck(handle, sectorAddress + (uint32_t)handle->eeSectorHeaderSize,
                                  handle->eeSectorSize - handle->eeSectorHeaderSize) == EE_OK)
                {
                    /* at this time, have data in erase cycle location, active indicator is blank
                    dead indicator is blank or alive*/
                    /* if dead indicator is blank, this sector is alternative */
                    returnCode = EE_SECTOR_ALTERNATIVE;
                }
                else
                {
                    returnCode = EE_SECTOR_INVALID;
                }
            }
            /*At this time, active indicator is blank,
            dead indicator is blank or alive,
            no data in erase cycle,
            sector area exclusive sector header is blank*/
            else
            {
                if (EE_BlankCheck(handle, sectorAddress + (uint32_t)handle->eeSectorHeaderSize,
                                  handle->eeSectorSize - handle->eeSectorHeaderSize) == EE_OK)
                {
                    /* at this time, have data in erase cycle location, active indicator is blank
                    dead indicator is blank or alive*/
                    /* if dead indicator is blank, this sector is alternative */
                    returnCode = EE_SECTOR_BLANK;
                }
                else
                {
                    returnCode = EE_SECTOR_INVALID;
                }
            }
        }
    }

    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_FindActSector
 *  Description      : This function will find the oldest/newest or active
 *                     sectors according to closestFlag flag.
 *  Arguments        : - sectorAddress: current sector address.
 *                     - closestFlag: flag to find the closest (true) active
 *                       sector or most far (false) sector.
 *                     - nextFlag: flag to find the active sector in the
 *                       right (true) or in the left (false).
 *  Return Value     :
 *                     - address of found record
 *                     - 0xFFFFFFFF If not found
 *
 *******************************************************************************/
uint32_t EE_FindActSector(eeprom_emulation_handle_t *handle, uint32_t sectorAddress, bool closestFlag, bool nextFlag)
{
    uint32_t returnCode = 0xFFFFFFFFu;
    uint32_t i;
    uint8_t sectorStatus;

    for (i = 0x00u; i < handle->eeAllotedSectors; i++)
    {
        if (nextFlag == true)
        {
            sectorAddress = EE_NextSector(handle, sectorAddress);
        }
        else
        {
            sectorAddress = EE_PrevSector(handle, sectorAddress);
        }
        sectorStatus = EE_GetSectorStatus(handle, sectorAddress);
        if ((EE_SECTOR_ACTIVE == sectorStatus) ||
            ((EE_SECTOR_ALTERNATIVE == sectorStatus) && (returnCode != 0xFFFFFFFFu)))
        {
            if (closestFlag == true)
            {
                returnCode = sectorAddress;
            }
            else
            {
                if (EE_SECTOR_ACTIVE == sectorStatus)
                {
                    returnCode = sectorAddress;
                }
                else
                {
                    i = handle->eeAllotedSectors;
                }
            }
        }
    }
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_GetSectorNumber
 *  Description      : This function will calculate sector number based on its
 *                     state.
 *  Arguments        :
 *                     - expStatus: expected status to accumulate sector number
 *  Return Value     :
 *                     - total number of sector for expected status
 *
 *******************************************************************************/
uint8_t EE_GetSectorNumber(eeprom_emulation_handle_t *handle, uint8_t expStatus)
{
    uint32_t sectorAddress;
    uint8_t sectorStatus;
    uint8_t cnt = 0x00u;
    uint8_t i;
    /* initialize value for pNum*/
    sectorAddress = handle->eeStartAddress;
    for (i = 0x00u; i < handle->eeAllotedSectors; i++)
    {
        sectorStatus = EE_GetSectorStatus(handle, sectorAddress);
        if (sectorStatus == expStatus)
        {
            cnt++;
        }
        /* sectorAddress += handle->eeSectorSize */
        sectorAddress = EE_NextSector(handle, sectorAddress);
    }
    return (cnt);
}

/*******************************************************************************
 *
 *  Function Name    : EE_ValidateDeadIndicator
 *  Description      : This function is to make a sector as DEAD
 *  Arguments        :
 *                     - sectorAddress: address of sector
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_ValidateDeadIndicator(eeprom_emulation_handle_t *handle, uint32_t sectorAddress)
{
    uint32_t returnCode = EE_OK;
    uint32_t data[2];
    uint8_t num = 0x00u;
    data[0]     = (uint32_t)EE_DATA_STATUS_DEAD;
    if (handle->ftfxProgramSize > FTFx_LONGWORD_SIZE)
    {
        data[1] = 0xFFFFFFFFu;
    }
    sectorAddress += (uint32_t)handle->eeSectorDeadIndOffset;
    do
    {
        returnCode = EE_MultiProgram(handle, sectorAddress, handle->ftfxProgramSize, (uint8_t *)&data);
        /* verify again */
        /* point to dead indicator address */
        if (EE_OK == EE_VerifySectorHeader(handle, sectorAddress, (uint32_t)EE_DATA_STATUS_BLANK))
        {
            num++;
            /* if after making this as DEAD but the data is still BLANK or ALIVE
            it means validate fails*/
            if (num > handle->eeRetryMax)
            {
                returnCode = EE_NOT_OK;
            }
        }
        else
        {
            returnCode = EE_OK;
        }
    } while ((returnCode != EE_OK) && (num <= handle->eeRetryMax));
    return (returnCode);
}
/*******************************************************************************
 *
 *  Function Name    : EE_ValidateEraseCycle
 *  Description      : This function will program erase cycle.
 *                     If possible, it will make this sector as DEAD if fails in
 *                     programming.
 *  Arguments        :
 *                     - sectorAddress: address of invalid sector
 *                     - pData: pointer for expected erase cycle value
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_ValidateEraseCycle(eeprom_emulation_handle_t *handle, uint32_t sectorAddress, uint8_t *pData)
{
    uint32_t returnCode = EE_OK;
    uint32_t ret        = EE_OK;
    uint8_t num         = 0x00u;

    do
    {
        returnCode =
            EE_MultiProgram(handle, sectorAddress + handle->eeSectorEraseCycleOffset, handle->ftfxProgramSize, pData);
        if (returnCode != EE_OK)
        {
            ret = EE_ReEraseEeprom(handle, sectorAddress);
            if (ret != EE_OK)
            {
                returnCode = ret;
                break;
            }
            else
            {
                num++;
                if (num > handle->eeRetryMax)
                {
                    returnCode = EE_ValidateDeadIndicator(handle, sectorAddress);
                    if (returnCode == EE_OK)
                    {
                        returnCode = EE_MAKEDEAD_OK;
                    }
                }
            }
        }
    } while ((returnCode != EE_OK) && (num <= handle->eeRetryMax));
    return (returnCode);
}
/*******************************************************************************
 *
 *  Function Name    : EE_ValidateActIndicator
 *  Description      : This function will program data to active indicator.
 *                     If possible, it will make this sector as DEAD if fails in
 *                     programming.
 *  Arguments        :
 *                     - sectorAddress: address sector
 *                     - deadNum: current number of dead sector
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *
 *******************************************************************************/
uint32_t EE_ValidateActIndicator(eeprom_emulation_handle_t *handle, uint32_t sectorAddress)
{
    uint32_t returnCode = EE_OK;
    uint32_t ret        = EE_OK;
#if (defined(FLASH_PGM_SIZE) && (FLASH_PGM_SIZE == 16))
    uint32_t data[4];
#else
    uint32_t data[2];
#endif
    uint8_t num = 0x00u;

    data[0] = (uint32_t)EE_DATA_STATUS_ACTIVE;
    if (handle->ftfxProgramSize > FTFx_LONGWORD_SIZE)
    {
#if (defined(FLASH_PGM_SIZE) && (FLASH_PGM_SIZE == 16))
        data[1] = 0xFFFFFFFFu;
        data[2] = 0xFFFFFFFFu;
        data[3] = 0xFFFFFFFFu;
#else
        data[1] = 0xFFFFFFFFu;
#endif
    }
    do
    {
        ret = EE_MultiProgram(handle, sectorAddress + (uint32_t)handle->eeSectorActIndOffset, handle->ftfxProgramSize,
                              (uint8_t *)&data);
        ret = EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorActIndOffset, EE_DATA_STATUS_BLANK);
        if (ret != EE_OK)
        {
            break;
        }
        else
        {
            num++;
            if (num > handle->eeRetryMax)
            {
                returnCode = EE_ValidateDeadIndicator(handle, sectorAddress);
                if (returnCode == EE_OK)
                {
                    returnCode = EE_MAKEDEAD_OK;
                }
            }
        }
    } while (num <= handle->eeRetryMax);

    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_ReEraseEeprom
 *  Description      : This function will re-erase 1 sector with several times
 *  Arguments        :
 *                     - sectorAddress: the address of sector need to re-erase
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if re-erase fail and make DEAD fail
 *                     - EE_MAKEDEAD_OK if re-erase fail and make DEAD successful
 *
 *******************************************************************************/
uint32_t EE_ReEraseEeprom(eeprom_emulation_handle_t *handle, uint32_t sectorAddress)
{
    uint32_t returnCode = EE_OK;
    uint8_t num         = 0x00u;

    do
    {
        /* if re-erase sector fail, re-erase several times before make it to DEAD sector */
        returnCode = EE_SyncFlashErase(handle, sectorAddress);
        if (returnCode != EE_OK)
        {
            num++;
            if (num > handle->eeRetryMax)
            {
                returnCode = EE_ValidateDeadIndicator(handle, sectorAddress);
                if (returnCode == EE_OK)
                {
                    returnCode = EE_MAKEDEAD_OK;
                }
            }
        }
    } while ((returnCode != EE_OK) && (num <= handle->eeRetryMax));
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_ReEraseEeprom
 *  Description      : This function will re-erase 1 sector with several times
 *  Arguments        : N/A
 *  Return Value     :
 *                     - EE_OK if enough sector for working sequence
 *                     - EE_NOT_OK if not enough sector for working sequence
 *
 *******************************************************************************/
uint32_t EE_CheckAvailabilityStatus(eeprom_emulation_handle_t *handle)
{
    uint32_t returnCode = EE_OK;
    uint32_t sectorAddress;
    uint32_t sectorStatus;
    uint8_t totalAliveSector = 0x00u;
    uint8_t i;
    sectorAddress = handle->eeStartAddress;
    for (i = 0x00u; i < handle->eeAllotedSectors; i++)
    {
        sectorStatus = EE_GetSectorStatus(handle, sectorAddress);
        if ((sectorStatus == EE_SECTOR_BLANK) || (sectorStatus == EE_SECTOR_ALTERNATIVE))
        {
            totalAliveSector++;
        }
        /* sectorAddress += handle->eeSectorSize */
        sectorAddress = EE_NextSector(handle, sectorAddress);
    }
    if (totalAliveSector < handle->eeActualReadySectors)
    {
        returnCode = EE_NOT_OK;
    }
    return (returnCode);
}
/*******************************************************************************
 *
 *  Function Name    : EE_UpdateCacheTable
 *  Description      : This function will update the cache table
 *  Arguments        : N/A
 *  Return Value     : N/A
 *
 *******************************************************************************/
/* Initialize the cache table with all the values, if it is enabled */
#if EE_CACHETABLE_ENABLE
void EE_UpdateCacheTable(eeprom_emulation_handle_t *handle)
{
    uint32_t tableAddress;
    uint32_t recordAddress;
    uint16_t dataID;

    /* Hold the start address of cache table */
    tableAddress = EE_CACHETABLE_START_ADDRESS;
    /* Loop through the data ID that should be written to the Cache Table */
    for (dataID = 1u; dataID <= EE_CACHETABLE_MAX_ENTRY; dataID++)
    {
        /* Search all the ACTIVE sectors */
        recordAddress = EE_SearchInAllActives(handle, dataID);
        WRITE32(tableAddress, recordAddress);

        tableAddress += (uint32_t)EE_CACHETABLE_ITEM_SIZE;
    }
}
#endif

/*******************************************************************************
 *
 *  Function Name    : EE_ISRHandler
 *  Description      : Interrupt service routine for Command Complete.
 *  Arguments        : N/A
 *  Return Value     : N/A
 *
 *******************************************************************************/
#if (EE_USE_ASYNCHRONOUS_MODEL == true)
#ifdef DSC_CORE
#pragma interrupt
#endif
void INTERRUPT EE_ISRHandler(void) /* Flash interrupt service function */
{
    /* Disable command complete interrupt */
    REG_BIT_CLEAR(FTFx_FCNFG, FTFx_FCNFG_CCIE);

    /* checking error */
    if (0x00u != (REG_READ(FTFx_FSTAT) & FTFx_FSTAT_CHECK_ERR))
    {
        g_eraseStatusFlag = FAIL;
    }
    else
    {
        g_eraseStatusFlag = DONE;
    }
}
#endif

/* High level functions */

static uint32_t EE_PreInitCheck(eeprom_emulation_handle_t *handle)
{
    uint32_t returnCode = EE_OK; /* variable return EE_InitEeprom() function state.*/
#if (defined(FLASH_PGM_SIZE) && (FLASH_PGM_SIZE == 16))
    uint32_t expErsCycValue[4]; /* buffer to store erase cycle, which is written to erase cycle address.*/
#else
    uint32_t expErsCycValue[2]; /* buffer to store erase cycle, which is written to erase cycle address.*/
#endif
    uint32_t sectorAddress; /* variable help we know the address is activated at that time.*/
    uint32_t currentActsectorAddress = 0x00u;
    uint8_t i;

    /***********
    STEP 1: Check for the first time initialization
       This step will find and erase oldest active sector if it has more than number expected active sector .
       If erasing oldest active sector is fail, it will re-erase this sector several times before make this
       to dead sector. If make dead sector fail return EE_NOT_OK error.It will check total dead sector and
       return EE_NOT_OK error if break sequence because of not enough alive sector.
    ***********/

    if (EE_GetSectorNumber(handle, EE_SECTOR_ACTIVE) >
        (uint8_t)handle->eeActiveSectors) /* check if more than expected active sectors */
    {
        /* find oldest active sector and erase it */
        sectorAddress = EE_FindActSector(handle, handle->eeStartAddress, false, false);
        returnCode    = EE_ReEraseEeprom(handle, sectorAddress);
        if (returnCode != EE_NOT_OK)
        {
            returnCode = EE_CheckAvailabilityStatus(handle);
        }
    }
    /***********
    STEP 2: Check for other cases - isn't the first time initialization
        This step will find and erase all invalid sector. If erasing all invalid sectors is fail, it will re-erase
    all these sector several times before make them to dead sectors. If make dead sector fail return EE_NOT_OK
    error. It will check total dead sector and return EE_NOT_OK error if break sequence because of not enough alive
    sector
    ***********/
    else
    {
        /* find all invalid sector and erase it */
        sectorAddress = (uint32_t)handle->eeStartAddress;
        for (i = 0x00u; i < handle->eeAllotedSectors; i++)
        {
            if (EE_GetSectorStatus(handle, sectorAddress) == EE_SECTOR_INVALID)
            {
                returnCode = EE_ReEraseEeprom(handle, sectorAddress);
                if (returnCode != EE_NOT_OK)
                {
                    returnCode = EE_CheckAvailabilityStatus(handle);
                }
            }
            if (returnCode == EE_NOT_OK)
            {
                break;
            }
            sectorAddress += (uint32_t)handle->eeSectorSize;
        }
    }

    if (returnCode == EE_OK)
    {
        sectorAddress = EE_FindActSector(handle, handle->eeStartAddress, false, false);
        /* it isn't the first time initialization because it has active sector*/
        if (sectorAddress != 0xFFFFFFFFu)
        {
            expErsCycValue[0]       = READ32(sectorAddress + handle->eeSectorEraseCycleOffset);
            currentActsectorAddress = sectorAddress;
            /* find the ALT sector before ACT sector that have invalid erase cycle and erase it */
            do
            {
                sectorAddress = EE_PrevSector(handle, sectorAddress);
                /* erase all alternate sector have invalid sector before oldest active sector */
                if ((EE_GetSectorStatus(handle, sectorAddress) == EE_SECTOR_ALTERNATIVE) &&
                    ((sectorAddress >= handle->eeStartAddress) && (sectorAddress < currentActsectorAddress)))
                {
                    if (EE_OK != EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorEraseCycleOffset,
                                                       expErsCycValue[0] + 0x01u))
                    {
                        returnCode = EE_ReEraseEeprom(handle, sectorAddress);
                        if (returnCode != EE_NOT_OK)
                        {
                            returnCode = EE_CheckAvailabilityStatus(handle);
                        }
                    }
                }
                /* erase all alternate sector have invalid sector behind oldest active sector */
                if ((EE_GetSectorStatus(handle, sectorAddress) == EE_SECTOR_ALTERNATIVE) &&
                    (sectorAddress > currentActsectorAddress) &&
                    (sectorAddress <= (g_eeEndAddress - handle->eeSectorSize)))
                {
                    if (EE_OK != EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorEraseCycleOffset,
                                                       expErsCycValue[0]))
                    {
                        returnCode = EE_ReEraseEeprom(handle, sectorAddress);
                        if (returnCode != EE_NOT_OK)
                        {
                            returnCode = EE_CheckAvailabilityStatus(handle);
                        }
                    }
                }
                if (returnCode == EE_NOT_OK)
                {
                    break;
                }
            } while (sectorAddress != currentActsectorAddress);
        }
        /* it is the first time initialization because it does not has active sector*/
        else
        {
            sectorAddress = (uint32_t)handle->eeStartAddress;
            /* find and erase all the ALT sectors have erase cycle different 1 if there is no ACT sector */
            for (i = 0x00u; i < handle->eeAllotedSectors; i++)
            {
                uint32_t tempVal =
                    EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorEraseCycleOffset, 0x01u);
                uint32_t tempValBackup =
                    EE_VerifySectorHeader(handle, sectorAddress + handle->eeSectorEraseCycleOffset, 0xFFFFFFFFu);

                if ((EE_OK != tempVal) && (EE_OK != tempValBackup))
                {
                    returnCode = EE_ReEraseEeprom(handle, sectorAddress);
                    if (returnCode != EE_NOT_OK)
                    {
                        returnCode = EE_CheckAvailabilityStatus(handle);
                    }
                }
                if (returnCode == EE_NOT_OK)
                {
                    break;
                }
                sectorAddress += (uint32_t)handle->eeSectorSize;
            }
        }
    }

    return returnCode;
}

static uint32_t EE_InitAltSector(eeprom_emulation_handle_t *handle, uint8_t *number)
{
    uint32_t returnCode = EE_OK; /* variable return EE_InitEeprom() function state.*/
#if (defined(FLASH_PGM_SIZE) && (FLASH_PGM_SIZE == 16))
    uint32_t expErsCycValue[4]; /* buffer to store erase cycle, which is written to erase cycle address.*/
#else
    uint32_t expErsCycValue[2]; /* buffer to store erase cycle, which is written to erase cycle address.*/
#endif
    uint32_t sectorAddress; /* variable help we know the address is activated at that time.*/
    uint32_t currentActsectorAddress = 0x00u;
    uint8_t tempTotalActiveSector    = 0x00u; /* variable help we know how many active sector at that time.*/
    uint8_t sectorStatus;                     /* variable help we know the state of sector when we call.*/
    uint8_t i;

    if (handle->ftfxProgramSize > FTFx_LONGWORD_SIZE)
    {
#if (defined(FLASH_PGM_SIZE) && (FLASH_PGM_SIZE == 16))
        expErsCycValue[1] = 0xFFFFFFFFu;
        expErsCycValue[2] = 0xFFFFFFFFu;
        expErsCycValue[3] = 0xFFFFFFFFu;
        g_eraseCycles[1]  = 0xFFFFFFFFu;
        g_eraseCycles[2]  = 0xFFFFFFFFu;
        g_eraseCycles[3]  = 0xFFFFFFFFu;
#else
        expErsCycValue[1] = 0xFFFFFFFFu;
        g_eraseCycles[1]  = 0xFFFFFFFFu;
#endif
    }

    /***********
    STEP 3:
       This step will check if STEP 1 & STEP 2is done and successful, it will make all alive sectors to ALT sectors
    ***********/

    /* This segment will make all blank sector to alter sector by write erase cycle to its address.
       When make a blank sector to alter sector, if making fail. It will re-erase this sector and
       re-make to alter sector several time before make dead sector. If make dead sector fail too
       return EE_NOT_OK error. It will check total dead sector and return EE_NOT_OK error if break
       sequence because of not enough alter sector */
    tempTotalActiveSector = EE_GetSectorNumber(handle, EE_SECTOR_ACTIVE);
    /* If this is the first time initializing, erase cycle must is 1 */
    if (tempTotalActiveSector == 0x00u)
    {
        expErsCycValue[0u]   = 0x01u;
        g_eraseCycles[0x00u] = expErsCycValue[0u];
        sectorAddress        = (uint32_t)handle->eeStartAddress;
        for (i = 0x00u; i < handle->eeAllotedSectors; i++)
        {
            sectorStatus = EE_GetSectorStatus(handle, sectorAddress);
            if (sectorStatus == EE_SECTOR_BLANK)
            {
                returnCode = EE_ValidateEraseCycle(handle, sectorAddress, (uint8_t *)expErsCycValue);
            }
            if (returnCode == EE_MAKEDEAD_OK)
            {
                returnCode = EE_CheckAvailabilityStatus(handle);
            }
            if (returnCode == EE_NOT_OK)
            {
                break;
            }
            sectorAddress += (uint32_t)handle->eeSectorSize;
        }
    }
    /* Write valid erase cycle for all BLANKS sectors */
    else
    {
        expErsCycValue[0u]      = READ32(currentActsectorAddress + handle->eeSectorEraseCycleOffset);
        g_eraseCycles[0u]       = expErsCycValue[0u];
        sectorAddress           = EE_FindActSector(handle, handle->eeStartAddress, false, false);
        currentActsectorAddress = sectorAddress;
        /* Make all blank sector before active sector to alternate sector */
        do
        {
            sectorAddress = EE_PrevSector(handle, sectorAddress);
            /* calculate erase cycle of all blank sectors before oldest active sector */
            if ((EE_GetSectorStatus(handle, sectorAddress) == EE_SECTOR_BLANK) &&
                (sectorAddress >= handle->eeStartAddress))
            {
                expErsCycValue[0u] = g_eraseCycles[0] + 0x01u;
            }
            /* calculate erase cycle of all blank sectors behind oldest active sector */
            if ((EE_GetSectorStatus(handle, sectorAddress) == EE_SECTOR_BLANK) &&
                (sectorAddress > currentActsectorAddress) && (sectorAddress <= (g_eeEndAddress - handle->eeSectorSize)))
            {
                expErsCycValue[0u] = g_eraseCycles[0u];
            }
            /* write erase cycle for blank sector */
            if (EE_GetSectorStatus(handle, sectorAddress) == EE_SECTOR_BLANK)
            {
                returnCode = EE_ValidateEraseCycle(handle, sectorAddress, (uint8_t *)expErsCycValue);
                if (returnCode == EE_MAKEDEAD_OK)
                {
                    returnCode = EE_CheckAvailabilityStatus(handle);
                }
                if (returnCode == EE_NOT_OK)
                {
                    break;
                }
            }
        } while (sectorAddress != currentActsectorAddress);
    }

    *number = tempTotalActiveSector;

    return returnCode;
}

static uint32_t EE_InitActiveSector(eeprom_emulation_handle_t *handle, uint8_t number)
{
    uint32_t returnCode           = EE_OK;  /* variable return EE_InitEeprom() function state.*/
    uint32_t sectorAddress        = 0x00U;  /* variable help we know the address is activated at that time.*/
    uint8_t tempTotalActiveSector = number; /* variable help we know how many active sector at that time.*/
    uint8_t sectorStatus;                   /* variable help we know the state of sector when we call.*/

    /***********
    STEP 4:
       This step will check if STEP 1, STEP 2,  and STEP 3 is done and successful, it will make all ALT sectors to
    ACT sectors
    ***********/

    /* This segment will make all alter sector to active sector by write erase cycle to its address.
       When make a alter sector to active sector, if making fail. It will re-erase this sector and
       re-make to active sector several time before make dead sector. If make dead sector fail return
       EE_NOT_OK error. It will check total dead sector and return EE_NOT_OK error if break sequence
       because of not enough alter sector */
    /* check enough sector for sequence */
    if (tempTotalActiveSector == 0x00u)
    {
        sectorAddress = handle->eeStartAddress;
    }
    else
    {
        sectorAddress = EE_FindActSector(handle, sectorAddress, true, true);
    }

    /* make enough active sector for EEE */
    if (tempTotalActiveSector < (uint32_t)handle->eeActiveSectors)
    {
        do
        {
            sectorStatus = EE_GetSectorStatus(handle, sectorAddress);
            if (sectorStatus == EE_SECTOR_ALTERNATIVE)
            {
                returnCode = EE_ValidateActIndicator(handle, sectorAddress);
                if (returnCode == EE_OK)
                {
                    tempTotalActiveSector++;
                }
                if (returnCode == EE_MAKEDEAD_OK)
                {
                    returnCode = EE_CheckAvailabilityStatus(handle);
                }
                if (returnCode == EE_NOT_OK)
                {
                    break;
                }
            }
            sectorAddress = EE_NextSector(handle, sectorAddress);
        } while (tempTotalActiveSector < handle->eeActiveSectors);
    }

    /* re-check enough sector for sequence */
    if (returnCode == EE_OK)
    {
        returnCode = EE_CheckAvailabilityStatus(handle);
        if (returnCode == EE_OK)
        {
            tempTotalActiveSector = 0x01u;
            g_currentActiveSector = EE_FindActSector(handle, handle->eeStartAddress, false, false);
            g_freeSpaceAddress    = EE_SearchBlankSpace(handle, g_currentActiveSector);
            while (
                (tempTotalActiveSector < handle->eeActiveSectors) &&
                ((g_freeSpaceAddress + handle->eeSectorRecordLength) > (g_currentActiveSector + handle->eeSectorSize)))
            {
                /* update g_freeSpaceAddress */
                g_currentActiveSector = EE_NextSector(handle, g_currentActiveSector);
                if (EE_GetSectorStatus(handle, g_currentActiveSector) == EE_SECTOR_ACTIVE)
                {
                    tempTotalActiveSector++;
                    g_freeSpaceAddress = EE_SearchBlankSpace(handle, g_currentActiveSector);
                }
            }
        }
    }

    return returnCode;
}

/*******************************************************************************
*
*  Function Name    : EE_Init
*  Description      : This function will determine active,
                      alternative and brown out affected sectors and
                      erase/update the sectors. Initializing variables
                      that hold active sector related information like
                      the start addresses of the active sector
                      and the blank space available is also done in this
                      function. The dead sectors are re-erased again for
                      next usage and cache table is also initialized in this
                      function. If no sectors are initialized then,
                      this function shall initialize all the sectors in
                      a round robin queue
*  Arguments        : N/A
*  Return Value     :
*                     - EE_OK if successful
*                     - EE_NOT_OK if failed
*
*******************************************************************************/

uint32_t EE_Init(eeprom_emulation_handle_t *handle)
{
    uint32_t returnCode       = EE_OK; /* variable return EE_InitEeprom() function state.*/
    uint8_t totalActiveSector = 0x00u; /* variable help we know how many active sector at that time.*/
    /* Initialize all global variables */
#if (EE_USE_ASYNCHRONOUS_MODEL == true)
    g_addressToMain    = 0xFFFFFFFFu;
    g_endAddressToMain = 0xFFFFFFFFu;
#endif
    g_eraseStatusFlag = IDLE;
    g_eeEndAddress    = handle->eeEndAddress;

    {
/* clear cache */
#if EE_CACHETABLE_ENABLE
        sectorAddress = (uint32_t)EE_CACHETABLE_START_ADDRESS;
        for (i = 0x01u; i <= EE_CACHETABLE_MAX_ENTRY; i++)
        {
            WRITE32(sectorAddress, 0xFFFFFFFFu);
            sectorAddress += (uint32_t)EE_CACHETABLE_ITEM_SIZE;
        }
#endif

        /* Check initliazation or not. */
        returnCode = EE_PreInitCheck(handle);
        if (EE_OK == returnCode)
        {
            /* Init altnative sectors. */
            returnCode = EE_InitAltSector(handle, &totalActiveSector);
        }

        if (EE_OK == returnCode)
        {
            /* Init active sectors. */
            returnCode = EE_InitActiveSector(handle, totalActiveSector);
        }
    }

/* update cache table if enabled */
#if EE_CACHETABLE_ENABLE == true
    if (returnCode == EE_OK)
    {
        EE_UpdateCacheTable(handle);
    }
#endif
    return (returnCode);
}

/*******************************************************************************
*
*  Function Name    : EE_ReadEeprom
*  Description      : This function is used to read the specific data record.
                      The starting address of the record data will be returned.
*  Arguments        :
*                     - dataID: the record ID to be read.
*                     - recordAddr: address of found record.
*  Return Value     :
*                     - EE_OK if found record.
*                     - 0xFFFFFFFFu if not found record.
*                     - EE_ERR_IDRANGE if ID invalid value.
*
*******************************************************************************/
uint32_t EE_ReadData(eeprom_emulation_handle_t *handle, uint16_t dataID, uint32_t *recordAddr)
{
    uint32_t returnCode = EE_OK;
    /* This segment will for validate ID, sure that it is in the range of ID */
    if (((uint16_t)(handle->eeMaxRecordNumber) < dataID) || (0x00u == dataID))
    {
        returnCode = EE_ERR_IDRANGE;
    }
    /* Search for data for the record in all active sectors. It will return address
       of data record if found ID. Or it return 0xFFFFFFFFu value*/
    if (returnCode != EE_ERR_IDRANGE)
    {
        *recordAddr = EE_SearchLoop(handle, dataID);
        if (*recordAddr == 0xFFFFFFFFu)
        {
            returnCode = 0xFFFFFFFFu;
        }
    }
    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_WriteData
 *  Description      : This function will be used to write new data record to
 *                     EEPROM emulation.
 *  Arguments        :
 *                     - dataID: record ID to be written.
 *                     - source: source data to be written.
 *  Return Value     :
 *                     - EE_OK if successful
 *                     - EE_NOT_OK if failed
 *                     - EE_ERR_IDRANGE if ID out of range
 *                     - EE_ERR_UPDATE if swapping occurred but fail
 *
 *******************************************************************************/
uint32_t EE_WriteData(eeprom_emulation_handle_t *handle, uint16_t dataID, uint32_t source)
{
    uint32_t returnCode = EE_OK;
    uint32_t sectorAddress;
    uint32_t alginedSize;
    uint32_t remainingSize;
#if (EE_USE_ASYNCHRONOUS_MODEL != true) /* synchronous model */
    uint32_t i;
#endif

    uint8_t sectorStatus = 0x00u;
    /* Defined in preprocessor */
    uint8_t remainData[EE_DATA_VALUE_REMAINING_PART];
    bool swapFlag = false;

    /*Calculate data value aligned part and remaining part */
    alginedSize   = handle->eeDataValueSize - (handle->eeDataValueSize % handle->ftfxProgramSize);
    remainingSize = handle->eeSectorRecordLength - alginedSize - handle->ftfxProgramSize - handle->complementSize;

    /* Check if the ID is within the range or equal to zero */
    if ((dataID > (uint16_t)handle->eeMaxRecordNumber) || (dataID == 0x00u))
    {
        returnCode = EE_ERR_IDRANGE;
    }
    else
    {
        /* Copying the data ID and the data Values into the structure */
        g_dataRecord.dataID = dataID;
        /* Copying the dataAddr into the structure */
        g_dataRecord.dataAddr = source;
/* Calculate free space available in the current active sector */
/* Check if the space is enough to write a record */
#if (EE_USE_ASYNCHRONOUS_MODEL != true) /* synchronous model */
        /* scan for 2 times in synchronous model to write internal data */
        for (i = 0x00u; i < handle->eeActiveSectors; i++)
        {
#endif
            /* for synchronous model,need to back WriteEeprom function to write
               internal data here (when i is 0x1) */

            if (((g_currentActiveSector + handle->eeSectorSize) - g_freeSpaceAddress) < handle->eeSectorRecordLength)
            {
                /* if there is no free space on current active sector*/
                sectorAddress = g_currentActiveSector;
                returnCode    = EE_CheckAvailabilityStatus(handle);

                if (returnCode == EE_NOT_OK)
                {
                    /* Return EE_NOT_OK error if break sequence because of not enough alter sector */
                    break;
                }

                if (returnCode == EE_OK)
                {
                    do
                    {
                        sectorAddress = EE_NextSector(handle, sectorAddress);
                        sectorStatus  = EE_GetSectorStatus(handle, sectorAddress);
                    } while ((sectorStatus == EE_SECTOR_DEAD) || (sectorStatus == EE_SECTOR_READY));
                }

                if ((sectorStatus == EE_SECTOR_ALTERNATIVE) && (returnCode == EE_OK))
                {
/* if there is no active sector in the next ones. Swapping must occur*/
#if (EE_USE_ASYNCHRONOUS_MODEL != true) /* synchronous model */
                    returnCode = EE_SwapSector(handle);
                    if (returnCode == EE_OK)
                    {
                        /* if swapping successful, continue to write internal data*/
                        continue;
                    }
                    else
                    {
                        /* if swapping fail, return EE_ERR_UPDATE*/
                        returnCode = EE_ERR_UPDATE;
                        break;
                    }
#else
                returnCode = EE_SwapSector(handle);
                swapFlag   = true;
#endif
                }
                /* if find active one in the next sector, no swapping is needed.*/
                /* Make new sector as active one to write record to this new sector */
                if (sectorStatus == EE_SECTOR_ACTIVE)
                {
                    g_currentActiveSector = sectorAddress;
                    g_freeSpaceAddress    = g_currentActiveSector + (uint32_t)handle->eeSectorHeaderSize;
#if (EE_USE_ASYNCHRONOUS_MODEL != true) /* synchronous model */
                    /* "i = handle->eeActiveSectors;" is same method to break this for() loop, but it violates MISRA
                     * rule 14.2(required). */
                    break;
#endif
                }
            }

#if (EE_USE_ASYNCHRONOUS_MODEL != true) /* synchronous model */
        }
#endif
    }

    /* no swapping occurs. Write new record to current free space address*/
    /* prepare remaining data */
    /* initialize remainData, reuse sectorStatus variable to save stack */
    if (((returnCode == (uint32_t)EE_OK) && (swapFlag == false) &&
         (((g_currentActiveSector + handle->eeSectorSize) - g_freeSpaceAddress) >=
          (uint32_t)handle->eeSectorRecordLength)))
    {
        for (sectorStatus = 0x00u; sectorStatus < remainingSize; sectorStatus++)
        {
            if (sectorStatus < ((uint8_t)handle->eeDataValueSize - (uint8_t)alginedSize))
            {
                remainData[sectorStatus] = (uint8_t)READ8(g_dataRecord.dataAddr + (uint8_t)alginedSize + sectorStatus);
            }
            else
            {
                remainData[sectorStatus] = 0xFFu;
            }
        }
        remainData[remainingSize - ID_LOWBYTE_OFFSET]  = (uint8_t)(g_dataRecord.dataID);
        remainData[remainingSize - ID_HIGHBYTE_OFFSET] = (uint8_t)(g_dataRecord.dataID >> 8);
        returnCode                                     = EE_CopyRecord(handle, g_dataRecord, remainData);
        if (returnCode == EE_OK)
        {
            g_eraseStatusFlag = IDLE;
        }
    }

    return (returnCode);
}

/*******************************************************************************
 *
 *  Function Name    : EE_ReportStatus
 *  Description      : This function reports the erase cycle of current active sector.
 *  Arguments        : N/A
 *  Return Value     :
 *                     - erase cycle of current active sector.
 *
 *******************************************************************************/
uint32_t EE_ReportStatus(eeprom_emulation_handle_t *handle)
{
    /* get erase cycle for current active sector */
    return (READ32(g_currentActiveSector + handle->eeSectorEraseCycleOffset));
}

/*******************************************************************************
*
*  Function Name    : EE_Deinit
*  Description      : This function is to release all the Flash used to
                      EEPROM emulation. After de-initialize, the Flash
                      for emulation will be fully erased.
*  Arguments        : N/A
*  Return Value     :
*                     - EE_OK if successful
*                     - EE_NOT_OK if failed
*
*******************************************************************************/
uint32_t EE_Deinit(eeprom_emulation_handle_t *handle)
{
    uint32_t sectorAddress = handle->eeStartAddress;
    uint32_t returnCode    = EE_OK;
    uint8_t numDead        = 0x00u;
    uint8_t i;
    /* Re-erase all sectors, one by one from first sector to end sector */
    for (i = 0x00u; i < handle->eeAllotedSectors; i++)
    {
        returnCode = EE_ReEraseEeprom(handle, sectorAddress);
        if (returnCode == EE_NOT_OK)
        {
            break;
        }
        if (returnCode == EE_MAKEDEAD_OK)
        {
            numDead++;
        }
        sectorAddress += (uint32_t)handle->eeSectorSize;
    }
    if (numDead > handle->eeExtraReadySectors)
    {
        returnCode = EE_NOT_OK;
    }
    if ((returnCode != EE_NOT_OK) && (numDead <= handle->eeActualReadySectors))
    {
        returnCode = EE_OK;
    }

    return (returnCode);
}

/*******************************************************************************
*
*  Function Name    : EE_Main()
*  Description      : Completes the initialization of sectors and other
                      operations to make it ready for EEPROM emulation.
*  Arguments        : N/A
*  Return Value     :
*                     - EE_OK if successful
*                     - EE_NOT_OK if failed
*                     - EE_ERR_UPDATE if swapping occurred but fail
*
*******************************************************************************/
#if (EE_USE_ASYNCHRONOUS_MODEL == true)
uint32_t EE_Main(eeprom_emulation_handle_t *handle)
{
    uint32_t returnCode = EE_OK;
    uint32_t erasedSectorAddr;

    if (DONE == g_eraseStatusFlag)
    {
        /* Check for there is still flash sector in the EEE sector need erased */
        g_addressToMain += handle->flashSectorSize;
        if (g_addressToMain < g_endAddressToMain)
        {
            /* Erase the next flash sector in the EEE sector */
            EE_AsyncFlashErase(handle, g_addressToMain);
        }
        else
        {
            /* Get address of the erased sector */
            erasedSectorAddr = g_endAddressToMain - handle->eeSectorSize;

            /* complete erase for entire EE sector. So, verify section to make sure the sector
               was erased successfully */
            /* verify if sector erase done and successful. If sector is dead ignore this section */
            returnCode = EE_FlashEraseVerifySection(handle, erasedSectorAddr,
                                                    (uint16_t)(handle->eeSectorSize / handle->ftfxRD1SECSize),
                                                    handle->flashReadMargin);
            if (returnCode == EE_OK)
            {
                /* pass verify section, change g_eraseStatusFlag to IDLE */
                /* program erase cycle to the sector which has been erased */
                /* write internal data which causes swapping */
                returnCode = EE_MultiProgram(handle, erasedSectorAddr + handle->eeSectorEraseCycleOffset,
                                             (uint32_t)handle->ftfxProgramSize, (uint8_t *)&g_eraseCycles);
            }

            if (returnCode != EE_OK)
            {
                /* fail in verify section, make the global flag to FAIL */
                g_eraseStatusFlag = FAIL;

                g_numErase++;
                if (g_numErase <= handle->eeRetryMax)
                {
                    /* Reset address point to start-address of the erased sector... */
                    g_addressToMain = erasedSectorAddr;

                    /* ...then re-erase the EEE sector  */
                    EE_AsyncFlashErase(handle, g_addressToMain);

                    /* Update return code */
                    returnCode = EE_OK;
                }
                else
                {
                    /* Make this sector as DEAD */
                    returnCode = EE_ValidateDeadIndicator(handle, erasedSectorAddr);

                    if (returnCode == EE_OK)
                    {
                        /* validate successfully */
                        /* update global flag to IDLE and then write internal data which causes swapping */
                        returnCode = EE_CheckAvailabilityStatus(handle);
                        if (returnCode == EE_OK)
                        {
                            /* Reset erase flag */
                            g_eraseStatusFlag = IDLE;
                        }
                    }

                    if (returnCode != EE_OK)
                    {
                        /* Return UPDATE error if can't make the sector to DEAD or
                         * there isn't enough sectors for the sequence */
                        returnCode = EE_ERR_UPDATE;
                    }

                    /* Reset re-erase number */
                    g_numErase = 0u;
                }
            }
            else
            {
                /* Reset erase flag */
                g_eraseStatusFlag = IDLE;
                g_numErase        = 0u;
            }

            /* Only write internal data if finish the erasing, updating erase cycle */
            if ((IDLE == g_eraseStatusFlag) && (returnCode == EE_OK))
            {
                returnCode = EE_WriteData(handle, g_dataRecord.dataID, g_dataRecord.dataAddr);
            }
        }
    }

    return (returnCode);
}
#endif /* EE_USE_ASYNCHRONOUS_MODEL */
