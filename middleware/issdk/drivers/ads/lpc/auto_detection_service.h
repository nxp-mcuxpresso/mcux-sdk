/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file auto_detection_service.h
 * @brief The auto_detection_service.h file describes the structures and definitions for a
 * service that automatically detects the LPC board and Sensor Shield.
 */

#ifndef AUTO_DETECTION_SERVICE_H_
#define AUTO_DETECTION_SERVICE_H_

#include <stdio.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ADS_NO_WHO_AM_I (0xFFFF)      // Special value if sensor doesn't have WHO_AM_I register.
#define ADS_MAX_STRING_LENGTH (64)    // Maximum length for sub-strings.
#define ADS_FLASH_STRING_LENGTH (128) // Maximum length of flash string.
#define ADS_NO_SHIELD_DETECTED (0xFFFFFFFF)
#define ADS_COOKIE_VALUE (0xDEADBEEF)

/*!
 * @brief This defines the return status.
 */
typedef enum ADS_Status
{
    ADS_OK,   /* Sensor Detection status : "Found". */
    ADS_FAIL, /* Sensor Detection status : "Not Found". */
    ADS_NULL  /* Sensor Detection status : "Dont Care". */
} ADS_Status_t;

/*!
 * @brief This defines the allowed communications channels.
 */
typedef enum ADS_Channel
{
    ADS_I2C_INT,
    ADS_I2C_EXT,
    ADS_SPI_DEV,
} ADS_Channel_t;

/*!
 * @brief This defines the allowed communications channels.
 */
typedef enum ADS_Sensor
{
    FXAS21002,
    FXLC95000,
    FXLS8471,
    FXLS8962,
    FXOS8700,
    FXPQ3115,
    MAG3110,
    MMA845x,
    MMA865x,
    MMA8491,
    MMA9553,
    MPL3115,
    DIFF_P,
} ADS_Sensor_t;

/*!
 * @brief This enumeration defines the FRDM boards that ADS can detect.
 */
typedef enum
{
    ADS_LPC_54113J128,
    ADS_LPC_54113J256,
    ADS_LPC_54114J256,
    ADS_NO_BOARD_DETECTED
} ADS_SupportedBoards_t;

/*!
 * @brief This enumeration defines the ADS Flash storage status.
 */
typedef enum
{
    ADS_NO_FLASH_RECORD,
    ADS_FLASH_RECORD_CHANGE,
    ADS_FLASH_RECORD_NO_CHANGE
} ADS_FlashStatus_t;

/*!
 * @brief This defines a record type to store the expected field values of the LPC device ID.
 */
typedef struct
{
    uint32_t mcuDeviceId;        // MCU Specific Device ID
    ADS_SupportedBoards_t board; // MCU Board corresponding to Device ID value.
} mcuDEVID_t;

/*!
 * @brief This defines a record type to store the communication channel info and WHO_AM_I address/value for various
 * Sensor Shields.
 */
typedef struct
{
    ADS_Channel_t channel; // Channel type over which to attempt communications.
    uint32_t slaveAddr;    // I2C Slave Address or Chip-Select value.
    uint32_t whoAmIAddr;   // WHO_AM_I Register Address (Offset).
    uint32_t whoAmIValue;  // WHO_AM_I Register Value.
    uint8_t whoAmIMask;    // The Mask for Fixed who ami i bits for sensors with variants.
} sensorAccess_t;

/*!
 * @brief This defines a record type to store ADS results string in Flash memory.
 */
typedef struct
{
    uint32_t cookie;                         // A unique 32-bit value unlikely to be randomly found in Flash.
    uint32_t length;                         // Length of the ADS result string in bytes.
    char ADSString[ADS_FLASH_STRING_LENGTH]; // The ADS results string.
} ADSFlashRecord_t;

/******************************************************************************/
/*! @brief       The function to register Application Name and initialte ADS.
 *  @details     The API will read the Application Name from the user and return
 *               the result string with the ADS detection results. It will also update
 *               the FLASH with the new results.
 *  @param[in]     pAppName - pointer to a buffer where the application name is placed.
 *  @param[in/out] boardString - pointer to a buffer to place the ADS board string.
 *  @param[in/out] shieldString - pointer to a buffer to place the ADS shield string.
 *  @param[in]     bufferLength - Length of output buffers.
 *  @Constraints In case the combined string to be written to flash becomes greater than
 *               permissible, it will be truncated and may lead to unexpected results.
 *  @Return      void
 *  @Reentrant   No
 */
void BOARD_RunADS(const char *appName, char *boardString, char *shieldString, size_t bufferLength);

#endif // AUTO_DETECTION_SERVICE_H_
