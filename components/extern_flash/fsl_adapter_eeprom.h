/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EEPROM_H_
#define _EEPROM_H_

/*!
 * @addtogroup EEPROM_Adapter
 * @{
 */

/*!*********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

/*!*********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#ifndef GET_EEPROM_SIZE
#define GET_EEPROM_SIZE 0
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/*! @brief List of the EEPROM status */
typedef enum _eeprom_status
{
    kStatus_EeSuccess         = kStatus_Success,                            /*!< Success */
    kStatus_EeTooBig          = MAKE_STATUS(kStatusGroup_EXTERN_EEPROM, 1), /*!< Too big */
    kStatus_EeNotAligned      = MAKE_STATUS(kStatusGroup_EXTERN_EEPROM, 2), /*!< Not Aligned */
    kStatus_EeBusy            = MAKE_STATUS(kStatusGroup_EXTERN_EEPROM, 3), /*!< Busy */
    kStatus_EeError           = MAKE_STATUS(kStatusGroup_EXTERN_EEPROM, 4), /*!< Error */
    kStatus_EeInvalidArgument = MAKE_STATUS(kStatusGroup_EXTERN_EEPROM, 5), /*!< Invalid Argument */
} eeprom_status_t;

/*! @brief List of the EEPROM devices type used on each of the FSL development boards */
typedef enum _eeprom_type
{
    kEEPROM_DeviceNone = 0x00U,  /*!< None eeprom device*/
    kEEPROM_DeviceInternalFlash, /*!< Use internal flash */
    kEEPROM_DeviceAT45DB161E,    /*!< TWR-KW2x */
    kEEPROM_DeviceAT26DF081A,    /*!< TWR-MEM  */
    kEEPROM_DeviceAT45DB021E,    /*!< FRDM-KW40 */
    kEEPROM_DeviceAT45DB041E,    /*!< FRDM-KW41*/
    kEEPROM_DeviceMX25R3235F,    /*!< FRDM-K32W */
} eeprom_type_t;

/*! @brief eeprom config. */
typedef struct _eeprom_config
{
    eeprom_type_t eeType;          /*!< eeprom type*/
    uint32_t spiBase;              /*!< spi base*/
    uint32_t spiSrcClock_Hz;       /*!< spi clock*/
    uint8_t spiInstance;           /*!< spi instance*/
    uint8_t csGpioPort;            /*!< gpio port*/
    uint8_t csGpiopin;             /*!< gpio pin*/
    uint8_t csGpiopinStateDefault; /*!< gpio default state*/
} eeprom_config_t;

/*! @brief eeprom property tag. */
typedef enum _eeprom_property_tag
{
    kEEPROM_PropertySectorSize = 0x00U, /*!< sector size property.*/
    kEEPROM_PropertyTotalSize  = 0x01U, /*!< total size property.*/
} eeprom_property_tag_t;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initializes the EEPROM peripheral with the user configuration structure.
 *
 * For Initializes eeprom peripheral,
 *  @code
 *   eeConfig.eeType = kEEPROM_DeviceAT45DB041E;
 *   eeConfig.spiBase = SPI0_BASE;
 *   eeConfig.spiSrcClock_Hz = CLOCK_GetFreq(DSPI0_CLK_SRC);
 *   eeConfig.csGpioPort = 2;
 *   eeConfig.csGpiopin =  19;
 *   eeConfig.csGpiopinStateDefault = 1;
 *
 *   if (kStatus_EeSuccess != EEPROM_Init(&eeConfig))
 *   {
 *       PRINTF("\r\n EEPROM_Init failure\r\n");
 *   }
 *  @endcode
 * @param eeConfig pointer to user-defined EEPROM configuration structure.
 * @retval kStatus_EeSuccess EEPROM initialization succeed.
 * @retval kStatus_EeError An error occurred.
 */
eeprom_status_t EEPROM_Init(eeprom_config_t *eepromConfig);

/*!
 * \brief  Reads the specified number of bytes from EEPROM memory
 *
 * @param noOfBytes         Number of bytes to be read
 * @param addr2eeprom       EEPROM address to start reading from
 * @param inbuf             A pointer to a memory location where the data read out from EEPROM
 *                          will be stored
 *
 * @retval #kStatus_EeSuccess if the read operation completed successfully.
 * @retval #kStatus_EeTooBig if the provided address is out of range.
 *
 */
eeprom_status_t EEPROM_ReadData(uint16_t noOfBytes,   /* IN: No of bytes to read */
                                uint32_t addr2eeprom, /* IN: EEPROM address to start reading from */
                                uint8_t *inbuf        /* OUT:Pointer to read buffer */
);

/*!
 * \brief  Writes the specified number of bytes to EEPROM memory
 *
 * @param noOfBytes       Number of bytes to be written
 * @param addr2eeprom     EEPROM address to start writing at
 * @param Outbuf          A pointer to a memory location where the data to be written is stored.
 *
 * @retval #kStatus_EeSuccess if the write operation completed successfully.
 * @retval #kStatus_EeTooBig  if the provided address is out of range.
 *
 */
eeprom_status_t EEPROM_WriteData(uint32_t noOfBytes,   /* IN: No of bytes to write */
                                 uint32_t addr2eeprom, /* IN: EEPROM address to start writing at. */
                                 uint8_t *Outbuf       /* IN: Pointer to data to write to EEPROM */
);

/*!
 * \brief   This function erase a block of memory
 *
 * @param addr2eeprom     EEPROM address to erase
 * @param size            Erase size
 *
 * @retval #kStatus_EeSuccess if the write operation completed successfully.
 * @retval #kStatus_EeTooBig  if the provided address is out of range.
 *
 */
eeprom_status_t EEPROM_EraseBlock(uint32_t addr2eeprom, uint32_t size);

/*!
 * \brief    This function erase the entire EEPROM memory
 *
 * @retval #kStatus_EeSuccess if the write operation completed successfully.
 * @retval #kStatus_EeTooBig  if the provided address is out of range.
 *
 */
eeprom_status_t EEPROM_ChipErase(void);

/*!
 * @brief Returns the desired hal EEPROM device property.
 *
 * @param Property          The desired property from the list of properties in
 *                          enum eeprom_property_tag_t
 * @param value           A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_NotSupport Flash currently not support.
 */
#if (defined(GET_EEPROM_SIZE) && (GET_EEPROM_SIZE > 0))
eeprom_status_t EEPROM_GetProperty(eeprom_property_tag_t property, uint32_t *value);
#endif

#ifdef __cplusplus
}
#endif
/*! @} */
#endif /* _EEPROM_H_ */
