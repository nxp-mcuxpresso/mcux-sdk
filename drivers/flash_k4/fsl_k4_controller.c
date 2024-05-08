/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_k4_controller.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name Flash controller command numbers
 * @{
 */
#define FLASH_VERIFY_ERASE_ALL        0x00U /*!< RD1ALL*/
#define FLASH_VERIFY_ERASE_BLOCK      0x01U /*!< RD1BLK*/
#define FLASH_VERIFY_ERASE_SECTOR     0x02U /*!< RD1SCR*/
#define FLASH_VERIFY_ERASE_PAGE       0x03U /*!< RD1PG*/
#define FLASH_VERIFY_ERASE_PHRASE     0x04U /*!< RD1PHR*/
#define FLASH_READ_INTO_MISR          0x05U /*!< RDMISR*/
#define FLASH_VERIFY_ERASE_IFR_SECTOR 0x12U /*!< RD1ISCR*/
#define FLASH_VERIFY_ERASE_IFR_PAGE   0x13U /*!< RD1IPG*/
#define FLASH_VERIFY_ERASE_IFR_PHRASE 0x14U /*!< RD1IPHR*/
#define FLASH_READ_IFR_INTO_MISR      0x15U /*!< RDIMISR*/
#define FLASH_PROGRAM_PAGE            0x23U /*!< PGMPG*/
#define FLASH_PROGRAM_PHRASE          0x24U /*!< PGMPHR*/
#define FLASH_ERASE_ALL               0x40U /*!< ERSALL*/
#define FLASH_ERASE_SECTOR            0x42U /*!< ERSSCR*/
/*@}*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void flash_command_pre_sequence(FMU_Type *base);

static void flash_command_sequence(FMU_Type *base);

static void flash_erase_sequence(FMU_Type *base, uint32_t start);

static void flash_pgm_sequence(FMU_Type *base, uint32_t start, uint32_t *src, uint8_t isPage);

/*! @brief Internal function Flash command*/
static status_t flash_command_complete(FMU_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t FLASH_CMD_EraseSector(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to erase a sector flash */
    base->FCCOB[0] = FLASH_ERASE_SECTOR;
    /* Erase Command sequence */
    flash_erase_sequence(base, start);
    /* check command completion and error handling */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_EraseAll(FMU_Type *base)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to erase all flash blocks */
    base->FCCOB[0] = FLASH_ERASE_ALL;
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_ProgramPhrase(FMU_Type *base, uint32_t start, uint32_t *src)
{
    status_t returnCode = kStatus_Fail;
    uint8_t isPage      = 0;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to program the flash block */
    base->FCCOB[0] = FLASH_PROGRAM_PHRASE;
    /* Program Command sequence */
    flash_pgm_sequence(base, start, src, isPage);
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_ProgramPage(FMU_Type *base, uint32_t start, uint32_t *src)
{
    status_t returnCode = kStatus_Fail;
    uint8_t isPage      = 1;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to program the flash block */
    base->FCCOB[0] = FLASH_PROGRAM_PAGE;
    /* Program Command sequence */
    flash_pgm_sequence(base, start, src, isPage);
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyErasePhrase(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* Fill in verify erase phrase command parameters. */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_PHRASE;
    base->FCCOB[2] = start;
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyErasePage(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* Fill in verify erase page command parameters. */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_PAGE;
    base->FCCOB[2] = start;
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyEraseSector(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* Fill in verify erase sector command parameters. */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_SECTOR;
    base->FCCOB[2] = start;
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyEraseIFRPhrase(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* Fill in verify erase ifr phrase command parameters. */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_IFR_PHRASE;
    base->FCCOB[2] = start;
    flash_command_sequence(base);
    /* calling flash command function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyEraseIFRPage(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* Fill in verify erase ifr page command parameters. */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_IFR_PAGE;
    base->FCCOB[2] = start;
    flash_command_sequence(base);
    /* calling flash command function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyEraseIFRSector(FMU_Type *base, uint32_t start)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* Fill in verify erase ifr sector command parameters. */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_IFR_SECTOR;
    base->FCCOB[2] = start;
    flash_command_sequence(base);
    /* calling flash command function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyEraseBlock(FMU_Type *base, uint32_t blockaddr)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to verify erase block command */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_BLOCK;
    base->FCCOB[2] = blockaddr;
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    return returnCode;
}

status_t FLASH_CMD_VerifyEraseAll(FMU_Type *base)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to verify erase all command */
    base->FCCOB[0] = FLASH_VERIFY_ERASE_ALL;
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);
    return returnCode;
}

status_t FLASH_CMD_ReadIntoMISR(FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to read into misr command */
    base->FCCOB[0] = FLASH_READ_INTO_MISR;
    base->FCCOB[2] = start;
    base->FCCOB[3] = ending;
    base->FCCOB[4] = seed[0];
    base->FCCOB[5] = seed[1];
    base->FCCOB[6] = seed[2];
    base->FCCOB[7] = seed[3];
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    if ((kStatus_FLASH_Success == returnCode) && (signature != NULL))
    {
        signature[0] = base->FCCOB[4];
        signature[1] = base->FCCOB[5];
        signature[2] = base->FCCOB[6];
        signature[3] = base->FCCOB[7];
    }

    return returnCode;
}

status_t FLASH_CMD_ReadIFRIntoMISR(FMU_Type *base, uint32_t start, uint32_t ending, uint32_t *seed, uint32_t *signature)
{
    status_t returnCode = kStatus_Fail;

    flash_command_pre_sequence(base);
    /* preparing passing parameter to read into misr command */
    base->FCCOB[0] = FLASH_READ_IFR_INTO_MISR;
    base->FCCOB[2] = start;
    base->FCCOB[3] = ending;
    base->FCCOB[4] = seed[0];
    base->FCCOB[5] = seed[1];
    base->FCCOB[6] = seed[2];
    base->FCCOB[7] = seed[3];
    flash_command_sequence(base);
    /* calling flash command sequence function to execute the command */
    returnCode = flash_command_complete(base);

    if ((kStatus_FLASH_Success == returnCode) && (signature != NULL))
    {
        signature[0] = base->FCCOB[4];
        signature[1] = base->FCCOB[5];
        signature[2] = base->FCCOB[6];
        signature[3] = base->FCCOB[7];
    }

    return returnCode;
}

/*!
 * @brief FLASH Command Pre Sequence
 *
 * This function is used to perform the check before loading FCCOB registers
 *
 * @param
 * @return
 */
#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && (FLASH_DRIVER_IS_FLASH_RESIDENT == 1)
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__((section(".ramfunc"))) __attribute__((__noinline__))
#endif
#endif
static void flash_command_pre_sequence(FMU_Type *base)
{
    if ((base->FSTAT & FLASH_FSTAT_DFDIF_MASK) != 0U)
    {
        /* Acknowledge previous ECC fault. The fault occured during a previous read or verify erase but too late to  */
        base->FSTAT = FLASH_FSTAT_DFDIF_MASK;
    }
    // Check if previous command complete, CCIF==1, wait for CCIF set
    while (((base->FSTAT) & FLASH_FSTAT_CCIF_MASK) == 0U)
    {
    }

    /* clear CMDABT & ACCERR & PVIOL flag in flash status register */
    base->FSTAT = (FLASH_FSTAT_CMDABT_MASK | FLASH_FSTAT_ACCERR_MASK | FLASH_FSTAT_PVIOL_MASK);
}

/*!
 * @brief FLASH Command Pre Sequence
 *
 * This function is used to perform launching command and wait for completion
 *
 * @param
 * @return
 */
#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && (FLASH_DRIVER_IS_FLASH_RESIDENT == 1)
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__((section(".ramfunc"))) __attribute__((__noinline__))
#endif
#endif
static void flash_command_sequence(FMU_Type *base)
{
    /* clear CCIF bit to launch the command */
    base->FSTAT = FLASH_FSTAT_CCIF_MASK;

    /* Check CCIF bit of the flash status register, wait till it is set */
    while ((base->FSTAT & FLASH_FSTAT_CCIF_MASK) == 0U)
    {
    }
}

/*!
 * @brief Flash Erase Sector(ERSSCR) Command
 *
 * This function is used to perform the erase sector command sequence to the flash.
 *
 * @param driver Pointer to storage for the driver runtime state.
 * @return
 */
#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && (FLASH_DRIVER_IS_FLASH_RESIDENT == 1)
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__((section(".ramfunc"))) __attribute__((__noinline__))
#endif
#endif
static void flash_erase_sequence(FMU_Type *base, uint32_t start)
{
    /* clear CCIF bit to launch the command */
    base->FSTAT = FLASH_FSTAT_CCIF_MASK;

    while ((base->FSTAT & FLASH_FSTAT_PEWEN_MASK) == 0U)
    {
    }

    for (uint32_t i = 0u; i < 4u; i++)
    {
        *((uint32_t *)(start + i * 4U)) = 0x0U;
    }

    while ((base->FSTAT & FLASH_FSTAT_PERDY_MASK) == 0U)
    {
    }

    base->FSTAT = FLASH_FSTAT_PERDY_MASK;

    /* Check CCIF bit of the flash status register, wait till it is set */
    while ((base->FSTAT & FLASH_FSTAT_CCIF_MASK) == 0U)
    {
    }
}

/*!
 * @brief Flash Program Command
 *
 * This function is used to perform the program command sequence to the flash.
 *
 * @param driver Pointer to storage for the driver runtime state.
 * @return
 */
#if defined(FLASH_DRIVER_IS_FLASH_RESIDENT) && (FLASH_DRIVER_IS_FLASH_RESIDENT == 1)
#if defined(__IAR_SYSTEMS_ICC__)
__ramfunc
#elif defined(__GNUC__)
__attribute__((section(".ramfunc"))) __attribute__((__noinline__))
#endif
#endif
static void flash_pgm_sequence(FMU_Type *base, uint32_t start, uint32_t *src, uint8_t isPage)
{
    /* clear CCIF bit to launch the command */
    base->FSTAT = FLASH_FSTAT_CCIF_MASK;

    while ((base->FSTAT & FLASH_FSTAT_PEWEN_MASK) == 0U)
    {
    }

    uint8_t lengthInWord;

    if (isPage == 1U)
    {
        lengthInWord = FLASH_FEATURE_PAGE_SIZE_IN_WORD;
    }
    else
    {
        lengthInWord = FLASH_FEATURE_PHRASE_SIZE_IN_WORD;
    }

    for (uint32_t i = 0; i < lengthInWord; i++)
    {
        *((uint32_t *)(start + i * 4U)) = src[i];
    }

    while ((base->FSTAT & FLASH_FSTAT_PERDY_MASK) == 0U)
    {
    }

    base->FSTAT = FLASH_FSTAT_PERDY_MASK;

    /* Check CCIF bit of the flash status register, wait till it is set */
    while ((base->FSTAT & FLASH_FSTAT_CCIF_MASK) == 0U)
    {
    }
}

/*!
 * @brief FLASH Command
 *
 * This function is used to perform the program/erase command sequence to the flash.
 *
 * @param driver Pointer to storage for the driver runtime state.
 * @return An error code or kStatus_FLASH_Success
 */
static status_t flash_command_complete(FMU_Type *base)
{
    uint32_t registerValue;

    /* Check error bits */
    /* Get flash status register value */
    registerValue   = base->FSTAT;
    status_t status = kStatus_Fail;

    /* checking access error */
    if ((registerValue & FLASH_FSTAT_ACCERR_MASK) != 0U)
    {
        status = kStatus_FLASH_AccessError;
    }
    /* checking protection error */
    else if ((registerValue & FLASH_FSTAT_PVIOL_MASK) != 0U)
    {
        status = kStatus_FLASH_ProtectionViolation;
    }
    /* check  protection level */
    else if ((registerValue & FLASH_FSTAT_CMDABT_MASK) != 0U)
    {
        status = kStatus_FLASH_CommandAborOption;
    }
    else if ((registerValue & FLASH_FSTAT_FAIL_MASK) != 0U)
    {
        status = kStatus_FLASH_CommandFailure;
    }
    else if ((registerValue & FLASH_FSTAT_DFDIF_MASK) != 0U)
    {
        status      = kStatus_FLASH_EccFaultDetected;
        base->FSTAT = FLASH_FSTAT_DFDIF_MASK;
    }
    else
    {
        status = kStatus_FLASH_Success;
    }
    return status;
}
