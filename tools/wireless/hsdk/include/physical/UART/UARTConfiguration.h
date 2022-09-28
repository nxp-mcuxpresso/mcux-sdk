/*
 * \file UARTConfiguration.h
 * This is the header file for the UARTConfiguration module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __UART_CONFIGURATION__
#define __UART_CONFIGURATION__

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>
#include <time.h>

#include "hsdkOSCommon.h"

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/**
 * @brief Baudrate values for opening a UART device.
 */
typedef enum {
    BR110,
    BR300,
    BR600,
    BR1200,
    BR2400,
    BR4800,
    BR9600,
    BR19200,
    BR38400,
    BR57600,
    BR115200,
    BR921600,
	BR1000000,
} Baudrate;

/**
 * @brief Parity values for opening a UART device.
 */
typedef enum {
    NO_PARITY,
    EVEN_PARITY,
    ODD_PARITY,
    MARK_PARITY,
    SPACE_PARITY
} ParityType;

/**
 * @brief Possible byte size values for opening a UART device.
 */
typedef enum {
    FIVEBITS,
    SIXBITS,
    SEVENBITS,
    EIGHTBITS
} ByteSize;

/**
 * @brief Possible stop bits values for opening a UART device.
 */
typedef enum {
    ONE_STOPBIT,
    ONE_HALF_STOPBITS,
    TWO_STOPBITS
} StopBits;

/**
 * @brief Enumeration for setting the Data Terminal Ready (DTR) mode.
 */
typedef enum {
    DISABLEDTR,
    ENABLEDTR,
    DTRHANDSHAKE
} DtrControl;

/**
 * @brief Enumeration for setting the Request To Send (RTS) mode.
 */
typedef enum {
    DISABLERTS,
    ENABLERTS,
    RTSHANDSHAKE,
    RTSTOGGLE
} RtsControl;

/**
 * @brief Structure to encompass the attributes required for configurations
 * regarding line properties.
 */
typedef struct {
    Baudrate baudrate;              /**< The baudrate. */
    ParityType parity;              /**< If parity is enabled or not. */
    ByteSize byteSize;              /**< The size of a byte during communication. */
    StopBits stopBits;              /**< The number of bits used to signal stop. */
    DtrControl handleDTRControl;    /**< The method in which to handle Data Terminal Ready flow control. */
    RtsControl handleRTSControl;    /**< The method in which to handle Request To Send flow control. */
    uint8_t handleDSRControl;       /**< The method in which to handle Data Set Ready flow control. */
    uint8_t outX;                   /**< Whether to enable flow control on output. */
    uint8_t inX;                    /**< Whether to enable flow control on input. */
    uint8_t outCtsFlow;             /**< Whether to enable CTS flow control on input. */
    uint8_t outDsrFlow;             /**< Whether to enable DSR flow control on input. */
    uint32_t XonLim;				/**< Transmit X-ON threshold. */
    uint32_t XoffLim;				/**< Transmit X-OFF threshold. */
    uint8_t dsrSensitivity;         /**< The method in which to handle DSR Sensitivity. */
    uint8_t abortOnError;			/**< Abort all reads and writes on Error. */
} UARTLineConfig;

/**
 * @brief Structure to encompass the attributes required for configurations
 * regarding timeout properties.
 */
typedef struct {
    uint32_t readTime;              /**< The timeout for a read operation. */
    uint32_t readTimeMultiplier;    /**< The timeout multiplier for a read operation. */
    uint32_t readTotalTime;         /**< A constant for the timeout of the entire read operation. */
    uint32_t writeTime;             /**< The timeout for a write operation. */
    uint32_t writeTimeMultiplier;   /**< The timeout multiplier for a write operation. */
} UARTTimeConfig;


/**
 * @brief Structure to encompass the attributes required for configuration.
 */
typedef struct {
    UARTLineConfig *lineConfig; /**< Pointer to the UART line configuration structure. */
    UARTTimeConfig *timeConfig; /**< Pointer to the UART timeout configuration structure. */
} UARTConfigurationData;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
DLLEXPORT void setDefaultLineConfig(UARTLineConfig *);
DLLEXPORT void setDefaultTimeConfig(UARTTimeConfig *);
DLLEXPORT UARTConfigurationData *defaultConfigurationData();
DLLEXPORT void freeConfigurationData(UARTConfigurationData *);
DLLEXPORT void setBaudrate(UARTConfigurationData *, Baudrate);
DLLEXPORT void disableFlowControl(UARTConfigurationData *);
void setParity(UARTConfigurationData *config, ParityType pt);
int InitPort(File portHandle, UARTConfigurationData *config);

#ifdef __cplusplus
}
#endif

#endif
