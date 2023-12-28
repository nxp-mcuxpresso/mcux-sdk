/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_EEPROM_H_
#define FSL_EEPROM_H_

#include "fsl_common.h"
#include "fsl_power.h"
/*!
 * @addtogroup eeprom
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief EEPROM driver version 2.1.3. */
#define FSL_EEPROM_DRIVER_VERSION (MAKE_VERSION(2, 1, 3))
/*! @} */

/*! @brief EEPROM automatic program option */
typedef enum _eeprom_auto_program
{
    kEEPROM_AutoProgramDisable   = 0x0, /*!< Disable auto program */
    kEEPROM_AutoProgramWriteWord = 0x1, /*!< Auto program triggered after 1 word is written */
    kEEPROM_AutoProgramLastWord  = 0x2  /*!< Auto program triggered after last word of a page written */
} eeprom_auto_program_t;

/*! @brief EEPROM interrupt source */
typedef enum _eeprom_interrupt_enable
{
    kEEPROM_ProgramFinishInterruptEnable = EEPROM_INTENSET_PROG_SET_EN_MASK, /*!< Interrupt while program finished */
} eeprom_interrupt_enable_t;

/*!
 * @brief EEPROM region configuration structure.
 */
typedef struct _eeprom_config
{
    eeprom_auto_program_t autoProgram; /*!< Automatic program feature. */
    uint8_t readWaitPhase1;            /*!< EEPROM read waiting phase 1 */
    uint8_t readWaitPhase2;            /*!< EEPROM read waiting phase 2 */
    uint8_t writeWaitPhase1;           /*!< EEPROM write waiting phase 1 */
    uint8_t writeWaitPhase2;           /*!< EEPROM write waiting phase 2 */
    uint8_t writeWaitPhase3;           /*!< EEPROM write waiting phase 3 */
    bool lockTimingParam;              /*!< If lock the read and write wait phase settings */
} eeprom_config_t;

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

/*!
 * @brief Initializes the EEPROM with the user configuration structure.
 *
 * This function configures the EEPROM module with the user-defined configuration. This function also sets the
 * internal clock frequency to about 155kHz according to the source clock frequency.
 *
 * @param base     EEPROM peripheral base address.
 * @param config   The pointer to the configuration structure.
 * @param sourceClock_Hz EEPROM source clock frequency in Hz.
 */
void EEPROM_Init(EEPROM_Type *base, const eeprom_config_t *config, uint32_t sourceClock_Hz);

/*!
 * @brief Get EEPROM default configure settings.
 *
 * @param config  EEPROM config structure pointer.
 */
void EEPROM_GetDefaultConfig(eeprom_config_t *config);

/*!
 * @brief Deinitializes the EEPROM regions.
 *
 * @param base     EEPROM peripheral base address.
 */
void EEPROM_Deinit(EEPROM_Type *base);

/*! @} */

/*!
 * @name Basic Control Operations
 * @{
 */

/*!
 * @brief Set EEPROM automatic program feature.
 *
 * EEPROM write always needs a program and erase cycle to write the data into EEPROM. This program and erase cycle can
 * be finished automaticlly or manually. If users want to use or disable auto program feature, users can call this API.
 *
 * @param base     EEPROM peripheral base address.
 * @param autoProgram EEPROM auto program feature need to set.
 */
static inline void EEPROM_SetAutoProgram(EEPROM_Type *base, eeprom_auto_program_t autoProgram)
{
    base->AUTOPROG = (uint32_t)autoProgram;
}

/*!
 * @brief Set EEPROM to in/out power down mode.
 *
 * This function make EEPROM eneter or out of power mode. Notice that, users shall not put EEPROM into power down mode
 * while there is still any pending EEPROM operation. While EEPROM is wakes up from power down mode, any EEPROM
 * operation has to be suspended for 100 us.
 *
 * @param base     EEPROM peripheral base address.
 * @param enable   True means enter to power down mode, false means wake up.
 */
static inline void EEPROM_SetPowerDownMode(EEPROM_Type *base, bool enable)
{
    base->PWRDWN = (uint32_t)enable;
}

/*!
 * @brief Enable EEPROM interrupt.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt enable mask. It is a logic OR of members the
 *                 enumeration :: eeprom_interrupt_enable_t
 */
static inline void EEPROM_EnableInterrupt(EEPROM_Type *base, uint32_t mask)
{
    base->INTENSET = mask;
}

/*!
 * @brief Disable EEPROM interrupt.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt enable mask. It is a logic OR of members the
 *                 enumeration :: eeprom_interrupt_enable_t
 */
static inline void EEPROM_DisableInterrupt(EEPROM_Type *base, uint32_t mask)
{
    base->INTENCLR = mask;
}

/*!
 * @brief Get the status of all interrupt flags for ERPROM.
 *
 * @param base     EEPROM peripheral base address.
 * @return EEPROM interrupt flag status
 */
static inline uint32_t EEPROM_GetInterruptStatus(EEPROM_Type *base)
{
    return base->INTSTAT;
}

/*!
 * @brief Clear interrupt flags manually.
 *
 * This API clears interrupt flags manually. Call this API will clear the corresponding bit in INSTAT register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt flag need to be cleared. It is a logic OR of members of
 *                 enumeration:: eeprom_interrupt_enable_t
 */
static inline void EEPROM_ClearInterruptFlag(EEPROM_Type *base, uint32_t mask)
{
    base->INTSTATCLR = mask;
}

/*!
 * @brief Get the status of enabled interrupt flags for ERPROM.
 *
 * @param base     EEPROM peripheral base address.
 * @return EEPROM enabled interrupt flag status
 */
static inline uint32_t EEPROM_GetEnabledInterruptStatus(EEPROM_Type *base)
{
    return base->INTEN;
}

/*!
 * @brief Set interrupt flags manually.
 *
 * This API trigger a interrupt manually, users can no need to wait for hardware trigger interrupt. Call this API will
 * set the corresponding bit in INSTAT register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt flag need to be set. It is a logic OR of members of
 *                 enumeration:: eeprom_interrupt_enable_t
 */
static inline void EEPROM_SetInterruptFlag(EEPROM_Type *base, uint32_t mask)
{
    base->INTSTATSET = mask;
}

/*!
 * @brief Write a word data in address of EEPROM.
 *
 * Users can write a page or at least a word data into EEPROM address.
 *
 * @param base     EEPROM peripheral base address.
 * @param offset   Offset from the begining address of EEPROM. This value shall be 4-byte aligned.
 * @param data     Data need be write.
 */
status_t EEPROM_WriteWord(EEPROM_Type *base, uint32_t offset, uint32_t data);

/*!
 * @brief Write data from a user allocated buffer in address of EEPROM.
 *
 * Users can write any bytes data into EEPROM address by wBuf.
 *
 * @param base     EEPROM peripheral base address.
 * @param offset   Offset from the begining address of EEPROM.
 * @param wBuf     Data need be write.
 * @param size     Number of bytes to write.
 */
void EEPROM_Write(EEPROM_Type *base, uint32_t offset, void *wBuf, uint32_t size);

/*!
 * @name Data Check Operations
 * @{
 */
#if !(defined(FSL_FEATURE_EEPROM_PAGE_COUNT) && FSL_FEATURE_EEPROM_PAGE_COUNT)
/*!
 * @brief read eeprom device status manually.
 *
 * This API read eeprom device status manually. Call this API will read the corresponding bit in STATUS register.
 *
 * @param base     EEPROM peripheral base address.
 */
static inline uint32_t EEPROM_GetDeviceStatus(EEPROM_Type *base)
{
    return base->STATUS;
}

/*!
 * @brief read ecc error count manually.
 *
 * This API read ecc error count manually. Call this API will read the corresponding bit in ECCERRCNT register.
 *
 * @param base     EEPROM peripheral base address.
 */
static inline uint32_t EEPROM_GetEccErrorCount(EEPROM_Type *base)
{
    return base->ECCERRCNT;
}

/*!
 * @brief set ecc error count manually.
 *
 * This API set ecc error count manually. Call this API will set the corresponding bit in ECCERRCNT register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     The mask of ecc error status.
 */
static inline void EEPROM_SetEccErrorCount(EEPROM_Type *base, uint32_t mask)
{
    base->ECCERRCNT = mask;
}

/*!
 * @brief set checksum start address manually.
 *
 * This API set checksum start address manually. Call this API will set the corresponding bit in MSSTART register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     The mask of checksum start address.
 */
static inline void EEPROM_SetCheckStartAddress(EEPROM_Type *base, uint32_t mask)
{
    base->MSSTART = mask;
}
/*!
 * @brief set checksum stop address manually.
 *
 * This API set checksum stop address manually. Call this API will set the corresponding bit in MSSTOP register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     The mask of checksum stop address.
 */
static inline void EEPROM_SetCheckStopAddress(EEPROM_Type *base, uint32_t mask)
{
    base->MSSTOP = mask;
}

/*!
 * @brief read data signature manually.
 *
 * This API read data signature manually. Call this API will clear the corresponding bit in MSDATASIG register.
 *
 * @param base     EEPROM peripheral base address.sss
 *
 */
static inline uint32_t EEPROM_GetDataSignature(EEPROM_Type *base)
{
    return base->MSDATASIG;
}

/*!
 * @brief read parity signature manually.
 *
 * This API read parity signature manually. Call this API will clear the corresponding bit in MSPARSIG register.
 *
 * @param base     EEPROM peripheral base address.
 */
static inline uint32_t EEPROM_GetParitySignature(EEPROM_Type *base)
{
    return base->MSPARSIG;
}

/*!
 * @brief Write a row data into EEPROM.
 *
 * Users can write a row or at least a word data into EEPROM address.
 *
 * @param base     EEPROM peripheral base address.
 * @param rowNum  Row number to be written.
 * @param data     Data need be write. This array data size shall equals to the row size.
 */
status_t EEPROM_WriteRow(EEPROM_Type *base, uint32_t rowNum, uint32_t *data);

/*!
 * @brief Write a page data into EEPROM.
 *
 * Users can write a page or at least a word data into EEPROM address.
 *
 * @param base     EEPROM peripheral base address.
 * @param pageNum  Page number to be written.
 * @param data     Data need be write. This array data size shall equals to the page size.
 */
#else
status_t EEPROM_WritePage(EEPROM_Type *base, uint32_t pageNum, uint32_t *data);
#endif /* FSL_FEATURE_EEPROM_PAGE_COUNT */

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/
#endif /*FSL_EEPROM_H_*/
