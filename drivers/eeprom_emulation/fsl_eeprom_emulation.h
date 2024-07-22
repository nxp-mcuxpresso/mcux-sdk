/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_EEPROM_EMULATION_H_
#define FSL_EEPROM_EMULATION_H_

#include "fsl_common.h"

/*!
 * @addtogroup eeprom_emulation
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief EEPROM Emulation driver version. */
#define EE_EEPROM_EMULATION_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

typedef struct _eeprom_emulation_data_record_t
{
    uint32_t dataAddr; /* The address of data source */
    uint16_t dataID;   /* The unique data ID */
} eeprom_emulation_data_record_t;

/* Monitoring states */
typedef enum
{
    IDLE = 0x00u,
    BUSY = 0x01u,
    DONE = 0x02u,
    FAIL = 0x03u
} eeprom_emulation_state_type_t;

/*! @brief Eeprom emulation driver state information.
 *
 * An instance of this structure is allocated by the user of the eeprom emulation driver and
 * passed into each of the driver APIs.
 */
typedef struct _eeprom_emulation_config
{
    uint32_t ftfxProgramSize;  /* check align of program function */
    uint32_t ftfxRD1SECSize;   /* check align of verify section on PFlash function */
    uint32_t ftfxPGMCheckSize; /* check align of program check function */

    uint32_t flashStartAddress; /* base address of flash module in byte address space */
    uint32_t flashSectorSize;   /* flash sector size */
    uint8_t flashReadMargin;    /* Flash margin read settings */

    uint32_t eeStartAddress;  /* Start address of Eeprom emulation in byte */
    uint32_t eeSectorSize;    /* Sector size of Eeprom emulation in bytes. It can be one or multiply consecutive flash
                                 sectors */
    uint32_t eeDataValueSize; /* The length of raw data for each record in byte */
    uint32_t eeActualReadySectors; /* Number of alternative sectors needed for Round Robin scheme. This number must be
                                      minimum equal to 2 */
    uint32_t eeMinActualReadySectors; /* The minimum number alternative of sectors that should be allotted for emulation
                                         Eeprom */
    uint32_t eeExtraActiveSectors;    /* Number of extra active sectors needed for emulation */
    uint32_t eeExtraReadySectors;     /* Number of extra ready sectors needed for emulation */
    uint32_t eeRetryMax;              /* Number of retry if failed to program sector indicator or erase sector */
    uint32_t eeSectorActIndOffset;    /*active indicator*/
    uint32_t eeMemorySize;            /* The total raw data user wants to emulate in byte */
    uint32_t eccSize;                 /*ECC size*/

} eeprom_emulation_config_t;

/*! @brief Eeprom emulation handle, users should not touch the content of the handle.*/
typedef struct _eeprom_emulation_handle
{
    uint32_t ftfxProgramSize;    /* Program size */
    uint32_t ftfxProgramCommand; /* Program command*/
    uint32_t ftfxRD1SECSize;     /* Check align of verify section on PFlash function */
    uint32_t ftfxBitNumber;      /* Number of bit to make programable size */
    uint32_t ftfxPGMCheckSize;   /* Check align of program check function */

    uint32_t flashStartAddress; /* Base address of flash module in byte address space */
    uint32_t flashSectorSize;   /* Flash sector size */
    uint8_t flashReadMargin;    /* Flash margin read settings */

    uint32_t eeStartAddress;  /* Start address of Eeprom emulation in byte */
    uint32_t eeEndAddress;    /* End address of Flash from EEPROM emulation. */
    uint32_t eeSectorSize;    /* Sector size of Eeprom emulation in bytes, one or multiply consecutive flash sectors */
    uint32_t eeDataValueSize; /* The length of raw data for each record in byte */
    uint32_t eeActualReadySectors; /* Number of alternative sectors needed for Round Robin scheme. This number must be
                                      minimum equal to 2 */
    uint32_t eeMinActualReadySectors; /* The minimum number alternative of sectors that should be allotted for emulation
                                         Eeprom */
    uint32_t eeExtraActiveSectors;    /* Number of extra active sectors needed for emulation */
    uint32_t eeExtraReadySectors;     /* Number of extra ready sectors needed for emulation */
    uint32_t eeReadySectors;          /* Number of ready sectors needed for emulation */
    uint32_t eeRetryMax;              /* Number of retry if failed to program sector indicator or erase sector */
    uint32_t eeSectorHeaderSize;      /* Header size */
    uint32_t eeSectorActIndOffset;    /* Active indicator offset */
    uint32_t eeSectorDeadIndOffset;   /* Dead indicator offset */
    uint32_t eeSectorEraseCycleOffset; /* Erase cycle offset */
    uint32_t eeGapSize;                /* The gap between status and ID field */
    uint32_t eeRecordIDOffset;         /* Record ID offset */
    uint32_t eeRecordStatusOffset;     /* Record statue offset */
    uint32_t eeSectorRecordLength;     /* One record length for emulated eeprom */
    uint16_t eeMaxRecordNumber;        /* Number of Data Records is calculated if we know the total Data Size. */
    uint32_t eeMemorySize;             /* The total raw data user wants to emulate in byte */
    uint32_t eeSectorWaste;            /* Number of bytes in a sector that are not used for emulation */
    uint32_t eeSectorCapacity;         /* Number of records that can be stored in a sector */
    uint32_t eeActiveSectorRequired;   /* Number of sectors required to store the specified EEPROM size */
    uint32_t eeActiveSectors;          /* Total number of ACTIVE sectors alloted */
    uint32_t eeAllotedSectors; /* Total number of sectors alloted will also include some 'alternative sectors' */

    uint32_t complementSize; /* Determine the complement size to avoid losing data in case having ECC according to
                                different ECC size */

} eeprom_emulation_handle_t;

/* Callback function prototype */
typedef void (*PEE_FUNCPOINTER)(void);

/******************************************************************************/
/*     MACRO for four functionalitys based on eeprom emulation                */
/******************************************************************************/
/* Flag to indicate the running mode is Async'ed or Sync'ed */
#define EE_USE_ASYNCHRONOUS_MODEL false
/* Macro to enable or disable Cache Table */
#define EE_CACHETABLE_ENABLE false
/* Macro to indicate Callback is enabled or not */
#define EE_CALLBACK_ENABLE false

/******************************************************************************/
/*                               Return codes                                 */
/******************************************************************************/
#define EE_OK          0x00000000u
#define EE_ERR_IDRANGE 0x00000100u
#define EE_ERR_SECURE  0x00001000u
#define EE_MAKEDEAD_OK 0x00010000u
#define EE_NOT_OK      0x10000000u
#define EE_ERR_UPDATE  0x20000000u

/******************************************************************************/
/*             Macros related to sector header and record header              */
/******************************************************************************/
/* size of each field in record header*/
#define EE_RECORD_ID_SIZE     0x02u
#define EE_RECORD_STATUS_SIZE 0x02u

/* offset byte for ID field */
#define ID_LOWBYTE_OFFSET  EE_RECORD_ID_SIZE
#define ID_HIGHBYTE_OFFSET 0x01u

/******************************************************************************/
/*             Macros related to value used to program to sector header to
                make different sector status*/
/******************************************************************************/
#define EE_DATA_STATUS_ACTIVE  0xFACFFACFu
#define EE_DATA_STATUS_ALIVE   0xFFFF5555u
#define EE_DATA_STATUS_DEAD    0x55555555u
#define EE_DATA_STATUS_BLANK   0xFFFFFFFFu
#define EE_RECORD_STATUS_VALID 0x5555u

/****************************************************************************
             Macros to identify sector status and record status
*****************************************************************************/
/* Macro to denote the Sector Status */
#define EE_SECTOR_BLANK       0x00u
#define EE_SECTOR_ALTERNATIVE 0x01u
#define EE_SECTOR_ACTIVE      0x02u
#define EE_SECTOR_ALIVE       0x03u
#define EE_SECTOR_READY       0x04u
#define EE_SECTOR_DEAD        0x05u
#define EE_SECTOR_INVALID     0x06u

/****************************************************************************
             Macros to identify the status of initialize progress
*****************************************************************************/
/* Macro to denote the Sector Status */
#define EE_FIRST_TIME_NOT_DONE 0x00u
#define EE_READY_TO_WORK       0x01u
#define EE_SWAPPING            0x02u
#define EE_SWAPPING_DONE       0x03u

/******************************************************************************/
/*                  Macros of devide/multiple fomular                         */
/******************************************************************************/
/* macro to get the remainder GET_MOD = divisor % dividend*/
#define GET_MOD(divisor, dividend) ((divisor) % (dividend))
/* macro to get the interger GET_INT = divisor / dividend*/
#define GET_INT(divisor, dividend) ((divisor) / (dividend))

/****************************************************************************
             Macros definition uses for synchronous and cache
*****************************************************************************/
/* Macro to determine the number of IDs to be stored in Cache table */
#if (EE_CACHETABLE_ENABLE == true)
#define EE_CACHETABLE_MAX_ENTRY 0x4 /* Number of Cache Table entries */
#define EE_CACHETABLE_START_ADDRESS \
    0x2000FF00 /* start address of the cache table in RAM. Must be consistent with linker file */
#define EE_CACHETABLE_ITEM_SIZE         0x04u
#define EE_CACHETABLE_ITEM_ADDR(dataID) (EE_CACHETABLE_START_ADDRESS + ((dataID - 0x01u) << 0x02u))
#endif

/******************************************************************************/
/*              Macros to determine the total number of sectors               */
/*                        alloted for EEPROM Emulation                        */
/******************************************************************************/
#define EE_MAX_ERASING_CYCLE_VALUE 0xFFFFFFFEu

#define MIN2(a, b)      (((a) < (b)) ? (a) : (b))
#define MIN3(a, b, c)   ((c) < (MIN2((a), (b))) ? (c) : (MIN2((a), (b))))
#define NOT_EQUAL(a, b) (((a) != (b)) ? 0x01u : 0x00u)

/******************************************************************************/
/*               Read/Write/Set/Clear Operation Macros                        */
/******************************************************************************/
#define REG_BIT_SET(address, mask)   (*(volatile uint8_t *)(address) |= (mask))
#define REG_BIT_CLEAR(address, mask) (*(volatile uint8_t *)(address) &= ~(mask))
#define REG_BIT_TEST(address, mask)  (*(volatile uint8_t *)(address) & (mask))
#define REG_WRITE(address, value)    (*(volatile uint8_t *)(address) = (value))
#define REG_READ(address)            ((uint8_t)(*(volatile uint8_t *)(address)))
#define REG_WRITE16(address, value)  (*(volatile uint16_t *)(address) = (value))
#define REG_READ16(address)          ((uint16_t)(*(volatile uint16_t *)(address)))

#define WRITE8(address, value)  (*(volatile uint8_t *)(address) = (value))
#define READ8(address)          ((uint8_t)(*(volatile uint8_t *)(address)))
#define WRITE16(address, value) (*(volatile uint16_t *)(address) = (value))
#define READ16(address)         ((uint16_t)(*(volatile uint16_t *)(address)))
#define WRITE32(address, value) (*(volatile uint32_t *)(address) = (value))
#define READ32(address)         ((uint32_t)(*(volatile uint32_t *)(address)))

/****************************************************************************
             Macros definition uses for RAM_TARGET
*****************************************************************************/

#if EE_CALLBACK_ENABLE
/* Counter if is reached, callback will be called */
#define EE_CALLBACK_COUNTER 0x4
/* A function pointer to the CallBack function */
extern PEE_FUNCPOINTER g_EECallBack;
/* length of this array depends on total size of the functions need to be copied to RAM*/
#define CALLBACK_SIZE 0x30
/* Null Callback function defination */
#define NULL_EE_CALLBACK ((PEE_FUNCPOINTER)0xFFFFFFFFu)
#endif

/* Protopyte of interrupt service routin */
#define INTERRUPT

/* FTFx Flash Module Memory Offset Map */
#define FTFx_FSTAT  (FTFE_BASE + 0x00000000u)
#define FTFx_FCNFG  (FTFE_BASE + 0x00000001u)
#define FTFx_FSEC   (FTFE_BASE + 0x00000002u)
#define FTFx_FCCOB0 (FTFE_BASE + 0x00000007u)
#define FTFx_FCCOB1 (FTFE_BASE + 0x00000006u)
#define FTFx_FCCOB2 (FTFE_BASE + 0x00000005u)
#define FTFx_FCCOB3 (FTFE_BASE + 0x00000004u)
#define FTFx_FCCOB4 (FTFE_BASE + 0x0000000Bu)
#define FTFx_FCCOB5 (FTFE_BASE + 0x0000000Au)
#define FTFx_FCCOB6 (FTFE_BASE + 0x00000009u)
#define FTFx_FCCOB7 (FTFE_BASE + 0x00000008u)
#define FTFx_FCCOB8 (FTFE_BASE + 0x0000000Fu)
#define FTFx_FCCOB9 (FTFE_BASE + 0x0000000Eu)
#define FTFx_FCCOBA (FTFE_BASE + 0x0000000Du)
#define FTFx_FCCOBB (FTFE_BASE + 0x0000000Cu)
#define GETINDEX(i) ((((i) / 0x04u) << 0x03u) + 0x03u - (i)) /* (i/4)*8 + 3 - i */

/* bit mask for FSTAT register */
#define FTFx_FSTAT_CCIF      0x80u
#define FTFx_FSTAT_CLEAR_ERR 0x70u /* (FTFx_FSTAT_RDCOLERR | FTFx_FSTAT_ACCERR | FTFx_FSTAT_FPVIOL) */
#define FTFx_FSTAT_CHECK_ERR 0x31u /* (FTFx_FSTAT_MGSTAT0 | FTFx_FSTAT_ACCERR | FTFx_FSTAT_FPVIOL) */
                                   /* bit mask for FCNFG register */
#define FTFx_FCNFG_CCIE 0x80u
#define FTFx_FSEC_SEC   0x03u

/* Programmable size Macro definition for FTFx */
#define FTFx_WORD_SIZE     0x02u
#define FTFx_LONGWORD_SIZE 0x04u
#define FTFx_PHRASE_SIZE   0x08u
#define FTFx_DPHRASE_SIZE  0x10u

/* Flash hardware algorithm operation commands */
#define FTFx_VERIFY_SECTION   0x01u
#define FTFx_PROGRAM_CHECK    0x02u
#define FTFx_PROGRAM_LONGWORD 0x06u
#define FTFx_PROGRAM_PHRASE   0x07u
#define FTFx_ERASE_SECTOR     0x09u

/*
** define flash command codes for K4W1
*/

#define RD1ALL  0x00 /*Read 1s All (Verify that all flash and IFR space is erased)*/
#define RD1BLK  0x01 /*Read 1s Block (Verify that a flash block is erased)*/
#define RD1SCR  0x02 /*Read 1s Sector(Verify that a flash sector is erased)*/
#define RD1PG   0x03 /*Read 1s Page (Verify that a flash page is erased)*/
#define RD1PHR  0x04 /*Read 1s Phrase (Verify that a flash phrase is erased)*/
#define RDMISR  0x05 /*Read into MISR (Generate MISR signature for range of flash pages)*/
#define RD1ISCR 0x12 /*Read 1s IFR Sector (Verify that an IFR sector is erased)*/
#define RD1IPG  0x13 /*Read 1s IFR Page (Verify that an IFR page is erased)*/
#define RD1IPHR 0x14 /*Read 1s IFR Phrase (Verify that an IFR phrase is erased)*/
#define RDIMISR 0x15 /*Read IFR into MISR (Generate MISR signature for range of IFR pages)*/
#define PGMPG   0x23 /*Program Page (Program data to a flash or IFR page)*/
#define PGMPHR  0x24 /*Program Phrase (Program data to a flash or IFR phrase)*/
#define ERSALL  0x40 /*Erase All (Erase all flash and IFR space)*/
#define ERSSCR  0x42 /*Erase Sector (Erase a flash sector)*/

#define FMU_CHECK_CCIF (FMU0->FSTAT & FMU_FSTAT_CCIF_MASK)
#define FMU_CHECK_PEWEN \
    (FMU0->FSTAT & FMU_FSTAT_PEWEN_MASK) /* MH - this define was mistakenly referencing the CCIF instead of PEWEN */
#define FMU_CHECK_PERDY  (FMU0->FSTAT & FMU_FSTAT_PERDY_MASK)
#define FMU_CHECK_FAIL   (FMU0->FSTAT & FMU_FSTAT_FAIL_MASK)
#define FMU_CHECK_SECURE (FMU0->FSTAT & FMU_FSTAT_CMDPRT_MASK)
#define FMU_CHECK_ERR    (FMU0->FSTAT & (FMU_FSTAT_ACCERR_MASK | FMU_FSTAT_FAIL_MASK | FMU_FSTAT_PVIOL_MASK))

#ifndef FLASH_PAGE_SIZE
#define FLASH_PAGE_SIZE 128
#endif
#ifndef FLASH_PHRASE_SIZE
#define FLASH_PHRASE_SIZE 16
#endif

#if defined(FMU0)
#define FLASH                   FMU0
#define FLASH_FSTAT_FAIL_MASK   FMU_FSTAT_FAIL_MASK
#define FLASH_FSTAT_CMDABT_MASK FMU_FSTAT_CMDABT_MASK
#define FLASH_FSTAT_PVIOL_MASK  FMU_FSTAT_PVIOL_MASK
#define FLASH_FSTAT_ACCERR_MASK FMU_FSTAT_ACCERR_MASK
#define FLASH_FSTAT_CWSABT_MASK FMU_FSTAT_CWSABT_MASK
#define FLASH_FSTAT_CCIF_MASK   FMU_FSTAT_CCIF_MASK
#define FLASH_FSTAT_CMDPRT_MASK FMU_FSTAT_CMDPRT_MASK
#define FLASH_FSTAT_CMDP_MASK   FMU_FSTAT_CMDP_MASK
#define FLASH_FSTAT_CMDDID_MASK FMU_FSTAT_CMDDID_MASK
#define FLASH_FSTAT_DFDIF_MASK  FMU_FSTAT_DFDIF_MASK
#define FLASH_FSTAT_PEWEN_MASK  FMU_FSTAT_PEWEN_MASK
#define FLASH_FSTAT_PERDY_MASK  FMU_FSTAT_PERDY_MASK
#elif defined(MSF1)
#define FLASH                   MSF1
#define FLASH_FSTAT_FAIL_MASK   MSF1_FSTAT_FAIL_MASK
#define FLASH_FSTAT_CMDABT_MASK MSF1_FSTAT_CMDABT_MASK
#define FLASH_FSTAT_PVIOL_MASK  MSF1_FSTAT_PVIOL_MASK
#define FLASH_FSTAT_ACCERR_MASK MSF1_FSTAT_ACCERR_MASK
#define FLASH_FSTAT_CWSABT_MASK MSF1_FSTAT_CWSABT_MASK
#define FLASH_FSTAT_CCIF_MASK   MSF1_FSTAT_CCIF_MASK
#define FLASH_FSTAT_CMDPRT_MASK MSF1_FSTAT_CMDPRT_MASK
#define FLASH_FSTAT_CMDP_MASK   MSF1_FSTAT_CMDP_MASK
#define FLASH_FSTAT_CMDDID_MASK MSF1_FSTAT_CMDDID_MASK
#define FLASH_FSTAT_DFDIF_MASK  MSF1_FSTAT_DFDIF_MASK
#define FLASH_FSTAT_PEWEN_MASK  MSF1_FSTAT_PEWEN_MASK
#define FLASH_FSTAT_PERDY_MASK  MSF1_FSTAT_PERDY_MASK
#endif

#if defined(SMSCM)
#define SMSCM_CACHE_CLEAR_MASK         SMSCM_OCMDR0_OCMCF2_MASK
#define SMSCM_CACHE_CLEAR(x)           SMSCM_OCMDR0_OCMCF2(x)
#define SMSCM_SPECULATION_DISABLE_MASK SMSCM_OCMDR0_OCMCF1_MASK
#endif

/* Default buffer size of the remaining data */
#ifndef EE_DATA_VALUE_REMAINING_PART
#define EE_DATA_VALUE_REMAINING_PART 16
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/* High level functions */
void EE_GetDefaultConfig(eeprom_emulation_config_t *config);
void EE_SetEepromEmulationInfo(eeprom_emulation_handle_t *handle, eeprom_emulation_config_t *config);
// void EE_DisableCache(FMC_Type *base);
// void EE_RestoreCache(FMC_Type *base);
uint32_t EE_Init(eeprom_emulation_handle_t *handle);
uint32_t EE_WriteData(eeprom_emulation_handle_t *handle, uint16_t dataID, uint32_t source);
uint32_t EE_ReadData(eeprom_emulation_handle_t *handle, uint16_t dataID, uint32_t *recordAddr);
uint32_t EE_ReportStatus(eeprom_emulation_handle_t *handle);
uint32_t EE_Deinit(eeprom_emulation_handle_t *handle);

#if (EE_USE_ASYNCHRONOUS_MODEL == true)
uint32_t EE_Main(eeprom_emulation_handle_t *handle);
#endif

/* Middle level functions */
uint32_t EE_NextSector(eeprom_emulation_handle_t *handle, uint32_t addr);
uint32_t EE_PrevSector(eeprom_emulation_handle_t *handle, uint32_t addr);
uint32_t EE_VerifyRecordStatus(eeprom_emulation_handle_t *handle, uint32_t dest, uint32_t expData);
uint32_t EE_VerifySectorHeader(eeprom_emulation_handle_t *handle, uint32_t dest, uint32_t expData);
uint32_t EE_MultiProgram(eeprom_emulation_handle_t *handle, uint32_t dest, uint32_t size, uint8_t *pData);
uint32_t EE_CopyRecord(eeprom_emulation_handle_t *handle,
                       eeprom_emulation_data_record_t dataRecord,
                       uint8_t remainData[]);
uint32_t EE_SwapSector(eeprom_emulation_handle_t *handle);
uint32_t EE_SearchInSector(eeprom_emulation_handle_t *handle, uint16_t expID, uint32_t sectorAddress);
uint32_t EE_SearchBlankSpace(eeprom_emulation_handle_t *handle, uint32_t sectorAddress);
uint32_t EE_SearchInAllActives(eeprom_emulation_handle_t *handle, uint16_t dataID);
uint32_t EE_SearchLoop(eeprom_emulation_handle_t *handle, uint16_t dataID);
uint32_t EE_BlankCheck(eeprom_emulation_handle_t *handle, uint32_t address, uint32_t size);
uint8_t EE_GetSectorStatus(eeprom_emulation_handle_t *handle, uint32_t sectorAddress);
uint32_t EE_FindActSector(eeprom_emulation_handle_t *handle, uint32_t sectorAddress, bool closestFlag, bool nextFlag);
uint8_t EE_GetSectorNumber(eeprom_emulation_handle_t *handle, uint8_t expStatus);
uint32_t EE_ValidateDeadIndicator(eeprom_emulation_handle_t *handle, uint32_t sectorAddress);
uint32_t EE_ValidateEraseCycle(eeprom_emulation_handle_t *handle, uint32_t sectorAddress, uint8_t *pData);
uint32_t EE_ValidateActIndicator(eeprom_emulation_handle_t *handle, uint32_t sectorAddress);
uint32_t EE_ReEraseEeprom(eeprom_emulation_handle_t *handle, uint32_t sectorAddress);
uint32_t EE_CheckAvailabilityStatus(eeprom_emulation_handle_t *handle);

#if (EE_CACHETABLE_ENABLE)
void EE_UpdateCacheTable(eeprom_emulation_handle_t *handle);
uint32_t EE_SearchInCache(uint16_t dataID);
#endif

#if (EE_USE_ASYNCHRONOUS_MODEL)
void INTERRUPT EE_ISRHandler(void);
#endif

/* Low level functions */
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_FlashEraseAll(eeprom_emulation_handle_t *handle));

uint32_t EE_FlashCheckErrorCode(void);
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_SyncFlashErase(eeprom_emulation_handle_t *handle, uint32_t destination));
#if (EE_USE_ASYNCHRONOUS_MODEL)
void EE_AsyncFlashErase(eeprom_emulation_handle_t *handle, uint32_t destination);
#endif

AT_QUICKACCESS_SECTION_CODE(uint32_t EE_FlashEraseVerifySection(
    eeprom_emulation_handle_t *handle, uint32_t destination, uint16_t Number, uint8_t marginLevel));
AT_QUICKACCESS_SECTION_CODE(uint32_t EE_SingleProgram(eeprom_emulation_handle_t *handle,
                                                      uint32_t destination,
                                                      uint8_t *pData));
uint32_t EE_SingleProgramCheck(eeprom_emulation_handle_t *handle,
                               uint32_t destination,
                               uint8_t *pExpectedData,
                               uint8_t marginLevel);
void FLASH_CACHE_Disable(void);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/
#endif /*FSL_EEPROM_EMULATION_H_*/
